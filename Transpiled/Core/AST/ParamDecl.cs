#line 1 "../../../Source/Core/AST/ParamDecl.nll"
namespace NumbatLogic
{
#line 4 "../../../Source/Core/AST/ParamDecl.nll"
	class ParamDecl : AST
	{
#line 6 "../../../Source/Core/AST/ParamDecl.nll"
		public Vector<VarDecl> m_pParamVector;
#line 8 "../../../Source/Core/AST/ParamDecl.nll"
		public ParamDecl()
		{
#line 10 "../../../Source/Core/AST/ParamDecl.nll"
			m_eType = AST.Type.AST_PARAM_DECL;
#line 11 "../../../Source/Core/AST/ParamDecl.nll"
			m_bCanDescend = true;
#line 12 "../../../Source/Core/AST/ParamDecl.nll"
			m_pParamVector = new Vector<VarDecl>();
		}

#line 15 "../../../Source/Core/AST/ParamDecl.nll"
		public static ParamDecl TryCreate(TokenContainer pTokenContainer, OffsetDatum pOffsetDatum)
		{
			OffsetDatum pTempOffset = OffsetDatum.Create(pOffsetDatum);
			Token m_pFirstToken = pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_PARENTHESIS_LEFT);
#line 21 "../../../Source/Core/AST/ParamDecl.nll"
			if (m_pFirstToken == null)
			{
#line 22 "../../../Source/Core/AST/ParamDecl.nll"
				return null;
			}
#line 23 "../../../Source/Core/AST/ParamDecl.nll"
			pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
			ParamDecl pParamDecl = new ParamDecl();
#line 27 "../../../Source/Core/AST/ParamDecl.nll"
			pParamDecl.m_pFirstToken = m_pFirstToken;
#line 28 "../../../Source/Core/AST/ParamDecl.nll"
			while (true)
			{
#line 30 "../../../Source/Core/AST/ParamDecl.nll"
				if (pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_PARENTHESIS_RIGHT) != null)
				{
#line 32 "../../../Source/Core/AST/ParamDecl.nll"
					pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
#line 33 "../../../Source/Core/AST/ParamDecl.nll"
					break;
				}
				VarDecl pParam = VarDecl.TryCreate(pTokenContainer, pTempOffset, true);
#line 37 "../../../Source/Core/AST/ParamDecl.nll"
				if (pParam == null)
				{
#line 39 "../../../Source/Core/AST/ParamDecl.nll"
					Console.Log("expected param");
#line 40 "../../../Source/Core/AST/ParamDecl.nll"
					Console.Log(pTokenContainer.StringifyOffset(pTempOffset));
#line 41 "../../../Source/Core/AST/ParamDecl.nll"
					Assert.Plz(false);
				}
#line 44 "../../../Source/Core/AST/ParamDecl.nll"
				pParamDecl.m_pParamVector.PushBack(pParam);
				NumbatLogic.VarDecl __3258004093 = pParam;
#line 45 "../../../Source/Core/AST/ParamDecl.nll"
				pParam = null;
#line 45 "../../../Source/Core/AST/ParamDecl.nll"
				pParamDecl.AddChild(__3258004093);
#line 47 "../../../Source/Core/AST/ParamDecl.nll"
				if (pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_PARENTHESIS_RIGHT) != null)
				{
#line 48 "../../../Source/Core/AST/ParamDecl.nll"
					continue;
				}
#line 50 "../../../Source/Core/AST/ParamDecl.nll"
				if (pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_COMMA) == null)
				{
#line 52 "../../../Source/Core/AST/ParamDecl.nll"
					Console.Log("expected comma");
#line 53 "../../../Source/Core/AST/ParamDecl.nll"
					Console.Log(pTokenContainer.StringifyOffset(pTempOffset));
#line 54 "../../../Source/Core/AST/ParamDecl.nll"
					Assert.Plz(false);
				}
#line 56 "../../../Source/Core/AST/ParamDecl.nll"
				pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
			}
#line 59 "../../../Source/Core/AST/ParamDecl.nll"
			pOffsetDatum.Set(pTempOffset);
			NumbatLogic.ParamDecl __3702794795 = pParamDecl;
#line 60 "../../../Source/Core/AST/ParamDecl.nll"
			pParamDecl = null;
