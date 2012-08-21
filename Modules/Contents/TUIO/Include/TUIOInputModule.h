
#pragma once

#include <PolyInputEvent.h>
#include <PolyCore.h>
#include <PolyModule.h>

#include "TuioListener.h"
#include "TuioClient.h"
#include "TuioObject.h"
#include "TuioCursor.h"
#include "TuioPoint.h"

using namespace TUIO;
using namespace Polycode;

class TUIOEvent {
	public:
		std::vector<TouchInfo> touches;		
		unsigned int type;
		TouchInfo touch;
};

class TUIOInputModule : public PolycodeModule, TuioListener {
	public:
		TUIOInputModule(int port);
		virtual ~TUIOInputModule();
		
		void addTuioObject(TuioObject *tobj);
		void updateTuioObject(TuioObject *tobj);
		void removeTuioObject(TuioObject *tobj);
	
		void addTuioCursor(TuioCursor *tcur);
		void updateTuioCursor(TuioCursor *tcur);
		void removeTuioCursor(TuioCursor *tcur);
	
		void refresh(TuioTime frameTime);
		
		void Update(Number elapsed);
		
	protected:
	
		CoreMutex *eventMutex;
		TuioClient *tuioClient;
		std::vector<TUIOEvent> events;
};