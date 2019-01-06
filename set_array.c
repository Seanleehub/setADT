/*
set ADT for arrays
*/

#include "set.h"
#include "util.h"
#include <stdlib.h>
#include <stdio.h>
#define INITIAL_SIZE 10
/******************************/


/* typedef struct set set_t is defined in set.h */
struct set {
	int Capacity;
	int Size;
	int *Array;	
};

set_t *set_create(void)
{
	set_t *new_set;
	new_set = safe_malloc(sizeof(set_t));
	new_set->Capacity = INITIAL_SIZE;
	new_set->Size = 0;
	new_set->Array = (int*)malloc(new_set->Capacity * sizeof(int));		
	return new_set;
}

void set_destroy(set_t *set)
{
	if( set != NULL ){
		free( set->Array );
		free( set );
    }
}

int binarySearch (int a[], int low, int high, int key)
{
    int mid;
    if (low == high)
    return low;
    mid = low + ((high - low) / 2);
    if (key > a[mid]){
        return binarySearch (a, mid + 1, high, key);
	}	
    else if (key < a[mid]){
        return binarySearch (a, low, mid, key);
	}
    return mid;
}

int set_insert(set_t *set, int new_val)
{	
	if (set->Size == set->Capacity - 1){	
		set->Capacity *= 2;
		set->Array = (int*)safe_realloc(set->Array,set->Capacity * sizeof(int));			
	}
	
	int a = set->Array[binarySearch(set->Array, 0, set->Size, new_val)];
	if (a == new_val){			
		return 0;		
	}
	
	int ins, i, j;
    int temp;
	set->Array[set->Size] = new_val;
	set->Size++;	
	 for (i =1; i < set->Size; i++){
        ins = binarySearch (set->Array, 0, i, set->Array[i]);	
        if (ins < i){
            temp = set->Array[i];
            for (j = i - 1; j >= ins; j--)
                set->Array[j + 1] = set->Array[j];
           set->Array[ins] = temp;
        }
    }
   		
	return 1;
}

int set_delete(set_t *set, int del_val)
{	
	int b = binarySearch(set->Array, 0, set->Size, del_val);
	int c = set->Array[binarySearch(set->Array, 0, set->Size, del_val)];
	int a;
		if(c == del_val){
			for (a = b ; a < set->Size;a++){
				set->Array[a] = set->Array[a + 1];
			}
		set->Size--;
		return 1;
		}		
	
	return 0;	
}

int set_search(set_t *set, int search_val)
{	
	int a = set->Array[binarySearch(set->Array, 0, set->Size, search_val)];
		if (a == search_val){			
			return 1;		
		}
	return 0;	
}

void set_print(set_t *set)
{
	int i;
	int a=0;
	if (set->Size == 0)
	{ 
		printf("Array is Empty"); 
	}
	else{
		for (i = 0; i < set->Size; i++){
		a = i+1;
		printf("%d", set->Array[i]);		
			if(set->Array[a]!= '\0'){
				printf("->");
			}
			else{
				printf("\n");
			}			
		}		
	}
}


