#pragma once

#include "../../../LangShared/Vector/CPP/Vector.hpp"
#include "AST/VarDecl.hpp"
#include "../../../LangShared/Transpiled/Vector/OwnedVector.hpp"
#include "Validator.hpp"

namespace NumbatLogic
{
	class InternalString;
	class Scope;
	template <class T>
	class Vector;
	class VarDecl;
	class Project;
	template <class T>
	class OwnedVector;
	class ValidatorError;
	class ValidatorScope;
	class NamespaceNode;
	class AST;
}
namespace NumbatLogic
{
	class ValidatorError
	{
		public: InternalString* m_sError;
		public: InternalString* m_sFile;
		public: int m_nLine;
		public: int m_nColumn;
		public: ValidatorError();
		public: virtual ~ValidatorError();
	};
	class ValidatorScope
	{
		public: Scope* m_pScope;
		public: Vector<VarDecl*>* m_pVarDeclVector;
		public: ValidatorScope(Scope* pScope);
		public: virtual ~ValidatorScope();
	};
	class Validator
	{
		protected: Project* m_pProject;
		protected: OwnedVector<ValidatorError*>* m_pValidatorErrorVector;
		protected: OwnedVector<ValidatorScope*>* m_pValidatorScopeVector;
		public: NamespaceNode* m_pCurrentNamespaceNode;
		public: Validator(Project* pProject);
		protected: void PreparseNamespaces(NamespaceNode* pCurrentNode, AST* pAST);
		public: bool Validate();
		public: void AddError(const char* sError, InternalString* sFile, int nLine, int nColumn);
		public: void BeginScope(Scope* pScope);
		public: void AddVarDecl(VarDecl* pVarDecl);
		public: void EndScope(Scope* pScope);
		public: void InjectCleanup(AST* pBreakOrContinueOrReturn);
		public: void BeginNamespace(const char* sxName);
		public: void EndNamespace(const char* sxName);
		public: virtual ~Validator();
	};
}

