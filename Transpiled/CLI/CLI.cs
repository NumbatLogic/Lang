#line 1 "../../../Source/CLI/CLI.nll"
namespace NumbatLogic
{
#line 4 "../../../Source/CLI/CLI.nll"
	class CLI
	{
#line 6 "../../../Source/CLI/CLI.nll"
		public static void Run(Vector<string> sArgVector)
		{
#line 8 "../../../Source/CLI/CLI.nll"
			Console.Log("CLI");
#line 10 "../../../Source/CLI/CLI.nll"
			if (sArgVector.GetSize() % 2 != 0)
			{
				InternalString sTemp = new InternalString("expected even number of args! Got ");
#line 13 "../../../Source/CLI/CLI.nll"
				sTemp.AppendInt(sArgVector.GetSize());
#line 14 "../../../Source/CLI/CLI.nll"
				Console.Log(sTemp.GetExternalString());
#line 15 "../../../Source/CLI/CLI.nll"
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
#line 29 "../../../Source/CLI/CLI.nll"
			while (i < sArgVector.GetSize())
			{
				InternalString sTemp;
				string sxArg0 = sArgVector.Get(i);
#line 34 "../../../Source/CLI/CLI.nll"
				i++;
				string sxArg1 = sArgVector.Get(i);
#line 36 "../../../Source/CLI/CLI.nll"
				i++;
#line 38 "../../../Source/CLI/CLI.nll"
				if (ExternalString.Equal(sxArg0, "-d"))
				{
#line 40 "../../../Source/CLI/CLI.nll"
					sDefineVector.PushBack(new InternalString(sxArg1));
#line 41 "../../../Source/CLI/CLI.nll"
					continue;
				}
#line 44 "../../../Source/CLI/CLI.nll"
				if (ExternalString.Equal(sxArg0, "-f"))
				{
#line 46 "../../../Source/CLI/CLI.nll"
					sTemp = new InternalString("Recurse: ");
#line 47 "../../../Source/CLI/CLI.nll"
					sTemp.Append(sxArg1);
#line 48 "../../../Source/CLI/CLI.nll"
					Console.Log(sTemp.GetExternalString());
#line 49 "../../../Source/CLI/CLI.nll"
					pProject.AddDirectory(sxArg1, sDefineVector);
#line 50 "../../../Source/CLI/CLI.nll"
					continue;
				}
#line 53 "../../../Source/CLI/CLI.nll"
				if (ExternalString.Equal(sxArg0, "-fi"))
				{
#line 55 "../../../Source/CLI/CLI.nll"
					sTemp = new InternalString("File: ");
#line 56 "../../../Source/CLI/CLI.nll"
					sTemp.Append(sxArg1);
#line 57 "../../../Source/CLI/CLI.nll"
					Console.Log(sTemp.GetExternalString());
#line 58 "../../../Source/CLI/CLI.nll"
					pProject.AddFile(sxArg1, sDefineVector);
#line 59 "../../../Source/CLI/CLI.nll"
					continue;
				}
#line 62 "../../../Source/CLI/CLI.nll"
				if (ExternalString.Equal(sxArg0, "-a"))
				{
#line 64 "../../../Source/CLI/CLI.nll"
					sAmalgamateFileName = new InternalString(sxArg1);
#line 65 "../../../Source/CLI/CLI.nll"
					continue;
				}
#line 68 "../../../Source/CLI/CLI.nll"
				if (ExternalString.Equal(sxArg0, "--output-nll-def"))
				{
#line 70 "../../../Source/CLI/CLI.nll"
					if (!ExternalString.Equal(sxArg1, "true"))
					{
#line 72 "../../../Source/CLI/CLI.nll"
						Console.Log("if set, --output-nll must be true");
#line 73 "../../../Source/CLI/CLI.nll"
						return;
					}
#line 76 "../../../Source/CLI/CLI.nll"
					bOutputNLLDef = true;
#line 77 "../../../Source/CLI/CLI.nll"
					continue;
				}
#line 80 "../../../Source/CLI/CLI.nll"
				if (ExternalString.Equal(sxArg0, "-ahppa"))
				{
#line 82 "../../../Source/CLI/CLI.nll"
					sAmalgamatedHPPAppend.PushBack(new InternalString(sxArg1));
#line 83 "../../../Source/CLI/CLI.nll"
					continue;
				}
#line 86 "../../../Source/CLI/CLI.nll"
				if (ExternalString.Equal(sxArg0, "-acppp"))
				{
#line 88 "../../../Source/CLI/CLI.nll"
					sAmalgamatedCPPPrepend.PushBack(new InternalString(sxArg1));
#line 89 "../../../Source/CLI/CLI.nll"
					continue;
				}
#line 92 "../../../Source/CLI/CLI.nll"
				if (ExternalString.Equal(sxArg0, "-acppa"))
				{
#line 94 "../../../Source/CLI/CLI.nll"
					sAmalgamatedCPPAppend.PushBack(new InternalString(sxArg1));
#line 95 "../../../Source/CLI/CLI.nll"
					continue;
				}
#line 98 "../../../Source/CLI/CLI.nll"
				if (ExternalString.Equal(sxArg0, "-acsa"))
				{
#line 100 "../../../Source/CLI/CLI.nll"
					sAmalgamatedCSAppend.PushBack(new InternalString(sxArg1));
#line 101 "../../../Source/CLI/CLI.nll"
					continue;
				}
#line 104 "../../../Source/CLI/CLI.nll"
				sTemp = new InternalString("Unexpected arg: ");
#line 105 "../../../Source/CLI/CLI.nll"
				sTemp.Append(sxArg0);
#line 106 "../../../Source/CLI/CLI.nll"
				Console.Log(sTemp.GetExternalString());
#line 107 "../../../Source/CLI/CLI.nll"
				return;
			}
#line 110 "../../../Source/CLI/CLI.nll"
			if (sAmalgamateFileName != null)
			{
#line 112 "../../../Source/CLI/CLI.nll"
				Console.Log("Amalgamate");
#line 113 "../../../Source/CLI/CLI.nll"
				pProject.Amalgamate(sAmalgamateFileName.GetExternalString());
			}
#line 116 "../../../Source/CLI/CLI.nll"
			Console.Log("Validate");
#line 117 "../../../Source/CLI/CLI.nll"
			pProject.FullValidate();
#line 119 "../../../Source/CLI/CLI.nll"
			Console.Log("Output CS");
#line 120 "../../../Source/CLI/CLI.nll"
			pProject.Output(AST.Language.CS, AST.OutputFile.SOURCE);
#line 121 "../../../Source/CLI/CLI.nll"
			if (sAmalgamateFileName != null)
			{
				InternalString sOutFileName = new InternalString(sAmalgamateFileName.GetExternalString());
#line 124 "../../../Source/CLI/CLI.nll"
				sOutFileName.Replace(".nll", ".cs");
				InternalString sAppend = new InternalString("");
#line 128 "../../../Source/CLI/CLI.nll"
				for (int x = 0; x < sAmalgamatedCSAppend.GetSize(); x++)
				{
					InternalString sInFileName = sAmalgamatedCSAppend.Get(x);
					InternalString sInFile = File.GetContents(sInFileName.GetExternalString());
#line 133 "../../../Source/CLI/CLI.nll"
					sAppend.AppendString(sInFile.GetExternalString());
#line 134 "../../../Source/CLI/CLI.nll"
					sAppend.AppendString("\n\n");
				}
				InternalString sOutFile = File.GetContents(sOutFileName.GetExternalString());
#line 138 "../../../Source/CLI/CLI.nll"
				sOutFile.AppendString(sAppend.GetExternalString());
#line 139 "../../../Source/CLI/CLI.nll"
				File.PutContents(sOutFileName.GetExternalString(), sOutFile.GetExternalString());
			}
#line 143 "../../../Source/CLI/CLI.nll"
			Console.Log("Output HPP");
#line 144 "../../../Source/CLI/CLI.nll"
			pProject.Output(AST.Language.CPP, AST.OutputFile.HEADER);
#line 145 "../../../Source/CLI/CLI.nll"
			if (sAmalgamateFileName != null)
			{
				InternalString sOutFileName = new InternalString(sAmalgamateFileName.GetExternalString());
#line 148 "../../../Source/CLI/CLI.nll"
				sOutFileName.Replace(".nll", ".hpp");
				InternalString sAppend = new InternalString("");
#line 152 "../../../Source/CLI/CLI.nll"
				for (int x = 0; x < sAmalgamatedHPPAppend.GetSize(); x++)
				{
					InternalString sInFileName = sAmalgamatedHPPAppend.Get(x);
					InternalString sInFile = File.GetContents(sInFileName.GetExternalString());
#line 157 "../../../Source/CLI/CLI.nll"
					sAppend.AppendString(sInFile.GetExternalString());
#line 158 "../../../Source/CLI/CLI.nll"
					sAppend.AppendString("\n\n");
				}
				InternalString sOutFile = File.GetContents(sOutFileName.GetExternalString());
#line 162 "../../../Source/CLI/CLI.nll"
				sOutFile.AppendString(sAppend.GetExternalString());
#line 163 "../../../Source/CLI/CLI.nll"
				File.PutContents(sOutFileName.GetExternalString(), sOutFile.GetExternalString());
			}
#line 168 "../../../Source/CLI/CLI.nll"
			Console.Log("Output CPP");
#line 169 "../../../Source/CLI/CLI.nll"
			pProject.Output(AST.Language.CPP, AST.OutputFile.SOURCE);
#line 171 "../../../Source/CLI/CLI.nll"
			if (sAmalgamateFileName != null)
			{
				InternalString sOutFileName = new InternalString(sAmalgamateFileName.GetExternalString());
#line 174 "../../../Source/CLI/CLI.nll"
				sOutFileName.Replace(".nll", ".cpp");
				InternalString sPrepend = new InternalString("");
				InternalString sAppend = new InternalString("");
#line 179 "../../../Source/CLI/CLI.nll"
				for (int x = 0; x < sAmalgamatedCPPPrepend.GetSize(); x++)
				{
					InternalString sInFileName = sAmalgamatedCPPPrepend.Get(x);
					InternalString sInFile = File.GetContents(sInFileName.GetExternalString());
#line 185 "../../../Source/CLI/CLI.nll"
					sInFile.Replace("#pragma once", "");
#line 186 "../../../Source/CLI/CLI.nll"
					sInFile.Replace("#include \"tinyxml2/tinyxml2.h\"", "");
#line 187 "../../../Source/CLI/CLI.nll"
					sInFile.Replace("#include \"miniz/miniz.h\"", "");
#line 189 "../../../Source/CLI/CLI.nll"
					sPrepend.AppendString(sInFile.GetExternalString());
#line 190 "../../../Source/CLI/CLI.nll"
					sPrepend.AppendString("\n\n");
				}
#line 193 "../../../Source/CLI/CLI.nll"
				for (int x = 0; x < sAmalgamatedCPPAppend.GetSize(); x++)
				{
					InternalString sInFileName = sAmalgamatedCPPAppend.Get(x);
					InternalString sInFile = File.GetContents(sInFileName.GetExternalString());
#line 199 "../../../Source/CLI/CLI.nll"
					sInFile.Replace("#include \"Assert.hpp\"", "");
#line 200 "../../../Source/CLI/CLI.nll"
					sInFile.Replace("#include \"../../Assert/CPP/Assert.hpp\"", "");
#line 202 "../../../Source/CLI/CLI.nll"
					sInFile.Replace("#include \"Blob.hpp\"", "");
#line 203 "../../../Source/CLI/CLI.nll"
					sInFile.Replace("#include \"../../Blob/CPP/Blob.hpp\"", "");
#line 205 "../../../Source/CLI/CLI.nll"
					sInFile.Replace("#include \"Console.hpp\"", "");
#line 206 "../../../Source/CLI/CLI.nll"
					sInFile.Replace("#include \"../../Console/CPP/Console.hpp\"", "");
#line 208 "../../../Source/CLI/CLI.nll"
					sInFile.Replace("#include \"ExternalString.hpp\"", "");
#line 209 "../../../Source/CLI/CLI.nll"
					sInFile.Replace("#include \"../../ExternalString/CPP/ExternalString.hpp\"", "");
#line 211 "../../../Source/CLI/CLI.nll"
					sInFile.Replace("#include \"InternalString.hpp\"", "");
#line 212 "../../../Source/CLI/CLI.nll"
					sInFile.Replace("#include \"../../InternalString/CPP/InternalString.hpp\"", "");
#line 214 "../../../Source/CLI/CLI.nll"
					sInFile.Replace("#include \"Utils.hpp\"", "");
#line 215 "../../../Source/CLI/CLI.nll"
					sInFile.Replace("#include \"../../Utils/CPP/Utils.hpp\"", "");
#line 217 "../../../Source/CLI/CLI.nll"
					sInFile.Replace("#include \"Vector.hpp\"", "");
#line 218 "../../../Source/CLI/CLI.nll"
					sInFile.Replace("#include \"../../Vector/CPP/Vector.hpp\"", "");
#line 222 "../../../Source/CLI/CLI.nll"
					sInFile.Replace("#include \"Xml.hpp\"", "");
#line 223 "../../../Source/CLI/CLI.nll"
					sInFile.Replace("#include \"../../Xml/CPP/Xml.hpp\"", "");
#line 225 "../../../Source/CLI/CLI.nll"
					sInFile.Replace("#include \"Zip.hpp\"", "");
#line 226 "../../../Source/CLI/CLI.nll"
					sInFile.Replace("#include \"../../Zip/CPP/Zip.hpp\"", "");
#line 228 "../../../Source/CLI/CLI.nll"
					sInFile.Replace("#include \"ZipWriter.hpp\"", "");
#line 229 "../../../Source/CLI/CLI.nll"
					sInFile.Replace("#include \"../../Zip/CPP/ZipWriter.hpp\"", "");
#line 231 "../../../Source/CLI/CLI.nll"
					sInFile.Replace("#include \"tinyxml2.h\"", "");
#line 232 "../../../Source/CLI/CLI.nll"
					sInFile.Replace("#include \"miniz.h\"", "");
#line 234 "../../../Source/CLI/CLI.nll"
					sAppend.AppendString(sInFile.GetExternalString());
#line 235 "../../../Source/CLI/CLI.nll"
					sAppend.AppendString("\n\n");
				}
				InternalString sOutFile = File.GetContents(sOutFileName.GetExternalString());
#line 239 "../../../Source/CLI/CLI.nll"
				sOutFile.PrependString(sPrepend.GetExternalString());
#line 240 "../../../Source/CLI/CLI.nll"
				sOutFile.AppendString(sAppend.GetExternalString());
#line 241 "../../../Source/CLI/CLI.nll"
				File.PutContents(sOutFileName.GetExternalString(), sOutFile.GetExternalString());
			}
#line 245 "../../../Source/CLI/CLI.nll"
			if (bOutputNLLDef)
			{
#line 247 "../../../Source/CLI/CLI.nll"
				Console.Log("Output NLL DEF");
#line 248 "../../../Source/CLI/CLI.nll"
				pProject.Output(AST.Language.NLL_DEF, AST.OutputFile.SOURCE);
			}
		}

	}
}

