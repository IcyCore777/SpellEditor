#include <UnionAfx.h>

namespace SystemPack
{
	
	// ====================================
	CFirstSymbolFilter::CFirstSymbolFilter (const char& sym)
	{
		symbol = sym;
	}

	void CFirstSymbolFilter::Push (CGlossaryWord* word)
	{
		for (uint32 i = 0; i < arrData.GetNum(); i++)
		{
			if(arrData[i]->GetKeyName() == word->GetKeyName())
			{
				arrData[i]->Merge(word);
				return;
			}
		}
		arrData.Insert(word);
	}

	void CFirstSymbolFilter::Pop (CGlossaryWord* word)
	{
		if (!arrData.GetNum())
			return;

		arrData.FastRemove(word);
	}

	CGlossaryWord* CFirstSymbolFilter::Get (const Common::CString& name)
	{
		if (!arrData.GetNum())
			return Null;

		for (uint32 i = 0; i < arrData.GetNum(); i++)
			if (arrData[i]->GetKeyName() == name)
				return arrData[i];
		return Null;
	}

	CGlossaryWord* CFirstSymbolFilter::Get (uint32 idx)
	{
		if (idx > arrData.GetNum())
			return Null;
		return arrData[idx];
	}

	uint32 CFirstSymbolFilter::Num ()
	{
		return arrData.GetNum();
	}

	void CFirstSymbolFilter::Clear ()
	{
		arrData.Clear ();
	}

	CFirstSymbolFilter::~CFirstSymbolFilter ()
	{
		Clear ();
	}



	// ====================================
	CLengthFilter::CLengthFilter (const uint32& len)
	{
		length = len;
	}

	void CLengthFilter::Push (CGlossaryWord* word)
	{
		const char& sym = toupper(word->GetKeyName()[0]);
		for (uint32 i = 0; i < arrData.GetNum(); i++)
			if (arrData[i]->symbol == sym)
				return arrData[i]->Push (word);

		CFirstSymbolFilter* filter = new CFirstSymbolFilter (sym);
		arrData.Insert (filter);
		filter->Push (word);
	}

	void CLengthFilter::Pop (CGlossaryWord* word)
	{
		if (!arrData.GetNum())
			return;

		const char& sym = toupper(word->GetKeyName()[0]);
		for (uint32 i = 0; i < arrData.GetNum(); i++)
			if (arrData[i]->symbol == sym)
				return arrData[i]->Pop (word);
	}

	CGlossaryWord* CLengthFilter::Get (const Common::CString& name)
	{
		if (!arrData.GetNum())
			return Null;

		const char& sym = toupper(name[0]);
		for (uint32 i = 0; i < arrData.GetNum(); i++)
			if (arrData[i]->symbol == sym)
				return arrData[i]->Get(name);
		return Null;
	}

	CGlossaryWord* CLengthFilter::Get (uint32 idx)
	{
		uint32 sum = 0;
		for (uint32 i = 0; i < arrData.GetNum(); i++)
		{
			uint32 num = arrData[i]->Num();
			if (sum + num > idx)
				return arrData[i]->Get(idx - sum);
			sum += num;
		}
		return Null;
	}

	uint32 CLengthFilter::Num ()
	{
		uint32 sum = 0;
		for (uint32 i = 0; i < arrData.GetNum(); i++)
			sum += arrData[i]->Num();
		return sum;
	}

	void CLengthFilter::Clear ()
	{
		for (uint32 i = 0; i < arrData.GetNum(); i++)
			arrData[i]->Clear ();
		arrData.DeleteData ();
	}

	uint32 CLengthFilter::GetLength()
	{
		return length;
	}

	CLengthFilter::~CLengthFilter ()
	{
		Clear ();
	}





	// ====================================
	void CHashTable::Push (CGlossaryWord* word)
	{
		// поиск в таблице следующего подуровн€ 
		// с подход€щим ассоциативным свойством. 
		// в данном примере - расширение файла.
		for (uint32 i = 0; i < arrData.GetNum(); i++)
			if (arrData[i]->GetLength() == word->GetKeyName().Length())
				return arrData[i]->Push (word);
	
		// при отсутствии ассоциации, создаем 
		// новый экземпл€р с указанным свойством
		CLengthFilter* filter = new CLengthFilter(word->GetKeyName().Length());
		arrData.Insert (filter);
		filter->Push (word);
	}

	void CHashTable::Pop (CGlossaryWord* word)
	{
		if (!arrData.GetNum())
			return;

		// поиск в таблице следующего подуровн€ 
		// с подход€щим ассоциативным свойством.
		// найденый подуровень по аналогии обработает 
		// файл и отправит его дальше
		for (uint32 i = 0; i < arrData.GetNum(); i++)
			if (arrData[i]->GetLength() == word->GetKeyName().Length())
				return arrData[i]->Pop (word);
	}

	CGlossaryWord* CHashTable::Get (const Common::CString& name)
	{
		// при отсутствии файлов 
		// смело возвращаем нуль
		if (!arrData.GetNum())
			return Null;
	
		// поиск в таблице следующего подуровн€ 
		// с подход€щим ассоциативным свойством.
		// если файл будет найдет в подуровн€х ниже, 
		// он автоматически вернет значение в 
		// запрашиваемую функцию.
		Common::CString ext = name.GetWord( ".", -1 ).ToChar();
		for (uint32 i = 0; i < arrData.GetNum(); i++)
			if (arrData[i]->GetLength() == name.Length())
				return arrData[i]->Get(name);
	
		// при отсутствии ассоциаций
		// также возвращаем нуль
		return Null;
	}

	CGlossaryWord* CHashTable::Get (uint32 idx)
	{
		uint32 sum = 0;
		for (uint32 i = 0; i < arrData.GetNum(); i++)
		{
			uint32 num = arrData[i]->Num();
			if (sum + num > idx)
				return arrData[i]->Get(idx - sum);
			sum += num;
		}
		return Null;
	}

	uint32 CHashTable::Num ()
	{
		uint32 sum = 0;
		for (uint32 i = 0; i < arrData.GetNum(); i++)
			sum += arrData[i]->Num();
		return sum;
	}

	void CHashTable::Clear ()
	{
		// отправл€ем запросы очистки 
		// данных подуровн€м ниже
		for (uint32 i = 0; i < arrData.GetNum(); i++)
			arrData[i]->Clear ();

		// удал€ем все данные таблиц
		arrData.DeleteData ();
	}

	CHashTable::~CHashTable ()
	{
		Clear ();
	}
};