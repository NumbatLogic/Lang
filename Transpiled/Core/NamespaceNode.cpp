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
#line 1 "../../../Source/Core/NamespaceNode.nll"
namespace NumbatLogic
{
#line 4 "../../../Source/Core/NamespaceNode.nll"
#line 11 "../../../Source/Core/NamespaceNode.nll"
	NamespaceNode::NamespaceNode(InternalString* sName, NamespaceNode* pParent)
	{
		m_sName = 0;
		m_pParent = 0;
		m_pChildVector = 0;
		m_pNamespaceDeclVector = 0;
#line 13 "../../../Source/Core/NamespaceNode.nll"
		m_sName = sName;
#line 14 "../../../Source/Core/NamespaceNode.nll"
		m_pParent = pParent;
#line 15 "../../../Source/Core/NamespaceNode.nll"
		m_pChildVector = new OwnedVector<NamespaceNode*>();
#line 16 "../../../Source/Core/NamespaceNode.nll"
		m_pNamespaceDeclVector = new Vector<NamespaceDecl*>();
	}

#line 19 "../../../Source/Core/NamespaceNode.nll"
	NamespaceNode* NamespaceNode::GetOrCreateChild(NamespaceDecl* pNamespaceDecl)
	{
		NamespaceNode* pNamespaceNode = GetChild(pNamespaceDecl->m_pNameToken->m_sValue->GetExternalString());
#line 23 "../../../Source/Core/NamespaceNode.nll"
		if (pNamespaceNode == 0)
		{
			NamespaceNode* pOwnedNamespaceNode = new NamespaceNode(pNamespaceDecl->m_pNameToken->m_sValue, this);
			NumbatLogic::NamespaceNode* __1383045035 = pOwnedNamespaceNode;
#line 26 "../../../Source/Core/NamespaceNode.nll"
			pOwnedNamespaceNode = 0;
#line 26 "../../../Source/Core/NamespaceNode.nll"
			pNamespaceNode = m_pChildVector->PushBack(__1383045035);
			if (pOwnedNamespaceNode) delete pOwnedNamespaceNode;
		}
#line 29 "../../../Source/Core/NamespaceNode.nll"
		pNamespaceNode->m_pNamespaceDeclVector->PushBack(pNamespaceDecl);
#line 30 "../../../Source/Core/NamespaceNode.nll"
		pNamespaceDecl->m_pNamespaceNode = pNamespaceNode;
#line 32 "../../../Source/Core/NamespaceNode.nll"
		return pNamespaceNode;
	}

#line 35 "../../../Source/Core/NamespaceNode.nll"
	NamespaceNode* NamespaceNode::GetChild(const char* sxName)
	{
#line 37 "../../../Source/Core/NamespaceNode.nll"
		for (int i = 0; i < m_pChildVector->GetSize(); i++)
		{
			NamespaceNode* pChild = m_pChildVector->Get(i);
#line 40 "../../../Source/Core/NamespaceNode.nll"
			if (ExternalString::Equal(sxName, pChild->m_sName->GetExternalString()))
#line 41 "../../../Source/Core/NamespaceNode.nll"
				return pChild;
		}
#line 43 "../../../Source/Core/NamespaceNode.nll"
		return 0;
	}

#line 46 "../../../Source/Core/NamespaceNode.nll"
	void NamespaceNode::AppendFullyQualifiedName(InternalString* sOut)
	{
#line 48 "../../../Source/Core/NamespaceNode.nll"
		if (m_pParent != 0 && m_pParent->m_sName != 0)
#line 49 "../../../Source/Core/NamespaceNode.nll"
			m_pParent->AppendFullyQualifiedName(sOut);
#line 50 "../../../Source/Core/NamespaceNode.nll"
		if (m_sName != 0)
		{
#line 52 "../../../Source/Core/NamespaceNode.nll"
			if (m_pParent != 0 && m_pParent->m_sName != 0)
#line 53 "../../../Source/Core/NamespaceNode.nll"
				sOut->Append("::");
#line 54 "../../../Source/Core/NamespaceNode.nll"
			sOut->Append(m_sName->GetExternalString());
		}
	}

#line 4 "../../../Source/Core/NamespaceNode.nll"
	NamespaceNode::~NamespaceNode()
	{
		if (m_pChildVector) delete m_pChildVector;
		if (m_pNamespaceDeclVector) delete m_pNamespaceDeclVector;
	}

}

