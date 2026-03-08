#line 0 "../../../Source/Core/Semantic/Resolver.nll"
namespace NumbatLogic
{
#line 4 "../../../Source/Core/Semantic/Resolver.nll"
	class Resolver
	{
		public SymbolScope m_pGlobalScope;
		public OwnedVector<SymbolScope> m_pScopeVector;
		protected Vector<Symbol> m_pBuildTempSymbolVector;
		public Resolver()
		{
			m_pGlobalScope = new SymbolScope();
			m_pGlobalScope.m_eKind = SymbolScope.Kind.GLOBAL;
			m_pGlobalScope.m_pParent = null;
			m_pGlobalScope.m_pOwnerAST = null;
			m_pScopeVector = new OwnedVector<SymbolScope>();
			m_pBuildTempSymbolVector = new Vector<Symbol>();
		}

		protected ClassDecl GetClassDeclFromOwnerAST(AST pOwner)
		{
			if (pOwner == null)
				return null;
			if (pOwner.m_eType == AST.Type.AST_CLASS_DECL)
				return (ClassDecl)(pOwner);
			if (pOwner.m_eType == AST.Type.AST_MEMBER_CLASS_DECL)
			{
				MemberClassDecl pMember = (MemberClassDecl)(pOwner);
				return pMember.m_pClassDecl;
			}
			return null;
		}

		protected SymbolScope CreateChildScope(AST pNode, SymbolScope pParent, SymbolScope.Kind eKind)
		{
			SymbolScope pOwnedScope = new SymbolScope();
			NumbatLogic.SymbolScope __1793915775 = pOwnedScope;
			pOwnedScope = null;
			SymbolScope pNewScope = m_pScopeVector.PushBack(__1793915775);
			pNewScope.m_eKind = eKind;
			pNewScope.m_pParent = pParent;
			pNewScope.m_pOwnerAST = pNode;
			pNode.m_pSymbolScope = pNewScope;
			return pNewScope;
		}

		protected void AddSymbolToScope(SymbolScope pScope, string sShortName, Symbol.Kind eKind, AST pDeclAST, string sQualifiedName)
		{
			if (pScope == null || sShortName == null)
				return;
			string sQual = (sQualifiedName != null && !ExternalString.Equal(sQualifiedName, "")) ? sQualifiedName : sShortName;
			Symbol pOwnedSymbol = new Symbol();
			pOwnedSymbol.m_eKind = eKind;
			pOwnedSymbol.m_sShortName = sShortName;
			pOwnedSymbol.m_sQualifiedName = sQual;
			pOwnedSymbol.m_pDeclAST = pDeclAST;
			pOwnedSymbol.m_pScope = null;
			NumbatLogic.Symbol __3172268842 = pOwnedSymbol;
			pOwnedSymbol = null;
			pScope.AddSymbol(sShortName, __3172268842);
		}

		public SymbolScope GetEnclosingScope(AST pNode)
		{
			if (pNode == null)
				return null;
			AST pWalk = pNode;
			while (pWalk != null)
			{
				if (pWalk.m_eType == AST.Type.AST_CLASS_DECL || pWalk.m_eType == AST.Type.AST_MEMBER_CLASS_DECL)
				{
					if (pWalk.m_pSymbolScope == null)
						EnsureClassScope(pWalk);
				}
				if (pWalk.m_pSymbolScope != null)
					return pWalk.m_pSymbolScope;
				pWalk = pWalk.m_pParent;
			}
			return m_pGlobalScope;
		}

		protected void EnsureClassScope(AST pOwnerNode)
		{
			if (pOwnerNode == null || pOwnerNode.m_pSymbolScope != null)
				return;
			ClassDecl pClassDecl = GetClassDeclFromOwnerAST(pOwnerNode);
			if (pClassDecl == null)
				return;
			SymbolScope pEnclosing = m_pGlobalScope;
			AST pWalk = pOwnerNode.m_pParent;
			while (pWalk != null)
			{
				if (pWalk.m_eType == AST.Type.AST_CLASS_DECL || pWalk.m_eType == AST.Type.AST_MEMBER_CLASS_DECL)
				{
					if (pWalk.m_pSymbolScope == null)
						EnsureClassScope(pWalk);
				}
				if (pWalk.m_pSymbolScope != null)
				{
					pEnclosing = pWalk.m_pSymbolScope;
#line 114 "../../../Source/Core/Semantic/Resolver.nll"
					break;
				}
				pWalk = pWalk.m_pParent;
			}
			SymbolScope pClassScope = CreateChildScope(pOwnerNode, pEnclosing, SymbolScope.Kind.CLASS);
			AddGenericParamsToScope(pClassDecl, pClassScope);
			AST pChild = pClassDecl.m_pFirstChild;
			while (pChild != null)
			{
				AddMemberSymbolToScope(pChild, pClassScope);
				pChild = pChild.m_pNextSibling;
			}
		}

