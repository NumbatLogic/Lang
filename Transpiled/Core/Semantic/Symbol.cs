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
		public string m_sShortName;
		public string m_sQualifiedName;
		public AST m_pDeclAST;
		public SymbolScope m_pScope;
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

