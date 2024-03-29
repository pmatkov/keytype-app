//---------------------------------------------------------------------------

#ifndef IGameDisplayH
#define IGameDisplayH
//---------------------------------------------------------------------------

__interface INTERFACE_UUID("{861c46f1-89d7-4ec8-8801-18823484db46}") IGameDisplay : public IInterface {
    public:
        virtual bool createTextControl(const UnicodeString& text, const UnicodeString& color) = 0;
        virtual bool removeTextControl(int index) = 0;
        virtual bool moveTextControl(int index, int x, int y) = 0;

        virtual int getTextHeight(int index) = 0;
        virtual int getTextWidth(int index) = 0;

};

#endif
