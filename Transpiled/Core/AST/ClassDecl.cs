#line 1 "../../../Source/Core/AST/ClassDecl.nll"
namespace NumbatLogic
{
	class ClassDecl : AST
	{
		public Token m_pNameToken;
		public bool m_bDisposable;
		public TypeRef m_pBaseTypeRef;
		public OwnedVector<GenericTypeDecl> m_pGenericTypeDeclVector;
		public NamespaceNode m_pNamespaceNode;
#line 11 "../../../Source/Core/AST/ClassDecl.nll"
		protected ClassDecl m_pBaseClassDecl;
#line 13 "../../../Source/Core/AST/ClassDecl.nll"
		protected Token m_pAccessLevelToken;
		protected Token m_pTypeToken;
#line 16 "../../../Source/Core/AST/ClassDecl.nll"
		protected Token m_pConstructorAccessLevelToken;
		protected Token m_pConstructorTypeToken;
#line 19 "../../../Source/Core/AST/ClassDecl.nll"
		public ClassDecl()
		{
			m_eType = AST.Type.AST_CLASS_DECL;
			m_bCanDescend = true;
			m_pGenericTypeDeclVector = new OwnedVector<GenericTypeDecl>();
			m_pNamespaceNode = null;
			m_pBaseClassDecl = null;
		}

		public static ClassDecl TryCreate(TokenContainer pTokenContainer, OffsetDatum pOffsetDatum, AST pParent)
		{
			OffsetDatum pTempOffset = OffsetDatum.Create(pOffsetDatum);
#line 32 "../../../Source/Core/AST/ClassDecl.nll"
			Token pClassToken = pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_KEYWORD_CLASS);
			if (pClassToken == null)
			{
#line 34 "../../../Source/Core/AST/ClassDecl.nll"
				return null;
			}
#line 35 "../../../Source/Core/AST/ClassDecl.nll"
			pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
#line 37 "../../../Source/Core/AST/ClassDecl.nll"
			Token pDisposableToken = pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_KEYWORD_DISPOSABLE);
			if (pDisposableToken != null)
				pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
#line 41 "../../../Source/Core/AST/ClassDecl.nll"
			ClassDecl pClassDecl = new ClassDecl();
			pClassDecl.m_bDisposable = pDisposableToken != null;
#line 44 "../../../Source/Core/AST/ClassDecl.nll"
			Token pNameToken = pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_IDENTIFIER);
			if (pNameToken == null)
			{
				Console.Log("expected class name");
				Console.Log(pTokenContainer.StringifyOffset(pTempOffset));
				Assert.Plz(false);
				return null;
			}
			pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
#line 55 "../../../Source/Core/AST/ClassDecl.nll"
			Token pAngleBracketLeft = pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_ANGLE_BRACKET_LEFT);
			if (pAngleBracketLeft != null)
			{
				pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
#line 60 "../../../Source/Core/AST/ClassDecl.nll"
				while (true)
				{
					if (pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_ANGLE_BRACKET_RIGHT) != null)
					{
						pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
						break;
					}
#line 68 "../../../Source/Core/AST/ClassDecl.nll"
					GenericTypeDecl pGenericTypeDecl = GenericTypeDecl.TryCreate(pTokenContainer, pTempOffset);
					if (pGenericTypeDecl == null)
					{
						Console.Log("expected inner GenericTypeDecl");
						Assert.Plz(false);
					}
					NumbatLogic.GenericTypeDecl __977309417 = pGenericTypeDecl;
					pGenericTypeDecl = null;
#line 75 "../../../Source/Core/AST/ClassDecl.nll"
					pClassDecl.m_pGenericTypeDeclVector.PushBack(__977309417);
#line 78 "../../../Source/Core/AST/ClassDecl.nll"
					if (pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_ANGLE_BRACKET_RIGHT) != null)
					{
#line 79 "../../../Source/Core/AST/ClassDecl.nll"
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
			}
#line 92 "../../../Source/Core/AST/ClassDecl.nll"
			TypeRef pBaseTypeRef = null;
			if (pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_COLON) != null)
			{
				pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
				pBaseTypeRef = TypeRef.TryCreate(pTokenContainer, pTempOffset);
				if (pBaseTypeRef == null)
				{
					Console.Log("expected base class");
					Console.Log(pTokenContainer.StringifyOffset(pTempOffset));
					Assert.Plz(false);
					return null;
				}
			}
