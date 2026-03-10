#pragma once

#include "AST.hpp"
#include "../../../../LangShared/Vector/CPP/Vector.hpp"

namespace NumbatLogic
{
	class AST;
	template <class T>
	class Vector;
	class SwitchStmt;
	class TokenContainer;
	class OffsetDatum;
	class OutputBuilder;
}
#line 0 "../../../Source/Core/AST/SwitchStmt.nll"
namespace NumbatLogic
{
#line 3 "../../../Source/Core/AST/SwitchStmt.nll"
	class SwitchStmt : public AST
	{
#line 5 "../../../Source/Core/AST/SwitchStmt.nll"
		public: AST* m_pExpression;
#line 6 "../../../Source/Core/AST/SwitchStmt.nll"
		public: Vector<AST*>* m_pExpressionVector;
#line 7 "../../../Source/Core/AST/SwitchStmt.nll"
		public: Vector<AST*>* m_pStatementVector;
#line 8 "../../../Source/Core/AST/SwitchStmt.nll"
		public: AST* m_pDefaultStatement;
#line 10 "../../../Source/Core/AST/SwitchStmt.nll"
		public: SwitchStmt();
#line 19 "../../../Source/Core/AST/SwitchStmt.nll"
		public: static SwitchStmt* TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum);
#line 181 "../../../Source/Core/AST/SwitchStmt.nll"
		public: virtual void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder* pOutputBuilder);
#line 3 "../../../Source/Core/AST/SwitchStmt.nll"
		public: virtual ~SwitchStmt();
	};
}

