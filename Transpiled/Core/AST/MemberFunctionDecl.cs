#line 1 "../../../Source/Core/AST/MemberFunctionDecl.nll"
namespace NumbatLogic
{
	class MemberFunctionDecl : AST
	{
		public ClassDecl m_pParentClassDecl;
		public AccessLevel m_pAccessLevel;
		public FunctionDecl m_pFunctionDecl;
		public bool m_bStatic;
		public bool m_bVirtual;
		public bool m_bOverride;
#line 12 "../../../Source/Core/AST/MemberFunctionDecl.nll"
		public MemberFunctionDecl()
		{
			m_eType = AST.Type.AST_MEMBER_FUNCTION_DECL;
			m_bCanDescend = true;
		}

		public static MemberFunctionDecl TryCreate(TokenContainer pTokenContainer, OffsetDatum pOffsetDatum, ClassDecl pParentClassDecl)
		{
			OffsetDatum pTempOffset = OffsetDatum.Create(pOffsetDatum);
#line 22 "../../../Source/Core/AST/MemberFunctionDecl.nll"
			AccessLevel pAccessLevel = AccessLevel.TryCreate(pTokenContainer, pTempOffset);
			if (pAccessLevel == null)
			{
#line 24 "../../../Source/Core/AST/MemberFunctionDecl.nll"
				return null;
			}
			bool bStatic = false;
			bool bVirtual = false;
			bool bOverride = false;
#line 30 "../../../Source/Core/AST/MemberFunctionDecl.nll"
			Token pToken = pTokenContainer.Peek(pTempOffset);
			if (pToken == null)
			{
#line 32 "../../../Source/Core/AST/MemberFunctionDecl.nll"
				return null;
			}
#line 33 "../../../Source/Core/AST/MemberFunctionDecl.nll"
			switch (pToken.m_eType)
			{
				case Token.Type.TOKEN_KEYWORD_STATIC:
				{
					bStatic = true;
					pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
					break;
				}

				case Token.Type.TOKEN_KEYWORD_VIRTUAL:
				{
#line 43 "../../../Source/Core/AST/MemberFunctionDecl.nll"
					bVirtual = true;
					pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
					break;
				}

				case Token.Type.TOKEN_KEYWORD_OVERRIDE:
				{
#line 49 "../../../Source/Core/AST/MemberFunctionDecl.nll"
					bOverride = true;
					pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
					break;
				}

			}
			MemberFunctionDecl pMemberFunctionDecl = new MemberFunctionDecl();
			pMemberFunctionDecl.m_pParent = pParentClassDecl;
			pMemberFunctionDecl.m_pParentClassDecl = pParentClassDecl;
			pMemberFunctionDecl.m_pAccessLevel = pAccessLevel;
			pMemberFunctionDecl.m_pFirstToken = pAccessLevel.m_pFirstToken;
			pMemberFunctionDecl.m_bStatic = bStatic;
			pMemberFunctionDecl.m_bVirtual = bVirtual;
			pMemberFunctionDecl.m_bOverride = bOverride;
#line 64 "../../../Source/Core/AST/MemberFunctionDecl.nll"
			FunctionDecl pFunctionDecl = FunctionDecl.TryCreate(pTokenContainer, pTempOffset, pMemberFunctionDecl);
			if (pFunctionDecl == null)
			{
#line 66 "../../../Source/Core/AST/MemberFunctionDecl.nll"
				return null;
			}
			NumbatLogic.AccessLevel __99074450 = pAccessLevel;
#line 68 "../../../Source/Core/AST/MemberFunctionDecl.nll"
			pAccessLevel = null;
#line 68 "../../../Source/Core/AST/MemberFunctionDecl.nll"
			pMemberFunctionDecl.AddChild(__99074450);
#line 70 "../../../Source/Core/AST/MemberFunctionDecl.nll"
			pMemberFunctionDecl.m_pFunctionDecl = pFunctionDecl;
			NumbatLogic.FunctionDecl __4280026732 = pFunctionDecl;
#line 71 "../../../Source/Core/AST/MemberFunctionDecl.nll"
			pFunctionDecl = null;
#line 71 "../../../Source/Core/AST/MemberFunctionDecl.nll"
			pMemberFunctionDecl.AddChild(__4280026732);
#line 73 "../../../Source/Core/AST/MemberFunctionDecl.nll"
			pOffsetDatum.Set(pTempOffset);
			NumbatLogic.MemberFunctionDecl __1564092617 = pMemberFunctionDecl;
#line 74 "../../../Source/Core/AST/MemberFunctionDecl.nll"
			pMemberFunctionDecl = null;
#line 74 "../../../Source/Core/AST/MemberFunctionDecl.nll"
			return __1564092617;
		}

		public override void Validate(Validator pValidator, OperatorExpr pParent)
		{
			base.Validate(pValidator, pParent);
		}

		public override void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder pOutputBuilder)
		{
			bool bGeneric = m_pParentClassDecl.m_pGenericTypeDeclVector.GetSize() > 0;
			if (bGeneric && eLanguage == AST.Language.CPP && eOutputFile == AST.OutputFile.SOURCE)
				return;
#line 88 "../../../Source/Core/AST/MemberFunctionDecl.nll"
			if (eLanguage == AST.Language.CPP && eOutputFile == AST.OutputFile.SOURCE)
			{
				if (m_pParentClassDecl.m_pGenericTypeDeclVector.GetSize() > 0)
				{
				}
			}
#line 98 "../../../Source/Core/AST/MemberFunctionDecl.nll"
			pOutputBuilder.UpdateSourceLocation(eLanguage, m_pFirstToken);
			Util.Pad(nDepth, pOutputBuilder.m_sOut);
#line 101 "../../../Source/Core/AST/MemberFunctionDecl.nll"
			if (!(eLanguage == AST.Language.CPP && eOutputFile == AST.OutputFile.SOURCE))
			{
				m_pAccessLevel.Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
				if (eLanguage == AST.Language.CPP)
					pOutputBuilder.m_sOut.AppendChar(':');
#line 107 "../../../Source/Core/AST/MemberFunctionDecl.nll"
				if (m_bStatic)
					pOutputBuilder.m_sOut.Append(" static");
#line 110 "../../../Source/Core/AST/MemberFunctionDecl.nll"
				if (m_bVirtual)
					pOutputBuilder.m_sOut.Append(" virtual");
#line 113 "../../../Source/Core/AST/MemberFunctionDecl.nll"
				if (m_bOverride)
					if (eLanguage == AST.Language.CPP)
						pOutputBuilder.m_sOut.Append(" virtual");
					else
						pOutputBuilder.m_sOut.Append(" override");
#line 119 "../../../Source/Core/AST/MemberFunctionDecl.nll"
				pOutputBuilder.m_sOut.AppendChar(' ');
			}
#line 122 "../../../Source/Core/AST/MemberFunctionDecl.nll"
			m_pFunctionDecl.Stringify(eLanguage, eOutputFile, nDepth, pOutputBuilder);
		}

	}
}

