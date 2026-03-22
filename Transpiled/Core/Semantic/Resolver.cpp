#include "Resolver.hpp"
#include "SymbolScope.hpp"
#include "../../../../LangShared/Transpiled/Vector/OwnedVector.hpp"
#include "Symbol.hpp"
#include "../../../../LangShared/Source/Vector/CPP/Vector.hpp"
#include "../AST/AST.hpp"
#include "../AST/MemberClassDecl.hpp"
#include "../../../../LangShared/Source/ExternalString/CPP/ExternalString.hpp"
#include "../AST/ClassDecl.hpp"
#include "../AST/GenericTypeDecl.hpp"
#include "../Token.hpp"
#include "../AST/MemberVarDecl.hpp"
#include "../AST/VarDecl.hpp"
#include "../AST/MemberFunctionDecl.hpp"
#include "../AST/FunctionDecl.hpp"
#include "../../../../LangShared/Source/InternalString/CPP/InternalString.hpp"
#include "../AST/MemberEnumDecl.hpp"
#include "../AST/EnumDecl.hpp"
#include "../AST/DelegateDecl.hpp"
#include "../AST/NamespaceDecl.hpp"
#include "../NamespaceNode.hpp"
#include "../AST/EnumDeclValue.hpp"
#include "../../../../LangShared/Source/Assert/CPP/Assert.hpp"

namespace NumbatLogic
{
	class Resolver;
	class SymbolScope;
	template <class T>
	class OwnedVector;
	class Symbol;
	template <class T>
	class Vector;
	class ClassDecl;
	class MemberClassDecl;
	class ExternalString;
	class AST;
	class GenericTypeDecl;
	class Token;
	class MemberVarDecl;
	class MemberFunctionDecl;
	class InternalString;
	class MemberEnumDecl;
	class DelegateDecl;
	class NamespaceDecl;
	class NamespaceNode;
	class EnumDecl;
	class FunctionDecl;
	class VarDecl;
	class EnumDeclValue;
	class Assert;
}
#line 0 "/home/cliffya/git/Lang/Source/Core/Semantic/Resolver.nll"
namespace NumbatLogic
{
#line 4 "/home/cliffya/git/Lang/Source/Core/Semantic/Resolver.nll"
#line 16 "/home/cliffya/git/Lang/Source/Core/Semantic/Resolver.nll"
	Resolver::Resolver()
	{
		m_pGlobalScope = 0;
		m_pScopeVector = 0;
		m_pBuildTempSymbolVector = 0;
#line 18 "/home/cliffya/git/Lang/Source/Core/Semantic/Resolver.nll"
		m_pGlobalScope = new SymbolScope();
		m_pGlobalScope->m_eKind = SymbolScope::Kind::GLOBAL;
		m_pGlobalScope->m_pParent = 0;
		m_pGlobalScope->m_pOwnerAST = 0;
#line 23 "/home/cliffya/git/Lang/Source/Core/Semantic/Resolver.nll"
		m_pScopeVector = new OwnedVector<SymbolScope*>();
		m_pBuildTempSymbolVector = new Vector<Symbol*>();
	}

	ClassDecl* Resolver::GetClassDeclFromOwnerAST(AST* pOwner)
	{
		if (pOwner == 0)
			return 0;
		if (pOwner->m_eType == AST::Type::AST_CLASS_DECL)
			return (ClassDecl*)(pOwner);
		if (pOwner->m_eType == AST::Type::AST_MEMBER_CLASS_DECL)
		{
			MemberClassDecl* pMember = (MemberClassDecl*)(pOwner);
			return pMember->m_pClassDecl;
		}
		return 0;
	}

	SymbolScope* Resolver::CreateChildScope(AST* pNode, SymbolScope* pParent, SymbolScope::Kind eKind)
	{
		SymbolScope* pOwnedScope = new SymbolScope();
		NumbatLogic::SymbolScope* __1793915775 = pOwnedScope;
#line 44 "/home/cliffya/git/Lang/Source/Core/Semantic/Resolver.nll"
		pOwnedScope = 0;
#line 44 "/home/cliffya/git/Lang/Source/Core/Semantic/Resolver.nll"
		SymbolScope* pNewScope = m_pScopeVector->PushBack(__1793915775);
		pNewScope->m_eKind = eKind;
		pNewScope->m_pParent = pParent;
		pNewScope->m_pOwnerAST = pNode;
		pNode->m_pSymbolScope = pNewScope;
		if (pOwnedScope) delete pOwnedScope;
#line 49 "/home/cliffya/git/Lang/Source/Core/Semantic/Resolver.nll"
		return pNewScope;
	}

