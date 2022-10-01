// Copyright 2022 Alexandru_Mihai 313CA
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "doubly_linked_list.h"

doubly_linked_list_t* dll_create(unsigned int data_size)
{
	doubly_linked_list_t* list = malloc(sizeof(doubly_linked_list_t));
	DIE(!list, "malloc failed!\n");

	list->head = NULL;
	list->tail = NULL;
	list->size = 0;
	list->data_size = data_size;

	return list;
}

dll_node_t* dll_get_nth_node(doubly_linked_list_t *list, int n)
{
	DIE(!list, "Uninitiliazed list!\n");

	if (n < 0 || n + 1 > (int)list->size)
		return NULL;

	dll_node_t *current = list->head;

	for (int i = 0; i < n; i++)
		current = current->next;

	return current;
}

void dll_add_nth_node(doubly_linked_list_t *list, unsigned int n, void* data)
{
	DIE(!list, "Uninitiliazed list!\n");

	dll_node_t *new_node = malloc(sizeof(dll_node_t));

	DIE(!new_node, "malloc failed.\n");

	new_node->data = malloc(list->data_size);
	memcpy(new_node->data, data, list->data_size);

	if (n > list->size)
		n = list->size;

	if (list->size == 0) {
		new_node->next = NULL;
		new_node->prev = NULL;
		list->head = new_node;
		list->tail = new_node;
	} else if (n == 0) {
		new_node->next = list->head;
		new_node->prev = NULL;
		list->head->prev = new_node;
		list->head = new_node;
	} else if (n == list->size) {
		new_node->next = NULL;
		new_node->prev = list->tail;
		list->tail->next = new_node;
		list->tail = new_node;
	} else {
		dll_node_t *current = dll_get_nth_node(list, n - 1);
		new_node->next = current->next;
		new_node->prev = current;
		current->next->prev = new_node;
		current->next = new_node;
	}

	list->size++;
}

dll_node_t *dll_remove_nth_node(doubly_linked_list_t *list, int n)
{
	DIE(!list, "Uninitiliazed list!\n");

	if (n < 0 || n + 1 > (int)list->size)
		return NULL;

	dll_node_t *removed;

	if (list->size == 1) {
		removed = list->tail;
		list->head = NULL;
		list->tail = NULL;
	} else if (n == 0) {
		removed = list->head;
		removed->next->prev = NULL;
		list->head = list->head->next;
	} else if (n == (int)list->size - 1) {
		removed = list->tail;
		removed->prev->next = NULL;
		list->tail = list->tail->prev;
	} else {
		removed = dll_get_nth_node(list, n);
		removed->next->prev = removed->prev;
		removed->prev->next = removed->next;
	}

	list->size--;
	return removed;
}

int dll_list_size(doubly_linked_list_t *list)
{
	DIE(!list, "Uninitiliazed list!\n");

	return list->size;
}

void dll_free_cardlist(doubly_linked_list_t **p_list)
{
	DIE(!p_list, "Uninitiliazed pointer to list!\n");

	DIE(!(*p_list), "Uninitiliazed list!\n");

	dll_node_t *current;

	while ((*p_list)->size) {
		current = dll_remove_nth_node(*p_list, 0);
		free(current->data);
		free(current);
	}
	free(*p_list);
}

void dll_free_decklist(doubly_linked_list_t **p_list)
{
	DIE(!p_list, "Uninitiliazed pointer to list!\n");

	DIE(!(*p_list), "Uninitiliazed list!\n");

	dll_node_t *current;

	while ((*p_list)->size) {
		current = dll_remove_nth_node(*p_list, 0);
		dll_free_cardlist((doubly_linked_list_t **)(&current->data));
		free(current);
	}

	free(*p_list);
}

void print_decklist(doubly_linked_list_t *list)
{
	DIE(!list, "Uninitiliazed list!\n");

	dll_node_t *current = list->head;

	for (unsigned int i = 0; i < list->size; i++) {
		print_cardlist(current->data, i);
		current = current->next;
	}
}

void print_cardlist(doubly_linked_list_t *list, unsigned int index)
{
	DIE(!list, "Uninitiliazed list!\n");

	dll_node_t *current = list->head;

	printf("Deck %d:\n", index);

	for (unsigned int i = 0; i < list->size; i++) {
		printf("\t%d %s\n", ((card_t *)current->data)->number,
			((card_t *)current->data)->symbol);
		current = current->next;
	}
}
