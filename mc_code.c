#include "mc_includes.h"

         static MC_CODE_SYS_FLAG MC_CodeSysFlag = {0};

         static MC_CODE_BUF      MC_QueueCodeBuf[MC_QUEUE_CODE_BUF_NUM] = {0};
volatile static MC_U32           MC_QueueCodeBufHead = 0;
volatile static MC_U32           MC_QueueCodeBufTail = 0;

         static MC_CODE_BUF      MC_FastCodeBuf[MC_FAST_CODE_BUF_NUM] = {0};
volatile static MC_U32           MC_FastCodeBufHead = 0;
volatile static MC_U32           MC_FastCodeBufTail = 0;

static MC_CODE_BUF				 MC_SuperCodeBuf[MC_SUPER_CODE_BUF_NUM] = {0};
volatile static MC_U32           MC_SuperCodeBufHead = 0;
volatile static MC_U32           MC_SuperCodeBufTail = 0;


void MC_CodeInit(void)
{
    MC_QueueCodeBufHead = MC_QueueCodeBufTail = 0;
    MC_FastCodeBufHead  = MC_FastCodeBufTail  = 0;
    MC_SuperCodeBufHead = MC_SuperCodeBufTail = 0;

    MC_CodeSysFlag.QueueCodeNum = 0;
    MC_CodeSysFlag.FastCodeNum  = 0;
    MC_CodeSysFlag.SuperCodeNum = 0;
    MC_CodeSysFlag.LoseQueueCodeNum = 0;
    MC_CodeSysFlag.LoseFastCodeNum  = 0;

	MC_CodeSysFlag.EnterVectMode = MC_FALSE;
    MC_CodeSysFlag.InVectModeLinearMotion = MC_FALSE;
    MC_CodeSysFlag.InterposeMotionStopHasLinearMotion = MC_FALSE;
	MC_CodeSysFlag.InterposeMotionStop = MC_FALSE;
	MC_CodeSysFlag.InterposeMotionStopFinish  = MC_TRUE;
	MC_CodeSysFlag.InterposeMotionStopOutSilk = MC_FALSE;
    MC_CodeSysFlag.InterposeMotionStopRecover = MC_FALSE;
    MC_CodeSysFlag.InterposeMotionStopRecoverStop = MC_FALSE;
    MC_CodeSysFlag.InterposeMotionFirstStop = 0;
    MC_CodeSysFlag.LinearMotionStop = MC_FALSE;
    MC_CodeSysFlag.LinearMotionStopFinish = MC_TRUE;
    MC_CodeSysFlag.PrintEndStopFinish = MC_TRUE;
    MC_CodeSysFlag.VectMotionRecover = MC_FALSE;
    MC_CodeSysFlag.ExecuteLineMove = MC_FALSE;

    MC_CodeSysFlag.HasGetM206 = MC_FALSE;
}

MC_CODE_SYS_FLAG* MC_CodeGetSysFlag(void)
{
    return &MC_CodeSysFlag;
}

MC_BOOL MC_CodeStoreQueueCode(CONST MC_CODE_BUF* code)
{
    if ( MC_QueueCodeBufHead != MC_QUEUE_CODE_BUF_NUM - 1 )
    {
        if ( MC_QueueCodeBufHead + 1 != MC_QueueCodeBufTail )
        {
            MC_QueueCodeBuf[MC_QueueCodeBufHead] = *code;

            MC_CodeSysFlag.QueueCodeNum ++;
            MC_QueueCodeBufHead ++;

            return MC_TRUE;
        }
    }
    else
    {
        if ( 0 != MC_QueueCodeBufHead )
        {
            MC_QueueCodeBuf[MC_QueueCodeBufHead] = *code;

            MC_CodeSysFlag.QueueCodeNum ++;
            MC_QueueCodeBufHead = 0;

            return MC_TRUE;
        }   
    }

    return MC_FALSE;
}

MC_BOOL MC_CodeStoreFastCode(CONST MC_CODE_BUF* code)
{
    if ( MC_FastCodeBufHead != MC_FAST_CODE_BUF_NUM - 1 )
    {
        if ( MC_FastCodeBufHead + 1 != MC_FastCodeBufTail )
        {
            MC_FastCodeBuf[MC_FastCodeBufHead] = *code;

            MC_CodeSysFlag.FastCodeNum ++;
            MC_FastCodeBufHead ++;

            return MC_TRUE;
        }
    }
    else
    {
        if ( 0 != MC_FastCodeBufHead )
        {
            MC_FastCodeBuf[MC_FastCodeBufHead] = *code;

            MC_CodeSysFlag.FastCodeNum ++;
            MC_FastCodeBufHead = 0;

            return MC_TRUE;
        }
    }

    return MC_FALSE;
}

MC_BOOL MC_CodeStoreSuperCode(CONST MC_CODE_BUF* code)
{
	if ( MC_SuperCodeBufHead != MC_FAST_CODE_BUF_NUM - 1 )
	{
		if ( MC_SuperCodeBufHead + 1 != MC_SuperCodeBufTail )
		{
			MC_SuperCodeBuf[MC_SuperCodeBufHead] = *code;

			MC_CodeSysFlag.SuperCodeNum ++;
			MC_SuperCodeBufHead ++;

			return MC_TRUE;
		}
	}
	else
	{
		if ( 0 != MC_SuperCodeBufHead )
		{
			MC_SuperCodeBuf[MC_SuperCodeBufHead] = *code;

			MC_CodeSysFlag.SuperCodeNum ++;
			MC_SuperCodeBufHead = 0;

			return MC_TRUE;
		}
	}

	return MC_FALSE;
}

MC_U32 MC_CodeGetQueueCodeNum(void)
{
    return MC_CodeSysFlag.QueueCodeNum;
}

MC_U32 MC_CodeGetFastCodeNum(void)
{
    return MC_CodeSysFlag.FastCodeNum;
}

MC_U32 MC_CodeGetSuperCodeNum(void)
{
	return MC_CodeSysFlag.SuperCodeNum;
}

static void MC_CodeFastCodeClear(void)
{
    MC_FastCodeBufHead = MC_FastCodeBufTail  = 0;
    MC_CodeSysFlag.FastCodeNum  = 0;
    MC_CodeSysFlag.LoseFastCodeNum  = 0;
}

static void MC_CodeAllCodeClear(void)
{
    MC_QueueCodeBufHead = MC_QueueCodeBufTail = 0;
    MC_FastCodeBufHead  = MC_FastCodeBufTail  = 0;
    MC_SuperCodeBufHead = MC_SuperCodeBufTail = 0;

    MC_CodeSysFlag.QueueCodeNum = 0;
    MC_CodeSysFlag.FastCodeNum  = 0;
    MC_CodeSysFlag.SuperCodeNum = 0;
    MC_CodeSysFlag.LoseQueueCodeNum = 0;
    MC_CodeSysFlag.LoseFastCodeNum  = 0;
}

