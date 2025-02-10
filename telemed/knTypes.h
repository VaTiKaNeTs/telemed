/* Copyright (c) 2004-2022 Kotlin-Novator */

/***************************************************************************//**
* ���� �������� ����������� �������� ����� ��� ���� �������������� ��������.
*
* � ������ ��������� ���, ������������, ��� ����� ���������� �� ��������.
* ������ ��� ��������� ������ KN_PLATFORM_STR,
* ������� ����� ��������� �������� ��������� � ���� ������.
*
* ����� ����, ����� �������� ���� �� ���� ��������:
*    KN_VX      - ��� VxWorks
*    KN_WIN     - ��� Windows
*    KN_LINUX   - ��� Linux
*    KN_PIKE    - ��� PikeOS
*    KN_SYSBIOS - ��� SYS/BIOS (TMS)
*    KN_QNXNTO  - ��� QNX Neutrino
*
* ��� ������ VxWorks, � ����������� �� ������, ��� �� ����� �������� ���� ��:
*    KN_VX_5_5
*    KN_VX_6_9
*    KN_VX_AE_2_4
*
* ���� ��� ���������/��������� ���������� �� ��� ����,
* � ��� ���������� ��������:
*    KN_VX_AE_PD
*
* �� 64-������ ����������:
*    KN_64
*
* �����, ��� ���� �������� ����� �������� ���� �� ���� ���� ��������:
*    KN_BE - ������� ������ Big Endian
*    KN_LE - ������� ������ Little Endian
*
*  �������, ������������ ����������� ���������� � ���������� ���������:
*    KN_PPC          - ��� ���� PowerPC
*    KN_PPC_8245     - MPC8245
*    KN_PPC_8572     - MPC8572 � MPC8536
*    KN_PPC_T1042    - T1024
*    KN_ARM          - ��� ���� ARM
*    KN_ARM_DAVINCI  - DaVinci
*    KN_ARM_STM32    - ��� ���� STM32
*    KN_ARM_STM32F4  - ��� STM32F4
*    KN_ARM_STM32F7  - ��� STM32F7
*    KN_E2K          - ��� ���� ������� 2�
*    KN_E2K_1C       - ��� �������-1�, 1C+
*    KN_E2K_8C       - ��� �������-8�, 8��
*    KN_X86          - x86
*    KN_KS           - KeyStone
*    KN_KS_TMS320C6X - TMS320C6X
*
*
* ��� ��� ������� ��� ������������� ����� ������������ � ����,
* ����� ���������� ��������� � ������� ������ �� ���.
*
* ���� ��� ��������������� ��������� �� ������ ���������� �,
* ���������� ����������� � ������� � ���������� "PLATFORM NOT RECOGNIZED!".
*******************************************************************************/

#ifndef __KNTYPES_H_
#define __KNTYPES_H_

/******************************************************************************/

/*
  � ����� ������� ������� ����� ����������� ����� ���� �� ���������
  (���� ������ ������������ ���� ��� ��������� ������ vxCpu.h).
  ��� ����, ������ CPU ��������, � ����� ��������� �����-�� �� ���.
  ����� �������� ��������� ���� ����������, ����� ��������� ��������
  �����-�� �����. �� �������� ������� ���, � ����� ����� �� �������.
*/
#ifndef PPC603
    #define PPC603       100500
#endif

#ifndef PPC604
    #define PPC604       100501
#endif

#ifndef PPCE500V2
    #define PPCE500V2    100502
#endif

#ifndef PPCE500MC
    #define PPCE500MC    100503
#endif

#ifndef ARMARCH4
    #define ARMARCH4     100504
#endif

#ifndef ARMARCH7
    #define ARMARCH7     100505
#endif

#ifndef _VX_ARMARCH7
    #define _VX_ARMARCH7 100506
#endif

#ifndef PPC85XX
    #define PPC85XX      100507
#endif

#ifndef ELBRUS
    #define ELBRUS       100508
#endif

#ifndef CORTEX_ARM4
    #define CORTEX_ARM4  100509
#endif

#ifndef CORTEX_ARM7
    #define CORTEX_ARM7  100510
#endif


