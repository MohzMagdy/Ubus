
#include "UI.h"

#include <iostream>
#include <conio.h>
#include <chrono>
#include <thread>

using namespace std;

UI::UI() {
	ApplicationMode = Mode::Interactive;
	setMode();

}

void UI::setMode() {
	int modeNum = -1;
	cout << "------------------------------------------" << endl;
	cout << "Please Choose Your Interface Mode: \n [1] For Interactive Mode \n [2] For Step-By-Step \n [3] For Silent Mode \n [4] For Immediate Passenger Ride"<<endl;
	cout << "------------------------------------------" << endl;
	cin >> modeNum;
	while (modeNum > 4 || modeNum < 1) {
		cout << "Please Enter A Valid Number: " << endl;
		cin >> modeNum;
	}
	switch (modeNum) {
		case 1:
			ApplicationMode = Mode::Interactive;
			break;
		case 2:
			ApplicationMode = Mode::Step;
			break;
		case 3:
			ApplicationMode = Mode::Silent;
			break;
		case 4:
			ApplicationMode = Mode::Immediate;
			break;
		default:
			ApplicationMode = Mode::Silent;
			break;
	}
}

Mode UI::GetCurrentMode()const {
	return ApplicationMode;
}

void UI::printMessage(string Message) const {
	if (ApplicationMode == Mode::Interactive || ApplicationMode == Mode::Immediate) {
		IntercativeModeOutput(Message);
	}
	if (ApplicationMode == Mode::Step) {
		StepByStepModeOutput(Message);
	}
}

void UI::IntercativeModeOutput(string Message) const {
	cout << Message << endl;
	_getch();
}

void UI::StepByStepModeOutput(string Message) const {
	cout << Message << endl;
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
}