/**\file
 * \brief
 * Math operations interface template declaration
 * @version 01.07.2021
 * @author João Pedro Carvalho de Souza
 */

#ifndef BASE_OPERATIONS_H
#define BASE_OPERATIONS_H

#include <iostream>
#include "factory.h"

class BaseOperations {
public:
    BaseOperations() {};
    ~BaseOperations() {};

    virtual float operate(float* _input_arr, int _size) = 0;
};

#endif //BASE_OPERATIONS_H
