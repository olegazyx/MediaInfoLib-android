###################################################
# MediaInfo library
#

#to build this file look at
#  ../libmediainfo_0.7.81/MediaInfoLib/Project/CMake/CMakeLists.txt
#  ../libmediainfo_0.7.81/ZenLib/Project/CMake/CMakeLists.txt
#
# section:
#  set(ZenLib_SRCS
#  ${ZenLib_SOURCES_PATH}...
#
# section:
#  set(MediaInfoLib_SRCS
#  ${MediaInfoLib_SOURCES_PATH}...
#

LOCAL_PATH := $(call my-dir)

MEDIAINFO_DIR        = ../libmediainfo_0.7.81
LIBZEN_INC_DIR       = $(MEDIAINFO_DIR)/ZenLib/Source
LIBZEN_SRC_DIR       = $(MEDIAINFO_DIR)/ZenLib/Source/ZenLib
LIBMEDIAINFO_INC_DIR = $(MEDIAINFO_DIR)/MediaInfoLib/Source
LIBMEDIAINFO_SRC_DIR = $(MEDIAINFO_DIR)/MediaInfoLib/Source/MediaInfo
THIRDPARTY_DIR       = ../thirdparty

USER_CFLAGS        += -DUNICODE
USER_CFLAGS        += -DMEDIAINFO_LIBCURL_NO
USER_CFLAGS        += -DMEDIAINFO_LIBMMS_NO

USER_CFLAGS        += -D_LARGE_FILES
USER_CFLAGS        += -D_FILE_OFFSET_BITS=64

USER_CFLAGS        += -fPIC

# In ZenLib, refer to int128s and int128u implelment
USER_CFLAGS        += -D__NO_LONG_DOUBLE_MATH

# Comment out for debug msg from library
#USER_CFLAGS        += -DDEBUG -D_DEBUG
#USER_CFLAGS        += -DMEDIAINFO_TRACE_YES    # default: NO
## flags bellow make file in /tmp, to change place edit MediaInfo_Internal.cpp, line 67
#USER_CFLAGS        += -DMEDIAINFO_DEBUG_OUTPUT
#USER_CFLAGS        += -DMEDIAINFO_DEBUG_CONFIG
#USER_CFLAGS        += -DMEDIAINFO_DEBUG_WARNING_GET
#USER_CFLAGS        += -DMEDIAINFO_DEBUG_BUFFER

#
# libmediainfo library configurations
#
include $(CLEAR_VARS)

