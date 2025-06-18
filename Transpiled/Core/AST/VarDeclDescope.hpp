#pragma once

#include "AST.hpp"
#include "../../../../LangShared/Vector/CPP/Vector.hpp"
#include "VarDecl.hpp"

namespace NumbatLogic
{
	class VarDecl;
	class InternalString;
}
namespace NumbatLogic
{
	class VarDeclDescope : public AST
	{
		protected: bool m_bScope;
		public: Vector<VarDecl*>* m_pVarDeclVector;
		public: VarDeclDescope(bool bScope);
		public: virtual void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, InternalString* sOut);
		public: virtual ~VarDeclDescope();
	};
}

