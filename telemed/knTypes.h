/* Copyright (c) 2004-2022 Kotlin-Novator */

/***************************************************************************//**
* Файл содержит определения основных типов для всех поддерживаемых платформ.
*
* В начале находится код, определяющий, под какой платформой мы работаем.
* Данный код определит макрос KN_PLATFORM_STR,
* который будет содержать описание платформы в виде строки.
*
* Кроме того, будет определён один из этих макросов:
*    KN_VX      - для VxWorks
*    KN_WIN     - для Windows
*    KN_LINUX   - для Linux
*    KN_PIKE    - для PikeOS
*    KN_SYSBIOS - для SYS/BIOS (TMS)
*    KN_QNXNTO  - для QNX Neutrino
*
* Для случая VxWorks, в зависимости от версии, так же будет объявлен один из:
*    KN_VX_5_5
*    KN_VX_6_9
*    KN_VX_AE_2_4
*
* Если код драйверов/библиотек собирается не для ядра,
* а для защищённых разделов:
*    KN_VX_AE_PD
*
* На 64-битных платформах:
*    KN_64
*
* Также, для всех платформ будет объявлен один из этих двух макросов:
*    KN_BE - порядок байтов Big Endian
*    KN_LE - порядок байтов Little Endian
*
*  Макросы, определяющие архитектуру процессора и конкретный процессор:
*    KN_PPC          - Для всех PowerPC
*    KN_PPC_8245     - MPC8245
*    KN_PPC_8572     - MPC8572 и MPC8536
*    KN_PPC_T1042    - T1024
*    KN_ARM          - Для всех ARM
*    KN_ARM_DAVINCI  - DaVinci
*    KN_ARM_STM32    - Для всех STM32
*    KN_ARM_STM32F4  - Для STM32F4
*    KN_ARM_STM32F7  - Для STM32F7
*    KN_E2K          - Для всех Эльбрус 2К
*    KN_E2K_1C       - Для Эльбрус-1С, 1C+
*    KN_E2K_8C       - Для Эльбрус-8С, 8СВ
*    KN_X86          - x86
*    KN_KS           - KeyStone
*    KN_KS_TMS320C6X - TMS320C6X
*
*
* Все эти макросы при необходимости можно использовать в коде,
* чтобы определить платформу и порядок байтов на ней.
*
* Если код автоопределения платформы не сможет определить её,
* компиляция остановится с ошибкой и сообщением "PLATFORM NOT RECOGNIZED!".
*******************************************************************************/

#ifndef __KNTYPES_H_
#define __KNTYPES_H_

/******************************************************************************/

/*
  К этому моменту макросы типов процессоров могут быть не объявлены
  (если данный заголовочный файл был подключен раньше vxCpu.h).
  При этом, макрос CPU объявлен, и имеет значением какой-то из них.
  Чтобы провести сравнение типа процессора, нужно назначить макросам
  какие-то числа. Мы временно сделаем это, а потом вернём всё обратно.
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


/* Нас компилирует arm компилятор */
#if defined (__CC_ARM)   || defined (__TI_ARM__)      || \
    defined (__CSMC__)   || defined (__TASKING__)     || \
    defined (__ARM_ARCH) || defined (__ARMCC_VERSION)
    /* Известные компиляторы:
       TASKING Compiler __TASKING__, TI Arm Compiler   __TI_ARM__,
       IAR Compiler __ICCARM__, Arm Compiler 6 __ARMCC_VERSION,
       Arm Compiler 4/5 __CC_ARM */

    /*#define KN_ARM*/
    #define KN_ARM_STM32
    #define KN_LE

    #if defined (STM32F407xx) /* Макрос STM32F407xx взводит компилятор */
        #define KN_ARM_STM32F407
        #define KN_PLATFORM_STR "/STM32F407/LE"
    #elif defined (STM32H743xx) /* Макрос STM32H743xx взводит компилятор */
        #define KN_ARM_STM32H743
        #define KN_PLATFORM_STR "/STM32F743/LE"
    #else
        #define KN_PLATFORM_STR "/STM32/LE"
    #endif

