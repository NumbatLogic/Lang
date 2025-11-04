#pragma once

#include "AST.hpp"

namespace NumbatLogic
{
	class AST;
	class ParamDecl;
	class ParamCall;
	class TokenContainer;
	class OffsetDatum;
	class InternalString;
}
namespace NumbatLogic
{
	class ParamCall : public AST
	{
		public: ParamDecl* m_pFoundParamDecl;
		public: static ParamCall* TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum);
		public: virtual void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, InternalString* sOut);
		public: ParamCall();
	};
}

