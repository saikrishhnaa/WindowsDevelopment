#pragma once

class IMultiplication :public IUnknown
{
public:
	// IMultiplication specific method declaration pure virtual
	virtual HRESULT __stdcall MultiplicationOfTwoIntegers(int, int, int*) = 0;
};

class IDivision :public IUnknown
{
public: 
	// IDivision specific method declaration pure virtual
	virtual HRESULT __stdcall DivisionOfTwoIntegers(int, int, int*) = 0;
};

class ISum :public IUnknown
{
public:
	// ISum specific method declaration pure virtual
	virtual HRESULT __stdcall SumOfTwoIntegers(int, int, int*) = 0;
};

class ISubtract :public IUnknown
{
public:
	// ISubtract specific method declaration pure virtual
	virtual HRESULT __stdcall SubtractionOfTwoIntegers(int, int, int*) = 0;
};

// CLSID of MultiplicationDivision Component - {249477C9-92A4-4559-BDA3-55D7F5E7E15A}
const CLSID CLSID_MultiplicationDivision = { 0x249477c9, 0x92a4, 0x4559, 0xbd, 0xa3, 0x55, 0xd7, 0xf5, 0xe7, 0xe1, 0x5a };

// IID of IMultiplication Interface - {B8290B44-0470-4aa3-84AF-1126ED4A2D49}
const IID IID_IMultiplication = { 0xb8290b44, 0x470, 0x4aa3, 0x84, 0xaf, 0x11, 0x26, 0xed, 0x4a, 0x2d, 0x49 };

// IID of IDivision Interface - {67A6093F-9450-4970-80E5-406D4DED2E0B}
const IID IID_IDivision = { 0x67a6093f, 0x9450, 0x4970, 0x80, 0xe5, 0x40, 0x6d, 0x4d, 0xed, 0x2e, 0xb };

// CLSID of SumSubtract Component {A35D4F8D-47DD-437a-B174-3F7EAA704F26}
const CLSID CLSID_SumSubtract = { 0xa35d4f8d, 0x47dd, 0x437a, 0xb1, 0x74, 0x3f, 0x7e, 0xaa, 0x70, 0x4f, 0x26 };

// {AEAF99B9-0519-4141-BE2C-FEE9A5467762}
const IID IID_ISum = { 0xaeaf99b9,0x519,0x4141,0xbe,0x2c,0xfe,0xe9,0xa5,0x46,0x77,0x62 };

// {D3687370-99C5-4504-9118-A2EAE798F7A5}
const IID IID_ISubtract = { 0xd3687370,0x99c5,0x4504,0x91,0x18,0xa2,0xea,0xe7,0x98,0xf7,0xa5 };
