//
//  mergesort.cpp
//  
//
//  Created by Jones, Andrew on 10/31/16.
//
//

#include <stdio.h>
#include <iostream>
using namespace std;

void mergesort(int* a, int start, int end) {
    if(end-start == 1) return;
    mergesort(a, start, end/2);
    mergesort(a, end/2 +1, end);
    merge(a, start, end/2, end);
    return;
}


int main()
{
    mergesort(a, 1, n)
    //declare start s, middle mid, end e
    void merge(int* a, int s, int mid, int e) {
        int* b = new int[e-s+1];
        int i = s;
    }
}
