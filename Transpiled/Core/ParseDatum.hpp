#pragma once

namespace NumbatLogic
{
	class InternalString;
}
#line 0 "../../../Source/Core/ParseDatum.nll"
namespace NumbatLogic
{
#line 3 "../../../Source/Core/ParseDatum.nll"
	class ParseDatum
	{
		public: InternalString* m_sInput;
		public: InternalString* m_sCurrentRead;
		public: int m_nCurrentReadLine;
		public: int m_nCurrentReadColumn;
		public: InternalString* m_sFileName;
		public: int m_nLine;
		public: int m_nColumn;
		public: ParseDatum();
		public: void ClearCurrentRead();
		public: virtual ~ParseDatum();
	};
}

