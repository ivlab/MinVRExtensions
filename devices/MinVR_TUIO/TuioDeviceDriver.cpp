/*
 * Copyright Regents of the University of Minnesota, 2015.  This software is released under the following license: http://opensource.org/licenses/GPL-2.0.
 * Source code originally developed at the University of Minnesota Interactive Visualization Lab (http://ivlab.cs.umn.edu).
 *
 * Code author(s):
 * 		Dan Orban (dtorban)
 */


#include <TuioDeviceDriver.h>
#include "InputDeviceTUIOClient.H"

namespace MinVR {

TuioDeviceDriver::TuioDeviceDriver() {
	// TODO Auto-generated constructor stub

}

TuioDeviceDriver::~TuioDeviceDriver() {
	// TODO Auto-generated destructor stub
}

VRInputDevice* TuioDeviceDriver::create(const std::string &type, const std::string& name, VRDataIndex& config)
{
	if (type == "BasicTUIOClient")
	{
		return new InputDeviceTUIOClient(name);
	}
	else if (type == "InputDeviceTUIOClient")
	{
		return new InputDeviceTUIOClient(name, config);
	}

	return NULL;
}

} /* namespace MinVR */

