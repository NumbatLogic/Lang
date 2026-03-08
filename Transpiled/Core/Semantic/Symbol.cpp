#include "Symbol.hpp"

namespace NumbatLogic
{
	class Symbol;
}
#line 0 "../../../Source/Core/Semantic/Symbol.nll"
namespace NumbatLogic
{
#line 3 "../../../Source/Core/Semantic/Symbol.nll"
	Symbol::Symbol()
	{
		m_eKind = Kind::NAMESPACE;
		m_sShortName = 0;
		m_sQualifiedName = 0;
		m_pDeclAST = 0;
		m_pScope = 0;
		m_eKind = Kind::VAR;
		m_sShortName = "";
		m_sQualifiedName = "";
		m_pDeclAST = 0;
		m_pScope = 0;
	}

}

