QT += testlib
QT += gui
CONFIG += qt warn_on depend_includepath testcase

TEMPLATE = app

SOURCES +=  tst_functiontest.cpp \
            ../core/math/function.cpp \
            ../core/math/support.cpp

HEADERS += ../core/globals.h \
           ../core/math/math.h \
           ../core/math/support.h

INCLUDEPATH += ../core
