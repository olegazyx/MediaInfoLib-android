#include <assert.h>
#include <jni.h>

// if need to debug messages, comment out below undef lines.
//#define _DEBUG
//#define DEBUG
//#define _DEBUG
//#define DEBUG
#undef _DEBUG
#undef DEBUG

#if defined(WIN32) && defined(_DEBUG)
#   include <vld.h>
#endif

////////////////////////////////////////////////////////////////////////////
//  Platform specific parts
//
////////////////////////////////////////////////////////////////////////////

#if defined(ANDROID)

#   include "MediaInfo/MediaInfo.h"
    using namespace MediaInfoLib;

#   include <android/log.h>

#   define LOGW(...)  __android_log_print(ANDROID_LOG_WARN, "libmediainfo-jni", __VA_ARGS__)
#   define LOGE(...)  __android_log_print(ANDROID_LOG_ERROR, "libmediainfo-jni", __VA_ARGS__)

#   if defined(_DEBUG) || defined(DEBUG)
#       define LOG(...)   __android_log_print(ANDROID_LOG_DEBUG, "libmediainfo-jni", __VA_ARGS__)
#   else
#       define LOG(...)   ((void)0)
#   endif

#   define FUNC        __func__

#elif defined(_WIN32)

#   include "MediaInfoDLL/MediaInfoDLL.h"
    using namespace MediaInfoDLL;

#   include <stdio.h>

#   define LOGW(...)  printf("[W|libmediainfo-jni] " __VA_ARGS__)
#   define LOGE(...)  printf("[E|libmediainfo-jni] " __VA_ARGS__)

#   if defined(_DEBUG) || defined(DEBUG)
#       define LOG(...)   printf("[D|libmediainfo-jni] " __VA_ARGS__)
#   else
#       define LOG(...)   ((void)0)
#   endif

#   define FUNC        __FUNCTION__

#else

#   error not support target!

#endif

static inline const char*
_PrintableChars(const Char* chars, char* buf, size_t buflen)
{
    assert(buf);
    assert(buflen > 0);

    const char* pend = buf + buflen - 1; // 1 for '\0'
    char* p = buf;

    while (*chars && p < pend)
        *p++ = (char) *chars++;

    *p = '\0';

    return buf;
}

static inline const char*
PrintableChars(const Char* chars)
{
#if defined(_DEBUG) || defined(DEBUG)
    static char buf[128];
    return _PrintableChars(chars, &buf[0], sizeof(buf)/sizeof(char));
#else
    return "";
#endif
}

static inline const char*
PrintableChars2(const Char* chars)
{
#if defined(_DEBUG) || defined(DEBUG)
    static char buf[128];
    return _PrintableChars(chars, &buf[0], sizeof(buf)/sizeof(char));
#else
    return "";
#endif
}


class FuncCallLog {

public:
    FuncCallLog(const char* pszFuncName) {

#if defined(_DEBUG) || defined(DEBUG)
        _pszFuncName = pszFuncName;
        LOG("%s() is called.\n", pszFuncName);
    }

    ~FuncCallLog() {
        LOG("%s() will be returned.\n", _pszFuncName);
    }

private:
    const char* _pszFuncName;

#else // defined(_DEBUG) || defined(DEBUG)

    } // end of constructor

#endif // defined(_DEBUG) || defined(DEBUG)
};


////////////////////////////////////////////////////////////////////////////
//  Declarations of exported functions
//
////////////////////////////////////////////////////////////////////////////

