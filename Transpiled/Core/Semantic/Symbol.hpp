#pragma once

namespace NumbatLogic
{
	class AST;
	class SymbolScope;
}
namespace NumbatLogic
{
	class Symbol
	{
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

		public: Kind m_eKind;
		public: const char* m_sShortName;
		public: const char* m_sQualifiedName;
		public: AST* m_pDeclAST;
		public: SymbolScope* m_pScope;
		public: Symbol();
	};
}

