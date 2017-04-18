#pragma once
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