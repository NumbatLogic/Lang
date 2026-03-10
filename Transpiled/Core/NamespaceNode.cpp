#include "NamespaceNode.hpp"
#include "../../../LangShared/Transpiled/Vector/OwnedVector.hpp"
#include "AST/NamespaceDecl.hpp"
#include "../../../LangShared/Vector/CPP/Vector.hpp"
#include "Token.hpp"
#include "../../../LangShared/InternalString/CPP/InternalString.hpp"
#include "../../../LangShared/ExternalString/CPP/ExternalString.hpp"

namespace NumbatLogic
{
	class NamespaceNode;
	template <class T>
	class OwnedVector;
	class NamespaceDecl;
	template <class T>
	class Vector;
	class Token;
	class InternalString;
	class ExternalString;
}
#line 0 "../../../Source/Core/NamespaceNode.nll"
namespace NumbatLogic
{
#line 3 "../../../Source/Core/NamespaceNode.nll"
#line 10 "../../../Source/Core/NamespaceNode.nll"
	NamespaceNode::NamespaceNode(InternalString* sName, NamespaceNode* pParent)
	{
		m_sName = 0;
		m_pParent = 0;
		m_pChildVector = 0;
		m_pNamespaceDeclVector = 0;
#line 12 "../../../Source/Core/NamespaceNode.nll"
		m_sName = sName;
#line 13 "../../../Source/Core/NamespaceNode.nll"
		m_pParent = pParent;
#line 14 "../../../Source/Core/NamespaceNode.nll"
		m_pChildVector = new OwnedVector<NamespaceNode*>();
#line 15 "../../../Source/Core/NamespaceNode.nll"
		m_pNamespaceDeclVector = new Vector<NamespaceDecl*>();
	}

#line 18 "../../../Source/Core/NamespaceNode.nll"
	NamespaceNode* NamespaceNode::GetOrCreateChild(NamespaceDecl* pNamespaceDecl)
	{
#line 20 "../../../Source/Core/NamespaceNode.nll"
		NamespaceNode* pNamespaceNode = GetChild(pNamespaceDecl->m_pNameToken->m_sValue->GetExternalString());
#line 22 "../../../Source/Core/NamespaceNode.nll"
		if (pNamespaceNode == 0)
		{
#line 24 "../../../Source/Core/NamespaceNode.nll"
			NamespaceNode* pOwnedNamespaceNode = new NamespaceNode(pNamespaceDecl->m_pNameToken->m_sValue, this);
			NumbatLogic::NamespaceNode* __1383045035 = pOwnedNamespaceNode;
#line 25 "../../../Source/Core/NamespaceNode.nll"
			pOwnedNamespaceNode = 0;
#line 25 "../../../Source/Core/NamespaceNode.nll"
			pNamespaceNode = m_pChildVector->PushBack(__1383045035);
			if (pOwnedNamespaceNode) delete pOwnedNamespaceNode;
		}
#line 28 "../../../Source/Core/NamespaceNode.nll"
		pNamespaceNode->m_pNamespaceDeclVector->PushBack(pNamespaceDecl);
#line 29 "../../../Source/Core/NamespaceNode.nll"
		pNamespaceDecl->m_pNamespaceNode = pNamespaceNode;
#line 31 "../../../Source/Core/NamespaceNode.nll"
		return pNamespaceNode;
	}

#line 34 "../../../Source/Core/NamespaceNode.nll"
	NamespaceNode* NamespaceNode::GetChild(const char* sxName)
	{
#line 36 "../../../Source/Core/NamespaceNode.nll"
		for (int i = 0; i < m_pChildVector->GetSize(); i++)
		{
#line 38 "../../../Source/Core/NamespaceNode.nll"
			NamespaceNode* pChild = m_pChildVector->Get(i);
#line 39 "../../../Source/Core/NamespaceNode.nll"
			if (ExternalString::Equal(sxName, pChild->m_sName->GetExternalString()))
#line 40 "../../../Source/Core/NamespaceNode.nll"
				return pChild;
		}
#line 42 "../../../Source/Core/NamespaceNode.nll"
		return 0;
	}

#line 45 "../../../Source/Core/NamespaceNode.nll"
	void NamespaceNode::AppendFullyQualifiedName(InternalString* sOut)
	{
#line 47 "../../../Source/Core/NamespaceNode.nll"
		if (m_pParent != 0 && m_pParent->m_sName != 0)
#line 48 "../../../Source/Core/NamespaceNode.nll"
			m_pParent->AppendFullyQualifiedName(sOut);
#line 49 "../../../Source/Core/NamespaceNode.nll"
		if (m_sName != 0)
		{
#line 51 "../../../Source/Core/NamespaceNode.nll"
			if (m_pParent != 0 && m_pParent->m_sName != 0)
#line 52 "../../../Source/Core/NamespaceNode.nll"
				sOut->Append("::");
#line 53 "../../../Source/Core/NamespaceNode.nll"
			sOut->Append(m_sName->GetExternalString());
		}
	}

#line 3 "../../../Source/Core/NamespaceNode.nll"
	NamespaceNode::~NamespaceNode()
	{
		if (m_pChildVector) delete m_pChildVector;
		if (m_pNamespaceDeclVector) delete m_pNamespaceDeclVector;
	}

}

