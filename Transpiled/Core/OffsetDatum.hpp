#pragma once

namespace NumbatLogic
{
	class OffsetDatum;
}
#line 0 "../../../Source/Core/OffsetDatum.nll"
namespace NumbatLogic
{
#line 3 "../../../Source/Core/OffsetDatum.nll"
	class OffsetDatum
	{
		public: int m_nOffset;
		public: static OffsetDatum* Create(OffsetDatum* pOther);
		public: void Set(OffsetDatum* pOther);
		public: OffsetDatum();
	};
}