/* ��� ����������� arm ���������� */
#if defined (__CC_ARM)   || defined (__TI_ARM__)      || \
    defined (__CSMC__)   || defined (__TASKING__)     || \
    defined (__ARM_ARCH) || defined (__ARMCC_VERSION)
    /* ��������� �����������:
       TASKING Compiler __TASKING__, TI Arm Compiler   __TI_ARM__,
       IAR Compiler __ICCARM__, Arm Compiler 6 __ARMCC_VERSION,
       Arm Compiler 4/5 __CC_ARM */

    /*#define KN_ARM*/
    #define KN_ARM_STM32
    #define KN_LE

    #if defined (STM32F407xx) /* ������ STM32F407xx ������� ���������� */
        #define KN_ARM_STM32F407
        #define KN_PLATFORM_STR "/STM32F407/LE"
    #elif defined (STM32H743xx) /* ������ STM32H743xx ������� ���������� */
        #define KN_ARM_STM32H743
        #define KN_PLATFORM_STR "/STM32F743/LE"
    #else
        #define KN_PLATFORM_STR "/STM32/LE"
    #endif

#elif defined (__GNUC__)

    /* ��� ����������� GCC. ������ ������. */
    #define GCC_VERSION (__GNUC__*10000 + __GNUC_MINOR__*100 + __GNUC_PATCHLEVEL__)

    #if defined (__BIG_ENDIAN__) || defined (__BIGENDIAN__)
        #define KN_BE /* ��������� Big Endian. */
    #else
        #define KN_LE /* ��������� Little Endian. */
    #endif

    #if defined (__vxworks)

        /* ��� ����������� GCC ��� VxWorks. */
        #define KN_VX

        #if (PPC603 == CPU)
            /* ������, �� �������� � VxWorks 5.5 �� MPC8245. */
            #define KN_PLATFORM_STR "VX5.5/PPC/8245/BE"
            #define KN_VX_5_5
            #define KN_PPC
            #define KN_PPC_8245
        #elif ((PPC604 == CPU) || (PPCE500V2 == CPU) || (PPC85XX == CPU))
            /* ������, �� �������� � VxWorks AE 653 2.4 �� MPC8572. */
            #define KN_PLATFORM_STR "VX2.4/PPC/8572/BE"
            #define KN_VX_AE_2_4
            #define KN_PPC
            #define KN_PPC_8572

            #if (defined VTHREADS) || (defined VXWORKS_AE653_PARTITION_LIB)
                #define KN_VX_AE_PD
            #endif

        #elif ((ARMARCH4 == CPU) || (ARMARCH7 == CPU) || (_VX_ARMARCH7 == CPU))
            /* ������, �� �������� � VxWorks 6.9 �� DaVinci. */
            #define KN_PLATFORM_STR "VX6.9/ARM/DaVinci/LE"
            #define KN_VX_6_9
            #define KN_ARM
            #define KN_ARM_DAVINCI
        #else
            /* �����-�� ���������������� ���������. */
            #error "CPU NOT SUPPORTED!"
        #endif

    #elif defined (__PikeOS__)

        #define KN_PIKE

        #if defined (__PPC64__)
            /* ��� ����������� GCC ��� PikeOS ��� T1042. */
            #define KN_PLATFORM_STR "PIKEOS/PPC/T1042/BE"
            #define KN_PPC
            #define KN_PPC_T1042
            #define KN_64
        #elif (defined (__PPC__) && ("4.4.5 (PikeOS-77)" == __VERSION__))
            /* ������, �� �������� � PikeOS �� MPC8572. */
            #define KN_PLATFORM_STR "PIKEOS/PPC/8572/BE"
            #define KN_PPC
            #define KN_PPC_8572
        #endif

    #elif defined (__gnu_linux__)

        #define KN_LINUX

        /* ��� ����������� GCC ��� GNU/Linux. */
        #define KN_PLATFORM_STR "LINUX/ARM/DaVinci/LE"
        #define KN_ARM
        #define KN_ARM_DAVINCI

    #elif defined (_WIN32)

        /* ��� ����������� GCC ��� Windows. */
        #define KN_PLATFORM_STR "WIN/X86/X86/LE"
        #define KN_WIN
        #define KN_X86

    #elif (defined (__pentiumpro__) && defined (__CYGWIN32__) && defined (KN_LE))

        /* ������, �� �������� � PikeOS �� x86. */
        #define KN_PLATFORM_STR "PIKEOS/X86/X86/LE"
        #define KN_PIKE
        #define KN_X86

    #elif defined (__QNX__)

        /* ������, �� �������� � QNX. */
        #if defined (__QNXNTO__)
            /* ������, �� �������� � QNX Neutrino. */
            #define KN_QNXNTO

            #if defined (__PPC__) && defined (KN_BE)
                /* ������, �� �������� � QNX Neutrino �� PPC. */
                #define KN_PLATFORM_STR "QNXNTO/PPC/85XX/BE"
                #define KN_PPC
                #define KN_PPC_8572
            #endif
        #else
            /* ������, �� �������� � QNX 4. */
        #endif
    #else
        /* �����-�� ���������������� ��. */
        #error "OS NOT SUPPORTED!"
    #endif