extern "C" {
    JNIEXPORT jlong   JNICALL MediaInfo_create(JNIEnv* pEnv, jobject self);
    JNIEXPORT void    JNICALL MediaInfo_destroy(JNIEnv* pEnv, jobject self, jlong handle);
    JNIEXPORT jint    JNICALL MediaInfo_open(JNIEnv* pEnv, jobject self, jlong handle, jstring filename);
    JNIEXPORT void    JNICALL MediaInfo_close(JNIEnv* pEnv, jobject self, jlong handle);

    JNIEXPORT jstring JNICALL MediaInfo_getById(JNIEnv* pEnv, jobject self, jlong handle, jint streamKind, jint streamNum, jint parameter);
    JNIEXPORT jstring JNICALL MediaInfo_getByName(JNIEnv* pEnv, jobject self, jlong handle, jint streamKind, jint streamNum, jstring parameter);
    JNIEXPORT jstring JNICALL MediaInfo_getByIdDetail(JNIEnv* pEnv, jobject self, jlong handle, jint streamKind, jint streamNum, jint parameter, jint kindOfInfo);
    JNIEXPORT jstring JNICALL MediaInfo_getByNameDetail(JNIEnv* pEnv, jobject self, jlong handle, jint streamKind, jint streamNum, jstring parameter, jint kindOfInfo, jint kindOfSearch);
    JNIEXPORT jstring JNICALL MediaInfo_informDetail(JNIEnv* pEnv, jobject self, jlong handle);
    JNIEXPORT jint    JNICALL MediaInfo_countGet(JNIEnv* pEnv, jobject self, jlong handle, jint streamKind, jint streamNum);
    JNIEXPORT jstring JNICALL MediaInfo_option(JNIEnv* pEnv, jobject self, jlong handle, jstring option, jstring value);
    JNIEXPORT jstring JNICALL MediaInfo_option2(JNIEnv* pEnv, jobject self, jlong handle, jstring option);
    JNIEXPORT jstring JNICALL MediaInfo_optionStatic(JNIEnv* pEnv, jclass clazz, jstring option, jstring value);
    JNIEXPORT jstring JNICALL MediaInfo_optionStatic2(JNIEnv* pEnv, jclass clazz, jstring option);

    JNIEXPORT jstring JNICALL MediaInfo_getMediaInfo(JNIEnv* pEnv, jobject self, jstring filename);
    JNIEXPORT jstring JNICALL MediaInfo_getMediaInfoOption(JNIEnv* pEnv, jobject self, jstring param);
}


static const JNINativeMethod gMethods[] = {
    { "create", "()J", (void*) MediaInfo_create},
    { "destroy", "(J)V", (void*)MediaInfo_destroy},
    { "open", "(JLjava/lang/String;)I", (void*)MediaInfo_open},
    { "close", "(J)V", (void*)MediaInfo_close},
    { "getById", "(JIII)Ljava/lang/String;", (void*)MediaInfo_getById},
    { "getByName", "(JIILjava/lang/String;)Ljava/lang/String;", (void*)MediaInfo_getByName},
    { "getByIdDetail", "(JIIII)Ljava/lang/String;", (void*)MediaInfo_getByIdDetail},
    { "getByNameDetail", "(JIILjava/lang/String;II)Ljava/lang/String;", (void*)MediaInfo_getByNameDetail},
    { "informDetail", "(J)Ljava/lang/String;", (void*)MediaInfo_informDetail},
    { "countGet", "(JII)I", (void*)MediaInfo_countGet},
    { "option", "(JLjava/lang/String;Ljava/lang/String;)Ljava/lang/String;", (void*)MediaInfo_option},
    { "option", "(JLjava/lang/String;)Ljava/lang/String;", (void*)MediaInfo_option2},
    { "optionStatic", "(Ljava/lang/String;Ljava/lang/String;)Ljava/lang/String;", (void*)MediaInfo_optionStatic},
    { "optionStatic", "(Ljava/lang/String;)Ljava/lang/String;", (void*)MediaInfo_optionStatic2},
    { "getMediaInfo", "(Ljava/lang/String;)Ljava/lang/String;", (void*)MediaInfo_getMediaInfo},
    { "getMediaInfoOption", "(Ljava/lang/String;)Ljava/lang/String;", (void*)MediaInfo_getMediaInfoOption},
};

