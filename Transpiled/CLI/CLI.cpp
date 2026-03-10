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
#line 7 "../../../Source/CLI/CLI.nll"
		Console::Log("CLI");
#line 9 "../../../Source/CLI/CLI.nll"
		if (sArgVector->GetSize() % 2 != 0)
		{
#line 11 "../../../Source/CLI/CLI.nll"
			InternalString* sTemp = new InternalString("expected even number of args! Got ");
#line 12 "../../../Source/CLI/CLI.nll"
			sTemp->AppendInt(sArgVector->GetSize());
#line 13 "../../../Source/CLI/CLI.nll"
			Console::Log(sTemp->GetExternalString());
			if (sTemp) delete sTemp;
#line 14 "../../../Source/CLI/CLI.nll"
			return;
		}
#line 17 "../../../Source/CLI/CLI.nll"
		Project* pProject = new Project();
#line 18 "../../../Source/CLI/CLI.nll"
		InternalString* sAmalgamateFileName = 0;
#line 19 "../../../Source/CLI/CLI.nll"
		bool bOutputNLLDef = false;
#line 21 "../../../Source/CLI/CLI.nll"
		OwnedVector<InternalString*>* sAmalgamatedHPPAppend = new OwnedVector<InternalString*>();
#line 22 "../../../Source/CLI/CLI.nll"
		OwnedVector<InternalString*>* sAmalgamatedCPPPrepend = new OwnedVector<InternalString*>();
#line 23 "../../../Source/CLI/CLI.nll"
		OwnedVector<InternalString*>* sAmalgamatedCPPAppend = new OwnedVector<InternalString*>();
#line 24 "../../../Source/CLI/CLI.nll"
		OwnedVector<InternalString*>* sAmalgamatedCSAppend = new OwnedVector<InternalString*>();
#line 25 "../../../Source/CLI/CLI.nll"
		OwnedVector<InternalString*>* sDefineVector = new OwnedVector<InternalString*>();
#line 27 "../../../Source/CLI/CLI.nll"
		int i = 0;