void MC_CodeGetG01FromCodeFormat(MC_CODE_FORMAT* format)
{
    MC_G01_CODE_FORMAT* pG01 = (MC_G01_CODE_FORMAT*)format;
    MC_U8 *pC = MC_NULL;

    pC = (MC_U8*)&pG01->CoordX;
    pG01->CoordX = MC_CodeFourByteToTrueValue(*pC, *(pC + 1), *(pC + 2), *(pC + 3));

    pC = (MC_U8*)&pG01->CoordY;
    pG01->CoordY = MC_CodeFourByteToTrueValue(*pC, *(pC + 1), *(pC + 2), *(pC + 3));

    pC = (MC_U8*)&pG01->CoordZ;
    pG01->CoordZ = MC_CodeFourByteToTrueValue(*pC, *(pC + 1), *(pC + 2), *(pC + 3));

    pC = (MC_U8*)&pG01->CoordU;
    pG01->CoordU = MC_CodeFourByteToTrueValue(*pC, *(pC + 1), *(pC + 2), *(pC + 3));

    pC = (MC_U8*)&pG01->MoveSpeed;
    pG01->MoveSpeed = MC_CodeFourByteToTrueValue(*pC, *(pC + 1), *(pC + 2), *(pC + 3));
}

void MC_CodeGetG02FromCodeFormat(MC_CODE_FORMAT* format)
{
    MC_G02_CODE_FORMAT* pG02 = (MC_G02_CODE_FORMAT*)format;
    MC_U8 *pC = MC_NULL;

    pC = (MC_U8*)&pG02->CoordX;
    pG02->CoordX = MC_CodeFourByteToTrueValue(*pC, *(pC + 1), *(pC + 2), *(pC + 3));

    pC = (MC_U8*)&pG02->CoordY;
    pG02->CoordY = MC_CodeFourByteToTrueValue(*pC, *(pC + 1), *(pC + 2), *(pC + 3));

    pC = (MC_U8*)&pG02->CentreX;
    pG02->CentreX = MC_CodeFourByteToTrueValue(*pC, *(pC + 1), *(pC + 2), *(pC + 3));

    pC = (MC_U8*)&pG02->CentreY;
    pG02->CentreY = MC_CodeFourByteToTrueValue(*pC, *(pC + 1), *(pC + 2), *(pC + 3));
}

void MC_CodeGetG03FromCodeFormat(MC_CODE_FORMAT* format)
{
    MC_G03_CODE_FORMAT* pG03 = (MC_G03_CODE_FORMAT*)format;
    MC_U8 *pC = MC_NULL;

    pC = (MC_U8*)&pG03->CoordX;
    pG03->CoordX = MC_CodeFourByteToTrueValue(*pC, *(pC + 1), *(pC + 2), *(pC + 3));

    pC = (MC_U8*)&pG03->CoordY;
    pG03->CoordY = MC_CodeFourByteToTrueValue(*pC, *(pC + 1), *(pC + 2), *(pC + 3));

    pC = (MC_U8*)&pG03->CentreX;
    pG03->CentreX = MC_CodeFourByteToTrueValue(*pC, *(pC + 1), *(pC + 2), *(pC + 3));

    pC = (MC_U8*)&pG03->CentreY;
    pG03->CentreY = MC_CodeFourByteToTrueValue(*pC, *(pC + 1), *(pC + 2), *(pC + 3));
}

void MC_CodeGetG90FromCodeFormat(MC_CODE_FORMAT* format)
{
	MC_G90_CODE_FORMAT* pG90 = (MC_G90_CODE_FORMAT*)format;
	MC_U8* pC   = (MC_U8*)&pG90->MoveSpeed;

    pG90->MoveSpeed = MC_CodeFourByteToTrueValue(*pC, *(pC + 1), *(pC + 2), *(pC + 3));
}


void MC_CodeGetG100FromCodeFormat(MC_CODE_FORMAT* format)
{
    MC_CodeGetG01FromCodeFormat(format);
}

void MC_CodeGetG101FromCodeFormat(MC_CODE_FORMAT* format)
{
    MC_CodeGetG01FromCodeFormat(format);
}

void MC_CodeGetM304FromCodeFormat(MC_CODE_FORMAT* format)
{
	MC_M304_CODE_FORMAT* pM304 = (MC_M304_CODE_FORMAT*)format;
	MC_U8* pC = MC_NULL;

	pC = (MC_U8*)&pM304->NowHead;
	pM304->NowHead = MC_CodeOneByteToTrueValue(*pC);

    pC = (MC_U8*)&pM304->ReturnShelf;
	pM304->ReturnShelf = MC_CodeOneByteToTrueValue(*pC);

	pC = (MC_U8*)&pM304->TargetHead;
	pM304->TargetHead = MC_CodeOneByteToTrueValue(*pC);

    pC = (MC_U8*)&pM304->TargetShelf;
	pM304->TargetShelf = MC_CodeOneByteToTrueValue(*pC);
}

void MC_CodeGetM100FromCodeFormat(MC_CODE_FORMAT* format)
{
    MC_M100_CODE_FORMAT* pM100 = (MC_M100_CODE_FORMAT*)format;
    MC_U8* pC	   = MC_NULL;

    pC = (MC_U8*)&pM100->AnalogV;
    pM100->AnalogV = MC_CodeFourByteToTrueValue(*pC, *(pC + 1), *(pC + 2), *(pC + 3));
}

//void MC_CodeGetM101FromCodeFormat(MC_CODE_FORMAT* format)
//{
//    MC_M101_CODE_FORMAT* pM101 = (MC_M101_CODE_FORMAT*)format;
//    MC_U8 *pC = MC_NULL;
//
//    pC = (MC_U8*)&pM101->TempHeadZ;
//    pM101->TempHeadZ = MC_CodeTwoByteToTrueValue(*pC, *(pC + 1));
//
//    pC = (MC_U8*)&pM101->TempHead1;
//    pM101->TempHead1 = MC_CodeTwoByteToTrueValue(*pC, *(pC + 1));
//
//    pC = (MC_U8*)&pM101->TempHead2;
//    pM101->TempHead2 = MC_CodeTwoByteToTrueValue(*pC, *(pC + 1));
//
//    pC = (MC_U8*)&pM101->TempHead3;
//    pM101->TempHead3 = MC_CodeTwoByteToTrueValue(*pC, *(pC + 1));
//
//    pC = (MC_U8*)&pM101->TempHead4;
//    pM101->TempHead4 = MC_CodeTwoByteToTrueValue(*pC, *(pC + 1));
//
//    pC = (MC_U8*)&pM101->TempPlatform;
//    pM101->TempPlatform = MC_CodeTwoByteToTrueValue(*pC, *(pC + 1));
//}

