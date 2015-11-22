/*
 * Copyright Regents of the University of Minnesota, 2015.  This software is released under the following license: http://opensource.org/licenses/GPL-2.0.
 * Source code originally developed at the University of Minnesota Interactive Visualization Lab (http://ivlab.cs.umn.edu).
 *
 * Code author(s):
 * 		Dan Orban (dtorban)
 */


#include <VrpnDeviceDriver.h>
#include "InputDeviceVRPNAnalog.H"
#include "InputDeviceVRPNButton.H"
#include "InputDeviceVRPNTracker.H"

namespace MinVR {

VrpnDeviceDriver::VrpnDeviceDriver() {
	// TODO Auto-generated constructor stub

}

VrpnDeviceDriver::~VrpnDeviceDriver() {
	// TODO Auto-generated destructor stub
}

VRInputDevice* VrpnDeviceDriver::create(const std::string &type, const std::string& name, VRDataIndex& config) {

	if (type == "InputDeviceVRPNAnalog") {
		return new InputDeviceVRPNAnalog(name, config);
	}
	else if (type == "InputDeviceVRPNButton") {
		return new InputDeviceVRPNButton(name, config);
	}
	else if (type == "InputDeviceVRPNTracker") {
		return new InputDeviceVRPNTracker(name, config);
	}

	return NULL;
}

} /* namespace MinVR */

