/*
 * Copyright Regents of the University of Minnesota, 2015.  This software is released under the following license: http://opensource.org/licenses/GPL-2.0.
 * Source code originally developed at the University of Minnesota Interactive Visualization Lab (http://ivlab.cs.umn.edu).
 *
 * Code author(s):
 * 		Dan Orban (dtorban)
 */


#ifndef TUIODEVICEFACTORY_H_
#define TUIODEVICEFACTORY_H_

#include "event/VRInputDevice.h"
#include "plugin/PluginFramework.h"

namespace MinVR {

class TuioDeviceDriver : public VRInputDeviceDriver {
public:
	PLUGIN_API TuioDeviceDriver();
	PLUGIN_API virtual ~TuioDeviceDriver();

	PLUGIN_API VRInputDevice* create(const std::string &type, const std::string& name, VRDataIndex& config);
};

} /* namespace MinVR */


#endif /* TUIODEVICEFACTORY_H_ */