JNIEXPORT jint JNICALL
JNI_OnLoad (JavaVM * vm, void * reserved)
{
    FuncCallLog funclog(FUNC);

    JNIEnv *env;

    if (vm->GetEnv((void**) &env, JNI_VERSION_1_6) == JNI_OK) {
        LOG("JNI_VERSION_1_6 OK!\n");
    } else if (vm->GetEnv((void**) &env, JNI_VERSION_1_4) == JNI_OK) {
        LOGW("JNI_VERSION_1_4 OK!\n");
    } else if (vm->GetEnv((void**) &env, JNI_VERSION_1_2) == JNI_OK) {
        LOGW("JNI_VERSION_1_2 OK!\n");
    } else {
        LOGE("JNI_VERSION_?_? FAIL!\n");
        return -1;
    }

    static const char* const kClassName = "org/mediainfo/android/MediaInfo";
    LOG("Registering %s natives\n", kClassName);

    jclass clazz = env->FindClass(kClassName);
    if (clazz == NULL) {
        LOGE("Native registration unable to find class '%s'!\n", kClassName);
        return -1;
    }

    if (env->RegisterNatives(clazz, gMethods, sizeof(gMethods)/sizeof(gMethods[0])) < 0) {
        LOGE("env->RegisterNatives)() fails for '%s'!\n", kClassName);
        env->DeleteLocalRef(clazz);
        return -1;
    }

    env->DeleteLocalRef(clazz);

    return JNI_VERSION_1_6;
}


////////////////////////////////////////////////////////////////////////////
//  Internal implementations
//
////////////////////////////////////////////////////////////////////////////

static inline MediaInfo*
GetMediaInfo(jlong handle)
{
    if (!handle) {
        LOGW("The mediainfo handle is invalid!\n");
    } else {
        LOG("The mediainfo handle is %lld\n", handle);
    }

    return (MediaInfo*) handle;
}

static inline stream_t
CastStreamKind(jint streamKind)
{
    assert(streamKind < Stream_Max);

    return (stream_t) streamKind;
}

static inline info_t
CastInfoKind(jint infoKind)
{
    assert(infoKind < Info_Max);

    return (info_t) infoKind;
}

static inline jstring
NewJString(JNIEnv *pEnv, String str)
{
    jsize len = str.size();
    /*const Char *raw = (Char *) str.c_str();

    // Allocate a buffer for the java string to pass JavaVM.
    // First arguments "" is such a hack for only a buffer allocation.
    jstring jstr = pEnv->NewString((jchar*)"", len);
    jchar* jchars = (jchar*) pEnv->GetStringChars(jstr, NULL);

    assert(raw != NULL);
    assert(jchars != NULL);

    // Discard two lead bytes in raw string
    while (len-- > 0) {
        *jchars++ = (jchar) *raw++;
    }

    if (!jstr) {
        LOGW("env->NewString('%s', %d) fails!\n", PrintableChars(str.c_str()), str.size());
    }*/

    char* cstr = new char[1048576];
    wcstombs(cstr, str.c_str(), len);
    jstring jstr = pEnv->NewStringUTF(cstr);
    jchar* jchars = (jchar*) pEnv->GetStringChars(jstr, NULL);

    pEnv->ReleaseStringChars(jstr, jchars);


    #if defined(_DEBUG) || defined(DEBUG)
        const char *nativeString = (pEnv)->GetStringUTFChars(jstr, NULL);
        LOG("NewJString(JNIEnv *pEnv, String str) -> jstring = '%s'\n", nativeString);
        pEnv->ReleaseStringUTFChars(jstr, nativeString);
    #endif

    return jstr;
}

class JStringHolder {
public:
    JStringHolder(JNIEnv* env, jstring jstr) : _env(env), _jstr(jstr), _jchars(NULL) {
        assert(env);
        assert(jstr);
    };

    ~JStringHolder() {
        if (_jchars)
            _env->ReleaseStringChars(_jstr, _jchars);
    }

    bool toString(String& str) {
        if (!_jchars) {
            _jchars = _env->GetStringChars(_jstr, NULL);
            if (_jchars == NULL) {
                LOGW("env->GetStringChars() fails!\n");
                return false;
            }
        }

        //
        // convert a wchar_t(maybe 4bytes) strings from a jstring(maybe 2bytes)
        //
        int jchars_len = _env->GetStringLength(_jstr);

        // allocate a actually buffer and set a given length
        str.resize(jchars_len);

        Char *cstr = (Char*) str.c_str();

        while (jchars_len-- > 0)
            *cstr++ = (Char) *_jchars++;

        return true;
    }

private:
    JNIEnv*       _env;
    jstring       _jstr;
    const jchar*  _jchars;
};


////////////////////////////////////////////////////////////////////////////
//  Implementations of exported functions
//
////////////////////////////////////////////////////////////////////////////


