#include <iostream>
#include <omp.h>
#include <vector>

using namespace std;

void merge(vector<int>& arr, int left, int mid, int right){

    vector<int> temp;

    int i = left;
    int j = mid+1;

    while(i<=mid && j<=right){
        if(arr[i]<arr[j]){
            temp.push_back(arr[i]);
            i++;
        }
        else{
            temp.push_back(arr[j]);
            j++;
        }
    }

    while(i<=mid){
        temp.push_back(arr[i]);
        i++;
    }

    while(j<=right){
        temp.push_back(arr[j]);
        j++;
    }


    for(int k = left; k<=right; k++){
        arr[k] = temp[k - left];
    }
}

void parallelmergesort(vector<int>& arr, int left, int right){
    if(left>=right)
    {
        return;
    }

    int mid  = (left+right)/2;

    //optimized parallel
    #pragma omp task shared(arr)
    parallelmergesort(arr, left, mid);

    #pragma omp task shared(arr)
    parallelmergesort(arr, mid + 1, right);

    #pragma omp taskwait

    ////sequential
    // parallelmergesort(arr,left,mid);
    // parallelmergesort(arr, mid+1, right);

    merge(arr, left, mid, right);
}

int main(){
    // vector<int> arr1 = {5,2,3,4,8,9,1};

    int m = 10000000;

    vector<int> arr1(m);


    for(int i=0; i<m; i++){
    arr1[i] = rand();
        }

    double start = omp_get_wtime();

    parallelmergesort(arr1, 0, arr1.size()-1);

    double end = omp_get_wtime();

    // cout<<"sorted array: ";

    // for(int x: arr1){
    //     cout<<" "<<x<<" ";
    // }

    cout<<endl;

    cout<<"Execution time: "<<end-start<<" seconds"<<endl;

    return 0;
}