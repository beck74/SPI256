//此头文件定义了MX25L25635F芯片的寄存器信息
#ifndef MX25L25635F_H_
#define MX25L25635F_H_

//更换芯片时，可能需要修改的宏定义有：
//WRITE_PAGE_SIZE
//READ_PAGE_SIZE
//SPI_CMD_PP
//SPI_CMD_READ


//芯片信息，用于填写编程器参数
//manufacturer & device ID
#define MX25L25635F_MSNU_ID    0xC2
#define MX25L25635F_DEVICE_ID  0x20

//读写page大小
#define WRITE_PAGE_SIZE   512		//64M芯片为512，32M芯片为256
#define READ_PAGE_SIZE    256

// CMD_INDEX   
#define SPI_CMD_WREN          0x06//WREN
#define SPI_CMD_RDSR          0x05//RDSR
#define SPI_CMD_EN4B          0xB7//进入4Byte模式
#define SPI_CMD_EX4B          0xE9//退出4Byte模式
#define SPI_CMD_CHECK_4BYTE   0x15//Check 4Byte状态
#define SPI_CMD_ERASE_CE1     0xC7//CHIP_ERASE
#define SPI_CMD_ERASE_CE2     0x60//CHIP_ERASE
#define SPI_CMD_PP            0x12//0x02//Page Program	256M用02,512M用12	
#define SPI_CMD_READ          0x13//0x03//Read			256M用03,512M用13
#define SPI_CMD_VERIFY        SPI_CMD_READ//Verify
#define SPI_CMD_REID          0x9F//manufacturer & device ID
#define SPI_CMD_REMS          0x90//manufacturer & device ID


#define CHECK_4BYTE_MODE  0x20//检查通道是否进入4Byte模式的标志位
#define CHECK_WIP         0x01//检查通道是否进入4Byte模式的标志位

#endif // !MX25L25635F_H_
