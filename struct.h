

typedef char			CHAR;
typedef unsigned char 	UCHAR;
typedef unsigned char	BYTE;

typedef unsigned int	WORD;

typedef int 	       	INT;
typedef unsigned int   	UINT;

typedef long           	LONG;
typedef unsigned long   ULONG;
typedef unsigned long  	DWORD;

union _WB {
	WORD	w;
	BYTE	b[2];
};

union _FDWB {
	float	f;
	DWORD	dw;
	WORD	w[2];
	BYTE	b[4];
};


//-----------------
//структуры обмена с пк
//-------------------
struct _Status_SL{
	BYTE NRange1;
	BYTE Data1_Lo;
	BYTE Data1_Hi;	
	BYTE NRange2;
	BYTE Data2_Lo;
	BYTE Data2_Hi;	
	BYTE NRange3;
	BYTE Data3_Lo;
	BYTE Data3_Hi;	
	BYTE NRange4;
	BYTE Data4_Lo;	
	BYTE Data4_Hi;
		
};

struct _Status_Rele_SL{
	BYTE Canal_1;
	BYTE Canal_2;
	BYTE Canal_3;
	BYTE Canal_4;	
};