//void MC_CodeGetM102FromCodeFormat(MC_CODE_FORMAT* format)
//{
//    MC_M102_CODE_FORMAT* pM102 = (MC_M102_CODE_FORMAT*)format;
//    MC_U8 *pC = MC_NULL;
//    MC_U8 i   = 0;
//
//    pC = (MC_U8*)&pM102->Request;
//
//    while ( i++ < MC_CODE_FORMAT_SIZE / 2 )
//        pM102->Request[i] = MC_CodeTwoByteToTrueValue(*pC++, *((pC++) + 1));
//}

//void MC_CodeGetM103FromCodeFormat(MC_CODE_FORMAT* format)
//{
//    /* Single byte data that needn't convertion */
//}

void MC_CodeGetM200FromCodeFormat(MC_CODE_FORMAT* format)
{
    MC_M200_CODE_FORMAT* pM200 = (MC_M200_CODE_FORMAT*)format;
    MC_U8*				 pC = MC_NULL;

    pC = (MC_U8*)&pM200->UnitPulseX;
    pM200->UnitPulseX = MC_CodeTwoByteToTrueValue(*pC, *(pC + 1));

    pC = (MC_U8*)&pM200->UnitPulseY;
    pM200->UnitPulseY = MC_CodeTwoByteToTrueValue(*pC, *(pC + 1));

    pC = (MC_U8*)&pM200->UnitPulseZ;
    pM200->UnitPulseZ = MC_CodeTwoByteToTrueValue(*pC, *(pC + 1));

    pC = (MC_U8*)&pM200->UnitPulseU;
    pM200->UnitPulseU = MC_CodeTwoByteToTrueValue(*pC, *(pC + 1));
}

void MC_CodeGetM205FromCodeFormat(MC_CODE_FORMAT* format)
{
    MC_M205_CODE_FORMAT* pM205 = (MC_M205_CODE_FORMAT*)format;
    MC_U8*				 pC    = MC_NULL;

    pC = (MC_U8*)&pM205->CoordX;
    pM205->CoordX = MC_CodeFourByteToTrueValue(*pC, *(pC + 1), *(pC + 2), *(pC + 3));

    pC = (MC_U8*)&pM205->CoordY;
    pM205->CoordY = MC_CodeFourByteToTrueValue(*pC, *(pC + 1), *(pC + 2), *(pC + 3));
}

void MC_CodeGetM206FromCodeFormat(MC_CODE_FORMAT* format)
{
    MC_M206_CODE_FORMAT* pM206 = (MC_M206_CODE_FORMAT*)format;
    MC_U8*				 pC    = MC_NULL;

    pC = (MC_U8*)&pM206->OffsetCoordX;
    pM206->OffsetCoordX = MC_CodeFourByteToTrueValue(*pC, *(pC + 1), *(pC + 2), *(pC + 3));

    pC = (MC_U8*)&pM206->OffsetCoordY;
    pM206->OffsetCoordY = MC_CodeFourByteToTrueValue(*pC, *(pC + 1), *(pC + 2), *(pC + 3));
}

void MC_CodeGetM211FromCodeFormat(MC_CODE_FORMAT* format)
{
    MC_M211_CODE_FORMAT* pM211 = (MC_M211_CODE_FORMAT*)format;
    MC_U8*				 pC    = MC_NULL;

    pC = (MC_U8*)&pM211->CoordZ;
    pM211->CoordZ = MC_CodeFourByteToTrueValue(*pC, *(pC + 1), *(pC + 2), *(pC + 3));
}

MC_BOOL MC_CodeRecoverOutSilk(void)
{
    if ( !MC_MotContrGetSysFlag()->AirPlugState )
    {
        MC_MotContrEnableLockAirCock();

        MC_MotContrGetSysFlag()->RecoverOutSilkStage = MC_MOT_OUT_AIR_PLUG_DELAY; // ��ѹ������Ƴ���ʱ��
    }

    if ( MC_MotContrGetSysFlag()->RecoverOutSilkStage ? !(--MC_MotContrGetSysFlag()->RecoverOutSilkStage) : MC_TRUE )
    {
        if ( MC_TRUE == MC_CodeSysFlag.InterposeMotionStopOutSilk )
        {
            if ( 0 == MC_MotContrGetSysFlag()->RecoverOutSilkDelay )
            {
                MC_MotContrGetSysFlag()->RecoverOutSilkDelay = 1;
                MC_MotContrM101(); // �ָ���˿��
            }
            else
            {   // ��˿���˶���ʱһ��ʱ�����˶���
                if ( ++(MC_MotContrGetSysFlag()->RecoverOutSilkDelay) > MC_CoreGetSysFlag()->OutSilkMotionDelay ) 
                {
                    MC_MotContrGetSysFlag()->RecoverOutSilkDelay = 0;

                    return MC_TRUE;
                }
            }

            return MC_FALSE;
        }
        else
            return MC_TRUE;
    }
    else
        return MC_FALSE;
}

static MC_BOOL MC_CodeM02Exec(void)
{
    // �յ�ֹͣ��ӡָ��֮���ȹر����������˳��岹ģʽ��
    MC_MotContrM103();         // ��������
    MC_MotContrStopVectMove(); // ֹͣ�岹����ջ��档
    MC_MotContrExitVectMove(); // �˳��岹ģʽ��
    MC_MotContrM02();          // ������ֹͣ��

    MC_CodeAllCodeClear();     // ��ղ岹���С�
    MC_MotContrClearAllCoordVariable(); // ��ʼ���������������
    MC_MotContrClearAllStateVariable(); // ��ʼ������ȫ�ֹ��̿��Ʊ�־������
    MC_CodeSysFlag.PrintEndStopFinish = MC_FALSE;

    MC_CoreOutputTestData("M02\r\n");

    return MC_TRUE;
}

static MC_BOOL MC_CodeM04Exec(void)
{
    MC_G90_CODE_FORMAT G90_Para;

    G90_Para.MoveSpeed = MC_CODE_COORD_NULL;

    // �յ�ֹͣ��ӡָ��֮���ȹر����������˳��岹ģʽ��
    if ( 0 == MC_MotContrGetSysFlag()->M04_Stage )
    {
        MC_MotContrM103();         // ��������
        MC_MotContrStopVectMove(); // ֹͣ�岹����ջ��档
        MC_MotContrExitVectMove(); // �˳��岹ģʽ��

        MC_MotContrGetSysFlag()->M04_Stage = 1; // ������һ���׶Ρ�
    }    // ���Ż��㡣
    else if ( 1 == MC_MotContrGetSysFlag()->M04_Stage )
    {
	    if ( (MC_TRUE == MC_MotContrAllAxisStop()) && !MC_MotContrIfHomeMoving() )
	    {
            if ( MC_TRUE == MC_MotContrG90(&G90_Para) )
                MC_MotContrGetSysFlag()->M04_Stage = 2; // ������һ���׶Ρ�
        }
    }
    else
    {
        MC_MotContrGetSysFlag()->M04_Stage = 0; // ָ�����̱�־��λ��

        MC_MotContrM04();
        MC_CodeAllCodeClear(); // ��ղ岹���С�
        MC_MotContrClearAllCoordVariable(); // ��ʼ���������������
        MC_MotContrClearAllStateVariable(); // ��ʼ������ȫ�ֹ��̿��Ʊ�־������
        MC_CodeSysFlag.PrintEndStopFinish = MC_FALSE;

        MC_CoreOutputTestData("M04\r\n");

        return MC_TRUE;
    }

    return MC_FALSE;
}

