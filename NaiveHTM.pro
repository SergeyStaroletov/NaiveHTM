QT -= gui
QT += core


CONFIG += c++11 console
CONFIG -= app_bundle

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

#INCLUDEPATH += "/usr/local/include"

INCLUDEPATH += "/Volumes/SD128/boost_1_35_0"


# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
main.cpp \
boostmemory.cpp \
hypothesis.cpp \
memorymodule.cpp \
midistrategy.cpp \
nodegroupprocessor.cpp \
offsetlist.cpp \
propertylist.cpp \
realnode.cpp \
timeoffset.cpp \
timeproperty.cpp \
utils.cpp \
abstract_module.cpp \
dispatcher.cpp \
message_queue.cpp \
mutex_wrapper.cpp \
thread_wrapper.cpp \
wait_condition_wrapper.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
basedifftype.h \
baseoffset.hpp \
baseproperty.hpp \
boostmemory.h \
brain.h \
compareresult.h \
event.h \
hypothesis.h \
imemory.h \
ioffset.h \
iproperty.h \
istrategy.h \
link.h \
memorymodule.h \
node.h \
nodegroup.h \
nodegroupprocessor.h \
offsetlist.h \
pattern.h \
predictionstatus.h \
 propertyid.h \
propertylist.h \
realnode.h \
stdlibs.h \
timeoffset.h \
timeproperty.h \
utils.h \
abstract_module.h \
dispatcher.h \
wait_condition_wrapper.h \
message_types.h \
    mystrategy.h