#line 106 "../../../Source/Core/AST/ClassDecl.nll"
			if (pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_CURLY_BRACE_LEFT) == null)
			{
				Console.Log("expected opening curly brace");
				Console.Log(pTokenContainer.StringifyOffset(pTempOffset));
				Assert.Plz(false);
				return null;
			}
			pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
#line 117 "../../../Source/Core/AST/ClassDecl.nll"
			pClassDecl.m_pFirstToken = pClassToken;
			pClassDecl.m_pNameToken = pNameToken;
			pClassDecl.m_pBaseTypeRef = pBaseTypeRef;
			if (pBaseTypeRef != null)
			{
				NumbatLogic.TypeRef __276219192 = pBaseTypeRef;
#line 121 "../../../Source/Core/AST/ClassDecl.nll"
				pBaseTypeRef = null;
#line 121 "../../../Source/Core/AST/ClassDecl.nll"
				pClassDecl.AddChild(__276219192);
			}
#line 124 "../../../Source/Core/AST/ClassDecl.nll"
			while (true)
			{
				if (pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_CURLY_BRACE_RIGHT) != null)
				{
					pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
					break;
				}
#line 132 "../../../Source/Core/AST/ClassDecl.nll"
				AST pAST;
#line 134 "../../../Source/Core/AST/ClassDecl.nll"
				pAST = MemberVarDecl.TryCreate(pTokenContainer, pTempOffset);
				if (pAST != null)
				{
					NumbatLogic.AST __3057670627 = pAST;
#line 137 "../../../Source/Core/AST/ClassDecl.nll"
					pAST = null;
#line 137 "../../../Source/Core/AST/ClassDecl.nll"
					pClassDecl.AddChild(__3057670627);
					continue;
				}
#line 141 "../../../Source/Core/AST/ClassDecl.nll"
				pAST = MemberFunctionDecl.TryCreate(pTokenContainer, pTempOffset, pClassDecl);
				if (pAST != null)
				{
					NumbatLogic.AST __3057736223 = pAST;
#line 144 "../../../Source/Core/AST/ClassDecl.nll"
					pAST = null;
#line 144 "../../../Source/Core/AST/ClassDecl.nll"
					pClassDecl.AddChild(__3057736223);
					continue;
				}
#line 148 "../../../Source/Core/AST/ClassDecl.nll"
				pAST = MemberClassDecl.TryCreate(pTokenContainer, pTempOffset, pClassDecl);
				if (pAST != null)
				{
					NumbatLogic.AST __3057801819 = pAST;
#line 151 "../../../Source/Core/AST/ClassDecl.nll"
					pAST = null;
#line 151 "../../../Source/Core/AST/ClassDecl.nll"
					pClassDecl.AddChild(__3057801819);
					continue;
				}
#line 155 "../../../Source/Core/AST/ClassDecl.nll"
				pAST = MemberEnumDecl.TryCreate(pTokenContainer, pTempOffset);
				if (pAST != null)
				{
					NumbatLogic.AST __3057801826 = pAST;
#line 158 "../../../Source/Core/AST/ClassDecl.nll"
					pAST = null;
#line 158 "../../../Source/Core/AST/ClassDecl.nll"
					pClassDecl.AddChild(__3057801826);
					continue;
				}
#line 162 "../../../Source/Core/AST/ClassDecl.nll"
				pAST = TorDecl.TryCreate(pTokenContainer, pTempOffset, pClassDecl);
				if (pAST != null)
				{
					NumbatLogic.AST __3057867422 = pAST;
#line 165 "../../../Source/Core/AST/ClassDecl.nll"
					pAST = null;
#line 165 "../../../Source/Core/AST/ClassDecl.nll"
					pClassDecl.AddChild(__3057867422);
					continue;
				}
#line 169 "../../../Source/Core/AST/ClassDecl.nll"
				pAST = DelegateDecl.TryCreate(pTokenContainer, pTempOffset, pClassDecl);
				if (pAST != null)
				{
					NumbatLogic.AST __3057933018 = pAST;
#line 172 "../../../Source/Core/AST/ClassDecl.nll"
					pAST = null;
#line 172 "../../../Source/Core/AST/ClassDecl.nll"
					pClassDecl.AddChild(__3057933018);
					continue;
				}
