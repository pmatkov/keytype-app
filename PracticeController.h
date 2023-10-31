//---------------------------------------------------------------------------

#ifndef PracticeControllerH
#define PracticeControllerH
//---------------------------------------------------------------------------
#include <vcl.h>
#include <windows.h>
#include "IOControl.h"
#include "PracticeSession.h"
#include "MForm.h"

class TFMain;

class PracticeController {
	private:
		TFMain *form;
		IOControl ioControl;
		PracticeSession session;

	public:
        PracticeController(TFMain* form);
		void startPractice();
		void processKeystroke(WPARAM wParam);

};

#endif
