// Copyright 2022 Alexandru_Mihai 313CA
#ifndef COMMANDS_H_
#define COMMANDS_H_

#include "functions.h"

#define MAX_STRING_LENGTH 64

void add_deck_command(char *token, doubly_linked_list_t  *my_decks);

void del_deck_command(char *token, doubly_linked_list_t  *my_decks);

void del_card_command(char *token, doubly_linked_list_t  *my_decks);

void add_cards_command(char *token, doubly_linked_list_t  *my_decks);

void deck_number_command(char *token, doubly_linked_list_t  *my_decks);

void deck_len_command(char *token, doubly_linked_list_t  *my_decks);

void shuffle_deck_command(char *token, doubly_linked_list_t  *my_decks);

void merge_decks_command(char *token, doubly_linked_list_t  *my_decks);

void split_deck_command(char *token, doubly_linked_list_t  *my_decks);

void reverse_deck_command(char *token, doubly_linked_list_t  *my_decks);

void show_deck_command(char *token, doubly_linked_list_t  *my_decks);

void show_all_command(char *token, doubly_linked_list_t  *my_decks);

void sort_deck_command(char *token, doubly_linked_list_t  *my_decks);

#endif  // COMMANDS_H_
