/*
Compile: cl.exe /c /EHsc /ZW Hello.cpp

Link: link.exe Hello.obj vccorlib.lib runtimeobject.lib /SUBSYSTEM:CONSOLE
*/

#include <iostream>

using namespace std;
using namespace Platform;

int main(Array<String^>^ args)
{
	// Code
	String^ str = "Hello World!!!";
	wcout << str->Data() << endl;
	return(0);
}
