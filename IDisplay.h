//---------------------------------------------------------------------------

#ifndef IDisplayH
#define IDisplayH
//---------------------------------------------------------------------------

#include <vector>
#include <vcl.h>
#include <System.Classes.hpp>


__interface INTERFACE_UUID("{C527B88F-3F8E-1134-80e0-01A04F57B270}") IDisplay : public IInterface {
    public:
        virtual void setItemSingleItemControl(const UnicodeString& componentName, const UnicodeString& item) = 0;

        virtual void selectItemMultiItemControl(const UnicodeString& componentName, const UnicodeString& item) = 0;
        virtual void setItemsMultiItemControl(const UnicodeString& componentName, const std::vector<UnicodeString>& items, int selectedIndex) = 0;
        virtual void addItemMultiItemControl(const UnicodeString& componentName, const UnicodeString& item, int selectedIndex) = 0;

};

#endif
