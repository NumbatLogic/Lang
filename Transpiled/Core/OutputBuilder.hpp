#pragma once

#include "AST/AST.hpp"

namespace NumbatLogic
{
	class InternalString;
	class AST;
	class Token;
}
#line 0 "../../../Source/Core/OutputBuilder.nll"
namespace NumbatLogic
{
#line 3 "../../../Source/Core/OutputBuilder.nll"
	class OutputBuilder
	{
#line 5 "../../../Source/Core/OutputBuilder.nll"
		public: InternalString* m_sOut;
#line 7 "../../../Source/Core/OutputBuilder.nll"
		public: OutputBuilder();
#line 12 "../../../Source/Core/OutputBuilder.nll"
		public: void UpdateSourceLocation(AST::Language eLanguage, Token* pToken);
#line 3 "../../../Source/Core/OutputBuilder.nll"
		public: virtual ~OutputBuilder();
	};
}

