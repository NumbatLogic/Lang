#line 1 "/home/cliffya/git/Lang/Source/Core/AST/DeleteStmt.nll"
namespace NumbatLogic
{
	class DeleteStmt : AST
	{
		public AST m_pExpression;
#line 7 "/home/cliffya/git/Lang/Source/Core/AST/DeleteStmt.nll"
		public DeleteStmt()
		{
			m_eType = AST.Type.AST_DELETE_STMT;
			m_bStatement = true;
		}

		public static DeleteStmt TryCreate(TokenContainer pTokenContainer, OffsetDatum pOffsetDatum)
		{
			OffsetDatum pTempOffset = OffsetDatum.Create(pOffsetDatum);
#line 17 "/home/cliffya/git/Lang/Source/Core/AST/DeleteStmt.nll"
			Token pDeleteToken = pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_KEYWORD_DELETE);
			if (pDeleteToken == null)
			{
#line 19 "/home/cliffya/git/Lang/Source/Core/AST/DeleteStmt.nll"
				return null;
			}
#line 20 "/home/cliffya/git/Lang/Source/Core/AST/DeleteStmt.nll"
			pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
#line 22 "/home/cliffya/git/Lang/Source/Core/AST/DeleteStmt.nll"
			AST pExpression = AST.TryCreateExpression(pTokenContainer, pTempOffset);
			if (pExpression == null)
			{
#line 24 "/home/cliffya/git/Lang/Source/Core/AST/DeleteStmt.nll"
				return null;
			}
			if (pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_SEMICOLON) == null)
			{
#line 27 "/home/cliffya/git/Lang/Source/Core/AST/DeleteStmt.nll"
				return null;
			}
#line 28 "/home/cliffya/git/Lang/Source/Core/AST/DeleteStmt.nll"
			pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
#line 30 "/home/cliffya/git/Lang/Source/Core/AST/DeleteStmt.nll"
			DeleteStmt pDelete = new DeleteStmt();
#line 32 "/home/cliffya/git/Lang/Source/Core/AST/DeleteStmt.nll"
			pDelete.m_pFirstToken = pDeleteToken;
			pDelete.m_pExpression = pExpression;
			NumbatLogic.AST __1929399914 = pExpression;
			pExpression = null;
#line 35 "/home/cliffya/git/Lang/Source/Core/AST/DeleteStmt.nll"
			pDelete.AddChild(__1929399914);
#line 37 "/home/cliffya/git/Lang/Source/Core/AST/DeleteStmt.nll"
			pOffsetDatum.Set(pTempOffset);
			NumbatLogic.DeleteStmt __2565256000 = pDelete;
#line 38 "/home/cliffya/git/Lang/Source/Core/AST/DeleteStmt.nll"
			pDelete = null;
#line 38 "/home/cliffya/git/Lang/Source/Core/AST/DeleteStmt.nll"
			return __2565256000;
		}

		public override void Validate(Validator pValidator, OperatorExpr pParent)
		{
			base.Validate(pValidator, pParent);
#line 45 "/home/cliffya/git/Lang/Source/Core/AST/DeleteStmt.nll"
			if (m_pExpression.m_pValueType == null)
			{
				pValidator.AddError("No valuetype for expression???", m_pExpression.m_pFirstToken.m_sFileName, m_pExpression.m_pFirstToken.m_nLine, m_pExpression.m_pFirstToken.m_nColumn);
				return;
			}
#line 51 "/home/cliffya/git/Lang/Source/Core/AST/DeleteStmt.nll"
			if (m_pExpression.m_pValueType.m_pClassDecl != null)
				AddClassDeclReference(m_pExpression.m_pValueType.m_pClassDecl, AST.OutputFile.SOURCE, false);
		}

		public override void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder pOutputBuilder)
		{
			pOutputBuilder.UpdateSourceLocation(eLanguage, m_pFirstToken);
#line 59 "/home/cliffya/git/Lang/Source/Core/AST/DeleteStmt.nll"
			Util.Pad(nDepth, pOutputBuilder.m_sOut);
			pOutputBuilder.m_sOut.Append("{\n");
			nDepth++;
#line 63 "/home/cliffya/git/Lang/Source/Core/AST/DeleteStmt.nll"
			if (eLanguage == AST.Language.CPP)
			{
				Util.Pad(nDepth, pOutputBuilder.m_sOut);
				pOutputBuilder.m_sOut.Append("delete ");
				m_pExpression.Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
				pOutputBuilder.m_sOut.Append(";\n");
			}
			else
#line 70 "/home/cliffya/git/Lang/Source/Core/AST/DeleteStmt.nll"
				if (eLanguage == AST.Language.CS)
				{
					if (m_pExpression.m_pValueType.m_pClassDecl != null && m_pExpression.m_pValueType.m_pClassDecl.m_bDisposable)
					{
						Util.Pad(nDepth, pOutputBuilder.m_sOut);
						pOutputBuilder.m_sOut.Append("(");
						m_pExpression.Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
						pOutputBuilder.m_sOut.Append(").Dispose();\n");
					}
				}
#line 81 "/home/cliffya/git/Lang/Source/Core/AST/DeleteStmt.nll"
			if (m_pExpression.m_eType == AST.Type.AST_IDENTIFIER)
			{
				Util.Pad(nDepth, pOutputBuilder.m_sOut);
				m_pExpression.Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
#line 86 "/home/cliffya/git/Lang/Source/Core/AST/DeleteStmt.nll"
				if (eLanguage == AST.Language.CPP)
					pOutputBuilder.m_sOut.Append(" = 0;\n");
				else
					pOutputBuilder.m_sOut.Append(" = null;\n");
			}
#line 92 "/home/cliffya/git/Lang/Source/Core/AST/DeleteStmt.nll"
			nDepth--;
			Util.Pad(nDepth, pOutputBuilder.m_sOut);
			pOutputBuilder.m_sOut.Append("}\n");
		}

	}
}