#elif defined (__GNUC__)

    /* Нас компилирует GCC. Узнаем версию. */
    #define GCC_VERSION (__GNUC__*10000 + __GNUC_MINOR__*100 + __GNUC_PATCHLEVEL__)

    #if defined (__BIG_ENDIAN__) || defined (__BIGENDIAN__)
        #define KN_BE /* Платформа Big Endian. */
    #else
        #define KN_LE /* Платформа Little Endian. */
    #endif

    #if defined (__vxworks)

        /* Нас компилирует GCC под VxWorks. */
        #define KN_VX

        #if (PPC603 == CPU)
            /* Похоже, мы работаем с VxWorks 5.5 на MPC8245. */
            #define KN_PLATFORM_STR "VX5.5/PPC/8245/BE"
            #define KN_VX_5_5
            #define KN_PPC
            #define KN_PPC_8245
        #elif ((PPC604 == CPU) || (PPCE500V2 == CPU) || (PPC85XX == CPU))
            /* Похоже, мы работаем с VxWorks AE 653 2.4 на MPC8572. */
            #define KN_PLATFORM_STR "VX2.4/PPC/8572/BE"
            #define KN_VX_AE_2_4
            #define KN_PPC
            #define KN_PPC_8572

            #if (defined VTHREADS) || (defined VXWORKS_AE653_PARTITION_LIB)
                #define KN_VX_AE_PD
            #endif

        #elif ((ARMARCH4 == CPU) || (ARMARCH7 == CPU) || (_VX_ARMARCH7 == CPU))
            /* Похоже, мы работаем с VxWorks 6.9 на DaVinci. */
            #define KN_PLATFORM_STR "VX6.9/ARM/DaVinci/LE"
            #define KN_VX_6_9
            #define KN_ARM
            #define KN_ARM_DAVINCI
        #else
            /* Какая-то неподдерживаемая платформа. */
            #error "CPU NOT SUPPORTED!"
        #endif

    #elif defined (__PikeOS__)

        #define KN_PIKE

        #if defined (__PPC64__)
            /* Нас компилирует GCC под PikeOS для T1042. */
            #define KN_PLATFORM_STR "PIKEOS/PPC/T1042/BE"
            #define KN_PPC
            #define KN_PPC_T1042
            #define KN_64
        #elif (defined (__PPC__) && ("4.4.5 (PikeOS-77)" == __VERSION__))
            /* Похоже, мы работаем с PikeOS на MPC8572. */
            #define KN_PLATFORM_STR "PIKEOS/PPC/8572/BE"
            #define KN_PPC
            #define KN_PPC_8572
        #endif

    #elif defined (__gnu_linux__)

        #define KN_LINUX

        /* Нас компилирует GCC под GNU/Linux. */
        #define KN_PLATFORM_STR "LINUX/ARM/DaVinci/LE"
        #define KN_ARM
        #define KN_ARM_DAVINCI

    #elif defined (_WIN32)

        /* Нас компилирует GCC под Windows. */
        #define KN_PLATFORM_STR "WIN/X86/X86/LE"
        #define KN_WIN
        #define KN_X86

    #elif (defined (__pentiumpro__) && defined (__CYGWIN32__) && defined (KN_LE))

        /* Похоже, мы работаем с PikeOS на x86. */
        #define KN_PLATFORM_STR "PIKEOS/X86/X86/LE"
        #define KN_PIKE
        #define KN_X86

    #elif defined (__QNX__)

        /* Похоже, мы работаем с QNX. */
        #if defined (__QNXNTO__)
            /* Похоже, мы работаем с QNX Neutrino. */
            #define KN_QNXNTO

            #if defined (__PPC__) && defined (KN_BE)
                /* Похоже, мы работаем с QNX Neutrino на PPC. */
                #define KN_PLATFORM_STR "QNXNTO/PPC/85XX/BE"
                #define KN_PPC
                #define KN_PPC_8572
            #endif
        #else
            /* Похоже, мы работаем с QNX 4. */
        #endif
    #else
        /* Какая-то неподдерживаемая ОС. */
        #error "OS NOT SUPPORTED!"
    #endif


#elif defined (__LCC__) /* Нас компилирует LCC "MCST compiler" */

    #if defined (__e2k__) /* Архитектура Elbrus 2000 */

        #define KN_E2K
        #define KN_LE

        #if defined (E1C) /* Эльбрус 1C or 1C+ */
            #define KN_E2K_1C
            #define KN_PLATFORM_STR "QNXNTO/E2K_1C/LE"
        #else /* Предполагаем, что Эльбрус 8C или 8CВ */
            #define KN_E2K_8C
            #define KN_PLATFORM_STR "QNXNTO/E2K_8C/LE"
        #endif
    #else /* Архитектура SPARK */

        /* TODO? */

    #endif

