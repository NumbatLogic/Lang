#include "VarDeclDescope.hpp"
#include "AST.hpp"
#include "VarDecl.hpp"
#include "../../../../LangShared/Vector/CPP/Vector.hpp"
#include "../Token.hpp"
#include "../Util.hpp"
#include "../../../../LangShared/InternalString/CPP/InternalString.hpp"

namespace NumbatLogic
{
	class VarDeclDescope;
	class AST;
	class VarDecl;
	template <class T>
	class Vector;
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
			for (int j = 0; j < m_pVarDeclVector->GetSize(); j++)
			{
				VarDecl* pVarDecl = m_pVarDeclVector->Get(j);
				const char* sxName = pVarDecl->m_pNameToken->GetString();
				if (pVarDecl->m_pArraySizeVector != 0)
				{
					int nArraySizeSize = pVarDecl->m_pArraySizeVector->GetSize();
					for (int i = 0; i < nArraySizeSize; i++)
					{
						AST* pArraySize = pVarDecl->m_pArraySizeVector->Get(i);
						Util::Pad(nDepth + i, sOut);
						sOut->Append("for (int _x");
						sOut->AppendInt(i);
						sOut->Append(" = 0; _x");
						sOut->AppendInt(i);
						sOut->Append(" < ");
						pArraySize->Stringify(eLanguage, eOutputFile, 0, sOut);
						sOut->Append("; _x");
						sOut->AppendInt(i);
						sOut->Append("++)\n");
					}
					Util::Pad(nDepth + nArraySizeSize, sOut);
					sOut->Append("delete ");
					sOut->Append(sxName);
					for (int i = 0; i < nArraySizeSize; i++)
					{
						sOut->Append("[_x");
						sOut->AppendInt(i);
						sOut->Append("]");
					}
					sOut->Append(";\n");
				}
				else
				{
					Util::Pad(nDepth, sOut);
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

