#include <iostream>

#include "nn1.cpp"
#include "aux.hpp"



typedef std::vector<RowVector*> data;
int main(){
    nn1 n({2,3,1});
    data in_dat, out_dat;
    genData("test");
    ReadCSV("test-in", in_dat);
    ReadCSV("test-out", out_dat);

    
    for (int i=0; i<in_dat.size(); i++){
        std::cout << *in_dat[i] << " ";
    }
    std::cout << std::endl << std::endl << std::endl;


    for (int i=0; i<out_dat.size(); i++){
        std::cout << *out_dat[i] << " ";
    }
    std::cout << std::endl << std::endl;
    

    n.train(in_dat, out_dat);

    return 0;
}
