namespace NumbatLogic
{
	class VarDeclDescope : AST
	{
		public Vector<VarDecl> m_pVarDeclVector;
		public VarDeclDescope()
		{
			m_eType = AST.Type.AST_VAR_DECL_DESCOPE;
			m_pVarDeclVector = new Vector<VarDecl>();
		}

		public override void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, InternalString sOut)
		{
			if (eLanguage == AST.Language.CPP)
			{
				for (int i = 0; i < m_pVarDeclVector.GetSize(); i++)
				{
					VarDecl pVarDecl = m_pVarDeclVector.Get(i);
					string sxName = pVarDecl.m_pNameToken.GetString();
					Util.Pad(nDepth, sOut);
					if (pVarDecl.m_pArraySize != null)
					{
						sOut.Append("for (int _x = 0; _x < ");
						pVarDecl.m_pArraySize.Stringify(eLanguage, eOutputFile, 0, sOut);
						sOut.Append("; _x++) if (");
						sOut.Append(sxName);
						sOut.Append("[_x]) delete ");
						sOut.Append(sxName);
						sOut.Append("[_x];\n");
					}
					else
					{
						sOut.Append("if (");
						sOut.Append(sxName);
						sOut.Append(") delete ");
						sOut.Append(sxName);
						sOut.Append(";\n");
					}
				}
			}
		}

		~VarDeclDescope()
		{
		}

	}
}

