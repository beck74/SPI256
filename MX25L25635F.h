//��ͷ�ļ�������MX25L25635FоƬ�ļĴ�����Ϣ
#ifndef MX25L25635F_H_
#define MX25L25635F_H_

//����оƬʱ��������Ҫ�޸ĵĺ궨���У�
//WRITE_PAGE_SIZE
//READ_PAGE_SIZE
//SPI_CMD_PP
//SPI_CMD_READ


//оƬ��Ϣ��������д���������
//manufacturer & device ID
#define MX25L25635F_MSNU_ID    0xC2
#define MX25L25635F_DEVICE_ID  0x20

//��дpage��С
#define WRITE_PAGE_SIZE   512		//64MоƬΪ512��32MоƬΪ256
#define READ_PAGE_SIZE    256

// CMD_INDEX   
#define SPI_CMD_WREN          0x06//WREN
#define SPI_CMD_RDSR          0x05//RDSR
#define SPI_CMD_EN4B          0xB7//����4Byteģʽ
#define SPI_CMD_EX4B          0xE9//�˳�4Byteģʽ
#define SPI_CMD_CHECK_4BYTE   0x15//Check 4Byte״̬
#define SPI_CMD_ERASE_CE1     0xC7//CHIP_ERASE
#define SPI_CMD_ERASE_CE2     0x60//CHIP_ERASE
#define SPI_CMD_PP            0x12//0x02//Page Program	256M��02,512M��12	
#define SPI_CMD_READ          0x13//0x03//Read			256M��03,512M��13
#define SPI_CMD_VERIFY        SPI_CMD_READ//Verify
#define SPI_CMD_REID          0x9F//manufacturer & device ID
#define SPI_CMD_REMS          0x90//manufacturer & device ID


#define CHECK_4BYTE_MODE  0x20//���ͨ���Ƿ����4Byteģʽ�ı�־λ
#define CHECK_WIP         0x01//���ͨ���Ƿ����4Byteģʽ�ı�־λ

#endif // !MX25L25635F_H_
