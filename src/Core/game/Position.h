//---------------------------------------------------------------------------

#ifndef PositionH
#define PositionH
//---------------------------------------------------------------------------

class Position {

    private:
        int x;
        int y;

    public:
        Position(int _x, int _y);

        int getX() const;
        void setX(int _x);
        int getY() const;
        void setY(int _y);
};

#endif
