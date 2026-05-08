#include <iostream>
#include <omp.h>
#include <vector>

using namespace std;

void parallelbubblesort(vector<int>& arr){

    int n = arr.size();

    for(int i=0; i<n; i++){

        #pragma omp parallel for
        for(int j=0; j<n-1; j+=2){
            if(arr[j]>arr[j+1]){
                swap(arr[j], arr[j+1]);
            }
        }

        #pragma omp parallel for
        for(int j=1; j<n-1; j+=2){
            if(arr[j]>arr[j+1]){
                swap(arr[j], arr[j+1]);
            }
        }
    }
    
}


void bubblesort(vector<int>& brr){
    int n = brr.size();

    for(int i=0; i<n; i++){
        for (int j=0; j<n-1; j++){
            if(brr[j] > brr[j+1]){
                swap(brr[j], brr[j+1]);
            }
        }
    }
}


int main(){
    // vector<int> arr = {5,2,1,9,3,8};
    // vector<int> brr = {5,2,1,9,3,8};

    int m = 100000;

    vector<int> arr1(m);
    vector<int> brr1(m);


    for(int i=0; i<m; i++){
    arr1[i] = rand();
    brr1[i] = rand();
        }

    double start1 = omp_get_wtime();

    parallelbubblesort(arr1);

    double end1 = omp_get_wtime();

    double start2 = omp_get_wtime();

    bubblesort(brr1);
    
    double end2 = omp_get_wtime();

    // cout<<"Sorted array parallel sort: ";

    // for(int x: arr){
    //     cout<<" "<<x<<" ";
    // }

    // cout<<"\nSorted array normal sort: ";

    // for(int x: brr){
    //     cout<<" "<<x<<" ";
    // }


    // cout<<endl;

    cout<<"Execution time for parallel: "<<end1-start1<<" seconds"<<endl;

    cout<<"Execution time for sequential: "<<end2-start2<<" seconds"<<endl;
}