#line 176 "../../../Source/Core/AST/ClassDecl.nll"
				Console.Log("expected to parse somethting within class...");
				Console.Log(pTokenContainer.StringifyOffset(pTempOffset));
				Assert.Plz(false);
			}
#line 182 "../../../Source/Core/AST/ClassDecl.nll"
			pOffsetDatum.Set(pTempOffset);
			NumbatLogic.ClassDecl __438903738 = pClassDecl;
#line 183 "../../../Source/Core/AST/ClassDecl.nll"
			pClassDecl = null;
#line 183 "../../../Source/Core/AST/ClassDecl.nll"
			return __438903738;
		}

		public override void PreValidate(Validator pValidator, OperatorExpr pParent)
		{
			m_pNamespaceNode = pValidator.m_pCurrentNamespaceNode;
		}

		public override void Validate(Validator pValidator, OperatorExpr pParent)
		{
			AddClassDeclReference(this, AST.OutputFile.SOURCE, false);
#line 195 "../../../Source/Core/AST/ClassDecl.nll"
			if (m_pBaseTypeRef != null)
			{
				ValueType pBaseValueType = m_pBaseTypeRef.CreateValueType(pValidator.m_pResolver);
				if (pBaseValueType == null)
				{
					InternalString sTemp = new InternalString("Unknown base class: ");
					sTemp.Append(m_pBaseTypeRef.m_pTypeToken.GetString());
					pValidator.AddError(sTemp.GetExternalString(), m_pBaseTypeRef.m_pFirstToken.m_sFileName, m_pBaseTypeRef.m_pFirstToken.m_nLine, m_pBaseTypeRef.m_pFirstToken.m_nColumn);
					return;
				}
#line 206 "../../../Source/Core/AST/ClassDecl.nll"
				if (pBaseValueType.m_eType != ValueType.Type.CLASS_DECL_VALUE)
				{
					InternalString sTemp = new InternalString("Unknown base class is not a class: ");
					sTemp.Append(m_pBaseTypeRef.m_pTypeToken.GetString());
					pValidator.AddError(sTemp.GetExternalString(), m_pBaseTypeRef.m_pFirstToken.m_sFileName, m_pBaseTypeRef.m_pFirstToken.m_nLine, m_pBaseTypeRef.m_pFirstToken.m_nColumn);
				}
#line 213 "../../../Source/Core/AST/ClassDecl.nll"
				Assert.Plz(pBaseValueType.m_pClassDecl != null);
				AddClassDeclReference(pBaseValueType.m_pClassDecl, AST.OutputFile.HEADER, false);
			}
			{
#line 220 "../../../Source/Core/AST/ClassDecl.nll"
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
						if (pTypeRef.m_ePointerType == TypeRef.PointerType.OWNED && !pMemberVarDecl.m_bStatic)
							bHasOwnedPointer = true;
#line 239 "../../../Source/Core/AST/ClassDecl.nll"
						bHasDefaultableVariable = true;
					}
#line 242 "../../../Source/Core/AST/ClassDecl.nll"
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
#line 255 "../../../Source/Core/AST/ClassDecl.nll"
					pChild = pChild.m_pNextSibling;
				}
#line 258 "../../../Source/Core/AST/ClassDecl.nll"
				if (bHasDefaultableVariable && !bHasConstructor)
				{
					m_pConstructorAccessLevelToken = new Token();
					m_pConstructorAccessLevelToken.m_eType = Token.Type.TOKEN_KEYWORD_PUBLIC;
#line 263 "../../../Source/Core/AST/ClassDecl.nll"
					AccessLevel pAccessLevel = new AccessLevel();
					pAccessLevel.m_eType = AST.Type.AST_ACCESS_LEVEL;
					pAccessLevel.m_pFirstToken = m_pConstructorAccessLevelToken;
#line 267 "../../../Source/Core/AST/ClassDecl.nll"
					m_pConstructorTypeToken = new Token();
					m_pConstructorTypeToken.m_eType = Token.Type.TOKEN_KEYWORD_CONSTRUCT;
#line 270 "../../../Source/Core/AST/ClassDecl.nll"
					ParamDecl pParamDecl = new ParamDecl();
					pParamDecl.m_pFirstToken = m_pFirstToken;
#line 273 "../../../Source/Core/AST/ClassDecl.nll"
					Scope pScope = new Scope();
					pScope.AddChild(new MemberVarsSetDefaultStmt());
#line 276 "../../../Source/Core/AST/ClassDecl.nll"
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
					NumbatLogic.AccessLevel __866280737 = pAccessLevel;
					pAccessLevel = null;
#line 287 "../../../Source/Core/AST/ClassDecl.nll"
					pTorDecl.AddChild(__866280737);
					NumbatLogic.ParamDecl __2030449163 = pParamDecl;
#line 288 "../../../Source/Core/AST/ClassDecl.nll"
					pParamDecl = null;
#line 288 "../../../Source/Core/AST/ClassDecl.nll"
					pTorDecl.AddChild(__2030449163);
					NumbatLogic.Scope __3578341519 = pScope;
#line 289 "../../../Source/Core/AST/ClassDecl.nll"
					pScope = null;
#line 289 "../../../Source/Core/AST/ClassDecl.nll"
					pTorDecl.AddChild(__3578341519);
					NumbatLogic.TorDecl __3664169497 = pTorDecl;
					pTorDecl = null;
#line 291 "../../../Source/Core/AST/ClassDecl.nll"
					AddChild(__3664169497);
				}
