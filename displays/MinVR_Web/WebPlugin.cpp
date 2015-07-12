/*
 * Copyright Regents of the University of Minnesota, 2015.  This software is released under the following license: http://opensource.org/licenses/GPL-2.0.
 * Source code originally developed at the University of Minnesota Interactive Visualization Lab (http://ivlab.cs.umn.edu).
 *
 * Code author(s):
 * 		Dan Orban (dtorban)
 */

#include "framework/plugin/Plugin.h"
#include "log/Logger.h"
#include "WebDeviceDriver.h"

namespace MinVR {

using namespace MinVR::framework;
using namespace MinVR::framework::plugin;

class WebPlugin : public MinVR::framework::plugin::Plugin {
public:
	PLUGIN_API WebPlugin() {}
	PLUGIN_API virtual ~WebPlugin() {}
	PLUGIN_API bool registerPlugin(MinVR::framework::plugin::PluginInterface *interface)
	{
		MinVR::Logger::getInstance().log("Registering Dome Plugin", "DomePlugin", "plugin");
		interface->getInterface<MinVRInterface>()->addDisplayDeviceDriver(DisplayDeviceDriverRef(new WebDeviceDriver()));
		MinVR::Logger::getInstance().log("Registering Dome Plugin Complete", "DomePlugin", "plugin");
		return true;
	}
};

} /* namespace MinVR_Test */


extern "C"
{
	PLUGIN_API MinVR::framework::plugin::Plugin*loadPlugin() {
		return new MinVR::WebPlugin();
	}
}