LOCAL_MODULE    := libmediainfo
LOCAL_SRC_FILES := \
    $(THIRDPARTY_DIR)/glob/glob.c \
    $(LIBZEN_SRC_DIR)/Conf.cpp \
    $(LIBZEN_SRC_DIR)/CriticalSection.cpp \
    $(LIBZEN_SRC_DIR)/Dir.cpp \
    $(LIBZEN_SRC_DIR)/File.cpp \
    $(LIBZEN_SRC_DIR)/FileName.cpp \
    $(LIBZEN_SRC_DIR)/InfoMap.cpp \
    $(LIBZEN_SRC_DIR)/int128s.cpp \
    $(LIBZEN_SRC_DIR)/int128u.cpp \
    $(LIBZEN_SRC_DIR)/MemoryDebug.cpp \
    $(LIBZEN_SRC_DIR)/OS_Utils.cpp \
    $(LIBZEN_SRC_DIR)/Translation.cpp \
    $(LIBZEN_SRC_DIR)/Thread.cpp \
    $(LIBZEN_SRC_DIR)/Utils.cpp \
    $(LIBZEN_SRC_DIR)/Ztring.cpp \
    $(LIBZEN_SRC_DIR)/ZtringList.cpp \
    $(LIBZEN_SRC_DIR)/ZtringListList.cpp \
    $(LIBZEN_SRC_DIR)/ZtringListListF.cpp \
    $(LIBZEN_SRC_DIR)/Format/Html/Html_Handler.cpp \
    $(LIBZEN_SRC_DIR)/Format/Html/Html_Request.cpp \
    $(LIBZEN_SRC_DIR)/Format/Http/Http_Cookies.cpp \
    $(LIBZEN_SRC_DIR)/Format/Http/Http_Handler.cpp \
    $(LIBZEN_SRC_DIR)/Format/Http/Http_Request.cpp \
    $(LIBZEN_SRC_DIR)/Format/Http/Http_Utils.cpp \
    $(LIBMEDIAINFO_SRC_DIR)/File__Analyze.cpp \
    $(LIBMEDIAINFO_SRC_DIR)/File__Analyze_Buffer.cpp \
    $(LIBMEDIAINFO_SRC_DIR)/File__Analyze_Buffer_MinimizeSize.cpp \
    $(LIBMEDIAINFO_SRC_DIR)/File__Analyze_Streams.cpp \
    $(LIBMEDIAINFO_SRC_DIR)/File__Analyze_Streams_Finish.cpp \
    $(LIBMEDIAINFO_SRC_DIR)/File__Base.cpp \
    $(LIBMEDIAINFO_SRC_DIR)/File__MultipleParsing.cpp \
    $(LIBMEDIAINFO_SRC_DIR)/File__Duplicate.cpp \
    $(LIBMEDIAINFO_SRC_DIR)/File_Dummy.cpp \
    $(LIBMEDIAINFO_SRC_DIR)/File_Other.cpp \
    $(LIBMEDIAINFO_SRC_DIR)/File_Unknown.cpp \
    $(LIBMEDIAINFO_SRC_DIR)/HashWrapper.cpp \
    $(LIBMEDIAINFO_SRC_DIR)/MediaInfo.cpp \
    $(LIBMEDIAINFO_SRC_DIR)/MediaInfo_Config.cpp \
    $(LIBMEDIAINFO_SRC_DIR)/MediaInfo_Config_Automatic.cpp \
    $(LIBMEDIAINFO_SRC_DIR)/MediaInfo_Config_MediaInfo.cpp \
    $(LIBMEDIAINFO_SRC_DIR)/MediaInfo_Config_PerPackage.cpp \
    $(LIBMEDIAINFO_SRC_DIR)/MediaInfo_File.cpp \
    $(LIBMEDIAINFO_SRC_DIR)/MediaInfo_Inform.cpp \
    $(LIBMEDIAINFO_SRC_DIR)/MediaInfo_Internal.cpp \
    $(LIBMEDIAINFO_SRC_DIR)/MediaInfoList.cpp \
    $(LIBMEDIAINFO_SRC_DIR)/MediaInfoList_Internal.cpp \
    $(LIBMEDIAINFO_SRC_DIR)/TimeCode.cpp \
    $(LIBMEDIAINFO_SRC_DIR)/Archive/File_7z.cpp \
    $(LIBMEDIAINFO_SRC_DIR)/Archive/File_Ace.cpp \
    $(LIBMEDIAINFO_SRC_DIR)/Archive/File_Bzip2.cpp \
    $(LIBMEDIAINFO_SRC_DIR)/Archive/File_Elf.cpp \
    $(LIBMEDIAINFO_SRC_DIR)/Archive/File_Gzip.cpp \
    $(LIBMEDIAINFO_SRC_DIR)/Archive/File_Iso9660.cpp \
    $(LIBMEDIAINFO_SRC_DIR)/Archive/File_Mz.cpp \
    $(LIBMEDIAINFO_SRC_DIR)/Archive/File_Rar.cpp \
    $(LIBMEDIAINFO_SRC_DIR)/Archive/File_Tar.cpp \
    $(LIBMEDIAINFO_SRC_DIR)/Archive/File_Zip.cpp \
    $(LIBMEDIAINFO_SRC_DIR)/Audio/File_Aac.cpp \
    $(LIBMEDIAINFO_SRC_DIR)/Audio/File_Aac_GeneralAudio.cpp \
    $(LIBMEDIAINFO_SRC_DIR)/Audio/File_Aac_GeneralAudio_Sbr.cpp \
    $(LIBMEDIAINFO_SRC_DIR)/Audio/File_Aac_GeneralAudio_Sbr_Ps.cpp \
    $(LIBMEDIAINFO_SRC_DIR)/Audio/File_Aac_Main.cpp \
    $(LIBMEDIAINFO_SRC_DIR)/Audio/File_Aac_Others.cpp \
    $(LIBMEDIAINFO_SRC_DIR)/Audio/File_Ac3.cpp \
    $(LIBMEDIAINFO_SRC_DIR)/Audio/File_Adpcm.cpp \
    $(LIBMEDIAINFO_SRC_DIR)/Audio/File_Als.cpp \
    $(LIBMEDIAINFO_SRC_DIR)/Audio/File_Amr.cpp \
    $(LIBMEDIAINFO_SRC_DIR)/Audio/File_Amv.cpp \
    $(LIBMEDIAINFO_SRC_DIR)/Audio/File_Ape.cpp \
    $(LIBMEDIAINFO_SRC_DIR)/Audio/File_Au.cpp \
    $(LIBMEDIAINFO_SRC_DIR)/Audio/File_Caf.cpp \
    $(LIBMEDIAINFO_SRC_DIR)/Audio/File_Celt.cpp \
    $(LIBMEDIAINFO_SRC_DIR)/Audio/File_ChannelGrouping.cpp \
    $(LIBMEDIAINFO_SRC_DIR)/Audio/File_Dts.cpp \
    $(LIBMEDIAINFO_SRC_DIR)/Audio/File_DolbyE.cpp \
    $(LIBMEDIAINFO_SRC_DIR)/Audio/File_ExtendedModule.cpp \
    $(LIBMEDIAINFO_SRC_DIR)/Audio/File_Flac.cpp \
    $(LIBMEDIAINFO_SRC_DIR)/Audio/File_ImpulseTracker.cpp \
    $(LIBMEDIAINFO_SRC_DIR)/Audio/File_La.cpp \
    $(LIBMEDIAINFO_SRC_DIR)/Audio/File_Midi.cpp \
    $(LIBMEDIAINFO_SRC_DIR)/Audio/File_Module.cpp \
    $(LIBMEDIAINFO_SRC_DIR)/Audio/File_Mpc.cpp \
    $(LIBMEDIAINFO_SRC_DIR)/Audio/File_MpcSv8.cpp \
    $(LIBMEDIAINFO_SRC_DIR)/Audio/File_Mpega.cpp \
    $(LIBMEDIAINFO_SRC_DIR)/Audio/File_OpenMG.cpp \
    $(LIBMEDIAINFO_SRC_DIR)/Audio/File_Opus.cpp \
    $(LIBMEDIAINFO_SRC_DIR)/Audio/File_Pcm.cpp \
    $(LIBMEDIAINFO_SRC_DIR)/Audio/File_Pcm_M2ts.cpp \
    $(LIBMEDIAINFO_SRC_DIR)/Audio/File_Pcm_Vob.cpp \
    $(LIBMEDIAINFO_SRC_DIR)/Audio/File_Ps2Audio.cpp \
    $(LIBMEDIAINFO_SRC_DIR)/Audio/File_Rkau.cpp \
    $(LIBMEDIAINFO_SRC_DIR)/Audio/File_ScreamTracker3.cpp \
    $(LIBMEDIAINFO_SRC_DIR)/Audio/File_SmpteSt0302.cpp \
    $(LIBMEDIAINFO_SRC_DIR)/Audio/File_SmpteSt0337.cpp \
    $(LIBMEDIAINFO_SRC_DIR)/Audio/File_SmpteSt0331.cpp \
    $(LIBMEDIAINFO_SRC_DIR)/Audio/File_Speex.cpp \
    $(LIBMEDIAINFO_SRC_DIR)/Audio/File_Tak.cpp \
    $(LIBMEDIAINFO_SRC_DIR)/Audio/File_Tta.cpp \
    $(LIBMEDIAINFO_SRC_DIR)/Audio/File_TwinVQ.cpp \
    $(LIBMEDIAINFO_SRC_DIR)/Audio/File_Vorbis.cpp \
    $(LIBMEDIAINFO_SRC_DIR)/Audio/File_Wvpk.cpp \
    $(LIBMEDIAINFO_SRC_DIR)/Duplicate/File__Duplicate__Base.cpp \
    $(LIBMEDIAINFO_SRC_DIR)/Duplicate/File__Duplicate__Writer.cpp \
    $(LIBMEDIAINFO_SRC_DIR)/Duplicate/File__Duplicate_MpegTs.cpp \
    $(LIBMEDIAINFO_SRC_DIR)/Export/Export_EbuCore.cpp \
    $(LIBMEDIAINFO_SRC_DIR)/Export/Export_Fims.cpp \
    $(LIBMEDIAINFO_SRC_DIR)/Export/Export_Mpeg7.cpp \
    $(LIBMEDIAINFO_SRC_DIR)/Export/Export_PBCore.cpp \
    $(LIBMEDIAINFO_SRC_DIR)/Export/Export_PBCore2.cpp \
    $(LIBMEDIAINFO_SRC_DIR)/Export/Export_reVTMD.cpp \
    $(LIBMEDIAINFO_SRC_DIR)/Image/File_ArriRaw.cpp \
    $(LIBMEDIAINFO_SRC_DIR)/Image/File_Bmp.cpp \
    $(LIBMEDIAINFO_SRC_DIR)/Image/File_Bpg.cpp \
    $(LIBMEDIAINFO_SRC_DIR)/Image/File_Dds.cpp \
    $(LIBMEDIAINFO_SRC_DIR)/Image/File_Dpx.cpp \
    $(LIBMEDIAINFO_SRC_DIR)/Image/File_Exr.cpp \
    $(LIBMEDIAINFO_SRC_DIR)/Image/File_Gif.cpp \
    $(LIBMEDIAINFO_SRC_DIR)/Image/File_Ico.cpp \
    $(LIBMEDIAINFO_SRC_DIR)/Image/File_Jpeg.cpp \
    $(LIBMEDIAINFO_SRC_DIR)/Image/File_Pcx.cpp \
    $(LIBMEDIAINFO_SRC_DIR)/Image/File_Png.cpp \
    $(LIBMEDIAINFO_SRC_DIR)/Image/File_Psd.cpp \
    $(LIBMEDIAINFO_SRC_DIR)/Image/File_Rle.cpp \
    $(LIBMEDIAINFO_SRC_DIR)/Image/File_Tiff.cpp \
    $(LIBMEDIAINFO_SRC_DIR)/Image/File_Tga.cpp \
    $(LIBMEDIAINFO_SRC_DIR)/Multiple/File__ReferenceFilesHelper.cpp \
    $(LIBMEDIAINFO_SRC_DIR)/Multiple/File__ReferenceFilesHelper_Resource.cpp \
    $(LIBMEDIAINFO_SRC_DIR)/Multiple/File__ReferenceFilesHelper_Sequence.cpp \
    $(LIBMEDIAINFO_SRC_DIR)/Multiple/File_Aaf.cpp \
    $(LIBMEDIAINFO_SRC_DIR)/Multiple/File_Ancillary.cpp \
    $(LIBMEDIAINFO_SRC_DIR)/Multiple/File_Bdmv.cpp \
    $(LIBMEDIAINFO_SRC_DIR)/Multiple/File_Cdxa.cpp \
    $(LIBMEDIAINFO_SRC_DIR)/Multiple/File_DashMpd.cpp \
    $(LIBMEDIAINFO_SRC_DIR)/Multiple/File_DcpAm.cpp \
    $(LIBMEDIAINFO_SRC_DIR)/Multiple/File_DcpCpl.cpp \
    $(LIBMEDIAINFO_SRC_DIR)/Multiple/File_DcpPkl.cpp \
    $(LIBMEDIAINFO_SRC_DIR)/Multiple/File_Dpg.cpp \
    $(LIBMEDIAINFO_SRC_DIR)/Multiple/File_DvDif.cpp \
    $(LIBMEDIAINFO_SRC_DIR)/Multiple/File_DvDif_Analysis.cpp \
    $(LIBMEDIAINFO_SRC_DIR)/Multiple/File_Dvdv.cpp \
    $(LIBMEDIAINFO_SRC_DIR)/Multiple/File_Dxw.cpp \
    $(LIBMEDIAINFO_SRC_DIR)/Multiple/File_Flv.cpp \
    $(LIBMEDIAINFO_SRC_DIR)/Multiple/File_HdsF4m.cpp \
    $(LIBMEDIAINFO_SRC_DIR)/Multiple/File_Hls.cpp \
    $(LIBMEDIAINFO_SRC_DIR)/Multiple/File_Gxf.cpp \
    $(LIBMEDIAINFO_SRC_DIR)/Multiple/File_Gxf_TimeCode.cpp \
    $(LIBMEDIAINFO_SRC_DIR)/Multiple/File_Ibi.cpp \
    $(LIBMEDIAINFO_SRC_DIR)/Multiple/File_Ibi_Creation.cpp \
    $(LIBMEDIAINFO_SRC_DIR)/Multiple/File_Ism.cpp \
    $(LIBMEDIAINFO_SRC_DIR)/Multiple/File_Ivf.cpp \
    $(LIBMEDIAINFO_SRC_DIR)/Multiple/File_Lxf.cpp \
    $(LIBMEDIAINFO_SRC_DIR)/Multiple/File_Mk.cpp \
    $(LIBMEDIAINFO_SRC_DIR)/Multiple/File_Mpeg4.cpp \
    $(LIBMEDIAINFO_SRC_DIR)/Multiple/File_Mpeg4_Descriptors.cpp \
    $(LIBMEDIAINFO_SRC_DIR)/Multiple/File_Mpeg4_Elements.cpp \
    $(LIBMEDIAINFO_SRC_DIR)/Multiple/File_Mpeg4_TimeCode.cpp \
    $(LIBMEDIAINFO_SRC_DIR)/Multiple/File_Mpeg_Descriptors.cpp \
    $(LIBMEDIAINFO_SRC_DIR)/Multiple/File_Mpeg_Psi.cpp \
    $(LIBMEDIAINFO_SRC_DIR)/Multiple/File_MpegPs.cpp \
    $(LIBMEDIAINFO_SRC_DIR)/Multiple/File_MpegTs.cpp \
    $(LIBMEDIAINFO_SRC_DIR)/Multiple/File_MpegTs_Duplicate.cpp \
    $(LIBMEDIAINFO_SRC_DIR)/Multiple/File_Mxf.cpp \
    $(LIBMEDIAINFO_SRC_DIR)/Multiple/File_Nut.cpp \
    $(LIBMEDIAINFO_SRC_DIR)/Multiple/File_Ogg.cpp \
    $(LIBMEDIAINFO_SRC_DIR)/Multiple/File_Ogg_SubElement.cpp \
    $(LIBMEDIAINFO_SRC_DIR)/Multiple/File_P2_Clip.cpp \
    $(LIBMEDIAINFO_SRC_DIR)/Multiple/File_Pmp.cpp \
    $(LIBMEDIAINFO_SRC_DIR)/Multiple/File_Ptx.cpp \
    $(LIBMEDIAINFO_SRC_DIR)/Multiple/File_Riff.cpp \
    $(LIBMEDIAINFO_SRC_DIR)/Multiple/File_Riff_Elements.cpp \
    $(LIBMEDIAINFO_SRC_DIR)/Multiple/File_Rm.cpp \
    $(LIBMEDIAINFO_SRC_DIR)/Multiple/File_SequenceInfo.cpp \
    $(LIBMEDIAINFO_SRC_DIR)/Multiple/File_Skm.cpp \
    $(LIBMEDIAINFO_SRC_DIR)/Multiple/File_Swf.cpp \
    $(LIBMEDIAINFO_SRC_DIR)/Multiple/File_Umf.cpp \
    $(LIBMEDIAINFO_SRC_DIR)/Multiple/File_Wm.cpp \
    $(LIBMEDIAINFO_SRC_DIR)/Multiple/File_Wm_Elements.cpp \
    $(LIBMEDIAINFO_SRC_DIR)/Multiple/File_Xdcam_Clip.cpp \
    $(LIBMEDIAINFO_SRC_DIR)/Reader/Reader_Directory.cpp \
    $(LIBMEDIAINFO_SRC_DIR)/Reader/Reader_File.cpp \
    $(LIBMEDIAINFO_SRC_DIR)/Reader/Reader_libcurl.cpp \
    $(LIBMEDIAINFO_SRC_DIR)/Reader/Reader_libmms.cpp \
    $(LIBMEDIAINFO_SRC_DIR)/Tag/File__Tags.cpp \
    $(LIBMEDIAINFO_SRC_DIR)/Tag/File_ApeTag.cpp \
    $(LIBMEDIAINFO_SRC_DIR)/Tag/File_Id3.cpp \
    $(LIBMEDIAINFO_SRC_DIR)/Tag/File_Id3v2.cpp \
    $(LIBMEDIAINFO_SRC_DIR)/Tag/File_Lyrics3.cpp \
    $(LIBMEDIAINFO_SRC_DIR)/Tag/File_Lyrics3v2.cpp \
    $(LIBMEDIAINFO_SRC_DIR)/Tag/File_PropertyList.cpp \
    $(LIBMEDIAINFO_SRC_DIR)/Tag/File_VorbisCom.cpp \
    $(LIBMEDIAINFO_SRC_DIR)/Tag/File_Xmp.cpp \
    $(LIBMEDIAINFO_SRC_DIR)/Text/File_AribStdB24B37.cpp \
    $(LIBMEDIAINFO_SRC_DIR)/Text/File_Cdp.cpp \
    $(LIBMEDIAINFO_SRC_DIR)/Text/File_Cmml.cpp \
    $(LIBMEDIAINFO_SRC_DIR)/Text/File_DvbSubtitle.cpp \
    $(LIBMEDIAINFO_SRC_DIR)/Text/File_DtvccTransport.cpp \
    $(LIBMEDIAINFO_SRC_DIR)/Text/File_Eia608.cpp \
    $(LIBMEDIAINFO_SRC_DIR)/Text/File_Eia708.cpp \
    $(LIBMEDIAINFO_SRC_DIR)/Text/File_Kate.cpp \
    $(LIBMEDIAINFO_SRC_DIR)/Text/File_N19.cpp \
    $(LIBMEDIAINFO_SRC_DIR)/Text/File_OtherText.cpp \
    $(LIBMEDIAINFO_SRC_DIR)/Text/File_Pdf.cpp \
    $(LIBMEDIAINFO_SRC_DIR)/Text/File_Pgs.cpp \
    $(LIBMEDIAINFO_SRC_DIR)/Text/File_Scc.cpp \
    $(LIBMEDIAINFO_SRC_DIR)/Text/File_Scte20.cpp \
    $(LIBMEDIAINFO_SRC_DIR)/Text/File_Sdp.cpp \
    $(LIBMEDIAINFO_SRC_DIR)/Text/File_SubRip.cpp \
    $(LIBMEDIAINFO_SRC_DIR)/Text/File_Teletext.cpp \
    $(LIBMEDIAINFO_SRC_DIR)/Text/File_TimedText.cpp \
    $(LIBMEDIAINFO_SRC_DIR)/Text/File_Ttml.cpp \
    $(LIBMEDIAINFO_SRC_DIR)/Video/File_Aic.cpp \
    $(LIBMEDIAINFO_SRC_DIR)/Video/File_AfdBarData.cpp \
    $(LIBMEDIAINFO_SRC_DIR)/Video/File_Avc.cpp \
    $(LIBMEDIAINFO_SRC_DIR)/Video/File_Avc_Duplicate.cpp \
    $(LIBMEDIAINFO_SRC_DIR)/Video/File_AvsV.cpp \
    $(LIBMEDIAINFO_SRC_DIR)/Video/File_Canopus.cpp \
    $(LIBMEDIAINFO_SRC_DIR)/Video/File_Dirac.cpp \
    $(LIBMEDIAINFO_SRC_DIR)/Video/File_Ffv1.cpp \
    $(LIBMEDIAINFO_SRC_DIR)/Video/File_Flic.cpp \
    $(LIBMEDIAINFO_SRC_DIR)/Video/File_Fraps.cpp \
    $(LIBMEDIAINFO_SRC_DIR)/Video/File_H263.cpp \
    $(LIBMEDIAINFO_SRC_DIR)/Video/File_Hevc.cpp \
    $(LIBMEDIAINFO_SRC_DIR)/Video/File_HuffYuv.cpp \
    $(LIBMEDIAINFO_SRC_DIR)/Video/File_Lagarith.cpp \
    $(LIBMEDIAINFO_SRC_DIR)/Video/File_Mpeg4v.cpp \
    $(LIBMEDIAINFO_SRC_DIR)/Video/File_Mpegv.cpp \
    $(LIBMEDIAINFO_SRC_DIR)/Video/File_ProRes.cpp \
    $(LIBMEDIAINFO_SRC_DIR)/Video/File_Theora.cpp \
    $(LIBMEDIAINFO_SRC_DIR)/Video/File_Vc1.cpp \
    $(LIBMEDIAINFO_SRC_DIR)/Video/File_Vc3.cpp \
    $(LIBMEDIAINFO_SRC_DIR)/Video/File_Vp8.cpp \
    $(LIBMEDIAINFO_SRC_DIR)/Video/File_Y4m.cpp \
    $(LIBMEDIAINFO_SRC_DIR)/../MediaInfoDLL/MediaInfoDLL.cpp \
    $(LIBMEDIAINFO_SRC_DIR)/../ThirdParty/md5/md5.c \
    $(LIBMEDIAINFO_SRC_DIR)/../ThirdParty/tinyxml2/tinyxml2.cpp \
    $(LIBMEDIAINFO_SRC_DIR)/../ThirdParty/aes-gladman/aes_modes.c \
    $(LIBMEDIAINFO_SRC_DIR)/../ThirdParty/aes-gladman/aescrypt.c \
    $(LIBMEDIAINFO_SRC_DIR)/../ThirdParty/aes-gladman/aeskey.c \
    $(LIBMEDIAINFO_SRC_DIR)/../ThirdParty/aes-gladman/aestab.c \
    $(LIBMEDIAINFO_SRC_DIR)/../ThirdParty/sha1-gladman/sha1.c \
    $(LIBMEDIAINFO_SRC_DIR)/../ThirdParty/sha2-gladman/sha2.c \
    $(LIBMEDIAINFO_SRC_DIR)/../ThirdParty/hmac-gladman/hmac.c \
    $(LIBMEDIAINFO_SRC_DIR)/../ThirdParty/hmac-gladman/pwd2key.c \
    wchar_multibyte.cpp \
    libmediainfo-jni.cpp

