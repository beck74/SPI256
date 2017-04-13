#ifndef SPI_PROGRAMMER_SETTING_H_
#define SPI_PROGRAMMER_SETTING_H_

//1.读取PLL锁定状态，目标值0x01
#define PLL_LOCK	0XC012	

//2.系统配置
//2.1配置SPI通道频率（SPI clock频率为 80M/(0xC030值+1)）
//例子 : 配置0x01时为40MHz， 配置为0x02时为27MHz
#define CLK_DIV	0xC030
#define FREQUENCY_40MHZ	0X01
#define FREQUENCY_27MHZ	0X02

//2.2 配置Slave FIFO中的数据发送顺序（BYTE_ORDER）：
//0x0 : 高字节先发	0x1 : 低字节先发
/*如果Slave FIFO中一个16比特数据为0xABCD，其中0xAB为高字节，即在16比特（用bit 15到0标注）中为 bit[15:8]的值，0xCD为低字节，即为 bit[7:0]的值（也就是说0xCD是字节地址0的值，0xAB为字节地址1的值）
	低字节先发 : 0xCD先发送，然后发送0xAB	
	高字节先发 : 0xAB先发送，然后发送0xCD*/
#define BYTE_ORDER 0xC031 
#define HIGH_FIRST	0x00
#define LOW_FIRST	0x01//默认

//3.通道公用参数配置：
//3.1 WREN_FORMAT ，默认值0x0602，表示WREN的命令为0x06，发送数据位宽为1bit。
	//0xC801 : WREN的命令值
	//0xC800 : [3:1]为发送数据位宽0000
#define WREN_FORMAT_CMD				0xC801
#define WREN_FORMAT_SEND_BITWIDE	0xC800
#define WREN						0x06//查芯片手册
#define WREN_FORMAT_1BIT			1<<1//当前所有芯片全部设置1bit
#define WREN_FORMAT_2BIT			1<<2
#define WREN_FORMAT_4BIT			1<<3

//3.2 RDSR_FORMAT ，默认值0x0581，表示RDSR的命令为0x05，发送数据位宽、接收响应的数据位宽都为1比特，响应字节数为4。
	//0xC803 :	RDSR的命令值									?为什么时89
	//0xC802 :	[7:5]，接收响应字节数，100 00 001
	//			[4:3], 预留为配置是接收响应，还是发送数据给SPI。现在保留不用。
	//			[2:0], 为数据位宽
#define RDSR_FORMAT_CMD		0xC803
#define RDSR	0x05//查手册
#define RDSR_FORMAT			0xC802

//3.3 WREN_LOOP_LIMIT : 默认值为0x64，即最大重复WREN - RDSR 100次
//在每次写数据的执行过程，都要先检查WREN是否置位，如果没有，则循环执行WREN，直到RDSR回读正确
	//0xC804 : 新的配置值
#define WREN_LOOP_LIMIT	0xC804

//3.4 RDSR_CHK_MASK ，检查RDSR的响应时忽略哪些比特位。默认值0xFFFFFFFC，即只检查最新收到的响应字节的最低两位
	//0xC808 ： 最高字节
	//0xC807 ： 次高字节
	//0xC806 ： 次低字节
	//0xC805 ： 最低字节
#define RDSR_CHK_MASK_HIGHEST	0xC808
#define RDSR_CHK_MASK_HIGHER	0xC807
#define RDSR_CHK_MASK_LOWER		0xC806
#define RDSR_CHK_MASK_LOWEST	0xC805

//3.5 RDSR_CHK_TARGET，检查RDSR的响应时的目标响应值。默认值为0x00000002
//RDSR_CHK_MASK为1的比特不比较。所以默认情况下即只检查最新收到的响应字节的最低两位是否为0x2，即WEL为1，WIP为0
	//0xC80C ： 最高字节
	//0xC80B ： 次高字节
	//0xC80A ： 次低字节   -- 这个字节对应最新收到的字节之前收到的字节
	//0xC809 ： 最低字节   -- 这个字节对应最新收到的字节
