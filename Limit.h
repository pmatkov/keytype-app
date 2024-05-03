//---------------------------------------------------------------------------

#ifndef LimitH
#define LimitH
//---------------------------------------------------------------------------

namespace FWLimit {

    class Limit {
        private:
            int top;
            int bottom;
            int left;
            int right;

        public:
            Limit();
            Limit(int _top, int _bottom, int _left, int _right);

            int getTop() const;
            void setTop(int _top);
            int getBottom() const;
            void setBottom(int _bottom);
            int getLeft() const;
            void setLeft(int _left);
            int getRight() const;
            void setRight(int _right);

    };
}
#endif
