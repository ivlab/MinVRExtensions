/*
 * Copyright Regents of the University of Minnesota, 2015.  This software is released under the following license: http://opensource.org/licenses/GPL-2.0.
 * Source code originally developed at the University of Minnesota Interactive Visualization Lab (http://ivlab.cs.umn.edu).
 *
 * Code author(s):
 * 		Dan Orban (dtorban)
 */

#include "framework/plugin/Plugin.h"
#include "log/Logger.h"
#include "VrpnDeviceDriver.h"

namespace MinVR {

using namespace MinVR::framework;
using namespace MinVR::framework::plugin;

class VrpnPlugin : public MinVR::framework::plugin::Plugin {
public:
	VrpnPlugin() {}
	virtual ~VrpnPlugin() {}
	bool registerPlugin(MinVR::framework::plugin::PluginInterface *interface)
	{
		MinVR::Logger::getInstance().log("Registering vrpn Plugin", "TUIOPlugin", "plugin");
		interface->getInterface<MinVRInterface>()->addInputDeviceDriver(InputDeviceDriverRef(new VrpnDeviceDriver()));
		MinVR::Logger::getInstance().log("Registering vrpn Plugin Complete", "TUIOPlugin", "plugin");
		return true;
	}
};

} /* namespace MinVR_Test */


extern "C"
{
	MinVR::framework::plugin::PluginRef loadPlugin() {
		return MinVR::framework::plugin::PluginRef(new MinVR::VrpnPlugin());
	}
}
