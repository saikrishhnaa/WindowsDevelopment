#pragma once

class ISum :public IUnknown
{
public:
	HRESULT __stdcall SumOfTwoIntegers(int, int, int*);
};

class ISubtract :public IUnknown
{
public:
	HRESULT __stdcall SubtractionOfTwoIntegers(int, int, int*);
};

// CLSID of SumSubtract Component {A35D4F8D-47DD-437a-B174-3F7EAA704F26}
const CLSID CLSID_SumSubtract = { 0xa35d4f8d, 0x47dd, 0x437a, 0xb1, 0x74, 0x3f, 0x7e, 0xaa, 0x70, 0x4f, 0x26 };

// {AEAF99B9-0519-4141-BE2C-FEE9A5467762}
const IID IID_ISum = { 0xaeaf99b9,0x519,0x4141,0xbe,0x2c,0xfe,0xe9,0xa5,0x46,0x77,0x62 };

// {D3687370-99C5-4504-9118-A2EAE798F7A5}
const IID IID_ISubtract = { 0xd3687370,0x99c5,0x4504,0x91,0x18,0xa2,0xea,0xe7,0x98,0xf7,0xa5 };