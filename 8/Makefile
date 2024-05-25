all: IOHandler LogicHandler
IOHandler: ../common/Common.h ../common/Common.c ./ioHandler.c
	gcc ./ioHandler.c ../common/Common.c -o IOHandler
LogicHandler: ../common/Common.h ../common/Common.c ./logicHandler.c
	gcc ./logicHandler.c ../common/Common.c -o LogicHandler