#define RDSR_CHK_TARGET_HIGHEST	0xC80C//具体配置值需要查手册
#define RDSR_CHK_TARGET_HIGHER	0xC80B
#define RDSR_CHK_TARGET_LOWER	0xC80A
#define RDSR_CHK_TARGET_LOWEST	0xC809

//3.6 DATA_BYTE_NUM ，默认值为0x00_00_00_00_03, 设置DATA字段的字节数量
	//0xC811 ： 最高字节
	//0xC810 ： 次高字节
	//0xC80F ：
	//0xC80E ： 次低字节
	//0xC80D ： 最低字节
#define DATA_BYTE_NUM_LOWEST	0xC80D
#define DATA_BYTE_NUM_LOWER		0xC80E
#define DATA_BYTE_NUM_MIDDLE	0xC80F
#define DATA_BYTE_NUM_HIGHER	0xC810
#define DATA_BYTE_NUM_HIGHEST	0xC811

//3.7 CMD_LOOP_NUM, 默认值0x00_00_00_00_01，设置命令重复执行的次数
	//0xC816 ： 最高字节
	//0xC815 ： 次高字节
	//0xC814 ：
	//0xC813 ： 次低字节
	//0xC812 ： 最低字节
#define CMD_LOOP_NUM_LOWEST		0xC812
#define CMD_LOOP_NUM_LOWER		0xC813
#define CMD_LOOP_NUM_MIDDLE		0xC814
#define CMD_LOOP_NUM_HIGHER		0xC815
#define CMD_LOOP_NUM_HIGHEST	0xC816

//3.8 DAT_RDY_THRESHD，默认值为0x0002，配置数据准备好的阈值
	//0xC818 ： 高字节
	//0xC817 ： 低字节
#define DAT_RDY_THRESHD_HIGH	0xC818
#define DAT_RDY_THRESHD_LOW		0xC817

//3.9 USER_CMD_DEF，默认值为0x00，配置预定义的用户命令
	//0xC819 ： bit[3] : copy_card   ，卡拷贝命令
	//			bit[2] : verify_card ，卡校验命令
	//			bit[1] : verify_cpu  ，CPU校验命令
	//			bit[0] : cmd_program ，编程命令
#define USER_CMD_DEF		0xC819
#define CMD_PROGRAM		1<<0
#define VERIFY_CPY		1<<1
#define VERIFY_CARD		1<<2
#define COPY_CARD		1<<3

//3.10 CSN_HIGH_PULSE，默认值为0x06，设置CSN信号高电平脉宽
	//0xC81A ：
#define CSN_HIGH_PULSE		0xC81A


//4, 配置通道组0的参数（通道0的配置）：
//4.0 ALLCH_SAME_CFG 设置是否全部通道采用相同的配置
	//1：全部通道采用通道0的配置
	//0：通道1及其以后的配置与通道0可以不同
#define ALLCH_SAME_CFG		0xC050

//4.1 CMD_ADDR  ，一共16字节。高字节为先发送的字节。如果实际需要发送的字节数（ADDR_BYTE_NUM定义实际发送多少字节）小于16，需要发送的字节按顺序放入高字节。默认值为全0.	
#define CMD_ADDR_CH0_F		0xC82F	//最高字节。 如果地址只有一个字节，应该使用这个字节配置
#define CMD_ADDR_CH0_E		0xC82E
#define CMD_ADDR_CH0_D		0xC82D
#define CMD_ADDR_CH0_C		0xC82C
#define CMD_ADDR_CH0_B		0xC82B
#define CMD_ADDR_CH0_A		0xC82A
#define CMD_ADDR_CH0_9		0xC829
#define CMD_ADDR_CH0_8		0xC828
#define CMD_ADDR_CH0_7		0xC827
#define CMD_ADDR_CH0_6		0xC826
#define CMD_ADDR_CH0_5		0xC825
#define CMD_ADDR_CH0_4		0xC824
#define CMD_ADDR_CH0_3		0xC823
#define CMD_ADDR_CH0_2		0xC822
#define CMD_ADDR_CH0_1		0xC821
#define CMD_ADDR_CH0_0		0xC820

