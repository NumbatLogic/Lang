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
#line 4 "../../../Source/Core/OutputBuilder.nll"
#line 8 "../../../Source/Core/OutputBuilder.nll"
	OutputBuilder::OutputBuilder()
	{
		m_sOut = 0;
#line 10 "../../../Source/Core/OutputBuilder.nll"
		m_sOut = new InternalString("");
	}

#line 13 "../../../Source/Core/OutputBuilder.nll"
	void OutputBuilder::UpdateSourceLocation(AST::Language eLanguage, Token* pToken)
	{
#line 15 "../../../Source/Core/OutputBuilder.nll"
		if (eLanguage == AST::Language::CPP || eLanguage == AST::Language::C || eLanguage == AST::Language::H || eLanguage == AST::Language::CS)
		{
#line 17 "../../../Source/Core/OutputBuilder.nll"
			m_sOut->Append("#line ");
#line 18 "../../../Source/Core/OutputBuilder.nll"
			m_sOut->AppendInt(pToken->m_nLine + 1);
#line 19 "../../../Source/Core/OutputBuilder.nll"
			m_sOut->Append(" \"");
#line 20 "../../../Source/Core/OutputBuilder.nll"
			m_sOut->Append(pToken->m_sFileName->GetExternalString());
#line 21 "../../../Source/Core/OutputBuilder.nll"
			m_sOut->Append("\"\n");
		}
	}

#line 4 "../../../Source/Core/OutputBuilder.nll"
	OutputBuilder::~OutputBuilder()
	{
		if (m_sOut) delete m_sOut;
	}

}

