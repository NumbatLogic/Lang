#include "AccessLevel.hpp"
#include "../OffsetDatum.hpp"
#include "../TokenContainer.hpp"
#include "../Token.hpp"
#include "AST.hpp"
#include "../OutputBuilder.hpp"
#include "../../../../LangShared/InternalString/CPP/InternalString.hpp"

namespace NumbatLogic
{
	class AST;
	class OffsetDatum;
	class Token;
	class TokenContainer;
	class AccessLevel;
	class OutputBuilder;
	class InternalString;
}
#line 0 "../../../Source/Core/AST/AccessLevel.nll"
namespace NumbatLogic
{
#line 3 "../../../Source/Core/AST/AccessLevel.nll"
#line 5 "../../../Source/Core/AST/AccessLevel.nll"
	AccessLevel* AccessLevel::TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum)
	{
		OffsetDatum* pTempOffset = OffsetDatum::Create(pOffsetDatum);
		Token* pAccessLevelToken = pTokenContainer->Peek(pTempOffset);
#line 10 "../../../Source/Core/AST/AccessLevel.nll"
		if (pAccessLevelToken == 0 || pAccessLevelToken->m_eType != Token::Type::TOKEN_KEYWORD_PRIVATE && pAccessLevelToken->m_eType != Token::Type::TOKEN_KEYWORD_PUBLIC)
		{
			if (pTempOffset) delete pTempOffset;
#line 11 "../../../Source/Core/AST/AccessLevel.nll"
			return 0;
		}
#line 12 "../../../Source/Core/AST/AccessLevel.nll"
		pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
		AccessLevel* pAccessLevel = new AccessLevel();
#line 16 "../../../Source/Core/AST/AccessLevel.nll"
		pAccessLevel->m_eType = AST::Type::AST_ACCESS_LEVEL;
#line 17 "../../../Source/Core/AST/AccessLevel.nll"
		pAccessLevel->m_pFirstToken = pAccessLevelToken;
#line 19 "../../../Source/Core/AST/AccessLevel.nll"
		pOffsetDatum->Set(pTempOffset);
		NumbatLogic::AccessLevel* __98812046 = pAccessLevel;
#line 20 "../../../Source/Core/AST/AccessLevel.nll"
		pAccessLevel = 0;
		if (pTempOffset) delete pTempOffset;
#line 20 "../../../Source/Core/AST/AccessLevel.nll"
		return __98812046;
	}

#line 23 "../../../Source/Core/AST/AccessLevel.nll"
	void AccessLevel::Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder* pOutputBuilder)
	{
#line 25 "../../../Source/Core/AST/AccessLevel.nll"
		switch (m_pFirstToken->m_eType)
		{
			case Token::Type::TOKEN_KEYWORD_PRIVATE:
			{
#line 29 "../../../Source/Core/AST/AccessLevel.nll"
				if (eLanguage == AST::Language::NLL_DEF)
#line 30 "../../../Source/Core/AST/AccessLevel.nll"
					pOutputBuilder->m_sOut->AppendString("private");
				else
#line 32 "../../../Source/Core/AST/AccessLevel.nll"
					pOutputBuilder->m_sOut->AppendString("protected");
#line 33 "../../../Source/Core/AST/AccessLevel.nll"
				return;
			}

			case Token::Type::TOKEN_KEYWORD_PUBLIC:
			{
#line 37 "../../../Source/Core/AST/AccessLevel.nll"
				pOutputBuilder->m_sOut->AppendString("public");
#line 38 "../../../Source/Core/AST/AccessLevel.nll"
				return;
			}

		}
#line 41 "../../../Source/Core/AST/AccessLevel.nll"
		pOutputBuilder->m_sOut->AppendString("???");
	}

}

