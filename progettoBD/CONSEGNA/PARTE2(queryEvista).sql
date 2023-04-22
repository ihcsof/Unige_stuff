SET search_path TO 'socialmarket';
SET datestyle to 'MDY';

-- Test basati sulle insert presenti nello script di popolamento del database socialmarket

--C(a, b, c)
-- determinare i nuclei familiari che, pur avendo punti assegnati, non hanno effettuato spese nell’ultimo mese;
SELECT idCliente
FROM CLIENTI C
WHERE saldo > 0 -- punti assegnati
AND NOT EXISTS ( -- nessuna spesa effettuata (appuntamento in cui è stato effettuato un acquisto effettivo)
	SELECT *
	FROM APPUNTAMENTI A
	WHERE A.idCliente = C.idCliente
	AND SaldoSucc < SaldoPrec
	AND EXTRACT(MONTH FROM dataA) = EXTRACT(MONTH FROM CURRENT_DATE)
);

-- Insert di appuntamenti (mesi di luglio e agosto) per non selezionare il cliente 3
--INSERT INTO APPUNTAMENTI VALUES ('80000','50','20','07-30-2022','20:00','3','DDDEEE1234567890','OPPMNB09876548');
--INSERT INTO APPUNTAMENTI VALUES ('80001','50','20','08-30-2022','20:00','3','DDDEEE1234567890','OPPMNB09876548');

--determinare le tipologie di prodotti acquistate nell’ultimo anno da tutte le famiglie 
--(cioè ogni famiglia ha acquistato almeno un prodotto di tale tipologia nell’ultimo anno)
SELECT tipologiaProdotto
FROM INVENTARIO JOIN MERCI ON prod = idProdotto
NATURAL JOIN ACQUISTI
JOIN APPUNTAMENTI USING(IdA)
GROUP BY tipologiaProdotto
HAVING COUNT(DISTINCT idCliente) = ( -- Divisione
	SELECT COUNT(idCliente)
	FROM CLIENTI
);

/* Dopo i seguenti 8 inserimenti la query soprastante non ritorna più vuoto. Seguono le delete per ripristinare
INSERT INTO APPUNTAMENTI VALUES ('50000','50','20','03-16-2024','20:00','3','DDDEEE1234567890','OPPMNB09876548');
INSERT INTO APPUNTAMENTI VALUES ('50001','50','20','03-17-2023','20:00','4','DDDEEE1234567890','OPPMNB09876548');
INSERT INTO APPUNTAMENTI VALUES ('50002','50','20','03-18-2023','20:00','5','DDDEEE1234567890','OPPMNB09876548');
INSERT INTO APPUNTAMENTI VALUES ('50003','50','20','03-19-2023','20:00','6','DDDEEE1234567890','OPPMNB09876548');
INSERT INTO ACQUISTI VALUES ('50000','60003','2');
INSERT INTO ACQUISTI VALUES ('50001','60004','2');
INSERT INTO ACQUISTI VALUES ('50002','60004','2');
INSERT INTO ACQUISTI VALUES ('50003','60004','2');
DELETE FROM ACQUISTI WHERE idA >= 50000;
DELETE FROM APPUNTAMENTI WHERE idA >= 50000;*/

--determinare i prodotti che vengono scaricati (cioè non riescono ad essere distribuiti alle famiglie)
-- in quantitativo maggiore rispetto al quantitativo medio scaricato per prodotti della loro tipologia
SELECT *
FROM INVENTARIO I
WHERE QtScaricato > (
	SELECT AVG(QtScaricato)
	FROM INVENTARIO
	WHERE I.TipologiaProdotto = TipologiaProdotto
);

-- Update di testing per scaricare 2 birre e 1 vino (birra ha ora avg > su bevande)
--UPDATE INVENTARIO SET QtScaricato = 2 WHERE idProdotto = 3;
--UPDATE INVENTARIO SET QtScaricato = 1 WHERE idProdotto = 4;

--------------------------------------------------------------------------------------