#line 294 "../../../Source/Core/AST/ClassDecl.nll"
				if (bHasOwnedPointer && !bHasDestructor)
				{
					m_pAccessLevelToken = new Token();
					m_pAccessLevelToken.m_eType = Token.Type.TOKEN_KEYWORD_PUBLIC;
#line 299 "../../../Source/Core/AST/ClassDecl.nll"
					AccessLevel pAccessLevel = new AccessLevel();
					pAccessLevel.m_eType = AST.Type.AST_ACCESS_LEVEL;
					pAccessLevel.m_pFirstToken = m_pAccessLevelToken;
#line 303 "../../../Source/Core/AST/ClassDecl.nll"
					m_pTypeToken = new Token();
					m_pTypeToken.m_eType = Token.Type.TOKEN_KEYWORD_DESTRUCT;
#line 306 "../../../Source/Core/AST/ClassDecl.nll"
					ParamDecl pParamDecl = new ParamDecl();
					pParamDecl.m_pFirstToken = m_pFirstToken;
#line 309 "../../../Source/Core/AST/ClassDecl.nll"
					Scope pScope = new Scope();
#line 311 "../../../Source/Core/AST/ClassDecl.nll"
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
					NumbatLogic.AccessLevel __874148643 = pAccessLevel;
					pAccessLevel = null;
#line 322 "../../../Source/Core/AST/ClassDecl.nll"
					pTorDecl.AddChild(__874148643);
					NumbatLogic.ParamDecl __2038317069 = pParamDecl;
#line 323 "../../../Source/Core/AST/ClassDecl.nll"
					pParamDecl = null;
#line 323 "../../../Source/Core/AST/ClassDecl.nll"
					pTorDecl.AddChild(__2038317069);
					NumbatLogic.Scope __3586209425 = pScope;
#line 324 "../../../Source/Core/AST/ClassDecl.nll"
					pScope = null;
#line 324 "../../../Source/Core/AST/ClassDecl.nll"
					pTorDecl.AddChild(__3586209425);
					NumbatLogic.TorDecl __3671971814 = pTorDecl;
					pTorDecl = null;
#line 326 "../../../Source/Core/AST/ClassDecl.nll"
					AddChild(__3671971814);
				}
			}
#line 330 "../../../Source/Core/AST/ClassDecl.nll"
			base.Validate(pValidator, pParent);
		}

