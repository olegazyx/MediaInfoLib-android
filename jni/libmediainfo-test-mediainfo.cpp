/**
 * Test codes for MediaInfo
 */
#include "libmediainfo-test-mediainfo.h"
#include "MediaInfo/Setup.h"
#include "MediaInfo/MediaInfo_Internal_Const.h"
#include <ZenLib/Ztring.h>
#include <android/log.h>


using namespace std;
using namespace ZenLib;


namespace MediaInfoLib
{

#define LOG(...)   __android_log_print(ANDROID_LOG_DEBUG, "mediainfo", __VA_ARGS__)

static inline char*
ConvChars(const Char* chars)
{
    static char buf[1024];

    char* p = &buf[0];

    while (*chars)
        *p++ = (char) *chars++;

    *p = '\0';

    return &buf[0];
}


size_t MediaInfoTest::Open(const String &strFileName)
{
    LOG("[%d]::Open(%s) 0x%x %d/%d bytes\n", __LINE__,
        ConvChars(strFileName.c_str()), strFileName.c_str(),
		strFileName.size(), strFileName.capacity());
    LOG("[%d]::Open(%s) 0x%x %d/%d bytes\n", __LINE__,
        ConvChars(mFileName.c_str()), mFileName.c_str(),
		mFileName.size(), mFileName.capacity());

#if 0
    mFileName=_T("");

    LOG("[%d]::Open(%s) 0x%x %d/%d bytes\n", __LINE__,
        ConvChars(strFileName.c_str()), strFileName.c_str(),
		strFileName.size(), strFileName.capacity());
    LOG("[%d]::Open(%s) 0x%x %d/%d bytes\n",
        ConvChars(mFileName.c_str()), mFileName.c_str(), __LINE__,
		mFileName.size(), mFileName.capacity());
#endif

    mFileName=strFileName;
    //mFileName=strFileName.c_str();
    //mFileName=(const wchar_t*) strFileName.c_str();
    //mFileName=(const ZenLib::Char*) strFileName.c_str();

    LOG("[%d]::Open() arg: 0x%x c_str 0x%x '%s' %d/%d bytes\n", __LINE__,
        &strFileName, strFileName.c_str(), ConvChars(strFileName.c_str()),
		strFileName.size(), strFileName.capacity());
    LOG("[%d]::Open() internal: 0x%x, c_str 0x%x '%s' %d/%d bytes\n", __LINE__,
        &mFileName, mFileName.c_str(), ConvChars(mFileName.c_str()),
		mFileName.size(), mFileName.capacity());


#if 0
    String tmpFileName=_T("abc");
    mFileName=tmpFileName;

    LOG("[%d]::Open() tmp: 0x%x '%s' %d/%d bytes\n", __LINE__,
		tmpFileName.c_str(), ConvChars(tmpFileName.c_str()),
	   	tmpFileName.size(), tmpFileName.capacity());
    LOG("[%d]::Open() internal: 0x%x '%s' %d/%d bytes\n", __LINE__,
        mFileName.c_str(), ConvChars(mFileName.c_str()),
		mFileName.size(), mFileName.capacity());

#endif

    return 1;
}


} // namespace
