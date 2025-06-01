#pragma once

#include "../Shared/OwnedVector.hpp"
#include "../../Shared/CPP/Vector.hpp"

namespace NumberDuck
{
	namespace Secret
	{
		class InternalString;
		class NamespaceNode;
		class NamespaceDecl;
	}
}
namespace NumberDuck
{
	namespace Secret
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
}

