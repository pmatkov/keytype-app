//---------------------------------------------------------------------------

#ifndef FlyingWordH
#define FlyingWordH
//---------------------------------------------------------------------------

#include <vector>
#include <vcl.h>
#include "Position.h"

enum class Speed {
	Fast,
    Normal,
	Slow,
	Count,
	Unknown
};


class FlyingWord {

    private:
        UnicodeString text;

        Limit limit;
        Position position;
        Speed speed;
        UnicodeString color;

        bool visible = true;

        static std::vector<UnicodeString> enumStrings;

    public:
        FlyingWord(const UnicodeString &text, Limit _limit, Position _position, Speed _speed, const UnicodeString &_color);

        void move(Position position);
        static std::vector<UnicodeString>& getEnumStrings();
};



#endif
