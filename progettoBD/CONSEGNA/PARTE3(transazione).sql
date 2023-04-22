set search_path to 'socialmarket';
SET datestyle to 'MDY';

-- Transazione basata sui dati presenti nelle insert manuali del file

-- Duplico l'importo donato della donazione del '03-20-2021' (l’ultima) -- … effettuata dal donatore con mail: donatore1@gmail.com
BEGIN;
SET CONSTRAINTS ALL IMMEDIATE;
SET TRANSACTION ISOLATION LEVEL REPEATABLE READ;

SELECT telD
FROM DONATORI
WHERE mail = 'donatore1@gmail.com';

-- ipotesi di aver trovato questo telD
SELECT idD
FROM DONAZIONI
WHERE telD = '3456664510'
AND dataD = '03-20-2021';

-- ipotesi di aver trovato questo idD
UPDATE DONAZIONI SET Importo = Importo + Importo * 2 WHERE idD = 50000;

SELECT *
FROM DONAZIONI 
WHERE idD = 50000;

COMMIT;