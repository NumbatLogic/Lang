namespace NumbatLogic
{
	class DeleteStmt : AST
	{
		public AST m_pExpression;
		public DeleteStmt()
		{
			m_eType = AST.Type.AST_DELETE_STMT;
			m_bStatement = true;
		}

		public static DeleteStmt TryCreate(TokenContainer pTokenContainer, OffsetDatum pOffsetDatum)
		{
			OffsetDatum pTempOffset = OffsetDatum.Create(pOffsetDatum);
			Token pDeleteToken = pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_KEYWORD_DELETE);
			if (pDeleteToken == null)
			{
				return null;
			}
			pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
			AST pExpression = AST.TryCreateExpression(pTokenContainer, pTempOffset);
			if (pExpression == null)
			{
				return null;
			}
			if (pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_SEMICOLON) == null)
			{
				return null;
			}
			pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
			DeleteStmt pDelete = new DeleteStmt();
			pDelete.m_pFirstToken = pDeleteToken;
			pDelete.m_pExpression = pExpression;
			NumbatLogic.AST __1067118945 = pExpression;
			pExpression = null;
			pDelete.AddChild(__1067118945);
			pOffsetDatum.Set(pTempOffset);
			NumbatLogic.DeleteStmt __4122039678 = pDelete;
			pDelete = null;
			return __4122039678;
		}

		public override void Validate(Validator pValidator, OperatorExpr pParent)
		{
			base.Validate(pValidator, pParent);
			if (m_pExpression.m_pValueType == null)
			{
				pValidator.AddError("No valuetype for expression???", m_pExpression.m_pFirstToken.m_sFileName, m_pExpression.m_pFirstToken.m_nLine, m_pExpression.m_pFirstToken.m_nColumn);
				return;
			}
			if (m_pExpression.m_pValueType.m_pClassDecl != null)
				AddClassDeclReference(m_pExpression.m_pValueType.m_pClassDecl, AST.OutputFile.SOURCE, false);
		}

		public override void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, InternalString sOut)
		{
			Util.Pad(nDepth, sOut);
			sOut.Append("{\n");
			nDepth++;
			if (eLanguage == AST.Language.CPP)
			{
				Util.Pad(nDepth, sOut);
				sOut.Append("delete ");
				m_pExpression.Stringify(eLanguage, eOutputFile, 0, sOut);
				sOut.Append(";\n");
			}
			if (m_pExpression.m_eType == AST.Type.AST_IDENTIFIER)
			{
				Util.Pad(nDepth, sOut);
				m_pExpression.Stringify(eLanguage, eOutputFile, 0, sOut);
				if (eLanguage == AST.Language.CPP)
					sOut.Append(" = 0;\n");
				else
					sOut.Append(" = null;\n");
			}
			nDepth--;
			Util.Pad(nDepth, sOut);
			sOut.Append("}\n");
		}

	}
}

