#include <Windows.h>
#include <stdio.h>
#include"GCONST.H"
#include"Intersdk.h"
#include"RegBuffer.h"
#include"DllMain.H"
#include"PbInt.h"
#include"SpiProgrammerSetting.h"
#include "MX25L25635F.h"
const int BYTE_1K = 0x04;//一次读写多少个256字节 ,4*256是1K
const int WR_BUFFER_WRITE = 32 * BYTE_1K;//32M
const int WR_BUFFER_READ = 32 * BYTE_1K;//32K ，读最多一次32k


const bool B_4BYTE = true;//是否使用4Byte模式
const int CLK_DIV_VAL_HS = 0x02;//5倍分频
const int CLK_DIV_VAL_LS = 0x05;//5倍分频
const ULONG StartAddr = 0;//起始地址
const int CHSEL = 0x0F;
void Enter4ByteMode(HANDLE h, BYTE ChSel)
{
	CRegBuffer regBuf;
	regBuf.Init();

	//1.1
	regBuf.Push(0xC030, CLK_DIV_VAL_LS);
	regBuf.Push(0xC031, 0x01);//BYTE_ORDER
							  //3.1
	regBuf.Push(0xC801, SPI_CMD_WREN);
	regBuf.Push(0xC800, 0x02);// WREN_FORMAT
							  //3.2
	regBuf.Push(0xC803, SPI_CMD_RDSR);
	regBuf.Push(0xC802, 0x89);//RDSR_FORMAT
							  //3.3
	regBuf.Push(0xC804, 0x64);//WREN_LOOP_LIMIT
							  //3.4
	regBuf.Push(0xC808, 0xFF);
	regBuf.Push(0xC807, 0xFF);
	regBuf.Push(0xC806, 0xFF);
	regBuf.Push(0xC805, 0xFC);// RDSR_CHK_MASK
							  //3.5
	regBuf.Push(0xC80C, 0x00);
	regBuf.Push(0xC80B, 0x00);
	regBuf.Push(0xC80A, 0x00);
	regBuf.Push(0xC809, 0x02);// RDSR_CHK_TARGET
							  //3.6
	regBuf.Push(0xC811, 0x00);
	regBuf.Push(0xC810, 0x00);
	regBuf.Push(0xC80F, 0x00);
	regBuf.Push(0xC80E, 0x00);
	regBuf.Push(0xC80D, 0x00);//DATA_BYTE_NUM
							  //3.7
	regBuf.Push(0xC816, 0x00);
	regBuf.Push(0xC815, 0x00);
	regBuf.Push(0xC814, 0x00);
	regBuf.Push(0xC813, 0x00);
	regBuf.Push(0xC812, 0x01);// CMD_LOOP_NUM
							  //3.8
	regBuf.Push(0xC818, 0x00);
	regBuf.Push(0xC817, 0x20);//DAT_RDY_THRESHD
							  //3.9
	regBuf.Push(0xC819, 0x00);// USER_CMD_DEF
							  //3.10
	regBuf.Push(0xC81A, 0x06);//CSN_HIGH_PULSE

							  //4.1
	regBuf.Push(0xC82F, 0x00);
	regBuf.Push(0xC82E, 0x00);
	regBuf.Push(0xC82D, 0x00);
	regBuf.Push(0xC82C, 0x00);
	regBuf.Push(0xC82B, 0x00);
	regBuf.Push(0xC82A, 0x00);
	regBuf.Push(0xC829, 0x00);
	regBuf.Push(0xC828, 0x00);
	regBuf.Push(0xC827, 0x00);
	regBuf.Push(0xC826, 0x00);
	regBuf.Push(0xC825, 0x00);
	regBuf.Push(0xC824, 0x00);
	regBuf.Push(0xC823, 0x00);
	regBuf.Push(0xC822, 0x00);
	regBuf.Push(0xC821, 0x00);
	regBuf.Push(0xC820, 0x00);// CMD_ADDR
							  //4.2
	regBuf.Push(0xC834, 0x00);
	regBuf.Push(0xC833, 0x00);
	regBuf.Push(0xC832, 0x00);
	regBuf.Push(0xC831, 0x00);
	regBuf.Push(0xC830, 0x00);// CMD_ADDR_INC
							  //4.3
	regBuf.Push(0xC835, 0x00);// CMD_NEED_WREN
							  //4.4
	regBuf.Push(0xC836, SPI_CMD_EN4B);// CMD_INDEX
							  //4.5
	regBuf.Push(0xC837, 0x00);// DATA_DIREC
							  //4.6
	regBuf.Push(0xC838, 0x01);// SEG1_BUS_WIDTH
							  //4.7
	regBuf.Push(0xC839, 0x00);// ADDR_BYTE_NUM
							  //4.8
	regBuf.Push(0xC83A, 0x01);// SEG2_BUS_WIDTH
							  //4.9
	regBuf.Push(0xC83B, 0x00);// CMD_DAT_TX_RX
							  //4.10
	regBuf.Push(0xC83C, 0x01);//SEG3_BUS_WIDTH
							  //4.11
	regBuf.Push(0xC02A, CHSEL);//使能该通道
							  //4.12
	regBuf.Push(0xC050, 0x01);//ALLCH_SAME_CFG
							  //5.1
	regBuf.Push(0xC040, 0x01);
	WriteFPGA(h, regBuf.GetData(), regBuf.GetLength());
	BYTE byStatus;//状态
	do
	{
		ReadCPLD(h, 0xC040, byStatus);
	} while (byStatus != 0);
	BYTE st0, st1, st2, st3;
}

void Exit4ByteMode(HANDLE h, BYTE ChSel)
{
	CRegBuffer regBuf;
	regBuf.Init();

	//1.1
	regBuf.Push(0xC030, CLK_DIV_VAL_LS);
	regBuf.Push(0xC031, 0x01);//BYTE_ORDER
							  //3.1
	regBuf.Push(0xC801, SPI_CMD_WREN);
	regBuf.Push(0xC800, 0x02);// WREN_FORMAT
							  //3.2
	regBuf.Push(0xC803, SPI_CMD_RDSR);
	regBuf.Push(0xC802, 0x89);//RDSR_FORMAT
							  //3.3
	regBuf.Push(0xC804, 0x64);//WREN_LOOP_LIMIT
							  //3.4
	regBuf.Push(0xC808, 0xFF);
	regBuf.Push(0xC807, 0xFF);
	regBuf.Push(0xC806, 0xFF);
	regBuf.Push(0xC805, 0xFC);// RDSR_CHK_MASK
							  //3.5
	regBuf.Push(0xC80C, 0x00);
	regBuf.Push(0xC80B, 0x00);
	regBuf.Push(0xC80A, 0x00);
	regBuf.Push(0xC809, 0x02);// RDSR_CHK_TARGET
							  //3.6
	regBuf.Push(0xC811, 0x00);
	regBuf.Push(0xC810, 0x00);
	regBuf.Push(0xC80F, 0x00);
	regBuf.Push(0xC80E, 0x00);
	regBuf.Push(0xC80D, 0x00);//DATA_BYTE_NUM
							  //3.7
	regBuf.Push(0xC816, 0x00);
	regBuf.Push(0xC815, 0x00);
	regBuf.Push(0xC814, 0x00);
	regBuf.Push(0xC813, 0x00);
	regBuf.Push(0xC812, 0x01);// CMD_LOOP_NUM
							  //3.8
	regBuf.Push(0xC818, 0x00);
	regBuf.Push(0xC817, 0x20);//DAT_RDY_THRESHD
							  //3.9
	regBuf.Push(0xC819, 0x00);// USER_CMD_DEF
							  //3.10
	regBuf.Push(0xC81A, 0x06);//CSN_HIGH_PULSE

							  //4.1
	regBuf.Push(0xC82F, 0x00);
	regBuf.Push(0xC82E, 0x00);
	regBuf.Push(0xC82D, 0x00);
	regBuf.Push(0xC82C, 0x00);
	regBuf.Push(0xC82B, 0x00);
	regBuf.Push(0xC82A, 0x00);
	regBuf.Push(0xC829, 0x00);
	regBuf.Push(0xC828, 0x00);
	regBuf.Push(0xC827, 0x00);
	regBuf.Push(0xC826, 0x00);
	regBuf.Push(0xC825, 0x00);
	regBuf.Push(0xC824, 0x00);
	regBuf.Push(0xC823, 0x00);
	regBuf.Push(0xC822, 0x00);
	regBuf.Push(0xC821, 0x00);
	regBuf.Push(0xC820, 0x00);// CMD_ADDR
							  //4.2
	regBuf.Push(0xC834, 0x00);
	regBuf.Push(0xC833, 0x00);
	regBuf.Push(0xC832, 0x00);
	regBuf.Push(0xC831, 0x00);
	regBuf.Push(0xC830, 0x00);// CMD_ADDR_INC
							  //4.3
	regBuf.Push(0xC835, 0x00);// CMD_NEED_WREN
							  //4.4
	regBuf.Push(0xC836, SPI_CMD_EX4B);// CMD_INDEX
							  //4.5
	regBuf.Push(0xC837, 0x00);// DATA_DIREC
							  //4.6
	regBuf.Push(0xC838, 0x01);// SEG1_BUS_WIDTH
							  //4.7
	regBuf.Push(0xC839, 0x00);// ADDR_BYTE_NUM
							  //4.8
	regBuf.Push(0xC83A, 0x01);// SEG2_BUS_WIDTH
							  //4.9
	regBuf.Push(0xC83B, 0x00);// CMD_DAT_TX_RX
							  //4.10
	regBuf.Push(0xC83C, 0x01);//SEG3_BUS_WIDTH
							  //4.11
	regBuf.Push(0xC02A, CHSEL);//使能该通道
							  //4.12
	regBuf.Push(0xC050, 0x01);//ALLCH_SAME_CFG
							  //5.1
	regBuf.Push(0xC040, 0x01);
	WriteFPGA(h, regBuf.GetData(), regBuf.GetLength());
	BYTE byStatus;//状态
	do
	{
		ReadCPLD(h, 0xC040, byStatus);
	} while (byStatus != 0);

}

