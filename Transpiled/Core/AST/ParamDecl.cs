#line 1 "../../../Source/Core/AST/ParamDecl.nll"
namespace NumbatLogic
{
	class ParamDecl : AST
	{
		public Vector<VarDecl> m_pParamVector;
#line 7 "../../../Source/Core/AST/ParamDecl.nll"
		public ParamDecl()
		{
			m_eType = AST.Type.AST_PARAM_DECL;
			m_bCanDescend = true;
			m_pParamVector = new Vector<VarDecl>();
		}

		public static ParamDecl TryCreate(TokenContainer pTokenContainer, OffsetDatum pOffsetDatum)
		{
			OffsetDatum pTempOffset = OffsetDatum.Create(pOffsetDatum);
#line 18 "../../../Source/Core/AST/ParamDecl.nll"
			Token m_pFirstToken = pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_PARENTHESIS_LEFT);
#line 20 "../../../Source/Core/AST/ParamDecl.nll"
			if (m_pFirstToken == null)
			{
#line 21 "../../../Source/Core/AST/ParamDecl.nll"
				return null;
			}
#line 22 "../../../Source/Core/AST/ParamDecl.nll"
			pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
#line 25 "../../../Source/Core/AST/ParamDecl.nll"
			ParamDecl pParamDecl = new ParamDecl();
			pParamDecl.m_pFirstToken = m_pFirstToken;
			while (true)
			{
				if (pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_PARENTHESIS_RIGHT) != null)
				{
					pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
					break;
				}
#line 35 "../../../Source/Core/AST/ParamDecl.nll"
				VarDecl pParam = VarDecl.TryCreate(pTokenContainer, pTempOffset, true);
				if (pParam == null)
				{
					Console.Log("expected param");
					Console.Log(pTokenContainer.StringifyOffset(pTempOffset));
					Assert.Plz(false);
				}
#line 43 "../../../Source/Core/AST/ParamDecl.nll"
				pParamDecl.m_pParamVector.PushBack(pParam);
				NumbatLogic.VarDecl __3258004093 = pParam;
#line 44 "../../../Source/Core/AST/ParamDecl.nll"
				pParam = null;
#line 44 "../../../Source/Core/AST/ParamDecl.nll"
				pParamDecl.AddChild(__3258004093);
#line 46 "../../../Source/Core/AST/ParamDecl.nll"
				if (pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_PARENTHESIS_RIGHT) != null)
				{
#line 47 "../../../Source/Core/AST/ParamDecl.nll"
					continue;
				}
				if (pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_COMMA) == null)
				{
					Console.Log("expected comma");
					Console.Log(pTokenContainer.StringifyOffset(pTempOffset));
					Assert.Plz(false);
				}
				pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
			}
#line 58 "../../../Source/Core/AST/ParamDecl.nll"
			pOffsetDatum.Set(pTempOffset);
			NumbatLogic.ParamDecl __3702794795 = pParamDecl;
#line 59 "../../../Source/Core/AST/ParamDecl.nll"
			pParamDecl = null;