#elif defined (__LCC__) /* ��� ����������� LCC "MCST compiler" */

    #if defined (__e2k__) /* ����������� Elbrus 2000 */

        #define KN_E2K
        #define KN_LE

        #if defined (E1C) /* ������� 1C or 1C+ */
            #define KN_E2K_1C
            #define KN_PLATFORM_STR "QNXNTO/E2K_1C/LE"
        #else /* ������������, ��� ������� 8C ��� 8C� */
            #define KN_E2K_8C
            #define KN_PLATFORM_STR "QNXNTO/E2K_8C/LE"
        #endif
    #else /* ����������� SPARK */

        /* TODO? */

    #endif

#else /* ��� ����������� �� GCC, ��� �����-�� �������� ��� �����������. */

    #if defined (_WIN32)
        /* �������, ��� �� ��� Windows. */
        #define KN_PLATFORM_STR "WIN/X86/X86/LE"
        #define KN_WIN
        #define KN_LE
        #define KN_X86
        #if defined QT_VERSION_STR
            /** ������������ ���������� Qt. */
            #define KN_QT
            /** \note   ����� ������ ��� ������������� � ����������� ����������
                        (KN_API.lib), ������ ������ �������� �� �����
                        (�� ���� ������� �������� ���������� �� ������),
                        �� ��� ����������� knTypes.h ����� ����� ���������� Qt
                        (������� � ����� ���������� <QtCore/qglobal.h>)
                        ����� ��������.
                        #include <QApplication>
                        #include "knTypes.h"
            */
        #endif
    #elif defined (_TMS320C6X)
        /* �������, ��� �� ��� SYSBIOS/TMS. */
        #define KN_TMS
        #define KN_KS
        #define KN_KS_TMS320C6X
        #define KN_SYSBIOS

        #ifdef _BIG_ENDIAN
            #define KN_BE
            #define KN_PLATFORM_STR "SYSBIOS/KS/TMS320C6X/BE"
        #else
            #define KN_LE
            #define KN_PLATFORM_STR "SYSBIOS/KS/TMS320C6X/LE"
        #endif

    #endif

#endif

#ifndef KN_PLATFORM_STR
    #error "PLATFORM NOT RECOGNIZED!"
#endif

/* ����� ������� �������� ����� �����������, ���� ���������� ��. */
#if (PPC603 >= 100500)
    #undef PPC603
#endif

#if (PPC604 >= 100500)
    #undef PPC604
#endif

#if (PPCE500V2 >= 100500)
    #undef PPCE500V2
#endif

#if (PPCE500MC >= 100500)
    #undef PPCE500MC
#endif

#if (ARMARCH4 >= 100500)
    #undef ARMARCH4
#endif

#if (ARMARCH7 >= 100500)
    #undef ARMARCH7
#endif

#if (_VX_ARMARCH7 >= 100500)
    #undef _VX_ARMARCH7
#endif

#if (PPC85XX >= 100500)
    #undef PPC85XX
#endif

#if (ELBRUS >= 100500)
    #undef ELBRUS
#endif

#if (CORTEX_ARM4 >= 100500)
    #undef CORTEX_ARM4
#endif

#if (CORTEX_ARM7 >= 100500)
    #undef CORTEX_ARM7
#endif

/******************************************************************************/
/* ������������ ��� ������-�������. */

#ifdef GCC_VERSION
    #if (GCC_VERSION > 30200)
        #define KN_INLINE static __inline__ __attribute__((always_inline))
    #else
        #define KN_INLINE static __inline__
    #endif
#elif defined __GNUC__
    #define KN_INLINE static __inline
#elif defined __CC_ARM
    /* TODO? */
    #define KN_INLINE static __inline __attribute__((always_inline))
#elif defined __LCC__
    /* TODO? */
    #define KN_INLINE static __inline__ __attribute__((always_inline))
#else
    #ifdef KN_TMS /* SYSBIOS. */
        #define KN_INLINE static inline
    #elif defined KN_WIN /* Win/MSVS. */
        #define KN_INLINE static __forceinline
    #endif
#endif

/******************************************************************************/

/* ������ ��� ����������� �������� ��������� �� ����� ����������. */
#define STATIC_ASSERT(cond) STATIC_ASSERT_1((cond), __LINE__)