//检查是否进入4Byte模式，返回0x0f表示四个通道全部进入，否则该位为0的未进入
BYTE Check4ByteMode(HANDLE h, BYTE ChSel)
{
	//对于不同芯片需要读的寄存器不同
	//比如MX25L256要读Configration Register (0x15)
	//N25QL128要读Security Register 

	CRegBuffer regBuf;
	regBuf.Init();

	//1.1
	regBuf.Push(0xC030, CLK_DIV_VAL_LS);
	regBuf.Push(0xC031, 0x01);//BYTE_ORDER
							  //3.1
	regBuf.Push(0xC801, SPI_CMD_WREN);
	regBuf.Push(0xC800, 0x02);// WREN_FORMAT
							  //3.2
	regBuf.Push(0xC803, SPI_CMD_RDSR);
	regBuf.Push(0xC802, 0x89);//RDSR_FORMAT
							  //3.3
	regBuf.Push(0xC804, 0x64);//WREN_LOOP_LIMIT
							  //3.4
	regBuf.Push(0xC808, 0xFF);
	regBuf.Push(0xC807, 0xFF);
	regBuf.Push(0xC806, 0xFF);
	regBuf.Push(0xC805, 0xFC);// RDSR_CHK_MASK
							  //3.5
	regBuf.Push(0xC80C, 0x00);
	regBuf.Push(0xC80B, 0x00);
	regBuf.Push(0xC80A, 0x00);
	regBuf.Push(0xC809, 0x02);// RDSR_CHK_TARGET
							  //3.6
	regBuf.Push(0xC811, 0x00);
	regBuf.Push(0xC810, 0x00);
	regBuf.Push(0xC80F, 0x00);
	regBuf.Push(0xC80E, 0x00);
	regBuf.Push(0xC80D, 0x03);//DATA_BYTE_NUM
							  //3.7
	regBuf.Push(0xC816, 0x00);
	regBuf.Push(0xC815, 0x00);
	regBuf.Push(0xC814, 0x00);
	regBuf.Push(0xC813, 0x00);
	regBuf.Push(0xC812, 0x01);// CMD_LOOP_NUM
							  //3.8
	regBuf.Push(0xC818, 0x00);
	regBuf.Push(0xC817, 0x20);//DAT_RDY_THRESHD
							  //3.9
	regBuf.Push(0xC819, 0x00);// USER_CMD_DEF
							  //3.10
	regBuf.Push(0xC81A, 0x06);//CSN_HIGH_PULSE

							  //4.1
	regBuf.Push(0xC82F, 0x00);
	regBuf.Push(0xC82E, 0x00);
	regBuf.Push(0xC82D, 0x00);
	regBuf.Push(0xC82C, 0x00);
	regBuf.Push(0xC82B, 0x00);
	regBuf.Push(0xC82A, 0x00);
	regBuf.Push(0xC829, 0x00);
	regBuf.Push(0xC828, 0x00);
	regBuf.Push(0xC827, 0x00);
	regBuf.Push(0xC826, 0x00);
	regBuf.Push(0xC825, 0x00);
	regBuf.Push(0xC824, 0x00);
	regBuf.Push(0xC823, 0x00);
	regBuf.Push(0xC822, 0x00);
	regBuf.Push(0xC821, 0x00);
	regBuf.Push(0xC820, 0x00);// CMD_ADDR
							  //4.2
	regBuf.Push(0xC834, 0x00);
	regBuf.Push(0xC833, 0x00);
	regBuf.Push(0xC832, 0x00);
	regBuf.Push(0xC831, 0x00);
	regBuf.Push(0xC830, 0x00);// CMD_ADDR_INC
							  //4.3
	regBuf.Push(0xC835, 0x00);// CMD_NEED_WREN
							  //4.4
	regBuf.Push(0xC836, SPI_CMD_CHECK_4BYTE);// CMD_INDEX
							  //4.5
	regBuf.Push(0xC837, 0x00);// DATA_DIREC
							  //4.6
	regBuf.Push(0xC838, 0x01);// SEG1_BUS_WIDTH
							  //4.7
	regBuf.Push(0xC839, 0x00);// ADDR_BYTE_NUM
							  //4.8
	regBuf.Push(0xC83A, 0x01);// SEG2_BUS_WIDTH
							  //4.9
	regBuf.Push(0xC83B, 0x01);// CMD_DAT_TX_RX
							  //4.10
	regBuf.Push(0xC83C, 0x01);//SEG3_BUS_WIDTH
							  //4.11
	regBuf.Push(0xC02A, CHSEL);//使能该通道
							  //4.12
	regBuf.Push(0xC050, 0x01);//ALLCH_SAME_CFG
							  //5.1
	regBuf.Push(0xC040, 0x01);
	WriteFPGA(h, regBuf.GetData(), regBuf.GetLength());
	BYTE byStatus;//状态
	do
	{
		ReadCPLD(h, 0xC040, byStatus);
	} while (byStatus != 0);

	BYTE st0, st1, st2, st3;
	// CH0
	//PRINT:[0xC060..0xC067]
	ReadCPLD(h, 0xC060, byStatus);
	if (byStatus & CHECK_4BYTE_MODE)
		st0 = 0x01;
	else
		st0 = 0x00;

	// CH1
	//PRINT : [0xC068..0xC06F]
	ReadCPLD(h, 0xC068, byStatus);
	if (byStatus & CHECK_4BYTE_MODE)
		st1 = 0x02;
	else
		st1 = 0x00;
	// CH2
	//PRINT : [0xC070..0xC077]
	ReadCPLD(h, 0xC070, byStatus);
	if (byStatus & CHECK_4BYTE_MODE)
		st2 = 0x04;
	else
		st2 = 0x00;
	// CH3
	//PRINT : [0xC078..0xC07F]
	ReadCPLD(h, 0xC078, byStatus);
	if (byStatus & CHECK_4BYTE_MODE)
		st3 = 0x08;
	else
		st3 = 0x00;

	return st0 | st1 | st2 | st3;
}

