/**\file
* \brief
  Plugin class declaration
* @version 01.07.2021
* @author João Pedro Carvalho de Souza (based on https://github.com/caiorss/sample-cpp-plugin)
*/

#ifndef PLUGIN_TEST_V1_PLUGIN_H
#define PLUGIN_TEST_V1_PLUGIN_H

#include <cassert>
//#include <memory>
//#include <vector>
//#include <filesystem>
#include <iostream>

#include "interfaces.h"
// Unix
#if defined(_WIN32)
#include <windows.h>
#elif defined(__unix__)
// APIs: dlopen, dlclose, dlopen
#include <dlfcn.h>

#else
#error "Not supported operating system"
#endif

#ifdef GetClassName
#undef GetClassName
#endif

/** @brief Class form managing and encapsulating shared libraries loading  */
class Plugin {
public:
    /** @brief Function pointer to DLL entry-point */
    using GetPluginInfo_fp = IPluginFactory *(*)();
    /** @brief Name of DLL entry point that a Plugin should export */
    static constexpr const char *DLLEntryPointName = "GetPluginFactory";

    /** @brief Shared library handle */
    void *m_hnd = nullptr;
    /** @brief Shared library file name */
    std::string m_file = "";
    /** @brief Flag to indicate whether plugin (shared library) is loaded into current process. */
    bool m_isLoaded = false;

    /** @brief Pointer to shared library factory class returned by the DLL entry-point function */
    IPluginFactory *m_info = nullptr;

    Plugin();

    explicit Plugin(std::string file) ;

    ~Plugin();

    Plugin(Plugin const &) = delete;

    Plugin &operator=(const Plugin &) = delete;

    Plugin(Plugin &&rhs);

    Plugin &operator=(Plugin &&rhs);

    IPluginFactory *GetInfo() const;

    void *CreateInstance(std::string const &className) ;

    bool isLoaded() const ;

    bool checkSharedLibHandle() ;

    bool checkFactoryHandle() ;

    void Unload() ;
};

#endif //PLUGIN_TEST_V1_PLUGIN_H
