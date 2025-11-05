#include "VarDeclDescope.hpp"
#include "AST.hpp"
#include "VarDecl.hpp"
#include "../../../../LangShared/Vector/CPP/Vector.hpp"
#include "../Token.hpp"
#include "../Util.hpp"
#include "../../../../LangShared/InternalString/CPP/InternalString.hpp"
#include "TypeRef.hpp"
#include "../ValueType.hpp"
#include "ClassDecl.hpp"

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
	class ValueType;
	class TypeRef;
	class ClassDecl;
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
		for (int j = 0; j < m_pVarDeclVector->GetSize(); j++)
		{
			VarDecl* pVarDecl = m_pVarDeclVector->Get(j);
			const char* sxName = pVarDecl->m_pNameToken->GetString();
			if (pVarDecl->m_pArraySizeVector != 0)
			{
				if (eLanguage == AST::Language::CPP)
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
			}
			else
			{
				if (eLanguage == AST::Language::CPP)
				{
					Util::Pad(nDepth, sOut);
					sOut->Append("if (");
					sOut->Append(sxName);
					sOut->Append(") delete ");
					sOut->Append(sxName);
					sOut->Append(";\n");
				}
				else
					if (eLanguage == AST::Language::CS)
					{
						ValueType* pValueType = pVarDecl->m_pTypeRef->CreateValueType();
						if (pValueType != 0 && pValueType->m_eType == ValueType::Type::CLASS_DECL_VALUE)
						{
							if (pValueType->m_pClassDecl != 0 && pValueType->m_pClassDecl->m_bDisposable)
							{
								Util::Pad(nDepth, sOut);
								sOut->Append("if (");
								sOut->Append(sxName);
								sOut->Append(" != null) ");
								sOut->Append(sxName);
								sOut->Append(".Dispose();\n");
							}
						}
						if (pValueType) delete pValueType;
					}
			}
		}
	}

	VarDeclDescope::~VarDeclDescope()
	{
		if (m_pVarDeclVector) delete m_pVarDeclVector;
	}

}

