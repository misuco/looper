QT += quick multimedia
CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Refer to the documentation for the
# deprecated API to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        main.cpp \
    submodules/audiooutput/audiooutput.cpp \
    submodules/audioinput/audioinput.cpp \
    submodules/audioinput/audioinfo.cpp \
    submodules/audiooutput/sampleformatconverter.cpp \
    submodules/soundsample/soundsample.cpp \
    submodules/soundsample/player.cpp \
    submodules/soundsample/recorder.cpp \
    submodules/soundsample/sound_image.cpp \
    submodules/soundsample/sample_graph_model.cpp \
    submodules/soundsample/sound_image_gesture.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    submodules/audiooutput/audiooutput.h \
    submodules/audioinput/audioinput.h \
    submodules/audioinput/audioinfo.h \
    submodules/audiooutput/sampleformatconverter.h \
    submodules/soundsample/soundsample.h \
    submodules/soundsample/player.h \
    submodules/audiooutput/iaudiosource.h \
    submodules/audiooutput/iaudiosink.h \
    submodules/soundsample/recorder.h \
    submodules/soundsample/sound_image.h \
    submodules/soundsample/sample_graph_model.h \
    submodules/soundsample/sound_image_gesture.h
