#include "nn1.hpp"

nn1::nn1(std::vector<uint> topology, Scalar learningRate){
    this->topology = topology;
    this->learningRate = learningRate;

    for (uint i=0; i<topology.size(); i++){
        // Initialize neuron layers
        if (i == topology.size()-1)
            neuronLayers.push_back(new RowVector(topology[i]));
        else
            neuronLayers.push_back(new RowVector(topology[i]+1));

        // Initialize cache and delta vectors
        cacheLayers.push_back(new RowVector(neuronLayers.size()));
        deltas.push_back(new RowVector(neuronLayers.size()));

        // vector.back() gives the handle to recently added element
        // coeffRef gives the reference of value at that place
        // (using this as we're using pointers)
        if (i != topology.size() - 1){
            neuronLayers.back()->coeffRef(topology[i]) = 1.0;
            cacheLayers.back()->coeffRef(topology[i]) = 1.0;
        }

        // Initialize weights matrix
        if (i>0){
            if (i!=topology.size()-1){
                weights.push_back(new Matrix(topology[i-1] + 1, topology[i]+1));
                weights.back()->setRandom();
                weights.back()->col(topology[i]).setZero();
                weights.back()->coeffRef(topology[i-1],topology[i]) = 1.0;
            }
            else{
                weights.push_back(new Matrix(topology[i-1]+1,topology[i]));
                weights.back()->setRandom();
            }
        }

    }
}


nn1::~nn1(){}


void nn1::propagateForward(RowVector& input){
    // Set the input to input layer. Block returns a part of the given vector or matrix
    // Block takes 4 arguments: startRow, startCol, blockRows, blockCols
    neuronLayers.front()->block(0, 0, 1, neuronLayers.front()->size()-1) = input;

    // Propagate the data forward
    for (uint i=1; i<topology.size(); i++)
        (*neuronLayers[i]) = (*neuronLayers[i - 1]) * (*weights[i - 1]);

    // Apply the activation function to your network
    // unaryExpr applies the given function to all elements of CURRENT_LAYER
    for (uint i = 1; i < topology.size() - 1; i++)
        //neuronLayers[i]->block(0, 0, 1, topology[i]).unaryExpr(std::ptr_fun(activationFunction));
        neuronLayers[i]->block(0, 0, 1, topology[i]).unaryExpr(std::ptr_fun(activationFunction));
}


void nn1::propagateBackward(RowVector& output){
    calcErrors(output);
    updateWeights();
}



void nn1::calcErrors(RowVector& output){
    // Calculate the errors made by neurons of last layer
    (*deltas.back()) = output - (*neuronLayers.back());

    // Error calculation of hidden layers is different, we will begin by the last hidden
    // layer and we will continue till the first hidden layer
    for (uint i = topology.size() - 2; i>0; i--)
        (*deltas[i]) = (*deltas[i+1]) * (weights[i]->transpose());
}



void nn1::updateWeights(){
    // topology.size()-1 = weights.size()
    for (uint i=0; i<topology.size()-1; i++){
        // In this loop we are iterating over the different layers (from first hidden to output layer)
        // If this layer is the output layer, there is no bias neuron there, number of neurons specified = number of cols
        // If this layer is not the output layer, there is a bias neuron and number of neurons specified = number of cols - 1
        if (i != topology.size() - 2) {
            for (uint c = 0; c<weights[i]->cols() - 1; c++){
                for (uint r = 0; r<weights[i]->rows(); r++){
                    weights[i]->coeffRef(r,c) += learningRate * deltas[i+1]->coeffRef(c) * activationFunctionDerivative(cacheLayers[i+1]->coeffRef(c)) * neuronLayers[i]->coeffRef(r);
                }
            }
        }
        else{
            for (uint c = 0; c<weights[i]->cols(); c++){
                for (uint r = 0; r<weights[i]->rows(); r++){
                    weights[i]->coeffRef(r,c) += learningRate * deltas[i+1]->coeffRef(c) * activationFunctionDerivative(cacheLayers[i+1]->coeffRef(c)) * neuronLayers[i]->coeffRef(r);
                }
            }
        }
    }
}



void nn1::train(std::vector<RowVector*> input_data, std::vector<RowVector*> output_data){
    for (uint i = 0; i < input_data.size(); i++){
        std::cout << "Input to neural network is: " << *input_data[i] << std::endl;
        propagateForward(*input_data[i]);
        std::cout << "Expected output is: " << *output_data[i] << std::endl;
        std::cout << "Output produced is: " << *neuronLayers.back() << std::endl;
        propagateBackward(*output_data[i]);
        std::cout << "MSE: " << std::sqrt((*deltas.back()).dot((*deltas.back())) / deltas.back()->size()) << std::endl;
    }
}


Scalar nn1::activationFunction(Scalar x){
    return tanhf(x);
}

Scalar nn1::activationFunctionDerivative(Scalar x){
    return 1 - tanhf(x) * tanhf(x);
}

