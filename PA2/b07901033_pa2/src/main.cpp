#include <iostream>
#include "maxPlanarSubset.h"

int main(int argc, char* argv[])
{
    std::cout<<"Main"<<std::endl;
    Mps d;
    // int aa[] = {1,4,23,37,45,56,68};
    std::ifstream infile(argv[1]);
    std::cout<<d.compute(infile)<<std::endl;
    infile.close();
}