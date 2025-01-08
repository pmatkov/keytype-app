//---------------------------------------------------------------------------

#pragma hdrstop

#include "SessionModule.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

SessionModule::SessionModule() {

	iocontrol = std::make_unique<IOControl>();
	session = std::make_unique<PracticeSession>();
}

IOControl* SessionModule::getIOControl() const {
	return iocontrol.get();
}

PracticeSession* SessionModule::getSession() const {
	return session.get();
}
