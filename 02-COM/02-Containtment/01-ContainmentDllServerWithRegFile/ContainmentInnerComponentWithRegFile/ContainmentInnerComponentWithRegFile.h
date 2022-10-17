#pragma once

class IMultiplication :public IUnknown {
public:
	//IMultiplication specific method declarations pure virtual
	virtual HRESULT __stdcall MultiplicationOfTwoIntegers(int, int, int*) = 0;
};

class IDivision :public IUnknown {
public:
	//IDivision specific method declarations pure virtual
	virtual HRESULT __stdcall DivisionOfTwoIntegers(int, int, int*) = 0;
};

// {066C297E-6927-44f9-8838-E47F2900B571}
const CLSID CLSID_MultiplicationDivision = { 0x66c297e, 0x6927, 0x44f9, 0x88, 0x38, 0xe4, 0x7f, 0x29, 0x0, 0xb5, 0x71 };

// {B8290B44-0470-4aa3-84AF-1126ED4A2D49}
const IID IID_IMultiplication = { 0xb8290b44, 0x470, 0x4aa3, 0x84, 0xaf, 0x11, 0x26, 0xed, 0x4a, 0x2d, 0x49 };

// {67A6093F-9450-4970-80E5-406D4DED2E0B}
const IID IID_IDivision = { 0x67a6093f, 0x9450, 0x4970, 0x80, 0xe5, 0x40, 0x6d, 0x4d, 0xed, 0x2e, 0xb };