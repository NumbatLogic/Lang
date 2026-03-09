#include "Resolver.hpp"
#include "SymbolScope.hpp"
#include "../../../../LangShared/Transpiled/Vector/OwnedVector.hpp"
#include "Symbol.hpp"
#include "../../../../LangShared/Vector/CPP/Vector.hpp"
#include "../AST/AST.hpp"
#include "../AST/MemberClassDecl.hpp"
#include "../../../../LangShared/ExternalString/CPP/ExternalString.hpp"
#include "../AST/ClassDecl.hpp"
#include "../AST/GenericTypeDecl.hpp"
#include "../Token.hpp"
#include "../AST/MemberVarDecl.hpp"
#include "../AST/VarDecl.hpp"
#include "../AST/MemberFunctionDecl.hpp"
#include "../AST/FunctionDecl.hpp"
#include "../../../../LangShared/InternalString/CPP/InternalString.hpp"
#include "../AST/MemberEnumDecl.hpp"
#include "../AST/EnumDecl.hpp"
#include "../AST/DelegateDecl.hpp"
#include "../AST/NamespaceDecl.hpp"
#include "../NamespaceNode.hpp"
#include "../AST/EnumDeclValue.hpp"
#include "../../../../LangShared/Assert/CPP/Assert.hpp"

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
#line 1 "../../../Source/Core/Semantic/Resolver.nll"
namespace NumbatLogic
{
#line 5 "../../../Source/Core/Semantic/Resolver.nll"
#line 17 "../../../Source/Core/Semantic/Resolver.nll"
	Resolver::Resolver()
	{
		m_pGlobalScope = 0;
		m_pScopeVector = 0;
		m_pBuildTempSymbolVector = 0;
#line 19 "../../../Source/Core/Semantic/Resolver.nll"
		m_pGlobalScope = new SymbolScope();
#line 20 "../../../Source/Core/Semantic/Resolver.nll"
		m_pGlobalScope->m_eKind = SymbolScope::Kind::GLOBAL;
#line 21 "../../../Source/Core/Semantic/Resolver.nll"
		m_pGlobalScope->m_pParent = 0;
#line 22 "../../../Source/Core/Semantic/Resolver.nll"
		m_pGlobalScope->m_pOwnerAST = 0;
#line 24 "../../../Source/Core/Semantic/Resolver.nll"
		m_pScopeVector = new OwnedVector<SymbolScope*>();
#line 25 "../../../Source/Core/Semantic/Resolver.nll"
		m_pBuildTempSymbolVector = new Vector<Symbol*>();
	}

#line 28 "../../../Source/Core/Semantic/Resolver.nll"
	ClassDecl* Resolver::GetClassDeclFromOwnerAST(AST* pOwner)
	{
#line 30 "../../../Source/Core/Semantic/Resolver.nll"
		if (pOwner == 0)
#line 31 "../../../Source/Core/Semantic/Resolver.nll"
			return 0;
#line 32 "../../../Source/Core/Semantic/Resolver.nll"
		if (pOwner->m_eType == AST::Type::AST_CLASS_DECL)
#line 33 "../../../Source/Core/Semantic/Resolver.nll"
			return (ClassDecl*)(pOwner);
#line 34 "../../../Source/Core/Semantic/Resolver.nll"
		if (pOwner->m_eType == AST::Type::AST_MEMBER_CLASS_DECL)
		{
			MemberClassDecl* pMember = (MemberClassDecl*)(pOwner);
#line 37 "../../../Source/Core/Semantic/Resolver.nll"
			return pMember->m_pClassDecl;
		}
#line 39 "../../../Source/Core/Semantic/Resolver.nll"
		return 0;
	}

#line 42 "../../../Source/Core/Semantic/Resolver.nll"
	SymbolScope* Resolver::CreateChildScope(AST* pNode, SymbolScope* pParent, SymbolScope::Kind eKind)
	{
		SymbolScope* pOwnedScope = new SymbolScope();
		NumbatLogic::SymbolScope* __1793915775 = pOwnedScope;
#line 45 "../../../Source/Core/Semantic/Resolver.nll"
		pOwnedScope = 0;
		SymbolScope* pNewScope = m_pScopeVector->PushBack(__1793915775);
#line 46 "../../../Source/Core/Semantic/Resolver.nll"
		pNewScope->m_eKind = eKind;
#line 47 "../../../Source/Core/Semantic/Resolver.nll"
		pNewScope->m_pParent = pParent;
#line 48 "../../../Source/Core/Semantic/Resolver.nll"
		pNewScope->m_pOwnerAST = pNode;
#line 49 "../../../Source/Core/Semantic/Resolver.nll"
		pNode->m_pSymbolScope = pNewScope;
		if (pOwnedScope) delete pOwnedScope;
#line 50 "../../../Source/Core/Semantic/Resolver.nll"
		return pNewScope;
	}

#line 53 "../../../Source/Core/Semantic/Resolver.nll"
	void Resolver::AddSymbolToScope(SymbolScope* pScope, const char* sShortName, Symbol::Kind eKind, AST* pDeclAST, const char* sQualifiedName)
	{
#line 55 "../../../Source/Core/Semantic/Resolver.nll"
		if (pScope == 0 || sShortName == 0)
#line 56 "../../../Source/Core/Semantic/Resolver.nll"
			return;
		const char* sQual = (sQualifiedName != 0 && !ExternalString::Equal(sQualifiedName, "")) ? sQualifiedName : sShortName;
		Symbol* pOwnedSymbol = new Symbol();
#line 59 "../../../Source/Core/Semantic/Resolver.nll"
		pOwnedSymbol->m_eKind = eKind;
#line 60 "../../../Source/Core/Semantic/Resolver.nll"
		pOwnedSymbol->m_sShortName = sShortName;
#line 61 "../../../Source/Core/Semantic/Resolver.nll"
		pOwnedSymbol->m_sQualifiedName = sQual;
#line 62 "../../../Source/Core/Semantic/Resolver.nll"
		pOwnedSymbol->m_pDeclAST = pDeclAST;
#line 63 "../../../Source/Core/Semantic/Resolver.nll"
		pOwnedSymbol->m_pScope = 0;
		NumbatLogic::Symbol* __3172268842 = pOwnedSymbol;
#line 64 "../../../Source/Core/Semantic/Resolver.nll"
		pOwnedSymbol = 0;
#line 64 "../../../Source/Core/Semantic/Resolver.nll"
		pScope->AddSymbol(sShortName, __3172268842);
		if (pOwnedSymbol) delete pOwnedSymbol;
	}

#line 70 "../../../Source/Core/Semantic/Resolver.nll"
	SymbolScope* Resolver::GetEnclosingScope(AST* pNode)
	{
#line 72 "../../../Source/Core/Semantic/Resolver.nll"
		if (pNode == 0)
#line 73 "../../../Source/Core/Semantic/Resolver.nll"
			return 0;
		AST* pWalk = pNode;
#line 76 "../../../Source/Core/Semantic/Resolver.nll"
		while (pWalk != 0)
		{
#line 78 "../../../Source/Core/Semantic/Resolver.nll"
			if (pWalk->m_eType == AST::Type::AST_CLASS_DECL || pWalk->m_eType == AST::Type::AST_MEMBER_CLASS_DECL)
			{
#line 80 "../../../Source/Core/Semantic/Resolver.nll"
				if (pWalk->m_pSymbolScope == 0)
#line 81 "../../../Source/Core/Semantic/Resolver.nll"
					EnsureClassScope(pWalk);
			}
#line 83 "../../../Source/Core/Semantic/Resolver.nll"
			if (pWalk->m_pSymbolScope != 0)
#line 84 "../../../Source/Core/Semantic/Resolver.nll"
				return pWalk->m_pSymbolScope;
#line 85 "../../../Source/Core/Semantic/Resolver.nll"
			pWalk = pWalk->m_pParent;
		}
#line 89 "../../../Source/Core/Semantic/Resolver.nll"
		return m_pGlobalScope;
	}

#line 93 "../../../Source/Core/Semantic/Resolver.nll"
	void Resolver::EnsureClassScope(AST* pOwnerNode)
	{
#line 95 "../../../Source/Core/Semantic/Resolver.nll"
		if (pOwnerNode == 0 || pOwnerNode->m_pSymbolScope != 0)
#line 96 "../../../Source/Core/Semantic/Resolver.nll"
			return;
		ClassDecl* pClassDecl = GetClassDeclFromOwnerAST(pOwnerNode);
#line 99 "../../../Source/Core/Semantic/Resolver.nll"
		if (pClassDecl == 0)
#line 100 "../../../Source/Core/Semantic/Resolver.nll"
			return;
		SymbolScope* pEnclosing = m_pGlobalScope;
		AST* pWalk = pOwnerNode->m_pParent;
#line 105 "../../../Source/Core/Semantic/Resolver.nll"
		while (pWalk != 0)
		{
#line 107 "../../../Source/Core/Semantic/Resolver.nll"
			if (pWalk->m_eType == AST::Type::AST_CLASS_DECL || pWalk->m_eType == AST::Type::AST_MEMBER_CLASS_DECL)
			{
#line 109 "../../../Source/Core/Semantic/Resolver.nll"
				if (pWalk->m_pSymbolScope == 0)
#line 110 "../../../Source/Core/Semantic/Resolver.nll"
					EnsureClassScope(pWalk);
			}
#line 112 "../../../Source/Core/Semantic/Resolver.nll"
			if (pWalk->m_pSymbolScope != 0)
			{
#line 114 "../../../Source/Core/Semantic/Resolver.nll"
				pEnclosing = pWalk->m_pSymbolScope;
#line 115 "../../../Source/Core/Semantic/Resolver.nll"
				break;
			}
#line 117 "../../../Source/Core/Semantic/Resolver.nll"
			pWalk = pWalk->m_pParent;
		}
		SymbolScope* pClassScope = CreateChildScope(pOwnerNode, pEnclosing, SymbolScope::Kind::CLASS);
#line 121 "../../../Source/Core/Semantic/Resolver.nll"
		AddGenericParamsToScope(pClassDecl, pClassScope);
		AST* pChild = pClassDecl->m_pFirstChild;
#line 124 "../../../Source/Core/Semantic/Resolver.nll"
		while (pChild != 0)
		{
#line 126 "../../../Source/Core/Semantic/Resolver.nll"
			AddMemberSymbolToScope(pChild, pClassScope);
#line 127 "../../../Source/Core/Semantic/Resolver.nll"
			pChild = pChild->m_pNextSibling;
		}
	}

#line 131 "../../../Source/Core/Semantic/Resolver.nll"
	void Resolver::AddGenericParamsToScope(ClassDecl* pClassDecl, SymbolScope* pScope)
	{
#line 133 "../../../Source/Core/Semantic/Resolver.nll"
		if (pClassDecl == 0 || pScope == 0 || pClassDecl->m_pGenericTypeDeclVector == 0)
#line 134 "../../../Source/Core/Semantic/Resolver.nll"
			return;
#line 135 "../../../Source/Core/Semantic/Resolver.nll"
		for (int i = 0; i < pClassDecl->m_pGenericTypeDeclVector->GetSize(); i++)
		{
			GenericTypeDecl* pGenericTypeDecl = pClassDecl->m_pGenericTypeDeclVector->Get(i);
			const char* sGenericName = pGenericTypeDecl->m_pFirstToken->GetString();
#line 139 "../../../Source/Core/Semantic/Resolver.nll"
			AddSymbolToScope(pScope, sGenericName, Symbol::Kind::GENERIC_PARAM, pGenericTypeDecl, 0);
		}
	}

#line 143 "../../../Source/Core/Semantic/Resolver.nll"
	void Resolver::AddMemberSymbolToScope(AST* pMemberNode, SymbolScope* pScope)
	{
#line 145 "../../../Source/Core/Semantic/Resolver.nll"
		if (pMemberNode == 0 || pScope == 0)
#line 146 "../../../Source/Core/Semantic/Resolver.nll"
			return;
#line 147 "../../../Source/Core/Semantic/Resolver.nll"
		if (pMemberNode->m_eType == AST::Type::AST_MEMBER_VAR_DECL)
		{
			MemberVarDecl* pMemberVar = (MemberVarDecl*)(pMemberNode);
#line 150 "../../../Source/Core/Semantic/Resolver.nll"
			if (pMemberVar->m_pVarDecl != 0)
#line 151 "../../../Source/Core/Semantic/Resolver.nll"
				AddSymbolToScope(pScope, pMemberVar->m_pVarDecl->m_pNameToken->GetString(), Symbol::Kind::VAR, pMemberNode, 0);
		}
		else
#line 153 "../../../Source/Core/Semantic/Resolver.nll"
			if (pMemberNode->m_eType == AST::Type::AST_MEMBER_FUNCTION_DECL)
			{
				MemberFunctionDecl* pMemberFunc = (MemberFunctionDecl*)(pMemberNode);
#line 156 "../../../Source/Core/Semantic/Resolver.nll"
				if (pMemberFunc->m_pFunctionDecl != 0)
#line 157 "../../../Source/Core/Semantic/Resolver.nll"
					AddSymbolToScope(pScope, pMemberFunc->m_pFunctionDecl->m_pNameToken->GetString(), Symbol::Kind::METHOD, pMemberNode, 0);
			}
			else
#line 159 "../../../Source/Core/Semantic/Resolver.nll"
				if (pMemberNode->m_eType == AST::Type::AST_MEMBER_CLASS_DECL)
				{
					MemberClassDecl* pMemberClass = (MemberClassDecl*)(pMemberNode);
#line 162 "../../../Source/Core/Semantic/Resolver.nll"
					if (pMemberClass->m_pClassDecl != 0)
					{
						const char* sName = pMemberClass->m_pClassDecl->m_pNameToken->GetString();
						InternalString* sTemp = new InternalString("");
#line 166 "../../../Source/Core/Semantic/Resolver.nll"
						pMemberClass->m_pClassDecl->AppendFullyQualifiedName(sTemp);
#line 167 "../../../Source/Core/Semantic/Resolver.nll"
						AddSymbolToScope(pScope, sName, Symbol::Kind::CLASS, pMemberNode, sTemp->GetExternalString());
						if (sTemp) delete sTemp;
					}
				}
				else
#line 170 "../../../Source/Core/Semantic/Resolver.nll"
					if (pMemberNode->m_eType == AST::Type::AST_MEMBER_ENUM_DECL)
					{
						MemberEnumDecl* pMemberEnum = (MemberEnumDecl*)(pMemberNode);
#line 173 "../../../Source/Core/Semantic/Resolver.nll"
						if (pMemberEnum->m_pEnumDecl != 0)
#line 174 "../../../Source/Core/Semantic/Resolver.nll"
							AddSymbolToScope(pScope, pMemberEnum->m_pEnumDecl->m_pNameToken->GetString(), Symbol::Kind::ENUM, pMemberNode, 0);
					}
					else
#line 176 "../../../Source/Core/Semantic/Resolver.nll"
						if (pMemberNode->m_eType == AST::Type::DELEGATE_DECL)
						{
							DelegateDecl* pDelegateDecl = (DelegateDecl*)(pMemberNode);
#line 179 "../../../Source/Core/Semantic/Resolver.nll"
							if (pDelegateDecl->m_pFunctionDecl != 0 && pDelegateDecl->m_pFunctionDecl->m_pNameToken != 0)
#line 180 "../../../Source/Core/Semantic/Resolver.nll"
								AddSymbolToScope(pScope, pDelegateDecl->m_pFunctionDecl->m_pNameToken->GetString(), Symbol::Kind::DELEGATE, pMemberNode, 0);
						}
	}

#line 185 "../../../Source/Core/Semantic/Resolver.nll"
	void Resolver::BuildForRoot(AST* pRoot)
	{
#line 187 "../../../Source/Core/Semantic/Resolver.nll"
		if (pRoot == 0)
#line 188 "../../../Source/Core/Semantic/Resolver.nll"
			return;
#line 191 "../../../Source/Core/Semantic/Resolver.nll"
		pRoot->m_pSymbolScope = m_pGlobalScope;
#line 192 "../../../Source/Core/Semantic/Resolver.nll"
		BuildForNode(pRoot, m_pGlobalScope);
	}

#line 195 "../../../Source/Core/Semantic/Resolver.nll"
	void Resolver::BuildForNode(AST* pNode, SymbolScope* pScope)
	{
#line 197 "../../../Source/Core/Semantic/Resolver.nll"
		if (pNode == 0 || pScope == 0)
#line 198 "../../../Source/Core/Semantic/Resolver.nll"
			return;
		SymbolScope* pCurrentScope = pScope;
#line 203 "../../../Source/Core/Semantic/Resolver.nll"
		switch (pNode->m_eType)
		{
			case AST::Type::NAMESPACE_DECL:
			{
				NamespaceDecl* pNamespaceDecl = (NamespaceDecl*)(pNode);
				const char* sName = pNamespaceDecl->m_pNameToken->GetString();
				SymbolScope* pNamespaceScope = pScope->FindNamespaceScope(sName);
#line 215 "../../../Source/Core/Semantic/Resolver.nll"
				if (pNamespaceScope != 0)
				{
#line 217 "../../../Source/Core/Semantic/Resolver.nll"
					pNode->m_pSymbolScope = pNamespaceScope;
#line 218 "../../../Source/Core/Semantic/Resolver.nll"
					pCurrentScope = pNamespaceScope;
#line 219 "../../../Source/Core/Semantic/Resolver.nll"
					break;
				}
				const char* sQual = sName;
#line 224 "../../../Source/Core/Semantic/Resolver.nll"
				if (pNamespaceDecl->m_pNamespaceNode != 0)
				{
					InternalString* sTemp = new InternalString("");
#line 227 "../../../Source/Core/Semantic/Resolver.nll"
					pNamespaceDecl->m_pNamespaceNode->AppendFullyQualifiedName(sTemp);
#line 228 "../../../Source/Core/Semantic/Resolver.nll"
					sQual = sTemp->GetExternalString();
					if (sTemp) delete sTemp;
				}
#line 230 "../../../Source/Core/Semantic/Resolver.nll"
				AddSymbolToScope(pScope, sName, Symbol::Kind::NAMESPACE, pNode, sQual);
#line 232 "../../../Source/Core/Semantic/Resolver.nll"
				pNamespaceScope = CreateChildScope(pNode, pScope, SymbolScope::Kind::NAMESPACE);
#line 233 "../../../Source/Core/Semantic/Resolver.nll"
				pCurrentScope = pNamespaceScope;
#line 237 "../../../Source/Core/Semantic/Resolver.nll"
				m_pBuildTempSymbolVector->Clear();
#line 238 "../../../Source/Core/Semantic/Resolver.nll"
				pScope->FindInThisScope(sName, m_pBuildTempSymbolVector);
#line 239 "../../../Source/Core/Semantic/Resolver.nll"
				if (m_pBuildTempSymbolVector->GetSize() > 0)
				{
					Symbol* pLast = m_pBuildTempSymbolVector->Get(m_pBuildTempSymbolVector->GetSize() - 1);
#line 242 "../../../Source/Core/Semantic/Resolver.nll"
					pLast->m_pScope = pNamespaceScope;
				}
#line 244 "../../../Source/Core/Semantic/Resolver.nll"
				break;
			}

			case AST::Type::AST_CLASS_DECL:
			{
				ClassDecl* pClassDecl = (ClassDecl*)(pNode);
				bool bIsInnerOfMemberClass = (pClassDecl->m_pParent != 0 && pClassDecl->m_pParent->m_eType == AST::Type::AST_MEMBER_CLASS_DECL);
#line 254 "../../../Source/Core/Semantic/Resolver.nll"
				if (!bIsInnerOfMemberClass)
				{
					const char* sName = pClassDecl->m_pNameToken->GetString();
					InternalString* sTemp = new InternalString("");
#line 258 "../../../Source/Core/Semantic/Resolver.nll"
					pClassDecl->AppendFullyQualifiedName(sTemp);
#line 259 "../../../Source/Core/Semantic/Resolver.nll"
					AddSymbolToScope(pScope, sName, Symbol::Kind::CLASS, pNode, sTemp->GetExternalString());
					if (sTemp) delete sTemp;
				}
#line 262 "../../../Source/Core/Semantic/Resolver.nll"
				pCurrentScope = CreateChildScope(pNode, pScope, SymbolScope::Kind::CLASS);
				SymbolScope* pClassScope = pCurrentScope;
#line 265 "../../../Source/Core/Semantic/Resolver.nll"
				AddGenericParamsToScope(pClassDecl, pClassScope);
#line 266 "../../../Source/Core/Semantic/Resolver.nll"
				break;
			}

			case AST::Type::AST_ENUM_DECL:
			{
				EnumDecl* pEnumDecl = (EnumDecl*)(pNode);
#line 274 "../../../Source/Core/Semantic/Resolver.nll"
				if (pEnumDecl->m_pParent != 0 && pEnumDecl->m_pParent->m_eType == AST::Type::AST_MEMBER_ENUM_DECL)
#line 276 "../../../Source/Core/Semantic/Resolver.nll"
					break;
#line 277 "../../../Source/Core/Semantic/Resolver.nll"
				AddSymbolToScope(pScope, pEnumDecl->m_pNameToken->GetString(), Symbol::Kind::ENUM, pNode, 0);
#line 278 "../../../Source/Core/Semantic/Resolver.nll"
				break;
			}

			case AST::Type::AST_GENERIC_TYPE_DECL:
			{
				GenericTypeDecl* pGenericTypeDecl = (GenericTypeDecl*)(pNode);
#line 287 "../../../Source/Core/Semantic/Resolver.nll"
				AddSymbolToScope(pScope, pGenericTypeDecl->m_pFirstToken->GetString(), Symbol::Kind::GENERIC_PARAM, pNode, 0);
#line 288 "../../../Source/Core/Semantic/Resolver.nll"
				break;
			}

			case AST::Type::AST_FUNCTION_DECL:
			{
				FunctionDecl* pFunctionDecl = (FunctionDecl*)(pNode);
#line 296 "../../../Source/Core/Semantic/Resolver.nll"
				if (pFunctionDecl->m_pParent != 0 && (pFunctionDecl->m_pParent->m_eType == AST::Type::DELEGATE_DECL || pFunctionDecl->m_pParent->m_eType == AST::Type::AST_TOR_DECL))
#line 299 "../../../Source/Core/Semantic/Resolver.nll"
					break;
				bool bIsInnerOfMember = (pFunctionDecl->m_pParent != 0 && pFunctionDecl->m_pParent->m_eType == AST::Type::AST_MEMBER_FUNCTION_DECL);
#line 307 "../../../Source/Core/Semantic/Resolver.nll"
				if (!bIsInnerOfMember)
#line 308 "../../../Source/Core/Semantic/Resolver.nll"
					AddSymbolToScope(pScope, pFunctionDecl->m_pNameToken->GetString(), Symbol::Kind::FUNCTION, pNode, 0);
#line 310 "../../../Source/Core/Semantic/Resolver.nll"
				pCurrentScope = CreateChildScope(pNode, pScope, SymbolScope::Kind::FUNCTION);
#line 311 "../../../Source/Core/Semantic/Resolver.nll"
				break;
			}

			case AST::Type::AST_VAR_DECL:
			{
				VarDecl* pVarDecl = (VarDecl*)(pNode);
#line 321 "../../../Source/Core/Semantic/Resolver.nll"
				if (pVarDecl->m_pParent != 0 && pVarDecl->m_pParent->m_eType == AST::Type::AST_MEMBER_VAR_DECL)
#line 323 "../../../Source/Core/Semantic/Resolver.nll"
					break;
#line 325 "../../../Source/Core/Semantic/Resolver.nll"
				AddSymbolToScope(pScope, pVarDecl->m_pNameToken->GetString(), Symbol::Kind::VAR, pNode, 0);
#line 326 "../../../Source/Core/Semantic/Resolver.nll"
				break;
			}

			case AST::Type::DELEGATE_DECL:
			{
				DelegateDecl* pDelegate = (DelegateDecl*)(pNode);
#line 331 "../../../Source/Core/Semantic/Resolver.nll"
				if (pDelegate->m_pFunctionDecl != 0)
#line 332 "../../../Source/Core/Semantic/Resolver.nll"
					AddSymbolToScope(pScope, pDelegate->m_pFunctionDecl->m_pNameToken->GetString(), Symbol::Kind::DELEGATE, pNode, 0);
#line 333 "../../../Source/Core/Semantic/Resolver.nll"
				break;
			}

			case AST::Type::AST_MEMBER_FUNCTION_DECL:
			{
#line 337 "../../../Source/Core/Semantic/Resolver.nll"
				AddMemberSymbolToScope(pNode, pCurrentScope);
#line 338 "../../../Source/Core/Semantic/Resolver.nll"
				break;
			}

			case AST::Type::AST_MEMBER_VAR_DECL:
			{
#line 342 "../../../Source/Core/Semantic/Resolver.nll"
				AddMemberSymbolToScope(pNode, pCurrentScope);
#line 343 "../../../Source/Core/Semantic/Resolver.nll"
				break;
			}

			case AST::Type::AST_MEMBER_CLASS_DECL:
			{
				MemberClassDecl* pMemberClass = (MemberClassDecl*)(pNode);
#line 348 "../../../Source/Core/Semantic/Resolver.nll"
				if (pMemberClass->m_pClassDecl != 0)
				{
#line 350 "../../../Source/Core/Semantic/Resolver.nll"
					AddMemberSymbolToScope(pNode, pCurrentScope);
#line 351 "../../../Source/Core/Semantic/Resolver.nll"
					pCurrentScope = CreateChildScope(pNode, pScope, SymbolScope::Kind::CLASS);
				}
#line 353 "../../../Source/Core/Semantic/Resolver.nll"
				break;
			}

			case AST::Type::AST_MEMBER_ENUM_DECL:
			{
#line 357 "../../../Source/Core/Semantic/Resolver.nll"
				AddMemberSymbolToScope(pNode, pCurrentScope);
#line 358 "../../../Source/Core/Semantic/Resolver.nll"
				break;
			}

			case AST::Type::ENUM_DECL_VALUE:
			{
				EnumDeclValue* pEnumValue = (EnumDeclValue*)(pNode);
#line 363 "../../../Source/Core/Semantic/Resolver.nll"
				AddSymbolToScope(pScope, pEnumValue->m_pFirstToken->GetString(), Symbol::Kind::ENUM_VALUE, pNode, 0);
#line 364 "../../../Source/Core/Semantic/Resolver.nll"
				break;
			}

			case AST::Type::AST_SCOPE:
			{
#line 368 "../../../Source/Core/Semantic/Resolver.nll"
				pCurrentScope = CreateChildScope(pNode, pScope, SymbolScope::Kind::BLOCK);
#line 369 "../../../Source/Core/Semantic/Resolver.nll"
				break;
			}

			case AST::Type::AST_FOR_STMT:
			{
#line 374 "../../../Source/Core/Semantic/Resolver.nll"
				pCurrentScope = CreateChildScope(pNode, pScope, SymbolScope::Kind::BLOCK);
#line 375 "../../../Source/Core/Semantic/Resolver.nll"
				break;
			}

			case AST::Type::AST_TOR_DECL:
			{
#line 380 "../../../Source/Core/Semantic/Resolver.nll"
				pCurrentScope = CreateChildScope(pNode, pScope, SymbolScope::Kind::FUNCTION);
#line 381 "../../../Source/Core/Semantic/Resolver.nll"
				break;
			}

		}
		AST* pChild = pNode->m_pFirstChild;
#line 387 "../../../Source/Core/Semantic/Resolver.nll"
		while (pChild != 0)
		{
			AST* pNext = pChild->m_pNextSibling;
#line 390 "../../../Source/Core/Semantic/Resolver.nll"
			BuildForNode(pChild, pCurrentScope);
#line 391 "../../../Source/Core/Semantic/Resolver.nll"
			pChild = pNext;
		}
	}

#line 397 "../../../Source/Core/Semantic/Resolver.nll"
	void Resolver::ResolveInScopeChainNoBaseClasses(const char* sName, SymbolScope* pStartScope, Vector<Symbol*>* pOut)
	{
#line 399 "../../../Source/Core/Semantic/Resolver.nll"
		Assert::Plz(pOut != 0);
#line 400 "../../../Source/Core/Semantic/Resolver.nll"
		pOut->Clear();
		SymbolScope* pScope = pStartScope;
#line 402 "../../../Source/Core/Semantic/Resolver.nll"
		while (pScope != 0)
		{
#line 404 "../../../Source/Core/Semantic/Resolver.nll"
			pScope->FindInThisScope(sName, pOut);
#line 405 "../../../Source/Core/Semantic/Resolver.nll"
			if (pOut->GetSize() > 0)
#line 406 "../../../Source/Core/Semantic/Resolver.nll"
				return;
#line 407 "../../../Source/Core/Semantic/Resolver.nll"
			pScope = pScope->m_pParent;
		}
	}

#line 414 "../../../Source/Core/Semantic/Resolver.nll"
	void Resolver::ResolveInScopeChain(const char* sName, SymbolScope* pStartScope, Vector<Symbol*>* pOut)
	{
#line 416 "../../../Source/Core/Semantic/Resolver.nll"
		Assert::Plz(pOut != 0);
#line 418 "../../../Source/Core/Semantic/Resolver.nll"
		pOut->Clear();
		SymbolScope* pScope = pStartScope;
#line 421 "../../../Source/Core/Semantic/Resolver.nll"
		while (pScope != 0)
		{
#line 423 "../../../Source/Core/Semantic/Resolver.nll"
			pScope->FindInThisScope(sName, pOut);
#line 424 "../../../Source/Core/Semantic/Resolver.nll"
			if (pOut->GetSize() > 0)
#line 425 "../../../Source/Core/Semantic/Resolver.nll"
				return;
#line 430 "../../../Source/Core/Semantic/Resolver.nll"
			if (pScope->m_eKind == SymbolScope::Kind::CLASS)
			{
				ClassDecl* pClass = GetClassDeclFromOwnerAST(pScope->m_pOwnerAST);
#line 433 "../../../Source/Core/Semantic/Resolver.nll"
				if (pClass != 0)
				{
					ClassDecl* pBase = pClass->GetBaseClassDeclForScopeLookup(this);
#line 436 "../../../Source/Core/Semantic/Resolver.nll"
					while (pBase != 0)
					{
#line 438 "../../../Source/Core/Semantic/Resolver.nll"
						if (pBase->m_pSymbolScope != 0)
						{
#line 440 "../../../Source/Core/Semantic/Resolver.nll"
							pBase->m_pSymbolScope->FindInThisScope(sName, pOut);
#line 441 "../../../Source/Core/Semantic/Resolver.nll"
							if (pOut->GetSize() > 0)
#line 442 "../../../Source/Core/Semantic/Resolver.nll"
								return;
						}
#line 444 "../../../Source/Core/Semantic/Resolver.nll"
						pBase = pBase->GetBaseClassDeclForScopeLookup(this);
					}
				}
			}
#line 449 "../../../Source/Core/Semantic/Resolver.nll"
			pScope = pScope->m_pParent;
		}
	}

#line 454 "../../../Source/Core/Semantic/Resolver.nll"
	void Resolver::ResolveFromNode(AST* pNode, const char* sName, Vector<Symbol*>* pOut)
	{
		SymbolScope* pScope = GetEnclosingScope(pNode);
#line 457 "../../../Source/Core/Semantic/Resolver.nll"
		ResolveInScopeChain(sName, pScope, pOut);
	}

#line 5 "../../../Source/Core/Semantic/Resolver.nll"
	Resolver::~Resolver()
	{
		if (m_pGlobalScope) delete m_pGlobalScope;
		if (m_pScopeVector) delete m_pScopeVector;
		if (m_pBuildTempSymbolVector) delete m_pBuildTempSymbolVector;
	}

}