#line 60 "../../../Source/Core/AST/ParamDecl.nll"
			return __3702794795;
		}

#line 63 "../../../Source/Core/AST/ParamDecl.nll"
		public override void Validate(Validator pValidator, OperatorExpr pParent)
		{
#line 65 "../../../Source/Core/AST/ParamDecl.nll"
			base.Validate(pValidator, pParent);
			AST pParam = m_pFirstChild;
#line 68 "../../../Source/Core/AST/ParamDecl.nll"
			while (pParam != null)
			{
#line 71 "../../../Source/Core/AST/ParamDecl.nll"
				if (pParam.m_eType != AST.Type.AST_VAR_DECL)
				{
#line 73 "../../../Source/Core/AST/ParamDecl.nll"
					pValidator.AddError("Param not var decl?", pParam.m_pFirstToken.m_sFileName, pParam.m_pFirstToken.m_nLine, pParam.m_pFirstToken.m_nColumn);
#line 74 "../../../Source/Core/AST/ParamDecl.nll"
					return;
				}
				VarDecl pVarDecl = (VarDecl)(pParam);
#line 79 "../../../Source/Core/AST/ParamDecl.nll"
				if (pVarDecl.m_pTypeRef.m_pTypeToken.m_eType == Token.Type.TOKEN_IDENTIFIER)
				{
#line 81 "../../../Source/Core/AST/ParamDecl.nll"
					if (pVarDecl.m_pTypeRef.m_ePointerType == TypeRef.PointerType.OWNED)
					{
#line 83 "../../../Source/Core/AST/ParamDecl.nll"
						pValidator.AddError("Param cannot be a owned pointer!", pParam.m_pFirstToken.m_sFileName, pParam.m_pFirstToken.m_nLine, pParam.m_pFirstToken.m_nColumn);
#line 84 "../../../Source/Core/AST/ParamDecl.nll"
						return;
					}
				}
#line 88 "../../../Source/Core/AST/ParamDecl.nll"
				pParam = pParam.m_pNextSibling;
			}
		}

