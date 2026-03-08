#line 1 "../../../Source/Core/AST/ReturnStmt.nll"
namespace NumbatLogic
{
	class ReturnStmt : AST
	{
		public AST m_pExpression;
		public ReturnStmt()
		{
			m_eType = AST.Type.AST_RETURN_STMT;
			m_bStatement = true;
		}

		public static ReturnStmt TryCreate(TokenContainer pTokenContainer, OffsetDatum pOffsetDatum)
		{
			OffsetDatum pTempOffset = OffsetDatum.Create(pOffsetDatum);
			Token pReturnToken = pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_KEYWORD_RETURN);
			if (pReturnToken == null)
			{
				return null;
			}
			pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
			AST pExpression = AST.TryCreateExpression(pTokenContainer, pTempOffset);
			if (pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_SEMICOLON) == null)
			{
				return null;
			}
			pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
			ReturnStmt pReturnStmt = new ReturnStmt();
			pReturnStmt.m_pFirstToken = pReturnToken;
			pReturnStmt.m_pExpression = pExpression;
			if (pExpression != null)
			{
				NumbatLogic.AST __1929399913 = pExpression;
				pExpression = null;
				pReturnStmt.AddChild(__1929399913);
			}
			pOffsetDatum.Set(pTempOffset);
			NumbatLogic.ReturnStmt __2739522412 = pReturnStmt;
			pReturnStmt = null;
			return __2739522412;
		}

		public override void Validate(Validator pValidator, OperatorExpr pParent)
		{
			base.Validate(pValidator, pParent);
			pValidator.InjectCleanup(this);
		}

		public override void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder out)
		{
			Util.Pad(nDepth, out.m_sOut);
			out.m_sOut.AppendString("return");
			if (m_pExpression != null)
			{
				out.m_sOut.AppendChar(' ');
				m_pExpression.Stringify(eLanguage, eOutputFile, 0, out);
			}
			out.m_sOut.AppendString(";\n");
		}

	}
}

