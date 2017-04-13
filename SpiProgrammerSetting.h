#ifndef SPI_PROGRAMMER_SETTING_H_
#define SPI_PROGRAMMER_SETTING_H_

//1.��ȡPLL����״̬��Ŀ��ֵ0x01
#define PLL_LOCK	0XC012	

//2.ϵͳ����
//2.1����SPIͨ��Ƶ�ʣ�SPI clockƵ��Ϊ 80M/(0xC030ֵ+1)��
//���� : ����0x01ʱΪ40MHz�� ����Ϊ0x02ʱΪ27MHz
#define CLK_DIV	0xC030
#define FREQUENCY_40MHZ	0X01
#define FREQUENCY_27MHZ	0X02

//2.2 ����Slave FIFO�е����ݷ���˳��BYTE_ORDER����
//0x0 : ���ֽ��ȷ�	0x1 : ���ֽ��ȷ�
/*���Slave FIFO��һ��16��������Ϊ0xABCD������0xABΪ���ֽڣ�����16���أ���bit 15��0��ע����Ϊ bit[15:8]��ֵ��0xCDΪ���ֽڣ���Ϊ bit[7:0]��ֵ��Ҳ����˵0xCD���ֽڵ�ַ0��ֵ��0xABΪ�ֽڵ�ַ1��ֵ��
	���ֽ��ȷ� : 0xCD�ȷ��ͣ�Ȼ����0xAB	
	���ֽ��ȷ� : 0xAB�ȷ��ͣ�Ȼ����0xCD*/
#define BYTE_ORDER 0xC031 
#define HIGH_FIRST	0x00
#define LOW_FIRST	0x01//Ĭ��

//3.ͨ�����ò������ã�
//3.1 WREN_FORMAT ��Ĭ��ֵ0x0602����ʾWREN������Ϊ0x06����������λ��Ϊ1bit��
	//0xC801 : WREN������ֵ
	//0xC800 : [3:1]Ϊ��������λ��0000
#define WREN_FORMAT_CMD				0xC801
#define WREN_FORMAT_SEND_BITWIDE	0xC800
#define WREN						0x06//��оƬ�ֲ�
#define WREN_FORMAT_1BIT			1<<1//��ǰ����оƬȫ������1bit
#define WREN_FORMAT_2BIT			1<<2
#define WREN_FORMAT_4BIT			1<<3

//3.2 RDSR_FORMAT ��Ĭ��ֵ0x0581����ʾRDSR������Ϊ0x05����������λ��������Ӧ������λ��Ϊ1���أ���Ӧ�ֽ���Ϊ4��
	//0xC803 :	RDSR������ֵ									?Ϊʲôʱ89
	//0xC802 :	[7:5]��������Ӧ�ֽ�����100 00 001
	//			[4:3], Ԥ��Ϊ�����ǽ�����Ӧ�����Ƿ������ݸ�SPI�����ڱ������á�
	//			[2:0], Ϊ����λ��
#define RDSR_FORMAT_CMD		0xC803
#define RDSR	0x05//���ֲ�
#define RDSR_FORMAT			0xC802

//3.3 WREN_LOOP_LIMIT : Ĭ��ֵΪ0x64��������ظ�WREN - RDSR 100��
//��ÿ��д���ݵ�ִ�й��̣���Ҫ�ȼ��WREN�Ƿ���λ�����û�У���ѭ��ִ��WREN��ֱ��RDSR�ض���ȷ
	//0xC804 : �µ�����ֵ
#define WREN_LOOP_LIMIT	0xC804

//3.4 RDSR_CHK_MASK �����RDSR����Ӧʱ������Щ����λ��Ĭ��ֵ0xFFFFFFFC����ֻ��������յ�����Ӧ�ֽڵ������λ
	//0xC808 �� ����ֽ�
	//0xC807 �� �θ��ֽ�
	//0xC806 �� �ε��ֽ�
	//0xC805 �� ����ֽ�
#define RDSR_CHK_MASK_HIGHEST	0xC808
#define RDSR_CHK_MASK_HIGHER	0xC807
#define RDSR_CHK_MASK_LOWER		0xC806
#define RDSR_CHK_MASK_LOWEST	0xC805

