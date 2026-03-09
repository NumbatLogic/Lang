#include "Symbol.hpp"

namespace NumbatLogic
{
	class Symbol;
}
#line 1 "../../../Source/Core/Semantic/Symbol.nll"
namespace NumbatLogic
{
#line 4 "../../../Source/Core/Semantic/Symbol.nll"
#line 34 "../../../Source/Core/Semantic/Symbol.nll"
	Symbol::Symbol()
	{
		m_eKind = Kind::NAMESPACE;
		m_sShortName = 0;
		m_sQualifiedName = 0;
		m_pDeclAST = 0;
		m_pScope = 0;
#line 36 "../../../Source/Core/Semantic/Symbol.nll"
		m_eKind = Kind::VAR;
#line 37 "../../../Source/Core/Semantic/Symbol.nll"
		m_sShortName = "";
#line 38 "../../../Source/Core/Semantic/Symbol.nll"
		m_sQualifiedName = "";
#line 39 "../../../Source/Core/Semantic/Symbol.nll"
		m_pDeclAST = 0;
#line 40 "../../../Source/Core/Semantic/Symbol.nll"
		m_pScope = 0;
	}

}

