/*  Copyright (c) MediaArea.net SARL. All Rights Reserved.
 *
 *  Use of this source code is governed by a BSD-style license that can
 *  be found in the License.html file in the root of the source tree.
 */
package org.mediainfo.android;

/**
 * Give information about a lot of media format.
 */
public class MediaInfo {

    // @remark Don't change it carelessly.
    // This order is from MediaInfo_Const.h
    public enum StreamKind {
        GENERAL, VIDEO, AUDIO, TEXT, OTHER, IMAGE, MENU, MAX
    }

    // @remark Don't change it carelessly.
    // This order is from MediaInfo_Const.h
    public enum InfoKind {
        NAME, // Unique name of parameter
        TEXT, // Value of parameter
        MEASURE, // Unique name of measure unit of parameter
        OPTIONS, // See InfoOptionKind
        NAME_TEXT, // Translated name of parameter
        MEASURE_TEXT, // Translated name of measure unit
        INFO, // More information about the parameter
        HOWTO, // How this parameter is supported, could be N(No), B(Beta),
               // R(Read only), W(Read/Write)
        DOMAIN, // Domain of this piece of information
        MAX
    }

    public MediaInfo() {
        //handle = create();
        System.out.println("MediaInfo created");
    }

    public void dispose() {
        if (handle == 0)
            throw new IllegalStateException();

        destroy(handle);
        handle = 0;
    }

    @Override
    protected void finalize() throws Throwable {
        if (handle != 0)
            dispose();
    }

    /**
     * Open a file and collect information about it (technical information and
     * tags)
     *
     * @param filename
     *            Full name of file to open
     * @return 1 if file was opened, 0 if file was not opened
     */
    public int open(String filename) {
        int result = open(handle, filename);
        return result;
    }

    /**
     * Close a file opened before with open().
     */
    public void close() {
        close(handle);
    }

    /**
     * Get all details about a file.
     *
     * @return All details about a file in one string
     */
    public String inform() {
        String result = informDetail(handle);
        return result;
    }

    /**
     * Get a piece of information about a file. (parameter is an integer)
     *
     * @param streamKind
     *            Kind of Stream
     * @param streamNum
     *            Stream number in Kind of stream
     * @param parameter
     *            Parameter you are looking for in the stream (codec, width,
     *            bitrate, ..), in integer format
     * @return a string about information you search, an empty string if there
     *         is a problem.
     */
    public String get(StreamKind streamKind, int streamNum, int parameter) {
        String result = getById(handle, streamKind.ordinal(), streamNum,
                parameter); /* InfoKind.TEXT */
        return result;
    }

    /**
     * Get a piece of information about a file. (parameter is an integer)
     *
     * @param streamKind
     *            Kind of Stream
     * @param streamNum
     *            Stream number in Kind of stream
     * @param parameter
     *            Parameter you are looking for in the stream (codec, width,
     *            bitrate, ..), in integer format
     * @param infoKind
     *            Kind of information you want about the parameter (the text,
     *            the measure, the help, ..)
     * @return a string about information you search, an empty string if there
     *         is a problem.
     */
    public String get(StreamKind streamKind, int streamNum, int parameter,
            InfoKind infoKind) {
        String result = getByIdDetail(handle, streamKind.ordinal(), streamNum,
                parameter, infoKind.ordinal());
        return result;
    }

    /**
     * Get a piece of information about a file. (parameter is an string)
     *
     * @param streamKind
     *            Kind of Stream (general, video, audio, ..)
     * @param streamNum
     *            Stream number in Kind of stream
     * @param parameter
     *            Parameter you are looking for in the stream (codec, width,
     *            bitrate, ..), in string format ("Codec", "Width", ..)
     * @return a string about information you search, an empty string if there
     *         is a problem
     */
    public String get(StreamKind streamKind, int streamNum, String parameter) {
        String result = getByName(handle, streamKind.ordinal(), streamNum,
                parameter); /* InfoKind.TEXT, InfoKind.NAME */
        return result;
    }

