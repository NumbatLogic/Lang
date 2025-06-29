#include "NamespaceNode.hpp"
#include "../LangShared/Vector/OwnedVector.hpp"
#include "../../../LangShared/Vector/CPP/Vector.hpp"
#include "AST/NamespaceDecl.hpp"
#include "Token.hpp"
#include "../../../LangShared/InternalString/CPP/InternalString.hpp"
#include "../../../LangShared/ExternalString/CPP/ExternalString.hpp"

namespace NumbatLogic
{
	class NamespaceNode;
	class NamespaceDecl;
}
namespace NumbatLogic
{
	NamespaceNode::NamespaceNode(InternalString* sName, NamespaceNode* pParent)
	{
		m_sName = 0;
		m_pParent = 0;
		m_pChildVector = 0;
		m_pNamespaceDeclVector = 0;
		m_sName = sName;
		m_pParent = pParent;
		m_pChildVector = new OwnedVector<NamespaceNode*>();
		m_pNamespaceDeclVector = new Vector<NamespaceDecl*>();
	}

	NamespaceNode* NamespaceNode::GetOrCreateChild(NamespaceDecl* pNamespaceDecl)
	{
		NamespaceNode* pNamespaceNode = GetChild(pNamespaceDecl->m_pNameToken->m_sValue->GetExternalString());
		if (pNamespaceNode == 0)
		{
			NamespaceNode* pOwnedNamespaceNode = new NamespaceNode(pNamespaceDecl->m_pNameToken->m_sValue, this);
			NumbatLogic::NamespaceNode* __1843017088 = pOwnedNamespaceNode;
			pOwnedNamespaceNode = 0;
			pNamespaceNode = m_pChildVector->PushBack(__1843017088);
			if (pOwnedNamespaceNode) delete pOwnedNamespaceNode;
		}
		pNamespaceNode->m_pNamespaceDeclVector->PushBack(pNamespaceDecl);
		pNamespaceDecl->m_pNamespaceNode = pNamespaceNode;
		return pNamespaceNode;
	}

	NamespaceNode* NamespaceNode::GetChild(const char* sxName)
	{
		for (int i = 0; i < m_pChildVector->GetSize(); i++)
		{
			NamespaceNode* pChild = m_pChildVector->Get(i);
			if (ExternalString::Equal(sxName, pChild->m_sName->GetExternalString()))
				return pChild;
		}
		return 0;
	}

	NamespaceNode* NamespaceNode::FindByName(const char* sxName, bool bCanAscend)
	{
		for (int i = 0; i < m_pChildVector->GetSize(); i++)
		{
			NamespaceNode* pChild = m_pChildVector->Get(i);
			if (ExternalString::Equal(sxName, pChild->m_sName->GetExternalString()))
				return pChild;
		}
		if (bCanAscend && m_pParent != 0)
			return m_pParent->FindByName(sxName, bCanAscend);
		return 0;
	}

	NamespaceNode::~NamespaceNode()
	{
		if (m_pChildVector) delete m_pChildVector;
		if (m_pNamespaceDeclVector) delete m_pNamespaceDeclVector;
	}

}