JNIEXPORT jlong JNICALL
MediaInfo_create(JNIEnv* pEnv, jobject self)
{
    FuncCallLog funclog(FUNC);

    MediaInfo* pMediaInfo = new MediaInfo();

    // avoid an implicit cast problem between signed and unsigned.
    jlong handle = (jlong) ((unsigned long long) pMediaInfo);

    if (handle) {
        LOG("MediaInfo->New() ok! %lld\n", handle);
    } else {
        LOGW("MediaInfo->New() fails!\n");
    }

    return handle;
}

JNIEXPORT void JNICALL
MediaInfo_destroy(JNIEnv* pEnv, jobject self, jlong handle)
{
    FuncCallLog funclog(FUNC);

    MediaInfo* pMediaInfo = GetMediaInfo(handle);

    if (pMediaInfo) {
        delete pMediaInfo;
        LOG("MediaInfo->Destroy() ok! %lld\n", handle);
    } else {
        LOGW("MediaInfo->Destroy() skip!\n");
    }
}

JNIEXPORT jint JNICALL
MediaInfo_open(JNIEnv* pEnv, jobject self, jlong handle, jstring filename)
{
    FuncCallLog funclog(FUNC);

    MediaInfo* pMediaInfo = GetMediaInfo(handle);
    if (!pMediaInfo)
        return 0;   // error

    String strFilename;
    JStringHolder jstrHolder(pEnv, filename);
    if (!jstrHolder.toString(strFilename))
        return 0;

    size_t res = pMediaInfo->Open(strFilename);
    LOG("MediaInfo->Open('%s') returns %d\n", PrintableChars(strFilename.c_str()), res);

    if (res == 0) {
        LOGW("MediaInfo->Open() fails!\n");
    }

    return (jint) res;
}

JNIEXPORT void JNICALL
MediaInfo_close(JNIEnv* pEnv, jobject self, jlong handle)
{
    FuncCallLog funclog(FUNC);

    MediaInfo* pMediaInfo = GetMediaInfo(handle);
    if (pMediaInfo)
        pMediaInfo->Close();

    //if (pMediaInfo)
    //    LOGW("MediaInfo->Close() ok!\n");
    //else
    //    LOGW("MediaInfo->Close() fail!\n");
}

JNIEXPORT jstring JNICALL
MediaInfo_getById(JNIEnv* pEnv, jobject self, jlong handle, jint streamKind, jint streamNum, jint parameter)
{
    FuncCallLog funclog(FUNC);

    MediaInfo* pMediaInfo = GetMediaInfo(handle);
    if (!pMediaInfo)
        return 0;

    String strInfo = pMediaInfo->Get(CastStreamKind(streamKind), streamNum, parameter);
    LOG("MediaInfo->Get(%d,%d,%d) returns '%s'\n",
        CastStreamKind(streamKind), streamNum, parameter, PrintableChars(strInfo.c_str()));

    return NewJString(pEnv, strInfo);
}

JNIEXPORT jstring JNICALL
MediaInfo_getByName(JNIEnv* pEnv, jobject self, jlong handle, jint streamKind, jint streamNum, jstring parameter)
{
    FuncCallLog funclog(FUNC);

    MediaInfo* pMediaInfo = GetMediaInfo(handle);
    if (!pMediaInfo)
        return 0;

    String strParameter;
    JStringHolder jstrHolder(pEnv, parameter);
    if (!jstrHolder.toString(strParameter))
        return 0;

    String strInfo = pMediaInfo->Get(CastStreamKind(streamKind), streamNum, strParameter);

    LOG("MediaInfo->Get(%d,%d,'%s') returns '%s'%d\n",
        CastStreamKind(streamKind), streamNum, PrintableChars(strParameter.c_str()), PrintableChars2(strInfo.c_str()), strInfo.length());

    return NewJString(pEnv, strInfo);
}

