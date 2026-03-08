namespace NumbatLogic
{
	class OperatorExpr : AST
	{
		public enum OperatorType
		{
			LOGICAL_AND,
			LESS_THAN,
			LESS_THAN_OR_EQUAL,
			GREATER_THAN,
			GREATER_THAN_OR_EQUAL,
			BITWISE_AND,
			BITWISE_OR,
			BITWISE_XOR,
			DIVISION,
			MEMBER_ACCESS,
			LEFT_SHIFT,
			RIGHT_SHIFT,
			SCOPE_RESOLUTION,
			EQUALITY,
			ASSIGNMENT,
			SUBTRACTION,
			SUBTRACT_ASSIGN,
			DECREMENT,
			MODULO,
			INEQUALITY,
			LOGICAL_OR,
			ADDITION,
			ADD_ASSIGN,
			INCREMENT,
			MULTIPLICATION,
			UNKNOWN,
		}

		public Vector<Token> m_pOperatorTokenVector;
		public Token m_pOwnedOperatorToken;
		public AST m_pLeft;
		public AST m_pRight;
		public OperatorExpr()
		{
			m_eType = AST.Type.AST_OPERATOR_EXPR;
			m_pOwnedOperatorToken = null;
		}

		public Token GetFirstOperatorToken()
		{
			Assert.Plz(m_pOperatorTokenVector != null && m_pOperatorTokenVector.GetSize() > 0);
			return m_pOperatorTokenVector.Get(0);
		}

		public OperatorExpr.OperatorType GetOperatorType()
		{
			Token pOp = GetFirstOperatorToken();
			if (m_pOperatorTokenVector.GetSize() >= 2)
			{
				Token pSecond = m_pOperatorTokenVector.Get(1);
				if (pOp.m_eType == Token.Type.TOKEN_ANGLE_BRACKET_LEFT && pSecond.m_eType == Token.Type.TOKEN_ANGLE_BRACKET_LEFT)
					return OperatorType.LEFT_SHIFT;
				if (pOp.m_eType == Token.Type.TOKEN_ANGLE_BRACKET_RIGHT && pSecond.m_eType == Token.Type.TOKEN_ANGLE_BRACKET_RIGHT)
					return OperatorType.RIGHT_SHIFT;
			}
			switch (pOp.m_eType)
			{
				case Token.Type.TOKEN_AND:
				{
					return OperatorType.LOGICAL_AND;
				}

				case Token.Type.TOKEN_ANGLE_BRACKET_LEFT:
				{
					return OperatorType.LESS_THAN;
				}

				case Token.Type.TOKEN_ANGLE_BRACKET_LEFT_EQUALS:
				{
					return OperatorType.LESS_THAN_OR_EQUAL;
				}

				case Token.Type.TOKEN_ANGLE_BRACKET_RIGHT:
				{
					return OperatorType.GREATER_THAN;
				}

				case Token.Type.TOKEN_ANGLE_BRACKET_RIGHT_EQUALS:
				{
					return OperatorType.GREATER_THAN_OR_EQUAL;
				}

				case Token.Type.TOKEN_BITWISE_AND:
				{
					return OperatorType.BITWISE_AND;
				}

				case Token.Type.TOKEN_BITWISE_OR:
				{
					return OperatorType.BITWISE_OR;
				}

				case Token.Type.TOKEN_CARET:
				{
					return OperatorType.BITWISE_XOR;
				}

				case Token.Type.TOKEN_DIVIDE:
				{
					return OperatorType.DIVISION;
				}

				case Token.Type.TOKEN_DOT:
				{
					return OperatorType.MEMBER_ACCESS;
				}

				case Token.Type.TOKEN_DOUBLE_ANGLE_BRACKET_LEFT:
				{
					return OperatorType.LEFT_SHIFT;
				}

				case Token.Type.TOKEN_DOUBLE_ANGLE_BRACKET_RIGHT:
				{
					return OperatorType.RIGHT_SHIFT;
				}

				case Token.Type.TOKEN_DOUBLE_COLON:
				{
					return OperatorType.SCOPE_RESOLUTION;
				}

				case Token.Type.TOKEN_DOUBLE_EQUALS:
				{
					return OperatorType.EQUALITY;
				}

				case Token.Type.TOKEN_EQUALS:
				{
					return OperatorType.ASSIGNMENT;
				}

				case Token.Type.TOKEN_MINUS:
				{
					return OperatorType.SUBTRACTION;
				}

				case Token.Type.TOKEN_MINUS_EQUALS:
				{
					return OperatorType.SUBTRACT_ASSIGN;
				}

				case Token.Type.TOKEN_MINUS_MINUS:
				{
					return OperatorType.DECREMENT;
				}

				case Token.Type.TOKEN_MODULUS:
				{
					return OperatorType.MODULO;
				}

				case Token.Type.TOKEN_NOT_EQUALS:
				{
					return OperatorType.INEQUALITY;
				}

				case Token.Type.TOKEN_OR:
				{
					return OperatorType.LOGICAL_OR;
				}

				case Token.Type.TOKEN_PLUS:
				{
					return OperatorType.ADDITION;
				}

				case Token.Type.TOKEN_PLUS_EQUALS:
				{
					return OperatorType.ADD_ASSIGN;
				}

				case Token.Type.TOKEN_PLUS_PLUS:
				{
					return OperatorType.INCREMENT;
				}

				case Token.Type.TOKEN_STAR:
				{
					return OperatorType.MULTIPLICATION;
				}

				default:
				{
					return OperatorType.UNKNOWN;
				}

			}
		}

		public static OperatorExpr Create(Vector<Token> pOperatorTokenVector, AST pLeft, AST pRight)
		{
			OperatorExpr pOperatorExpr = new OperatorExpr();
			AST pOwnedLeft = pLeft;
			AST pOwnedRight = pRight;
			pOperatorExpr.m_pFirstToken = pLeft.m_pFirstToken;
			pOperatorExpr.m_pOperatorTokenVector = pOperatorTokenVector;
			pOperatorExpr.m_pLeft = pOwnedLeft;
			pOperatorExpr.m_pRight = pOwnedRight;
			if (pLeft != null)
			{
				NumbatLogic.AST __4182113595 = pOwnedLeft;
				pOwnedLeft = null;
				pOperatorExpr.AddChild(__4182113595);
			}
			if (pRight != null)
			{
				NumbatLogic.AST __2506281843 = pOwnedRight;
				pOwnedRight = null;
				pOperatorExpr.AddChild(__2506281843);
			}
			NumbatLogic.OperatorExpr __2365581576 = pOperatorExpr;
			pOperatorExpr = null;
			return __2365581576;
		}

		public override AST BaseClone()
		{
			AST pLeft = null;
			AST pRight = null;
			if (m_pLeft != null)
				pLeft = m_pLeft.BaseClone();
			if (m_pRight != null)
				pRight = m_pRight.BaseClone();
			Vector<Token> pOpTokens = new Vector<Token>();
			Token pOwnedClone = null;
			for (int i = 0; i < m_pOperatorTokenVector.GetSize(); i = i + 1)
			{
				if (i == 0 && m_pOwnedOperatorToken != null)
				{
					pOwnedClone = m_pOwnedOperatorToken.Clone();
					pOpTokens.PushBack(pOwnedClone);
				}
				else
					pOpTokens.PushBack(m_pOperatorTokenVector.Get(i));
			}
			NumbatLogic.Vector<NumbatLogic.Token> __1714663050 = pOpTokens;
			pOpTokens = null;
			NumbatLogic.AST __3919013150 = pLeft;
			pLeft = null;
			NumbatLogic.AST __534132297 = pRight;
			pRight = null;
			OperatorExpr pResult = OperatorExpr.Create(__1714663050, __3919013150, __534132297);
			if (pOwnedClone != null)
			{
				NumbatLogic.Token __417611343 = pOwnedClone;
				pOwnedClone = null;
				pResult.m_pOwnedOperatorToken = __417611343;
			}
			NumbatLogic.OperatorExpr __3068411296 = pResult;
			pResult = null;
			return __3068411296;
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
						Token pOpToken = GetFirstOperatorToken();
						if (pOpToken.m_eType != Token.Type.TOKEN_DOUBLE_COLON)
						{
							pValidator.AddError("Expected TOKEN_DOUBLE_COLON ", pOpToken.m_sFileName, pOpToken.m_nLine, pOpToken.m_nColumn);
							return;
						}
						if (m_pRight == null)
						{
							pValidator.AddError("Expected right side of TOKEN_DOUBLE_COLON operator", pOpToken.m_sFileName, pOpToken.m_nLine, pOpToken.m_nColumn);
							return;
						}
						if (m_pRight.m_eType != AST.Type.AST_IDENTIFIER && m_pRight.m_eType != AST.Type.AST_OPERATOR_EXPR && m_pRight.m_eType != AST.Type.AST_FUNCTION_CALL && m_pRight.m_eType != AST.Type.AST_ARRAY_LOOKUP)
						{
							InternalString sTemp = new InternalString("Unexpected right side of TOKEN_DOUBLE_COLON operator: ");
							m_pRight.StringifyType(sTemp);
							pValidator.AddError(sTemp.GetExternalString(), pOpToken.m_sFileName, pOpToken.m_nLine, pOpToken.m_nColumn);
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
					Token pOpToken = GetFirstOperatorToken();
					if (pOpToken.m_eType == Token.Type.TOKEN_DOT)
					{
						if (m_pLeft.m_pValueType.m_eType == ValueType.Type.GENERIC_TYPE_DECL_VALUE)
						{
							if (m_pLeft.m_pValueType.m_pGenericTypeDecl == null)
							{
								pValidator.AddError(" set but m_pGenericTypeDecl is null???", pOpToken.m_sFileName, pOpToken.m_nLine, pOpToken.m_nColumn);
								return;
							}
						}
						else
							if (m_pLeft.m_pValueType.m_eType == ValueType.Type.CLASS_DECL_VALUE)
							{
								if (m_pLeft.m_pValueType.m_pClassDecl == null)
								{
									pValidator.AddError(" set but m_pClassDecl is null???", pOpToken.m_sFileName, pOpToken.m_nLine, pOpToken.m_nColumn);
									return;
								}
							}
							else
							{
								pValidator.AddError("Expected ValueType::Type::CLASS_DECL_VALUE or ValueType::Type::GENERIC_TYPE_DECL_VALUE on left of TOKEN_DOT operator", pOpToken.m_sFileName, pOpToken.m_nLine, pOpToken.m_nColumn);
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
					if (pOpToken.m_eType == Token.Type.TOKEN_PLUS)
					{
						if (m_pLeft.m_pValueType.m_eType == ValueType.Type.STRING)
						{
							pValidator.AddError("Cannot concat strings with +", pOpToken.m_sFileName, pOpToken.m_nLine, pOpToken.m_nColumn);
							return;
						}
					}
					if (pOpToken.m_eType == Token.Type.TOKEN_DOUBLE_EQUALS || pOpToken.m_eType == Token.Type.TOKEN_NOT_EQUALS)
					{
						if (m_pRight == null)
						{
							pValidator.AddError("Nohing on right side to compare?", pOpToken.m_sFileName, pOpToken.m_nLine, pOpToken.m_nColumn);
							return;
						}
						m_pRight.Validate(pValidator, this);
						if (m_pLeft.m_pValueType.m_eType == ValueType.Type.STRING && m_pRight.m_pValueType.m_eType == ValueType.Type.STRING)
						{
							pValidator.AddError("Cannot == or != strings use ExternalString::Equal", pOpToken.m_sFileName, pOpToken.m_nLine, pOpToken.m_nColumn);
							return;
						}
						m_pValueType = new ValueType(ValueType.Type.BOOL);
						return;
					}
					if (m_pRight != null)
						m_pRight.Validate(pValidator, this);
					if (pOpToken.m_eType == Token.Type.TOKEN_EQUALS)
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
									InternalString sTemp = new InternalString("Expected right side of = to be OWNED_PREASSSIGN (result of own). FROM[");
									m_pRight.m_pValueType.StringifyType(sTemp);
									if (m_pRight.m_pValueType.m_pClassDecl != null)
									{
										sTemp.Append(" name=");
										sTemp.AppendString(m_pRight.m_pValueType.m_pClassDecl.m_pNameToken.GetString());
									}
									sTemp.Append(" ptr=");
									ValueType.StringifyPointerType(sTemp, m_pRight.m_pValueType.m_ePointerType);
									sTemp.Append("] TO[");
									m_pLeft.m_pValueType.StringifyType(sTemp);
									if (m_pLeft.m_pValueType.m_pClassDecl != null)
									{
										sTemp.Append(" name=");
										sTemp.AppendString(m_pLeft.m_pValueType.m_pClassDecl.m_pNameToken.GetString());
									}
									sTemp.Append(" ptr=");
									ValueType.StringifyPointerType(sTemp, m_pLeft.m_pValueType.m_ePointerType);
									sTemp.Append("]");
									pValidator.AddError(sTemp.GetExternalString(), pOpToken.m_sFileName, pOpToken.m_nLine, pOpToken.m_nColumn);
									return;
								}
								if (m_pLeft.m_pValueType.m_ePointerType == TypeRef.PointerType.SHARED && m_pRight.m_pValueType.m_ePointerType == TypeRef.PointerType.OWNED_PREASSSIGN)
								{
									InternalString sTemp = new InternalString("Can't store an owned pointer in a shared pointer. FROM[");
									m_pRight.m_pValueType.StringifyType(sTemp);
									if (m_pRight.m_pValueType.m_pClassDecl != null)
									{
										sTemp.Append(" name=");
										sTemp.AppendString(m_pRight.m_pValueType.m_pClassDecl.m_pNameToken.GetString());
									}
									sTemp.Append(" ptr=");
									ValueType.StringifyPointerType(sTemp, m_pRight.m_pValueType.m_ePointerType);
									sTemp.Append("] TO[");
									m_pLeft.m_pValueType.StringifyType(sTemp);
									if (m_pLeft.m_pValueType.m_pClassDecl != null)
									{
										sTemp.Append(" name=");
										sTemp.AppendString(m_pLeft.m_pValueType.m_pClassDecl.m_pNameToken.GetString());
									}
									sTemp.Append(" ptr=");
									ValueType.StringifyPointerType(sTemp, m_pLeft.m_pValueType.m_ePointerType);
									sTemp.Append("]");
									pValidator.AddError(sTemp.GetExternalString(), pOpToken.m_sFileName, pOpToken.m_nLine, pOpToken.m_nColumn);
									return;
								}
								if (m_pRight.m_pValueType.m_ePointerType == TypeRef.PointerType.TRANSITON)
								{
									InternalString sTemp = new InternalString("Cannot store a TRANSITION pointer (need to `own` it). FROM[");
									m_pRight.m_pValueType.StringifyType(sTemp);
									if (m_pRight.m_pValueType.m_pClassDecl != null)
									{
										sTemp.Append(" name=");
										sTemp.AppendString(m_pRight.m_pValueType.m_pClassDecl.m_pNameToken.GetString());
									}
									sTemp.Append(" ptr=");
									ValueType.StringifyPointerType(sTemp, m_pRight.m_pValueType.m_ePointerType);
									sTemp.Append("] TO[");
									m_pLeft.m_pValueType.StringifyType(sTemp);
									if (m_pLeft.m_pValueType.m_pClassDecl != null)
									{
										sTemp.Append(" name=");
										sTemp.AppendString(m_pLeft.m_pValueType.m_pClassDecl.m_pNameToken.GetString());
									}
									sTemp.Append(" ptr=");
									ValueType.StringifyPointerType(sTemp, m_pLeft.m_pValueType.m_ePointerType);
									sTemp.Append("]");
									pValidator.AddError(sTemp.GetExternalString(), pOpToken.m_sFileName, pOpToken.m_nLine, pOpToken.m_nColumn);
									return;
								}
								if (m_pLeft.m_pValueType.m_pClassDecl != m_pRight.m_pValueType.m_pClassDecl)
								{
									AddClassDeclReference(m_pRight.m_pValueType.m_pClassDecl, AST.OutputFile.SOURCE, false);
									ClassDecl pBaseClassDecl = m_pRight.m_pValueType.m_pClassDecl.GetBaseClassDecl(pValidator);
									while (pBaseClassDecl != null)
									{
										if (pBaseClassDecl == m_pLeft.m_pValueType.m_pClassDecl)
											break;
										pBaseClassDecl = pBaseClassDecl.GetBaseClassDecl(pValidator);
									}
									if (pBaseClassDecl != m_pLeft.m_pValueType.m_pClassDecl)
									{
										InternalString sTemp = new InternalString("Can't assign ");
										sTemp.AppendString(m_pRight.m_pValueType.m_pClassDecl.m_pNameToken.GetString());
										sTemp.AppendString(" to ");
										sTemp.AppendString(m_pLeft.m_pValueType.m_pClassDecl.m_pNameToken.GetString());
										pValidator.AddError(sTemp.GetExternalString(), pOpToken.m_sFileName, pOpToken.m_nLine, pOpToken.m_nColumn);
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
										pValidator.AddError("Expected right side of = to also be CLASS_DECL_VALUE or NULL_VALUE\n", pOpToken.m_sFileName, pOpToken.m_nLine, pOpToken.m_nColumn);
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
			Token pOpToken = GetFirstOperatorToken();
			string sPad = " ";
			if (pOpToken.m_eType == Token.Type.TOKEN_MINUS_MINUS || pOpToken.m_eType == Token.Type.TOKEN_PLUS_PLUS || pOpToken.m_eType == Token.Type.TOKEN_DOT || pOpToken.m_eType == Token.Type.TOKEN_DOUBLE_COLON)
				sPad = "";
			InternalString sOperatorTemp = new InternalString("");
			if (m_pOperatorTokenVector != null)
			{
				for (int i = 0; i < m_pOperatorTokenVector.GetSize(); i = i + 1)
					sOperatorTemp.Append(m_pOperatorTokenVector.Get(i).GetString());
			}
			string sOperator = sOperatorTemp.GetExternalString();
			if (eLanguage == AST.Language.CS && pOpToken.m_eType == Token.Type.TOKEN_DOUBLE_COLON)
				sOperator = ".";
			if (eLanguage == AST.Language.CPP && pOpToken.m_eType == Token.Type.TOKEN_DOT)
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