#line 92 "../../../Source/Core/AST/ParamDecl.nll"
		public bool ValidateParamCall(ParamCall pParamCall, Validator pValidator, bool bReportErrors)
		{
			int nIndex = 0;
			AST pCallChild = pParamCall.m_pFirstChild;
			AST pDeclChild = m_pFirstChild;
#line 98 "../../../Source/Core/AST/ParamDecl.nll"
			while (true)
			{
#line 100 "../../../Source/Core/AST/ParamDecl.nll"
				if (pCallChild == null)
				{
#line 102 "../../../Source/Core/AST/ParamDecl.nll"
					if (pDeclChild == null)
#line 103 "../../../Source/Core/AST/ParamDecl.nll"
						break;
#line 105 "../../../Source/Core/AST/ParamDecl.nll"
					if (pDeclChild.m_eType == AST.Type.AST_VAR_DECL)
					{
						VarDecl pVarDecl2 = (VarDecl)(pDeclChild);
#line 108 "../../../Source/Core/AST/ParamDecl.nll"
						if (pVarDecl2.m_pAssignment != null)
						{
#line 110 "../../../Source/Core/AST/ParamDecl.nll"
							nIndex++;
#line 111 "../../../Source/Core/AST/ParamDecl.nll"
							pDeclChild = pDeclChild.m_pNextSibling;
#line 112 "../../../Source/Core/AST/ParamDecl.nll"
							continue;
						}
					}
#line 116 "../../../Source/Core/AST/ParamDecl.nll"
					if (bReportErrors && pValidator != null)
#line 117 "../../../Source/Core/AST/ParamDecl.nll"
						pValidator.AddError("Param count mismatch (pCallChild == null)", pParamCall.m_pFirstToken.m_sFileName, pParamCall.m_pFirstToken.m_nLine, pParamCall.m_pFirstToken.m_nColumn);
#line 118 "../../../Source/Core/AST/ParamDecl.nll"
					return false;
				}
				else
#line 120 "../../../Source/Core/AST/ParamDecl.nll"
					if (pDeclChild == null)
					{
#line 122 "../../../Source/Core/AST/ParamDecl.nll"
						if (bReportErrors && pValidator != null)
#line 123 "../../../Source/Core/AST/ParamDecl.nll"
							pValidator.AddError("Param count mismatch (pDeclChild == null)", pParamCall.m_pFirstToken.m_sFileName, pParamCall.m_pFirstToken.m_nLine, pParamCall.m_pFirstToken.m_nColumn);
#line 124 "../../../Source/Core/AST/ParamDecl.nll"
						return false;
					}
#line 127 "../../../Source/Core/AST/ParamDecl.nll"
				if (pCallChild.m_pValueType == null)
				{
#line 129 "../../../Source/Core/AST/ParamDecl.nll"
					if (bReportErrors && pValidator != null)
					{
						InternalString sTemp = new InternalString("no value type for param at index: ");
#line 132 "../../../Source/Core/AST/ParamDecl.nll"
						sTemp.AppendInt(nIndex);
#line 133 "../../../Source/Core/AST/ParamDecl.nll"
						pValidator.AddError(sTemp.GetExternalString(), pCallChild.m_pFirstToken.m_sFileName, pCallChild.m_pFirstToken.m_nLine, pCallChild.m_pFirstToken.m_nColumn);
					}
#line 135 "../../../Source/Core/AST/ParamDecl.nll"
					return false;
				}
#line 139 "../../../Source/Core/AST/ParamDecl.nll"
				if (pDeclChild.m_eType != AST.Type.AST_VAR_DECL)
				{
#line 141 "../../../Source/Core/AST/ParamDecl.nll"
					if (bReportErrors && pValidator != null)
					{
						InternalString sTemp = new InternalString("param expected to be var decl at index: ");
#line 144 "../../../Source/Core/AST/ParamDecl.nll"
						sTemp.AppendInt(nIndex);
#line 145 "../../../Source/Core/AST/ParamDecl.nll"
						pValidator.AddError(sTemp.GetExternalString(), pCallChild.m_pFirstToken.m_sFileName, pCallChild.m_pFirstToken.m_nLine, pCallChild.m_pFirstToken.m_nColumn);
					}
#line 147 "../../../Source/Core/AST/ParamDecl.nll"
					return false;
				}
				VarDecl pVarDecl = (VarDecl)(pDeclChild);
				ValueType pValueType = pVarDecl.m_pTypeRef.CreateValueType(pValidator.m_pResolver);
#line 153 "../../../Source/Core/AST/ParamDecl.nll"
				if (pValueType == null)
				{
#line 155 "../../../Source/Core/AST/ParamDecl.nll"
					if (bReportErrors && pValidator != null)
#line 156 "../../../Source/Core/AST/ParamDecl.nll"
						pValidator.AddError("Unknown decl valuetype???", pCallChild.m_pFirstToken.m_sFileName, pCallChild.m_pFirstToken.m_nLine, pCallChild.m_pFirstToken.m_nColumn);
#line 157 "../../../Source/Core/AST/ParamDecl.nll"
					return false;
				}
#line 160 "../../../Source/Core/AST/ParamDecl.nll"
				if (pValueType.m_ePointerType == TypeRef.PointerType.TRANSITON && pCallChild.m_pValueType.m_ePointerType != TypeRef.PointerType.TRANSITON && pCallChild.m_pValueType.m_eType != ValueType.Type.NULL_VALUE)
				{
#line 162 "../../../Source/Core/AST/ParamDecl.nll"
					if (bReportErrors && pValidator != null)
#line 163 "../../../Source/Core/AST/ParamDecl.nll"
						pValidator.AddError("Must pass a transition pointer!", pCallChild.m_pFirstToken.m_sFileName, pCallChild.m_pFirstToken.m_nLine, pCallChild.m_pFirstToken.m_nColumn);
#line 164 "../../../Source/Core/AST/ParamDecl.nll"
					return false;
				}
#line 167 "../../../Source/Core/AST/ParamDecl.nll"
				if (pCallChild.m_pValueType.m_ePointerType == TypeRef.PointerType.TRANSITON && pValueType.m_ePointerType != TypeRef.PointerType.TRANSITON)
				{
#line 169 "../../../Source/Core/AST/ParamDecl.nll"
					if (bReportErrors && pValidator != null)
#line 170 "../../../Source/Core/AST/ParamDecl.nll"
						pValidator.AddError("Was not expecting a transition pointer??", pCallChild.m_pFirstToken.m_sFileName, pCallChild.m_pFirstToken.m_nLine, pCallChild.m_pFirstToken.m_nColumn);
#line 171 "../../../Source/Core/AST/ParamDecl.nll"
					return false;
				}
#line 176 "../../../Source/Core/AST/ParamDecl.nll"
				if (pCallChild.m_pValueType.m_eType == ValueType.Type.CLASS_DECL_VALUE || pCallChild.m_pValueType.m_eType == ValueType.Type.GENERIC_TYPE_DECL_VALUE || pCallChild.m_pValueType.m_eType == ValueType.Type.VOIDPTR)
				{
#line 178 "../../../Source/Core/AST/ParamDecl.nll"
					if (pValueType.m_eType != ValueType.Type.CLASS_DECL_VALUE && pValueType.m_eType != ValueType.Type.GENERIC_TYPE_DECL_VALUE && pValueType.m_eType != ValueType.Type.VOIDPTR)
					{
#line 180 "../../../Source/Core/AST/ParamDecl.nll"
						if (bReportErrors && pValidator != null)
						{
							InternalString sTemp = new InternalString("type mismatch ");
#line 183 "../../../Source/Core/AST/ParamDecl.nll"
							pCallChild.m_pValueType.StringifyType(sTemp);
#line 184 "../../../Source/Core/AST/ParamDecl.nll"
							sTemp.Append(" != ");
#line 185 "../../../Source/Core/AST/ParamDecl.nll"
							pValueType.StringifyType(sTemp);
#line 186 "../../../Source/Core/AST/ParamDecl.nll"
							pValidator.AddError(sTemp.GetExternalString(), pCallChild.m_pFirstToken.m_sFileName, pCallChild.m_pFirstToken.m_nLine, pCallChild.m_pFirstToken.m_nColumn);
						}
#line 188 "../../../Source/Core/AST/ParamDecl.nll"
						return false;
					}
				}
#line 193 "../../../Source/Core/AST/ParamDecl.nll"
				if (pVarDecl.m_pTypeRef.m_bRef)
				{
#line 195 "../../../Source/Core/AST/ParamDecl.nll"
					if (pCallChild.m_eType != AST.Type.AST_REF_EXPR)
					{
#line 197 "../../../Source/Core/AST/ParamDecl.nll"
						if (bReportErrors && pValidator != null)
#line 198 "../../../Source/Core/AST/ParamDecl.nll"
							pValidator.AddError("Must prefix ref parameter with ref!", pCallChild.m_pFirstToken.m_sFileName, pCallChild.m_pFirstToken.m_nLine, pCallChild.m_pFirstToken.m_nColumn);
#line 199 "../../../Source/Core/AST/ParamDecl.nll"
						return false;
					}
				}
#line 205 "../../../Source/Core/AST/ParamDecl.nll"
				nIndex++;
#line 206 "../../../Source/Core/AST/ParamDecl.nll"
				pCallChild = pCallChild.m_pNextSibling;
#line 207 "../../../Source/Core/AST/ParamDecl.nll"
				pDeclChild = pDeclChild.m_pNextSibling;
			}
#line 210 "../../../Source/Core/AST/ParamDecl.nll"
			return true;
		}

#line 213 "../../../Source/Core/AST/ParamDecl.nll"
		public override void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder pOutputBuilder)
		{
#line 215 "../../../Source/Core/AST/ParamDecl.nll"
			pOutputBuilder.m_sOut.AppendChar('(');
			AST pParam = m_pFirstChild;
#line 217 "../../../Source/Core/AST/ParamDecl.nll"
			while (pParam != null)
			{
#line 219 "../../../Source/Core/AST/ParamDecl.nll"
				if (pParam != m_pFirstChild)
#line 220 "../../../Source/Core/AST/ParamDecl.nll"
					pOutputBuilder.m_sOut.Append(", ");
#line 221 "../../../Source/Core/AST/ParamDecl.nll"
				pParam.Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
#line 222 "../../../Source/Core/AST/ParamDecl.nll"
				pParam = pParam.m_pNextSibling;
			}
#line 224 "../../../Source/Core/AST/ParamDecl.nll"
			pOutputBuilder.m_sOut.AppendChar(')');
		}

#line 4 "../../../Source/Core/AST/ParamDecl.nll"
		~ParamDecl()
		{
		}

	}
}

