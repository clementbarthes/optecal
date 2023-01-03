#-------------------------------------------------
#
# Project created by QtCreator 2014-04-12T21:37:02
#
#-------------------------------------------------

LIBSDIR =  C://libs

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

QT += xml

TARGET = OpteCAL
TEMPLATE = app

CONFIG(debug, debug|release) {
    DESTDIR = debug
}
CONFIG(release, debug|release) {
    DESTDIR = release
}

OBJECTS_DIR = $$DESTDIR/.obj
MOC_DIR = $$DESTDIR/.moc
RCC_DIR = $$DESTDIR/.qrc
UI_DIR = $$DESTDIR/.u


SOURCES += main.cpp\
    calibration.cpp \
    calibrationmodule.cpp \
    optecal.cpp \
    filelist.cpp \
    autoresize.cpp \
    drawshape.cpp \
    qlabelwmouse.cpp \
    drawseedpoint.cpp \
    subsetsmap.cpp \
    nloptimizer.cpp \
    interpcoef.cpp \
    interpolator.cpp \
    displacements.cpp \
    roimodule.cpp \
    displacementsmodule.cpp \
    runanalysis.cpp \
    filelistpage.cpp \
    filelistcorrelationpage.cpp \
    draworigin.cpp \
    rawconverter.cpp \
    templatematch.cpp \
    rawmodule.cpp \
    filelistcalibrationpage.cpp \
    virtualmeasurementtools.cpp \
    exportmodule.cpp \
    postprocessingmodule.cpp

HEADERS  += optecal.h \
    calibration.h \
    calibrationmodule.h \
    filelist.h \
    autoresize.h \
    drawshape.h \
    qlabelwmouse.h \
    drawseedpoint.h \
    subsetsmap.h \
    nloptimizer.h \
    interpcoef.h \
    interpolator.h \
    displacements.h \
    roimodule.h \
    displacementsmodule.h \
    runanalysis.h \
    filelistpage.h \
    filelistcorrelationpage.h \
    draworigin.h \
    staticreadwritefunctions.h \
    rawconverter.h \
    templatematch.h \
    rawmodule.h \
    filelistcalibrationpage.h \
    virtualmeasurementtools.h \
    exportmodule.h \
    postprocessingmodule.h

FORMS    += optecal.ui

RC_FILE = icon.rc


# x64
INCLUDEPATH += $$LIBSDIR//opencv-4.6.0//build//install//include//
LIBS += $$LIBSDIR//opencv-4.6.0//build//install//x64//vc16//lib//*.lib

INCLUDEPATH += $$LIBSDIR//libraw//
LIBS += $$LIBSDIR//libraw//buildfiles//debug-x86_64//libraw.lib

INCLUDEPATH += $$LIBSDIR//matlab//include//
LIBS += $$LIBSDIR//matlab//lib//win64//microsoft//*.lib


RESOURCES += \
    icons.qrc

OTHER_FILES +=


