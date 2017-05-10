/********************************** SMC6ϵ��PC������  ************************************************
**--------------�ļ���Ϣ--------------------------------------------------------------------------------
**�ļ���: smc6x.h
**������: ֣Т��
**ʱ��: 20080725
**����: �û��ӿ�C++ͷ�ļ�, �������C++�﷨���á�

**------------�޶���ʷ��¼----------------------------------------------------------------------------
** �޸���: ֣Т��
** ��  ��: 1.0
** �ա���: 20081017
** �衡��: �汾����
**
**------------------------------------------------------------------------------------------------------



********************************************************************************************************/


#ifndef _SMC6200_PC_INCLUDE_H
#define _SMC6200_PC_INCLUDE_H

#define __SMC6200_EXPORTS

//������������
#ifdef __SMC6200_EXPORTS
#define SMC6200API __declspec(dllexport)
#else
#define SMC6200API __declspec(dllimport)
#endif

#ifdef __cplusplus
extern "C" {
#endif 

/*********************************************************
�������Ͷ���
**********************************************************/

//����Ķ����������
typedef unsigned __int64   uint64;  

//����Ķ����������
typedef __int64   int64;  

//#define BYTE           INT8U
//#define WORD           INT16U
//#define DWORD          INT32U

typedef unsigned char  BYTE;
typedef unsigned short  WORD;
//typedef unsigned int  DWORD;

//#define __stdcall 

typedef unsigned char  uint8;                   /* defined for unsigned 8-bits integer variable     �޷���8λ���ͱ���  */
typedef signed   char  int8;                    /* defined for signed 8-bits integer variable        �з���8λ���ͱ���  */
typedef unsigned short uint16;                  /* defined for unsigned 16-bits integer variable     �޷���16λ���ͱ��� */
typedef signed   short int16;                   /* defined for signed 16-bits integer variable         �з���16λ���ͱ��� */
typedef unsigned int   uint32;                  /* defined for unsigned 32-bits integer variable     �޷���32λ���ͱ��� */
typedef signed   int   int32;                   /* defined for signed 32-bits integer variable         �з���32λ���ͱ��� */
typedef float          fp32;                    /* single precision floating point variable (32bits) �����ȸ�������32λ���ȣ� */
typedef double         fp64;                    /* double precision floating point variable (64bits) ˫���ȸ�������64λ���ȣ� */
typedef unsigned int   uint;                  /* defined for unsigned 32-bits integer variable     �޷���32λ���ͱ��� */




#ifndef TRUE
#define TRUE  1
#endif

#ifndef FALSE
#define FALSE 0
#endif

#ifndef true
#define true  1
#endif

#ifndef false
#define false 0
#endif


#ifndef NULL
#define NULL 0                   /* see <stddef.h> */
#endif



//���ڶ��ֽڰ�λ���в���
union un_byte {                                        /*   */
              unsigned char BYTE;                       /*  Byte Access */
              struct {                                  /*  Bit  Access */
                     unsigned char B0:1;                /*    Bit 7     */
                     unsigned char B1:1;                /*    Bit 6     */
                     unsigned char B2:1;                /*    Bit 5     */
                     unsigned char B3:1;                /*    Bit 4     */
                     unsigned char B4:1;                /*    Bit 3     */
                     unsigned char B5:1;                /*    Bit 2     */
                     unsigned char B6:1;                /*    Bit 1     */
                     unsigned char B7:1;                /*    Bit 0     */
                     }      BIT;                        /*              */
};                                                      /*              */

union un_uint16 {                                        /*   */
              uint16 m_UINT;                       /*  Byte Access */
              struct {                                  /*  Bit  Access */
                  unsigned short B0:1;                /*    Bit 1     */
                  unsigned short B1:1;                /*    Bit 2     */
                  unsigned short B2:1;                /*    Bit 3     */
                  unsigned short B3:1;                /*    Bit 4     */
                  unsigned short B4:1;                /*    Bit 5     */
                  unsigned short B5:1;                /*    Bit 6     */
                  unsigned short B6:1;                /*    Bit 7     */
                  unsigned short B7:1;                /*    Bit 8     */
                  
                  unsigned short B8:1;                /*    Bit 9     */
                  unsigned short B9:1;                /*    Bit 10     */
                  unsigned short B10:1;                /*    Bit 11     */
                  unsigned short B11:1;                /*    Bit 12     */
                  unsigned short B12:1;                /*    Bit 13     */
                  unsigned short B13:1;                /*    Bit 14     */
                  unsigned short B14:1;                /*    Bit 15     */
                  unsigned short B15:1;                /*    Bit 16     */
                     }      BIT;                        /*              */
};  


union un_uint32 {                                        /*   */
              uint32 m_UINT32;                       /*  Byte Access */
              struct {                                  /*  Bit  Access */
                  unsigned int B0:1;                /*    Bit 7     */
                  unsigned int B1:1;                /*    Bit 6     */
                  unsigned int B2:1;                /*    Bit 5     */
                  unsigned int B3:1;                /*    Bit 4     */
                  unsigned int B4:1;                /*    Bit 3     */
                  unsigned int B5:1;                /*    Bit 2     */
                  unsigned int B6:1;                /*    Bit 1     */
                  unsigned int B7:1;                /*    Bit 0     */
                  
                  unsigned int B8:1;                /*    Bit 7     */
                  unsigned int B9:1;                /*    Bit 6     */
                  unsigned int B10:1;                /*    Bit 5     */
                  unsigned int B11:1;                /*    Bit 4     */
                  unsigned int B12:1;                /*    Bit 3     */
                  unsigned int B13:1;                /*    Bit 2     */
                  unsigned int B14:1;                /*    Bit 1     */
                  unsigned int B15:1;                /*    Bit 0     */

                  unsigned int B16:1;                /*    Bit 7     */
                  unsigned int B17:1;                /*    Bit 6     */
                  unsigned int B18:1;                /*    Bit 5     */
                  unsigned int B19:1;                /*    Bit 4     */
                  unsigned int B20:1;                /*    Bit 3     */
                  unsigned int B21:1;                /*    Bit 2     */
                  unsigned int B22:1;                /*    Bit 1     */
                  unsigned int B23:1;                /*    Bit 0     */
                  
                  unsigned int B24:1;                /*    Bit 7     */
                  unsigned int B25:1;                /*    Bit 6     */
                  unsigned int B26:1;                /*    Bit 5     */
                  unsigned int B27:1;                /*    Bit 4     */
                  unsigned int B28:1;                /*    Bit 3     */
                  unsigned int B29:1;                /*    Bit 2     */
                  unsigned int B30:1;                /*    Bit 1     */
                  unsigned int B31:1;                /*    Bit 0     */
                  
                     }      BIT;                        /*              */
};  



//
// ��������, 6200�����ô���������
enum SMC6X_CONNECTION_TYPE
{
    SMC6X_CONNECTION_COM = 1,
    SMC6X_CONNECTION_ETH = 2,
    SMC6X_CONNECTION_USB = 3,
    SMC6X_CONNECTION_PCI = 4,
};

//ȱʡ�ĵȴ�ʱ��
#define SMC6X_DEFAULT_TIMEOUT   5000

//������ʱ��Ҫ���ӳ�һЩ
#define SMC6X_DEFAULT_TIMEOUT_COM   10000



typedef  void* SMCHANDLE;




//
//���ش�����
#ifndef ERR_SUCCESS
#define ERR_SUCCESS  0
#endif
#ifndef ERR_OK
#define ERR_OK  0
#endif

enum ERR_CODE_SMC6X
{
    ERRCODE_UNKNOWN = 1,
    ERRCODE_PARAERR = 2,        
    ERRCODE_TIMEOUT = 3,
    ERRCODE_CONTROLLERBUSY = 4,
    ERRCODE_CONNECT_TOOMANY = 5,

    ERRCODE_OS_ERR = 6,
    ERRCODE_CANNOT_OPEN_COM = 7,
    ERRCODE_CANNOT_CONNECTETH = 8,
    ERRCODE_HANDLEERR = 9, //���Ӵ���
    ERRCODE_SENDERR = 10, //���Ӵ���
    ERRCODE_GFILE_ERR = 11, //G�ļ��﷨����
    ERRCODE_FIRMWAREERR = 12, //�̼��ļ�����

    ERRCODE_FILENAME_TOOLONG = 13, //�ļ���̫��
    ERRCODE_FIRMWAR_MISMATCH = 14, //�̼��ļ���ƥ��

    ERRCODE_CARD_NOTSUPPORT = 15, //��Ӧ�Ŀ���֧���������


    ERRCODE_BUFFER_TOO_SMALL = 15, //����Ļ���̫С
    ERRCODE_NEED_PASSWORD = 16,    //���뱣��
    ERRCODE_PASSWORD_ENTER_TOOFAST = 17,    //��������̫��



    ERRCODE_GET_LENGTH_ERR = 100, //�յ������ݰ��ĳ��ȴ��� ���������ɺ󲻻����, �ַ����ӿ�ʱ���ܳ������峤��

    ERRCODE_COMPILE_OFFSET = 1000, //�ļ��������


    ERRCODE_CONTROLLERERR_OFFSET = 100000, //���������洫���Ĵ��󣬼������ƫ��

};

/*********************************************************
ϵͳ״̬����
**********************************************************/
#define  SYS_STATE_IDLE        1 //����
//#define  SYS_STATE_ORIGINING  2 �����״̬����ȷ��������ɣ���Ҫ���״̬��
#define  SYS_STATE_GRUNNING    3  //����
#define  SYS_STATE_MANUALING   4  //�ֶ�
#define  SYS_STATE_PAUSE       5 //��ͣ
#define  SYS_STATE_GEDIT       6 //����༭
#define  SYS_STATE_SETTING     7 //����

#define  SYS_STATE_TEST        8 //����
#define  SYS_STATE_GFILEREVIEW 9 //gfile ���
#define  SYS_STATE_UDISK       10 //U�̲���
#define  SYS_STATE_GTEACHING   11 //ʾ��

//������
#define  SYS_STATE_CANNOT_CONNECT   50 //���Ӳ���


//G��������ֹͣ�Ĵ�����
#define ERR_GSTOP_OFFSET        2000
#define ERR_GSTOP_EMG           (ERR_GSTOP_OFFSET + 1)          //EMGֹͣ
#define ERR_GSTOP_EL            (ERR_GSTOP_OFFSET + 2)          //��λֹͣ
#define ERR_GSTOP_GFILE_TYPE_ERR     (ERR_GSTOP_OFFSET + 3)     //���ͳ���
#define ERR_GSTOP_STOPKEYDOWN     (ERR_GSTOP_OFFSET + 4)        //ֹͣ�����£���������
#define ERR_GSTOP_LOOPERR       (ERR_GSTOP_OFFSET + 5)          //ѭ������, ��������
#define ERR_GSTOP_SUBERR        (ERR_GSTOP_OFFSET + 6)          //�ӳ�����ó���, ��ι����
#define ERR_GSTOP_NLINEERR      (ERR_GSTOP_OFFSET + 7)          //��ӦN�к��Ҳ���
#define ERR_GSTOP_NOTSUPPORT     (ERR_GSTOP_OFFSET + 8)         //��֧�ֵ�G����
#define ERR_GSTOP_FILEEND       (ERR_GSTOP_OFFSET + 9)          //�ļ��쳣����
#define ERR_GSTOP_SOFTLIMITED     (ERR_GSTOP_OFFSET + 10)       //����λֹͣ
#define ERR_GSTOP_GLINE_PARA_ERR     (ERR_GSTOP_OFFSET + 11)    //�����ȳ���
#define ERR_GSTOP_TASKERR       (ERR_GSTOP_OFFSET + 12)         //���������
#define ERR_GSTOP_USER_FORCEEND     (ERR_GSTOP_OFFSET + 13)     //ǿ��ֹͣ
#define ERR_GSTOP_GFILECHECKERR     (ERR_GSTOP_OFFSET + 14)     //g�ļ�������
#define ERR_GSTOP_GFILEIDERR     (ERR_GSTOP_OFFSET + 15)        //g�ļ��Ŵ���
#define ERR_GSTOP_ALM              (ERR_GSTOP_OFFSET + 16)      //g�ļ��Ŵ���
#define ERR_GSTOP_ENCODE      (ERR_GSTOP_OFFSET + 17)      //g�ļ��Ŵ���
#define ERR_GSTOP_UNKNOWN     (ERR_GSTOP_OFFSET + 30)           //�����ܵĴ���




/*********************************************************
��������
**********************************************************/

/*************************************************************
˵�������������������
���룺��
�����������handle
����ֵ��������
*************************************************************/
SMC6200API  int32 __stdcall SMCOpen(enum SMC6X_CONNECTION_TYPE type, char *pconnectstring ,SMCHANDLE * phandle);

/*************************************************************
˵�������������������
���룺��
�����������handle
����ֵ��������
*************************************************************/
SMC6200API  int32 __stdcall SMCOpenCom(uint comid, SMCHANDLE * phandle);

/*************************************************************
˵�������������������
���룺IP��ַ���ַ����ķ�ʽ����
�����������handle
����ֵ��������
*************************************************************/
SMC6200API  int32 __stdcall SMCOpenEth(char *ipaddr, SMCHANDLE * phandle);

/*************************************************************
˵�������������������
���룺IP��ַ��32λ����IP��ַ����, ע���ֽ�˳��
�����������handle
����ֵ��������
*************************************************************/
SMC6200API  int32 __stdcall SMCOpenEth2(struct in_addr straddr, SMCHANDLE * phandle);


/*************************************************************
˵�����رտ���������
���룺������handle
�����
����ֵ��������
*************************************************************/
SMC6200API  int32 __stdcall SMCClose(SMCHANDLE  handle);

/*************************************************************
˵�����������ʱ�ȴ�ʱ��
���룺������handle ����ʱ��
�����
����ֵ��������
*************************************************************/
SMC6200API  int32 __stdcall SMCSetTimeOut(SMCHANDLE  handle, uint32 timems);

/*************************************************************
˵�����������ʱ�ȴ�ʱ��
���룺������handle 
���������ʱ��
����ֵ��������
*************************************************************/
SMC6200API  int32 __stdcall SMCGetTimeOut(SMCHANDLE  handle, uint32* ptimems);

/*************************************************************
˵������ȡ��ʱ������Ľ���
���룺������handle 
�����
����ֵ�����ȣ� ���㣬 
*************************************************************/
float  __stdcall SMCGetProgress(SMCHANDLE  handle);


#if 0
#endif
/**********************************************

	command �����б�

*******************************************/


/*************************************************************
˵����//��ȡϵͳ״̬
���룺������handle
�����״̬
����ֵ��������
*************************************************************/
SMC6200API  int32 __stdcall SMCGetState(SMCHANDLE handle,uint8 *pstate);

/*************************************************************
˵����//��ȡ���ӿ�����������
���룺������handle
�����
����ֵ������������0
*************************************************************/
uint8 __stdcall SMCGetAxises(SMCHANDLE handle);

/*************************************************************
˵�������س����ļ� ����ǰ�����һ��
���룺������handle �ļ���
�����
����ֵ��������
*************************************************************/
SMC6200API  int32 __stdcall SMCDownProgram(SMCHANDLE handle, const char* pfilename, const char* pfilenameinControl);

/*************************************************************
˵�������س����ļ� ����ǰ�����һ��
���룺������handle buff ���������ļ�������
�����
����ֵ��������
*************************************************************/
SMC6200API  int32 __stdcall SMCDownMemProgram(SMCHANDLE handle, const char* pbuffer, uint32 buffsize, const char* pfilenameinControl);


/*************************************************************
˵�������س����ļ� ����ʱ�ļ���
���룺������handle buff ���������ļ�������
�����
����ֵ��������
*************************************************************/
SMC6200API  int32 __stdcall SMCDownProgramToTemp(SMCHANDLE handle, const char* pfilename);

/*************************************************************
˵�������س����ļ� ����ʱ�ļ���
���룺������handle buff ���������ļ�������
�����
����ֵ��������
*************************************************************/
SMC6200API  int32 __stdcall SMCDownMemProgramToTemp(SMCHANDLE handle, const char* pbuffer, uint32 buffsize);


/*************************************************************
˵��������
���룺������handle �ļ����� ��ΪNULL��ʱ������ȱʡ�ļ�
�����
����ֵ��������
*************************************************************/
SMC6200API  int32 __stdcall SMCRunProgramFile(SMCHANDLE handle, const char* pfilenameinControl);

/*************************************************************
˵�������ص�ram������
���룺������handle �ļ���
�����
����ֵ��������
*************************************************************/
SMC6200API  int32 __stdcall SMCDownProgramToRamAndRun(SMCHANDLE handle, const char* pfilename);

/*************************************************************
˵�������ص�ram������
���룺������handle �ڴ�buff
�����
����ֵ��������
*************************************************************/
SMC6200API  int32 __stdcall SMCDownMemProgramToRamAndRun(SMCHANDLE handle, const char* pbuffer, uint32 buffsize);

/*************************************************************
˵�����ϴ������ļ�
���룺������handle �ڴ�buff
�����
����ֵ��������
*************************************************************/
SMC6200API  int32 __stdcall SMCUpProgram(SMCHANDLE handle, const char* pfilename, const char* pfilenameinControl);
/*************************************************************
˵�����ϴ������ļ�
���룺������handle �ڴ�buff
�����
����ֵ��������
*************************************************************/
SMC6200API  int32 __stdcall SMCUpProgramToMem(SMCHANDLE handle, char* pbuffer, uint32 buffsize, char* pfilenameinControl, uint32* puifilesize);





/*************************************************************
˵������ͣ
���룺������handle �ļ����� ��ΪNULL��ʱ������ȱʡ�ļ�
�����
����ֵ��������
*************************************************************/
SMC6200API  int32 __stdcall SMCPause(SMCHANDLE handle);

/*************************************************************
˵����ֹͣ
���룺������handle �ļ����� ��ΪNULL��ʱ������ȱʡ�ļ�
�����
����ֵ��������
*************************************************************/
SMC6200API  int32 __stdcall SMCStop(SMCHANDLE handle);

/*************************************************************
˵����������ʱ�ļ�
���룺������handle
�����
����ֵ��������
*************************************************************/
SMC6200API  int32 __stdcall SMCRunTempFile(SMCHANDLE handle);

/*************************************************************
˵������ȡʣ��ռ�
���룺������handle
�����
����ֵ��������
*************************************************************/
SMC6200API  int32 __stdcall SMCCheckRemainProgramSpace(SMCHANDLE handle, uint32 * pRemainSpaceInKB);

/*************************************************************
˵������ȡ����ֹͣԭ��
���룺������handle
�����
����ֵ��������
*************************************************************/
SMC6200API  int32 __stdcall SMCCheckProgramStopReason(SMCHANDLE handle, uint32 * pStopReason);
/*************************************************************
˵������ȡ����ǰ��
���룺������handle
�����
����ֵ��������
*************************************************************/
SMC6200API  int32 __stdcall SMCGetCurRunningLine(SMCHANDLE handle, uint32 * pLineNum);

/*************************************************************
˵�������õ������У����ʵʱ�޸�״̬��������ʧ
���룺������handle
�����
����ֵ��������
*************************************************************/
SMC6200API  int32 __stdcall SMCSetStepRun(SMCHANDLE handle, uint8 bifStep);

/*************************************************************
˵�������ÿ��ߣ����ʵʱ�޸�״̬��������ʧ
���룺������handle
�����
����ֵ��������
*************************************************************/
SMC6200API  int32 __stdcall SMCSetRunNoIO(SMCHANDLE handle, uint8 bifVainRun);

/*************************************************************
˵������ȡ����
���룺������handle
�����
����ֵ��������
*************************************************************/
SMC6200API  int32 __stdcall SMCGetRunningOption(SMCHANDLE handle, uint8* bifStep, uint8* bifVainRun);


/*************************************************************
˵������������
���룺������handle
�����
����ֵ��������
*************************************************************/
SMC6200API  int32 __stdcall SMCContinueRun(SMCHANDLE handle);

/*************************************************************
˵��������ļ��Ƿ����
���룺������handle ���������ļ�����������չ
�����
����ֵ��������
*************************************************************/
SMC6200API  int32 __stdcall SMCCheckProgramFile(SMCHANDLE handle, const char* pfilenameinControl, uint8 *pbIfExist, uint32 *pFileSize);

/*************************************************************
˵�������ҿ������ϵ��ļ��� �ļ���Ϊ�ձ�ʾ�ļ���������
���룺������handle ���������ļ�����������չ
����� �Ƿ���� �ļ���С
����ֵ��������
*************************************************************/
SMC6200API  int32 __stdcall SMCFindFirstProgramFile(SMCHANDLE handle, char* pfilenameinControl, uint32 *pFileSize);

/*************************************************************
˵�������ҿ������ϵ��ļ��� �ļ���Ϊ�ձ�ʾ�ļ���������
���룺������handle ���������ļ�����������չ
����� �Ƿ���� �ļ���С
����ֵ��������
*************************************************************/
SMC6200API  int32 __stdcall SMCFindNextProgramFile(SMCHANDLE handle, char* pfilenameinControl, uint32 *pFileSize);

/*************************************************************
˵�������ҿ������ϵĵ�ǰ�ļ�
���룺������handle ���������ļ�����������չ
����� �Ƿ���� �ļ���С(��ʱ��֧��)
����ֵ��������
*************************************************************/
SMC6200API  int32 __stdcall SMCGetCurProgramFile(SMCHANDLE handle, char* pfilenameinControl, uint32 *pFileSize);

/*************************************************************
˵����ɾ���������ϵ��ļ�
���룺������handle ���������ļ�����������չ
�����
����ֵ��������
*************************************************************/
SMC6200API  int32 __stdcall SMCDeleteProgramFile(SMCHANDLE handle, const char* pfilenameinControl);

/*************************************************************
˵����ɾ���������ϵ��ļ�
���룺������handle
�����
����ֵ��������
*************************************************************/
SMC6200API  int32 __stdcall SMCRemoveAllProgramFiles(SMCHANDLE handle);


#if 0
/***********************  ���ò���  ************************/
#endif

/*************************************************************
˵����ͨ�õ��ַ����ӿ�
���룺������handle �����ַ����������ַ����� �����ַ�������, ������ҪӦ��ʱ����uiResponseLength = 0
�����
����ֵ��������
*************************************************************/
SMC6200API  int32 __stdcall SMCCommand(SMCHANDLE handle, const char* pszCommand, char* psResponse, uint32 uiResponseLength);
/*************************************************************
˵������ǰ���ô���
���룺������handle
�����
����ֵ��������
*************************************************************/
SMC6200API  int32 __stdcall SMCBurnSetting(SMCHANDLE handle);

/*************************************************************
˵�������������ļ�
���룺������handle �ļ���
�����
����ֵ��������
*************************************************************/
SMC6200API  int32 __stdcall SMCDownSetting(SMCHANDLE handle, const char* pfilename);

/*************************************************************
˵�������������ļ�
���룺������handle buff 
�����
����ֵ��������
*************************************************************/
SMC6200API  int32 __stdcall SMCDownMemSetting(SMCHANDLE handle, const char* pbuffer, uint32 buffsize);

/*************************************************************
˵�����ϴ�����
���룺������handle �ڴ�buff
�����
����ֵ��������
*************************************************************/
SMC6200API  int32 __stdcall SMCUpSetting(SMCHANDLE handle, const char* pfilename);
/*************************************************************
˵�����ϴ�����
���룺������handle �ڴ�buff ����ʵ�ʵ��ļ�����
�����
����ֵ��������
*************************************************************/
SMC6200API  int32 __stdcall SMCUpSettingToMem(SMCHANDLE handle, char* pbuffer, uint32 buffsize, uint32* puifilesize);


/*************************************************************
˵�������������ļ�
���룺������handle �ļ���
�����
����ֵ��������
*************************************************************/
SMC6200API  int32 __stdcall SMCDownDefaultSetting(SMCHANDLE handle, const char* pfilename);
/*************************************************************
˵�������������ļ�, �ı��ļ��ĳ�����strlen ����
���룺������handle buff 
�����
����ֵ��������
*************************************************************/
SMC6200API  int32 __stdcall SMCDownMemDefaultSetting(SMCHANDLE handle, const char* pbuffer, uint32 buffsize);

/*************************************************************
˵�����ϴ�����
���룺������handle �ڴ�buff
�����
����ֵ��������
*************************************************************/
SMC6200API  int32 __stdcall SMCUpDefaultSetting(SMCHANDLE handle, const char* pfilename);

/*************************************************************
˵�����ϴ�����
���룺������handle �ڴ�buff
�����
����ֵ��������
*************************************************************/
SMC6200API  int32 __stdcall SMCUpDefaultSettingToMem(SMCHANDLE handle, char* pbuffer, uint32 buffsize, uint32* puifilesize);

/*************************************************************
˵������������
���룺������handle
�����
����ֵ��������
*************************************************************/
SMC6200API  int32 __stdcall SMCSetIpAddr(SMCHANDLE handle, const char* sIpAddr, const char* sGateAddr, const char* sMask, uint8 bifdhcp);

/*************************************************************
˵������������
���룺������handle
�����
����ֵ��������
*************************************************************/
SMC6200API  int32 __stdcall SMCGetIpAddr(SMCHANDLE handle, char* sIpAddr, char* sGateAddr, char* sMask, uint8 *pbifdhcp);

/*************************************************************
˵������ȡ��ǰ��������IP��ַ, ע��:������dhcp�Ժ����õ�IP��ʵ�ʵĲ�һ�¡�
���룺������handle
�����
����ֵ��������
*************************************************************/
SMC6200API  int32 __stdcall SMCGetCurIpAddr(SMCHANDLE handle, char* sIpAddr);

/*************************************************************
˵������������
���룺������handle
�����
����ֵ��������
*************************************************************/
SMC6200API  int32 __stdcall SMCSetZeroSpeed(SMCHANDLE handle, uint8 iaxis, uint32 uiSpeed);

/*************************************************************
˵������������
���룺������handle
�����
����ֵ��������
*************************************************************/
SMC6200API  int32 __stdcall SMCGetZeroSpeed(SMCHANDLE handle, uint8 iaxis, uint32* puiSpeed);

/*************************************************************
˵������������
���룺������handle
�����
����ֵ��������
*************************************************************/
SMC6200API  int32 __stdcall SMCSetLocateSpeed(SMCHANDLE handle, uint8 iaxis, uint32 uiSpeed);

/*************************************************************
˵������������
���룺������handle
�����
����ֵ��������
*************************************************************/
SMC6200API  int32 __stdcall SMCGetLocateSpeed(SMCHANDLE handle, uint8 iaxis, uint32* puiSpeed);

/*************************************************************
˵������������
���룺������handle
�����
����ֵ��������
*************************************************************/
SMC6200API  int32 __stdcall SMCSetLocateStartSpeed(SMCHANDLE handle, uint8 iaxis, uint32 uiSpeed);

/*************************************************************
˵������������
���룺������handle
�����
����ֵ��������
*************************************************************/
SMC6200API  int32 __stdcall SMCGetLocateStartSpeed(SMCHANDLE handle, uint8 iaxis, uint32* puiSpeed);


/*************************************************************
˵������������
���룺������handle
�����
����ֵ��������
*************************************************************/
SMC6200API  int32 __stdcall SMCSetLocateAcceleration(SMCHANDLE handle, uint8 iaxis, uint32 uiValue);

/*************************************************************
˵������������
���룺������handle
�����
����ֵ��������
*************************************************************/
SMC6200API  int32 __stdcall SMCGetLocateAcceleration(SMCHANDLE handle, uint8 iaxis, uint32* puiValue);

/*************************************************************
˵������������
���룺������handle
�����
����ֵ��������
*************************************************************/
SMC6200API  int32 __stdcall SMCSetLocateDeceleration(SMCHANDLE handle, uint8 iaxis, uint32 uiValue);
/*************************************************************
˵������������
���룺������handle
�����
����ֵ��������
*************************************************************/
SMC6200API  int32 __stdcall SMCGetLocateDeceleration(SMCHANDLE handle, uint8 iaxis, uint32* puiValue);

/*************************************************************
˵������������
���룺������handle
�����
����ֵ��������
*************************************************************/
SMC6200API  int32 __stdcall SMCSetUnitPulses(SMCHANDLE handle, uint8 iaxis, uint32 uiValue);

/*************************************************************
˵������������
���룺������handle
�����
����ֵ��������
*************************************************************/
SMC6200API  int32 __stdcall SMCGetUnitPulses(SMCHANDLE handle, uint8 iaxis, uint32* puiValue);


/*************************************************************
˵������������
���룺������handle
�����
����ֵ��������
*************************************************************/
SMC6200API  int32 __stdcall SMCSetVectStartSpeed(SMCHANDLE handle, uint32 uiValue);
/*************************************************************
˵������������
���룺������handle
�����
����ֵ��������
*************************************************************/
SMC6200API  int32 __stdcall SMCGetVectStartSpeed(SMCHANDLE handle, uint32* puiValue);

/*************************************************************
˵������������
���룺������handle
�����
����ֵ��������
*************************************************************/
SMC6200API  int32 __stdcall SMCSetVectSpeed(SMCHANDLE handle, uint32 uiValue);

/*************************************************************
˵������������
���룺������handle
�����
����ֵ��������
*************************************************************/
SMC6200API  int32 __stdcall SMCGetVectSpeed(SMCHANDLE handle, uint32* puiValue);

/*************************************************************
˵������������
���룺������handle
�����
����ֵ��������
*************************************************************/
SMC6200API  int32 __stdcall SMCSetVectAcceleration(SMCHANDLE handle, uint32 uiValue);

/*************************************************************
˵������������
���룺������handle
�����
����ֵ��������
*************************************************************/
SMC6200API  int32 __stdcall SMCGetVectAcceleration(SMCHANDLE handle, uint32* puiValue);


/*************************************************************
˵������������
���룺������handle
�����
����ֵ��������
*************************************************************/
SMC6200API  int32 __stdcall SMCSetVectDeceleration(SMCHANDLE handle, uint32 uiValue);

/*************************************************************
˵������������
���룺������handle
�����
����ֵ��������
*************************************************************/
SMC6200API  int32 __stdcall SMCGetVectDeceleration(SMCHANDLE handle, uint32* puiValue);



#if 0
/***********************  �˶�����  ************************/
#endif


//������Ŷ���
enum SMC_AXIS_NUM_LIST
{
    SMC_AXIS_X = 0,
    SMC_AXIS_Y = 1,
    SMC_AXIS_Z = 2,
    SMC_AXIS_U = 3,

    SMC_AXIS_NUM_VECT = 0XFE,
    SMC_AXIS_NUM_ALL = 0XFF,
};

/*************************************************************
˵����
���룺������handle ��ţ� ���ȣ� �Ƿ�����ƶ�
�����
����ֵ��������
*************************************************************/
SMC6200API  int32 __stdcall SMCPMove(SMCHANDLE handle, uint8 iaxis, double dlength, uint8 bIfAbs);

/*************************************************************
˵����
���룺������handle ��ţ� ���ȣ� �Ƿ�����ƶ�
�����
����ֵ��������
*************************************************************/
SMC6200API  int32 __stdcall SMCPMovePluses(SMCHANDLE handle, uint8 iaxis, int32 ilength, uint8 bIfAbs);

/*************************************************************
˵����
���룺������handle ��ţ� ����
�����
����ֵ��������
*************************************************************/
SMC6200API  int32 __stdcall SMCVMove(SMCHANDLE handle, uint8 iaxis, uint8 bIfPositiveDir);


/*************************************************************
˵����
���룺������handle ��ţ� ����
�����
����ֵ��������
*************************************************************/
SMC6200API  int32 __stdcall SMCPMoveList(SMCHANDLE handle,uint8 itotalaxises, uint8 *puilineaxislist, uint32 uisteps, double *pDistanceList, uint8 bIfAbs);



/*************************************************************
˵����
���룺������handle ��ţ� ����
�����
����ֵ��������
*************************************************************/
SMC6200API  int32 __stdcall SMCCheckDown(SMCHANDLE handle,uint8 iaxis, uint8* pbIfDown);

/*************************************************************
˵�������㣬����ģʽͨ������ָ��
���룺������handle ��ţ� ����
�����
����ֵ��������
*************************************************************/
SMC6200API  int32 __stdcall SMCHomeMove(SMCHANDLE handle,uint8 iaxis);

/*************************************************************
˵����
���룺������handle ���
�����
����ֵ��������
*************************************************************/
SMC6200API  int32 __stdcall SMCIfHomeMoveing(SMCHANDLE handle,uint8 iaxis, uint8* pbIfHoming);

/*************************************************************
˵����
���룺������handle ���
�����
����ֵ��������
*************************************************************/
SMC6200API  int32 __stdcall SMCDecelStop(SMCHANDLE handle,uint8 iaxis);

/*************************************************************
˵����
���룺������handle ���
�����
����ֵ��������
*************************************************************/
SMC6200API  int32 __stdcall SMCImdStop(SMCHANDLE handle,uint8 iaxis);


/*************************************************************
˵����
���룺������handle
�����
����ֵ��������
*************************************************************/
SMC6200API  int32 __stdcall SMCEmgStop(SMCHANDLE handle);

/*************************************************************
˵�������ٶ�
���룺������handle ���
�����
����ֵ��������
*************************************************************/
SMC6200API  int32 __stdcall SMCChangeSpeed(SMCHANDLE handle,uint8 iaxis, double dspeed);


/*************************************************************
˵����
���룺������handle ���
���������
����ֵ��������
*************************************************************/
SMC6200API  int32 __stdcall SMCGetPosition(SMCHANDLE handle,uint8 iaxis, double* pposition);


/*************************************************************
˵���� ��ȡ��ǰ�Ĺ�������
���룺������handle ���
���������
����ֵ��������
*************************************************************/
SMC6200API  int32 __stdcall SMCGetWorkPosition(SMCHANDLE handle,uint8 iaxis, double* pposition);

/*************************************************************
˵���� ��ȡ��е���꣬���巽ʽ
���룺������handle ���
���������
����ֵ��������
*************************************************************/
SMC6200API  int32 __stdcall SMCGetPositionPulses(SMCHANDLE handle,uint8 iaxis, int32* pposition);

/*************************************************************
˵���� ��ȡ�������
���룺������handle ���
���������
����ֵ��������
*************************************************************/
SMC6200API  int32 __stdcall SMCGetWorkOriginPosition(SMCHANDLE handle, uint8 iaxis, double* pposition);

/*************************************************************
˵����
���룺������handle ��� ����
�����
����ֵ��������
*************************************************************/
SMC6200API  int32 __stdcall SMCSetPosition(SMCHANDLE handle,uint8 iaxis, double dposition);
/*************************************************************
˵����
���룺������handle ��� ����
�����
����ֵ��������
*************************************************************/
SMC6200API  int32 __stdcall SMCSetPositionPulses(SMCHANDLE handle,uint8 iaxis, int32 iposition);

/*************************************************************
˵����
���룺������handle ���
�����
����ֵ��������
*************************************************************/
SMC6200API  int32 __stdcall SMCWaitDown(SMCHANDLE handle,uint8 iaxis);

/*************************************************************
˵����
���룺������handle ���
�����
����ֵ��������
*************************************************************/
SMC6200API  int32 __stdcall SMCWaitPoint(SMCHANDLE handle,uint8 iaxis, double dpos);

/*************************************************************
˵����
���룺������handle ���
�����
����ֵ��������
*************************************************************/
SMC6200API  int32 __stdcall SMCHandWheelSet(SMCHANDLE handle,uint8 iaxis, uint16 imulti, uint8 bifDirReverse);
/*************************************************************
˵����
���룺������handle ���
�����
����ֵ��������
*************************************************************/
SMC6200API  int32 __stdcall SMCHandWheelMove(SMCHANDLE handle,uint8 iaxis, uint8 bifenable);


/*************************************************************
˵����
���룺������handle
�����
����ֵ��������
*************************************************************/
SMC6200API  int32 __stdcall SMCVectMoveStart(SMCHANDLE handle);

/*************************************************************
˵����
���룺������handle
�����
����ֵ��������
*************************************************************/
SMC6200API  int32 __stdcall SMCVectMoveEnd(SMCHANDLE handle);

// �岹����״̬, һ���������ͻ������ͣ״̬
enum SMC6X_VECTMOVE_STATE
{
    VECTMOVE_STATE_RUNING = 1,
    VECTMOVE_STATE_PAUSE = 2,
    VECTMOVE_STATE_STOP = 3,
};

/*************************************************************
˵����
���룺������handle
�����
����ֵ��������
*************************************************************/
SMC6200API  int32 __stdcall SMCGetVectMoveState(SMCHANDLE handle, uint8 *pState);

/*************************************************************
˵����
���룺������handle
�����
����ֵ��������
*************************************************************/
SMC6200API  int32 __stdcall SMCGetVectMoveRemainSpace(SMCHANDLE handle, uint32 *pSpace);

/*************************************************************
˵�����岹�����޸��ٶ�����
���룺������handle
�����
����ֵ��������
*************************************************************/
SMC6200API  int32 __stdcall SMCVectMoveLine1(SMCHANDLE handle, uint8 iaxis, double Distance, double dspeed, uint8 bIfAbs);
/*************************************************************
˵�����岹�����޸��ٶ�����
���룺������handle
�����
����ֵ��������
*************************************************************/
SMC6200API  int32 __stdcall SMCVectMoveLine2(SMCHANDLE handle, uint8 iaxis1, double Distance1, uint8 iaxis2, double Distance2, double dspeed, uint8 bIfAbs);

/*************************************************************
˵�����岹�������޸��ٶ�����
���룺������handle
�����
����ֵ��������
*************************************************************/
SMC6200API  int32 __stdcall SMCVectMoveLineN(SMCHANDLE handle, uint8 itotalaxis, uint8* piaxisList, double* DistanceList, double dspeed, uint8 bIfAbs);

//3D��ӡ��Ӧ��ͨ��ģ��������ѹ���������۽��ı�������
SMC6200API  int32 __stdcall SMCVectMoveLineN_Extern(SMCHANDLE handle, uint8 itotalaxis, uint8* piaxisList, double* DistanceList, double dspeed, uint8 bIfAbs, char* pVoltOut);


/*************************************************************
˵�����岹�����޸��ٶ�����
���룺������handle
�����
����ֵ��������
*************************************************************/
SMC6200API  int32 __stdcall SMCVectMoveMultiLine2(SMCHANDLE handle, uint8 iaxis1, uint8 iaxis2, uint16 uiSectes, double* DistanceList, double* dspeedList, uint8 bIfAbs);

/*************************************************************
˵�����岹�������޸��ٶ�����
���룺������handle
�����
����ֵ��������
*************************************************************/
SMC6200API  int32 __stdcall SMCVectMoveMultiLineN(SMCHANDLE handle, uint8 itotalaxis, uint8* piaxisList, uint16 uiSectes,double* DistanceList, double* dspeedList, uint8 bIfAbs);

/*************************************************************
˵�����岹�����޸��ٶ�����
���룺������handle
�����
����ֵ��������
*************************************************************/
SMC6200API  int32 __stdcall SMCVectMoveArc(SMCHANDLE handle, uint8 iaxis1, uint8 iaxis2, double Distance1, double Distance2, double Center1, double Center2, uint8 bIfAnticlockwise, double dspeed, uint8 bIfAbs);


/*************************************************************
˵�������ٵ����
���룺������handle
�����
����ֵ��������
*************************************************************/
SMC6200API  int32 __stdcall SMCVectMoveSetSpeedLimition(SMCHANDLE handle, double dspeed);


/*************************************************************
˵����
���룺������handle
�����
����ֵ��������
*************************************************************/
SMC6200API  int32 __stdcall SMCWaitVectLength(SMCHANDLE handle, double vectlength);

/*************************************************************
˵����
���룺������handle
�����
����ֵ��������
*************************************************************/
SMC6200API  int32 __stdcall SMCGetCurRunVectLength(SMCHANDLE handle, double* pvectlength);
/*************************************************************
˵����
���룺������handle
�����
����ֵ��������
*************************************************************/
SMC6200API  int32 __stdcall SMCGetCurSpeed(SMCHANDLE handle, uint8 iaxis, double* pspeed);

/*************************************************************
˵���� ������ͣ, �岹��ͣ����Ȼ���Լ���С��
���룺������handle
�����
����ֵ��������
*************************************************************/
SMC6200API  int32 __stdcall SMCVectMovePause(SMCHANDLE handle);

/*************************************************************
˵���� �岹����ֹͣ
���룺������handle
�����
����ֵ��������
*************************************************************/
SMC6200API  int32 __stdcall SMCVectMoveStop(SMCHANDLE handle);


/*************************************************************
˵������ͣ; ������������ݲ�֧��
���룺������handle
�����
����ֵ��������
*************************************************************/
SMC6200API  int32 __stdcall SMCAxisPause(SMCHANDLE handle, uint8 iaxis);

#if 0
/***********************  IO�Ƚӿڲ���  ************************/
#endif

//�����
#define    SMC_IN_VALIDVALUE      0    //��Ч��ƽ��ͨ��IOΪ�͵�ƽ, ԭ����λ�źŵĵ�ƽ��������
#define    SMC_IN_INVALIDVALUE    1    //�ߵ�ƽ

//�����
#define    SMC_OUT_VALIDVALUE      0    //��Ч��ƽ��ͨ��IOΪ�͵�ƽ, ���л���ʼ��ƽ�������ƽ���෴
#define    SMC_OUT_INVALIDVALUE    1    //�ߵ�ƽ

//���е�IO��ţ���������IO
enum enu_SMC_IONUM
{
    //��ͨIO��1��ʼ���
    SMC_IONUM_1 = 1, 

    SMC_IONUM_24 = 24, 

    //pwm��daҲ���
    SMC_IONUM_PWM1 = 41,
    SMC_IONUM_PWM2 = 42,
    SMC_IONUM_DA1 = 51,
    SMC_IONUM_DA2 = 52,

    //���ڲ���LED    
    SMC_IONUM_LED1 = 61,
    SMC_IONUM_LED2 = 62,
    
    //���ڲ���PWM��Ƶ��
    SMC_IONUM_PWM1_FREQENCY = 71,
    SMC_IONUM_PWM2_FREQENCY = 72,

};


typedef struct
{
    uint8 m_axisnum;
    
    uint8 m_HomeState;
    uint8 m_AlarmState;
    
    uint8 m_SDState;
    uint8 m_INPState;
    
    uint8 m_ElDecState;
    uint8 m_ElPlusState;
    
    uint8 m_HandWheelAState;
    uint8 m_HandWheelBState;
    uint8 m_EncodeAState; //6200û������ź�
    uint8 m_EncodeBState; //6200û������ź�
    //uint8 m_EMGState; //ÿ���ᶼһ��

    uint8 m_ClearState; //6200û������ź�

    //��������λ�ź�
    uint8 m_SoftElDecState; //0- ��Ч
    uint8 m_SoftElPlusState;
    uint8 m_LatchState;
}struct_AxisStates;


/*************************************************************
˵��������LED���������
���룺������handle led��ţ���1��ʼ
�����
����ֵ��������
*************************************************************/
SMC6200API  int32 __stdcall SMCWriteLed(SMCHANDLE handle, uint16 iLedNum, uint8 bifLighten);


/*************************************************************
˵����д�����
���룺������handle io��ţ���1��ʼ 0-�͵�ƽ�� 1- �ߵ�ƽ
�����
����ֵ��������
*************************************************************/
SMC6200API  int32 __stdcall SMCWriteOutBit(SMCHANDLE handle, uint16 ioNum, uint8 IoState);

/*************************************************************
˵�����������
���룺������handle io��ţ���1��ʼ
�����0-�͵�ƽ�� 1- �ߵ�ƽ
����ֵ��������
*************************************************************/
SMC6200API  int32 __stdcall SMCReadInBit(SMCHANDLE handle, uint16 ioNum, uint8* pIoState);

/*************************************************************
˵�����������
���룺������handle io��ţ���1��ʼ
�����0-�͵�ƽ�� 1- �ߵ�ƽ
����ֵ��������
*************************************************************/
SMC6200API  int32 __stdcall SMCReadOutBit(SMCHANDLE handle, uint16 ioNum, uint8* pIoState);

/*************************************************************
˵����дȫ�������
���룺������handle 
      IoMask: 1��λҪ�޸ģ�����ͨ����������޸�ָ������IO
      IoState:  0-�͵�ƽ�� 1- �ߵ�ƽ;  0-31λ ���� 1-32IO
�����
����ֵ��������
*************************************************************/
SMC6200API  int32 __stdcall SMCWriteOutPort(SMCHANDLE handle, uint32 IoMask, uint32 IoState);

/*************************************************************
˵������ȫ�������
���룺������handle 
�����0-�͵�ƽ�� 1- �ߵ�ƽ
����ֵ��������
*************************************************************/
SMC6200API  int32 __stdcall SMCReadInPort(SMCHANDLE handle, uint32* pIoState);

/*************************************************************
˵������ȫ�������
���룺������handle 
�����0-�͵�ƽ�� 1- �ߵ�ƽ
����ֵ��������
*************************************************************/
SMC6200API  int32 __stdcall SMCReadOutPort(SMCHANDLE handle, uint32* pIoState);


/*************************************************************
˵�������ŷ��澯����״̬ 6200û��
���룺������handle io��ţ���1��ʼ
�����0-��Ч�� 1- ��Ч
����ֵ��������
*************************************************************/
SMC6200API  int32 __stdcall SMCReadAlarmState(SMCHANDLE handle, uint8 iaxis, uint8* pIoState);

/*************************************************************
˵������ԭ������״̬
���룺������handle io��ţ���1��ʼ
�����0-��Ч�� 1- ��Ч
����ֵ��������
*************************************************************/
SMC6200API  int32 __stdcall SMCReadHomeState(SMCHANDLE handle, uint8 iaxis, uint8* pIoState);


/*************************************************************
˵��������ͣ����״̬
���룺������handle
�����0-��Ч�� 1- ��Ч
����ֵ��������
*************************************************************/
SMC6200API  int32 __stdcall SMCReadEMGState(SMCHANDLE handle, uint8* pIoState);
/*************************************************************
˵����������AB����״̬, 6200������Ϊ9 10��������޹� 
���룺������handle
�����0-��Ч�� 1- ��Ч
����ֵ��������
*************************************************************/
SMC6200API  int32 __stdcall SMCReadHandWheelStates(SMCHANDLE handle, uint8 iaxis, uint8* pIoAState, uint8* pIoBState);

/*************************************************************
˵��������λ״̬
���룺������handle
�����0-��Ч�� 1- ��Ч
����ֵ��������
*************************************************************/
SMC6200API  int32 __stdcall SMCReadElStates(SMCHANDLE handle, uint8 iaxis, uint8* pElDecState, uint8* pElPlusState);


/*************************************************************
˵�����������ź�����״̬
���룺������handle io��ţ���1��ʼ
�����0-��Ч�� 1- ��Ч
����ֵ��������
*************************************************************/
SMC6200API  int32 __stdcall SMCReadSdStates(SMCHANDLE handle, uint8 iaxis, uint8* pIoState);

/*************************************************************
˵��������λ�ź�����״̬
���룺������handle io��ţ���1��ʼ
�����0-��Ч�� 1- ��Ч
����ֵ��������
*************************************************************/
SMC6200API  int32 __stdcall SMCReadInpStates(SMCHANDLE handle, uint8 iaxis, uint8* pIoState);

/*************************************************************
˵����������������״̬
���룺������handle ��ţ���0XFF��ʱ�򣬱�ʾ��ȡ���е��ᣬ
�����0-��Ч�� 1- ��Ч
����ֵ��������
*************************************************************/
SMC6200API  int32 __stdcall SMCReadAxisStates(SMCHANDLE handle, uint8 iaxis, struct_AxisStates* pAxisState);
/*************************************************************
˵����дPWMռ�ձ�
���룺������handle ͨ��:1/2
�����
����ֵ��������
*************************************************************/
SMC6200API  int32 __stdcall SMCWritePwmDuty(SMCHANDLE handle, uint8 ichannel, float fDuty);
/*************************************************************
˵����дPWMƵ��
���룺������handle ͨ��:1/2
�����
����ֵ��������
*************************************************************/
SMC6200API  int32 __stdcall SMCWritePwmFreqency(SMCHANDLE handle, uint8 ichannel, float fFre);

/*************************************************************
˵����дDA�����ѹ
���룺������handle ͨ��:1/2
�����
����ֵ��������
*************************************************************/
SMC6200API  int32 __stdcall SMCWriteDaOut(SMCHANDLE handle, uint8 ichannel, float fLevel);

/*************************************************************
˵����PWMռ�ձ�
���룺������handle ͨ��:1/2
�����
����ֵ��������
*************************************************************/
SMC6200API  int32 __stdcall SMCReadPwmDuty(SMCHANDLE handle, uint8 ichannel, float* fDuty);

/*************************************************************
˵����PWMƵ��
���룺������handle ͨ��:1/2
�����
����ֵ��������
*************************************************************/
SMC6200API  int32 __stdcall SMCReadPwmFreqency(SMCHANDLE handle, uint8 ichannel, float* fFre);

/*************************************************************
˵����DA�����ѹ
���룺������handle ͨ��:1/2
�����
����ֵ��������
*************************************************************/
SMC6200API  int32 __stdcall SMCReadDaOut(SMCHANDLE handle, uint8 ichannel, float* fLevel);


/*************************************************************
˵�����ͻ����, �������ֻ�Բ��ֿͻ�����
���룺������handle
�����״̬
����ֵ��������
*************************************************************/
SMC6200API  int32 __stdcall SMCGetClientId(SMCHANDLE handle,uint16 *pId);

/*************************************************************
˵���������Ʒ����
���룺������handle
�����״̬
����ֵ��������
*************************************************************/
SMC6200API  int32 __stdcall SMCGetSoftwareId(SMCHANDLE handle,uint16 *pId);


/*************************************************************
˵����Ӳ�����
���룺������handle
�����״̬
����ֵ��������
*************************************************************/
SMC6200API  int32 __stdcall SMCGetHardwareId(SMCHANDLE handle,uint16 *pId);


/*************************************************************
˵��������汾�ţ������ڱ�ʶ
���룺������handle
�����״̬
����ֵ��������
*************************************************************/
SMC6200API  int32 __stdcall SMCGetSoftwareVersion(SMCHANDLE handle,uint32 *pVersion);

/*************************************************************
˵�����ϴ������ļ�
���룺������handle �ڴ�buff
�����
����ֵ��������
*************************************************************/
SMC6200API  int32 __stdcall SMCUpPasswordFile(SMCHANDLE handle, const char* pfilename);

/*************************************************************
˵�����ϴ������ļ�
���룺������handle �ڴ�buff ����ʵ�ʵ��ļ�����
�����
����ֵ��������
*************************************************************/
SMC6200API  int32 __stdcall SMCUpPasswordFileToMem(SMCHANDLE handle, char* pbuffer, uint32 buffsize, uint32* puifilesize);

/*************************************************************
˵�������������ļ�
���룺������handle �ļ���
�����
����ֵ��������
*************************************************************/
SMC6200API  int32 __stdcall SMCDownPasswordFile(SMCHANDLE handle, const char* pfilename);


/*************************************************************
˵�������������ļ�, �ı��ļ��ĳ�����strlen ����
���룺������handle buff 
�����
����ֵ��������
*************************************************************/
SMC6200API  int32 __stdcall SMCDownMemPasswordFile(SMCHANDLE handle, const char* pbuffer, uint32 buffsize);


/*************************************************************
˵������������
���룺������handle ����
�����
����ֵ��������
*************************************************************/
SMC6200API  int32 __stdcall SMCEnterSetPassword(SMCHANDLE handle, uint32 uipassword);

/*************************************************************
˵������������
���룺������handle ����
�����
����ֵ��������
*************************************************************/
SMC6200API  int32 __stdcall SMCEnterEditPassword(SMCHANDLE handle, uint32 uipassword);


/*************************************************************
˵������������
���룺������handle ����
�����
����ֵ��������
*************************************************************/
SMC6200API  int32 __stdcall SMCEnterSuperPassword(SMCHANDLE handle, uint32 uipassword);

/*************************************************************
˵������������
���룺������handle ����
�����
����ֵ��������
*************************************************************/
SMC6200API  int32 __stdcall SMCEnterTimePassword(SMCHANDLE handle, uint32 uipassword);


/*************************************************************
˵��������Ѿ����������, �����ٴ�����������ܽ�����Ӧ����
���룺������handle ����
�����
����ֵ��������
*************************************************************/
SMC6200API  int32 __stdcall SMCClearEnteredPassword(SMCHANDLE handle);

/*************************************************************
˵�����޸�����
���룺������handle ����
�����
����ֵ��������
*************************************************************/
SMC6200API  int32 __stdcall SMCModifySetPassword(SMCHANDLE handle, uint32 uipassword);

/*************************************************************
˵�����޸�����
���룺������handle ����
�����
����ֵ��������
*************************************************************/
SMC6200API  int32 __stdcall SMCModifyEditPassword(SMCHANDLE handle, uint32 uipassword);

/*************************************************************
˵�����޸�����
���룺������handle ����
�����
����ֵ��������
*************************************************************/
SMC6200API  int32 __stdcall SMCModifySuperPassword(SMCHANDLE handle, uint32 uipassword);
/*************************************************************
˵������ȡ�û��������
���룺������handle ����
�����
����ֵ��������
*************************************************************/
SMC6200API  int32 __stdcall SMCGetTrialCondition(SMCHANDLE handle, uint32* pRunHours, uint16* pbifTimeLocked, uint16* pAlreadyEnterdTimePasswordNum);


#if 0
/********************  ��Щ���������⿪�� ***********************/
#endif


/*************************************************************
˵�����̼�����
���룺������handle
�����
����ֵ��������
*************************************************************/
SMC6200API  int32 __stdcall SMCDownFirmWare(SMCHANDLE handle, const char* pfirmwarefilename);

/*************************************************************
˵������ȡ������ID
���룺������handle
�����
����ֵ��������
*************************************************************/
SMC6200API  int32 __stdcall SMCGetControllerID(SMCHANDLE handle, uint32 *pid);

/*************************************************************
˵�������ÿ�����ID
���룺������handle
�����
����ֵ��������
*************************************************************/
SMC6200API  int32 __stdcall SMCSetControllerID(SMCHANDLE handle, uint32 id);
/*************************************************************
˵������ʽ��
���룺������handle
�����
����ֵ��������
*************************************************************/
SMC6200API  int32 __stdcall SMCLowFormatNand(SMCHANDLE handle);
/*************************************************************
˵������λ
���룺������handle
�����
����ֵ��������
*************************************************************/
SMC6200API  int32 __stdcall SMCResetController(SMCHANDLE handle);

/*************************************************************
˵����Ӳ������
���룺������handle
�����
����ֵ��������
*************************************************************/
SMC6200API  int32 __stdcall SMCStartHardwareTest(SMCHANDLE handle);

/*************************************************************
˵������ȡ������ID
���룺������handle mac��ַ���ַ�����ʽ
�����
����ֵ��������
*************************************************************/
SMC6200API  int32 __stdcall SMCSetMac(SMCHANDLE handle, char *smac);

/*************************************************************
˵�������ÿ�����ID
���룺������handle
����� mac��ַ���ַ�����ʽ
����ֵ��������
*************************************************************/
SMC6200API  int32 __stdcall SMCGetMac(SMCHANDLE handle, char *smac);

/*************************************************************
˵�������ҿ������ϵ��ļ��� �ļ���Ϊ�ձ�ʾ�ļ���������
���룺������handle ���������ļ���������չ
����� �ļ��� �ļ���С
����ֵ��������
*************************************************************/
SMC6200API  int32 __stdcall SMCFindFirstFile(SMCHANDLE handle, char* pfilenameinControl, uint32 *pFileSize);
/*************************************************************
˵�������ҿ������ϵ��ļ��� �ļ���Ϊ�ձ�ʾ�ļ���������
���룺������handle ���������ļ���������չ
����� �Ƿ���� �ļ���С
����ֵ��������
*************************************************************/
SMC6200API  int32 __stdcall SMCFindNextFile(SMCHANDLE handle, char* pfilenameinControl, uint32 *pFileSize);

/*************************************************************
˵���������ļ�
���룺������handle �ļ���
�����
����ֵ��������
*************************************************************/
SMC6200API  int32 __stdcall SMCDownFile(SMCHANDLE handle, const char* pfilename, const char* pfilenameinControl);

/*************************************************************
˵���������ļ�, �ı��ļ��ĳ�����strlen ����
���룺������handle buff 
�����
����ֵ��������
*************************************************************/
SMC6200API  int32 __stdcall SMCDownMemFile(SMCHANDLE handle, const char* pbuffer, uint32 buffsize, const char* pfilenameinControl);

/*************************************************************
˵�����ϴ�
���룺������handle �ڴ�buff
�����
����ֵ��������
*************************************************************/
SMC6200API  int32 __stdcall SMCUpFile(SMCHANDLE handle, const char* pfilename, const char* pfilenameinControl);

/*************************************************************
˵�����ϴ�
���룺������handle �ڴ�buff ����ʵ�ʵ��ļ�����
�����
����ֵ��������
*************************************************************/
SMC6200API  int32 __stdcall SMCUpFileToMem(SMCHANDLE handle, char* pbuffer, uint32 buffsize, const char* pfilenameinControl, uint32* puifilesize);

/*************************************************************
˵����ɾ���������ϵ��ļ�
���룺������handle
�����
����ֵ��������
*************************************************************/
SMC6200API  int32 __stdcall SMCDeleteFile(SMCHANDLE handle, const char* pfilenameinControl);

/*************************************************************
˵��������ʹ��
���룺
�����
����ֵ��������
*************************************************************/
SMC6200API  int32 __stdcall SMCTestSoftware(SMCHANDLE handle);


/********************** ���溯�������⿪�� ***************************/


/*************************************************************
˵����modbus�Ĵ�������
���룺������handle �Ĵ�����ַ
�����
����ֵ��������
*************************************************************/
SMC6200API  uint32 __stdcall SMCModbus_Set0x(SMCHANDLE handle, uint16 start, uint16 inum, uint8* pdata);
SMC6200API  uint32 __stdcall SMCModbus_Get0x(SMCHANDLE handle, uint16 start, uint16 inum, uint8* pdata);
SMC6200API  uint32 __stdcall SMCModbus_Get4x(SMCHANDLE handle, uint16 start, uint16 inum, uint16* pdata);
SMC6200API  uint32 __stdcall SMCModbus_Set4x(SMCHANDLE handle, uint16 start, uint16 inum, uint16* pdata);


/*************************************************************
˵�����Ѵ�����ת�������ַ���
���룺Ӧ�����Ϣ
�����
����ֵ��������
*************************************************************/
char* __stdcall SMCGetErrcodeDescription(int32 ierrcode);
/*************************************************************
˵�����������﷨
���룺�����ַ������棬����1024�ֽ�
�����
����ֵ��������
*************************************************************/
SMC6200API  int32 __stdcall SMCCheckProgramSyntax(const char *sin, char *sError);

SMC6200API  int32 __stdcall SMC_MultiLine(SMCHANDLE handle,uint8 itotalaxis, uint8* piaxisList, uint16 uiSectes, double* DistanceList, double* dspeedList, uint8 bIfAbs);


/*ADD*/
/*************************************************************
˵���� ����S���߱���
���룺axis ���
	   para ���߱���
�������
����ֵ��������
*************************************************************/
SMC6200API  int32 __stdcall SMCLineScureSet(SMCHANDLE handle,uint8 axis,double para);





/*************************************************************
˵�������ù������
���룺������handle ���0-3 ����
�����
����ֵ��������
*************************************************************/
SMC6200API  int32 __stdcall SMCSetWorkOriginPosition(SMCHANDLE handle, uint8 iaxis, double dposition);


/*************************************************************
���ܣ�����/��ȡ�����λ��ʹ��, ��λ��ֵ, ��Ӧ����
������axis ָ�����
	  ON_OFF ����λʹ�ܣ� 0 �C��ֹ�� 1 �Cʹ��
      SL_action ��λ������ 0 �C��ͣ�� 1 �C����ͣ
      N_limit ����λֵ
      P_limit ����λֵ
����ֵ���������
*************************************************************/
SMC6200API  int32 __stdcall SMCConfigSoftlimit(SMCHANDLE handle, uint8 axis, uint8 ON_OFF,uint8 SL_action,float N_limit,float Plimit);


/*************************************************************
���ܣ�����/��ȡ�����λ��ʹ��, ��λ��ֵ, ��Ӧ����
������axis ָ�����
	  ON_OFF ����λʹ�ܣ� 0 �C��ֹ�� 1 �Cʹ��
      SL_action ��λ������ 0 �C��ͣ�� 1 �C����ͣ
      N_limit ����λֵ
      P_limit ����λֵ
����ֵ���������
*************************************************************/
SMC6200API  int32 __stdcall SMCGetConfigSoftlimit(SMCHANDLE handle, uint8 axis, uint8 *ON_OFF,uint8 *SL_action,float *N_limit,float *Plimit);
/*************************************************************
���ܣ�����/��ȡ��϶����ֵ
������axis ָ�����
backlash ��϶����ֵ�� ��λ������
����ֵ���������
*************************************************************/
SMC6200API  int32 __stdcall SMCSetBackLash(SMCHANDLE handle, uint8 axis, float lash );
/*************************************************************
���ܣ�����/��ȡ��϶����ֵ
������axis ָ�����
backlash ��϶����ֵ�� ��λ������
����ֵ���������
*************************************************************/
SMC6200API  int32 __stdcall SMCGetBackLash(SMCHANDLE handle, uint8 axis, float *lash );


/**************************************************************
���ܣ����ֲ�ͬ�Ļ�ԭ��ģʽ��ʵ�־�ȷ��λ��ԭ��ķ�����ͨ�����ô˺��������ѡ������һ��ģʽ��
������axis����ţ�
home_dir ���㷽��1��������0��������
vel �����ٶ�
mode ��ԭ����ź�ģʽ
1 �C һ�λ���
2 �C ���λ���
3 �C һ�λ���ӻ���
����ֵ���������
**********************************************************************/
SMC6200API  int32 __stdcall SMCConfigHomeMode(SMCHANDLE handle, uint8 axis,uint8 home_dir,double vel,uint8 mode);


/*************************************************************
˵������ȡĿ��λ��
���룺������handle ���
���������
����ֵ��������
*************************************************************/
SMC6200API  int32 __stdcall SMCGetAimPosition(SMCHANDLE handle, uint8 iaxis, double* pposition);
/*************************************************************
˵��������Ŀ��λ�ã������ڵ�λ�˶�ģʽ�£��������õ�Ŀ��λ��Ϊ����λ��
���룺������handle ��� ����
�����
����ֵ��������
*************************************************************/
SMC6200API  int32 __stdcall SMCSetAimPosition(SMCHANDLE handle, uint8 iaxis, double dposition);
#ifdef  __cplusplus
}
#endif

#endif
