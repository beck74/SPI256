//��ͷ�ļ�������MX25L25635FоƬ�ļĴ�����Ϣ
#ifndef MX25L25635F_H_
#define MX25L25635F_H_


#define CHECK_4BYTE_MODE		0x20//���ͨ���Ƿ����4Byteģʽ�ı�־λ
#define CHECK_WIP				0x01//���ͨ���Ƿ����4Byteģʽ�ı�־λ


// CMD_NEED_WREN
#define WREN_NEEDED    0X1 
#define WREN_DONT_NEED  0X0 
// CMD_INDEX   
#define SPI_CMD_WREN			0x06//WREN
#define SPI_CMD_RDSR			0x05//RDSR
#define SPI_CMD_EN4B			0xB7//����4Byteģʽ
#define SPI_CMD_EX4B			0xE9//�˳�4Byteģʽ
#define SPI_CMD_CHECK_4BYTE		0x15//Check 4Byte״̬
#define SPI_CMD_ERASE_CE1		0xC7//CHIP_ERASE
#define SPI_CMD_ERASE_CE2		0x60//CHIP_ERASE
#define SPI_CMD_PP				0x02//Page Program
#define SPI_CMD_READ			0x03//Read
#define SPI_CMD_VERIFY			SPI_CMD_READ//Verify
#define SPI_CMD_REMS			0x90//manufacturer & device ID
// DATA_DIRECT
#define SPI_PROG       0X28
#define SPI_READ       0X01
#define SPI_VERIFY     0X30
// segX_BUS_WIDTH
#define ONE_LINE       0X01
#define TWO_LINE       0X02
#define FOR_LINE       0X04
//ADDR_BYTE_NUM
#define MODE_3BYTE     0X03 
#define MODE_4BYTE     0X04 
// CMD_DAT_TX_RX
#define DAT_TX         0X02 
#define DAT_RX         0X01 
#define DAT_NONE       0X00 
#endif // !MX25L25635F_H_
