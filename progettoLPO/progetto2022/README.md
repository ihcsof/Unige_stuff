# Progetto finale LPO a.a. 2021-'22
Il progetto finale consiste nello sviluppo di una parser, un typechecker e un interprete di un linguaggio di programmazione che è l'estensione
di quello sviluppato durante gli ultimi laboratori Java (laboratori 9, 10 e 11); è quindi consigliabile usare come base di partenza la soluzione proposta per l'ultimo laboratorio.

L'interfaccia da linea di comando per interagire con l'interprete è la stessa utilizzata nei laboratori finali:
- il programma da eseguire può essere letto da un file di testo `<filename>` con l’opzione `-i <filename>`, altrimenti viene letto dallo standard
input
- l'output del programma in esecuzione può essere salvato su un file di testo `<filename>` con l’opzione `-o <filename>`, altrimenti viene usato lo standard output
- l’opzione `-ntc` (abbreviazione di no-type-checking) permette di eseguire il programma senza effettuare prima il controllo di semantica statica del
typechecker 

## Definizione del linguaggio

### Sintassi
Il linguaggio contiene le nuove parole chiave `length` e `while` e i nuovi simboli `[` e `]`.

La sintassi del linguaggio è definita da questa grammatica in forma EBNF:

```
Prog ::= StmtSeq EOF
StmtSeq ::= Stmt (';' StmtSeq)?
Stmt ::= 'var'? IDENT '=' Exp | 'print' Exp |  'if' '(' Exp ')' Block ('else' Block)? | 'while' '(' Exp ')' Block 
Block ::= '{' StmtSeq '}'
Exp ::= And (',' And)* 
And ::= Eq ('&&' Eq)* 
Eq ::= Add ('==' Add)*
Add ::= Mul ('+' Mul)*
Mul::= Unary ('*' Unary)*
Unary ::= 'fst' Unary | 'snd' Unary | '-' Unary | '!' Unary | 'length' Unary | AtomOrArrayAcc
AtomOrArrayAcc ::= Atom ('[' Exp ']')?
Atom ::= BOOL | NUM | IDENT | '(' Exp ')' | '[' ExpSeq ']'
ExpSeq ::= Exp (';' ExpSeq)?
```
**Importante**: la grammatica **non** richiede trasformazioni e può essere utilizzata così com'è per sviluppare il parser del linguaggio.

Rispetto al linguaggio del laboratorio, sono stati aggiunti
- lo statement `'while' '(' Exp ')' Block`
- i literal di tipo array `'[' ExpSeq ']'`, dove `ExpSeq` è una sequenza di una o più espressioni separate da `;`. Per semplicità non è possibile definire array vuoti 
- l'operatore unario che calcola la lunghezza di un array `'length' Unary`
- l'operatore binario di accesso agli elementi di un array `Atom '[' Exp ']'`

La grammatica è definita in modo che l'operatore binario di accesso agli elementi di un array abbia la precedenza rispetto a tutti gli altri operatori binari e unari; per esempio, l'espressione `a[0] + -a[1]` permette di calcolare la differenza tra il primo e secondo elemento dell'array contenuto nella variabile `a`. Gli array **non sono modificabili**: la sintassi dell'assegnazione non ammette statement del tipo `a[x]=31`.  

L'operatore unario `length` è definito dalla grammatica in modo che abbia la precedenza rispetto a tutti gli operatori binari, con esclusione dell'operatore di accesso agli elementi di un array; per esempio `1 + length [1;2;3]` calcola il valore 4.

*Suggerimento per l'implementazione del parser*: per il parsing di `ExpSeq` seguire lo stesso procedimento adottato per `StmtSeq`, riutilizzando le classi `More` e `Single` del package `parser.ast`.

### Semantica statica

La semantica statica è definita in OCaml nel file `semantica-statica.ml`; è utile consultare anche gli esempi nel folder `test`. Il nuovo tipo `array` permette di definire la semantica statica dei literal `'[' ExpSeq ']'`; per semplicità, nella semantica statica gli array possono contenere solo elementi di tipo `int`.

Per esempio `[1; 1+2; 3*2]` ha tipo `array`, mentre `[true; false]`, `[1; true; 2]` o `[(1,2);(4,5)]` non sono espressioni staticamente corrette. 

#### Regole della semantica statica
- lo statement `'while' '(' Exp ')' Block` è corretto se `Exp` ha tipo `bool` e `Block` è corretto rispetto alle stesse regole per i blocchi dello statement `if`
- il literal `'[' ExpSeq ']'` è corretto e ha tipo `array` se tutte le espressioni in `ExpSeq` hanno tipo `int`
- l'espressione `'length' Unary` è corretta e ha tipo `int` se `Unary` ha tipo `array`
- l'espressione `Atom '[' Exp ']'` è corretta e ha tipo `int` se `Atom` ha tipo `array` ed `Exp` ha tipo `int` 


*Suggerimenti per l'implementazione del typechecker*:
- la visita delle sequenze di espressioni `ExpSeq` può limitarsi a controllare che tutte le espressioni contenute nelle sequenze abbiano tipo `int`
- il tipo `array` può essere implementato come elemento della classe `SimpleType`

### Semantica dinamica
La semantica dinamica è definita in OCaml nel file `semantica-dinamica.ml`; è utile consultare anche gli esempi nel folder `test`.

#### Regole della semantica dinamica

