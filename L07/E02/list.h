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
    char codice[6];
    char nome[MAXL];
    char cognome[MAXL];
    Date data;
    char via[MAXL];
    char citta[MAXL];
    int cap;
}Info;

typedef struct node{
    Info info;
    struct node *next;
}Item;

// Returna la testa della lista
void addRow(Item **p, Info inf){
    Item *tmp = (Item*) malloc(sizeof(Item));
    tmp->info = inf;

    if(*p == NULL){ // Lista vuota
        tmp->next = NULL;
        *p = tmp;
        return;
    }

    Item *iter = *p;
    Item *prev = NULL;

    while(iter->next != NULL){
        if(cmp_date(inf.data, iter->info.data) == 1){ // Inserisco
            if(prev == NULL){ // Primo elemento: cambio testa della lista
                tmp->next = *p;
                *p = tmp;
                return;
            }
            else{
                prev->next = tmp;
                tmp->next = iter;
                return;
            }
        }
        // Proseguo
        prev = iter;
        iter = iter->next;
    }
    iter->next = tmp;
    tmp->next = NULL;
    return;
}

void addMult(Item **p, FILE *fp){
    Info tmp;
    while(fscanf(fp, "%s %s %s %d/%d/%d %s %s %d\n", tmp.codice, tmp.nome, tmp.cognome, &tmp.data.gg, &tmp.data.mm, &tmp.data.aaaa, tmp.via, tmp.citta, &tmp.cap) > 0)
        addRow(p, tmp);
}

int searchByCode(Item *p, char *code){
    if(p == NULL) return 0; // Lista vuota
    do{
        if(strcmp(p->info.codice, code) == 0){ // Se trova il codice stampa se no proseguo
            printf("%s %s %s %d/%d/%d %s %s %d\n", p->info.codice, p->info.nome, p->info.cognome, p->info.data.gg, p->info.data.mm, p->info.data.aaaa, p->info.via, p->info.citta, p->info.cap);
            return 1; // Successo
        }
        p = p->next;  // Avanza nella lista
    } while(p->next != NULL);
    return 0;
}

Item* deleteByCode(Item **p, char *code){
    if(p == NULL) return NULL; // Lista vuota

    Item *prev = NULL, *iter = *p;
    while(iter != NULL){
        if(strcmp(iter->info.codice, code) == 0){
            if(prev == NULL){ // Cambia la testa della lista
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
    }
    return NULL;
}

Item* deleteByDates(Item **p, Date d1, Date d2){
    if(*p == NULL) return NULL;

    if(cmp_date(d1, d2) == -1){
        Date dtmp = d1;
        d1 = d2;
        d2 = dtmp;
    }

    int flag = 0;
    Item *lastIn = NULL, *lastOut = NULL, *prev = NULL;
    Item *iter = *p;

    while(iter != NULL){
        if(cmp_date(iter->info.data, d1) <= 0){ // data <= d1
            if(prev == NULL){
                flag = 1;
                lastIn = iter; // Diventa firstOut
            }
            else{
                lastIn = prev;
            }
            break;
        }
        prev = iter;
        iter = iter->next;
    }
    if(lastIn == NULL) return NULL;

    while(iter != NULL){
        if(cmp_date(iter->info.data, d2) < 0){ // data < d2
            if(prev == NULL) return NULL;
            break;
        }
        prev = iter;
        iter = iter->next;
    }
    lastOut = prev;

    if(flag){
        *p = lastOut->next;
        prev = lastIn;
        lastOut->next = NULL;
    }
    else{
        prev = lastIn->next;
        lastIn->next = lastOut->next;
        lastOut->next = NULL;
    }
    return prev;
}

void print(Item *p, FILE *fp){
    if(p == NULL) return; // Lista vuota
    while(p != NULL){
        fprintf(fp, "%s %s %s %d/%d/%d %s %s %d\n", p->info.codice, p->info.nome, p->info.cognome, p->info.data.gg, p->info.data.mm, p->info.data.aaaa, p->info.via, p->info.citta, p->info.cap);
        p = p->next;                // Avanza nella lista
    }
}

#endif /*LIST_H */
