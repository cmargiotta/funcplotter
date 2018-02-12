QT += testlib
QT += gui
CONFIG += qt warn_on depend_includepath testcase

TEMPLATE = app

SOURCES +=  tst_functiontest.cpp \
            ../core/math/core/function.cpp \
            ../core/math/core/support.cpp

HEADERS += ../core/math/globals.h \
           ../core/math/core/math.h

INCLUDEPATH += ../core
