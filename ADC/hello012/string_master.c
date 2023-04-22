/*** ATTENZIONE: questo sorgente NON E` un esempio di un programma "scritto bene",
     anzi, e` decisamente un controesempio dal punto di vista della chiarezza e
     della organizzazione del codice! Serve per capire quali sono le regole lessicali,
     sintattiche e semantiche del linguaggio C, con particolare riferimento ai puntatori,
     agli array e alle stringhe, e per farsi una idea delle difficolta` a cui si puo` andare
     incontro usandole senza opportune precauzioni.
***/
    
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LZ 5
#define my_strncpy(d,s) strncpy(d,s,sizeof(d)-1)
#define my_printc for ( j=0 ; j < sizeof(c) ; j++ ) \
			printf("%s(c[%d]==%d)", j ? " && " : "" , j, c[j] );

char zero[LZ];

char c[]={ '0', 0, 'o', 'a', 'i', 'e' };

char s_format[] = { "\nBra"
	"v%c!\n" };

int main(int argc, char ** argv){
	int i = 0, j, lc=strlen(c);
	FILE * ff = stdout;
        char * q = c, * p = NULL;

	if ( argc > 1 && strlen(argv[1]) ) {
		if ( *(argv[1]) == 'f' )
			i = 1;
	}

        printf("Questo eseguibile e` stato prodotto compilando il file sorgente %s.c",
		MY_SOURCE_FILE);
        fprintf(stdout,"\ned e` stato mandato in esecuzione da shell col comando:\n");
	fputs(argv[0],stdout);
	for (j=1;j<argc ; j++)
		printf(" %s",argv[j]);

	putchar('\n'); putc('\n',ff);

	printf("Nel file %s.c, \"char zero[LZ];\" definisce un array di %d caratteri, ",
		MY_SOURCE_FILE,LZ);
	printf("che\nviene successivamente inizializzato con \"my_strncpy(zero,c);\"");
        my_strncpy(zero,c);
	fprintf(stdout," per contenere una strin-\nga di lunghezza %d < %d.\n",
		(int)strlen(zero), (int)sizeof(zero));
	printf("Di conseguenza, dopo tale inizializzazione \"zero\" diventa la stringa: \"%s\"",
               zero);
	printf("\nSia \"*zero\" sia \"zero[0]\" indicano il primo elemento dell'array, ");
        fprintf(ff,"ossia la codifica\nASCII del carattere '%c' (rappresentato dal numero %d).\n",
		*zero, zero[0] );
	printf("Tutte le stringhe devono essere terminate col codice %d (che non rap"
		"presenta un\ncarattere stampabile), dopo l'ultimo carattere della stringa.\n",
		*(zero+strlen(zero)) );

	printf("\n\"char c[]={ '0', 0, ... };\" definisce un array di %d caratteri "
		"inizializzato staticamen-\nte", (int)sizeof(c) );
        printf(" il cui contenuto inizialmente e`:\n");
        my_printc
	printf("\nMa \"c\", oltre a rappresentare tale array di %d caratteri, e` anche una stringa"
		" di\nlunghezza %d che gode della proprieta`:\n", (int)sizeof(c),lc);
	printf("( strcmp(c,zero) == %d )\ne questo perche` contiene il valore %d in "
		"corrispondenza dell'indice %d ;-)\n\n", strcmp(c,zero), c[lc], lc );
	printf("Ovviamente il contenuto dell'array \"c\" puo` essere modificato in qualsiasi"
		" momento,\nper esempio eseguendo l'istruzione \"sprintf(c,\"%%c\",'p');\"");
	sprintf(c,"%c",'p');
	printf(" e ottenendo " "come risultato:\n");
        my_printc
        for ( j=2 ; j ; j-- )
		putc('\n',stdout);

	printf("\"char * q = c,\" definisce un puntatore a caratteri allocato automaticamente"
		" nello\nstack e allo stesso tempo lo inizializza in modo da farlo puntare"
		" al primo elemento\ndell'array \"c\".\n");
 	printf("Quindi sia \"*q\" che \"q[0]\" possono essere usati come alias di"
		" \"*c\" e/o di \"c[0]\" dopo\ntale definizione/inizializzazione.\n");
        printf("C'e` tuttavia una differenza importante tra \"c\" e \"q\": il primo e` solo "
		"il nome di\nuna variabile di tipo array, mentre il secondo e` solo il nome di"
		" un'altra variabile\ndi tipo puntatore!");
	printf("  Di conseguenza il puntatore \"q\" puo` essere cambiato dopo\nl'inizializzazione,"
		" per esempio eseguendo l'istruzione \"q += lc;\", mentre questa\nstessa"
		" istruzione non avrebbe senso se applicata a \"c\"!\n");
	q += lc;
	printf("Dopo questo incremento, il puntatore \"q\" passa a puntare all'elemento di indice"
		" %d\ndell'array \"c\" e quindi puo` essere usato come il nome di un array di %d "
		"caratteri\n(che coincidono con gli ultimi %d elementi di \"c\".\n",
		lc, (int)(sizeof(c)-lc), (int)(sizeof(c)-lc) );
	printf("Siccome ora il primo elemento dell'array \"q\" contiene il valore 0, \"q\" e`"
		" diventato\nanche la stringa vuota \"%s\" dopo questo incremento ...\n", q );
	printf("Incrementando ulteriormente il puntatore \"q\", per esempio valutando "
		"l'espressione\n\"*++q\", \"q\" passa a puntare al carattere successivo di \"c\""
		" che contiene il valore %d\n(diverso da 0).", *++q );
	printf("  A questo punto, \"q\" non e` piu` il nome di una stringa, perche`\nnessuno degli "
		"elementi dell'array \"q\" contiene il valore 0 atto a terminare una\nstringa.\n");
	printf("In effetti, ora abbiamo i seguenti caratteri nell'array \"q\":");

/*** TO BE COMPLETED START ***/

	//sizeof(c)-2 : size iniziale (6) - 2 (incrementi di q) = 4
	//for che stampa i primi 4 (indici 0,1,2,3) char di q (o,a,i,e)
	for(j=0; j<sizeof(c)-2; ++j)
		putchar(q[j]);
	printf("\n\n");

	//testo con opportuni \n ed escape:
	printf("Anche \"p\" e` un puntatore a carattere esattamente come \"q\", ma poiche` e` stato\n");
	printf("inizializzato al valore NULL (che corrisponde al valore 0), non puo` essere usato\n");
	printf("per accedere alla memoria, pena un Segmentation Fault.\n");
	printf("Solo dopo avergli assegnato un valore appropriato diverso da NULL, per esempio\n");
	printf("eseguendo l'istruzione \"p=c;\" lo si puo` correttamente usare per indirizzare la\n");
	//istruzione p=c
	p=c;
	printf("memoria, per esempio eseguendo l'istruzione\n");
	printf("\"if(argc>1&&strlen(argv[1])>1&&argv[1][1]==p[0])i+=2;\"\n");

	//stampa del testo finale discriminata sugli argomenti
	//output diversi (maschile, femminile, maschile plurale, femminile plurale)
	/*
		0: o (m) --> non ho eseguito l'if iniziale e neanche il prossimo
		1: a (f) --> ho eseguito solo l'if iniziale (if ( *(argv[1]) == 'f' ))
		2: i (mp) --> ho eseguito solo il prox. if (parametro mp o fp)
		3: e (fp) --> ho eseguito entrambi gli if
	*/
	if(argc>1&&strlen(argv[1])>1&&argv[1][1]==p[0])
		i+=2;
	printf(s_format,q[i]);

/*** TO BE COMPLETED END ***/

	exit(0);
}
