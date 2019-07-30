#ifndef COMBOBOX_H
#define COMBOBOX_H

#include <vector>
#include <string>
#include <iostream>
#include <Windows.h>

#include "BaseComponent.h"

using namespace std;

class ComboBox : public BaseComponent {
private:

	int selectedIndex = -1;
	vector<string> options;
	string selectionText;
	bool isOpened = false;

	void open();
	void close();

	bool isFocused();
	bool isIntersects(COORD mousePos);
	bool isIntersectsWithOpenBox(COORD mousePos);
	void invertColors();
	string getCurrentText();
	
public:
	ComboBox(vector<string> _op, string _selectionText, int _x, int _y, int w, BorderType bType = None, Color tColor = Black, Color bColor = White);
	void draw();
	void onMouseClick(COORD mousePos);
	void onKeyPressed(WORD key);

	int getSelectedIndex() const;
	string getSelectedOption() const;
};

#endif