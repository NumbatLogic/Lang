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
		public: DelegateDecl();
		public: static DelegateDecl* TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum, ClassDecl* pParentClassDecl);
		public: virtual void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder* out);
	};
}

