#pragma once

#include "AST.hpp"

namespace NumbatLogic
{
	class AST;
	class AccessLevel;
	class FunctionDecl;
	class DelegateDecl;
	class TokenContainer;
	class OffsetDatum;
	class ClassDecl;
	class OutputBuilder;
}
#line 1 "../../../Source/Core/AST/DelegateDecl.nll"
namespace NumbatLogic
{
#line 4 "../../../Source/Core/AST/DelegateDecl.nll"
	class DelegateDecl : public AST
	{
#line 6 "../../../Source/Core/AST/DelegateDecl.nll"
		public: AccessLevel* m_pAccessLevel;
#line 7 "../../../Source/Core/AST/DelegateDecl.nll"
		public: FunctionDecl* m_pFunctionDecl;
#line 9 "../../../Source/Core/AST/DelegateDecl.nll"
		public: DelegateDecl();
#line 14 "../../../Source/Core/AST/DelegateDecl.nll"
		public: static DelegateDecl* TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum, ClassDecl* pParentClassDecl);
#line 59 "../../../Source/Core/AST/DelegateDecl.nll"
		public: virtual void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder* pOutputBuilder);
	};
}