static MC_BOOL MC_CodeM06Exec(MC_CODE_FORMAT* pFormat)
{
    switch ( MC_MotContrGetSysFlag()->M06_Stage1 )
    {
        case 0: MC_CodeGetM304FromCodeFormat(pFormat);
                MC_MotContrGetSysFlag()->M06_Stage1 ++;
                MC_ComUdcsGetFlag()->QueueSwitchHeadStart = MC_TRUE;
                break;

                // ����ָ��ģʽ�½�����ֱ���˶���
        case 1: MC_CodeSysFlag.InVectModeLinearMotion = MC_TRUE;
                
                // ֱ�ӵ��ÿ���ָ��M304����ͷ�л�����������
                if ( MC_TRUE == MC_MotContrM304((MC_M304_CODE_FORMAT*)pFormat) )
                    MC_MotContrGetSysFlag()->M06_Stage1 ++;

                break;

                // ��ʱ��ͷ�л����,��λ����ָ���ͷ�л���ɱ�־��
        case 2: MC_CodeSysFlag.InVectModeLinearMotion = MC_FALSE;
                MC_ComUdcsGetFlag()->QueueSwitchHeadFinish = MC_TRUE;
                MC_MotContrGetSysFlag()->M06_Stage1 ++;
                break;

        default:
            break;
    }

    if ( 3 == MC_MotContrGetSysFlag()->M06_Stage1 )
    {
        MC_MotContrGetSysFlag()->M06_Stage1 = 0;

        return MC_TRUE;
    }
    else
        return MC_FALSE;
}

static MC_BOOL MC_CodeM101Exec(MC_CODE_FORMAT* pFormat)
{
    if ( 0 == MC_MotContrGetSysFlag()->M101_Stage )
    {
	    MC_MotContrGetSysFlag()->M101_Stage = 1;
	    MC_MotContrM101();
	    MC_CodeSysFlag.InterposeMotionStopOutSilk = MC_TRUE;
    }
    else
    {   // ��˿���˶���ʱһ��ʱ�����˶���
	    if ( ++MC_MotContrGetSysFlag()->M101_Stage > MC_CoreGetSysFlag()->OutSilkMotionDelay ) 
        {
            MC_MotContrGetSysFlag()->M101_Stage = 0;

            return MC_TRUE;
        }
    }

    return MC_FALSE;
}

static MC_BOOL MC_CodeM103Exec(MC_CODE_FORMAT* pFormat)
{
    MC_MotContrM103();
    MC_CodeSysFlag.InterposeMotionStopOutSilk = MC_FALSE;

    return MC_TRUE;
}

static MC_BOOL MC_CodeM104Exec(MC_CODE_FORMAT* pFormat)
{
    if ( ((MC_M104_CODE_FORMAT*)pFormat)->HeadId )
    {
        if ( MC_CLEAR_MODULE_HIGH == MC_CoreGetSysFlag()->HeadSpecData[((MC_M104_CODE_FORMAT*)pFormat)->HeadId].ClearModule )
        {
            if ( MC_TRUE == MC_MotContrM204_HighTempHead(((MC_M104_CODE_FORMAT*)pFormat)->HeadId) )
            {
                MC_ComUdcsGetFlag()->ClearHeadFinish = MC_TRUE;
                
                return MC_TRUE;
            }
        }
        else if ( MC_CLEAR_MODULE_LOW == MC_CoreGetSysFlag()->HeadSpecData[((MC_M104_CODE_FORMAT*)pFormat)->HeadId].ClearModule )
        {
            if ( MC_TRUE == MC_MotContrM204_LowTempHead(((MC_M104_CODE_FORMAT*)pFormat)->HeadId) )
            {
                MC_ComUdcsGetFlag()->ClearHeadFinish = MC_TRUE;

                return MC_TRUE;
            }
        }
        else
            return MC_TRUE;

        return MC_FALSE;
    }
    else
        return MC_TRUE;
}

static MC_BOOL MC_CodeM106Exec(void)
{
    switch ( MC_MotContrGetSysFlag()->M106_Stage )
    {           // ����ָ��ģʽ�½�����ֱ���˶���
        case 0: MC_CodeSysFlag.InVectModeLinearMotion = MC_TRUE; 

                // ʹ�ô�ӡ�ָ��˶������������ص�֮ǰ��ӡλ�á�
                if ( MC_TRUE == MC_MotContrM06() )
                    MC_MotContrGetSysFlag()->M106_Stage ++;
                break;
                
                // ����ָ��ģʽ���˳���ֱ���˶���
        case 1: MC_CodeSysFlag.InVectModeLinearMotion = MC_FALSE;
                
                if ( MC_TRUE == MC_CodeRecoverOutSilk() )
                    MC_MotContrGetSysFlag()->M106_Stage ++;
                break;

        default:
            break;
    }

    if ( 2 == MC_MotContrGetSysFlag()->M106_Stage )
    {
        MC_MotContrGetSysFlag()->M106_Stage = 0;

        return MC_TRUE;
    }
    else
        return MC_FALSE;
}

