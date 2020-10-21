#include <stdlib.h>
#include <stdio.h>

int gcd(int a, int b){
    if(a == b){ return a; } // Terminazione
    
    if(b > a){ // Scambio
        int tmp = a;
        a = b;
        b = tmp;
    }
    
    if(a%2 == 0){
        if(b%2 == 0)
            return 2*gcd(a/2, b/2);
        return gcd(a/2, b);
    }
    if(b%2 == 0)
        return gcd(a, b/2);
    return gcd((a-b)/2, b);
    
}

int main(int argc, char *argv[]){
    int x, y;
    
    do{
        printf("Inserisci due numeri interi positivi:\n");
        scanf("%d %d", &x, &y);
    } while(x < 0 || y < 0);
    
    printf("GCD: %d\n", gcd(x, y));
    
    return 0;
}
