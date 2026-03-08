#line 1 "../../../Source/Core/AST/Scope.nll"
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
						NumbatLogic.AST __356897802 = pChild;
						pChild = null;
						pScope.AddChild(__356897802);
						pOffsetDatum.Set(pTempOffset);
						NumbatLogic.Scope __1530552932 = pScope;
						pScope = null;
						return __1530552932;
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
					Assert.Plz(false);
					return null;
				}
				NumbatLogic.AST __357094601 = pChild;
				pChild = null;
				pScope.AddChild(__357094601);
			}
			pOffsetDatum.Set(pTempOffset);
			NumbatLogic.Scope __1530749733 = pScope;
			pScope = null;
			return __1530749733;
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
							if (!pMemberVarDecl.m_bStatic)
							{
								pValidator.AddVarDecl(pMemberVarDecl.m_pVarDecl);
								if (pMemberVarDecl.m_pVarDecl.m_pTypeRef.m_pTypeToken.m_eType == Token.Type.TOKEN_IDENTIFIER)
								{
									AST pType = null;
									Vector<Symbol> pCandidates = new Vector<Symbol>();
									pValidator.m_pResolver.ResolveFromNode(this, pMemberVarDecl.m_pVarDecl.m_pTypeRef.m_pTypeToken.GetString(), pCandidates);
									if (pCandidates.GetSize() == 1 && pCandidates.Get(0).m_pDeclAST != null && pCandidates.Get(0).m_pDeclAST.m_eType == AST.Type.AST_CLASS_DECL)
										pType = pCandidates.Get(0).m_pDeclAST;
									if (pType != null && pType.m_eType == AST.Type.AST_CLASS_DECL)
									{
										ClassDecl pClassDecl = (ClassDecl)(pType);
										AddClassDeclReference(pClassDecl, AST.OutputFile.SOURCE, false);
									}
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

		public override void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder out)
		{
			if (!m_bPseudo || m_pFirstChild == null || m_pFirstChild != m_pLastChild)
			{
				Util.Pad(nDepth, out.m_sOut);
				out.m_sOut.Append("{\n");
			}
			AST pChild = m_pFirstChild;
			while (pChild != null)
			{
				pChild.Stringify(eLanguage, eOutputFile, nDepth + 1, out);
				pChild = pChild.m_pNextSibling;
			}
			if (!m_bPseudo || m_pFirstChild == null || m_pFirstChild != m_pLastChild)
			{
				Util.Pad(nDepth, out.m_sOut);
				out.m_sOut.Append("}\n");
			}
		}

	}
}