//3.5 RDSR_CHK_TARGET�����RDSR����Ӧʱ��Ŀ����Ӧֵ��Ĭ��ֵΪ0x00000002
//RDSR_CHK_MASKΪ1�ı��ز��Ƚϡ�����Ĭ������¼�ֻ��������յ�����Ӧ�ֽڵ������λ�Ƿ�Ϊ0x2����WELΪ1��WIPΪ0
	//0xC80C �� ����ֽ�
	//0xC80B �� �θ��ֽ�
	//0xC80A �� �ε��ֽ�   -- ����ֽڶ�Ӧ�����յ����ֽ�֮ǰ�յ����ֽ�
	//0xC809 �� ����ֽ�   -- ����ֽڶ�Ӧ�����յ����ֽ�
#define RDSR_CHK_TARGET_HIGHEST	0xC80C//��������ֵ��Ҫ���ֲ�
#define RDSR_CHK_TARGET_HIGHER	0xC80B
#define RDSR_CHK_TARGET_LOWER	0xC80A
#define RDSR_CHK_TARGET_LOWEST	0xC809

//3.6 DATA_BYTE_NUM ��Ĭ��ֵΪ0x00_00_00_00_03, ����DATA�ֶε��ֽ�����
	//0xC811 �� ����ֽ�
	//0xC810 �� �θ��ֽ�
	//0xC80F ��
	//0xC80E �� �ε��ֽ�
	//0xC80D �� ����ֽ�
#define DATA_BYTE_NUM_LOWEST	0xC80D
#define DATA_BYTE_NUM_LOWER		0xC80E
#define DATA_BYTE_NUM_MIDDLE	0xC80F
#define DATA_BYTE_NUM_HIGHER	0xC810
#define DATA_BYTE_NUM_HIGHEST	0xC811

//3.7 CMD_LOOP_NUM, Ĭ��ֵ0x00_00_00_00_01�����������ظ�ִ�еĴ���
	//0xC816 �� ����ֽ�
	//0xC815 �� �θ��ֽ�
	//0xC814 ��
	//0xC813 �� �ε��ֽ�
	//0xC812 �� ����ֽ�
#define CMD_LOOP_NUM_LOWEST		0xC812
#define CMD_LOOP_NUM_LOWER		0xC813
#define CMD_LOOP_NUM_MIDDLE		0xC814
#define CMD_LOOP_NUM_HIGHER		0xC815
#define CMD_LOOP_NUM_HIGHEST	0xC816

//3.8 DAT_RDY_THRESHD��Ĭ��ֵΪ0x0002����������׼���õ���ֵ
	//0xC818 �� ���ֽ�
	//0xC817 �� ���ֽ�
#define DAT_RDY_THRESHD_HIGH	0xC818
#define DAT_RDY_THRESHD_LOW		0xC817

//3.9 USER_CMD_DEF��Ĭ��ֵΪ0x00������Ԥ������û�����
	//0xC819 �� bit[3] : copy_card   ������������
	//			bit[2] : verify_card ����У������
	//			bit[1] : verify_cpu  ��CPUУ������
	//			bit[0] : cmd_program ���������
#define USER_CMD_DEF		0xC819
#define CMD_PROGRAM		1<<0
#define VERIFY_CPY		1<<1
#define VERIFY_CARD		1<<2
#define COPY_CARD		1<<3

//3.10 CSN_HIGH_PULSE��Ĭ��ֵΪ0x06������CSN�źŸߵ�ƽ����
	//0xC81A ��
#define CSN_HIGH_PULSE		0xC81A


//4, ����ͨ����0�Ĳ�����ͨ��0�����ã���
//4.0 ALLCH_SAME_CFG �����Ƿ�ȫ��ͨ��������ͬ������
	//1��ȫ��ͨ������ͨ��0������
	//0��ͨ��1�����Ժ��������ͨ��0���Բ�ͬ
#define ALLCH_SAME_CFG		0xC050

//4.1 CMD_ADDR  ��һ��16�ֽڡ����ֽ�Ϊ�ȷ��͵��ֽڡ����ʵ����Ҫ���͵��ֽ�����ADDR_BYTE_NUM����ʵ�ʷ��Ͷ����ֽڣ�С��16����Ҫ���͵��ֽڰ�˳�������ֽڡ�Ĭ��ֵΪȫ0.	
#define CMD_ADDR_CH0_F		0xC82F	//����ֽڡ� �����ַֻ��һ���ֽڣ�Ӧ��ʹ������ֽ�����
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

