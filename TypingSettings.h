//---------------------------------------------------------------------------

#ifndef TypingSettingsH
#define TypingSettingsH

//---------------------------------------------------------------------------

#include<vcl.h>
#include <vector>

#include "ISettings.h"
#include "User.h"

//---------------------------------------------------------------------------

enum class CaretType {
	Block,
	Underline,
    Count,
	Unknown
};

enum class SeparatorType {
	Dot,
	Space,
    Count,
	Unknown
};

class TypingSettings: public ISettings {

    private:
    	CaretType caretType;
        SeparatorType separatorType;

        UnicodeString fontFamily;
        int fontSize;

        bool stopOnMistake;
        bool countConsecutiveMistakes;
        bool displaySpeed;
        bool displayAccuracy;

    	UnicodeString section = "";
        static std::vector<UnicodeString> caretTypeStrings;
        static std::vector<UnicodeString> separatorTypeStrings;

    public:
        TypingSettings();
        TypingSettings(User user);
    	const CaretType& getCaretType() const;
		void setCaretType(const CaretType &_caretType);

        const SeparatorType& getSeparatorType() const;
		void setSeparatorType(const SeparatorType &_separatorType);

        const UnicodeString& getFontFamily() const;
        void setFontFamily(const UnicodeString& _fontFamily);

        int getFontSize() const;
        void setFontSize(int _fontSize);

        bool getStopOnMistake() const;
        void setStopOnMistake(bool _stopOnMistake);

        bool getCountConsecutiveMistakes() const;
        void setCountConsecutiveMistakes(bool _countConsecutiveMistakes);

        bool getDisplaySpeed() const;
        void setDisplaySpeed(bool _displaySpeed);

        bool getDisplayAccuracy() const;
        void setDisplayAccuracy(bool _displayAccuracy);

        void loadDefaults() override;
        void loadSettings() override;
        void saveSettings() override;

        static const std::vector<UnicodeString>& getCaretTypeStrings();
        static const std::vector<UnicodeString>& getSeparatorTypeStrings();

};


#endif
