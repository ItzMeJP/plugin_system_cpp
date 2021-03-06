/**\file
 * \brief
 * Interface class that provides plugin's metadata and instantiate exported classes
 * @version 01.07.2021
 * @author João Pedro Carvalho de Souza (based on https://github.com/caiorss/sample-cpp-plugin)
 */

#ifndef _INTERFACES_HPP_
#define _INTERFACES_HPP_

#include <vector>

struct IPluginFactory{
	/** Get Plugin Name */
	virtual const char* Name() const = 0 ;
	/** Get Plugin Version */
	virtual const char* Version() const = 0;

	virtual size_t NumberOfClasses() const = 0;
	virtual const char* GetClassName(size_t index) const = 0;
	
	/** Instantiate a class from its name */
	virtual void* Factory(const char* className) const = 0;

};

#endif 
