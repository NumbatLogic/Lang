#line 1 "/home/cliffya/git/Lang/Source/Core/AST/ClassDecl.nll"
namespace NumbatLogic
{
	class ClassDecl : AST
	{
		public Token m_pNameToken;
		public bool m_bDisposable;
		public TypeRef m_pBaseTypeRef;
		public OwnedVector<GenericTypeDecl> m_pGenericTypeDeclVector;
		public Vector<DecoratorCall> m_pDecoratorCallVector;
		public NamespaceNode m_pNamespaceNode;
#line 12 "/home/cliffya/git/Lang/Source/Core/AST/ClassDecl.nll"
		protected ClassDecl m_pBaseClassDecl;
#line 14 "/home/cliffya/git/Lang/Source/Core/AST/ClassDecl.nll"
		protected Token m_pAccessLevelToken;
		protected Token m_pTypeToken;
#line 17 "/home/cliffya/git/Lang/Source/Core/AST/ClassDecl.nll"
		protected Token m_pConstructorAccessLevelToken;
		protected Token m_pConstructorTypeToken;
#line 20 "/home/cliffya/git/Lang/Source/Core/AST/ClassDecl.nll"
		public ClassDecl()
		{
			m_eType = AST.Type.AST_CLASS_DECL;
			m_bCanDescend = true;
			m_pGenericTypeDeclVector = new OwnedVector<GenericTypeDecl>();
			m_pDecoratorCallVector = new Vector<DecoratorCall>();
			m_pNamespaceNode = null;
			m_pBaseClassDecl = null;
		}

		public static ClassDecl TryCreate(TokenContainer pTokenContainer, OffsetDatum pOffsetDatum, AST pParent)
		{
			OffsetDatum pTempOffset = OffsetDatum.Create(pOffsetDatum);
#line 34 "/home/cliffya/git/Lang/Source/Core/AST/ClassDecl.nll"
			Token pClassToken = pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_KEYWORD_CLASS);
			if (pClassToken == null)
			{
#line 36 "/home/cliffya/git/Lang/Source/Core/AST/ClassDecl.nll"
				return null;
			}
#line 37 "/home/cliffya/git/Lang/Source/Core/AST/ClassDecl.nll"
			pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
#line 39 "/home/cliffya/git/Lang/Source/Core/AST/ClassDecl.nll"
			Token pDisposableToken = pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_KEYWORD_DISPOSABLE);
			if (pDisposableToken != null)
				pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
#line 43 "/home/cliffya/git/Lang/Source/Core/AST/ClassDecl.nll"
			ClassDecl pClassDecl = new ClassDecl();
			pClassDecl.m_bDisposable = pDisposableToken != null;
#line 46 "/home/cliffya/git/Lang/Source/Core/AST/ClassDecl.nll"
			OwnedVector<DecoratorCall> pOwnedDecoratorCallVector = new OwnedVector<DecoratorCall>();
			while (true)
			{
				DecoratorCall pDecoratorCall = DecoratorCall.TryCreate(pTokenContainer, pTempOffset);
				if (pDecoratorCall == null)
				{
#line 51 "/home/cliffya/git/Lang/Source/Core/AST/ClassDecl.nll"
					break;
				}
				NumbatLogic.DecoratorCall __1592970759 = pDecoratorCall;
#line 53 "/home/cliffya/git/Lang/Source/Core/AST/ClassDecl.nll"
				pDecoratorCall = null;
#line 53 "/home/cliffya/git/Lang/Source/Core/AST/ClassDecl.nll"
				pOwnedDecoratorCallVector.PushBack(__1592970759);
			}
#line 56 "/home/cliffya/git/Lang/Source/Core/AST/ClassDecl.nll"
			while (pOwnedDecoratorCallVector.GetSize() > 0)
			{
				DecoratorCall pDecoratorCall = pOwnedDecoratorCallVector.PopFront();
				pDecoratorCall.m_pParent = pClassDecl;
				DecoratorCall pTemp = pDecoratorCall;
				pClassDecl.m_pDecoratorCallVector.PushBack(pTemp);
				NumbatLogic.DecoratorCall __1593036357 = pDecoratorCall;
#line 62 "/home/cliffya/git/Lang/Source/Core/AST/ClassDecl.nll"
				pDecoratorCall = null;
#line 62 "/home/cliffya/git/Lang/Source/Core/AST/ClassDecl.nll"
				pClassDecl.AddChild(__1593036357);
			}
#line 65 "/home/cliffya/git/Lang/Source/Core/AST/ClassDecl.nll"
			Token pNameToken = pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_IDENTIFIER);
			if (pNameToken == null)
			{
				Console.Log("expected class name");
				Console.Log(pTokenContainer.StringifyOffset(pTempOffset));
				Assert.Plz(false);
				return null;
			}
			pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
