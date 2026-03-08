#include "VarDeclDescope.hpp"
#include "AST.hpp"
#include "VarDecl.hpp"
#include "../../../../LangShared/Vector/CPP/Vector.hpp"
#include "../Token.hpp"
#include "../Util.hpp"
#include "../OutputBuilder.hpp"
#include "../../../../LangShared/InternalString/CPP/InternalString.hpp"
#include "TypeRef.hpp"
#include "../Project.hpp"
#include "../Validator.hpp"
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
	class OutputBuilder;
	class InternalString;
	class Project;
	class ValueType;
	class TypeRef;
	class Validator;
	class ClassDecl;
}
#line 1 "../../../Source/Core/AST/VarDeclDescope.nll"
namespace NumbatLogic
{
	VarDeclDescope::VarDeclDescope()
	{
		m_pVarDeclVector = 0;
		m_eType = AST::Type::AST_VAR_DECL_DESCOPE;
		m_pVarDeclVector = new Vector<VarDecl*>();
	}

	void VarDeclDescope::Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder* out)
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
						Util::Pad(nDepth + i, out->m_sOut);
						out->m_sOut->Append("for (int _x");
						out->m_sOut->AppendInt(i);
						out->m_sOut->Append(" = 0; _x");
						out->m_sOut->AppendInt(i);
						out->m_sOut->Append(" < ");
						pArraySize->Stringify(eLanguage, eOutputFile, 0, out);
						out->m_sOut->Append("; _x");
						out->m_sOut->AppendInt(i);
						out->m_sOut->Append("++)\n");
					}
					Util::Pad(nDepth + nArraySizeSize, out->m_sOut);
					out->m_sOut->Append("delete ");
					out->m_sOut->Append(sxName);
					for (int i = 0; i < nArraySizeSize; i++)
					{
						out->m_sOut->Append("[_x");
						out->m_sOut->AppendInt(i);
						out->m_sOut->Append("]");
					}
					out->m_sOut->Append(";\n");
				}
			}
			else
			{
				if (eLanguage == AST::Language::CPP)
				{
					Util::Pad(nDepth, out->m_sOut);
					out->m_sOut->Append("if (");
					out->m_sOut->Append(sxName);
					out->m_sOut->Append(") delete ");
					out->m_sOut->Append(sxName);
					out->m_sOut->Append(";\n");
				}
				else
					if (eLanguage == AST::Language::CS)
					{
						Project* pProject = GetProject();
						ValueType* pValueType = pVarDecl->m_pTypeRef->CreateValueType(pProject->m_pValidator->m_pResolver);
						if (pValueType != 0 && pValueType->m_eType == ValueType::Type::CLASS_DECL_VALUE)
						{
							if (pValueType->m_pClassDecl != 0 && pValueType->m_pClassDecl->m_bDisposable)
							{
								Util::Pad(nDepth, out->m_sOut);
								out->m_sOut->Append("if (");
								out->m_sOut->Append(sxName);
								out->m_sOut->Append(" != null) ");
								out->m_sOut->Append(sxName);
								out->m_sOut->Append(".Dispose();\n");
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

