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
#line 0 "/home/cliffya/git/Lang/Source/Core/AST/VarDeclDescope.nll"
namespace NumbatLogic
{
#line 3 "/home/cliffya/git/Lang/Source/Core/AST/VarDeclDescope.nll"
	class VarDeclDescope : public AST
	{
		public: Vector<VarDecl*>* m_pVarDeclVector;
#line 7 "/home/cliffya/git/Lang/Source/Core/AST/VarDeclDescope.nll"
		public: VarDeclDescope();
#line 13 "/home/cliffya/git/Lang/Source/Core/AST/VarDeclDescope.nll"
		public: virtual void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder* pOutputBuilder);
#line 3 "/home/cliffya/git/Lang/Source/Core/AST/VarDeclDescope.nll"
		public: virtual ~VarDeclDescope();
	};
}

