QT += testlib
QT += gui
CONFIG += qt warn_on depend_includepath testcase

TEMPLATE = app

SOURCES +=  tst_functiontest.cpp \
            ../core/function.cpp \
            ../core/support.cpp

HEADERS += ../core/globals.h \
           ../core/math.h

INCLUDEPATH += ../core
