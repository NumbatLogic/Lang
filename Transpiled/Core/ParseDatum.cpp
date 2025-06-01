#include "ParseDatum.hpp"
#include "../../Shared/CPP/InternalString.hpp"

namespace NumberDuck
{
	namespace Secret
	{
		ParseDatum::ParseDatum()
		{
			m_sInput = 0;
			m_sCurrentRead = 0;
			m_nCurrentReadLine = 0;
			m_nCurrentReadColumn = 0;
			m_sFileName = 0;
			m_nLine = 0;
			m_nColumn = 0;
			m_sInput = new InternalString("");
			m_sCurrentRead = new InternalString("");
			ClearCurrentRead();
			m_nLine = 1;
		}

		void ParseDatum::ClearCurrentRead()
		{
			m_sCurrentRead->Set("");
			m_nCurrentReadLine = m_nLine;
			m_nCurrentReadColumn = m_nColumn;
		}

		ParseDatum::~ParseDatum()
		{
			if (m_sInput) delete m_sInput;
			if (m_sCurrentRead) delete m_sCurrentRead;
		}

	}
}