//4.2 CMD_ADDR_INC ��Ĭ��ֵΪ0.���������ظ�ִ��ʱ�ĵ�ַ����
	//0x834 : ����ֽڣ���Ӧ 0x82F�ĵ�ַ
	//0x833 :
	//0x832 :
	//0x831 :
	//0x830 :
	//�����ٴ�ִ��ʱ��ʹ�õĵ�ַ�ǣ�
	//��5�ֽ� �� ����CMD_ADDR_INC
	//�����ֽڣ� ���ֲ���
#define CMD_ADDR_INC_CH0_4		0xC834
#define CMD_ADDR_INC_CH0_3		0xC833
#define CMD_ADDR_INC_CH0_2		0xC832
#define CMD_ADDR_INC_CH0_1		0xC831
#define CMD_ADDR_INC_CH0_0		0xC830

//4.3 CMD_NEED_WREN
	//0x835 : bit[0] :	1:��Ҫ�Զ�ִ��WREN  0:����Ҫִ��WREN
#define CMD_NEED_WREN_CH0		0xC835//���ֲῴ�Ƿ���Ҫִ��WREN

//4.4 CMD_INDEX��Ĭ��ֵ��0x9F��Ĭ������¶�Ӧ RDID��� ���������CMD�ֽ�ֵ��
	//0x836 :
#define CMD_INDEX_CH0		0xC836
#define PAGE_PROGRAM	0x02
#define Sector_Erase	0xD8
#define Chip_Erase	0x60//or 0xC7
//4.5 DATA_DIREC�������ڲ���������Ĭ��ֵΪ0
	//0x837 :	[7:5] ��ͨ������������Դ(DSDATA_SRC)
	//			[4:3] ��ͨ����������ȥ��(DSDATA_TGT)
	//			[2:0] ����SPI����������ȥ��(USDATA_TGT)
	//DSDATA_SRC ��	0b001 ������Slave FIFO
	//				0b010 ������ͨ��0�����ڿ������Ϳ���֤ʱʹ��
	//				0b100 ������Local Bus��
	//				0b000 ��û��DATA�ֶ�
	//DSDATA_TGT ��	0b01 �������SPI
	//				0b10 ���������֤ģ�飬����У��ʱʹ��
	//				0b00 ��û��DATA�ֶ�
	//USDATA_TGT ��	0b001 ��д��Slave FIFO
	//				0b100 ��д��Local Bus��

	//ע�� 0x837�ڼ��ֳ��������µ��������£�
	//��SPI�����ݰ����ãӣ����塡�ƣɣƣ��գ�����������
	//��SPI��̣��ãӣ����塡�ƣɣƣϷ�������������
	//�ãӣ����塡�ƣɣƣ������ݽ��п�У�飨�ãУ�У�飩��������������
	//�������������������ݣ�������������������40
	//�������뿨������У�飨��У�飩����������12
	//��Ӧ�ģ� 0x867���⼸�ֳ��������µ��������£�
	//��SPI�����ݰ����ãӣ����塡�ƣɣƣ��գ�����������
	//��SPI��̣��ãӣ����塡�ƣɣƣϷ�������������
	//�ãӣ����塡�ƣɣƣ������ݽ��п�У�飨�ãУ�У�飩��������������
	//�������������������ݣ�������������������48
	//�������뿨������У�飨��У�飩����������52
	//����û�������ֶε���������������Ĵ���Ϊ0x0��
#define DATA_DIREC_CH0		0xC837

//4.6 SEG1_BUS_WIDTH ��Ĭ��ֵΪ0x01������CMD�ֽڷ���ʱ��SPI�ӿ�����λ��
	//0x838 : [2:0],	1��1����ģʽ
	//					2��2����ģʽ
	//					4��4����ģʽ
	//					����ֵ���Ƿ�ֵ
#define SEG1_BUS_WIDTH_CH0		0xC838

//4.7 ADDR_BYTE_NUM��Ĭ��ֵΪ0�����������ADDR�ֶε��ֽ���
	//0x839 : [4:0] ��	0 �������ҪADDR�ֶ�
	//					1~16 ������ADDR�ֶε��ֽ���
	//					17~31 ����Ч����
