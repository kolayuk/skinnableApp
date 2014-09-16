This example loads IDLE background from skin into your app as background.

To add skin support to your project:

Copy skinsupport folder to your project's root folder

Add line to your pro file:
```
include($$PWD/skinsupport/skinsupport.pri)
```
Add 
```
#include <skinsupport/skinimageprovider.h>
```
and
```
SkinImageProvider::installForViewer(&viewer);
```
lines to your main.cpp, installForViewer accepts a pointer to your QDeclarativeView (QmlApplicationViewer) element, and it should be called before installing a QML source (setMainQmlFile, setSource, etc)

And finally Image component for background into your QML, use sourceSize.width and sourceSize.height fields to control theme element size (it may be different than Image's width, height), and set source property to image://skin/MAJOR_ID/MINOR_ID where MAJOR_ID is major uid of skin element, and MINOR_ID is minor one. They should be in HEX. You can use MAJOR_ID=10005A26 and MINOR_ID=1001 to get IDLE background (so, source should be image://skin/10005A26/1001).

You can ask skin makers for another IDs, and you can load any element from skin this way, but to make skinnable ToolBar for example you should create a custom one (Image and Row with buttons inside).
