// Supported with union (c) 2018 Union team

#ifndef __ZFILE3D_H__VER3__
#define __ZFILE3D_H__VER3__

#include "z3d.h"
#include "zDisk.h"
#include <assert.h>

namespace Gothic_II_Addon {

  class zCFile3DS {
  public:

    zCFile3DS() {}
    void Load3DS( zSTRING const&, zCMesh* ) zCall( 0x0055D660 );
    void Save3DS( zSTRING const&, zCMesh* ) zCall( 0x0055F010 );
  };

  class zCFileQuakeBSP {
  public:
    zFILE* file;

    void zCFileQuakeBSP_OnInit()                           zCall( 0x00560BE0 );
    zCFileQuakeBSP()                                       zInit( zCFileQuakeBSP_OnInit() );
    ~zCFileQuakeBSP()                                      zCall( 0x00560BF0 );
    void LoadQuakeBSP( zSTRING const&, zCMesh*, zCWorld* ) zCall( 0x00560C10 );
  };

  class zCFileBIN {
  public:
    int lastStart;
    int nextStart;
    int externalFile;
    zFILE* file;
	zCFileBIN(const zSTRING& fname);
    void zCFileBIN_OnInit()               zCall( 0x00567F50 );
    zCFileBIN()                           zInit( zCFileBIN_OnInit() );
    ~zCFileBIN()                          zCall( 0x00567F70 );


	BOOL	BinEof() { assert(file); return (nextStart >= file->Size()); }			// ??
	BOOL	BinExists() { assert(file); return file->Exists(); };
	void	BinOpen(const zSTRING& name = "");
	void	BinClose() { BinEndChunk(); if (!externalFile) { file->Close(); delete file; }; file = 0; };
	void	BinWrite(const void* ptr, const int num) { assert(file); file->Write(ptr, num); };
	void	BinWriteFloat(const float  f) { assert(file); file->Write(&f, sizeof(f)); };
	void	BinWriteInt(const int    f) { assert(file); file->Write(&f, sizeof(f)); };
	void	BinWriteDWord(const DWORD f) { assert(file); file->Write(&f, sizeof(f)); };
	void	BinWriteWord(const WORD  f) { assert(file); file->Write(&f, sizeof(f)); };
	void	BinWriteByte(const BYTE  f) { assert(file); file->Write(&f, sizeof(f)); };
	void	BinWriteString(const zSTRING& s) { assert(file); file->Write(s + "\n"); };
	void	BinSetFile(zFILE* inFile) { file = inFile; lastStart = nextStart = -1; externalFile = TRUE; };
	void	BinRead(void* ptr, const int num) { assert(file); file->Read(ptr, num); };
	void	BinReadFloat(float   &f) { assert(file); file->Read(&f, sizeof(f)); };
	void	BinReadInt(int     &f) { assert(file); file->Read(&f, sizeof(f)); };
	void	BinReadDWord(DWORD  &f) { assert(file); file->Read(&f, sizeof(f)); };
	void	BinReadWord(WORD   &f) { assert(file); file->Read(&f, sizeof(f)); };
	void	BinReadByte(BYTE   &f) { assert(file); file->Read(&f, sizeof(f)); };
	void	BinReadString(zSTRING &f) { assert(file); file->Read(f); };
	void	BinOpenChunk(WORD& id, LONG& len)
	{
		if (file == 0) return;
		file->Read(&id, sizeof(id));
		if (file->Eof()) { id = 0; return; };
		file->Read(&len, sizeof(len));
		int actPos = file->Pos();
		nextStart = actPos + len;
	};
	void	BinSkipChunk()
	{
		if (file == 0) return;
		if (nextStart >= file->Size()) return;
		file->Seek(nextStart);
	};
	BOOL	BinSeekChunk(const WORD id)
	{
		if (file == 0) return FALSE;
		WORD fid;
		LONG flen;
		BinOpenChunk(fid, flen);
		while ((!file->Eof()) && (fid != id))
		{
			BinSkipChunk();
			BinOpenChunk(fid, flen);
		};
		return ((fid == id) && (!file->Eof()));
	};
	// write
	void	BinCreate(const zSTRING& name) zCall(0x00567FF0);

	void	BinStartChunk(const WORD id)
	{
		if (file == 0) return;
		// close last chunk: write len
		if (lastStart != -1) {
			int actPos = file->Pos();
			int len = actPos - lastStart - 6; //6
			file->Seek(lastStart + sizeof(id));
			file->Write(&len, sizeof(len));
			file->Seek(actPos);
		};
		// write header-frame for new chunk
		LONG len = 0;
		lastStart = file->Pos();
		file->Write(&id, sizeof(id));
		file->Write(&len, sizeof(len));
	};

	void	BinEndChunk()
	{
		// close last chunk: write len
		// 'lastStart' ist nur im WriteMode !=-1 !
		if (lastStart != -1)
		{
			int actPos = file->Pos();
			int len = actPos - lastStart - 6; //6
			file->Seek(lastStart + sizeof(WORD));
			file->Write(&len, sizeof(len));
			file->Seek(actPos);
		};
	};
  };

} // namespace Gothic_II_Addon

#endif // __ZFILE3D_H__VER3__