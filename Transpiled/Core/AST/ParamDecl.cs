namespace NumbatLogic
{
	class ParamDecl : AST
	{
		public Vector<VarDecl> m_pParamVector;
		public ParamDecl()
		{
			m_eType = AST.Type.AST_PARAM_DECL;
			m_bCanDescend = true;
			m_pParamVector = new Vector<VarDecl>();
		}

		public static ParamDecl TryCreate(TokenContainer pTokenContainer, OffsetDatum pOffsetDatum)
		{
			OffsetDatum pTempOffset = OffsetDatum.Create(pOffsetDatum);
			Token m_pFirstToken = pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_PARENTHESIS_LEFT);
			if (m_pFirstToken == null)
			{
				return null;
			}
			pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
			ParamDecl pParamDecl = new ParamDecl();
			pParamDecl.m_pFirstToken = m_pFirstToken;
			while (true)
			{
				if (pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_PARENTHESIS_RIGHT) != null)
				{
					pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
					break;
				}
				VarDecl pParam = VarDecl.TryCreate(pTokenContainer, pTempOffset, true);
				if (pParam == null)
				{
					Console.Log("expected param");
					Console.Log(pTokenContainer.StringifyOffset(pTempOffset));
					NumbatLogic.Assert.Plz(false);
				}
				pParamDecl.m_pParamVector.PushBack(pParam);
				NumbatLogic.VarDecl __658120647 = pParam;
				pParam = null;
				pParamDecl.AddChild(__658120647);
				if (pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_PARENTHESIS_RIGHT) != null)
				{
					continue;
				}
				if (pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_COMMA) == null)
				{
					Console.Log("expected comma");
					Console.Log(pTokenContainer.StringifyOffset(pTempOffset));
					NumbatLogic.Assert.Plz(false);
				}
				pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
			}
			pOffsetDatum.Set(pTempOffset);
			NumbatLogic.ParamDecl __3963700199 = pParamDecl;
			pParamDecl = null;
			return __3963700199;
		}

		public override void Validate(Validator pValidator, OperatorExpr pParent)
		{
			base.Validate(pValidator, pParent);
			AST pParam = m_pFirstChild;
			while (pParam != null)
			{
				if (pParam.m_eType != AST.Type.AST_VAR_DECL)
				{
					pValidator.AddError("Param not var decl?", pParam.m_pFirstToken.m_sFileName, pParam.m_pFirstToken.m_nLine, pParam.m_pFirstToken.m_nColumn);
					return;
				}
				VarDecl pVarDecl = (VarDecl)(pParam);
				if (pVarDecl.m_pTypeRef.m_pTypeToken.m_eType == Token.Type.TOKEN_IDENTIFIER)
				{
					if (pVarDecl.m_pTypeRef.m_ePointerType == TypeRef.PointerType.OWNED)
					{
						pValidator.AddError("Param cannot be a owned pointer!", pParam.m_pFirstToken.m_sFileName, pParam.m_pFirstToken.m_nLine, pParam.m_pFirstToken.m_nColumn);
						return;
					}
				}
				pParam = pParam.m_pNextSibling;
			}
		}

		public bool ValidateParamCall(ParamCall pParamCall, Validator pValidator)
		{
			int nIndex = 0;
			AST pCallChild = pParamCall.m_pFirstChild;
			AST pDeclChild = m_pFirstChild;
			while (true)
			{
				if (pCallChild == null)
				{
					if (pDeclChild == null)
						break;
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
					if (pValidator != null)
						pValidator.AddError("Param count mismatch (pCallChild == null)", pParamCall.m_pFirstToken.m_sFileName, pParamCall.m_pFirstToken.m_nLine, pParamCall.m_pFirstToken.m_nColumn);
					return false;
				}
				else
					if (pDeclChild == null)
					{
						if (pValidator != null)
							pValidator.AddError("Param count mismatch (pDeclChild == null)", pParamCall.m_pFirstToken.m_sFileName, pParamCall.m_pFirstToken.m_nLine, pParamCall.m_pFirstToken.m_nColumn);
						return false;
					}
				if (pCallChild.m_pValueType == null)
				{
					if (pValidator != null)
					{
						InternalString sTemp = new InternalString("no value type for param at index: ");
						sTemp.AppendInt(nIndex);
						pValidator.AddError(sTemp.GetExternalString(), pCallChild.m_pFirstToken.m_sFileName, pCallChild.m_pFirstToken.m_nLine, pCallChild.m_pFirstToken.m_nColumn);
					}
					return false;
				}
				if (pDeclChild.m_eType != AST.Type.AST_VAR_DECL)
				{
					if (pValidator != null)
					{
						InternalString sTemp = new InternalString("param expected to be var decl at index: ");
						sTemp.AppendInt(nIndex);
						pValidator.AddError(sTemp.GetExternalString(), pCallChild.m_pFirstToken.m_sFileName, pCallChild.m_pFirstToken.m_nLine, pCallChild.m_pFirstToken.m_nColumn);
					}
					return false;
				}
				VarDecl pVarDecl = (VarDecl)(pDeclChild);
				ValueType pValueType = pVarDecl.m_pTypeRef.CreateValueType();
				if (pValueType == null)
				{
					if (pValidator != null)
						pValidator.AddError("Unknown decl valuetype???", pCallChild.m_pFirstToken.m_sFileName, pCallChild.m_pFirstToken.m_nLine, pCallChild.m_pFirstToken.m_nColumn);
					return false;
				}
				if (pValueType.m_ePointerType == TypeRef.PointerType.TRANSITON && pCallChild.m_pValueType.m_ePointerType != TypeRef.PointerType.TRANSITON && pCallChild.m_pValueType.m_eType != ValueType.Type.NULL_VALUE)
				{
					if (pValidator != null)
						pValidator.AddError("Must pass a transition pointer!", pCallChild.m_pFirstToken.m_sFileName, pCallChild.m_pFirstToken.m_nLine, pCallChild.m_pFirstToken.m_nColumn);
					return false;
				}
				if (pCallChild.m_pValueType.m_ePointerType == TypeRef.PointerType.TRANSITON && pValueType.m_ePointerType != TypeRef.PointerType.TRANSITON)
				{
					if (pValidator != null)
						pValidator.AddError("Was not expecting a transition pointer??", pCallChild.m_pFirstToken.m_sFileName, pCallChild.m_pFirstToken.m_nLine, pCallChild.m_pFirstToken.m_nColumn);
					return false;
				}
				if (pCallChild.m_pValueType.m_eType == ValueType.Type.CLASS_DECL_VALUE || pCallChild.m_pValueType.m_eType == ValueType.Type.GENERIC_TYPE_DECL_VALUE || pCallChild.m_pValueType.m_eType == ValueType.Type.VOIDPTR)
				{
					if (pValueType.m_eType != ValueType.Type.CLASS_DECL_VALUE && pValueType.m_eType != ValueType.Type.GENERIC_TYPE_DECL_VALUE && pValueType.m_eType != ValueType.Type.VOIDPTR)
					{
						if (pValidator != null)
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
				if (pVarDecl.m_pTypeRef.m_bRef)
				{
					if (pCallChild.m_eType != AST.Type.AST_REF_EXPR)
					{
						pValidator.AddError("Must prefix ref parameter with ref!", pCallChild.m_pFirstToken.m_sFileName, pCallChild.m_pFirstToken.m_nLine, pCallChild.m_pFirstToken.m_nColumn);
						return false;
					}
				}
				nIndex++;
				pCallChild = pCallChild.m_pNextSibling;
				pDeclChild = pDeclChild.m_pNextSibling;
			}
			return true;
		}

		public override void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, InternalString sOut)
		{
			sOut.AppendChar('(');
			AST pParam = m_pFirstChild;
			while (pParam != null)
			{
				if (pParam != m_pFirstChild)
					sOut.Append(", ");
				pParam.Stringify(eLanguage, eOutputFile, 0, sOut);
				pParam = pParam.m_pNextSibling;
			}
			sOut.AppendChar(')');
		}

		~ParamDecl()
		{
		}

	}
}

