#ifndef CONSOLE_MANAGER_H
#define CONSOLE_MANAGER_H

#include <vector>
#include <Windows.h>
#include <algorithm>
#include "BaseComponent.h"

using namespace std;

class ConsoleManager
{
private:

	// Windows STD Handlers
	HANDLE hOutput;
	HANDLE hInput;
	DWORD mode;
	WORD attr;
	CONSOLE_CURSOR_INFO cursorInfo;

	Color defaultTextColor = White, defaultBackgroundColor = Black;


	std::vector<BaseComponent*> components;
	ConsoleManager();
	static ConsoleManager* instance;

public:
	static ConsoleManager* getInstance();

	void addComponent(BaseComponent* component);
	void listenToUserEvents();

	// Setters
	void setMouseEnabled(bool isEnabled);
	void setCursorVisible(bool isVisible);

	bool isIntersects(COORD mousePosition, BaseComponent* component);
};

#endif