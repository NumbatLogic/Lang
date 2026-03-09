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
#line 1 "../../../Source/Core/Project.nll"
namespace NumbatLogic
{
#line 4 "../../../Source/Core/Project.nll"
	class Project : public AST
	{
#line 6 "../../../Source/Core/Project.nll"
		public: Vector<TranslationUnit*>* m_pTranslationUnitVector;
#line 7 "../../../Source/Core/Project.nll"
		public: NamespaceNode* m_pRootNamespaceNode;
#line 8 "../../../Source/Core/Project.nll"
		public: Validator* m_pValidator;
#line 10 "../../../Source/Core/Project.nll"
		public: Project();
#line 19 "../../../Source/Core/Project.nll"
		public: void AddFile(const char* sFile, OwnedVector<InternalString*>* sDefineVector);
#line 46 "../../../Source/Core/Project.nll"
		public: void AddDirectory(const char* sDirectory, OwnedVector<InternalString*>* sDefineVector);
#line 57 "../../../Source/Core/Project.nll"
		public: void FullValidate();
#line 81 "../../../Source/Core/Project.nll"
		protected: void RecurseNamespaces(AST* pInAst, NamespaceDecl* pSecretNamespace, TranslationUnit* pSecretTranslationUnit);
#line 140 "../../../Source/Core/Project.nll"
		protected: void NamespaceMerge(AST* pParentAST);
#line 213 "../../../Source/Core/Project.nll"
		public: void Amalgamate(const char* sAmalgamateFileName);
#line 277 "../../../Source/Core/Project.nll"
		public: void Output(AST::Language eLanguage, OutputFile eOutputFile);
#line 4 "../../../Source/Core/Project.nll"
		public: virtual ~Project();
	};
}

