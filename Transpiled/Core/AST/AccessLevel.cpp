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
	AccessLevel* AccessLevel::TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum)
	{
		OffsetDatum* pTempOffset = OffsetDatum::Create(pOffsetDatum);
		Token* pAccessLevelToken = pTokenContainer->Peek(pTempOffset);
		if (pAccessLevelToken == 0 || pAccessLevelToken->m_eType != Token::Type::TOKEN_KEYWORD_PRIVATE && pAccessLevelToken->m_eType != Token::Type::TOKEN_KEYWORD_PUBLIC)
		{
			if (pTempOffset) delete pTempOffset;
			return 0;
		}
		pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
		AccessLevel* pAccessLevel = new AccessLevel();
		pAccessLevel->m_eType = AST::Type::AST_ACCESS_LEVEL;
		pAccessLevel->m_pFirstToken = pAccessLevelToken;
		pOffsetDatum->Set(pTempOffset);
		NumbatLogic::AccessLevel* __98812046 = pAccessLevel;
		pAccessLevel = 0;
		if (pTempOffset) delete pTempOffset;
		return __98812046;
	}

	void AccessLevel::Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder* pOutputBuilder)
	{
		switch (m_pFirstToken->m_eType)
		{
			case Token::Type::TOKEN_KEYWORD_PRIVATE:
			{
				if (eLanguage == AST::Language::NLL_DEF)
					pOutputBuilder->m_sOut->AppendString("private");
				else
					pOutputBuilder->m_sOut->AppendString("protected");
				return;
			}

			case Token::Type::TOKEN_KEYWORD_PUBLIC:
			{
				pOutputBuilder->m_sOut->AppendString("public");
				return;
			}

		}
		pOutputBuilder->m_sOut->AppendString("???");
	}

}

