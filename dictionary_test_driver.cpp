/*----------------------------------------------------------
 *				HTBLA-Leonding / Class: 2<X>HIF
 * ---------------------------------------------------------
 * Exercise Number:
 * Title:			Arrays Frequency
 * Author:			P. Bauer
 * Due Date:
 * ----------------------------------------------------------
 * Description:
 * Test header file for dictionary.
 * ----------------------------------------------------------
 */
#include "dictionary.h"

#include "shortcut.h"
#include "test_dictionary.h"

int main(int argc, char *argv[])
{
	ADD_TEST(construction);
	ADD_TEST(add_first_entry);
	ADD_TEST(add_two);
	ADD_TEST(ignore_double_entry);
	ADD_TEST(add_many);
	ADD_TEST(in_dictionary);
	ADD_TEST(case_insensitivity);
	ADD_TEST(iterating);
	ADD_TEST(iterating_fails_because_call_start_iterating_is_missing);
	ADD_TEST(iterating_an_empty_directory);
	ADD_TEST(insert_sorted_first_element);
	ADD_TEST(insert_sorted_second_element);
	ADD_TEST(insert_sorted_elements_coming_unordered);
	ADD_TEST(insert_sorted_at_end);
	ADD_TEST(insert_revers_sorted);
	ADD_TEST(insert_random);
	ADD_TEST(insert_ignores_double_entries);

	run_tests();
	return 0;
}
