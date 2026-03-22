#line 1 "/home/cliffya/git/Lang/Source/CLI/CLI.nll"
namespace NumbatLogic
{
	class CLI
	{
		public static void Run(Vector<string> sArgVector)
		{
			Console.Log("CLI");
#line 9 "/home/cliffya/git/Lang/Source/CLI/CLI.nll"
			if (sArgVector.GetSize() % 2 != 0)
			{
				InternalString sTemp = new InternalString("expected even number of args! Got ");
				sTemp.AppendInt(sArgVector.GetSize());
				Console.Log(sTemp.GetExternalString());
				return;
			}
#line 17 "/home/cliffya/git/Lang/Source/CLI/CLI.nll"
			Project pProject = new Project();
			InternalString sAmalgamateFileName = null;
			bool bOutputNLLDef = false;
#line 21 "/home/cliffya/git/Lang/Source/CLI/CLI.nll"
			OwnedVector<InternalString> sAmalgamatedHPPAppend = new OwnedVector<InternalString>();
			OwnedVector<InternalString> sAmalgamatedCPPPrepend = new OwnedVector<InternalString>();
			OwnedVector<InternalString> sAmalgamatedCPPAppend = new OwnedVector<InternalString>();
			OwnedVector<InternalString> sAmalgamatedCSAppend = new OwnedVector<InternalString>();
			OwnedVector<InternalString> sDefineVector = new OwnedVector<InternalString>();
#line 27 "/home/cliffya/git/Lang/Source/CLI/CLI.nll"
			int i = 0;
			while (i < sArgVector.GetSize())
			{
				InternalString sTemp;
#line 32 "/home/cliffya/git/Lang/Source/CLI/CLI.nll"
				string sxArg0 = sArgVector.Get(i);
				i++;
				string sxArg1 = sArgVector.Get(i);
				i++;
#line 37 "/home/cliffya/git/Lang/Source/CLI/CLI.nll"
				if (ExternalString.Equal(sxArg0, "-d"))
				{
					sDefineVector.PushBack(new InternalString(sxArg1));
					continue;
				}
#line 43 "/home/cliffya/git/Lang/Source/CLI/CLI.nll"
				if (ExternalString.Equal(sxArg0, "-f"))
				{
					sTemp = new InternalString("Recurse: ");
					sTemp.Append(sxArg1);
					Console.Log(sTemp.GetExternalString());
					if (!pProject.AddDirectory(sxArg1, sDefineVector))
					{
						Console.Log("Error: Directory not found:");
						Console.Log(sxArg1);
						return;
					}
					continue;
				}
#line 57 "/home/cliffya/git/Lang/Source/CLI/CLI.nll"
				if (ExternalString.Equal(sxArg0, "-fi"))
				{
					sTemp = new InternalString("File: ");
					sTemp.Append(sxArg1);
					Console.Log(sTemp.GetExternalString());
					pProject.AddFile(sxArg1, sDefineVector);
					continue;
				}
#line 66 "/home/cliffya/git/Lang/Source/CLI/CLI.nll"
				if (ExternalString.Equal(sxArg0, "-a"))
				{
					sAmalgamateFileName = new InternalString(sxArg1);
					continue;
				}
#line 72 "/home/cliffya/git/Lang/Source/CLI/CLI.nll"
				if (ExternalString.Equal(sxArg0, "--output-nll-def"))
				{
					if (!ExternalString.Equal(sxArg1, "true"))
					{
						Console.Log("if set, --output-nll must be true");
						return;
					}
#line 80 "/home/cliffya/git/Lang/Source/CLI/CLI.nll"
					bOutputNLLDef = true;
					continue;
				}
#line 84 "/home/cliffya/git/Lang/Source/CLI/CLI.nll"
				if (ExternalString.Equal(sxArg0, "-ahppa"))
				{
					sAmalgamatedHPPAppend.PushBack(new InternalString(sxArg1));
					continue;
				}
#line 90 "/home/cliffya/git/Lang/Source/CLI/CLI.nll"
				if (ExternalString.Equal(sxArg0, "-acppp"))
				{
					sAmalgamatedCPPPrepend.PushBack(new InternalString(sxArg1));
					continue;
				}
#line 96 "/home/cliffya/git/Lang/Source/CLI/CLI.nll"
				if (ExternalString.Equal(sxArg0, "-acppa"))
				{
					sAmalgamatedCPPAppend.PushBack(new InternalString(sxArg1));
					continue;
				}
#line 102 "/home/cliffya/git/Lang/Source/CLI/CLI.nll"
				if (ExternalString.Equal(sxArg0, "-acsa"))
				{
					sAmalgamatedCSAppend.PushBack(new InternalString(sxArg1));
					continue;
				}
#line 108 "/home/cliffya/git/Lang/Source/CLI/CLI.nll"
				sTemp = new InternalString("Unexpected arg: ");
				sTemp.Append(sxArg0);
				Console.Log(sTemp.GetExternalString());
				return;
			}
#line 114 "/home/cliffya/git/Lang/Source/CLI/CLI.nll"
			if (sAmalgamateFileName != null)
			{
				Console.Log("Amalgamate");
				pProject.Amalgamate(sAmalgamateFileName.GetExternalString());
			}
#line 120 "/home/cliffya/git/Lang/Source/CLI/CLI.nll"
			Console.Log("Validate");
			pProject.FullValidate();
#line 123 "/home/cliffya/git/Lang/Source/CLI/CLI.nll"
			Console.Log("Output CS");
			pProject.Output(AST.Language.CS, AST.OutputFile.SOURCE);
			if (sAmalgamateFileName != null)
			{
				InternalString sOutFileName = new InternalString(sAmalgamateFileName.GetExternalString());
				sOutFileName.Replace(".nll", ".cs");
#line 130 "/home/cliffya/git/Lang/Source/CLI/CLI.nll"
				InternalString sAppend = new InternalString("");
#line 132 "/home/cliffya/git/Lang/Source/CLI/CLI.nll"
				for (int x = 0; x < sAmalgamatedCSAppend.GetSize(); x++)
				{
					InternalString sInFileName = sAmalgamatedCSAppend.Get(x);
					InternalString sInFile = File.GetContents(sInFileName.GetExternalString());
#line 137 "/home/cliffya/git/Lang/Source/CLI/CLI.nll"
					sAppend.AppendString(sInFile.GetExternalString());
					sAppend.AppendString("\n\n");
				}
#line 141 "/home/cliffya/git/Lang/Source/CLI/CLI.nll"
				InternalString sOutFile = File.GetContents(sOutFileName.GetExternalString());
				sOutFile.AppendString(sAppend.GetExternalString());
				File.PutContents(sOutFileName.GetExternalString(), sOutFile.GetExternalString());
			}
#line 147 "/home/cliffya/git/Lang/Source/CLI/CLI.nll"
			Console.Log("Output HPP");
			pProject.Output(AST.Language.CPP, AST.OutputFile.HEADER);
			if (sAmalgamateFileName != null)
			{
				InternalString sOutFileName = new InternalString(sAmalgamateFileName.GetExternalString());
				sOutFileName.Replace(".nll", ".hpp");
#line 154 "/home/cliffya/git/Lang/Source/CLI/CLI.nll"
				InternalString sAppend = new InternalString("");
#line 156 "/home/cliffya/git/Lang/Source/CLI/CLI.nll"
				for (int x = 0; x < sAmalgamatedHPPAppend.GetSize(); x++)
				{
					InternalString sInFileName = sAmalgamatedHPPAppend.Get(x);
					InternalString sInFile = File.GetContents(sInFileName.GetExternalString());
#line 161 "/home/cliffya/git/Lang/Source/CLI/CLI.nll"
					sAppend.AppendString(sInFile.GetExternalString());
					sAppend.AppendString("\n\n");
				}
#line 165 "/home/cliffya/git/Lang/Source/CLI/CLI.nll"
				InternalString sOutFile = File.GetContents(sOutFileName.GetExternalString());
				sOutFile.AppendString(sAppend.GetExternalString());
				File.PutContents(sOutFileName.GetExternalString(), sOutFile.GetExternalString());
			}
#line 172 "/home/cliffya/git/Lang/Source/CLI/CLI.nll"
			Console.Log("Output CPP");
			pProject.Output(AST.Language.CPP, AST.OutputFile.SOURCE);
#line 175 "/home/cliffya/git/Lang/Source/CLI/CLI.nll"
			if (sAmalgamateFileName != null)
			{
				InternalString sOutFileName = new InternalString(sAmalgamateFileName.GetExternalString());
				sOutFileName.Replace(".nll", ".cpp");
#line 180 "/home/cliffya/git/Lang/Source/CLI/CLI.nll"
				InternalString sPrepend = new InternalString("");
				InternalString sAppend = new InternalString("");
#line 183 "/home/cliffya/git/Lang/Source/CLI/CLI.nll"
				for (int x = 0; x < sAmalgamatedCPPPrepend.GetSize(); x++)
				{
					InternalString sInFileName = sAmalgamatedCPPPrepend.Get(x);
					InternalString sInFile = File.GetContents(sInFileName.GetExternalString());
#line 189 "/home/cliffya/git/Lang/Source/CLI/CLI.nll"
					sInFile.Replace("#pragma once", "");
					sInFile.Replace("#include \"tinyxml2/tinyxml2.h\"", "");
					sInFile.Replace("#include \"miniz/miniz.h\"", "");
#line 193 "/home/cliffya/git/Lang/Source/CLI/CLI.nll"
					sPrepend.AppendString(sInFile.GetExternalString());
					sPrepend.AppendString("\n\n");
				}
#line 197 "/home/cliffya/git/Lang/Source/CLI/CLI.nll"
				for (int x = 0; x < sAmalgamatedCPPAppend.GetSize(); x++)
				{
					InternalString sInFileName = sAmalgamatedCPPAppend.Get(x);
					InternalString sInFile = File.GetContents(sInFileName.GetExternalString());
#line 203 "/home/cliffya/git/Lang/Source/CLI/CLI.nll"
					sInFile.Replace("#include \"Assert.hpp\"", "");
					sInFile.Replace("#include \"../../Assert/CPP/Assert.hpp\"", "");
#line 206 "/home/cliffya/git/Lang/Source/CLI/CLI.nll"
					sInFile.Replace("#include \"Blob.hpp\"", "");
					sInFile.Replace("#include \"../../Blob/CPP/Blob.hpp\"", "");
#line 209 "/home/cliffya/git/Lang/Source/CLI/CLI.nll"
					sInFile.Replace("#include \"Console.hpp\"", "");
					sInFile.Replace("#include \"../../Console/CPP/Console.hpp\"", "");
#line 212 "/home/cliffya/git/Lang/Source/CLI/CLI.nll"
					sInFile.Replace("#include \"ExternalString.hpp\"", "");
					sInFile.Replace("#include \"../../ExternalString/CPP/ExternalString.hpp\"", "");
#line 215 "/home/cliffya/git/Lang/Source/CLI/CLI.nll"
					sInFile.Replace("#include \"InternalString.hpp\"", "");
					sInFile.Replace("#include \"../../InternalString/CPP/InternalString.hpp\"", "");
#line 218 "/home/cliffya/git/Lang/Source/CLI/CLI.nll"
					sInFile.Replace("#include \"Utils.hpp\"", "");
					sInFile.Replace("#include \"../../Utils/CPP/Utils.hpp\"", "");
#line 221 "/home/cliffya/git/Lang/Source/CLI/CLI.nll"
					sInFile.Replace("#include \"Vector.hpp\"", "");
					sInFile.Replace("#include \"../../Vector/CPP/Vector.hpp\"", "");
#line 226 "/home/cliffya/git/Lang/Source/CLI/CLI.nll"
					sInFile.Replace("#include \"Xml.hpp\"", "");
					sInFile.Replace("#include \"../../Xml/CPP/Xml.hpp\"", "");
#line 229 "/home/cliffya/git/Lang/Source/CLI/CLI.nll"
					sInFile.Replace("#include \"Zip.hpp\"", "");
					sInFile.Replace("#include \"../../Zip/CPP/Zip.hpp\"", "");
#line 232 "/home/cliffya/git/Lang/Source/CLI/CLI.nll"
					sInFile.Replace("#include \"ZipWriter.hpp\"", "");
					sInFile.Replace("#include \"../../Zip/CPP/ZipWriter.hpp\"", "");
#line 235 "/home/cliffya/git/Lang/Source/CLI/CLI.nll"
					sInFile.Replace("#include \"tinyxml2.h\"", "");
					sInFile.Replace("#include \"miniz.h\"", "");
#line 238 "/home/cliffya/git/Lang/Source/CLI/CLI.nll"
					sAppend.AppendString(sInFile.GetExternalString());
					sAppend.AppendString("\n\n");
				}
#line 242 "/home/cliffya/git/Lang/Source/CLI/CLI.nll"
				InternalString sOutFile = File.GetContents(sOutFileName.GetExternalString());
				sOutFile.PrependString(sPrepend.GetExternalString());
				sOutFile.AppendString(sAppend.GetExternalString());
				File.PutContents(sOutFileName.GetExternalString(), sOutFile.GetExternalString());
			}
#line 249 "/home/cliffya/git/Lang/Source/CLI/CLI.nll"
			if (bOutputNLLDef)
			{
				Console.Log("Output NLL DEF");
				pProject.Output(AST.Language.NLL_DEF, AST.OutputFile.SOURCE);
			}
		}

	}
}


class Application
{
	static void Main(string[] args)
	{
		NumbatLogic.Vector<string> pArgVector = new NumbatLogic.Vector<string>();
		for (int i = 0; i < args.Length; i++)
			pArgVector.PushBack(args[i]);

		NumbatLogic.CLI.Run(pArgVector);
	}
}
