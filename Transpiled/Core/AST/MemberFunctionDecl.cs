#line 1 "../../../Source/Core/AST/MemberFunctionDecl.nll"
namespace NumbatLogic
{
#line 3 "../../../Source/Core/AST/MemberFunctionDecl.nll"
	class MemberFunctionDecl : AST
	{
#line 5 "../../../Source/Core/AST/MemberFunctionDecl.nll"
		public ClassDecl m_pParentClassDecl;
#line 6 "../../../Source/Core/AST/MemberFunctionDecl.nll"
		public AccessLevel m_pAccessLevel;
#line 7 "../../../Source/Core/AST/MemberFunctionDecl.nll"
		public FunctionDecl m_pFunctionDecl;
#line 8 "../../../Source/Core/AST/MemberFunctionDecl.nll"
		public bool m_bStatic;
#line 9 "../../../Source/Core/AST/MemberFunctionDecl.nll"
		public bool m_bVirtual;
#line 10 "../../../Source/Core/AST/MemberFunctionDecl.nll"
		public bool m_bOverride;
#line 12 "../../../Source/Core/AST/MemberFunctionDecl.nll"
		public MemberFunctionDecl()
		{
#line 14 "../../../Source/Core/AST/MemberFunctionDecl.nll"
			m_eType = AST.Type.AST_MEMBER_FUNCTION_DECL;
#line 15 "../../../Source/Core/AST/MemberFunctionDecl.nll"
			m_bCanDescend = true;
		}

#line 18 "../../../Source/Core/AST/MemberFunctionDecl.nll"
		public static MemberFunctionDecl TryCreate(TokenContainer pTokenContainer, OffsetDatum pOffsetDatum, ClassDecl pParentClassDecl)
		{
#line 20 "../../../Source/Core/AST/MemberFunctionDecl.nll"
			OffsetDatum pTempOffset = OffsetDatum.Create(pOffsetDatum);
#line 22 "../../../Source/Core/AST/MemberFunctionDecl.nll"
			AccessLevel pAccessLevel = AccessLevel.TryCreate(pTokenContainer, pTempOffset);
#line 23 "../../../Source/Core/AST/MemberFunctionDecl.nll"
			if (pAccessLevel == null)
			{
#line 24 "../../../Source/Core/AST/MemberFunctionDecl.nll"
				return null;
			}
#line 26 "../../../Source/Core/AST/MemberFunctionDecl.nll"
			bool bStatic = false;
#line 27 "../../../Source/Core/AST/MemberFunctionDecl.nll"
			bool bVirtual = false;
#line 28 "../../../Source/Core/AST/MemberFunctionDecl.nll"
			bool bOverride = false;
#line 30 "../../../Source/Core/AST/MemberFunctionDecl.nll"
			Token pToken = pTokenContainer.Peek(pTempOffset);
#line 31 "../../../Source/Core/AST/MemberFunctionDecl.nll"
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
#line 37 "../../../Source/Core/AST/MemberFunctionDecl.nll"
					bStatic = true;
#line 38 "../../../Source/Core/AST/MemberFunctionDecl.nll"
					pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
#line 39 "../../../Source/Core/AST/MemberFunctionDecl.nll"
					break;
				}

				case Token.Type.TOKEN_KEYWORD_VIRTUAL:
				{
#line 43 "../../../Source/Core/AST/MemberFunctionDecl.nll"
					bVirtual = true;
#line 44 "../../../Source/Core/AST/MemberFunctionDecl.nll"
					pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
#line 45 "../../../Source/Core/AST/MemberFunctionDecl.nll"
					break;
				}

