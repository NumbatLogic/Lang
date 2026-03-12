#include "CLI.hpp"
#include "../../../LangShared/Console/CPP/Console.hpp"
#include "../../../LangShared/Vector/CPP/Vector.hpp"
#include "../../../LangShared/InternalString/CPP/InternalString.hpp"
#include "../Core/Project.hpp"
#include "../../../LangShared/Transpiled/Vector/OwnedVector.hpp"
#include "../../../LangShared/ExternalString/CPP/ExternalString.hpp"
#include "../Core/AST/AST.hpp"
#include "../../../LangShared/File/CPP/File.hpp"

namespace NumbatLogic
{
	class CLI;
	class Console;
	template <class T>
	class Vector;
	class InternalString;
	class Project;
	template <class T>
	class OwnedVector;
	class ExternalString;
	class AST;
	class File;
}
#line 0 "../../../Source/CLI/CLI.nll"
namespace NumbatLogic
{
#line 3 "../../../Source/CLI/CLI.nll"
#line 5 "../../../Source/CLI/CLI.nll"
	void CLI::Run(Vector<const char*>* sArgVector)
	{
		Console::Log("CLI");
#line 9 "../../../Source/CLI/CLI.nll"
		if (sArgVector->GetSize() % 2 != 0)
		{
			InternalString* sTemp = new InternalString("expected even number of args! Got ");
			sTemp->AppendInt(sArgVector->GetSize());
			Console::Log(sTemp->GetExternalString());
			if (sTemp) delete sTemp;
#line 14 "../../../Source/CLI/CLI.nll"
			return;
		}
#line 17 "../../../Source/CLI/CLI.nll"
		Project* pProject = new Project();
		InternalString* sAmalgamateFileName = 0;
		bool bOutputNLLDef = false;
#line 21 "../../../Source/CLI/CLI.nll"
		OwnedVector<InternalString*>* sAmalgamatedHPPAppend = new OwnedVector<InternalString*>();
		OwnedVector<InternalString*>* sAmalgamatedCPPPrepend = new OwnedVector<InternalString*>();
		OwnedVector<InternalString*>* sAmalgamatedCPPAppend = new OwnedVector<InternalString*>();
		OwnedVector<InternalString*>* sAmalgamatedCSAppend = new OwnedVector<InternalString*>();
		OwnedVector<InternalString*>* sDefineVector = new OwnedVector<InternalString*>();
#line 27 "../../../Source/CLI/CLI.nll"
		int i = 0;
		while (i < sArgVector->GetSize())
		{
			InternalString* sTemp = 0;
#line 32 "../../../Source/CLI/CLI.nll"
			const char* sxArg0 = sArgVector->Get(i);
			i++;
			const char* sxArg1 = sArgVector->Get(i);
			i++;
#line 37 "../../../Source/CLI/CLI.nll"
			if (ExternalString::Equal(sxArg0, "-d"))
			{
				sDefineVector->PushBack(new InternalString(sxArg1));
				if (sTemp) delete sTemp;
#line 40 "../../../Source/CLI/CLI.nll"
				continue;
			}
#line 43 "../../../Source/CLI/CLI.nll"
			if (ExternalString::Equal(sxArg0, "-f"))
			{
				sTemp = new InternalString("Recurse: ");
				sTemp->Append(sxArg1);
				Console::Log(sTemp->GetExternalString());
				pProject->AddDirectory(sxArg1, sDefineVector);
				if (sTemp) delete sTemp;
#line 49 "../../../Source/CLI/CLI.nll"
				continue;
			}
#line 52 "../../../Source/CLI/CLI.nll"
			if (ExternalString::Equal(sxArg0, "-fi"))
			{
				sTemp = new InternalString("File: ");
				sTemp->Append(sxArg1);
				Console::Log(sTemp->GetExternalString());
				pProject->AddFile(sxArg1, sDefineVector);
				if (sTemp) delete sTemp;
#line 58 "../../../Source/CLI/CLI.nll"
				continue;
			}
#line 61 "../../../Source/CLI/CLI.nll"
			if (ExternalString::Equal(sxArg0, "-a"))
			{
				sAmalgamateFileName = new InternalString(sxArg1);
				if (sTemp) delete sTemp;
#line 64 "../../../Source/CLI/CLI.nll"
				continue;
			}
#line 67 "../../../Source/CLI/CLI.nll"
			if (ExternalString::Equal(sxArg0, "--output-nll-def"))
			{
				if (!ExternalString::Equal(sxArg1, "true"))
				{
					Console::Log("if set, --output-nll must be true");
					if (sTemp) delete sTemp;
					if (pProject) delete pProject;
					if (sAmalgamateFileName) delete sAmalgamateFileName;
					if (sAmalgamatedHPPAppend) delete sAmalgamatedHPPAppend;
					if (sAmalgamatedCPPPrepend) delete sAmalgamatedCPPPrepend;
					if (sAmalgamatedCPPAppend) delete sAmalgamatedCPPAppend;
					if (sAmalgamatedCSAppend) delete sAmalgamatedCSAppend;
					if (sDefineVector) delete sDefineVector;
#line 72 "../../../Source/CLI/CLI.nll"
					return;
				}
#line 75 "../../../Source/CLI/CLI.nll"
				bOutputNLLDef = true;
				if (sTemp) delete sTemp;
#line 76 "../../../Source/CLI/CLI.nll"
				continue;
			}
#line 79 "../../../Source/CLI/CLI.nll"
			if (ExternalString::Equal(sxArg0, "-ahppa"))
			{
				sAmalgamatedHPPAppend->PushBack(new InternalString(sxArg1));
				if (sTemp) delete sTemp;
#line 82 "../../../Source/CLI/CLI.nll"
				continue;
			}
#line 85 "../../../Source/CLI/CLI.nll"
			if (ExternalString::Equal(sxArg0, "-acppp"))
			{
				sAmalgamatedCPPPrepend->PushBack(new InternalString(sxArg1));
				if (sTemp) delete sTemp;
#line 88 "../../../Source/CLI/CLI.nll"
				continue;
			}
#line 91 "../../../Source/CLI/CLI.nll"
			if (ExternalString::Equal(sxArg0, "-acppa"))
			{
				sAmalgamatedCPPAppend->PushBack(new InternalString(sxArg1));
				if (sTemp) delete sTemp;
#line 94 "../../../Source/CLI/CLI.nll"
				continue;
			}
#line 97 "../../../Source/CLI/CLI.nll"
			if (ExternalString::Equal(sxArg0, "-acsa"))
			{
				sAmalgamatedCSAppend->PushBack(new InternalString(sxArg1));
				if (sTemp) delete sTemp;
#line 100 "../../../Source/CLI/CLI.nll"
				continue;
			}
#line 103 "../../../Source/CLI/CLI.nll"
			sTemp = new InternalString("Unexpected arg: ");
			sTemp->Append(sxArg0);
			Console::Log(sTemp->GetExternalString());
			if (sTemp) delete sTemp;
			if (pProject) delete pProject;
			if (sAmalgamateFileName) delete sAmalgamateFileName;
			if (sAmalgamatedHPPAppend) delete sAmalgamatedHPPAppend;
			if (sAmalgamatedCPPPrepend) delete sAmalgamatedCPPPrepend;
			if (sAmalgamatedCPPAppend) delete sAmalgamatedCPPAppend;
			if (sAmalgamatedCSAppend) delete sAmalgamatedCSAppend;
			if (sDefineVector) delete sDefineVector;
#line 106 "../../../Source/CLI/CLI.nll"
			return;
		}
#line 109 "../../../Source/CLI/CLI.nll"
		if (sAmalgamateFileName != 0)
		{
			Console::Log("Amalgamate");
			pProject->Amalgamate(sAmalgamateFileName->GetExternalString());
		}
#line 115 "../../../Source/CLI/CLI.nll"
		Console::Log("Validate");
		pProject->FullValidate();
#line 118 "../../../Source/CLI/CLI.nll"
		Console::Log("Output CS");
		pProject->Output(AST::Language::CS, AST::OutputFile::SOURCE);
		if (sAmalgamateFileName != 0)
		{
			InternalString* sOutFileName = new InternalString(sAmalgamateFileName->GetExternalString());
			sOutFileName->Replace(".nll", ".cs");
#line 125 "../../../Source/CLI/CLI.nll"
			InternalString* sAppend = new InternalString("");
#line 127 "../../../Source/CLI/CLI.nll"
			for (int x = 0; x < sAmalgamatedCSAppend->GetSize(); x++)
			{
				InternalString* sInFileName = sAmalgamatedCSAppend->Get(x);
				InternalString* sInFile = File::GetContents(sInFileName->GetExternalString());
#line 132 "../../../Source/CLI/CLI.nll"
				sAppend->AppendString(sInFile->GetExternalString());
				sAppend->AppendString("\n\n");
				if (sInFile) delete sInFile;
			}
			InternalString* sOutFile = File::GetContents(sOutFileName->GetExternalString());
			sOutFile->AppendString(sAppend->GetExternalString());
			File::PutContents(sOutFileName->GetExternalString(), sOutFile->GetExternalString());
			if (sOutFileName) delete sOutFileName;
			if (sAppend) delete sAppend;
			if (sOutFile) delete sOutFile;
		}
#line 142 "../../../Source/CLI/CLI.nll"
		Console::Log("Output HPP");
		pProject->Output(AST::Language::CPP, AST::OutputFile::HEADER);
		if (sAmalgamateFileName != 0)
		{
			InternalString* sOutFileName = new InternalString(sAmalgamateFileName->GetExternalString());
			sOutFileName->Replace(".nll", ".hpp");
#line 149 "../../../Source/CLI/CLI.nll"
			InternalString* sAppend = new InternalString("");
#line 151 "../../../Source/CLI/CLI.nll"
			for (int x = 0; x < sAmalgamatedHPPAppend->GetSize(); x++)
			{
				InternalString* sInFileName = sAmalgamatedHPPAppend->Get(x);
				InternalString* sInFile = File::GetContents(sInFileName->GetExternalString());
#line 156 "../../../Source/CLI/CLI.nll"
				sAppend->AppendString(sInFile->GetExternalString());
				sAppend->AppendString("\n\n");
				if (sInFile) delete sInFile;
			}
			InternalString* sOutFile = File::GetContents(sOutFileName->GetExternalString());
			sOutFile->AppendString(sAppend->GetExternalString());
			File::PutContents(sOutFileName->GetExternalString(), sOutFile->GetExternalString());
			if (sOutFileName) delete sOutFileName;
			if (sAppend) delete sAppend;
			if (sOutFile) delete sOutFile;
		}
		Console::Log("Output CPP");
		pProject->Output(AST::Language::CPP, AST::OutputFile::SOURCE);
#line 170 "../../../Source/CLI/CLI.nll"
		if (sAmalgamateFileName != 0)
		{
			InternalString* sOutFileName = new InternalString(sAmalgamateFileName->GetExternalString());
			sOutFileName->Replace(".nll", ".cpp");
#line 175 "../../../Source/CLI/CLI.nll"
			InternalString* sPrepend = new InternalString("");
			InternalString* sAppend = new InternalString("");
#line 178 "../../../Source/CLI/CLI.nll"
			for (int x = 0; x < sAmalgamatedCPPPrepend->GetSize(); x++)
			{
				InternalString* sInFileName = sAmalgamatedCPPPrepend->Get(x);
				InternalString* sInFile = File::GetContents(sInFileName->GetExternalString());
#line 184 "../../../Source/CLI/CLI.nll"
				sInFile->Replace("#pragma once", "");
				sInFile->Replace("#include \"tinyxml2/tinyxml2.h\"", "");
				sInFile->Replace("#include \"miniz/miniz.h\"", "");
#line 188 "../../../Source/CLI/CLI.nll"
				sPrepend->AppendString(sInFile->GetExternalString());
				sPrepend->AppendString("\n\n");
				if (sInFile) delete sInFile;
			}
			for (int x = 0; x < sAmalgamatedCPPAppend->GetSize(); x++)
			{
				InternalString* sInFileName = sAmalgamatedCPPAppend->Get(x);
				InternalString* sInFile = File::GetContents(sInFileName->GetExternalString());
#line 198 "../../../Source/CLI/CLI.nll"
				sInFile->Replace("#include \"Assert.hpp\"", "");
				sInFile->Replace("#include \"../../Assert/CPP/Assert.hpp\"", "");
#line 201 "../../../Source/CLI/CLI.nll"
				sInFile->Replace("#include \"Blob.hpp\"", "");
				sInFile->Replace("#include \"../../Blob/CPP/Blob.hpp\"", "");
#line 204 "../../../Source/CLI/CLI.nll"
				sInFile->Replace("#include \"Console.hpp\"", "");
				sInFile->Replace("#include \"../../Console/CPP/Console.hpp\"", "");
#line 207 "../../../Source/CLI/CLI.nll"
				sInFile->Replace("#include \"ExternalString.hpp\"", "");
				sInFile->Replace("#include \"../../ExternalString/CPP/ExternalString.hpp\"", "");
#line 210 "../../../Source/CLI/CLI.nll"
				sInFile->Replace("#include \"InternalString.hpp\"", "");
				sInFile->Replace("#include \"../../InternalString/CPP/InternalString.hpp\"", "");
#line 213 "../../../Source/CLI/CLI.nll"
				sInFile->Replace("#include \"Utils.hpp\"", "");
				sInFile->Replace("#include \"../../Utils/CPP/Utils.hpp\"", "");
#line 216 "../../../Source/CLI/CLI.nll"
				sInFile->Replace("#include \"Vector.hpp\"", "");
				sInFile->Replace("#include \"../../Vector/CPP/Vector.hpp\"", "");
#line 221 "../../../Source/CLI/CLI.nll"
				sInFile->Replace("#include \"Xml.hpp\"", "");
				sInFile->Replace("#include \"../../Xml/CPP/Xml.hpp\"", "");
#line 224 "../../../Source/CLI/CLI.nll"
				sInFile->Replace("#include \"Zip.hpp\"", "");
				sInFile->Replace("#include \"../../Zip/CPP/Zip.hpp\"", "");
#line 227 "../../../Source/CLI/CLI.nll"
				sInFile->Replace("#include \"ZipWriter.hpp\"", "");
				sInFile->Replace("#include \"../../Zip/CPP/ZipWriter.hpp\"", "");
#line 230 "../../../Source/CLI/CLI.nll"
				sInFile->Replace("#include \"tinyxml2.h\"", "");
				sInFile->Replace("#include \"miniz.h\"", "");
#line 233 "../../../Source/CLI/CLI.nll"
				sAppend->AppendString(sInFile->GetExternalString());
				sAppend->AppendString("\n\n");
				if (sInFile) delete sInFile;
			}
			InternalString* sOutFile = File::GetContents(sOutFileName->GetExternalString());
			sOutFile->PrependString(sPrepend->GetExternalString());
			sOutFile->AppendString(sAppend->GetExternalString());
			File::PutContents(sOutFileName->GetExternalString(), sOutFile->GetExternalString());
			if (sOutFileName) delete sOutFileName;
			if (sPrepend) delete sPrepend;
			if (sAppend) delete sAppend;
			if (sOutFile) delete sOutFile;
		}
#line 244 "../../../Source/CLI/CLI.nll"
		if (bOutputNLLDef)
		{
			Console::Log("Output NLL DEF");
			pProject->Output(AST::Language::NLL_DEF, AST::OutputFile::SOURCE);
		}
		if (pProject) delete pProject;
		if (sAmalgamateFileName) delete sAmalgamateFileName;
		if (sAmalgamatedHPPAppend) delete sAmalgamatedHPPAppend;
		if (sAmalgamatedCPPPrepend) delete sAmalgamatedCPPPrepend;
		if (sAmalgamatedCPPAppend) delete sAmalgamatedCPPAppend;
		if (sAmalgamatedCSAppend) delete sAmalgamatedCSAppend;
		if (sDefineVector) delete sDefineVector;
	}

}

