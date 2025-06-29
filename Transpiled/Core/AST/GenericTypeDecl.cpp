#include "GenericTypeDecl.hpp"
#include "../OffsetDatum.hpp"
#include "../TokenContainer.hpp"
#include "../Token.hpp"
#include "AST.hpp"

namespace NumbatLogic
{
	class OffsetDatum;
	class Token;
	class GenericTypeDecl;
}
namespace NumbatLogic
{
	GenericTypeDecl* GenericTypeDecl::TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum)
	{
		OffsetDatum* pTempOffset = OffsetDatum::Create(pOffsetDatum);
		Token* pTypeToken = pTokenContainer->Peek(pTempOffset);
		if (pTypeToken == 0 || pTypeToken->m_eType != Token::Type::TOKEN_IDENTIFIER)
		{
			if (pTempOffset) delete pTempOffset;
			return 0;
		}
		pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
		GenericTypeDecl* pGenericTypeDecl = new GenericTypeDecl();
		pGenericTypeDecl->m_eType = AST::Type::AST_GENERIC_TYPE_DECL;
		pGenericTypeDecl->m_pFirstToken = pTypeToken;
		pOffsetDatum->Set(pTempOffset);
		NumbatLogic::GenericTypeDecl* __3828846222 = pGenericTypeDecl;
		pGenericTypeDecl = 0;
		if (pTempOffset) delete pTempOffset;
		return __3828846222;
	}

	void GenericTypeDecl::Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, InternalString* sOut)
	{
		m_pFirstToken->Stringify(sOut);
	}

}

