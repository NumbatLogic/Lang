namespace NumbatLogic
{
	class ClassDecl : AST
	{
		public Token m_pNameToken;
		public Token m_pBaseToken;
		public OwnedVector<GenericTypeDecl> m_pGenericTypeDeclVector;
		public NamespaceNode m_pNamespaceNode;
		protected ClassDecl m_pBaseClassDecl;
		protected Token m_pAccessLevelToken;
		protected Token m_pTypeToken;
		protected Token m_pConstructorAccessLevelToken;
		protected Token m_pConstructorTypeToken;
		public ClassDecl()
		{
			m_eType = AST.Type.AST_CLASS_DECL;
			m_bCanDescend = true;
			m_pGenericTypeDeclVector = new OwnedVector<GenericTypeDecl>();
			m_pNamespaceNode = null;
			m_pBaseClassDecl = null;
		}

		public static ClassDecl TryCreate(TokenContainer pTokenContainer, OffsetDatum pOffsetDatum)
		{
			OffsetDatum pTempOffset = OffsetDatum.Create(pOffsetDatum);
			Token pClassToken = pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_KEYWORD_CLASS);
			if (pClassToken == null)
			{
				return null;
			}
			pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
			ClassDecl pClassDecl = new ClassDecl();
			Token pNameToken = pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_IDENTIFIER);
			if (pNameToken == null)
			{
				Console.Log("expected class name");
				Console.Log(pTokenContainer.StringifyOffset(pTempOffset));
				NumbatLogic.Assert.Plz(false);
				return null;
			}
			pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
			Token pAngleBracketLeft = pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_ANGLE_BRACKET_LEFT);
			if (pAngleBracketLeft != null)
			{
				pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
				while (true)
				{
					if (pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_ANGLE_BRACKET_RIGHT) != null)
					{
						pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
						break;
					}
					GenericTypeDecl pGenericTypeDecl = GenericTypeDecl.TryCreate(pTokenContainer, pTempOffset);
					if (pGenericTypeDecl == null)
					{
						Console.Log("expected inner GenericTypeDecl");
						NumbatLogic.Assert.Plz(false);
					}
					NumbatLogic.GenericTypeDecl __3828846222 = pGenericTypeDecl;
					pGenericTypeDecl = null;
					pClassDecl.m_pGenericTypeDeclVector.PushBack(__3828846222);
					if (pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_ANGLE_BRACKET_RIGHT) != null)
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
			}
			Token pBaseToken = null;
			if (pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_COLON) != null)
			{
				pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
				pBaseToken = pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_IDENTIFIER);
				if (pNameToken == null)
				{
					Console.Log("expected base class name");
					Console.Log(pTokenContainer.StringifyOffset(pTempOffset));
					NumbatLogic.Assert.Plz(false);
					return null;
				}
				pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
			}
			if (pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_CURLY_BRACE_LEFT) == null)
			{
				Console.Log("expected opening curly brace");
				Console.Log(pTokenContainer.StringifyOffset(pTempOffset));
				NumbatLogic.Assert.Plz(false);
				return null;
			}
			pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
			pClassDecl.m_pFirstToken = pClassToken;
			pClassDecl.m_pNameToken = pNameToken;
			pClassDecl.m_pBaseToken = pBaseToken;
			while (true)
			{
				if (pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_CURLY_BRACE_RIGHT) != null)
				{
					pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
					break;
				}
				AST pAST;
				pAST = MemberVarDecl.TryCreate(pTokenContainer, pTempOffset);
				if (pAST != null)
				{
					NumbatLogic.AST __3125986036 = pAST;
					pAST = null;
					pClassDecl.AddChild(__3125986036);
					continue;
				}
				pAST = MemberFunctionDecl.TryCreate(pTokenContainer, pTempOffset, pClassDecl);
				if (pAST != null)
				{
					NumbatLogic.AST __3125986036 = pAST;
					pAST = null;
					pClassDecl.AddChild(__3125986036);
					continue;
				}
				pAST = MemberEnumDecl.TryCreate(pTokenContainer, pTempOffset);
				if (pAST != null)
				{
					NumbatLogic.AST __3125986036 = pAST;
					pAST = null;
					pClassDecl.AddChild(__3125986036);
					continue;
				}
				pAST = TorDecl.TryCreate(pTokenContainer, pTempOffset, pClassDecl);
				if (pAST != null)
				{
					NumbatLogic.AST __3125986036 = pAST;
					pAST = null;
					pClassDecl.AddChild(__3125986036);
					continue;
				}
				pAST = DelegateDecl.TryCreate(pTokenContainer, pTempOffset, pClassDecl);
				if (pAST != null)
				{
					NumbatLogic.AST __3125986036 = pAST;
					pAST = null;
					pClassDecl.AddChild(__3125986036);
					continue;
				}
				Console.Log("expected to parse somethting within class...");
				Console.Log(pTokenContainer.StringifyOffset(pTempOffset));
				NumbatLogic.Assert.Plz(false);
			}
			pOffsetDatum.Set(pTempOffset);
			NumbatLogic.ClassDecl __112680214 = pClassDecl;
			pClassDecl = null;
			return __112680214;
		}

		public override void PreValidate(Validator pValidator, OperatorExpr pParent)
		{
			m_pNamespaceNode = pValidator.m_pCurrentNamespaceNode;
		}

		public override void Validate(Validator pValidator, OperatorExpr pParent)
		{
			AddClassDeclReference(this, AST.OutputFile.SOURCE, false);
			if (m_pBaseToken != null)
			{
				string sClassName = m_pBaseToken.GetString();
				AST pType = FindByName(sClassName, this);
				if (pType == null)
				{
					InternalString sTemp = new InternalString("Unknown base class: ");
					sTemp.Append(sClassName);
					pValidator.AddError(sTemp.GetExternalString(), m_pBaseToken.m_sFileName, m_pBaseToken.m_nLine, m_pBaseToken.m_nColumn);
				}
				else
					if (pType.m_eType != AST.Type.AST_CLASS_DECL)
					{
						InternalString sTemp = new InternalString("Unknown base class is not a class: ");
						sTemp.Append(sClassName);
						pValidator.AddError(sTemp.GetExternalString(), m_pBaseToken.m_sFileName, m_pBaseToken.m_nLine, m_pBaseToken.m_nColumn);
					}
				ClassDecl pClassDecl = (ClassDecl)(pType);
				AddClassDeclReference(pClassDecl, AST.OutputFile.HEADER, false);
			}
			{
				bool bHasOwnedPointer = false;
				bool bHasDefaultableVariable = false;
				bool bHasConstructor = false;
				bool bHasDestructor = false;
				AST pChild = m_pFirstChild;
				while (pChild != null)
				{
					if (pChild.m_eType == AST.Type.AST_MEMBER_VAR_DECL)
					{
						MemberVarDecl pMemberVarDecl = (MemberVarDecl)(pChild);
						TypeRef pTypeRef = pMemberVarDecl.m_pVarDecl.m_pTypeRef;
						while (pTypeRef.m_pChildTypeRef != null)
						{
							pTypeRef = pTypeRef.m_pChildTypeRef;
						}
						if (pTypeRef.m_ePointerType == TypeRef.PointerType.OWNED)
							bHasOwnedPointer = true;
						bHasDefaultableVariable = true;
					}
					if (pChild.m_eType == AST.Type.AST_TOR_DECL)
					{
						TorDecl pTorDecl = (TorDecl)(pChild);
						if (pTorDecl.m_pTypeToken.m_eType == Token.Type.TOKEN_KEYWORD_DESTRUCT)
							bHasDestructor = true;
						if (pTorDecl.m_pTypeToken.m_eType == Token.Type.TOKEN_KEYWORD_CONSTRUCT)
						{
							bHasConstructor = true;
							if (pTorDecl.m_pScope != null)
								pTorDecl.m_pScope.AddChildFront(new MemberVarsSetDefaultStmt());
						}
					}
					pChild = pChild.m_pNextSibling;
				}
				if (bHasDefaultableVariable && !bHasConstructor)
				{
					m_pConstructorAccessLevelToken = new Token();
					m_pConstructorAccessLevelToken.m_eType = Token.Type.TOKEN_KEYWORD_PUBLIC;
					AccessLevel pAccessLevel = new AccessLevel();
					pAccessLevel.m_eType = AST.Type.AST_ACCESS_LEVEL;
					pAccessLevel.m_pFirstToken = m_pConstructorAccessLevelToken;
					m_pConstructorTypeToken = new Token();
					m_pConstructorTypeToken.m_eType = Token.Type.TOKEN_KEYWORD_CONSTRUCT;
					ParamDecl pParamDecl = new ParamDecl();
					pParamDecl.m_pFirstToken = m_pFirstToken;
					Scope pScope = new Scope();
					pScope.AddChild(new MemberVarsSetDefaultStmt());
					TorDecl pTorDecl = new TorDecl();
					pTorDecl.m_eType = AST.Type.AST_TOR_DECL;
					pTorDecl.m_pParent = this;
					pTorDecl.m_pParentClassDecl = this;
					pTorDecl.m_pFirstToken = m_pFirstToken;
					pTorDecl.m_pAccessLevel = pAccessLevel;
					pTorDecl.m_pTypeToken = m_pConstructorTypeToken;
					pTorDecl.m_pParamDecl = pParamDecl;
					pTorDecl.m_pScope = pScope;
					pTorDecl.m_sDisambiguate = "";
					NumbatLogic.AccessLevel __2194276919 = pAccessLevel;
					pAccessLevel = null;
					pTorDecl.AddChild(__2194276919);
					NumbatLogic.ParamDecl __2049651157 = pParamDecl;
					pParamDecl = null;
					pTorDecl.AddChild(__2049651157);
					NumbatLogic.Scope __693694853 = pScope;
					pScope = null;
					pTorDecl.AddChild(__693694853);
					NumbatLogic.TorDecl __3416457985 = pTorDecl;
					pTorDecl = null;
					AddChild(__3416457985);
				}
				if (bHasOwnedPointer && !bHasDestructor)
				{
					m_pAccessLevelToken = new Token();
					m_pAccessLevelToken.m_eType = Token.Type.TOKEN_KEYWORD_PUBLIC;
					AccessLevel pAccessLevel = new AccessLevel();
					pAccessLevel.m_eType = AST.Type.AST_ACCESS_LEVEL;
					pAccessLevel.m_pFirstToken = m_pAccessLevelToken;
					m_pTypeToken = new Token();
					m_pTypeToken.m_eType = Token.Type.TOKEN_KEYWORD_DESTRUCT;
					ParamDecl pParamDecl = new ParamDecl();
					pParamDecl.m_pFirstToken = m_pFirstToken;
					Scope pScope = new Scope();
					TorDecl pTorDecl = new TorDecl();
					pTorDecl.m_eType = AST.Type.AST_TOR_DECL;
					pTorDecl.m_pParent = this;
					pTorDecl.m_pParentClassDecl = this;
					pTorDecl.m_pFirstToken = m_pFirstToken;
					pTorDecl.m_pAccessLevel = pAccessLevel;
					pTorDecl.m_pTypeToken = m_pTypeToken;
					pTorDecl.m_pParamDecl = pParamDecl;
					pTorDecl.m_pScope = pScope;
					pTorDecl.m_sDisambiguate = "";
					NumbatLogic.AccessLevel __2194276919 = pAccessLevel;
					pAccessLevel = null;
					pTorDecl.AddChild(__2194276919);
					NumbatLogic.ParamDecl __2049651157 = pParamDecl;
					pParamDecl = null;
					pTorDecl.AddChild(__2049651157);
					NumbatLogic.Scope __693694853 = pScope;
					pScope = null;
					pTorDecl.AddChild(__693694853);
					NumbatLogic.TorDecl __3416457985 = pTorDecl;
					pTorDecl = null;
					AddChild(__3416457985);
				}
			}
			base.Validate(pValidator, pParent);
		}

		public override ClassDecl FindClassDecl(string sTypeName, AST pCallingChild)
		{
			if (ExternalString.Equal(sTypeName, m_pNameToken.GetString()))
				return this;
			return null;
		}

		public override AST FindByName(string sxName, AST pCallingChild)
		{
			if (ExternalString.Equal(sxName, m_pNameToken.GetString()))
				return this;
			ClassDecl pBaseClassDecl = GetBaseClassDecl();
			if (pBaseClassDecl != null)
			{
				AST pResult = pBaseClassDecl.FindByName(sxName, null);
				if (pResult != null)
					return pResult;
			}
			if (pCallingChild != null)
			{
				for (int i = 0; i < m_pGenericTypeDeclVector.GetSize(); i++)
				{
					GenericTypeDecl pGenericTypeDecl = m_pGenericTypeDeclVector.Get(i);
					if (ExternalString.Equal(pGenericTypeDecl.m_pFirstToken.GetString(), sxName))
					{
						return pGenericTypeDecl;
					}
				}
			}
			return base.FindByName(sxName, pCallingChild);
		}

		public ClassDecl GetBaseClassDecl()
		{
			if (m_pBaseClassDecl != null)
				return m_pBaseClassDecl;
			if (m_pBaseToken != null && m_pParent != null)
			{
				string sBaseClassName = m_pBaseToken.GetString();
				ClassDecl pBaseClassDecl = m_pParent.FindClassDecl(sBaseClassName, this);
				if (pBaseClassDecl != null)
				{
					m_pBaseClassDecl = pBaseClassDecl;
					return pBaseClassDecl;
				}
			}
			return null;
		}

		public void StringifyTemplateThing(Language eLanguage, OutputFile eOutputFile, InternalString sOut)
		{
			sOut.AppendString("template <class ");
			for (int i = 0; i < m_pGenericTypeDeclVector.GetSize(); i++)
			{
				if (i > 0)
					sOut.Append(", ");
				GenericTypeDecl pGenericTypeDecl = m_pGenericTypeDeclVector.Get(i);
				pGenericTypeDecl.Stringify(eLanguage, eOutputFile, 0, sOut);
			}
			sOut.AppendString(">");
		}

		public override void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, InternalString sOut)
		{
			if (!(eLanguage == AST.Language.CPP && eOutputFile == AST.OutputFile.SOURCE))
			{
				if (eLanguage == AST.Language.CPP)
				{
					if (m_pGenericTypeDeclVector.GetSize() > 0)
					{
						Util.Pad(nDepth, sOut);
						StringifyTemplateThing(eLanguage, eOutputFile, sOut);
						sOut.AppendString("\n");
					}
				}
				Util.Pad(nDepth, sOut);
				sOut.Append("class ");
				m_pNameToken.Stringify(sOut);
				if (eLanguage == AST.Language.CS || eLanguage == AST.Language.NLL_DEF)
				{
					if (m_pGenericTypeDeclVector.GetSize() > 0)
					{
						sOut.AppendChar('<');
						for (int i = 0; i < m_pGenericTypeDeclVector.GetSize(); i++)
						{
							if (i > 0)
								sOut.Append(", ");
							GenericTypeDecl pGenericTypeDecl = m_pGenericTypeDeclVector.Get(i);
							pGenericTypeDecl.Stringify(eLanguage, eOutputFile, 0, sOut);
						}
						sOut.AppendChar('>');
					}
				}
				if (m_pBaseToken != null)
				{
					sOut.Append(" : ");
					if (eLanguage == AST.Language.CPP)
						sOut.Append("public ");
					m_pBaseToken.Stringify(sOut);
				}
				if (eLanguage == AST.Language.CS && m_pGenericTypeDeclVector.GetSize() > 0)
				{
					for (int i = 0; i < m_pGenericTypeDeclVector.GetSize(); i++)
					{
						if (m_pGenericTypeDeclVector.GetSize() == 1)
						{
							sOut.AppendChar(' ');
						}
						else
						{
							sOut.Append("\n");
							Util.Pad(nDepth + 1, sOut);
						}
						sOut.Append("where ");
						GenericTypeDecl pGenericTypeDecl = m_pGenericTypeDeclVector.Get(i);
						pGenericTypeDecl.Stringify(eLanguage, eOutputFile, 0, sOut);
						sOut.Append(" : class");
					}
				}
				sOut.Append("\n");
				Util.Pad(nDepth, sOut);
				sOut.Append("{\n");
				nDepth++;
			}
			AST pMember = m_pFirstChild;
			while (pMember != null)
			{
				pMember.Stringify(eLanguage, eOutputFile, nDepth, sOut);
				pMember = pMember.m_pNextSibling;
			}
			if (!(eLanguage == AST.Language.CPP && eOutputFile == AST.OutputFile.SOURCE))
			{
				nDepth--;
				Util.Pad(nDepth, sOut);
				if (eLanguage == AST.Language.CPP)
					sOut.Append("};\n");
				else
					sOut.Append("}\n");
			}
		}

		~ClassDecl()
		{
		}

	}
}

