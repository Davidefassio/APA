#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void stampaCodifica(void *p, int size, int bigEndian){
    unsigned char *c;
    int i, j;
    
    if(size > 8){ size = 10; } // Long double utilizzano 10 Byte
    
    if(bigEndian){  // Stampo in ordine crescente di Byte
        c = (unsigned char*) p;
        printf("Sign: ");
        for(i = 0; i < size; ++i, ++c){
            for(j = 7; j > -1; --j){
                if(i*8 + 7 - j == 1){ printf("\nExp: "); }
                else if(size ==  4 && i*8 + 7 - j ==  9){ printf("\nMantissa: "); }
                else if(size ==  8 && i*8 + 7 - j == 12){ printf("\nMantissa: "); }
                else if(size == 10 && i*8 + 7 - j == 16){ printf("\nMantissa: "); }
                printf("%d", (*c >> j)&1);
            }
        }
    }
    else{  // Stampo in ordine decrescente di Byte
        c = ((unsigned char*) p) + size - 1;
        printf("Sign: ");
        for(i = size - 1; i > -1; --i, --c){
            for(j = 7; j > -1; --j){
                if((size - 1 - i)*8 + 7 - j == 1){ printf("\nExp: "); }
                else if(size ==  4 && (size - 1 - i)*8 + 7 - j ==  9){ printf("\nMantissa: "); }
                else if(size ==  8 && (size - 1 - i)*8 + 7 - j == 12){ printf("\nMantissa: "); }
                else if(size == 10 && (size - 1 - i)*8 + 7 - j == 16){ printf("\nMantissa: "); }
                printf("%d", (*c >> j)&1);
            }
        }
    }
    printf("\n\n");
}

int main(int argc, char *argv[]){
    int bigEndian;
    
    int b = 1;
    if(*((unsigned char*) &b) & 0x01){
        bigEndian = 0;
        printf("L'architettura e' little endian\n\n");
    }
    else{
        bigEndian = 1;
        printf("L'architettura e' big endian\n\n");
    }
    
    float af;
    double ad;
    long double ald;
    
    printf("Sizeof float: %lu bit = %lu Byte\n", 8*sizeof(float), sizeof(float));
    printf("Sizeof double: %lu bit = %lu Byte\n", 8*sizeof(double), sizeof(double));
    printf("Sizeof long double: %d bit = %d Byte\n\n", 80, 10);
    
    printf("Inserire numero float: ");
    scanf("%f", &af);
    stampaCodifica((void*) &af, sizeof(float), bigEndian);
    
    printf("Inserire numero double: ");
    scanf("%lg", &ad);
    stampaCodifica((void*) &ad, sizeof(double), bigEndian);
    
    printf("Inserire numero long double: ");
    scanf("%Lf", &ald);
    stampaCodifica((void*) &ald, sizeof(long double), bigEndian);
    
    return 0;
}
