/*
 * Copyright Regents of the University of Minnesota, 2015.  This software is released under the following license: http://opensource.org/licenses/GPL-2.0.
 * Source code originally developed at the University of Minnesota Interactive Visualization Lab (http://ivlab.cs.umn.edu).
 *
 * Code author(s):
 * 		Dan Orban (dtorban)
 */

#include "framework/plugin/Plugin.h"
#include "log/Logger.h"
#include "TuioDeviceDriver.h"

namespace MinVR {

using namespace MinVR::framework;
using namespace MinVR::framework::plugin;

class TUIOPlugin : public MinVR::framework::plugin::Plugin {
public:
	PLUGIN_API TUIOPlugin() {}
	PLUGIN_API virtual ~TUIOPlugin() {}
	PLUGIN_API bool registerPlugin(MinVR::framework::plugin::PluginInterface *interface)
	{
		MinVR::Logger::getInstance().log("Registering TUIO Plugin", "TUIOPlugin", "plugin");
		interface->getInterface<MinVRInterface>()->addInputDeviceDriver(InputDeviceDriverRef(new TuioDeviceDriver()));
		MinVR::Logger::getInstance().log("Registering TUIO Plugin Complete", "TUIOPlugin", "plugin");
		return true;
	}
};

} /* namespace MinVR_Test */


extern "C"
{
	PLUGIN_API MinVR::framework::plugin::Plugin*loadPlugin() {
		return new MinVR::TUIOPlugin();
	}
}
