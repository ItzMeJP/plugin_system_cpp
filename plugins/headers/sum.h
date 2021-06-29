//
// Created by joaopedro on 28/06/21.
//
#ifndef PLUGIN_TEST_V1_SUM_H
#define PLUGIN_TEST_V1_SUM_H
class Sum {
public:
    Sum();
    ~Sum();

    float operate(float* _input_arr, int _size);

protected:
    float* input_arr_;
    int size_;
    bool setArgs(float* _input_arr, int _size);
    void run();
    float result_ = -9.999;
};
#endif //PLUGIN_TEST_V1_SUM_H
