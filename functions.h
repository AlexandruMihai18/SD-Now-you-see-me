// Copyright 2022 Alexandru_Mihai 313CA
#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_

#include "doubly_linked_list.h"

void invalid_command();

unsigned int check_card(card_t card);

unsigned int check_deck_index(doubly_linked_list_t* list, int index);

unsigned int
check_card_index(doubly_linked_list_t* list, int index, int deck_index);

void shuffle(doubly_linked_list_t* list);

doubly_linked_list_t*
merge_decks(doubly_linked_list_t* list1, doubly_linked_list_t* list2);

doubly_linked_list_t* split_deck(doubly_linked_list_t* list, int split_index);

void reverse_deck(doubly_linked_list_t* list);

void sort_deck(doubly_linked_list_t* list);

int compare_cards(card_t* card1, card_t* card2);

int determine_symbol(char *symbol);

card_t get_card(char *card_string);

#endif  // FUNCTIONS_H_
