#pragma once

namespace SystemPack
{
	class CPatchStack;
	class ASTAPI CPatchOperator : public CPatchSymbol
	{
		friend class CPatchStack;

		CString		 sOperator;
		CPatchStack* pOnStack;

		PATCH_CLASS_DECLARATION(CPatchOperator);
	public:
				void		Init		(const CString& opName);
				CString		GetOperator	();
		virtual	CPatchType*	Execute		();
	};
}