#line 59 "../../../Source/Core/AST/ParamDecl.nll"
			return __3702794795;
		}

		public override void Validate(Validator pValidator, OperatorExpr pParent)
		{
			base.Validate(pValidator, pParent);
#line 66 "../../../Source/Core/AST/ParamDecl.nll"
			AST pParam = m_pFirstChild;
			while (pParam != null)
			{
#line 70 "../../../Source/Core/AST/ParamDecl.nll"
				if (pParam.m_eType != AST.Type.AST_VAR_DECL)
				{
					pValidator.AddError("Param not var decl?", pParam.m_pFirstToken.m_sFileName, pParam.m_pFirstToken.m_nLine, pParam.m_pFirstToken.m_nColumn);
					return;
				}
#line 76 "../../../Source/Core/AST/ParamDecl.nll"
				VarDecl pVarDecl = (VarDecl)(pParam);
#line 78 "../../../Source/Core/AST/ParamDecl.nll"
				if (pVarDecl.m_pTypeRef.m_pTypeToken.m_eType == Token.Type.TOKEN_IDENTIFIER)
				{
					if (pVarDecl.m_pTypeRef.m_ePointerType == TypeRef.PointerType.OWNED)
					{
						pValidator.AddError("Param cannot be a owned pointer!", pParam.m_pFirstToken.m_sFileName, pParam.m_pFirstToken.m_nLine, pParam.m_pFirstToken.m_nColumn);
						return;
					}
				}
#line 87 "../../../Source/Core/AST/ParamDecl.nll"
				pParam = pParam.m_pNextSibling;
			}
		}

		public bool ValidateParamCall(ParamCall pParamCall, Validator pValidator, bool bReportErrors)
		{
			int nIndex = 0;
			AST pCallChild = pParamCall.m_pFirstChild;
			AST pDeclChild = m_pFirstChild;
#line 97 "../../../Source/Core/AST/ParamDecl.nll"
			while (true)
			{
				if (pCallChild == null)
				{
					if (pDeclChild == null)
						break;
#line 104 "../../../Source/Core/AST/ParamDecl.nll"
					if (pDeclChild.m_eType == AST.Type.AST_VAR_DECL)
					{
						VarDecl pVarDecl2 = (VarDecl)(pDeclChild);
						if (pVarDecl2.m_pAssignment != null)
						{
							nIndex++;
							pDeclChild = pDeclChild.m_pNextSibling;
							continue;
						}
					}
#line 115 "../../../Source/Core/AST/ParamDecl.nll"
					if (bReportErrors && pValidator != null)
						pValidator.AddError("Param count mismatch (pCallChild == null)", pParamCall.m_pFirstToken.m_sFileName, pParamCall.m_pFirstToken.m_nLine, pParamCall.m_pFirstToken.m_nColumn);
					return false;
				}
				else
#line 119 "../../../Source/Core/AST/ParamDecl.nll"
					if (pDeclChild == null)
					{
						if (bReportErrors && pValidator != null)
							pValidator.AddError("Param count mismatch (pDeclChild == null)", pParamCall.m_pFirstToken.m_sFileName, pParamCall.m_pFirstToken.m_nLine, pParamCall.m_pFirstToken.m_nColumn);
						return false;
					}
#line 126 "../../../Source/Core/AST/ParamDecl.nll"
				if (pCallChild.m_pValueType == null)
				{
					if (bReportErrors && pValidator != null)
					{
						InternalString sTemp = new InternalString("no value type for param at index: ");
						sTemp.AppendInt(nIndex);
						pValidator.AddError(sTemp.GetExternalString(), pCallChild.m_pFirstToken.m_sFileName, pCallChild.m_pFirstToken.m_nLine, pCallChild.m_pFirstToken.m_nColumn);
					}
					return false;
				}
#line 138 "../../../Source/Core/AST/ParamDecl.nll"
				if (pDeclChild.m_eType != AST.Type.AST_VAR_DECL)
				{
					if (bReportErrors && pValidator != null)
					{
						InternalString sTemp = new InternalString("param expected to be var decl at index: ");
						sTemp.AppendInt(nIndex);
						pValidator.AddError(sTemp.GetExternalString(), pCallChild.m_pFirstToken.m_sFileName, pCallChild.m_pFirstToken.m_nLine, pCallChild.m_pFirstToken.m_nColumn);
					}
					return false;
				}
#line 149 "../../../Source/Core/AST/ParamDecl.nll"
				VarDecl pVarDecl = (VarDecl)(pDeclChild);
				ValueType pValueType = pVarDecl.m_pTypeRef.CreateValueType(pValidator.m_pResolver);
#line 152 "../../../Source/Core/AST/ParamDecl.nll"
				if (pValueType == null)
				{
					if (bReportErrors && pValidator != null)
						pValidator.AddError("Unknown decl valuetype???", pCallChild.m_pFirstToken.m_sFileName, pCallChild.m_pFirstToken.m_nLine, pCallChild.m_pFirstToken.m_nColumn);
					return false;
				}
#line 159 "../../../Source/Core/AST/ParamDecl.nll"
				if (pValueType.m_ePointerType == TypeRef.PointerType.TRANSITON && pCallChild.m_pValueType.m_ePointerType != TypeRef.PointerType.TRANSITON && pCallChild.m_pValueType.m_eType != ValueType.Type.NULL_VALUE)
				{
					if (bReportErrors && pValidator != null)
						pValidator.AddError("Must pass a transition pointer!", pCallChild.m_pFirstToken.m_sFileName, pCallChild.m_pFirstToken.m_nLine, pCallChild.m_pFirstToken.m_nColumn);
					return false;
				}
#line 166 "../../../Source/Core/AST/ParamDecl.nll"
				if (pCallChild.m_pValueType.m_ePointerType == TypeRef.PointerType.TRANSITON && pValueType.m_ePointerType != TypeRef.PointerType.TRANSITON)
				{
					if (bReportErrors && pValidator != null)
						pValidator.AddError("Was not expecting a transition pointer??", pCallChild.m_pFirstToken.m_sFileName, pCallChild.m_pFirstToken.m_nLine, pCallChild.m_pFirstToken.m_nColumn);
					return false;
				}
#line 175 "../../../Source/Core/AST/ParamDecl.nll"
				if (pCallChild.m_pValueType.m_eType == ValueType.Type.CLASS_DECL_VALUE || pCallChild.m_pValueType.m_eType == ValueType.Type.GENERIC_TYPE_DECL_VALUE || pCallChild.m_pValueType.m_eType == ValueType.Type.VOIDPTR)
				{
					if (pValueType.m_eType != ValueType.Type.CLASS_DECL_VALUE && pValueType.m_eType != ValueType.Type.GENERIC_TYPE_DECL_VALUE && pValueType.m_eType != ValueType.Type.VOIDPTR)
					{
						if (bReportErrors && pValidator != null)
						{
							InternalString sTemp = new InternalString("type mismatch ");
							pCallChild.m_pValueType.StringifyType(sTemp);
							sTemp.Append(" != ");
							pValueType.StringifyType(sTemp);
							pValidator.AddError(sTemp.GetExternalString(), pCallChild.m_pFirstToken.m_sFileName, pCallChild.m_pFirstToken.m_nLine, pCallChild.m_pFirstToken.m_nColumn);
						}
						return false;
					}
				}
#line 192 "../../../Source/Core/AST/ParamDecl.nll"
				if (pVarDecl.m_pTypeRef.m_bRef)
				{
					if (pCallChild.m_eType != AST.Type.AST_REF_EXPR)
					{
						if (bReportErrors && pValidator != null)
							pValidator.AddError("Must prefix ref parameter with ref!", pCallChild.m_pFirstToken.m_sFileName, pCallChild.m_pFirstToken.m_nLine, pCallChild.m_pFirstToken.m_nColumn);
						return false;
					}
				}
#line 204 "../../../Source/Core/AST/ParamDecl.nll"
				nIndex++;
				pCallChild = pCallChild.m_pNextSibling;
				pDeclChild = pDeclChild.m_pNextSibling;
			}
#line 209 "../../../Source/Core/AST/ParamDecl.nll"
			return true;
		}

		public override void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder pOutputBuilder)
		{
			pOutputBuilder.m_sOut.AppendChar('(');
			AST pParam = m_pFirstChild;
			while (pParam != null)
			{
				if (pParam != m_pFirstChild)
					pOutputBuilder.m_sOut.Append(", ");
				pParam.Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
				pParam = pParam.m_pNextSibling;
			}
			pOutputBuilder.m_sOut.AppendChar(')');
		}

#line 3 "../../../Source/Core/AST/ParamDecl.nll"
		~ParamDecl()
		{
		}

	}
}

