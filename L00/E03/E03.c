#include <stdio.h>
#include <stdlib.h>

#define MAXN 30

void ruota(int v[MAXN], int N, int P, int dir){
    int tmp[MAXN], i;
    
    for(i = 0; i < N; ++i){
        tmp[i] = v[(i+(-dir*P)+N)%N];
    }
    for(i = 0; i < N; ++i){
        v[i] = tmp[i];
    }
    return;
}

int main(int argc, char* argv[]){
    int vec[MAXN], i, n, p, dir;
    
    printf("Inserire numero di elementi (n <= 30): ");
    scanf("%d", &n);
    if(n > MAXN){ return -1; }
    
    for(i = 0; i < n; ++i){
        printf("%d) ", i+1);
        scanf("%d", &vec[i]);
    }
    
    while(1){
        printf("Inserisci numero di posti da ruotare (p < n, se p = 0 termina): ");
        scanf("%d", &p);
        if(p == 0){ break; }
        if(p >= n){ return -1; }
        
        printf("Inserisci direzione (1 : destra, -1 : sinistra): ");
        scanf("%d", &dir);
        
        ruota(vec, n, p, dir);
        
        for(i = 0; i < n; ++i){
            printf("%d ", vec[i]);
        }
        printf("\n\n");
    }
    return 0;
}
