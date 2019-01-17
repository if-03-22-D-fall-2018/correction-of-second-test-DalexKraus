/*----------------------------------------------------------
 *				HTBLA-Leonding / Klasse: 2DHIF
 * ---------------------------------------------------------
 * Exercise Number: 0
 * Title:			dictionary.cpp
 * Author:			D. Kraus
 * Due Date:		November 25, 2012
 * ----------------------------------------------------------
 * Description:
 * Implementation of dictionary.h.
 * ----------------------------------------------------------
 */

#include "dictionary.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>

struct WordImplementation;
typedef WordImplementation* Word;

struct WordImplementation
{
    Word next;
    Word parent;
    char text[25];
};

struct DictionaryImplementation
{
    int length; //TODO: Removed = 0; to get rid of warning
    Word head;
    Word tail;
    Word current_iteration_pos;
};

Dictionary new_dictionary()
{
    Dictionary dict = (Dictionary) malloc(sizeof(DictionaryImplementation));
    dict->head = 0;
    dict->tail = 0;
    dict->length = 0;     //TODO: Somehow removed this eXtreMely important line for absolutely no fucking reason during exam
    dict->current_iteration_pos = 0;
    return dict;
}

void delete_dictionary(Dictionary dictionary)
{
    Word currentNode = dictionary->tail;
    while (currentNode != 0)
    {
        Word toDelete = currentNode;
        currentNode = currentNode->parent;
        sfree(toDelete);
    }
    sfree(dictionary);
}

Word new_word()
{
    Word toAdd = (Word) malloc(sizeof(WordImplementation));
    toAdd->next = 0;
    toAdd->parent = 0;
    return toAdd;
}

void add(Dictionary dict, const char *word)
{
    if (!is_in_dict(dict, word)) {
        Word toAdd = new_word();
        strcpy(toAdd->text, word);

        if (dict->head == 0) {
            toAdd->parent = 0;
            dict->head = toAdd;
            dict->tail = toAdd;
        }
        else {
            toAdd->parent       = dict->tail;
            dict->tail->next    = toAdd;
            dict->tail          = toAdd;
        }
        dict->length++;
    }
}

int get_size(Dictionary dict)
{
    return dict->length;
}

bool is_equal(const char* a, const char* b)
{
    return strcasecmp(a, b) == 0; //TODO Changed string comparison to work on macOS
}

bool is_in_dict(Dictionary dict, const char *word)
{
    Word currentNode = dict->head;
    while (currentNode != 0)
    {
        if (is_equal(currentNode->text, word)) return true;
        currentNode = currentNode->next;
    }
    return false;
}

void start_iterating(Dictionary dict)
{
    dict->current_iteration_pos = dict->head;
}

bool has_next(Dictionary dict)
{
    return dict->current_iteration_pos != 0;
}

const char*	get_next_entry(Dictionary dict)
{
    if (dict->current_iteration_pos != 0)
    {
        char* text = dict->current_iteration_pos->text;
        if (has_next(dict)) 
            dict->current_iteration_pos = dict->current_iteration_pos->next;

        return text;
    }
    return 0;
}

void insert_sorted(Dictionary dict, const char *word)
{
    Word toAdd = new_word();
    strcpy(toAdd->text, word);

    if (!is_in_dict(dict, word)) {
        if (dict->head == 0) {
            toAdd->parent = 0;
            dict->head = toAdd;
            dict->tail = toAdd;
            //TODO: Removed length++
        }
        else if (dict->head->next == 0) //TODO: Changed condition
        {
            //TODO: Checked if new old one has to be swapped
            if (strcasecmp(dict->head->text, word) > 0)
            {
                toAdd->next = dict->head;   //TODO: removed ->next-> inbetween
                dict->head = toAdd;         //This line stayed the same
            }
            else
            {
                dict->head->next = toAdd;
                dict->tail = toAdd;
            }
        }
        else if (strcasecmp(word, dict->head->text) < 0) //TODO: Changed to strcasecmp
        {
            toAdd->parent = 0;
            toAdd->next = dict->head; //removed ->next statement
            dict->head = toAdd;
            //TODO: Moved this line down
        }
        else
        {
            Word currentNode = dict->head;
            while (currentNode != 0 && currentNode->next != 0 && strcasecmp(currentNode->next->text, word) < 0) //TODO: Extended while condition
            {
                //TODO: Removed swap algorithm
                currentNode = currentNode->next;
            }
            if (currentNode->next == 0) //Added check
            {
                dict->length--; //TODO: Added decrementation
                add(dict, word);
            }
            if (currentNode->next != 0 && strcasecmp(currentNode->next->text, word) > 0) //TODO: Added comparison
            {
                toAdd->next = currentNode->next;   //TODO: Addded swap algorithm
                currentNode->next = toAdd;
            }
        }
       
        dict->length++; //TODO: Moved statement from upper comment to here
    }
}
