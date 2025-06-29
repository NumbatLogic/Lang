namespace NumbatLogic
{
	class NamespaceNode
	{
		public InternalString m_sName;
		public NamespaceNode m_pParent;
		public OwnedVector<NamespaceNode> m_pChildVector;
		public Vector<NamespaceDecl> m_pNamespaceDeclVector;
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
			if (pNamespaceNode == null)
			{
				NamespaceNode pOwnedNamespaceNode = new NamespaceNode(pNamespaceDecl.m_pNameToken.m_sValue, this);
				NumbatLogic.NamespaceNode __1551009467 = pOwnedNamespaceNode;
				pOwnedNamespaceNode = null;
				pNamespaceNode = m_pChildVector.PushBack(__1551009467);
			}
			pNamespaceNode.m_pNamespaceDeclVector.PushBack(pNamespaceDecl);
			pNamespaceDecl.m_pNamespaceNode = pNamespaceNode;
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

		public NamespaceNode FindByName(string sxName, bool bCanAscend)
		{
			for (int i = 0; i < m_pChildVector.GetSize(); i++)
			{
				NamespaceNode pChild = m_pChildVector.Get(i);
				if (ExternalString.Equal(sxName, pChild.m_sName.GetExternalString()))
					return pChild;
			}
			if (bCanAscend && m_pParent != null)
				return m_pParent.FindByName(sxName, bCanAscend);
			return null;
		}

		~NamespaceNode()
		{
		}

	}
}