#line 76 "/home/cliffya/git/Lang/Source/Core/AST/ClassDecl.nll"
			Token pAngleBracketLeft = pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_ANGLE_BRACKET_LEFT);
			if (pAngleBracketLeft != null)
			{
				pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
#line 81 "/home/cliffya/git/Lang/Source/Core/AST/ClassDecl.nll"
				while (true)
				{
					if (pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_ANGLE_BRACKET_RIGHT) != null)
					{
						pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
						break;
					}
#line 89 "/home/cliffya/git/Lang/Source/Core/AST/ClassDecl.nll"
					GenericTypeDecl pGenericTypeDecl = GenericTypeDecl.TryCreate(pTokenContainer, pTempOffset);
					if (pGenericTypeDecl == null)
					{
						Console.Log("expected inner GenericTypeDecl");
						Assert.Plz(false);
					}
					NumbatLogic.GenericTypeDecl __977440616 = pGenericTypeDecl;
					pGenericTypeDecl = null;
#line 96 "/home/cliffya/git/Lang/Source/Core/AST/ClassDecl.nll"
					pClassDecl.m_pGenericTypeDeclVector.PushBack(__977440616);
#line 99 "/home/cliffya/git/Lang/Source/Core/AST/ClassDecl.nll"
					if (pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_ANGLE_BRACKET_RIGHT) != null)
					{
#line 100 "/home/cliffya/git/Lang/Source/Core/AST/ClassDecl.nll"
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
#line 113 "/home/cliffya/git/Lang/Source/Core/AST/ClassDecl.nll"
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
#line 127 "/home/cliffya/git/Lang/Source/Core/AST/ClassDecl.nll"
			if (pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_CURLY_BRACE_LEFT) == null)
			{
				Console.Log("expected opening curly brace");
				Console.Log(pTokenContainer.StringifyOffset(pTempOffset));
				Assert.Plz(false);
				return null;
			}
			pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
#line 138 "/home/cliffya/git/Lang/Source/Core/AST/ClassDecl.nll"
			pClassDecl.m_pFirstToken = pClassToken;
			pClassDecl.m_pNameToken = pNameToken;
			pClassDecl.m_pBaseTypeRef = pBaseTypeRef;
			if (pBaseTypeRef != null)
			{
				NumbatLogic.TypeRef __276350391 = pBaseTypeRef;
#line 142 "/home/cliffya/git/Lang/Source/Core/AST/ClassDecl.nll"
				pBaseTypeRef = null;
#line 142 "/home/cliffya/git/Lang/Source/Core/AST/ClassDecl.nll"
				pClassDecl.AddChild(__276350391);
			}
#line 145 "/home/cliffya/git/Lang/Source/Core/AST/ClassDecl.nll"
			while (true)
			{
				if (pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_CURLY_BRACE_RIGHT) != null)
				{
					pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
					break;
				}
#line 153 "/home/cliffya/git/Lang/Source/Core/AST/ClassDecl.nll"
				AST pAST;
#line 155 "/home/cliffya/git/Lang/Source/Core/AST/ClassDecl.nll"
				pAST = MemberVarDecl.TryCreate(pTokenContainer, pTempOffset);
				if (pAST != null)
				{
					NumbatLogic.AST __3057801826 = pAST;
#line 158 "/home/cliffya/git/Lang/Source/Core/AST/ClassDecl.nll"
					pAST = null;
#line 158 "/home/cliffya/git/Lang/Source/Core/AST/ClassDecl.nll"
					pClassDecl.AddChild(__3057801826);
					continue;
				}
