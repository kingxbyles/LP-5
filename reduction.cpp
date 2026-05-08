#include <iostream>
#include <omp.h>
#include <vector>
#include <climits>

using namespace std;

int main(){
    vector<int> arr = {10, 20, 5, 40, 15, 25, 30};

    int n = arr.size();

    int min_val = INT_MAX;
    int max_val = INT_MIN;

    int sum = 0;

    #pragma omp parallel for reduction(min:min_val) reduction(max:max_val) reduction(+:sum)
    for(int i = 0; i<n; i++){
        if(arr[i]<min_val){
            min_val = arr[i];
        }
        if(arr[i]>max_val){
            max_val = arr[i];
        }
        sum += arr[i];
    }

    double avg = (double)sum / n;

    cout<<"Minimum: "<<min_val<<endl;
    cout<<"Maximum: "<<max_val<<endl;
    cout<<"Sum: "<<sum<<endl;
    cout<<"Average: "<<avg<<endl;


    return 0;
}