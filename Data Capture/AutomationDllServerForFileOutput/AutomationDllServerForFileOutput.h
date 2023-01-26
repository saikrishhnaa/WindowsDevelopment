#pragma once
#include<string>
using namespace std;

class IAutomationFileWriter : public IDispatch
{
public:
	// pure virtual
	virtual HRESULT __stdcall WriteIntoFile(char[], char[]) = 0;
};

// {A5F85CE7-D53F-4c66-93D9-00743A87D188}
const CLSID CLSID_AutomationFileWriter = { 0xa5f85ce7, 0xd53f, 0x4c66, 0x93, 0xd9, 0x0, 0x74, 0x3a, 0x87, 0xd1, 0x88 };

// {F5BDE086-36D5-4d01-99B8-2D4882D90DB6}
const IID IID_IAutomationFileWriter = { 0xf5bde086, 0x36d5, 0x4d01, 0x99, 0xb8, 0x2d, 0x48, 0x82, 0xd9, 0xd, 0xb6 };
