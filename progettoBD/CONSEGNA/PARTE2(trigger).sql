SET search_path TO 'socialmarket';
SET datestyle to 'MDY';

-- Test basati sulle insert presenti nello script di popolamento del database socialmarket

--E(a)
-- verifica del vincolo che nessun volontario possa essere assegnato a più attività contemporanee
CREATE OR REPLACE FUNCTION turniOverlap()
RETURNS TRIGGER AS
$$
BEGIN
	-- Se esiste un turno per il volontario con date che vanno in overlap con il nuovo...
	IF EXISTS (
		SELECT (orarioInizio, orarioFine) OVERLAPS (NEW.orarioFine, NEW.orarioFine)
		FROM TURNI
		WHERE cfV = NEW.cfV AND dataTurno = NEW.dataTurno 
	)
	THEN
		RAISE EXCEPTION 'Overlap su turni'; -- ...eccezione
	END IF;
	
	RETURN NEW; -- sennò si ritorna NEW (trigger BEFORE)
END;
$$ language plpgsql;

CREATE TRIGGER attivitaContemporanee
BEFORE INSERT OR UPDATE ON TURNI
FOR EACH ROW
EXECUTE PROCEDURE turniOverlap();

--UTILE PER TESTING:
--INSERT INTO TURNI VALUES ('30000','11-18-2023','9:15','17:05','GHKMNB09876545');
--DROP TRIGGER IF EXISTS attivitaContemporanee on socialmarket.TURNI;

--E(b) TRIGGER 1
-- mantenimento della disponibilità corrente dei prodotti (1)

-- INSERT in MERCI --> + su INVENTARIO
-- DELETE in MERCI --> - su INVENTARIO
-- UPDATE in MERCI --> +/- su INVENTARIO
CREATE OR REPLACE FUNCTION merciChange()
RETURNS TRIGGER AS
$$
BEGIN
	-- Si guarda alla variabile TG_OP per differenziare in base all'op. (v.nota sopra)
	IF (TG_OP = 'INSERT') THEN
		UPDATE INVENTARIO SET QuantitaInv = QuantitaInv + NEW.quantita 
		WHERE idProdotto = NEW.prod; -- con INSERT si ha accesso a NEW
	ELSEIF (TG_OP = 'DELETE') THEN
		UPDATE INVENTARIO SET QuantitaInv = QuantitaInv - OLD.quantita 
		WHERE idProdotto = OLD.prod; -- con DELETE si ha accesso a OLD
	ELSE
		UPDATE INVENTARIO SET QuantitaInv = QuantitaInv + (NEW.quantita - OLD.quantita)
		WHERE idProdotto = NEW.prod;
	END IF;												
	RETURN null;
END;
$$ language plpgsql;

--DROP TRIGGER disp ON MERCI;
CREATE TRIGGER disp
AFTER UPDATE OR INSERT OR DELETE ON MERCI
FOR EACH ROW
EXECUTE PROCEDURE merciChange();

-- Test sulle quantità del prodotto mozzarella
--SELECT * FROM MERCI;
--SELECT * FROM INVENTARIO;
--INSERT INTO MERCI VALUES ('60006','10','7','10-01-2020','13:00','5-01-2022','LKJMNB09876541', NULL,'30000',1);
--SELECT * FROM MERCI;
--SELECT * FROM INVENTARIO;
--UPDATE MERCI SET Quantita = 100 WHERE idlotto = 60000;
--SELECT * FROM MERCI;
--SELECT * FROM INVENTARIO;
--UPDATE MERCI SET Quantita = 80 WHERE idlotto = 60000;
--SELECT * FROM MERCI;
--SELECT * FROM INVENTARIO;
--DELETE FROM MERCI WHERE idlotto = 60006;

--E(b) TRIGGER 2
-- mantenimento della disponibilità corrente dei prodotti (2)

-- INSERT in ACQUISTI --> - su INVENTARIO (tramite trigger in cascata)
-- SE tento di acquistare più prodotti di quelli disponibili si viola:
-- "inventario_quantitainv_check" (check su quantitaInv >= 0)
CREATE OR REPLACE FUNCTION acquistiChange()
RETURNS TRIGGER AS
$$
BEGIN
	-- update su merci --> poi trigger disp in cascata
	UPDATE MERCI SET quantita = quantita - NEW.quantitaRif  
	WHERE idLotto = NEW.idLotto;											
	RETURN null;
END;
$$ language plpgsql;

--DROP TRIGGER disp2 ON ACQUISTI;
CREATE TRIGGER disp2
AFTER INSERT ON ACQUISTI
FOR EACH ROW
EXECUTE PROCEDURE acquistiChange();

-- Violo il vincolo check acquistando più di quanto presente
--INSERT INTO ACQUISTI VALUES ('40001','60000','300');
-- Acquisto di vino
--INSERT INTO ACQUISTI VALUES ('40001','60004','10');
--SELECT * FROM MERCI;
--SELECT * FROM INVENTARIO;