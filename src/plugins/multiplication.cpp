/**\file
 * \brief
 * Multiplication Plugin definition
 * @version 01.07.2021
 * @author João Pedro Carvalho de Souza
 */

#include "plugins/multiplication.h"

Multiplication::Multiplication() {};

Multiplication::~Multiplication() {};

void Multiplication::run(){
    float mult = 1, tmp;
    for (int i = 0; i < size_; ++i) {
        tmp = *(input_arr_+i);
        mult = mult * tmp;
    }
    result_ = mult;
}

bool Multiplication::setArgs(float *_input_arr, int _size){
    input_arr_ = _input_arr;
    size_ = _size;
    return true;
}

float Multiplication::operate(float* _input_arr, int _size)
{
    setArgs(_input_arr,_size);
    run();
    return result_;
}