#include <stdlib.h>
#include <stdio.h>

int majority(int *v, int l){
    if(l == 1){ return v[0]; }
 
    int mid = l/2, m1, m2, i, cnt;
    m1 = majority(v, mid);
    m2 = majority(v+mid, l-mid);
 
    if(m1 == -1 && m2 == -1){ return -1; }
    if(m1 != -1 && m2 != -1 && m1 != m2){ return -1; }
    if(m1 == m2){ return m1; }
 
    if(m1 != -1){
        cnt = 0;
        for(i = 0; i < l; ++i){
            if(v[i] == m1){ ++cnt; }
        }
        if(cnt > l/2.0){ return m1; }
    }
    else{
        cnt = 0;
        for(i = 0; i < l; ++i){
            if(v[i] == m2){ ++cnt; }
        }
        if(cnt > l/2.0){ return m2; }
    }
    return -1;
}


int main(int argc, char *argv[]){
    int arr[7] = {3, 3, 9, 4, 3, 5, 3};
    printf("Elemento maggioritario: %d\n", majority(arr, 7));
 
    return 0;
}
