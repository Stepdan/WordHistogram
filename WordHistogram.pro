QT += core gui widgets

CONFIG += c++17

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
	Engine/Application.cpp \
	Engine/Mediator.cpp \
	Proc/Histogram/Histogram.cpp \
	Proc/ProcessManager/ProcessManager.cpp \
	UI/MainWindow.cpp \
	UI/Scene/Scene.cpp \
	Util/Forwarder.cpp \
	Util/ProgressController/ProgressController.cpp \
	main.cpp

FORMS += \
	UI/MainWindow.ui

HEADERS += \
	Engine/Application.h \
	Engine/Mediator.h \
	Proc/Histogram/Histogram.h \
	Proc/Interfaces/IHistogram.h \
	Proc/ProcessManager/ProcessManager.h \
	UI/MainWindow.h \
	UI/Scene/Scene.h \
	Util/EventHandler/EventHandlerList.h \
	Util/EventHandler/EventPublisher.h \
	Util/Forwarder.h \
	Util/Interfaces/IProgressBar.h \
	Util/Interfaces/IProgressController.h \
	Util/Interfaces/IProgressObserver.h \
	Util/ProgressController/ProgressController.h \
	Util/ThreadWorker.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
