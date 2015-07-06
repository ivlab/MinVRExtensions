/*
 * Copyright Regents of the University of Minnesota, 2015.  This software is released under the following license: http://opensource.org/licenses/GPL-2.0.
 * Source code originally developed at the University of Minnesota Interactive Visualization Lab (http://ivlab.cs.umn.edu).
 *
 * Code author(s):
 * 		Dan Orban (dtorban)
 */


#ifndef DOMEDEVICEFACTORY_H_
#define DOMEDEVICEFACTORY_H_

#include "framework/DisplayDevice.h"
#include "framework/plugin/PluginFramework.h"

namespace MinVR {

class DomeDeviceDriver : public MinVR::framework::DisplayDeviceDriver {
public:
	PLUGIN_API DomeDeviceDriver();
	PLUGIN_API virtual ~DomeDeviceDriver();

	PLUGIN_API MinVR::framework::DisplayDeviceRef create(const std::string &type, ConfigMapRef config);
};

} /* namespace MinVR */

#endif /* DOMEDEVICEFACTORY_H_ */
