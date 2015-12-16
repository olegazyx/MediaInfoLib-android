#include <stdlib.h>
#include <wchar.h>

extern "C" {


extern size_t mbstowcs(wchar_t* wcstr, const char* mbstr, size_t max);
extern size_t wcstombs(char* mbstr, const wchar_t* wcstr, size_t max);
extern int wctomb(char *pmb, wchar_t character);
extern size_t wcrtomb(char *, wchar_t, mbstate_t *);



//
// Bellow lines from converters.h
//
typedef unsigned int ucs4_t;
typedef struct conv_struct * conv_t;
typedef struct {
  unsigned short indx; /* index into big table */
  unsigned short used; /* bitmask of used entries */
} Summary16;
/* Return code if invalid input after a shift sequence of n bytes was read.
   (xxx_mbtowc) */
#define RET_SHIFT_ILSEQ(n)  (-1-2*(n))
/* Return code if invalid. (xxx_mbtowc) */
#define RET_ILSEQ           RET_SHIFT_ILSEQ(0)
/* Return code if only a shift sequence of n bytes was read. (xxx_mbtowc) */
#define RET_TOOFEW(n)       (-2-2*(n))
/* Return code if invalid. (xxx_wctomb) */
#define RET_ILUNI      -1
/* Return code if output buffer is too small. (xxx_wctomb, xxx_reset) */
#define RET_TOOSMALL   -2

//#define NULL (0)
#define MB_MAX_LEN      (8)

//#include "libiconv/lib/ascii.h"
//#include "libiconv/lib/ksc5601.h"
//#include "libiconv/lib/cp949.h"
#include "libiconv/lib/utf8.h"

#include <android/log.h>

//#define LOG(...)  __android_log_print(ANDROID_LOG_DEBUG, "android-extra", __VA_ARGS__)
#define LOG(...)  ((void)0)
#define LOGW(...)  __android_log_print(ANDROID_LOG_WARN, "android-extra", __VA_ARGS__)



/**
 * Convert multibyte character to wide character.
 * The C multibyte character string @p mbstr is interpreted character by character
 * and translated to its @c wchar_t equivalent, which is stored in the location
 * pointed by @p wcstr. The length in characters of the resulting string, not
 * including the ending null-character, is returned.
 *
 * @param   wcstr Pointer to an array of @c wchar_t elements long enough to store
 *                a wide string @p max characters long.
 * @param   mbstr C multibyte character string to be interpreted.
 * @param   max Maximum number of @c wchar_t characters to be interpreted.
 * @return  The number of characters translated, not including the ending
 *          null-character.If an invalid multibyte character is encountered,
 *          a @c -1 value is returned.
 */
size_t mbstowcs(wchar_t* wcstr, const char* mbstr, size_t max)
{
    LOG("mbstowcs()\n");

    if (!mbstr)
        return (size_t) -1;

    const conv_t    conv = 0;  // dummy handle for iconv
    const char*     p = mbstr;
    const char*     mbend;
    ucs4_t          wc;
    int             res;

    mbend = mbstr;
    while (*mbend)
        ++mbend;

    if (!wcstr) { // count only mode
        int count = 0;

        while (*p) {
            
            res = utf8_mbtowc(conv, &wc, (const unsigned char*) p, mbend - p);
            //LOGW("utf8_mbtowc(conv, &wc, '%s', %d) return %d", p, mbend - p, res);
            //res = cp949_mbtowc(conv, &wc, (const unsigned char*) p, mbend - p);
            //LOG("cp949_mbtowc(conv, &wc, '%s', %d) return %d", p, mbend - p, res);
            if (res <= 0) {
                //LOGW("mbstowcs(NULL, '%s', %d) returns %d", mbstr, max, -1);
                return (size_t) -1;
            }

            ; // not store into wcstr

            p += res;
            ++count;
        }

        res = count;
        LOG("mbstowcs(NULL, '%s', %d) returns %d", mbstr, max, res);
        //LOGW("mbstowcs(NULL, '%s', %d) returns %d", mbstr, max, res);

    } else {

        const wchar_t* tend = wcstr + max;
        wchar_t* t = wcstr;
 
        while ((p < mbend) && (t < tend)) {
            res = utf8_mbtowc(conv, &wc, (const unsigned char*) p, mbend - p);
            //LOGW("utf8_mbtowc(conv, &wc, '%s', %d) return %d", p, mbend - p, res);
            //res = cp949_mbtowc(conv, &wc, (const unsigned char*) p, mbend - p);
            //LOG("cp949_mbtowc(conv, &wc, '%s', %d) return %d", p, mbend - p, res);
            if (res <= 0) {
                //LOGW("mbstowcs(wchar_t*, '%s', %d) returns %d", mbstr, max, -1);
                return (size_t) -1;
            }
 
            *t++ = (wchar_t) wc;
 
            p += res;
        }
 
        res = t - wcstr;

        LOG("mbstowcs(%x %x %x, '%s', %d) returns %d", wcstr[0], wcstr[1], wcstr[2], mbstr, max, res);
        //LOGW("mbstowcs(%x %x %x, '%s', %d) returns %d", wcstr[0], wcstr[1], wcstr[2], mbstr, max, res);
    }

    return res;
}

/**
 * Convert wide-character string to multibyte string.
 * The C @c wchar_t string @p wcstr is interpreted character by character and
 * translated to its multibyte equivalent, which is stored in the location
 * pointed by @p mbstr. The length in bytes of the resulting multibyte string,
 * not including the ending null-character, is returned.
 *
 * @param   mbstr Pointer to an array of char elements at least max bytes long.
 * @param   wcstr C @c wchar_t string to be translated.
 * @param   max Maximum number of bytes to be written to @p mbstr. 
 * @return  The number of bytes (not characters) translated and written to
 *          @p mbstr, not including the ending null-character. If an invalid
 *          multibyte character is encountered, a @c -1 value is returned.
 */
size_t wcstombs(char* mbstr, const wchar_t* wcstr, size_t max)
{
    LOG("wcstombs()\n");

    if (!wcstr)
        return (size_t) -1;

    const conv_t    conv = 0;  // dummy handle for iconv
    const wchar_t*  pwc = wcstr;
    const wchar_t*  wcend;
    int             res;

    wcend = wcstr;
    while (*wcend)
        ++wcend;

    if (!mbstr) { // count only mode
        unsigned char cbuf[MB_MAX_LEN];
        int count = 0;

        while (*pwc) {
            
            res = utf8_wctomb(conv, cbuf, *pwc, MB_MAX_LEN);
            //res = cp949_wctomb(conv, cbuf, *pwc, MB_MAX_LEN);

            if (res <= 0) {
                //LOGW("wcstombs(NULL, %s, %d) returns %d", wcstr, max, -1);
                return (size_t) -1;
            }

            ; // not store into mbstr

            ++pwc;
            count += res;
        }

        res = count;

    } else {

        const char* tend = mbstr + max;
        char* t = mbstr;
 
        while ((pwc < wcend) && (t < tend)) {
            res = utf8_wctomb(conv, (unsigned char*)t, *pwc, tend - t);
            //res = cp949_wctomb(conv, (unsigned char*)t, *pwc, tend - t);
            //LOG("cp949_wctomb(conv, t, wc, %d) return %d", tend - t, res);

            if (res <= 0) {
                //LOGW("wcstombs(char*, %s, %d) returns %d", wcstr, max, -1);
                return (size_t) -1;
            }
 
            ++pwc;
            t += res;
        }
 
        res = t - mbstr;
    }

    LOG("wcstombs(char*, '%s', %d) returns %d", wcstr, max, res);
    return res;
}

/**
 * Convert wide character to multibyte character.
 * The wide @p character specified as second argument is translated to its
 * multibyte equivalent and stored in the array pointed by @p pmb. The length
 * in bytes of the equivalent multibyte character pointed by @p pmb is returned.
 * @c wctomb has its own internal @p shift state, which is altered as necessary
 * only by calls to this function.
 *
 * @param   pmb Pointer to an array large enough to hold a multibyte character,
 *          which at most is @c MB_CUR_MAX. Alternativelly, the function may be
 *          called with a null pointer, in which case the function resets its
 *          internal shift state to the initial value and returns whether
 *          multibyte characters have state-dependent encodings or not.
 *
 * @param   character Wide character of type @c wchar_t.
 * @return  If the argument passed as @p pmb is not a null pointer, the size in
 *          bytes of the character pointed by @p pmb is returned when it forms
 *          a valid multibyte character and is not the terminating null character.
 *          If it is the terminating null character, the function returns zero,
 *          and in the case they do not form a valid multibyte character,
 *          @c -1 is returned. If the argument passed as @p pmb is a null pointer,
 *          the function returns a nonzero value if multibyte character encodings
 *          are state-dependent, and zero otherwise.
 */
int wctomb(char *pmb, wchar_t character)
{
    LOG("wctomb()\n");

    if (!pmb) {
        LOGW("wctomb(NULL, wchar_t %d) returns %d", character, 0);
        return 0;
    }

    const conv_t conv = 0; // dummy handle for iconv
    int res = utf8_wctomb(conv, (unsigned char*)pmb, character, MB_MAX_LEN);
    //int res = cp949_wctomb(conv, (unsigned char*)pmb, character, MB_MAX_LEN);
    if (res < 0)
        res = -1;

    LOG("wctomb(pmb, %c) returns %d\n", character, res);
    return res;
}

// convert a wide-character code to a character (restartable) 
size_t wcrtomb(char *s, wchar_t wc, mbstate_t *ps)
{
    return wctomb(s, wc);
}


} /* extern "C" */