/* ��������������� ������� ��� ������ STATIC_ASSERT. */
#define STATIC_ASSERT_1(cond, line) STATIC_ASSERT_2(cond, line)
#define STATIC_ASSERT_2(cond, line) typedef char \
    static_assertion_failed_at_line_##line[(cond)?1:-1];

/******************************************************************************/
/* ����������� �����. */

#ifdef KN_VX

#include <VxWorks.h>

#ifdef __cplusplus

/** ��������� �� �������, ������������ UINT32. */
typedef UINT32 (*U32FUNCPTR)(...);

#else /* �� */

/** ��������� �� �������, ������������ UINT32. */
typedef UINT32 (*U32FUNCPTR)();

#endif

#else /* ��� ���� ������ ��������, ����� Vx (�.�. ��� ��� ���� ��� ���������). */

#ifdef KN_WIN
#include <stdint.h>
#endif

typedef signed char        INT8;   /**< 8-�� ������ ����� ����� �� ������.    */
typedef unsigned char      UINT8;  /**< ����������� 8-�� ������ ����� �����.  */

typedef short              INT16;  /**< 16-�� ������ ����� ����� �� ������.   */
typedef unsigned short     UINT16; /**< ����������� 16-�� ������ ����� �����. */

typedef int                INT32;  /**< 32-� ������ ����� ����� �� ������.    */
typedef unsigned int       UINT32; /**< ����������� 32-� ������ ����� �����.  */

typedef long long          INT64;  /**< 64-� ������ ����� ����� �� ������.    */
typedef unsigned long long UINT64; /**< ����������� 64-� ������ ����� �����.  */

typedef int                BOOL;   /**< ��������� ��� �� ���������. */

typedef INT32              STATUS; /**< ��� ����������.  */

#ifdef __cplusplus

/** ��������� �� �������, ������������ INT32. */
typedef INT32   (*FUNCPTR)(...);

/** ��������� �� �������, ������������ UINT32. */
typedef UINT32  (*U32FUNCPTR)(...);

/** ��������� �� �������, �� ������������ ��������. */
typedef void    (*VOIDFUNCPTR)(...);

#else /* �� */

/** ��������� �� �������, ������������ INT32. */
typedef INT32   (*FUNCPTR)();

/** ��������� �� �������, ������������ UINT32. */
typedef UINT32  (*U32FUNCPTR)();

/** ��������� �� �������, ������������ INT64. */
typedef INT64   (*I64FUNCPTR)();

/** ��������� �� �������, ������������ UINT64. */
typedef UINT64  (*U64FUNCPTR)();
/** ��������� �� �������, �� ������������ ��������. */
typedef void    (*VOIDFUNCPTR)();

#endif

#endif /* ifndef KN_VX */

typedef float      FLOAT32;/**< 32-� ������ ����� � ��������� ������. */
typedef double     FLOAT64;/**< 64-� ������ ����� � ��������� ������. */

typedef UINT8      BOOL8;  /**< 8-�� ������ ��������� ���.  */
typedef UINT16     BOOL16; /**< 16-�� ������ ��������� ���. */

#ifndef KN_VX_5_5
    typedef UINT32 BOOL32; /**< 32-� ������ ��������� ���.  */
#endif

/* ��������, ��� ������� ����� ������������� ���������. */
STATIC_ASSERT(1 == sizeof(INT8));
STATIC_ASSERT(1 == sizeof(UINT8));
STATIC_ASSERT(2 == sizeof(INT16));
STATIC_ASSERT(2 == sizeof(UINT16));
STATIC_ASSERT(4 == sizeof(INT32));
STATIC_ASSERT(4 == sizeof(UINT32));
STATIC_ASSERT(8 == sizeof(INT64));
STATIC_ASSERT(8 == sizeof(UINT64));
STATIC_ASSERT(4 == sizeof(FLOAT32));
STATIC_ASSERT(8 == sizeof(FLOAT64));
STATIC_ASSERT(4 == sizeof(STATUS));

/** �������������� �������� ����� ������. */
typedef enum
{
    KN_TYPE_UNKNOWN = 0, /**< ��� ����������. */
    KN_INT8         = 1,
    KN_UINT8        = 2,
    KN_INT16        = 3,
    KN_UINT16       = 4,
    KN_INT32        = 5,
    KN_UINT32       = 6,
    KN_INT64        = 7,
    KN_UINT64       = 8,
    KN_FLOAT32      = 9,
    KN_FLOAT64      = 10,
    KN_BOOL8        = 11,
    KN_BOOL         = 12,
    KN_STRINGZ      = 13  /**< ������, �������������� ����. */

} KN_TYPE;