#line 162 "/home/cliffya/git/Lang/Source/Core/AST/ClassDecl.nll"
				pAST = MemberFunctionDecl.TryCreate(pTokenContainer, pTempOffset, pClassDecl);
				if (pAST != null)
				{
					NumbatLogic.AST __3057867422 = pAST;
#line 165 "/home/cliffya/git/Lang/Source/Core/AST/ClassDecl.nll"
					pAST = null;
#line 165 "/home/cliffya/git/Lang/Source/Core/AST/ClassDecl.nll"
					pClassDecl.AddChild(__3057867422);
					continue;
				}
#line 169 "/home/cliffya/git/Lang/Source/Core/AST/ClassDecl.nll"
				pAST = MemberClassDecl.TryCreate(pTokenContainer, pTempOffset, pClassDecl);
				if (pAST != null)
				{
					NumbatLogic.AST __3057933018 = pAST;
#line 172 "/home/cliffya/git/Lang/Source/Core/AST/ClassDecl.nll"
					pAST = null;
#line 172 "/home/cliffya/git/Lang/Source/Core/AST/ClassDecl.nll"
					pClassDecl.AddChild(__3057933018);
					continue;
				}
#line 176 "/home/cliffya/git/Lang/Source/Core/AST/ClassDecl.nll"
				pAST = MemberEnumDecl.TryCreate(pTokenContainer, pTempOffset);
				if (pAST != null)
				{
					NumbatLogic.AST __3057933025 = pAST;
#line 179 "/home/cliffya/git/Lang/Source/Core/AST/ClassDecl.nll"
					pAST = null;
#line 179 "/home/cliffya/git/Lang/Source/Core/AST/ClassDecl.nll"
					pClassDecl.AddChild(__3057933025);
					continue;
				}
#line 183 "/home/cliffya/git/Lang/Source/Core/AST/ClassDecl.nll"
				pAST = TorDecl.TryCreate(pTokenContainer, pTempOffset, pClassDecl);
				if (pAST != null)
				{
					NumbatLogic.AST __3057998621 = pAST;
#line 186 "/home/cliffya/git/Lang/Source/Core/AST/ClassDecl.nll"
					pAST = null;
#line 186 "/home/cliffya/git/Lang/Source/Core/AST/ClassDecl.nll"
					pClassDecl.AddChild(__3057998621);
					continue;
				}
#line 190 "/home/cliffya/git/Lang/Source/Core/AST/ClassDecl.nll"
				pAST = DelegateDecl.TryCreate(pTokenContainer, pTempOffset, pClassDecl);
				if (pAST != null)
				{
					NumbatLogic.AST __3058064217 = pAST;
#line 193 "/home/cliffya/git/Lang/Source/Core/AST/ClassDecl.nll"
					pAST = null;
#line 193 "/home/cliffya/git/Lang/Source/Core/AST/ClassDecl.nll"
					pClassDecl.AddChild(__3058064217);
					continue;
				}
#line 197 "/home/cliffya/git/Lang/Source/Core/AST/ClassDecl.nll"
				Console.Log("expected to parse somethting within class...");
				Console.Log(pTokenContainer.StringifyOffset(pTempOffset));
				Assert.Plz(false);
			}
#line 203 "/home/cliffya/git/Lang/Source/Core/AST/ClassDecl.nll"
			pOffsetDatum.Set(pTempOffset);
			NumbatLogic.ClassDecl __446640452 = pClassDecl;
#line 204 "/home/cliffya/git/Lang/Source/Core/AST/ClassDecl.nll"
			pClassDecl = null;
