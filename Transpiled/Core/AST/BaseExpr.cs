#line 1 "../../../Source/Core/AST/BaseExpr.nll"
namespace NumbatLogic
{
#line 4 "../../../Source/Core/AST/BaseExpr.nll"
	class BaseExpr : AST
	{
#line 6 "../../../Source/Core/AST/BaseExpr.nll"
		public ClassDecl m_pBaseClassDecl;
#line 8 "../../../Source/Core/AST/BaseExpr.nll"
		public static BaseExpr TryCreate(TokenContainer pTokenContainer, OffsetDatum pOffsetDatum)
		{
			OffsetDatum pTempOffset = OffsetDatum.Create(pOffsetDatum);
			Token pThisToken = pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_KEYWORD_BASE);
#line 13 "../../../Source/Core/AST/BaseExpr.nll"
			if (pThisToken == null)
			{
#line 14 "../../../Source/Core/AST/BaseExpr.nll"
				return null;
			}
#line 15 "../../../Source/Core/AST/BaseExpr.nll"
			pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
			BaseExpr pBaseExpr = new BaseExpr();
#line 19 "../../../Source/Core/AST/BaseExpr.nll"
			pBaseExpr.m_eType = AST.Type.BASE_EXPR;
#line 20 "../../../Source/Core/AST/BaseExpr.nll"
			pBaseExpr.m_pFirstToken = pThisToken;
#line 22 "../../../Source/Core/AST/BaseExpr.nll"
			pOffsetDatum.Set(pTempOffset);
			NumbatLogic.BaseExpr __3152999094 = pBaseExpr;
#line 23 "../../../Source/Core/AST/BaseExpr.nll"
			pBaseExpr = null;
#line 23 "../../../Source/Core/AST/BaseExpr.nll"
			return __3152999094;
		}

#line 26 "../../../Source/Core/AST/BaseExpr.nll"
		public override void Validate(Validator pValidator, OperatorExpr pParent)
		{
#line 28 "../../../Source/Core/AST/BaseExpr.nll"
			m_pValueType = new ValueType(ValueType.Type.CLASS_DECL_VALUE);
			AST pTestParent = m_pParent;
#line 31 "../../../Source/Core/AST/BaseExpr.nll"
			while (true)
			{
#line 33 "../../../Source/Core/AST/BaseExpr.nll"
				if (pTestParent == null)
				{
#line 35 "../../../Source/Core/AST/BaseExpr.nll"
					pValidator.AddError("this is not the child of a ClassDec???", m_pFirstToken.m_sFileName, m_pFirstToken.m_nLine, m_pFirstToken.m_nColumn);
#line 36 "../../../Source/Core/AST/BaseExpr.nll"
					return;
				}
#line 39 "../../../Source/Core/AST/BaseExpr.nll"
				if (pTestParent.m_eType == AST.Type.AST_CLASS_DECL)
#line 40 "../../../Source/Core/AST/BaseExpr.nll"
					break;
#line 42 "../../../Source/Core/AST/BaseExpr.nll"
				pTestParent = pTestParent.m_pParent;
			}
			ClassDecl pClassDecl = (ClassDecl)(pTestParent);
			ClassDecl pBaseClassDecl = pClassDecl.GetBaseClassDecl(pValidator);
#line 48 "../../../Source/Core/AST/BaseExpr.nll"
			if (pBaseClassDecl == null)
			{
#line 50 "../../../Source/Core/AST/BaseExpr.nll"
				pValidator.AddError("class does not have a base class!", m_pFirstToken.m_sFileName, m_pFirstToken.m_nLine, m_pFirstToken.m_nColumn);
#line 51 "../../../Source/Core/AST/BaseExpr.nll"
				return;
			}
#line 54 "../../../Source/Core/AST/BaseExpr.nll"
			m_pValueType.m_pClassDecl = pClassDecl;
#line 56 "../../../Source/Core/AST/BaseExpr.nll"
			m_pBaseClassDecl = pBaseClassDecl;
		}

#line 61 "../../../Source/Core/AST/BaseExpr.nll"
		public override void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder pOutputBuilder)
		{
#line 63 "../../../Source/Core/AST/BaseExpr.nll"
			if (eLanguage == AST.Language.CPP)
#line 64 "../../../Source/Core/AST/BaseExpr.nll"
				m_pBaseClassDecl.m_pNameToken.Stringify(pOutputBuilder.m_sOut);
			else
#line 66 "../../../Source/Core/AST/BaseExpr.nll"
				pOutputBuilder.m_sOut.Append("base");
		}

#line 4 "../../../Source/Core/AST/BaseExpr.nll"
		public BaseExpr()
		{
		}

	}
}

