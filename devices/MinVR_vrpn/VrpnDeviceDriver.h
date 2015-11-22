/*
 * Copyright Regents of the University of Minnesota, 2015.  This software is released under the following license: http://opensource.org/licenses/GPL-2.0.
 * Source code originally developed at the University of Minnesota Interactive Visualization Lab (http://ivlab.cs.umn.edu).
 *
 * Code author(s):
 * 		Dan Orban (dtorban)
 */


#ifndef VRPNDEVICEFACTORY_H_
#define VRPNDEVICEFACTORY_H_

#include "event/VRInputDevice.h"
#include "plugin/PluginFramework.h"

namespace MinVR {

class VrpnDeviceDriver : public MinVR::framework::InputDeviceDriver {
public:
	PLUGIN_API VrpnDeviceDriver();
	PLUGIN_API virtual ~VrpnDeviceDriver();

	PLUGIN_API MinVR::framework::InputDeviceRef create(const std::string &type, const std::string& name, ConfigMapRef config);
};

} /* namespace MinVR */

#endif /* VRPNDEVICEFACTORY_H_ */
