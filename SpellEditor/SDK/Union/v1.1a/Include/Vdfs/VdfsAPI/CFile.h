#pragma once

#include "CCache.h"

typedef int32 FILE_ERR;

class CFileBase
{
protected:
	FILE*		hFile;
	CCache*		pCache;
	CString		sName, sFullName;
	FILE_ERR	errLastError;

private:
			 CFileBase ();
	virtual ~CFileBase ();

public:
			virtual FILE_ERR	Open		()=0;
			virtual FILE_ERR	Close		()=0;
	VDFAPI	virtual uint32		Read		(char*, const int32&)=0;
	VDFAPI	virtual uint32		ReadEnd		(char*)=0;
	VDFAPI	virtual FILE_ERR	Seek		(const int32&)=0;
	VDFAPI	virtual uint32		Tell		()=0;
	VDFAPI	virtual bool32		IsVirtual	()=0;
	VDFAPI	virtual uint32		Sizeof		()=0;
					FILE_ERR	LastError	();
	VDFAPI 			CString		Name		();
	VDFAPI 			CString		FullName	();
};






class CFileVirtual : 
	public CFileBase
{
protected:
	struct
	{
		uint32 unOffset;
		uint32 unPos;
		uint32 unSizeof;
	} meta;

public:
	CFileVirtual (const CString&, FILE*, const uint32&, const uint32&);

			virtual FILE_ERR	Open		();
			virtual FILE_ERR	Close		();
	VDFAPI	virtual uint32		Read		(char*, const int32&);
	VDFAPI	virtual uint32		ReadEnd		(char*);
	VDFAPI	virtual FILE_ERR	Seek		(const int32&);
	VDFAPI	virtual uint32		Tell		();
	VDFAPI	virtual bool32		IsVirtual	();
	VDFAPI	virtual uint32		Sizeof		();

private:
	virtual ~CFileVirtual ();
};





class CFilePhysical : 
	public CFileBase
{
protected:
	struct
	{
		uint32  unRef;
		uint32  unPos;
		uint32  unSizeof;
	} meta;

public:
	CFilePhysical (const CString&);

			virtual	FILE_ERR	Open		();
			virtual	FILE_ERR	Close		();
	VDFAPI	virtual	uint32		Read		(char*, const int32&);
	VDFAPI	virtual	uint32		ReadEnd		(char*);
	VDFAPI	virtual	FILE_ERR	Seek		(const int32&);
	VDFAPI	virtual	uint32		Tell		();
	VDFAPI	virtual	bool32		IsVirtual	();
	VDFAPI	virtual	uint32		Sizeof		();
	VDFAPI 			bool		IsOpen		();

private:
	virtual ~CFilePhysical ();
};