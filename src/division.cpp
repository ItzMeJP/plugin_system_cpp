//
// Created by joaopedro on 28/06/21.
//

#include "division.h"

Division::Division() {};

Division::~Division() {};

void Division::run(){
    float count = *(input_arr_);
    for (int i = 1; i < size_; ++i) {
        count = count / *(input_arr_+i);
    }

    result_ = count;
}

bool Division::setArgs(float *_input_arr, int _size){
    input_arr_ = _input_arr;
    size_ = _size;
    return true;
}

float Division::operate(float* _input_arr, int _size)
{
    setArgs(_input_arr,_size);
    run();
    return result_;
}