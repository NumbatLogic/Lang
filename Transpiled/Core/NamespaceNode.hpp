#pragma once

#include "../../../LangShared/Transpiled/Vector/OwnedVector.hpp"
#include "NamespaceNode.hpp"
#include "../../../LangShared/Source/Vector/CPP/Vector.hpp"
#include "AST/NamespaceDecl.hpp"
#include "AST/AST.hpp"

namespace NumbatLogic
{
	class InternalString;
	class NamespaceNode;
	template <class T>
	class OwnedVector;
	template <class T>
	class Vector;
	class NamespaceDecl;
	class AST;
}
#line 0 "/home/cliffya/git/Lang/Source/Core/NamespaceNode.nll"
namespace NumbatLogic
{
#line 3 "/home/cliffya/git/Lang/Source/Core/NamespaceNode.nll"
	class NamespaceNode
	{
		public: InternalString* m_sName;
		public: NamespaceNode* m_pParent;
		public: OwnedVector<NamespaceNode*>* m_pChildVector;
		public: Vector<NamespaceDecl*>* m_pNamespaceDeclVector;
#line 10 "/home/cliffya/git/Lang/Source/Core/NamespaceNode.nll"
		public: NamespaceNode(InternalString* sName, NamespaceNode* pParent);
#line 18 "/home/cliffya/git/Lang/Source/Core/NamespaceNode.nll"
		public: NamespaceNode* GetOrCreateChild(NamespaceDecl* pNamespaceDecl);
#line 34 "/home/cliffya/git/Lang/Source/Core/NamespaceNode.nll"
		public: NamespaceNode* GetChild(const char* sxName);
#line 45 "/home/cliffya/git/Lang/Source/Core/NamespaceNode.nll"
		public: void AppendFullyQualifiedName(AST::Language eLanguage, InternalString* sOut);
#line 3 "/home/cliffya/git/Lang/Source/Core/NamespaceNode.nll"
		public: virtual ~NamespaceNode();
	};
}

