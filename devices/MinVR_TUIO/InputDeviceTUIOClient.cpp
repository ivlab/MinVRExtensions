/*
 * Copyright Regents of the University of Minnesota, 2015.  This software is released under the following license: http://opensource.org/licenses/GPL-2.0.
 * Source code originally developed at the University of Minnesota Interactive Visualization Lab (http://ivlab.cs.umn.edu).
 *
 * Code author(s):
 * 		Dan Orban (dtorban)
 */


#include "InputDeviceTUIOClient.H"

#include <list>
#include <sstream>

namespace MinVR {

#ifdef USE_TUIO

using namespace TUIO;

InputDeviceTUIOClient::InputDeviceTUIOClient(const std::string name, int port, double xScale, double yScale) : _name(name)
{
	_xScale = xScale;
	_yScale = yScale;
	_tuioClient = new TuioClient(port);
	_tuioClient->connect();

	if (!_tuioClient->isConnected())
	{  
		std::cout << "InputDeviceTUIOClient: Cannot connect on port " << port << "." << std::endl;
	}
}



InputDeviceTUIOClient::InputDeviceTUIOClient(const std::string name, VRDataIndex& map ) : _name(name)
{
	int  port = map.getValue( "port" );
	double xs = map.getValue( "xScaleFactor" );
	double ys = map.getValue( "yScaleFactor" );

	_xScale = xs;
	_yScale = ys;
	_tuioClient = new TuioClient(port);
	_tuioClient->connect();

	if (!_tuioClient->isConnected())
	{ 
		std::cout << "InputDeviceTUIOClient: Cannot connect on port " << port << "." << std::endl;
	}
}

InputDeviceTUIOClient::~InputDeviceTUIOClient()
{
	if (_tuioClient) {
		_tuioClient->disconnect();
		delete _tuioClient;
	}
}

inline std::string	intToString(int i)
{
	std::ostringstream ostr;
	// if using strstream rather than stringstream, the following call
	// requires a   << "\0"   at the end.
	ostr << i;
	return std::string(ostr.str());
}

inline VRDoubleArray fromGlm(const glm::dvec2 & v) {
	VRDoubleArray a;
	a.push_back(v.x);
	a.push_back(v.y);
	return a;
}

void InputDeviceTUIOClient::appendNewInputEventsSinceLastCall(std::vector<VREvent> &events)
{
	// Send out events for TUIO "cursors" by polling the TuioClient for the current state  
	std::list<TuioCursor*> cursorList = _tuioClient->getTuioCursors();
	_tuioClient->lockCursorList();

	std::list<int> toErase;

	// Send "button" up events for cursors that were down last frame, but are now up.
	for ( auto downLast_it = _cursorsDown.begin(); downLast_it!= _cursorsDown.end(); ++downLast_it ) {
		bool stillDown = false;
		for (std::list<TuioCursor*>::iterator iter = cursorList.begin(); iter!=cursorList.end(); iter++) {
			TuioCursor *tcur = (*iter);
			if (tcur->getCursorID() == *downLast_it) {
				stillDown = true;
			}
		}
		if (!stillDown) {

			VRDataIndex di;
			di.addData("id", *downLast_it);
			di.addData("action", "Up");

			events.push_back(VREvent(_name, di));
			toErase.push_back(*downLast_it);
		}
	}

	for (std::list<int>::iterator iter = toErase.begin(); iter != toErase.end(); iter++) {
		_cursorsDown.erase(*iter);
	}

	// Send "button" down events for cursors that are new and updated positions for all cursors
	for (std::list<TuioCursor*>::iterator iter = cursorList.begin(); iter!=cursorList.end(); iter++) {
		TuioCursor *tcur = (*iter);
		glm::dvec2 pos = glm::dvec2(_xScale*tcur->getX(), _yScale*tcur->getY());

		if (_cursorsDown.find(tcur->getCursorID()) == _cursorsDown.end()) {
			VRDataIndex di;
			di.addData("id", tcur->getCursorID());
			di.addData("pos", fromGlm(pos));
			di.addData("action", "Down");
			events.push_back(VREvent(_name, di));
			_cursorsDown.insert(tcur->getCursorID());
		}

		if (tcur->getMotionSpeed() > 0.0) {
			VRDataIndex di;
			di.addData("id", tcur->getCursorID());
			di.addData("pos", fromGlm(pos));
			di.addData("speed", tcur->getMotionSpeed());
			di.addData("acc", tcur->getMotionAccel());
			di.addData("action", "Move");
			glm::dvec4 data = glm::dvec4(pos, tcur->getMotionSpeed(), tcur->getMotionAccel());
			events.push_back(VREvent(_name, di));
		}

		// Can also access several other properties of cursors (speed, acceleration, path followed, etc.)
		//std::cout << "cur " << tcur->getCursorID() << " (" <<  tcur->getSessionID() << ") " << tcur->getX() << " " << tcur->getY() 
		// << " " << tcur->getMotionSpeed() << " " << tcur->getMotionAccel() << " " << std::endl;

		// This is how to access all the points in the path that a cursor follows:     
		//std::list<TuioPoint> path = tuioCursor->getPath();
		//if (path.size() > 0) {
		//  TuioPoint last_point = path.front();
		//  for (std::list<TuioPoint>::iterator point = path.begin(); point!=path.end(); point++) {
		//    last_point.update(point->getX(),point->getY());   
		//  }
		//}
	}
	_tuioClient->unlockCursorList();


	// Unsure what TUIO "objects" are -- perhaps tangible props.  In any case, this is how to access object data:
	std::list<TuioObject*> objectList = _tuioClient->getTuioObjects();
	_tuioClient->lockObjectList();
	for (std::list<TuioObject*>::iterator iter = objectList.begin(); iter!=objectList.end(); iter++) {
		TuioObject* tuioObject = (*iter);    
		int   id    = tuioObject->getSymbolID();
		double xpos  = _xScale*tuioObject->getX();
		double ypos  = _yScale*tuioObject->getY();
		double angle = tuioObject->getAngle()/M_PI*180.0;

		VRDataIndex di;
		di.addData("id", id);
		di.addData("xpos", xpos);
		di.addData("ypos", ypos);
		di.addData("angle", angle);
		di.addData("action", "Obj");

		std::string name = _name;
		events.push_back(VREvent(name, di));
	}
	_tuioClient->unlockObjectList();
}

#endif //USE_TUIO

};         // end namespace
