#include "OffsetDatum.hpp"

namespace NumbatLogic
{
	class OffsetDatum;
}
#line 0 "../../../Source/Core/OffsetDatum.nll"
namespace NumbatLogic
{
#line 3 "../../../Source/Core/OffsetDatum.nll"
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

