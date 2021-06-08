CONFIG -= qt

TEMPLATE = lib
DEFINES += JDKMIDI_LIBRARY

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += ../include

SOURCES += \
    ../src/jdkmidi_advancedsequencer.cpp \
    ../src/jdkmidi_driver.cpp \
    ../src/jdkmidi_driverdump.cpp \
    ../src/jdkmidi_driverwin32.cpp \
    ../src/jdkmidi_edittrack.cpp \
    ../src/jdkmidi_file.cpp \
    ../src/jdkmidi_fileread.cpp \
    ../src/jdkmidi_filereadmultitrack.cpp \
    ../src/jdkmidi_fileshow.cpp \
    ../src/jdkmidi_filewrite.cpp \
    ../src/jdkmidi_filewritemultitrack.cpp \
    ../src/jdkmidi_keysig.cpp \
    ../src/jdkmidi_manager.cpp \
    ../src/jdkmidi_matrix.cpp \
    ../src/jdkmidi_midi.cpp \
    ../src/jdkmidi_msg.cpp \
    ../src/jdkmidi_multitrack.cpp \
    ../src/jdkmidi_parser.cpp \
    ../src/jdkmidi_process.cpp \
    ../src/jdkmidi_queue.cpp \
    ../src/jdkmidi_sequencer.cpp \
    ../src/jdkmidi_showcontrol.cpp \
    ../src/jdkmidi_showcontrolhandler.cpp \
    ../src/jdkmidi_smpte.cpp \
    ../src/jdkmidi_sysex.cpp \
    ../src/jdkmidi_tempo.cpp \
    ../src/jdkmidi_tick.cpp \
    ../src/jdkmidi_track.cpp

HEADERS += \
    jdkmidi_global.h \
    jdkmidi.h

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target
