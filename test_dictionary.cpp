/*----------------------------------------------------------
 *				HTBLA-Leonding / Klasse: <your class>
 * ---------------------------------------------------------
 * Exercise Number: 0
 * Title:			test_dictionary.c
 * Author:			P. Bauer
 * Due Date:		November 25, 2012
 * ----------------------------------------------------------
 * Description:
 * Test functions for dictionary.
 * ----------------------------------------------------------
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "shortcut.h"
#include "dictionary.h"
#include "test_dictionary.h"

#define WORD_COUNT 45
static const char* test_words[] = {
	"abalone", "and", "bang", "bull", "cabbage", "commitment", "demanding", "downstairs", "eager",
	"expressive", "finally", "giant", "happiness", "hole", "important", "match", "mathematics", "modem",
	"pathologists", "phone", "pneumonic", "pollute", "quit", "rabbit", "ready", "repair", "romantic",
	"salary", "schedule", "selfish", "spooler", "tailor", "test", "tomorrow", "touch", "translate",
	"tweed", "unattended", "uncontrollable", "unimportant", "vanisher", "vendor", "vibrate", "wacky", "weekend", 0
};

enum Direction {
	ASCENDING, DESCENDING, RANDOM
};

TEST(construction)
{
	init_free_list();
	Dictionary dict = new_dictionary();
	ASSERT_FALSE(dict == 0, "Pointer to dictionary must not be null");
	ASSERT_EQUALS(0, get_size(dict));

	delete_dictionary(dict);
	ASSERT_EQUALS(1, get_free_list_length());
	ASSERT_TRUE(get_free_list()[0] == dict, "Pointer to dictionary expected to be deleted");
}

TEST(add_first_entry)
{
	init_free_list();
	Dictionary dict = new_dictionary();
	add(dict, "and");
	ASSERT_EQUALS(1, get_size(dict));

	delete_dictionary(dict);
	ASSERT_EQUALS(2, get_free_list_length());
	ASSERT_TRUE(get_free_list()[1] == dict, "Pointer to dictionary expected to be the last deleted");
}

TEST(add_two)
{
	init_free_list();
	Dictionary dict = new_dictionary();
	add(dict, "and");
	add(dict, "bang");
	ASSERT_EQUALS(2, get_size(dict));
	ASSERT_TRUE(is_in_dict(dict, "and"), "'and' expected to be in dictionary");
	ASSERT_TRUE(is_in_dict(dict, "bang"), "'bang' expected to be in dictionary");
	ASSERT_FALSE(is_in_dict(dict, "hui"), "'hui' expected NOT to be in dictionary");

	delete_dictionary(dict);
	ASSERT_EQUALS(3, get_free_list_length());
	ASSERT_TRUE(get_free_list()[2] == dict, "Pointer to dictionary expected to be the last deleted");
}

TEST(ignore_double_entry)
{
	init_free_list();
	Dictionary dict = new_dictionary();
	add(dict, "hui");
	add(dict, "pfui");
	add(dict, "lui");
	ASSERT_EQUALS(3, get_size(dict));

	add(dict, "pfui");
	ASSERT_EQUALS(3, get_size(dict));
	ASSERT_TRUE(is_in_dict(dict, "hui"), "'hui' expected to be in dictionary");
	ASSERT_TRUE(is_in_dict(dict, "pfui"), "'pfui' expected to be in dictionary");
	ASSERT_TRUE(is_in_dict(dict, "lui"), "'lui' expected to be in dictionary");

	delete_dictionary(dict);
	ASSERT_EQUALS(4, get_free_list_length());
	ASSERT_TRUE(get_free_list()[3] == dict, "Pointer to dictionary expected to be the last deleted");
}

static Dictionary setup_dict_with_add();
TEST(add_many)
{
	init_free_list();
	Dictionary dict = setup_dict_with_add();
	ASSERT_EQUALS(45, get_size(dict));

	delete_dictionary(dict);
	ASSERT_EQUALS(46, get_free_list_length());
	ASSERT_TRUE(get_free_list()[45] == dict, "Pointer to dictionary expected to be the last deleted");
}

static Dictionary setup_dict_with_add()
{
	Dictionary dict = new_dictionary();
	for (int i = 0; test_words[i] != 0; i++) {
		add(dict, test_words[i]);
	}
	return dict;
}

TEST(in_dictionary)
{
	init_free_list();
	Dictionary dict = setup_dict_with_add();

	ASSERT_TRUE(is_in_dict(dict, "and"), "'and' expected to be in dict");
	ASSERT_TRUE(is_in_dict(dict, "downstairs"), "'downstairs' expected to be in dict");
	ASSERT_TRUE(is_in_dict(dict, "tailor"), "'tailor' expected to be in dict");
	ASSERT_TRUE(is_in_dict(dict, "vanisher"), "'vanisher' expected to be in dict");
	ASSERT_TRUE(is_in_dict(dict, "weekend"), "'weekend' expected to be in dict");

	ASSERT_FALSE(is_in_dict(dict, "aaron"), "'aaron' NOT expected to be in dict");
	ASSERT_FALSE(is_in_dict(dict, "scheduler"), "'scheduler' NOT expected to be in dict");
	ASSERT_FALSE(is_in_dict(dict, "zeppelin"), "'zeppelin' NOT expected to be in dict");
	delete_dictionary(dict);
}

TEST(case_insensitivity)
{
	init_free_list();
	Dictionary dict = setup_dict_with_add();

	ASSERT_TRUE(is_in_dict(dict, "Downstairs"), "'Downstairs' expected to be in dict");
	ASSERT_TRUE(is_in_dict(dict, "Cabbage"), "'Cabbage' expected to be in dict");
	ASSERT_TRUE(is_in_dict(dict, "Weekend"), "'Weekend' expected to be in dict");
	delete_dictionary(dict);
}

// for a test length these tests are added
TEST(iterating)
{
	Dictionary dict = new_dictionary();
	add(dict, "Hui");
	add(dict, "Pfui");
	start_iterating(dict);
	ASSERT_TRUE(has_next(dict), "It is expected that a first entry is available");
	const char* first_word = get_next_entry(dict);
	ASSERT_EQUALS("Hui", first_word);

	ASSERT_TRUE(has_next(dict), "It is expected that a second entry is available");
	const char* second_word = get_next_entry(dict);
	ASSERT_EQUALS("Pfui", second_word);

	ASSERT_FALSE(has_next(dict), "No further entry is expected");
	ASSERT_TRUE(get_next_entry(dict) == 0, "If iterator is at end 0 is expected");
	delete_dictionary(dict);
}

TEST(iterating_fails_because_call_start_iterating_is_missing)
{
	Dictionary dict = new_dictionary();
	add(dict, "Hui");
	add(dict, "Pfui");
	// start_iterating(dict) not called to make it fail
	ASSERT_FALSE(has_next(dict), "has_next expected to be false if no start_iterating was called");
	ASSERT_TRUE(get_next_entry(dict) == 0, "If start_iterating is not called no entry shall be returned");
	delete_dictionary(dict);
}

TEST(iterating_an_empty_directory)
{
	Dictionary dict = new_dictionary();
	start_iterating(dict);
	ASSERT_FALSE(has_next(dict), "has_next expected to be false if no start_iterating was called");
	ASSERT_TRUE(get_next_entry(dict) == 0, "If start_iterating is not called no entry shall be returned");
	delete_dictionary(dict);
}

TEST(insert_sorted_first_element)
{
	Dictionary dict = new_dictionary();
	insert_sorted(dict, "Hui");
	ASSERT_EQUALS(1, get_size(dict));
	start_iterating(dict);
	ASSERT_EQUALS("Hui", get_next_entry(dict));
	delete_dictionary(dict);
}

TEST(insert_sorted_second_element)
{
	Dictionary dict = new_dictionary();
	insert_sorted(dict, "Hui");
	insert_sorted(dict, "Pfui");
	ASSERT_EQUALS(2, get_size(dict));
	start_iterating(dict);
	ASSERT_EQUALS("Hui", get_next_entry(dict));
	ASSERT_EQUALS("Pfui", get_next_entry(dict));
	delete_dictionary(dict);
}

TEST(insert_sorted_elements_coming_unordered)
{
	Dictionary dict = new_dictionary();
	insert_sorted(dict, "Pfui");
	insert_sorted(dict, "Hui");
	ASSERT_EQUALS(2, get_size(dict));

	start_iterating(dict);
	ASSERT_EQUALS("Hui", get_next_entry(dict));
	ASSERT_EQUALS("Pfui", get_next_entry(dict));
}

static Dictionary setup_dict_with_insert(Direction direction);
TEST(insert_sorted_at_end)
{
	Dictionary dict = setup_dict_with_insert(ASCENDING);
	start_iterating(dict);
	for (int i = 0; test_words[i] != 0; i++) {
		ASSERT_EQUALS(test_words[i], get_next_entry(dict));
	}
}

static Dictionary setup_dict_with_insert(Direction direction)
{
	Dictionary dict = new_dictionary();
	for (int i = 0; test_words[i] != 0; i++) {
		switch (direction) {
			case ASCENDING:
				insert_sorted(dict, test_words[i]);
				break;

			case DESCENDING:
				insert_sorted(dict, test_words[WORD_COUNT - i - 1]);
				break;

			default:
				int shuffled_indices[WORD_COUNT];
				for (int i = 0; i < WORD_COUNT; i++) {
					shuffled_indices[i] = i;
				}
				srandom(time(NULL));
				for (int i = 0; i < WORD_COUNT; i++) {
					int r = random() % WORD_COUNT;
					int swap_element = shuffled_indices[i];
					shuffled_indices[i] = shuffled_indices[r];
					shuffled_indices[r] = swap_element;
				}
				insert_sorted(dict, test_words[shuffled_indices[i]]);
				break;
		}
	}
	return dict;
}

TEST(insert_revers_sorted)
{
	Dictionary dict = setup_dict_with_insert(DESCENDING);
	start_iterating(dict);
	for (int i = 0; test_words[i] != 0; i++) {
		ASSERT_EQUALS(test_words[i], get_next_entry(dict));
	}
}

TEST(insert_random)
{
	Dictionary dict = setup_dict_with_insert(RANDOM);
	start_iterating(dict);
	for (int i = 0; test_words[i] != 0; i++) {
		ASSERT_EQUALS(test_words[i], get_next_entry(dict));
	}
}

TEST(insert_ignores_double_entries)
{
	Dictionary dict = setup_dict_with_insert(ASCENDING);
	ASSERT_EQUALS(WORD_COUNT, get_size(dict));
	insert_sorted(dict, test_words[WORD_COUNT / 2]);
	ASSERT_EQUALS(WORD_COUNT, get_size(dict));
}