void SetWriteParam(HANDLE h,ULONG ulStartAddr, BOOL b4ByteMode,BYTE ChSel)
{
	CRegBuffer regBuf;
	regBuf.Init();
	//1.1
	regBuf.Push(0xC030, CLK_DIV_VAL_LS);
	regBuf.Push(0xC031, 0x01);//BYTE_ORDER
							  //3.1
	regBuf.Push(0xC801, SPI_CMD_WREN);
	regBuf.Push(0xC800, 0x02);// WREN_FORMAT
							  //3.2
	regBuf.Push(0xC803, SPI_CMD_RDSR);
	regBuf.Push(0xC802, 0x89);//RDSR_FORMAT
							  //3.3
	regBuf.Push(0xC804, 0xF0);//WREN_LOOP_LIMIT
							  //3.4
	regBuf.Push(0xC808, 0xFF);
	regBuf.Push(0xC807, 0xFF);
	regBuf.Push(0xC806, 0xFF);
	regBuf.Push(0xC805, 0xFC);// RDSR_CHK_MASK
							  //3.5
	regBuf.Push(0xC80C, 0x00);
	regBuf.Push(0xC80B, 0x00);
	regBuf.Push(0xC80A, 0x00);
	regBuf.Push(0xC809, 0x02);// RDSR_CHK_TARGET
							  //3.6
	regBuf.Push(0xC811, 0x00);
	regBuf.Push(0xC810, 0x00);
	regBuf.Push(0xC80F, 0x00);
	regBuf.Push(0xC80E, 0x01);
	regBuf.Push(0xC80D, 0x00);//DATA_BYTE_NUM
							  //3.7
	regBuf.Push(0xC816, WR_BUFFER_WRITE / 256 / 256 / 256 / 256);
	regBuf.Push(0xC815, WR_BUFFER_WRITE / 256 / 256 / 256);
	regBuf.Push(0xC814, WR_BUFFER_WRITE / 256 / 256);
	regBuf.Push(0xC813, WR_BUFFER_WRITE / 256);
	regBuf.Push(0xC812, WR_BUFFER_WRITE % 256);// CMD_LOOP_NUM
										 //3.8
	regBuf.Push(0xC818, 0x00);
	regBuf.Push(0xC817, 0xF0);//DAT_RDY_THRESHD *******************写入多少代码开始执行
							  //3.9
	regBuf.Push(0xC819, 0x00);// USER_CMD_DEF
							  //3.10
	regBuf.Push(0xC81A, 0x80);//CSN_HIGH_PULSE

							  //4.1
							  //if (b4ByteMode)
							  //{
							  //	regBuf.Push(0xC82F, (ulStartAddr >> 24) & 0xFF);
							  //	regBuf.Push(0xC82E, (ulStartAddr >> 16) & 0xFF);// *
							  //	regBuf.Push(0xC82D, (ulStartAddr >> 8) & 0xFF);//4Byte模式向下移动，此处为ulStartAddr>>8
							  //	regBuf.Push(0xC82C, (ulStartAddr) & 0xFF);
							  //}
							  //else
							  //{
							  //	regBuf.Push(0xC82F, (ulStartAddr >> 16) & 0xFF);
							  //	regBuf.Push(0xC82E, (ulStartAddr >> 8) & 0xFF);// *
							  //	regBuf.Push(0xC82D, (ulStartAddr) & 0xFF);//4Byte模式向下移动，此处为ulStartAddr>>8
							  //	regBuf.Push(0xC82C, 0x00);
							  //}
	regBuf.Push(0xC82B, 0x00);
	regBuf.Push(0xC82A, 0x00);
	regBuf.Push(0xC829, 0x00);
	regBuf.Push(0xC828, 0x00);
	regBuf.Push(0xC827, 0x00);
	regBuf.Push(0xC826, 0x00);
	regBuf.Push(0xC825, 0x00);
	regBuf.Push(0xC824, 0x00);
	regBuf.Push(0xC823, 0x00);
	regBuf.Push(0xC822, 0x00);
	regBuf.Push(0xC821, 0x00);
	regBuf.Push(0xC820, 0x00);// CMD_ADDR
							  //4.2
	if (B_4BYTE)
	{
		regBuf.Push(0xC834, 0x00);
		regBuf.Push(0xC833, 0x00);// *3Byte模式写01,4Byte模式写00
		regBuf.Push(0xC832, 0x01);// *3Byte模式写00,4Byte模式写01
		regBuf.Push(0xC831, 0x00);
		regBuf.Push(0xC830, 0x00);// CMD_ADDR_INC
	}
	else
	{
		regBuf.Push(0xC834, 0x00);
		regBuf.Push(0xC833, 0x01);// *3Byte模式写01,4Byte模式写00
		regBuf.Push(0xC832, 0x00);// *3Byte模式写00,4Byte模式写01
		regBuf.Push(0xC831, 0x00);
		regBuf.Push(0xC830, 0x00);// CMD_ADDR_INC
	}
	//4.3
	regBuf.Push(0xC835, 0x01);// CMD_NEED_WREN****************
							  //4.4
	regBuf.Push(0xC836, SPI_CMD_PP);// CMD_INDEX****************
									//4.5
	regBuf.Push(0xC837, 0x28);// DATA_DIREC**************** *
							  //4.6
	regBuf.Push(0xC838, 0x01);// SEG1_BUS_WIDTH
							  //4.7
	if (B_4BYTE)
		regBuf.Push(0xC839, 0x04);// ADDR_BYTE_NUM *3Byte模式写03,4Byte模式写04
	else
		regBuf.Push(0xC839, 0x03);// ADDR_BYTE_NUM *3Byte模式写03,4Byte模式写04
								  //4.8
	regBuf.Push(0xC83A, 0x01);// SEG2_BUS_WIDTH
							  //4.9
	regBuf.Push(0xC83B, 0x02);// CMD_DAT_TX_RX**************** *
							  //4.10
	regBuf.Push(0xC83C, 0x01);//SEG3_BUS_WIDTH
							  //4.11
	regBuf.Push(0xC02A, CHSEL);//使能该通道
							   //4.12
	regBuf.Push(0xC050, 0x01);//ALLCH_SAME_CFG
							  //5.1
	WriteFPGA(h, regBuf.GetData(), regBuf.GetLength());
	BYTE byStatus;//状态
	do
	{
		ReadCPLD(h, 0xC040, byStatus);
	} while (byStatus != 0);

/*

	//if (b4ByteMode)
	//	Enter4ByteMode(h,ChSel);
	CRegBuffer regBuf;
	regBuf.Init();
	////1.1
	//regBuf.Push(0xC030, CLK_DIV_VAL_LS);
	//regBuf.Push(0xC031, 0x01);//BYTE_ORDER
	//						  //3.1
	//regBuf.Push(0xC801, SPI_CMD_WREN);
	//regBuf.Push(0xC800, 0x02);// WREN_FORMAT
	//						  //3.2
	//regBuf.Push(0xC803, SPI_CMD_RDSR);
	//regBuf.Push(0xC802, 0x89);//RDSR_FORMAT
	//						  //3.3
	//regBuf.Push(0xC804, 0xF0);//WREN_LOOP_LIMIT
	//						  //3.4
	//regBuf.Push(0xC808, 0xFF);
	//regBuf.Push(0xC807, 0xFF);
	//regBuf.Push(0xC806, 0xFF);
	//regBuf.Push(0xC805, 0xFC);// RDSR_CHK_MASK
	//						  //3.5
	//regBuf.Push(0xC80C, 0x00);
	//regBuf.Push(0xC80B, 0x00);
	//regBuf.Push(0xC80A, 0x00);
	//regBuf.Push(0xC809, 0x02);// RDSR_CHK_TARGET
	//						  //3.6
	//regBuf.Push(0xC811, 0x00);
	//regBuf.Push(0xC810, 0x00);
	//regBuf.Push(0xC80F, 0x00);
	//regBuf.Push(0xC80E, 0x01);
	//regBuf.Push(0xC80D, 0x00);//DATA_BYTE_NUM
	//						  //3.7
	//regBuf.Push(0xC816, WR_BUFFER / 256 / 256 / 256 / 256);
	//regBuf.Push(0xC815, WR_BUFFER / 256 / 256 / 256);
	//regBuf.Push(0xC814, WR_BUFFER / 256 / 256);
	//regBuf.Push(0xC813, WR_BUFFER / 256);
	//regBuf.Push(0xC812, WR_BUFFER % 256);// CMD_LOOP_NUM
	//									 //3.8
	//regBuf.Push(0xC818, 0x00);
	//regBuf.Push(0xC817, 0xF0);//DAT_RDY_THRESHD *******************写入多少代码开始执行
	//						  //3.9
	//regBuf.Push(0xC819, 0x00);// USER_CMD_DEF
	//						  //3.10
	//regBuf.Push(0xC81A, 0x80);//CSN_HIGH_PULSE

							  //4.1
	if (b4ByteMode)
	{
		regBuf.Push(0xC82F, (ulStartAddr >> 24) & 0xFF);
		regBuf.Push(0xC82E, (ulStartAddr >> 16) & 0xFF);// *
		regBuf.Push(0xC82D, (ulStartAddr >> 8) & 0xFF);//4Byte模式向下移动，此处为ulStartAddr>>8
		regBuf.Push(0xC82C, (ulStartAddr) & 0xFF);
	}
	else
	{
		regBuf.Push(0xC82F, (ulStartAddr >> 16) & 0xFF);
		regBuf.Push(0xC82E, (ulStartAddr >> 8) & 0xFF);// *
		regBuf.Push(0xC82D, (ulStartAddr) & 0xFF);//4Byte模式向下移动，此处为ulStartAddr>>8
		regBuf.Push(0xC82C, 0x00);
	}
	//regBuf.Push(0xC82B, 0x00);
	//regBuf.Push(0xC82A, 0x00);
	//regBuf.Push(0xC829, 0x00);
	//regBuf.Push(0xC828, 0x00);
	//regBuf.Push(0xC827, 0x00);
	//regBuf.Push(0xC826, 0x00);
	//regBuf.Push(0xC825, 0x00);
	//regBuf.Push(0xC824, 0x00);
	//regBuf.Push(0xC823, 0x00);
	//regBuf.Push(0xC822, 0x00);
	//regBuf.Push(0xC821, 0x00);
	//regBuf.Push(0xC820, 0x00);// CMD_ADDR
	//						  //4.2
	//if (b4ByteMode)
	//{
	//	regBuf.Push(0xC834, 0x00);
	//	regBuf.Push(0xC833, 0x00);// *3Byte模式写01,4Byte模式写00
	//	regBuf.Push(0xC832, 0x01);// *3Byte模式写00,4Byte模式写01
	//	regBuf.Push(0xC831, 0x00);
	//	regBuf.Push(0xC830, 0x00);// CMD_ADDR_INC
	//}
	//else
	//{
	//	regBuf.Push(0xC834, 0x00);
	//	regBuf.Push(0xC833, 0x01);// *3Byte模式写01,4Byte模式写00
	//	regBuf.Push(0xC832, 0x00);// *3Byte模式写00,4Byte模式写01
	//	regBuf.Push(0xC831, 0x00);
	//	regBuf.Push(0xC830, 0x00);// CMD_ADDR_INC
	//}
	//						  //4.3
	//regBuf.Push(0xC835, 0x01);// CMD_NEED_WREN****************
	//						  //4.4
	//regBuf.Push(0xC836, SPI_CMD_PP);// CMD_INDEX****************
	//						  //4.5
	//regBuf.Push(0xC837, 0x28);// DATA_DIREC**************** *
	//						  //4.6
	//regBuf.Push(0xC838, 0x01);// SEG1_BUS_WIDTH
	//						  //4.7
	//if(b4ByteMode)
	//	regBuf.Push(0xC839, 0x04);// ADDR_BYTE_NUM *3Byte模式写03,4Byte模式写04
	//else
	//	regBuf.Push(0xC839, 0x03);// ADDR_BYTE_NUM *3Byte模式写03,4Byte模式写04
	//						  //4.8
	//regBuf.Push(0xC83A, 0x01);// SEG2_BUS_WIDTH
	//						  //4.9
	//regBuf.Push(0xC83B, 0x02);// CMD_DAT_TX_RX**************** *
	//						  //4.10
	//regBuf.Push(0xC83C, 0x01);//SEG3_BUS_WIDTH
	//						  //4.11
	//regBuf.Push(0xC02A, CHSEL);//使能该通道
	//						  //4.12
	//regBuf.Push(0xC050, 0x01);//ALLCH_SAME_CFG
	//						  //5.1
	WriteFPGA(h, regBuf.GetData(), regBuf.GetLength());
	BYTE byStatus;//状态
	do
	{
		ReadCPLD(h, 0xC040, byStatus);
	} while (byStatus != 0);
*/
}

