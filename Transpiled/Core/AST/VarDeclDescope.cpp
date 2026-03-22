#include "VarDeclDescope.hpp"
#include "AST.hpp"
#include "VarDecl.hpp"
#include "../../../../LangShared/Source/Vector/CPP/Vector.hpp"
#include "../Token.hpp"
#include "../Util.hpp"
#include "../OutputBuilder.hpp"
#include "../../../../LangShared/Source/InternalString/CPP/InternalString.hpp"
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
#line 0 "/home/cliffya/git/Lang/Source/Core/AST/VarDeclDescope.nll"
namespace NumbatLogic
{
#line 3 "/home/cliffya/git/Lang/Source/Core/AST/VarDeclDescope.nll"
#line 7 "/home/cliffya/git/Lang/Source/Core/AST/VarDeclDescope.nll"
	VarDeclDescope::VarDeclDescope()
	{
		m_pVarDeclVector = 0;
#line 9 "/home/cliffya/git/Lang/Source/Core/AST/VarDeclDescope.nll"
		m_eType = AST::Type::AST_VAR_DECL_DESCOPE;
		m_pVarDeclVector = new Vector<VarDecl*>();
	}

	void VarDeclDescope::Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder* pOutputBuilder)
	{
		for (int j = 0; j < m_pVarDeclVector->GetSize(); j++)
		{
			VarDecl* pVarDecl = m_pVarDeclVector->Get(j);
			const char* sxName = pVarDecl->m_pNameToken->GetString();
#line 20 "/home/cliffya/git/Lang/Source/Core/AST/VarDeclDescope.nll"
			if (pVarDecl->m_pArraySizeVector != 0)
			{
				if (eLanguage == AST::Language::CPP)
				{
					int nArraySizeSize = pVarDecl->m_pArraySizeVector->GetSize();
					for (int i = 0; i < nArraySizeSize; i++)
					{
						AST* pArraySize = pVarDecl->m_pArraySizeVector->Get(i);
						Util::Pad(nDepth + i, pOutputBuilder->m_sOut);
						pOutputBuilder->m_sOut->Append("for (int _x");
						pOutputBuilder->m_sOut->AppendInt(i);
						pOutputBuilder->m_sOut->Append(" = 0; _x");
						pOutputBuilder->m_sOut->AppendInt(i);
						pOutputBuilder->m_sOut->Append(" < ");
						pArraySize->Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
						pOutputBuilder->m_sOut->Append("; _x");
						pOutputBuilder->m_sOut->AppendInt(i);
						pOutputBuilder->m_sOut->Append("++)\n");
					}
#line 40 "/home/cliffya/git/Lang/Source/Core/AST/VarDeclDescope.nll"
					Util::Pad(nDepth + nArraySizeSize, pOutputBuilder->m_sOut);
					pOutputBuilder->m_sOut->Append("delete ");
					pOutputBuilder->m_sOut->Append(sxName);
					for (int i = 0; i < nArraySizeSize; i++)
					{
						pOutputBuilder->m_sOut->Append("[_x");
						pOutputBuilder->m_sOut->AppendInt(i);
						pOutputBuilder->m_sOut->Append("]");
					}
					pOutputBuilder->m_sOut->Append(";\n");
				}
			}
			else
			{
				if (eLanguage == AST::Language::CPP)
				{
					Util::Pad(nDepth, pOutputBuilder->m_sOut);
					pOutputBuilder->m_sOut->Append("if (");
					pOutputBuilder->m_sOut->Append(sxName);
					pOutputBuilder->m_sOut->Append(") delete ");
					pOutputBuilder->m_sOut->Append(sxName);
					pOutputBuilder->m_sOut->Append(";\n");
				}
				else
#line 63 "/home/cliffya/git/Lang/Source/Core/AST/VarDeclDescope.nll"
					if (eLanguage == AST::Language::CS)
					{
						Project* pProject = GetProject();
						ValueType* pValueType = pVarDecl->m_pTypeRef->CreateValueType(pProject->m_pValidator->m_pResolver);
						if (pValueType != 0 && pValueType->m_eType == ValueType::Type::CLASS_DECL_VALUE)
						{
							if (pValueType->m_pClassDecl != 0 && pValueType->m_pClassDecl->m_bDisposable)
							{
								Util::Pad(nDepth, pOutputBuilder->m_sOut);
								pOutputBuilder->m_sOut->Append("if (");
								pOutputBuilder->m_sOut->Append(sxName);
								pOutputBuilder->m_sOut->Append(" != null) ");
								pOutputBuilder->m_sOut->Append(sxName);
								pOutputBuilder->m_sOut->Append(".Dispose();\n");
							}
						}
						if (pValueType) delete pValueType;
					}
			}
		}
	}

#line 3 "/home/cliffya/git/Lang/Source/Core/AST/VarDeclDescope.nll"
	VarDeclDescope::~VarDeclDescope()
	{
		if (m_pVarDeclVector) delete m_pVarDeclVector;
	}

}

