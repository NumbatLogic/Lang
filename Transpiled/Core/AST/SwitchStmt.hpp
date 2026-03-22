#pragma once

#include "AST.hpp"
#include "../../../../LangShared/Source/Vector/CPP/Vector.hpp"

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
#line 0 "/home/cliffya/git/Lang/Source/Core/AST/SwitchStmt.nll"
namespace NumbatLogic
{
#line 3 "/home/cliffya/git/Lang/Source/Core/AST/SwitchStmt.nll"
	class SwitchStmt : public AST
	{
		public: AST* m_pExpression;
		public: Vector<AST*>* m_pExpressionVector;
		public: Vector<AST*>* m_pStatementVector;
		public: AST* m_pDefaultStatement;
#line 10 "/home/cliffya/git/Lang/Source/Core/AST/SwitchStmt.nll"
		public: SwitchStmt();
#line 19 "/home/cliffya/git/Lang/Source/Core/AST/SwitchStmt.nll"
		public: static SwitchStmt* TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum);
#line 181 "/home/cliffya/git/Lang/Source/Core/AST/SwitchStmt.nll"
		public: virtual void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder* pOutputBuilder);
#line 3 "/home/cliffya/git/Lang/Source/Core/AST/SwitchStmt.nll"
		public: virtual ~SwitchStmt();
	};
}

