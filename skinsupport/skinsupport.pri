SOURCES+=$$PWD/skinimageprovider.cpp
HEADERS+=$$PWD/skinimageprovider.h

symbian:LIBS+=-lgdi
symbian:LIBS+=-lbitgdi
symbian:LIBS+=-laknskins
symbian:LIBS+=-lfbscli
symbian:LIBS+=-legul
symbian:LIBS+=-laknicon
symbian:LIBS+=-leikcore
symbian:LIBS+=-lavkon
symbian:LIBS+=-leiksrv
symbian:LIBS+=-lcone
symbian:LIBS+=-lapparc
symbian:LIBS+=-lws32
