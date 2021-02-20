QT -= gui
QT += core


CONFIG += c++11 console
CONFIG -= app_bundle


DEFINES += QT_DEPRECATED_WARNINGS _LIBCPP_ENABLE_CXX17_REMOVED_AUTO_PTR

INCLUDEPATH += "/Volumes/SD128/boost_1_35_0"



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
