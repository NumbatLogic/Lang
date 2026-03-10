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
#line 0 "../../../Source/Core/OutputBuilder.nll"
namespace NumbatLogic
{
#line 3 "../../../Source/Core/OutputBuilder.nll"
#line 7 "../../../Source/Core/OutputBuilder.nll"
	OutputBuilder::OutputBuilder()
	{
		m_sOut = 0;
#line 9 "../../../Source/Core/OutputBuilder.nll"
		m_sOut = new InternalString("");
	}

#line 12 "../../../Source/Core/OutputBuilder.nll"
	void OutputBuilder::UpdateSourceLocation(AST::Language eLanguage, Token* pToken)
	{
#line 14 "../../../Source/Core/OutputBuilder.nll"
		if (eLanguage == AST::Language::CPP || eLanguage == AST::Language::C || eLanguage == AST::Language::H || eLanguage == AST::Language::CS)
		{
#line 16 "../../../Source/Core/OutputBuilder.nll"
			m_sOut->Append("#line ");
#line 17 "../../../Source/Core/OutputBuilder.nll"
			if (eLanguage == AST::Language::CS && pToken->m_nLine == 0)
#line 18 "../../../Source/Core/OutputBuilder.nll"
				m_sOut->AppendInt(pToken->m_nLine + 1);
			else
#line 20 "../../../Source/Core/OutputBuilder.nll"
				m_sOut->AppendInt(pToken->m_nLine);
#line 21 "../../../Source/Core/OutputBuilder.nll"
			m_sOut->Append(" \"");
#line 22 "../../../Source/Core/OutputBuilder.nll"
			m_sOut->Append(pToken->m_sFileName->GetExternalString());
#line 23 "../../../Source/Core/OutputBuilder.nll"
			m_sOut->Append("\"\n");
		}
	}

#line 3 "../../../Source/Core/OutputBuilder.nll"
	OutputBuilder::~OutputBuilder()
	{
		if (m_sOut) delete m_sOut;
	}

}

