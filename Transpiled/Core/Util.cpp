#include "Util.hpp"
#include "../../../LangShared/InternalString/CPP/InternalString.hpp"
#include "../../../LangShared/Blob/CPP/Blob.hpp"

namespace NumberDuck
{
	class Blob;
	class BlobView;
}
namespace NumbatLogic
{
	void Util::Pad(int nDepth, InternalString* sOut)
	{
		for (int i = 0; i < nDepth; i = i + 1)
			sOut->AppendChar('\t');
	}

	unsigned int Util::BadHash(InternalString* sString)
	{
		Blob* pBlob = new Blob(true);
		BlobView* pBlobView = pBlob->GetBlobView();
		for (int i = 0; i < sString->GetLength(); i++)
		{
			unsigned short nChar = sString->GetChar(i);
			pBlobView->PackUint32(nChar);
		}
		unsigned int nHaxTemp = pBlob->GetMsoCrc32();
		{
			if (pBlob) delete pBlob;
			return nHaxTemp;
		}
	}

}

