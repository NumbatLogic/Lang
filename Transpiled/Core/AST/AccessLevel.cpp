#include "AccessLevel.hpp"
#include "../OffsetDatum.hpp"
#include "../TokenContainer.hpp"
#include "../Token.hpp"
#include "AST.hpp"
#include "../../../../LangShared/InternalString/CPP/InternalString.hpp"

namespace NumbatLogic
{
	class OffsetDatum;
	class Token;
	class AccessLevel;
}
namespace NumbatLogic
{
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
		NumbatLogic::AccessLevel* __2194276919 = pAccessLevel;
		pAccessLevel = 0;
		if (pTempOffset) delete pTempOffset;
		return __2194276919;
	}

	void AccessLevel::Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, InternalString* sOut)
	{
		switch (m_pFirstToken->m_eType)
		{
			case Token::Type::TOKEN_KEYWORD_PRIVATE:
			{
				if (eLanguage == AST::Language::NLL_DEF)
					sOut->AppendString("private");
				else
					sOut->AppendString("protected");
				return;
			}

			case Token::Type::TOKEN_KEYWORD_PUBLIC:
			{
				sOut->AppendString("public");
				return;
			}

		}
		sOut->AppendString("???");
	}

}

