#include "OffsetDatum.hpp"

namespace NumbatLogic
{
	class OffsetDatum;
}
namespace NumbatLogic
{
	OffsetDatum* OffsetDatum::Create(OffsetDatum* pOther)
	{
		OffsetDatum* pThis = new OffsetDatum();
		if (pOther != 0)
			pThis->Set(pOther);
		{
			NumbatLogic::OffsetDatum* __186135525 = pThis;
			pThis = 0;
			return __186135525;
		}
	}

	void OffsetDatum::Set(OffsetDatum* pOther)
	{
		m_nOffset = pOther->m_nOffset;
	}

	OffsetDatum::OffsetDatum()
	{
		m_nOffset = 0;
	}

}

