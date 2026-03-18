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
#line 0 "/home/cliffya/git/Lang/Source/Core/AST/GenericTypeDecl.nll"
namespace NumbatLogic
{
#line 3 "/home/cliffya/git/Lang/Source/Core/AST/GenericTypeDecl.nll"
#line 5 "/home/cliffya/git/Lang/Source/Core/AST/GenericTypeDecl.nll"
	GenericTypeDecl* GenericTypeDecl::TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum)
	{
		OffsetDatum* pTempOffset = OffsetDatum::Create(pOffsetDatum);
#line 9 "/home/cliffya/git/Lang/Source/Core/AST/GenericTypeDecl.nll"
		Token* pTypeToken = pTokenContainer->Peek(pTempOffset);
		if (pTypeToken == 0 || pTypeToken->m_eType != Token::Type::TOKEN_IDENTIFIER)
		{
			if (pTempOffset) delete pTempOffset;
#line 11 "/home/cliffya/git/Lang/Source/Core/AST/GenericTypeDecl.nll"
			return 0;
		}
#line 12 "/home/cliffya/git/Lang/Source/Core/AST/GenericTypeDecl.nll"
		pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
#line 14 "/home/cliffya/git/Lang/Source/Core/AST/GenericTypeDecl.nll"
		GenericTypeDecl* pGenericTypeDecl = new GenericTypeDecl();
#line 16 "/home/cliffya/git/Lang/Source/Core/AST/GenericTypeDecl.nll"
		pGenericTypeDecl->m_eType = AST::Type::AST_GENERIC_TYPE_DECL;
		pGenericTypeDecl->m_pFirstToken = pTypeToken;
#line 19 "/home/cliffya/git/Lang/Source/Core/AST/GenericTypeDecl.nll"
		pOffsetDatum->Set(pTempOffset);
		NumbatLogic::GenericTypeDecl* __976981417 = pGenericTypeDecl;
#line 20 "/home/cliffya/git/Lang/Source/Core/AST/GenericTypeDecl.nll"
		pGenericTypeDecl = 0;
		if (pTempOffset) delete pTempOffset;
#line 20 "/home/cliffya/git/Lang/Source/Core/AST/GenericTypeDecl.nll"
		return __976981417;
	}

	void GenericTypeDecl::Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder* pOutputBuilder)
	{
		m_pFirstToken->Stringify(pOutputBuilder->m_sOut);
	}

}

