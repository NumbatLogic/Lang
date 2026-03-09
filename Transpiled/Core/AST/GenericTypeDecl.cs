#line 1 "../../../Source/Core/AST/GenericTypeDecl.nll"
namespace NumbatLogic
{
#line 4 "../../../Source/Core/AST/GenericTypeDecl.nll"
	class GenericTypeDecl : AST
	{
#line 6 "../../../Source/Core/AST/GenericTypeDecl.nll"
		public static GenericTypeDecl TryCreate(TokenContainer pTokenContainer, OffsetDatum pOffsetDatum)
		{
			OffsetDatum pTempOffset = OffsetDatum.Create(pOffsetDatum);
			Token pTypeToken = pTokenContainer.Peek(pTempOffset);
#line 11 "../../../Source/Core/AST/GenericTypeDecl.nll"
			if (pTypeToken == null || pTypeToken.m_eType != Token.Type.TOKEN_IDENTIFIER)
			{
#line 12 "../../../Source/Core/AST/GenericTypeDecl.nll"
				return null;
			}
#line 13 "../../../Source/Core/AST/GenericTypeDecl.nll"
			pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
			GenericTypeDecl pGenericTypeDecl = new GenericTypeDecl();
#line 17 "../../../Source/Core/AST/GenericTypeDecl.nll"
			pGenericTypeDecl.m_eType = AST.Type.AST_GENERIC_TYPE_DECL;
#line 18 "../../../Source/Core/AST/GenericTypeDecl.nll"
			pGenericTypeDecl.m_pFirstToken = pTypeToken;
#line 20 "../../../Source/Core/AST/GenericTypeDecl.nll"
			pOffsetDatum.Set(pTempOffset);
			NumbatLogic.GenericTypeDecl __976981417 = pGenericTypeDecl;
#line 21 "../../../Source/Core/AST/GenericTypeDecl.nll"
			pGenericTypeDecl = null;
#line 21 "../../../Source/Core/AST/GenericTypeDecl.nll"
			return __976981417;
		}

#line 24 "../../../Source/Core/AST/GenericTypeDecl.nll"
		public override void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder pOutputBuilder)
		{
#line 26 "../../../Source/Core/AST/GenericTypeDecl.nll"
			m_pFirstToken.Stringify(pOutputBuilder.m_sOut);
		}

	}
}

