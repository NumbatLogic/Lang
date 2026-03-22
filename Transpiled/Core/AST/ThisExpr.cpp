#include "ThisExpr.hpp"
#include "../OffsetDatum.hpp"
#include "../TokenContainer.hpp"
#include "../Token.hpp"
#include "AST.hpp"
#include "../ValueType.hpp"
#include "../Validator.hpp"
#include "../OutputBuilder.hpp"
#include "../../../../LangShared/Source/InternalString/CPP/InternalString.hpp"

namespace NumbatLogic
{
	class AST;
	class OffsetDatum;
	class Token;
	class TokenContainer;
	class ThisExpr;
	class ValueType;
	class Validator;
	class ClassDecl;
	class OutputBuilder;
	class InternalString;
}
#line 0 "/home/cliffya/git/Lang/Source/Core/AST/ThisExpr.nll"
namespace NumbatLogic
{
#line 3 "/home/cliffya/git/Lang/Source/Core/AST/ThisExpr.nll"
#line 5 "/home/cliffya/git/Lang/Source/Core/AST/ThisExpr.nll"
	ThisExpr* ThisExpr::TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum)
	{
		OffsetDatum* pTempOffset = OffsetDatum::Create(pOffsetDatum);
#line 9 "/home/cliffya/git/Lang/Source/Core/AST/ThisExpr.nll"
		Token* pThisToken = pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_KEYWORD_THIS);
		if (pThisToken == 0)
		{
			if (pTempOffset) delete pTempOffset;
#line 11 "/home/cliffya/git/Lang/Source/Core/AST/ThisExpr.nll"
			return 0;
		}
#line 12 "/home/cliffya/git/Lang/Source/Core/AST/ThisExpr.nll"
		pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
#line 14 "/home/cliffya/git/Lang/Source/Core/AST/ThisExpr.nll"
		ThisExpr* pThisExpr = new ThisExpr();
#line 16 "/home/cliffya/git/Lang/Source/Core/AST/ThisExpr.nll"
		pThisExpr->m_eType = AST::Type::THIS_EXPR;
		pThisExpr->m_pFirstToken = pThisToken;
#line 19 "/home/cliffya/git/Lang/Source/Core/AST/ThisExpr.nll"
		pOffsetDatum->Set(pTempOffset);
		NumbatLogic::ThisExpr* __1365567169 = pThisExpr;
#line 20 "/home/cliffya/git/Lang/Source/Core/AST/ThisExpr.nll"
		pThisExpr = 0;
		if (pTempOffset) delete pTempOffset;
#line 20 "/home/cliffya/git/Lang/Source/Core/AST/ThisExpr.nll"
		return __1365567169;
	}

	void ThisExpr::Validate(Validator* pValidator, OperatorExpr* pParent)
	{
		m_pValueType = new ValueType(ValueType::Type::CLASS_DECL_VALUE);
#line 27 "/home/cliffya/git/Lang/Source/Core/AST/ThisExpr.nll"
		AST* pTestParent = m_pParent;
		while (true)
		{
			if (pTestParent == 0)
			{
				pValidator->AddError("this is not the child of a ClassDec???", m_pFirstToken->m_sFileName, m_pFirstToken->m_nLine, m_pFirstToken->m_nColumn);
				return;
			}
#line 36 "/home/cliffya/git/Lang/Source/Core/AST/ThisExpr.nll"
			if (pTestParent->m_eType == AST::Type::AST_CLASS_DECL)
				break;
#line 39 "/home/cliffya/git/Lang/Source/Core/AST/ThisExpr.nll"
			pTestParent = pTestParent->m_pParent;
		}
#line 42 "/home/cliffya/git/Lang/Source/Core/AST/ThisExpr.nll"
		m_pValueType->m_pClassDecl = (ClassDecl*)(pTestParent);
	}

	void ThisExpr::Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder* pOutputBuilder)
	{
		pOutputBuilder->m_sOut->Append("this");
	}

}

