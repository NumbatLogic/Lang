#line 1 "../../../Source/Core/NamespaceNode.nll"
namespace NumbatLogic
{
#line 3 "../../../Source/Core/NamespaceNode.nll"
	class NamespaceNode
	{
#line 5 "../../../Source/Core/NamespaceNode.nll"
		public InternalString m_sName;
#line 6 "../../../Source/Core/NamespaceNode.nll"
		public NamespaceNode m_pParent;
#line 7 "../../../Source/Core/NamespaceNode.nll"
		public OwnedVector<NamespaceNode> m_pChildVector;
#line 8 "../../../Source/Core/NamespaceNode.nll"
		public Vector<NamespaceDecl> m_pNamespaceDeclVector;
#line 10 "../../../Source/Core/NamespaceNode.nll"
		public NamespaceNode(InternalString sName, NamespaceNode pParent)
		{
#line 12 "../../../Source/Core/NamespaceNode.nll"
			m_sName = sName;
#line 13 "../../../Source/Core/NamespaceNode.nll"
			m_pParent = pParent;
#line 14 "../../../Source/Core/NamespaceNode.nll"
			m_pChildVector = new OwnedVector<NamespaceNode>();
#line 15 "../../../Source/Core/NamespaceNode.nll"
			m_pNamespaceDeclVector = new Vector<NamespaceDecl>();
		}

#line 18 "../../../Source/Core/NamespaceNode.nll"
		public NamespaceNode GetOrCreateChild(NamespaceDecl pNamespaceDecl)
		{
#line 20 "../../../Source/Core/NamespaceNode.nll"
			NamespaceNode pNamespaceNode = GetChild(pNamespaceDecl.m_pNameToken.m_sValue.GetExternalString());
#line 22 "../../../Source/Core/NamespaceNode.nll"
			if (pNamespaceNode == null)
			{
#line 24 "../../../Source/Core/NamespaceNode.nll"
				NamespaceNode pOwnedNamespaceNode = new NamespaceNode(pNamespaceDecl.m_pNameToken.m_sValue, this);
				NumbatLogic.NamespaceNode __1383045035 = pOwnedNamespaceNode;
#line 25 "../../../Source/Core/NamespaceNode.nll"
				pOwnedNamespaceNode = null;
#line 25 "../../../Source/Core/NamespaceNode.nll"
				pNamespaceNode = m_pChildVector.PushBack(__1383045035);
			}
#line 28 "../../../Source/Core/NamespaceNode.nll"
			pNamespaceNode.m_pNamespaceDeclVector.PushBack(pNamespaceDecl);
#line 29 "../../../Source/Core/NamespaceNode.nll"
			pNamespaceDecl.m_pNamespaceNode = pNamespaceNode;
#line 31 "../../../Source/Core/NamespaceNode.nll"
			return pNamespaceNode;
		}

#line 34 "../../../Source/Core/NamespaceNode.nll"
		public NamespaceNode GetChild(string sxName)
		{
#line 36 "../../../Source/Core/NamespaceNode.nll"
			for (int i = 0; i < m_pChildVector.GetSize(); i++)
			{
#line 38 "../../../Source/Core/NamespaceNode.nll"
				NamespaceNode pChild = m_pChildVector.Get(i);
#line 39 "../../../Source/Core/NamespaceNode.nll"
				if (ExternalString.Equal(sxName, pChild.m_sName.GetExternalString()))
#line 40 "../../../Source/Core/NamespaceNode.nll"
					return pChild;
			}
#line 42 "../../../Source/Core/NamespaceNode.nll"
			return null;
		}

#line 45 "../../../Source/Core/NamespaceNode.nll"
		public void AppendFullyQualifiedName(InternalString sOut)
		{
#line 47 "../../../Source/Core/NamespaceNode.nll"
			if (m_pParent != null && m_pParent.m_sName != null)
#line 48 "../../../Source/Core/NamespaceNode.nll"
				m_pParent.AppendFullyQualifiedName(sOut);
#line 49 "../../../Source/Core/NamespaceNode.nll"
			if (m_sName != null)
			{
#line 51 "../../../Source/Core/NamespaceNode.nll"
				if (m_pParent != null && m_pParent.m_sName != null)
#line 52 "../../../Source/Core/NamespaceNode.nll"
					sOut.Append("::");
#line 53 "../../../Source/Core/NamespaceNode.nll"
				sOut.Append(m_sName.GetExternalString());
			}
		}

#line 3 "../../../Source/Core/NamespaceNode.nll"
		~NamespaceNode()
		{
		}

	}
}

