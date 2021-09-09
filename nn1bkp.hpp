#include <iostream>
#include <vector>
#include <eigen3/Eigen/Eigen>


class nn1{

    private:
        int nDimX1, nDimX2, nDimX3, nDimX4;
        int nDimY1, nDimY2, nDimY3, nDimY4;
        bool bDebug;

        std::vector<float> vX1;
        std::vector<std::vector<float> > vX2;
        std::vector<std::vector<std::vector<float> > > vX3;
        std::vector<std::vector<std::vector<std::vector<float> > > > vX4;

        std::vector<float> vY1;
        std::vector<std::vector<float> > vY2;
        std::vector<std::vector<std::vector<float> > > vY3;
        std::vector<std::vector<std::vector<std::vector<float> > > > vY4;



    public:


        nn1(int dimX1i = 0, int dimX2i = 0, int dimX3i = 0, int dimX4i = 0,
            int dimY1i = 0, int dimY2i = 0, int dimY3i = 0, int dimY4i = 0, bool bDebugi = false):
            nDimX1(dimX1i), nDimX2(dimX2i), nDimX3(dimX3i), nDimX4(dimX4i),
            nDimY1(dimY1i), nDimY2(dimY2i), nDimY3(dimY3i), nDimY4(dimY4i), bDebug(bDebugi) {
            
            // if (nDimX2==0)      vX1 = std::vector<float>(nDimX1, 0.0);
            // else if (nDimX3==0) vX2 = std::vector<std::vector<float> >(nDimX1, std::vector<float>(nDimX2, 0.0));
            // else if (nDimX4==0) vX3 = std::vector<std::vector<std::vector<float> > >(nDimX1, std::vector<std::vector<float> >(nDimX2, std::vector<float>(nDimX3, 0.0)));
            // else                vX4 = std::vector<std::vector<std::vector<std::vector<float> > > >(nDimX1, std::vector<std::vector<std::vector<float> > >(nDimX2, std::vector<std::vector<float> >(nDimX3, std::vector<float>(nDimX4, 0.0))));

            vX1 = std::vector<float>(nDimX1, 0.0);
            vX2 = std::vector<std::vector<float> >(nDimX1, std::vector<float>(nDimX2, 0.0));
            vX3 = std::vector<std::vector<std::vector<float> > >(nDimX1, std::vector<std::vector<float> >(nDimX2, std::vector<float>(nDimX3, 0.0)));
            vX4 = std::vector<std::vector<std::vector<std::vector<float> > > >(nDimX1, std::vector<std::vector<std::vector<float> > >(nDimX2, std::vector<std::vector<float> >(nDimX3, std::vector<float>(nDimX4, 0.0))));

            vY1 = std::vector<float>(nDimY1, 0.0);
            vY2 = std::vector<std::vector<float> >(nDimY1, std::vector<float>(nDimY2, 0.0));
            vY3 = std::vector<std::vector<std::vector<float> > >(nDimY1, std::vector<std::vector<float> >(nDimY2, std::vector<float>(nDimY3, 0.0)));
            vY4 = std::vector<std::vector<std::vector<std::vector<float> > > >(nDimY1, std::vector<std::vector<std::vector<float> > >(nDimY2, std::vector<std::vector<float> >(nDimY3, std::vector<float>(nDimY4, 0.0))));

        }

        ~nn1(){}





};