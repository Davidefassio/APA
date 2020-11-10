#ifndef LIST_H
#define LIST_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAXL 50

typedef struct{
    int gg;
    int mm;
    int aaaa;
}Date;

/*
 * -1 se d1 < d2
 *  0 se d1 = d2
 *  1 se d1 > d2
 */
int cmp_date(Date d1, Date d2){
    if(d1.aaaa < d2.aaaa) return -1;
    if(d1.aaaa > d2.aaaa) return  1;
    if(d1.mm < d2.mm) return -1;
    if(d1.mm > d2.mm) return  1;
    if(d1.gg < d2.gg) return -1;
    if(d1.gg > d2.gg) return  1;
    return 0;
}

typedef struct{
    char codice[MAXL];
    char nome[MAXL];
    char cognome[MAXL];
    Date data;
    char via[MAXL];
    char citta[MAXL];
    int cap;
}Info;

typedef struct list{
    Info info;
    struct list *next;
}Item;

// Returna la testa della lista
Item* addRow(Item *p, Info inf){
    Item *tmp = (Item*) malloc(sizeof(Item));
    tmp->info = inf;

    if(p == NULL){ // Lista vuota
        tmp->next = NULL;
        return tmp;
    }

    int pos = 0;
    Item *head = p;
    Item *prev;

    while(p->next != NULL){
        if(cmp_date(inf.data, p->info.data) == -1){ // Inserisco
            if(pos == 0){ // Primo elemento: cambio testa della lista
                tmp->next = p;
                return tmp;
            }
            else{
                prev->next = tmp;
                tmp->next = p;
                return head;
            }
        }
        // Proseguo
        prev = p;
        p = p->next;
        ++pos;
    }
    p->next = tmp;
    tmp->next = NULL;
    return head;
}

Item* addMult(Item *p, FILE *fp){
    Info tmp;
    while(fscanf(fp, "%s %s %s %d/%d/%d %s %s %d\n", tmp.codice, tmp.nome, tmp.cognome, tmp.data.gg, tmp.data.mm, tmp.data.aaaa, tmp.via, tmp.citta, tmp.cap) != 0)
        p = addRow(p, tmp);
    return p;
}

int searchByCode(Item *p, char *code){
    if(p == NULL) return 0; // Lista vuota
    do{
        if(strcmp(p->info.codice, code) == 0){ // Se trova il codice stampa se no proseguo
            printf("%s %s %s %d/%d/%d %s %s %d\n", p->info.codice, p->info.nome, p->info.cognome, p->info.data.gg, p->info.data.mm, p->info.data.aaaa, p->info.via, p->info.citta, p->info.cap);
            return 1; // Successo
        }
        p = p->next;                // Avanza nella lista
    } while(p->next != NULL);
    return 0;
}

Item* deleteByCode(Item **p, char *code){
    if(p == NULL) return NULL; // Lista vuota
    int pos = 0;
    Item *prev, *iter = *p;
    do{
        if(strcmp(iter->info.codice, code) == 0){
            if(pos == 0){ // Cambia la testa della lista
                *p = iter->next;
                return iter;
            }
            else{ // Elimino l'elemento dalla lista e lo returno
                prev->next = iter->next;
                return iter;
            }
        }
        prev = iter;
        iter = iter->next; // Avanza nella lista
        ++pos;           
    } while(iter->next != NULL);
    return NULL;
}

void deleteByDates(Item *p, Date d1, Date d2){

}

void print(Item *p, FILE *fp){
    if(p == NULL) return; // Lista vuota
    do{
        fprintf(fp, "%s %s %s %d/%d/%d %s %s %d\n", p->info.codice, p->info.nome, p->info.cognome, p->info.data.gg, p->info.data.mm, p->info.data.aaaa, p->info.via, p->info.citta, p->info.cap);
        p = p->next;                // Avanza nella lista
    } while(p->next != NULL);
}

#endif /*LIST_H */
