#pragma once

#include "AST/AST.hpp"
#include "../../../LangShared/Vector/CPP/Vector.hpp"
#include "AST/TranslationUnit.hpp"
#include "../../../LangShared/Transpiled/Vector/OwnedVector.hpp"

namespace NumbatLogic
{
	template <class T>
	class Vector;
	class TranslationUnit;
	class NamespaceNode;
	class Validator;
	template <class T>
	class OwnedVector;
	class InternalString;
	class AST;
	class NamespaceDecl;
	class Token;
}
#line 0 "../../../Source/Core/Project.nll"
namespace NumbatLogic
{
#line 3 "../../../Source/Core/Project.nll"
	class Project : public AST
	{
		public: Vector<TranslationUnit*>* m_pTranslationUnitVector;
		public: NamespaceNode* m_pRootNamespaceNode;
		public: Validator* m_pValidator;
#line 9 "../../../Source/Core/Project.nll"
		public: Project();
#line 18 "../../../Source/Core/Project.nll"
		public: void AddFile(const char* sFile, OwnedVector<InternalString*>* sDefineVector);
#line 45 "../../../Source/Core/Project.nll"
		public: void AddDirectory(const char* sDirectory, OwnedVector<InternalString*>* sDefineVector);
#line 60 "../../../Source/Core/Project.nll"
		public: void FullValidate();
#line 84 "../../../Source/Core/Project.nll"
		protected: void RecurseNamespaces(AST* pInAst, NamespaceDecl* pSecretNamespace, TranslationUnit* pSecretTranslationUnit);
#line 143 "../../../Source/Core/Project.nll"
		protected: void NamespaceMerge(AST* pParentAST);
#line 216 "../../../Source/Core/Project.nll"
		public: void Amalgamate(const char* sAmalgamateFileName);
#line 280 "../../../Source/Core/Project.nll"
		public: void Output(AST::Language eLanguage, OutputFile eOutputFile);
#line 3 "../../../Source/Core/Project.nll"
		public: virtual ~Project();
	};
}

