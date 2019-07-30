#include "ConsoleManager.h"

ConsoleManager* ConsoleManager::instance = 0;

ConsoleManager::ConsoleManager() {
	hInput = GetStdHandle(STD_INPUT_HANDLE);
	//GetConsoleMode(hInput, &mode);
	SetConsoleMode(hInput, ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT | ENABLE_EXTENDED_FLAGS);
	GetConsoleCursorInfo(hOutput, &cursorInfo);
	setCursorVisible(false);
}

ConsoleManager* ConsoleManager::getInstance() {
	if (instance == 0) {
		instance = new ConsoleManager();
	}
	return instance;
}

void ConsoleManager::addComponent(BaseComponent* component) {
	components.push_back(component);
}

void ConsoleManager::setMouseEnabled(bool isEnabled) {
	mode = (isEnabled) ? mode | ENABLE_MOUSE_INPUT : mode & ~ENABLE_MOUSE_INPUT;
	SetConsoleMode(hInput, mode);
}

void ConsoleManager::setCursorVisible(bool isVisible) {
	cursorInfo.bVisible = isVisible;
	SetConsoleCursorInfo(hOutput, &cursorInfo);
}

bool ConsoleManager::isIntersects(COORD mousePosition, BaseComponent* component) {

	return (mousePosition.X >= component->getX() && mousePosition.X <= component->getX() + component->getWidth()
		&& mousePosition.Y >= component->getY() && mousePosition.Y <= component->getY() + component->getHeight());
}

void ConsoleManager::listenToUserEvents() {

	INPUT_RECORD inputRecord[1] = { 0 };
	DWORD numRead;
	int counter = 0;

	setMouseEnabled(true);
	setCursorVisible(false);

	while (true) {
		ReadConsoleInput(hInput, inputRecord, 1, &numRead);
		//CONSOLE_SCREEN_BUFFER_INFO cursor;
		KEY_EVENT_RECORD key;
		//bool tabDown = false;

		if (numRead) {
			for (int i = 0; i < (int) numRead; i++) {
				switch (inputRecord[i].EventType) {
				case KEY_EVENT:
					key = inputRecord[i].Event.KeyEvent;
					if (key.bKeyDown) {
						switch (key.wVirtualKeyCode) {
						case VK_ESCAPE:
							return;

						default: 
							if (components.size() == 0) continue;
							for (auto component : components) {
								if (component->isFocused()) {
									component->onKeyPressed(key.wVirtualKeyCode);
								}
							}
						}
					}
				case MOUSE_EVENT:
					switch (inputRecord[i].Event.MouseEvent.dwButtonState) {
					case RI_MOUSE_LEFT_BUTTON_DOWN:
						setCursorVisible(false);
						COORD mousePosition = inputRecord[i].Event.MouseEvent.dwMousePosition;
						bool isIntersects = false;
						for (auto component : components) {
							if (component->isIntersects(mousePosition)) {
								component->onMouseClick(mousePosition);
							}
						}
					}
				}
			}
		}
	}
}