				case Token.Type.TOKEN_KEYWORD_OVERRIDE:
				{
#line 49 "../../../Source/Core/AST/MemberFunctionDecl.nll"
					bOverride = true;
#line 50 "../../../Source/Core/AST/MemberFunctionDecl.nll"
					pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
#line 51 "../../../Source/Core/AST/MemberFunctionDecl.nll"
					break;
				}

			}
#line 55 "../../../Source/Core/AST/MemberFunctionDecl.nll"
			MemberFunctionDecl pMemberFunctionDecl = new MemberFunctionDecl();
#line 56 "../../../Source/Core/AST/MemberFunctionDecl.nll"
			pMemberFunctionDecl.m_pParent = pParentClassDecl;
#line 57 "../../../Source/Core/AST/MemberFunctionDecl.nll"
			pMemberFunctionDecl.m_pParentClassDecl = pParentClassDecl;
#line 58 "../../../Source/Core/AST/MemberFunctionDecl.nll"
			pMemberFunctionDecl.m_pAccessLevel = pAccessLevel;
#line 59 "../../../Source/Core/AST/MemberFunctionDecl.nll"
			pMemberFunctionDecl.m_pFirstToken = pAccessLevel.m_pFirstToken;
#line 60 "../../../Source/Core/AST/MemberFunctionDecl.nll"
			pMemberFunctionDecl.m_bStatic = bStatic;
#line 61 "../../../Source/Core/AST/MemberFunctionDecl.nll"
			pMemberFunctionDecl.m_bVirtual = bVirtual;
#line 62 "../../../Source/Core/AST/MemberFunctionDecl.nll"
			pMemberFunctionDecl.m_bOverride = bOverride;
#line 64 "../../../Source/Core/AST/MemberFunctionDecl.nll"
			FunctionDecl pFunctionDecl = FunctionDecl.TryCreate(pTokenContainer, pTempOffset, pMemberFunctionDecl);
#line 65 "../../../Source/Core/AST/MemberFunctionDecl.nll"
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

#line 77 "../../../Source/Core/AST/MemberFunctionDecl.nll"
		public override void Validate(Validator pValidator, OperatorExpr pParent)
		{
#line 79 "../../../Source/Core/AST/MemberFunctionDecl.nll"
			base.Validate(pValidator, pParent);
		}

#line 82 "../../../Source/Core/AST/MemberFunctionDecl.nll"
		public override void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder pOutputBuilder)
		{
#line 84 "../../../Source/Core/AST/MemberFunctionDecl.nll"
			bool bGeneric = m_pParentClassDecl.m_pGenericTypeDeclVector.GetSize() > 0;
#line 85 "../../../Source/Core/AST/MemberFunctionDecl.nll"
			if (bGeneric && eLanguage == AST.Language.CPP && eOutputFile == AST.OutputFile.SOURCE)
#line 86 "../../../Source/Core/AST/MemberFunctionDecl.nll"
				return;
#line 88 "../../../Source/Core/AST/MemberFunctionDecl.nll"
			if (eLanguage == AST.Language.CPP && eOutputFile == AST.OutputFile.SOURCE)
			{
#line 90 "../../../Source/Core/AST/MemberFunctionDecl.nll"
				if (m_pParentClassDecl.m_pGenericTypeDeclVector.GetSize() > 0)
				{
				}
			}
#line 98 "../../../Source/Core/AST/MemberFunctionDecl.nll"
			pOutputBuilder.UpdateSourceLocation(eLanguage, m_pFirstToken);
#line 99 "../../../Source/Core/AST/MemberFunctionDecl.nll"
			Util.Pad(nDepth, pOutputBuilder.m_sOut);
#line 101 "../../../Source/Core/AST/MemberFunctionDecl.nll"
			if (!(eLanguage == AST.Language.CPP && eOutputFile == AST.OutputFile.SOURCE))
			{
#line 103 "../../../Source/Core/AST/MemberFunctionDecl.nll"
				m_pAccessLevel.Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
#line 104 "../../../Source/Core/AST/MemberFunctionDecl.nll"
				if (eLanguage == AST.Language.CPP)
#line 105 "../../../Source/Core/AST/MemberFunctionDecl.nll"
					pOutputBuilder.m_sOut.AppendChar(':');
#line 107 "../../../Source/Core/AST/MemberFunctionDecl.nll"
				if (m_bStatic)
#line 108 "../../../Source/Core/AST/MemberFunctionDecl.nll"
					pOutputBuilder.m_sOut.Append(" static");
#line 110 "../../../Source/Core/AST/MemberFunctionDecl.nll"
				if (m_bVirtual)
#line 111 "../../../Source/Core/AST/MemberFunctionDecl.nll"
					pOutputBuilder.m_sOut.Append(" virtual");
#line 113 "../../../Source/Core/AST/MemberFunctionDecl.nll"
				if (m_bOverride)
#line 114 "../../../Source/Core/AST/MemberFunctionDecl.nll"
					if (eLanguage == AST.Language.CPP)
#line 115 "../../../Source/Core/AST/MemberFunctionDecl.nll"
						pOutputBuilder.m_sOut.Append(" virtual");
					else
#line 117 "../../../Source/Core/AST/MemberFunctionDecl.nll"
						pOutputBuilder.m_sOut.Append(" override");
#line 119 "../../../Source/Core/AST/MemberFunctionDecl.nll"
				pOutputBuilder.m_sOut.AppendChar(' ');
			}
#line 122 "../../../Source/Core/AST/MemberFunctionDecl.nll"
			m_pFunctionDecl.Stringify(eLanguage, eOutputFile, nDepth, pOutputBuilder);
		}

	}
}

