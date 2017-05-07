#include <iostream>
#include "smc6200.h"

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
#define		IFABS_NO	2		//���Ǿ�������ϵ

SMCHANDLE   g_handle = NULL;

using namespace std;
int main()
{
	char   buffer[256];
	int		m_moveAxis;		//������ 0---X��
	int		m_moveMode;
	int		stop = 0;
	int32 iresult;
	int32 out;
	double  distance;	//�ƶ�����
	double  speed;		//���ƶ��ٶ�
	double	smc_length;


	iresult = SMCOpenEth("192.168.1.11", &g_handle);
	printf("ok=%d \n", iresult);
	SMCWriteOutBit(g_handle, 1, SMC_OUT_INVALIDVALUE);
	//m_moveAxis = 0;
	//cin >> m_moveAxis;		//����ָ��
	cin >> smc_length;
	cin.get();
	SMCWriteOutBit(g_handle, OUT_1, SMC_OUT_VALIDVALUE);	//OUT�����

	SMCPMove(g_handle, X_IAXIS, smc_length, 0);

//	SMCVectMoveLine1(g_handle, X_IAXIS, distance, speed, IFABS_NO);
//	SMCVectMoveLine1(g_handle, Y_IAXIS, distance, speed, IFABS_NO);
	cout << "hello world!" << iresult << "\n" << endl;
	
	cin >> stop;
	cin.get();//������Բ�Ҫ
	if (stop == 1)
	{
		SMCDecelStop(g_handle, SMC_AXIS_NUM_ALL);
	}
			
	cin.get();//������Բ�Ҫ
	return 0;
	
}

/*

if (NULL == g_handle)
{
return;
}

SMCDecelStop(g_handle, SMC_AXIS_NUM_ALL);
*/
