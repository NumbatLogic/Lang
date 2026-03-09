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
#line 1 "../../../Source/Core/AST/WhileStmt.nll"
namespace NumbatLogic
{
#line 4 "../../../Source/Core/AST/WhileStmt.nll"
	class WhileStmt : public AST
	{
#line 6 "../../../Source/Core/AST/WhileStmt.nll"
		public: AST* m_pExpression;
#line 7 "../../../Source/Core/AST/WhileStmt.nll"
		public: Scope* m_pScope;
#line 9 "../../../Source/Core/AST/WhileStmt.nll"
		public: WhileStmt();
#line 14 "../../../Source/Core/AST/WhileStmt.nll"
		public: static WhileStmt* TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum);
#line 70 "../../../Source/Core/AST/WhileStmt.nll"
		public: virtual void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder* pOutputBuilder);
	};
}

