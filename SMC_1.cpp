#include <iostream>
#include "smc6200.h"

#define    SMC_OUT_VALIDVALUE      0    //有效电平，通用IO为低电平, 当切换初始电平后，输出电平会相反
#define    SMC_OUT_INVALIDVALUE    1    //高电平
#define		OUT_1		1		//OUT输出口1
#define		OUT_2		2		//OUT输出口2
#define		OUT_3		3		//OUT输出口3
#define		OUT_4		4		//OUT输出口4
#define		OUT_5		5		//OUT输出口5
#define		OUT_6		6		//OUT输出口6
#define		OUT_7		7		//OUT输出口7
#define		OUT_8		8		//OUT输出口8
#define		X_IAXIS		0		//X轴
#define		Y_IAXIS		1		//Y轴
#define		Z_IAXIS		2		//Z轴
#define		IFABS_YES	1		//绝对坐标系
#define		IFABS_NO	2		//不是绝对坐标系

SMCHANDLE   g_handle = NULL;

using namespace std;
int main()
{
	char   buffer[256];
	int		m_moveAxis;		//定义轴 0---X轴
	int		m_moveMode;
	int		stop = 0;
	int32 iresult;
	int32 out;
	double  distance;	//移动坐标
	double  speed;		//轴移动速度
	double	smc_length;


	iresult = SMCOpenEth("192.168.1.11", &g_handle);
	printf("ok=%d \n", iresult);
	SMCWriteOutBit(g_handle, 1, SMC_OUT_INVALIDVALUE);
	//m_moveAxis = 0;
	//cin >> m_moveAxis;		//输入指令
	cin >> smc_length;
	cin.get();
	SMCWriteOutBit(g_handle, OUT_1, SMC_OUT_VALIDVALUE);	//OUT口输出

	SMCPMove(g_handle, X_IAXIS, smc_length, 0);

//	SMCVectMoveLine1(g_handle, X_IAXIS, distance, speed, IFABS_NO);
//	SMCVectMoveLine1(g_handle, Y_IAXIS, distance, speed, IFABS_NO);
	cout << "hello world!" << iresult << "\n" << endl;
	
	cin >> stop;
	cin.get();//这个可以不要
	if (stop == 1)
	{
		SMCDecelStop(g_handle, SMC_AXIS_NUM_ALL);
	}
			
	cin.get();//这个可以不要
	return 0;
	
}

/*

if (NULL == g_handle)
{
return;
}

SMCDecelStop(g_handle, SMC_AXIS_NUM_ALL);
*/
