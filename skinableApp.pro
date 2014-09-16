# Add more folders to ship with the application, here
folder_01.source = qml/skinableApp
folder_01.target = qml
DEPLOYMENTFOLDERS = folder_01

# Additional import path used to resolve QML modules in Creator's code model
QML_IMPORT_PATH =

symbian:TARGET.UID3 = 0xE672567A

symbian:TARGET.CAPABILITY += NetworkServices

SOURCES += main.cpp

include(qmlapplicationviewer/qmlapplicationviewer.pri)
qtcAddDeployment()


#add following line to add skin support support
include($$PWD/skinsupport/skinsupport.pri)

