#line 1 "/home/cliffya/git/Lang/Source/Core/NamespaceNode.nll"
namespace NumbatLogic
{
	class NamespaceNode
	{
		public InternalString m_sName;
		public NamespaceNode m_pParent;
		public OwnedVector<NamespaceNode> m_pChildVector;
		public Vector<NamespaceDecl> m_pNamespaceDeclVector;
#line 10 "/home/cliffya/git/Lang/Source/Core/NamespaceNode.nll"
		public NamespaceNode(InternalString sName, NamespaceNode pParent)
		{
			m_sName = sName;
			m_pParent = pParent;
			m_pChildVector = new OwnedVector<NamespaceNode>();
			m_pNamespaceDeclVector = new Vector<NamespaceDecl>();
		}

		public NamespaceNode GetOrCreateChild(NamespaceDecl pNamespaceDecl)
		{
			NamespaceNode pNamespaceNode = GetChild(pNamespaceDecl.m_pNameToken.m_sValue.GetExternalString());
#line 22 "/home/cliffya/git/Lang/Source/Core/NamespaceNode.nll"
			if (pNamespaceNode == null)
			{
				NamespaceNode pOwnedNamespaceNode = new NamespaceNode(pNamespaceDecl.m_pNameToken.m_sValue, this);
				NumbatLogic.NamespaceNode __1383045035 = pOwnedNamespaceNode;
#line 25 "/home/cliffya/git/Lang/Source/Core/NamespaceNode.nll"
				pOwnedNamespaceNode = null;
#line 25 "/home/cliffya/git/Lang/Source/Core/NamespaceNode.nll"
				pNamespaceNode = m_pChildVector.PushBack(__1383045035);
			}
#line 28 "/home/cliffya/git/Lang/Source/Core/NamespaceNode.nll"
			pNamespaceNode.m_pNamespaceDeclVector.PushBack(pNamespaceDecl);
			pNamespaceDecl.m_pNamespaceNode = pNamespaceNode;
#line 31 "/home/cliffya/git/Lang/Source/Core/NamespaceNode.nll"
			return pNamespaceNode;
		}

		public NamespaceNode GetChild(string sxName)
		{
			for (int i = 0; i < m_pChildVector.GetSize(); i++)
			{
				NamespaceNode pChild = m_pChildVector.Get(i);
				if (ExternalString.Equal(sxName, pChild.m_sName.GetExternalString()))
					return pChild;
			}
			return null;
		}

		public void AppendFullyQualifiedName(AST.Language eLanguage, InternalString sOut)
		{
			string sxSeparator = "::";
			if (eLanguage == AST.Language.CS)
				sxSeparator = ".";
#line 51 "/home/cliffya/git/Lang/Source/Core/NamespaceNode.nll"
			if (m_pParent != null && m_pParent.m_sName != null)
				m_pParent.AppendFullyQualifiedName(eLanguage, sOut);
			if (m_sName != null)
			{
				if (m_pParent != null && m_pParent.m_sName != null)
					sOut.Append(sxSeparator);
				sOut.Append(m_sName.GetExternalString());
			}
		}

#line 3 "/home/cliffya/git/Lang/Source/Core/NamespaceNode.nll"
		~NamespaceNode()
		{
		}

	}
}

