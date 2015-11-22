/*
 * Copyright Regents of the University of Minnesota, 2015.  This software is released under the following license: http://opensource.org/licenses/GPL-2.0.
 * Source code originally developed at the University of Minnesota Interactive Visualization Lab (http://ivlab.cs.umn.edu).
 *
 * Code author(s):
 * 		Dan Orban (dtorban)
 */

#include "plugin/Plugin.h"
#include <iostream>
#include "event/VRInputDevice.h"
#include "VrpnDeviceDriver.h"

namespace MinVR {

class VrpnPlugin : public MinVR::Plugin {
public:
	PLUGIN_API VrpnPlugin() {
		std::cout << "VrpnPlugin created." << std::endl;
	}
	PLUGIN_API virtual ~VrpnPlugin() {
		std::cout << "VrpnPlugin destroyed." << std::endl;
	}
	PLUGIN_API bool registerPlugin(MinVR::PluginInterface *iface)
	{
		VRInputDeviceInterface* inputDeviceInterface = iface->getInterface<VRInputDeviceInterface>();
		if (inputDeviceInterface != NULL)
		{
			std::cout << "Registering VrpnPlugin with the following interface: " << iface->getName() << std::endl;
			inputDeviceInterface->addInputDeviceDriver(new VrpnDeviceDriver());
			return true;
		}

		return false;
	}
	PLUGIN_API bool unregisterPlugin(MinVR::PluginInterface *iface)
	{
		std::cout << "Unregistering VrpnPlugin with the following interface: " << iface->getName() << std::endl;
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

