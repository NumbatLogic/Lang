namespace NumbatLogic
{
	class FunctionCall : AST
	{
		public string m_sMangledName;
		public ParamCall m_pParamCall;
		public static FunctionCall TryCreate(TokenContainer pTokenContainer, OffsetDatum pOffsetDatum)
		{
			OffsetDatum pTempOffset = OffsetDatum.Create(pOffsetDatum);
			Token pNameToken = pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_IDENTIFIER);
			if (pNameToken == null)
			{
				return null;
			}
			pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
			if (pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_PARENTHESIS_LEFT) == null)
			{
				return null;
			}
			ParamCall pParamCall = ParamCall.TryCreate(pTokenContainer, pTempOffset);
			if (pParamCall == null)
			{
				InternalString sTemp = new InternalString("expected ParamCall ");
				sTemp.Append(pTokenContainer.StringifyOffset(pTempOffset));
				Console.Log(sTemp.GetExternalString());
				NumbatLogic.Assert.Plz(false);
				return null;
			}
			FunctionCall pFunctionCall = new FunctionCall();
			pFunctionCall.m_eType = AST.Type.AST_FUNCTION_CALL;
			pFunctionCall.m_pFirstToken = pNameToken;
			pFunctionCall.m_sMangledName = pNameToken.GetString();
			pFunctionCall.m_pParamCall = pParamCall;
			NumbatLogic.ParamCall __3256575972 = pParamCall;
			pParamCall = null;
			pFunctionCall.AddChild(__3256575972);
			pOffsetDatum.Set(pTempOffset);
			NumbatLogic.FunctionCall __2343173761 = pFunctionCall;
			pFunctionCall = null;
			return __2343173761;
		}

		public override void Validate(Validator pValidator, OperatorExpr pParent)
		{
			string sName = m_pFirstToken.GetString();
			AST pBase = this;
			AST pChild = this;
			if (pParent != null)
			{
				if (pParent.m_pOperatorToken.m_eType == Token.Type.TOKEN_DOT && pParent.m_pLeft.m_pValueType.m_eType == ValueType.Type.CLASS_DECL_VALUE)
				{
					AddClassDeclReference(pParent.m_pLeft.m_pValueType.m_pClassDecl, AST.OutputFile.SOURCE, false);
					pBase = pParent.m_pLeft.m_pValueType.m_pClassDecl;
					pChild = null;
				}
				else
					if (pParent.m_pOperatorToken.m_eType == Token.Type.TOKEN_DOUBLE_COLON)
					{
						if (pParent.m_pLeft.m_pValueType.m_eType == ValueType.Type.CLASS_DECL)
						{
							AddClassDeclReference(pParent.m_pLeft.m_pValueType.m_pClassDecl, AST.OutputFile.SOURCE, false);
							pBase = pParent.m_pLeft.m_pValueType.m_pClassDecl;
							pChild = null;
						}
						else
							if (pParent.m_pLeft.m_pValueType.m_eType == ValueType.Type.ENUM_DECL)
							{
								pBase = pParent.m_pLeft.m_pValueType.m_pEnumDecl;
								pChild = null;
							}
							else
							{
								pValidator.AddError("Unexpected left of ::", m_pFirstToken.m_sFileName, m_pFirstToken.m_nLine, m_pFirstToken.m_nColumn);
								return;
							}
					}
			}
			AST pAST = pBase.FindByName(sName, pChild);
			if (pAST == null)
			{
				InternalString sTemp = new InternalString("Func Unbeknownst! ");
				sTemp.Append(sName);
				pValidator.AddError(sTemp.GetExternalString(), m_pFirstToken.m_sFileName, m_pFirstToken.m_nLine, m_pFirstToken.m_nColumn);
				return;
			}
			FunctionDecl pFunctionDecl = null;
			if (pAST.m_eType == AST.Type.AST_VAR_DECL)
			{
				VarDecl pVarDecl = (VarDecl)(pAST);
				ValueType pValueType = pVarDecl.m_pTypeRef.CreateValueType();
				if (pValueType != null)
				{
					if (pValueType.m_eType == ValueType.Type.DELEGATE_DECL_VALUE)
					{
						if (pValueType.m_pDelegateDecl == null)
						{
							InternalString sTemp = new InternalString("DELEGATE_DECL_VALUE does not have m_pDelegateDecl set???");
							pValidator.AddError(sTemp.GetExternalString(), m_pFirstToken.m_sFileName, m_pFirstToken.m_nLine, m_pFirstToken.m_nColumn);
							return;
						}
						pFunctionDecl = pValueType.m_pDelegateDecl.m_pFunctionDecl;
					}
				}
			}
			if (pAST.m_eType == AST.Type.AST_FUNCTION_DECL)
			{
				pFunctionDecl = (FunctionDecl)(pAST);
			}
			if (pFunctionDecl == null)
			{
				InternalString sTemp = new InternalString("Is not a function? ");
				sTemp.Append(sName);
				sTemp.Append(" ");
				pAST.StringifyType(sTemp);
				pValidator.AddError(sTemp.GetExternalString(), m_pFirstToken.m_sFileName, m_pFirstToken.m_nLine, m_pFirstToken.m_nColumn);
				return;
			}
			if (pParent != null && pParent.m_pLeft != null)
			{
				ValueType pLeftValueType = pParent.m_pLeft.m_pValueType;
				if (pLeftValueType.m_eType == ValueType.Type.CLASS_DECL_VALUE && pLeftValueType.m_pGenericValueTypeVector != null && pLeftValueType.m_pGenericValueTypeVector.GetSize() > 0)
				{
					if (pLeftValueType.m_pGenericValueTypeVector.GetSize() != pLeftValueType.m_pClassDecl.m_pGenericTypeDeclVector.GetSize())
					{
						InternalString sTemp2 = new InternalString("Mismatched generics? ");
						pLeftValueType.StringifyType(sTemp2);
						sTemp2.Append(" ");
						sTemp2.AppendInt(pLeftValueType.m_pGenericValueTypeVector.GetSize());
						sTemp2.Append(" != ");
						sTemp2.Append(pLeftValueType.m_pClassDecl.m_pNameToken.GetString());
						sTemp2.Append(" ");
						sTemp2.AppendInt(pLeftValueType.m_pClassDecl.m_pGenericTypeDeclVector.GetSize());
						pValidator.AddError(sTemp2.GetExternalString(), m_pFirstToken.m_sFileName, m_pFirstToken.m_nLine, m_pFirstToken.m_nColumn);
						return;
					}
					for (int i = 0; i < pLeftValueType.m_pGenericValueTypeVector.GetSize(); i++)
					{
						ValueType pGenericValueType = pLeftValueType.m_pGenericValueTypeVector.Get(i).Clone();
						GenericTypeDecl pGenericTypeDecl = pLeftValueType.m_pClassDecl.m_pGenericTypeDeclVector.Get(i);
						if (ExternalString.Equal(pGenericTypeDecl.m_pFirstToken.GetString(), pFunctionDecl.m_pTypeRef.m_pTypeToken.GetString()))
						{
							NumbatLogic.ValueType __3823392953 = pGenericValueType;
							pGenericValueType = null;
							m_pValueType = __3823392953;
							m_pValueType.m_ePointerType = pFunctionDecl.m_pTypeRef.m_ePointerType;
						}
					}
				}
			}
			if (m_pValueType == null)
			{
				m_pValueType = pFunctionDecl.m_pTypeRef.CreateValueType();
			}
			if (m_pValueType == null)
			{
				InternalString sTemp = new InternalString("could not get valuetype for some reason ");
				sTemp.Append(pFunctionDecl.m_pTypeRef.m_pTypeToken.GetString());
				pValidator.AddError(sTemp.GetExternalString(), m_pFirstToken.m_sFileName, m_pFirstToken.m_nLine, m_pFirstToken.m_nColumn);
			}
			base.Validate(pValidator, pParent);
			if (m_pParamCall.m_pFirstChild == null)
			{
				if (pFunctionDecl.m_pParamDecl.m_pFirstChild != null)
				{
					pValidator.AddError("Params needed for function call?", m_pFirstToken.m_sFileName, m_pFirstToken.m_nLine, m_pFirstToken.m_nColumn);
					return;
				}
			}
			else
			{
				if (!pFunctionDecl.m_pParamDecl.ValidateParamCall(m_pParamCall, pValidator))
					return;
			}
		}

		public override void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, InternalString sOut)
		{
			sOut.Append(m_sMangledName);
			m_pParamCall.Stringify(eLanguage, eOutputFile, 0, sOut);
		}

		public FunctionCall()
		{
		}

	}
}

