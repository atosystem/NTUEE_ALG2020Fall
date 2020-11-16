#include "maxPlanarSubset.h"
#include <iostream>
#include <algorithm>
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

int Mps::compute(std::ifstream& f)
{

    if(SHOW_STEP)
        std::cout<<"Read file start"<<std::endl;
    
    f>>input_sizeN;
    input_sizeN = input_sizeN/2;

    // declare arrays

    if(SHOW_STEP)
        std::cout<<"declare m_table"<<std::endl;
    int m_table[input_sizeN*2][input_sizeN*2];

    if(SHOW_STEP)
        std::cout<<"declare chords_k"<<std::endl;
    int chords_k[input_sizeN*2];
    
    for (int i=0;i<input_sizeN;++i)
    {
        int a,b;
        f>>a>>b;
        chords_k[a] = b;
        chords_k[b] = a;
    }

    if(SHOW_STEP)
        std::cout<<"Done file parseing"<<std::endl;

    // f>>x;
    // if (x!=0)
    // {
    //     std::cerr<<"Input file format error [does not ends with 0]"<<std::endl;
    //     exit(1);
    // }



    if (DEBUG)
        std::cout<<"Compute start"<<std::endl;
    

    if (DEBUG)
    {
        std::cout<<"chord_k list"<<std::endl;
        for (int i=0;i<input_sizeN*2;++i)
            std::cout<<chords_k[i]<<std::endl;

        std::cout<<std::endl;
    }
    
    
    // for (int i=0;i<input_sizeN;++i)
    // {
    //     chords_a[i] = chords_k[i];
    //     chords_b[i] = chords_j[i];
    // }
    for (int i=0;i<2*input_sizeN;++i)
        m_table[i][i] = 0;

    for (int d=1;d<input_sizeN*2;++d)
    {
        for (int i = 0;i < (input_sizeN*2)-d;++i)
        {
            int j = i + d;

            if (DEBUG)
                std::cout<<"Now processing N= "<<input_sizeN<<" i = "<<i<<" j = "<<j<<" k = "<<chords_k[j]<<std::endl;
            
            // check which case
            // chords_k[j];
            if (chords_k[j] == i)
            {
                // case kj=ij
                if (DEBUG)
                    std::cout<<"case kj=ij"<<std::endl;
                m_table[i][j] = m_table[i+1][j-1]+1;
            }else if (chords_k[j] > j || chords_k[j] < i)
            {
                if (DEBUG)
                    std::cout<<"case k not in [i,j]"<<std::endl;
                // case k not in [i,j]
                m_table[i][j] = m_table[i][j-1]; 
                if (DEBUG)
                    std::cout<<"done"<<std::endl;
            }else{
                // case k in [i,j]
                if (DEBUG)
                    std::cout<<"case k in [i,j]"<<std::endl;

                int tmp = m_table[i][chords_k[j]-1] + 1 + m_table[chords_k[j]+1][j-1];
                if (m_table[i][j-1]<tmp)
                {
                    m_table[i][j] = tmp;
                }else
                {
                    m_table[i][j] = m_table[i][j-1];
                }
            }
            
            
        }
    }
    return m_table[0][2*input_sizeN-1];

}