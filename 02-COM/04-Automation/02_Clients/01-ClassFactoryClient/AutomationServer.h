#pragma once

class IMyMath :public IDispatch
{
public:
	// pure virtual
	virtual HRESULT __stdcall SumOfTwoIntegers(int, int, int*) = 0;

	// pure virtual 
	virtual HRESULT __stdcall SubtractionOfTwoIntegers(int, int, int*) = 0;
};

// CLSID of MyMath Component : {35DE3040-99A6-434f-9EFD-EBD413476C9D}
const CLSID CLSID_MyMath = { 0x35de3040, 0x99a6, 0x434f, 0x9e, 0xfd, 0xeb, 0xd4, 0x13, 0x47, 0x6c, 0x9d };

// IID of IMyMath Interface : {047E6749-E548-4f2a-BABC-9C3DE5D40505}
const IID IID_IMyMath = { 0x47e6749, 0xe548, 0x4f2a, 0xba, 0xbc, 0x9c, 0x3d, 0xe5, 0xd4, 0x5, 0x5 };
