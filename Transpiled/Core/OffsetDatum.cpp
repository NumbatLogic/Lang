#include "OffsetDatum.hpp"

namespace NumbatLogic
{
	class OffsetDatum;
}
#line 1 "../../../Source/Core/OffsetDatum.nll"
namespace NumbatLogic
{
#line 4 "../../../Source/Core/OffsetDatum.nll"
#line 8 "../../../Source/Core/OffsetDatum.nll"
	OffsetDatum* OffsetDatum::Create(OffsetDatum* pOther)
	{
		OffsetDatum* pThis = new OffsetDatum();
#line 11 "../../../Source/Core/OffsetDatum.nll"
		if (pOther != 0)
#line 12 "../../../Source/Core/OffsetDatum.nll"
			pThis->Set(pOther);
		NumbatLogic::OffsetDatum* __3749477135 = pThis;
#line 13 "../../../Source/Core/OffsetDatum.nll"
		pThis = 0;
#line 13 "../../../Source/Core/OffsetDatum.nll"
		return __3749477135;
	}

#line 16 "../../../Source/Core/OffsetDatum.nll"
	void OffsetDatum::Set(OffsetDatum* pOther)
	{
#line 18 "../../../Source/Core/OffsetDatum.nll"
		m_nOffset = pOther->m_nOffset;
	}

#line 4 "../../../Source/Core/OffsetDatum.nll"
	OffsetDatum::OffsetDatum()
	{
		m_nOffset = 0;
	}

}

