//---------------------------------------------------------------------------

#ifndef PositionH
#define PositionH
//---------------------------------------------------------------------------

class Limit {
	private:
        int top;
        int bottom;
        int left;
        int right;

    public:
        Limit(int _top, int _bottom, int _left, int _right);

        int getTop() const;
        int getBottom() const;
        int getLeft() const;
        int getRight() const;

        void setTop(int _top);
        void setBottom(int _bottom);
        void setLeft(int _left);
        void setRight(int _right);

};


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
