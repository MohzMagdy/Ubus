#pragma once
#include "Defs.h"

#include <string>
#include <iostream>

using namespace std;

class UI {
private:
	Mode ApplicationMode;
	
public:
	UI();
	void setMode();
	Mode GetCurrentMode() const;
	void printMessage(string message) const;
	void IntercativeModeOutput(string message) const;
	void StepByStepModeOutput(string message) const;


};