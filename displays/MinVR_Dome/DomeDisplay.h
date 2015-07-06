/*
 * Copyright Regents of the University of Minnesota, 2015.  This software is released under the following license: http://opensource.org/licenses/lgpl-3.0.html.
 * Source code originally developed at the University of Minnesota Interactive Visualization Lab (http://ivlab.cs.umn.edu).
 *
 * Code author(s):
 * 		Dan Orban (dtorban)
 */

#ifndef DOMEDISPLAY_H_
#define DOMEDISPLAY_H_

#include "framework/DisplayDevice.h"

namespace MinVR {

class DomeDisplay : public framework::DisplayDevice {
public:
	DomeDisplay();
	virtual ~DomeDisplay();

	void init(int threadId, WindowRef window);
	void drawGraphics(AbstractMVRAppRef app, int threadId, AbstractCameraRef camera, WindowRef window);
};

} /* namespace MinVR */

#endif /* DOMEDISPLAY_H_ */
