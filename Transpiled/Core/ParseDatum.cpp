#include "ParseDatum.hpp"
#include "../../../LangShared/InternalString/CPP/InternalString.hpp"

namespace NumbatLogic
{
	class ParseDatum;
	class InternalString;
}
#line 0 "../../../Source/Core/ParseDatum.nll"
namespace NumbatLogic
{
#line 3 "../../../Source/Core/ParseDatum.nll"
#line 15 "../../../Source/Core/ParseDatum.nll"
	ParseDatum::ParseDatum()
	{
		m_sInput = 0;
		m_sCurrentRead = 0;
		m_nCurrentReadLine = 0;
		m_nCurrentReadColumn = 0;
		m_sFileName = 0;
		m_nLine = 0;
		m_nColumn = 0;
#line 17 "../../../Source/Core/ParseDatum.nll"
		m_sInput = new InternalString("");
#line 18 "../../../Source/Core/ParseDatum.nll"
		m_sCurrentRead = new InternalString("");
#line 19 "../../../Source/Core/ParseDatum.nll"
		ClearCurrentRead();
#line 20 "../../../Source/Core/ParseDatum.nll"
		m_nLine = 1;
	}

#line 23 "../../../Source/Core/ParseDatum.nll"
	void ParseDatum::ClearCurrentRead()
	{
#line 25 "../../../Source/Core/ParseDatum.nll"
		m_sCurrentRead->Set("");
#line 26 "../../../Source/Core/ParseDatum.nll"
		m_nCurrentReadLine = m_nLine;
#line 27 "../../../Source/Core/ParseDatum.nll"
		m_nCurrentReadColumn = m_nColumn;
	}

#line 3 "../../../Source/Core/ParseDatum.nll"
	ParseDatum::~ParseDatum()
	{
		if (m_sInput) delete m_sInput;
		if (m_sCurrentRead) delete m_sCurrentRead;
	}

}

