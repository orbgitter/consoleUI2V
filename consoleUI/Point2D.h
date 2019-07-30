#ifndef POINT2D_H
#define POINT2D_H

class Point2D {
private:
	int x, y;

public:
	Point2D(int _x = 0, int _y = 0);
	inline int getX() const { return x; }
	inline int getY() const { return y; }
	inline virtual void setX(int _x) { x = _x; }
	inline virtual void setY(int _y) { y = _y; }
};

#endif