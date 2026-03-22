#include "Test.hpp"
#include "../../../LangShared/Source/Console/CPP/Console.hpp"
#include "../Core/AST/AST.hpp"
#include "../../../LangShared/Transpiled/Vector/OwnedVector.hpp"
#include "../../../LangShared/Source/InternalString/CPP/InternalString.hpp"
#include "../Core/TokenContainer.hpp"
#include "../Core/OffsetDatum.hpp"
#include "../Core/OutputBuilder.hpp"

namespace NumbatLogic
{
	class Test;
	class Console;
	template <class T>
	class OwnedVector;
	class InternalString;
	class TokenContainer;
	class OffsetDatum;
	class AST;
	class OutputBuilder;
}
#line 0 "/home/cliffya/git/Lang/Source/Test/Test.nll"
namespace NumbatLogic
{
#line 3 "/home/cliffya/git/Lang/Source/Test/Test.nll"
#line 5 "/home/cliffya/git/Lang/Source/Test/Test.nll"
	void Test::Run(Vector<const char*>* sArgVector)
	{
		Console::Log("Tests!");
#line 10 "/home/cliffya/git/Lang/Source/Test/Test.nll"
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
#line 39 "/home/cliffya/git/Lang/Source/Test/Test.nll"
		FullCheck("Thing pThing = new Thing();", AST::Type::AST_VAR_DECL);
		FullCheck("int function() {return 0;}", AST::Type::AST_FUNCTION_DECL);
		FullCheck("string func(int a, int b) {}", AST::Type::AST_FUNCTION_DECL);
		FullCheck("class Test {\npublic int thing;\n}", AST::Type::AST_CLASS_DECL);
		FullCheck("class @Dummy() Test {\npublic int thing;\n}", AST::Type::AST_CLASS_DECL);
		FullCheck("class @Dummy() Test {\npublic int @Dummy() thing;\n}", AST::Type::AST_CLASS_DECL);
		FullCheck("class Test {\npublic int @Dummy() thing;\npublic int @Dummy() func() {return 1;}\n}", AST::Type::AST_CLASS_DECL);
		FullCheck("class Test:Base {\npublic int thing;\n}", AST::Type::AST_CLASS_DECL);
		FullCheck("class Test {\npublic int func() {return 1;} public int thing;\n}", AST::Type::AST_CLASS_DECL);
		FullCheck("class Test:Base {\npublic virtual int thing() {}\n}", AST::Type::AST_CLASS_DECL);
		FullCheck("int @Dummy(1, \"x\") function() {return 0;}", AST::Type::AST_FUNCTION_DECL);
		FullCheck("int @Dummy() i = abc();", AST::Type::AST_VAR_DECL);
		FullCheck("enum Type {A,B,C,}", AST::Type::AST_ENUM_DECL);
#line 53 "/home/cliffya/git/Lang/Source/Test/Test.nll"
		FullCheck("while (true) {}", AST::Type::AST_WHILE_STMT);
		FullCheck("zero == 0 || abc == '\\\\'", AST::Type::AST_OPERATOR_EXPR);
		FullCheck("if (zero == 0) {return 0;}", AST::Type::AST_IF_STMT);
		FullCheck("if (zero == 0 || abc == '\\\\') {return 0;}", AST::Type::AST_IF_STMT);
		FullCheck("if (a) {return 0;} else return b;", AST::Type::AST_IF_STMT);
		FullCheck("wub[43+1]", AST::Type::AST_ARRAY_LOOKUP);
		FullCheck("for (int i = 0; i < 10; i = i + 1) {return 0;}", AST::Type::AST_FOR_STMT);
#line 61 "/home/cliffya/git/Lang/Source/Test/Test.nll"
		FullCheck("sOut = sOut + this.pGenericTypeRefVector.Get(i).Stringify(eLanguage, 0);", AST::Type::AST_EXPRESSION_STMT);
		FullCheck("Vector<AST> pMemberVector = new Vector<AST>();", AST::Type::AST_VAR_DECL);
		FullCheck("Token::Type eType = bloop;", AST::Type::AST_VAR_DECL);
	}

#line 69 "/home/cliffya/git/Lang/Source/Test/Test.nll"
	void Test::FullCheck(const char* sInput, AST::Type eAstType)
	{
		OwnedVector<InternalString*>* sDefineVector = new OwnedVector<InternalString*>();
		TokenContainer* pTokenContainer = new TokenContainer();
		InternalString* sTest = new InternalString("test.nll");
		pTokenContainer->Tokenize(sInput, sTest, sDefineVector);
#line 76 "/home/cliffya/git/Lang/Source/Test/Test.nll"
		InternalString* sTokenized = new InternalString("");
#line 78 "/home/cliffya/git/Lang/Source/Test/Test.nll"
		pTokenContainer->Stringify(sTokenized);
		const char* sxTokenized = sTokenized->GetExternalString();
#line 81 "/home/cliffya/git/Lang/Source/Test/Test.nll"
		if (!sTokenized->IsEqual(sInput))
		{
			Console::Log("Initial tokenize failed!\n");
			Console::Log(sInput);
			Console::Log("\n->\n");
			Console::Log(sxTokenized);
			if (sDefineVector) delete sDefineVector;
			if (pTokenContainer) delete pTokenContainer;
			if (sTest) delete sTest;
			if (sTokenized) delete sTokenized;
#line 87 "/home/cliffya/git/Lang/Source/Test/Test.nll"
			return;
		}
#line 90 "/home/cliffya/git/Lang/Source/Test/Test.nll"
		pTokenContainer->StripWhitespace();
#line 92 "/home/cliffya/git/Lang/Source/Test/Test.nll"
		OffsetDatum* pOffsetDatum = OffsetDatum::Create(0);
#line 94 "/home/cliffya/git/Lang/Source/Test/Test.nll"
		AST* pAST = AST::CreateFromTokenContainer(pTokenContainer, pOffsetDatum);
#line 96 "/home/cliffya/git/Lang/Source/Test/Test.nll"
		if (pAST == 0)
		{
			Console::Log("  ** NO AST!");
			if (sDefineVector) delete sDefineVector;
			if (pTokenContainer) delete pTokenContainer;
			if (sTest) delete sTest;
			if (sTokenized) delete sTokenized;
			if (pOffsetDatum) delete pOffsetDatum;
			if (pAST) delete pAST;
#line 99 "/home/cliffya/git/Lang/Source/Test/Test.nll"
			return;
		}
#line 102 "/home/cliffya/git/Lang/Source/Test/Test.nll"
		if (pAST->m_eType != eAstType)
		{
			Console::Log("  ** AST TYPE MISMATCH!\n");
			Console::Log(sxTokenized);
#line 107 "/home/cliffya/git/Lang/Source/Test/Test.nll"
			Console::Log(" != ");
			if (sDefineVector) delete sDefineVector;
			if (pTokenContainer) delete pTokenContainer;
			if (sTest) delete sTest;
			if (sTokenized) delete sTokenized;
			if (pOffsetDatum) delete pOffsetDatum;
			if (pAST) delete pAST;
#line 109 "/home/cliffya/git/Lang/Source/Test/Test.nll"
			return;
		}
#line 112 "/home/cliffya/git/Lang/Source/Test/Test.nll"
		OutputBuilder* pOutputBuilder = new OutputBuilder();
		pAST->Stringify(AST::Language::NLL, AST::OutputFile::SOURCE, 0, pOutputBuilder);
		pOutputBuilder->m_sOut->Replace(" ", "");
		pOutputBuilder->m_sOut->Replace("\n", "");
		pOutputBuilder->m_sOut->Replace("\t", "");
#line 118 "/home/cliffya/git/Lang/Source/Test/Test.nll"
		sTokenized->Set("");
		pTokenContainer->Stringify(sTokenized);
		sxTokenized = sTokenized->GetExternalString();
#line 122 "/home/cliffya/git/Lang/Source/Test/Test.nll"
		if (!pOutputBuilder->m_sOut->IsEqual(sxTokenized))
		{
			Console::Log("Stringify failed!\n'");
			Console::Log(sxTokenized);
			Console::Log("'\n->\n'");
			Console::Log(pOutputBuilder->m_sOut->GetExternalString());
			Console::Log("'");
			if (sDefineVector) delete sDefineVector;
			if (pTokenContainer) delete pTokenContainer;
			if (sTest) delete sTest;
			if (sTokenized) delete sTokenized;
			if (pOffsetDatum) delete pOffsetDatum;
			if (pAST) delete pAST;
			if (pOutputBuilder) delete pOutputBuilder;
#line 129 "/home/cliffya/git/Lang/Source/Test/Test.nll"
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


int main(int argc, const char* argv[])
{
	NumbatLogic::Vector<const char*>* sArgVector = new NumbatLogic::Vector<const char*>();
	for (int i = 1; i < argc; i++)
		sArgVector->PushBack(argv[i]);

	NumbatLogic::Test::Run(sArgVector);

	delete sArgVector;
	return 0;
}