LOCAL_C_INCLUDES        += $(LOCAL_PATH)/$(THIRDPARTY_DIR)
LOCAL_C_INCLUDES        += $(LOCAL_PATH)/$(THIRDPARTY_DIR)/glob
LOCAL_C_INCLUDES        += $(LOCAL_PATH)/$(LIBMEDIAINFO_INC_DIR)
LOCAL_C_INCLUDES        += $(LOCAL_PATH)/$(LIBMEDIAINFO_INC_DIR)/MediaInfo
LOCAL_C_INCLUDES        += $(LOCAL_PATH)/$(LIBMEDIAINFO_INC_DIR)/../MediaInfoDLL
LOCAL_C_INCLUDES        += $(LOCAL_PATH)/$(LIBMEDIAINFO_INC_DIR)/ThirdParty/base64
LOCAL_C_INCLUDES        += $(LOCAL_PATH)/$(LIBMEDIAINFO_INC_DIR)/ThirdParty/md5
LOCAL_C_INCLUDES        += $(LOCAL_PATH)/$(LIBMEDIAINFO_INC_DIR)/ThirdParty/tinyxml2
LOCAL_C_INCLUDES        += $(LOCAL_PATH)/$(LIBMEDIAINFO_INC_DIR)/ThirdParty/aes-gladman
LOCAL_C_INCLUDES        += $(LOCAL_PATH)/$(LIBMEDIAINFO_INC_DIR)/ThirdParty/sha1-gladman
LOCAL_C_INCLUDES        += $(LOCAL_PATH)/$(LIBMEDIAINFO_INC_DIR)/ThirdParty/sha2-gladman
LOCAL_C_INCLUDES        += $(LOCAL_PATH)/$(LIBMEDIAINFO_INC_DIR)/ThirdParty/hmac-gladman
LOCAL_C_INCLUDES        += $(LOCAL_PATH)/$(LIBZEN_INC_DIR)
LOCAL_C_INCLUDES        += $(LOCAL_PATH)/$(LIBZEN_INC_DIR)/ZenLib

LOCAL_CFLAGS            += -Wall $(USER_CFLAGS)
LOCAL_LDLIBS            := -llog -lz -lm
LOCAL_CXXFLAGS          += -DUNICODE

include $(BUILD_SHARED_LIBRARY)
