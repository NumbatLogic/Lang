#line 1 "../../../Source/Core/AST/BaseExpr.nll"
namespace NumbatLogic
{
#line 3 "../../../Source/Core/AST/BaseExpr.nll"
	class BaseExpr : AST
	{
#line 5 "../../../Source/Core/AST/BaseExpr.nll"
		public ClassDecl m_pBaseClassDecl;
#line 7 "../../../Source/Core/AST/BaseExpr.nll"
		public static BaseExpr TryCreate(TokenContainer pTokenContainer, OffsetDatum pOffsetDatum)
		{
#line 9 "../../../Source/Core/AST/BaseExpr.nll"
			OffsetDatum pTempOffset = OffsetDatum.Create(pOffsetDatum);
#line 11 "../../../Source/Core/AST/BaseExpr.nll"
			Token pThisToken = pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_KEYWORD_BASE);
#line 12 "../../../Source/Core/AST/BaseExpr.nll"
			if (pThisToken == null)
			{
#line 13 "../../../Source/Core/AST/BaseExpr.nll"
				return null;
			}
#line 14 "../../../Source/Core/AST/BaseExpr.nll"
			pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
#line 16 "../../../Source/Core/AST/BaseExpr.nll"
			BaseExpr pBaseExpr = new BaseExpr();
#line 18 "../../../Source/Core/AST/BaseExpr.nll"
			pBaseExpr.m_eType = AST.Type.BASE_EXPR;
#line 19 "../../../Source/Core/AST/BaseExpr.nll"
			pBaseExpr.m_pFirstToken = pThisToken;
#line 21 "../../../Source/Core/AST/BaseExpr.nll"
			pOffsetDatum.Set(pTempOffset);
			NumbatLogic.BaseExpr __3152999094 = pBaseExpr;
#line 22 "../../../Source/Core/AST/BaseExpr.nll"
			pBaseExpr = null;
#line 22 "../../../Source/Core/AST/BaseExpr.nll"
			return __3152999094;
		}

#line 25 "../../../Source/Core/AST/BaseExpr.nll"
		public override void Validate(Validator pValidator, OperatorExpr pParent)
		{
#line 27 "../../../Source/Core/AST/BaseExpr.nll"
			m_pValueType = new ValueType(ValueType.Type.CLASS_DECL_VALUE);
#line 29 "../../../Source/Core/AST/BaseExpr.nll"
			AST pTestParent = m_pParent;
#line 30 "../../../Source/Core/AST/BaseExpr.nll"
			while (true)
			{
#line 32 "../../../Source/Core/AST/BaseExpr.nll"
				if (pTestParent == null)
				{
#line 34 "../../../Source/Core/AST/BaseExpr.nll"
					pValidator.AddError("this is not the child of a ClassDec???", m_pFirstToken.m_sFileName, m_pFirstToken.m_nLine, m_pFirstToken.m_nColumn);
#line 35 "../../../Source/Core/AST/BaseExpr.nll"
					return;
				}
#line 38 "../../../Source/Core/AST/BaseExpr.nll"
				if (pTestParent.m_eType == AST.Type.AST_CLASS_DECL)
#line 39 "../../../Source/Core/AST/BaseExpr.nll"
					break;
#line 41 "../../../Source/Core/AST/BaseExpr.nll"
				pTestParent = pTestParent.m_pParent;
			}
#line 44 "../../../Source/Core/AST/BaseExpr.nll"
			ClassDecl pClassDecl = (ClassDecl)(pTestParent);
#line 45 "../../../Source/Core/AST/BaseExpr.nll"
			ClassDecl pBaseClassDecl = pClassDecl.GetBaseClassDecl(pValidator);
#line 47 "../../../Source/Core/AST/BaseExpr.nll"
			if (pBaseClassDecl == null)
			{
#line 49 "../../../Source/Core/AST/BaseExpr.nll"
				pValidator.AddError("class does not have a base class!", m_pFirstToken.m_sFileName, m_pFirstToken.m_nLine, m_pFirstToken.m_nColumn);
#line 50 "../../../Source/Core/AST/BaseExpr.nll"
				return;
			}
#line 53 "../../../Source/Core/AST/BaseExpr.nll"
			m_pValueType.m_pClassDecl = pClassDecl;
#line 55 "../../../Source/Core/AST/BaseExpr.nll"
			m_pBaseClassDecl = pBaseClassDecl;
		}

#line 60 "../../../Source/Core/AST/BaseExpr.nll"
		public override void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder pOutputBuilder)
		{
#line 62 "../../../Source/Core/AST/BaseExpr.nll"
			if (eLanguage == AST.Language.CPP)
#line 63 "../../../Source/Core/AST/BaseExpr.nll"
				m_pBaseClassDecl.m_pNameToken.Stringify(pOutputBuilder.m_sOut);
			else
#line 65 "../../../Source/Core/AST/BaseExpr.nll"
				pOutputBuilder.m_sOut.Append("base");
		}

#line 3 "../../../Source/Core/AST/BaseExpr.nll"
		public BaseExpr()
		{
		}

	}
}