//4.2 CMD_ADDR_INC ，默认值为0.配置命令重复执行时的地址增量
	//0x834 : 最高字节，对应 0x82F的地址
	//0x833 :
	//0x832 :
	//0x831 :
	//0x830 :
	//命令再次执行时，使用的地址是：
	//高5字节 ： 增加CMD_ADDR_INC
	//其他字节： 保持不变
#define CMD_ADDR_INC_CH0_4		0xC834
#define CMD_ADDR_INC_CH0_3		0xC833
#define CMD_ADDR_INC_CH0_2		0xC832
#define CMD_ADDR_INC_CH0_1		0xC831
#define CMD_ADDR_INC_CH0_0		0xC830

//4.3 CMD_NEED_WREN
	//0x835 : bit[0] :	1:需要自动执行WREN  0:不需要执行WREN
#define CMD_NEED_WREN_CH0		0xC835//看手册看是否需要执行WREN

//4.4 CMD_INDEX，默认值是0x9F，默认情况下对应 RDID命令。 配置命令的CMD字节值。
	//0x836 :
#define CMD_INDEX_CH0		0xC836
#define PAGE_PROGRAM	0x02
#define Sector_Erase	0xD8
#define Chip_Erase	0x60//or 0xC7
//4.5 DATA_DIREC，配置内部数据流，默认值为0
	//0x837 :	[7:5] ：通道处理数据来源(DSDATA_SRC)
	//			[4:3] ：通道处理数据去向(DSDATA_TGT)
	//			[2:0] ：从SPI读到的数据去向(USDATA_TGT)
	//DSDATA_SRC ：	0b001 ：来自Slave FIFO
	//				0b010 ：来自通道0。这在卡拷贝和卡验证时使用
	//				0b100 ：来自Local Bus。
	//				0b000 ：没有DATA字段
	//DSDATA_TGT ：	0b01 ：输出给SPI
	//				0b10 ：输出给验证模块，这在校验时使用
	//				0b00 ：没有DATA字段
	//USDATA_TGT ：	0b001 ：写入Slave FIFO
	//				0b100 ：写入Local Bus。

	//注： 0x837在几种常见场景下的设置如下：
	//从SPI收数据包，用Ｓｌａｖｅ　ＦＩＦＯ收：　０ｘ０１
	//对SPI编程，用Ｓｌａｖｅ　ＦＩＦＯ发：　０ｘ２８
	//用Ｓｌａｖｅ　ＦＩＦＯ下数据进行卡校验（ＣＰＵ校验）　：　０ｘ３０
	//卡１向其他卡拷贝数据（卡拷贝）　：　０ｘ40
	//其他卡与卡１数据校验（卡校验）　：　０ｘ12
	//对应的： 0x867在这几种常见场景下的设置如下：
	//从SPI收数据包，用Ｓｌａｖｅ　ＦＩＦＯ收：　０ｘ０１
	//对SPI编程，用Ｓｌａｖｅ　ＦＩＦＯ发：　０ｘ２８
	//用Ｓｌａｖｅ　ＦＩＦＯ下数据进行卡校验（ＣＰＵ校验）　：　０ｘ３０
	//卡１向其他卡拷贝数据（卡拷贝）　：　０ｘ48
	//其他卡与卡１数据校验（卡校验）　：　０ｘ52
	//其他没有数据字段的命令，设置这两个寄存器为0x0。
#define DATA_DIREC_CH0		0xC837

//4.6 SEG1_BUS_WIDTH ，默认值为0x01，配置CMD字节发送时的SPI接口数据位宽
	//0x838 : [2:0],	1：1比特模式
	//					2：2比特模式
	//					4：4比特模式
	//					其他值：非法值
