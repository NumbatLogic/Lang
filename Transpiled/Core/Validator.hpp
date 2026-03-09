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
	class Resolver;
	class AST;
	class VarDeclDescope;
}
#line 1 "../../../Source/Core/Validator.nll"
namespace NumbatLogic
{
#line 4 "../../../Source/Core/Validator.nll"
	class ValidatorError
	{
#line 6 "../../../Source/Core/Validator.nll"
		public: InternalString* m_sError;
#line 7 "../../../Source/Core/Validator.nll"
		public: InternalString* m_sFile;
#line 8 "../../../Source/Core/Validator.nll"
		public: int m_nLine;
#line 9 "../../../Source/Core/Validator.nll"
		public: int m_nColumn;
#line 4 "../../../Source/Core/Validator.nll"
		public: ValidatorError();
#line 4 "../../../Source/Core/Validator.nll"
		public: virtual ~ValidatorError();
	};
#line 12 "../../../Source/Core/Validator.nll"
	class ValidatorScope
	{
#line 14 "../../../Source/Core/Validator.nll"
		public: Scope* m_pScope;
#line 15 "../../../Source/Core/Validator.nll"
		public: Vector<VarDecl*>* m_pVarDeclVector;
#line 17 "../../../Source/Core/Validator.nll"
		public: ValidatorScope(Scope* pScope);
#line 12 "../../../Source/Core/Validator.nll"
		public: virtual ~ValidatorScope();
	};
#line 24 "../../../Source/Core/Validator.nll"
	class Validator
	{
#line 26 "../../../Source/Core/Validator.nll"
		protected: Project* m_pProject;
#line 27 "../../../Source/Core/Validator.nll"
		protected: OwnedVector<ValidatorError*>* m_pValidatorErrorVector;
#line 28 "../../../Source/Core/Validator.nll"
		protected: OwnedVector<ValidatorScope*>* m_pValidatorScopeVector;
#line 30 "../../../Source/Core/Validator.nll"
		public: NamespaceNode* m_pCurrentNamespaceNode;
#line 33 "../../../Source/Core/Validator.nll"
		public: Resolver* m_pResolver;
#line 35 "../../../Source/Core/Validator.nll"
		public: Validator(Project* pProject);
#line 45 "../../../Source/Core/Validator.nll"
		protected: void PreparseNamespaces(NamespaceNode* pCurrentNode, AST* pAST);
#line 60 "../../../Source/Core/Validator.nll"
		public: bool Validate();
#line 114 "../../../Source/Core/Validator.nll"
		public: void AddError(const char* sError, InternalString* sFile, int nLine, int nColumn);
#line 128 "../../../Source/Core/Validator.nll"
		public: void ValidateSubtree(AST* pRoot);
#line 134 "../../../Source/Core/Validator.nll"
		public: void BeginScope(Scope* pScope);
#line 140 "../../../Source/Core/Validator.nll"
		public: void AddVarDecl(VarDecl* pVarDecl);
#line 154 "../../../Source/Core/Validator.nll"
		public: void EndScope(Scope* pScope);
#line 181 "../../../Source/Core/Validator.nll"
		public: void InjectCleanup(AST* pBreakOrContinueOrReturn);
#line 240 "../../../Source/Core/Validator.nll"
		public: void BeginNamespace(const char* sxName);
#line 246 "../../../Source/Core/Validator.nll"
		public: void EndNamespace(const char* sxName);
#line 24 "../../../Source/Core/Validator.nll"
		public: virtual ~Validator();
	};
}

