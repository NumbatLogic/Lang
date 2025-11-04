namespace NumbatLogic
{
	class AST
	{
		public enum Type
		{
			AST_ACCESS_LEVEL,
			AST_ARRAY_LOOKUP,
			AST_BOOL_EXPR,
			AST_BREAK_STMT,
			AST_CAST_EXP,
			AST_CHAR,
			AST_CLASS_DECL,
			AST_CONTINUE_STMT,
			AST_DELETE_STMT,
			AST_DISOWN_EXP,
			AST_ENUM_DECL,
			AST_EXPRESSION_STMT,
			AST_FOR_STMT,
			AST_FUNCTION_CALL,
			AST_FUNCTION_DECL,
			AST_GENERIC_TYPE_DECL,
			AST_IDENTIFIER,
			AST_IF_STMT,
			AST_MEMBER_CLASS_DECL,
			AST_MEMBER_ENUM_DECL,
			AST_MEMBER_FUNCTION_DECL,
			AST_MEMBER_VAR_DECL,
			AST_NEW_EXP,
			AST_NUMBER,
			AST_OPERATOR_EXPR,
			AST_OWN_EXP,
			AST_PARAM_CALL,
			AST_PARAM_DECL,
			AST_PAREN,
			AST_REF_EXPR,
			AST_RETURN_STMT,
			AST_SCOPE,
			AST_STATIC_ARRAY,
			AST_STRING,
			AST_SWITCH_STMT,
			AST_TOR_DECL,
			AST_TRANSLATION_UNIT,
			AST_TTHASH_EXP,
			AST_TYPE_REF,
			AST_UNARY,
			AST_VAR_DECL_DESCOPE,
			AST_VAR_DECL,
			AST_WHILE_STMT,
			BASE_EXPR,
			DELEGATE_DECL,
			ENUM_DECL_VALUE,
			MEMBER_VARS_SET_DEFAULT_STMT,
			NAMESPACE_DECL,
			NULL_EXPR,
			THIS_EXPR,
		}

		public enum Language
		{
			NLL,
			NLL_DEF,
			CS,
			CPP,
			C,
			H,
			PHP,
		}

		public enum OutputFile
		{
			SOURCE,
			HEADER,
		}

		public Type m_eType;
		public Token m_pFirstToken;
		public AST m_pParent;
		public AST m_pFirstChild;
		public AST m_pLastChild;
		public AST m_pPrevSibling;
		public AST m_pNextSibling;
		public bool m_bCanDescend;
		public ValueType m_pValueType;
		public bool m_bStatement;
		public bool m_bSkipOutput;
		public AST()
		{
			m_bStatement = false;
			m_bSkipOutput = false;
		}

		~AST()
		{
		}

		public static AST CreateFromTokenContainer(TokenContainer pTokenContainer, OffsetDatum pOffsetDatum)
		{
			AST pAst = null;
			pAst = FunctionDecl.TryCreate(pTokenContainer, pOffsetDatum, null);
			if (pAst != null)
			{
				NumbatLogic.AST __3531452304 = pAst;
				pAst = null;
				return __3531452304;
			}
			pAst = ClassDecl.TryCreate(pTokenContainer, pOffsetDatum, null);
			if (pAst != null)
			{
				NumbatLogic.AST __1702725405 = pAst;
				pAst = null;
				return __1702725405;
			}
			pAst = NamespaceDecl.TryCreate(pTokenContainer, pOffsetDatum);
			if (pAst != null)
			{
				NumbatLogic.AST __3648882243 = pAst;
				pAst = null;
				return __3648882243;
			}
			pAst = CreateStatementFromTokenContainer(pTokenContainer, pOffsetDatum);
			if (pAst != null)
			{
				NumbatLogic.AST __494765326 = pAst;
				pAst = null;
				return __494765326;
			}
			pAst = TryCreateExpression(pTokenContainer, pOffsetDatum);
			if (pAst != null)
			{
				NumbatLogic.AST __3296590902 = pAst;
				pAst = null;
				return __3296590902;
			}
			return null;
		}

		public static AST CreateStatementFromTokenContainer(TokenContainer pTokenContainer, OffsetDatum pOffsetDatum)
		{
			AST pAst = null;
			pAst = ReturnStmt.TryCreate(pTokenContainer, pOffsetDatum);
			if (pAst != null)
			{
				NumbatLogic.AST __3699233979 = pAst;
				pAst = null;
				return __3699233979;
			}
			pAst = BreakStmt.TryCreate(pTokenContainer, pOffsetDatum);
			if (pAst != null)
			{
				NumbatLogic.AST __410900470 = pAst;
				pAst = null;
				return __410900470;
			}
			pAst = ContinueStmt.TryCreate(pTokenContainer, pOffsetDatum);
			if (pAst != null)
			{
				NumbatLogic.AST __2508000145 = pAst;
				pAst = null;
				return __2508000145;
			}
			pAst = Scope.TryCreate(pTokenContainer, pOffsetDatum, false);
			if (pAst != null)
			{
				NumbatLogic.AST __696060623 = pAst;
				pAst = null;
				return __696060623;
			}
			pAst = VarDecl.TryCreate(pTokenContainer, pOffsetDatum, false);
			if (pAst != null)
			{
				NumbatLogic.AST __2659000898 = pAst;
				pAst = null;
				return __2659000898;
			}
			pAst = EnumDecl.TryCreate(pTokenContainer, pOffsetDatum);
			if (pAst != null)
			{
				NumbatLogic.AST __578626332 = pAst;
				pAst = null;
				return __578626332;
			}
			pAst = DeleteStmt.TryCreate(pTokenContainer, pOffsetDatum);
			if (pAst != null)
			{
				NumbatLogic.AST __3866959953 = pAst;
				pAst = null;
				return __3866959953;
			}
			pAst = IfStmt.TryCreate(pTokenContainer, pOffsetDatum);
			if (pAst != null)
			{
				NumbatLogic.AST __1065179497 = pAst;
				pAst = null;
				return __1065179497;
			}
			pAst = ForStmt.TryCreate(pTokenContainer, pOffsetDatum);
			if (pAst != null)
			{
				NumbatLogic.AST __2206029879 = pAst;
				pAst = null;
				return __2206029879;
			}
			pAst = WhileStmt.TryCreate(pTokenContainer, pOffsetDatum);
			if (pAst != null)
			{
				NumbatLogic.AST __880636090 = pAst;
				pAst = null;
				return __880636090;
			}
			pAst = SwitchStmt.TryCreate(pTokenContainer, pOffsetDatum);
			if (pAst != null)
			{
				NumbatLogic.AST __2289922532 = pAst;
				pAst = null;
				return __2289922532;
			}
			pAst = ExpressionStmt.TryCreate(pTokenContainer, pOffsetDatum);
			if (pAst != null)
			{
				NumbatLogic.AST __1283289769 = pAst;
				pAst = null;
				return __1283289769;
			}
			return null;
		}

		protected static AST TryCreateInnerExpression(TokenContainer pTokenContainer, OffsetDatum pOffsetDatum)
		{
			AST pAst = null;
			pAst = NumberExpr.TryCreate(pTokenContainer, pOffsetDatum);
			if (pAst != null)
			{
				NumbatLogic.AST __3766281932 = pAst;
				pAst = null;
				return __3766281932;
			}
			pAst = BoolExpr.TryCreate(pTokenContainer, pOffsetDatum);
			if (pAst != null)
			{
				NumbatLogic.AST __2474429708 = pAst;
				pAst = null;
				return __2474429708;
			}
			pAst = CharExpr.TryCreate(pTokenContainer, pOffsetDatum);
			if (pAst != null)
			{
				NumbatLogic.AST __796707922 = pAst;
				pAst = null;
				return __796707922;
			}
			pAst = StringExpr.TryCreate(pTokenContainer, pOffsetDatum);
			if (pAst != null)
			{
				NumbatLogic.AST __1431150190 = pAst;
				pAst = null;
				return __1431150190;
			}
			pAst = NullExpr.TryCreate(pTokenContainer, pOffsetDatum);
			if (pAst != null)
			{
				NumbatLogic.AST __3914178352 = pAst;
				pAst = null;
				return __3914178352;
			}
			pAst = ThisExpr.TryCreate(pTokenContainer, pOffsetDatum);
			if (pAst != null)
			{
				NumbatLogic.AST __760061053 = pAst;
				pAst = null;
				return __760061053;
			}
			pAst = BaseExpr.TryCreate(pTokenContainer, pOffsetDatum);
			if (pAst != null)
			{
				NumbatLogic.AST __1582151613 = pAst;
				pAst = null;
				return __1582151613;
			}
			pAst = FunctionCall.TryCreate(pTokenContainer, pOffsetDatum);
			if (pAst != null)
			{
				NumbatLogic.AST __3796743907 = pAst;
				pAst = null;
				return __3796743907;
			}
			pAst = New.TryCreate(pTokenContainer, pOffsetDatum);
			if (pAst != null)
			{
				NumbatLogic.AST __4283288726 = pAst;
				pAst = null;
				return __4283288726;
			}
			pAst = CastExpr.TryCreate(pTokenContainer, pOffsetDatum);
			if (pAst != null)
			{
				NumbatLogic.AST __1129172424 = pAst;
				pAst = null;
				return __1129172424;
			}
			pAst = TTHashExpr.TryCreate(pTokenContainer, pOffsetDatum);
			if (pAst != null)
			{
				NumbatLogic.AST __2270023301 = pAst;
				pAst = null;
				return __2270023301;
			}
			pAst = Unary.TryCreate(pTokenContainer, pOffsetDatum);
			if (pAst != null)
			{
				NumbatLogic.AST __4098745669 = pAst;
				pAst = null;
				return __4098745669;
			}
			pAst = Paren.TryCreate(pTokenContainer, pOffsetDatum);
			if (pAst != null)
			{
				NumbatLogic.AST __1213064219 = pAst;
				pAst = null;
				return __1213064219;
			}
			pAst = ArrayLookup.TryCreate(pTokenContainer, pOffsetDatum);
			if (pAst != null)
			{
				NumbatLogic.AST __21838641 = pAst;
				pAst = null;
				return __21838641;
			}
			pAst = StaticArray.TryCreate(pTokenContainer, pOffsetDatum);
			if (pAst != null)
			{
				NumbatLogic.AST __3175955055 = pAst;
				pAst = null;
				return __3175955055;
			}
			pAst = OwnExpr.TryCreate(pTokenContainer, pOffsetDatum);
			if (pAst != null)
			{
				NumbatLogic.AST __2035104034 = pAst;
				pAst = null;
				return __2035104034;
			}
			pAst = DisownExpr.TryCreate(pTokenContainer, pOffsetDatum);
			if (pAst != null)
			{
				NumbatLogic.AST __172823266 = pAst;
				pAst = null;
				return __172823266;
			}
			pAst = RefExpr.TryCreate(pTokenContainer, pOffsetDatum);
			if (pAst != null)
			{
				NumbatLogic.AST __3058504636 = pAst;
				pAst = null;
				return __3058504636;
			}
			pAst = Identifier.TryCreate(pTokenContainer, pOffsetDatum);
			if (pAst != null)
			{
				NumbatLogic.AST __2873977289 = pAst;
				pAst = null;
				return __2873977289;
			}
			return null;
		}

		public static AST TryCreateExpression(TokenContainer pTokenContainer, OffsetDatum pOffsetDatum)
		{
			OffsetDatum pTempOffset = OffsetDatum.Create(pOffsetDatum);
			AST pLeft = TryCreateInnerExpression(pTokenContainer, pTempOffset);
			if (pLeft != null)
			{
				Token pOperatorToken = pTokenContainer.Peek(pTempOffset);
				if (pOperatorToken != null)
				{
					if (pOperatorToken.m_eType == Token.Type.TOKEN_MINUS_MINUS || pOperatorToken.m_eType == Token.Type.TOKEN_PLUS_PLUS)
					{
						pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
						pOffsetDatum.Set(pTempOffset);
						NumbatLogic.AST __4143710821 = pLeft;
						pLeft = null;
						return OperatorExpr.Create(pOperatorToken, __4143710821, null);
					}
					if (pOperatorToken.m_eType == Token.Type.TOKEN_QUESTION_MARK)
					{
						pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
						pOffsetDatum.Set(pTempOffset);
						NumbatLogic.AST __570163318 = pLeft;
						pLeft = null;
						return TrinaryExpr.Create(__570163318, pTokenContainer, pOffsetDatum);
					}
					if (pOperatorToken.m_eType == Token.Type.TOKEN_AND || pOperatorToken.m_eType == Token.Type.TOKEN_ANGLE_BRACKET_LEFT || pOperatorToken.m_eType == Token.Type.TOKEN_ANGLE_BRACKET_LEFT_EQUALS || pOperatorToken.m_eType == Token.Type.TOKEN_ANGLE_BRACKET_RIGHT || pOperatorToken.m_eType == Token.Type.TOKEN_ANGLE_BRACKET_RIGHT_EQUALS || pOperatorToken.m_eType == Token.Type.TOKEN_BITWISE_AND || pOperatorToken.m_eType == Token.Type.TOKEN_BITWISE_OR || pOperatorToken.m_eType == Token.Type.TOKEN_CARET || pOperatorToken.m_eType == Token.Type.TOKEN_DIVIDE || pOperatorToken.m_eType == Token.Type.TOKEN_DOT || pOperatorToken.m_eType == Token.Type.TOKEN_DOUBLE_ANGLE_BRACKET_LEFT || pOperatorToken.m_eType == Token.Type.TOKEN_DOUBLE_ANGLE_BRACKET_RIGHT || pOperatorToken.m_eType == Token.Type.TOKEN_DOUBLE_COLON || pOperatorToken.m_eType == Token.Type.TOKEN_DOUBLE_EQUALS || pOperatorToken.m_eType == Token.Type.TOKEN_EQUALS || pOperatorToken.m_eType == Token.Type.TOKEN_MINUS || pOperatorToken.m_eType == Token.Type.TOKEN_MINUS_EQUALS || pOperatorToken.m_eType == Token.Type.TOKEN_NOT_EQUALS || pOperatorToken.m_eType == Token.Type.TOKEN_OR || pOperatorToken.m_eType == Token.Type.TOKEN_PLUS || pOperatorToken.m_eType == Token.Type.TOKEN_PLUS_EQUALS || pOperatorToken.m_eType == Token.Type.TOKEN_STAR || pOperatorToken.m_eType == Token.Type.TOKEN_MODULUS)
					{
						pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
						AST pRight = TryCreateExpression(pTokenContainer, pTempOffset);
						if (pRight != null)
						{
							pOffsetDatum.Set(pTempOffset);
							NumbatLogic.AST __3622636070 = pLeft;
							pLeft = null;
							NumbatLogic.AST __2072852733 = pRight;
							pRight = null;
							return OperatorExpr.Create(pOperatorToken, __3622636070, __2072852733);
						}
					}
				}
				pOffsetDatum.Set(pTempOffset);
				NumbatLogic.AST __2599226327 = pLeft;
				pLeft = null;
				return __2599226327;
			}
			return null;
		}

		public virtual void PreValidate(Validator pValidator, OperatorExpr pParent)
		{
			AST pChild = m_pFirstChild;
			while (pChild != null)
			{
				AST pNextSibling = pChild.m_pNextSibling;
				pChild.PreValidate(pValidator, null);
				pChild = pNextSibling;
			}
		}

		public virtual void Validate(Validator pValidator, OperatorExpr pParent)
		{
			AST pChild = m_pFirstChild;
			while (pChild != null)
			{
				AST pNextSibling = pChild.m_pNextSibling;
				pChild.Validate(pValidator, null);
				pChild = pNextSibling;
			}
		}

		public virtual ClassDecl FindClassDecl(string sTypeName, AST pCallingChild)
		{
			if (pCallingChild != null)
			{
				AST pChild = m_pFirstChild;
				while (pChild != null)
				{
					if (pChild != pCallingChild)
					{
						ClassDecl pResult = pChild.FindClassDecl(sTypeName, null);
						if (pResult != null)
							return pResult;
					}
					pChild = pChild.m_pNextSibling;
				}
				if (m_pParent != null)
					return m_pParent.FindClassDecl(sTypeName, this);
			}
			else
			{
				if (m_bCanDescend)
				{
					AST pChild = m_pFirstChild;
					while (pChild != null)
					{
						ClassDecl pResult = pChild.FindClassDecl(sTypeName, null);
						if (pResult != null)
							return pResult;
						pChild = pChild.m_pNextSibling;
					}
				}
			}
			return null;
		}

		public virtual NamespaceDecl FindNamespaceDecl(string sTypeName, AST pCallingChild)
		{
			if (pCallingChild != null)
			{
				AST pChild = m_pFirstChild;
				while (pChild != null)
				{
					if (pChild != pCallingChild)
					{
						NamespaceDecl pResult = pChild.FindNamespaceDecl(sTypeName, null);
						if (pResult != null)
							return pResult;
					}
					pChild = pChild.m_pNextSibling;
				}
				if (m_pParent != null)
					return m_pParent.FindNamespaceDecl(sTypeName, this);
			}
			return null;
		}

		public virtual AST FindByName(string sName, AST pCallingChild)
		{
			if (pCallingChild != null)
			{
				AST pChild = m_pFirstChild;
				while (pChild != null)
				{
					if (pChild != pCallingChild)
					{
						AST pResult = pChild.FindByName(sName, null);
						if (pResult != null)
							return pResult;
					}
					pChild = pChild.m_pNextSibling;
				}
				if (m_pParent != null)
					return m_pParent.FindByName(sName, this);
			}
			else
			{
				if (m_bCanDescend)
				{
					AST pChild = m_pFirstChild;
					while (pChild != null)
					{
						AST pResult = pChild.FindByName(sName, null);
						if (pResult != null)
							return pResult;
						pChild = pChild.m_pNextSibling;
					}
				}
			}
			return null;
		}

		public void AddChild(AST pAst)
		{
			pAst.m_pParent = this;
			if (m_pFirstChild == null)
			{
				m_pFirstChild = pAst;
				m_pLastChild = m_pFirstChild;
			}
			else
			{
				m_pLastChild.m_pNextSibling = pAst;
				m_pLastChild.m_pNextSibling.m_pPrevSibling = m_pLastChild;
				m_pLastChild = m_pLastChild.m_pNextSibling;
			}
		}

		public void AddChildFront(AST pAst)
		{
			if (m_pFirstChild == null)
			{
				AddChild(pAst);
				return;
			}
			pAst.m_pParent = this;
			NumbatLogic.AST __1770372804 = m_pFirstChild;
			m_pFirstChild = null;
			pAst.m_pNextSibling = __1770372804;
			m_pFirstChild = pAst;
			pAst.m_pNextSibling.m_pPrevSibling = m_pFirstChild;
		}

		public void AddChildBefore(AST pAst, AST pBefore)
		{
			NumbatLogic.Assert.Plz(pBefore.m_pParent == this);
			pAst.m_pParent = this;
			if (m_pFirstChild == pBefore)
			{
				NumbatLogic.AST __1921253932 = m_pFirstChild;
				m_pFirstChild = null;
				pAst.m_pNextSibling = __1921253932;
				m_pFirstChild = pAst;
				pBefore.m_pPrevSibling = m_pFirstChild;
			}
			else
			{
				NumbatLogic.AST __2720658430 = pBefore.m_pPrevSibling.m_pNextSibling;
				pBefore.m_pPrevSibling.m_pNextSibling = null;
				pAst.m_pNextSibling = __2720658430;
				pAst.m_pPrevSibling = pBefore.m_pPrevSibling;
				pBefore.m_pPrevSibling = (AST)(pAst);
				pAst.m_pPrevSibling.m_pNextSibling = pAst;
			}
		}

		public AST RemoveChild(AST pChild)
		{
			if (m_pFirstChild == pChild)
			{
				NumbatLogic.AST __3784667162 = m_pFirstChild;
				m_pFirstChild = null;
				AST pOwnedChild = __3784667162;
				if (m_pLastChild == pOwnedChild)
					m_pLastChild = null;
				else
				{
					NumbatLogic.AST __3980650266 = pOwnedChild.m_pNextSibling;
					pOwnedChild.m_pNextSibling = null;
					m_pFirstChild = __3980650266;
				}
				pOwnedChild.m_pParent = null;
				NumbatLogic.AST __4186937732 = pOwnedChild;
				pOwnedChild = null;
				return __4186937732;
			}
			else
			{
				AST pFindChild = m_pFirstChild;
				while (pFindChild != null)
				{
					if (pFindChild.m_pNextSibling == pChild)
					{
						NumbatLogic.AST __3634029399 = pFindChild.m_pNextSibling;
						pFindChild.m_pNextSibling = null;
						AST pOwnedChild = __3634029399;
						if (m_pLastChild == pOwnedChild)
							m_pLastChild = pFindChild;
						else
						{
							NumbatLogic.AST __1598266735 = pOwnedChild.m_pNextSibling;
							pOwnedChild.m_pNextSibling = null;
							pFindChild.m_pNextSibling = __1598266735;
						}
						pOwnedChild.m_pParent = null;
						NumbatLogic.AST __2408571068 = pOwnedChild;
						pOwnedChild = null;
						return __2408571068;
					}
					pFindChild = pFindChild.m_pNextSibling;
				}
			}
			return null;
		}

		public virtual void AddClassDeclReference(ClassDecl pClassDecl, OutputFile eOutputFile, bool bForwardReference)
		{
			if (m_pParent != null)
				m_pParent.AddClassDeclReference(pClassDecl, eOutputFile, bForwardReference);
		}

		public virtual void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, InternalString sOut)
		{
			sOut.Append("???");
		}

		public virtual AST BaseClone()
		{
			InternalString sTemp = new InternalString("BaseClone() not setup for ");
			StringifyType(sTemp);
			Console.Log(sTemp.GetExternalString());
			NumbatLogic.Assert.Plz(false);
			return null;
		}

		public AST GetParentStatement()
		{
			AST pParent = m_pParent;
			while (pParent != null)
			{
				if (pParent.m_bStatement)
					break;
				pParent = pParent.m_pParent;
			}
			return pParent;
		}

		public virtual void StringifyType(InternalString sOut)
		{
			switch (m_eType)
			{
				case Type.AST_ACCESS_LEVEL:
				{
					sOut.Append("AST_ACCESS_LEVEL");
					return;
				}

				case Type.AST_ARRAY_LOOKUP:
				{
					sOut.Append("AST_ARRAY_LOOKUP");
					return;
				}

				case Type.AST_BOOL_EXPR:
				{
					sOut.Append("AST_BOOL_EXPR");
					return;
				}

				case Type.AST_BREAK_STMT:
				{
					sOut.Append("AST_BREAK_STMT");
					return;
				}

				case Type.AST_CAST_EXP:
				{
					sOut.Append("AST_CAST_EXP");
					return;
				}

				case Type.AST_CHAR:
				{
					sOut.Append("AST_CHAR");
					return;
				}

				case Type.AST_CLASS_DECL:
				{
					sOut.Append("AST_CLASS_DECL");
					return;
				}

				case Type.AST_CONTINUE_STMT:
				{
					sOut.Append("AST_CONTINUE_STMT");
					return;
				}

				case Type.AST_DELETE_STMT:
				{
					sOut.Append("AST_DELETE_STMT");
					return;
				}

				case Type.AST_DISOWN_EXP:
				{
					sOut.Append("AST_DISOWN_EXP");
					return;
				}

				case Type.AST_ENUM_DECL:
				{
					sOut.Append("AST_ENUM_DECL");
					return;
				}

				case Type.AST_EXPRESSION_STMT:
				{
					sOut.Append("AST_EXPRESSION_STMT");
					return;
				}

				case Type.AST_FOR_STMT:
				{
					sOut.Append("AST_FOR_STMT");
					return;
				}

				case Type.AST_FUNCTION_CALL:
				{
					sOut.Append("AST_FUNCTION_CALL");
					return;
				}

				case Type.AST_FUNCTION_DECL:
				{
					sOut.Append("AST_FUNCTION_DECL");
					return;
				}

				case Type.AST_GENERIC_TYPE_DECL:
				{
					sOut.Append("AST_GENERIC_TYPE_DECL");
					return;
				}

				case Type.AST_IDENTIFIER:
				{
					sOut.Append("AST_IDENTIFIER");
					return;
				}

				case Type.AST_IF_STMT:
				{
					sOut.Append("AST_IF_STMT");
					return;
				}

				case Type.AST_MEMBER_ENUM_DECL:
				{
					sOut.Append("AST_MEMBER_ENUM_DECL");
					return;
				}

				case Type.AST_MEMBER_FUNCTION_DECL:
				{
					sOut.Append("AST_MEMBER_FUNCTION_DECL");
					return;
				}

				case Type.AST_MEMBER_VAR_DECL:
				{
					sOut.Append("AST_MEMBER_VAR_DECL");
					return;
				}

				case Type.AST_NEW_EXP:
				{
					sOut.Append("AST_NEW_EXP");
					return;
				}

				case Type.AST_NUMBER:
				{
					sOut.Append("AST_NUMBER");
					return;
				}

				case Type.AST_OPERATOR_EXPR:
				{
					sOut.Append("AST_OPERATOR_EXPR");
					return;
				}

				case Type.AST_OWN_EXP:
				{
					sOut.Append("AST_OWN_EXP");
					return;
				}

				case Type.AST_PARAM_CALL:
				{
					sOut.Append("AST_PARAM_CALL");
					return;
				}

				case Type.AST_PARAM_DECL:
				{
					sOut.Append("AST_PARAM_DECL");
					return;
				}

				case Type.AST_PAREN:
				{
					sOut.Append("AST_PAREN");
					return;
				}

				case Type.AST_REF_EXPR:
				{
					sOut.Append("AST_REF_EXPR");
					return;
				}

				case Type.AST_RETURN_STMT:
				{
					sOut.Append("AST_RETURN_STMT");
					return;
				}

				case Type.AST_SCOPE:
				{
					sOut.Append("AST_SCOPE");
					return;
				}

				case Type.AST_STATIC_ARRAY:
				{
					sOut.Append("AST_STATIC_ARRAY");
					return;
				}

				case Type.AST_STRING:
				{
					sOut.Append("AST_STRING");
					return;
				}

				case Type.AST_SWITCH_STMT:
				{
					sOut.Append("AST_SWITCH_STMT");
					return;
				}

				case Type.AST_TOR_DECL:
				{
					sOut.Append("AST_TOR_DECL");
					return;
				}

				case Type.AST_TRANSLATION_UNIT:
				{
					sOut.Append("AST_TRANSLATION_UNIT");
					return;
				}

				case Type.AST_TTHASH_EXP:
				{
					sOut.Append("AST_TTHASH_EXP");
					return;
				}

				case Type.AST_TYPE_REF:
				{
					sOut.Append("AST_TYPE_REF");
					return;
				}

				case Type.AST_UNARY:
				{
					sOut.Append("AST_UNARY");
					return;
				}

				case Type.AST_VAR_DECL_DESCOPE:
				{
					sOut.Append("AST_VAR_DECL_DESCOPE");
					return;
				}

				case Type.AST_VAR_DECL:
				{
					sOut.Append("AST_VAR_DECL");
					return;
				}

				case Type.AST_WHILE_STMT:
				{
					sOut.Append("AST_WHILE_STMT");
					return;
				}

				case Type.BASE_EXPR:
				{
					sOut.Append("BASE_EXPR");
					return;
				}

				case Type.DELEGATE_DECL:
				{
					sOut.Append("DELEGATE_DECL");
					return;
				}

				case Type.ENUM_DECL_VALUE:
				{
					sOut.Append("ENUM_DECL_VALUE");
					return;
				}

				case Type.MEMBER_VARS_SET_DEFAULT_STMT:
				{
					sOut.Append("MEMBER_VARS_SET_DEFAULT_STMT");
					return;
				}

				case Type.NAMESPACE_DECL:
				{
					sOut.Append("NAMESPACE_DECL");
					return;
				}

				case Type.NULL_EXPR:
				{
					sOut.Append("NULL_EXPR");
					return;
				}

				case Type.THIS_EXPR:
				{
					sOut.Append("THIS_EXPR");
					return;
				}

			}
			sOut.Append("???");
		}

	}
}