#define ADDR_BYTE_NUM_CH0		0xC839

//4.8 SEG2_BUS_WIDTH��Ĭ��ֵΪ0x01������ADDR�ֽڷ���ʱ��SPI�ӿ�����λ��
	//0x83A : [2:0],	1��1����ģʽ
	//					2��2����ģʽ
	//					4��4����ģʽ
	//					����ֵ���Ƿ�ֵ
#define SEG2_BUS_WIDTH_CH0		0xC83A

//4.9 CMD_DAT_TX_RX�����������DATA�ֶ��Ǵ�SPI��ȡ���ݣ�������SPIд���ݡ�Ĭ��ֵΪ0x01����ʾ��ȡ���ݣ�������RDID������ƥ�����õģ�
	//0x83B : [1:0],	1����SPI��ȡ���ݣ�
	//					2����SPIд����
	//					3������ģʽ
	//					0��û�����ݴ���
#define CMD_DAT_TX_RX_CH0		0xC83B

//4.10 SEG3_BUS_WIDTH��Ĭ��ֵΪ0x01������DATA�ֶδ���ʱSPI�ӿ�����λ��
	//0x83C : [2:0],	1��1����ģʽ
	//					2��2����ģʽ
	//					4��4����ģʽ
	//					����ֵ���Ƿ�ֵ
#define SEG3_BUS_WIDTH_CH0		0xC83C

//4.11 CH_EN ��ͨ����0�ĸ���ͨ��ʹ�����ã�Ĭ��ֵΪ0x01����ʾͨ��0ʹ��
	//0x83D : [0],	1��ͨ��0ʹ��
	//				0��ͨ��0��ʹ��
#define CH_EN_CH0		0xC83D

//5.����ͨ����1�Ĳ�����ͨ��1~��n - 1�������ã��� ����Ӧ�Ĵ�����ƫ�Ƶ�ַ��ͨ����0�Ĵ�0x30��
//5.1 CMD_ADDR  ��һ��16�ֽڡ����ֽ�Ϊ�ȷ��͵��ֽڡ����ʵ����Ҫ���͵��ֽ�����ADDR_BYTE_NUM����ʵ�ʷ��Ͷ����ֽڣ�С��16����Ҫ���͵��ֽڰ�˳�������ֽڡ�
	//Ĭ��ֵΪȫ0.
#define CMD_ADDR_CH1_F		0xC85F//����ֽڡ� �����ַֻ��һ���ֽڣ�Ӧ��ʹ������ֽ�����
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

//5.2 CMD_ADDR_INC ��Ĭ��ֵΪ0.���������ظ�ִ��ʱ�ĵ�ַ����
	//0x864 : ����ֽڣ���Ӧ 0x82F�ĵ�ַ
	//0x863 :
	//0x862 :
	//0x861 :
	//0x860 :
	//�����ٴ�ִ��ʱ��ʹ�õĵ�ַ�ǣ�
	//��5�ֽ�  �� ����CMD_ADDR_INC
	//�����ֽڣ� ���ֲ���
#define CMD_ADDR_INC_CH1_4		0xC864
#define CMD_ADDR_INC_CH1_3		0xC863
#define CMD_ADDR_INC_CH1_2		0xC862
#define CMD_ADDR_INC_CH1_1		0xC861
#define CMD_ADDR_INC_CH1_0		0xC860

//5.3 CMD_NEED_WREN
	//0x865 : bit[0] :	1, ��Ҫ�Զ�ִ��WREN
	//					0, ����Ҫִ��WREN
#define CMD_NEED_WREN_CH1		0xC865

//5.4 CMD_INDEX��Ĭ��ֵ��0x9F��Ĭ������¶�Ӧ RDID��� ���������CMD�ֽ�ֵ��
	//0x866 :
#define CMD_INDEX_CH1		0xC866

