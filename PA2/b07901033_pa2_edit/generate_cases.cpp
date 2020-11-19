// random_shuffle example
#include <iostream>     // std::cout
#include <algorithm>    // std::random_shuffle
#include <vector>       // std::vector
#include <ctime>        // std::time
#include <cstdlib>      // std::rand, std::srand
#include <sstream>
#include <fstream>

// random generator function:
int myrandom (unsigned long long int i) { return std::rand()%i;}

int main(int argc, char *argv[]) {
    if (argc!=3)
    {
        std::cerr<<"[Usage] ./generate_cases <N> <outputfile>"<<std::endl;
        exit(1);
    }
    std::istringstream ss(argv[1]);
    unsigned long long int x;
    if (!(ss >> x)) {
        std::cerr << "Invalid number: " << argv[1] << '\n';
    } else if (!ss.eof()) {
        std::cerr << "Trailing characters after number: " << argv[1] << '\n';
    }

    std::cout<<"N="<<x<<std::endl;
    std::srand ( unsigned ( std::time(0) ) );
    std::vector<int> myvector;

    // set some values:
    myvector.reserve(2*x);
    for (unsigned long long int i=0; i<2*x; ++i) myvector[i] = i; // 1 2 3 4 5 6 7 8 9

    // using built-in random generator:
    std::random_shuffle ( myvector.begin(), myvector.end() );

    // using myrandom:
    std::random_shuffle ( myvector.begin(), myvector.end(), myrandom);
    std::ofstream outfile(argv[2]);
    unsigned long long int a = 0;
    outfile<<2*x<<std::endl;
    while(a<2*x)
    {
        outfile<<myvector[a]<<" "<<myvector[a+1]<<std::endl;
        a +=2;
    }
    outfile<<0<<std::endl;
    outfile.close();
    std::cout<<argv[2]<<" generated"<<std::endl;

  // print out content:
//   std::cout << "myvector contains:";
//   for (std::vector<int>::iterator it=myvector.begin(); it!=myvector.end(); ++it)
//     std::cout << ' ' << *it;


  return 0;
}