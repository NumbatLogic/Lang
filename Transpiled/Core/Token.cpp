#include "Token.hpp"
#include "../../../LangShared/Source/InternalString/CPP/InternalString.hpp"

namespace NumbatLogic
{
	class InternalString;
	class Token;
}
#line 0 "/home/cliffya/git/Lang/Source/Core/Token.nll"
namespace NumbatLogic
{
#line 3 "/home/cliffya/git/Lang/Source/Core/Token.nll"
#line 104 "/home/cliffya/git/Lang/Source/Core/Token.nll"
	void Token::Stringify(InternalString* sOut)
	{
		sOut->Append(GetString());
	}

	const char* Token::GetString()
	{
		switch (m_eType)
		{
			case Type::TOKEN_ANGLE_BRACKET_LEFT:
			{
#line 113 "/home/cliffya/git/Lang/Source/Core/Token.nll"
				return "<";
			}

			case Type::TOKEN_ANGLE_BRACKET_RIGHT:
			{
#line 114 "/home/cliffya/git/Lang/Source/Core/Token.nll"
				return ">";
			}

			case Type::TOKEN_BANG:
			{
#line 115 "/home/cliffya/git/Lang/Source/Core/Token.nll"
				return "!";
			}

			case Type::TOKEN_BITWISE_AND:
			{
#line 116 "/home/cliffya/git/Lang/Source/Core/Token.nll"
				return "&";
			}

			case Type::TOKEN_BITWISE_OR:
			{
#line 117 "/home/cliffya/git/Lang/Source/Core/Token.nll"
				return "|";
			}

			case Type::TOKEN_CARET:
			{
#line 118 "/home/cliffya/git/Lang/Source/Core/Token.nll"
				return "^";
			}

			case Type::TOKEN_CARRIGE_RETURN:
			{
#line 119 "/home/cliffya/git/Lang/Source/Core/Token.nll"
				return "\r";
			}

			case Type::TOKEN_COLON:
			{
#line 120 "/home/cliffya/git/Lang/Source/Core/Token.nll"
				return ":";
			}

			case Type::TOKEN_COMMA:
			{
#line 121 "/home/cliffya/git/Lang/Source/Core/Token.nll"
				return ",";
			}

			case Type::TOKEN_CURLY_BRACE_LEFT:
			{
#line 122 "/home/cliffya/git/Lang/Source/Core/Token.nll"
				return "{";
			}

			case Type::TOKEN_CURLY_BRACE_RIGHT:
			{
#line 123 "/home/cliffya/git/Lang/Source/Core/Token.nll"
				return "}";
			}

			case Type::TOKEN_DIVIDE:
			{
#line 124 "/home/cliffya/git/Lang/Source/Core/Token.nll"
				return "/";
			}

			case Type::TOKEN_DOT:
			{
#line 125 "/home/cliffya/git/Lang/Source/Core/Token.nll"
				return ".";
			}

			case Type::TOKEN_DOUBLE_COLON:
			{
#line 126 "/home/cliffya/git/Lang/Source/Core/Token.nll"
				return "::";
			}

			case Type::TOKEN_EQUALS:
			{
#line 127 "/home/cliffya/git/Lang/Source/Core/Token.nll"
				return "=";
			}

			case Type::TOKEN_KEYWORD_BASE:
			{
#line 128 "/home/cliffya/git/Lang/Source/Core/Token.nll"
				return "base";
			}

			case Type::TOKEN_KEYWORD_BOOL:
			{
#line 129 "/home/cliffya/git/Lang/Source/Core/Token.nll"
				return "bool";
			}

			case Type::TOKEN_KEYWORD_BREAK:
			{
#line 130 "/home/cliffya/git/Lang/Source/Core/Token.nll"
				return "break";
			}

			case Type::TOKEN_KEYWORD_CASE:
			{
#line 131 "/home/cliffya/git/Lang/Source/Core/Token.nll"
				return "case";
			}

			case Type::TOKEN_KEYWORD_CAST:
			{
#line 132 "/home/cliffya/git/Lang/Source/Core/Token.nll"
				return "cast";
			}

			case Type::TOKEN_KEYWORD_CLASS:
			{
#line 133 "/home/cliffya/git/Lang/Source/Core/Token.nll"
				return "class";
			}

			case Type::TOKEN_KEYWORD_CONST:
			{
#line 134 "/home/cliffya/git/Lang/Source/Core/Token.nll"
				return "const";
			}

			case Type::TOKEN_KEYWORD_DEFAULT:
			{
#line 135 "/home/cliffya/git/Lang/Source/Core/Token.nll"
				return "default";
			}

			case Type::TOKEN_KEYWORD_DELETE:
			{
#line 136 "/home/cliffya/git/Lang/Source/Core/Token.nll"
				return "delete";
			}

			case Type::TOKEN_KEYWORD_DISOWN:
			{
#line 137 "/home/cliffya/git/Lang/Source/Core/Token.nll"
				return "disown";
			}

			case Type::TOKEN_KEYWORD_DISPOSABLE:
			{
#line 138 "/home/cliffya/git/Lang/Source/Core/Token.nll"
				return "disposable";
			}

			case Type::TOKEN_KEYWORD_DOUBLE:
			{
#line 139 "/home/cliffya/git/Lang/Source/Core/Token.nll"
				return "double";
			}

			case Type::TOKEN_KEYWORD_ELSE:
			{
#line 140 "/home/cliffya/git/Lang/Source/Core/Token.nll"
				return "else";
			}

			case Type::TOKEN_KEYWORD_ENUM:
			{
#line 141 "/home/cliffya/git/Lang/Source/Core/Token.nll"
				return "enum";
			}

			case Type::TOKEN_KEYWORD_FALSE:
			{
#line 142 "/home/cliffya/git/Lang/Source/Core/Token.nll"
				return "false";
			}

			case Type::TOKEN_KEYWORD_FLOAT:
			{
#line 143 "/home/cliffya/git/Lang/Source/Core/Token.nll"
				return "float";
			}

			case Type::TOKEN_KEYWORD_FOR:
			{
#line 144 "/home/cliffya/git/Lang/Source/Core/Token.nll"
				return "for";
			}

			case Type::TOKEN_KEYWORD_IF:
			{
#line 145 "/home/cliffya/git/Lang/Source/Core/Token.nll"
				return "if";
			}

			case Type::TOKEN_KEYWORD_INT:
			{
#line 146 "/home/cliffya/git/Lang/Source/Core/Token.nll"
				return "int";
			}

			case Type::TOKEN_KEYWORD_INT16:
			{
#line 147 "/home/cliffya/git/Lang/Source/Core/Token.nll"
				return "Int16";
			}

			case Type::TOKEN_KEYWORD_INT32:
			{
#line 148 "/home/cliffya/git/Lang/Source/Core/Token.nll"
				return "Int32";
			}

			case Type::TOKEN_KEYWORD_INT8:
			{
#line 149 "/home/cliffya/git/Lang/Source/Core/Token.nll"
				return "Int8";
			}

			case Type::TOKEN_KEYWORD_NAMESPACE:
			{
#line 150 "/home/cliffya/git/Lang/Source/Core/Token.nll"
				return "namespace";
			}

			case Type::TOKEN_KEYWORD_NEW:
			{
#line 151 "/home/cliffya/git/Lang/Source/Core/Token.nll"
				return "new";
			}

			case Type::TOKEN_KEYWORD_NULL:
			{
#line 152 "/home/cliffya/git/Lang/Source/Core/Token.nll"
				return "null";
			}

			case Type::TOKEN_KEYWORD_OVERRIDE:
			{
#line 153 "/home/cliffya/git/Lang/Source/Core/Token.nll"
				return "override";
			}

			case Type::TOKEN_KEYWORD_OWN:
			{
#line 154 "/home/cliffya/git/Lang/Source/Core/Token.nll"
				return "own";
			}

			case Type::TOKEN_KEYWORD_PRIVATE:
			{
#line 155 "/home/cliffya/git/Lang/Source/Core/Token.nll"
				return "private";
			}

			case Type::TOKEN_KEYWORD_PUBLIC:
			{
#line 156 "/home/cliffya/git/Lang/Source/Core/Token.nll"
				return "public";
			}

			case Type::TOKEN_KEYWORD_REF:
			{
#line 157 "/home/cliffya/git/Lang/Source/Core/Token.nll"
				return "ref";
			}

			case Type::TOKEN_KEYWORD_RETURN:
			{
#line 158 "/home/cliffya/git/Lang/Source/Core/Token.nll"
				return "return";
			}

			case Type::TOKEN_KEYWORD_STRING:
			{
#line 159 "/home/cliffya/git/Lang/Source/Core/Token.nll"
				return "string";
			}

			case Type::TOKEN_KEYWORD_SWITCH:
			{
#line 160 "/home/cliffya/git/Lang/Source/Core/Token.nll"
				return "switch";
			}

			case Type::TOKEN_KEYWORD_THIS:
			{
#line 161 "/home/cliffya/git/Lang/Source/Core/Token.nll"
				return "this";
			}

			case Type::TOKEN_KEYWORD_TRUE:
			{
#line 162 "/home/cliffya/git/Lang/Source/Core/Token.nll"
				return "true";
			}

			case Type::TOKEN_KEYWORD_TTHASH:
			{
#line 163 "/home/cliffya/git/Lang/Source/Core/Token.nll"
				return "tthash";
			}

			case Type::TOKEN_KEYWORD_UINT:
			{
#line 164 "/home/cliffya/git/Lang/Source/Core/Token.nll"
				return "uint";
			}

			case Type::TOKEN_KEYWORD_UINT16:
			{
#line 165 "/home/cliffya/git/Lang/Source/Core/Token.nll"
				return "Uint16";
			}

			case Type::TOKEN_KEYWORD_UINT32:
			{
#line 166 "/home/cliffya/git/Lang/Source/Core/Token.nll"
				return "Uint32";
			}

			case Type::TOKEN_KEYWORD_UINT64:
			{
#line 167 "/home/cliffya/git/Lang/Source/Core/Token.nll"
				return "Uint64";
			}

			case Type::TOKEN_KEYWORD_UINT8:
			{
#line 168 "/home/cliffya/git/Lang/Source/Core/Token.nll"
				return "Uint8";
			}

			case Type::TOKEN_KEYWORD_UNICHAR:
			{
#line 169 "/home/cliffya/git/Lang/Source/Core/Token.nll"
				return "UniChar";
			}

			case Type::TOKEN_KEYWORD_USING:
			{
#line 170 "/home/cliffya/git/Lang/Source/Core/Token.nll"
				return "using";
			}

			case Type::TOKEN_KEYWORD_VIRTUAL:
			{
#line 171 "/home/cliffya/git/Lang/Source/Core/Token.nll"
				return "virtual";
			}

			case Type::TOKEN_KEYWORD_VOID:
			{
#line 172 "/home/cliffya/git/Lang/Source/Core/Token.nll"
				return "void";
			}

			case Type::TOKEN_KEYWORD_VOIDPTR:
			{
#line 173 "/home/cliffya/git/Lang/Source/Core/Token.nll"
				return "voidptr";
			}

			case Type::TOKEN_KEYWORD_WHILE:
			{
#line 174 "/home/cliffya/git/Lang/Source/Core/Token.nll"
				return "while";
			}

			case Type::TOKEN_MINUS:
			{
#line 175 "/home/cliffya/git/Lang/Source/Core/Token.nll"
				return "-";
			}

			case Type::TOKEN_MINUS_MINUS:
			{
#line 176 "/home/cliffya/git/Lang/Source/Core/Token.nll"
				return "--";
			}

			case Type::TOKEN_MODULUS:
			{
#line 177 "/home/cliffya/git/Lang/Source/Core/Token.nll"
				return "%";
			}

			case Type::TOKEN_NEW_LINE:
			{
#line 178 "/home/cliffya/git/Lang/Source/Core/Token.nll"
				return "\n";
			}

			case Type::TOKEN_PARENTHESIS_LEFT:
			{
#line 179 "/home/cliffya/git/Lang/Source/Core/Token.nll"
				return "(";
			}

			case Type::TOKEN_PARENTHESIS_RIGHT:
			{
#line 180 "/home/cliffya/git/Lang/Source/Core/Token.nll"
				return ")";
			}

			case Type::TOKEN_PLUS:
			{
#line 181 "/home/cliffya/git/Lang/Source/Core/Token.nll"
				return "+";
			}

			case Type::TOKEN_PLUS_PLUS:
			{
#line 182 "/home/cliffya/git/Lang/Source/Core/Token.nll"
				return "++";
			}

			case Type::TOKEN_QUESTION_MARK:
			{
#line 183 "/home/cliffya/git/Lang/Source/Core/Token.nll"
				return "?";
			}

			case Type::TOKEN_SEMICOLON:
			{
#line 184 "/home/cliffya/git/Lang/Source/Core/Token.nll"
				return ";";
			}

			case Type::TOKEN_SPACE:
			{
#line 185 "/home/cliffya/git/Lang/Source/Core/Token.nll"
				return " ";
			}

			case Type::TOKEN_SQUARE_BRACKET_LEFT:
			{
#line 186 "/home/cliffya/git/Lang/Source/Core/Token.nll"
				return "[";
			}

			case Type::TOKEN_SQUARE_BRACKET_RIGHT:
			{
#line 187 "/home/cliffya/git/Lang/Source/Core/Token.nll"
				return "]";
			}

			case Type::TOKEN_STAR:
			{
#line 188 "/home/cliffya/git/Lang/Source/Core/Token.nll"
				return "*";
			}

			case Type::TOKEN_STAR_DOUBLE:
			{
#line 189 "/home/cliffya/git/Lang/Source/Core/Token.nll"
				return "**";
			}

			case Type::TOKEN_TAB:
			{
#line 190 "/home/cliffya/git/Lang/Source/Core/Token.nll"
				return "\t";
			}

			case Type::TOKEN_TILDE:
			{
#line 191 "/home/cliffya/git/Lang/Source/Core/Token.nll"
				return "~";
			}

			case Type::TOKEN_CHAR:
			{
#line 193 "/home/cliffya/git/Lang/Source/Core/Token.nll"
				return m_sValue->GetExternalString();
			}

			case Type::TOKEN_CHAR_UNTERMINATED:
			{
#line 194 "/home/cliffya/git/Lang/Source/Core/Token.nll"
				return m_sValue->GetExternalString();
			}

			case Type::TOKEN_IDENTIFIER:
			{
#line 195 "/home/cliffya/git/Lang/Source/Core/Token.nll"
				return m_sValue->GetExternalString();
			}

			case Type::TOKEN_NUMBER:
			{
#line 196 "/home/cliffya/git/Lang/Source/Core/Token.nll"
				return m_sValue->GetExternalString();
			}

			case Type::TOKEN_STRING:
			{
#line 197 "/home/cliffya/git/Lang/Source/Core/Token.nll"
				return m_sValue->GetExternalString();
			}

			case Type::TOKEN_STRING_UNTERMINATED:
			{
#line 198 "/home/cliffya/git/Lang/Source/Core/Token.nll"
				return m_sValue->GetExternalString();
			}

		}
#line 201 "/home/cliffya/git/Lang/Source/Core/Token.nll"
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
		NumbatLogic::Token* __3778724684 = pToken;
		pToken = 0;
#line 214 "/home/cliffya/git/Lang/Source/Core/Token.nll"
		return __3778724684;
	}

#line 3 "/home/cliffya/git/Lang/Source/Core/Token.nll"
	Token::Token()
	{
		m_eType = Type::TOKEN_ANGLE_BRACKET_LEFT;
		m_sFileName = 0;
		m_nLine = 0;
		m_nColumn = 0;
		m_sValue = 0;
	}

#line 3 "/home/cliffya/git/Lang/Source/Core/Token.nll"
	Token::~Token()
	{
		if (m_sValue) delete m_sValue;
	}

}