JNIEXPORT jstring JNICALL
MediaInfo_getByIdDetail(JNIEnv* pEnv, jobject self, jlong handle, jint streamKind, jint streamNum, jint parameter, jint kindOfInfo)
{
    FuncCallLog funclog(FUNC);

    MediaInfo* pMediaInfo = GetMediaInfo(handle);
    if (!pMediaInfo)
        return 0;

    String strInfo = pMediaInfo->Get(CastStreamKind(streamKind), streamNum, parameter,
                                     CastInfoKind(kindOfInfo));
    LOG("MediaInfo->Get(%d,%d,%d,%d) returns '%s'\n",
        CastStreamKind(streamKind), streamNum, parameter, kindOfInfo, PrintableChars(strInfo.c_str()));

    return NewJString(pEnv, strInfo);
}

JNIEXPORT jstring JNICALL
MediaInfo_getByNameDetail(JNIEnv* pEnv, jobject self, jlong handle, jint streamKind, jint streamNum, jstring parameter, jint kindOfInfo, jint kindOfSearch)
{
    FuncCallLog funclog(FUNC);

    MediaInfo* pMediaInfo = GetMediaInfo(handle);
    if (!pMediaInfo)
        return 0;

    String strParameter;
    JStringHolder jstrHolder(pEnv, parameter);
    if (!jstrHolder.toString(strParameter))
        return 0;

    String strInfo = pMediaInfo->Get(CastStreamKind(streamKind), streamNum, strParameter,
                                     CastInfoKind(kindOfInfo), CastInfoKind(kindOfSearch));

    LOG("MediaInfo->Get(%d,%d,'%s',%d,%d) returns '%s'\n",
        CastStreamKind(streamKind), streamNum, PrintableChars(strParameter.c_str()),
        CastInfoKind(kindOfInfo), CastInfoKind(kindOfSearch), PrintableChars2(strInfo.c_str()));

    return NewJString(pEnv, strInfo);
}

JNIEXPORT jstring JNICALL
MediaInfo_informDetail(JNIEnv* pEnv, jobject self, jlong handle)
{
    MediaInfo* pMediaInfo = GetMediaInfo(handle);

    if (!pMediaInfo)
        return 0;

    String strInfo = pMediaInfo->Inform();

    LOG("MediaInfo->Inform() returns '%s'.\n", PrintableChars(strInfo.c_str()));

    return NewJString(pEnv, strInfo);
}

JNIEXPORT jint JNICALL
MediaInfo_countGet(JNIEnv* pEnv, jobject self, jlong handle, jint streamKind, jint streamNum)
{
    MediaInfo* pMediaInfo = GetMediaInfo(handle);

    if (!pMediaInfo)
        return 0;

    return pMediaInfo->Count_Get(CastStreamKind(streamKind), (size_t) streamNum);
}

JNIEXPORT jstring JNICALL
MediaInfo_option(JNIEnv* pEnv, jobject self, jlong handle, jstring option, jstring value)
{
    MediaInfo* pMediaInfo = GetMediaInfo(handle);

    if (!pMediaInfo)
        return 0;

    String strOption;
    String strValue;

    JStringHolder jstrOption(pEnv, option);
    JStringHolder jstrValue(pEnv, value);

    if (!jstrOption.toString(strOption))
        return 0;

    if (!jstrValue.toString(strValue))
        return 0;

    String strResult = pMediaInfo->Option(strOption, strValue);
    LOG("MediaInfo->Option('%s', ..) returns '%s'.\n",
        PrintableChars(strOption.c_str()), PrintableChars2(strResult.c_str()));

    return NewJString(pEnv, strResult);
}

JNIEXPORT jstring JNICALL
MediaInfo_option2(JNIEnv* pEnv, jobject self, jlong handle, jstring option)
{
    MediaInfo* pMediaInfo = GetMediaInfo(handle);

    if (!pMediaInfo)
        return 0;

    String strOption;

    JStringHolder jstrOption(pEnv, option);

    if (!jstrOption.toString(strOption))
        return 0;

    String strResult = pMediaInfo->Option(strOption, __T(""));
    LOG("MediaInfo->Option('%s', ..) returns '%s'.\n",
        PrintableChars(strOption.c_str()), PrintableChars2(strResult.c_str()));

    return NewJString(pEnv, strResult);
}

