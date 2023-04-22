/*** File ken_tool.c
 *** implementazione di uno strumento automatico per la scrittura della
 *** parte iniziale del programma "ken_init.c", contenente l'inizializzazione
 *** della stringa costante "s". Programma sviluppato a supporto delle
 *** esercitazioni di laboratorio del corso di Architettura dei Calcolatori,
 *** corso di laurea in Informatica, Universita` degli studi di Genova,
 *** anno accademico 2020-2021.
 ***
 *** Copyright (C) Giovanni Chiola 2010-2021.
 *** All rights reserved.
 ***/

#include "ken_header.h"

#include<stdio.h>
#include<stdlib.h>

int main(){
	int i;
	char c;
        INITIAL_PRINTF
	for(i=0; (c = getchar()) != EOF ; i++) {
		switch(c){
		case'\n':printf("\t\'\\n\',");break;
		case'\t':printf("\t\'\\t\',");break;
		case'\\':

/*** TO BE DONE START ***/
		/*
			Potrei anche stampare tutti i case, per ogni char componente
			l'array, ma basta inserire i case solamente dei casi 
			"problematici" + il default che stampa il c che viene ciclato
			(letto mano a mano da getchar fino ad end of file (EOF)).
			I casi problematici sono: '\\' ossia il \ a cui però devo
			anteporre un escape; il single quote che devo stampare 
			in maniera non triviale (non basta ', perchè si genererebbe
			un ''' che crea inevitabilmente un errore).
		*/
		printf("\t'\\\\',");break;	
		case '\'':printf("\t\'\\\'\',");break;
		default: printf("\t\'%c\',",c);break;
/*** TO BE DONE END ***/

		}
                putchar(((i+1)%10)?' ':'\n');
            }
	exit(0);
}
