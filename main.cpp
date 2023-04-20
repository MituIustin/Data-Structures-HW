#include <iostream>
#include <cstdlib>
#include <vector>

void heapify(std::vector <int> & arr, int nod, int n)
{
    int st = (nod+1)*2-1;
    int dr = (nod+1)*2;

    if(st<n){
        if(arr[st]>arr[nod] && arr[st]>=arr[dr]){
            std::swap(arr[st],arr[nod]);
            heapify(arr,st,n);
        }
    }

    if(dr<n){
        if(arr[dr]>arr[nod] && arr[st]<arr[dr]){
            std::swap(arr[dr],arr[nod]);
            heapify(arr,dr,n);
        }
    }
}

void build_max(std::vector <int> & arr, int n)
{
    for(int i=n-1; i>=0; i--){
        heapify(arr,i,n);
    }
}

void heap_sort(std::vector <int> & arr, int n)
{
    build_max(arr,n);
    n--;
    for( int i=n; i>=0; i--){
        std::swap(arr[0],arr[n]);
        n--;
        heapify(arr, 0,n);
    }
}

int main()
{
    std::vector <int> arr;
	srand((unsigned) time(NULL));

	int n = 30;
    for(int i=0; i<n; i++){
        int random = rand()%100;
        arr.push_back(random);
        std::cout<<random<<" ";
    }
    std::cout<<"\n";

    heap_sort(arr,n);

    for(int i=0; i<n; i++){
        std::cout<<arr[i]<<" ";
    }


}
