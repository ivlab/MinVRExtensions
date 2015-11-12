/*
 * Copyright Regents of the University of Minnesota, 2014.  This software is released under the following license: http://opensource.org/licenses/lgpl-3.0.html.
 * Source code originally developed at the University of Minnesota Interactive Visualization Lab (http://ivlab.cs.umn.edu).
 *
 * Code author(s):
 * 		Dan Orban (dtorban)
 */

#include "framework/plugin/Plugin.h"
#include "log/Logger.h"
#include "OculusRiftDisplay.h"

using namespace MinVR::framework;
using namespace MinVR::framework::plugin;

namespace MinVR {

class OculusPlugin : public MinVR::framework::plugin::Plugin {
public:
	PLUGIN_API OculusPlugin() {}
	PLUGIN_API virtual ~OculusPlugin() {}
	PLUGIN_API bool registerPlugin(MinVR::framework::plugin::PluginInterface *interface)
	{
		MinVR::Logger::getInstance().log("Registering Oculus Plugin", "TestPlugin", "plugin");

		interface->getInterface<MinVRInterface>()->addStereoDisplayDriver(MinVR::framework::StereoDisplayDriverRef(new OculusRiftDisplayFactory()));

		return true;
	}
};

} /* namespace MinVR_Test */


extern "C"
{
	PLUGIN_API MinVR::framework::plugin::Plugin* loadPlugin() {
		return new MinVR::OculusPlugin();
	}
}
