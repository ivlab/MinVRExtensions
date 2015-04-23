/*
 * Copyright Regents of the University of Minnesota, 2015.  This software is released under the following license: http://opensource.org/licenses/GPL-2.0.
 * Source code originally developed at the University of Minnesota Interactive Visualization Lab (http://ivlab.cs.umn.edu).
 *
 * Code author(s):
 * 		Dan Orban (dtorban)
 */


#ifndef MINVR_TUIOEVENTS_H
#define MINVR_TUIOEVENTS_H

#include  <glm/glm.hpp>

#ifdef USE_TUIO
#include  <TuioClient.h>
#endif


#include "framework/InputDevice.h"
#include "MVRCore/ConfigMap.H"
#include "MVRCore/Event.H"
#include <vector>
#include <unordered_set>
#include <log/Logger.h>



#define TUIO_PORT  3333

namespace MinVR {

class InputDeviceTUIOClient : public MinVR::framework::InputDevice
{
public:

#ifdef USE_TUIO
	InputDeviceTUIOClient(int port = TUIO_PORT, double  xScaleFactor = 1.0, double  yScaleFactor=1.0 );
	InputDeviceTUIOClient( const std::string name, const ConfigMapRef map );
	virtual ~InputDeviceTUIOClient();
	
	void pollForInput( std::vector<EventRef>  &events );


private:
	TUIO::TuioClient *_tuioClient;
	std::unordered_set<int>    _cursorsDown;
	double      _xScale;
	double      _yScale;

#else
	InputDeviceTUIOClient(int port = TUIO_PORT, double  xScaleFactor = 1.0, double  yScaleFactor=1.0 )
	{
		MinVR::Logger::getInstance().assertMessage(false, "TUIO is currently unsupported. Set cmake option USE_TUIO to ON and recompile.");
	}

	InputDeviceTUIOClient( const std::string name, const ConfigMapRef map )
	{
		MinVR::Logger::getInstance().assertMessage(false, "TUIO is currently unsupported. Set cmake option USE_TUIO to ON and recompile.");
	}

	virtual ~InputDeviceTUIOClient() {}
	void pollForInput( std::vector<EventRef> &events) {}


#endif                   // USE_TUIO
};

}                        // end namespace

#endif                  
