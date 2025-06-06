#pragma once

#include "AST.hpp"
#include "../../../../LangShared/Vector/CPP/Vector.hpp"

namespace NumberDuck
{
	namespace Secret
	{
		class AST;
		class SwitchStmt;
		class TokenContainer;
		class OffsetDatum;
		class InternalString;
	}
}
namespace NumberDuck
{
	namespace Secret
	{
		class SwitchStmt : public AST
		{
			public: AST* m_pExpression;
			public: Vector<AST*>* m_pExpressionVector;
			public: Vector<AST*>* m_pStatementVector;
			public: AST* m_pDefaultStatement;
			public: SwitchStmt();
			public: static SwitchStmt* TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum);
			public: virtual void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, InternalString* sOut);
			public: virtual ~SwitchStmt();
		};
	}
}

