#include "Token.hpp"
#include "../../../LangShared/InternalString/CPP/InternalString.hpp"

namespace NumbatLogic
{
	class InternalString;
	class Token;
}
namespace NumbatLogic
{
	void Token::Stringify(InternalString* sOut)
	{
		sOut->Append(GetString());
	}

	const char* Token::GetString()
	{
		switch (m_eType)
		{
			case Type::TOKEN_AND:
			{
				return "&&";
			}

			case Type::TOKEN_ANGLE_BRACKET_LEFT:
			{
				return "<";
			}

			case Type::TOKEN_ANGLE_BRACKET_LEFT_EQUALS:
			{
				return "<=";
			}

			case Type::TOKEN_ANGLE_BRACKET_RIGHT:
			{
				return ">";
			}

			case Type::TOKEN_ANGLE_BRACKET_RIGHT_EQUALS:
			{
				return ">=";
			}

			case Type::TOKEN_BANG:
			{
				return "!";
			}

			case Type::TOKEN_BITWISE_AND:
			{
				return "&";
			}

			case Type::TOKEN_BITWISE_OR:
			{
				return "|";
			}

			case Type::TOKEN_CARET:
			{
				return "^";
			}

			case Type::TOKEN_CARRIGE_RETURN:
			{
				return "\r";
			}

			case Type::TOKEN_COLON:
			{
				return ":";
			}

			case Type::TOKEN_COMMA:
			{
				return ",";
			}

			case Type::TOKEN_CURLY_BRACE_LEFT:
			{
				return "{";
			}

			case Type::TOKEN_CURLY_BRACE_RIGHT:
			{
				return "}";
			}

			case Type::TOKEN_DIVIDE:
			{
				return "/";
			}

			case Type::TOKEN_DOT:
			{
				return ".";
			}

			case Type::TOKEN_DOUBLE_ANGLE_BRACKET_LEFT:
			{
				return "<<";
			}

			case Type::TOKEN_DOUBLE_ANGLE_BRACKET_RIGHT:
			{
				return ">>";
			}

			case Type::TOKEN_DOUBLE_COLON:
			{
				return "::";
			}

			case Type::TOKEN_DOUBLE_EQUALS:
			{
				return "==";
			}

			case Type::TOKEN_EQUALS:
			{
				return "=";
			}

			case Type::TOKEN_KEYWORD_BASE:
			{
				return "base";
			}

			case Type::TOKEN_KEYWORD_BOOL:
			{
				return "bool";
			}

			case Type::TOKEN_KEYWORD_BREAK:
			{
				return "break";
			}

			case Type::TOKEN_KEYWORD_CASE:
			{
				return "case";
			}

			case Type::TOKEN_KEYWORD_CAST:
			{
				return "cast";
			}

			case Type::TOKEN_KEYWORD_CLASS:
			{
				return "class";
			}

			case Type::TOKEN_KEYWORD_CONST:
			{
				return "const";
			}

			case Type::TOKEN_KEYWORD_DEFAULT:
			{
				return "default";
			}

			case Type::TOKEN_KEYWORD_DELETE:
			{
				return "delete";
			}

			case Type::TOKEN_KEYWORD_DISOWN:
			{
				return "disown";
			}

			case Type::TOKEN_KEYWORD_DOUBLE:
			{
				return "double";
			}

			case Type::TOKEN_KEYWORD_ELSE:
			{
				return "else";
			}

			case Type::TOKEN_KEYWORD_ENUM:
			{
				return "enum";
			}

			case Type::TOKEN_KEYWORD_FALSE:
			{
				return "false";
			}

			case Type::TOKEN_KEYWORD_FLOAT:
			{
				return "float";
			}

			case Type::TOKEN_KEYWORD_FOR:
			{
				return "for";
			}

			case Type::TOKEN_KEYWORD_IF:
			{
				return "if";
			}

			case Type::TOKEN_KEYWORD_INT16:
			{
				return "Int16";
			}

			case Type::TOKEN_KEYWORD_INT32:
			{
				return "Int32";
			}

			case Type::TOKEN_KEYWORD_INT8:
			{
				return "Int8";
			}

			case Type::TOKEN_KEYWORD_INT:
			{
				return "int";
			}

			case Type::TOKEN_KEYWORD_NAMESPACE:
			{
				return "namespace";
			}

			case Type::TOKEN_KEYWORD_NEW:
			{
				return "new";
			}

			case Type::TOKEN_KEYWORD_NULL:
			{
				return "null";
			}

			case Type::TOKEN_KEYWORD_OVERRIDE:
			{
				return "override";
			}

			case Type::TOKEN_KEYWORD_OWN:
			{
				return "own";
			}

			case Type::TOKEN_KEYWORD_PRIVATE:
			{
				return "private";
			}

			case Type::TOKEN_KEYWORD_PUBLIC:
			{
				return "public";
			}

			case Type::TOKEN_KEYWORD_RETURN:
			{
				return "return";
			}

			case Type::TOKEN_KEYWORD_REF:
			{
				return "ref";
			}

			case Type::TOKEN_KEYWORD_STRING:
			{
				return "string";
			}

			case Type::TOKEN_KEYWORD_SWITCH:
			{
				return "switch";
			}

			case Type::TOKEN_KEYWORD_THIS:
			{
				return "this";
			}

			case Type::TOKEN_KEYWORD_TRUE:
			{
				return "true";
			}

			case Type::TOKEN_KEYWORD_UINT16:
			{
				return "Uint16";
			}

			case Type::TOKEN_KEYWORD_UINT32:
			{
				return "Uint32";
			}

			case Type::TOKEN_KEYWORD_UINT64:
			{
				return "Uint64";
			}

			case Type::TOKEN_KEYWORD_UINT8:
			{
				return "Uint8";
			}

			case Type::TOKEN_KEYWORD_UINT:
			{
				return "uint";
			}

			case Type::TOKEN_KEYWORD_UNICHAR:
			{
				return "UniChar";
			}

			case Type::TOKEN_KEYWORD_USING:
			{
				return "using";
			}

			case Type::TOKEN_KEYWORD_VIRTUAL:
			{
				return "virtual";
			}

			case Type::TOKEN_KEYWORD_VOID:
			{
				return "void";
			}

			case Type::TOKEN_KEYWORD_VOIDPTR:
			{
				return "voidptr";
			}

			case Type::TOKEN_KEYWORD_WHILE:
			{
				return "while";
			}

			case Type::TOKEN_MINUS:
			{
				return "-";
			}

			case Type::TOKEN_MINUS_EQUALS:
			{
				return "-=";
			}

			case Type::TOKEN_MINUS_MINUS:
			{
				return "--";
			}

			case Type::TOKEN_MODULUS:
			{
				return "%";
			}

			case Type::TOKEN_NEW_LINE:
			{
				return "\n";
			}

			case Type::TOKEN_NOT_EQUALS:
			{
				return "!=";
			}

			case Type::TOKEN_OR:
			{
				return "||";
			}

			case Type::TOKEN_PARENTHESIS_LEFT:
			{
				return "(";
			}

			case Type::TOKEN_PARENTHESIS_RIGHT:
			{
				return ")";
			}

			case Type::TOKEN_PLUS:
			{
				return "+";
			}

			case Type::TOKEN_PLUS_EQUALS:
			{
				return "+=";
			}

			case Type::TOKEN_PLUS_PLUS:
			{
				return "++";
			}

			case Type::TOKEN_QUESTION_MARK:
			{
				return "?";
			}

			case Type::TOKEN_SEMICOLON:
			{
				return ";";
			}

			case Type::TOKEN_SPACE:
			{
				return " ";
			}

			case Type::TOKEN_SQUARE_BRACKET_LEFT:
			{
				return "[";
			}

			case Type::TOKEN_SQUARE_BRACKET_RIGHT:
			{
				return "]";
			}

			case Type::TOKEN_STAR:
			{
				return "*";
			}

			case Type::TOKEN_STAR_DOUBLE:
			{
				return "**";
			}

			case Type::TOKEN_TAB:
			{
				return "\t";
			}

			case Type::TOKEN_TILDE:
			{
				return "~";
			}

			case Type::TOKEN_CHAR:
			{
				return m_sValue->GetExternalString();
			}

			case Type::TOKEN_CHAR_UNTERMINATED:
			{
				return m_sValue->GetExternalString();
			}

			case Type::TOKEN_IDENTIFIER:
			{
				return m_sValue->GetExternalString();
			}

			case Type::TOKEN_NUMBER:
			{
				return m_sValue->GetExternalString();
			}

			case Type::TOKEN_STRING:
			{
				return m_sValue->GetExternalString();
			}

			case Type::TOKEN_STRING_UNTERMINATED:
			{
				return m_sValue->GetExternalString();
			}

		}
		return "???";
	}

	Token* Token::Clone()
	{
		Token* pToken = new Token();
		pToken->m_eType = m_eType;
		pToken->m_sFileName = m_sFileName;
		pToken->m_nLine = m_nLine;
		pToken->m_nColumn = m_nColumn;
		if (m_sValue != 0)
			pToken->m_sValue = new InternalString(m_sValue->GetExternalString());
		NumbatLogic::Token* __338280889 = pToken;
		pToken = 0;
		return __338280889;
	}

	Token::Token()
	{
		m_eType = Type::TOKEN_AND;
		m_sFileName = 0;
		m_nLine = 0;
		m_nColumn = 0;
		m_sValue = 0;
	}

	Token::~Token()
	{
		if (m_sValue) delete m_sValue;
	}

}

