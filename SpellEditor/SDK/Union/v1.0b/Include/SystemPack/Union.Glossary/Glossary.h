#pragma once

namespace SystemPack
{
	class CGlossaryWord
	{
		struct TWordInfo
		{
			uint32	ulLangIndex;
			Common::CString	sData;
		};
		Common::CString sKeyName;
		Common::CArray<TWordInfo*> arrInfos;
	public:
		CGlossaryWord(const Common::CString& keyName);

		Common::CString		GetKeyName	();
		TWordInfo*	GetData		(const uint32& langID);
		void		SetData		(const uint32& langID, const Common::CString& data);
		void		Merge		(CGlossaryWord* word);
	};
};

#include "HashTable\HashTable.h"

namespace SystemPack
{
	class CGlossary
	{
		CHashTable tblData;
	public:
		static void LoadGlossaries(const Common::CString& list);

		void			LoadFile(const Common::CString& fileName);
		CGlossaryWord*	GetWord	(const Common::CString& keyName);
	};
}