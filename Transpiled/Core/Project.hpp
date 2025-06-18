#pragma once

#include "AST/AST.hpp"
#include "../../../LangShared/Vector/CPP/Vector.hpp"
#include "AST/TranslationUnit.hpp"
#include "../LangShared/Vector/OwnedVector.hpp"

namespace NumbatLogic
{
	class TranslationUnit;
	class NamespaceNode;
	class InternalString;
	class AST;
	class NamespaceDecl;
}
namespace NumbatLogic
{
	class Project : public AST
	{
		public: Vector<TranslationUnit*>* m_pTranslationUnitVector;
		public: NamespaceNode* m_pRootNamespaceNode;
		public: Project();
		public: void AddFile(const char* sFile, OwnedVector<InternalString*>* sDefineVector);
		public: void AddDirectory(const char* sDirectory, OwnedVector<InternalString*>* sDefineVector);
		public: void FullValidate();
		protected: void RecurseNamespaces(AST* pInAst, NamespaceDecl* pSecretNamespace, TranslationUnit* pSecretTranslationUnit);
		protected: void NamespaceMerge(AST* pParentAST);
		public: void Amalgamate(const char* sAmalgamateFileName);
		public: void Output(AST::Language eLanguage, OutputFile eOutputFile);
		public: virtual ~Project();
	};
}

