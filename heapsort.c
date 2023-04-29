#include <stdio.h>

void swap(int *a, int *b){
    int tmp;
    tmp = *a;
    *a = *b;
    *b = tmp;
}

void heapify(int A[], int i, int N){
	int L = 2*i;
	int R = 2*i + 1;
	int max = i;
	if(L <= N && A[L] > A[i])
		max = L;
	if(R <= N && A[R] > A[max])
		max = R;
	if(max != i){
		swap(&A[i], &A[max]);
		heapify(A, max, N);
	}
}

void buildHeap(int A[], int N){
	for(int i = N/2; i >= 1; i--)
		heapify(A, i, N);
}

void heapSort(int A[], int N){
	//index from 1 to N
	buildHeap(A, N);
	for(int i = N; i > 1; i--){
		swap(&A[1], &A[i]);
		heapify(A, 1, i-1);
	}
}

int main(){
    int n, i;
    int A[100000];

    scanf("%d", &n);
    for(i = 1; i <= n; i++)
        scanf("%d", &A[i]);
    heapSort(A, n);
    for(i = 1; i <= n; i++)
        printf("%d ", A[i]);
    return 0;
}