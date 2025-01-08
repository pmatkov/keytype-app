//---------------------------------------------------------------------------

#ifndef SessionModuleH
#define SessionModuleH
//---------------------------------------------------------------------------

#include <memory>
#include <vector>

#include "IOControl.h"
#include "PracticeSession.h"

class SessionModule {

	private:
		std::unique_ptr<IOControl> iocontrol;
		std::unique_ptr<PracticeSession> session;

	public:
		SessionModule();
		IOControl* getIOControl() const;
		PracticeSession* getSession() const;

};

#endif
