
#ifndef LABEL_H
#define LABEL_H

#include <string>
#include <iostream>
#include <Windows.h>
#include "BaseComponent.h"

class Label : public BaseComponent
{
private:
	std::string text;

public:
	Label(std::string txt, int _x, int _y, int w, int h, BorderType bType = None, Color tColor = Black, Color bColor = White);
	void setText(std::string);

	std::string getText();

	void setPosition(int, int);
	void draw();

};

#endif