#else /* Нас компилирует не GCC, или какая-то странная его модификация. */

    #if defined (_WIN32)
        /* Считаем, что мы под Windows. */
        #define KN_PLATFORM_STR "WIN/X86/X86/LE"
        #define KN_WIN
        #define KN_LE
        #define KN_X86
        #if defined QT_VERSION_STR
            /** Используются библиотеки Qt. */
            #define KN_QT
            /** \note   Когда данный код компилируется в статическую библиотеку
                        (KN_API.lib), макрос заране известен не будет
                        (то есть заранее развести библиотеку им нельзя),
                        но при подключении knTypes.h после любой библиотеки Qt
                        (которая в итоге подключает <QtCore/qglobal.h>)
                        будет определён.
                        #include <QApplication>
                        #include "knTypes.h"
            */
        #endif
    #elif defined (_TMS320C6X)
        /* Считаем, что мы под SYSBIOS/TMS. */
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

/* Вернём обратно значения типов процессоров, если определяли их. */
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
/* Спецификатор для инлайн-функций. */

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

/* Макрос для статической проверки выражений на этапе компиляции. */
#define STATIC_ASSERT(cond) STATIC_ASSERT_1((cond), __LINE__)

/* Вспомогательные макросы для работы STATIC_ASSERT. */
#define STATIC_ASSERT_1(cond, line) STATIC_ASSERT_2(cond, line)
#define STATIC_ASSERT_2(cond, line) typedef char \
    static_assertion_failed_at_line_##line[(cond)?1:-1];

/******************************************************************************/
/* Определения типов. */

#ifdef KN_VX

#include <VxWorks.h>

#ifdef __cplusplus

/** Указатель на функцию, возвращающую UINT32. */
typedef UINT32 (*U32FUNCPTR)(...);

#else /* Си */

/** Указатель на функцию, возвращающую UINT32. */
typedef UINT32 (*U32FUNCPTR)();

#endif

#else /* Для всех прочих платформ, кроме Vx (т.к. там эти типы уже объявлены). */

#ifdef KN_WIN
#include <stdint.h>
#endif

typedef signed char        INT8;   /**< 8-ми битное целое число со знаком.    */
typedef unsigned char      UINT8;  /**< Беззнаковое 8-ми битное целое число.  */

typedef short              INT16;  /**< 16-ти битное целое число со знаком.   */
typedef unsigned short     UINT16; /**< Беззнаковое 16-ти битное целое число. */

typedef int                INT32;  /**< 32-х битное целое число со знаком.    */
typedef unsigned int       UINT32; /**< Беззнаковое 32-х битное целое число.  */

typedef long long          INT64;  /**< 64-х битное целое число со знаком.    */
typedef unsigned long long UINT64; /**< Беззнаковое 64-х битное целое число.  */

typedef int                BOOL;   /**< Булевский тип по умолчанию. */

typedef INT32              STATUS; /**< Код результата.  */

#ifdef __cplusplus

/** Указатель на функцию, возвращающую INT32. */
typedef INT32   (*FUNCPTR)(...);

/** Указатель на функцию, возвращающую UINT32. */
typedef UINT32  (*U32FUNCPTR)(...);

/** Указатель на функцию, не возвращающую значения. */
typedef void    (*VOIDFUNCPTR)(...);

#else /* Си */

/** Указатель на функцию, возвращающую INT32. */
typedef INT32   (*FUNCPTR)();

/** Указатель на функцию, возвращающую UINT32. */
typedef UINT32  (*U32FUNCPTR)();

/** Указатель на функцию, возвращающую INT64. */
typedef INT64   (*I64FUNCPTR)();

/** Указатель на функцию, возвращающую UINT64. */
typedef UINT64  (*U64FUNCPTR)();
/** Указатель на функцию, не возвращающую значения. */
typedef void    (*VOIDFUNCPTR)();

#endif

#endif /* ifndef KN_VX */

typedef float      FLOAT32;/**< 32-х битное число с плавающей точкой. */
typedef double     FLOAT64;/**< 64-х битное число с плавающей точкой. */