    /**
     * Get a piece of information about a file. (parameter is an string)
     *
     * @param streamKind
     *            Kind of Stream (general, video, audio, ..)
     * @param streamNum
     *            Stream number in Kind of stream
     * @param parameter
     *            Parameter you are looking for in the stream (codec, width,
     *            bitrate, ..), in string format ("Codec", "Width", ..)
     * @param infoKind
     *            Kind of information you want about the parameter (the text,
     *            the measure, the help, ..)
     * @return a string about information you search, an empty string if there
     *         is a problem.
     */
    public String get(StreamKind streamKind, int streamNum, String parameter,
            InfoKind infoKind) {
        String result = getByNameDetail(handle, streamKind.ordinal(),
                streamNum, parameter, infoKind.ordinal(),
                InfoKind.NAME.ordinal());
        return result;
    }

    /**
     * Get a piece of information about a file. (parameter is an string)
     *
     * @param streamKind
     *            Kind of Stream (general, video, audio, ..)
     * @param streamNum
     *            Stream number in Kind of stream
     * @param parameter
     *            Parameter you are looking for in the stream (codec, width,
     *            bitrate, ..), in string format ("Codec", "Width", ..)
     * @param infoKind
     *            Kind of information you want about the parameter (the text,
     *            the measure, the help, ..)
     * @param searchKind
     *            Where to look for the parameter
     * @return a string about information you search, an empty string if there
     *         is a problem.
     */
    public String get(StreamKind streamKind, int streamNum, String parameter,
            InfoKind infoKind, InfoKind searchKind) {
        String result = getByNameDetail(handle, streamKind.ordinal(),
                streamNum, parameter, infoKind.ordinal(), searchKind.ordinal());
        return result;
    }

    /**
     * Count of streams of a stream kin (StreamNumber not filled), or count of
     * piece of information in this stream.
     *
     * @param streamKind
     *            Kind of Stream (general, video, audio, ..)
     * @return number of streams of the given stream kind
     */
    public int countGet(StreamKind streamKind) {
        int result = countGet(handle, streamKind.ordinal(), -1);
        return result;
    }

    /**
     * Count of streams of a stream kin (StreamNumber not filled), or count of
     * piece of information in this stream.
     *
     * @param streamKind
     *            Kind of Stream (general, video, audio, ..)
     * @param streamNumber
     *            Stream number in Kind of stream
     * @return number of streams of the given stream kind
     */
    public int countGet(StreamKind streamKind, int streamNumber) {
        int result = countGet(handle, streamKind.ordinal(), streamNumber);
        return result;
    }

    /**
     * Configure or get information about MediaInfo
     *
     * @param name
     *            The name of option
     * @return
     */
    public String option(String name) {
        String result = option(handle, name);
        return result;
    }

    public String getMI(String filename) {
        String result = getMediaInfo(filename);
        return result;
    }

    public String getMIOption(String param) {
        String result = getMediaInfoOption(param);
        return result;
    }

