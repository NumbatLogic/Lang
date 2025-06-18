namespace NumbatLogic
{
	class NamespaceDecl : AST
	{
		public Token m_pNameToken;
		public NamespaceNode m_pNamespaceNode;
		public NamespaceDecl()
		{
			m_eType = AST.Type.NAMESPACE_DECL;
			m_bCanDescend = true;
		}

		public static NamespaceDecl TryCreate(TokenContainer pTokenContainer, OffsetDatum pOffsetDatum)
		{
			OffsetDatum pTempOffset = OffsetDatum.Create(pOffsetDatum);
			Token pNamespaceToken = pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_KEYWORD_NAMESPACE);
			if (pNamespaceToken == null)
			{
				return null;
			}
			pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
			NamespaceDecl pNamespaceDecl = new NamespaceDecl();
			Token pNameToken = pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_IDENTIFIER);
			if (pNameToken == null)
			{
				Console.Log("expected namespace name");
				Console.Log(pTokenContainer.StringifyOffset(pTempOffset));
				NumbatLogic.Assert.Plz(false);
				{
					return null;
				}
			}
			pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
			if (pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_CURLY_BRACE_LEFT) == null)
			{
				Console.Log("expected opening curly brace");
				Console.Log(pTokenContainer.StringifyOffset(pTempOffset));
				NumbatLogic.Assert.Plz(false);
				{
					return null;
				}
			}
			pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
			pNamespaceDecl.m_pFirstToken = pNamespaceToken;
			pNamespaceDecl.m_pNameToken = pNameToken;
			while (true)
			{
				if (pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_CURLY_BRACE_RIGHT) != null)
				{
					pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
					break;
				}
				AST pAST = AST.CreateFromTokenContainer(pTokenContainer, pTempOffset);
				if (pAST != null)
				{
					{
						NumbatLogic.AST __3125986036 = pAST;
						pAST = null;
						pNamespaceDecl.AddChild(__3125986036);
					}
					{
						continue;
					}
				}
				Console.Log("expected to parse somethting within namespace...");
				Console.Log(pTokenContainer.StringifyOffset(pTempOffset));
				NumbatLogic.Assert.Plz(false);
			}
			pOffsetDatum.Set(pTempOffset);
			{
				NumbatLogic.NamespaceDecl __2577615172 = pNamespaceDecl;
				pNamespaceDecl = null;
				{
					return __2577615172;
				}
			}
		}

		public override void PreValidate(Validator pValidator, OperatorExpr pParent)
		{
			string sxName = m_pNameToken.GetString();
			pValidator.BeginNamespace(sxName);
			base.PreValidate(pValidator, pParent);
			pValidator.EndNamespace(sxName);
		}

		public override void Validate(Validator pValidator, OperatorExpr pParent)
		{
			string sxName = m_pNameToken.GetString();
			pValidator.BeginNamespace(sxName);
			base.Validate(pValidator, pParent);
			pValidator.EndNamespace(sxName);
		}

		protected AST SubFindByName(string sxName, AST pCallingChild)
		{
			return base.FindByName(sxName, pCallingChild);
		}

		public override AST FindByName(string sxName, AST pCallingChild)
		{
			if (ExternalString.Equal(sxName, m_pNameToken.GetString()))
				return this;
			AST pFound = SubFindByName(sxName, pCallingChild);
			if (pFound != null)
				return pFound;
			NamespaceNode pFoundNamespace = m_pNamespaceNode.FindByName(sxName, pCallingChild == null);
			if (pFoundNamespace != null)
				return pFoundNamespace.m_pNamespaceDeclVector.Get(0);
			for (int i = 0; i < m_pNamespaceNode.m_pNamespaceDeclVector.GetSize(); i++)
			{
				NamespaceDecl pNamespaceDecl = m_pNamespaceNode.m_pNamespaceDeclVector.Get(i);
				if (pNamespaceDecl != this)
				{
					ClassDecl pClassDecl = pNamespaceDecl.FindClassDecl(sxName, null);
					if (pClassDecl != null)
					{
						if (pClassDecl.m_pNameToken != null)
							return pClassDecl;
						return pClassDecl;
					}
				}
			}
			return null;
		}

		public override void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, InternalString sOut)
		{
			Util.Pad(nDepth, sOut);
			sOut.Append("namespace ");
			m_pNameToken.Stringify(sOut);
			sOut.Append("\n");
			Util.Pad(nDepth, sOut);
			sOut.Append("{\n");
			nDepth++;
			AST pChild = m_pFirstChild;
			while (pChild != null)
			{
				pChild.Stringify(eLanguage, eOutputFile, nDepth, sOut);
				pChild = pChild.m_pNextSibling;
			}
			nDepth--;
			Util.Pad(nDepth, sOut);
			sOut.Append("}\n");
		}

	}
}

