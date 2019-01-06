/*
set ADT for hash tables with separate chaining
*/

#include "set.h"
#include "util.h"
#include <stdlib.h>
#include <stdio.h>
#define SIZE 307
/******************************/



struct hash_list{
	struct hash_list *next;
	int val;
};

/* typedef struct set set_t is defined in set.h */
struct set {
	struct hash_list *buckets[SIZE]; 
};

set_t *set_create(void)
{
	int i;
	set_t *new_set;
	new_set = safe_malloc(sizeof(set_t));
	for (i = 0; i < SIZE; ++i) {
		new_set->buckets[i] = NULL;
	}
	return new_set;
}

void set_destroy(set_t *set)
{
	int i;
	for (i = 0; i < SIZE; ++i) {
		struct hash_list *node;
		node = set->buckets[i];
		while (node != NULL) {
			struct hash_list *del_node = node;
			node = node->next;
			free(del_node);
		}
	}
	free(set);	
	return;	
}

int set_insert(set_t *set, int new_val)
{
	int i = new_val % SIZE;
	struct hash_list *curr;
	curr = set->buckets[i];
	if (curr == NULL) { 
		set->buckets[i] = safe_malloc(sizeof(struct hash_list));
		set->buckets[i]->next = NULL;
		set->buckets[i]->val = new_val;
		return 1;
	}
	while (curr->next && curr->val != new_val) {
		curr = curr->next;
	}
	if (curr->val == new_val){
		return 0;
	}
	struct hash_list *node = safe_malloc(sizeof(struct hash_list));
	node->next = NULL;
	node->val = new_val;
	curr->next = node;
	return 1;
}

int set_delete(set_t *set, int del_val)
{
	int i = del_val % SIZE;
	struct hash_list *curr;
	curr = set->buckets[i];
	if (curr == NULL) {
		return 0;
	}
	struct hash_list *prev;
	prev = curr;
	while (curr->next && curr->val != del_val ) {
		prev = curr;
		curr = curr->next;
	}
	if (curr->val == del_val) {
		if (curr == prev) {
			set->buckets[i] = curr->next;
		} else {
			prev->next = curr->next;
		}
		free(curr);
		return 1;	
	}
	return 0;
}

int set_search(set_t *set, int search_val)
{
	int i = search_val % SIZE;
	struct hash_list *curr;
	curr = set->buckets[i];
	if (curr == NULL) {
		return 0;
	}
	while (curr->next && curr->val != search_val ){
		curr = curr->next;
	}
	if (curr->val == search_val) {
		return 1;
	}
	return 0;
}

void set_print(set_t *set)
{	 
	int i=0;
    while(i != SIZE){
		printf("Position %d-Values with the same hash value:",i);
		while((set->buckets[i])!= NULL){
		printf("%d",set->buckets[i]->val);
		printf("->");
		set->buckets[i]=set->buckets[i]->next;
		}
    printf("\n");
    i++;
    }
}

