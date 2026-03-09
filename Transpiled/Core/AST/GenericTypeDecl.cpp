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
#line 1 "../../../Source/Core/AST/GenericTypeDecl.nll"
namespace NumbatLogic
{
#line 4 "../../../Source/Core/AST/GenericTypeDecl.nll"
#line 6 "../../../Source/Core/AST/GenericTypeDecl.nll"
	GenericTypeDecl* GenericTypeDecl::TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum)
	{
		OffsetDatum* pTempOffset = OffsetDatum::Create(pOffsetDatum);
		Token* pTypeToken = pTokenContainer->Peek(pTempOffset);
#line 11 "../../../Source/Core/AST/GenericTypeDecl.nll"
		if (pTypeToken == 0 || pTypeToken->m_eType != Token::Type::TOKEN_IDENTIFIER)
		{
			if (pTempOffset) delete pTempOffset;
#line 12 "../../../Source/Core/AST/GenericTypeDecl.nll"
			return 0;
		}
#line 13 "../../../Source/Core/AST/GenericTypeDecl.nll"
		pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
		GenericTypeDecl* pGenericTypeDecl = new GenericTypeDecl();
#line 17 "../../../Source/Core/AST/GenericTypeDecl.nll"
		pGenericTypeDecl->m_eType = AST::Type::AST_GENERIC_TYPE_DECL;
#line 18 "../../../Source/Core/AST/GenericTypeDecl.nll"
		pGenericTypeDecl->m_pFirstToken = pTypeToken;
#line 20 "../../../Source/Core/AST/GenericTypeDecl.nll"
		pOffsetDatum->Set(pTempOffset);
		NumbatLogic::GenericTypeDecl* __976981417 = pGenericTypeDecl;
#line 21 "../../../Source/Core/AST/GenericTypeDecl.nll"
		pGenericTypeDecl = 0;
		if (pTempOffset) delete pTempOffset;
#line 21 "../../../Source/Core/AST/GenericTypeDecl.nll"
		return __976981417;
	}

#line 24 "../../../Source/Core/AST/GenericTypeDecl.nll"
	void GenericTypeDecl::Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder* pOutputBuilder)
	{
#line 26 "../../../Source/Core/AST/GenericTypeDecl.nll"
		m_pFirstToken->Stringify(pOutputBuilder->m_sOut);
	}

}