JNIEXPORT jstring JNICALL
MediaInfo_optionStatic(JNIEnv* pEnv, jclass clazz, jstring option, jstring value)
{
    String strOption;
    String strValue;

    JStringHolder jstrOption(pEnv, option);
    JStringHolder jstrValue(pEnv, value);

    if (!jstrOption.toString(strOption))
        return 0;

    if (!jstrValue.toString(strValue))
        return 0;

    String strResult = MediaInfo::Option_Static(strOption, strValue);

    LOG("MediaInfo::Option_Static('%s', ..) returns '%s'.\n",
        PrintableChars(strOption.c_str()), PrintableChars2(strResult.c_str()));

    return NewJString(pEnv, strResult);
}

JNIEXPORT jstring JNICALL
MediaInfo_optionStatic2(JNIEnv* pEnv, jclass clazz, jstring option)
{
    String strOption;

    JStringHolder jstrOption(pEnv, option);

    if (!jstrOption.toString(strOption))
        return 0;

    String strResult = MediaInfo::Option_Static(strOption, __T(""));

    LOG("MediaInfo::Option_Static('%s', ..) returns '%s'.\n",
        PrintableChars(strOption.c_str()), PrintableChars2(strResult.c_str()));

    return NewJString(pEnv, strResult);
}

JNIEXPORT jstring JNICALL
MediaInfo_getMediaInfo(JNIEnv* pEnv, jobject self, jstring filename)
{
    const char *CStrfilename = pEnv->GetStringUTFChars(filename, NULL);
    if (NULL == CStrfilename)
        return NULL;

    jsize len = pEnv->GetStringUTFLength(filename);
    wchar_t* cstr = new wchar_t[1048576];;
    mbstowcs(cstr, CStrfilename, len);

    pEnv->ReleaseStringUTFChars(filename, CStrfilename);

    MediaInfo MI;

    String strInfo;

    //String strInfo = MI.Option(__T("Info_Version"), __T("0.7.0.0;MediaInfoDLL_Example_MSVC;0.7.0.0")).c_str();
    //strInfo += __T("\r\n\r\nInfo_Parameters\r\n");
    //strInfo += MI.Option(__T("Info_Parameters")).c_str();
    //strInfo += __T("\r\n\r\nInfo_Capacities\r\n");
    //strInfo += MI.Option(__T("Info_Capacities")).c_str();
    //strInfo += __T("\r\n\r\nInfo_Codecs\r\n");
    //strInfo += MI.Option(__T("Info_Codecs")).c_str();

    //strInfo += __T("\r\n\r\nOpen\r\n");
    MI.Open(cstr);
    //strInfo += __T("\r\n\r\nInform with Complete=false\r\n");
    MI.Option(__T("Complete"));
    strInfo = MI.Inform().c_str();
    //strInfo += __T("\r\n\r\nInform with Complete=true\r\n");
    //MI.Option(__T("Complete"), __T("1"));
    //strInfo += MI.Inform().c_str();
    //strInfo += __T("\r\n\r\nClose\r\n");
    MI.Close();

    LOG("MediaInfo_getMediaInfo('%s', ..) returns '%s'.\n",
        PrintableChars(strInfo.c_str()), PrintableChars2(strInfo.c_str()));

    return NewJString(pEnv, strInfo);
}

JNIEXPORT jstring JNICALL
MediaInfo_getMediaInfoOption(JNIEnv* pEnv, jobject self, jstring param)
{
    const char *CStrparam = pEnv->GetStringUTFChars(param, NULL);
    if (NULL == CStrparam)
        return NULL;

    jsize len = pEnv->GetStringUTFLength(param);
    wchar_t* cstr = new wchar_t[1048576];;
    mbstowcs(cstr, CStrparam, len);

    pEnv->ReleaseStringUTFChars(param, CStrparam);

    MediaInfo MI;

    String strInfo;

    //String strInfo = MI.Option(__T("Info_Version"), __T("0.7.0.0;MediaInfoDLL_Example_MSVC;0.7.0.0")).c_str();
    //strInfo += __T("\r\n\r\nInfo_Parameters\r\n");
    strInfo = MI.Option(cstr).c_str();
    MI.Close();

    LOG("MediaInfo_getMediaInfoOption('%s', ..) returns '%s'.\n",
        PrintableChars(strInfo.c_str()), PrintableChars2(strInfo.c_str()));

    return NewJString(pEnv, strInfo);
}
