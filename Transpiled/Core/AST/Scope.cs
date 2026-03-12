#line 1 "../../../Source/Core/AST/Scope.nll"
namespace NumbatLogic
{
	class Scope : AST
	{
#line 6 "../../../Source/Core/AST/Scope.nll"
		public bool m_bPseudo;
#line 8 "../../../Source/Core/AST/Scope.nll"
		public Scope()
		{
			m_eType = AST.Type.AST_SCOPE;
			m_bPseudo = false;
		}

		public static Scope TryCreate(TokenContainer pTokenContainer, OffsetDatum pOffsetDatum, bool bPseudoScope)
		{
			Scope pScope;
#line 18 "../../../Source/Core/AST/Scope.nll"
			OffsetDatum pTempOffset = OffsetDatum.Create(pOffsetDatum);
#line 20 "../../../Source/Core/AST/Scope.nll"
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
#line 31 "../../../Source/Core/AST/Scope.nll"
						pChild = null;
#line 31 "../../../Source/Core/AST/Scope.nll"
						pScope.AddChild(__356897802);
						pOffsetDatum.Set(pTempOffset);
						NumbatLogic.Scope __1530552932 = pScope;
#line 33 "../../../Source/Core/AST/Scope.nll"
						pScope = null;
#line 33 "../../../Source/Core/AST/Scope.nll"
						return __1530552932;
					}
				}
#line 37 "../../../Source/Core/AST/Scope.nll"
				return null;
			}
#line 40 "../../../Source/Core/AST/Scope.nll"
			pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
#line 42 "../../../Source/Core/AST/Scope.nll"
			pScope = new Scope();
			pScope.m_pFirstToken = pOpeningToken;
#line 45 "../../../Source/Core/AST/Scope.nll"
			while (true)
			{
				Token pClosingToken = pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_CURLY_BRACE_RIGHT);
				if (pClosingToken != null)
				{
					pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
					break;
				}
#line 54 "../../../Source/Core/AST/Scope.nll"
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
#line 63 "../../../Source/Core/AST/Scope.nll"
				pScope.AddChild(__357094601);
			}
#line 66 "../../../Source/Core/AST/Scope.nll"
			pOffsetDatum.Set(pTempOffset);
			NumbatLogic.Scope __1530749733 = pScope;
#line 67 "../../../Source/Core/AST/Scope.nll"
			pScope = null;
#line 67 "../../../Source/Core/AST/Scope.nll"
			return __1530749733;
		}

		public override void Validate(Validator pValidator, OperatorExpr pParent)
		{
			pValidator.BeginScope(this);
#line 75 "../../../Source/Core/AST/Scope.nll"
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
#line 86 "../../../Source/Core/AST/Scope.nll"
					AST pChild = pTorDecl.m_pParent.m_pFirstChild;
					while (pChild != null)
					{
						if (pChild.m_eType == AST.Type.AST_MEMBER_VAR_DECL)
						{
							MemberVarDecl pMemberVarDecl = (MemberVarDecl)(pChild);
#line 93 "../../../Source/Core/AST/Scope.nll"
							if (!pMemberVarDecl.m_bStatic)
							{
								pValidator.AddVarDecl(pMemberVarDecl.m_pVarDecl);
#line 97 "../../../Source/Core/AST/Scope.nll"
								if (pMemberVarDecl.m_pVarDecl.m_pTypeRef.m_pTypeToken.m_eType == Token.Type.TOKEN_IDENTIFIER)
								{
#line 100 "../../../Source/Core/AST/Scope.nll"
									AST pType = null;
									Vector<Symbol> pCandidates = new Vector<Symbol>();
									pValidator.m_pResolver.ResolveFromNode(this, pMemberVarDecl.m_pVarDecl.m_pTypeRef.m_pTypeToken.GetString(), pCandidates);
									if (pCandidates.GetSize() == 1 && pCandidates.Get(0).m_pDeclAST != null && pCandidates.Get(0).m_pDeclAST.m_eType == AST.Type.AST_CLASS_DECL)
										pType = pCandidates.Get(0).m_pDeclAST;
#line 106 "../../../Source/Core/AST/Scope.nll"
									if (pType != null && pType.m_eType == AST.Type.AST_CLASS_DECL)
									{
										ClassDecl pClassDecl = (ClassDecl)(pType);
										AddClassDeclReference(pClassDecl, AST.OutputFile.SOURCE, false);
									}
								}
							}
						}
#line 115 "../../../Source/Core/AST/Scope.nll"
						pChild = pChild.m_pNextSibling;
					}
				}
			}
#line 120 "../../../Source/Core/AST/Scope.nll"
			base.Validate(pValidator, pParent);
#line 122 "../../../Source/Core/AST/Scope.nll"
			pValidator.EndScope(this);
		}

		public override void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder pOutputBuilder)
		{
			if (!m_bPseudo || m_pFirstChild == null || m_pFirstChild != m_pLastChild)
			{
				Util.Pad(nDepth, pOutputBuilder.m_sOut);
				pOutputBuilder.m_sOut.Append("{\n");
			}
#line 133 "../../../Source/Core/AST/Scope.nll"
			AST pChild = m_pFirstChild;
			while (pChild != null)
			{
				pChild.Stringify(eLanguage, eOutputFile, nDepth + 1, pOutputBuilder);
				pChild = pChild.m_pNextSibling;
			}
#line 140 "../../../Source/Core/AST/Scope.nll"
			if (!m_bPseudo || m_pFirstChild == null || m_pFirstChild != m_pLastChild)
			{
				Util.Pad(nDepth, pOutputBuilder.m_sOut);
				pOutputBuilder.m_sOut.Append("}\n");
			}
		}

	}
}

