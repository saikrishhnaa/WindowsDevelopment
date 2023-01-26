#pragma once

#include<string>

using namespace std;

class IFileInput : public IUnknown {
public:
	virtual HRESULT __stdcall ReadDataFromFile(string, string &) = 0;
};

// {A24C5F00-1A02-44b8-8E47-302ABF24FCC6}
const CLSID CLSID_FileInput = { 0xa24c5f00, 0x1a02, 0x44b8, 0x8e, 0x47, 0x30, 0x2a, 0xbf, 0x24, 0xfc, 0xc6 };

// {0B7A1DCC-6DC6-4ad8-B8C5-72CA3279A42F}
const IID IID_IFileInput = { 0xb7a1dcc, 0x6dc6, 0x4ad8, 0xb8, 0xc5, 0x72, 0xca, 0x32, 0x79, 0xa4, 0x2f };
