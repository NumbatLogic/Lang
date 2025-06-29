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
		NumbatLogic::OffsetDatum* __3620161242 = pThis;
		pThis = 0;
		return __3620161242;
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