    /**
     * Configuration or get information about MediaInfo
     * <p/>
     * <ul>
     * Known options are (refer to a native MediaInfoLib):
     * <li>(NOT IMPLEMENTED YET) "BlockMethod": Configure when Open Method must
     * return (default or not command not understood: "1")
     * <ul>
     * <li>"0": immediately
     * <li>"1": After getting local information
     * <li>"2": When user interaction is needed, or when Internet information is
     * get
     * </ul>
     * <li>"Complete": For debug, configure if MediaInfoLib::Inform() show all
     * information (doesn't care of InfoOption_NoShow tag): shows all
     * information if true, shows only useful for user information if false (No
     * by default)
     * <li>"Complete_Get": return the state of "Complete"
     * <li>"Language": Configure language (default language, and this object);
     * Value is Description of language (format: "Column1;Colum2...)
     * <ul>
     * <li>Column 1: Unique name ("Bytes", "Title")
     * <li>Column 2: translation ("Octets", "Titre")
     * </ul>
     * <li>"Language_Get": Get the language file in memory
     * <li>"Language_Update": Configure language of this object only (for
     * optimization); Value is Description of language (format:
     * "Column1;Colum2...)
     * <ul>
     * <li>Column 1: Unique name ("Bytes", "Title")
     * <li>Column 2: translation ("Octets", "Titre")
     * </ul>
     * <li>"Inform": Configure custom text, See MediaInfoLib::Inform() function;
     * Description of views (format: "Column1;Colum2...)
     * <ul>
     * <li>Column 1: code (11 lines: "General", "Video", "Audio", "Text",
     * "Other", "Begin", "End", "Page_Begin", "Page_Middle", "Page_End")
     * <li>Column 2: The text to show (example:
     * "Audio: %FileName% is at %BitRate/String%")
     * </ul>
     * <li>"ParseUnknownExtensions": Configure if MediaInfo parse files with
     * unknown extension
     * <li>"ParseUnknownExtensions_Get": Get if MediaInfo parse files with
     * unknown extension
     * <li>"ShowFiles": Configure if MediaInfo keep in memory files with
     * specific kind of streams (or no streams); Value is Description of
     * components (format: "Column1;Colum2...)
     * <ul>
     * <li>Column 1: code (available: "Nothing" for unknown format, "VideoAudio"
     * for at least 1 video and 1 audio, "VideoOnly" for video streams only,
     * "AudioOnly", "TextOnly")
     * <li>Column 2: "" (nothing) not keeping, other for keeping
     * </ul>
     * <li>(NOT IMPLEMENTED YET) "TagSeparator": Configure the separator if
     * there are multiple same tags (" | " by default)
     * <li>(NOT IMPLEMENTED YET) "TagSeparator_Get": return the state of
     * "TagSeparator"
     * <li>(NOT IMPLEMENTED YET) "Internet": Authorize Internet connection (Yes
     * by default)
     * <li>(NOT IMPLEMENTED YET) "Internet_Title_Get": When State=5000, give all
     * possible titles for this file (one per line)
     * <ul>
     * <li>Form: Author TagSeparator Title TagSeparator Year...
     * </ul>
     * <li>(NOT IMPLEMENTED YET) "Internet_Title_Set": Set the Good title (same
     * as given by Internet_Title_Get)
     * <ul>
     * <li>Form: Author TagSeparator Title TagSeparator Year
     * </ul>
     * <li>"Info_Parameters": Information about what are known unique names for
     * parameters
     * <li>"Info_Parameters_CSV": Information about what are known unique names
     * for parameters, in CSV format
     * </ul>
     *
     * @param name
     *            The name of option
     * @param value
     *            The value of option
     * @return Depend of the option: "" by default means No, other means Yes
     */
    public String option(String name, String value) {
        String result = option(handle, name, value);
        return result;
    }

    /**
     * Configure or get information about MediaInfo (static version).
     *
     * @param name
     *            the name of option
     * @return
     */
    public native static String optionStatic(String name);

    /**
     * Configure or get information about MediaInfo (static version).
     *
     * @param name
     *            the name of option
     * @param value
     *            the name of option
     * @return Depend of the option: "" by default means No, other means Yes
     */
    public native static String optionStatic(String name, String value);

    //
    // private, protected, static
    //

    private long handle;

    private native long create();

    private native void destroy(long handle);

    private native int open(long handle, String filename);

    private native void close(long handle);

    private native String getById(long handle, int streamKind, int streamNum,
            int parameter);

    private native String getByIdDetail(long handle, int streamKind,
            int streamNum, int parameter, int kindOfInfo);

    private native String getByName(long handle, int streamKind, int streamNum,
            String parameter);

    private native String getByNameDetail(long handle, int streamKind,
            int streamNum, String parameter, int kindOfInfo, int kindOfSearch);

    private native String informDetail(long handle);

    private native int countGet(long handle, int streamKind, int streamNum);

    private native String option(long handle, String option, String value);

    private native String option(long handle, String option);

    private native String getMediaInfo(String filename);

    private native String getMediaInfoOption(String param);

    static {
        System.loadLibrary("mediainfo");
    }
}
