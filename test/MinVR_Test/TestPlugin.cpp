/*
 * Copyright Regents of the University of Minnesota, 2014.  This software is released under the following license: http://opensource.org/licenses/lgpl-3.0.html.
 * Source code originally developed at the University of Minnesota Interactive Visualization Lab (http://ivlab.cs.umn.edu).
 *
 * Code author(s):
 * 		Dan Orban (dtorban)
 */

#include "framework/plugin/Plugin.h"
#include "log/Logger.h"

namespace MinVR_Test {

class TestPlugin : public MinVR::framework::plugin::Plugin {
public:
	TestPlugin() {}
	virtual ~TestPlugin() {}
	bool registerPlugin(MinVR::framework::plugin::PluginInterface *interface)
	{
		MinVR::Logger::getInstance().log("Registering Test Plugin", "TestPlugin", "plugin");
		return true;
	}
};

} /* namespace MinVR_Test */


extern "C"
{
	MinVR::framework::plugin::PluginRef loadPlugin() {
		return MinVR::framework::plugin::PluginRef(new MinVR_Test::TestPlugin());
	}
}
