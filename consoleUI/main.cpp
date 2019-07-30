#include "Label.h"
#include "ComboBox.h"
#include "ConsoleManager.h"
int main(int argc, char** argv)
{

	vector<string> strings;
	strings.push_back("Maserati");
	strings.push_back("Ferrari");
	strings.push_back("Porsche");

	 /*BaseComponent* label = new Label("Hello", 5, 5, 20, 2, Solid, Green, Black);*/ 
	BaseComponent* comboBox = new ComboBox(strings, "Please select a car", 5, 5, 30, Solid, Red, Black);
	comboBox->draw();
	/*label->draw();*/
	//Sleep(3000);

	//label->setBackgroundColor(Cyan);


	ConsoleManager* consoleManager = ConsoleManager::getInstance();

	consoleManager->addComponent(comboBox);

	consoleManager->listenToUserEvents();

	//while (1);
	delete comboBox;
	//delete label;
}