#include "BaseComponent.h"

BaseComponent::BaseComponent(int _x, int _y, int w, int h, BorderType bType, Color tColor, Color bColor)
	: topLeftPoint(_x, _y), width(w), height(h), borderType(bType), textColor(tColor), backgroundColor(bColor), isVisible(false) {

}

void BaseComponent::draw() {

	drawBorder();
}

void BaseComponent::applyColors() {

	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(out, textColor | FOREGROUND_INTENSITY | backgroundColor * 16);
}

void BaseComponent::removeFromScreen() {

	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD c = { topLeftPoint.getX(), topLeftPoint.getY() };

	SetConsoleCursorPosition(out, c);
	SetConsoleTextAttribute(out, Black | FOREGROUND_INTENSITY | Black * 16);

	for (int i = 0; i <= height; i++) {
		for (int j = 0; j <= width + 1; j++) {
			std::cout << " ";
		}
		++c.Y;
		SetConsoleCursorPosition(out, c);
	}
}

void BaseComponent::setTextColor(Color tColor) {

	removeFromScreen();

	textColor = tColor;

	draw();
}

void BaseComponent::setBackgroundColor(Color bColor){
	
	removeFromScreen();

	backgroundColor = bColor;

	draw();
}

void BaseComponent::setX(int _x){

	removeFromScreen();

	topLeftPoint.setX(_x);

	draw();
}

void BaseComponent::setY(int _y){

	removeFromScreen();

	topLeftPoint.setY(_y);

	draw();
}

void BaseComponent::setHeight(int _h){

	removeFromScreen();
	
	height = _h;
	
	draw();

}

void BaseComponent::setWidth(int _w){

	removeFromScreen();

	width = _w;

	draw();

}

void BaseComponent::setBorderType(BorderType bType){

	removeFromScreen();

	borderType = bType;

	draw();
}

Color BaseComponent::getTextColor() const{
	return this->textColor;
}

Color BaseComponent::getBackgroundColor() const{
	return this->backgroundColor;
}

int BaseComponent::getX() const{
	return topLeftPoint.getX();
}

int BaseComponent::getY() const{
	return topLeftPoint.getY();
}

int BaseComponent::getHeight() const{
	return this->height;
}

int BaseComponent::getWidth() const{
	return this->width;
}

BorderType BaseComponent::getBorderType() const{
	return this->borderType;
}




void BaseComponent::drawBorder() {


	//windows console uses COORD structure to identify position inside the console
	COORD position = { topLeftPoint.getX(), topLeftPoint.getY() };


	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO info;


	SetConsoleCursorPosition(out, position);

	applyColors();
	int i;
	COORD c;
	switch (borderType) {
	case Dotted:
		borderCharacters = { '\xDA', '\xBF', '\xC0', '\xD9', '-', '|' };
		break;
	case Solid:
		borderCharacters = { '\xDA', '\xBF', '\xC0', '\xD9', '\xC4', '\xB3' };
		break;
	case Double:
		borderCharacters = { '\xC9', '\xBB', '\xC8', '\xBC', '\xCD', '\xBA' };
		break;
	case None: return;
	default: return;
	}

	std::cout << borderCharacters.leftTopCorner;

	for (i = 0; i < width; i++)
		std::cout << borderCharacters.horizontal;

	std::cout << borderCharacters.rightTopCorner;

	for (i = 1; i < height; i++) {
		c = { topLeftPoint.getX(), topLeftPoint.getY() + i };
		SetConsoleCursorPosition(out, c);
		std::cout << borderCharacters.vertical;
		c = { topLeftPoint.getX() + width + 1, topLeftPoint.getY() + i };
		SetConsoleCursorPosition(out, c);
		std::cout << borderCharacters.vertical;
	}

	c = { topLeftPoint.getX(), topLeftPoint.getY() + i };
	SetConsoleCursorPosition(out, c);
	std::cout << borderCharacters.leftBottomCorner;
	for (i = 0; i < width; i++) {
		std::cout << borderCharacters.horizontal;
	}
	std::cout << borderCharacters.rightBottomCorner;

}


bool BaseComponent::isIntersects(COORD mousePos) {
	return (mousePos.X >= getX() && mousePos.X <= getX() + getWidth()
		&& mousePos.Y >= getY() && mousePos.Y <= getY() + getHeight());
}