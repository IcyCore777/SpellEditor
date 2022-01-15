#include <UnionAfx.h>

namespace SystemPack
{
	CGlossaryWord::CGlossaryWord(const Common::CString& keyName)
	{
		sKeyName = keyName;
	}

	Common::CString CGlossaryWord::GetKeyName()
	{
		return sKeyName;
	}

	CGlossaryWord::TWordInfo* CGlossaryWord::GetData(const uint32& langID)
	{
		for (uint32 i = 0; i < arrInfos.GetNum(); i++)
		{
			if( arrInfos[i]->ulLangIndex == langID )
				return arrInfos[i];
		}
		return Null;
	}

	void CGlossaryWord::SetData(const uint32& langID, const Common::CString& data)
	{
		for (uint32 i = 0; i < arrInfos.GetNum(); i++)
		{
			if( arrInfos[i]->ulLangIndex == langID )
				arrInfos[i]->sData = data;
		}
		TWordInfo* info		= new TWordInfo;
		info->ulLangIndex	= langID;
		info->sData			= data;
	}

	void CGlossaryWord::Merge(CGlossaryWord* word)
	{
		if( sKeyName == word->sKeyName )
		{
			for (uint32 i = 0; i < word->arrInfos.GetNum(); i++)
			{
				TWordInfo* langInfo = GetData( word->arrInfos[i]->ulLangIndex );
				if( !langInfo )
				{
					langInfo				= new TWordInfo;
					langInfo->ulLangIndex	= word->arrInfos[i]->ulLangIndex;
					langInfo->sData			= word->arrInfos[i]->sData;
					arrInfos.Insert( langInfo );
				}
			}
		}
	}







	void CGlossary::LoadGlossaries(const Common::CString& list)
	{
		uint32 offset = 0;
		for (uint32 i = 0;; i++)
		{
			Common::CString sFileName = list.GetWordEx(" \t", 1, offset, &offset);
			if( sFileName.IsEmpty() )
				break;
			CGlossary* glossary = new CGlossary;
			glossary->LoadFile( sFileName );
		}
	}

	static uint32 GetLangID(const Common::CString& langName)
	{
		if( langName.MatchesMask( sNumber_Integer ))
		{
			return langName.ToInt32();
		}
		if( langName == "RUS" )		return 0x0419;
		if( langName == "ENG" )		return 0x0C09;
		if( langName == "GER" )		return 0x0C07;
		if( langName == "POL" )		return 0x0415;
		if( langName == "ROU" )		return 0x0418;
		if( langName == "ITA" )		return 0x0410;
		if( langName == "CZE" )		return 0x0405;
		if( langName == "ESP" )		return 0x1034;
		return 0;
	}

	void CGlossary::LoadFile(const Common::CString& fileName)
	{
		Common::CString sSource;
		sSource.ReadFromVdf(fileName, VDF_VIRTUAL | VDF_PHYSICAL);
		Common::CDocument sDocument( sSource );

		for (uint32 i = 0; i < sDocument.GetNum(); i++)
		{
			if( sDocument[i].GetData().ShrinkFront().IsEmpty() )
				continue;

			Common::CString sKeyName	= sDocument[i].GetData().GetWord( ":", 1 ).Shrink();
			Common::CString sLangName	= sDocument[i].GetData().GetWord( ":", 2 ).Shrink();
			Common::CString sData		= sDocument[i].GetData().GetWord( ":", 3 );

			CGlossaryWord* word = new CGlossaryWord( sKeyName );
			word->SetData( GetLangID( sLangName ), sData );
			tblData.Push( word );
		}
	}

	CGlossaryWord* CGlossary::GetWord(const Common::CString& keyName)
	{
		return tblData.Get( keyName );
	}
	
	


}