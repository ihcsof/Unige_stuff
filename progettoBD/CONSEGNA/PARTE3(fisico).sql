-- Query e indici basati sullo schema socialmarketshort (script di creazione della PARTE3)
SET search_path TO 'socialmarketshort';

/*
Prima query del workload scelto, facciamo semplicemente una select dell’id, del nome e della tipologia di tutti i prodotti nell’inventario
*/
SELECT idProdotto, nomeProdotto, tipologiaProdotto
FROM INVENTARIO
WHERE costopunti = 30;

/*
Seconda query delle tre a scelta. Si vanno a
cercare i prodotti nell'inventario (selezionandone id, nome e quantità presente) che soddisfano una determinata condizione complessa. 
Nello specifico la condizione richiede che o la quantità sia 10 o il costoPunti sia maggiore di 2, che l’id del prodotto sia diverso da 1 e che non sia mai stato scaricato.
*/
SELECT idProdotto, nomeProdotto, quantitaInv
FROM INVENTARIO
WHERE (quantitaInv = 10 OR costoPunti > 2) AND idProdotto <> 1 AND qtScaricato = 0;

/*
Terza ed ultima query di quelle a scelta, in questo caso la query comprende un join dove si richiede di selezionare i volontari con i rispettivi turni 
(limitandosi ai volontati per cui è registrato almeno un turno. Si seleziona codice fiscale, cognome e nome dei volontari, 
insieme alla data e all’orario di inizio e di fine dei loro rispettivi turni.
*/
SELECT cfV, cognomeV, nomeV, dataTurno, orarioInizio, orarioFine
FROM VOLONTARI NATURAL JOIN TURNI

CREATE INDEX idxInv1 ON INVENTARIO(costopunti);
CLUSTER INVENTARIO USING idxInv1;
CREATE INDEX idxInv2 ON INVENTARIO(qtScaricato);