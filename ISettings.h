//---------------------------------------------------------------------------

#ifndef ISettingsH
#define ISettingsH
//---------------------------------------------------------------------------
#include<vcl.h>

class ISettings {
    public:
      	virtual void loadDefaults() = 0;
        virtual void loadSettings() = 0;
        virtual void saveSettings() = 0;
};

#endif
