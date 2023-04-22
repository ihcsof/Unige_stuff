/*
 * vector.h: include file della libreria vector.
 *
 * versione 1.5 del 14/03/2021
 *
 * Programma sviluppato a supporto del laboratorio di
 * Architettura dei Calcolatori del corso di laurea triennale
 * in Informatica classe L-31 presso l'Universita` degli Studi di
 * Genova, anno accademico 2020/2021.
 *
 * Copyright (C) 2013-2021 by Giovanni Chiola <chiolag@acm.org>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 */

#ifndef vECTOR_h
#  define vECTOR_h

#  include <string.h>
#  include <stdio.h>
#  include <stdlib.h>

typedef int iterator;
#define iterator_begin 0
#define iterator_end -1

typedef struct vector_struct {
	size_t e_sz;
        char e_type;

/*** TO BE OPTIONALLY CHANGED START ***/

  /*** optionally add the definition of V_FLOAT type ***/

#define V_INT 1
#define V_DOUBLE 2
#define V_CHAR 3
#define V_FLOAT 4

/*** TO BE OPTIONALLY CHANGED END ***/

	unsigned no_e;
	unsigned cur_cap;
	void* e_array; // -=-=- insieme elementi a cui punta la struttura

}* vector_type;

#define vector_size(v) ((v)->no_e)
#define vector_capacity(v) ((v)->cur_cap)

/*** TO BE OPTIONALLY CHANGED START ***/

  /*** optionally add the definition of V_FLOAT type ***/

#define vector_int_at(v,i) (*((int*)v_at(v,i)))
#define vector_double_at(v,i) (*((double*)v_at(v,i)))
#define vector_char_at(v,i) (*((char*)v_at(v,i)))
#define vector_string(v) ((char*)v_at(v,0))
#define vector_float_at(v,i) (*((float*)v_at(v,i)))

/*** TO BE OPTIONALLY CHANGED END ***/


extern vector_type v_create_empty(char);
extern void v_destroy(vector_type);
extern void* v_at(vector_type, iterator);
extern void v_push_back(vector_type,void*);
extern void v_pop_back(vector_type);
extern void v_insert_n(vector_type,iterator,unsigned,void*);
extern void v_erase_range(vector_type,iterator,iterator);

#endif
