#ifndef __maxPlanarSubset__
#define __maxPlanarSubset__

#include <vector>
#include <fstream>

#define DEBUG 0
#define SHOW_STEP 1
class Mps
{
    public:
        Mps();
        bool parseFile(std::ifstream& f);
        int compute(std::ifstream& f);

        int aux_BS(int* arr,int v,int s);
    private:

        // int isChord(int k,int j);
        int input_sizeN;
        // std::vector<int> m_table;
        // std::vector<int> chords_k;
        // std::vector<int> chords_j;
        


    
};

#endif