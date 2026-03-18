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
#line 0 "/home/cliffya/git/Lang/Source/Core/Validator.nll"
namespace NumbatLogic
{
#line 3 "/home/cliffya/git/Lang/Source/Core/Validator.nll"
	class ValidatorError
	{
		public: InternalString* m_sError;
		public: InternalString* m_sFile;
		public: int m_nLine;
		public: int m_nColumn;
#line 3 "/home/cliffya/git/Lang/Source/Core/Validator.nll"
		public: ValidatorError();
#line 3 "/home/cliffya/git/Lang/Source/Core/Validator.nll"
		public: virtual ~ValidatorError();
	};
#line 11 "/home/cliffya/git/Lang/Source/Core/Validator.nll"
	class ValidatorScope
	{
		public: Scope* m_pScope;
		public: Vector<VarDecl*>* m_pVarDeclVector;
#line 16 "/home/cliffya/git/Lang/Source/Core/Validator.nll"
		public: ValidatorScope(Scope* pScope);
#line 11 "/home/cliffya/git/Lang/Source/Core/Validator.nll"
		public: virtual ~ValidatorScope();
	};
#line 23 "/home/cliffya/git/Lang/Source/Core/Validator.nll"
	class Validator
	{
		protected: Project* m_pProject;
		protected: OwnedVector<ValidatorError*>* m_pValidatorErrorVector;
		protected: OwnedVector<ValidatorScope*>* m_pValidatorScopeVector;
#line 29 "/home/cliffya/git/Lang/Source/Core/Validator.nll"
		public: NamespaceNode* m_pCurrentNamespaceNode;
#line 32 "/home/cliffya/git/Lang/Source/Core/Validator.nll"
		public: Resolver* m_pResolver;
#line 34 "/home/cliffya/git/Lang/Source/Core/Validator.nll"
		public: Validator(Project* pProject);
#line 44 "/home/cliffya/git/Lang/Source/Core/Validator.nll"
		protected: void PreparseNamespaces(NamespaceNode* pCurrentNode, AST* pAST);
#line 59 "/home/cliffya/git/Lang/Source/Core/Validator.nll"
		public: bool Validate();
#line 113 "/home/cliffya/git/Lang/Source/Core/Validator.nll"
		public: void AddError(const char* sError, InternalString* sFile, int nLine, int nColumn);
#line 127 "/home/cliffya/git/Lang/Source/Core/Validator.nll"
		public: void ValidateSubtree(AST* pRoot);
#line 133 "/home/cliffya/git/Lang/Source/Core/Validator.nll"
		public: void BeginScope(Scope* pScope);
#line 139 "/home/cliffya/git/Lang/Source/Core/Validator.nll"
		public: void AddVarDecl(VarDecl* pVarDecl);
#line 153 "/home/cliffya/git/Lang/Source/Core/Validator.nll"
		public: void EndScope(Scope* pScope);
#line 180 "/home/cliffya/git/Lang/Source/Core/Validator.nll"
		public: void InjectCleanup(AST* pBreakOrContinueOrReturn);
#line 239 "/home/cliffya/git/Lang/Source/Core/Validator.nll"
		public: void BeginNamespace(const char* sxName);
#line 245 "/home/cliffya/git/Lang/Source/Core/Validator.nll"
		public: void EndNamespace(const char* sxName);
#line 23 "/home/cliffya/git/Lang/Source/Core/Validator.nll"
		public: virtual ~Validator();
	};
}

