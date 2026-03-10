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
#line 0 "../../../Source/Core/Semantic/Resolver.nll"
namespace NumbatLogic
{
#line 4 "../../../Source/Core/Semantic/Resolver.nll"
#line 16 "../../../Source/Core/Semantic/Resolver.nll"
	Resolver::Resolver()
	{
		m_pGlobalScope = 0;
		m_pScopeVector = 0;
		m_pBuildTempSymbolVector = 0;
#line 18 "../../../Source/Core/Semantic/Resolver.nll"
		m_pGlobalScope = new SymbolScope();
#line 19 "../../../Source/Core/Semantic/Resolver.nll"
		m_pGlobalScope->m_eKind = SymbolScope::Kind::GLOBAL;
#line 20 "../../../Source/Core/Semantic/Resolver.nll"
		m_pGlobalScope->m_pParent = 0;
#line 21 "../../../Source/Core/Semantic/Resolver.nll"
		m_pGlobalScope->m_pOwnerAST = 0;
#line 23 "../../../Source/Core/Semantic/Resolver.nll"
		m_pScopeVector = new OwnedVector<SymbolScope*>();
#line 24 "../../../Source/Core/Semantic/Resolver.nll"
		m_pBuildTempSymbolVector = new Vector<Symbol*>();
	}

#line 27 "../../../Source/Core/Semantic/Resolver.nll"
	ClassDecl* Resolver::GetClassDeclFromOwnerAST(AST* pOwner)
	{
#line 29 "../../../Source/Core/Semantic/Resolver.nll"
		if (pOwner == 0)
#line 30 "../../../Source/Core/Semantic/Resolver.nll"
			return 0;
#line 31 "../../../Source/Core/Semantic/Resolver.nll"
		if (pOwner->m_eType == AST::Type::AST_CLASS_DECL)
#line 32 "../../../Source/Core/Semantic/Resolver.nll"
			return (ClassDecl*)(pOwner);
#line 33 "../../../Source/Core/Semantic/Resolver.nll"
		if (pOwner->m_eType == AST::Type::AST_MEMBER_CLASS_DECL)
		{
#line 35 "../../../Source/Core/Semantic/Resolver.nll"
			MemberClassDecl* pMember = (MemberClassDecl*)(pOwner);
#line 36 "../../../Source/Core/Semantic/Resolver.nll"
			return pMember->m_pClassDecl;
		}
#line 38 "../../../Source/Core/Semantic/Resolver.nll"
		return 0;
	}

#line 41 "../../../Source/Core/Semantic/Resolver.nll"
	SymbolScope* Resolver::CreateChildScope(AST* pNode, SymbolScope* pParent, SymbolScope::Kind eKind)
	{
#line 43 "../../../Source/Core/Semantic/Resolver.nll"
		SymbolScope* pOwnedScope = new SymbolScope();
		NumbatLogic::SymbolScope* __1793915775 = pOwnedScope;
#line 44 "../../../Source/Core/Semantic/Resolver.nll"
		pOwnedScope = 0;
#line 44 "../../../Source/Core/Semantic/Resolver.nll"
		SymbolScope* pNewScope = m_pScopeVector->PushBack(__1793915775);
#line 45 "../../../Source/Core/Semantic/Resolver.nll"
		pNewScope->m_eKind = eKind;
#line 46 "../../../Source/Core/Semantic/Resolver.nll"
		pNewScope->m_pParent = pParent;
#line 47 "../../../Source/Core/Semantic/Resolver.nll"
		pNewScope->m_pOwnerAST = pNode;
#line 48 "../../../Source/Core/Semantic/Resolver.nll"
		pNode->m_pSymbolScope = pNewScope;
		if (pOwnedScope) delete pOwnedScope;
#line 49 "../../../Source/Core/Semantic/Resolver.nll"
		return pNewScope;
	}

#line 52 "../../../Source/Core/Semantic/Resolver.nll"
	void Resolver::AddSymbolToScope(SymbolScope* pScope, const char* sShortName, Symbol::Kind eKind, AST* pDeclAST, const char* sQualifiedName)
	{
#line 54 "../../../Source/Core/Semantic/Resolver.nll"
		if (pScope == 0 || sShortName == 0)
#line 55 "../../../Source/Core/Semantic/Resolver.nll"
			return;
#line 56 "../../../Source/Core/Semantic/Resolver.nll"
		const char* sQual = (sQualifiedName != 0 && !ExternalString::Equal(sQualifiedName, "")) ? sQualifiedName : sShortName;
#line 57 "../../../Source/Core/Semantic/Resolver.nll"
		Symbol* pOwnedSymbol = new Symbol();
#line 58 "../../../Source/Core/Semantic/Resolver.nll"
		pOwnedSymbol->m_eKind = eKind;
#line 59 "../../../Source/Core/Semantic/Resolver.nll"
		pOwnedSymbol->m_sShortName = sShortName;
#line 60 "../../../Source/Core/Semantic/Resolver.nll"
		pOwnedSymbol->m_sQualifiedName = sQual;
#line 61 "../../../Source/Core/Semantic/Resolver.nll"
		pOwnedSymbol->m_pDeclAST = pDeclAST;
#line 62 "../../../Source/Core/Semantic/Resolver.nll"
		pOwnedSymbol->m_pScope = 0;
		NumbatLogic::Symbol* __3172268842 = pOwnedSymbol;
#line 63 "../../../Source/Core/Semantic/Resolver.nll"
		pOwnedSymbol = 0;
#line 63 "../../../Source/Core/Semantic/Resolver.nll"
		pScope->AddSymbol(sShortName, __3172268842);
		if (pOwnedSymbol) delete pOwnedSymbol;
	}

#line 69 "../../../Source/Core/Semantic/Resolver.nll"
	SymbolScope* Resolver::GetEnclosingScope(AST* pNode)
	{
#line 71 "../../../Source/Core/Semantic/Resolver.nll"
		if (pNode == 0)
#line 72 "../../../Source/Core/Semantic/Resolver.nll"
			return 0;
#line 74 "../../../Source/Core/Semantic/Resolver.nll"
		AST* pWalk = pNode;
#line 75 "../../../Source/Core/Semantic/Resolver.nll"
		while (pWalk != 0)
		{
#line 77 "../../../Source/Core/Semantic/Resolver.nll"
			if (pWalk->m_eType == AST::Type::AST_CLASS_DECL || pWalk->m_eType == AST::Type::AST_MEMBER_CLASS_DECL)
			{
#line 79 "../../../Source/Core/Semantic/Resolver.nll"
				if (pWalk->m_pSymbolScope == 0)
#line 80 "../../../Source/Core/Semantic/Resolver.nll"
					EnsureClassScope(pWalk);
			}
#line 82 "../../../Source/Core/Semantic/Resolver.nll"
			if (pWalk->m_pSymbolScope != 0)
#line 83 "../../../Source/Core/Semantic/Resolver.nll"
				return pWalk->m_pSymbolScope;
#line 84 "../../../Source/Core/Semantic/Resolver.nll"
			pWalk = pWalk->m_pParent;
		}
#line 88 "../../../Source/Core/Semantic/Resolver.nll"
		return m_pGlobalScope;
	}

#line 92 "../../../Source/Core/Semantic/Resolver.nll"
	void Resolver::EnsureClassScope(AST* pOwnerNode)
	{
#line 94 "../../../Source/Core/Semantic/Resolver.nll"
		if (pOwnerNode == 0 || pOwnerNode->m_pSymbolScope != 0)
#line 95 "../../../Source/Core/Semantic/Resolver.nll"
			return;
#line 97 "../../../Source/Core/Semantic/Resolver.nll"
		ClassDecl* pClassDecl = GetClassDeclFromOwnerAST(pOwnerNode);
#line 98 "../../../Source/Core/Semantic/Resolver.nll"
		if (pClassDecl == 0)
#line 99 "../../../Source/Core/Semantic/Resolver.nll"
			return;
#line 102 "../../../Source/Core/Semantic/Resolver.nll"
		SymbolScope* pEnclosing = m_pGlobalScope;
#line 103 "../../../Source/Core/Semantic/Resolver.nll"
		AST* pWalk = pOwnerNode->m_pParent;
#line 104 "../../../Source/Core/Semantic/Resolver.nll"
		while (pWalk != 0)
		{
#line 106 "../../../Source/Core/Semantic/Resolver.nll"
			if (pWalk->m_eType == AST::Type::AST_CLASS_DECL || pWalk->m_eType == AST::Type::AST_MEMBER_CLASS_DECL)
			{
#line 108 "../../../Source/Core/Semantic/Resolver.nll"
				if (pWalk->m_pSymbolScope == 0)
#line 109 "../../../Source/Core/Semantic/Resolver.nll"
					EnsureClassScope(pWalk);
			}
#line 111 "../../../Source/Core/Semantic/Resolver.nll"
			if (pWalk->m_pSymbolScope != 0)
			{
#line 113 "../../../Source/Core/Semantic/Resolver.nll"
				pEnclosing = pWalk->m_pSymbolScope;
#line 114 "../../../Source/Core/Semantic/Resolver.nll"
				break;
			}
#line 116 "../../../Source/Core/Semantic/Resolver.nll"
			pWalk = pWalk->m_pParent;
		}
#line 119 "../../../Source/Core/Semantic/Resolver.nll"
		SymbolScope* pClassScope = CreateChildScope(pOwnerNode, pEnclosing, SymbolScope::Kind::CLASS);
#line 120 "../../../Source/Core/Semantic/Resolver.nll"
		AddGenericParamsToScope(pClassDecl, pClassScope);
#line 122 "../../../Source/Core/Semantic/Resolver.nll"
		AST* pChild = pClassDecl->m_pFirstChild;
#line 123 "../../../Source/Core/Semantic/Resolver.nll"
		while (pChild != 0)
		{
#line 125 "../../../Source/Core/Semantic/Resolver.nll"
			AddMemberSymbolToScope(pChild, pClassScope);
#line 126 "../../../Source/Core/Semantic/Resolver.nll"
			pChild = pChild->m_pNextSibling;
		}
	}

#line 130 "../../../Source/Core/Semantic/Resolver.nll"
	void Resolver::AddGenericParamsToScope(ClassDecl* pClassDecl, SymbolScope* pScope)
	{
#line 132 "../../../Source/Core/Semantic/Resolver.nll"
		if (pClassDecl == 0 || pScope == 0 || pClassDecl->m_pGenericTypeDeclVector == 0)
#line 133 "../../../Source/Core/Semantic/Resolver.nll"
			return;
#line 134 "../../../Source/Core/Semantic/Resolver.nll"
		for (int i = 0; i < pClassDecl->m_pGenericTypeDeclVector->GetSize(); i++)
		{
#line 136 "../../../Source/Core/Semantic/Resolver.nll"
			GenericTypeDecl* pGenericTypeDecl = pClassDecl->m_pGenericTypeDeclVector->Get(i);
#line 137 "../../../Source/Core/Semantic/Resolver.nll"
			const char* sGenericName = pGenericTypeDecl->m_pFirstToken->GetString();
#line 138 "../../../Source/Core/Semantic/Resolver.nll"
			AddSymbolToScope(pScope, sGenericName, Symbol::Kind::GENERIC_PARAM, pGenericTypeDecl, 0);
		}
	}

#line 142 "../../../Source/Core/Semantic/Resolver.nll"
	void Resolver::AddMemberSymbolToScope(AST* pMemberNode, SymbolScope* pScope)
	{
#line 144 "../../../Source/Core/Semantic/Resolver.nll"
		if (pMemberNode == 0 || pScope == 0)
#line 145 "../../../Source/Core/Semantic/Resolver.nll"
			return;
#line 146 "../../../Source/Core/Semantic/Resolver.nll"
		if (pMemberNode->m_eType == AST::Type::AST_MEMBER_VAR_DECL)
		{
#line 148 "../../../Source/Core/Semantic/Resolver.nll"
			MemberVarDecl* pMemberVar = (MemberVarDecl*)(pMemberNode);
#line 149 "../../../Source/Core/Semantic/Resolver.nll"
			if (pMemberVar->m_pVarDecl != 0)
#line 150 "../../../Source/Core/Semantic/Resolver.nll"
				AddSymbolToScope(pScope, pMemberVar->m_pVarDecl->m_pNameToken->GetString(), Symbol::Kind::VAR, pMemberNode, 0);
		}
		else
#line 152 "../../../Source/Core/Semantic/Resolver.nll"
			if (pMemberNode->m_eType == AST::Type::AST_MEMBER_FUNCTION_DECL)
			{
#line 154 "../../../Source/Core/Semantic/Resolver.nll"
				MemberFunctionDecl* pMemberFunc = (MemberFunctionDecl*)(pMemberNode);
#line 155 "../../../Source/Core/Semantic/Resolver.nll"
				if (pMemberFunc->m_pFunctionDecl != 0)
#line 156 "../../../Source/Core/Semantic/Resolver.nll"
					AddSymbolToScope(pScope, pMemberFunc->m_pFunctionDecl->m_pNameToken->GetString(), Symbol::Kind::METHOD, pMemberNode, 0);
			}
			else
#line 158 "../../../Source/Core/Semantic/Resolver.nll"
				if (pMemberNode->m_eType == AST::Type::AST_MEMBER_CLASS_DECL)
				{
#line 160 "../../../Source/Core/Semantic/Resolver.nll"
					MemberClassDecl* pMemberClass = (MemberClassDecl*)(pMemberNode);
#line 161 "../../../Source/Core/Semantic/Resolver.nll"
					if (pMemberClass->m_pClassDecl != 0)
					{
#line 163 "../../../Source/Core/Semantic/Resolver.nll"
						const char* sName = pMemberClass->m_pClassDecl->m_pNameToken->GetString();
#line 164 "../../../Source/Core/Semantic/Resolver.nll"
						InternalString* sTemp = new InternalString("");
#line 165 "../../../Source/Core/Semantic/Resolver.nll"
						pMemberClass->m_pClassDecl->AppendFullyQualifiedName(sTemp);
#line 166 "../../../Source/Core/Semantic/Resolver.nll"
						AddSymbolToScope(pScope, sName, Symbol::Kind::CLASS, pMemberNode, sTemp->GetExternalString());
						if (sTemp) delete sTemp;
					}
				}
				else
#line 169 "../../../Source/Core/Semantic/Resolver.nll"
					if (pMemberNode->m_eType == AST::Type::AST_MEMBER_ENUM_DECL)
					{
#line 171 "../../../Source/Core/Semantic/Resolver.nll"
						MemberEnumDecl* pMemberEnum = (MemberEnumDecl*)(pMemberNode);
#line 172 "../../../Source/Core/Semantic/Resolver.nll"
						if (pMemberEnum->m_pEnumDecl != 0)
#line 173 "../../../Source/Core/Semantic/Resolver.nll"
							AddSymbolToScope(pScope, pMemberEnum->m_pEnumDecl->m_pNameToken->GetString(), Symbol::Kind::ENUM, pMemberNode, 0);
					}
					else
#line 175 "../../../Source/Core/Semantic/Resolver.nll"
						if (pMemberNode->m_eType == AST::Type::DELEGATE_DECL)
						{
#line 177 "../../../Source/Core/Semantic/Resolver.nll"
							DelegateDecl* pDelegateDecl = (DelegateDecl*)(pMemberNode);
#line 178 "../../../Source/Core/Semantic/Resolver.nll"
							if (pDelegateDecl->m_pFunctionDecl != 0 && pDelegateDecl->m_pFunctionDecl->m_pNameToken != 0)
#line 179 "../../../Source/Core/Semantic/Resolver.nll"
								AddSymbolToScope(pScope, pDelegateDecl->m_pFunctionDecl->m_pNameToken->GetString(), Symbol::Kind::DELEGATE, pMemberNode, 0);
						}
	}

#line 184 "../../../Source/Core/Semantic/Resolver.nll"
	void Resolver::BuildForRoot(AST* pRoot)
	{
#line 186 "../../../Source/Core/Semantic/Resolver.nll"
		if (pRoot == 0)
#line 187 "../../../Source/Core/Semantic/Resolver.nll"
			return;
#line 190 "../../../Source/Core/Semantic/Resolver.nll"
		pRoot->m_pSymbolScope = m_pGlobalScope;
#line 191 "../../../Source/Core/Semantic/Resolver.nll"
		BuildForNode(pRoot, m_pGlobalScope);
	}

#line 194 "../../../Source/Core/Semantic/Resolver.nll"
	void Resolver::BuildForNode(AST* pNode, SymbolScope* pScope)
	{
#line 196 "../../../Source/Core/Semantic/Resolver.nll"
		if (pNode == 0 || pScope == 0)
#line 197 "../../../Source/Core/Semantic/Resolver.nll"
			return;
#line 200 "../../../Source/Core/Semantic/Resolver.nll"
		SymbolScope* pCurrentScope = pScope;
#line 202 "../../../Source/Core/Semantic/Resolver.nll"
		switch (pNode->m_eType)
		{
			case AST::Type::NAMESPACE_DECL:
			{
#line 206 "../../../Source/Core/Semantic/Resolver.nll"
				NamespaceDecl* pNamespaceDecl = (NamespaceDecl*)(pNode);
#line 207 "../../../Source/Core/Semantic/Resolver.nll"
				const char* sName = pNamespaceDecl->m_pNameToken->GetString();
#line 213 "../../../Source/Core/Semantic/Resolver.nll"
				SymbolScope* pNamespaceScope = pScope->FindNamespaceScope(sName);
#line 214 "../../../Source/Core/Semantic/Resolver.nll"
				if (pNamespaceScope != 0)
				{
#line 216 "../../../Source/Core/Semantic/Resolver.nll"
					pNode->m_pSymbolScope = pNamespaceScope;
#line 217 "../../../Source/Core/Semantic/Resolver.nll"
					pCurrentScope = pNamespaceScope;
#line 218 "../../../Source/Core/Semantic/Resolver.nll"
					break;
				}
#line 222 "../../../Source/Core/Semantic/Resolver.nll"
				const char* sQual = sName;
#line 223 "../../../Source/Core/Semantic/Resolver.nll"
				if (pNamespaceDecl->m_pNamespaceNode != 0)
				{
#line 225 "../../../Source/Core/Semantic/Resolver.nll"
					InternalString* sTemp = new InternalString("");
#line 226 "../../../Source/Core/Semantic/Resolver.nll"
					pNamespaceDecl->m_pNamespaceNode->AppendFullyQualifiedName(sTemp);
#line 227 "../../../Source/Core/Semantic/Resolver.nll"
					sQual = sTemp->GetExternalString();
					if (sTemp) delete sTemp;
				}
#line 229 "../../../Source/Core/Semantic/Resolver.nll"
				AddSymbolToScope(pScope, sName, Symbol::Kind::NAMESPACE, pNode, sQual);
#line 231 "../../../Source/Core/Semantic/Resolver.nll"
				pNamespaceScope = CreateChildScope(pNode, pScope, SymbolScope::Kind::NAMESPACE);
#line 232 "../../../Source/Core/Semantic/Resolver.nll"
				pCurrentScope = pNamespaceScope;
#line 236 "../../../Source/Core/Semantic/Resolver.nll"
				m_pBuildTempSymbolVector->Clear();
#line 237 "../../../Source/Core/Semantic/Resolver.nll"
				pScope->FindInThisScope(sName, m_pBuildTempSymbolVector);
#line 238 "../../../Source/Core/Semantic/Resolver.nll"
				if (m_pBuildTempSymbolVector->GetSize() > 0)
				{
#line 240 "../../../Source/Core/Semantic/Resolver.nll"
					Symbol* pLast = m_pBuildTempSymbolVector->Get(m_pBuildTempSymbolVector->GetSize() - 1);
#line 241 "../../../Source/Core/Semantic/Resolver.nll"
					pLast->m_pScope = pNamespaceScope;
				}
#line 243 "../../../Source/Core/Semantic/Resolver.nll"
				break;
			}

			case AST::Type::AST_CLASS_DECL:
			{
#line 247 "../../../Source/Core/Semantic/Resolver.nll"
				ClassDecl* pClassDecl = (ClassDecl*)(pNode);
#line 251 "../../../Source/Core/Semantic/Resolver.nll"
				bool bIsInnerOfMemberClass = (pClassDecl->m_pParent != 0 && pClassDecl->m_pParent->m_eType == AST::Type::AST_MEMBER_CLASS_DECL);
#line 253 "../../../Source/Core/Semantic/Resolver.nll"
				if (!bIsInnerOfMemberClass)
				{
#line 255 "../../../Source/Core/Semantic/Resolver.nll"
					const char* sName = pClassDecl->m_pNameToken->GetString();
#line 256 "../../../Source/Core/Semantic/Resolver.nll"
					InternalString* sTemp = new InternalString("");
#line 257 "../../../Source/Core/Semantic/Resolver.nll"
					pClassDecl->AppendFullyQualifiedName(sTemp);
#line 258 "../../../Source/Core/Semantic/Resolver.nll"
					AddSymbolToScope(pScope, sName, Symbol::Kind::CLASS, pNode, sTemp->GetExternalString());
					if (sTemp) delete sTemp;
				}
#line 261 "../../../Source/Core/Semantic/Resolver.nll"
				pCurrentScope = CreateChildScope(pNode, pScope, SymbolScope::Kind::CLASS);
#line 262 "../../../Source/Core/Semantic/Resolver.nll"
				SymbolScope* pClassScope = pCurrentScope;
#line 264 "../../../Source/Core/Semantic/Resolver.nll"
				AddGenericParamsToScope(pClassDecl, pClassScope);
#line 265 "../../../Source/Core/Semantic/Resolver.nll"
				break;
			}

			case AST::Type::AST_ENUM_DECL:
			{
#line 269 "../../../Source/Core/Semantic/Resolver.nll"
				EnumDecl* pEnumDecl = (EnumDecl*)(pNode);
#line 273 "../../../Source/Core/Semantic/Resolver.nll"
				if (pEnumDecl->m_pParent != 0 && pEnumDecl->m_pParent->m_eType == AST::Type::AST_MEMBER_ENUM_DECL)
#line 275 "../../../Source/Core/Semantic/Resolver.nll"
					break;
#line 276 "../../../Source/Core/Semantic/Resolver.nll"
				AddSymbolToScope(pScope, pEnumDecl->m_pNameToken->GetString(), Symbol::Kind::ENUM, pNode, 0);
#line 277 "../../../Source/Core/Semantic/Resolver.nll"
				break;
			}

			case AST::Type::AST_GENERIC_TYPE_DECL:
			{
#line 285 "../../../Source/Core/Semantic/Resolver.nll"
				GenericTypeDecl* pGenericTypeDecl = (GenericTypeDecl*)(pNode);
#line 286 "../../../Source/Core/Semantic/Resolver.nll"
				AddSymbolToScope(pScope, pGenericTypeDecl->m_pFirstToken->GetString(), Symbol::Kind::GENERIC_PARAM, pNode, 0);
#line 287 "../../../Source/Core/Semantic/Resolver.nll"
				break;
			}

			case AST::Type::AST_FUNCTION_DECL:
			{
#line 291 "../../../Source/Core/Semantic/Resolver.nll"
				FunctionDecl* pFunctionDecl = (FunctionDecl*)(pNode);
#line 295 "../../../Source/Core/Semantic/Resolver.nll"
				if (pFunctionDecl->m_pParent != 0 && (pFunctionDecl->m_pParent->m_eType == AST::Type::DELEGATE_DECL || pFunctionDecl->m_pParent->m_eType == AST::Type::AST_TOR_DECL))
#line 298 "../../../Source/Core/Semantic/Resolver.nll"
					break;
#line 304 "../../../Source/Core/Semantic/Resolver.nll"
				bool bIsInnerOfMember = (pFunctionDecl->m_pParent != 0 && pFunctionDecl->m_pParent->m_eType == AST::Type::AST_MEMBER_FUNCTION_DECL);
#line 306 "../../../Source/Core/Semantic/Resolver.nll"
				if (!bIsInnerOfMember)
#line 307 "../../../Source/Core/Semantic/Resolver.nll"
					AddSymbolToScope(pScope, pFunctionDecl->m_pNameToken->GetString(), Symbol::Kind::FUNCTION, pNode, 0);
#line 309 "../../../Source/Core/Semantic/Resolver.nll"
				pCurrentScope = CreateChildScope(pNode, pScope, SymbolScope::Kind::FUNCTION);
#line 310 "../../../Source/Core/Semantic/Resolver.nll"
				break;
			}

			case AST::Type::AST_VAR_DECL:
			{
#line 314 "../../../Source/Core/Semantic/Resolver.nll"
				VarDecl* pVarDecl = (VarDecl*)(pNode);
#line 320 "../../../Source/Core/Semantic/Resolver.nll"
				if (pVarDecl->m_pParent != 0 && pVarDecl->m_pParent->m_eType == AST::Type::AST_MEMBER_VAR_DECL)
#line 322 "../../../Source/Core/Semantic/Resolver.nll"
					break;
#line 324 "../../../Source/Core/Semantic/Resolver.nll"
				AddSymbolToScope(pScope, pVarDecl->m_pNameToken->GetString(), Symbol::Kind::VAR, pNode, 0);
#line 325 "../../../Source/Core/Semantic/Resolver.nll"
				break;
			}

			case AST::Type::DELEGATE_DECL:
			{
#line 329 "../../../Source/Core/Semantic/Resolver.nll"
				DelegateDecl* pDelegate = (DelegateDecl*)(pNode);
#line 330 "../../../Source/Core/Semantic/Resolver.nll"
				if (pDelegate->m_pFunctionDecl != 0)
#line 331 "../../../Source/Core/Semantic/Resolver.nll"
					AddSymbolToScope(pScope, pDelegate->m_pFunctionDecl->m_pNameToken->GetString(), Symbol::Kind::DELEGATE, pNode, 0);
#line 332 "../../../Source/Core/Semantic/Resolver.nll"
				break;
			}

			case AST::Type::AST_MEMBER_FUNCTION_DECL:
			{
#line 336 "../../../Source/Core/Semantic/Resolver.nll"
				AddMemberSymbolToScope(pNode, pCurrentScope);
#line 337 "../../../Source/Core/Semantic/Resolver.nll"
				break;
			}

			case AST::Type::AST_MEMBER_VAR_DECL:
			{
#line 341 "../../../Source/Core/Semantic/Resolver.nll"
				AddMemberSymbolToScope(pNode, pCurrentScope);
#line 342 "../../../Source/Core/Semantic/Resolver.nll"
				break;
			}

			case AST::Type::AST_MEMBER_CLASS_DECL:
			{
#line 346 "../../../Source/Core/Semantic/Resolver.nll"
				MemberClassDecl* pMemberClass = (MemberClassDecl*)(pNode);
#line 347 "../../../Source/Core/Semantic/Resolver.nll"
				if (pMemberClass->m_pClassDecl != 0)
				{
#line 349 "../../../Source/Core/Semantic/Resolver.nll"
					AddMemberSymbolToScope(pNode, pCurrentScope);
#line 350 "../../../Source/Core/Semantic/Resolver.nll"
					pCurrentScope = CreateChildScope(pNode, pScope, SymbolScope::Kind::CLASS);
				}
#line 352 "../../../Source/Core/Semantic/Resolver.nll"
				break;
			}

			case AST::Type::AST_MEMBER_ENUM_DECL:
			{
#line 356 "../../../Source/Core/Semantic/Resolver.nll"
				AddMemberSymbolToScope(pNode, pCurrentScope);
#line 357 "../../../Source/Core/Semantic/Resolver.nll"
				break;
			}

			case AST::Type::ENUM_DECL_VALUE:
			{
#line 361 "../../../Source/Core/Semantic/Resolver.nll"
				EnumDeclValue* pEnumValue = (EnumDeclValue*)(pNode);
#line 362 "../../../Source/Core/Semantic/Resolver.nll"
				AddSymbolToScope(pScope, pEnumValue->m_pFirstToken->GetString(), Symbol::Kind::ENUM_VALUE, pNode, 0);
#line 363 "../../../Source/Core/Semantic/Resolver.nll"
				break;
			}

			case AST::Type::AST_SCOPE:
			{
#line 367 "../../../Source/Core/Semantic/Resolver.nll"
				pCurrentScope = CreateChildScope(pNode, pScope, SymbolScope::Kind::BLOCK);
#line 368 "../../../Source/Core/Semantic/Resolver.nll"
				break;
			}

			case AST::Type::AST_FOR_STMT:
			{
#line 373 "../../../Source/Core/Semantic/Resolver.nll"
				pCurrentScope = CreateChildScope(pNode, pScope, SymbolScope::Kind::BLOCK);
#line 374 "../../../Source/Core/Semantic/Resolver.nll"
				break;
			}

			case AST::Type::AST_TOR_DECL:
			{
#line 379 "../../../Source/Core/Semantic/Resolver.nll"
				pCurrentScope = CreateChildScope(pNode, pScope, SymbolScope::Kind::FUNCTION);
#line 380 "../../../Source/Core/Semantic/Resolver.nll"
				break;
			}

		}
#line 385 "../../../Source/Core/Semantic/Resolver.nll"
		AST* pChild = pNode->m_pFirstChild;
#line 386 "../../../Source/Core/Semantic/Resolver.nll"
		while (pChild != 0)
		{
#line 388 "../../../Source/Core/Semantic/Resolver.nll"
			AST* pNext = pChild->m_pNextSibling;
#line 389 "../../../Source/Core/Semantic/Resolver.nll"
			BuildForNode(pChild, pCurrentScope);
#line 390 "../../../Source/Core/Semantic/Resolver.nll"
			pChild = pNext;
		}
	}

#line 396 "../../../Source/Core/Semantic/Resolver.nll"
	void Resolver::ResolveInScopeChainNoBaseClasses(const char* sName, SymbolScope* pStartScope, Vector<Symbol*>* pOut)
	{
#line 398 "../../../Source/Core/Semantic/Resolver.nll"
		Assert::Plz(pOut != 0);
#line 399 "../../../Source/Core/Semantic/Resolver.nll"
		pOut->Clear();
#line 400 "../../../Source/Core/Semantic/Resolver.nll"
		SymbolScope* pScope = pStartScope;
#line 401 "../../../Source/Core/Semantic/Resolver.nll"
		while (pScope != 0)
		{
#line 403 "../../../Source/Core/Semantic/Resolver.nll"
			pScope->FindInThisScope(sName, pOut);
#line 404 "../../../Source/Core/Semantic/Resolver.nll"
			if (pOut->GetSize() > 0)
#line 405 "../../../Source/Core/Semantic/Resolver.nll"
				return;
#line 406 "../../../Source/Core/Semantic/Resolver.nll"
			pScope = pScope->m_pParent;
		}
	}

#line 413 "../../../Source/Core/Semantic/Resolver.nll"
	void Resolver::ResolveInScopeChain(const char* sName, SymbolScope* pStartScope, Vector<Symbol*>* pOut)
	{
#line 415 "../../../Source/Core/Semantic/Resolver.nll"
		Assert::Plz(pOut != 0);
#line 417 "../../../Source/Core/Semantic/Resolver.nll"
		pOut->Clear();
#line 419 "../../../Source/Core/Semantic/Resolver.nll"
		SymbolScope* pScope = pStartScope;
#line 420 "../../../Source/Core/Semantic/Resolver.nll"
		while (pScope != 0)
		{
#line 422 "../../../Source/Core/Semantic/Resolver.nll"
			pScope->FindInThisScope(sName, pOut);
#line 423 "../../../Source/Core/Semantic/Resolver.nll"
			if (pOut->GetSize() > 0)
#line 424 "../../../Source/Core/Semantic/Resolver.nll"
				return;
#line 429 "../../../Source/Core/Semantic/Resolver.nll"
			if (pScope->m_eKind == SymbolScope::Kind::CLASS)
			{
#line 431 "../../../Source/Core/Semantic/Resolver.nll"
				ClassDecl* pClass = GetClassDeclFromOwnerAST(pScope->m_pOwnerAST);
#line 432 "../../../Source/Core/Semantic/Resolver.nll"
				if (pClass != 0)
				{
#line 434 "../../../Source/Core/Semantic/Resolver.nll"
					ClassDecl* pBase = pClass->GetBaseClassDeclForScopeLookup(this);
#line 435 "../../../Source/Core/Semantic/Resolver.nll"
					while (pBase != 0)
					{
#line 437 "../../../Source/Core/Semantic/Resolver.nll"
						if (pBase->m_pSymbolScope != 0)
						{
#line 439 "../../../Source/Core/Semantic/Resolver.nll"
							pBase->m_pSymbolScope->FindInThisScope(sName, pOut);
#line 440 "../../../Source/Core/Semantic/Resolver.nll"
							if (pOut->GetSize() > 0)
#line 441 "../../../Source/Core/Semantic/Resolver.nll"
								return;
						}
#line 443 "../../../Source/Core/Semantic/Resolver.nll"
						pBase = pBase->GetBaseClassDeclForScopeLookup(this);
					}
				}
			}
#line 448 "../../../Source/Core/Semantic/Resolver.nll"
			pScope = pScope->m_pParent;
		}
	}

#line 453 "../../../Source/Core/Semantic/Resolver.nll"
	void Resolver::ResolveFromNode(AST* pNode, const char* sName, Vector<Symbol*>* pOut)
	{
#line 455 "../../../Source/Core/Semantic/Resolver.nll"
		SymbolScope* pScope = GetEnclosingScope(pNode);
#line 456 "../../../Source/Core/Semantic/Resolver.nll"
		ResolveInScopeChain(sName, pScope, pOut);
	}

#line 4 "../../../Source/Core/Semantic/Resolver.nll"
	Resolver::~Resolver()
	{
		if (m_pGlobalScope) delete m_pGlobalScope;
		if (m_pScopeVector) delete m_pScopeVector;
		if (m_pBuildTempSymbolVector) delete m_pBuildTempSymbolVector;
	}

}

