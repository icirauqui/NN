#include <eigen3/Eigen/Eigen>
#include <iostream>
#include <vector>


typedef float Scalar;
typedef Eigen::MatrixXf Matrix;
typedef Eigen::RowVectorXf RowVector;
typedef Eigen::VectorXf ColVector;


class nn1{

    public:

        // Constructor
        nn1(std::vector<uint> topology, Scalar learningRate = Scalar(0.005));
        
        // Destructor
        ~nn1();

        // Function for forward propagation of data
        void propagateForward(RowVector& input);

        // Function for backward propagation of errors made by neurons
        void propagateBackward(RowVector& output);

        // Function to calculate errors made by neurons in each layer
        void calcErrors(RowVector& output);

        // Function to update the weights of connections
        void updateWeights();

        // Function to train the neural network give an array of datapoints
        void train(std::vector<RowVector*> data);

        /*
            Storage objects for working of neural network
            Use pointers when using std::vector<Class> as std::vector<Class> calls destructor of
            Class as soon as it is pushed back! When we use pointers it can't do that, besides it
            also makes our neural network class less heavy!! It would be nice if you can use smart
            pointers instead of usual ones like this
        */






        std::vector<RowVector*> neuronLayers;   // Stores the different layers of our network
        std::vector<RowVector*> cacheLayers;    // Stores the unactivated values of layers
        std::vector<RowVector*> deltas;         // Stores the error contribution of each neuron
        std::vector<Matrix*> weights;           // The weight of each connection.
        Scalar learningRate;        
        std::vector<uint> topology;             // Describes how many neurons we have in each layer

};