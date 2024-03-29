//---------------------------------------------------------------------------

#ifndef GameAreaH
#define GameAreaH
//---------------------------------------------------------------------------


class GameArea {
    private:
    	int top, bottom;
        int left, right;
    public:
    	GameArea();
        GameArea(int _top, int _bottom, int _left, int _right);
        int getTop() const;
        int getBottom() const;
        int getLeft() const;
        int getRight() const;


};

#endif
