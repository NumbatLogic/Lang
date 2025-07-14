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
	class InternalString;
}
namespace NumbatLogic
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