typedef UINT8      BOOL8;  /**< 8-ми битный булевский тип.  */
typedef UINT16     BOOL16; /**< 16-ти битный булевский тип. */

#ifndef KN_VX_5_5
    typedef UINT32 BOOL32; /**< 32-х битный булевский тип.  */
#endif

/* Проверим, что размеры типов соответствуют ожидаемым. */
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

/** Идентификаторы основных типов данных. */
typedef enum
{
    KN_TYPE_UNKNOWN = 0, /**< Тип неизвестен. */
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
    KN_STRINGZ      = 13  /**< Строка, оканчивающаяся нулём. */

} KN_TYPE;

/******************************************************************************/
/* Определения констант. */

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
        #define NULL    nullptr    /**< Нулевой указатель. */
    #else
        #define NULL    ((void*)0) /**< Нулевой указатель. */
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
/* Представленные ниже сущности не следует использовать в новом коде!
Оставлено в целях обратной совместимости. */

#define BSP_FALSE   0
#define BSP_TRUE    1
#define BSP_ERROR   (-8)

/* Устаревшие типы данных. */
typedef UINT32 UNSIGNED32;  /**< Беззнаковое 32-х битное целое число.  */
typedef UINT16 UNSIGNED16;  /**< Беззнаковое 16-ти битное целое число. */
typedef INT32  SIGNED32;    /**< 32-х битное целое число со знаком.    */
typedef INT16  SIGNED16;    /**< 16-ти битное целое число со знаком.   */
typedef INT8   SIGNED8;     /**< 8-ми битное целое число со знаком.    */
typedef UINT8  UNSIGNED8;   /**< Беззнаковое 8-ми битное целое число.  */
typedef char   CHAR;        /**< 8-ти битное целое число со знаком.    */

                            /* Старые типы. Оставим для совместимости. */
typedef char           BSP_CHAR;   /**< 8-ми битное целое число со знаком.    */
typedef short          BSP_SHORT;  /**< 16-ти битное целое число со знаком.   */
typedef int            BSP_INT;    /**< 32-х битное целое число со знаком.    */
typedef float          BSP_FLOAT;  /**< 32-х битное число с плавающей точкой. */
typedef double         BSP_DOUBLE; /**< 64-х битное число с плавающей точкой. */
typedef unsigned char  BSP_UCHAR;  /**< Беззнаковое 8-ми битное целое число.  */
typedef unsigned int   BSP_UINT;   /**< Беззнаковое 32-х битное целое число.  */
typedef unsigned short BSP_USHORT; /**< Беззнаковое 16-ти битное целое число. */
typedef unsigned char  BSP_BOOL;   /**< 8-ми битный булевский тип.            */
typedef long           BSP_LONG;   /**< 32-х битное целое число со знаком.    */
typedef unsigned long  BSP_ULONG;  /**< Беззнаковое 32-х битное целое число.  */

/******************************************************************************/

/** TODO Возможно, cтруктура нигде не используется. Проверить.
    \deprecated */
typedef union
{
    INT32   int_val[2];
    FLOAT64 dval;

} BSP_BIT64;


/** Cтруктура для работы с таймером.
\deprecated */
typedef struct
{
    INT32 sec;   /**< Секунды. */
    INT32 usec;  /**< Микросекунды. */

} BSP_TIME;


/** Структура для работы с последовательным каналом.
TODO Возможно, cтруктура нигде не используется. Проверить.
\deprecated */
typedef struct
{
    INT32 baudRate;    /**< От BAUD_RATE_50 до BAUD_RATE_230400,
                            или определяется пользователем. */
    INT32 parity;      /**< _PARITY_NONE, PARITY_EVEN или PARITY_ODD. */
    INT32 dataSize;    /**< DATA_SIZE_5 - DATA_SIZE_8. */
    INT32 numStopBits; /**< STOP_BITS_1, STOP_BITS_1_5, или STOP_BITS_2. */

} BSP_STTY;

/** TODO Возможно, cтруктура нигде не используется. Проверить.
\deprecated */
typedef struct
{
    void *pPhysAddr;
    void *pVirtAddr;
    UINT32 length;

} SG_MAP_INFO;

/******************************************************************************/

#endif /* __KNTYPES_H_ */
