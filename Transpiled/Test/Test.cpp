#include "Test.hpp"
#include "../../../LangShared/Console/CPP/Console.hpp"
#include "../Core/AST/AST.hpp"
#include "PointerTest.hpp"
#include "../../../LangShared/Transpiled/Vector/OwnedVector.hpp"
#include "../../../LangShared/InternalString/CPP/InternalString.hpp"
#include "../Core/TokenContainer.hpp"
#include "../Core/OffsetDatum.hpp"
#include "../Core/OutputBuilder.hpp"

namespace NumbatLogic
{
	class Test;
	class Console;
	class PointerTest;
	template <class T>
	class OwnedVector;
	class InternalString;
	class TokenContainer;
	class OffsetDatum;
	class AST;
	class OutputBuilder;
}
#line 0 "../../../Source/Test/Test.nll"
namespace NumbatLogic
{
#line 3 "../../../Source/Test/Test.nll"
#line 12 "../../../Source/Test/Test.nll"
	void Test::Run()
	{
#line 14 "../../../Source/Test/Test.nll"
		Console::Log("Tests!");
#line 17 "../../../Source/Test/Test.nll"
		FullCheck("return;", AST::Type::AST_RETURN_STMT);
#line 18 "../../../Source/Test/Test.nll"
		FullCheck("'s'", AST::Type::AST_CHAR);
#line 19 "../../../Source/Test/Test.nll"
		FullCheck("return 'b';", AST::Type::AST_RETURN_STMT);
#line 20 "../../../Source/Test/Test.nll"
		FullCheck("\"banana\"", AST::Type::AST_STRING);
#line 21 "../../../Source/Test/Test.nll"
		FullCheck("1", AST::Type::AST_NUMBER);
#line 22 "../../../Source/Test/Test.nll"
		FullCheck("return \"hello\";", AST::Type::AST_RETURN_STMT);
#line 23 "../../../Source/Test/Test.nll"
		FullCheck("{{return 1;}}", AST::Type::AST_SCOPE);
#line 24 "../../../Source/Test/Test.nll"
		FullCheck("33;", AST::Type::AST_EXPRESSION_STMT);
#line 25 "../../../Source/Test/Test.nll"
		FullCheck("3+3", AST::Type::AST_OPERATOR_EXPR);
#line 26 "../../../Source/Test/Test.nll"
		FullCheck("true || false", AST::Type::AST_OPERATOR_EXPR);
#line 27 "../../../Source/Test/Test.nll"
		FullCheck("fun()", AST::Type::AST_FUNCTION_CALL);
#line 28 "../../../Source/Test/Test.nll"
		FullCheck("call(thing(), banana())", AST::Type::AST_FUNCTION_CALL);
#line 29 "../../../Source/Test/Test.nll"
		FullCheck("a", AST::Type::AST_IDENTIFIER);
#line 30 "../../../Source/Test/Test.nll"
		FullCheck("a.b()", AST::Type::AST_OPERATOR_EXPR);
#line 31 "../../../Source/Test/Test.nll"
		FullCheck("a().b()", AST::Type::AST_OPERATOR_EXPR);
#line 32 "../../../Source/Test/Test.nll"
		FullCheck("-3", AST::Type::AST_UNARY);
#line 33 "../../../Source/Test/Test.nll"
		FullCheck("!!3", AST::Type::AST_UNARY);
#line 34 "../../../Source/Test/Test.nll"
		FullCheck("ObjectType i;", AST::Type::AST_VAR_DECL);
#line 35 "../../../Source/Test/Test.nll"
		FullCheck("ObjectType i = abc();", AST::Type::AST_VAR_DECL);
#line 36 "../../../Source/Test/Test.nll"
		FullCheck("int i = abc(call(thing(), banana(), 22, \"word\"));", AST::Type::AST_VAR_DECL);
#line 37 "../../../Source/Test/Test.nll"
		FullCheck("(abc())", AST::Type::AST_PAREN);
#line 38 "../../../Source/Test/Test.nll"
		FullCheck("ObjectType i = abc();", AST::Type::AST_VAR_DECL);
#line 39 "../../../Source/Test/Test.nll"
		FullCheck("ObjectType i = (abc());", AST::Type::AST_VAR_DECL);
#line 40 "../../../Source/Test/Test.nll"
		FullCheck("a<b> pThing;", AST::Type::AST_VAR_DECL);
#line 41 "../../../Source/Test/Test.nll"
		FullCheck("List<int> ff;", AST::Type::AST_VAR_DECL);
#line 42 "../../../Source/Test/Test.nll"
		FullCheck("ObjectType i = (abc());", AST::Type::AST_VAR_DECL);
#line 43 "../../../Source/Test/Test.nll"
		FullCheck("new Thing()", AST::Type::AST_NEW_EXP);
#line 44 "../../../Source/Test/Test.nll"
		FullCheck("new Thing();", AST::Type::AST_EXPRESSION_STMT);
#line 46 "../../../Source/Test/Test.nll"
		FullCheck("Thing pThing = new Thing();", AST::Type::AST_VAR_DECL);
#line 47 "../../../Source/Test/Test.nll"
		FullCheck("int function() {return 0;}", AST::Type::AST_FUNCTION_DECL);
#line 48 "../../../Source/Test/Test.nll"
		FullCheck("string func(int a, int b) {}", AST::Type::AST_FUNCTION_DECL);
#line 49 "../../../Source/Test/Test.nll"
		FullCheck("class Test {\npublic int thing;\n}", AST::Type::AST_CLASS_DECL);
#line 50 "../../../Source/Test/Test.nll"
		FullCheck("class Test:Base {\npublic int thing;\n}", AST::Type::AST_CLASS_DECL);
#line 51 "../../../Source/Test/Test.nll"
		FullCheck("class Test {\npublic int func() {return 1;} public int thing;\n}", AST::Type::AST_CLASS_DECL);
#line 52 "../../../Source/Test/Test.nll"
		FullCheck("class Test:Base {\npublic virtual int thing() {}\n}", AST::Type::AST_CLASS_DECL);
#line 53 "../../../Source/Test/Test.nll"
		FullCheck("enum Type {A,B,C,}", AST::Type::AST_ENUM_DECL);
#line 55 "../../../Source/Test/Test.nll"
		FullCheck("while (true) {}", AST::Type::AST_WHILE_STMT);
#line 56 "../../../Source/Test/Test.nll"
		FullCheck("zero == 0 || abc == '\\\\'", AST::Type::AST_OPERATOR_EXPR);
#line 57 "../../../Source/Test/Test.nll"
		FullCheck("if (zero == 0) {return 0;}", AST::Type::AST_IF_STMT);
#line 58 "../../../Source/Test/Test.nll"
		FullCheck("if (zero == 0 || abc == '\\\\') {return 0;}", AST::Type::AST_IF_STMT);
#line 59 "../../../Source/Test/Test.nll"
		FullCheck("if (a) {return 0;} else return b;", AST::Type::AST_IF_STMT);
#line 60 "../../../Source/Test/Test.nll"
		FullCheck("wub[43+1]", AST::Type::AST_ARRAY_LOOKUP);
#line 61 "../../../Source/Test/Test.nll"
		FullCheck("for (int i = 0; i < 10; i = i + 1) {return 0;}", AST::Type::AST_FOR_STMT);
#line 63 "../../../Source/Test/Test.nll"
		FullCheck("sOut = sOut + this.pGenericTypeRefVector.Get(i).Stringify(eLanguage, 0);", AST::Type::AST_EXPRESSION_STMT);
#line 64 "../../../Source/Test/Test.nll"
		FullCheck("Vector<AST> pMemberVector = new Vector<AST>();", AST::Type::AST_VAR_DECL);
#line 65 "../../../Source/Test/Test.nll"
		FullCheck("Token::Type eType = bloop;", AST::Type::AST_VAR_DECL);
#line 67 "../../../Source/Test/Test.nll"
		PointerTest::Run();
	}

#line 73 "../../../Source/Test/Test.nll"
	void Test::FullCheck(const char* sInput, AST::Type eAstType)
	{
		OwnedVector<InternalString*>* sDefineVector = new OwnedVector<InternalString*>();
		TokenContainer* pTokenContainer = new TokenContainer();
		InternalString* sTest = new InternalString("test.nll");
#line 78 "../../../Source/Test/Test.nll"
		pTokenContainer->Tokenize(sInput, sTest, sDefineVector);
		InternalString* sTokenized = new InternalString("");
#line 82 "../../../Source/Test/Test.nll"
		pTokenContainer->Stringify(sTokenized);
		const char* sxTokenized = sTokenized->GetExternalString();
#line 85 "../../../Source/Test/Test.nll"
		if (!sTokenized->IsEqual(sInput))
		{
#line 87 "../../../Source/Test/Test.nll"
			Console::Log("Initial tokenize failed!\n");
#line 88 "../../../Source/Test/Test.nll"
			Console::Log(sInput);
#line 89 "../../../Source/Test/Test.nll"
			Console::Log("\n->\n");
#line 90 "../../../Source/Test/Test.nll"
			Console::Log(sxTokenized);
			if (sDefineVector) delete sDefineVector;
			if (pTokenContainer) delete pTokenContainer;
			if (sTest) delete sTest;
			if (sTokenized) delete sTokenized;
#line 91 "../../../Source/Test/Test.nll"
			return;
		}
#line 94 "../../../Source/Test/Test.nll"
		pTokenContainer->StripWhitespace();
		OffsetDatum* pOffsetDatum = OffsetDatum::Create(0);
		AST* pAST = AST::CreateFromTokenContainer(pTokenContainer, pOffsetDatum);
#line 100 "../../../Source/Test/Test.nll"
		if (pAST == 0)
		{
#line 102 "../../../Source/Test/Test.nll"
			Console::Log("  ** NO AST!");
			if (sDefineVector) delete sDefineVector;
			if (pTokenContainer) delete pTokenContainer;
			if (sTest) delete sTest;
			if (sTokenized) delete sTokenized;
			if (pOffsetDatum) delete pOffsetDatum;
			if (pAST) delete pAST;
#line 103 "../../../Source/Test/Test.nll"
			return;
		}
#line 106 "../../../Source/Test/Test.nll"
		if (pAST->m_eType != eAstType)
		{
#line 108 "../../../Source/Test/Test.nll"
			Console::Log("  ** AST TYPE MISMATCH!\n");
#line 109 "../../../Source/Test/Test.nll"
			Console::Log(sxTokenized);
#line 111 "../../../Source/Test/Test.nll"
			Console::Log(" != ");
			if (sDefineVector) delete sDefineVector;
			if (pTokenContainer) delete pTokenContainer;
			if (sTest) delete sTest;
			if (sTokenized) delete sTokenized;
			if (pOffsetDatum) delete pOffsetDatum;
			if (pAST) delete pAST;
#line 113 "../../../Source/Test/Test.nll"
			return;
		}
		OutputBuilder* pOutputBuilder = new OutputBuilder();
#line 117 "../../../Source/Test/Test.nll"
		pAST->Stringify(AST::Language::NLL, AST::OutputFile::SOURCE, 0, pOutputBuilder);
#line 118 "../../../Source/Test/Test.nll"
		pOutputBuilder->m_sOut->Replace(" ", "");
#line 119 "../../../Source/Test/Test.nll"
		pOutputBuilder->m_sOut->Replace("\n", "");
#line 120 "../../../Source/Test/Test.nll"
		pOutputBuilder->m_sOut->Replace("\t", "");
#line 122 "../../../Source/Test/Test.nll"
		sTokenized->Set("");
#line 123 "../../../Source/Test/Test.nll"
		pTokenContainer->Stringify(sTokenized);
#line 124 "../../../Source/Test/Test.nll"
		sxTokenized = sTokenized->GetExternalString();
#line 126 "../../../Source/Test/Test.nll"
		if (!pOutputBuilder->m_sOut->IsEqual(sxTokenized))
		{
#line 128 "../../../Source/Test/Test.nll"
			Console::Log("Stringify failed!\n'");
#line 129 "../../../Source/Test/Test.nll"
			Console::Log(sxTokenized);
#line 130 "../../../Source/Test/Test.nll"
			Console::Log("'\n->\n'");
#line 131 "../../../Source/Test/Test.nll"
			Console::Log(pOutputBuilder->m_sOut->GetExternalString());
#line 132 "../../../Source/Test/Test.nll"
			Console::Log("'");
			if (sDefineVector) delete sDefineVector;
			if (pTokenContainer) delete pTokenContainer;
			if (sTest) delete sTest;
			if (sTokenized) delete sTokenized;
			if (pOffsetDatum) delete pOffsetDatum;
			if (pAST) delete pAST;
			if (pOutputBuilder) delete pOutputBuilder;
#line 133 "../../../Source/Test/Test.nll"
			return;
		}
		if (sDefineVector) delete sDefineVector;
		if (pTokenContainer) delete pTokenContainer;
		if (sTest) delete sTest;
		if (sTokenized) delete sTokenized;
		if (pOffsetDatum) delete pOffsetDatum;
		if (pAST) delete pAST;
		if (pOutputBuilder) delete pOutputBuilder;
	}

}

