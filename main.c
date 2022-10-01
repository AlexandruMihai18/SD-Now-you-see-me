// Copyright 2022 Alexandru_Mihai 313CA
#include <stdio.h>
#include <string.h>

#include "commands.h"

int main(void){
	doubly_linked_list_t *my_decks = dll_create(sizeof(doubly_linked_list_t));
	char command[MAX_STRING_LENGTH];
	char *token;
	while (1) {
		fgets(command, MAX_STRING_LENGTH, stdin);
		token = strtok(command, " \n");
		if (strcmp(command, "ADD_DECK") == 0) {
			add_deck_command(token, my_decks);
		} else if (strcmp(command, "DEL_DECK") == 0) {
			del_deck_command(token, my_decks);
		} else if (strcmp(command, "DEL_CARD") == 0) {
			del_card_command(token, my_decks);
		} else if (strcmp(command, "ADD_CARDS") == 0) {
			add_cards_command(token, my_decks);
		} else if (strcmp(command, "DECK_NUMBER") == 0) {
			deck_number_command(token, my_decks);
		} else if (strcmp(command, "DECK_LEN") == 0) {
			deck_len_command(token, my_decks);
		} else if (strcmp(command, "SHUFFLE_DECK") == 0) {
			shuffle_deck_command(token, my_decks);
		} else if (strcmp(command, "MERGE_DECKS") == 0) {
			merge_decks_command(token, my_decks);
		} else if (strcmp(command, "SPLIT_DECK") == 0) {
			split_deck_command(token, my_decks);
		} else if (strcmp(command, "REVERSE_DECK") == 0){
			reverse_deck_command(token, my_decks);
		} else if (strcmp(command, "SHOW_DECK") == 0) {
			show_deck_command(token, my_decks);
		} else if (strcmp(command, "SHOW_ALL") == 0) {
			show_all_command(token, my_decks);
		} else if (strcmp(command, "SORT_DECK") == 0) {
			sort_deck_command(token, my_decks);
		} else if (strcmp(command, "EXIT") == 0) {
			break;
		} else {
			invalid_command();
		}
	}
	dll_free_decklist(&my_decks);
	return 0;
}
