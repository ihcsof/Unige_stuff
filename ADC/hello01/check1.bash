#!/bin/bash
C=hello0
E=hello1
if (( $# > 0 )) ; then E=$1 ; fi
if (( $# > 1 )) ; then C=$2 ; fi
/bin/rm -f $E
make $E
./$E > $E.out
make $C
./$C > $E.cmp
diff $E.out $E.cmp > $E.diff
A=$(stat --format="%s" $E.diff)
/bin/rm -f $E.out $E.cmp $E.diff
if [[ $A != 0 ]] ; then printf "Spiacente, %s.c non e\` corretto: riprova!\n" $E ;
	 exit 1 ; else printf "OK, %s.c e\` corretto\n" $E ; fi
grep "/*** TO BE DONE START ***" < $E.c | grep "/*** TO BE DONE END ***" > $E.line
A=$(stat --format="%s" $E.line)
/bin/rm -f $E.line
printf "La riga da completare e\` lunga " ; echo $A
if (( $A > 110 )) ; then printf "Spiacente, la riga completata e\` troppo lunga, riprova!\n" ;
	 exit 1 ; fi
if (( $A < 80 )) ; then printf "Spiacente, non riesco a calcolare la lunghezza della riga completata\n" ;
         exit 0 ; fi
if (( $A > 99 )) ; then printf "OK, %s.c e\` stato completato correttamente, anche se non in forma minimale\n" $E ;
         exit 0 ; fi
printf "\nOttimo!!! %s.c e\` stato completato col numero minimo di caratteri:\n   bonus di +1 sulla valutazione dell\'esame  :-)\n\n" $E