//5.5 DATA_DIREC�������ڲ���������Ĭ��ֵΪ0
	//0x867 : [7:5] ��ͨ������������Դ(DSDATA_SRC)
	//		[4:3] ��ͨ����������ȥ��(DSDATA_TGT)
	//		[2:0] ����SPI����������ȥ��(USDATA_TGT)
	//DSDATA_SRC ��	0b001 ������Slave FIFO
	//				0b010 ������ͨ��0�����ڿ������Ϳ���֤ʱʹ��
	//				0b100 ������Local Bus��
	//				0b000 ��û��DATA�ֶ�
	//DSDATA_TGT ��	0b01 �������SPI
	//				0b10 ���������֤ģ�飬����У��ʱʹ��
	//				0b00 ��û��DATA�ֶ�
	//USDATA_TGT ��	0b001 ��д��Slave FIFO
	//				0b010 ��д����֤ģ�飬��У��ʱʹ��
	//				0b100 ��д��Local Bus��
#define DATA_DIREC_CH1		0xC867

//5.6 SEG1_BUS_WIDTH ��Ĭ��ֵΪ0x01������CMD�ֽڷ���ʱ��SPI�ӿ�����λ��
	//0x868 : [2:0],	1��1����ģʽ
	//					2��2����ģʽ
	//					4��4����ģʽ
	//					����ֵ���Ƿ�ֵ
#define SEG1_BUS_WIDTH_CH1		0xC868

//5.7 ADDR_BYTE_NUM��Ĭ��ֵΪ0�����������ADDR�ֶε��ֽ���
	//0x869 : [4:0] ��	0 �������ҪADDR�ֶ�
	//					1~16 ������ADDR�ֶε��ֽ���
	//					17~31 ����Ч����
#define ADDR_BYTE_NUM_CH1		0xC869

//5.8 SEG2_BUS_WIDTH��Ĭ��ֵΪ0x01������ADDR�ֽڷ���ʱ��SPI�ӿ�����λ��
	//0x86A : [2:0],	1��1����ģʽ
	//					2��2����ģʽ
	//					4��4����ģʽ
	//					����ֵ���Ƿ�ֵ
#define SEG2_BUS_WIDTH_CH1		0xC86A

//5.9 CMD_DAT_TX_RX�����������DATA�ֶ��Ǵ�SPI��ȡ���ݣ�������SPIд���ݡ�Ĭ��ֵΪ0x01����ʾ��ȡ���ݣ�������RDID������ƥ�����õģ�
	//0x86B : [1:0],	1����SPI��ȡ���ݣ�
	//					2����SPIд����
	//					3������ģʽ
	//					0��û�����ݴ���
#define CMD_DAT_TX_RX_CH1		0xC86B

//5.10 SEG3_BUS_WIDTH��Ĭ��ֵΪ0x01������DATA�ֶδ���ʱSPI�ӿ�����λ��
	//0x86C : [2:0],		1��1����ģʽ
	//					2��2����ģʽ
	//					4��4����ģʽ
	//					����ֵ���Ƿ�ֵ
#define SEG3_BUS_WIDTH_CH1		0xC86C

//5.11 CH_EN ��ͨ����1�ĸ���ͨ��ʹ�����ã�Ĭ��ֵΪ0x01����ʾͨ��1ʹ��
	//0x86D : [0], 1��ͨ��1ʹ�ܣ�    0��ͨ��1��ʹ��
	//		[1], 1��ͨ��2ʹ�ܣ�    0��ͨ��2��ʹ��
	//		[2], 1��ͨ��3ʹ�ܣ�    0��ͨ��3��ʹ��
	//		[3], 1��ͨ��4ʹ�ܣ�    0��ͨ��4��ʹ��
	//		[4], 1��ͨ��5ʹ�ܣ�    0��ͨ��5��ʹ��
	//		[5], 1��ͨ��6ʹ�ܣ�    0��ͨ��6��ʹ��
	//		[6], 1��ͨ��7ʹ�ܣ�    0��ͨ��7��ʹ��
	//		[7], 1��ͨ��8ʹ�ܣ�    0��ͨ��8��ʹ��
	//0x86E : ����ͨ��9 ~16ʹ��
	//0x86F : ����ͨ��17~24ʹ��
	//0x870 : ����ͨ��25~32ʹ��
	//0x871 : ����ͨ��33~40ʹ��
	//0x872 : ����ͨ��41~48ʹ��
	//0x873 : ����ͨ��49~56ʹ��
	//0x874 : ����ͨ��57~64ʹ��
#define CH_EN_CH1		0xC86D

#endif // !SPI_PROGRAMMER_SETTING_H_
