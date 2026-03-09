#pragma once

namespace NumbatLogic
{
	class AST;
	class SymbolScope;
}
#line 1 "../../../Source/Core/Semantic/Symbol.nll"
namespace NumbatLogic
{
#line 4 "../../../Source/Core/Semantic/Symbol.nll"
	class Symbol
	{
#line 6 "../../../Source/Core/Semantic/Symbol.nll"
		public: enum Kind
		{
			NAMESPACE,
			CLASS,
			ENUM,
			GENERIC_PARAM,
			FUNCTION,
			DELEGATE,
			METHOD,
			VAR,
			PARAM,
			ENUM_VALUE,
		};

#line 20 "../../../Source/Core/Semantic/Symbol.nll"
		public: Kind m_eKind;
#line 23 "../../../Source/Core/Semantic/Symbol.nll"
		public: const char* m_sShortName;
#line 26 "../../../Source/Core/Semantic/Symbol.nll"
		public: const char* m_sQualifiedName;
#line 29 "../../../Source/Core/Semantic/Symbol.nll"
		public: AST* m_pDeclAST;
#line 32 "../../../Source/Core/Semantic/Symbol.nll"
		public: SymbolScope* m_pScope;
#line 34 "../../../Source/Core/Semantic/Symbol.nll"
		public: Symbol();
	};
}

