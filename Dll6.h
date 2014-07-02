#ifdef __cplusplus
extern "C" {
#endif

//Dll6 Data Types
typedef unsigned char   U8;
typedef short           I16;
typedef unsigned short  U16;
typedef long            I32;
typedef unsigned long   U32;
typedef float           F32;
typedef double          F64;

//Parity
#ifndef NOPARITY
#define NOPARITY        0
#endif
#ifndef ODDPARITY
#define ODDPARITY       1
#endif
#ifndef EVENPARITY
#define EVENPARITY      2
#endif

//Stop bits
#ifndef ONESTOPBIT
#define ONESTOPBIT      0
#endif
#ifndef ONE5STOPBITS
#define ONE5STOPBITS    1
#endif
#ifndef TWOSTOPBITS
#define TWOSTOPBITS     2
#endif

//Baud Rate
#define BAUDRATE_1200   3
#define BAUDRATE_2400   4
#define BAUDRATE_4800   5
#define BAUDRATE_9600   6
#define BAUDRATE_19200  7
#define BAUDRATE_38400  8
#define BAUDRATE_115200 9
#define BAUDRATE_57600  10  //0x0A

//Alarm Setting
#define NOALARM         0
#define MOMENTARY       1
#define LATCH           2

//Data Format
#define ENGINEERING_UNITS  0   //A/D & D/A
#define PERCENTAGE_FSR     1   //A/D & D/A
#define HEXADECIMAL        2   //A/D & D/A
#define OHMS               3   //A/D

//Analog Input Channel
#define CHANNEL0           0x01
#define CHANNEL1           0x02
#define CHANNEL2           0x04
#define CHANNEL3           0x08
#define CHANNEL4           0x10
#define CHANNEL5           0x20
#define CHANNEL6           0x40
#define CHANNEL7           0x80

//Counter Input Mode
#define TTL                0
#define PHOTO_ISOLATED     1

//Counter Gate Mode
#define GATE_LOW           0
#define GATE_HIGH          1
#define GATE_DISABLE       2

//ND6521 Addressable Mode
#define ADDRESSABLE        0
#define NON_ADDRESSABLE    1

//ND6521 RS-422/485 Interfce
#define RS_422             0
#define RS_485             1

//ND6521 Append CR in output string
#define NOT_APPEND_CR      0
#define APPEND_CR          1


//Error Codes
//#define NO_ERROR                 0
#define INVALID_COMMAND         -1
#define DEVICE_ALREADY_OPEN     -2
#define DEVICE_NOT_OPEN         -3
#define MEMORY_ERROR            -4
#define DEVICE_LOCK             -10
#define INVALID_BAUDRATE        -12
#define COMMUNICATION_ERROR     -13
#define COMMUNICATION_TIMEOUT   -14
#define CHECKSUM_ERROR          -15
#define BAD_MODULE_TYPE         -16
#define BAD_DATA_VALUE          -17
#define INVALID_COUNTER         -18
#define BAD_PORT_VALUE          -19

typedef LPSTR   DATA;
typedef LPSTR   STRING;

typedef  struct  ND_Config
{
  U16      address;
  U16      type;
  U16      range;
  U16      baudRate;
  U16      checkSum;
  U16      dataFormat;
} NDCONFIG;

typedef  struct  ND6521_Config
{
  U16      address;
  U16      baudRate232;
  U16      baudRate422;
  U16      checkSum;
  U16      addressableMode;  //ADDRESSABLE, NON_ADDRESSABLE
  U16      interfaceType;    //RS_422, RS_485
  U16      appendCR;         //NOT_APPEND_AR, APPEND_CR
  U16      parityMode;       //NOPARITY, ODDPARITY, EVENPARITY
  U16      stopbits;         //ONESTOPBIT, TWOSTOPBITS
  U16      databits;         //5, 6, 7, or 8
} ND6521CONFIG;


//Function Declarations
I16 FAR PASCAL ND_InitialComm(U16 com_port, U16 baud_rate, U16 data_bits, U16 parity, U16 stop_bits);
I16 FAR PASCAL ND_ReleaseComm(U16 com_port);
I16 FAR PASCAL ND_EnableChecksum(U16 com_port);
I16 FAR PASCAL ND_DisableChecksum(U16 com_port);
I16 FAR PASCAL ND_Sync(U16 com_port);
I16 FAR PASCAL ND_ReadSyncData(U16 com_port, U16 m_id, DATA data, U16 module_type);
I16 FAR PASCAL ND_SetConfig(U16 com_port, U16 m_id, NDCONFIG FAR *config);
I16 FAR PASCAL ND_GetConfig(U16 com_port, U16 m_id, NDCONFIG FAR *config);
I16 FAR PASCAL ND_GetVersion(U16 com_port, U16 m_id, DATA version);
I16 FAR PASCAL ND_GetModuleName(U16 com_port, U16 m_id, DATA name);
I16 FAR PASCAL ND_ReadAI(U16 com_port, U16 m_id, DATA data);
I16 FAR PASCAL ND_ReadAllAI(U16 com_port, U16 m_id, DATA data0, DATA data1, DATA data2);
I16 FAR PASCAL ND_SetMUXChans(U16 com_port, U16 m_id, U16 enable_chans);
I16 FAR PASCAL ND_ReadChanStatus(U16 com_port, U16 m_id, U16 FAR *chan_status);
I16 FAR PASCAL ND_ReadChanAI(U16 com_port, U16 m_id, U16 ch_no, DATA data);
I16 FAR PASCAL ND_WriteAO(U16 com_port, U16 m_id, DATA data);
I16 FAR PASCAL ND_WriteChanAO(U16 com_port, U16 m_id, U16 ch_no, DATA data);
I16 FAR PASCAL ND_ReadBackAO(U16 com_port, U16 m_id, DATA data);
I16 FAR PASCAL ND_ResetStatusAO(U16 com_port, U16 m_id, U16 FAR *status);
I16 FAR PASCAL ND_ReadDI(U16 com_port, U16 m_id, U32 FAR *data, U16 module_type);
I16 FAR PASCAL ND_WriteDOPort(U16 com_port, U16 m_id, U16 do_port, U16 do_data, U16 module_type);
I16 FAR PASCAL ND_WriteDOLine(U16 com_port, U16 m_id, U16 do_port, U16 do_line, U16 do_data, U16 module_type);
I16 FAR PASCAL ND_ReadBackDO(U16 com_port, U16 m_id, U16 FAR *data, U16 module_type);
I16 FAR PASCAL ND_GetHighAlarmLimit(U16 com_port, U16 m_id, DATA hi_alarm);
I16 FAR PASCAL ND_GetLowAlarmLimit(U16 com_port, U16 m_id, DATA lo_alarm);
I16 FAR PASCAL ND_SetHighAlarmLimit(U16 com_port, U16 m_id, DATA hi_alarm);
I16 FAR PASCAL ND_SetLowAlarmLimit(U16 com_port, U16 m_id, DATA lo_alarm);
I16 FAR PASCAL ND_GetAlarmStatus(U16 com_port, U16 m_id, U16 FAR *alarm_status);
I16 FAR PASCAL ND_EnableAlarm(U16 com_port, U16 m_id, U16 alarm_type);
I16 FAR PASCAL ND_DisableAlarm(U16 com_port, U16 m_id);
I16 FAR PASCAL ND_ClearLatchAlarm(U16 com_port, U16 m_id);
I16 FAR PASCAL ND_ReadCJC(U16 com_port, U16 m_id, DATA data);
I16 FAR PASCAL ND_ReadEventCount(U16 com_port, U16 m_id, DATA data);
I16 FAR PASCAL ND_ResetEventCount(U16 com_port, U16 m_id);
I16 FAR PASCAL ND_SetIoPolarity(U16 com_port, U16 m_id, U16 polarity_state);

I16 FAR PASCAL ND_SendCommand(U16 com_port, STRING command, STRING result);
I16 FAR PASCAL ND_TimeOut(U16 com_port, U16 m_sec);
I16 FAR PASCAL ND_SetWDT(U16 com_port, U16 m_id, U16 enable, U16 timeout, U16 safe_state);
I16 FAR PASCAL ND_SetWDT6021(U16 com_port, U16 m_id, U16 enable, U16 timeout, U16 safe_mode);
I16 FAR PASCAL ND_SetWDT6024(U16 com_port, U16 m_id, U16 enable, U16 timeout, U16 PortA_mode, U16 PortB_mode, U16 PortC_mode, U16 PortD_mode);
I16 FAR PASCAL ND_GetWDT(U16 com_port, U16 m_id, U16 FAR *enable, U16 FAR *timeout, U16 FAR *safe_state);
I16 FAR PASCAL ND_GetWDT6021(U16 com_port, U16 m_id, U16 FAR *enable, U16 FAR *timeout, U16 FAR *safe_mode);
I16 FAR PASCAL ND_GetWDT6024(U16 com_port, U16 m_id, U16 FAR *enable, U16 FAR *timeout, U16 FAR *PortA_mode, U16 FAR *PortB_mode, U16 FAR *PortC_mode, U16 FAR *PortD_mode);
I16 FAR PASCAL ND_HostOK(U16 com_port);
I16 FAR PASCAL ND_ConfigLeadingCode(U16 com_port, U16 m_id, DATA leading_code_string);

//6058 Functions
I16 FAR PASCAL ND_SetDioMode(U16 com_port, U16 m_id, U16 dio_mode);
I16 FAR PASCAL ND_GetDioMode(U16 com_port, U16 m_id, U16 *dio_mode);

//6080 Functions
I16 FAR PASCAL ND_SetCtrInputMode(U16 com_port, U16 m_id, U16 input_mode);
I16 FAR PASCAL ND_ReadCtrInputMode(U16 com_port, U16 m_id, U16 FAR *input_mode);
I16 FAR PASCAL ND_ReadCtrValue(U16 com_port, U16 m_id, U16 counter, U32 FAR *ctr_value);
I16 FAR PASCAL ND_SetCtrGateMode(U16 com_port, U16 m_id, U16 gate_mode);
I16 FAR PASCAL ND_ReadCtrGateMode(U16 com_port, U16 m_id, U16 FAR *gate_mode);
I16 FAR PASCAL ND_SetCtrMaxValue(U16 com_port, U16 m_id, U16 counter, U32 max_value);
I16 FAR PASCAL ND_ReadCtrMaxValue(U16 com_port, U16 m_id, U16 counter, U32 FAR *max_value);
I16 FAR PASCAL ND_SetCtrInitialValue(U16 com_port, U16 m_id, U16 counter, U32 init_value);
I16 FAR PASCAL ND_ReadCtrInitialValue(U16 com_port, U16 m_id, U16 counter, U32 FAR *init_value);
I16 FAR PASCAL ND_StartCtr(U16 com_port, U16 m_id, U16 counter, U16 status);
I16 FAR PASCAL ND_ReadCtrStatus(U16 com_port, U16 m_id, U16 counter, U16 FAR *active_status);
I16 FAR PASCAL ND_ClearCtr(U16 com_port, U16 m_id, U16 counter);
I16 FAR PASCAL ND_ReadCtrOverflowFlag(U16 com_port, U16 m_id, U16 counter, U16 FAR *overflow_flag);
I16 FAR PASCAL ND_EnableDigitalFilter(U16 com_port, U16 m_id, U16 enable);
I16 FAR PASCAL ND_ReadFilterStatus(U16 com_port, U16 m_id, U16 FAR *filter_status);
I16 FAR PASCAL ND_SetMinWidthAtHigh(U16 com_port, U16 m_id, U16 min_width);
I16 FAR PASCAL ND_ReadMinWidthAtHigh(U16 com_port, U16 m_id, U16 FAR *min_width);
I16 FAR PASCAL ND_SetMinWidthAtLow(U16 com_port, U16 m_id, U16 min_width);
I16 FAR PASCAL ND_ReadMinWidthAtLow(U16 com_port, U16 m_id, U16 FAR *min_width);
I16 FAR PASCAL ND_SetTTLInputHigh(U16 com_port, U16 m_id, U16 high_level);
I16 FAR PASCAL ND_ReadTTLInputHigh(U16 com_port, U16 m_id, U16 FAR *high_level);
I16 FAR PASCAL ND_SetTTLInputLow(U16 com_port, U16 m_id, U16 low_level);
I16 FAR PASCAL ND_ReadTTLInputLow(U16 com_port, U16 m_id, U16 FAR *low_level);
I16 FAR PASCAL ND_EnableCtrAlarm(U16 com_port, U16 m_id, U16 counter);
I16 FAR PASCAL ND_DisableCtrAlarm(U16 com_port, U16 m_id, U16 counter);
I16 FAR PASCAL ND_GetCtrAlarmStatus(U16 com_port, U16 m_id, U16 counter, U16 FAR *alarm_status);
I16 FAR PASCAL ND_SetCtrAlarmLimit(U16 com_port, U16 m_id, U16 counter, U32 alarm_value);
I16 FAR PASCAL ND_ReadCtrAlarmLimit(U16 com_port, U16 m_id, U16 counter, U32 FAR *alarm_value);

//6014D Linear Mapping Functions
I16 FAR PASCAL ND_ReadMappingSource(U16 com_port, U16 m_id, DATA low_source, DATA high_source);
I16 FAR PASCAL ND_ReadMappingTarget(U16 com_port, U16 m_id, DATA low_target, DATA high_target);
I16 FAR PASCAL ND_WriteMappingSource(U16 com_port, U16 m_id, DATA low_source, DATA high_source);
I16 FAR PASCAL ND_WriteMappingTarget(U16 com_port, U16 m_id, DATA low_target, DATA high_target);
I16 FAR PASCAL ND_EnableLinearMapping(U16 com_port, U16 m_id, U16 enable);

//6521 Functions
I16 FAR PASCAL ND_Get6521Config(U16 com_port, U16 m_id, ND6521CONFIG FAR *config);
I16 FAR PASCAL ND_Set6521Config(U16 com_port, U16 m_id, ND6521CONFIG FAR *config);
I16 FAR PASCAL ND_SoftReset(U16 com_port, U16 m_id);
I16 FAR PASCAL ND_ResetStatus(U16 com_port, U16 m_id, U16 *reset_status);
I16 FAR PASCAL ND_SetRTS(U16 com_port, U16 m_id, U16 RTS_status);
I16 FAR PASCAL ND_GetRTS(U16 com_port, U16 m_id, U16 *RTS_status);
I16 FAR PASCAL ND_GetCTS(U16 com_port, U16 m_id, U16 *CTS_status);
I16 FAR PASCAL ND_SetDeviceID(U16 com_port, U16 m_id, DATA device_id);
I16 FAR PASCAL ND_GetDeviceID(U16 com_port, U16 m_id, DATA device_id);
I16 FAR PASCAL ND_SetDelimiter(U16 com_port, U16 m_id, char delimiter);
I16 FAR PASCAL ND_GetDelimiter(U16 com_port, U16 m_id, char *delimiter);
I16 FAR PASCAL ND_DataPass(U16 com_port, U16 m_id, DATA data_string, DATA return_data);
I16 FAR PASCAL ND_DataPassConfig(U16 com_port, U16 m_id, U16 len);
I16 FAR PASCAL ND_SetDataGate(U16 com_port, U16 m_id, U16 addressable_mode);

#ifdef __cplusplus
}
#endif
