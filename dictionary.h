/*----------------------------------------------------------
 *				HTBLA-Leonding / Klasse: 2DHIF
 * ---------------------------------------------------------
 * Exercise Number: 0
 * Title:			dictionary.h
 * Author:			D. Kraus
 * Due Date:		November 25, 2012
 * ----------------------------------------------------------
 * Description:
 * dictionary.h defines functions to maintain a simple
 * dictionary.
 * ----------------------------------------------------------
 */
#ifndef ___DICTIONARY_H
#define ___DICTIONARY_H

#include "general.h"

struct DictionaryImplementation;
typedef DictionaryImplementation* Dictionary;

Dictionary 	    new_dictionary();
void 	        delete_dictionary(Dictionary dictionary);
void 	        add(Dictionary dict, const char *word);
int 	        get_size(Dictionary dict);
bool 	        is_in_dict(Dictionary dict, const char *word);
void 	        start_iterating(Dictionary dict);
bool 	        has_next(Dictionary dict);
const char * 	get_next_entry(Dictionary dict);
void 	        insert_sorted(Dictionary dict, const char *word);

#endif