	void Resolver::AddSymbolToScope(SymbolScope* pScope, const char* sShortName, Symbol::Kind eKind, AST* pDeclAST, const char* sQualifiedName)
	{
		if (pScope == 0 || sShortName == 0)
			return;
		const char* sQual = (sQualifiedName != 0 && !ExternalString::Equal(sQualifiedName, "")) ? sQualifiedName : sShortName;
		Symbol* pOwnedSymbol = new Symbol();
		pOwnedSymbol->m_eKind = eKind;
		pOwnedSymbol->m_sShortName = sShortName;
		pOwnedSymbol->m_sQualifiedName = sQual;
		pOwnedSymbol->m_pDeclAST = pDeclAST;
		pOwnedSymbol->m_pScope = 0;
		NumbatLogic::Symbol* __3172268842 = pOwnedSymbol;
#line 63 "/home/cliffya/git/Lang/Source/Core/Semantic/Resolver.nll"
		pOwnedSymbol = 0;
#line 63 "/home/cliffya/git/Lang/Source/Core/Semantic/Resolver.nll"
		pScope->AddSymbol(sShortName, __3172268842);
		if (pOwnedSymbol) delete pOwnedSymbol;
	}

#line 69 "/home/cliffya/git/Lang/Source/Core/Semantic/Resolver.nll"
	SymbolScope* Resolver::GetEnclosingScope(AST* pNode)
	{
		if (pNode == 0)
			return 0;
#line 74 "/home/cliffya/git/Lang/Source/Core/Semantic/Resolver.nll"
		AST* pWalk = pNode;
		while (pWalk != 0)
		{
			if (pWalk->m_eType == AST::Type::AST_CLASS_DECL || pWalk->m_eType == AST::Type::AST_MEMBER_CLASS_DECL)
			{
				if (pWalk->m_pSymbolScope == 0)
					EnsureClassScope(pWalk);
			}
			if (pWalk->m_pSymbolScope != 0)
				return pWalk->m_pSymbolScope;
			pWalk = pWalk->m_pParent;
		}
#line 88 "/home/cliffya/git/Lang/Source/Core/Semantic/Resolver.nll"
		return m_pGlobalScope;
	}

#line 92 "/home/cliffya/git/Lang/Source/Core/Semantic/Resolver.nll"
	void Resolver::EnsureClassScope(AST* pOwnerNode)
	{
		if (pOwnerNode == 0 || pOwnerNode->m_pSymbolScope != 0)
			return;
#line 97 "/home/cliffya/git/Lang/Source/Core/Semantic/Resolver.nll"
		ClassDecl* pClassDecl = GetClassDeclFromOwnerAST(pOwnerNode);
		if (pClassDecl == 0)
			return;
#line 102 "/home/cliffya/git/Lang/Source/Core/Semantic/Resolver.nll"
		SymbolScope* pEnclosing = m_pGlobalScope;
		AST* pWalk = pOwnerNode->m_pParent;
		while (pWalk != 0)
		{
			if (pWalk->m_eType == AST::Type::AST_CLASS_DECL || pWalk->m_eType == AST::Type::AST_MEMBER_CLASS_DECL)
			{
				if (pWalk->m_pSymbolScope == 0)
					EnsureClassScope(pWalk);
			}
			if (pWalk->m_pSymbolScope != 0)
			{
				pEnclosing = pWalk->m_pSymbolScope;
				break;
			}
			pWalk = pWalk->m_pParent;
		}
#line 119 "/home/cliffya/git/Lang/Source/Core/Semantic/Resolver.nll"
		SymbolScope* pClassScope = CreateChildScope(pOwnerNode, pEnclosing, SymbolScope::Kind::CLASS);
		AddGenericParamsToScope(pClassDecl, pClassScope);
#line 122 "/home/cliffya/git/Lang/Source/Core/Semantic/Resolver.nll"
		AST* pChild = pClassDecl->m_pFirstChild;
		while (pChild != 0)
		{
			AddMemberSymbolToScope(pChild, pClassScope);
			pChild = pChild->m_pNextSibling;
		}
	}