		protected void AddGenericParamsToScope(ClassDecl pClassDecl, SymbolScope pScope)
		{
			if (pClassDecl == null || pScope == null || pClassDecl.m_pGenericTypeDeclVector == null)
				return;
			for (int i = 0; i < pClassDecl.m_pGenericTypeDeclVector.GetSize(); i++)
			{
				GenericTypeDecl pGenericTypeDecl = pClassDecl.m_pGenericTypeDeclVector.Get(i);
				string sGenericName = pGenericTypeDecl.m_pFirstToken.GetString();
				AddSymbolToScope(pScope, sGenericName, Symbol.Kind.GENERIC_PARAM, pGenericTypeDecl, null);
			}
		}

		protected void AddMemberSymbolToScope(AST pMemberNode, SymbolScope pScope)
		{
			if (pMemberNode == null || pScope == null)
				return;
			if (pMemberNode.m_eType == AST.Type.AST_MEMBER_VAR_DECL)
			{
				MemberVarDecl pMemberVar = (MemberVarDecl)(pMemberNode);
				if (pMemberVar.m_pVarDecl != null)
					AddSymbolToScope(pScope, pMemberVar.m_pVarDecl.m_pNameToken.GetString(), Symbol.Kind.VAR, pMemberNode, null);
			}
			else
				if (pMemberNode.m_eType == AST.Type.AST_MEMBER_FUNCTION_DECL)
				{
					MemberFunctionDecl pMemberFunc = (MemberFunctionDecl)(pMemberNode);
					if (pMemberFunc.m_pFunctionDecl != null)
						AddSymbolToScope(pScope, pMemberFunc.m_pFunctionDecl.m_pNameToken.GetString(), Symbol.Kind.METHOD, pMemberNode, null);
				}
				else
					if (pMemberNode.m_eType == AST.Type.AST_MEMBER_CLASS_DECL)
					{
						MemberClassDecl pMemberClass = (MemberClassDecl)(pMemberNode);
						if (pMemberClass.m_pClassDecl != null)
						{
							string sName = pMemberClass.m_pClassDecl.m_pNameToken.GetString();
							InternalString sTemp = new InternalString("");
							pMemberClass.m_pClassDecl.AppendFullyQualifiedName(sTemp);
							AddSymbolToScope(pScope, sName, Symbol.Kind.CLASS, pMemberNode, sTemp.GetExternalString());
						}
					}
					else
						if (pMemberNode.m_eType == AST.Type.AST_MEMBER_ENUM_DECL)
						{
							MemberEnumDecl pMemberEnum = (MemberEnumDecl)(pMemberNode);
							if (pMemberEnum.m_pEnumDecl != null)
								AddSymbolToScope(pScope, pMemberEnum.m_pEnumDecl.m_pNameToken.GetString(), Symbol.Kind.ENUM, pMemberNode, null);
						}
						else
							if (pMemberNode.m_eType == AST.Type.DELEGATE_DECL)
							{
								DelegateDecl pDelegateDecl = (DelegateDecl)(pMemberNode);
								if (pDelegateDecl.m_pFunctionDecl != null && pDelegateDecl.m_pFunctionDecl.m_pNameToken != null)
									AddSymbolToScope(pScope, pDelegateDecl.m_pFunctionDecl.m_pNameToken.GetString(), Symbol.Kind.DELEGATE, pMemberNode, null);
							}
		}

		public void BuildForRoot(AST pRoot)
		{
			if (pRoot == null)
				return;
			pRoot.m_pSymbolScope = m_pGlobalScope;
			BuildForNode(pRoot, m_pGlobalScope);
		}