#line 204 "/home/cliffya/git/Lang/Source/Core/AST/ClassDecl.nll"
			return __446640452;
		}

		public override void PreValidate(Validator pValidator, OperatorExpr pParent)
		{
			m_pNamespaceNode = pValidator.m_pCurrentNamespaceNode;
		}

		public override void Validate(Validator pValidator, OperatorExpr pParent)
		{
			AddClassDeclReference(this, AST.OutputFile.SOURCE, false);
#line 216 "/home/cliffya/git/Lang/Source/Core/AST/ClassDecl.nll"
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
#line 227 "/home/cliffya/git/Lang/Source/Core/AST/ClassDecl.nll"
				if (pBaseValueType.m_eType != ValueType.Type.CLASS_DECL_VALUE)
				{
					InternalString sTemp = new InternalString("Unknown base class is not a class: ");
					sTemp.Append(m_pBaseTypeRef.m_pTypeToken.GetString());
					pValidator.AddError(sTemp.GetExternalString(), m_pBaseTypeRef.m_pFirstToken.m_sFileName, m_pBaseTypeRef.m_pFirstToken.m_nLine, m_pBaseTypeRef.m_pFirstToken.m_nColumn);
				}
#line 234 "/home/cliffya/git/Lang/Source/Core/AST/ClassDecl.nll"
				Assert.Plz(pBaseValueType.m_pClassDecl != null);
				AddClassDeclReference(pBaseValueType.m_pClassDecl, AST.OutputFile.HEADER, false);
			}
			{
#line 241 "/home/cliffya/git/Lang/Source/Core/AST/ClassDecl.nll"
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
#line 260 "/home/cliffya/git/Lang/Source/Core/AST/ClassDecl.nll"
						bHasDefaultableVariable = true;
					}
#line 263 "/home/cliffya/git/Lang/Source/Core/AST/ClassDecl.nll"
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
#line 276 "/home/cliffya/git/Lang/Source/Core/AST/ClassDecl.nll"
					pChild = pChild.m_pNextSibling;
				}
#line 279 "/home/cliffya/git/Lang/Source/Core/AST/ClassDecl.nll"
				if (bHasDefaultableVariable && !bHasConstructor)
				{
					m_pConstructorAccessLevelToken = new Token();
					m_pConstructorAccessLevelToken.m_eType = Token.Type.TOKEN_KEYWORD_PUBLIC;
#line 284 "/home/cliffya/git/Lang/Source/Core/AST/ClassDecl.nll"
					AccessLevel pAccessLevel = new AccessLevel();
					pAccessLevel.m_eType = AST.Type.AST_ACCESS_LEVEL;
					pAccessLevel.m_pFirstToken = m_pConstructorAccessLevelToken;
#line 288 "/home/cliffya/git/Lang/Source/Core/AST/ClassDecl.nll"
					m_pConstructorTypeToken = new Token();
					m_pConstructorTypeToken.m_eType = Token.Type.TOKEN_KEYWORD_CONSTRUCT;
#line 291 "/home/cliffya/git/Lang/Source/Core/AST/ClassDecl.nll"
					ParamDecl pParamDecl = new ParamDecl();
					pParamDecl.m_pFirstToken = m_pFirstToken;
#line 294 "/home/cliffya/git/Lang/Source/Core/AST/ClassDecl.nll"
					Scope pScope = new Scope();
					pScope.AddChild(new MemberVarsSetDefaultStmt());
#line 297 "/home/cliffya/git/Lang/Source/Core/AST/ClassDecl.nll"
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
					NumbatLogic.AccessLevel __874017451 = pAccessLevel;
					pAccessLevel = null;
#line 308 "/home/cliffya/git/Lang/Source/Core/AST/ClassDecl.nll"
					pTorDecl.AddChild(__874017451);
					NumbatLogic.ParamDecl __2038185877 = pParamDecl;
#line 309 "/home/cliffya/git/Lang/Source/Core/AST/ClassDecl.nll"
					pParamDecl = null;
#line 309 "/home/cliffya/git/Lang/Source/Core/AST/ClassDecl.nll"
					pTorDecl.AddChild(__2038185877);
					NumbatLogic.Scope __3586143822 = pScope;
#line 310 "/home/cliffya/git/Lang/Source/Core/AST/ClassDecl.nll"
					pScope = null;
#line 310 "/home/cliffya/git/Lang/Source/Core/AST/ClassDecl.nll"
					pTorDecl.AddChild(__3586143822);
					NumbatLogic.TorDecl __3671906211 = pTorDecl;
					pTorDecl = null;
#line 312 "/home/cliffya/git/Lang/Source/Core/AST/ClassDecl.nll"
					AddChild(__3671906211);
				}