void SetVerifyParam(HANDLE h, ULONG ulStartAddr, BOOL b4ByteMode, BYTE ChSel)
{
	//if (b4ByteMode)
	//	Enter4ByteMode(h, ChSel);
	CRegBuffer regBuf;
	regBuf.Init();
	//1.1
	regBuf.Push(0xC030, CLK_DIV_VAL_HS);
	regBuf.Push(0xC031, 0x01);//BYTE_ORDER
							  //3.1
	regBuf.Push(0xC801, SPI_CMD_WREN);
	regBuf.Push(0xC800, 0x02);// WREN_FORMAT
							  //3.2
	regBuf.Push(0xC803, SPI_CMD_RDSR);
	regBuf.Push(0xC802, 0x89);//RDSR_FORMAT
							  //3.3
	regBuf.Push(0xC804, 0x64);//WREN_LOOP_LIMIT
							  //3.4
	regBuf.Push(0xC808, 0xFF);
	regBuf.Push(0xC807, 0xFF);
	regBuf.Push(0xC806, 0xFF);
	regBuf.Push(0xC805, 0xFC);// RDSR_CHK_MASK
							  //3.5
	regBuf.Push(0xC80C, 0x00);
	regBuf.Push(0xC80B, 0x00);
	regBuf.Push(0xC80A, 0x00);
	regBuf.Push(0xC809, 0x02);// RDSR_CHK_TARGET
							  //3.6
	regBuf.Push(0xC811, WR_BUFFER_READ / 256 / 256 / 256);
	regBuf.Push(0xC810, WR_BUFFER_READ / 256 / 256);
	regBuf.Push(0xC80F, WR_BUFFER_READ / 256);
	regBuf.Push(0xC80E, WR_BUFFER_READ % 256);
	regBuf.Push(0xC80D, 0x00);//DATA_BYTE_NUM
							  //3.7
	regBuf.Push(0xC816, 0x00);
	regBuf.Push(0xC815, 0x00);
	regBuf.Push(0xC814, 0x00);
	regBuf.Push(0xC813, 0x00);
	regBuf.Push(0xC812, 0x01);// CMD_LOOP_NUM
							  //3.8
	regBuf.Push(0xC818, 0x00);
	regBuf.Push(0xC817, 0x02);//DAT_RDY_THRESHD****************
							  //3.9
	regBuf.Push(0xC819, 0x00);// USER_CMD_DEF
							  //3.10
	regBuf.Push(0xC81A, 0x06);//CSN_HIGH_PULSE

							  //4.1
	regBuf.Push(0xC82B, 0x00);
	regBuf.Push(0xC82A, 0x00);
	regBuf.Push(0xC829, 0x00);
	regBuf.Push(0xC828, 0x00);
	regBuf.Push(0xC827, 0x00);
	regBuf.Push(0xC826, 0x00);
	regBuf.Push(0xC825, 0x00);
	regBuf.Push(0xC824, 0x00);
	regBuf.Push(0xC823, 0x00);
	regBuf.Push(0xC822, 0x00);
	regBuf.Push(0xC821, 0x00);
	regBuf.Push(0xC820, 0x00);// CMD_ADDR**************
							  //4.2
	if (b4ByteMode)
	{
		regBuf.Push(0xC834, 0x00);
		regBuf.Push(0xC833, 0x00);
		regBuf.Push(0xC832, 0x01);
		regBuf.Push(0xC831, 0x00);
		regBuf.Push(0xC830, 0x00);// CMD_ADDR_INC*****************
	}
	else
	{
		regBuf.Push(0xC834, 0x00);
		regBuf.Push(0xC833, 0x01);
		regBuf.Push(0xC832, 0x00);
		regBuf.Push(0xC831, 0x00);
		regBuf.Push(0xC830, 0x00);// CMD_ADDR_INC*****************
	}
							  //4.3
	regBuf.Push(0xC835, 0x00);// CMD_NEED_WREN****************
							  //4.4
	regBuf.Push(0xC836, SPI_CMD_VERIFY);// CMD_INDEX****************
							  //4.5
	regBuf.Push(0xC837, 0x30);// DATA_DIREC****************
							  //4.6
	regBuf.Push(0xC838, 0x01);// SEG1_BUS_WIDTH
							  //4.7
	if (b4ByteMode)
		regBuf.Push(0xC839, 0x04);// ADDR_BYTE_NUM *3Byte模式写03,4Byte模式写04
	else
		regBuf.Push(0xC839, 0x03);// ADDR_BYTE_NUM *3Byte模式写03,4Byte模式写04
								  //4.8
	regBuf.Push(0xC83A, 0x01);// SEG2_BUS_WIDTH
							  //4.9
	regBuf.Push(0xC83B, 0x01);// CMD_DAT_TX_RX****************
							  //4.10
	regBuf.Push(0xC83C, 0x01);//SEG3_BUS_WIDTH
							  //4.11
	regBuf.Push(0xC02A, CHSEL);//使能该通道
							  //4.12
	regBuf.Push(0xC050, 0x01);//ALLCH_SAME_CFG
							  //5.1

	WriteFPGA(h, regBuf.GetData(), regBuf.GetLength());
	BYTE byStatus;//状态
	do
	{
		ReadCPLD(h, 0xC040, byStatus);
	} while (byStatus != 0);

}

