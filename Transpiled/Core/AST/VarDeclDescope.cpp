#include "VarDeclDescope.hpp"
#include "AST.hpp"
#include "../../../../LangShared/Vector/CPP/Vector.hpp"
#include "VarDecl.hpp"
#include "../Token.hpp"
#include "../Util.hpp"
#include "../../../../LangShared/InternalString/CPP/InternalString.hpp"

namespace NumbatLogic
{
	class VarDeclDescope;
	class AST;
	template <class T>
	class Vector;
	class VarDecl;
	class Token;
	class Util;
	class InternalString;
}
namespace NumbatLogic
{
	VarDeclDescope::VarDeclDescope()
	{
		m_pVarDeclVector = 0;
		m_eType = AST::Type::AST_VAR_DECL_DESCOPE;
		m_pVarDeclVector = new Vector<VarDecl*>();
	}

	void VarDeclDescope::Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, InternalString* sOut)
	{
		if (eLanguage == AST::Language::CPP)
		{
			for (int i = 0; i < m_pVarDeclVector->GetSize(); i++)
			{
				VarDecl* pVarDecl = m_pVarDeclVector->Get(i);
				const char* sxName = pVarDecl->m_pNameToken->GetString();
				Util::Pad(nDepth, sOut);
				if (pVarDecl->m_pArraySize != 0)
				{
					sOut->Append("for (int _x = 0; _x < ");
					pVarDecl->m_pArraySize->Stringify(eLanguage, eOutputFile, 0, sOut);
					sOut->Append("; _x++) if (");
					sOut->Append(sxName);
					sOut->Append("[_x]) delete ");
					sOut->Append(sxName);
					sOut->Append("[_x];\n");
				}
				else
				{
					sOut->Append("if (");
					sOut->Append(sxName);
					sOut->Append(") delete ");
					sOut->Append(sxName);
					sOut->Append(";\n");
				}
			}
		}
	}

	VarDeclDescope::~VarDeclDescope()
	{
		if (m_pVarDeclVector) delete m_pVarDeclVector;
	}

}