MC_BOOL MC_CodeQueueCodeExec(void)
{
    MC_BOOL waitFlag = MC_TRUE;

    if ( MC_QueueCodeBufTail != MC_QueueCodeBufHead )
    {
	    if ( MC_CodeGetQueueCodeNum() && (MC_FALSE == MC_CodeGetSysFlag()->InterposeMotionStop) )
	    {
            if ( MC_FALSE == MC_CodeSysFlag.VectMotionRecover )
            {
			    MC_CODE_FORMAT* pFormat = &MC_QueueCodeBuf[MC_QueueCodeBufTail].CodeFromat;
			    MC_U8*		    pCodeId = (MC_U8 *)(&MC_QueueCodeBuf[MC_QueueCodeBufTail].CodeId);
			    MC_U16	        codeId  = MC_CodeTwoByteToTrueValue(*pCodeId, *(pCodeId + 1));
			    MC_BOOL         excFlag = MC_TRUE;

                MC_CoreGetSysFlag()->LoadHeadEnable = MC_FALSE; // ִ�ж���ָ��֮ǰ�Ƚ�ֹװ����ͷ����M305�л�ʹ�ܡ�

			    if ( 'G' == MC_QueueCodeBuf[MC_QueueCodeBufTail].CodeType )
			    {
                    if ( MC_TRUE == MC_CodeGetSysFlag()->EnterVectMode )
                    {
				        switch ( codeId )
				        {
					        case   1: MC_CodeGetG01FromCodeFormat(pFormat);
							          MC_MotContrG01((MC_G01_CODE_FORMAT*)pFormat);
							          break;

					        case   2: MC_CodeGetG02FromCodeFormat(pFormat);
							          MC_MotContrG02((MC_G02_CODE_FORMAT*)pFormat);
							          break;

					        case   3: MC_CodeGetG03FromCodeFormat(pFormat);
							          MC_MotContrG03((MC_G03_CODE_FORMAT*)pFormat);
							          break;

					        default:
						        break;
				        }
                    }
                    else
                    {
                        if ( MC_TRUE == MC_MotContrAllAxisStop() && !MC_MotContrIfHomeMoving() )
                            MC_MotContrEnterVectMove();

                        excFlag = MC_FALSE;
                    }
			    }
			    else if ( 'M' == MC_QueueCodeBuf[MC_QueueCodeBufTail].CodeType )
			    {
                    // Ŀǰ����ָ���е�Mָ�����Ҫ����ֱ���˶�����Ҫ�ȴ�ֱ���˶���ɲ��ܽ�����Ӧ�Ĳ�����
			        MC_MotContrExitVectMove();

					if ( (MC_MotContrGetEmptyBufNum() != MC_MotContrGetSysFlag()->MotTotalBuffNum) ||
						(MC_TRUE != MC_MotContrAllAxisStop()) || MC_MotContrIfHomeMoving() )
					{
						excFlag = MC_FALSE;
					}
                    else
                    {
                        switch ( codeId )
                        {
                            case 4:   excFlag = MC_CodeM04Exec();         break;
                            case 6:   excFlag = MC_CodeM06Exec(pFormat);  break;
                            case 101: excFlag = MC_CodeM101Exec(pFormat); break;
                            case 103: excFlag = MC_CodeM103Exec(pFormat); break;
                            case 104: excFlag = MC_CodeM104Exec(pFormat); break;
                            case 106: excFlag = MC_CodeM106Exec();        break;

                            default: break;
                        }
                    }
			    }
			    else
			    {
				    __mc_assert(0 && "The type of the recieved queue-code should't be neither 'G' or 'M' ");
			    }

			    if ( excFlag )
			    {
                    // ���յ�ֹͣ��ӡ֮�󣬲�����ִ�иò��衣
                    if ( 4 != codeId )
                    {
				        MC_CodeSysFlag.QueueCodeNum --; /* A queue code is executed */

				        if ( ++MC_QueueCodeBufTail >= MC_QUEUE_CODE_BUF_NUM )
					        MC_QueueCodeBufTail = 0;
                    }
			    }
                else
                    waitFlag = MC_FALSE;
		    }
        }
	}

    return waitFlag;
}

static MC_BOOL MC_CodeG90Exec(MC_CODE_FORMAT* pFormat)
{
	if ( 0 == MC_MotContrGetSysFlag()->G90_Stage1 )
	{
		MC_CodeGetG90FromCodeFormat(pFormat);
		MC_MotContrGetSysFlag()->G90_Stage1 = 1;
	}

	if ( MC_TRUE == MC_MotContrG90((MC_G90_CODE_FORMAT*)pFormat) )
    {
		MC_MotContrGetSysFlag()->G90_Stage1 = 0;
        MC_ComUdcsGetFlag()->ReturnHomeFinish = MC_TRUE;
        MC_CodeSysFlag.InterposeMotionStopHasLinearMotion = MC_TRUE; //�������ָ����֮ͣ�󣬽����˻����˶�����ָ���ӡ��ִ�лָ��˶�������

        return MC_TRUE;
    }

    return MC_FALSE;
}

static MC_BOOL MC_CodeG100Exec(MC_CODE_FORMAT* pFormat)
{
    if ( !MC_CodeSysFlag.ExecuteLineMove )
    {
        MC_CodeSysFlag.ExecuteLineMove = MC_TRUE; // ��ǵ�ǰִ����ֱ���˶�ָ�

        // ���ֱ���˶�����ͣ������Ե�ֱ���˶�ָ�
        if ( MC_FALSE == MC_CodeSysFlag.LinearMotionStop )
        {   
            MC_CodeGetG100FromCodeFormat(pFormat);

		    if ( MC_TRUE == MC_MotContrG100((MC_G100_CODE_FORMAT*)pFormat) )
            {
                MC_MotContrGetSysFlag()->M204_StageLowTempHead  = 0; // ���������ֱ���˶���������ͷ������½��С�
                MC_MotContrGetSysFlag()->M204_StageHighTempHead = 0; // ���������ֱ���˶���������ͷ������½��С�
                MC_MotContrGetSysFlag()->M205_Stage2 = 0; // ���������ֱ���˶���ƽ̨������½��С�
                MC_MotContrGetSysFlag()->M207_Stage = 0;  // ���������ֱ���˶�����Z��Ե��˶�������������ִ�С�
                MC_MotContrGetSysFlag()->M303_Stage = 0;  // ���������ֱ���˶������ӡ�ָ��˶�������������ִ�С�
                MC_CodeSysFlag.InterposeMotionStopHasLinearMotion = MC_TRUE; //�������ָ����֮ͣ�󣬽�����ֱ���˶�����ָ���ӡ��ִ�лָ��˶�������
            }
        }
    }
    else
        return MC_FALSE;

    return MC_TRUE;
}

static MC_BOOL MC_CodeG101Exec(MC_CODE_FORMAT* pFormat)
{
    if ( !MC_CodeSysFlag.ExecuteLineMove )
    {
        MC_CodeSysFlag.ExecuteLineMove = MC_TRUE; // ��ǵ�ǰִ����ֱ���˶�ָ�

        // ���ֱ���˶�����ͣ������Ե�ֱ���˶�ָ�
        if ( MC_FALSE == MC_CodeSysFlag.LinearMotionStop )
        {   
            MC_CodeGetG101FromCodeFormat(pFormat);

		    if ( MC_TRUE == MC_MotContrG101((MC_G101_CODE_FORMAT*)pFormat) )
            {
                MC_MotContrGetSysFlag()->M204_StageLowTempHead  = 0; // ���������ֱ���˶���������ͷ������½��С�
                MC_MotContrGetSysFlag()->M204_StageHighTempHead = 0; // ���������ֱ���˶���������ͷ������½��С�
                MC_MotContrGetSysFlag()->M205_Stage2 = 0; // ���������ֱ���˶���ƽ̨������½��С�
                MC_MotContrGetSysFlag()->M207_Stage  = 0; // ���������ֱ���˶�����Z��Ե��˶�������������ִ�С�
                MC_MotContrGetSysFlag()->M303_Stage  = 0; // ���������ֱ���˶������ӡ�ָ��˶�������������ִ�С�
                MC_CodeSysFlag.InterposeMotionStopHasLinearMotion = MC_TRUE; //�������ָ����֮ͣ�󣬽�����ֱ���˶�����ָ���ӡ��ִ�лָ��˶�������
            }
        }
    }
    else
        return MC_FALSE;

    return MC_TRUE;
}

