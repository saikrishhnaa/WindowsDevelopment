#pragma once

class ISum : public IUnknown
{
	public:
		virtual HRESULT __stdcall SumOfTwoIntegers(int, int, int*) = 0; //must be used __stdcall in COM as per specification
};

class ISubstract : public IUnknown
{
	public:
		virtual HRESULT __stdcall SubtractionOfTwoIntegers(int, int, int*) = 0; //PASCAL calling conv (parameter right to left) - stdcall, __ vendor specific _ compile , 
};

// {5C605C63-2FFA-4406-B7D9-93ABB4E0A680}
const CLSID CLSID_SumSubstract = { 0x5c605c63, 0x2ffa, 0x4406, 0xb7, 0xd9, 0x93, 0xab, 0xb4, 0xe0, 0xa6, 0x80 }; //CLSID, IID typedef of GUID which is type of UUID

// {BDBF38C7-6BC2-45be-8354-D1A1577403A8}
const IID IID_ISum = { 0xbdbf38c7, 0x6bc2, 0x45be, 0x83, 0x54, 0xd1, 0xa1, 0x57, 0x74, 0x3, 0xa8 };

// {CB1D61C3-C73F-4769-8574-A36ED04077F4}
const IID IID_ISubstract = { 0xcb1d61c3, 0xc73f, 0x4769, 0x85, 0x74, 0xa3, 0x6e, 0xd0, 0x40, 0x77, 0xf4 };