#line 315 "/home/cliffya/git/Lang/Source/Core/AST/ClassDecl.nll"
				if (bHasOwnedPointer && !bHasDestructor)
				{
					m_pAccessLevelToken = new Token();
					m_pAccessLevelToken.m_eType = Token.Type.TOKEN_KEYWORD_PUBLIC;
#line 320 "/home/cliffya/git/Lang/Source/Core/AST/ClassDecl.nll"
					AccessLevel pAccessLevel = new AccessLevel();
					pAccessLevel.m_eType = AST.Type.AST_ACCESS_LEVEL;
					pAccessLevel.m_pFirstToken = m_pAccessLevelToken;
#line 324 "/home/cliffya/git/Lang/Source/Core/AST/ClassDecl.nll"
					m_pTypeToken = new Token();
					m_pTypeToken.m_eType = Token.Type.TOKEN_KEYWORD_DESTRUCT;
#line 327 "/home/cliffya/git/Lang/Source/Core/AST/ClassDecl.nll"
					ParamDecl pParamDecl = new ParamDecl();
					pParamDecl.m_pFirstToken = m_pFirstToken;
#line 330 "/home/cliffya/git/Lang/Source/Core/AST/ClassDecl.nll"
					Scope pScope = new Scope();
#line 332 "/home/cliffya/git/Lang/Source/Core/AST/ClassDecl.nll"
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
					NumbatLogic.AccessLevel __874279842 = pAccessLevel;
					pAccessLevel = null;
#line 343 "/home/cliffya/git/Lang/Source/Core/AST/ClassDecl.nll"
					pTorDecl.AddChild(__874279842);
					NumbatLogic.ParamDecl __2038448268 = pParamDecl;
#line 344 "/home/cliffya/git/Lang/Source/Core/AST/ClassDecl.nll"
					pParamDecl = null;
#line 344 "/home/cliffya/git/Lang/Source/Core/AST/ClassDecl.nll"
					pTorDecl.AddChild(__2038448268);
					NumbatLogic.Scope __3586340624 = pScope;
#line 345 "/home/cliffya/git/Lang/Source/Core/AST/ClassDecl.nll"
					pScope = null;
#line 345 "/home/cliffya/git/Lang/Source/Core/AST/ClassDecl.nll"
					pTorDecl.AddChild(__3586340624);
					NumbatLogic.TorDecl __3672103013 = pTorDecl;
					pTorDecl = null;
#line 347 "/home/cliffya/git/Lang/Source/Core/AST/ClassDecl.nll"
					AddChild(__3672103013);
				}
			}
#line 351 "/home/cliffya/git/Lang/Source/Core/AST/ClassDecl.nll"
			base.Validate(pValidator, pParent);
		}

