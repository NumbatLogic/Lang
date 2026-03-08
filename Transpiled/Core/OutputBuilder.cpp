#include "OutputBuilder.hpp"
#include "../../../LangShared/InternalString/CPP/InternalString.hpp"
#include "AST/AST.hpp"
#include "Token.hpp"

namespace NumbatLogic
{
	class OutputBuilder;
	class InternalString;
	class AST;
	class Token;
}
#line 1 "../../../Source/Core/OutputBuilder.nll"
namespace NumbatLogic
{
	OutputBuilder::OutputBuilder()
	{
		m_sOut = 0;
		m_sOut = new InternalString("");
	}

	void OutputBuilder::OutputSourceLocation(AST::Language eLanguage, Token* pToken)
	{
		if (eLanguage == AST::Language::CPP || eLanguage == AST::Language::C || eLanguage == AST::Language::H || eLanguage == AST::Language::CS)
		{
			m_sOut->Append("#line ");
			m_sOut->AppendInt(pToken->m_nLine);
			m_sOut->Append(" \"");
			m_sOut->Append(pToken->m_sFileName->GetExternalString());
			m_sOut->Append("\"\n");
		}
	}

	OutputBuilder::~OutputBuilder()
	{
		if (m_sOut) delete m_sOut;
	}

}

