#include <assert.h>
#include <jni.h>
#include <android/log.h>

#include "MediaInfo/MediaInfo.h"
#include "libmediainfo-test-mediainfo.h"


using namespace MediaInfoLib;


#define LOG(...)   __android_log_print(ANDROID_LOG_DEBUG, "mediainfo", __VA_ARGS__)
#define LOGW(...)  __android_log_print(ANDROID_LOG_WARN, "mediainfo", __VA_ARGS__)
#define LOGE(...)  __android_log_print(ANDROID_LOG_ERROR, "mediainfo", __VA_ARGS__)




extern "C" {
    JNIEXPORT jlong   JNICALL Java_org_mediainfo_android_MediaInfo_create(JNIEnv* pEnv, jobject self);
    JNIEXPORT void    JNICALL Java_org_mediainfo_android_MediaInfo_destroy(JNIEnv* pEnv, jobject self, jlong peer);
    JNIEXPORT jint    JNICALL Java_org_mediainfo_android_MediaInfo_open(JNIEnv* pEnv, jobject self, jlong peer, jstring filename);
    JNIEXPORT void    JNICALL Java_org_mediainfo_android_MediaInfo_close(JNIEnv* pEnv, jobject self, jlong peer);
    JNIEXPORT jstring JNICALL Java_org_mediainfo_android_MediaInfo_getById(JNIEnv* pEnv, jobject self, jlong peer, jint streamKind, jint streamNum, jint parameter);
    JNIEXPORT jstring JNICALL Java_org_mediainfo_android_MediaInfo_getByName(JNIEnv* pEnv, jobject self, jlong peer, jint streamKind, jint streamNum, jstring parameter);
    JNIEXPORT jstring JNICALL Java_org_mediainfo_android_MediaInfo_getByIdDetail(JNIEnv* pEnv, jobject self, jlong peer, jint streamKind, jint streamNum, jint parameter, jint kindOfInfo);
    JNIEXPORT jstring JNICALL Java_org_mediainfo_android_MediaInfo_getByNameDetail(JNIEnv* pEnv, jobject self, jlong peer, jint streamKind, jint streamNum, jstring parameter, jint kindOfInfo, jint kindOfSearch);
    JNIEXPORT jstring JNICALL Java_org_mediainfo_android_MediaInfo_getOption(JNIEnv* pEnv, jobject self, jlong peer, jstring option);
    JNIEXPORT jint    JNICALL Java_org_mediainfo_android_MediaInfo_count(JNIEnv* pEnv, jobject self, jlong peer, jint streamKind, jint streamNum);
}


JNIEXPORT jlong JNICALL
Java_org_mediainfo_android_MediaInfo_create(JNIEnv* pEnv, jobject self)
{
    LOG(("called __create()\n"));

    return (jlong) new MediaInfoTest();
}

JNIEXPORT void JNICALL
Java_org_mediainfo_android_MediaInfo_destroy(JNIEnv* pEnv, jobject self, jlong peer)
{
    LOG(("called __destroy()\n"));

    if (peer)
        delete (MediaInfoTest*) peer;
}

static inline const Char*
CastChars(const jchar* chars)
{
    assert(sizeof(jchar) == sizeof(Char));

    return (const Char*) chars;
}

static inline const jchar*
CastChars(const Char* chars)
{
    assert(sizeof(jchar) == sizeof(Char));

    return (const jchar*) chars;
}

static inline stream_t
GetStreamKind(jint streamKind)
{
    return (stream_t) streamKind;
}

static inline info_t
GetInfoKind(jint infoKind)
{
    return (info_t) infoKind;
}

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


JNIEXPORT jint JNICALL
Java_org_mediainfo_android_MediaInfo_open(JNIEnv* pEnv, jobject self, jlong peer, jstring filename)
{
    if (!peer)
        return 0;

    MediaInfoTest* pmi = (MediaInfoTest*) peer;

    const jchar* jchars = pEnv->GetStringChars(filename, NULL);
    if (jchars == NULL) {
        LOGW("GetStringChars() failed.\n");
        return 0;
    }

    String strFileName;
    strFileName.assign(CastChars(jchars), pEnv->GetStringLength(filename));

    size_t res = pmi->Open(strFileName);

    LOG("__open() returns %d\n", res);

    pEnv->ReleaseStringChars(filename, jchars);

    return (jint) res;
}

JNIEXPORT void JNICALL
Java_org_mediainfo_android_MediaInfo_close(JNIEnv* pEnv, jobject self, jlong peer)
{
}

JNIEXPORT jstring JNICALL
Java_org_mediainfo_android_MediaInfo_getById(JNIEnv* pEnv, jobject self, jlong peer, jint streamKind, jint streamNum, jint parameter)
{
    return 0;
}

JNIEXPORT jstring JNICALL
Java_org_mediainfo_android_MediaInfo_getByName(JNIEnv* pEnv, jobject self, jlong peer, jint streamKind, jint streamNum, jstring parameter)
{
	ZenLib::Ztring strInfo;

	// test for mbstowcs()
	switch(streamKind) {
	case 0:
		strInfo.From_Local("babo¹Ùº¸foo"); break;
	case 1:
		strInfo.From_Local("babo¹Ùº¸fooÇª¿ì"); break;
	case 2:
		strInfo.From_Local("foo"); break;
	case 5:
		strInfo.From_Local("Çª"); break;
	default:
		strInfo.From_Local("fooÇªfoo"); break;
	}

	// test for wcstombs()
	std::string localInfo = strInfo.To_Local();

	// test for wctomb()
	/*char cbuf[ZenLib::Ztring::MB_MAX_LEN];
	int bytes = wctomb(cbuf, strInfo.at(0));
	if (bytes > 0)
		cbuf[bytes] = '\0';

    LOG("__getByName() returns '%s'.\n\t\tThe local string is '%s'. cbuf is '%s' %d bytes.\n",
		ConvChars(strInfo.c_str()), localInfo.c_str(), cbuf, bytes);
	*/

    jstring res = pEnv->NewString(CastChars(strInfo.c_str()), strInfo.size());

    return res;
}

JNIEXPORT jstring JNICALL
Java_org_mediainfo_android_MediaInfo_getByIdDetail(JNIEnv* pEnv, jobject self, jlong peer, jint streamKind, jint streamNum, jint parameter, jint kindOfInfo)
{
    return 0;
}

JNIEXPORT jstring JNICALL
Java_org_mediainfo_android_MediaInfo_getByNameDetail(JNIEnv* pEnv, jobject self, jlong peer, jint streamKind, jint streamNum, jstring parameter, jint kindOfInfo, jint kindOfSearch)
{
    return 0;
}

JNIEXPORT jstring JNICALL
Java_org_mediainfo_android_MediaInfo_getOption(JNIEnv* pEnv, jobject self, jlong peer, jstring option)
{
    return 0;

}

JNIEXPORT jint JNICALL
Java_org_mediainfo_android_MediaInfo_count(JNIEnv* pEnv, jobject self, jlong peer, jint streamKind, jint streamNum)
{
    return 0;
}

