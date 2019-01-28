#include "InputInterfaces.h"
#include <string>


class KeyboardHandler:public IKeyboardHandler 
{
	bool VOnKeyDown(unsigned int const kcode)
	{
		std::string temp;
		temp = std::to_string(kcode);
		OutputDebugStringA(temp.c_str());
		return true;
	}

	bool VOnKeyUp(unsigned int const kcode)
	{
		return true;
	}

};