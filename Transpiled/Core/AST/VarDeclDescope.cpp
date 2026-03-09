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
#line 4 "../../../Source/Core/AST/VarDeclDescope.nll"
#line 8 "../../../Source/Core/AST/VarDeclDescope.nll"
	VarDeclDescope::VarDeclDescope()
	{
		m_pVarDeclVector = 0;
#line 10 "../../../Source/Core/AST/VarDeclDescope.nll"
		m_eType = AST::Type::AST_VAR_DECL_DESCOPE;
#line 11 "../../../Source/Core/AST/VarDeclDescope.nll"
		m_pVarDeclVector = new Vector<VarDecl*>();
	}

#line 14 "../../../Source/Core/AST/VarDeclDescope.nll"
	void VarDeclDescope::Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder* pOutputBuilder)
	{
#line 16 "../../../Source/Core/AST/VarDeclDescope.nll"
		for (int j = 0; j < m_pVarDeclVector->GetSize(); j++)
		{
			VarDecl* pVarDecl = m_pVarDeclVector->Get(j);
			const char* sxName = pVarDecl->m_pNameToken->GetString();
#line 21 "../../../Source/Core/AST/VarDeclDescope.nll"
			if (pVarDecl->m_pArraySizeVector != 0)
			{
#line 23 "../../../Source/Core/AST/VarDeclDescope.nll"
				if (eLanguage == AST::Language::CPP)
				{
					int nArraySizeSize = pVarDecl->m_pArraySizeVector->GetSize();
#line 26 "../../../Source/Core/AST/VarDeclDescope.nll"
					for (int i = 0; i < nArraySizeSize; i++)
					{
						AST* pArraySize = pVarDecl->m_pArraySizeVector->Get(i);
#line 29 "../../../Source/Core/AST/VarDeclDescope.nll"
						Util::Pad(nDepth + i, pOutputBuilder->m_sOut);
#line 30 "../../../Source/Core/AST/VarDeclDescope.nll"
						pOutputBuilder->m_sOut->Append("for (int _x");
#line 31 "../../../Source/Core/AST/VarDeclDescope.nll"
						pOutputBuilder->m_sOut->AppendInt(i);
#line 32 "../../../Source/Core/AST/VarDeclDescope.nll"
						pOutputBuilder->m_sOut->Append(" = 0; _x");
#line 33 "../../../Source/Core/AST/VarDeclDescope.nll"
						pOutputBuilder->m_sOut->AppendInt(i);
#line 34 "../../../Source/Core/AST/VarDeclDescope.nll"
						pOutputBuilder->m_sOut->Append(" < ");
#line 35 "../../../Source/Core/AST/VarDeclDescope.nll"
						pArraySize->Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
#line 36 "../../../Source/Core/AST/VarDeclDescope.nll"
						pOutputBuilder->m_sOut->Append("; _x");
#line 37 "../../../Source/Core/AST/VarDeclDescope.nll"
						pOutputBuilder->m_sOut->AppendInt(i);
#line 38 "../../../Source/Core/AST/VarDeclDescope.nll"
						pOutputBuilder->m_sOut->Append("++)\n");
					}
#line 41 "../../../Source/Core/AST/VarDeclDescope.nll"
					Util::Pad(nDepth + nArraySizeSize, pOutputBuilder->m_sOut);
#line 42 "../../../Source/Core/AST/VarDeclDescope.nll"
					pOutputBuilder->m_sOut->Append("delete ");
#line 43 "../../../Source/Core/AST/VarDeclDescope.nll"
					pOutputBuilder->m_sOut->Append(sxName);
#line 44 "../../../Source/Core/AST/VarDeclDescope.nll"
					for (int i = 0; i < nArraySizeSize; i++)
					{
#line 46 "../../../Source/Core/AST/VarDeclDescope.nll"
						pOutputBuilder->m_sOut->Append("[_x");
#line 47 "../../../Source/Core/AST/VarDeclDescope.nll"
						pOutputBuilder->m_sOut->AppendInt(i);
#line 48 "../../../Source/Core/AST/VarDeclDescope.nll"
						pOutputBuilder->m_sOut->Append("]");
					}
#line 50 "../../../Source/Core/AST/VarDeclDescope.nll"
					pOutputBuilder->m_sOut->Append(";\n");
				}
			}
			else
			{
#line 55 "../../../Source/Core/AST/VarDeclDescope.nll"
				if (eLanguage == AST::Language::CPP)
				{
#line 57 "../../../Source/Core/AST/VarDeclDescope.nll"
					Util::Pad(nDepth, pOutputBuilder->m_sOut);
#line 58 "../../../Source/Core/AST/VarDeclDescope.nll"
					pOutputBuilder->m_sOut->Append("if (");
#line 59 "../../../Source/Core/AST/VarDeclDescope.nll"
					pOutputBuilder->m_sOut->Append(sxName);
#line 60 "../../../Source/Core/AST/VarDeclDescope.nll"
					pOutputBuilder->m_sOut->Append(") delete ");
#line 61 "../../../Source/Core/AST/VarDeclDescope.nll"
					pOutputBuilder->m_sOut->Append(sxName);
#line 62 "../../../Source/Core/AST/VarDeclDescope.nll"
					pOutputBuilder->m_sOut->Append(";\n");
				}
				else
#line 64 "../../../Source/Core/AST/VarDeclDescope.nll"
					if (eLanguage == AST::Language::CS)
					{
						Project* pProject = GetProject();
						ValueType* pValueType = pVarDecl->m_pTypeRef->CreateValueType(pProject->m_pValidator->m_pResolver);
#line 68 "../../../Source/Core/AST/VarDeclDescope.nll"
						if (pValueType != 0 && pValueType->m_eType == ValueType::Type::CLASS_DECL_VALUE)
						{
#line 70 "../../../Source/Core/AST/VarDeclDescope.nll"
							if (pValueType->m_pClassDecl != 0 && pValueType->m_pClassDecl->m_bDisposable)
							{
#line 72 "../../../Source/Core/AST/VarDeclDescope.nll"
								Util::Pad(nDepth, pOutputBuilder->m_sOut);
#line 73 "../../../Source/Core/AST/VarDeclDescope.nll"
								pOutputBuilder->m_sOut->Append("if (");
#line 74 "../../../Source/Core/AST/VarDeclDescope.nll"
								pOutputBuilder->m_sOut->Append(sxName);
#line 75 "../../../Source/Core/AST/VarDeclDescope.nll"
								pOutputBuilder->m_sOut->Append(" != null) ");
#line 76 "../../../Source/Core/AST/VarDeclDescope.nll"
								pOutputBuilder->m_sOut->Append(sxName);
#line 77 "../../../Source/Core/AST/VarDeclDescope.nll"
								pOutputBuilder->m_sOut->Append(".Dispose();\n");
							}
						}
						if (pValueType) delete pValueType;
					}
			}
		}
	}

#line 4 "../../../Source/Core/AST/VarDeclDescope.nll"
	VarDeclDescope::~VarDeclDescope()
	{
		if (m_pVarDeclVector) delete m_pVarDeclVector;
	}

}

