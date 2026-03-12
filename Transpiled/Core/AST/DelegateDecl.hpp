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
#line 0 "../../../Source/Core/AST/DelegateDecl.nll"
namespace NumbatLogic
{
#line 3 "../../../Source/Core/AST/DelegateDecl.nll"
	class DelegateDecl : public AST
	{
		public: AccessLevel* m_pAccessLevel;
		public: FunctionDecl* m_pFunctionDecl;
#line 8 "../../../Source/Core/AST/DelegateDecl.nll"
		public: DelegateDecl();
#line 13 "../../../Source/Core/AST/DelegateDecl.nll"
		public: static DelegateDecl* TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum, ClassDecl* pParentClassDecl);
#line 58 "../../../Source/Core/AST/DelegateDecl.nll"
		public: virtual void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder* pOutputBuilder);
	};
}

