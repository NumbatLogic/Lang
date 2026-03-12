#pragma once

#include "AST.hpp"

namespace NumbatLogic
{
	class AST;
	class Scope;
	class WhileStmt;
	class TokenContainer;
	class OffsetDatum;
	class OutputBuilder;
}
#line 0 "../../../Source/Core/AST/WhileStmt.nll"
namespace NumbatLogic
{
#line 3 "../../../Source/Core/AST/WhileStmt.nll"
	class WhileStmt : public AST
	{
		public: AST* m_pExpression;
		public: Scope* m_pScope;
#line 8 "../../../Source/Core/AST/WhileStmt.nll"
		public: WhileStmt();
#line 13 "../../../Source/Core/AST/WhileStmt.nll"
		public: static WhileStmt* TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum);
#line 69 "../../../Source/Core/AST/WhileStmt.nll"
		public: virtual void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder* pOutputBuilder);
	};
}

