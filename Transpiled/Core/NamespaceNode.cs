#line 1 "../../../Source/Core/NamespaceNode.nll"
namespace NumbatLogic
{
#line 4 "../../../Source/Core/NamespaceNode.nll"
	class NamespaceNode
	{
#line 6 "../../../Source/Core/NamespaceNode.nll"
		public InternalString m_sName;
#line 7 "../../../Source/Core/NamespaceNode.nll"
		public NamespaceNode m_pParent;
#line 8 "../../../Source/Core/NamespaceNode.nll"
		public OwnedVector<NamespaceNode> m_pChildVector;
#line 9 "../../../Source/Core/NamespaceNode.nll"
		public Vector<NamespaceDecl> m_pNamespaceDeclVector;
#line 11 "../../../Source/Core/NamespaceNode.nll"
		public NamespaceNode(InternalString sName, NamespaceNode pParent)
		{
#line 13 "../../../Source/Core/NamespaceNode.nll"
			m_sName = sName;
#line 14 "../../../Source/Core/NamespaceNode.nll"
			m_pParent = pParent;
#line 15 "../../../Source/Core/NamespaceNode.nll"
			m_pChildVector = new OwnedVector<NamespaceNode>();
#line 16 "../../../Source/Core/NamespaceNode.nll"
			m_pNamespaceDeclVector = new Vector<NamespaceDecl>();
		}

#line 19 "../../../Source/Core/NamespaceNode.nll"
		public NamespaceNode GetOrCreateChild(NamespaceDecl pNamespaceDecl)
		{
			NamespaceNode pNamespaceNode = GetChild(pNamespaceDecl.m_pNameToken.m_sValue.GetExternalString());
#line 23 "../../../Source/Core/NamespaceNode.nll"
			if (pNamespaceNode == null)
			{
				NamespaceNode pOwnedNamespaceNode = new NamespaceNode(pNamespaceDecl.m_pNameToken.m_sValue, this);
				NumbatLogic.NamespaceNode __1383045035 = pOwnedNamespaceNode;
#line 26 "../../../Source/Core/NamespaceNode.nll"
				pOwnedNamespaceNode = null;
#line 26 "../../../Source/Core/NamespaceNode.nll"
				pNamespaceNode = m_pChildVector.PushBack(__1383045035);
			}
#line 29 "../../../Source/Core/NamespaceNode.nll"
			pNamespaceNode.m_pNamespaceDeclVector.PushBack(pNamespaceDecl);
#line 30 "../../../Source/Core/NamespaceNode.nll"
			pNamespaceDecl.m_pNamespaceNode = pNamespaceNode;
#line 32 "../../../Source/Core/NamespaceNode.nll"
			return pNamespaceNode;
		}

#line 35 "../../../Source/Core/NamespaceNode.nll"
		public NamespaceNode GetChild(string sxName)
		{
#line 37 "../../../Source/Core/NamespaceNode.nll"
			for (int i = 0; i < m_pChildVector.GetSize(); i++)
			{
				NamespaceNode pChild = m_pChildVector.Get(i);
#line 40 "../../../Source/Core/NamespaceNode.nll"
				if (ExternalString.Equal(sxName, pChild.m_sName.GetExternalString()))
#line 41 "../../../Source/Core/NamespaceNode.nll"
					return pChild;
			}
#line 43 "../../../Source/Core/NamespaceNode.nll"
			return null;
		}

#line 46 "../../../Source/Core/NamespaceNode.nll"
		public void AppendFullyQualifiedName(InternalString sOut)
		{
#line 48 "../../../Source/Core/NamespaceNode.nll"
			if (m_pParent != null && m_pParent.m_sName != null)
#line 49 "../../../Source/Core/NamespaceNode.nll"
				m_pParent.AppendFullyQualifiedName(sOut);
#line 50 "../../../Source/Core/NamespaceNode.nll"
			if (m_sName != null)
			{
#line 52 "../../../Source/Core/NamespaceNode.nll"
				if (m_pParent != null && m_pParent.m_sName != null)
#line 53 "../../../Source/Core/NamespaceNode.nll"
					sOut.Append("::");
#line 54 "../../../Source/Core/NamespaceNode.nll"
				sOut.Append(m_sName.GetExternalString());
			}
		}

#line 4 "../../../Source/Core/NamespaceNode.nll"
		~NamespaceNode()
		{
		}

	}
}

