/* Command to compile : cl.exe /clr Hybrid.cpp ('/clr' switch introduced in cl.exe version 13 and above)*/

#include<stdio.h>
#using<mscorlib.dll>
using namespace System;

int main(void)
{
	printf("This line is from native cpp.\n");
	Console::WriteLine("This line is from Dot net managed c++.");
	return 0;
}
