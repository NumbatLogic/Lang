#pragma once

namespace NumbatLogic
{
	class OffsetDatum;
}
#line 1 "../../../Source/Core/OffsetDatum.nll"
namespace NumbatLogic
{
#line 4 "../../../Source/Core/OffsetDatum.nll"
	class OffsetDatum
	{
#line 6 "../../../Source/Core/OffsetDatum.nll"
		public: int m_nOffset;
#line 8 "../../../Source/Core/OffsetDatum.nll"
		public: static OffsetDatum* Create(OffsetDatum* pOther);
#line 16 "../../../Source/Core/OffsetDatum.nll"
		public: void Set(OffsetDatum* pOther);
#line 4 "../../../Source/Core/OffsetDatum.nll"
		public: OffsetDatum();
	};
}

