# Plugin system management for C++

<a rel="license" href="http://creativecommons.org/licenses/by-nc-nd/4.0/"><img alt="Creative Commons License" style="border-width:0" src="https://i.creativecommons.org/l/by-nc-nd/4.0/88x31.png" />

* [Description](#Description)
* [Use case example](#Example)
* [Installation](#Installation)
* [Creating a plugin](#Usage)
* [Notes](#Notes)
* [References](#References)

## <a name="Description"></a>1. Description

Plugin system management for C++. An API to load in run-time dynamic libraries classes.

## <a name="Example"></a>2. Use Case Example

This package have a calculator app use case example. The calculator functionalities are implemented as plugins and loaded at run-time. The plugins are placed at [plugins folder](./plugins/) after the [instalation](#Installation) procedure.

To run just type in terminal (after the [instalation](#Installation) procedure):
```
cd build
./calculator_app
```

## <a name="Installation"></a>3. Installation
```
mkdir build
cd build
cmake ..
make install
```

After the installation the shared libs will be located at ```/usr/local/lib/plugin_system_management```. The headers files will be located at ```/usr/local/include/plugin_system_management```

## <a name="Usage"></a>4. Creating a Plugin

The API is design to load libraries with a specific interface class that provides plugin's metadata and instantiate exported classes. See [this example](./templates/plugin_interface_template.h).
The plugins must have this [structure](./templates/plugin_template.h) (i.e. a footnote code part addition), otherwise the manager will not be able to load them.

**NOTE**: All plugins need to have memory management implicit. In other words, if pointers or mallocs are used be sure that in the end the plugin will delete/free them. The plugin system management (Unix version) uses the [dlfcn](https://pubs.opengroup.org/onlinepubs/7908799/xsh/dlfcn.h.html) lib that does not support the identification of inner dynamic lib memory allocations.

**NOTE**: Avoid inheritance between plugins. The plugin **must** be the last child class, i.e., the class that have the footnote code part addition cannot be a parent class.

**NOTE**: Despite working as a typical class, plugin classes should be avoided as a typical class instantiation. Until now, this situation leads to multiple classes constructions that, at a destruction stage, can lead to "double free or corruption" issues.
Therefore, the instantion should be made by the PluginManagement method [CreateInstanceAs](./src/plugin_system_management/plugin_system_management.cpp) as such presented in [calculator example](./src/calculator.cpp).

## <a name="Notes"></a>5. Notes
The system was tested on:
- Ubuntu: 20.04
    - Cpp versions: 9.3 and 10.3;
- ~~Windows~~: **TODO**

## <a name="Usage"></a>6. References

The work was based on [this](https://github.com/caiorss/sample-cpp-plugin).

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
<br />This work is licensed under a <a rel="license" href="http://creativecommons.org/licenses/by-nc-nd/4.0/">Creative Commons Attribution-NonCommercial-NoDerivatives 4.0 International License</a>.
