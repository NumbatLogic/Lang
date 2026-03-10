#line 1 "../../../Source/Core/AST/Scope.nll"
namespace NumbatLogic
{
#line 3 "../../../Source/Core/AST/Scope.nll"
	class Scope : AST
	{
#line 6 "../../../Source/Core/AST/Scope.nll"
		public bool m_bPseudo;
#line 8 "../../../Source/Core/AST/Scope.nll"
		public Scope()
		{
#line 10 "../../../Source/Core/AST/Scope.nll"
			m_eType = AST.Type.AST_SCOPE;
#line 11 "../../../Source/Core/AST/Scope.nll"
			m_bPseudo = false;
		}

#line 14 "../../../Source/Core/AST/Scope.nll"
		public static Scope TryCreate(TokenContainer pTokenContainer, OffsetDatum pOffsetDatum, bool bPseudoScope)
		{
#line 16 "../../../Source/Core/AST/Scope.nll"
			Scope pScope;
#line 18 "../../../Source/Core/AST/Scope.nll"
			OffsetDatum pTempOffset = OffsetDatum.Create(pOffsetDatum);
#line 20 "../../../Source/Core/AST/Scope.nll"
			Token pOpeningToken = pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_CURLY_BRACE_LEFT);
#line 21 "../../../Source/Core/AST/Scope.nll"
			if (pOpeningToken == null)
			{
#line 23 "../../../Source/Core/AST/Scope.nll"
				if (bPseudoScope)
				{
#line 25 "../../../Source/Core/AST/Scope.nll"
					AST pChild = AST.CreateStatementFromTokenContainer(pTokenContainer, pTempOffset);
#line 26 "../../../Source/Core/AST/Scope.nll"
					if (pChild != null)
					{
#line 28 "../../../Source/Core/AST/Scope.nll"
						pScope = new Scope();
#line 29 "../../../Source/Core/AST/Scope.nll"
						pScope.m_pFirstToken = pChild.m_pFirstToken;
#line 30 "../../../Source/Core/AST/Scope.nll"
						pScope.m_bPseudo = true;
						NumbatLogic.AST __356897802 = pChild;
#line 31 "../../../Source/Core/AST/Scope.nll"
						pChild = null;
#line 31 "../../../Source/Core/AST/Scope.nll"
						pScope.AddChild(__356897802);
#line 32 "../../../Source/Core/AST/Scope.nll"
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
#line 43 "../../../Source/Core/AST/Scope.nll"
			pScope.m_pFirstToken = pOpeningToken;
#line 45 "../../../Source/Core/AST/Scope.nll"
			while (true)
			{
#line 47 "../../../Source/Core/AST/Scope.nll"
				Token pClosingToken = pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_CURLY_BRACE_RIGHT);
#line 48 "../../../Source/Core/AST/Scope.nll"
				if (pClosingToken != null)
				{
#line 50 "../../../Source/Core/AST/Scope.nll"
					pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
#line 51 "../../../Source/Core/AST/Scope.nll"
					break;
				}
#line 54 "../../../Source/Core/AST/Scope.nll"
				AST pChild = AST.CreateStatementFromTokenContainer(pTokenContainer, pTempOffset);
#line 55 "../../../Source/Core/AST/Scope.nll"
				if (pChild == null)
				{
#line 57 "../../../Source/Core/AST/Scope.nll"
					Console.Log("expected to parse somethting within scope...");
#line 58 "../../../Source/Core/AST/Scope.nll"
					Console.Log(pTokenContainer.StringifyOffset(pTempOffset));
#line 59 "../../../Source/Core/AST/Scope.nll"
					Assert.Plz(false);
#line 60 "../../../Source/Core/AST/Scope.nll"
					return null;
				}
				NumbatLogic.AST __357094601 = pChild;
#line 63 "../../../Source/Core/AST/Scope.nll"
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

#line 70 "../../../Source/Core/AST/Scope.nll"
		public override void Validate(Validator pValidator, OperatorExpr pParent)
		{
#line 72 "../../../Source/Core/AST/Scope.nll"
			pValidator.BeginScope(this);
#line 75 "../../../Source/Core/AST/Scope.nll"
			if (m_pParent.m_eType == AST.Type.AST_TOR_DECL)
			{
#line 77 "../../../Source/Core/AST/Scope.nll"
				TorDecl pTorDecl = (TorDecl)(m_pParent);
#line 78 "../../../Source/Core/AST/Scope.nll"
				if (pTorDecl.m_pTypeToken.m_eType == Token.Type.TOKEN_KEYWORD_DESTRUCT)
				{
#line 80 "../../../Source/Core/AST/Scope.nll"
					if (pTorDecl.m_pParent.m_eType != AST.Type.AST_CLASS_DECL)
					{
#line 82 "../../../Source/Core/AST/Scope.nll"
						pValidator.AddError("Expected parent TorDecl to be child of AST_CLASS_DECL", m_pFirstToken.m_sFileName, m_pFirstToken.m_nLine, m_pFirstToken.m_nColumn);
#line 83 "../../../Source/Core/AST/Scope.nll"
						return;
					}
#line 86 "../../../Source/Core/AST/Scope.nll"
					AST pChild = pTorDecl.m_pParent.m_pFirstChild;
#line 87 "../../../Source/Core/AST/Scope.nll"
					while (pChild != null)
					{
#line 89 "../../../Source/Core/AST/Scope.nll"
						if (pChild.m_eType == AST.Type.AST_MEMBER_VAR_DECL)
						{
#line 91 "../../../Source/Core/AST/Scope.nll"
							MemberVarDecl pMemberVarDecl = (MemberVarDecl)(pChild);
#line 93 "../../../Source/Core/AST/Scope.nll"
							if (!pMemberVarDecl.m_bStatic)
							{
#line 95 "../../../Source/Core/AST/Scope.nll"
								pValidator.AddVarDecl(pMemberVarDecl.m_pVarDecl);
#line 97 "../../../Source/Core/AST/Scope.nll"
								if (pMemberVarDecl.m_pVarDecl.m_pTypeRef.m_pTypeToken.m_eType == Token.Type.TOKEN_IDENTIFIER)
								{
#line 100 "../../../Source/Core/AST/Scope.nll"
									AST pType = null;
#line 101 "../../../Source/Core/AST/Scope.nll"
									Vector<Symbol> pCandidates = new Vector<Symbol>();
#line 102 "../../../Source/Core/AST/Scope.nll"
									pValidator.m_pResolver.ResolveFromNode(this, pMemberVarDecl.m_pVarDecl.m_pTypeRef.m_pTypeToken.GetString(), pCandidates);
#line 103 "../../../Source/Core/AST/Scope.nll"
									if (pCandidates.GetSize() == 1 && pCandidates.Get(0).m_pDeclAST != null && pCandidates.Get(0).m_pDeclAST.m_eType == AST.Type.AST_CLASS_DECL)
#line 104 "../../../Source/Core/AST/Scope.nll"
										pType = pCandidates.Get(0).m_pDeclAST;
#line 106 "../../../Source/Core/AST/Scope.nll"
									if (pType != null && pType.m_eType == AST.Type.AST_CLASS_DECL)
									{
#line 108 "../../../Source/Core/AST/Scope.nll"
										ClassDecl pClassDecl = (ClassDecl)(pType);
#line 109 "../../../Source/Core/AST/Scope.nll"
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

#line 125 "../../../Source/Core/AST/Scope.nll"
		public override void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder pOutputBuilder)
		{
#line 127 "../../../Source/Core/AST/Scope.nll"
			if (!m_bPseudo || m_pFirstChild == null || m_pFirstChild != m_pLastChild)
			{
#line 129 "../../../Source/Core/AST/Scope.nll"
				Util.Pad(nDepth, pOutputBuilder.m_sOut);
#line 130 "../../../Source/Core/AST/Scope.nll"
				pOutputBuilder.m_sOut.Append("{\n");
			}
#line 133 "../../../Source/Core/AST/Scope.nll"
			AST pChild = m_pFirstChild;
#line 134 "../../../Source/Core/AST/Scope.nll"
			while (pChild != null)
			{
#line 136 "../../../Source/Core/AST/Scope.nll"
				pChild.Stringify(eLanguage, eOutputFile, nDepth + 1, pOutputBuilder);
#line 137 "../../../Source/Core/AST/Scope.nll"
				pChild = pChild.m_pNextSibling;
			}
#line 140 "../../../Source/Core/AST/Scope.nll"
			if (!m_bPseudo || m_pFirstChild == null || m_pFirstChild != m_pLastChild)
			{
#line 142 "../../../Source/Core/AST/Scope.nll"
				Util.Pad(nDepth, pOutputBuilder.m_sOut);
#line 143 "../../../Source/Core/AST/Scope.nll"
				pOutputBuilder.m_sOut.Append("}\n");
			}
		}

	}
}

