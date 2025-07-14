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
	class VarDecl;
	class InternalString;
}
namespace NumbatLogic
{
	class VarDeclDescope : public AST
	{
		public: Vector<VarDecl*>* m_pVarDeclVector;
		public: VarDeclDescope();
		public: virtual void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, InternalString* sOut);
		public: virtual ~VarDeclDescope();
	};
}

