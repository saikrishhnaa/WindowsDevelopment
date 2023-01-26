#pragma once

#include<string>
using namespace std;

class IFileOutput: public IUnknown 
{
public:
	// IFileOutput specific method declarations pure virtual
	virtual HRESULT __stdcall WriteIntoFile(string path, string data) = 0;
};

// {15D4BAB6-8852-489c-9F48-12394E350B3E}
const CLSID CLSID_FileOutput = { 0x15d4bab6, 0x8852, 0x489c, 0x9f, 0x48, 0x12, 0x39, 0x4e, 0x35, 0xb, 0x3e };

// {FDD99E9F-A83A-47a7-8BAC-DD2362796B07}
const IID IID_IFileOutput = { 0xfdd99e9f, 0xa83a, 0x47a7, 0x8b, 0xac, 0xdd, 0x23, 0x62, 0x79, 0x6b, 0x7 };
