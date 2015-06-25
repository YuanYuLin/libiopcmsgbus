
TARGET = libiopcmsgbus.so

CFLAGS += -I$(SDKSTAGE)/usr/include/
CFLAGS += 

LDFLAGS += -L$(SDKSTAGE)/usr/lib/ 
LDFLAGS += -lc -lpthread 

SRC = 
SRC += utils.c
SRC += uds_server.c
SRC += uds_client.c

include Makefile.include