#line 336 "../../../Source/Core/AST/ClassDecl.nll"
		public ClassDecl GetBaseClassDeclForScopeLookup(Resolver pResolver)
		{
			if (m_pBaseClassDecl != null)
				return m_pBaseClassDecl;
			if (m_pBaseTypeRef == null)
				return null;
			ClassDecl pBase = m_pBaseTypeRef.GetFoundClassDecl();
			if (pBase == null && m_pBaseTypeRef.m_pChildTypeRef != null)
				pBase = m_pBaseTypeRef.m_pChildTypeRef.GetFoundClassDecl();
			if (pBase != null)
			{
				m_pBaseClassDecl = pBase;
				return m_pBaseClassDecl;
			}
#line 351 "../../../Source/Core/AST/ClassDecl.nll"
			if (pResolver == null || m_pSymbolScope == null)
				return null;
			SymbolScope pParentScope = m_pSymbolScope.m_pParent;
			if (pParentScope == null)
				return null;
			string sBaseName = m_pBaseTypeRef.m_pTypeToken.GetString();
			Vector<Symbol> pCandidates = new Vector<Symbol>();
			pResolver.ResolveInScopeChainNoBaseClasses(sBaseName, pParentScope, pCandidates);
			if (pCandidates.GetSize() == 1)
			{
				Symbol pSym = pCandidates.Get(0);
				if (pSym.m_eKind == Symbol.Kind.CLASS && pSym.m_pDeclAST != null && pSym.m_pDeclAST.m_eType == AST.Type.AST_CLASS_DECL)
				{
					m_pBaseClassDecl = (ClassDecl)(pSym.m_pDeclAST);
					return m_pBaseClassDecl;
				}
#line 368 "../../../Source/Core/AST/ClassDecl.nll"
				if (pSym.m_eKind == Symbol.Kind.NAMESPACE && pSym.m_pScope != null && m_pBaseTypeRef.m_pChildTypeRef != null)
				{
					string sChildName = m_pBaseTypeRef.m_pChildTypeRef.m_pTypeToken.GetString();
					Vector<Symbol> pChildCandidates = new Vector<Symbol>();
					pResolver.ResolveInScopeChainNoBaseClasses(sChildName, pSym.m_pScope, pChildCandidates);
					if (pChildCandidates.GetSize() == 1)
					{
						Symbol pChildSym = pChildCandidates.Get(0);
						if (pChildSym.m_eKind == Symbol.Kind.CLASS && pChildSym.m_pDeclAST != null && pChildSym.m_pDeclAST.m_eType == AST.Type.AST_CLASS_DECL)
						{
							m_pBaseClassDecl = (ClassDecl)(pChildSym.m_pDeclAST);
							return m_pBaseClassDecl;
						}
					}
				}
			}
			return null;
		}

		public ClassDecl GetBaseClassDecl(Validator pValidator)
		{
			if (m_pBaseClassDecl != null)
				return m_pBaseClassDecl;
#line 392 "../../../Source/Core/AST/ClassDecl.nll"
			Validator pV = pValidator;
			if (pV == null)
			{
				Project pProject = GetProject();
				if (pProject != null)
					pV = pProject.m_pValidator;
			}
			if (m_pBaseTypeRef != null && m_pParent != null && pV != null)
			{
				ValueType pBaseValueType = m_pBaseTypeRef.CreateValueType(pV.m_pResolver);
				if (pBaseValueType != null)
				{
					m_pBaseClassDecl = pBaseValueType.m_pClassDecl;
					return m_pBaseClassDecl;
				}
			}
			return null;
		}

		public void AppendFullyQualifiedName(InternalString sOut)
		{
			if (m_pParent != null && m_pParent.m_eType == AST.Type.AST_MEMBER_CLASS_DECL)
			{
				MemberClassDecl pMember = (MemberClassDecl)(m_pParent);
				pMember.m_pParentClassDecl.AppendFullyQualifiedName(sOut);
				sOut.Append("::");
			}
			else
#line 419 "../../../Source/Core/AST/ClassDecl.nll"
				if (m_pNamespaceNode != null && m_pNamespaceNode.m_sName != null)
				{
					m_pNamespaceNode.AppendFullyQualifiedName(sOut);
					sOut.Append("::");
				}
			sOut.Append(m_pNameToken.GetString());
		}

		public void StringifyTemplateThing(Language eLanguage, OutputFile eOutputFile, OutputBuilder pOutputBuilder)
		{
			pOutputBuilder.m_sOut.AppendString("template <class ");
			for (int i = 0; i < m_pGenericTypeDeclVector.GetSize(); i++)
			{
				if (i > 0)
					pOutputBuilder.m_sOut.Append(", ");
				GenericTypeDecl pGenericTypeDecl = m_pGenericTypeDeclVector.Get(i);
				pGenericTypeDecl.Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
			}
			pOutputBuilder.m_sOut.AppendString(">");
		}

		public override void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder pOutputBuilder)
		{
			pOutputBuilder.UpdateSourceLocation(eLanguage, m_pFirstToken);
#line 444 "../../../Source/Core/AST/ClassDecl.nll"
			if (!(eLanguage == AST.Language.CPP && eOutputFile == AST.OutputFile.SOURCE))
			{
				if (eLanguage == AST.Language.CPP)
				{
					if (m_pGenericTypeDeclVector.GetSize() > 0)
					{
						Util.Pad(nDepth, pOutputBuilder.m_sOut);
						StringifyTemplateThing(eLanguage, eOutputFile, pOutputBuilder);
						pOutputBuilder.m_sOut.AppendString("\n");
					}
				}
#line 456 "../../../Source/Core/AST/ClassDecl.nll"
				Util.Pad(nDepth, pOutputBuilder.m_sOut);
				pOutputBuilder.m_sOut.Append("class ");
				m_pNameToken.Stringify(pOutputBuilder.m_sOut);
#line 460 "../../../Source/Core/AST/ClassDecl.nll"
				if (eLanguage == AST.Language.CS || eLanguage == AST.Language.NLL_DEF)
				{
					if (m_pGenericTypeDeclVector.GetSize() > 0)
					{
						pOutputBuilder.m_sOut.AppendChar('<');
						for (int i = 0; i < m_pGenericTypeDeclVector.GetSize(); i++)
						{
							if (i > 0)
								pOutputBuilder.m_sOut.Append(", ");
							GenericTypeDecl pGenericTypeDecl = m_pGenericTypeDeclVector.Get(i);
							pGenericTypeDecl.Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
						}
						pOutputBuilder.m_sOut.AppendChar('>');
					}
				}
#line 476 "../../../Source/Core/AST/ClassDecl.nll"
				if (m_pBaseTypeRef != null)
				{
					pOutputBuilder.m_sOut.Append(" : ");
					if (eLanguage == AST.Language.CPP)
						pOutputBuilder.m_sOut.Append("public ");
					m_pBaseTypeRef.Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
				}
#line 484 "../../../Source/Core/AST/ClassDecl.nll"
				if (eLanguage == AST.Language.CS && m_bDisposable)
				{
					if (m_pBaseTypeRef == null)
						pOutputBuilder.m_sOut.Append(" : ");
					else
						pOutputBuilder.m_sOut.Append(", ");
					pOutputBuilder.m_sOut.Append("System.IDisposable");
				}
#line 493 "../../../Source/Core/AST/ClassDecl.nll"
				if (eLanguage == AST.Language.CS && m_pGenericTypeDeclVector.GetSize() > 0)
				{
					for (int i = 0; i < m_pGenericTypeDeclVector.GetSize(); i++)
					{
						if (m_pGenericTypeDeclVector.GetSize() == 1)
						{
							pOutputBuilder.m_sOut.AppendChar(' ');
						}
						else
						{
							pOutputBuilder.m_sOut.Append("\n");
							Util.Pad(nDepth + 1, pOutputBuilder.m_sOut);
						}
#line 507 "../../../Source/Core/AST/ClassDecl.nll"
						pOutputBuilder.m_sOut.Append("where ");
						GenericTypeDecl pGenericTypeDecl = m_pGenericTypeDeclVector.Get(i);
						pGenericTypeDecl.Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
						pOutputBuilder.m_sOut.Append(" : class");
					}
				}
#line 514 "../../../Source/Core/AST/ClassDecl.nll"
				pOutputBuilder.m_sOut.Append("\n");
				Util.Pad(nDepth, pOutputBuilder.m_sOut);
				pOutputBuilder.m_sOut.Append("{\n");
#line 518 "../../../Source/Core/AST/ClassDecl.nll"
				nDepth++;
			}
#line 521 "../../../Source/Core/AST/ClassDecl.nll"
			AST pMember = m_pFirstChild;
			while (pMember != null)
			{
				if (pMember != m_pBaseTypeRef)
					pMember.Stringify(eLanguage, eOutputFile, nDepth, pOutputBuilder);
				pMember = pMember.m_pNextSibling;
			}
#line 529 "../../../Source/Core/AST/ClassDecl.nll"
			if (!(eLanguage == AST.Language.CPP && eOutputFile == AST.OutputFile.SOURCE))
			{
				nDepth--;
#line 533 "../../../Source/Core/AST/ClassDecl.nll"
				Util.Pad(nDepth, pOutputBuilder.m_sOut);
				if (eLanguage == AST.Language.CPP)
					pOutputBuilder.m_sOut.Append("};\n");
				else
					pOutputBuilder.m_sOut.Append("}\n");
			}
		}

#line 3 "../../../Source/Core/AST/ClassDecl.nll"
		~ClassDecl()
		{
		}

	}
}