#define SEG1_BUS_WIDTH_CH0		0xC838

//4.7 ADDR_BYTE_NUM，默认值为0，配置命令的ADDR字段的字节数
	//0x839 : [4:0] ，	0 ：命令不需要ADDR字段
	//					1~16 ：命令ADDR字段的字节数
	//					17~31 ：无效设置
#define ADDR_BYTE_NUM_CH0		0xC839

//4.8 SEG2_BUS_WIDTH，默认值为0x01，配置ADDR字节发送时的SPI接口数据位宽
	//0x83A : [2:0],	1：1比特模式
	//					2：2比特模式
	//					4：4比特模式
	//					其他值：非法值
#define SEG2_BUS_WIDTH_CH0		0xC83A

//4.9 CMD_DAT_TX_RX，配置命令的DATA字段是从SPI读取数据，还是向SPI写数据。默认值为0x01，表示读取数据（这是与RDID命令相匹配设置的）
	//0x83B : [1:0],	1：从SPI读取数据；
	//					2：向SPI写数据
	//					3：测试模式
	//					0：没有数据处理
#define CMD_DAT_TX_RX_CH0		0xC83B

//4.10 SEG3_BUS_WIDTH，默认值为0x01，配置DATA字段处理时SPI接口数据位宽
	//0x83C : [2:0],	1：1比特模式
	//					2：2比特模式
	//					4：4比特模式
	//					其他值：非法值
#define SEG3_BUS_WIDTH_CH0		0xC83C

//4.11 CH_EN ，通道组0的各个通道使能设置，默认值为0x01，表示通道0使能
	//0x83D : [0],	1：通道0使能
	//				0：通道0不使能
#define CH_EN_CH0		0xC83D

//5.配置通道组1的参数（通道1~（n - 1）的配置）： （相应寄存器的偏移地址比通道组0的大0x30）
//5.1 CMD_ADDR  ，一共16字节。高字节为先发送的字节。如果实际需要发送的字节数（ADDR_BYTE_NUM定义实际发送多少字节）小于16，需要发送的字节按顺序放入高字节。
	//默认值为全0.
#define CMD_ADDR_CH1_F		0xC85F//最高字节。 如果地址只有一个字节，应该使用这个字节配置
#define CMD_ADDR_CH1_E		0xC85E
#define CMD_ADDR_CH1_D		0xC85D
#define CMD_ADDR_CH1_C		0xC85C
#define CMD_ADDR_CH1_B		0xC85B
#define CMD_ADDR_CH1_A		0xC85A
#define CMD_ADDR_CH1_9		0xC859
#define CMD_ADDR_CH1_8		0xC858
#define CMD_ADDR_CH1_7		0xC857
#define CMD_ADDR_CH1_6		0xC856
#define CMD_ADDR_CH1_5		0xC855
#define CMD_ADDR_CH1_4		0xC854
#define CMD_ADDR_CH1_3		0xC853
#define CMD_ADDR_CH1_2		0xC852
#define CMD_ADDR_CH1_1		0xC851
#define CMD_ADDR_CH1_0		0xC850

//5.2 CMD_ADDR_INC ，默认值为0.配置命令重复执行时的地址增量
	//0x864 : 最高字节，对应 0x82F的地址
	//0x863 :
	//0x862 :
	//0x861 :
	//0x860 :
	//命令再次执行时，使用的地址是：
	//高5字节  ： 增加CMD_ADDR_INC
	//其他字节： 保持不变
#define CMD_ADDR_INC_CH1_4		0xC864
#define CMD_ADDR_INC_CH1_3		0xC863
#define CMD_ADDR_INC_CH1_2		0xC862
#define CMD_ADDR_INC_CH1_1		0xC861
#define CMD_ADDR_INC_CH1_0		0xC860

//5.3 CMD_NEED_WREN
	//0x865 : bit[0] :	1, 需要自动执行WREN
	//					0, 不需要执行WREN
#define CMD_NEED_WREN_CH1		0xC865

