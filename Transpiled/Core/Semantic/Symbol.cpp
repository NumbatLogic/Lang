#include "Symbol.hpp"

namespace NumbatLogic
{
	class Symbol;
}
#line 0 "/home/cliffya/git/Lang/Source/Core/Semantic/Symbol.nll"
namespace NumbatLogic
{
#line 3 "/home/cliffya/git/Lang/Source/Core/Semantic/Symbol.nll"
#line 33 "/home/cliffya/git/Lang/Source/Core/Semantic/Symbol.nll"
	Symbol::Symbol()
	{
		m_eKind = Kind::NAMESPACE;
		m_sShortName = 0;
		m_sQualifiedName = 0;
		m_pDeclAST = 0;
		m_pScope = 0;
#line 35 "/home/cliffya/git/Lang/Source/Core/Semantic/Symbol.nll"
		m_eKind = Kind::VAR;
		m_sShortName = "";
		m_sQualifiedName = "";
		m_pDeclAST = 0;
		m_pScope = 0;
	}

}

