//
// Created by joaopedro on 28/06/21.
//

#include "sum.h"

Sum::Sum() {};

Sum::~Sum() {};

void Sum::run(){
    float count = 0;
    for (int i = 0; i < size_; ++i) {
        count = count + *(input_arr_+i);
    }

    result_ = count;
}

bool Sum::setArgs(float *_input_arr, int _size){
    input_arr_ = _input_arr;
    size_ = _size;
    return true;
}

float Sum::operate(float* _input_arr, int _size)
{
    setArgs(_input_arr,_size);
    run();
    return result_;
}