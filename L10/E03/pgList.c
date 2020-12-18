#include "pgList.h"

typedef struct node{
    pg_t pg;
    struct node* next;
}Node;

struct pgList_s{
    Node* head;
};

static Node* newNode(pg_t pg){
    Node *tmp = (Node*) malloc(sizeof(Node));
    tmp->pg = pg;
    return tmp;
}

pgList_t pgList_init(){
    pgList_t tmp = (pgList_t) malloc(sizeof(struct pgList_s));
    tmp->head = NULL;
    return tmp;
}

static void pgList_freeR(Node *p){
    if(p == NULL) return;
    pgList_freeR(p->next);
    free(p);
}

void pgList_free(pgList_t pgList){
    pgList_freeR(pgList->head);
    free(pgList);
}

void pgList_read(FILE *fp, pgList_t pgList){
    pg_t tmp;
    while(pg_read(fp, &tmp) != 0)
        pgList_insert(pgList, tmp);
}

void pgList_print(FILE *fp, pgList_t pgList, invArray_t invArray){
    Node *p = pgList->head;
    while(p != NULL){
        pg_print(fp, &p->pg, invArray);
        p = p->next;
    }
}

void pgList_insert(pgList_t pgList, pg_t pg){
    Node *p = newNode(pg);
    p->next = pgList->head;
    pgList->head = p;
}

void pgList_remove(pgList_t pgList, char* cod){
    Node *p = pgList->head, *prev = NULL;
    while(p != NULL){
        if(strcmp(p->pg.cod, cod) == 0){
            if(prev == NULL)
                pgList->head = p->next;
            else
                prev->next = p->next;
        }
        prev = p;
        p = p->next;
    }
    printf("Personaggio non trovato.\n");
}

pg_t *pgList_searchByCode(pgList_t pgList, char* cod){
    Node *p = pgList->head;
    while(p != NULL){
        if(strcmp(p->pg.cod, cod) == 0)
            return &p->pg;
        p = p->next;
    }
    return NULL;
}
