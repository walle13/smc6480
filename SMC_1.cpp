#include <iostream>
#include "smc6200.h"
#include "SMC_1.h"
#include<list>


#define    SMC_OUT_VALIDVALUE      0    //��Ч��ƽ��ͨ��IOΪ�͵�ƽ, ���л���ʼ��ƽ�������ƽ���෴
#define    SMC_OUT_INVALIDVALUE    1    //�ߵ�ƽ
#define		OUT_1		1		//OUT�����1
#define		OUT_2		2		//OUT�����2
#define		OUT_3		3		//OUT�����3
#define		OUT_4		4		//OUT�����4
#define		OUT_5		5		//OUT�����5
#define		OUT_6		6		//OUT�����6
#define		OUT_7		7		//OUT�����7
#define		OUT_8		8		//OUT�����8
#define		X_IAXIS		0		//X��
#define		Y_IAXIS		1		//Y��
#define		Z_IAXIS		2		//Z��
#define		IFABS_YES	1		//��������ϵ
#define		IFABS_NO	0		//���Ǿ�������ϵ
#define		MC_CODE_FORMAT_SIZE                     20
#define		MC_QUEUE_CODE_BUF_NUM			        1000
#define		MC_FAST_CODE_BUF_NUM                    1000
#define		MC_SUPER_CODE_BUF_NUM                   1000

using namespace std;


SMCHANDLE   g_handle = NULL;

static MC_CODE_BUF      MC_QueueCodeBuf[MC_QUEUE_CODE_BUF_NUM] = { 0 };



uint8 _axis_iaxis[] = {0,1,2,3};


double dist_array[] = { 200,200,200,200 };

int main()
{
	
	char   buffer[256];
	char	code_ins[256];
	int		m_moveAxis;		//������ 0---X��
	int		m_moveMode;
	int		stop = 0;
	int32 iresult;
	int32 out;
	double  distance;	//�ƶ�����
	double  speed;		//���ƶ��ٶ�
	double	smc_length;
	char	code[1];



	
	iresult = SMCOpenEth("192.168.1.11", &g_handle);
	printf("ok=%d \n", iresult);
	SMCWriteOutBit(g_handle, 1, SMC_OUT_INVALIDVALUE);
	//m_moveAxis = 0;
	//cin >> m_moveAxis;		//����ָ��

	int Error_Code = 1;
	while (1)
	{
		cin >> code_ins;
//		cin.get();
		/*
		if (code_ins[0] = 'G')
			printf("right");*/

		switch (code_ins[0])
		{
		case 'G':
			printf("abc");
			cout << "ABC!" << iresult << "\n" << endl;
			smc_length = 1000;
			SMCWriteOutBit(g_handle, OUT_1, SMC_OUT_VALIDVALUE);	//OUT�����
			SMCPMove(g_handle, X_IAXIS, smc_length, 0);
		//	SMCPMove(g_handle, Y_IAXIS, smc_length, 0);
		//	SMCPMove(g_handle, Z_IAXIS, smc_length, 0);
		//	SMCVectMoveStart(g_handle);
		//	SMCVectMoveLine2(g_handle, X_IAXIS, smc_length, Y_IAXIS, smc_length, 100, IFABS_YES);    //2��岹
		//	Error_Code=SMCVectMoveLineN(g_handle, 2, _axis_iaxis, dist_array, 10, IFABS_NO);		//����岹
			cout << Error_Code << endl;
			
			break ;
		case 'M':
			printf("123");
			cout << "DEF!" << iresult << "\n" << endl;
			SMCPMove(g_handle, Z_IAXIS, smc_length, 0);
		//	SMCVectMoveStart(g_handle);
		//	Error_Code = SMCVectMoveLineN(g_handle, 3, _axis_iaxis, dist_array, 10, IFABS_NO);		//����岹
			break;
		case 'T':
			printf("456");
			break;
		default:
			cout << "other!" << iresult << "\n" << endl;
			break;
		}

		//cin >> smc_length;
		//cin.get();
		//SMCWriteOutBit(g_handle, OUT_1, SMC_OUT_VALIDVALUE);	//OUT�����
		//SMCPMove(g_handle, X_IAXIS, smc_length, 0);

		//	SMCVectMoveLine1(g_handle, X_IAXIS, distance, speed, IFABS_NO);
		//	SMCVectMoveLine1(g_handle, Y_IAXIS, distance, speed, IFABS_NO);
		cout << "hello world! " << iresult << "\n" << endl;

		cout << "Is need to stop? " << iresult << "\n" << endl;
		cin >> stop;
		if (stop == 1)
		{
			SMCDecelStop(g_handle, SMC_AXIS_NUM_ALL);
		}
		memset(code_ins, 0, 256);
	}
	
	return 0;
	
}

/*
if (NULL == g_handle)
{
return;
}

SMCDecelStop(g_handle, SMC_AXIS_NUM_ALL);
*/