void SetReadParam(HANDLE h, ULONG ulStartAddr, BOOL b4ByteMode, BYTE ChSel)
{
	//if (b4ByteMode)
	//	Enter4ByteMode(h, ChSel);
	CRegBuffer regBuf;

	regBuf.Init();
	//1.1
	regBuf.Push(0xC030, CLK_DIV_VAL_HS);
	regBuf.Push(0xC031, 0x01);//BYTE_ORDER
							  //3.1
	regBuf.Push(0xC801, SPI_CMD_WREN);
	regBuf.Push(0xC800, 0x02);// WREN_FORMAT
							  //3.2
	regBuf.Push(0xC803, SPI_CMD_RDSR);
	regBuf.Push(0xC802, 0x89);//RDSR_FORMAT
							  //3.3
	regBuf.Push(0xC804, 0x64);//WREN_LOOP_LIMIT
							  //3.4
	regBuf.Push(0xC808, 0xFF);
	regBuf.Push(0xC807, 0xFF);
	regBuf.Push(0xC806, 0xFF);
	regBuf.Push(0xC805, 0xFC);// RDSR_CHK_MASK
							  //3.5
	regBuf.Push(0xC80C, 0x00);
	regBuf.Push(0xC80B, 0x00);
	regBuf.Push(0xC80A, 0x00);
	regBuf.Push(0xC809, 0x02);// RDSR_CHK_TARGET
				
							  //3.6
	regBuf.Push(0xC811, WR_BUFFER_READ / 256 / 256 / 256);
	regBuf.Push(0xC810, WR_BUFFER_READ / 256 / 256);
	regBuf.Push(0xC80F, WR_BUFFER_READ / 256);
	regBuf.Push(0xC80E, WR_BUFFER_READ % 256);
	regBuf.Push(0xC80D, 0x00);//DATA_BYTE_NUM
							  //3.7
	//regBuf.Push(0xC816, WR_BUFFER / 256 / 256 / 256 / 256);
	//regBuf.Push(0xC815, WR_BUFFER / 256 / 256 / 256);
	//regBuf.Push(0xC814, WR_BUFFER / 256 / 256);
	//regBuf.Push(0xC813, WR_BUFFER / 256);
	//regBuf.Push(0xC812, WR_BUFFER % 256);// CMD_LOOP_NUM
										 //3.8
	regBuf.Push(0xC816, 0x00);
	regBuf.Push(0xC815, 0x00);
	regBuf.Push(0xC814, 0x00);
	regBuf.Push(0xC813, 0x00);
	regBuf.Push(0xC812, 0x01);// CMD_LOOP_NUM
										 //3.8
	regBuf.Push(0xC818, 0x00);
	regBuf.Push(0xC817, 0x02);//DAT_RDY_THRESHD
							  //3.9
	regBuf.Push(0xC819, 0x00);// USER_CMD_DEF
							  //3.10
	regBuf.Push(0xC81A, 0x06);//CSN_HIGH_PULSE

							  //4.1
	regBuf.Push(0xC82B, 0x00);
	regBuf.Push(0xC82A, 0x00);
	regBuf.Push(0xC829, 0x00);
	regBuf.Push(0xC828, 0x00);
	regBuf.Push(0xC827, 0x00);
	regBuf.Push(0xC826, 0x00);
	regBuf.Push(0xC825, 0x00);
	regBuf.Push(0xC824, 0x00);
	regBuf.Push(0xC823, 0x00);
	regBuf.Push(0xC822, 0x00);
	regBuf.Push(0xC821, 0x00);
	regBuf.Push(0xC820, 0x00);// CMD_ADDR
							  //4.2
	if (b4ByteMode)
	{
		regBuf.Push(0xC834, 0x00);
		regBuf.Push(0xC833, 0x00);
		regBuf.Push(0xC832, 0x01);
		regBuf.Push(0xC831, 0x00);
		regBuf.Push(0xC830, 0x00);// CMD_ADDR_INC*****************
	}
	else
	{
		regBuf.Push(0xC834, 0x00);
		regBuf.Push(0xC833, 0x01);
		regBuf.Push(0xC832, 0x00);
		regBuf.Push(0xC831, 0x00);
		regBuf.Push(0xC830, 0x00);// CMD_ADDR_INC*****************
	}
	//4.3
	regBuf.Push(0xC835, 0x00);// CMD_NEED_WREN
							  //4.4
	regBuf.Push(0xC836, SPI_CMD_READ);// CMD_INDEX****************
								  //4.5
	regBuf.Push(0xC837, 0x01);// DATA_DIREC
							  //4.6
	regBuf.Push(0xC838, 0x01);// SEG1_BUS_WIDTH
							  //4.7
	if (b4ByteMode)
		regBuf.Push(0xC839, 0x04);// ADDR_BYTE_NUM *3Byte模式写03,4Byte模式写04
	else
		regBuf.Push(0xC839, 0x03);// ADDR_BYTE_NUM *3Byte模式写03,4Byte模式写04
								  //4.8
	regBuf.Push(0xC83A, 0x01);// SEG2_BUS_WIDTH
							  //4.9
	regBuf.Push(0xC83B, 0x01);// CMD_DAT_TX_RX
							  //4.10
	regBuf.Push(0xC83C, 0x01);//SEG3_BUS_WIDTH
							  //4.11
	regBuf.Push(0xC02A, CHSEL);//使能该通道
							  //4.12
	regBuf.Push(0xC050, 0x01);//ALLCH_SAME_CFG
							  //5.1
	WriteFPGA(h, regBuf.GetData(), regBuf.GetLength());	
	BYTE byStatus;//状态
	do
	{
		ReadCPLD(h, 0xC040, byStatus);
	} while (byStatus != 0);

}
bool ReadRDSR(HANDLE h, BYTE &ChSel)
{
	BYTE byStatus;//状态
	CRegBuffer regBuf;

	regBuf.Init();
	//1.1
	regBuf.Push(0xC030, 0x02);
	regBuf.Push(0xC031, 0x01);//BYTE_ORDER
							  //3.1
	regBuf.Push(0xC801, SPI_CMD_WREN);
	regBuf.Push(0xC800, 0x02);// WREN_FORMAT
							  //3.2
	regBuf.Push(0xC803, SPI_CMD_RDSR);
	regBuf.Push(0xC802, 0x89);//RDSR_FORMAT
							  //3.3
	regBuf.Push(0xC804, 0x64);//WREN_LOOP_LIMIT
							  //3.4
	regBuf.Push(0xC808, 0xFF);
	regBuf.Push(0xC807, 0xFF);
	regBuf.Push(0xC806, 0xFF);
	regBuf.Push(0xC805, 0xFC);// RDSR_CHK_MASK
							  //3.5
	regBuf.Push(0xC80C, 0x00);
	regBuf.Push(0xC80B, 0x00);
	regBuf.Push(0xC80A, 0x00);
	regBuf.Push(0xC809, 0x02);// RDSR_CHK_TARGET
							  //3.6
	regBuf.Push(0xC811, 0x00);
	regBuf.Push(0xC810, 0x00);
	regBuf.Push(0xC80F, 0x00);
	regBuf.Push(0xC80E, 0x00);
	regBuf.Push(0xC80D, 0x01);//DATA_BYTE_NUM	擦除不用设置数据长度
							  //3.7
	regBuf.Push(0xC816, 0x00);
	regBuf.Push(0xC815, 0x00);
	regBuf.Push(0xC814, 0x00);
	regBuf.Push(0xC813, 0x00);
	regBuf.Push(0xC812, 0x01);// CMD_LOOP_NUM	擦除需要循环一次
							  //3.8
	regBuf.Push(0xC818, 0x00);
	regBuf.Push(0xC817, 0x02);//DAT_RDY_THRESHD
							  //3.9
	regBuf.Push(0xC819, 0x00);// USER_CMD_DEF
							  //3.10
	regBuf.Push(0xC81A, 0x06);//CSN_HIGH_PULSE

							  //4.1
	regBuf.Push(0xC82F, 0x00);
	regBuf.Push(0xC82E, 0x00);
	regBuf.Push(0xC82D, 0x00);
	regBuf.Push(0xC82C, 0x00);
	regBuf.Push(0xC82B, 0x00);
	regBuf.Push(0xC82A, 0x00);
	regBuf.Push(0xC829, 0x00);
	regBuf.Push(0xC828, 0x00);
	regBuf.Push(0xC827, 0x00);
	regBuf.Push(0xC826, 0x00);
	regBuf.Push(0xC825, 0x00);
	regBuf.Push(0xC824, 0x00);
	regBuf.Push(0xC823, 0x00);
	regBuf.Push(0xC822, 0x00);
	regBuf.Push(0xC821, 0x00);
	regBuf.Push(0xC820, 0x00);// CMD_ADDR**************
							  //4.2
	regBuf.Push(0xC834, 0x00);
	regBuf.Push(0xC833, 0x00);
	regBuf.Push(0xC832, 0x00);
	regBuf.Push(0xC831, 0x00);
	regBuf.Push(0xC830, 0x00);// CMD_ADDR_INC*****************
							  //4.3
	regBuf.Push(0xC835, 0x00);// CMD_NEED_WREN****************
							  //4.4
	regBuf.Push(0xC836, SPI_CMD_RDSR);// CMD_INDEX****************
										 //4.5
	regBuf.Push(0xC837, 0x00);// DATA_DIREC****************
							  //4.6
	regBuf.Push(0xC838, 0x01);// SEG1_BUS_WIDTH
							  //4.7
	regBuf.Push(0xC839, 0x00);// ADDR_BYTE_NUM
							  //4.8
	regBuf.Push(0xC83A, 0x01);// SEG2_BUS_WIDTH
							  //4.9
	regBuf.Push(0xC83B, 0x01);// CMD_DAT_TX_RX****************
							  //4.10
	regBuf.Push(0xC83C, 0x01);//SEG3_BUS_WIDTH
							  //4.11
	regBuf.Push(0xC02A, ChSel);//使能该通道
							   //4.12
	regBuf.Push(0xC050, 0x01);//ALLCH_SAME_CFG
							  //5.1
	regBuf.Push(0xC040, 0x01);

	WriteFPGA(h, regBuf.GetData(), regBuf.GetLength());
	//WriteDMANotSetLength(h, pBuf, ulLen);
	do
	{
		ReadCPLD(h, 0xC040, byStatus);
	} while (byStatus != 0);

	BYTE st0, st1, st2, st3;
	//if(ChSel)
	// CH0
	//PRINT:[0xC060..0xC067]
	ReadCPLD(h, 0xC060, byStatus);
	if (byStatus & CHECK_WIP)
		st0 = 0x01;
	else
		st0 = 0x00;

	// CH1
	//PRINT : [0xC068..0xC06F]
	ReadCPLD(h, 0xC068, byStatus);
	if (byStatus & CHECK_WIP)
		st1 = 0x02;
	else
		st1 = 0x00;
	// CH2
	//PRINT : [0xC070..0xC077]
	ReadCPLD(h, 0xC070, byStatus);
	if (byStatus & CHECK_WIP)
		st2 = 0x04;
	else
		st2 = 0x00;
	// CH3
	//PRINT : [0xC078..0xC07F]
	ReadCPLD(h, 0xC078, byStatus);
	if (byStatus & CHECK_WIP)
		st3 = 0x08;
	else
		st3 = 0x00;

	return st0/* | st1 | st2 | st3*/;

}
void WINAPI SPIErase(HANDLE h, PDEVICE p, PBYTE pBuf, LPVOID pf[], BYTE &ChSel)
{
	BYTE byStatus;//状态
	ULONG ulRemain,//剩余数据
		ulStartAddr, //写起始地址
		ulLen;//写的长度
	WORD wPageSize;//页大小
	WORD wPageNo;//页数量
	ULONG ulPbValue;//进度条
	INT64 llChipSize;//芯片大小
	CRegBuffer regBuf;

	llChipSize = p->llMemSize[0];
	if (ChSel == 0)
		return;

	regBuf.Init();
	//1.1
	regBuf.Push(0xC030, 0x05);
	regBuf.Push(0xC031, 0x01);//BYTE_ORDER
							  //3.1
	regBuf.Push(0xC801, SPI_CMD_WREN);
	regBuf.Push(0xC800, 0x02);// WREN_FORMAT
							  //3.2
	regBuf.Push(0xC803, SPI_CMD_RDSR);
	regBuf.Push(0xC802, 0x89);//RDSR_FORMAT
							  //3.3
	regBuf.Push(0xC804, 0x64);//WREN_LOOP_LIMIT
							  //3.4
	regBuf.Push(0xC808, 0xFF);
	regBuf.Push(0xC807, 0xFF);
	regBuf.Push(0xC806, 0xFF);
	regBuf.Push(0xC805, 0xFC);// RDSR_CHK_MASK
							  //3.5
	regBuf.Push(0xC80C, 0x00);
	regBuf.Push(0xC80B, 0x00);
	regBuf.Push(0xC80A, 0x00);
	regBuf.Push(0xC809, 0x02);// RDSR_CHK_TARGET
							  //3.6
	regBuf.Push(0xC811, 0x00);
	regBuf.Push(0xC810, 0x00);
	regBuf.Push(0xC80F, 0x00);
	regBuf.Push(0xC80E, 0x00);
	regBuf.Push(0xC80D, 0x00);//DATA_BYTE_NUM	擦除不用设置数据长度
							  //3.7
	regBuf.Push(0xC816, 0x00);
	regBuf.Push(0xC815, 0x00);
	regBuf.Push(0xC814, 0x00);
	regBuf.Push(0xC813, 0x00);
	regBuf.Push(0xC812, 0x01);// CMD_LOOP_NUM	擦除需要循环一次
							  //3.8
	regBuf.Push(0xC818, 0x00);
	regBuf.Push(0xC817, 0x02);//DAT_RDY_THRESHD
							  //3.9
	regBuf.Push(0xC819, 0x00);// USER_CMD_DEF
							  //3.10
	regBuf.Push(0xC81A, 0x06);//CSN_HIGH_PULSE

							  //4.1
	regBuf.Push(0xC82F, 0x00);
	regBuf.Push(0xC82E, 0x00);
	regBuf.Push(0xC82D, 0x00);
	regBuf.Push(0xC82C, 0x00);
	regBuf.Push(0xC82B, 0x00);
	regBuf.Push(0xC82A, 0x00);
	regBuf.Push(0xC829, 0x00);
	regBuf.Push(0xC828, 0x00);
	regBuf.Push(0xC827, 0x00);
	regBuf.Push(0xC826, 0x00);
	regBuf.Push(0xC825, 0x00);
	regBuf.Push(0xC824, 0x00);
	regBuf.Push(0xC823, 0x00);
	regBuf.Push(0xC822, 0x00);
	regBuf.Push(0xC821, 0x00);
	regBuf.Push(0xC820, 0x00);// CMD_ADDR**************
							  //4.2
	regBuf.Push(0xC834, 0x00);
	regBuf.Push(0xC833, 0x00);
	regBuf.Push(0xC832, 0x00);
	regBuf.Push(0xC831, 0x00);
	regBuf.Push(0xC830, 0x00);// CMD_ADDR_INC*****************
							  //4.3
	regBuf.Push(0xC835, 0x01);// CMD_NEED_WREN****************
							  //4.4
	regBuf.Push(0xC836, SPI_CMD_ERASE_CE1);// CMD_INDEX****************
							  //4.5
	regBuf.Push(0xC837, 0x00);// DATA_DIREC****************
							  //4.6
	regBuf.Push(0xC838, 0x01);// SEG1_BUS_WIDTH
							  //4.7
	regBuf.Push(0xC839, 0x00);// ADDR_BYTE_NUM
							  //4.8
	regBuf.Push(0xC83A, 0x01);// SEG2_BUS_WIDTH
							  //4.9
	regBuf.Push(0xC83B, 0x00);// CMD_DAT_TX_RX****************
							  //4.10
	regBuf.Push(0xC83C, 0x01);//SEG3_BUS_WIDTH
							  //4.11
	regBuf.Push(0xC02A, CHSEL);//使能该通道
							  //4.12
	regBuf.Push(0xC050, 0x01);//ALLCH_SAME_CFG
							  //5.1
	regBuf.Push(0xC040, 0x01);

	WriteFPGA(h, regBuf.GetData(), regBuf.GetLength());
	//WriteDMANotSetLength(h, pBuf, ulLen);
	PbInit(pf, ChSel);
	ulPbValue = 0;
	do
	{
		ulPbValue++;
		PbUpdate(pf, ulPbValue, ChSel);
		Sleep(1800);
		ReadCPLD(h, 0xC040, byStatus);
		if (!ReadRDSR(h, ChSel))
			break;
	}while (ulPbValue != 100);
	ulPbValue = 100;
	PbUpdate(pf, ulPbValue, ChSel);
}

