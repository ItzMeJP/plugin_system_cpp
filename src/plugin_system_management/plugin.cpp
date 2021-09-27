/**\file
 * \brief
 * Plugin class definition
 * @version 01.07.2021
 * @author João Pedro Carvalho de Souza (based on https://github.com/caiorss/sample-cpp-plugin)
 */

#include "plugin.h"

Plugin::Plugin(){}

Plugin::~Plugin() { // TODO: error: The destructor is called everytime that a plugin is constructed...
    this->Unload();
}

Plugin::Plugin(std::string file){
        m_file = std::move(file);

#if !defined(_WIN32)
        m_hnd = ::dlopen((m_file).c_str(), RTLD_GLOBAL | RTLD_LAZY);
#else
        m_hnd  = (void*) ::LoadLibraryA(m_file.c_str());
#endif
        m_isLoaded = true;
        //std::cout<< "file: " <<m_file.c_str()<<std::endl;
        //std::cout<< "m_file: " <<m_file.c_str()<<std::endl;
        //assert(m_hnd != nullptr && "\n>>>> Check the file and path names.\n");
        if (m_hnd != nullptr) {
#if !defined(_WIN32)
            auto dllEntryPoint =
                    reinterpret_cast<GetPluginInfo_fp>(dlsym(m_hnd, DLLEntryPointName));
#else
            auto dllEntryPoint =
                  reinterpret_cast<GetPluginInfo_fp>(GetProcAddress((HMODULE) m_hnd, DLLEntryPointName));
#endif
            // assert(dllEntryPoint != nullptr && "\n>>>>Check the plugin design.\n");
            // Retrieve plugin metadata from DLL entry-point function
            try {
                if(*dllEntryPoint== nullptr)
                    throw 20;
                m_info = dllEntryPoint();
            }
            catch (int e)
            {
                m_info = nullptr;
            }

        }
    }

Plugin::Plugin(Plugin &&rhs) {
m_isLoaded = std::move(rhs.m_isLoaded);
m_hnd = std::move(rhs.m_hnd);
m_file = std::move(rhs.m_file);
m_info = std::move(rhs.m_info);
}

Plugin &Plugin::operator=(Plugin &&rhs) {
    std::swap(rhs.m_isLoaded, m_isLoaded);
    std::swap(rhs.m_hnd, m_hnd);
    std::swap(rhs.m_file, m_file);
    std::swap(rhs.m_info, m_info);
    return *this;
}

IPluginFactory *Plugin::GetInfo() const {
    return m_info;
}

void* Plugin::CreateInstance(std::string const& className)
{
    return m_info->Factory(className.c_str());
}

bool Plugin::isLoaded() const {
    return m_isLoaded;
}

bool Plugin::checkSharedLibHandle() {
    return (m_hnd != nullptr);
}

bool Plugin::checkFactoryHandle() {
    return (m_info != nullptr);
}

void Plugin::Unload() {

    if (m_hnd != nullptr) {
#if !defined(_WIN32)
        ::dlclose(m_hnd);
#else
        ::FreeLibrary((HMODULE) m_hnd);
#endif
        m_hnd = nullptr;
        m_isLoaded = false;
    }
}

