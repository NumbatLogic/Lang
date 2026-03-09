#line 1 "../../../Source/Core/AST/DeleteStmt.nll"
namespace NumbatLogic
{
#line 4 "../../../Source/Core/AST/DeleteStmt.nll"
	class DeleteStmt : AST
	{
#line 6 "../../../Source/Core/AST/DeleteStmt.nll"
		public AST m_pExpression;
#line 8 "../../../Source/Core/AST/DeleteStmt.nll"
		public DeleteStmt()
		{
#line 10 "../../../Source/Core/AST/DeleteStmt.nll"
			m_eType = AST.Type.AST_DELETE_STMT;
#line 11 "../../../Source/Core/AST/DeleteStmt.nll"
			m_bStatement = true;
		}

#line 14 "../../../Source/Core/AST/DeleteStmt.nll"
		public static DeleteStmt TryCreate(TokenContainer pTokenContainer, OffsetDatum pOffsetDatum)
		{
			OffsetDatum pTempOffset = OffsetDatum.Create(pOffsetDatum);
			Token pDeleteToken = pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_KEYWORD_DELETE);
#line 19 "../../../Source/Core/AST/DeleteStmt.nll"
			if (pDeleteToken == null)
			{
#line 20 "../../../Source/Core/AST/DeleteStmt.nll"
				return null;
			}
#line 21 "../../../Source/Core/AST/DeleteStmt.nll"
			pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
			AST pExpression = AST.TryCreateExpression(pTokenContainer, pTempOffset);
#line 24 "../../../Source/Core/AST/DeleteStmt.nll"
			if (pExpression == null)
			{
#line 25 "../../../Source/Core/AST/DeleteStmt.nll"
				return null;
			}
#line 27 "../../../Source/Core/AST/DeleteStmt.nll"
			if (pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_SEMICOLON) == null)
			{
#line 28 "../../../Source/Core/AST/DeleteStmt.nll"
				return null;
			}
#line 29 "../../../Source/Core/AST/DeleteStmt.nll"
			pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
			DeleteStmt pDelete = new DeleteStmt();
#line 33 "../../../Source/Core/AST/DeleteStmt.nll"
			pDelete.m_pFirstToken = pDeleteToken;
#line 34 "../../../Source/Core/AST/DeleteStmt.nll"
			pDelete.m_pExpression = pExpression;
			NumbatLogic.AST __1929399914 = pExpression;
#line 36 "../../../Source/Core/AST/DeleteStmt.nll"
			pExpression = null;
#line 36 "../../../Source/Core/AST/DeleteStmt.nll"
			pDelete.AddChild(__1929399914);
#line 38 "../../../Source/Core/AST/DeleteStmt.nll"
			pOffsetDatum.Set(pTempOffset);
			NumbatLogic.DeleteStmt __2565256000 = pDelete;
#line 39 "../../../Source/Core/AST/DeleteStmt.nll"
			pDelete = null;
#line 39 "../../../Source/Core/AST/DeleteStmt.nll"
			return __2565256000;
		}

#line 42 "../../../Source/Core/AST/DeleteStmt.nll"
		public override void Validate(Validator pValidator, OperatorExpr pParent)
		{
#line 44 "../../../Source/Core/AST/DeleteStmt.nll"
			base.Validate(pValidator, pParent);
#line 46 "../../../Source/Core/AST/DeleteStmt.nll"
			if (m_pExpression.m_pValueType == null)
			{
#line 48 "../../../Source/Core/AST/DeleteStmt.nll"
				pValidator.AddError("No valuetype for expression???", m_pExpression.m_pFirstToken.m_sFileName, m_pExpression.m_pFirstToken.m_nLine, m_pExpression.m_pFirstToken.m_nColumn);
#line 49 "../../../Source/Core/AST/DeleteStmt.nll"
				return;
			}
#line 52 "../../../Source/Core/AST/DeleteStmt.nll"
			if (m_pExpression.m_pValueType.m_pClassDecl != null)
#line 53 "../../../Source/Core/AST/DeleteStmt.nll"
				AddClassDeclReference(m_pExpression.m_pValueType.m_pClassDecl, AST.OutputFile.SOURCE, false);
		}

#line 56 "../../../Source/Core/AST/DeleteStmt.nll"
		public override void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder pOutputBuilder)
		{
#line 58 "../../../Source/Core/AST/DeleteStmt.nll"
			pOutputBuilder.UpdateSourceLocation(eLanguage, m_pFirstToken);
#line 60 "../../../Source/Core/AST/DeleteStmt.nll"
			Util.Pad(nDepth, pOutputBuilder.m_sOut);
#line 61 "../../../Source/Core/AST/DeleteStmt.nll"
			pOutputBuilder.m_sOut.Append("{\n");
#line 62 "../../../Source/Core/AST/DeleteStmt.nll"
			nDepth++;
#line 64 "../../../Source/Core/AST/DeleteStmt.nll"
			if (eLanguage == AST.Language.CPP)
			{
#line 66 "../../../Source/Core/AST/DeleteStmt.nll"
				Util.Pad(nDepth, pOutputBuilder.m_sOut);
#line 67 "../../../Source/Core/AST/DeleteStmt.nll"
				pOutputBuilder.m_sOut.Append("delete ");
#line 68 "../../../Source/Core/AST/DeleteStmt.nll"
				m_pExpression.Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
#line 69 "../../../Source/Core/AST/DeleteStmt.nll"
				pOutputBuilder.m_sOut.Append(";\n");
			}
			else
#line 71 "../../../Source/Core/AST/DeleteStmt.nll"
				if (eLanguage == AST.Language.CS)
				{
#line 73 "../../../Source/Core/AST/DeleteStmt.nll"
					if (m_pExpression.m_pValueType.m_pClassDecl != null && m_pExpression.m_pValueType.m_pClassDecl.m_bDisposable)
					{
#line 75 "../../../Source/Core/AST/DeleteStmt.nll"
						Util.Pad(nDepth, pOutputBuilder.m_sOut);
#line 76 "../../../Source/Core/AST/DeleteStmt.nll"
						pOutputBuilder.m_sOut.Append("(");
#line 77 "../../../Source/Core/AST/DeleteStmt.nll"
						m_pExpression.Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
#line 78 "../../../Source/Core/AST/DeleteStmt.nll"
						pOutputBuilder.m_sOut.Append(").Dispose();\n");
					}
				}
#line 82 "../../../Source/Core/AST/DeleteStmt.nll"
			if (m_pExpression.m_eType == AST.Type.AST_IDENTIFIER)
			{
#line 84 "../../../Source/Core/AST/DeleteStmt.nll"
				Util.Pad(nDepth, pOutputBuilder.m_sOut);
#line 85 "../../../Source/Core/AST/DeleteStmt.nll"
				m_pExpression.Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
#line 87 "../../../Source/Core/AST/DeleteStmt.nll"
				if (eLanguage == AST.Language.CPP)
#line 88 "../../../Source/Core/AST/DeleteStmt.nll"
					pOutputBuilder.m_sOut.Append(" = 0;\n");
				else
#line 90 "../../../Source/Core/AST/DeleteStmt.nll"
					pOutputBuilder.m_sOut.Append(" = null;\n");
			}
#line 93 "../../../Source/Core/AST/DeleteStmt.nll"
			nDepth--;
#line 94 "../../../Source/Core/AST/DeleteStmt.nll"
			Util.Pad(nDepth, pOutputBuilder.m_sOut);
#line 95 "../../../Source/Core/AST/DeleteStmt.nll"
			pOutputBuilder.m_sOut.Append("}\n");
		}

	}
}

