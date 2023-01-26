#pragma once

#include<string>
using namespace std;

class IFileOutput : public IUnknown
{
public:
	// IFileOutput specific method declarations pure virtual
	virtual HRESULT __stdcall WriteIntoFile(char*, char*) = 0;
};

// {15D4BAB6-8852-489c-9F48-12394E350B3E}
const CLSID CLSID_FileOutput = { 0x15d4bab6, 0x8852, 0x489c, 0x9f, 0x48, 0x12, 0x39, 0x4e, 0x35, 0xb, 0x3e };

// {70CBC695-56C8-49e6-B0E1-A9B198F54E02}
const CLSID CLSID_FileWriter = { 0x70cbc695, 0x56c8, 0x49e6, 0xb0, 0xe1, 0xa9, 0xb1, 0x98, 0xf5, 0x4e, 0x2 };

// {FDD99E9F-A83A-47a7-8BAC-DD2362796B07}
const IID IID_IFileOutput = { 0xfdd99e9f, 0xa83a, 0x47a7, 0x8b, 0xac, 0xdd, 0x23, 0x62, 0x79, 0x6b, 0x7 };
