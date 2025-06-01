#include "Test.hpp"
#include "../../Shared/CPP/Console.hpp"
#include "../Core/AST/AST.hpp"
#include "PointerTest.hpp"
#include "../Shared/OwnedVector.hpp"
#include "../../Shared/CPP/InternalString.hpp"
#include "../Core/TokenContainer.hpp"
#include "../Core/OffsetDatum.hpp"

namespace NumberDuck
{
	namespace Secret
	{
		class InternalString;
		class TokenContainer;
		class OffsetDatum;
		class AST;
	}
}
namespace NumberDuck
{
	namespace Secret
	{
		void Test::Run()
		{
			Console::Log("Tests!");
			FullCheck("return;", AST::Type::AST_RETURN_STMT);
			FullCheck("'s'", AST::Type::AST_CHAR);
			FullCheck("return 'b';", AST::Type::AST_RETURN_STMT);
			FullCheck("\"banana\"", AST::Type::AST_STRING);
			FullCheck("1", AST::Type::AST_NUMBER);
			FullCheck("return \"hello\";", AST::Type::AST_RETURN_STMT);
			FullCheck("{{return 1;}}", AST::Type::AST_SCOPE);
			FullCheck("33;", AST::Type::AST_EXPRESSION_STMT);
			FullCheck("3+3", AST::Type::AST_OPERATOR_EXPR);
			FullCheck("true || false", AST::Type::AST_OPERATOR_EXPR);
			FullCheck("fun()", AST::Type::AST_FUNCTION_CALL);
			FullCheck("call(thing(), banana())", AST::Type::AST_FUNCTION_CALL);
			FullCheck("a", AST::Type::AST_IDENTIFIER);
			FullCheck("a.b()", AST::Type::AST_OPERATOR_EXPR);
			FullCheck("a().b()", AST::Type::AST_OPERATOR_EXPR);
			FullCheck("-3", AST::Type::AST_UNARY);
			FullCheck("!!3", AST::Type::AST_UNARY);
			FullCheck("ObjectType i;", AST::Type::AST_VAR_DECL);
			FullCheck("ObjectType i = abc();", AST::Type::AST_VAR_DECL);
			FullCheck("int i = abc(call(thing(), banana(), 22, \"word\"));", AST::Type::AST_VAR_DECL);
			FullCheck("(abc())", AST::Type::AST_PAREN);
			FullCheck("ObjectType i = abc();", AST::Type::AST_VAR_DECL);
			FullCheck("ObjectType i = (abc());", AST::Type::AST_VAR_DECL);
			FullCheck("a<b> pThing;", AST::Type::AST_VAR_DECL);
			FullCheck("List<int> ff;", AST::Type::AST_VAR_DECL);
			FullCheck("ObjectType i = (abc());", AST::Type::AST_VAR_DECL);
			FullCheck("new Thing()", AST::Type::AST_NEW_EXP);
			FullCheck("new Thing();", AST::Type::AST_EXPRESSION_STMT);
			FullCheck("Thing pThing = new Thing();", AST::Type::AST_VAR_DECL);
			FullCheck("int function() {return 0;}", AST::Type::AST_FUNCTION_DECL);
			FullCheck("string func(int a, int b) {}", AST::Type::AST_FUNCTION_DECL);
			FullCheck("class Test {\npublic int thing;\n}", AST::Type::AST_CLASS_DECL);
			FullCheck("class Test:Base {\npublic int thing;\n}", AST::Type::AST_CLASS_DECL);
			FullCheck("class Test {\npublic int func() {return 1;} public int thing;\n}", AST::Type::AST_CLASS_DECL);
			FullCheck("class Test:Base {\npublic virtual int thing() {}\n}", AST::Type::AST_CLASS_DECL);
			FullCheck("enum Type {A,B,C,}", AST::Type::AST_ENUM_DECL);
			FullCheck("while (true) {}", AST::Type::AST_WHILE_STMT);
			FullCheck("zero == 0 || abc == '\\\\'", AST::Type::AST_OPERATOR_EXPR);
			FullCheck("if (zero == 0) {return 0;}", AST::Type::AST_IF_STMT);
			FullCheck("if (zero == 0 || abc == '\\\\') {return 0;}", AST::Type::AST_IF_STMT);
			FullCheck("if (a) {return 0;} else return b;", AST::Type::AST_IF_STMT);
			FullCheck("wub[43+1]", AST::Type::AST_ARRAY_LOOKUP);
			FullCheck("for (int i = 0; i < 10; i = i + 1) {return 0;}", AST::Type::AST_FOR_STMT);
			FullCheck("sOut = sOut + this.pGenericTypeRefVector.Get(i).Stringify(eLanguage, 0);", AST::Type::AST_EXPRESSION_STMT);
			FullCheck("Vector<AST> pMemberVector = new Vector<AST>();", AST::Type::AST_VAR_DECL);
			FullCheck("Token::Type eType = bloop;", AST::Type::AST_VAR_DECL);
			PointerTest::Run();
		}