#line 357 "/home/cliffya/git/Lang/Source/Core/AST/ClassDecl.nll"
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
#line 372 "/home/cliffya/git/Lang/Source/Core/AST/ClassDecl.nll"
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
#line 389 "/home/cliffya/git/Lang/Source/Core/AST/ClassDecl.nll"
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
#line 413 "/home/cliffya/git/Lang/Source/Core/AST/ClassDecl.nll"
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

		public void AppendFullyQualifiedName(AST.Language eLanguage, InternalString sOut)
		{
			string sxSeparator = "::";
			if (eLanguage == AST.Language.CS)
				sxSeparator = ".";
#line 438 "/home/cliffya/git/Lang/Source/Core/AST/ClassDecl.nll"
			if (m_pParent != null && m_pParent.m_eType == AST.Type.AST_MEMBER_CLASS_DECL)
			{
				MemberClassDecl pMember = (MemberClassDecl)(m_pParent);
				pMember.m_pParentClassDecl.AppendFullyQualifiedName(eLanguage, sOut);
				sOut.Append(sxSeparator);
			}
			else
#line 444 "/home/cliffya/git/Lang/Source/Core/AST/ClassDecl.nll"
				if (m_pNamespaceNode != null && m_pNamespaceNode.m_sName != null)
				{
					m_pNamespaceNode.AppendFullyQualifiedName(eLanguage, sOut);
					sOut.Append(sxSeparator);
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
#line 469 "/home/cliffya/git/Lang/Source/Core/AST/ClassDecl.nll"
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
#line 481 "/home/cliffya/git/Lang/Source/Core/AST/ClassDecl.nll"
				Util.Pad(nDepth, pOutputBuilder.m_sOut);
				pOutputBuilder.m_sOut.Append("class ");
#line 484 "/home/cliffya/git/Lang/Source/Core/AST/ClassDecl.nll"
				if (eLanguage == AST.Language.NLL && m_pDecoratorCallVector != null && m_pDecoratorCallVector.GetSize() > 0)
				{
					for (int i = 0; i < m_pDecoratorCallVector.GetSize(); i++)
					{
						DecoratorCall pDecoratorCall = m_pDecoratorCallVector.Get(i);
						pDecoratorCall.Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
					}
					pOutputBuilder.m_sOut.AppendChar(' ');
				}
#line 494 "/home/cliffya/git/Lang/Source/Core/AST/ClassDecl.nll"
				m_pNameToken.Stringify(pOutputBuilder.m_sOut);
#line 496 "/home/cliffya/git/Lang/Source/Core/AST/ClassDecl.nll"
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
#line 512 "/home/cliffya/git/Lang/Source/Core/AST/ClassDecl.nll"
				if (m_pBaseTypeRef != null)
				{
					pOutputBuilder.m_sOut.Append(" : ");
					if (eLanguage == AST.Language.CPP)
						pOutputBuilder.m_sOut.Append("public ");
					m_pBaseTypeRef.Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
				}
#line 520 "/home/cliffya/git/Lang/Source/Core/AST/ClassDecl.nll"
				if (eLanguage == AST.Language.CS && m_bDisposable)
				{
					if (m_pBaseTypeRef == null)
						pOutputBuilder.m_sOut.Append(" : ");
					else
						pOutputBuilder.m_sOut.Append(", ");
					pOutputBuilder.m_sOut.Append("System.IDisposable");
				}
#line 529 "/home/cliffya/git/Lang/Source/Core/AST/ClassDecl.nll"
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
#line 543 "/home/cliffya/git/Lang/Source/Core/AST/ClassDecl.nll"
						pOutputBuilder.m_sOut.Append("where ");
						GenericTypeDecl pGenericTypeDecl = m_pGenericTypeDeclVector.Get(i);
						pGenericTypeDecl.Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
						pOutputBuilder.m_sOut.Append(" : class");
					}
				}
#line 550 "/home/cliffya/git/Lang/Source/Core/AST/ClassDecl.nll"
				pOutputBuilder.m_sOut.Append("\n");
				Util.Pad(nDepth, pOutputBuilder.m_sOut);
				pOutputBuilder.m_sOut.Append("{\n");
#line 554 "/home/cliffya/git/Lang/Source/Core/AST/ClassDecl.nll"
				nDepth++;
			}
#line 557 "/home/cliffya/git/Lang/Source/Core/AST/ClassDecl.nll"
			AST pMember = m_pFirstChild;
			while (pMember != null)
			{
				if (pMember != m_pBaseTypeRef && pMember.m_eType != AST.Type.AST_DECORATOR_CALL)
					pMember.Stringify(eLanguage, eOutputFile, nDepth, pOutputBuilder);
				pMember = pMember.m_pNextSibling;
			}
#line 565 "/home/cliffya/git/Lang/Source/Core/AST/ClassDecl.nll"
			if (!(eLanguage == AST.Language.CPP && eOutputFile == AST.OutputFile.SOURCE))
			{
				nDepth--;
#line 569 "/home/cliffya/git/Lang/Source/Core/AST/ClassDecl.nll"
				Util.Pad(nDepth, pOutputBuilder.m_sOut);
				if (eLanguage == AST.Language.CPP)
					pOutputBuilder.m_sOut.Append("};\n");
				else
					pOutputBuilder.m_sOut.Append("}\n");
			}
		}

#line 3 "/home/cliffya/git/Lang/Source/Core/AST/ClassDecl.nll"
		~ClassDecl()
		{
		}

	}
}

