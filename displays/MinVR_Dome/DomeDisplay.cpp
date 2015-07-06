/*
 * Copyright Regents of the University of Minnesota, 2015.  This software is released under the following license: http://opensource.org/licenses/lgpl-3.0.html.
 * Source code originally developed at the University of Minnesota Interactive Visualization Lab (http://ivlab.cs.umn.edu).
 *
 * Code author(s):
 * 		Dan Orban (dtorban)
 */

#include <displays/MinVR_Dome/DomeDisplay.h>
#include <iostream>

namespace MinVR {

DomeDisplay::DomeDisplay() {
	// TODO Auto-generated constructor stub

}

DomeDisplay::~DomeDisplay() {
	// TODO Auto-generated destructor stub
}

void DomeDisplay::init(int threadId, WindowRef window) {
}

void DomeDisplay::drawGraphics(AbstractMVRAppRef app, int threadId,
		AbstractCameraRef camera, WindowRef window) {
	app->drawGraphics(threadId, camera, window);
}

} /* namespace MinVR */
