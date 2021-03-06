#include <iostream>
// #include "maxPlanarSubset.h"
#include <stack>
#include <algorithm>
#include <fstream>

#include <vector>

#define DEBUG 1
#define SHOW_STEP 1

unsigned long long int input_sizeN;
// #define ij2index (i,j) ( ((i)==(j)) ? 0 : ((j)*((j)-1))/2+(i)+1)

static inline unsigned long long int ij2index(unsigned long long int i,unsigned long long int j)
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
        if ((j*(j-1))/2+i+1>input_sizeN*(2*input_sizeN-1))
        {
            std::cerr<<"Error : m_table out of bound (i,j)="<<i<<" "<<j<<std::endl;
			std::cerr<<"m_index = "<<(j*(j-1))/2+i+1<<"  max = "<<input_sizeN*(2*input_sizeN-1)<<std::endl;
			exit(1);
        }else
        {
            return (j*(j-1))/2+i+1;

        }
    }
}



int main(int argc, char* argv[])
{
    std::cout<<"Main"<<std::endl;
    // int aa[] = {1,4,23,37,45,56,68};
    std::ifstream infile(argv[1]);
    
    if(SHOW_STEP)
        std::cout<<"Read file start"<<std::endl;

    
    infile>>input_sizeN;
    input_sizeN = input_sizeN/2;

    // declare arrays

    if(SHOW_STEP)
        std::cout<<"declare m_table"<<std::endl;
    
    std::vector<int> m_table;
    m_table.reserve(input_sizeN*(2*input_sizeN-1)+1);

    for (unsigned long long int i=0;i<input_sizeN*(2*input_sizeN-1)+1;++i)
        m_table[i]=-1;

    // int m_table[input_sizeN*(2*input_sizeN-1)+1];
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
    {
        std::cout<<"chord_k list"<<std::endl;
        for (int i=0;i<input_sizeN*2;++i)
            std::cout<<chords_k[i]<<std::endl;

        std::cout<<std::endl;
    }
    
    if (DEBUG)
        std::cout<<"Compute start"<<std::endl;

    // if (SHOW_STEP)
    //     std::cout<<"Done computing "<<input_sizeN*2<<std::endl;

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
    

    // int result_chords[m_table[ij2index(0,2*input_sizeN-1)]];
    int ind = 0;

    std::cout<<"Start Computing"<<std::endl;

    std::stack< std::pair<int,int> > tmp_stack;
    std::vector<int> result_chords;
    result_chords.reserve(input_sizeN);

    std::pair<int,int> p ;
    p.first = 0;
    p.second = 2*input_sizeN-1;

    tmp_stack.push(p);
    
    while(!tmp_stack.empty())
    {
        
        // std::pair<int,int> p = tmp_stack.top();
        p = tmp_stack.top();
        // tmp_stack.pop();
        if (DEBUG)
            std::cout<<"check "<<p.first<<" "<<p.second<<std::endl;

        if (m_table[ij2index(p.first,p.second)] != -1)
        {
            if (DEBUG)
                std::cout<<"case calculated before"<<std::endl;
            
            tmp_stack.pop();
            continue;
        }

        
        // backtrack cases
        if (chords_k[p.second] == p.first)
        {
            // case kj==ij
            if (DEBUG)
                std::cout<<"Case kj==ij"<<std::endl;
            if (m_table[ij2index(p.first+1,p.second-1)]!=-1)
            {
                m_table[ij2index(p.first,p.second)] = m_table[ij2index(p.first+1,p.second-1)] + 1;
                tmp_stack.pop();
                continue;
            }
            if (DEBUG)
                std::cout<<"add chord ("<<p.first<<","<<p.second<<")"<<std::endl;

            // result_chords[ind] = p.first;
            result_chords.push_back(p.first);
            ++ind;

            std::pair<int,int> pp;
            pp.first = p.first+1;
            pp.second = p.second-1;
            if (DEBUG)
                std::cout<<"add subp ("<<pp.first<<","<<pp.second<<")"<<std::endl;
            
            
            tmp_stack.push(pp);

        }else if (chords_k[p.second] > p.second || chords_k[p.second] < p.first){
            // kj k not in [i,j]
            if (DEBUG)
                std::cout<<"Case kj k not in [i,j]"<<std::endl;
            if (m_table[ij2index(p.first,p.second-1)]!=-1)
            {
                m_table[ij2index(p.first,p.second)] = m_table[ij2index(p.first,p.second-1)];
                tmp_stack.pop();
                continue;
            }
            std::pair<int,int> pp;
            pp.first = p.first;
            pp.second = p.second-1;
            if (DEBUG)
                std::cout<<"add subp ("<<pp.first<<","<<pp.second<<")"<<std::endl;
            
            
            tmp_stack.push(pp);

        }else{
            // kj k in [i,j]
            if (DEBUG)
                std::cout<<"Case kj k in [i,j]"<<std::endl;
            if (m_table[ij2index(p.first,chords_k[p.second]-1)]==-1)
            {
                std::pair<int,int> pp;
                pp.first = p.first;
                pp.second = chords_k[p.second]-1;
                if (DEBUG)
                    std::cout<<"add subp1 ("<<pp.first<<","<<pp.second<<")";
                tmp_stack.push(pp);
            }
            if (m_table[ij2index(chords_k[p.second]+1,p.second-1)]==-1)
            {
                std::pair<int,int> pp;
                pp.first = chords_k[p.second]+1;
                pp.second = p.second-1;
                if (DEBUG)
                    std::cout<<" subp2 ("<<pp.first<<","<<pp.second<<")"<<std::endl;
                tmp_stack.push(pp);
            }
            if (m_table[ij2index(p.first,p.second-1)]==-1)
            {
                std::pair<int,int> pp;
                pp.first = p.first;
                pp.second = p.second-1;
                if (DEBUG)
                    std::cout<<" subp3 ("<<pp.first<<","<<pp.second<<")"<<std::endl;

                tmp_stack.push(pp);
            }
            if (m_table[ij2index(p.first,p.second-1)]!=-1 && m_table[ij2index(p.first,chords_k[p.second]-1)]!=-1 && m_table[ij2index(chords_k[p.second]+1,p.second-1)]!=-1)
            {
                
                // m_table[ij2index(p.first,p.second)] = m_table[ij2index(p.first,p.second-1)];
                int tmp = m_table[ij2index(p.first,chords_k[p.second]-1)] + 1 + m_table[ij2index(chords_k[p.second]+1,p.second-1)];
                if (m_table[ij2index(p.first,p.second-1)]<tmp)
                {
                    if (DEBUG)
                        std::cout<<"add chord ("<<chords_k[p.second]<<","<<p.second<<")"<<std::endl;

                    result_chords.push_back(chords_k[p.second]);
                    ++ind;
                    m_table[ij2index(p.first,p.second)] = tmp;
                }else
                {
                    // m_table[ij2index(p.first,p.second)] = m_table[ij2index(p.first,p.second-1)];
                    m_table[ij2index(p.first,p.second)] = m_table[ij2index(p.first,p.second-1)];
                }
                tmp_stack.pop();
            }
            
        }
    }

    if (DEBUG)
        std::cout<<"end travel size = "<<ind<<std::endl;    
    
    std::sort(result_chords.begin(),result_chords.end());

    if (SHOW_STEP)
        std::cout<<"sort done ans = "<<result_chords.size()<<std::endl;    

    
    std::ofstream outfile(argv[2]);


    outfile<<result_chords.size()<<std::endl;

    for (int i=0;i<result_chords.size();++i)
    {
        outfile<<result_chords[i]<<" "<<chords_k[result_chords[i]]<<std::endl;
    }

    // m_table[0][2*input_sizeN-1][0];


    outfile.close();
}
