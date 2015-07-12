/*
 * Copyright Regents of the University of Minnesota, 2015.  This software is released under the following license: http://opensource.org/licenses/GPL-2.0.
 * Source code originally developed at the University of Minnesota Interactive Visualization Lab (http://ivlab.cs.umn.edu).
 *
 * Code author(s):
 * 		Dan Orban (dtorban)
 */


#include <WebDeviceDriver.h>
#include "framework/plugin/PluginFramework.h"
#include "WebDisplay.h"

extern "C" {
int main3();
}

namespace MinVR {

WebDeviceDriver::WebDeviceDriver() {
	// TODO Auto-generated constructor stub

}

WebDeviceDriver::~WebDeviceDriver() {
	// TODO Auto-generated destructor stub
}

framework::DisplayDeviceRef WebDeviceDriver::create(const std::string &type, ConfigMapRef config) {
	main3();
	if (type == "Web")
	{

		return framework::DisplayDeviceRef(new WebDisplay());
	}

	return NULL;
}

} /* namespace MinVR */

