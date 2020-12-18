#include "equipArray.h"

struct equipArray_s{
    int *vettEq;
    int inUso;
};

equipArray_t equipArray_init(){
    int i;
    equipArray_t tmp = (equipArray_t) malloc(sizeof(struct equipArray_s));
    tmp->vettEq = (int*) malloc(EQUIP_SLOT * sizeof(int));
    for(i = 0; i < EQUIP_SLOT; ++i) tmp->vettEq[i] = -1;
    tmp->inUso = 0;
    return tmp;
}

void equipArray_free(equipArray_t equipArray){
    free(equipArray->vettEq);
    free(equipArray);
}

int equipArray_inUse(equipArray_t equipArray){
    return equipArray->inUso;
}

void equipArray_print(FILE *fp, equipArray_t equipArray, invArray_t invArray){
    int i;
    for(i = 0; i < EQUIP_SLOT; ++i){
        if(equipArray->vettEq[i] >= 0){
            inv_print(fp, invArray_getByIndex(invArray, equipArray->vettEq[i]));
            fprintf(fp, "\n");
        }
    }
}

stat_t equipArray_update(equipArray_t equipArray, invArray_t invArray){
    stat_t statNull = {0, 0, 0, 0, 0, 0}, tmp;
    int scelta, i, k;
    char nome[LEN];
    printf("0 (Aggiungi), 1 (Elimina): ");
    scanf("%d", &scelta);
    
    if(scelta == 0){
        if(equipArray->inUso < EQUIP_SLOT){
            printf("Nome oggetto da inserire: ");
            scanf("%s", nome);
            
            k = invArray_searchByName(invArray, nome);
            
            for(i = 0; i < EQUIP_SLOT; ++i){
                if(equipArray->vettEq[i] == -1){
                    equipArray->vettEq[i] = k;
                    break;
                }
            }
            ++(equipArray->inUso);
            
            return invArray_getByIndex(invArray, k)->stat;
        }
        else{
            printf("Limite massimo di oggetti raggiunto.\n");
        }
    }
    else if(scelta == 1){
        printf("Nome oggetto da eliminare: ");
        scanf("%s", nome);
        
        k = invArray_searchByName(invArray, nome);
        
        for(i = 0; i < EQUIP_SLOT; ++i){
            if(equipArray->vettEq[i] == k){
                equipArray->vettEq[i] = -1;
                break;
            }
        }
        
        --(equipArray->inUso);
        
        tmp = invArray_getByIndex(invArray, k)->stat;
        tmp.hp *= -1; tmp.mp *= -1; tmp.atk *= -1;
        tmp.def *= -1; tmp.mag *= -1; tmp.spr *= -1;
        return tmp;
    }
    else{
        exit(EXIT_FAILURE);
    }
    return statNull;
}

int equipArray_getEquipByIndex(equipArray_t equipArray, int index){
    return equipArray->vettEq[index];
}
