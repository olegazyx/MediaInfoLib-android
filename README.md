# MediaInfoLib-android
MediaInfo is a convenient unified display of the most relevant technical and tag data for video and audio files.
</br>
</br>
This product uses various open source software.</br>
These source code has been modified, including little improvement, extending Android Environment.</br>
Thanks to a MediaInfo project.
</br>
</br>
How to use:
This is android jni library.
</br>
</br>
-Compile it with android-ndk or take prebuild binary files in /libs/<arch></br>
-Put MediaInfo.java to your project in org.mediainfo.android package or modify MediaInfo.java and libmediainfo-jni.cpp</br>
-Call MediaInfo class, (example: MediaInfo mi = new MediaInfo(); String result= mi.getMI(filepath);)</br>
</br>
</br>