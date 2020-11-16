#include <iostream>
// #include "maxPlanarSubset.h"
#include <stack>
#include <algorithm>
#include <fstream>

#define DEBUG 0
#define SHOW_STEP 1

inline int ij2index(int i,int j)
{
    if (i>j)
    {
        std::cerr<<"Error : i>j"<<std::endl;
        exit(1);
        return -1;
    }
    if (i==j)
    {
        return 0;
    }else{
        return (j*(j-1))/2+i+1;
    }
}

int main(int argc, char* argv[])
{
    std::cout<<"Main"<<std::endl;
    // int aa[] = {1,4,23,37,45,56,68};
    std::ifstream infile(argv[1]);
    
    if(SHOW_STEP)
        std::cout<<"Read file start"<<std::endl;

    int input_sizeN;
    infile>>input_sizeN;
    input_sizeN = input_sizeN/2;

    // declare arrays

    if(SHOW_STEP)
        std::cout<<"declare m_table"<<std::endl;
    
    int m_table[(input_sizeN-1)*(2*input_sizeN-1)+1];
    m_table[0] = 0;


    if(SHOW_STEP)
        std::cout<<"declare chords_k"<<std::endl;
    int chords_k[input_sizeN*2];

    // if(SHOW_STEP)
        // std::cout<<"declare dp_mem"<<std::endl;
    // int dp_mem[input_sizeN*2][input_sizeN*2][input_sizeN];
    
    for (int i=0;i<input_sizeN;++i)
    {
        int a,b;
        infile>>a>>b;
        chords_k[a] = b;
        chords_k[b] = a;
    }
    infile.close();

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

    
    // for (int i=0;i<2*input_sizeN;++i)
    //     for (int j=0;j<2*input_sizeN;++j)
    //     {
    //         m_table[i][j][0] = 0;

    //     }

    for (int d=1;d<input_sizeN*2;++d)
    {
        for (int i = 0;i < (input_sizeN*2)-d;++i)
        {
            int j = i + d;

            if (DEBUG>1)
                std::cout<<"Now processing N= "<<input_sizeN<<" i = "<<i<<" j = "<<j<<" k = "<<chords_k[j]<<std::endl;
            
            // check which case
            // chords_k[j];
            if (chords_k[j] == i)
            {
                // std::cout<<"asdasdasda"<<std::endl;
                // case kj=ij
                if (DEBUG>1)
                    std::cout<<"case kj=ij"<<std::endl;

                if (i==j-1)
                    m_table[ij2index(i,j)] = 0;
                else
                    m_table[ij2index(i,j)] = m_table[ij2index(i+1,j-1)] + 1;
                
                // add new chord record
                // format : 1(max mps)+1(add chord)+2(sub porblem1)+2(sub porblem2)
                // m_table[i][j][1] = i;

                // m_table[i][j][2] = i+1;
                // m_table[i][j][3] = j-1;
            }else if (chords_k[j] > j || chords_k[j] < i)
            {
                if (DEBUG>1)
                    std::cout<<"case k not in [i,j]"<<std::endl;
                // case k not in [i,j]
                m_table[ij2index(i,j)] = m_table[ij2index(i,j-1)];
                // m_table[i][j][0] = m_table[i][j-1][0]; 
                

                // add new chord record
                // format : 1(max mps)+1(add chord)+2(sub porblem1)+2(sub porblem2)
                // m_table[i][j][1] = -1;

                // m_table[i][j][2] = i;
                // m_table[i][j][3] = j-1;

                if (DEBUG>1)
                    std::cout<<"done"<<std::endl;
            }else{
                // case k in [i,j]
                if (DEBUG>1)
                    std::cout<<"case k in [i,j]"<<std::endl;
                int tmp = m_table[ij2index(i,chords_k[j]-1)] + 1 + m_table[ij2index(chords_k[j]+1,j-1)];
                // int tmp = m_table[i][chords_k[j]-1][0] + 1 + m_table[chords_k[j]+1][j-1][0];
                // if (m_table[i][j-1][0]<tmp)
                if (m_table[ij2index(i,j-1)]<tmp)
                {
                    
                    if (DEBUG>1)
                        std::cout<<"case A"<<std::endl;
                    
                    // std::cout<<"asdasdasda "<<tmp<<std::endl;
                    m_table[ij2index(i,j)] = tmp;
                    // m_table[i][j][0] = tmp;

                    // add new chord record
                    // format : 1(max mps)+1(add chord)+2(sub porblem1)+2(sub porblem2)
                    // m_table[i][j][1] = chords_k[j];

                    // m_table[i][j][2] = i;
                    // m_table[i][j][3] = chords_k[j]-1;

                    // m_table[i][j][4] = chords_k[j]+1;
                    // m_table[i][j][5] = j-1;

                }else
                {
                    if (DEBUG>1)
                        std::cout<<"case B"<<std::endl;
                    m_table[ij2index(i,j)] = m_table[ij2index(i,j-1)];
                    // m_table[i][j][0] = m_table[i][j-1][0];
                    // add new chord record
                    // format : 1(max mps)+1(add chord)+2(sub porblem1)+2(sub porblem2)
                    // m_table[i][j][1] = -1;
                    // m_table[i][j][2] = i;
                    // m_table[i][j][3] = j-1;
                }
            }
            
            
        }
    }

    if (SHOW_STEP)
        std::cout<<"Done computing "<<input_sizeN*2<<std::endl;

    if (DEBUG)
        for (int d=1;d<input_sizeN*2;++d)
        {
            for (int i = 0;i < (input_sizeN*2)-d;++i)
            {
                int j = i + d;
                std::cout<<ij2index(i,j)<<"  m("<<i<<","<<j<<") = "<<m_table[ij2index(i,j)]<<std::endl;
            }
        }

    if (DEBUG)
        for (int i =0;i<input_sizeN*2;++i)
            std::cout<<"chords_k["<<i<<"]"<<chords_k[i]<<std::endl;
    

    int result_chords[m_table[ij2index(0,2*input_sizeN-1)]];
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

        if (p.first==p.second)
        {
            if (DEBUG)
                std::cout<<"skip base case"<<std::endl;
            continue;
        }
        // backtrack cases
        if (chords_k[p.second] == p.first)
        {
            // case kj==ij
            if (DEBUG)
                std::cout<<"add chord ("<<p.first<<","<<p.second<<")"<<std::endl;

            result_chords[ind] = p.first;
            ++ind;

            std::pair<int,int> pp;
            pp.first = p.first+1;
            pp.second = p.second-1;
            if (DEBUG)
                std::cout<<"add subp ("<<pp.first<<","<<pp.second<<")"<<std::endl;
            tmp_stack.push(pp);

        }else if (chords_k[p.second] > p.second || chords_k[p.second] < p.first){
            // kj k not in [i,j]
            std::pair<int,int> pp;
            pp.first = p.first;
            pp.second = p.second-1;
            if (DEBUG)
                std::cout<<"add subp ("<<pp.first<<","<<pp.second<<")"<<std::endl;;
            tmp_stack.push(pp);

        }else{
            // kj k in [i,j]
            int tmp = m_table[ij2index(p.first,chords_k[p.second]-1)] + 1 + m_table[ij2index(chords_k[p.second]+1,p.second-1)];
            if (m_table[ij2index(p.first,p.second-1)]<tmp)
            {
                if (DEBUG)
                    std::cout<<"add chord ("<<chords_k[p.second]<<","<<p.second<<")"<<std::endl;

                result_chords[ind] = chords_k[p.second];
                ++ind;

                // m_table[ij2index(i,j)] = tmp;

                std::pair<int,int> pp;
                pp.first = p.first;
                pp.second = chords_k[p.second]-1;
                if (DEBUG)
                    std::cout<<"add subp1 ("<<pp.first<<","<<pp.second<<")";
                tmp_stack.push(pp);

                pp.first = chords_k[p.second]+1;
                pp.second = p.second-1;
                if (DEBUG)
                    std::cout<<" subp2 ("<<pp.first<<","<<pp.second<<")"<<std::endl;
                tmp_stack.push(pp);

            }else
            {
                // m_table[ij2index(p.first,p.second)] = m_table[ij2index(p.first,p.second-1)];
                std::pair<int,int> pp;
                pp.first = p.first;
                pp.second = p.second-1;
                if (DEBUG)
                    std::cout<<"add subp ("<<pp.first<<","<<pp.second<<")"<<std::endl;;
                tmp_stack.push(pp);
            }
        }
    }
    if (DEBUG)
        std::cout<<"end travel size = "<<ind<<std::endl;    
    std::sort(result_chords,result_chords+m_table[ij2index(0,2*input_sizeN-1)]);
    if (SHOW_STEP)
        std::cout<<"sort done ans = "<<m_table[ij2index(0,2*input_sizeN-1)]<<std::endl;    

    
    std::ofstream outfile(argv[2]);
    std::cout<<"asd"<<std::endl;

    // outfile<<m_table[ij2index(0,2*input_sizeN-1)]<<std::endl;

    for (int i=0;i<m_table[ij2index(0,2*input_sizeN-1)];++i)
    {
        outfile<<result_chords[i]<<" "<<chords_k[result_chords[i]]<<std::endl;
    }

    // m_table[0][2*input_sizeN-1][0];


    outfile.close();
}