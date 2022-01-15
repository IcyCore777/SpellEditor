#include <UnionAfx.h>

#define swsepar " \t\n\r"

namespace SystemPack
{
	CString CPatch::sLastFile	= "";
	CString CPatch::sLastRegion	= "";
	uint32  CPatch::ulLastLine	= None;

	void CPatch::Init (CString fileName)
	{
		sFileName = fileName;

		char fullname[1024];
		if (!vdf_searchfile((char*)fileName.GetVector(), fullname))
			return Say::Warning(fileName + " not found.", "Union::SystemPack");

		if (!vdf_fexists (fullname, VDF_VIRTUAL | VDF_PHYSICAL))
			return Say::Warning(fileName + " does not exists.", "Union::SystemPack");
		
		int32 unHandle = vdf_fopen (fullname, VDF_VIRTUAL | VDF_PHYSICAL);
		if (unHandle == Invalid)
			return Say::Warning(fileName + " is invalid.", "Union::SystemPack");

		int32	unSizeof = vdf_ffilesize	(unHandle);
		text	hData	 = (text)shi_malloc	(unSizeof);

		vdf_fread  (unHandle, _rcast(HBuffer, hData), unSizeof);
		vdf_fclose (unHandle);

		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

		CString sFileSrc = hData;
		shi_free (hData);

		while (true)
		{
			uint32 idx1 = sFileSrc.Search("/*");
			if (idx1 != Invalid) {
				uint32 idx2 = sFileSrc.Search("*/") + 2;
				if (idx1 != Invalid) {
					sFileSrc.Cut(idx1, idx2 - idx1);
					continue;
				}
				return; // error
			}
			break;
		}

		CDocument sFile (sFileSrc);

		for (uint32 i = 0; i < sFile.GetNum(); i++)
		{
			if (sFile[i].GetData().HasWord("//"))
				sFile[i].GetData() = sFile[i].GetData().GetPattern("", "//");
			sFile[i].GetData().Shrink();
			if (sFile[i].GetData().IsEmpty()) {
				sFile.RemoveLinesAt(i--);
				continue;
			}
		}

		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

		uint32 uStartRegion	= Invalid;
		uint32 uEndRegion	= Invalid;
		
		for (uint32 i = 0; i < sFile.GetNum(); i++) 
		{
			if (sFile[i].GetData().GetWord(swsepar).CompareI("#engine")) 
			{
				CString sHash = sFile[i].GetData().GetPattern("[", "]");
				if (!sHash.IsEmpty() && Union.GetGothicHash() == sHash.ToInt32(16)) 
				{
					uStartRegion = i + 1;
					for (uint32 j = i; j < sFile.GetNum(); j++) 
					{
						if (sFile[j].GetData().GetWord(swsepar).CompareI("#/engine")) 
						{
							uEndRegion = j - 1;
							break;
						}
					}
					break;
				}
			}
		}

		if (uStartRegion == Invalid || uEndRegion == Invalid)
			return;

		CDocument sEngineRegion;
		for (uint32 i = uStartRegion; i <= uEndRegion; i++)
			sEngineRegion.InsertLines( sFile[i] );
		sFile.Clear();

		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

		for (uint32 i = 0; i < sEngineRegion.GetNum(); i++) 
		{
			CString sLine = sEngineRegion[i];
			if (sLine.GetWord(swsepar).CompareI("#patch")) 
			{
				uint32 uPatchStart	= i + 1;
				uint32 uPatchEnd	= Invalid;

				CString sPatchName = sLine.GetPattern("[", "]");

				for (; i < sEngineRegion.GetNum(); i++) 
				{
					CString sLine = sEngineRegion[i];
					if (sLine.GetWord(swsepar).CompareI("#/patch"))
					{
						uPatchEnd = i - 1;
						break;
					}
				}
				if (uPatchEnd == Invalid)
					return;

				CPatchRegion* patch = new CPatchRegion(sPatchName, this);
				for (uint32 j = uPatchStart; j <= uPatchEnd; j++)
					patch->PushCommand (sEngineRegion[j]);
				arrPatches.Insert(patch);
			}
		}
		
		sLastFile = fileName;
		for (uint32 i = 0; i < arrPatches.GetNum(); i++)
			arrPatches[i]->Execute();
		

	}
}