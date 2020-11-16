#include "maxPlanarSubset.h"
#include <iostream>
// #include <algorithm>
// #include <stack>
Mps::Mps()
{
    // chords_k.reserve(N);
    // chords_j.reserve(N);

}

bool Mps::parseFile(std::ifstream& f)
{
    /*
    int N;
    f>>N;
    N = N/2;
    chords_k.reserve(N);
    chords_j.reserve(N);
    int x;
    for (int i=0;i<N;++i)
    {
        f>>x;
        chords_k[i] = x;
        f>>x;
        chords_j[i] = x;
    }
    f>>x;
    if (x!=0)
    {
        std::cerr<<"input file format error [does not ends with 0]"<<std::endl;
        exit(1);
    }
    */
    return 0;
}

int Mps::aux_BS(int* arr,int v,int s)
{
    // (&arr);

    int i,j;
    i = 0;
    j = s-1;
    while(i<=j)
    {
        int middle = (i+j)/2;
        if (v == arr[middle])
            return i;
        else if(v > arr[middle])
            i = middle+1;   
        else
            j = middle-1;

    }
    return -1;
}

int Mps::compute(std::ifstream& f , std::ofstream& out_f)
{
    


}