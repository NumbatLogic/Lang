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
#line 0 "../../../Source/Core/AST/VarDeclDescope.nll"
namespace NumbatLogic
{
#line 3 "../../../Source/Core/AST/VarDeclDescope.nll"
#line 7 "../../../Source/Core/AST/VarDeclDescope.nll"
	VarDeclDescope::VarDeclDescope()
	{
		m_pVarDeclVector = 0;
#line 9 "../../../Source/Core/AST/VarDeclDescope.nll"
		m_eType = AST::Type::AST_VAR_DECL_DESCOPE;
#line 10 "../../../Source/Core/AST/VarDeclDescope.nll"
		m_pVarDeclVector = new Vector<VarDecl*>();
	}

#line 13 "../../../Source/Core/AST/VarDeclDescope.nll"
	void VarDeclDescope::Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder* pOutputBuilder)
	{
#line 15 "../../../Source/Core/AST/VarDeclDescope.nll"
		for (int j = 0; j < m_pVarDeclVector->GetSize(); j++)
		{
			VarDecl* pVarDecl = m_pVarDeclVector->Get(j);
			const char* sxName = pVarDecl->m_pNameToken->GetString();
#line 20 "../../../Source/Core/AST/VarDeclDescope.nll"
			if (pVarDecl->m_pArraySizeVector != 0)
			{
#line 22 "../../../Source/Core/AST/VarDeclDescope.nll"
				if (eLanguage == AST::Language::CPP)
				{
					int nArraySizeSize = pVarDecl->m_pArraySizeVector->GetSize();
#line 25 "../../../Source/Core/AST/VarDeclDescope.nll"
					for (int i = 0; i < nArraySizeSize; i++)
					{
						AST* pArraySize = pVarDecl->m_pArraySizeVector->Get(i);
#line 28 "../../../Source/Core/AST/VarDeclDescope.nll"
						Util::Pad(nDepth + i, pOutputBuilder->m_sOut);
#line 29 "../../../Source/Core/AST/VarDeclDescope.nll"
						pOutputBuilder->m_sOut->Append("for (int _x");
#line 30 "../../../Source/Core/AST/VarDeclDescope.nll"
						pOutputBuilder->m_sOut->AppendInt(i);
#line 31 "../../../Source/Core/AST/VarDeclDescope.nll"
						pOutputBuilder->m_sOut->Append(" = 0; _x");
#line 32 "../../../Source/Core/AST/VarDeclDescope.nll"
						pOutputBuilder->m_sOut->AppendInt(i);
#line 33 "../../../Source/Core/AST/VarDeclDescope.nll"
						pOutputBuilder->m_sOut->Append(" < ");
#line 34 "../../../Source/Core/AST/VarDeclDescope.nll"
						pArraySize->Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
#line 35 "../../../Source/Core/AST/VarDeclDescope.nll"
						pOutputBuilder->m_sOut->Append("; _x");
#line 36 "../../../Source/Core/AST/VarDeclDescope.nll"
						pOutputBuilder->m_sOut->AppendInt(i);
#line 37 "../../../Source/Core/AST/VarDeclDescope.nll"
						pOutputBuilder->m_sOut->Append("++)\n");
					}
#line 40 "../../../Source/Core/AST/VarDeclDescope.nll"
					Util::Pad(nDepth + nArraySizeSize, pOutputBuilder->m_sOut);
#line 41 "../../../Source/Core/AST/VarDeclDescope.nll"
					pOutputBuilder->m_sOut->Append("delete ");
#line 42 "../../../Source/Core/AST/VarDeclDescope.nll"
					pOutputBuilder->m_sOut->Append(sxName);
#line 43 "../../../Source/Core/AST/VarDeclDescope.nll"
					for (int i = 0; i < nArraySizeSize; i++)
					{
#line 45 "../../../Source/Core/AST/VarDeclDescope.nll"
						pOutputBuilder->m_sOut->Append("[_x");
#line 46 "../../../Source/Core/AST/VarDeclDescope.nll"
						pOutputBuilder->m_sOut->AppendInt(i);
#line 47 "../../../Source/Core/AST/VarDeclDescope.nll"
						pOutputBuilder->m_sOut->Append("]");
					}
#line 49 "../../../Source/Core/AST/VarDeclDescope.nll"
					pOutputBuilder->m_sOut->Append(";\n");
				}
			}
			else
			{
#line 54 "../../../Source/Core/AST/VarDeclDescope.nll"
				if (eLanguage == AST::Language::CPP)
				{
#line 56 "../../../Source/Core/AST/VarDeclDescope.nll"
					Util::Pad(nDepth, pOutputBuilder->m_sOut);
#line 57 "../../../Source/Core/AST/VarDeclDescope.nll"
					pOutputBuilder->m_sOut->Append("if (");
#line 58 "../../../Source/Core/AST/VarDeclDescope.nll"
					pOutputBuilder->m_sOut->Append(sxName);
#line 59 "../../../Source/Core/AST/VarDeclDescope.nll"
					pOutputBuilder->m_sOut->Append(") delete ");
#line 60 "../../../Source/Core/AST/VarDeclDescope.nll"
					pOutputBuilder->m_sOut->Append(sxName);
#line 61 "../../../Source/Core/AST/VarDeclDescope.nll"
					pOutputBuilder->m_sOut->Append(";\n");
				}
				else
#line 63 "../../../Source/Core/AST/VarDeclDescope.nll"
					if (eLanguage == AST::Language::CS)
					{
						Project* pProject = GetProject();
						ValueType* pValueType = pVarDecl->m_pTypeRef->CreateValueType(pProject->m_pValidator->m_pResolver);
#line 67 "../../../Source/Core/AST/VarDeclDescope.nll"
						if (pValueType != 0 && pValueType->m_eType == ValueType::Type::CLASS_DECL_VALUE)
						{
#line 69 "../../../Source/Core/AST/VarDeclDescope.nll"
							if (pValueType->m_pClassDecl != 0 && pValueType->m_pClassDecl->m_bDisposable)
							{
#line 71 "../../../Source/Core/AST/VarDeclDescope.nll"
								Util::Pad(nDepth, pOutputBuilder->m_sOut);
#line 72 "../../../Source/Core/AST/VarDeclDescope.nll"
								pOutputBuilder->m_sOut->Append("if (");
#line 73 "../../../Source/Core/AST/VarDeclDescope.nll"
								pOutputBuilder->m_sOut->Append(sxName);
#line 74 "../../../Source/Core/AST/VarDeclDescope.nll"
								pOutputBuilder->m_sOut->Append(" != null) ");
#line 75 "../../../Source/Core/AST/VarDeclDescope.nll"
								pOutputBuilder->m_sOut->Append(sxName);
#line 76 "../../../Source/Core/AST/VarDeclDescope.nll"
								pOutputBuilder->m_sOut->Append(".Dispose();\n");
							}
						}
						if (pValueType) delete pValueType;
					}
			}
		}
	}

#line 3 "../../../Source/Core/AST/VarDeclDescope.nll"
	VarDeclDescope::~VarDeclDescope()
	{
		if (m_pVarDeclVector) delete m_pVarDeclVector;
	}

}

