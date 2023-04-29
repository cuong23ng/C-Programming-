#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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

int binarySearch(int a[], int L, int R, int Y){
    if(L > R) return 0;
    if(L == R)
        if(a[L] == Y) return 1;
        else return 0;
    int m = (L+R)/2;
    if(a[m] == Y) return 1;
    if(a[m] > Y) return binarySearch(a, L, m-1, Y);
    return binarySearch(a, m+1, R, Y);
}

int main()
{
    int n, m;
    int a[100000];
    int mark[100000];
    time_t t;
    //for(int i = 1; i <= 1000000; i++)mark[i] = 0;
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= n; i++){
        scanf("%d", &a[i]);
        mark[a[i]] = 1;
    }
    heapSort(a, n);
    int cnt = 0;
    for (int i = 1; i <= n; i++)
    {
        if(a[i] != m - a[i]){
            if(binarySearch(a, 1, n, m-a[i])) cnt++;
        }
        else {
            int k = 1;
            //printf("%d\n", i);
            while(a[i+1] == a[i]){
                i++;
                k++;
            }
            if(k > 1)cnt = cnt + k*2;
            //printf("%d\n", i);
        }
    }
    printf("%d\n", cnt/2);
    return 0;
}