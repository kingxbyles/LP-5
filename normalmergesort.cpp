#include <iostream>
#include <vector>
#include <chrono>
#include <cstdlib>

using namespace std;
using namespace std::chrono;

void merge(vector<int>& arr, int left, int mid, int right)
{
    vector<int> temp;

    int i = left;
    int j = mid + 1;

    while(i <= mid && j <= right)
    {
        if(arr[i] <= arr[j])
        {
            temp.push_back(arr[i]);
            i++;
        }
        else
        {
            temp.push_back(arr[j]);
            j++;
        }
    }

    while(i <= mid)
    {
        temp.push_back(arr[i]);
        i++;
    }

    while(j <= right)
    {
        temp.push_back(arr[j]);
        j++;
    }

    for(int k = left; k <= right; k++)
    {
        arr[k] = temp[k - left];
    }
}

void mergesort(vector<int>& arr, int left, int right)
{
    if(left >= right)
    {
        return;
    }

    int mid = (left + right) / 2;

    mergesort(arr, left, mid);
    mergesort(arr, mid + 1, right);

    merge(arr, left, mid, right);
}

int main()
{
    int n = 10000000;

    vector<int> arr(n);

    for(int i = 0; i < n; i++)
    {
        arr[i] = rand();
    }

    auto start = high_resolution_clock::now();

    mergesort(arr, 0, n - 1);

    auto end = high_resolution_clock::now();

    duration<double> elapsed = end - start;

    cout << "Execution time: "
         << elapsed.count()
         << " seconds" << endl;

    return 0;
}