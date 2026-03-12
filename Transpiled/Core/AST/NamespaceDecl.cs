#line 1 "../../../Source/Core/AST/NamespaceDecl.nll"
namespace NumbatLogic
{
	class NamespaceDecl : AST
	{
		public Token m_pNameToken;
		public NamespaceNode m_pNamespaceNode;
#line 8 "../../../Source/Core/AST/NamespaceDecl.nll"
		public NamespaceDecl()
		{
			m_eType = AST.Type.NAMESPACE_DECL;
			m_bCanDescend = true;
		}

		public static NamespaceDecl TryCreate(TokenContainer pTokenContainer, OffsetDatum pOffsetDatum)
		{
			OffsetDatum pTempOffset = OffsetDatum.Create(pOffsetDatum);
#line 18 "../../../Source/Core/AST/NamespaceDecl.nll"
			Token pNamespaceToken = pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_KEYWORD_NAMESPACE);
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
			if (pNameToken == null)
			{
				Console.Log("expected namespace name");
				Console.Log(pTokenContainer.StringifyOffset(pTempOffset));
				Assert.Plz(false);
				return null;
			}
			pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
#line 35 "../../../Source/Core/AST/NamespaceDecl.nll"
			if (pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_CURLY_BRACE_LEFT) == null)
			{
				Console.Log("expected opening curly brace");
				Console.Log(pTokenContainer.StringifyOffset(pTempOffset));
				Assert.Plz(false);
				return null;
			}
			pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
#line 44 "../../../Source/Core/AST/NamespaceDecl.nll"
			pNamespaceDecl.m_pFirstToken = pNamespaceToken;
			pNamespaceDecl.m_pNameToken = pNameToken;
#line 47 "../../../Source/Core/AST/NamespaceDecl.nll"
			while (true)
			{
				if (pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_CURLY_BRACE_RIGHT) != null)
				{
					pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
					break;
				}
#line 55 "../../../Source/Core/AST/NamespaceDecl.nll"
				AST pAST = AST.CreateFromTokenContainer(pTokenContainer, pTempOffset);
				if (pAST != null)
				{
					NumbatLogic.AST __834042965 = pAST;
#line 58 "../../../Source/Core/AST/NamespaceDecl.nll"
					pAST = null;
#line 58 "../../../Source/Core/AST/NamespaceDecl.nll"
					pNamespaceDecl.AddChild(__834042965);
					continue;
				}
#line 62 "../../../Source/Core/AST/NamespaceDecl.nll"
				Console.Log("expected to parse somethting within namespace...");
				Console.Log(pTokenContainer.StringifyOffset(pTempOffset));
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

		public override void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder pOutputBuilder)
		{
			pOutputBuilder.UpdateSourceLocation(eLanguage, m_pFirstToken);
#line 92 "../../../Source/Core/AST/NamespaceDecl.nll"
			Util.Pad(nDepth, pOutputBuilder.m_sOut);
			pOutputBuilder.m_sOut.Append("namespace ");
			m_pNameToken.Stringify(pOutputBuilder.m_sOut);
			pOutputBuilder.m_sOut.Append("\n");
#line 97 "../../../Source/Core/AST/NamespaceDecl.nll"
			Util.Pad(nDepth, pOutputBuilder.m_sOut);
			pOutputBuilder.m_sOut.Append("{\n");
			nDepth++;
#line 101 "../../../Source/Core/AST/NamespaceDecl.nll"
			AST pChild = m_pFirstChild;
			while (pChild != null)
			{
				pChild.Stringify(eLanguage, eOutputFile, nDepth, pOutputBuilder);
				pChild = pChild.m_pNextSibling;
			}
#line 108 "../../../Source/Core/AST/NamespaceDecl.nll"
			nDepth--;
			Util.Pad(nDepth, pOutputBuilder.m_sOut);
			pOutputBuilder.m_sOut.Append("}\n");
		}

	}
}

