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
		public: WhileStmt();
		public: static WhileStmt* TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum);
		public: virtual void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder* out);
	};
}

