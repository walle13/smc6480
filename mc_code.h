#ifndef __MC_CODE_H__
#define __MC_CODE_H__

/** @brief The struct of MC_CODE_SYS_FLAG */
typedef struct
{
    MC_U32  QueueCodeNum;
    MC_U32  FastCodeNum;
	MC_U32  SuperCodeNum;
    MC_U32  LoseQueueCodeNum;
    MC_U32  LoseFastCodeNum;
    MC_U32  ToSendFrameNum;
	MC_BOOL EnterVectMode;
    MC_BOOL InVectModeLinearMotion;
    MC_BOOL InterposeMotionStopHasLinearMotion;
	MC_BOOL InterposeMotionStop;
	MC_BOOL InterposeMotionStopFinish;
	MC_U8   InterposeMotionStopOutSilk;
    MC_BOOL InterposeMotionStopRecover;       // 暂停打印之后，在恢复的过程之中置位，在恢复完成或恢复的过程中发生了暂停清零。
    MC_BOOL InterposeMotionStopRecoverStop;   // 暂停打印之后，在恢复的过程之中又发生了暂停置位，再恢复函数再次循环的之后清零。
    MC_U8   InterposeMotionFirstStop;         // 记录第一次暂停打印后置1，记录暂停后的坐标之后置2，恢复完成之后被清零。
	MC_BOOL LinearMotionStop;
    MC_BOOL LinearMotionStopFinish;
    MC_BOOL VectMotionRecover;
    MC_BOOL PrintEndStopFinish;
    MC_BOOL ExecuteLineMove;

    MC_BOOL HasGetM206;
} MC_CODE_SYS_FLAG;

#pragma pack(1) /* Set the method of memory align */

/** @brief The struct of MC_CODE_FORMAT */
typedef struct
{
    MC_U8   MC_GMI_CodeFormat[MC_CODE_FORMAT_SIZE];
} MC_CODE_FORMAT;

/** @brief The struct of MC_CODE_BUF */
typedef struct MC_CODE_BUF
{
    MC_U8           CodeType;   /** < Two commands,G-Code,M-Code */
    MC_S16          CodeId;     /** < The id of the code */
    MC_CODE_FORMAT  CodeFromat;
} MC_CODE_BUF, MC_SEND_BUF;

/** @brief The format of G01 */
typedef struct
{
    MC_S32  CoordX;
    MC_S32  CoordY;
    MC_S32  CoordZ;
    MC_S32  CoordU;
	MC_S32  MoveSpeed;
} MC_G01_CODE_FORMAT, MC_G100_CODE_FORMAT, MC_G101_CODE_FORMAT;

/** @brief The format of G02 */
typedef struct
{
    MC_S32  CoordX;
    MC_S32  CoordY;
    MC_S32  CentreX;
    MC_S32  CentreY;
    MC_S32  MoveSpeed;
} MC_G02_CODE_FORMAT;

/** @brief The format of G03 */
typedef struct
{
    MC_S32  CoordX;
    MC_S32  CoordY;
    MC_S32  CentreX;
    MC_S32  CentreY;
    MC_S32  MoveSpeed;
} MC_G03_CODE_FORMAT;

/** @brief The format of G90 */
typedef struct
{
	MC_S32  MoveSpeed;
} MC_G90_CODE_FORMAT;

/** @brief The format of M06 and M304 */
typedef struct
{
	MC_U8 NowHead;
    MC_U8 ReturnShelf;
	MC_U8 TargetHead;
    MC_U8 TargetShelf;
} MC_M06_CODE_FORMAT, MC_M304_CODE_FORMAT, MC_M305_CODE_FORMAT;

/** @brief The format of M100 */
typedef struct
{
    MC_S32  AnalogV;
} MC_M100_CODE_FORMAT;

/** @brief The format of M101 */
typedef struct
{
    MC_S16  TempHeadZ;
    MC_S16  TempHead1;
    MC_S16  TempHead2;
    MC_S16  TempHead3;
    MC_S16  TempHead4;
    MC_S16  TempPlatform;
} MC_M101_CODE_FORMAT, MC_CORE_NOW_TEMP;