static MC_BOOL MC_CodeM204Exec(MC_CODE_FORMAT* pFormat)
{
    // ���ֱ���˶�����ͣ������Ե�ֱ���˶�ָ�
    if ( MC_FALSE == MC_CodeSysFlag.LinearMotionStop )
    {
        if ( MC_CLEAR_MODULE_HIGH == MC_CoreGetSysFlag()->HeadSpecData[((MC_M204_CODE_FORMAT*)pFormat)->HeadId].ClearModule )
        {
            if ( MC_TRUE == MC_MotContrM204_HighTempHead(((MC_M204_CODE_FORMAT*)pFormat)->HeadId) )
            {
                MC_ComUdcsGetFlag()->ClearHeadFinish = MC_TRUE;
                MC_CodeSysFlag.InterposeMotionStopHasLinearMotion = MC_TRUE; //�������ָ����֮ͣ�󣬽�������ͷ����˶�����ָ���ӡ��ִ�лָ��˶�������

                return MC_TRUE;
            }
        }
        else if ( MC_CLEAR_MODULE_LOW == MC_CoreGetSysFlag()->HeadSpecData[((MC_M204_CODE_FORMAT*)pFormat)->HeadId].ClearModule )
        {
            if ( MC_TRUE == MC_MotContrM204_LowTempHead(((MC_M204_CODE_FORMAT*)pFormat)->HeadId) )
            {
                MC_ComUdcsGetFlag()->ClearHeadFinish = MC_TRUE;
                MC_CodeSysFlag.InterposeMotionStopHasLinearMotion = MC_TRUE; //�������ָ����֮ͣ�󣬽�������ͷ����˶�����ָ���ӡ��ִ�лָ��˶�������
                
                return MC_TRUE;
            }
        }
        else
            return MC_TRUE;

        return MC_FALSE;
    }
    else
        return MC_TRUE;
}

static MC_BOOL MC_CodeM205Exec(MC_CODE_FORMAT* pFormat)
{
    // ���ֱ���˶�����ͣ������Ե�ֱ���˶�ָ�
    if ( MC_FALSE == MC_CodeSysFlag.LinearMotionStop )
    {  
        if ( 0 == MC_MotContrGetSysFlag()->M205_Stage1 )
        {
            MC_MotContrGetSysFlag()->M205_Stage1 = 1;
            MC_CodeGetM205FromCodeFormat(pFormat);
        }
                                    
        if ( MC_TRUE == MC_MotContrM205((MC_M205_CODE_FORMAT*)pFormat) )
        {
            MC_MotContrGetSysFlag()->M205_Stage1 = 0;
            MC_ComUdcsGetFlag()->MeasurePlatformHeightFinish = MC_TRUE;
            MC_CodeSysFlag.InterposeMotionStopHasLinearMotion = MC_TRUE; //�������ָ����֮ͣ�󣬽�����ƽ̨��ƽ�˶�����ָ���ӡ��ִ�лָ��˶�������

            return MC_TRUE;
        }
    }
    else
        return MC_TRUE;

    return MC_FALSE;
}

static MC_BOOL MC_CodeM207Exec(MC_CODE_FORMAT* pFormat)
{
    // ���ֱ���˶�����ͣ������Ե�ֱ���˶�ָ�
    if ( MC_FALSE == MC_CodeSysFlag.LinearMotionStop )
    { 
        if ( MC_TRUE == MC_MotContrM207((CONST MC_M207_CODE_FORMAT*)pFormat) )
        {
            // ���Z��Ե���ɡ�
            MC_ComUdcsGetFlag()->AdjZ_HeadHeightFinish = MC_TRUE;
            MC_CodeSysFlag.InterposeMotionStopHasLinearMotion = MC_TRUE; //�������ָ����֮ͣ�󣬽�����Z��Ե��˶�����ָ���ӡ��ִ�лָ��˶�������

            return MC_TRUE;
        }
    }
    else
        return MC_TRUE;

    return MC_FALSE;
}

static MC_BOOL MC_CodeM209Exec(MC_CODE_FORMAT* pFormat)
{
    if ( MC_FALSE == MC_CodeSysFlag.LinearMotionStop )
    { 
        if ( MC_TRUE == MC_MotContrM209(((CONST MC_M207_CODE_FORMAT*)pFormat)->NowHead) )
        {
            MC_ComUdcsGetFlag()->AdjZ_PlatformAndSensorHeightFinish = MC_TRUE; // ��Ǵ������Ըߺ�ƽ̨�Ը���ɡ�
            MC_CodeSysFlag.InterposeMotionStopHasLinearMotion = MC_TRUE; //�������ָ����֮ͣ�󣬽����˴�������ߺ�ƽ̨����˶�����ָ���ӡ��ִ�лָ��˶�������

            return MC_TRUE;
        }
    }
    else
        return MC_TRUE;

    return MC_FALSE;
}

static MC_BOOL MC_CodeM210Exec(void)
{
    return MC_MotContrM210();
}

