#include "Symbol.hpp"

namespace NumbatLogic
{
	class Symbol;
}
namespace NumbatLogic
{
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

