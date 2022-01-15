#pragma once

namespace SystemPack
{
	typedef Common::CArray<CPatchType*> TParameters;

	class ASTAPI CPatchFunction : public CPatchSymbol
	{
	protected:
				TParameters	arrParameters;
	public:
				void		PushParameter(CPatchType* sym);
				void		CreateParameters(const Common::CString& line);
		virtual	CPatchType*	Execute()=0;
		~CPatchFunction();
	};
}

#include "BaseFunctions\BaseFunctions.h"