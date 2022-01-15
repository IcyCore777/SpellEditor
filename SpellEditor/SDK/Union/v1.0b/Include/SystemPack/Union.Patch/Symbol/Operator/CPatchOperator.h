#pragma once

namespace SystemPack
{
	class CPatchStack;
	class ASTAPI CPatchOperator : public CPatchSymbol
	{
		friend class CPatchStack;

		Common::CString		 sOperator;
		CPatchStack* pOnStack;

		PATCH_CLASS_DECLARATION(CPatchOperator);
	public:
				void		Init		(const Common::CString& opName);
				Common::CString		GetOperator	();
		virtual	CPatchType*	Execute		();
	};
}