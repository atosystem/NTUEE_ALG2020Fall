// **************************************************************************
//  File       [sort_tool.cpp]
//  Author     [Yu-Hao Ho]
//  Synopsis   [The implementation of the SortTool Class]
//  Modify     [2020/9/15 Mu-Ting Wu]
// **************************************************************************

#include "sort_tool.h"
#include<iostream>

// Constructor
SortTool::SortTool() {}

// Insertsion sort method
void SortTool::InsertionSort(vector<int>& data) {
    // Function : Insertion sort
    // TODO : Please complete insertion sort code here
    for (int i = 1; i < data.size(); ++i)
    {
        int current_item = data[i];
        int x;
        for (x = i-1; x >=0; --x)
        {
            if ( data[x] <= data[i] )
            {
                break;
            }
        }

        std::vector<int>::iterator rm_it= data.begin() + i;
        
        data.erase(rm_it);
        
        std::vector<int>::iterator ins_it= data.begin() + x+1;

        data.insert(ins_it,current_item);
    }
}

// Quick sort method
void SortTool::QuickSort(vector<int>& data){
    QuickSortSubVector(data, 0, data.size() - 1);
}
// Sort subvector (Quick sort)
void SortTool::QuickSortSubVector(vector<int>& data, int low, int high) {
    // Function : Quick sort subvector
    // TODO : Please complete QuickSortSubVector code here
    // Hint : recursively call itself
    //        Partition function is needed
    if (low < high)
    {
        int q = Partition(data,low,high);
        QuickSortSubVector(data,low,q);
        QuickSortSubVector(data,q+1,high);
    }
}

int SortTool::Partition(vector<int>& data, int low, int high) {
    // Function : Partition the vector 
    // TODO : Please complete the function
    // Hint : Textbook page 171
    // cout<<"partition ("<<low<<","<<high<<")"<<endl;
    int a = data[low];
    int b = data[(low+high)/2];
    int c = data[high];
    int x  = data[low];
    if (a>=b && b>=c)
        x = b;
    else if (c>=b && b>=a)
        x = a;
    else if (b>=a && a>=c)
        x = a;
    else if (c>=a && a>=b)
        x = a;
    else if (a>=c && c>=b)
        x = c;
    else if (b>=c && c>=a)
        x = c;
    
    int i = low-1;
    int j = high+1;
    while(1)
    {
        do
        {
            --j;
        } while (data[j]>x);
        do
        {
            ++i;
        } while (data[i]<x);
        if (i<j) {
            int tmp = data[i];
            data[i] = data[j];
            data[j] = tmp;
        } else {
            return j;
        }
        
    }
}

// Merge sort method
void SortTool::MergeSort(vector<int>& data){
    MergeSortSubVector(data, 0, data.size() - 1);
}

// Sort subvector (Merge sort)
void SortTool::MergeSortSubVector(vector<int>& data, int low, int high) {
    // Function : Merge sort subvector
    // TODO : Please complete MergeSortSubVector code here
    // Hint : recursively call itself
    //        Merge function is needed
    if (low >= high)
    {
        // sorted
    }else{
        int m1 = (low+high)/2;
        // int m2 = (low+high)/2 + 1;
        MergeSortSubVector(data,low,m1);
        MergeSortSubVector(data,m1+1,high);
        Merge(data,low,m1,m1+1,high);
    }
}

// Merge
void SortTool::Merge(vector<int>& data, int low, int middle1, int middle2, int high) {
    // Function : Merge two sorted subvector
    // TODO : Please complete the function
    int i = low;
    int j = middle2;
    
    // vector<int> tmp_arr;

    int tmp_arr[high-low+1];
    int tmp_arr_i = 0;


    while(i<=middle1 && j<=high)
    {
        if (data[i] <= data[j])
        {
            tmp_arr[tmp_arr_i] = data[i];
            ++tmp_arr_i;
            ++i;
        }else{
            tmp_arr[tmp_arr_i] = data[j];
            ++tmp_arr_i;
            ++j;
        }
    }
    while(i<=middle1)
    {
        tmp_arr[tmp_arr_i] = data[i];
        ++tmp_arr_i;
        ++i;
    }
    while(j<=high)
    {
        tmp_arr[tmp_arr_i] = data[j];
        ++tmp_arr_i;
        ++j;
    }

    for (int x=0;x<(high-low+1);++x)
        data[low+x] = tmp_arr[x];

}

// Heap sort method
void SortTool::HeapSort(vector<int>& data) {
    // Build Max-Heap
    BuildMaxHeap(data);
    // for(int x =0;x<data.size();++x)
    //     cout<<data[x]<<" ";
    // cout<<endl;
    // 1. Swap data[0] which is max value and data[i] so that the max value will be in correct location
    // 2. Do max-heapify for data[0]
    for (int i = data.size(); i >= 2; i--) {
        swap(data[1-1],data[i-1]);
        // cout<<"After swap=================="<<i-1<<endl;
        // for(int x =0;x<data.size();++x)
        //     cout<<data[x]<<" ";
        // cout<<endl;

        heapSize--;
        MaxHeapify(data,1);
        // cout<<"After Heapify=================="<<endl;
        // for(int x =0;x<data.size();++x)
        //     cout<<data[x]<<" ";
        // cout<<endl;
    }
}

//Max heapify
void SortTool::MaxHeapify(vector<int>& data, int root) {
    // Function : Make tree with given root be a max-heap if both right and left sub-tree are max-heap
    // TODO : Please complete max-heapify code here
    // root = root+1;
    int left_index = (root)*2;
    int right_index = (root)*2+1;

    int exchange_index = -1;

    if (left_index <= heapSize && data[left_index-1]> data[root-1] )
        exchange_index = left_index;
    else
        exchange_index = root;

    if (right_index <= heapSize && data[right_index-1]> data[exchange_index-1] )
        exchange_index = right_index;
    
    if (exchange_index != root)
    {
        swap(data[exchange_index-1],data[root-1]);
        MaxHeapify(data,exchange_index);
    }
}

//Build max heap
void SortTool::BuildMaxHeap(vector<int>& data) {
    heapSize = data.size(); // initialize heap size
    // Function : Make input data become a max-heap
    // TODO : Please complete BuildMaxHeap code here
    for (int i=data.size()/2;i>=1;--i)
        MaxHeapify(data,i);
}
