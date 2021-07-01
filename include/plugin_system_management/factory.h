/**\file
 * \brief
 * Factory class declaration
 * @version 01.07.2021
 * @author João Pedro Carvalho de Souza (based on https://github.com/caiorss/sample-cpp-plugin)
 */

#ifndef _FACTORY_HPP_
#define _FACTORY_HPP_

#include <string>
#include <functional>
#include "interfaces.h"

/** Macro EXPORT_CPP makes a symbol visible. */
#if defined(_WIN32)
  // MS-Windows NT 
  #define PSDK_PLUGIN_EXPORT_C extern "C" __declspec(dllexport) 
#else
  // Unix-like OSes
  #define PLUGIN_EXPORT_C extern "C" __attribute__ ((visibility ("default")))
#endif 

/** @brief Concrete implementation of the interface IPluginFactory.
 * An instance of this class is supposed to be exported by the plugin
 * entry-point function
 */
class PluginFactory: public IPluginFactory
{
	/** Contains the pair <ClassName, Constructor Function  **/
	using CtorItem = std::pair<std::string, std::function<void* ()>>;
	// Constructor database
	using CtorDB = std::vector<CtorItem>;
	
	/** Plugin name */
	std::string m_name;
	/** Plugin version */
	std::string m_version;	
	CtorDB m_ctordb;	
public:
	
	PluginFactory(const char* name, const char* version);
	
	/** Get Plugin Name */
	const char* Name() const;

    /** Get Plugin Version */
	const char* Version() const;

    /** Get number of classes exported by the plugin */
	virtual size_t NumberOfClasses() const;

	virtual const char* GetClassName(size_t index) const;
	
	/** Instantiate a class from its name.
	 * This member function returns a type-erased pointer
	 * to a class object allocated on the heap.
     */
	void* Factory(const char* className) const;

    void* Factory(int _class_index) const;

	/** Register class name and constructor in the plugin database */
	template<typename AClass>
	PluginFactory& registerClass(std::string const& name)
	{
		auto constructor = []{ return new (std::nothrow) AClass; };
		m_ctordb.push_back(std::make_pair(name, constructor));
		return *this;
	}
		
};


#endif 
