#line 1 "../../../Source/Core/AST/NamespaceDecl.nll"
namespace NumbatLogic
{
#line 3 "../../../Source/Core/AST/NamespaceDecl.nll"
	class NamespaceDecl : AST
	{
#line 5 "../../../Source/Core/AST/NamespaceDecl.nll"
		public Token m_pNameToken;
#line 6 "../../../Source/Core/AST/NamespaceDecl.nll"
		public NamespaceNode m_pNamespaceNode;
#line 8 "../../../Source/Core/AST/NamespaceDecl.nll"
		public NamespaceDecl()
		{
#line 10 "../../../Source/Core/AST/NamespaceDecl.nll"
			m_eType = AST.Type.NAMESPACE_DECL;
#line 11 "../../../Source/Core/AST/NamespaceDecl.nll"
			m_bCanDescend = true;
		}

#line 14 "../../../Source/Core/AST/NamespaceDecl.nll"
		public static NamespaceDecl TryCreate(TokenContainer pTokenContainer, OffsetDatum pOffsetDatum)
		{
#line 16 "../../../Source/Core/AST/NamespaceDecl.nll"
			OffsetDatum pTempOffset = OffsetDatum.Create(pOffsetDatum);
#line 18 "../../../Source/Core/AST/NamespaceDecl.nll"
			Token pNamespaceToken = pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_KEYWORD_NAMESPACE);
#line 19 "../../../Source/Core/AST/NamespaceDecl.nll"
			if (pNamespaceToken == null)
			{
#line 20 "../../../Source/Core/AST/NamespaceDecl.nll"
				return null;
			}
#line 21 "../../../Source/Core/AST/NamespaceDecl.nll"
			pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
#line 23 "../../../Source/Core/AST/NamespaceDecl.nll"
			NamespaceDecl pNamespaceDecl = new NamespaceDecl();
#line 25 "../../../Source/Core/AST/NamespaceDecl.nll"
			Token pNameToken = pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_IDENTIFIER);
#line 26 "../../../Source/Core/AST/NamespaceDecl.nll"
			if (pNameToken == null)
			{
#line 28 "../../../Source/Core/AST/NamespaceDecl.nll"
				Console.Log("expected namespace name");
#line 29 "../../../Source/Core/AST/NamespaceDecl.nll"
				Console.Log(pTokenContainer.StringifyOffset(pTempOffset));
#line 30 "../../../Source/Core/AST/NamespaceDecl.nll"
				Assert.Plz(false);
#line 31 "../../../Source/Core/AST/NamespaceDecl.nll"
				return null;
			}
#line 33 "../../../Source/Core/AST/NamespaceDecl.nll"
			pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
#line 35 "../../../Source/Core/AST/NamespaceDecl.nll"
			if (pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_CURLY_BRACE_LEFT) == null)
			{
#line 37 "../../../Source/Core/AST/NamespaceDecl.nll"
				Console.Log("expected opening curly brace");
#line 38 "../../../Source/Core/AST/NamespaceDecl.nll"
				Console.Log(pTokenContainer.StringifyOffset(pTempOffset));
#line 39 "../../../Source/Core/AST/NamespaceDecl.nll"
				Assert.Plz(false);
#line 40 "../../../Source/Core/AST/NamespaceDecl.nll"
				return null;
			}
#line 42 "../../../Source/Core/AST/NamespaceDecl.nll"
			pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
#line 44 "../../../Source/Core/AST/NamespaceDecl.nll"
			pNamespaceDecl.m_pFirstToken = pNamespaceToken;
#line 45 "../../../Source/Core/AST/NamespaceDecl.nll"
			pNamespaceDecl.m_pNameToken = pNameToken;
#line 47 "../../../Source/Core/AST/NamespaceDecl.nll"
			while (true)
			{
#line 49 "../../../Source/Core/AST/NamespaceDecl.nll"
				if (pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_CURLY_BRACE_RIGHT) != null)
				{
#line 51 "../../../Source/Core/AST/NamespaceDecl.nll"
					pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
#line 52 "../../../Source/Core/AST/NamespaceDecl.nll"
					break;
				}
#line 55 "../../../Source/Core/AST/NamespaceDecl.nll"
				AST pAST = AST.CreateFromTokenContainer(pTokenContainer, pTempOffset);
#line 56 "../../../Source/Core/AST/NamespaceDecl.nll"
				if (pAST != null)
				{
					NumbatLogic.AST __834042965 = pAST;
#line 58 "../../../Source/Core/AST/NamespaceDecl.nll"
					pAST = null;
#line 58 "../../../Source/Core/AST/NamespaceDecl.nll"
					pNamespaceDecl.AddChild(__834042965);
#line 59 "../../../Source/Core/AST/NamespaceDecl.nll"
					continue;
				}
