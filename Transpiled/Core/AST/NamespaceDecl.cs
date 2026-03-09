#line 1 "../../../Source/Core/AST/NamespaceDecl.nll"
namespace NumbatLogic
{
#line 4 "../../../Source/Core/AST/NamespaceDecl.nll"
	class NamespaceDecl : AST
	{
#line 6 "../../../Source/Core/AST/NamespaceDecl.nll"
		public Token m_pNameToken;
#line 7 "../../../Source/Core/AST/NamespaceDecl.nll"
		public NamespaceNode m_pNamespaceNode;
#line 9 "../../../Source/Core/AST/NamespaceDecl.nll"
		public NamespaceDecl()
		{
#line 11 "../../../Source/Core/AST/NamespaceDecl.nll"
			m_eType = AST.Type.NAMESPACE_DECL;
#line 12 "../../../Source/Core/AST/NamespaceDecl.nll"
			m_bCanDescend = true;
		}

#line 15 "../../../Source/Core/AST/NamespaceDecl.nll"
		public static NamespaceDecl TryCreate(TokenContainer pTokenContainer, OffsetDatum pOffsetDatum)
		{
			OffsetDatum pTempOffset = OffsetDatum.Create(pOffsetDatum);
			Token pNamespaceToken = pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_KEYWORD_NAMESPACE);
#line 20 "../../../Source/Core/AST/NamespaceDecl.nll"
			if (pNamespaceToken == null)
			{
#line 21 "../../../Source/Core/AST/NamespaceDecl.nll"
				return null;
			}
#line 22 "../../../Source/Core/AST/NamespaceDecl.nll"
			pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
			NamespaceDecl pNamespaceDecl = new NamespaceDecl();
			Token pNameToken = pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_IDENTIFIER);
#line 27 "../../../Source/Core/AST/NamespaceDecl.nll"
			if (pNameToken == null)
			{
#line 29 "../../../Source/Core/AST/NamespaceDecl.nll"
				Console.Log("expected namespace name");
#line 30 "../../../Source/Core/AST/NamespaceDecl.nll"
				Console.Log(pTokenContainer.StringifyOffset(pTempOffset));
#line 31 "../../../Source/Core/AST/NamespaceDecl.nll"
				Assert.Plz(false);
#line 32 "../../../Source/Core/AST/NamespaceDecl.nll"
				return null;
			}
#line 34 "../../../Source/Core/AST/NamespaceDecl.nll"
			pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
#line 36 "../../../Source/Core/AST/NamespaceDecl.nll"
			if (pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_CURLY_BRACE_LEFT) == null)
			{
#line 38 "../../../Source/Core/AST/NamespaceDecl.nll"
				Console.Log("expected opening curly brace");
#line 39 "../../../Source/Core/AST/NamespaceDecl.nll"
				Console.Log(pTokenContainer.StringifyOffset(pTempOffset));
#line 40 "../../../Source/Core/AST/NamespaceDecl.nll"
				Assert.Plz(false);
#line 41 "../../../Source/Core/AST/NamespaceDecl.nll"
				return null;
			}
#line 43 "../../../Source/Core/AST/NamespaceDecl.nll"
			pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
#line 45 "../../../Source/Core/AST/NamespaceDecl.nll"
			pNamespaceDecl.m_pFirstToken = pNamespaceToken;
#line 46 "../../../Source/Core/AST/NamespaceDecl.nll"
			pNamespaceDecl.m_pNameToken = pNameToken;
#line 48 "../../../Source/Core/AST/NamespaceDecl.nll"
			while (true)
			{
#line 50 "../../../Source/Core/AST/NamespaceDecl.nll"
				if (pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_CURLY_BRACE_RIGHT) != null)
				{
#line 52 "../../../Source/Core/AST/NamespaceDecl.nll"
					pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
#line 53 "../../../Source/Core/AST/NamespaceDecl.nll"
					break;
				}
				AST pAST = AST.CreateFromTokenContainer(pTokenContainer, pTempOffset);
#line 57 "../../../Source/Core/AST/NamespaceDecl.nll"
				if (pAST != null)
				{
					NumbatLogic.AST __834042965 = pAST;
#line 59 "../../../Source/Core/AST/NamespaceDecl.nll"
					pAST = null;
#line 59 "../../../Source/Core/AST/NamespaceDecl.nll"
					pNamespaceDecl.AddChild(__834042965);
#line 60 "../../../Source/Core/AST/NamespaceDecl.nll"
					continue;
				}
