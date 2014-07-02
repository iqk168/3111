#define ADLINK_MATRIX_WDT_API

#ifdef __cplusplus
extern "C" {
#endif

SHORT __stdcall GPIO_Init(void);
SHORT __stdcall GPI_Read(unsigned short* pwState);
SHORT __stdcall GPO_Write(unsigned short wState);

#define NoError                     0
#define ErrorOpenDriverFailed      -13
#define ErrorDeviceIoctl           -200

typedef short                I16;
typedef unsigned short       U16;

#ifdef __cplusplus
}
#endif