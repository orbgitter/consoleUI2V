#ifndef BASE_COMPONENT_H
#define BASE_COMPONENT_H

#include "Enums.h"
#include "Point2D.h"
#include <Windows.h>
#include <iostream>

struct BorderCharacters {
	char leftTopCorner, rightTopCorner, leftBottomCorner, rightBottomCorner, horizontal, vertical;
};

class BaseComponent {

protected:
	Point2D topLeftPoint;
	int width, height;
	Color backgroundColor, textColor;
	BorderType borderType;
	BorderCharacters borderCharacters;

	bool isVisible;

	void drawBorder();
	void applyColors();
	//void removeFromScreen();

public:
	BaseComponent(int _x, int _y, int w, int h, BorderType bType = None, Color tColor = Black, Color bColor = White);

	virtual void draw() = 0;
	virtual void onMouseClick(COORD mousePos) = 0 {};
	virtual bool isIntersects(COORD mousePos) = 0;
	virtual bool isFocused() = 0 {};
	virtual void onKeyPressed(WORD key) = 0 {};

	void removeFromScreen();

	// Setters
	void setTextColor(Color tColor);
	void setBackgroundColor(Color bColor);
	void setX(int _x);
	void setY(int _y);
	void setHeight(int _h);
	void setWidth(int _w);
	void setBorderType(BorderType bType);

	//getters
	Color getTextColor() const;
	Color getBackgroundColor() const;
	int getX() const;
	int getY() const;
	int getHeight() const;
	int getWidth() const;
	BorderType getBorderType() const;

};

#endif