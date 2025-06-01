namespace NumberDuck
{
	namespace Secret
	{
		class MemberVarDecl : AST
		{
			public AccessLevel m_pAccessLevel;
			public bool m_bStatic;
			public VarDecl m_pVarDecl;
			public MemberVarDecl()
			{
				m_bCanDescend = true;
			}

			public static MemberVarDecl TryCreate(TokenContainer pTokenContainer, OffsetDatum pOffsetDatum)
			{
				OffsetDatum pTempOffset = OffsetDatum.Create(pOffsetDatum);
				bool bStatic = false;
				AccessLevel pAccessLevel = AccessLevel.TryCreate(pTokenContainer, pTempOffset);
				if (pAccessLevel == null)
				{
					return null;
				}
				Token pStaticToken = pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_KEYWORD_STATIC);
				if (pStaticToken != null)
				{
					bStatic = true;
					pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
				}
				VarDecl pVarDecl = VarDecl.TryCreate(pTokenContainer, pTempOffset, false);
				if (pVarDecl == null)
				{
					return null;
				}
				MemberVarDecl pMemberVarDecl = new MemberVarDecl();
				pMemberVarDecl.m_eType = AST.Type.AST_MEMBER_VAR_DECL;
				pMemberVarDecl.m_pAccessLevel = pAccessLevel;
				pMemberVarDecl.m_bStatic = bStatic;
				pMemberVarDecl.m_pVarDecl = pVarDecl;
				{
					NumberDuck.Secret.AccessLevel __2194276919 = pAccessLevel;
					pAccessLevel = null;
					pMemberVarDecl.AddChild(__2194276919);
				}
				{
					NumberDuck.Secret.VarDecl __2920859675 = pVarDecl;
					pVarDecl = null;
					pMemberVarDecl.AddChild(__2920859675);
				}
				pOffsetDatum.Set(pTempOffset);
				{
					NumberDuck.Secret.MemberVarDecl __1908094182 = pMemberVarDecl;
					pMemberVarDecl = null;
					{
						return __1908094182;
					}
				}
			}

			public override void Validate(Validator pValidator, OperatorExpr pParent)
			{
				base.Validate(pValidator, pParent);
				InternalString sTemp = new InternalString(m_pVarDecl.m_pNameToken.GetString());
				if (!sTemp.StartsWith("m_") && !m_pVarDecl.m_pTypeRef.m_bConst)
				{
					pValidator.AddError("Member var name does not start with \"m_\"", m_pVarDecl.m_pNameToken.m_sFileName, m_pVarDecl.m_pNameToken.m_nLine, m_pVarDecl.m_pNameToken.m_nColumn);
				}
			}

			public override void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, InternalString sOut)
			{
				bool bArrayAssignment = m_pVarDecl.m_pArraySize != null && m_pVarDecl.m_pAssignment != null;
				if (eLanguage == AST.Language.CPP && eOutputFile == AST.OutputFile.SOURCE && !bArrayAssignment)
					return;
				Util.Pad(nDepth, sOut);
				if (!(eLanguage == AST.Language.CPP && eOutputFile == AST.OutputFile.SOURCE))
				{
					m_pAccessLevel.Stringify(eLanguage, eOutputFile, 0, sOut);
					if (eLanguage == AST.Language.CPP)
						sOut.AppendChar(':');
					sOut.AppendChar(' ');
					if (m_bStatic)
					{
						if (eLanguage == AST.Language.CS)
						{
							if (m_pVarDecl.m_pTypeRef.m_bConst == false || m_pVarDecl.m_pArraySize != null)
								sOut.AppendString("static ");
						}
						else
						{
							sOut.AppendString("static ");
						}
					}
				}
				m_pVarDecl.Stringify(eLanguage, eOutputFile, 0, sOut);
			}

		}
	}
}

