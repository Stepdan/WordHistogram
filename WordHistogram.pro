QT += core gui widgets

CONFIG += c++17

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
	Engine/Application.cpp \
	Engine/Mediator.cpp \
	Proc/Histogram/Histogram.cpp \
	Proc/ProcessManager/ProcessManager.cpp \
	UI/Drawer/Drawer.cpp \
	UI/Drawer/DrawerFactory.cpp \
	UI/LegendModel/Delegate/LegendModelDelegate.cpp \
	UI/LegendModel/Item/LegendModelItem.cpp \
	UI/LegendModel/LegendModel.cpp \
	UI/MainWindow.cpp \
	UI/Scene/Scene.cpp \
	Util/FileUtils.cpp \
	Util/Forwarder.cpp \
	main.cpp

FORMS += \
	UI/MainWindow.ui

HEADERS += \
	Engine/Application.h \
	Engine/Mediator.h \
	Proc/Histogram/Histogram.h \
	Proc/Interfaces/IHistogram.h \
	Proc/ProcessManager/ProcessManager.h \
	UI/Drawer/Drawer.h \
	UI/Drawer/DrawerFactory.h \
	UI/Drawer/DrawerType.h \
	UI/Interfaces/IDrawer.h \
	UI/LegendModel/DeclareMetatype.h \
	UI/LegendModel/Delegate/LegendModelDelegate.h \
	UI/LegendModel/Item/ILegendModelItem.h \
	UI/LegendModel/Item/LegendModelItem.h \
	UI/LegendModel/LegendModel.h \
	UI/LegendModel/LegendModelRoles.h \
	UI/MainWindow.h \
	UI/Scene/Scene.h \
	Util/FileUtils.h \
	Util/FindPair.h \
	Util/Forwarder.h \
	Util/RAII/PainterGuard.h \
	Util/ThreadWorker.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
