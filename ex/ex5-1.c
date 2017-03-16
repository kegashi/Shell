#include <stdio.h>
#define NULL 0

struct list{
	struct list *next;
	int suit;
	int number;		
};

struct list *add(struct list *l, int suit, int number){
	struct list *new;

	new = (struct list *) malloc(sizeof(struct list));
	new->next = l;
	new->suit = suit;
	new->number = number;
	return new;
}

int main(){
	struct list *head, *lp;
	int suit, number;
	
	head = NULL;
	for (suit = 1; suit <= 4; suit++){
		for (number = 1; number <= 13; number++){
			head = add(head, suit, number);		
		}		
	}	
}
