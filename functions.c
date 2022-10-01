// Copyright 2022 Alexandru_Mihai 313CA
#include <stdio.h>
#include <string.h>

#include "functions.h"

void invalid_command()
{
	printf("Invalid command. Please try again.\n");
}

unsigned int check_card(card_t card)
{
	if (card.number > 0 && card.number < 15) {
		if (strcmp(card.symbol, "HEART") == 0 || strcmp(card.symbol, "CLUB") == 0 ||
			strcmp(card.symbol, "DIAMOND") == 0 || strcmp(card.symbol, "SPADE") == 0)
			return 1;
	}

	printf("The provided card is not a valid one.\n");
	return 0;
}

unsigned int check_deck_index(doubly_linked_list_t* list, int index)
{
	DIE(!list, "Uninitiliazed list!\n");

	if (index < 0 || index + 1 > (int)list->size) {
		printf("The provided index is out of bounds for the deck list.\n");
		return 0;
	}
	return 1;
}

unsigned int
check_card_index(doubly_linked_list_t* list, int index, int deck_index)
{
	DIE(!list, "Uninitiliazed list!\n");

	if (index < 0 || index + 1 > (int)list->size) {
		printf("The provided index is out of bounds for deck %d.\n", deck_index);
		return 0;
	}

	return 1;
}

void shuffle(doubly_linked_list_t* list)
{
	unsigned int length = dll_list_size(list);

	if (length == 1)
		return;

	// rearranging the nodes for the shuffle
	dll_node_t *new_first = dll_get_nth_node(list, (length / 2));

	dll_node_t *new_last = new_first->prev;

	new_first->prev = NULL;
	new_last->next = NULL;

	list->head->prev = list->tail;
	list->tail->next = list->head;

	list->head = new_first;
	list->tail = new_last;
}

doubly_linked_list_t*
merge_decks(doubly_linked_list_t* list1, doubly_linked_list_t* list2)
{
	doubly_linked_list_t* new_list = dll_create(sizeof(card_t));

	dll_node_t *current1 = list1->head;
	dll_node_t *current2 = list2->head;

	while (current1 || current2) {
		if (current1 != NULL) {
			dll_add_nth_node(new_list, new_list->size, current1->data);
			current1 = current1->next;
		}
		if (current2 != NULL) {
			dll_add_nth_node(new_list, new_list->size, current2->data);
			current2 = current2->next;
		}
	}

	return new_list;
}

doubly_linked_list_t* split_deck(doubly_linked_list_t* list, int split_index)
{
	if (split_index == 0)
		return NULL;

	doubly_linked_list_t* new_deck = dll_create(sizeof(card_t));

	dll_node_t *current;

	// removing the additional nodes and adding them to the new deck
	while ((int)list->size > split_index) {
		current = dll_remove_nth_node(list, split_index);
		dll_add_nth_node(new_deck, new_deck->size, current->data);
		free(current->data);
		free(current);
	}

	return new_deck;
}

void reverse_deck(doubly_linked_list_t* list)
{
	int length = list->size;

	dll_node_t *removed;

	for (int i = 0; i < length; i++) {
		removed = dll_remove_nth_node(list, length - 1);
		dll_add_nth_node(list, i, removed->data);
		free(removed->data);
		free(removed);
	}
}

void sort_deck(doubly_linked_list_t* list)
{
	int index_min;

	dll_node_t *replaced, *current;

	for (unsigned int i = 0; i < list->size; i++) {
		index_min = i;
		replaced = dll_get_nth_node(list, i);

		for (unsigned int k = i + 1; k < list->size; k++) {
			current = dll_get_nth_node(list, k);
			if (compare_cards(replaced->data, current->data) > 0) {
				replaced = current;
				index_min = k;
			}
		}

		replaced = dll_remove_nth_node(list, index_min);
		dll_add_nth_node(list, i, replaced->data);

		free(replaced->data);
		free(replaced);
	}
}

int compare_cards(card_t* card1, card_t* card2)
{
	if (card1->number > card2->number)
		return 1;

	if (card1->number < card2->number)
		return -1;

	int symbol1 = determine_symbol(card1->symbol);
	int symbol2 = determine_symbol(card2->symbol);

	if (symbol1 > symbol2)
		return 1;

	if (symbol1 < symbol2)
		return -1;

	return 0;
}

// functions for priority of the symbols
int determine_symbol(char *symbol)
{
	if (strcmp(symbol, "HEART") == 0)
		return 0;

	if (strcmp(symbol, "SPADE") == 0)
		return 1;

	if (strcmp(symbol, "DIAMOND") == 0)
		return 2;

	return 3;
}

// converting a string that includes card info
card_t get_card(char *card_string)
{
	card_t new_card;

	char *token = strtok(card_string, " \n");
	new_card.number = atoi(token);
	token = strtok(NULL, " \n");
	strcpy(new_card.symbol, token);

	return new_card;
}
