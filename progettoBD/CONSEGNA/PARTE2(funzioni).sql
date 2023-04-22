SET search_path TO 'socialmarket';
SET datestyle to 'MDY';

-- Test basati sulle insert presenti nello script di popolamento del database socialmarket

--D(a)
--funzione che realizza lo scarico dall’inventario dei prodotti scaduti
CREATE OR REPLACE FUNCTION scarico()
RETURNS void --nessun tipo di ritorno
AS $$
DECLARE -- variabili ausiliarie e cursore per la selezione dei prodotti scaduti
	lotto INT;
	prodotto INT;
	qt INT;
	trash CURSOR FOR
		SELECT idLotto, prod, Quantita
		FROM MERCI 
		WHERE Quantita > 0 AND Scadenza <= CURRENT_DATE;
BEGIN
	OPEN trash; -- apertura cursore e primo fetch
	FETCH trash INTO lotto, prodotto, qt; 
	WHILE FOUND LOOP -- fino a che "trovo qualcosa" effettuo update di inventario
		BEGIN
			-- non necessario perchè il trigger disp è in azione:
			-- UPDATE INVENTARIO SET Quantita = Quantita - qt WHERE idProdotto = prodotto;
			UPDATE INVENTARIO SET QtScaricato = QtScaricato + qt WHERE idProdotto = prodotto;
			FETCH trash INTO lotto, prodotto, qt;
		END;
	END LOOP;
	-- set di quantita a 0 dopo il ciclo per efficienza
	UPDATE MERCI SET Quantita = 0 WHERE Scadenza <= CURRENT_DATE;
	CLOSE trash; -- chiusura del cursore
END
$$
LANGUAGE plpgsql;
-- SELECT * FROM scarico() per il testing (si assume trigger disp in azione in cascata)
-- Vengono scaricate mozzarelle e tonno
--SELECT * FROM MERCI;
--SELECT * FROM INVENTARIO;

--D(b)
-- dato un volontario e due date, determinare i turni assegnati al volontario nel periodo compreso tra le due date.
CREATE OR REPLACE FUNCTION assignTurnInPeriod(IN vol CHAR(16), IN d1 DATE, IN d2 DATE)
RETURNS TABLE(LIKE Turni) -- ritorna una tabella con template turni
AS $$
BEGIN
	RETURN QUERY
	SELECT * -- ritorna tutta la tabella per match sul template
	FROM TURNI
	WHERE dataTurno BETWEEN d1 AND d2
	AND cfV = vol;
END;
$$
LANGUAGE plpgsql;
-- SELECT * FROM assignTurnInPeriod('GHKMNB09876545','11-17-2024','11-19-2024') per test