static MC_BOOL MC_CodeM303Exec(MC_CODE_FORMAT* pFormat)
{
    if ( MC_TRUE == MC_CodeSysFlag.InterposeMotionStop )
    {
        // ��ͣ��ӡ֮���ڻָ��Ĺ���֮�У��ַ�������ͣ��
        if ( MC_TRUE == MC_CodeSysFlag.InterposeMotionStopRecoverStop )
        {
            MC_MotContrGetSysFlag()->LockMotContrM303 = MC_FALSE;
            MC_MotContrGetSysFlag()->LockOutSilk      = MC_TRUE;

            MC_CodeSysFlag.InterposeMotionStopRecover     = MC_FALSE; // �ָ���ɡ�
            MC_CodeSysFlag.InterposeMotionStopRecoverStop = MC_FALSE; // ������ͣ��ӡ���ָ������У��ַ�����ͣ������

            return MC_TRUE; // �����ָ�ָ���ָͣ��Ϊ����ָ��ж��˻ָ�ָ�����ָͣ��ִ�����֮�󣬻�����ִ��ʣ��ָ�ָ�����Ӧ�ý�����
        }
        else
        {
            MC_CodeSysFlag.InterposeMotionStopRecover = MC_TRUE; // �ڻָ�����֮�б���λ��

            if ( MC_FALSE == MC_MotContrGetSysFlag()->LockMotContrM303 )
            {
                // ����ڲ岹ģʽ�½�����ֱ�߻�����˶�����ִ���˶��ָ�������
                if ( MC_TRUE == MC_CodeSysFlag.InterposeMotionStopHasLinearMotion )
                {
                    if ( MC_TRUE == MC_MotContrM303() )
                        MC_MotContrGetSysFlag()->LockOutSilk = MC_FALSE;
                }
                else
                    MC_MotContrGetSysFlag()->LockOutSilk = MC_FALSE;
            }

            if ( MC_FALSE == MC_MotContrGetSysFlag()->LockOutSilk )
            {
                MC_MotContrGetSysFlag()->LockMotContrM303 = MC_TRUE;

                if ( MC_TRUE == MC_CodeRecoverOutSilk() ) // �ָ�֮ǰ��˿״̬��
                {
                    MC_MotContrGetSysFlag()->LockMotContrM303 = MC_FALSE;
                    MC_MotContrGetSysFlag()->LockOutSilk      = MC_TRUE;

                    {
                        MC_C8 testDataBuf[1000] = {0};

                        sprintf_s(testDataBuf, 1000, "Recover Print:\r\nThe InterposeMotionFirstStop is %d\r\n", MC_CodeSysFlag.InterposeMotionFirstStop);
                        MC_CoreOutputTestData(testDataBuf);
                    }

                    MC_CodeSysFlag.InterposeMotionFirstStop   = 0; // �ָ���ɣ���¼��һ����ͣ���������㡣
                    MC_CodeSysFlag.InterposeMotionStop        = MC_FALSE;
                    MC_CodeSysFlag.InterposeMotionStopFinish  = MC_TRUE;

                    MC_CodeSysFlag.InterposeMotionStopRecover = MC_FALSE; // �ָ���ɱ����㡣

                    return MC_TRUE;
                }
            }

            return MC_FALSE;
        }
    }
    else
        return MC_TRUE;
}

static MC_BOOL MC_CodeM304Exec(MC_CODE_FORMAT* pFormat)
{
    // ���ֱ���˶�����ͣ������Ե�ֱ���˶�ָ�
    if ( MC_FALSE == MC_CodeSysFlag.LinearMotionStop )
    {
        if ( 0 == MC_MotContrGetSysFlag()->M304_Stage1 )
        {
            MC_MotContrGetSysFlag()->M304_Stage1 = 1;
            MC_CodeGetM304FromCodeFormat(pFormat);
        }
        
        MC_ComUdcsGetFlag()->FastSwitchHeadStart = MC_TRUE;

        if ( MC_TRUE == MC_MotContrM304((MC_M304_CODE_FORMAT*)pFormat) )
        {
            MC_MotContrGetSysFlag()->M304_Stage1 = 0;
            MC_ComUdcsGetFlag()->FastSwitchHeadFinish = MC_TRUE;
            MC_CodeSysFlag.InterposeMotionStopHasLinearMotion = MC_TRUE; //�������ָ����֮ͣ�󣬽�������ͷ�л��˶�����ָ���ӡ��ִ�лָ��˶�������

            return MC_TRUE;
        }
    }
    else
        return MC_TRUE;

    return MC_FALSE;
}

static MC_BOOL MC_CodeM305Exec(MC_CODE_FORMAT* pFormat)
{
    // ���ֱ���˶�����ͣ������Ե�ֱ���˶�ָ�
    if ( MC_FALSE == MC_CodeSysFlag.LinearMotionStop )
    {
        if ( 0 == MC_MotContrGetSysFlag()->M305_Stage1 )
        {
            MC_MotContrGetSysFlag()->M305_Stage1 = 1;
            MC_CodeGetM304FromCodeFormat(pFormat);
        }

        // ֱ��ͨ��M304 ץȡĿ����ͷ��
        if ( 1 == MC_MotContrGetSysFlag()->M305_Stage1 )
        {
            if ( MC_TRUE == MC_MotContrM304((MC_M304_CODE_FORMAT*)pFormat) )
                MC_MotContrGetSysFlag()->M305_Stage1 = 2;
        }
        else if ( MC_TRUE == MC_MotContrM305() )
        {
            MC_MotContrGetSysFlag()->M305_Stage1 = 0;
            MC_CoreGetSysFlag()->LoadHeadEnable = MC_TRUE; // ʹ����ͷװ��ָ�
            MC_ComUdcsGetFlag()->AddHeadFinish = MC_TRUE; // ��Ϊ��ͷ������ɱ�־��
            MC_CodeSysFlag.InterposeMotionStopHasLinearMotion = MC_TRUE; //�������ָ����֮ͣ�󣬽�������ͷװ���˶�����ָ���ӡ��ִ�лָ��˶�������

            return MC_TRUE;
        }
    }
    else
        return MC_TRUE;

    return MC_FALSE;
}

static MC_BOOL MC_CodeM307Exec(MC_CODE_FORMAT* pFormat)
{
    MC_MotContrElectromagnetDegaussing(((MC_M307_CODE_FORMAT*)pFormat)->HeadId);

    return MC_TRUE;
}

static MC_BOOL MC_CodeM308Exec(void)
{
    MC_MotContrElectromagnetRecover();

    return MC_TRUE;
}

