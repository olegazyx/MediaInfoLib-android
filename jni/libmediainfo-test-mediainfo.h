#ifndef __libmediainfo_test_mediainfo_h__
#define __libmediainfo_test_mediainfo_h__


#include "MediaInfo/MediaInfo.h"
#include "ZenLib/Ztring.h"

namespace MediaInfoLib
{

class MediaInfoTest 
{
public:
    MediaInfoTest() {
    }
	size_t Open(const String &strFileName);

    ZenLib::Ztring mFileName;
};
}

#endif /** __libmediainfo_test_mediainfo_h__ */
