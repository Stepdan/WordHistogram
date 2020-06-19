QT += core gui widgets

CONFIG += c++17

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
	Engine/Application.cpp \
	Engine/Mediator.cpp \
	Proc/Data/Histogram.cpp \
	UI/MainWindow.cpp \
	UI/Scene/Scene.cpp \
	Util/Forwarder.cpp \
	main.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

FORMS += \
	UI/MainWindow.ui

HEADERS += \
	Engine/Application.h \
	Engine/Mediator.h \
	Proc/Data/Histogram.h \
	Proc/Interfaces/IHistogram.h \
	UI/MainWindow.h \
	UI/Scene/Scene.h \
	Util/Forwarder.h \
	Util/ThreadWorker.h
