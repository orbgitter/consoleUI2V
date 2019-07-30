#include "ComboBox.h"
const int HEIGHT_WHEN_CLOSED = 2;


ComboBox::ComboBox(vector<string> _op, string _selectionText, int _x, int _y, int w, BorderType bType, Color tColor, Color bColor)
	: BaseComponent(_x, _y, w, HEIGHT_WHEN_CLOSED, bType, tColor, bColor), options(_op), selectionText(_selectionText) {
}

bool ComboBox::isFocused() {
	return isOpened;
}

string ComboBox::getCurrentText() {
	return selectedIndex == -1 ? selectionText : options[selectedIndex];
}

void ComboBox::draw(){

	string text = getCurrentText();
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

	SetConsoleCursorPosition(out, {topLeftPoint.getX() + width - 1, topLeftPoint.getY() + 1 });
	std::cout << "\\/";
	isVisible = true;
}

void ComboBox::onMouseClick(COORD mousePos) {

	// Open comboBox
	if (isOpened) {
		// Detect if the click intersects the open-box
		if (isIntersectsWithOpenBox(mousePos)) {
			selectedIndex = (mousePos.Y - topLeftPoint.getY() - height - 1) % options.size();
			close();
			removeFromScreen();
			draw();
		}
	}
	else {
		open();
	}
}

bool ComboBox::isIntersects(COORD mousePos) {
	if (isOpened) {
		return isIntersectsWithOpenBox(mousePos);
	}
	return BaseComponent::isIntersects(mousePos);
}

bool ComboBox::isIntersectsWithOpenBox(COORD mousePos) {

	Point2D topLeftPoint(topLeftPoint.getX(), topLeftPoint.getY() + height);
	Point2D bottomRightPoint(topLeftPoint.getX() + width, topLeftPoint.getY() + height + options.size() - 1);

	return (mousePos.X >= topLeftPoint.getX() && mousePos.X <= bottomRightPoint.getX()
		&& mousePos.Y >= topLeftPoint.getY() && mousePos.Y < bottomRightPoint.getY());

}

void ComboBox::onKeyPressed(WORD key) {

	switch (key) {
	case VK_DOWN:
		if (selectedIndex == -1)
			selectedIndex = 0;
		else
			selectedIndex = ++selectedIndex % options.size();
		removeFromScreen();
		draw();
		open();

		break;
	case VK_UP:
		if (selectedIndex == -1)
			selectedIndex = 0;
		else
			selectedIndex = --selectedIndex < 0 ? selectedIndex + options.size() : selectedIndex % options.size();
		removeFromScreen();
		draw();
		open();
		break;
	case VK_SPACE:
	case VK_RETURN:
		close();
		removeFromScreen();
		draw();
		break;
	default:
		break;
	}
}

void ComboBox::open() {


	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
	applyColors();
	
	SetConsoleCursorPosition(out, { topLeftPoint.getX() + width - 1, topLeftPoint.getY() + 1 });
	std::cout << "/\\";
	
	COORD c = { topLeftPoint.getX(), topLeftPoint.getY() + height };
	SetConsoleCursorPosition(out, c);

	//string option = options[0];
	for (int currIndex = 0; currIndex < (int) options.size(); currIndex++) {
		
		string option = options[currIndex];

		// Print the left border
		c = { topLeftPoint.getX(), topLeftPoint.getY() + height + currIndex };
		SetConsoleCursorPosition(out, c);
		cout << borderCharacters.vertical;
		c = { c.X, c.Y + 1 };
		SetConsoleCursorPosition(out, c);
		cout << borderCharacters.vertical;
		c = { c.X, c.Y + 1 };
		SetConsoleCursorPosition(out, c);
		cout << borderCharacters.leftBottomCorner;

		// Print the right border
		c = { topLeftPoint.getX() + width + 1, topLeftPoint.getY() + height + currIndex };
		SetConsoleCursorPosition(out, c);
		cout << borderCharacters.vertical;
		c = { c.X, c.Y + 1 };
		SetConsoleCursorPosition(out, c);
		cout << borderCharacters.vertical;
		c = { c.X, c.Y + 1 };
		SetConsoleCursorPosition(out, c);
		cout << borderCharacters.rightBottomCorner;

		int text_len = static_cast<int>(option.length());
		if (currIndex == selectedIndex) {
			// print centered text and mark it
			invertColors();
			applyColors();

			// draw the background // TODO
			c = { topLeftPoint.getX() + 1, topLeftPoint.getY() + 3 + currIndex };
			SetConsoleCursorPosition(out, c);
			for (int i = 0; i < width; i++) {
				SetConsoleCursorPosition(out, c);
				cout << " ";
				c.X++;
			}

			// draw the text
			c = { topLeftPoint.getX() + 1 + width / 2 - text_len / 2, topLeftPoint.getY() + 3 + currIndex };
			SetConsoleCursorPosition(out, c);
			cout << option;

			invertColors();
			applyColors();
		}
		else {

			// draw the background
			c = { topLeftPoint.getX() + 1, topLeftPoint.getY() + 3 + currIndex };
			SetConsoleCursorPosition(out, c);
			for (int i = 0; i < width; i++) {
				SetConsoleCursorPosition(out, c);
				cout << " ";
				c.X++;
			}


			// print centered text
			c = { topLeftPoint.getX() + 1 + width / 2 - text_len / 2, topLeftPoint.getY() + 3 + currIndex };
			SetConsoleCursorPosition(out, c);
			cout << option;
		}

	}

	// Print the bottom border
	c = { topLeftPoint.getX() + 1, topLeftPoint.getY() + height + options.size() + 1 };
	for (int i = 0; i < width; i++) {
		SetConsoleCursorPosition(out, c);
		cout << borderCharacters.horizontal;
		c.X++;
	}

	isOpened = true;
}

void ComboBox::close() {

	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD c = { topLeftPoint.getX(), topLeftPoint.getY() + height + 1 };

	SetConsoleCursorPosition(out, c);
	SetConsoleTextAttribute(out, Black | FOREGROUND_INTENSITY | Black * 16);

	for (int i = 0; i <= height + 1; i++) {
		for (int j = 0; j <= width + 1; j++) {
			std::cout << " ";
		}
		++c.Y;
		SetConsoleCursorPosition(out, c);
	}

	isOpened = false;
}

int ComboBox::getSelectedIndex() const {
	return selectedIndex;
}

string ComboBox::getSelectedOption() const {
	return selectedIndex == -1 ? string() : options[selectedIndex];
}

void ComboBox::invertColors() {
	Color tmp = textColor;
	textColor = backgroundColor;
	backgroundColor = tmp;
}