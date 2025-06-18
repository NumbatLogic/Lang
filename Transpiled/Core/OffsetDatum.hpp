#pragma once

namespace NumbatLogic
{
	class OffsetDatum;
}
namespace NumbatLogic
{
	class OffsetDatum
	{
		public: int m_nOffset;
		public: static OffsetDatum* Create(OffsetDatum* pOther);
		public: void Set(OffsetDatum* pOther);
		public: OffsetDatum();
	};
}

