#include "smc6200.h"

typedef unsigned char           MC_BOOL;
typedef char                    MC_C8;
typedef unsigned char           MC_U8;
typedef signed char             MC_S8;

typedef unsigned short int      MC_U16;
typedef unsigned int            MC_U32;
typedef unsigned long int       MC_U64;

typedef short int               MC_S16;
typedef int                     MC_S32;
typedef long int                MC_S64;

typedef float                   MC_F32;
typedef double                  MC_F64;

typedef struct MC_CODE_BUF
{
	MC_U8           CodeType;   /** < Two commands,G-Code,M-Code */
	MC_S16          CodeId;     /** < The id of the code */
//	MC_CODE_FORMAT  CodeFromat;
} MC_CODE_BUF, MC_SEND_BUF;
