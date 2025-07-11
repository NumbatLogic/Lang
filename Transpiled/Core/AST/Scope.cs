namespace NumbatLogic
{
	class Scope : AST
	{
		public bool m_bPseudo;
		public Scope()
		{
			m_eType = AST.Type.AST_SCOPE;
			m_bPseudo = false;
		}

		public static Scope TryCreate(TokenContainer pTokenContainer, OffsetDatum pOffsetDatum, bool bPseudoScope)
		{
			Scope pScope;
			OffsetDatum pTempOffset = OffsetDatum.Create(pOffsetDatum);
			Token pOpeningToken = pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_CURLY_BRACE_LEFT);
			if (pOpeningToken == null)
			{
				if (bPseudoScope)
				{
					AST pChild = AST.CreateStatementFromTokenContainer(pTokenContainer, pTempOffset);
					if (pChild != null)
					{
						pScope = new Scope();
						pScope.m_pFirstToken = pChild.m_pFirstToken;
						pScope.m_bPseudo = true;
						NumbatLogic.AST __1363581045 = pChild;
						pChild = null;
						pScope.AddChild(__1363581045);
						pOffsetDatum.Set(pTempOffset);
						NumbatLogic.Scope __4264334019 = pScope;
						pScope = null;
						return __4264334019;
					}
				}
				return null;
			}
			pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
			pScope = new Scope();
			pScope.m_pFirstToken = pOpeningToken;
			while (true)
			{
				Token pClosingToken = pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_CURLY_BRACE_RIGHT);
				if (pClosingToken != null)
				{
					pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
					break;
				}
				AST pChild = AST.CreateStatementFromTokenContainer(pTokenContainer, pTempOffset);
				if (pChild == null)
				{
					Console.Log("expected to parse somethting within scope...");
					Console.Log(pTokenContainer.StringifyOffset(pTempOffset));
					NumbatLogic.Assert.Plz(false);
					return null;
				}
				NumbatLogic.AST __239473913 = pChild;
				pChild = null;
				pScope.AddChild(__239473913);
			}
			pOffsetDatum.Set(pTempOffset);
			NumbatLogic.Scope __1126965182 = pScope;
			pScope = null;
			return __1126965182;
		}

		public override void Validate(Validator pValidator, OperatorExpr pParent)
		{
			pValidator.BeginScope(this);
			if (m_pParent.m_eType == AST.Type.AST_TOR_DECL)
			{
				TorDecl pTorDecl = (TorDecl)(m_pParent);
				if (pTorDecl.m_pTypeToken.m_eType == Token.Type.TOKEN_KEYWORD_DESTRUCT)
				{
					if (pTorDecl.m_pParent.m_eType != AST.Type.AST_CLASS_DECL)
					{
						pValidator.AddError("Expected parent TorDecl to be child of AST_CLASS_DECL", m_pFirstToken.m_sFileName, m_pFirstToken.m_nLine, m_pFirstToken.m_nColumn);
						return;
					}
					AST pChild = pTorDecl.m_pParent.m_pFirstChild;
					while (pChild != null)
					{
						if (pChild.m_eType == AST.Type.AST_MEMBER_VAR_DECL)
						{
							MemberVarDecl pMemberVarDecl = (MemberVarDecl)(pChild);
							pValidator.AddVarDecl(pMemberVarDecl.m_pVarDecl);
							if (pMemberVarDecl.m_pVarDecl.m_pTypeRef.m_pTypeToken.m_eType == Token.Type.TOKEN_IDENTIFIER)
							{
								string sTypeName = pMemberVarDecl.m_pVarDecl.m_pTypeRef.m_pTypeToken.GetString();
								AST pType = FindByName(sTypeName, this);
								if (pType != null && pType.m_eType == AST.Type.AST_CLASS_DECL)
								{
									ClassDecl pClassDecl = (ClassDecl)(pType);
									AddClassDeclReference(pClassDecl, AST.OutputFile.SOURCE, false);
								}
							}
						}
						pChild = pChild.m_pNextSibling;
					}
				}
			}
			base.Validate(pValidator, pParent);
			pValidator.EndScope(this);
		}

		public override void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, InternalString sOut)
		{
			if (!m_bPseudo || m_pFirstChild == null || m_pFirstChild != m_pLastChild)
			{
				Util.Pad(nDepth, sOut);
				sOut.Append("{\n");
			}
			AST pChild = m_pFirstChild;
			while (pChild != null)
			{
				pChild.Stringify(eLanguage, eOutputFile, nDepth + 1, sOut);
				pChild = pChild.m_pNextSibling;
			}
			if (!m_bPseudo || m_pFirstChild == null || m_pFirstChild != m_pLastChild)
			{
				Util.Pad(nDepth, sOut);
				sOut.Append("}\n");
			}
		}

	}
}

