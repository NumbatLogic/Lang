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
#line 1 "../../../Source/Core/NamespaceNode.nll"
namespace NumbatLogic
{
#line 4 "../../../Source/Core/NamespaceNode.nll"
	class NamespaceNode
	{
#line 6 "../../../Source/Core/NamespaceNode.nll"
		public: InternalString* m_sName;
#line 7 "../../../Source/Core/NamespaceNode.nll"
		public: NamespaceNode* m_pParent;
#line 8 "../../../Source/Core/NamespaceNode.nll"
		public: OwnedVector<NamespaceNode*>* m_pChildVector;
#line 9 "../../../Source/Core/NamespaceNode.nll"
		public: Vector<NamespaceDecl*>* m_pNamespaceDeclVector;
#line 11 "../../../Source/Core/NamespaceNode.nll"
		public: NamespaceNode(InternalString* sName, NamespaceNode* pParent);
#line 19 "../../../Source/Core/NamespaceNode.nll"
		public: NamespaceNode* GetOrCreateChild(NamespaceDecl* pNamespaceDecl);
#line 35 "../../../Source/Core/NamespaceNode.nll"
		public: NamespaceNode* GetChild(const char* sxName);
#line 46 "../../../Source/Core/NamespaceNode.nll"
		public: void AppendFullyQualifiedName(InternalString* sOut);
#line 4 "../../../Source/Core/NamespaceNode.nll"
		public: virtual ~NamespaceNode();
	};
}