void WINAPI SPIProgram(HANDLE h, PDEVICE p, PBYTE pBuf, PVOID pf[], BYTE &ChSel)
{
	BYTE byStatus;//状态
	ULONG ulRemain,//剩余数据
		ulStartAddr, //写起始地址
		ulLen;//写的长度
	ULONG ulPbValue;//进度条
	INT64 llChipSize;//芯片大小
	CRegBuffer regBuf;

	if (ChSel == 0)
		return;

	//static ULONG ulStartAddr = 0;
	if (B_4BYTE)
		Enter4ByteMode(h,ChSel);
	ulStartAddr = StartAddr;
	SetWriteParam(h, ulStartAddr, B_4BYTE, ChSel);

	llChipSize = p->llMemSize[0];
	ulLen = WR_BUFFER_WRITE * 256;
	ulRemain = llChipSize;
	PbInit(pf, ChSel);

	while (ulRemain > 0)
	{
		regBuf.Init();
		if (B_4BYTE)
		{
			regBuf.Push(0xC82F, (ulStartAddr >> 24) & 0xFF);
			regBuf.Push(0xC82E, (ulStartAddr >> 16) & 0xFF);// *
			regBuf.Push(0xC82D, (ulStartAddr >> 8) & 0xFF);//4Byte模式向下移动，此处为ulStartAddr>>8
			regBuf.Push(0xC82C, (ulStartAddr) & 0xFF);
		}
		else
		{
			regBuf.Push(0xC82F, (ulStartAddr >> 16) & 0xFF);
			regBuf.Push(0xC82E, (ulStartAddr >> 8) & 0xFF);// *
			regBuf.Push(0xC82D, (ulStartAddr) & 0xFF);//4Byte模式向下移动，此处为ulStartAddr>>8
			regBuf.Push(0xC82C, 0x00);
		}

		WriteFPGA(h, regBuf.GetData(), regBuf.GetLength());
		do
		{
			ReadCPLD(h, 0xC040, byStatus);
		} while (byStatus != 0);

		WriteDMANotSetLength(h, pBuf, ulLen);
		do
		{
			ReadCPLD(h, 0xC040, byStatus);
		} while (byStatus != 0);

		ulRemain -= ulLen;
		ulStartAddr += ulLen;
		pBuf += ulLen;
		ulPbValue = (llChipSize - ulRemain) * 100 / llChipSize;
		PbUpdate(pf, ulPbValue, ChSel);
		//Sleep(100);
	}
}

