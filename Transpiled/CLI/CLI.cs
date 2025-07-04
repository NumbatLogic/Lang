namespace NumbatLogic
{
	class CLI
	{
		public static void Run(Vector<string> sArgVector)
		{
			Console.Log("CLI");
			if (sArgVector.GetSize() % 2 != 0)
			{
				InternalString sTemp = new InternalString("expected even number of args! Got ");
				sTemp.AppendInt(sArgVector.GetSize());
				Console.Log(sTemp.GetExternalString());
				return;
			}
			Project pProject = new Project();
			InternalString sAmalgamateFileName = null;
			bool bOutputNLLDef = false;
			OwnedVector<InternalString> sAmalgamatedHPPAppend = new OwnedVector<InternalString>();
			OwnedVector<InternalString> sAmalgamatedCPPPrepend = new OwnedVector<InternalString>();
			OwnedVector<InternalString> sAmalgamatedCPPAppend = new OwnedVector<InternalString>();
			OwnedVector<InternalString> sAmalgamatedCSAppend = new OwnedVector<InternalString>();
			OwnedVector<InternalString> sDefineVector = new OwnedVector<InternalString>();
			int i = 0;
			while (i < sArgVector.GetSize())
			{
				InternalString sTemp;
				string sxArg0 = sArgVector.Get(i);
				i++;
				string sxArg1 = sArgVector.Get(i);
				i++;
				if (ExternalString.Equal(sxArg0, "-d"))
				{
					sDefineVector.PushBack(new InternalString(sxArg1));
					continue;
				}
				if (ExternalString.Equal(sxArg0, "-f"))
				{
					sTemp = new InternalString("Recurse: ");
					sTemp.Append(sxArg1);
					Console.Log(sTemp.GetExternalString());
					pProject.AddDirectory(sxArg1, sDefineVector);
					continue;
				}
				if (ExternalString.Equal(sxArg0, "-fi"))
				{
					sTemp = new InternalString("File: ");
					sTemp.Append(sxArg1);
					Console.Log(sTemp.GetExternalString());
					pProject.AddFile(sxArg1, sDefineVector);
					continue;
				}
				if (ExternalString.Equal(sxArg0, "-a"))
				{
					sAmalgamateFileName = new InternalString(sxArg1);
					continue;
				}
				if (ExternalString.Equal(sxArg0, "--output-nll-def"))
				{
					if (!ExternalString.Equal(sxArg1, "true"))
					{
						Console.Log("if set, --output-nll must be true");
						return;
					}
					bOutputNLLDef = true;
					continue;
				}
				if (ExternalString.Equal(sxArg0, "-ahppa"))
				{
					sAmalgamatedHPPAppend.PushBack(new InternalString(sxArg1));
					continue;
				}
				if (ExternalString.Equal(sxArg0, "-acppp"))
				{
					sAmalgamatedCPPPrepend.PushBack(new InternalString(sxArg1));
					continue;
				}
				if (ExternalString.Equal(sxArg0, "-acppa"))
				{
					sAmalgamatedCPPAppend.PushBack(new InternalString(sxArg1));
					continue;
				}
				if (ExternalString.Equal(sxArg0, "-acsa"))
				{
					sAmalgamatedCSAppend.PushBack(new InternalString(sxArg1));
					continue;
				}
				sTemp = new InternalString("Unexpected arg: ");
				sTemp.Append(sxArg0);
				Console.Log(sTemp.GetExternalString());
				return;
			}
			if (sAmalgamateFileName != null)
			{
				Console.Log("Amalgamate");
				pProject.Amalgamate(sAmalgamateFileName.GetExternalString());
			}
			Console.Log("Validate");
			pProject.FullValidate();
			Console.Log("Output CS");
			pProject.Output(AST.Language.CS, AST.OutputFile.SOURCE);
			if (sAmalgamateFileName != null)
			{
				InternalString sOutFileName = new InternalString(sAmalgamateFileName.GetExternalString());
				sOutFileName.Replace(".nll", ".cs");
				InternalString sAppend = new InternalString("");
				for (int x = 0; x < sAmalgamatedCSAppend.GetSize(); x++)
				{
					InternalString sInFileName = sAmalgamatedCSAppend.Get(x);
					InternalString sInFile = File.GetContents(sInFileName.GetExternalString());
					sAppend.AppendString(sInFile.GetExternalString());
					sAppend.AppendString("\n\n");
				}
				InternalString sOutFile = File.GetContents(sOutFileName.GetExternalString());
				sOutFile.AppendString(sAppend.GetExternalString());
				File.PutContents(sOutFileName.GetExternalString(), sOutFile.GetExternalString());
			}
			Console.Log("Output HPP");
			pProject.Output(AST.Language.CPP, AST.OutputFile.HEADER);
			if (sAmalgamateFileName != null)
			{
				InternalString sOutFileName = new InternalString(sAmalgamateFileName.GetExternalString());
				sOutFileName.Replace(".nll", ".hpp");
				InternalString sAppend = new InternalString("");
				for (int x = 0; x < sAmalgamatedHPPAppend.GetSize(); x++)
				{
					InternalString sInFileName = sAmalgamatedHPPAppend.Get(x);
					InternalString sInFile = File.GetContents(sInFileName.GetExternalString());
					sAppend.AppendString(sInFile.GetExternalString());
					sAppend.AppendString("\n\n");
				}
				InternalString sOutFile = File.GetContents(sOutFileName.GetExternalString());
				sOutFile.AppendString(sAppend.GetExternalString());
				File.PutContents(sOutFileName.GetExternalString(), sOutFile.GetExternalString());
			}
			Console.Log("Output CPP");
			pProject.Output(AST.Language.CPP, AST.OutputFile.SOURCE);
			if (sAmalgamateFileName != null)
			{
				InternalString sOutFileName = new InternalString(sAmalgamateFileName.GetExternalString());
				sOutFileName.Replace(".nll", ".cpp");
				InternalString sPrepend = new InternalString("");
				InternalString sAppend = new InternalString("");
				for (int x = 0; x < sAmalgamatedCPPPrepend.GetSize(); x++)
				{
					InternalString sInFileName = sAmalgamatedCPPPrepend.Get(x);
					InternalString sInFile = File.GetContents(sInFileName.GetExternalString());
					sInFile.Replace("#pragma once", "");
					sInFile.Replace("#include \"tinyxml2/tinyxml2.h\"", "");
					sInFile.Replace("#include \"miniz/miniz.h\"", "");
					sPrepend.AppendString(sInFile.GetExternalString());
					sPrepend.AppendString("\n\n");
				}
				for (int x = 0; x < sAmalgamatedCPPAppend.GetSize(); x++)
				{
					InternalString sInFileName = sAmalgamatedCPPAppend.Get(x);
					InternalString sInFile = File.GetContents(sInFileName.GetExternalString());
					sInFile.Replace("#include \"Assert.hpp\"", "");
					sInFile.Replace("#include \"../../Assert/CPP/Assert.hpp\"", "");
					sInFile.Replace("#include \"Blob.hpp\"", "");
					sInFile.Replace("#include \"../../Blob/CPP/Blob.hpp\"", "");
					sInFile.Replace("#include \"Console.hpp\"", "");
					sInFile.Replace("#include \"../../Console/CPP/Console.hpp\"", "");
					sInFile.Replace("#include \"ExternalString.hpp\"", "");
					sInFile.Replace("#include \"../../ExternalString/CPP/ExternalString.hpp\"", "");
					sInFile.Replace("#include \"InternalString.hpp\"", "");
					sInFile.Replace("#include \"../../InternalString/CPP/InternalString.hpp\"", "");
					sInFile.Replace("#include \"Utils.hpp\"", "");
					sInFile.Replace("#include \"../../Utils/CPP/Utils.hpp\"", "");
					sInFile.Replace("#include \"Vector.hpp\"", "");
					sInFile.Replace("#include \"../../Vector/CPP/Vector.hpp\"", "");
					sInFile.Replace("#include \"Xml.hpp\"", "");
					sInFile.Replace("#include \"../../Xml/CPP/Xml.hpp\"", "");
					sInFile.Replace("#include \"Zip.hpp\"", "");
					sInFile.Replace("#include \"../../Zip/CPP/Zip.hpp\"", "");
					sInFile.Replace("#include \"ZipWriter.hpp\"", "");
					sInFile.Replace("#include \"../../Zip/CPP/ZipWriter.hpp\"", "");
					sInFile.Replace("#include \"tinyxml2.h\"", "");
					sInFile.Replace("#include \"miniz.h\"", "");
					sAppend.AppendString(sInFile.GetExternalString());
					sAppend.AppendString("\n\n");
				}
				InternalString sOutFile = File.GetContents(sOutFileName.GetExternalString());
				sOutFile.PrependString(sPrepend.GetExternalString());
				sOutFile.AppendString(sAppend.GetExternalString());
				File.PutContents(sOutFileName.GetExternalString(), sOutFile.GetExternalString());
			}
			if (bOutputNLLDef)
			{
				Console.Log("Output NLL DEF");
				pProject.Output(AST.Language.NLL_DEF, AST.OutputFile.SOURCE);
			}
		}

	}
}