	void Resolver::AddGenericParamsToScope(ClassDecl* pClassDecl, SymbolScope* pScope)
	{
		if (pClassDecl == 0 || pScope == 0 || pClassDecl->m_pGenericTypeDeclVector == 0)
			return;
		for (int i = 0; i < pClassDecl->m_pGenericTypeDeclVector->GetSize(); i++)
		{
			GenericTypeDecl* pGenericTypeDecl = pClassDecl->m_pGenericTypeDeclVector->Get(i);
			const char* sGenericName = pGenericTypeDecl->m_pFirstToken->GetString();
			AddSymbolToScope(pScope, sGenericName, Symbol::Kind::GENERIC_PARAM, pGenericTypeDecl, 0);
		}
	}

	void Resolver::AddMemberSymbolToScope(AST* pMemberNode, SymbolScope* pScope)
	{
		if (pMemberNode == 0 || pScope == 0)
			return;
		if (pMemberNode->m_eType == AST::Type::AST_MEMBER_VAR_DECL)
		{
			MemberVarDecl* pMemberVar = (MemberVarDecl*)(pMemberNode);
			if (pMemberVar->m_pVarDecl != 0)
				AddSymbolToScope(pScope, pMemberVar->m_pVarDecl->m_pNameToken->GetString(), Symbol::Kind::VAR, pMemberNode, 0);
		}
		else
#line 152 "/home/cliffya/git/Lang/Source/Core/Semantic/Resolver.nll"
			if (pMemberNode->m_eType == AST::Type::AST_MEMBER_FUNCTION_DECL)
			{
				MemberFunctionDecl* pMemberFunc = (MemberFunctionDecl*)(pMemberNode);
				if (pMemberFunc->m_pFunctionDecl != 0)
					AddSymbolToScope(pScope, pMemberFunc->m_pFunctionDecl->m_pNameToken->GetString(), Symbol::Kind::METHOD, pMemberNode, 0);
			}
			else
#line 158 "/home/cliffya/git/Lang/Source/Core/Semantic/Resolver.nll"
				if (pMemberNode->m_eType == AST::Type::AST_MEMBER_CLASS_DECL)
				{
					MemberClassDecl* pMemberClass = (MemberClassDecl*)(pMemberNode);
					if (pMemberClass->m_pClassDecl != 0)
					{
						const char* sName = pMemberClass->m_pClassDecl->m_pNameToken->GetString();
						InternalString* sTemp = new InternalString("");
						pMemberClass->m_pClassDecl->AppendFullyQualifiedName(AST::Language::NLL, sTemp);
						AddSymbolToScope(pScope, sName, Symbol::Kind::CLASS, pMemberNode, sTemp->GetExternalString());
						if (sTemp) delete sTemp;
					}
				}
				else
#line 169 "/home/cliffya/git/Lang/Source/Core/Semantic/Resolver.nll"
					if (pMemberNode->m_eType == AST::Type::AST_MEMBER_ENUM_DECL)
					{
						MemberEnumDecl* pMemberEnum = (MemberEnumDecl*)(pMemberNode);
						if (pMemberEnum->m_pEnumDecl != 0)
							AddSymbolToScope(pScope, pMemberEnum->m_pEnumDecl->m_pNameToken->GetString(), Symbol::Kind::ENUM, pMemberNode, 0);
					}
					else
#line 175 "/home/cliffya/git/Lang/Source/Core/Semantic/Resolver.nll"
						if (pMemberNode->m_eType == AST::Type::DELEGATE_DECL)
						{
							DelegateDecl* pDelegateDecl = (DelegateDecl*)(pMemberNode);
							if (pDelegateDecl->m_pFunctionDecl != 0 && pDelegateDecl->m_pFunctionDecl->m_pNameToken != 0)
								AddSymbolToScope(pScope, pDelegateDecl->m_pFunctionDecl->m_pNameToken->GetString(), Symbol::Kind::DELEGATE, pMemberNode, 0);
						}
	}

#line 184 "/home/cliffya/git/Lang/Source/Core/Semantic/Resolver.nll"
	void Resolver::BuildForRoot(AST* pRoot)
	{
		if (pRoot == 0)
			return;
#line 190 "/home/cliffya/git/Lang/Source/Core/Semantic/Resolver.nll"
		pRoot->m_pSymbolScope = m_pGlobalScope;
		BuildForNode(pRoot, m_pGlobalScope);
	}