void WINAPI SPIRead(HANDLE h, PDEVICE p, PBYTE pBuf, LPVOID pf[], BYTE &ChSel)
{
	int i, j;
	BYTE byStatus;//状态
	ULONG ulRemain, ulStartAddr, ulLen;
	BYTE byTmpStat;
	ULONG ulPbValue;
	INT64 llChipSize;
	CRegBuffer regBuf;
	if (ChSel == 0)
		return;
	if (B_4BYTE)
		Enter4ByteMode(h, ChSel);
	ulStartAddr = StartAddr;
	SetReadParam(h, ulStartAddr, B_4BYTE, ChSel);

	llChipSize = p->llMemSize[0];
	ulRemain = llChipSize;
	ulLen = WR_BUFFER_READ * 256;
	PbInit(pf, ChSel);
	
	while (ulRemain > 0)
	{
		regBuf.Init();
		if (B_4BYTE)
		{
			regBuf.Push(0xC82F, (ulStartAddr >> 24) & 0xFF);
			regBuf.Push(0xC82E, (ulStartAddr >> 16) & 0xFF);// *
			regBuf.Push(0xC82D, (ulStartAddr >> 8) & 0xFF);//4Byte模式向下移动，此处为ulStartAddr>>8
			regBuf.Push(0xC82C, (ulStartAddr) & 0xFF);
		}
		else
		{
			regBuf.Push(0xC82F, (ulStartAddr >> 16) & 0xFF);
			regBuf.Push(0xC82E, (ulStartAddr >> 8) & 0xFF);// *
			regBuf.Push(0xC82D, (ulStartAddr) & 0xFF);//4Byte模式向下移动，此处为ulStartAddr>>8
			regBuf.Push(0xC82C, 0x00);
		}
		WriteFPGA(h, regBuf.GetData(), regBuf.GetLength());
		//BYTE byStatus;//状态
		do
		{
			ReadCPLD(h, 0xC040, byStatus);
		} while (byStatus != 0);
		Sleep(1);
		ReadDMA(h, pBuf, ulLen);
		do
		{
			ReadCPLD(h, 0xC040, byStatus);
		} while (byStatus != 0);
		ulRemain -= ulLen;
		pBuf += ulLen;
		ulStartAddr += ulLen;
		ulPbValue = (llChipSize - ulRemain) * 100 / llChipSize;
		PbUpdate(pf, ulPbValue, ChSel);
	}
}