#line 28 "../../../Source/CLI/CLI.nll"
		while (i < sArgVector->GetSize())
		{
#line 30 "../../../Source/CLI/CLI.nll"
			InternalString* sTemp = 0;
#line 32 "../../../Source/CLI/CLI.nll"
			const char* sxArg0 = sArgVector->Get(i);
#line 33 "../../../Source/CLI/CLI.nll"
			i++;
#line 34 "../../../Source/CLI/CLI.nll"
			const char* sxArg1 = sArgVector->Get(i);
#line 35 "../../../Source/CLI/CLI.nll"
			i++;
#line 37 "../../../Source/CLI/CLI.nll"
			if (ExternalString::Equal(sxArg0, "-d"))
			{
#line 39 "../../../Source/CLI/CLI.nll"
				sDefineVector->PushBack(new InternalString(sxArg1));
				if (sTemp) delete sTemp;
#line 40 "../../../Source/CLI/CLI.nll"
				continue;
			}
#line 43 "../../../Source/CLI/CLI.nll"
			if (ExternalString::Equal(sxArg0, "-f"))
			{
#line 45 "../../../Source/CLI/CLI.nll"
				sTemp = new InternalString("Recurse: ");
#line 46 "../../../Source/CLI/CLI.nll"
				sTemp->Append(sxArg1);
#line 47 "../../../Source/CLI/CLI.nll"
				Console::Log(sTemp->GetExternalString());
#line 48 "../../../Source/CLI/CLI.nll"
				pProject->AddDirectory(sxArg1, sDefineVector);
				if (sTemp) delete sTemp;
#line 49 "../../../Source/CLI/CLI.nll"
				continue;
			}
#line 52 "../../../Source/CLI/CLI.nll"
			if (ExternalString::Equal(sxArg0, "-fi"))
			{
#line 54 "../../../Source/CLI/CLI.nll"
				sTemp = new InternalString("File: ");
#line 55 "../../../Source/CLI/CLI.nll"
				sTemp->Append(sxArg1);
#line 56 "../../../Source/CLI/CLI.nll"
				Console::Log(sTemp->GetExternalString());
#line 57 "../../../Source/CLI/CLI.nll"
				pProject->AddFile(sxArg1, sDefineVector);
				if (sTemp) delete sTemp;
#line 58 "../../../Source/CLI/CLI.nll"
				continue;
			}
#line 61 "../../../Source/CLI/CLI.nll"
			if (ExternalString::Equal(sxArg0, "-a"))
			{
#line 63 "../../../Source/CLI/CLI.nll"
				sAmalgamateFileName = new InternalString(sxArg1);
				if (sTemp) delete sTemp;
#line 64 "../../../Source/CLI/CLI.nll"
				continue;
			}
#line 67 "../../../Source/CLI/CLI.nll"
			if (ExternalString::Equal(sxArg0, "--output-nll-def"))
			{
#line 69 "../../../Source/CLI/CLI.nll"
				if (!ExternalString::Equal(sxArg1, "true"))
				{
#line 71 "../../../Source/CLI/CLI.nll"
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
#line 81 "../../../Source/CLI/CLI.nll"
				sAmalgamatedHPPAppend->PushBack(new InternalString(sxArg1));
				if (sTemp) delete sTemp;
#line 82 "../../../Source/CLI/CLI.nll"
				continue;
			}
#line 85 "../../../Source/CLI/CLI.nll"
			if (ExternalString::Equal(sxArg0, "-acppp"))
			{
#line 87 "../../../Source/CLI/CLI.nll"
				sAmalgamatedCPPPrepend->PushBack(new InternalString(sxArg1));
				if (sTemp) delete sTemp;
#line 88 "../../../Source/CLI/CLI.nll"
				continue;
			}
#line 91 "../../../Source/CLI/CLI.nll"
			if (ExternalString::Equal(sxArg0, "-acppa"))
			{
#line 93 "../../../Source/CLI/CLI.nll"
				sAmalgamatedCPPAppend->PushBack(new InternalString(sxArg1));
				if (sTemp) delete sTemp;
#line 94 "../../../Source/CLI/CLI.nll"
				continue;
			}
#line 97 "../../../Source/CLI/CLI.nll"
			if (ExternalString::Equal(sxArg0, "-acsa"))
			{
#line 99 "../../../Source/CLI/CLI.nll"
				sAmalgamatedCSAppend->PushBack(new InternalString(sxArg1));
				if (sTemp) delete sTemp;
#line 100 "../../../Source/CLI/CLI.nll"
				continue;
			}
#line 103 "../../../Source/CLI/CLI.nll"
			sTemp = new InternalString("Unexpected arg: ");
#line 104 "../../../Source/CLI/CLI.nll"
			sTemp->Append(sxArg0);
#line 105 "../../../Source/CLI/CLI.nll"
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
#line 111 "../../../Source/CLI/CLI.nll"
			Console::Log("Amalgamate");
#line 112 "../../../Source/CLI/CLI.nll"
			pProject->Amalgamate(sAmalgamateFileName->GetExternalString());
		}
#line 115 "../../../Source/CLI/CLI.nll"
		Console::Log("Validate");
#line 116 "../../../Source/CLI/CLI.nll"
		pProject->FullValidate();
#line 118 "../../../Source/CLI/CLI.nll"
		Console::Log("Output CS");
#line 119 "../../../Source/CLI/CLI.nll"
		pProject->Output(AST::Language::CS, AST::OutputFile::SOURCE);
#line 120 "../../../Source/CLI/CLI.nll"
		if (sAmalgamateFileName != 0)
		{
#line 122 "../../../Source/CLI/CLI.nll"
			InternalString* sOutFileName = new InternalString(sAmalgamateFileName->GetExternalString());
#line 123 "../../../Source/CLI/CLI.nll"
			sOutFileName->Replace(".nll", ".cs");
#line 125 "../../../Source/CLI/CLI.nll"
			InternalString* sAppend = new InternalString("");
#line 127 "../../../Source/CLI/CLI.nll"
			for (int x = 0; x < sAmalgamatedCSAppend->GetSize(); x++)
			{
#line 129 "../../../Source/CLI/CLI.nll"
				InternalString* sInFileName = sAmalgamatedCSAppend->Get(x);
#line 130 "../../../Source/CLI/CLI.nll"
				InternalString* sInFile = File::GetContents(sInFileName->GetExternalString());
#line 132 "../../../Source/CLI/CLI.nll"
				sAppend->AppendString(sInFile->GetExternalString());
#line 133 "../../../Source/CLI/CLI.nll"
				sAppend->AppendString("\n\n");
				if (sInFile) delete sInFile;
			}
#line 136 "../../../Source/CLI/CLI.nll"
			InternalString* sOutFile = File::GetContents(sOutFileName->GetExternalString());
#line 137 "../../../Source/CLI/CLI.nll"
			sOutFile->AppendString(sAppend->GetExternalString());
#line 138 "../../../Source/CLI/CLI.nll"
			File::PutContents(sOutFileName->GetExternalString(), sOutFile->GetExternalString());
			if (sOutFileName) delete sOutFileName;
			if (sAppend) delete sAppend;
			if (sOutFile) delete sOutFile;
		}
#line 142 "../../../Source/CLI/CLI.nll"
		Console::Log("Output HPP");
#line 143 "../../../Source/CLI/CLI.nll"
		pProject->Output(AST::Language::CPP, AST::OutputFile::HEADER);
#line 144 "../../../Source/CLI/CLI.nll"
		if (sAmalgamateFileName != 0)
		{
#line 146 "../../../Source/CLI/CLI.nll"
			InternalString* sOutFileName = new InternalString(sAmalgamateFileName->GetExternalString());
#line 147 "../../../Source/CLI/CLI.nll"
			sOutFileName->Replace(".nll", ".hpp");
#line 149 "../../../Source/CLI/CLI.nll"
			InternalString* sAppend = new InternalString("");
#line 151 "../../../Source/CLI/CLI.nll"
			for (int x = 0; x < sAmalgamatedHPPAppend->GetSize(); x++)
			{
#line 153 "../../../Source/CLI/CLI.nll"
				InternalString* sInFileName = sAmalgamatedHPPAppend->Get(x);
#line 154 "../../../Source/CLI/CLI.nll"
				InternalString* sInFile = File::GetContents(sInFileName->GetExternalString());
#line 156 "../../../Source/CLI/CLI.nll"
				sAppend->AppendString(sInFile->GetExternalString());
#line 157 "../../../Source/CLI/CLI.nll"
				sAppend->AppendString("\n\n");
				if (sInFile) delete sInFile;
			}
#line 160 "../../../Source/CLI/CLI.nll"
			InternalString* sOutFile = File::GetContents(sOutFileName->GetExternalString());
#line 161 "../../../Source/CLI/CLI.nll"
			sOutFile->AppendString(sAppend->GetExternalString());
#line 162 "../../../Source/CLI/CLI.nll"
			File::PutContents(sOutFileName->GetExternalString(), sOutFile->GetExternalString());
			if (sOutFileName) delete sOutFileName;
			if (sAppend) delete sAppend;
			if (sOutFile) delete sOutFile;
		}
#line 167 "../../../Source/CLI/CLI.nll"
		Console::Log("Output CPP");
#line 168 "../../../Source/CLI/CLI.nll"
		pProject->Output(AST::Language::CPP, AST::OutputFile::SOURCE);
#line 170 "../../../Source/CLI/CLI.nll"
		if (sAmalgamateFileName != 0)
		{
#line 172 "../../../Source/CLI/CLI.nll"
			InternalString* sOutFileName = new InternalString(sAmalgamateFileName->GetExternalString());
#line 173 "../../../Source/CLI/CLI.nll"
			sOutFileName->Replace(".nll", ".cpp");
#line 175 "../../../Source/CLI/CLI.nll"
			InternalString* sPrepend = new InternalString("");
#line 176 "../../../Source/CLI/CLI.nll"
			InternalString* sAppend = new InternalString("");
#line 178 "../../../Source/CLI/CLI.nll"
			for (int x = 0; x < sAmalgamatedCPPPrepend->GetSize(); x++)
			{
#line 180 "../../../Source/CLI/CLI.nll"
				InternalString* sInFileName = sAmalgamatedCPPPrepend->Get(x);
#line 181 "../../../Source/CLI/CLI.nll"
				InternalString* sInFile = File::GetContents(sInFileName->GetExternalString());
#line 184 "../../../Source/CLI/CLI.nll"
				sInFile->Replace("#pragma once", "");
#line 185 "../../../Source/CLI/CLI.nll"
				sInFile->Replace("#include \"tinyxml2/tinyxml2.h\"", "");
#line 186 "../../../Source/CLI/CLI.nll"
				sInFile->Replace("#include \"miniz/miniz.h\"", "");
#line 188 "../../../Source/CLI/CLI.nll"
				sPrepend->AppendString(sInFile->GetExternalString());
#line 189 "../../../Source/CLI/CLI.nll"
				sPrepend->AppendString("\n\n");
				if (sInFile) delete sInFile;
			}
#line 192 "../../../Source/CLI/CLI.nll"
			for (int x = 0; x < sAmalgamatedCPPAppend->GetSize(); x++)
			{
#line 194 "../../../Source/CLI/CLI.nll"
				InternalString* sInFileName = sAmalgamatedCPPAppend->Get(x);
#line 195 "../../../Source/CLI/CLI.nll"
				InternalString* sInFile = File::GetContents(sInFileName->GetExternalString());
#line 198 "../../../Source/CLI/CLI.nll"
				sInFile->Replace("#include \"Assert.hpp\"", "");
#line 199 "../../../Source/CLI/CLI.nll"
				sInFile->Replace("#include \"../../Assert/CPP/Assert.hpp\"", "");
#line 201 "../../../Source/CLI/CLI.nll"
				sInFile->Replace("#include \"Blob.hpp\"", "");
#line 202 "../../../Source/CLI/CLI.nll"
				sInFile->Replace("#include \"../../Blob/CPP/Blob.hpp\"", "");
#line 204 "../../../Source/CLI/CLI.nll"
				sInFile->Replace("#include \"Console.hpp\"", "");
#line 205 "../../../Source/CLI/CLI.nll"
				sInFile->Replace("#include \"../../Console/CPP/Console.hpp\"", "");
#line 207 "../../../Source/CLI/CLI.nll"
				sInFile->Replace("#include \"ExternalString.hpp\"", "");
#line 208 "../../../Source/CLI/CLI.nll"
				sInFile->Replace("#include \"../../ExternalString/CPP/ExternalString.hpp\"", "");
#line 210 "../../../Source/CLI/CLI.nll"
				sInFile->Replace("#include \"InternalString.hpp\"", "");
#line 211 "../../../Source/CLI/CLI.nll"
				sInFile->Replace("#include \"../../InternalString/CPP/InternalString.hpp\"", "");
#line 213 "../../../Source/CLI/CLI.nll"
				sInFile->Replace("#include \"Utils.hpp\"", "");
#line 214 "../../../Source/CLI/CLI.nll"
				sInFile->Replace("#include \"../../Utils/CPP/Utils.hpp\"", "");
#line 216 "../../../Source/CLI/CLI.nll"
				sInFile->Replace("#include \"Vector.hpp\"", "");
#line 217 "../../../Source/CLI/CLI.nll"
				sInFile->Replace("#include \"../../Vector/CPP/Vector.hpp\"", "");
#line 221 "../../../Source/CLI/CLI.nll"
				sInFile->Replace("#include \"Xml.hpp\"", "");
#line 222 "../../../Source/CLI/CLI.nll"
				sInFile->Replace("#include \"../../Xml/CPP/Xml.hpp\"", "");
#line 224 "../../../Source/CLI/CLI.nll"
				sInFile->Replace("#include \"Zip.hpp\"", "");
#line 225 "../../../Source/CLI/CLI.nll"
				sInFile->Replace("#include \"../../Zip/CPP/Zip.hpp\"", "");
#line 227 "../../../Source/CLI/CLI.nll"
				sInFile->Replace("#include \"ZipWriter.hpp\"", "");
#line 228 "../../../Source/CLI/CLI.nll"
				sInFile->Replace("#include \"../../Zip/CPP/ZipWriter.hpp\"", "");
#line 230 "../../../Source/CLI/CLI.nll"
				sInFile->Replace("#include \"tinyxml2.h\"", "");
#line 231 "../../../Source/CLI/CLI.nll"
				sInFile->Replace("#include \"miniz.h\"", "");
#line 233 "../../../Source/CLI/CLI.nll"
				sAppend->AppendString(sInFile->GetExternalString());
#line 234 "../../../Source/CLI/CLI.nll"
				sAppend->AppendString("\n\n");
				if (sInFile) delete sInFile;
			}
#line 237 "../../../Source/CLI/CLI.nll"
			InternalString* sOutFile = File::GetContents(sOutFileName->GetExternalString());
#line 238 "../../../Source/CLI/CLI.nll"
			sOutFile->PrependString(sPrepend->GetExternalString());
#line 239 "../../../Source/CLI/CLI.nll"
			sOutFile->AppendString(sAppend->GetExternalString());
#line 240 "../../../Source/CLI/CLI.nll"
			File::PutContents(sOutFileName->GetExternalString(), sOutFile->GetExternalString());
			if (sOutFileName) delete sOutFileName;
			if (sPrepend) delete sPrepend;
			if (sAppend) delete sAppend;
			if (sOutFile) delete sOutFile;
		}
#line 244 "../../../Source/CLI/CLI.nll"
		if (bOutputNLLDef)
		{
#line 246 "../../../Source/CLI/CLI.nll"
			Console::Log("Output NLL DEF");
#line 247 "../../../Source/CLI/CLI.nll"
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

