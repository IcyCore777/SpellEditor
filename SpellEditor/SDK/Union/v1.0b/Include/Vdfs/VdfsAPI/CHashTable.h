#pragma once

class CFilterBase
{
public:
	virtual void		Push (CFileBase*)=0;
	virtual void		Pop	 (CFileBase*)=0;
	virtual CFileBase*	Get	 (CString&)=0;
	virtual void		Clear()=0;
};

class CHashTable : CFilterBase
{
	CArray <CFilterBase*> arrData;
	
public:
	virtual void		Push (CFileBase*);
	virtual void		Pop	 (CFileBase*);
	virtual CFileBase*	Get	 (CString&);
	virtual void		Clear();

	~CHashTable ();
};