		protected void BuildForNode(AST pNode, SymbolScope pScope)
		{
			if (pNode == null || pScope == null)
				return;
			SymbolScope pCurrentScope = pScope;
			switch (pNode.m_eType)
			{
				case AST.Type.NAMESPACE_DECL:
				{
					NamespaceDecl pNamespaceDecl = (NamespaceDecl)(pNode);
					string sName = pNamespaceDecl.m_pNameToken.GetString();
					SymbolScope pNamespaceScope = pScope.FindNamespaceScope(sName);
					if (pNamespaceScope != null)
					{
						pNode.m_pSymbolScope = pNamespaceScope;
						pCurrentScope = pNamespaceScope;
#line 218 "../../../Source/Core/Semantic/Resolver.nll"
						break;
					}
					string sQual = sName;
					if (pNamespaceDecl.m_pNamespaceNode != null)
					{
						InternalString sTemp = new InternalString("");
						pNamespaceDecl.m_pNamespaceNode.AppendFullyQualifiedName(sTemp);
						sQual = sTemp.GetExternalString();
					}
					AddSymbolToScope(pScope, sName, Symbol.Kind.NAMESPACE, pNode, sQual);
					pNamespaceScope = CreateChildScope(pNode, pScope, SymbolScope.Kind.NAMESPACE);
					pCurrentScope = pNamespaceScope;
					m_pBuildTempSymbolVector.Clear();
					pScope.FindInThisScope(sName, m_pBuildTempSymbolVector);
					if (m_pBuildTempSymbolVector.GetSize() > 0)
					{
						Symbol pLast = m_pBuildTempSymbolVector.Get(m_pBuildTempSymbolVector.GetSize() - 1);
						pLast.m_pScope = pNamespaceScope;
					}
#line 243 "../../../Source/Core/Semantic/Resolver.nll"
					break;
				}

				case AST.Type.AST_CLASS_DECL:
				{
					ClassDecl pClassDecl = (ClassDecl)(pNode);
					bool bIsInnerOfMemberClass = (pClassDecl.m_pParent != null && pClassDecl.m_pParent.m_eType == AST.Type.AST_MEMBER_CLASS_DECL);
					if (!bIsInnerOfMemberClass)
					{
						string sName = pClassDecl.m_pNameToken.GetString();
						InternalString sTemp = new InternalString("");
						pClassDecl.AppendFullyQualifiedName(sTemp);
						AddSymbolToScope(pScope, sName, Symbol.Kind.CLASS, pNode, sTemp.GetExternalString());
					}
					pCurrentScope = CreateChildScope(pNode, pScope, SymbolScope.Kind.CLASS);
					SymbolScope pClassScope = pCurrentScope;
					AddGenericParamsToScope(pClassDecl, pClassScope);
#line 265 "../../../Source/Core/Semantic/Resolver.nll"
					break;
				}

				case AST.Type.AST_ENUM_DECL:
				{
					EnumDecl pEnumDecl = (EnumDecl)(pNode);
					if (pEnumDecl.m_pParent != null && pEnumDecl.m_pParent.m_eType == AST.Type.AST_MEMBER_ENUM_DECL)
#line 275 "../../../Source/Core/Semantic/Resolver.nll"
						break;
					AddSymbolToScope(pScope, pEnumDecl.m_pNameToken.GetString(), Symbol.Kind.ENUM, pNode, null);
#line 277 "../../../Source/Core/Semantic/Resolver.nll"
					break;
				}

				case AST.Type.AST_GENERIC_TYPE_DECL:
				{
					GenericTypeDecl pGenericTypeDecl = (GenericTypeDecl)(pNode);
					AddSymbolToScope(pScope, pGenericTypeDecl.m_pFirstToken.GetString(), Symbol.Kind.GENERIC_PARAM, pNode, null);
#line 287 "../../../Source/Core/Semantic/Resolver.nll"
					break;
				}

				case AST.Type.AST_FUNCTION_DECL:
				{
					FunctionDecl pFunctionDecl = (FunctionDecl)(pNode);
					if (pFunctionDecl.m_pParent != null && (pFunctionDecl.m_pParent.m_eType == AST.Type.DELEGATE_DECL || pFunctionDecl.m_pParent.m_eType == AST.Type.AST_TOR_DECL))
#line 298 "../../../Source/Core/Semantic/Resolver.nll"
						break;
					bool bIsInnerOfMember = (pFunctionDecl.m_pParent != null && pFunctionDecl.m_pParent.m_eType == AST.Type.AST_MEMBER_FUNCTION_DECL);
					if (!bIsInnerOfMember)
						AddSymbolToScope(pScope, pFunctionDecl.m_pNameToken.GetString(), Symbol.Kind.FUNCTION, pNode, null);
					pCurrentScope = CreateChildScope(pNode, pScope, SymbolScope.Kind.FUNCTION);
#line 310 "../../../Source/Core/Semantic/Resolver.nll"
					break;
				}

				case AST.Type.AST_VAR_DECL:
				{
					VarDecl pVarDecl = (VarDecl)(pNode);
					if (pVarDecl.m_pParent != null && pVarDecl.m_pParent.m_eType == AST.Type.AST_MEMBER_VAR_DECL)
#line 322 "../../../Source/Core/Semantic/Resolver.nll"
						break;
					AddSymbolToScope(pScope, pVarDecl.m_pNameToken.GetString(), Symbol.Kind.VAR, pNode, null);
#line 325 "../../../Source/Core/Semantic/Resolver.nll"
					break;
				}

				case AST.Type.DELEGATE_DECL:
				{
					DelegateDecl pDelegate = (DelegateDecl)(pNode);
					if (pDelegate.m_pFunctionDecl != null)
						AddSymbolToScope(pScope, pDelegate.m_pFunctionDecl.m_pNameToken.GetString(), Symbol.Kind.DELEGATE, pNode, null);
#line 332 "../../../Source/Core/Semantic/Resolver.nll"
					break;
				}

				case AST.Type.AST_MEMBER_FUNCTION_DECL:
				{
					AddMemberSymbolToScope(pNode, pCurrentScope);
#line 337 "../../../Source/Core/Semantic/Resolver.nll"
					break;
				}

				case AST.Type.AST_MEMBER_VAR_DECL:
				{
					AddMemberSymbolToScope(pNode, pCurrentScope);
#line 342 "../../../Source/Core/Semantic/Resolver.nll"
					break;
				}

				case AST.Type.AST_MEMBER_CLASS_DECL:
				{
					MemberClassDecl pMemberClass = (MemberClassDecl)(pNode);
					if (pMemberClass.m_pClassDecl != null)
					{
						AddMemberSymbolToScope(pNode, pCurrentScope);
						pCurrentScope = CreateChildScope(pNode, pScope, SymbolScope.Kind.CLASS);
					}
#line 352 "../../../Source/Core/Semantic/Resolver.nll"
					break;
				}

				case AST.Type.AST_MEMBER_ENUM_DECL:
				{
					AddMemberSymbolToScope(pNode, pCurrentScope);
#line 357 "../../../Source/Core/Semantic/Resolver.nll"
					break;
				}

				case AST.Type.ENUM_DECL_VALUE:
				{
					EnumDeclValue pEnumValue = (EnumDeclValue)(pNode);
					AddSymbolToScope(pScope, pEnumValue.m_pFirstToken.GetString(), Symbol.Kind.ENUM_VALUE, pNode, null);
#line 363 "../../../Source/Core/Semantic/Resolver.nll"
					break;
				}

				case AST.Type.AST_SCOPE:
				{
					pCurrentScope = CreateChildScope(pNode, pScope, SymbolScope.Kind.BLOCK);
#line 368 "../../../Source/Core/Semantic/Resolver.nll"
					break;
				}

				case AST.Type.AST_FOR_STMT:
				{
					pCurrentScope = CreateChildScope(pNode, pScope, SymbolScope.Kind.BLOCK);
#line 374 "../../../Source/Core/Semantic/Resolver.nll"
					break;
				}

				case AST.Type.AST_TOR_DECL:
				{
					pCurrentScope = CreateChildScope(pNode, pScope, SymbolScope.Kind.FUNCTION);
#line 380 "../../../Source/Core/Semantic/Resolver.nll"
					break;
				}

			}
			AST pChild = pNode.m_pFirstChild;
			while (pChild != null)
			{
				AST pNext = pChild.m_pNextSibling;
				BuildForNode(pChild, pCurrentScope);
				pChild = pNext;
			}
		}