/******************************************************************************/
/* ����������� ��������. */

#define KN_OK        0
#define KN_ERROR     (-1)
#define UINT32_ERROR 0xFFFFFFFFU

#ifndef KN_ARM_STM32
    #ifndef OK
        #define OK      KN_OK
    #endif

    #ifndef ERROR
        #define ERROR   KN_ERROR
    #endif
#endif

#ifndef FALSE
    #define FALSE   0
#endif

#ifndef TRUE
    #define TRUE    1
#endif

#ifndef NULL
    #ifdef __cplusplus
        #define NULL    nullptr    /**< ������� ���������. */
    #else
        #define NULL    ((void*)0) /**< ������� ���������. */
    #endif
#endif

#ifdef KN_VX
    #define KN_EAGAIN   EAGAIN
#elif defined KN_QNXNTO
    #define KN_EAGAIN   (-11)
#endif

STATIC_ASSERT(0  == KN_OK);
STATIC_ASSERT(-1 == KN_ERROR);

/******************************************************************************/
/* �������������� ���� �������� �� ������� ������������ � ����� ����!
��������� � ����� �������� �������������. */

#define BSP_FALSE   0
#define BSP_TRUE    1
#define BSP_ERROR   (-8)

/* ���������� ���� ������. */
typedef UINT32 UNSIGNED32;  /**< ����������� 32-� ������ ����� �����.  */
typedef UINT16 UNSIGNED16;  /**< ����������� 16-�� ������ ����� �����. */
typedef INT32  SIGNED32;    /**< 32-� ������ ����� ����� �� ������.    */
typedef INT16  SIGNED16;    /**< 16-�� ������ ����� ����� �� ������.   */
typedef INT8   SIGNED8;     /**< 8-�� ������ ����� ����� �� ������.    */
typedef UINT8  UNSIGNED8;   /**< ����������� 8-�� ������ ����� �����.  */
typedef char   CHAR;        /**< 8-�� ������ ����� ����� �� ������.    */

                            /* ������ ����. ������� ��� �������������. */
typedef char           BSP_CHAR;   /**< 8-�� ������ ����� ����� �� ������.    */
typedef short          BSP_SHORT;  /**< 16-�� ������ ����� ����� �� ������.   */
typedef int            BSP_INT;    /**< 32-� ������ ����� ����� �� ������.    */
typedef float          BSP_FLOAT;  /**< 32-� ������ ����� � ��������� ������. */
typedef double         BSP_DOUBLE; /**< 64-� ������ ����� � ��������� ������. */
typedef unsigned char  BSP_UCHAR;  /**< ����������� 8-�� ������ ����� �����.  */
typedef unsigned int   BSP_UINT;   /**< ����������� 32-� ������ ����� �����.  */
typedef unsigned short BSP_USHORT; /**< ����������� 16-�� ������ ����� �����. */
typedef unsigned char  BSP_BOOL;   /**< 8-�� ������ ��������� ���.            */
typedef long           BSP_LONG;   /**< 32-� ������ ����� ����� �� ������.    */
typedef unsigned long  BSP_ULONG;  /**< ����������� 32-� ������ ����� �����.  */

/******************************************************************************/

/** TODO ��������, c�������� ����� �� ������������. ���������.
    \deprecated */
typedef union
{
    INT32   int_val[2];
    FLOAT64 dval;

} BSP_BIT64;


/** C�������� ��� ������ � ��������.
\deprecated */
typedef struct
{
    INT32 sec;   /**< �������. */
    INT32 usec;  /**< ������������. */

} BSP_TIME;


/** ��������� ��� ������ � ���������������� �������.
TODO ��������, c�������� ����� �� ������������. ���������.
\deprecated */
typedef struct
{
    INT32 baudRate;    /**< �� BAUD_RATE_50 �� BAUD_RATE_230400,
                            ��� ������������ �������������. */
    INT32 parity;      /**< _PARITY_NONE, PARITY_EVEN ��� PARITY_ODD. */
    INT32 dataSize;    /**< DATA_SIZE_5 - DATA_SIZE_8. */
    INT32 numStopBits; /**< STOP_BITS_1, STOP_BITS_1_5, ��� STOP_BITS_2. */

} BSP_STTY;

/** TODO ��������, c�������� ����� �� ������������. ���������.
\deprecated */
typedef struct
{
    void *pPhysAddr;
    void *pVirtAddr;
    UINT32 length;

} SG_MAP_INFO;

/******************************************************************************/

#endif /* __KNTYPES_H_ */
