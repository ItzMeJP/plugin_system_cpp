/**\file
 * \brief
 * Plugin interface template declaration
 * @version 01.07.2021
 * @author João Pedro Carvalho de Souza
 */

#ifndef FOO_INTERFACE_H
#define FOO_INTERFACE_H

/** Include the factory interface class that provides plugin's management metadata and instantiate exported classes **/
#include "factory.h"

class FooInterface {
public:
    FooInterface() {};
    ~FooInterface() {};

    /** Declare all virtual methods and variables **/
    virtual float operate(float* _input_arr, int _size) = 0;
};

#endif //FOO_INTERFACE_H