void WINAPI SPIVerify(HANDLE h, PDEVICE p, PBYTE pBuf, PVOID pf[], BYTE &ChSel)
{
	BYTE byStatus, byOldStatus = 0;
	int i;
	ULONG ulRemain, ulStartAddr, ulLen;
	ULONG ulPbValue;
	INT64 llChipSize;
	CRegBuffer regBuf;

	if (ChSel == 0)
		return;
	if (B_4BYTE)
		Enter4ByteMode(h, ChSel);
	ulStartAddr = StartAddr;
	SetVerifyParam(h, ulStartAddr, B_4BYTE, ChSel);

	llChipSize = p->llMemSize[0];
	ulRemain = llChipSize;
	ulLen = WR_BUFFER_READ * 256;
	PbInit(pf, ChSel);

	while (ulRemain > 0)
	{
		regBuf.Init();
		if (B_4BYTE)
		{
			regBuf.Push(0xC82F, (ulStartAddr >> 24) & 0xFF);
			regBuf.Push(0xC82E, (ulStartAddr >> 16) & 0xFF);// *
			regBuf.Push(0xC82D, (ulStartAddr >> 8) & 0xFF);//4Byte模式向下移动，此处为ulStartAddr>>8
			regBuf.Push(0xC82C, (ulStartAddr) & 0xFF);
		}
		else
		{
			regBuf.Push(0xC82F, (ulStartAddr >> 16) & 0xFF);
			regBuf.Push(0xC82E, (ulStartAddr >> 8) & 0xFF);// *
			regBuf.Push(0xC82D, (ulStartAddr) & 0xFF);//4Byte模式向下移动，此处为ulStartAddr>>8
			regBuf.Push(0xC82C, 0x00);
		}
		WriteFPGA(h, regBuf.GetData(), regBuf.GetLength());
		//BYTE byStatus;//状态
		do
		{
			ReadCPLD(h, 0xC040, byStatus);
		} while (byStatus != 0);

		WriteDMANotSetLength(h, pBuf, ulLen);
		do
		{
			ReadCPLD(h, 0xC040, byStatus);
		} while (byStatus != 0);
		//ReadCPLD(h, 0xC035, byStatus);

		//if ((byStatus != 0) && (byStatus != byOldStatus))
		//{
		//	ChSel = ChSel&(~byStatus);
		//	byOldStatus = byStatus;
		//}
		//if (byStatus == 0xF || ChSel == 0)
		//	break;

		ulRemain -= ulLen;
		pBuf += ulLen;
		ulStartAddr += ulLen;
		ulPbValue = (llChipSize - ulRemain) * 100 / llChipSize;
		PbUpdate(pf, ulPbValue, ChSel);
	}
	for (int i = 0; i < 4; i++)
	{
		if (ChSel >> i & 0x01)
		{
			WriteCPLD(h, 0xC02A, 1 << i);
			do
			{
				ReadCPLD(h, 0xC040, byStatus);
			} while (byStatus != 0);
			ReadCPLD(h, 0xC0B7, byStatus);
			if ((byStatus & 0x01))
				ChSel = ChSel&(~(1 << i));
		}
	}
}

void WINAPI SPIBlank(HANDLE h, PDEVICE p, PBYTE pBuf, PVOID pf[], BYTE &ChSel)
{
	//const int iLen = 4096;

	//BYTE byOldStatus=0, byStatus;
	//BYTE byBuf[iLen];
	//ULONG ulRemain, ulStartAddr;
	//INT64 llChipSize;
	//ULONG ulPbVlaue;
	//CRegBuffer regBuf;

	//llChipSize = p->llMemSize[0];
	//if (ChSel == 0)
	//	return;
	//WriteCPLD(h, 0xC030, 5);//Clock

	//memset(byBuf, 0xFF, sizeof byBuf);

	//ulRemain = llChipSize;
	//PbInit(pf, ChSel);
	//ulStartAddr = 0;

	//while (ulRemain > 0)
	//{
	//	regBuf.Init();
	//	regBuf.Push(F_CMD, 0x7C);
	//	regBuf.Push(F_SEL, ChSel);

	//	regBuf.Push(0xC025, (ulStartAddr >> 16) & 0xFF);
	//	regBuf.Push(0xC024, (ulStartAddr >> 8) & 0xFF);
	//	regBuf.Push(0xC023, (ulStartAddr & 0xFF));

	//	regBuf.Push(0xC029, (iLen >> 24) & 0xFF);
	//	regBuf.Push(0xC028, (iLen >> 16) & 0xFF);
	//	regBuf.Push(0xC027, (iLen >> 8) & 0xFF);
	//	regBuf.Push(0xC026, (iLen) & 0xFF);

	//	WriteFPGA(h, regBuf.GetData(), regBuf.GetLength());
	//	WriteDMANotSetLength(h, byBuf, iLen);
	//	do
	//	{
	//		ReadCPLD(h, 0xC040, byStatus);
	//	} while (byStatus != 0);
	//	ReadCPLD(h, 0xC035, byStatus);

	//	if ((byStatus != 0) && (byStatus != byOldStatus))
	//	{
	//		ChSel = ChSel&(~byStatus);
	//		byOldStatus = byStatus;
	//	}
	//	if ((byStatus == 0xF) || (ChSel == 0))
	//		break;

	//	ulRemain -= iLen;
	//	ulStartAddr += iLen;
	//	ulPbVlaue = (llChipSize - ulRemain) * 100 / llChipSize;
	//	PbUpdate(pf, ulPbVlaue, ChSel);
	//}
	//WriteCPLD(h, 0xC030, 2);
}
void WINAPI SPICheckID(HANDLE h, PDEVICE p, PBYTE pBuf, PVOID pf[], BYTE &ChSel)
{
	//BYTE byStatus;
	//int i;
	//BOOL bM[ALLOWED_SLOTS];
	//CRegBuffer regBuf;
	//WriteCPLD(h, 0xC030, 5);

	//regBuf.Init();
	//regBuf.Push(F_CMD, 0x9F);
	//regBuf.Push(F_SEL, ChSel);
	//regBuf.Push(0xC029, 0);
	//regBuf.Push(0xC028, 0);
	//regBuf.Push(0xC027, 0);
	//regBuf.Push(0xC026, 3);
	//regBuf.Push(F_EXEC, 1);
	//WriteFPGA(h, regBuf.GetData(), regBuf.GetLength());

	//do
	//{
	//	ReadCPLD(h, F_EXEC, byStatus);
	//} while (byStatus != 0);

	//for (i = 0; i < ALLOWED_SLOTS; i++)
	//{
	//	bM[i] = TRUE;
	//	if ((ChSel&(1 << i)) != 0)
	//	{
	//		ReadCPLD(h, 0xC060 + i * 8, byStatus);
	//		bM[i] = (byStatus == p->wManuID);
	//		ReadCPLD(h, 0xC061 + i * 8, byStatus);
	//		bM[i] = (bM[i] && (byStatus == p->wDeviceID));
	//		ReadCPLD(h, 0xC062 + i * 8, byStatus);

	//		if (!bM[i])
	//			ChSel = ChSel&(~(1 << i));
	//	}
	//}
	//WriteCPLD(h, 0xC030, 2);
}


ULONG WINAPI GetDllInfo(void)
{
	return EN_PROG + EN_READ + EN_VERIFY + EN_ERASE;// +EN_IDCHECK + EN_BLANK;
}

BOOL WINAPI DllMain(HANDLE hinstDLL, DWORD dwReason, LPVOID lpvReserved)
{
	switch (dwReason)
	{
	case DLL_PROCESS_ATTACH:
		// Initialize once for each new process.
		// Return FALSE to fail DLL load.
		LoadPbIntDll();
		LoadInterDll();
		break;

	case DLL_THREAD_ATTACH:
		// Do thread-specific initialization.
		break;

	case DLL_THREAD_DETACH:
		// Do thread-specific cleanup.
		break;

	case DLL_PROCESS_DETACH:
		// Perform any necessary cleanup.
		UnloadInterDll();
		UnloadPbIntDll();
		break;
	}
	return TRUE;  // Successful DLL_PROCESS_ATTACH.
}