	void Resolver::BuildForNode(AST* pNode, SymbolScope* pScope)
	{
		if (pNode == 0 || pScope == 0)
			return;
#line 200 "/home/cliffya/git/Lang/Source/Core/Semantic/Resolver.nll"
		SymbolScope* pCurrentScope = pScope;
#line 202 "/home/cliffya/git/Lang/Source/Core/Semantic/Resolver.nll"
		switch (pNode->m_eType)
		{
			case AST::Type::NAMESPACE_DECL:
			{
				NamespaceDecl* pNamespaceDecl = (NamespaceDecl*)(pNode);
				const char* sName = pNamespaceDecl->m_pNameToken->GetString();
#line 213 "/home/cliffya/git/Lang/Source/Core/Semantic/Resolver.nll"
				SymbolScope* pNamespaceScope = pScope->FindNamespaceScope(sName);
				if (pNamespaceScope != 0)
				{
					pNode->m_pSymbolScope = pNamespaceScope;
					pCurrentScope = pNamespaceScope;
					break;
				}
#line 222 "/home/cliffya/git/Lang/Source/Core/Semantic/Resolver.nll"
				const char* sQual = sName;
				if (pNamespaceDecl->m_pNamespaceNode != 0)
				{
					InternalString* sTemp = new InternalString("");
					pNamespaceDecl->m_pNamespaceNode->AppendFullyQualifiedName(AST::Language::NLL, sTemp);
					sQual = sTemp->GetExternalString();
					if (sTemp) delete sTemp;
				}
#line 229 "/home/cliffya/git/Lang/Source/Core/Semantic/Resolver.nll"
				AddSymbolToScope(pScope, sName, Symbol::Kind::NAMESPACE, pNode, sQual);
#line 231 "/home/cliffya/git/Lang/Source/Core/Semantic/Resolver.nll"
				pNamespaceScope = CreateChildScope(pNode, pScope, SymbolScope::Kind::NAMESPACE);
				pCurrentScope = pNamespaceScope;
#line 236 "/home/cliffya/git/Lang/Source/Core/Semantic/Resolver.nll"
				m_pBuildTempSymbolVector->Clear();
				pScope->FindInThisScope(sName, m_pBuildTempSymbolVector);
				if (m_pBuildTempSymbolVector->GetSize() > 0)
				{
					Symbol* pLast = m_pBuildTempSymbolVector->Get(m_pBuildTempSymbolVector->GetSize() - 1);
					pLast->m_pScope = pNamespaceScope;
				}
				break;
			}

			case AST::Type::AST_CLASS_DECL:
			{
#line 247 "/home/cliffya/git/Lang/Source/Core/Semantic/Resolver.nll"
				ClassDecl* pClassDecl = (ClassDecl*)(pNode);
#line 251 "/home/cliffya/git/Lang/Source/Core/Semantic/Resolver.nll"
				bool bIsInnerOfMemberClass = (pClassDecl->m_pParent != 0 && pClassDecl->m_pParent->m_eType == AST::Type::AST_MEMBER_CLASS_DECL);
#line 253 "/home/cliffya/git/Lang/Source/Core/Semantic/Resolver.nll"
				if (!bIsInnerOfMemberClass)
				{
					const char* sName = pClassDecl->m_pNameToken->GetString();
					InternalString* sTemp = new InternalString("");
					pClassDecl->AppendFullyQualifiedName(AST::Language::NLL, sTemp);
					AddSymbolToScope(pScope, sName, Symbol::Kind::CLASS, pNode, sTemp->GetExternalString());
					if (sTemp) delete sTemp;
				}
				pCurrentScope = CreateChildScope(pNode, pScope, SymbolScope::Kind::CLASS);
				SymbolScope* pClassScope = pCurrentScope;
#line 264 "/home/cliffya/git/Lang/Source/Core/Semantic/Resolver.nll"
				AddGenericParamsToScope(pClassDecl, pClassScope);
				break;
			}

			case AST::Type::AST_ENUM_DECL:
			{
#line 269 "/home/cliffya/git/Lang/Source/Core/Semantic/Resolver.nll"
				EnumDecl* pEnumDecl = (EnumDecl*)(pNode);
#line 273 "/home/cliffya/git/Lang/Source/Core/Semantic/Resolver.nll"
				if (pEnumDecl->m_pParent != 0 && pEnumDecl->m_pParent->m_eType == AST::Type::AST_MEMBER_ENUM_DECL)
#line 275 "/home/cliffya/git/Lang/Source/Core/Semantic/Resolver.nll"
					break;
				AddSymbolToScope(pScope, pEnumDecl->m_pNameToken->GetString(), Symbol::Kind::ENUM, pNode, 0);
				break;
			}

			case AST::Type::AST_GENERIC_TYPE_DECL:
			{
#line 285 "/home/cliffya/git/Lang/Source/Core/Semantic/Resolver.nll"
				GenericTypeDecl* pGenericTypeDecl = (GenericTypeDecl*)(pNode);
				AddSymbolToScope(pScope, pGenericTypeDecl->m_pFirstToken->GetString(), Symbol::Kind::GENERIC_PARAM, pNode, 0);
				break;
			}

			case AST::Type::AST_FUNCTION_DECL:
			{
#line 291 "/home/cliffya/git/Lang/Source/Core/Semantic/Resolver.nll"
				FunctionDecl* pFunctionDecl = (FunctionDecl*)(pNode);
#line 295 "/home/cliffya/git/Lang/Source/Core/Semantic/Resolver.nll"
				if (pFunctionDecl->m_pParent != 0 && (pFunctionDecl->m_pParent->m_eType == AST::Type::DELEGATE_DECL || pFunctionDecl->m_pParent->m_eType == AST::Type::AST_TOR_DECL))
#line 298 "/home/cliffya/git/Lang/Source/Core/Semantic/Resolver.nll"
					break;
#line 304 "/home/cliffya/git/Lang/Source/Core/Semantic/Resolver.nll"
				bool bIsInnerOfMember = (pFunctionDecl->m_pParent != 0 && pFunctionDecl->m_pParent->m_eType == AST::Type::AST_MEMBER_FUNCTION_DECL);
#line 306 "/home/cliffya/git/Lang/Source/Core/Semantic/Resolver.nll"
				if (!bIsInnerOfMember)
					AddSymbolToScope(pScope, pFunctionDecl->m_pNameToken->GetString(), Symbol::Kind::FUNCTION, pNode, 0);
#line 309 "/home/cliffya/git/Lang/Source/Core/Semantic/Resolver.nll"
				pCurrentScope = CreateChildScope(pNode, pScope, SymbolScope::Kind::FUNCTION);
				break;
			}

			case AST::Type::AST_VAR_DECL:
			{
#line 314 "/home/cliffya/git/Lang/Source/Core/Semantic/Resolver.nll"
				VarDecl* pVarDecl = (VarDecl*)(pNode);
#line 320 "/home/cliffya/git/Lang/Source/Core/Semantic/Resolver.nll"
				if (pVarDecl->m_pParent != 0 && pVarDecl->m_pParent->m_eType == AST::Type::AST_MEMBER_VAR_DECL)
#line 322 "/home/cliffya/git/Lang/Source/Core/Semantic/Resolver.nll"
					break;
#line 324 "/home/cliffya/git/Lang/Source/Core/Semantic/Resolver.nll"
				AddSymbolToScope(pScope, pVarDecl->m_pNameToken->GetString(), Symbol::Kind::VAR, pNode, 0);
				break;
			}

			case AST::Type::DELEGATE_DECL:
			{
#line 329 "/home/cliffya/git/Lang/Source/Core/Semantic/Resolver.nll"
				DelegateDecl* pDelegate = (DelegateDecl*)(pNode);
				if (pDelegate->m_pFunctionDecl != 0)
					AddSymbolToScope(pScope, pDelegate->m_pFunctionDecl->m_pNameToken->GetString(), Symbol::Kind::DELEGATE, pNode, 0);
				break;
			}

			case AST::Type::AST_MEMBER_FUNCTION_DECL:
			{
#line 336 "/home/cliffya/git/Lang/Source/Core/Semantic/Resolver.nll"
				AddMemberSymbolToScope(pNode, pCurrentScope);
				break;
			}

			case AST::Type::AST_MEMBER_VAR_DECL:
			{
#line 341 "/home/cliffya/git/Lang/Source/Core/Semantic/Resolver.nll"
				AddMemberSymbolToScope(pNode, pCurrentScope);
				break;
			}

			case AST::Type::AST_MEMBER_CLASS_DECL:
			{
#line 346 "/home/cliffya/git/Lang/Source/Core/Semantic/Resolver.nll"
				MemberClassDecl* pMemberClass = (MemberClassDecl*)(pNode);
				if (pMemberClass->m_pClassDecl != 0)
				{
					AddMemberSymbolToScope(pNode, pCurrentScope);
					pCurrentScope = CreateChildScope(pNode, pScope, SymbolScope::Kind::CLASS);
				}
				break;
			}

			case AST::Type::AST_MEMBER_ENUM_DECL:
			{
#line 356 "/home/cliffya/git/Lang/Source/Core/Semantic/Resolver.nll"
				AddMemberSymbolToScope(pNode, pCurrentScope);
				break;
			}

			case AST::Type::ENUM_DECL_VALUE:
			{
#line 361 "/home/cliffya/git/Lang/Source/Core/Semantic/Resolver.nll"
				EnumDeclValue* pEnumValue = (EnumDeclValue*)(pNode);
				AddSymbolToScope(pScope, pEnumValue->m_pFirstToken->GetString(), Symbol::Kind::ENUM_VALUE, pNode, 0);
				break;
			}

			case AST::Type::AST_SCOPE:
			{
#line 367 "/home/cliffya/git/Lang/Source/Core/Semantic/Resolver.nll"
				pCurrentScope = CreateChildScope(pNode, pScope, SymbolScope::Kind::BLOCK);
				break;
			}

			case AST::Type::AST_FOR_STMT:
			{
				pCurrentScope = CreateChildScope(pNode, pScope, SymbolScope::Kind::BLOCK);
				break;
			}

			case AST::Type::AST_TOR_DECL:
			{
				pCurrentScope = CreateChildScope(pNode, pScope, SymbolScope::Kind::FUNCTION);
				break;
			}

		}
#line 385 "/home/cliffya/git/Lang/Source/Core/Semantic/Resolver.nll"
		AST* pChild = pNode->m_pFirstChild;
		while (pChild != 0)
		{
			AST* pNext = pChild->m_pNextSibling;
			BuildForNode(pChild, pCurrentScope);
			pChild = pNext;
		}
	}

#line 396 "/home/cliffya/git/Lang/Source/Core/Semantic/Resolver.nll"
	void Resolver::ResolveInScopeChainNoBaseClasses(const char* sName, SymbolScope* pStartScope, Vector<Symbol*>* pOut)
	{
		Assert::Plz(pOut != 0);
		pOut->Clear();
		SymbolScope* pScope = pStartScope;
		while (pScope != 0)
		{
			pScope->FindInThisScope(sName, pOut);
			if (pOut->GetSize() > 0)
				return;
			pScope = pScope->m_pParent;
		}
	}

#line 413 "/home/cliffya/git/Lang/Source/Core/Semantic/Resolver.nll"
	void Resolver::ResolveInScopeChain(const char* sName, SymbolScope* pStartScope, Vector<Symbol*>* pOut)
	{
		Assert::Plz(pOut != 0);
#line 417 "/home/cliffya/git/Lang/Source/Core/Semantic/Resolver.nll"
		pOut->Clear();
#line 419 "/home/cliffya/git/Lang/Source/Core/Semantic/Resolver.nll"
		SymbolScope* pScope = pStartScope;
		while (pScope != 0)
		{
			pScope->FindInThisScope(sName, pOut);
			if (pOut->GetSize() > 0)
				return;
#line 429 "/home/cliffya/git/Lang/Source/Core/Semantic/Resolver.nll"
			if (pScope->m_eKind == SymbolScope::Kind::CLASS)
			{
				ClassDecl* pClass = GetClassDeclFromOwnerAST(pScope->m_pOwnerAST);
				if (pClass != 0)
				{
					ClassDecl* pBase = pClass->GetBaseClassDeclForScopeLookup(this);
					while (pBase != 0)
					{
						if (pBase->m_pSymbolScope != 0)
						{
							pBase->m_pSymbolScope->FindInThisScope(sName, pOut);
							if (pOut->GetSize() > 0)
								return;
						}
						pBase = pBase->GetBaseClassDeclForScopeLookup(this);
					}
				}
			}
#line 448 "/home/cliffya/git/Lang/Source/Core/Semantic/Resolver.nll"
			pScope = pScope->m_pParent;
		}
	}

#line 453 "/home/cliffya/git/Lang/Source/Core/Semantic/Resolver.nll"
	void Resolver::ResolveFromNode(AST* pNode, const char* sName, Vector<Symbol*>* pOut)
	{
		SymbolScope* pScope = GetEnclosingScope(pNode);
		ResolveInScopeChain(sName, pScope, pOut);
	}

#line 4 "/home/cliffya/git/Lang/Source/Core/Semantic/Resolver.nll"
	Resolver::~Resolver()
	{
		if (m_pGlobalScope) delete m_pGlobalScope;
		if (m_pScopeVector) delete m_pScopeVector;
		if (m_pBuildTempSymbolVector) delete m_pBuildTempSymbolVector;
	}

}

