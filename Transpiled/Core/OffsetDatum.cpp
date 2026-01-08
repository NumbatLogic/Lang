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
		NumbatLogic::OffsetDatum* __3749477135 = pThis;
		pThis = 0;
		return __3749477135;
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

