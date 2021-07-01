//
// Created by joaopedro on 28/06/21.
//

#ifndef PLUGIN_TEST_V1_BASE_OPERATIONS_H
#define PLUGIN_TEST_V1_BASE_OPERATIONS_H

#include <filesystem>
#include <iostream>
#include "plugin_handling/factory.h"

class BaseOperations {
public:
    BaseOperations() {};
    ~BaseOperations() {};

    virtual float operate(float* _input_arr, int _size) = 0;
};

// DLL export funcs


#endif //PLUGIN_TEST_V1_BASE_OPERATIONS_H
