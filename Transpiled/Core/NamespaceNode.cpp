#include "NamespaceNode.hpp"
#include "../../../LangShared/Transpiled/Vector/OwnedVector.hpp"
#include "AST/NamespaceDecl.hpp"
#include "../../../LangShared/Vector/CPP/Vector.hpp"
#include "Token.hpp"
#include "../../../LangShared/InternalString/CPP/InternalString.hpp"
#include "../../../LangShared/ExternalString/CPP/ExternalString.hpp"
#include "AST/AST.hpp"

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
	class AST;
}
#line 0 "/home/cliffya/git/Lang/Source/Core/NamespaceNode.nll"
namespace NumbatLogic
{
#line 3 "/home/cliffya/git/Lang/Source/Core/NamespaceNode.nll"
#line 10 "/home/cliffya/git/Lang/Source/Core/NamespaceNode.nll"
	NamespaceNode::NamespaceNode(InternalString* sName, NamespaceNode* pParent)
	{
		m_sName = 0;
		m_pParent = 0;
		m_pChildVector = 0;
		m_pNamespaceDeclVector = 0;
#line 12 "/home/cliffya/git/Lang/Source/Core/NamespaceNode.nll"
		m_sName = sName;
		m_pParent = pParent;
		m_pChildVector = new OwnedVector<NamespaceNode*>();
		m_pNamespaceDeclVector = new Vector<NamespaceDecl*>();
	}

	NamespaceNode* NamespaceNode::GetOrCreateChild(NamespaceDecl* pNamespaceDecl)
	{
		NamespaceNode* pNamespaceNode = GetChild(pNamespaceDecl->m_pNameToken->m_sValue->GetExternalString());
#line 22 "/home/cliffya/git/Lang/Source/Core/NamespaceNode.nll"
		if (pNamespaceNode == 0)
		{
			NamespaceNode* pOwnedNamespaceNode = new NamespaceNode(pNamespaceDecl->m_pNameToken->m_sValue, this);
			NumbatLogic::NamespaceNode* __1383045035 = pOwnedNamespaceNode;
#line 25 "/home/cliffya/git/Lang/Source/Core/NamespaceNode.nll"
			pOwnedNamespaceNode = 0;
#line 25 "/home/cliffya/git/Lang/Source/Core/NamespaceNode.nll"
			pNamespaceNode = m_pChildVector->PushBack(__1383045035);
			if (pOwnedNamespaceNode) delete pOwnedNamespaceNode;
		}
		pNamespaceNode->m_pNamespaceDeclVector->PushBack(pNamespaceDecl);
		pNamespaceDecl->m_pNamespaceNode = pNamespaceNode;
#line 31 "/home/cliffya/git/Lang/Source/Core/NamespaceNode.nll"
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

	void NamespaceNode::AppendFullyQualifiedName(AST::Language eLanguage, InternalString* sOut)
	{
		const char* sxSeparator = "::";
		if (eLanguage == AST::Language::CS)
			sxSeparator = ".";
#line 51 "/home/cliffya/git/Lang/Source/Core/NamespaceNode.nll"
		if (m_pParent != 0 && m_pParent->m_sName != 0)
			m_pParent->AppendFullyQualifiedName(eLanguage, sOut);
		if (m_sName != 0)
		{
			if (m_pParent != 0 && m_pParent->m_sName != 0)
				sOut->Append(sxSeparator);
			sOut->Append(m_sName->GetExternalString());
		}
	}

#line 3 "/home/cliffya/git/Lang/Source/Core/NamespaceNode.nll"
	NamespaceNode::~NamespaceNode()
	{
		if (m_pChildVector) delete m_pChildVector;
		if (m_pNamespaceDeclVector) delete m_pNamespaceDeclVector;
	}

}