///** @brief The format of M102 */
//typedef struct
//{
//    MC_S16  Request[MC_CODE_FORMAT_SIZE / 2];
//} MC_M102_CODE_FORMAT;

/** @brief The format of M103 */
typedef struct
{
    MC_U8   LockGasZ;
    MC_U8   LockHeadZ;
    MC_U8   LockHead1;
    MC_U8   LockHead2;
    MC_U8   LockHead3;
    MC_U8   LockHead4;
} MC_M103_CODE_FORMAT;

/** @brief The format of M200 */
typedef struct
{
    MC_U16  UnitPulseX;
    MC_U16  UnitPulseY;
    MC_U16  UnitPulseZ;
    MC_U16  UnitPulseU;
} MC_M200_CODE_FORMAT;

/** @brief The format of M206 */
typedef struct
{
	MC_U8 HeadId;
} MC_M104_CODE_FORMAT, MC_M204_CODE_FORMAT, MC_M307_CODE_FORMAT;

/** @brief The format of M206 */
typedef struct
{
	MC_S32 CoordX;
	MC_S32 CoordY;
} MC_M205_CODE_FORMAT;

/** @brief The format of M206 */
typedef struct
{
	MC_S32 OffsetCoordX;
	MC_S32 OffsetCoordY;
} MC_M206_CODE_FORMAT;

/** @brief The format of M207 */
typedef struct
{
	MC_U8 NowHead;
    MC_U8 NowShelf;
} MC_M207_CODE_FORMAT, MC_M209_CODE_FORMAT, MC_M301_CODE_FORMAT;

/** @brief The format of M211 */
typedef struct
{
	MC_S32 CoordZ;
} MC_M211_CODE_FORMAT;

#pragma pack()  /* Reset the method of memory align */

void MC_CodeInit(void);
MC_CODE_SYS_FLAG* MC_CodeGetSysFlag(void);
MC_BOOL MC_CodeStoreQueueCode(CONST MC_CODE_BUF* code);
MC_BOOL MC_CodeStoreFastCode(CONST MC_CODE_BUF* code);
MC_BOOL MC_CodeStoreSuperCode(CONST MC_CODE_BUF* code);
MC_U32 MC_CodeGetQueueCodeNum(void);
MC_U32 MC_CodeGetFastCodeNum(void);
MC_U32 MC_CodeGetSuperCodeNum(void);
void MC_CodeGetG01FromCodeFormat(MC_CODE_FORMAT* format);
void MC_CodeGetG02FromCodeFormat(MC_CODE_FORMAT* format);
void MC_CodeGetG03FromCodeFormat(MC_CODE_FORMAT* format);
void MC_CodeGetG90FromCodeFormat(MC_CODE_FORMAT* format);
void MC_CodeGetG100FromCodeFormat(MC_CODE_FORMAT* format);
void MC_CodeGetG101FromCodeFormat(MC_CODE_FORMAT* format);
void MC_CodeGetM100FromCodeFormat(MC_CODE_FORMAT* format);
void MC_CodeGetM101FromCodeFormat(MC_CODE_FORMAT* format);
//void MC_CodeGetM102FromCodeFormat(MC_CODE_FORMAT* format);
void MC_CodeGetM103FromCodeFormat(MC_CODE_FORMAT* format);
void MC_CodeGetM200FromCodeFormat(MC_CODE_FORMAT* format);
void MC_CodeGetM205FromCodeFormat(MC_CODE_FORMAT* format);
void MC_CodeGetM206FromCodeFormat(MC_CODE_FORMAT* format);
void MC_CodeGetM211FromCodeFormat(MC_CODE_FORMAT* format);
void MC_CodeGetM304FromCodeFormat(MC_CODE_FORMAT* format);
MC_BOOL MC_CodeQueueCodeExec(void);
void MC_CodeFastCodeExec(void);
void MC_CodeSuperCodeExec(void);

#endif // !__MC_CODE_H__