- la semantica dello statement `'while' '(' Exp ')' Block` è standard, con le regole di scope dei blocchi come nello statement `if`
- la valutazione di `'[' ExpSeq ']'` si ottiene attraverso i seguenti passi: 
  - `ExpSeq` viene valutata in un valore rispettando l'ordine delle espressioni in `ExpSeq`
  -  il valore viene convertito in una sequenza di valori `v_1...v_n` 
  -  viene restituito un valore di tipo array che contiene come elementi la sequenza `v_1...v_n`
  
  **Osservazione**: la semantica dinamica dei literal di tipo array è più flessibile rispetto a quella statica; infatti con l'opzione `-ntc` è possibile definire array con elementi di tipi arbitrari, possibilmente diversi tra loro; due esempi relativi a questo importante dettaglio della semantica dinamica sono presenti nel folder `tests/failure/static-semantics-only` 
- la valutazione di `'length' Unary` si ottiene attraverso i seguenti passi:
  - `Unary` viene valutato
  - il valore viene convertito in un array
  - viene calcolata la lunghezza dell'array
  - il risultato viene convertito in un valore di tipo intero
- la valutazione di `Atom '[' Exp ']'` si ottiene attraverso i seguenti passi:
  - `Atom` viene valutato e convertito in un array 'a'
  - `Exp` viene valutato e convertito in un intero 'i'
  - viene calcolato `a[i]`, assumendo che l'indice del primo elemento parta da 0, come accade in molti linguaggi di programmazione
  
**Importante**: i valori di tipo array sono stampabili e vengono visualizzati usando la stessa notazione dei literal. Per esempio, `print [1+2;3*4]` stampa `[3;12]`.

*Suggerimenti per l'implementazione dell'interprete*:
- per implementare l'esecuzione dello statement `while` conviene usare il corrispondente statement Java evitando la ricorsione
- per definire la classe che implementa i valori di tipo array
    - conviene dichiarare un array Java di tipo `Value[]` invece che `int[]`, `Integer[]` o `IntValue[]` 
    - **non** conviene estendere la classe `SimpleValue<T>` poiché gli array in Java ereditano `equals()` e `hashCode()` da `Object`
    - per ridefinire `equals()` e `hashCode()` è utile usare i metodi `java.util.Arrays.equals(Object[] a, Object[] a2)` e `java.util.Arrays.hashCode(Object[] a)`
    - ricordarsi di ridefinire il metodo `toString()` per permettere che lo statement `print` stampi correttamente gli array
- la valutazione di `ExpSeq` dovrebbe restituire sequenze di valori
- per implementare le sequenze di valori ottenute dalla valutazione di `ExpSeq` è consigliabile dichiarare una classe che estende `java.util.LinkedList<Value>` e implementa l'interfaccia `Value`
- è utile usare il metodo `java.util.LinkedList.toArray(Value[] a)` per creare un array di valori a partire da una sequenza di valori
- la valutazione dell'operatore di accesso a un elemento di un array dovrebbe catturare possibili eccezioni `exc` di tipo `ArrayIndexOutOfBoundsException` e risollevare un'eccezione di tipo `InterpreterException` con `exc` come causa dell'errore, come accade negli esempi presenti in `tests/failure/dynamic-semantics`
  

## Contenuto del repository

* `semantica-statica.ml` : semantica statica del linguaggio esteso, definita in OCaml
* `semantica-dinamica.ml` : semantica dinamica del linguaggio esteso, definita in OCaml
* `tests/success`: test che vengono eseguiti correttamente **senza** l'opzione `-ntc`
* `tests/failure/syntax`: test che generano errori di sintassi 
* `tests/failure/static-semantics`: test che generano errori statici **senza** l'opzione `-ntc` ed errori dinamici **con** l'opzione `-ntc`
* `tests/failure/static-semantics-only`: test che generano errori statici **senza** l'opzione `-ntc` e vengono eseguiti correttamente con l'opzione `-ntc`
* `tests/failure/dynamic-semantics`: test che generano errori dinamici **con** o **senza** l'opzione `-ntc`

## Modalità di consegna

- Le scadenze per la consegna coincidono con le date delle prove scritte; dopo ogni scadenza, verranno corretti tutti i progetti consegnati e pubblicati i relativi risultati prima che le consegne siano riaperte. **Dopo la data dell'ultima prova scritta dell'appello invernale non sarà più possibile consegnare progetti validi per l'anno accademico in corso**
- Il progetto può essere consegnato da **un solo componente del gruppo**, dopo aver fatto commit (e push) finale, utilizzando [AulaWeb](https://2021.aulaweb.unige.it/mod/assign/view.php?id=9582) e indicando **il numero del gruppo** 
- Il numero del gruppo è definito nell'[elenco su AulaWeb](https://2021.aulaweb.unige.it/mod/wiki/view.php?id=9585) e dovrebbe coincidere con quello di GitHub
- Per ricevere supporto dai docenti durante lo sviluppo del progetto è consigliabile tenere sempre aggiornato il codice sul repository GitHub  
- La consegna è valida solo se il **progetto passa tutti i test** contenuti nel folder `tests`; la valutazione del progetto tiene conto dell'esecuzione di test aggiuntivi e della qualità del codice
- Il colloquio sul progetto è **individuale** e ha lo scopo di verificare che ogni componente del gruppo abbia compreso il funzionamento del codice e abbia contribuito attivamente al suo sviluppo
- Per ulteriori informazioni consultare la [pagina AulaWeb sulle modalità di esame](https://2021.aulaweb.unige.it/mod/page/view.php?id=9574)
