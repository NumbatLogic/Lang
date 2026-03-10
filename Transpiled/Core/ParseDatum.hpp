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
#line 5 "../../../Source/Core/ParseDatum.nll"
		public: InternalString* m_sInput;
#line 6 "../../../Source/Core/ParseDatum.nll"
		public: InternalString* m_sCurrentRead;
#line 8 "../../../Source/Core/ParseDatum.nll"
		public: int m_nCurrentReadLine;
#line 9 "../../../Source/Core/ParseDatum.nll"
		public: int m_nCurrentReadColumn;
#line 11 "../../../Source/Core/ParseDatum.nll"
		public: InternalString* m_sFileName;
#line 12 "../../../Source/Core/ParseDatum.nll"
		public: int m_nLine;
#line 13 "../../../Source/Core/ParseDatum.nll"
		public: int m_nColumn;
#line 15 "../../../Source/Core/ParseDatum.nll"
		public: ParseDatum();
#line 23 "../../../Source/Core/ParseDatum.nll"
		public: void ClearCurrentRead();
#line 3 "../../../Source/Core/ParseDatum.nll"
		public: virtual ~ParseDatum();
	};
}

