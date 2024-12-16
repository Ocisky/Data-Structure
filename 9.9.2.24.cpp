#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
typedef struct Cell{
    double c;
    int e;
    struct Cell *next;
}Cell;

typedef Cell *Position;
typedef Position Polynomial;

Position makeNull(Polynomial *pL){
    Position header = (Position) malloc(sizeof(Cell));
    header->next = NULL;
    *pL = header;
    return *pL;
}

void printList(Polynomial *pL){
    if((*pL)->next == NULL){
        printf("\n");
        return;
    }
    Position temp = *pL;
    while(temp->next != NULL){
        printf("%.2lfx^%d", temp->next->c, temp->next->e);
        if(temp->next->next != NULL){
            printf(" + ");
        }
        temp = temp->next;
    }
    printf("\n");
}

void insert(double c, int e, Polynomial *pL){
    Position newNode = (Position)malloc(sizeof(Cell));
    if((*pL)->next == NULL){
        newNode->c = c;
        newNode->e = e;
        (*pL)->next = newNode;
        newNode->next = NULL;
    }
    Position temp = *pL;
    while(temp->next != NULL){
        if(e == temp->next->e){
            temp->next->c = c;
            return;
        }
        
        if(e > temp->next->e){
            newNode->c = c;
            newNode->e = e;
            newNode->next = temp->next;
            temp->next = newNode;
            return;
        }
        
        temp=temp->next;
    }
    newNode->c = c;
    newNode->e = e;
    temp->next = newNode;
    newNode->next = NULL;
}

double evaluate(double val, Polynomial *pL){
    double tong=0;
    Position temp = *pL;
    while(temp->next != NULL){
        tong += pow(val,temp->next->e)*temp->next->c;
//        printf("%.2lf %d\n", temp->next->c, temp->next->e);
        temp = temp->next;
    }
    return tong;
}

double coefficient(int e, Polynomial *pL){
	Position temp = *pL;
	while(temp->next != NULL){
		if(temp->next->e == e){
			return temp->next->c;
		}
		temp = temp->next;
	}
	return 0;
}

void deleted(double c, int e, Polynomial *pL){
	if((*pL)->next == NULL){
		printf(">>HY>GT");
		return;
	}
	Position temp = *pL;
	while(temp->next != NULL){
		if(e == temp->next->e){
			if(c == temp->next->c){
				Position tmp = temp->next;
				temp->next = temp->next->next;
				free(tmp);
			} else {
				temp->next->c -= c;
			}
			return;
		}
		temp = temp->next;
	}
	printf("sadas");
}

int main(){
    Polynomial L;
	makeNull(&L);
	insert(1,2,&L);
	insert(5,0,&L);
	insert(2,1,&L);
	insert(3,1,&L);
	deleted(5,5,&L);
	printList(&L);
    return 0;
}