		public void ResolveInScopeChainNoBaseClasses(string sName, SymbolScope pStartScope, Vector<Symbol> pOut)
		{
			Assert.Plz(pOut != null);
			pOut.Clear();
			SymbolScope pScope = pStartScope;
			while (pScope != null)
			{
				pScope.FindInThisScope(sName, pOut);
				if (pOut.GetSize() > 0)
					return;
				pScope = pScope.m_pParent;
			}
		}

		public void ResolveInScopeChain(string sName, SymbolScope pStartScope, Vector<Symbol> pOut)
		{
			Assert.Plz(pOut != null);
			pOut.Clear();
			SymbolScope pScope = pStartScope;
			while (pScope != null)
			{
				pScope.FindInThisScope(sName, pOut);
				if (pOut.GetSize() > 0)
					return;
				if (pScope.m_eKind == SymbolScope.Kind.CLASS)
				{
					ClassDecl pClass = GetClassDeclFromOwnerAST(pScope.m_pOwnerAST);
					if (pClass != null)
					{
						ClassDecl pBase = pClass.GetBaseClassDeclForScopeLookup(this);
						while (pBase != null)
						{
							if (pBase.m_pSymbolScope != null)
							{
								pBase.m_pSymbolScope.FindInThisScope(sName, pOut);
								if (pOut.GetSize() > 0)
									return;
							}
							pBase = pBase.GetBaseClassDeclForScopeLookup(this);
						}
					}
				}
				pScope = pScope.m_pParent;
			}
		}

		public void ResolveFromNode(AST pNode, string sName, Vector<Symbol> pOut)
		{
			SymbolScope pScope = GetEnclosingScope(pNode);
			ResolveInScopeChain(sName, pScope, pOut);
		}

		~Resolver()
		{
		}

	}
}

