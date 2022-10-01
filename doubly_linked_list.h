// Copyright 2022 Alexandru_Mihai 313CA
#ifndef DOUBLY_LINKED_LIST_H_
#define DOUBLY_LINKED_LIST_H_

#include "utils.h"

#define MAX_SYMBOL_LENGTH 8

typedef struct doubly_linked_list_t doubly_linked_list_t;

typedef struct dll_node_t dll_node_t;

typedef struct card_t card_t;

struct doubly_linked_list_t {
	dll_node_t* head;
	dll_node_t* tail;
	unsigned int size;
	unsigned int data_size;
};

struct dll_node_t {
	void *data;
	dll_node_t *prev, *next;
};

struct card_t {
	unsigned int number;
	char symbol[MAX_SYMBOL_LENGTH];
};

doubly_linked_list_t* dll_create(unsigned int data_size);

dll_node_t* dll_get_nth_node(doubly_linked_list_t *list, int n);

void dll_add_nth_node(doubly_linked_list_t *list, unsigned int n, void* data);

dll_node_t *dll_remove_nth_node(doubly_linked_list_t *list, int n);

int dll_list_size(doubly_linked_list_t *list);

void dll_free_cardlist(doubly_linked_list_t **p_list);

void dll_free_decklist(doubly_linked_list_t **p_list);

void print_decklist(doubly_linked_list_t *list);

void print_cardlist(doubly_linked_list_t *list, unsigned int index);

#endif  // DOUBLY_LINKED_LIST_H_
