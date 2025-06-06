#pragma once

#include "AST.hpp"
#include "../../../../LangShared/Vector/CPP/Vector.hpp"

namespace NumberDuck
{
	namespace Secret
	{
		class VarDecl;
		class InternalString;
	}
}
namespace NumberDuck
{
	namespace Secret
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
}

