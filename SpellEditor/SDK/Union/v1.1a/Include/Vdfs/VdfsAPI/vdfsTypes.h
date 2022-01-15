#pragma once

typedef struct _tagVdfstamp
{
	uint32	unSec	: 5;
	uint32	unMin	: 6;
	uint32	unHour	: 5;
	uint32	unDay	: 5;
	uint32	unMonth	: 4;
	uint32	unYear	: 7;

	operator uint32& () {
		return *reinterpret_cast <uint32*> (this);
	}

} VDFTIMESTAMP;

typedef struct _tagVdfheader
{
	char			cComment	[256];
	char			s0			[16];
	uint32			NumOfAllDatas;
	uint32			NumOfFiles;
	VDFTIMESTAMP	Timestamp;
	uint32			Sizeof;
	uint32			BinOffset;
	uint32			s1;

} VDFHEADER;



#define VDF_VIRTUAL        (1)
#define VDF_PHYSICAL       (2)
#define VDF_PHYSICALFIRST  (4)

