This example loads IDLE background from skin into your app as background.

To add skin support to your project:

1. copy skinsupport folder to your project's root folder
2. add line to your pro file:
`include($$PWD/skinsupport/skinsupport.pri)
3. add 
`&#35;include &lt;skinsupport/skinimageprovider.h&gt;
and
`SkinImageProvider::installForViewer(&viewer);
lines to your main.cpp, installForViewer accepts a pointer to your QDeclarativeView (QmlApplicationViewer) element, and it should be called before installing a QML source (setMainQmlFile, setSource, etc)

4. Add Image component for background into your QML, use sourceSize.width and sourceSize.height fields to control theme element size (it may be different than Image's width, height), and set source property to image://skin/MAJOR_ID/MINOR_ID where MAJOR_ID is major uid of skin element, and MINOR_ID is minor one. They should be in HEX. You can use MAJOR_ID=10005A26 and MINOR_ID=1001 to get IDLE background (so, source should be image://skin/10005A26/1001).

You can ask skin makers for another IDs, and you can load any element from skin this way, but to make skinnable ToolBar for example you should create a custom one (Image and Row with buttons inside).
