// Copyright 2022 Alexandru_Mihai 313CA
#include <stdio.h>
#include <string.h>

#include "commands.h"

void add_deck_command(char *token, doubly_linked_list_t *my_decks)
{
	token = strtok(NULL, " \n");
	if (!token) {
		invalid_command();
		return;
	}

	int cards_number = atoi(token);
	if (cards_number < 1) {
		invalid_command();
		return;
	}

	token = strtok(NULL, " \n");
	if (token) {
		invalid_command();
		return;
	}

	doubly_linked_list_t *new_deck = dll_create(sizeof(card_t));


	card_t new_card;
	char card_string[MAX_STRING_LENGTH];

	for (int i = 0; i < cards_number; i++) {
		fgets(card_string, MAX_STRING_LENGTH, stdin);

		new_card = get_card(card_string);

		// the card is not valid, looking for another one
		if (!check_card(new_card))
			i--;
		else
			dll_add_nth_node(new_deck, new_deck->size, &new_card);
	}

	dll_add_nth_node(my_decks, my_decks->size, new_deck);

	free(new_deck);

	printf("The deck was successfully created with %d cards.\n", cards_number);
}

void del_deck_command(char *token, doubly_linked_list_t *my_decks)
{
	token = strtok(NULL, " \n");
	if (!token) {
		invalid_command();
		return;
	}

	int deck_index = atoi(token);

	token = strtok(NULL, " \n");
	if (token) {
		invalid_command();
		return;
	}

	if (!check_deck_index(my_decks, deck_index))
		return;

	dll_node_t* removed = dll_remove_nth_node(my_decks, deck_index);

	dll_free_cardlist((doubly_linked_list_t **)(&removed->data));
	free(removed);

	printf("The deck %d was successfully deleted.\n", deck_index);
}

void del_card_command(char *token, doubly_linked_list_t *my_decks)
{
	token = strtok(NULL, " \n");
	if (!token) {
		invalid_command();
		return;
	}

	int deck_index = atoi(token);

	token = strtok(NULL, " \n");
	if (!token) {
		invalid_command();
		return;
	}

	int card_index = atoi(token);

	token = strtok(NULL, " \n");
	if (token) {
		invalid_command();
		return;
	}

	if (!check_deck_index(my_decks, deck_index))
		return;

	dll_node_t *current = dll_get_nth_node(my_decks, deck_index);

	if(!check_card_index(current->data, card_index, deck_index))
		return;

	dll_node_t* removed = dll_remove_nth_node(current->data, card_index);

	free(removed->data);
	free(removed);

	// in case that the deck has no more cards, the deck will be removed
	if (((doubly_linked_list_t *)current->data)->size == 0) {
		current = dll_remove_nth_node(my_decks, deck_index);
		free(current->data);
		free(current);
	}

	printf("The card was successfully deleted from deck %d.\n", deck_index);
}

void add_cards_command(char *token, doubly_linked_list_t *my_decks)
{
	token = strtok(NULL, " \n");
	if (!token) {
		invalid_command();
		return;
	}

	int deck_index = atoi(token);

	token = strtok(NULL, " \n");
	if (!token) {
		invalid_command();
		return;
	}

	int cards_number = atoi(token);
	if (cards_number < 1) {
		invalid_command();
		return;
	}

	token = strtok(NULL, " \n");
	if (token) {
		invalid_command();
		return;
	}

	if (!check_deck_index(my_decks, deck_index))
		return;

	dll_node_t *current = dll_get_nth_node(my_decks, deck_index);

	card_t new_card;
	char card_string[MAX_STRING_LENGTH];

	for (int i = 0; i < cards_number; i++) {
		fgets(card_string, MAX_STRING_LENGTH, stdin);

		new_card = get_card(card_string);

		if (!check_card(new_card))
			i--;
		else
			dll_add_nth_node(current->data,
				((doubly_linked_list_t *)current->data)->size, &new_card);
	}

	printf("The cards were successfully added to deck %d.\n", deck_index);
}

void deck_number_command(char *token, doubly_linked_list_t *my_decks)
{
	token = strtok(NULL, " \n");
	if (token) {
		invalid_command();
		return;
	}

	printf("The number of decks is %d.\n", dll_list_size(my_decks));
}

void deck_len_command(char *token, doubly_linked_list_t *my_decks)
{
	token = strtok(NULL, " \n");
	if (!token) {
		invalid_command();
		return;
	}

	int deck_index = atoi(token);

	token = strtok(NULL, " \n");
	if (token) {
		invalid_command();
		return;
	}

	if (!check_deck_index(my_decks, deck_index))
		return;

	dll_node_t *current = dll_get_nth_node(my_decks, deck_index);

	printf("The length of deck %d is %d.\n", deck_index,
		dll_list_size(current->data));
}

