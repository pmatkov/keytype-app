//---------------------------------------------------------------------------

#ifndef ISingleItemDisplayH
#define ISingleItemDisplayH
//---------------------------------------------------------------------------

__interface INTERFACE_UUID("{A1B2C3D4-E5F6-789A-BCDE-F0123456789A}") ISingleItemDisplay : public IInterface {
    public:
        virtual void setItemSingleItemControl(const UnicodeString& componentName, const UnicodeString& item) = 0;

};

#endif
