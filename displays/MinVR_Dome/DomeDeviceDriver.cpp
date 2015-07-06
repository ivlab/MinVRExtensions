/*
 * Copyright Regents of the University of Minnesota, 2015.  This software is released under the following license: http://opensource.org/licenses/GPL-2.0.
 * Source code originally developed at the University of Minnesota Interactive Visualization Lab (http://ivlab.cs.umn.edu).
 *
 * Code author(s):
 * 		Dan Orban (dtorban)
 */


#include <DomeDeviceDriver.h>
#include "framework/plugin/PluginFramework.h"

namespace MinVR {

DomeDeviceDriver::DomeDeviceDriver() {
	// TODO Auto-generated constructor stub

}

DomeDeviceDriver::~DomeDeviceDriver() {
	// TODO Auto-generated destructor stub
}

framework::DisplayDeviceRef DomeDeviceDriver::create(const std::string &type, ConfigMapRef config) {

	if (type == "Dome")
	{
		//return framework::InputDeviceRef(new InputDeviceTUIOClient(name, config));
	}

	return NULL;
}

} /* namespace MinVR */

