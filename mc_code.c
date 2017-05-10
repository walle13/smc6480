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

        MC_MotContrGetSysFlag()->RecoverOutSilkStage = MC_MOT_OUT_AIR_PLUG_DELAY; // 气压封堵器推出延时。
    }

    if ( MC_MotContrGetSysFlag()->RecoverOutSilkStage ? !(--MC_MotContrGetSysFlag()->RecoverOutSilkStage) : MC_TRUE )
    {
        if ( MC_TRUE == MC_CodeSysFlag.InterposeMotionStopOutSilk )
        {
            if ( 0 == MC_MotContrGetSysFlag()->RecoverOutSilkDelay )
            {
                MC_MotContrGetSysFlag()->RecoverOutSilkDelay = 1;
                MC_MotContrM101(); // 恢复出丝。
            }
            else
            {   // 出丝后运动延时一段时间再运动。
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
    // 收到停止打印指令之后，先关闭气阀，并退出插补模式。
    MC_MotContrM103();         // 关气阀。
    MC_MotContrStopVectMove(); // 停止插补，清空缓存。
    MC_MotContrExitVectMove(); // 退出插补模式。
    MC_MotContrM02();          // 轴立即停止。

    MC_CodeAllCodeClear();     // 清空插补队列。
    MC_MotContrClearAllCoordVariable(); // 初始化所有坐标变量。
    MC_MotContrClearAllStateVariable(); // 初始化所有全局过程控制标志变量。
    MC_CodeSysFlag.PrintEndStopFinish = MC_FALSE;

    MC_CoreOutputTestData("M02\r\n");

    return MC_TRUE;
}

static MC_BOOL MC_CodeM04Exec(void)
{
    MC_G90_CODE_FORMAT G90_Para;

    G90_Para.MoveSpeed = MC_CODE_COORD_NULL;

    // 收到停止打印指令之后，先关闭气阀，并退出插补模式。
    if ( 0 == MC_MotContrGetSysFlag()->M04_Stage )
    {
        MC_MotContrM103();         // 关气阀。
        MC_MotContrStopVectMove(); // 停止插补，清空缓存。
        MC_MotContrExitVectMove(); // 退出插补模式。

        MC_MotContrGetSysFlag()->M04_Stage = 1; // 进入下一个阶段。
    }    // 接着回零。
    else if ( 1 == MC_MotContrGetSysFlag()->M04_Stage )
    {
	    if ( (MC_TRUE == MC_MotContrAllAxisStop()) && !MC_MotContrIfHomeMoving() )
	    {
            if ( MC_TRUE == MC_MotContrG90(&G90_Para) )
                MC_MotContrGetSysFlag()->M04_Stage = 2; // 进入下一个阶段。
        }
    }
    else
    {
        MC_MotContrGetSysFlag()->M04_Stage = 0; // 指令流程标志复位。

        MC_MotContrM04();
        MC_CodeAllCodeClear(); // 清空插补队列。
        MC_MotContrClearAllCoordVariable(); // 初始化所有坐标变量。
        MC_MotContrClearAllStateVariable(); // 初始化所有全局过程控制标志变量。
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

                // 队列指令模式下进入了直线运动。
        case 1: MC_CodeSysFlag.InVectModeLinearMotion = MC_TRUE;
                
                // 直接调用快速指令M304的喷头切换动作函数。
                if ( MC_TRUE == MC_MotContrM304((MC_M304_CODE_FORMAT*)pFormat) )
                    MC_MotContrGetSysFlag()->M06_Stage1 ++;

                break;

                // 此时喷头切换完成,置位队列指令，喷头切换完成标志。
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
    {   // 出丝后运动延时一段时间再运动。
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
    {           // 队列指令模式下进入了直线运动。
        case 0: MC_CodeSysFlag.InVectModeLinearMotion = MC_TRUE; 

                // 使用打印恢复运动操作函数，回到之前打印位置。
                if ( MC_TRUE == MC_MotContrM06() )
                    MC_MotContrGetSysFlag()->M106_Stage ++;
                break;
                
                // 队列指令模式下退出了直线运动。
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

                MC_CoreGetSysFlag()->LoadHeadEnable = MC_FALSE; // 执行队列指令之前先禁止装载喷头，在M305中会使能。

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
                    // 目前队列指令中的M指令均需要进行直线运动，需要等待直线运动完成才能进行相应的操作。
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
                    // 当收到停止打印之后，不能再执行该步骤。
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
        MC_CodeSysFlag.InterposeMotionStopHasLinearMotion = MC_TRUE; //如果队列指令暂停之后，进行了回零运动，则恢复打印会执行恢复运动操作。

        return MC_TRUE;
    }

    return MC_FALSE;
}

static MC_BOOL MC_CodeG100Exec(MC_CODE_FORMAT* pFormat)
{
    if ( !MC_CodeSysFlag.ExecuteLineMove )
    {
        MC_CodeSysFlag.ExecuteLineMove = MC_TRUE; // 标记当前执行了直线运动指令。

        // 如果直线运动被暂停，则忽略掉直线运动指令。
        if ( MC_FALSE == MC_CodeSysFlag.LinearMotionStop )
        {   
            MC_CodeGetG100FromCodeFormat(pFormat);

		    if ( MC_TRUE == MC_MotContrG100((MC_G100_CODE_FORMAT*)pFormat) )
            {
                MC_MotContrGetSysFlag()->M204_StageLowTempHead  = 0; // 如果进行了直线运动，低温喷头清洁重新进行。
                MC_MotContrGetSysFlag()->M204_StageHighTempHead = 0; // 如果进行了直线运动，高温喷头清洁重新进行。
                MC_MotContrGetSysFlag()->M205_Stage2 = 0; // 如果进行了直线运动，平台测高重新进行。
                MC_MotContrGetSysFlag()->M207_Stage = 0;  // 如果进行了直线运动，则Z轴对刀运动操作将被重新执行。
                MC_MotContrGetSysFlag()->M303_Stage = 0;  // 如果进行了直线运动，则打印恢复运动操作将被重新执行。
                MC_CodeSysFlag.InterposeMotionStopHasLinearMotion = MC_TRUE; //如果队列指令暂停之后，进行了直线运动，则恢复打印会执行恢复运动操作。
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
        MC_CodeSysFlag.ExecuteLineMove = MC_TRUE; // 标记当前执行了直线运动指令。

        // 如果直线运动被暂停，则忽略掉直线运动指令。
        if ( MC_FALSE == MC_CodeSysFlag.LinearMotionStop )
        {   
            MC_CodeGetG101FromCodeFormat(pFormat);

		    if ( MC_TRUE == MC_MotContrG101((MC_G101_CODE_FORMAT*)pFormat) )
            {
                MC_MotContrGetSysFlag()->M204_StageLowTempHead  = 0; // 如果进行了直线运动，低温喷头清洁重新进行。
                MC_MotContrGetSysFlag()->M204_StageHighTempHead = 0; // 如果进行了直线运动，高温喷头清洁重新进行。
                MC_MotContrGetSysFlag()->M205_Stage2 = 0; // 如果进行了直线运动，平台测高重新进行。
                MC_MotContrGetSysFlag()->M207_Stage  = 0; // 如果进行了直线运动，则Z轴对刀运动操作将被重新执行。
                MC_MotContrGetSysFlag()->M303_Stage  = 0; // 如果进行了直线运动，则打印恢复运动操作将被重新执行。
                MC_CodeSysFlag.InterposeMotionStopHasLinearMotion = MC_TRUE; //如果队列指令暂停之后，进行了直线运动，则恢复打印会执行恢复运动操作。
            }
        }
    }
    else
        return MC_FALSE;

    return MC_TRUE;
}

static MC_BOOL MC_CodeM204Exec(MC_CODE_FORMAT* pFormat)
{
    // 如果直线运动被暂停，则忽略掉直线运动指令。
    if ( MC_FALSE == MC_CodeSysFlag.LinearMotionStop )
    {
        if ( MC_CLEAR_MODULE_HIGH == MC_CoreGetSysFlag()->HeadSpecData[((MC_M204_CODE_FORMAT*)pFormat)->HeadId].ClearModule )
        {
            if ( MC_TRUE == MC_MotContrM204_HighTempHead(((MC_M204_CODE_FORMAT*)pFormat)->HeadId) )
            {
                MC_ComUdcsGetFlag()->ClearHeadFinish = MC_TRUE;
                MC_CodeSysFlag.InterposeMotionStopHasLinearMotion = MC_TRUE; //如果队列指令暂停之后，进行了喷头清洁运动，则恢复打印会执行恢复运动操作。

                return MC_TRUE;
            }
        }
        else if ( MC_CLEAR_MODULE_LOW == MC_CoreGetSysFlag()->HeadSpecData[((MC_M204_CODE_FORMAT*)pFormat)->HeadId].ClearModule )
        {
            if ( MC_TRUE == MC_MotContrM204_LowTempHead(((MC_M204_CODE_FORMAT*)pFormat)->HeadId) )
            {
                MC_ComUdcsGetFlag()->ClearHeadFinish = MC_TRUE;
                MC_CodeSysFlag.InterposeMotionStopHasLinearMotion = MC_TRUE; //如果队列指令暂停之后，进行了喷头清洁运动，则恢复打印会执行恢复运动操作。
                
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
    // 如果直线运动被暂停，则忽略掉直线运动指令。
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
            MC_CodeSysFlag.InterposeMotionStopHasLinearMotion = MC_TRUE; //如果队列指令暂停之后，进行了平台测平运动，则恢复打印会执行恢复运动操作。

            return MC_TRUE;
        }
    }
    else
        return MC_TRUE;

    return MC_FALSE;
}

static MC_BOOL MC_CodeM207Exec(MC_CODE_FORMAT* pFormat)
{
    // 如果直线运动被暂停，则忽略掉直线运动指令。
    if ( MC_FALSE == MC_CodeSysFlag.LinearMotionStop )
    { 
        if ( MC_TRUE == MC_MotContrM207((CONST MC_M207_CODE_FORMAT*)pFormat) )
        {
            // 标记Z轴对刀完成。
            MC_ComUdcsGetFlag()->AdjZ_HeadHeightFinish = MC_TRUE;
            MC_CodeSysFlag.InterposeMotionStopHasLinearMotion = MC_TRUE; //如果队列指令暂停之后，进行了Z轴对刀运动，则恢复打印会执行恢复运动操作。

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
            MC_ComUdcsGetFlag()->AdjZ_PlatformAndSensorHeightFinish = MC_TRUE; // 标记传感器对高和平台对高完成。
            MC_CodeSysFlag.InterposeMotionStopHasLinearMotion = MC_TRUE; //如果队列指令暂停之后，进行了传感器测高和平台测高运动，则恢复打印会执行恢复运动操作。

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
        // 暂停打印之后，在恢复的过程之中，又发生了暂停。
        if ( MC_TRUE == MC_CodeSysFlag.InterposeMotionStopRecoverStop )
        {
            MC_MotContrGetSysFlag()->LockMotContrM303 = MC_FALSE;
            MC_MotContrGetSysFlag()->LockOutSilk      = MC_TRUE;

            MC_CodeSysFlag.InterposeMotionStopRecover     = MC_FALSE; // 恢复完成。
            MC_CodeSysFlag.InterposeMotionStopRecoverStop = MC_FALSE; // 清零暂停打印，恢复过程中，又发生暂停变量。

            return MC_TRUE; // 结束恢复指令。暂停指令为超级指令，中断了恢复指令。但暂停指令执行完成之后，会立即执行剩余恢复指令，所以应该结束。
        }
        else
        {
            MC_CodeSysFlag.InterposeMotionStopRecover = MC_TRUE; // 在恢复过程之中被置位。

            if ( MC_FALSE == MC_MotContrGetSysFlag()->LockMotContrM303 )
            {
                // 如果在插补模式下进行了直线或回零运动，才执行运动恢复操作。
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

                if ( MC_TRUE == MC_CodeRecoverOutSilk() ) // 恢复之前出丝状态。
                {
                    MC_MotContrGetSysFlag()->LockMotContrM303 = MC_FALSE;
                    MC_MotContrGetSysFlag()->LockOutSilk      = MC_TRUE;

                    {
                        MC_C8 testDataBuf[1000] = {0};

                        sprintf_s(testDataBuf, 1000, "Recover Print:\r\nThe InterposeMotionFirstStop is %d\r\n", MC_CodeSysFlag.InterposeMotionFirstStop);
                        MC_CoreOutputTestData(testDataBuf);
                    }

                    MC_CodeSysFlag.InterposeMotionFirstStop   = 0; // 恢复完成，记录第一次暂停变量被清零。
                    MC_CodeSysFlag.InterposeMotionStop        = MC_FALSE;
                    MC_CodeSysFlag.InterposeMotionStopFinish  = MC_TRUE;

                    MC_CodeSysFlag.InterposeMotionStopRecover = MC_FALSE; // 恢复完成被清零。

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
    // 如果直线运动被暂停，则忽略掉直线运动指令。
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
            MC_CodeSysFlag.InterposeMotionStopHasLinearMotion = MC_TRUE; //如果队列指令暂停之后，进行了喷头切换运动，则恢复打印会执行恢复运动操作。

            return MC_TRUE;
        }
    }
    else
        return MC_TRUE;

    return MC_FALSE;
}

static MC_BOOL MC_CodeM305Exec(MC_CODE_FORMAT* pFormat)
{
    // 如果直线运动被暂停，则忽略掉直线运动指令。
    if ( MC_FALSE == MC_CodeSysFlag.LinearMotionStop )
    {
        if ( 0 == MC_MotContrGetSysFlag()->M305_Stage1 )
        {
            MC_MotContrGetSysFlag()->M305_Stage1 = 1;
            MC_CodeGetM304FromCodeFormat(pFormat);
        }

        // 直接通过M304 抓取目标喷头。
        if ( 1 == MC_MotContrGetSysFlag()->M305_Stage1 )
        {
            if ( MC_TRUE == MC_MotContrM304((MC_M304_CODE_FORMAT*)pFormat) )
                MC_MotContrGetSysFlag()->M305_Stage1 = 2;
        }
        else if ( MC_TRUE == MC_MotContrM305() )
        {
            MC_MotContrGetSysFlag()->M305_Stage1 = 0;
            MC_CoreGetSysFlag()->LoadHeadEnable = MC_TRUE; // 使能喷头装载指令。
            MC_ComUdcsGetFlag()->AddHeadFinish = MC_TRUE; // 置为喷头加载完成标志。
            MC_CodeSysFlag.InterposeMotionStopHasLinearMotion = MC_TRUE; //如果队列指令暂停之后，进行了喷头装载运动，则恢复打印会执行恢复运动操作。

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

                MC_CoreGetSysFlag()->LoadHeadEnable = MC_FALSE; // 执行快速指令之前先禁止装载喷头，在M305中会使能。

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
				{             // 在非插补运动中，一段直线运动完成之后才会进行轴的暂停操作。但是既然收到了直线运动暂停指令，则接下来的
                              // 直线运动都不可进行。如果在队列指令中，进行了直线运动，则队列指令的直线运动照常进行。
                    case  4:  if ( (MC_FALSE == MC_CodeGetSysFlag()->EnterVectMode) && (MC_FALSE == MC_CodeSysFlag.InVectModeLinearMotion) )
                              {
                                  MC_MotContrExitVectMove();
                                  MC_MotContrG04();
                                  MC_CodeFastCodeClear(); // 清空快速指令缓冲。
                                  MC_MotContrClearAllStateVariable(); // 初始化所有全局过程控制标志变量。

                                  // 直线运动模式下，暂停直线运动之后，直线运动停止完成标志设置为false。则系统进入等待直
                                  // 线运动停止状态。
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
                    case 2:   excFlag = MC_CodeM02Exec();  // 停止打印。
                              break;
                              
                    case 201: MC_MotContrM101(); // 开气阀。
							  break;

                    case 202: MC_MotContrM202(); // 锁住气嘴。
                              break;

                    case 203: MC_MotContrM103(); // 关气阀。
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

                              // 之前没有进行过暂停打印，或者暂停之后完全恢复，则标志当前状态是暂停状态。
                              if ( 0 == MC_CodeSysFlag.InterposeMotionFirstStop )
                                  MC_CodeSysFlag.InterposeMotionFirstStop = 1;

                              //在暂停打印之后，恢复的过程中，又暂停，该标志置位。用于解决恢复过程之中暂停而不能暂停的BUG。
                              if (MC_TRUE == MC_CodeSysFlag.InterposeMotionStopRecover)
                              {
                                  MC_CodeSysFlag.InterposeMotionStopRecoverStop = MC_TRUE;
                                  MC_MotContrGetSysFlag()->M303_Stage = 0;
                              }
                              else //如果第一次暂停之后，恢复过程中发生了直线运动，未完全恢复下再暂停，则不能清除该标志。
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
                // 当收到停止打印之后，不能再执行该步骤。
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
