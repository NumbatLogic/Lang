#pragma once

#include "AST.hpp"
#include "../../../../LangShared/Vector/CPP/Vector.hpp"
#include "VarDecl.hpp"

namespace NumbatLogic
{
	class AST;
	template <class T>
	class Vector;
	class VarDecl;
	class OutputBuilder;
}
#line 1 "../../../Source/Core/AST/VarDeclDescope.nll"
namespace NumbatLogic
{
#line 4 "../../../Source/Core/AST/VarDeclDescope.nll"
	class VarDeclDescope : public AST
	{
#line 6 "../../../Source/Core/AST/VarDeclDescope.nll"
		public: Vector<VarDecl*>* m_pVarDeclVector;
#line 8 "../../../Source/Core/AST/VarDeclDescope.nll"
		public: VarDeclDescope();
#line 14 "../../../Source/Core/AST/VarDeclDescope.nll"
		public: virtual void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder* pOutputBuilder);
#line 4 "../../../Source/Core/AST/VarDeclDescope.nll"
		public: virtual ~VarDeclDescope();
	};
}

