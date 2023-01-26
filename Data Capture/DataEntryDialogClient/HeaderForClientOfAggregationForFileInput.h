class IFileReader : public IUnknown
{
public:
	// IFileInput specific method declaration pure virtual
	virtual HRESULT __stdcall ReadFromFile(char path[], char data[]) = 0;
};

// {0E728716-C829-4eb3-BE55-625E327C503B}
const IID IID_IFileReader = { 0xe728716, 0xc829, 0x4eb3, 0xbe, 0x55, 0x62, 0x5e, 0x32, 0x7c, 0x50, 0x3b };

// {DBD576C7-807F-47de-A418-55CC38474280}
const CLSID CLSID_FileReader = { 0xdbd576c7, 0x807f, 0x47de, 0xa4, 0x18, 0x55, 0xcc, 0x38, 0x47, 0x42, 0x80 };
