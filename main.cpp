#include <iostream>

#include "nn1.cpp"
#include "aux.hpp"



typedef std::vector<RowVector*> data;
int main(){
    nn1 n({2,3,1}, 0.005, true);
    data in_dat, out_dat;
    genData("test");
    ReadCSV("test-in", in_dat);
    ReadCSV("test-out", out_dat);
    
    n.train(in_dat, out_dat);

    return 0;
}
