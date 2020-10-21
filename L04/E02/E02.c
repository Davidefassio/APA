#include <stdlib.h>
#include <stdio.h>

/* FUNZIONA
int majority(int *v, int l){
    if(l == 1){ return v[0]; }

    int mid = l/2, m1, m2, i, cnt;
    m1 = majority(v, mid);
    m2 = majority(v+mid, l-mid);
    printf("l:%d m1:%d m2:%d\n", l, m1, m2);

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
}*/

/* FUNZIONA MA NON RICORSIVO
int majority(int *v, int l){
    int i, x = v[0], c = 1;

    for(i = 1; i < l; ++i){
        if(v[i] == x){ ++c; }
        else{ --c; }

        if(c < 0){
            x = v[i];
            c = 1;
        }

        printf("%d\n", x);
    }
    c = 0;
    for(i = 0; i < l; ++i){
        if(v[i] == x){ ++c; }
    }
    if(c > l/2){ return x; }
    return -1;
}
*/


/*int main(int argc, char *argv[]){
    int arr[8] = {0, 1, 0, 2, 3, 4, 0, 5};
    printf("\n\n%d\n", majority(arr, 8));

    return 0;
}*/

/*
// CPP program for implementation of QuickSelect
#include <bits/stdc++.h>
using namespace std;

// Standard partition process of QuickSort().
// It considers the last element as pivot
// and moves all smaller element to left of
// it and greater elements to right
int partition(int arr[], int l, int r)
{
    int x = arr[r], i = l;
    for (int j = l; j <= r - 1; j++) {
        if (arr[j] <= x) {
            swap(arr[i], arr[j]);
            i++;
        }
    }
    swap(arr[i], arr[r]);
    return i;
}

// This function returns k'th smallest
// element in arr[l..r] using QuickSort
// based method.  ASSUMPTION: ALL ELEMENTS
// IN ARR[] ARE DISTINCT
int kthSmallest(int arr[], int l, int r, int k)
{
    // If k is smaller than number of
    // elements in array
    if (k > 0 && k <= r - l + 1) {

        // Partition the array around last
        // element and get position of pivot
        // element in sorted array
        int index = partition(arr, l, r);

        // If position is same as k
        if (index - l == k - 1)
            return arr[index];

        // If position is more, recur
        // for left subarray
        if (index - l > k - 1)
            return kthSmallest(arr, l, index - 1, k);

        // Else recur for right subarray
        return kthSmallest(arr, index + 1, r,
                            k - index + l - 1);
    }

    // If k is more than number of
    // elements in array
    return INT_MAX;
}

// Driver program to test above methods
int main()
{
    int arr[] = { 10, 4, 5, 8, 6, 11, 26 };
    int n = sizeof(arr) / sizeof(arr[0]);
    int k = 3;
    cout << "K-th smallest element is "
        << kthSmallest(arr, 0, n - 1, k);
    return 0;
}

*/
