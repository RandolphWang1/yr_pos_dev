CC = /usr/local/arm/2.95.3/bin/arm-linux-gcc
STRIP = /usr/local/arm/2.95.3/bin/arm-linux-strip
CFLAGS= -I/YF2410/kernel/include -I../inc/sys -I../inc/SDKInc -I../inc

TARGET1 = SDK
TARGET2 = lcd
TARGET3 = printer
TARGET4 = icc
TARGET5 = kbd
TARGET6 = magcard
TARGET7 = armd8linux
TARGET8 = control
BRANCH_NAME = $(shell git branch --no-color 2> /dev/null | sed -e '/^[^*]/d' -e 's/* \(.*\)/\1/')
#BUILD_TIME = $(shell date "+%F_%R" 2>/dev/null | sed -e 's/[^0-9_-:]//g')
BUILD_TIME = $(shell date "+%F" 2>/dev/null | sed -e 's/[^0-9_-:]//g')

YRJT_VERSION=$(BRANCH_NAME)_$(BUILD_TIME) 
#YRJT_VERSION=$(BUILD_TIME)_$(BRANCH_NAME) 
FOTA_PKG_NAME=$(YRJT_VERSION)
#FOTA_ALL_PKG_NAME = $(shell sed -e '[^YRJT_VERSION]/d' yr_version.h -e )


all:GEN_VEN_H YRJT_OUT fota fota_all 

D620D_test:InitPos.o Main.o Param.o CommTest.o KbdTest.o LcdTest.o \
	PrinterTest.o ModemTest.o GprsTest.o EthernetTest.o CardReaderTest.o \
	PinpadTest.o JingZhenTest.o Function.o OtherTest.o IdentifyReader.o	\
	unicode.o Sms.o FM17XX.o ReadCardNo.o Epp.o WifiTest.o ProcCard.o \
    md5.o xmlparser.o https.o aliqr.o statement.o qrgenerator.o update.o
	$(CC) $^ -o $@ -L ../lib -l$(TARGET1) -l$(TARGET2) -l$(TARGET3)  -l$(TARGET4) -l$(TARGET5) -l$(TARGET6) -l$(TARGET7) -l$(TARGET8) -lm -lcurl -lexpat -pthread 

D620D:D620D_test
	$(STRIP) -s -I D620D_test
	chmod +x D620D_test
	mv ./D620D_test ./D620D/D620D

GEN_VEN_H:
	rm -f yr_version.h
	@echo "#ifndef __YR_VER__" >> yr_version.h
	@echo "#define __YR_VER__" >> yr_version.h
	@echo -n "\\t#define YRJT_VERSION "  >> yr_version.h
	@echo -n \" >> yr_version.h
	@echo -n $(YRJT_VERSION) >> yr_version.h    
	@echo -n \" >> yr_version.h
	@echo >> yr_version.h
	@echo "#endif" >> yr_version.h 

YRJT_OUT:D620D
	tar zcvf D620D.tar.gz D620D/D620D
	mv ./D620D.tar.gz ../
	rm -f *.o *bak

fota:D620D
	tar zcvf tmp.tgz D620D/D620D D620D/download_desc.txt D620D/download_update.txt D620D/removeTmpFile.txt local.sh
	rm -f ../$(BRANCH_NAME)*
	mv ./tmp.tgz ../$(FOTA_PKG_NAME)
	rm -f *.o *bak
	
fota_all:D620D
	tar zcvf tmp.tgz D620D/ drv/ local.sh
	rm -f ../all_$(BRANCH_NAME)*
	mv ./tmp.tgz ../all_$(FOTA_PKG_NAME)
	rm -f *.o *bak	

%.o:%.c
	$(CC) $(CFLAGS) -DALIPAY_FIFO -DRECEIPT_CONF -DREFUND_EN -c -Wall $< -o $@

clean:
	rm -f *.o *bak
