/*
 * Copyright Regents of the University of Minnesota, 2014.  This software is released under the following license: http://opensource.org/licenses/lgpl-3.0.html.
 * Source code originally developed at the University of Minnesota Interactive Visualization Lab (http://ivlab.cs.umn.edu).
 *
 * Code author(s):
 * 		Dan Orban (dtorban)
 */

#include "framework/plugin/Plugin.h"
#include "log/Logger.h"

#if defined(WIN32)
#define PLUGIN_API __declspec(dllexport)
#else
#define PLUGIN_API
#endif

namespace MinVR {

class TestPlugin : public MinVR::framework::plugin::Plugin {
public:
	PLUGIN_API TestPlugin() {}
	PLUGIN_API virtual ~TestPlugin() {}
	PLUGIN_API bool registerPlugin(MinVR::framework::plugin::PluginInterface *interface)
	{
		MinVR::Logger::getInstance().log("Registering Test Plugin", "TestPlugin", "plugin");
		return true;
	}
};

} /* namespace MinVR_Test */


extern "C"
{
	PLUGIN_API MinVR::framework::plugin::PluginRef loadPlugin() {
		return MinVR::framework::plugin::PluginRef(new MinVR::TestPlugin());
	}
}
