#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define B 5

typedef char KeyType[50];
typedef int ValueType;

typedef struct {
    KeyType key;
    ValueType value;
} ElementType;

typedef struct CellTag {
    ElementType element;
    struct CellTag *next;
} Cell;

typedef Cell *Position;

typedef struct {
    Position buckets[B];
} Map;

int h(KeyType k) {
    int sum = 0;
    for (int i = 0; k[i] != '\0'; i++)
        sum += k[i];
    return sum % B;
}

void makeNull(Map *pM) {
    //makes the map be empty.
}

void printMap(Map *pM) {
    //prints map.
}

//OPEN HASH TABLE FOR MAP
void insert(KeyType k, ValueType v, Map *pM){
	int i = h(k);
	Position p = pM->buckets[i];
	while(p != NULL){
		if(strcmp(k, p->element.key) == 0){
			return;
		}
		p = p->next;
	}
	Position tmp = pM->buckets[i];
	pM->buckets[i] = (Cell*)malloc(sizeof(Cell));
	strcpy(pM->buckets[i]->element.key, k);
	pM->buckets[i]->element.value = v;
	pM->buckets[i]->next = tmp;
} 

ValueType retrieve(KeyType k, Map *pM){
	int i = h(k);
	Position p = pM->buckets[i];
	while(p != NULL){
		if(strcmp(p->element.key, k) == 0){
			return p->element.value;
		}
		p = p->next;
	}
	return -4419;
}

int member(KeyType k, Map *pM){
	int i = h(k);
	Position p = pM->buckets[i];
	while(p != NULL){
		if(strcmp(k, p->element.key) == 0){
			return 1;
		}
		p = p->next;
	}
	return 0;
}

void delete(KeyType k, Map *pM){
	int  i = h(k);
	if(!member(k, pM)) return;
	if(pM->buckets[i] == NULL) return;
	if(strcmp(pM->buckets[i]->element.key, k) == 0){
		Position tmp = pM->buckets[i];
		pM->buckets[i] = tmp->next;
		free(tmp);
		return;
	}
	Position p = pM->buckets[i];
	while(p->next != NULL){
		if(strcmp(p->next->element.key, k) == 0){
			Position tmp = p->next;
			p->next = tmp->next;
			free(tmp);
			return;
		}
		p = p->next;
	}
}

void update(KeyType k, ValueType new_v, Map *pM){
	int i = h(k);
	Position p =pM->buckets[i];
	while(p != NULL){
		if(strcmp(k, p->element.key) == 0){
			p->element.value = new_v;
		}
		p = p->next;
	}
}


//CLOSE HASH TABLE FOR MAP
void insert(KeyType k, ValueType v, Map *pM){
	int i = locate(k ,pM);
	if(strcmp(k, pM->buckets[i].key) == 0){
		return;
	}
	i = locate1(k, pM);
	if(strcmp(pM->buckets[i].key, EMPTY) == 0 || strcmp(pM->buckets[i].key, DELETED) == 0){
		strcpy(pM->buckets[i].key, k);
		pM->buckets[i].value = v;
		return;
	}
}

void delete(KeyType k, Map *pM) {
    int i = locate(k, pM);
    if(strcmp(pM->buckets[i].key, k) == 0){
        strcpy(pM->buckets[i].key, DELETED);
        return;
    }
}

ValueType retrieve(KeyType k, Map *pM){
	int md = h(k);
	int i = 0;
	for(i=0; i<B; i++){
		int p = (i+md)%B;
		if(strcmp(pM->buckets[p].key, EMPTY) == 0){
			return -4376;
		}
		if(strcmp(pM->buckets[p].key, k) == 0)
			return pM->buckets[p].value;
		}
	 return -4376;
}

void update(KeyType k, ValueType v, Map *pM){
	int md = h(k);
	int i = 0;
	for(i=0; i<B; i++){
		int  p = (i+md)%B;
		if(strcmp(pM->buckets[p].key, k) == 0){
			pM->buckets[p].value = v;
			return;
		}else{
			if(strcmp(pM->buckets[p].key, EMPTY) == 0 || strcmp(pM->buckets[p].key, DELETED) == 0){
			strcpy(pM->buckets[p].key, k);
			pM->buckets[p].value = v;
			return;	
			}	
		}
	}
}
///
void locate(KeyType k,Map *pM){
	int md = h(k);
	int i = 0; 
	while(i<B &&
	strcmp(pM->buckets[(i+md)%B], k) != 0 &&
	strcmp(pM->buckets[(i+md)%B], EMPTY) != 0){
		i++;
	}
	return (i+md)%B;
}


void locate1(KeyType k, Map *pM){
	int md = h(k);
	int i = 0; 
	while(i<B &&
	strcmp(pM->buckets[(i+md)%B], k) != 0 &&
	strcmp(pM->buckets[(i+md)%B], EMPTY) != 0 &&
	strcmp(pM->buckets[(i+md)%B], DELETED) != 0){
		i++;
	}
	return (i+md)%B;
}

void update(KeyType k, ValueType v, Map *pM){
	int md = h(k);
	int i = 0;
	for(i=0; i<B; i++){
		int  p = (i+md)%B;
		if(strcmp(pM->buckets[p].key, k) == 0){
			pM->buckets[p].value = v;
			return;
		}else{
			if(strcmp(pM->buckets[p].key, EMPTY) == 0 || strcmp(pM->buckets[p].key, DELETED) == 0){
			strcpy(pM->buckets[p].key, k);
			pM->buckets[p].value = v;
			return;	
			}	
		}
	}
}
void insert(KeyType k, ValueType v, Map *pM){
	int i = locate(k ,pM);
	if(strcmp(k, pM->buckets[i]) == 0){
		return;
	}
	i = locate1(k, pM);
	if(strcmp(pM->buckets[i]->element.key, EMPTY) == 0 || strcmp(pM->buckets[i]->element.key, DELETED) == 0){
		strcpy(pM->buckets[i]->element.key, k);
		pM->buckets[i]->element.value = v;
		return;
	}
}


//
int locate(ElementType x, HashTable *pT) {
    int md = h(x);
    int i = 0;
    while(i<B &&
    strcmp(pT->buckets[(i+md)%B], x) != 0 &&
    strcmp(pT->buckets[(i+md)%B], EMPTY) != 0){
        i++;
    }
    return (i + md)%B;
}


ValueType retrieve(KeyType k, Map *pM){
	int md = h(k);
	int i = 0;
	while(i<B &&
	strcmp(pM->buckets[(i+md)%B], k) == 0){
		return pM->buckets[i]->element.value;
		
	}
	return -4376;
}

ValueType retrieve(KeyType k, Map *pM) {
    int i = locate(k, pM);
    return strcmp(pT->buckets[i].key, k) == 0;
}