void MC_CodeFastCodeExec(void)
{
	if ( MC_CodeGetFastCodeNum() )
	{
        if ( MC_FastCodeBufTail != MC_FastCodeBufHead )
        {
            MC_U8 excFlag = MC_TRUE;

            MC_MotContrExitVectMove();

			if ( (MC_TRUE == MC_MotContrAllAxisStop()) && !MC_MotContrIfHomeMoving() )
			{
				MC_CODE_FORMAT* pFormat = &MC_FastCodeBuf[MC_FastCodeBufTail].CodeFromat;
				MC_U8*		    pCodeId = (MC_U8 *)(&MC_FastCodeBuf[MC_FastCodeBufTail].CodeId);
				MC_U16		    codeId  = MC_CodeTwoByteToTrueValue(*pCodeId, *(pCodeId + 1));

                MC_CoreGetSysFlag()->LoadHeadEnable = MC_FALSE; // ִ�п���ָ��֮ǰ�Ƚ�ֹװ����ͷ����M305�л�ʹ�ܡ�

				if ( 'G' == MC_FastCodeBuf[MC_FastCodeBufTail].CodeType )
				{
					switch ( codeId )
					{
						case  90: excFlag = MC_CodeG90Exec(pFormat);  break;
						case 100: excFlag = MC_CodeG100Exec(pFormat); break;
                        case 101: excFlag = MC_CodeG101Exec(pFormat); break;

						default:
							break;
					}
				}
				else if ( 'M' == MC_FastCodeBuf[MC_FastCodeBufTail].CodeType )
				{
					switch ( codeId )
					{
                        case 204: excFlag = MC_CodeM204Exec(pFormat); break;
                        case 205: excFlag = MC_CodeM205Exec(pFormat); break;
                        case 207: excFlag = MC_CodeM207Exec(pFormat); break;
						case 209: excFlag = MC_CodeM209Exec(pFormat); break;
                        case 210: excFlag = MC_CodeM210Exec();        break;
                        case 303: excFlag = MC_CodeM303Exec(pFormat); break;
                        case 304: excFlag = MC_CodeM304Exec(pFormat); break;
                        case 305: excFlag = MC_CodeM305Exec(pFormat); break;

						default:
							break;
					}
				}
				else
				{
					__mc_assert(0 && "The type of the recieved fast-code should't be neither 'G' or 'M' ");
				}
			}
            else
                excFlag = MC_FALSE;
            
            if ( excFlag )
            {
                MC_CodeSysFlag.FastCodeNum --; /* A fast code is executed */

                if ( ++MC_FastCodeBufTail >= MC_FAST_CODE_BUF_NUM )
                    MC_FastCodeBufTail = 0;
            }
        }
	}
}

void MC_CodeSuperCodeExec(void)
{
	if ( MC_CodeGetSuperCodeNum() )
	{
		if ( MC_SuperCodeBufTail != MC_SuperCodeBufHead )
		{
			MC_CODE_FORMAT* pFormat = &MC_SuperCodeBuf[MC_SuperCodeBufTail].CodeFromat;
			MC_U8*		    pCodeId = (MC_U8 *)(&MC_SuperCodeBuf[MC_SuperCodeBufTail].CodeId);
			MC_U16		    codeId  = MC_CodeTwoByteToTrueValue(*pCodeId, *(pCodeId + 1));
			MC_U8           excFlag = MC_TRUE;

			if ( 'G' == MC_SuperCodeBuf[MC_SuperCodeBufTail].CodeType )
			{
				switch ( codeId )
				{             // �ڷǲ岹�˶��У�һ��ֱ���˶����֮��Ż���������ͣ���������Ǽ�Ȼ�յ���ֱ���˶���ָͣ����������
                              // ֱ���˶������ɽ��С�����ڶ���ָ���У�������ֱ���˶��������ָ���ֱ���˶��ճ����С�
                    case  4:  if ( (MC_FALSE == MC_CodeGetSysFlag()->EnterVectMode) && (MC_FALSE == MC_CodeSysFlag.InVectModeLinearMotion) )
                              {
                                  MC_MotContrExitVectMove();
                                  MC_MotContrG04();
                                  MC_CodeFastCodeClear(); // ��տ���ָ��塣
                                  MC_MotContrClearAllStateVariable(); // ��ʼ������ȫ�ֹ��̿��Ʊ�־������

                                  // ֱ���˶�ģʽ�£���ֱͣ���˶�֮��ֱ���˶�ֹͣ��ɱ�־����Ϊfalse����ϵͳ����ȴ�ֱ
                                  // ���˶�ֹͣ״̬��
                                  MC_CodeSysFlag.LinearMotionStopFinish = MC_FALSE;
                              }

							  MC_CodeSysFlag.LinearMotionStop = MC_TRUE;
							  break;

					case  5:  MC_MotContrG05();
							  MC_CodeSysFlag.LinearMotionStop = MC_FALSE;
							  break;

					default:
						break;
				}
			}
			else if ( 'M' == MC_SuperCodeBuf[MC_SuperCodeBufTail].CodeType )
			{
				switch ( codeId )
				{
                    case 2:   excFlag = MC_CodeM02Exec();  // ֹͣ��ӡ��
                              break;
                              
                    case 201: MC_MotContrM101(); // ��������
							  break;

                    case 202: MC_MotContrM202(); // ��ס���졣
                              break;

                    case 203: MC_MotContrM103(); // ��������
							  break;

                    case 206: MC_CodeGetM206FromCodeFormat(pFormat);
                              MC_MotContrM206((MC_M206_CODE_FORMAT*)pFormat);
                              MC_CodeSysFlag.HasGetM206 = MC_TRUE;
							  break;

                    case 211: MC_CodeGetM211FromCodeFormat(pFormat);
                              MC_MotContrM211((MC_M211_CODE_FORMAT*)pFormat);
							  break;

                    case 301: MC_MotContrM301((MC_M301_CODE_FORMAT*)pFormat);
                              break;

					case 302: MC_MotContrExitVectMove();
							  MC_CodeSysFlag.InterposeMotionStop = MC_TRUE;
							  MC_CodeSysFlag.InterposeMotionStopFinish = MC_FALSE;

                              // ֮ǰû�н��й���ͣ��ӡ��������֮ͣ����ȫ�ָ������־��ǰ״̬����ͣ״̬��
                              if ( 0 == MC_CodeSysFlag.InterposeMotionFirstStop )
                                  MC_CodeSysFlag.InterposeMotionFirstStop = 1;

                              //����ͣ��ӡ֮�󣬻ָ��Ĺ����У�����ͣ���ñ�־��λ�����ڽ���ָ�����֮����ͣ��������ͣ��BUG��
                              if (MC_TRUE == MC_CodeSysFlag.InterposeMotionStopRecover)
                              {
                                  MC_CodeSysFlag.InterposeMotionStopRecoverStop = MC_TRUE;
                                  MC_MotContrGetSysFlag()->M303_Stage = 0;
                              }
                              else //�����һ����֮ͣ�󣬻ָ������з�����ֱ���˶���δ��ȫ�ָ�������ͣ����������ñ�־��
                                  MC_CodeSysFlag.InterposeMotionStopHasLinearMotion = MC_FALSE;
							  break;

                    case 307: excFlag = MC_CodeM307Exec(pFormat); break;
                    case 308: excFlag = MC_CodeM308Exec();        break;

					default:
						break;
				}
			}
			else
			{
				__mc_assert(0 && "The type of the recieved Super-code should't be neither 'G' or 'M' ");
			}

			if ( excFlag )
			{
                // ���յ�ֹͣ��ӡ֮�󣬲�����ִ�иò��衣
                if ( 2 != codeId )
                {
				    MC_CodeSysFlag.SuperCodeNum --; /* A Super code is executed */

				    if ( ++MC_SuperCodeBufTail >= MC_SUPER_CODE_BUF_NUM )
					    MC_SuperCodeBufTail = 0;
                }
			}
		}
	}
}
