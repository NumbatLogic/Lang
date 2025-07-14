#pragma once

#include "../LangShared/Vector/OwnedVector.hpp"
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
		public: NamespaceNode* FindByName(const char* sxName, bool bCanAscend);
		public: virtual ~NamespaceNode();
	};
}

