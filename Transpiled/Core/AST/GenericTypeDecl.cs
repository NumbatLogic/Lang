#line 1 "../../../Source/Core/AST/GenericTypeDecl.nll"
namespace NumbatLogic
{
	class GenericTypeDecl : AST
	{
		public static GenericTypeDecl TryCreate(TokenContainer pTokenContainer, OffsetDatum pOffsetDatum)
		{
			OffsetDatum pTempOffset = OffsetDatum.Create(pOffsetDatum);
#line 9 "../../../Source/Core/AST/GenericTypeDecl.nll"
			Token pTypeToken = pTokenContainer.Peek(pTempOffset);
			if (pTypeToken == null || pTypeToken.m_eType != Token.Type.TOKEN_IDENTIFIER)
			{
#line 11 "../../../Source/Core/AST/GenericTypeDecl.nll"
				return null;
			}
#line 12 "../../../Source/Core/AST/GenericTypeDecl.nll"
			pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
#line 14 "../../../Source/Core/AST/GenericTypeDecl.nll"
			GenericTypeDecl pGenericTypeDecl = new GenericTypeDecl();
#line 16 "../../../Source/Core/AST/GenericTypeDecl.nll"
			pGenericTypeDecl.m_eType = AST.Type.AST_GENERIC_TYPE_DECL;
			pGenericTypeDecl.m_pFirstToken = pTypeToken;
#line 19 "../../../Source/Core/AST/GenericTypeDecl.nll"
			pOffsetDatum.Set(pTempOffset);
			NumbatLogic.GenericTypeDecl __976981417 = pGenericTypeDecl;
#line 20 "../../../Source/Core/AST/GenericTypeDecl.nll"
			pGenericTypeDecl = null;
#line 20 "../../../Source/Core/AST/GenericTypeDecl.nll"
			return __976981417;
		}

		public override void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder pOutputBuilder)
		{
			m_pFirstToken.Stringify(pOutputBuilder.m_sOut);
		}

	}
}

