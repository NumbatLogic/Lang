#pragma once

#include "../../../LangShared/Transpiled/Vector/OwnedVector.hpp"
#include "NamespaceNode.hpp"
#include "../../../LangShared/Vector/CPP/Vector.hpp"
#include "AST/NamespaceDecl.hpp"

namespace NumbatLogic
{
	class InternalString;
	class NamespaceNode;
	template <class T>
	class OwnedVector;
	template <class T>
	class Vector;
	class NamespaceDecl;
}
#line 0 "../../../Source/Core/NamespaceNode.nll"
namespace NumbatLogic
{
#line 3 "../../../Source/Core/NamespaceNode.nll"
	class NamespaceNode
	{
		public: InternalString* m_sName;
		public: NamespaceNode* m_pParent;
		public: OwnedVector<NamespaceNode*>* m_pChildVector;
		public: Vector<NamespaceDecl*>* m_pNamespaceDeclVector;
#line 10 "../../../Source/Core/NamespaceNode.nll"
		public: NamespaceNode(InternalString* sName, NamespaceNode* pParent);
#line 18 "../../../Source/Core/NamespaceNode.nll"
		public: NamespaceNode* GetOrCreateChild(NamespaceDecl* pNamespaceDecl);
#line 34 "../../../Source/Core/NamespaceNode.nll"
		public: NamespaceNode* GetChild(const char* sxName);
#line 45 "../../../Source/Core/NamespaceNode.nll"
		public: void AppendFullyQualifiedName(InternalString* sOut);
#line 3 "../../../Source/Core/NamespaceNode.nll"
		public: virtual ~NamespaceNode();
	};
}

