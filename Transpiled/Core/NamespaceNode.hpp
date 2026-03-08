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
	class NamespaceNode
	{
		public: InternalString* m_sName;
		public: NamespaceNode* m_pParent;
		public: OwnedVector<NamespaceNode*>* m_pChildVector;
		public: Vector<NamespaceDecl*>* m_pNamespaceDeclVector;
		public: NamespaceNode(InternalString* sName, NamespaceNode* pParent);
		public: NamespaceNode* GetOrCreateChild(NamespaceDecl* pNamespaceDecl);
		public: NamespaceNode* GetChild(const char* sxName);
		public: void AppendFullyQualifiedName(InternalString* sOut);
		public: virtual ~NamespaceNode();
	};
}