void shuffle_deck_command(char *token, doubly_linked_list_t *my_decks)
{
	token = strtok(NULL, " \n");
	if (!token) {
		invalid_command();
		return;
	}

	int deck_index = atoi(token);

	token = strtok(NULL, " \n");
	if (token) {
		invalid_command();
		return;
	}

	if (!check_deck_index(my_decks, deck_index))
		return;

	dll_node_t *current = dll_get_nth_node(my_decks, deck_index);

	shuffle(current->data);

	printf("The deck %d was successfully shuffled.\n", deck_index);
}

void merge_decks_command(char *token, doubly_linked_list_t *my_decks)
{
	token = strtok(NULL, " \n");
	if (!token) {
		invalid_command();
		return;
	}

	int deck1_index = atoi(token);

	token = strtok(NULL, " \n");

	if (!token) {
		invalid_command();
		return;
	}

	int deck2_index = atoi(token);

	token = strtok(NULL, " \n");
	if (token) {
		invalid_command();
		return;
	}

	if (!check_deck_index(my_decks, deck1_index))
		return;

	if(!check_deck_index(my_decks, deck2_index))
		return;

	dll_node_t *deck1, *deck2;

	// the size of the list could be misleading while removing a node
	// therefore the cases have been treated separately
	if (deck1_index > deck2_index) {
		deck1 = dll_remove_nth_node(my_decks, deck1_index);
		deck2 = dll_remove_nth_node(my_decks, deck2_index);
	} else {
		deck2 = dll_remove_nth_node(my_decks, deck2_index);
		deck1 = dll_remove_nth_node(my_decks, deck1_index);
	}

	doubly_linked_list_t *new_deck = merge_decks(deck1->data, deck2->data);

	dll_free_cardlist((doubly_linked_list_t **)(&deck1->data));
	free(deck1);
	dll_free_cardlist((doubly_linked_list_t **)(&deck2->data));
	free(deck2);

	dll_add_nth_node(my_decks, my_decks->size, new_deck);

	free(new_deck);

	printf("The deck %d and the deck %d were successfully merged.\n",
		deck1_index, deck2_index);
}

void split_deck_command(char *token, doubly_linked_list_t *my_decks)
{
	token = strtok(NULL, " \n");
	if (!token) {
		invalid_command();
		return;
	}

	int deck_index = atoi(token);

	token = strtok(NULL, " \n");
	if (!token) {
		invalid_command();
		return;
	}

	int split_index = atoi(token);

	token = strtok(NULL, " \n");
	if (token) {
		invalid_command();
		return;
	}

	if (!check_deck_index(my_decks, deck_index))
		return;

	dll_node_t *deck = dll_get_nth_node(my_decks, deck_index);

	if (!check_card_index(deck->data, split_index, deck_index))
		return;

	doubly_linked_list_t *new_deck = split_deck(deck->data, split_index);

	// cannot add an empty deck to the list, although the opperation was made
	if (new_deck) {
		dll_add_nth_node(my_decks, deck_index + 1, new_deck);
		free(new_deck);
	}

	printf("The deck %d was successfully split by index %d.\n",
		deck_index, split_index);
}

void reverse_deck_command(char *token, doubly_linked_list_t *my_decks)
{
	token = strtok(NULL, " \n");
	if (!token) {
		invalid_command();
		return;
	}

	int deck_index = atoi(token);

	token = strtok(NULL, " \n");
	if (token) {
		invalid_command();
		return;
	}

	if (!check_deck_index(my_decks, deck_index))
		return;

	dll_node_t *deck = dll_get_nth_node(my_decks, deck_index);

	reverse_deck(deck->data);

	printf("The deck %d was successfully reversed.\n", deck_index);
}

void show_deck_command(char *token, doubly_linked_list_t *my_decks)
{
	token = strtok(NULL, " \n");
	if (!token) {
		invalid_command();
		return;
	}

	int deck_index = atoi(token);

	token = strtok(NULL, " \n");
	if (token) {
		invalid_command();
		return;
	}

	if (!check_deck_index(my_decks, deck_index))
		return;

	dll_node_t *current = dll_get_nth_node(my_decks, deck_index);

	print_cardlist(current->data, deck_index);
}

void show_all_command(char *token, doubly_linked_list_t *my_decks)
{
	token = strtok(NULL, " \n");
	if (token) {
		invalid_command();
		return;
	}

	print_decklist(my_decks);
}

void sort_deck_command(char *token, doubly_linked_list_t *my_decks)
{
	token = strtok(NULL, " \n");
	if (!token) {
		invalid_command();
		return;
	}

	int deck_index = atoi(token);

	token = strtok(NULL, " \n");
	if (token) {
		invalid_command();
		return;
	}

	if (!check_deck_index(my_decks, deck_index))
		return;

	dll_node_t *deck = dll_get_nth_node(my_decks, deck_index);

	sort_deck(deck->data);

	printf("The deck %d was successfully sorted.\n", deck_index);
}
