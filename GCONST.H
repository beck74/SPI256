#pragma once

#define FIFO_LEN	512

#define CUR_PROJ_VERSION	0x0010

#define HEADER_PROJ_LEN		0x800

#define OFFSET_VERSION	0x10 //2 Bytes
#define OFFSET_SERIAL	0x20 //
#define OFFSET_DEV_TYPE	0xFF

#define OFFSET_FILE_INFO	0x100
#define OFFSET_DEVICE_INFO	0x200
#define FILE_NAME_MAX_LENG	(OFFSET_DEVICE_INFO - OFFSET_FILE_INFO - 1)

#define OFFSET_PARTITION	(OFFSET_DEVICE_INFO + 0x60)
#define OFFSET_ECSD			(OFFSET_DEVICE_INFO + 0x90)
#define OFFSET_SETTINGS		(OFFSET_DEVICE_INFO + 0xB0) //important
#define OFFSET_CHECKSUM		(OFFSET_DEVICE_INFO + 0xC0)
#define OFFSET_FILENAME		(OFFSET_DEVICE_INFO + 0xD0)
#define OFFSET_HW_DATA		0x400
#define OFFSET_WP_DATA		0x600
#define OFFSET_KEY_DATA		OFFSET_HW_DATA

#define BIT_BM_UNICODE	1

#define FP_EMMC		0
#define FP_PIN		1
#define FP_SPI		2
#define FP_SD		3
#define FP_PHI		4
#define FP_IIC		5
#define FP_CCG2		6
#define FP_STM32	7
#define FP_NOR		8
#define FP_IRMCK	9
#define FP_IRMCF	10
#define FP_STM8L	11
#define FP_SPI1		12


#define DT_EMMC		0
#define DT_SPI		1
#define DT_IIC		2
#define DT_NAND1	3
#define DT_CCG1		4
#define DT_STM32	7
#define DT_NOR		8
#define DT_IRMCK	9
#define DT_IRMCF	10
#define DT_STM8L	11
#define DT_SPI1		12


#define SM_DEFAULT	0
#define SM_SONIX	1
#define SM_REALTEK	2
#define SM_SUNPLUS	3

//#define SNMode: array[0..3] of string = ('System', 'Sonix', 'Realtek', 'Sunplus');

#define F_EXEC		0xC040
#define F_STAT		0xC044
#define F_CMD		0xC020
#define F_ADDR		0xC022
#define F_SEL		0xC02A
#define F_CKFR		0xC030
#define F_BITW		0xC034 //BITWIDTH 0 = 1Bit; 1 = 4BIT; 2 = 8BIT
#define F_SEC_MODE	0xC035
#define F_CKEN		0xC038

#define PARAM_TOTAL	8
#define CFG_LEN		16

#define I_IDCHECK	0
#define I_ERASE		1
#define I_BLANK		2
#define I_PROG		3
#define I_VERIFY	4
#define I_READ		5

#define STR_INFO	"getinfo"
#define STR_PROG	"Program"
#define STR_READ	"Read"
#define STR_VERIFY	"Verify"
#define STR_ERASE	"Erase"
#define STR_IDCHECK	"IDCheck"
#define STR_BLANK	"Blank"

#define EN_PROG		(1 << I_PROG)
#define EN_READ		(1 << I_READ)
#define EN_VERIFY	(1 << I_VERIFY)
#define EN_ERASE	(1 << I_ERASE)
#define EN_IDCHECK	(1 << I_IDCHECK)
#define EN_BLANK	(1 << I_BLANK)

#define INDEX_PROG		0
#define INDEX_READ		1
#define INDEX_VERIFY	2
#define INDEX_ERASE		3
#define INDEX_IDCHECK	4
#define INDEX_BLANK		5

#define PARAM_TOTAL 8
#define CFG_LEN		16

#pragma pack(1)//内存对齐以1个字节为单位，也就是紧凑型
typedef	struct TDEVICE {
	CHAR cVender[33];
	CHAR cName[33];
	CHAR cPackage[17];
	CHAR cAdapter[6];
	INT64  llMemSize[4];
	WORD wManuID;
	WORD wDeviceID;
	WORD wDeviceType;
	BYTE byParam[PARAM_TOTAL];
	BYTE byCfgWord[CFG_LEN * 2];
	DOUBLE dVoltage;
}DEVICE, *PDEVICE;
#pragma pack()//默认对齐方式为：变量首地址为变量所占字节数的整数倍