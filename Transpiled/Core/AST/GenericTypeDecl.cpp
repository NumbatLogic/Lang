#include "GenericTypeDecl.hpp"
#include "../OffsetDatum.hpp"
#include "../TokenContainer.hpp"
#include "../Token.hpp"
#include "AST.hpp"
#include "../OutputBuilder.hpp"

namespace NumbatLogic
{
	class AST;
	class OffsetDatum;
	class Token;
	class TokenContainer;
	class GenericTypeDecl;
	class OutputBuilder;
}
#line 0 "../../../Source/Core/AST/GenericTypeDecl.nll"
namespace NumbatLogic
{
#line 3 "../../../Source/Core/AST/GenericTypeDecl.nll"
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
		NumbatLogic::GenericTypeDecl* __976981417 = pGenericTypeDecl;
		pGenericTypeDecl = 0;
		if (pTempOffset) delete pTempOffset;
		return __976981417;
	}

	void GenericTypeDecl::Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder* out)
	{
		m_pFirstToken->Stringify(out->m_sOut);
	}

}

