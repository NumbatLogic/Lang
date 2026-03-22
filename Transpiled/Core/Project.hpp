#pragma once

#include "AST/AST.hpp"
#include "../../../LangShared/Source/Vector/CPP/Vector.hpp"
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
#line 0 "/home/cliffya/git/Lang/Source/Core/Project.nll"
namespace NumbatLogic
{
#line 3 "/home/cliffya/git/Lang/Source/Core/Project.nll"
	class Project : public AST
	{
		public: Vector<TranslationUnit*>* m_pTranslationUnitVector;
		public: NamespaceNode* m_pRootNamespaceNode;
		public: Validator* m_pValidator;
#line 9 "/home/cliffya/git/Lang/Source/Core/Project.nll"
		public: Project();
#line 18 "/home/cliffya/git/Lang/Source/Core/Project.nll"
		public: void AddFile(const char* sFile, OwnedVector<InternalString*>* sDefineVector);
#line 45 "/home/cliffya/git/Lang/Source/Core/Project.nll"
		public: bool AddDirectory(const char* sDirectory, OwnedVector<InternalString*>* sDefineVector);
#line 66 "/home/cliffya/git/Lang/Source/Core/Project.nll"
		public: void FullValidate();
#line 76 "/home/cliffya/git/Lang/Source/Core/Project.nll"
		protected: void RecurseNamespaces(AST* pInAst, NamespaceDecl* pSecretNamespace, TranslationUnit* pSecretTranslationUnit);
#line 135 "/home/cliffya/git/Lang/Source/Core/Project.nll"
		protected: void NamespaceMerge(AST* pParentAST);
#line 208 "/home/cliffya/git/Lang/Source/Core/Project.nll"
		public: void Amalgamate(const char* sAmalgamateFileName);
#line 272 "/home/cliffya/git/Lang/Source/Core/Project.nll"
		public: void Output(AST::Language eLanguage, OutputFile eOutputFile);
#line 3 "/home/cliffya/git/Lang/Source/Core/Project.nll"
		public: virtual ~Project();
	};
}

