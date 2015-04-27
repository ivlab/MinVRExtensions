/*
 * Copyright Regents of the University of Minnesota, 2015.  This software is released under the following license: http://opensource.org/licenses/GPL-2.0.
 * Source code originally developed at the University of Minnesota Interactive Visualization Lab (http://ivlab.cs.umn.edu).
 *
 * Code author(s):
 * 		Dan Orban (dtorban)
 */


#ifndef TUIODEVICEFACTORY_H_
#define TUIODEVICEFACTORY_H_

#include "framework/InputDevice.h"
#include "framework/plugin/PluginFramework.h"

namespace MinVR {

class TuioDeviceDriver : public MinVR::framework::InputDeviceDriver {
public:
	PLUGIN_API TuioDeviceDriver();
	PLUGIN_API virtual ~TuioDeviceDriver();

	PLUGIN_API MinVR::framework::InputDeviceRef create(const std::string &type, const std::string& name, ConfigMapRef config);
};

} /* namespace MinVR */

#endif /* TUIODEVICEFACTORY_H_ */
