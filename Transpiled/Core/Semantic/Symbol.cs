#line 1 "../../../Source/Core/Semantic/Symbol.nll"
namespace NumbatLogic
{
	class Symbol
	{
		public enum Kind
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
		}

		public Kind m_eKind;
#line 22 "../../../Source/Core/Semantic/Symbol.nll"
		public string m_sShortName;
#line 25 "../../../Source/Core/Semantic/Symbol.nll"
		public string m_sQualifiedName;
#line 28 "../../../Source/Core/Semantic/Symbol.nll"
		public AST m_pDeclAST;
#line 31 "../../../Source/Core/Semantic/Symbol.nll"
		public SymbolScope m_pScope;
#line 33 "../../../Source/Core/Semantic/Symbol.nll"
		public Symbol()
		{
			m_eKind = Kind.VAR;
			m_sShortName = "";
			m_sQualifiedName = "";
			m_pDeclAST = null;
			m_pScope = null;
		}

	}
}

