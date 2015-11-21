/*
 * Copyright Regents of the University of Minnesota, 2015.  This software is released under the following license: http://opensource.org/licenses/GPL-2.0.
 * Source code originally developed at the University of Minnesota Interactive Visualization Lab (http://ivlab.cs.umn.edu).
 *
 * Code author(s):
 * 		Dan Orban (dtorban)
 */

/*#include "framework/plugin/Plugin.h"
#include "log/Logger.h"
#include "VrpnDeviceDriver.h"
#include "framework/plugin/PluginFramework.h"

namespace MinVR {

using namespace MinVR::framework;
using namespace MinVR::framework::plugin;

class VrpnPlugin : public MinVR::framework::plugin::Plugin {
public:
	PLUGIN_API VrpnPlugin() {}
	PLUGIN_API virtual ~VrpnPlugin() {}
	PLUGIN_API bool registerPlugin(MinVR::framework::plugin::PluginInterface *interface)
	{
		MinVR::Logger::getInstance().log("Registering vrpn Plugin", "TUIOPlugin", "plugin");
		interface->getInterface<MinVRInterface>()->addInputDeviceDriver(InputDeviceDriverRef(new VrpnDeviceDriver()));
		MinVR::Logger::getInstance().log("Registering vrpn Plugin Complete", "TUIOPlugin", "plugin");
		return true;
	}
};

} /* namespace MinVR_Test


extern "C"
{
	PLUGIN_API MinVR::framework::plugin::Plugin* loadPlugin() {
		return new MinVR::VrpnPlugin();
	}
} */

#include "plugin/Plugin.h"
#include <iostream>

namespace MinVR {

class VrpnPlugin : public MinVR::Plugin {
public:
	PLUGIN_API VrpnPlugin() {
		std::cout << "VrpnPlugin created." << std::endl;
	}
	PLUGIN_API virtual ~VrpnPlugin() {
		std::cout << "VrpnPlugin destroyed." << std::endl;
	}
	PLUGIN_API bool registerPlugin(MinVR::PluginInterface *interface)
	{
		std::cout << "Registering VrpnPlugin with the following interface: " << interface->getName() << std::endl;
		return true;
	}
	PLUGIN_API bool unregisterPlugin(MinVR::PluginInterface *interface)
	{
		std::cout << "Unregistering VrpnPlugin with the following interface: " << interface->getName() << std::endl;

		return true;
	}
};

}

extern "C"
{
	PLUGIN_API MinVR::Plugin* loadPlugin() {
		return new MinVR::VrpnPlugin();
	}
}

