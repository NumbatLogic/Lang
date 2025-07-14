#include "CLI.hpp"
#include "../../../LangShared/Console/CPP/Console.hpp"
#include "../../../LangShared/Vector/CPP/Vector.hpp"
#include "../../../LangShared/InternalString/CPP/InternalString.hpp"
#include "../Core/Project.hpp"
#include "../LangShared/Vector/OwnedVector.hpp"
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
	class InternalString;
	class Project;
	class Project;
	template <class T>
	class OwnedVector;
	class ExternalString;
	class AST;
	class File;
}
namespace NumbatLogic
{
	void CLI::Run(Vector<const char*>* sArgVector)
	{
		Console::Log("CLI");
		if (sArgVector->GetSize() % 2 != 0)
		{
			InternalString* sTemp = new InternalString("expected even number of args! Got ");
			sTemp->AppendInt(sArgVector->GetSize());
			Console::Log(sTemp->GetExternalString());
			if (sTemp) delete sTemp;
			return;
		}
		Project* pProject = new Project();
		InternalString* sAmalgamateFileName = 0;
		bool bOutputNLLDef = false;
		OwnedVector<InternalString*>* sAmalgamatedHPPAppend = new OwnedVector<InternalString*>();
		OwnedVector<InternalString*>* sAmalgamatedCPPPrepend = new OwnedVector<InternalString*>();
		OwnedVector<InternalString*>* sAmalgamatedCPPAppend = new OwnedVector<InternalString*>();
		OwnedVector<InternalString*>* sAmalgamatedCSAppend = new OwnedVector<InternalString*>();
		OwnedVector<InternalString*>* sDefineVector = new OwnedVector<InternalString*>();
		int i = 0;
		while (i < sArgVector->GetSize())
		{
			InternalString* sTemp = 0;
			const char* sxArg0 = sArgVector->Get(i);
			i++;
			const char* sxArg1 = sArgVector->Get(i);
			i++;
			if (ExternalString::Equal(sxArg0, "-d"))
			{
				sDefineVector->PushBack(new InternalString(sxArg1));
				if (sTemp) delete sTemp;
				continue;
			}
			if (ExternalString::Equal(sxArg0, "-f"))
			{
				sTemp = new InternalString("Recurse: ");
				sTemp->Append(sxArg1);
				Console::Log(sTemp->GetExternalString());
				pProject->AddDirectory(sxArg1, sDefineVector);
				if (sTemp) delete sTemp;
				continue;
			}
			if (ExternalString::Equal(sxArg0, "-fi"))
			{
				sTemp = new InternalString("File: ");
				sTemp->Append(sxArg1);
				Console::Log(sTemp->GetExternalString());
				pProject->AddFile(sxArg1, sDefineVector);
				if (sTemp) delete sTemp;
				continue;
			}
			if (ExternalString::Equal(sxArg0, "-a"))
			{
				sAmalgamateFileName = new InternalString(sxArg1);
				if (sTemp) delete sTemp;
				continue;
			}
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
					return;
				}
				bOutputNLLDef = true;
				if (sTemp) delete sTemp;
				continue;
			}
			if (ExternalString::Equal(sxArg0, "-ahppa"))
			{
				sAmalgamatedHPPAppend->PushBack(new InternalString(sxArg1));
				if (sTemp) delete sTemp;
				continue;
			}
			if (ExternalString::Equal(sxArg0, "-acppp"))
			{
				sAmalgamatedCPPPrepend->PushBack(new InternalString(sxArg1));
				if (sTemp) delete sTemp;
				continue;
			}
			if (ExternalString::Equal(sxArg0, "-acppa"))
			{
				sAmalgamatedCPPAppend->PushBack(new InternalString(sxArg1));
				if (sTemp) delete sTemp;
				continue;
			}
			if (ExternalString::Equal(sxArg0, "-acsa"))
			{
				sAmalgamatedCSAppend->PushBack(new InternalString(sxArg1));
				if (sTemp) delete sTemp;
				continue;
			}
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
			return;
		}
		if (sAmalgamateFileName != 0)
		{
			Console::Log("Amalgamate");
			pProject->Amalgamate(sAmalgamateFileName->GetExternalString());
		}
		Console::Log("Validate");
		pProject->FullValidate();
		Console::Log("Output CS");
		pProject->Output(AST::Language::CS, AST::OutputFile::SOURCE);
		if (sAmalgamateFileName != 0)
		{
			InternalString* sOutFileName = new InternalString(sAmalgamateFileName->GetExternalString());
			sOutFileName->Replace(".nll", ".cs");
			InternalString* sAppend = new InternalString("");
			for (int x = 0; x < sAmalgamatedCSAppend->GetSize(); x++)
			{
				InternalString* sInFileName = sAmalgamatedCSAppend->Get(x);
				InternalString* sInFile = File::GetContents(sInFileName->GetExternalString());
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
		Console::Log("Output HPP");
		pProject->Output(AST::Language::CPP, AST::OutputFile::HEADER);
		if (sAmalgamateFileName != 0)
		{
			InternalString* sOutFileName = new InternalString(sAmalgamateFileName->GetExternalString());
			sOutFileName->Replace(".nll", ".hpp");
			InternalString* sAppend = new InternalString("");
			for (int x = 0; x < sAmalgamatedHPPAppend->GetSize(); x++)
			{
				InternalString* sInFileName = sAmalgamatedHPPAppend->Get(x);
				InternalString* sInFile = File::GetContents(sInFileName->GetExternalString());
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
		if (sAmalgamateFileName != 0)
		{
			InternalString* sOutFileName = new InternalString(sAmalgamateFileName->GetExternalString());
			sOutFileName->Replace(".nll", ".cpp");
			InternalString* sPrepend = new InternalString("");
			InternalString* sAppend = new InternalString("");
			for (int x = 0; x < sAmalgamatedCPPPrepend->GetSize(); x++)
			{
				InternalString* sInFileName = sAmalgamatedCPPPrepend->Get(x);
				InternalString* sInFile = File::GetContents(sInFileName->GetExternalString());
				sInFile->Replace("#pragma once", "");
				sInFile->Replace("#include \"tinyxml2/tinyxml2.h\"", "");
				sInFile->Replace("#include \"miniz/miniz.h\"", "");
				sPrepend->AppendString(sInFile->GetExternalString());
				sPrepend->AppendString("\n\n");
				if (sInFile) delete sInFile;
			}
			for (int x = 0; x < sAmalgamatedCPPAppend->GetSize(); x++)
			{
				InternalString* sInFileName = sAmalgamatedCPPAppend->Get(x);
				InternalString* sInFile = File::GetContents(sInFileName->GetExternalString());
				sInFile->Replace("#include \"Assert.hpp\"", "");
				sInFile->Replace("#include \"../../Assert/CPP/Assert.hpp\"", "");
				sInFile->Replace("#include \"Blob.hpp\"", "");
				sInFile->Replace("#include \"../../Blob/CPP/Blob.hpp\"", "");
				sInFile->Replace("#include \"Console.hpp\"", "");
				sInFile->Replace("#include \"../../Console/CPP/Console.hpp\"", "");
				sInFile->Replace("#include \"ExternalString.hpp\"", "");
				sInFile->Replace("#include \"../../ExternalString/CPP/ExternalString.hpp\"", "");
				sInFile->Replace("#include \"InternalString.hpp\"", "");
				sInFile->Replace("#include \"../../InternalString/CPP/InternalString.hpp\"", "");
				sInFile->Replace("#include \"Utils.hpp\"", "");
				sInFile->Replace("#include \"../../Utils/CPP/Utils.hpp\"", "");
				sInFile->Replace("#include \"Vector.hpp\"", "");
				sInFile->Replace("#include \"../../Vector/CPP/Vector.hpp\"", "");
				sInFile->Replace("#include \"Xml.hpp\"", "");
				sInFile->Replace("#include \"../../Xml/CPP/Xml.hpp\"", "");
				sInFile->Replace("#include \"Zip.hpp\"", "");
				sInFile->Replace("#include \"../../Zip/CPP/Zip.hpp\"", "");
				sInFile->Replace("#include \"ZipWriter.hpp\"", "");
				sInFile->Replace("#include \"../../Zip/CPP/ZipWriter.hpp\"", "");
				sInFile->Replace("#include \"tinyxml2.h\"", "");
				sInFile->Replace("#include \"miniz.h\"", "");
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