		void Test::FullCheck(const char* sInput, AST::Type eAstType)
		{
			OwnedVector<InternalString*>* sDefineVector = new OwnedVector<InternalString*>();
			TokenContainer* pTokenContainer = new TokenContainer();
			InternalString* sTest = new InternalString("test.nll");
			pTokenContainer->Tokenize(sInput, sTest, sDefineVector);
			InternalString* sTokenized = new InternalString("");
			pTokenContainer->Stringify(sTokenized);
			const char* sxTokenized = sTokenized->GetExternalString();
			if (!sTokenized->IsEqual(sInput))
			{
				Console::Log("Initial tokenize failed!\n");
				Console::Log(sInput);
				Console::Log("\n->\n");
				Console::Log(sxTokenized);
				{
					if (sDefineVector) delete sDefineVector;
					if (pTokenContainer) delete pTokenContainer;
					if (sTest) delete sTest;
					if (sTokenized) delete sTokenized;
					return;
				}
			}
			pTokenContainer->StripWhitespace();
			OffsetDatum* pOffsetDatum = OffsetDatum::Create(0);
			AST* pAST = AST::CreateFromTokenContainer(pTokenContainer, pOffsetDatum);
			if (pAST == 0)
			{
				Console::Log("  ** NO AST!");
				{
					if (sDefineVector) delete sDefineVector;
					if (pTokenContainer) delete pTokenContainer;
					if (sTest) delete sTest;
					if (sTokenized) delete sTokenized;
					if (pOffsetDatum) delete pOffsetDatum;
					if (pAST) delete pAST;
					return;
				}
			}
			if (pAST->m_eType != eAstType)
			{
				Console::Log("  ** AST TYPE MISMATCH!\n");
				Console::Log(sxTokenized);
				Console::Log(" != ");
				{
					if (sDefineVector) delete sDefineVector;
					if (pTokenContainer) delete pTokenContainer;
					if (sTest) delete sTest;
					if (sTokenized) delete sTokenized;
					if (pOffsetDatum) delete pOffsetDatum;
					if (pAST) delete pAST;
					return;
				}
			}
			InternalString* sOut = new InternalString("");
			pAST->Stringify(AST::Language::NLL, AST::OutputFile::SOURCE, 0, sOut);
			sOut->Replace(" ", "");
			sOut->Replace("\n", "");
			sOut->Replace("\t", "");
			sTokenized->Set("");
			pTokenContainer->Stringify(sTokenized);
			sxTokenized = sTokenized->GetExternalString();
			if (!sOut->IsEqual(sxTokenized))
			{
				Console::Log("Stringify failed!\n'");
				Console::Log(sxTokenized);
				Console::Log("'\n->\n'");
				Console::Log(sOut->GetExternalString());
				Console::Log("'");
				{
					if (sDefineVector) delete sDefineVector;
					if (pTokenContainer) delete pTokenContainer;
					if (sTest) delete sTest;
					if (sTokenized) delete sTokenized;
					if (pOffsetDatum) delete pOffsetDatum;
					if (pAST) delete pAST;
					if (sOut) delete sOut;
					return;
				}
			}
			if (sDefineVector) delete sDefineVector;
			if (pTokenContainer) delete pTokenContainer;
			if (sTest) delete sTest;
			if (sTokenized) delete sTokenized;
			if (pOffsetDatum) delete pOffsetDatum;
			if (pAST) delete pAST;
			if (sOut) delete sOut;
		}

	}
}

