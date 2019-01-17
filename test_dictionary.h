/*----------------------------------------------------------
 *				HTBLA-Leonding / Klasse: 2AHDV
 * ---------------------------------------------------------
 * Exercise Number: 0
 * Title:			test_dictionary.h
 * Author:			P. Bauer
 * Due Date:		November 25, 2012
 * ----------------------------------------------------------
 * Description:
 * Test functions for dictionary.
 * ----------------------------------------------------------
 */
#ifndef ___TEST_DICTIONARY_H
#define ___TEST_DICTIONARY_H

#include "shortcut.h"

TEST(construction);
TEST(add_first_entry);
TEST(add_two);
TEST(ignore_double_entry);
TEST(add_many);
TEST(in_dictionary);
TEST(case_insensitivity);
TEST(iterating);
TEST(iterating_fails_because_call_start_iterating_is_missing);
TEST(iterating_an_empty_directory);
TEST(insert_sorted_first_element);
TEST(insert_sorted_second_element);
TEST(insert_sorted_elements_coming_unordered);
TEST(insert_sorted_at_end);
TEST(insert_revers_sorted);
TEST(insert_random);
TEST(insert_ignores_double_entries);

#endif
