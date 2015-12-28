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
        GENERAL,
        VIDEO,
        AUDIO,
        TEXT,
        OTHER,
        IMAGE,
        MENU,
        MAX
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
    public String get(String filename, StreamKind streamKind, int streamNum, int parameter) {
        String result = getById(filename, streamKind.ordinal(), streamNum,
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
    public String get(String filename, StreamKind streamKind, int streamNum, int parameter,
            InfoKind infoKind) {
        String result = getByIdDetail(filename, streamKind.ordinal(), streamNum,
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
    public String get(String filename, StreamKind streamKind, int streamNum, String parameter) {
        String result = getByName(filename, streamKind.ordinal(), streamNum,
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
    public String get(String filename, StreamKind streamKind, int streamNum, String parameter,
            InfoKind infoKind) {
        String result = getByNameDetail(filename, streamKind.ordinal(),
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
    public String get(String filename, StreamKind streamKind, int streamNum, String parameter,
            InfoKind infoKind, InfoKind searchKind) {
        String result = getByNameDetail(filename, streamKind.ordinal(),
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
    public int countGet(String filename, StreamKind streamKind) {
        int result = countGet(filename, streamKind.ordinal(), -1);
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
    public int countGet(String filename, StreamKind streamKind, int streamNumber) {
        int result = countGet(filename, streamKind.ordinal(), streamNumber);
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

    private native String getById(String filename, int streamKind, int streamNum,
            int parameter);

    private native String getByIdDetail(String filename, int streamKind, int streamNum,
            int parameter, int kindOfInfo);

    private native String getByName(String filename, int streamKind, int streamNum,
            String parameter);

    private native String getByNameDetail(String filename, int streamKind,
            int streamNum, String parameter, int kindOfInfo, int kindOfSearch);

    private native int countGet(String filename, int streamKind, int streamNum);

    private native String getMediaInfo(String filename);

    private native String getMediaInfoOption(String param);

    static {
        System.loadLibrary("mediainfo");
    }
}