/*La definizione di una vista che fornisca alcune informazioni riassuntive per ogni nucleo familiare: 
il numero di punti mensili a disposizione, 
i punti residui per il mese corrente, 
il numero di persone autorizzate per l’accesso al market, 
il numero di componenti totali e 
quelli appartenenti alla fascia d’età più bassa, 
il numero di spese effettuate nell’ultimo anno, 
i punti eventualmente non utilizzati nell’ultimo anno, 
la percentuale di punti utilizzata per prodotti deperibili e non deperibili nell’ultimo anno;*/

SET search_path TO 'socialmarket';

-- il numero di persone autorizzate per l’accesso al market
-- Conta dei famigliari per cui UsaPunti è vero + 1 (il cliente titolare)
CREATE OR REPLACE VIEW auth AS (
	SELECT idCliente, COUNT(*) + 1 AS autorizzati
	FROM FAMIGLIARI
	WHERE UsaPunti = 'true'
	GROUP BY idCliente
);

-- il numero di spese effettuate nell’ultimo anno
-- (appuntamenti in cui è stato comprato qualcosa = quante volte ho fatto la spesa)
CREATE OR REPLACE VIEW speseAnnuali AS (
	SELECT idCliente, COUNT(*) AS spese
	FROM APPUNTAMENTI
	WHERE EXTRACT(year FROM DataA) = EXTRACT(year FROM CURRENT_DATE)
	AND (saldoPrec - saldoSucc) > 0
	GROUP BY idCliente
);

-- il totale di punti utilizzati nell’ultimo anno
CREATE OR REPLACE VIEW totale AS (
	SELECT idCliente, SUM(saldoPrec - saldoSucc) AS tot
	FROM APPUNTAMENTI
	WHERE EXTRACT(year FROM DataA) = EXTRACT(year FROM CURRENT_DATE)
	GROUP BY idCliente
);

-- la percentuale di punti utilizzata per prodotti deperibili nell’ultimo anno
CREATE OR REPLACE VIEW percDep AS (
	SELECT idCliente, SUM(quantitaRif * costoPunti) / tot * 100 AS Deperibili
	FROM MERCI 
		NATURAL JOIN ACQUISTI
		JOIN APPUNTAMENTI USING(idA) 
		JOIN INVENTARIO ON prod = idProdotto 
		NATURAL RIGHT JOIN totale
	WHERE EXTRACT(year FROM DataA) = EXTRACT(year FROM CURRENT_DATE)
	AND Scadenza IS NOT NULL
	GROUP BY idCliente, tot
);

-- la percentuale di punti utilizzata per prodotti non deperibili nell’ultimo anno
CREATE OR REPLACE VIEW percNonDep AS (
	SELECT idCliente, SUM(quantitaRif * costoPunti) / tot * 100 AS NonDeperibili
	FROM MERCI 
		NATURAL JOIN ACQUISTI
		JOIN APPUNTAMENTI USING(idA) 
		JOIN INVENTARIO ON prod = idProdotto 
		NATURAL RIGHT JOIN totale
	WHERE EXTRACT(year FROM DataA) = EXTRACT(year FROM CURRENT_DATE)
	AND Scadenza IS NULL
	GROUP BY idCliente, tot
);

-- Vista finale
-- NB: COALESCE ritorna il primo arg non null - TRUNC effettua un troncamento alle prime n cifre decimali
-- NB: nBimbi+nAdulti+nAnziani è uguale alla somma totale dei componenti per costruzione
CREATE OR REPLACE VIEW infoFamiglia AS
SELECT idCliente, PuntiMensili, saldo, COALESCE(autorizzati, 1) AS nAuth, nBimbi+nAdulti+nAnziani AS membri, 
	nBimbi, spese, ptiNonSpesi, COALESCE(TRUNC(NonDeperibili, 2),0) AS NonDeperibili, COALESCE(TRUNC(Deperibili, 2),0) AS Deperibili
FROM CLIENTI NATURAL LEFT JOIN auth NATURAL LEFT JOIN speseAnnuali NATURAL LEFT JOIN percDep NATURAL LEFT JOIN percNonDep;

SELECT * FROM infoFamiglia;


