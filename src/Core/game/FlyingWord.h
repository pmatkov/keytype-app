//---------------------------------------------------------------------------

#ifndef FlyingWordH
#define FlyingWordH
//---------------------------------------------------------------------------

#include <vector>
#include <vcl.h>
#include "Position.h"
#include "Limit.h"

enum class Speed {
	Slow = 1,
	Normal = 2,
	Fast = 3,
	Count = 4,
	Unknown
};

enum class Direction {
	Up,
	Down,
	Neutral,
	Count,
	Unknown
};


class FlyingWord {

    private:
        UnicodeString text;

		FWLimit::Limit outerLimit;
		FWLimit::Limit innerLimit;

		Position position;
		Speed speed;
		Direction direction;
		UnicodeString color;

		int maxHDistance;

		static std::vector<UnicodeString> enumSpeed;
		static std::vector<UnicodeString> enumDirection;

    public:
		FlyingWord(const UnicodeString &text, FWLimit::Limit _outerLimit, Position _position, Speed _speed, Direction _direction, \
		const UnicodeString &_color, int _maxHDistance);

		const UnicodeString &getText() const;
		const FWLimit::Limit &getOuterLimit() const;
		const FWLimit::Limit &getInnerLimit() const;

		const Position &getPosition() const;
		void setPosition(Position _position);
		const Speed &getSpeed() const;
		const Direction &getDirection() const;
		void setDirection(Direction _direction);
		const UnicodeString &getColor() const;

		const int getMaxHDistance() const;
		void setMaxHDistance(int _maxHDistance);

		void setOuterLimit(int bottom, int right);
		void setInnerLimit(int top, int bottom);

		static std::vector<UnicodeString>& getEnumSpeed();
		static std::vector<UnicodeString>& getEnumDirection();
};



#endif
