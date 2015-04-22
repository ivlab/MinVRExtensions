/*
 * Copyright Regents of the University of Minnesota, 2014.  This software is released under the following license: http://opensource.org/licenses/lgpl-3.0.html.
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
	TUIOPlugin() {}
	virtual ~TUIOPlugin() {}
	bool registerPlugin(MinVR::framework::plugin::PluginInterface *interface)
	{
		MinVR::Logger::getInstance().log("Registering TUIO Plugin", "TUIOPlugin", "plugin");
		interface->addInputDeviceDriver(InputDeviceDriverRef(new TuioDeviceDriver()));
		MinVR::Logger::getInstance().log("Registering TUIO Plugin Complete", "TUIOPlugin", "plugin");
		return true;
	}
};

} /* namespace MinVR_Test */


extern "C"
{
	MinVR::framework::plugin::PluginRef loadPlugin() {
		return MinVR::framework::plugin::PluginRef(new MinVR::TUIOPlugin());
	}
}
