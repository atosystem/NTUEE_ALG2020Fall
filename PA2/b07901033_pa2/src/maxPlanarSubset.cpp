#include "maxPlanarSubset.h"
#include <iostream>
#include <algorithm>
#include <stack>
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

    if(SHOW_STEP)
        std::cout<<"Read file start"<<std::endl;
    
    f>>input_sizeN;
    input_sizeN = input_sizeN/2;

    // declare arrays

    if(SHOW_STEP)
        std::cout<<"declare m_table"<<std::endl;
    int m_table[input_sizeN*2][input_sizeN*2][1+1+2+2];
    // format : 1(max mps)+1(add chord)+2(sub porblem1)+2(sub porblem2)

    if(SHOW_STEP)
        std::cout<<"declare chords_k"<<std::endl;
    int chords_k[input_sizeN*2];

    // if(SHOW_STEP)
        // std::cout<<"declare dp_mem"<<std::endl;
    // int dp_mem[input_sizeN*2][input_sizeN*2][input_sizeN];
    
    for (int i=0;i<input_sizeN;++i)
    {
        int a,b;
        f>>a>>b;
        chords_k[a] = b;
        chords_k[b] = a;
    }

    if(SHOW_STEP)
        std::cout<<"Done file parsing"<<std::endl;

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
    // init m_table
    // for (int i=0;i<2*input_sizeN;++i)
    //     m_table[i][i][0] = 0;

    // format : 1(max mps)+1(add chord)+2(sub porblem1)+2(sub porblem2)
    for (int i=0;i<2*input_sizeN;++i)
        for (int j=0;j<2*input_sizeN;++j)
        {
            m_table[i][j][0] = 0;

            m_table[i][j][1] = -1;

            m_table[i][j][2] = -1;
            m_table[i][j][3] = -1;

            m_table[i][j][4] = -1;
            m_table[i][j][5] = -1;

        }

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
                m_table[i][j][0] = m_table[i+1][j-1][0]+1;
                
                // add new chord record
                // format : 1(max mps)+1(add chord)+2(sub porblem1)+2(sub porblem2)
                m_table[i][j][1] = i;

                m_table[i][j][2] = i+1;
                m_table[i][j][3] = j-1;
            }else if (chords_k[j] > j || chords_k[j] < i)
            {
                if (DEBUG)
                    std::cout<<"case k not in [i,j]"<<std::endl;
                // case k not in [i,j]
                m_table[i][j][0] = m_table[i][j-1][0]; 
                

                // add new chord record
                // format : 1(max mps)+1(add chord)+2(sub porblem1)+2(sub porblem2)
                m_table[i][j][1] = -1;

                m_table[i][j][2] = i;
                m_table[i][j][3] = j-1;

                if (DEBUG)
                    std::cout<<"done"<<std::endl;
            }else{
                // case k in [i,j]
                if (DEBUG)
                    std::cout<<"case k in [i,j]"<<std::endl;

                int tmp = m_table[i][chords_k[j]-1][0] + 1 + m_table[chords_k[j]+1][j-1][0];
                if (m_table[i][j-1][0]<tmp)
                {
                    m_table[i][j][0] = tmp;

                    // add new chord record
                    // format : 1(max mps)+1(add chord)+2(sub porblem1)+2(sub porblem2)
                    m_table[i][j][1] = chords_k[j];

                    m_table[i][j][2] = i;
                    m_table[i][j][3] = chords_k[j]-1;

                    m_table[i][j][4] = chords_k[j]+1;
                    m_table[i][j][5] = j-1;

                }else
                {
                    m_table[i][j][0] = m_table[i][j-1][0];
                    // add new chord record
                    // format : 1(max mps)+1(add chord)+2(sub porblem1)+2(sub porblem2)
                    m_table[i][j][1] = -1;
                    m_table[i][j][2] = i;
                    m_table[i][j][3] = j-1;
                }
            }
            
            
        }
    }

    if (SHOW_STEP)
        std::cout<<"Done computing"<<std::endl;


    

    int result_chords[m_table[0][2*input_sizeN-1][0]];
    int ind = 0;

    

    std::stack< std::pair<int,int> > tmp_stack;

    std::pair<int,int> p ;
    p.first = 0;
    p.second = 2*input_sizeN-1;

    
    
    tmp_stack.push(p);
    while(!tmp_stack.empty())
    {
        
        // std::pair<int,int> p = tmp_stack.top();
        p = tmp_stack.top();
        tmp_stack.pop();
        if (DEBUG)
            std::cout<<"check "<<p.first<<" "<<p.second<<std::endl;

        // add new chord to array
        if (m_table[p.first][p.second][1]!=-1)
        {
            if (DEBUG)
                std::cout<<"add chord "<<m_table[p.first][p.second][1]<<std::endl;
            result_chords[ind] = m_table[p.first][p.second][1];
            ++ind;
        }

        if (m_table[p.first][p.second][2]!=-1)
        {
            std::pair<int,int> pp;
            pp.first = m_table[p.first][p.second][2];
            pp.second = m_table[p.first][p.second][3];
            if (DEBUG)
                std::cout<<"add subp ("<<pp.first<<","<<pp.second<<")";
            tmp_stack.push(pp);
            if (m_table[p.first][p.second][4]!=-1)
            {
                pp.first = m_table[p.first][p.second][4];
                pp.second = m_table[p.first][p.second][5];
                if (DEBUG)
                    std::cout<<" ("<<pp.first<<","<<pp.second<<")";
                tmp_stack.push(pp);
            }
            if (DEBUG)
                std::cout<<std::endl;
        }
        
    }
    if (DEBUG)
        std::cout<<"end travel size = "<<ind<<std::endl;    
    std::sort(result_chords,result_chords+m_table[0][2*input_sizeN-1][0]);
    if (SHOW_STEP)
        std::cout<<"sort done"<<std::endl;    

    out_f<<m_table[0][2*input_sizeN-1][0]<<std::endl;

    for (int i=0;i<m_table[0][2*input_sizeN-1][0];++i)
    {
        out_f<<result_chords[i]<<" "<<chords_k[result_chords[i]]<<std::endl;
    }

    return m_table[0][2*input_sizeN-1][0];

}