#line 62 "../../../Source/Core/AST/NamespaceDecl.nll"
				Console.Log("expected to parse somethting within namespace...");
#line 63 "../../../Source/Core/AST/NamespaceDecl.nll"
				Console.Log(pTokenContainer.StringifyOffset(pTempOffset));
#line 64 "../../../Source/Core/AST/NamespaceDecl.nll"
				Assert.Plz(false);
			}
#line 68 "../../../Source/Core/AST/NamespaceDecl.nll"
			pOffsetDatum.Set(pTempOffset);
			NumbatLogic.NamespaceDecl __1424002840 = pNamespaceDecl;
#line 69 "../../../Source/Core/AST/NamespaceDecl.nll"
			pNamespaceDecl = null;
#line 69 "../../../Source/Core/AST/NamespaceDecl.nll"
			return __1424002840;
		}

#line 72 "../../../Source/Core/AST/NamespaceDecl.nll"
		public override void PreValidate(Validator pValidator, OperatorExpr pParent)
		{
#line 74 "../../../Source/Core/AST/NamespaceDecl.nll"
			string sxName = m_pNameToken.GetString();
#line 75 "../../../Source/Core/AST/NamespaceDecl.nll"
			pValidator.BeginNamespace(sxName);
#line 76 "../../../Source/Core/AST/NamespaceDecl.nll"
			base.PreValidate(pValidator, pParent);
#line 77 "../../../Source/Core/AST/NamespaceDecl.nll"
			pValidator.EndNamespace(sxName);
		}

#line 80 "../../../Source/Core/AST/NamespaceDecl.nll"
		public override void Validate(Validator pValidator, OperatorExpr pParent)
		{
#line 82 "../../../Source/Core/AST/NamespaceDecl.nll"
			string sxName = m_pNameToken.GetString();
#line 83 "../../../Source/Core/AST/NamespaceDecl.nll"
			pValidator.BeginNamespace(sxName);
#line 84 "../../../Source/Core/AST/NamespaceDecl.nll"
			base.Validate(pValidator, pParent);
#line 85 "../../../Source/Core/AST/NamespaceDecl.nll"
			pValidator.EndNamespace(sxName);
		}

#line 88 "../../../Source/Core/AST/NamespaceDecl.nll"
		public override void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder pOutputBuilder)
		{
#line 90 "../../../Source/Core/AST/NamespaceDecl.nll"
			pOutputBuilder.UpdateSourceLocation(eLanguage, m_pFirstToken);
#line 92 "../../../Source/Core/AST/NamespaceDecl.nll"
			Util.Pad(nDepth, pOutputBuilder.m_sOut);
#line 93 "../../../Source/Core/AST/NamespaceDecl.nll"
			pOutputBuilder.m_sOut.Append("namespace ");
#line 94 "../../../Source/Core/AST/NamespaceDecl.nll"
			m_pNameToken.Stringify(pOutputBuilder.m_sOut);
#line 95 "../../../Source/Core/AST/NamespaceDecl.nll"
			pOutputBuilder.m_sOut.Append("\n");
#line 97 "../../../Source/Core/AST/NamespaceDecl.nll"
			Util.Pad(nDepth, pOutputBuilder.m_sOut);
#line 98 "../../../Source/Core/AST/NamespaceDecl.nll"
			pOutputBuilder.m_sOut.Append("{\n");
#line 99 "../../../Source/Core/AST/NamespaceDecl.nll"
			nDepth++;
#line 101 "../../../Source/Core/AST/NamespaceDecl.nll"
			AST pChild = m_pFirstChild;
#line 102 "../../../Source/Core/AST/NamespaceDecl.nll"
			while (pChild != null)
			{
#line 104 "../../../Source/Core/AST/NamespaceDecl.nll"
				pChild.Stringify(eLanguage, eOutputFile, nDepth, pOutputBuilder);
#line 105 "../../../Source/Core/AST/NamespaceDecl.nll"
				pChild = pChild.m_pNextSibling;
			}
#line 108 "../../../Source/Core/AST/NamespaceDecl.nll"
			nDepth--;
#line 109 "../../../Source/Core/AST/NamespaceDecl.nll"
			Util.Pad(nDepth, pOutputBuilder.m_sOut);
#line 110 "../../../Source/Core/AST/NamespaceDecl.nll"
			pOutputBuilder.m_sOut.Append("}\n");
		}

	}
}

