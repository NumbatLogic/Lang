namespace NumbatLogic
{
	class OperatorExpr : AST
	{
		public Token m_pOperatorToken;
		public AST m_pLeft;
		public AST m_pRight;
		public Token m_pOwnedOperatorToken;
		public OperatorExpr()
		{
			m_eType = AST.Type.AST_OPERATOR_EXPR;
		}

		public static OperatorExpr Create(Token pOperatorToken, AST pLeft, AST pRight)
		{
			OperatorExpr pOperatorExpr = new OperatorExpr();
			AST pOwnedLeft = pLeft;
			AST pOwnedRight = pRight;
			pOperatorExpr.m_pFirstToken = pLeft.m_pFirstToken;
			pOperatorExpr.m_pOperatorToken = pOperatorToken;
			pOperatorExpr.m_pLeft = pOwnedLeft;
			pOperatorExpr.m_pRight = pOwnedRight;
			if (pLeft != null)
			{
				NumbatLogic.AST __2216975023 = pOwnedLeft;
				pOwnedLeft = null;
				pOperatorExpr.AddChild(__2216975023);
			}
			if (pRight != null)
			{
				NumbatLogic.AST __766380242 = pOwnedRight;
				pOwnedRight = null;
				pOperatorExpr.AddChild(__766380242);
			}
			NumbatLogic.OperatorExpr __304301329 = pOperatorExpr;
			pOperatorExpr = null;
			return __304301329;
		}

		public override AST BaseClone()
		{
			AST pLeft = null;
			AST pRight = null;
			if (m_pLeft != null)
				pLeft = m_pLeft.BaseClone();
			if (m_pRight != null)
				pRight = m_pRight.BaseClone();
			NumbatLogic.AST __2461073728 = pLeft;
			pLeft = null;
			NumbatLogic.AST __1625873296 = pRight;
			pRight = null;
			return Create(m_pOperatorToken, __2461073728, __1625873296);
		}

		public override void Validate(Validator pValidator, OperatorExpr pParent)
		{
			if (m_pLeft != null)
			{
				m_pLeft.Validate(pValidator, pParent);
				if (m_pLeft.m_pValueType == null)
				{
					pValidator.AddError("No ValueType for left of operator: ", m_pLeft.m_pFirstToken.m_sFileName, m_pLeft.m_pFirstToken.m_nLine, m_pLeft.m_pFirstToken.m_nColumn);
					return;
				}
				else
				{
					if (m_pLeft.m_pValueType.m_eType == ValueType.Type.CLASS_DECL || m_pLeft.m_pValueType.m_eType == ValueType.Type.ENUM_DECL || m_pLeft.m_pValueType.m_eType == ValueType.Type.NAMESPACE_NODE)
					{
						if (m_pOperatorToken.m_eType != Token.Type.TOKEN_DOUBLE_COLON)
						{
							pValidator.AddError("Expected TOKEN_DOUBLE_COLON ", m_pOperatorToken.m_sFileName, m_pOperatorToken.m_nLine, m_pOperatorToken.m_nColumn);
							return;
						}
						if (m_pRight == null)
						{
							pValidator.AddError("Expected right side of TOKEN_DOUBLE_COLON operator", m_pOperatorToken.m_sFileName, m_pOperatorToken.m_nLine, m_pOperatorToken.m_nColumn);
							return;
						}
						if (m_pRight.m_eType != AST.Type.AST_IDENTIFIER && m_pRight.m_eType != AST.Type.AST_OPERATOR_EXPR && m_pRight.m_eType != AST.Type.AST_FUNCTION_CALL && m_pRight.m_eType != AST.Type.AST_ARRAY_LOOKUP)
						{
							InternalString sTemp = new InternalString("Unexpected right side of TOKEN_DOUBLE_COLON operator: ");
							m_pRight.StringifyType(sTemp);
							pValidator.AddError(sTemp.GetExternalString(), m_pOperatorToken.m_sFileName, m_pOperatorToken.m_nLine, m_pOperatorToken.m_nColumn);
							return;
						}
						m_pRight.Validate(pValidator, this);
						if (m_pRight.m_pValueType == null)
						{
							pValidator.AddError("No ValueType for right of operator: ", m_pRight.m_pFirstToken.m_sFileName, m_pRight.m_pFirstToken.m_nLine, m_pRight.m_pFirstToken.m_nColumn);
							return;
						}
						m_pValueType = m_pRight.m_pValueType.Clone();
						return;
					}
					if (m_pOperatorToken.m_eType == Token.Type.TOKEN_DOT)
					{
						if (m_pLeft.m_pValueType.m_eType == ValueType.Type.GENERIC_TYPE_DECL_VALUE)
						{
							if (m_pLeft.m_pValueType.m_pGenericTypeDecl == null)
							{
								pValidator.AddError(" set but m_pGenericTypeDecl is null???", m_pOperatorToken.m_sFileName, m_pOperatorToken.m_nLine, m_pOperatorToken.m_nColumn);
								return;
							}
						}
						else
							if (m_pLeft.m_pValueType.m_eType == ValueType.Type.CLASS_DECL_VALUE)
							{
								if (m_pLeft.m_pValueType.m_pClassDecl == null)
								{
									pValidator.AddError(" set but m_pClassDecl is null???", m_pOperatorToken.m_sFileName, m_pOperatorToken.m_nLine, m_pOperatorToken.m_nColumn);
									return;
								}
							}
							else
							{
								pValidator.AddError("Expected ValueType::Type::CLASS_DECL_VALUE or ValueType::Type::GENERIC_TYPE_DECL_VALUE on left of TOKEN_DOT operator", m_pOperatorToken.m_sFileName, m_pOperatorToken.m_nLine, m_pOperatorToken.m_nColumn);
								return;
							}
						m_pRight.Validate(pValidator, this);
						if (m_pRight.m_pValueType == null)
						{
							pValidator.AddError("No ValueType for right of operator: ", m_pRight.m_pFirstToken.m_sFileName, m_pRight.m_pFirstToken.m_nLine, m_pRight.m_pFirstToken.m_nColumn);
							return;
						}
						m_pValueType = m_pRight.m_pValueType.Clone();
						return;
					}
					if (m_pOperatorToken.m_eType == Token.Type.TOKEN_PLUS)
					{
						if (m_pLeft.m_pValueType.m_eType == ValueType.Type.STRING)
						{
							pValidator.AddError("Cannot concat strings with +", m_pOperatorToken.m_sFileName, m_pOperatorToken.m_nLine, m_pOperatorToken.m_nColumn);
							return;
						}
					}
					if (m_pOperatorToken.m_eType == Token.Type.TOKEN_DOUBLE_EQUALS || m_pOperatorToken.m_eType == Token.Type.TOKEN_NOT_EQUALS)
					{
						if (m_pRight == null)
						{
							pValidator.AddError("Nohing on right side to compare?", m_pOperatorToken.m_sFileName, m_pOperatorToken.m_nLine, m_pOperatorToken.m_nColumn);
							return;
						}
						m_pRight.Validate(pValidator, this);
						if (m_pLeft.m_pValueType.m_eType == ValueType.Type.STRING && m_pRight.m_pValueType.m_eType == ValueType.Type.STRING)
						{
							pValidator.AddError("Cannot == or != strings use ExternalString::Equal", m_pOperatorToken.m_sFileName, m_pOperatorToken.m_nLine, m_pOperatorToken.m_nColumn);
							return;
						}
						m_pValueType = new ValueType(ValueType.Type.BOOL);
						return;
					}
					if (m_pRight != null)
						m_pRight.Validate(pValidator, this);
					if (m_pOperatorToken.m_eType == Token.Type.TOKEN_EQUALS)
					{
						if (m_pRight.m_pValueType == null)
						{
							pValidator.AddError("No ValueType for right of operator = ???", m_pRight.m_pFirstToken.m_sFileName, m_pRight.m_pFirstToken.m_nLine, m_pRight.m_pFirstToken.m_nColumn);
							return;
						}
						if (m_pLeft.m_pValueType.m_eType == ValueType.Type.CLASS_DECL_VALUE)
						{
							if (m_pRight.m_pValueType.m_eType == ValueType.Type.CLASS_DECL_VALUE)
							{
								if (m_pLeft.m_pValueType.m_ePointerType == TypeRef.PointerType.OWNED && m_pRight.m_pValueType.m_ePointerType != TypeRef.PointerType.OWNED_PREASSSIGN)
								{
									pValidator.AddError("Expected right side of = to be OWNED_PREASSSIGN (result of own)", m_pOperatorToken.m_sFileName, m_pOperatorToken.m_nLine, m_pOperatorToken.m_nColumn);
									return;
								}
								if (m_pLeft.m_pValueType.m_ePointerType == TypeRef.PointerType.SHARED && m_pRight.m_pValueType.m_ePointerType == TypeRef.PointerType.OWNED_PREASSSIGN)
								{
									pValidator.AddError("Can't store an owned pointer in a shared pointer", m_pOperatorToken.m_sFileName, m_pOperatorToken.m_nLine, m_pOperatorToken.m_nColumn);
									return;
								}
								if (m_pRight.m_pValueType.m_ePointerType == TypeRef.PointerType.TRANSITON)
								{
									pValidator.AddError("Cannot store a TRANSITION pointer (need to `own` it)", m_pOperatorToken.m_sFileName, m_pOperatorToken.m_nLine, m_pOperatorToken.m_nColumn);
									return;
								}
								if (m_pLeft.m_pValueType.m_pClassDecl != m_pRight.m_pValueType.m_pClassDecl)
								{
									AddClassDeclReference(m_pRight.m_pValueType.m_pClassDecl, AST.OutputFile.SOURCE, false);
									ClassDecl pBaseClassDecl = m_pRight.m_pValueType.m_pClassDecl.GetBaseClassDecl();
									while (pBaseClassDecl != null)
									{
										if (pBaseClassDecl == m_pLeft.m_pValueType.m_pClassDecl)
											break;
										pBaseClassDecl = pBaseClassDecl.GetBaseClassDecl();
									}
									if (pBaseClassDecl != m_pLeft.m_pValueType.m_pClassDecl)
									{
										InternalString sTemp = new InternalString("Can't assign ");
										sTemp.AppendString(m_pRight.m_pValueType.m_pClassDecl.m_pNameToken.GetString());
										sTemp.AppendString(" to ");
										sTemp.AppendString(m_pLeft.m_pValueType.m_pClassDecl.m_pNameToken.GetString());
										pValidator.AddError(sTemp.GetExternalString(), m_pOperatorToken.m_sFileName, m_pOperatorToken.m_nLine, m_pOperatorToken.m_nColumn);
										return;
									}
								}
							}
							else
								if (m_pRight.m_pValueType.m_eType == ValueType.Type.NULL_VALUE)
								{
								}
								else
									if (m_pRight.m_pValueType.m_eType == ValueType.Type.GENERIC_TYPE_DECL_VALUE)
									{
									}
									else
									{
										pValidator.AddError("Expected right side of = to also be CLASS_DECL_VALUE or NULL_VALUE\n", m_pOperatorToken.m_sFileName, m_pOperatorToken.m_nLine, m_pOperatorToken.m_nColumn);
										return;
									}
						}
						m_pValueType = m_pLeft.m_pValueType.Clone();
						return;
					}
					m_pValueType = m_pLeft.m_pValueType.Clone();
					return;
				}
			}
			if (m_pRight != null)
			{
				m_pRight.Validate(pValidator, null);
				if (m_pRight.m_pValueType == null)
				{
				}
			}
			if (m_pParent != null)
			{
			}
		}

		public override void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, InternalString sOut)
		{
			string sPad = " ";
			if (m_pOperatorToken.m_eType == Token.Type.TOKEN_MINUS_MINUS || m_pOperatorToken.m_eType == Token.Type.TOKEN_PLUS_PLUS || m_pOperatorToken.m_eType == Token.Type.TOKEN_DOT || m_pOperatorToken.m_eType == Token.Type.TOKEN_DOUBLE_COLON)
				sPad = "";
			string sOperator = m_pOperatorToken.GetString();
			if (eLanguage == AST.Language.CS && m_pOperatorToken.m_eType == Token.Type.TOKEN_DOUBLE_COLON)
				sOperator = ".";
			if (eLanguage == AST.Language.CPP && m_pOperatorToken.m_eType == Token.Type.TOKEN_DOT)
			{
				sOperator = "->";
				if (m_pLeft != null && m_pLeft.m_eType == AST.Type.BASE_EXPR)
					sOperator = "::";
			}
			m_pLeft.Stringify(eLanguage, eOutputFile, 0, sOut);
			sOut.Append(sPad);
			sOut.Append(sOperator);
			if (m_pRight != null)
			{
				sOut.Append(sPad);
				m_pRight.Stringify(eLanguage, eOutputFile, 0, sOut);
			}
		}

		~OperatorExpr()
		{
		}

	}
}