#line 63 "../../../Source/Core/AST/NamespaceDecl.nll"
				Console.Log("expected to parse somethting within namespace...");
#line 64 "../../../Source/Core/AST/NamespaceDecl.nll"
				Console.Log(pTokenContainer.StringifyOffset(pTempOffset));
#line 65 "../../../Source/Core/AST/NamespaceDecl.nll"
				Assert.Plz(false);
			}
#line 69 "../../../Source/Core/AST/NamespaceDecl.nll"
			pOffsetDatum.Set(pTempOffset);
			NumbatLogic.NamespaceDecl __1424002840 = pNamespaceDecl;
#line 70 "../../../Source/Core/AST/NamespaceDecl.nll"
			pNamespaceDecl = null;
#line 70 "../../../Source/Core/AST/NamespaceDecl.nll"
			return __1424002840;
		}

#line 73 "../../../Source/Core/AST/NamespaceDecl.nll"
		public override void PreValidate(Validator pValidator, OperatorExpr pParent)
		{
			string sxName = m_pNameToken.GetString();
#line 76 "../../../Source/Core/AST/NamespaceDecl.nll"
			pValidator.BeginNamespace(sxName);
#line 77 "../../../Source/Core/AST/NamespaceDecl.nll"
			base.PreValidate(pValidator, pParent);
#line 78 "../../../Source/Core/AST/NamespaceDecl.nll"
			pValidator.EndNamespace(sxName);
		}

#line 81 "../../../Source/Core/AST/NamespaceDecl.nll"
		public override void Validate(Validator pValidator, OperatorExpr pParent)
		{
			string sxName = m_pNameToken.GetString();
#line 84 "../../../Source/Core/AST/NamespaceDecl.nll"
			pValidator.BeginNamespace(sxName);
#line 85 "../../../Source/Core/AST/NamespaceDecl.nll"
			base.Validate(pValidator, pParent);
#line 86 "../../../Source/Core/AST/NamespaceDecl.nll"
			pValidator.EndNamespace(sxName);
		}

#line 89 "../../../Source/Core/AST/NamespaceDecl.nll"
		public override void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder pOutputBuilder)
		{
#line 91 "../../../Source/Core/AST/NamespaceDecl.nll"
			pOutputBuilder.UpdateSourceLocation(eLanguage, m_pFirstToken);
#line 93 "../../../Source/Core/AST/NamespaceDecl.nll"
			Util.Pad(nDepth, pOutputBuilder.m_sOut);
#line 94 "../../../Source/Core/AST/NamespaceDecl.nll"
			pOutputBuilder.m_sOut.Append("namespace ");
#line 95 "../../../Source/Core/AST/NamespaceDecl.nll"
			m_pNameToken.Stringify(pOutputBuilder.m_sOut);
#line 96 "../../../Source/Core/AST/NamespaceDecl.nll"
			pOutputBuilder.m_sOut.Append("\n");
#line 98 "../../../Source/Core/AST/NamespaceDecl.nll"
			Util.Pad(nDepth, pOutputBuilder.m_sOut);
#line 99 "../../../Source/Core/AST/NamespaceDecl.nll"
			pOutputBuilder.m_sOut.Append("{\n");
#line 100 "../../../Source/Core/AST/NamespaceDecl.nll"
			nDepth++;
			AST pChild = m_pFirstChild;
#line 103 "../../../Source/Core/AST/NamespaceDecl.nll"
			while (pChild != null)
			{
#line 105 "../../../Source/Core/AST/NamespaceDecl.nll"
				pChild.Stringify(eLanguage, eOutputFile, nDepth, pOutputBuilder);
#line 106 "../../../Source/Core/AST/NamespaceDecl.nll"
				pChild = pChild.m_pNextSibling;
			}
#line 109 "../../../Source/Core/AST/NamespaceDecl.nll"
			nDepth--;
#line 110 "../../../Source/Core/AST/NamespaceDecl.nll"
			Util.Pad(nDepth, pOutputBuilder.m_sOut);
#line 111 "../../../Source/Core/AST/NamespaceDecl.nll"
			pOutputBuilder.m_sOut.Append("}\n");
		}

	}
}