//5.4 CMD_INDEX，默认值是0x9F，默认情况下对应 RDID命令。 配置命令的CMD字节值。
	//0x866 :
#define CMD_INDEX_CH1		0xC866

//5.5 DATA_DIREC，配置内部数据流，默认值为0
	//0x867 : [7:5] ：通道处理数据来源(DSDATA_SRC)
	//		[4:3] ：通道处理数据去向(DSDATA_TGT)
	//		[2:0] ：从SPI读到的数据去向(USDATA_TGT)
	//DSDATA_SRC ：	0b001 ：来自Slave FIFO
	//				0b010 ：来自通道0。这在卡拷贝和卡验证时使用
	//				0b100 ：来自Local Bus。
	//				0b000 ：没有DATA字段
	//DSDATA_TGT ：	0b01 ：输出给SPI
	//				0b10 ：输出给验证模块，这在校验时使用
	//				0b00 ：没有DATA字段
	//USDATA_TGT ：	0b001 ：写入Slave FIFO
	//				0b010 ：写入验证模块，在校验时使用
	//				0b100 ：写入Local Bus。
#define DATA_DIREC_CH1		0xC867

//5.6 SEG1_BUS_WIDTH ，默认值为0x01，配置CMD字节发送时的SPI接口数据位宽
	//0x868 : [2:0],	1：1比特模式
	//					2：2比特模式
	//					4：4比特模式
	//					其他值：非法值
#define SEG1_BUS_WIDTH_CH1		0xC868

//5.7 ADDR_BYTE_NUM，默认值为0，配置命令的ADDR字段的字节数
	//0x869 : [4:0] ，	0 ：命令不需要ADDR字段
	//					1~16 ：命令ADDR字段的字节数
	//					17~31 ：无效设置
#define ADDR_BYTE_NUM_CH1		0xC869

//5.8 SEG2_BUS_WIDTH，默认值为0x01，配置ADDR字节发送时的SPI接口数据位宽
	//0x86A : [2:0],	1：1比特模式
	//					2：2比特模式
	//					4：4比特模式
	//					其他值：非法值
#define SEG2_BUS_WIDTH_CH1		0xC86A

//5.9 CMD_DAT_TX_RX，配置命令的DATA字段是从SPI读取数据，还是向SPI写数据。默认值为0x01，表示读取数据（这是与RDID命令相匹配设置的）
	//0x86B : [1:0],	1：从SPI读取数据；
	//					2：向SPI写数据
	//					3：测试模式
	//					0：没有数据处理
#define CMD_DAT_TX_RX_CH1		0xC86B

//5.10 SEG3_BUS_WIDTH，默认值为0x01，配置DATA字段处理时SPI接口数据位宽
	//0x86C : [2:0],		1：1比特模式
	//					2：2比特模式
	//					4：4比特模式
	//					其他值：非法值
#define SEG3_BUS_WIDTH_CH1		0xC86C

//5.11 CH_EN ，通道组1的各个通道使能设置，默认值为0x01，表示通道1使能
	//0x86D : [0], 1：通道1使能，    0：通道1不使能
	//		[1], 1：通道2使能，    0：通道2不使能
	//		[2], 1：通道3使能，    0：通道3不使能
	//		[3], 1：通道4使能，    0：通道4不使能
	//		[4], 1：通道5使能，    0：通道5不使能
	//		[5], 1：通道6使能，    0：通道6不使能
	//		[6], 1：通道7使能，    0：通道7不使能
	//		[7], 1：通道8使能，    0：通道8不使能
	//0x86E : 配置通道9 ~16使能
	//0x86F : 配置通道17~24使能
	//0x870 : 配置通道25~32使能
	//0x871 : 配置通道33~40使能
	//0x872 : 配置通道41~48使能
	//0x873 : 配置通道49~56使能
	//0x874 : 配置通道57~64使能
#define CH_EN_CH1		0xC86D

#endif // !SPI_PROGRAMMER_SETTING_H_
