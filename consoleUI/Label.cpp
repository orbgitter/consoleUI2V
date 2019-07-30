
#include "Label.h"


Label::Label(std::string txt, int _x, int _y, int w, int h, BorderType bType, Color tColor, Color bColor)
	: BaseComponent(_x, _y, w, h, bType, tColor, bColor), text(txt) {

}

void Label::setText(std::string text)
{
	this->text = text;
}

std::string Label::getText() { return this->text; }

void Label::draw() {

	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

	//applyColors();
	BaseComponent::draw();

	// clear background
	COORD c = { topLeftPoint.getX() + 1, topLeftPoint.getY() + 1 };
	int text_len = static_cast<int>(text.length());

	SetConsoleCursorPosition(out, c);

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			std::cout << " ";
		}

		SetConsoleCursorPosition(out, { topLeftPoint.getX() + 1, topLeftPoint.getY() + i + 1 });
	}

	// print centered text
	c = { topLeftPoint.getX() + 1 + width / 2 - text_len / 2, topLeftPoint.getY() + 1 };
	SetConsoleCursorPosition(out, c);

	std::cout << text;

	isVisible = true;
}