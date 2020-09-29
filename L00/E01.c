#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]){
    const int n = 15;
    int vec[n] = {1, 3, 4, 0, 1, 0, 9, 4, 2, 0, 1, 2, 3};
    int max = 0, curr = 0;
    int i, j;
    
    for(i = 0; i < n; ++i){
        if(vec[i] != 0){ ++curr; }
        else{
            if(curr > max){
                max = curr;
            }
            curr = 0;
        }
    }
    if(curr > max){
        max = curr;
    }
    
    for(i = 0; i < n; ++i){
        if(vec[i] != 0){
            for(j = i; j < i + max; ++j){
                if(vec[j] == 0){
                    i = j;
                    break;
                }
            }
            if(j == i + max){
                printf("[ ");
                for(j = i; j < i + max; ++j){
                    printf("%d ", vec[j]);
                }
                printf("]\n");
            }
        }
    }
    
    return 0;
}
