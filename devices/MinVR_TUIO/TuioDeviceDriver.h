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

namespace MinVR {

class TuioDeviceDriver : public MinVR::framework::InputDeviceDriver {
public:
	TuioDeviceDriver();
	virtual ~TuioDeviceDriver();

	MinVR::framework::InputDeviceRef create(const std::string &type, const std::string& name, ConfigMapRef config);
};

} /* namespace MinVR */

#endif /* TUIODEVICEFACTORY_H_ */
