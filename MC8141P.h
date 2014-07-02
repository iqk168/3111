
// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the MC8141P_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// MC8141P_API functions as being imported from a DLL, wheras this DLL sees symbols
// defined with this macro as being exported.

#ifdef MC8141P_EXPORTS
#define MC8141P_API extern "C" __declspec(dllexport)
#else
#define MC8141P_API extern "C" //__declspec(dllimport)
#endif

#define FEXPORT MC8141P_API

#if !defined(_WIN31)
//    #define FEXPORT __declspec (dllexport)
    #define FTYPE  CALLBACK
#else
//    #define FEXPORT extern
    #define FTYPE  FAR PASCAL
#endif

#define DOUBLE double

/************************************************************************
   Define Global Value
************************************************************************/
#define CW                      0
#define CCW                     1
#define ImmediateStop           0
#define SlowStop                1
#define RelativeCoordinate      0
#define AbsoluteCoordinate      1
#define TCurveAcceleration      0
#define SCurveAcceleration      1
/************************************************************************
   Define Register ID
************************************************************************/
#define Rcnt                    0x0100          /* Real position counter */
#define Lcnt                    0x0101          /* Logical position counter */
#define Pcmp                    0x0102          /* P direction compare register */
#define Ncmp                    0x0103          /* N direction compare register */
#define Pnum                    0x0104          /* Pulse number */

#define CurV					0x0105			/* current logical speed */  
#define CurAC					0x0106			/* current logical acc	*/

#define SLDN_STOP               0x0026			
#define IMME_STOP               0x0027

#define WR3_OUTSL               0x0080

#define RESET					0x8000
#define RR0                     0x0200          
#define RR1                     0x0202
#define RR2                     0x0204
#define RR3                     0x0206
#define RR4                     0x0208
#define RR5                     0x020A
#define RR6                     0x020C
#define RR7                     0x020E

#define WR0                     0x0210
#define WR1                     0x0212
#define WR2                     0x0214
#define WR3                     0x0216
#define WR4                     0x0218
#define WR5                     0x021A
#define WR6                     0x021C
#define WR7                     0x021E

#define RG                      0x0300
#define SV                      0x0301
#define DV                      0x0302
#define MDV                     0x0303
#define AC                      0x0304
#define DC                      0x0305
#define AK                      0x0306
#define PLmt                    0x0307
#define NLmt                    0x0308
#define HomeOffset              0x0309
#define HomeMode                0x030A
#define HomeType                0x030B
#define HomeP0_Dir              0x030C
#define HomeP0_Speed            0x030D
#define HomeP1_Dir              0x030E
#define HomeP1_Speed            0x030F
#define HomeP2_Dir              0x0310
#define HomeOffset_Speed        0x0311
/************************************************************************
   Define Operation Axis
************************************************************************/
#define IPO_Axis				0x00	
#define X_Axis                  0x01
#define Y_Axis                  0x02
#define Z_Axis                  0x04
#define U_Axis                  0x08
#define XY_Axis                 0x03
#define XZ_Axis                 0x05
#define XU_Axis                 0x09
#define YZ_Axis                 0x06
#define YU_Axis                 0x0A
#define ZU_Axis                 0x0C
#define XYZ_Axis                0x07
#define XYU_Axis                0x0B
#define XZU_axis                0x0D
#define YZU_Axis                0x0E
#define XYZU_Axis               0x0F

/************************************************************************
   Path type for continue moving
************************************************************************/
#define IPO_L2                  0x0030
#define IPO_L3                  0x0031
#define IPO_CW                  0x0032
#define IPO_CCW                 0x0134

/************************************************************************
   Return Code
************************************************************************/
#define BoardNumErr             0x0001	
#define CreateKernelDriverFail  0x0002	//internal system error
#define CallKernelDriverFail    0x0003  //internal system error
#define RegistryOpenFail        0x0004	//Open registry file fail
#define RegistryReadFail        0x0005	//Read registry file fail
#define AxisNumErr              0x0006
#define UnderRGErr              0x0007
#define OverRGErr               0x0008
#define UnderSVErr              0x0009
#define OverSVErr               0x000a
#define OverMDVErr              0x000b
#define UnderDVErr              0x000c
#define OverDVErr               0x000d
#define UnderACErr              0x000e
#define OverACErr               0x000f
#define UnderAKErr              0x0010
#define OverAKErr               0x0011
#define OverPLmtErr             0x0012
#define OverNLmtErr             0x0013
#define MaxMoveDistErr          0x0014
#define AxisDrvBusy             0x0015
#define RegUnDefine             0x0016
#define ParaValueErr            0x0017
#define ParaValueOverRange      0x0018
#define ParaValueUnderRange     0x0019
#define AxisHomeBusy            0x001a
#define AxisExtBusy             0x001b
#define RegistryWriteFail       0x001c
#define ParaValueOverErr        0x001d
#define ParaValueUnderErr       0x001e
#define OverDCErr               0x001f
#define UnderDCErr              0x0020
#define UnderMDVErr             0x0021
#define RegistryCreateFail      0x0022
#define CreateThreadErr         0x0023		//internal system fail
#define HomeSwStop		        0x0024		//MC8141PHomeStatus
#define ChangeSpeedErr          0x0025
#define DOPortAsDriverStatus    0x0026

#define OpenEventFail           0x0030		//Internal system fail
#define DeviceCloseErr		     0x0032		//Internal system fail

#define HomeEMGStop             0x0040		//MC8141PHomeStatus
#define HomeLMTPStop            0x0041		//MC8141PHomeStatus
#define HomeLMTNStop            0x0042		//MC8141PHomeStatus
#define HomeALARMStop           0x0043		//MC8141PHomeStatus

#define AllocateBufferFail				0x0050
#define BufferReAllocate				0x0051
#define FreeBufferFail					0x0052
#define FirstPointNumberFail			0x0053	
#define PointNumExceedAllocatedSize	0x0054
#define BufferNoneAllocate				0x0055
#define SequenceNumberErr				0x0056	
#define PathTypeErr						0x0057
#define PathTypeMixErr					0x0060
#define BufferDataNotEnough			0x0061
#define CallDllDriverFailed         0x0062

/************************************************************************
   External mode
************************************************************************/
#define JOGDisable              0x00
#define JOGSelfAxis             0x01
#define JOGSelect_XAxis         0x02
#define JOGSelect_YAxis         0x03
#define JOGConnect_XAxis        0x04
#define JOGConnect_YAxis        0x05
#define JOGConnect_ZAxis        0x06
#define JOGConnect_UAxis        0x07
#define HandWheelDisable        0x08
#define HandWheelSelfAxis       0x09
#define HandWheelSelect_XAxis   0x0a
#define HandWheelSelect_YAxis   0x0b
#define HandWheelFrom_XAxis     0x0c
#define HandWheelFrom_YAxis     0x0d
#define HandWheelFrom_ZAxis     0x0e
#define HandWheelFrom_UAxis     0x0f

// Structure defination
// Line Interplation( 2 axes )  
//		- dwEndPoint_ax1;
//		- dwEndPoint_ax2;
//		- wCommand;					; IPO_L2	
// Line Interplation( 3 axes )  
//		- dwEndPoint_ax1;
//		- dwEndPoint_ax2;
//		- dwEndPoint_ax3;
//		- wCommand;					; IPO_L3	
// Arc  Interplation( only 2 axes )  
//		- dwEndPoint_ax1;			; Arc end point of axis 1
//		- dwEndPoint_ax2;			; Arc end point of axis 2
//		- dwCenPoint_ax1;			; Arc center point of axis 1
//		- dwCenPoint_ax1;			; Arc center point of axis 2	
//		- wCommand;					; IPO_CW,IPO_CCW		
typedef struct _MotMoveBuffer
{
  DWORD			dwEndPoint_ax1;		// End position for 1'st axis
  DWORD			dwEndPoint_ax2;		// End position for 2'nd axis
  DWORD			dwEndPoint_ax3;		// End position for 3'rd axis
  DWORD			dwCenPoint_ax1;		// Center position for 1'st axis	
  DWORD			dwCenPoint_ax2;		// Center position for 2'rd axis
  DWORD			dwPointNum;			// Serial number for current data

  WORD			wCommand;			// IPO_CW,IPO_CCW,IPO_L2,IPO_L3 			
  WORD			TempB;				// For internal using
  DWORD			TempA;				// For internal using

}	MotMoveBuffer, * LPMotMoveBuffer;

typedef struct _MotSpeedTable
{

	DWORD	dwSpeed;	// speed data
	DWORD	dwComp;		// comparator data
  
}	MotSpeedTable, * LPMotSpeedTable; 	

// export functions
FEXPORT LRESULT FTYPE MC8141PMotDevAvailable( DWORD *lpReturnBoardStatus );

FEXPORT LRESULT FTYPE MC8141PMotDevOpen( BYTE byBoard_ID );

FEXPORT LRESULT FTYPE MC8141PMotDevClose( BYTE byBoard_ID );

FEXPORT LRESULT FTYPE MC8141PMotAxisParaSet(
                         BYTE byBoard_ID,
								 BYTE bySetAxis,
								 BYTE byTS,
								 DWORD dwSV,
								 DWORD dwDV,
								 DWORD dwMDV,
								 DWORD dwAC,
								 DWORD dwAK );

FEXPORT LRESULT FTYPE MC8141PMotChgDV(
                         BYTE byBoard_ID,
								 BYTE bySetAxis,
								 DWORD dwSetDVValue );

FEXPORT LRESULT FTYPE MC8141PMotChgLineArcDV(
                         BYTE byBoard_ID,
								 DWORD dwSetDVValue );

FEXPORT LRESULT FTYPE MC8141PMotCmove(
                         BYTE byBoard_ID,
                         BYTE byCMoveAxis,
								 BYTE byAxisDirection );

FEXPORT LRESULT FTYPE MC8141PMotPtp(
                         BYTE byBoard_ID,
								 BYTE byMoveAxis,
								 BYTE byRA,
								 LONG lPulseX,
								 LONG lPulseY,
								 LONG lPulseZ,
								 LONG lPulseU );

FEXPORT LRESULT FTYPE MC8141PMotLine(
                         BYTE byBoard_ID,
								 BYTE byMoveAxis,
								 BYTE byRA,
								 LONG lPulseX,
								 LONG lPulseY,
								 LONG lPulseZ,
								 LONG lPulseU );

FEXPORT LRESULT FTYPE MC8141PMotArc(
                         BYTE byBoard_ID,
								 BYTE byMoveAxis,
								 BYTE byRA,
								 BYTE byAxisDirection,
								 LONG lCenter1,
								 LONG lCenter2,
								 LONG lEnd1,
								 LONG lEnd2 );

FEXPORT LRESULT FTYPE MC8141PMotArcTheta(
                         BYTE byBoard_ID,
								 BYTE byMoveAxis,
								 BYTE byRA,
								 LONG lCenter1,
								 LONG lCenter2,
								 DOUBLE dMoveDeg );

FEXPORT LRESULT FTYPE MC8141PMotStop(
                         BYTE byBoard_ID,
								 BYTE byStopAxis,
								 BYTE byStopMode );

FEXPORT LRESULT FTYPE MC8141PMotAxisBusy(
                         BYTE byBoard_ID,
								 BYTE byCheckAxis );

FEXPORT LRESULT FTYPE MC8141PMotClrErr(
                         BYTE byBoard_ID,
								 BYTE byClearAxis);

FEXPORT LRESULT FTYPE MC8141PMotRdReg(
                         BYTE byBoard_ID,
								 BYTE byReadAxis,
								 WORD wCommandCode,
								 DWORD *lpReturnValue);

FEXPORT LRESULT FTYPE MC8141PMotWrReg(
                         BYTE byBoard_ID,
								 BYTE byWriteAxis,
								 WORD wCommandCode,
								 DWORD dwWriteValue );

FEXPORT LRESULT FTYPE MC8141PMotSavePara(
                         BYTE byBoard_ID,
								 BYTE bySaveAxis );

FEXPORT LRESULT FTYPE MC8141PMotEnableEvent(
                         BYTE byBoard_ID,
								 BYTE bySettingAxis,
								 BYTE byX_AxisEvent,
								 BYTE byY_AxisEvent,
								 BYTE byZ_AxisEvent,
								 BYTE byU_AxisEvent );

FEXPORT LRESULT FTYPE MC8141PMotCheckEvent(
                         BYTE  byBoard_ID,
								 DWORD *lpRetEventStatus,
								 DWORD dwMillisecond);

FEXPORT LRESULT FTYPE MC8141PMotRdMutiReg(
                         BYTE  byBoard_ID,
								 BYTE  byReadAxis,
								 WORD  wCommandCode,
                         DWORD *lpReturn_XAxisValue,
								 DWORD *lpReturn_YAxisValue,
                         DWORD *lpReturn_ZAxisValue,
								 DWORD *lpReturn_UAxisValue );

FEXPORT LRESULT FTYPE MC8141PMotWrMutiReg(
                         BYTE  byBoard_ID,
								 BYTE  byWriteAxis,
								 WORD  wCommandCode,
                         DWORD dwWrite_XAxisValue,
								 DWORD dwWrite_YAxisValue,
                         DWORD dwWrite_ZAxisValue,
								 DWORD dwWrite_UAxisValue );

FEXPORT LRESULT FTYPE MC8141PMotHome(
                         BYTE byBoard_ID,
								 BYTE byHomeAxis );

FEXPORT LRESULT FTYPE MC8141PMotHomeStatus(
                         BYTE byBoard_ID,
								 BYTE byHomeAxis,
								 DWORD *lpReturnValue );

FEXPORT LRESULT FTYPE MC8141PMotDI(
                         BYTE byBoard_ID,
								 BYTE byReadDIAxis,
								 BYTE *lpReturnValue );

FEXPORT LRESULT FTYPE MC8141PMotDO(
                         BYTE byBoard_ID,
								 BYTE byWriteDOAxis,
								 BYTE byWriteValue );

FEXPORT LRESULT FTYPE MC8141PMotExtMode(
                         BYTE byBoard_ID,
								 BYTE byAssignmentAxis,
								 BYTE byExternalMode,
								 LONG lPulseNum );

FEXPORT LRESULT FTYPE MC8141PMotReset( BYTE byBoard_ID );

FEXPORT LRESULT FTYPE MC8141PInitialContiBuf(
                         BYTE byBufID, 
								 DWORD dwAllPointNum );

FEXPORT LRESULT FTYPE MC8141PFreeContiBuf( BYTE byBufID );

FEXPORT LRESULT FTYPE MC8141PSetContiData(
                         BYTE byBufID,
								 LPMotMoveBuffer lpPathData,
								 DWORD dwPointNum );

FEXPORT LRESULT FTYPE MC8141PStartContiDrive(
                         BYTE byBoard_ID,
								 BYTE byMoveAxis,
								 BYTE byBufID );

FEXPORT LRESULT FTYPE MC8141PGetCurContiNum(
                         BYTE	byBoard_ID,
                         DWORD *lpReturnValue);

FEXPORT LRESULT FTYPE MC8141PBuildCompTable(
                         BYTE byBoard_ID,
                         BYTE byMoveAxis,
                         DWORD *dwTableArray,
                         DWORD dwAllPointNum	);

FEXPORT LRESULT FTYPE MC8141PBuildSpeedTable(
                         BYTE byBoard_ID,
                         BYTE byMoveAxis,
                         MotSpeedTable	*SpeedTable,
                         DWORD dwAllPointNum	);

FEXPORT LRESULT FTYPE MC8141PSetCompPLimit ( 
	                      BYTE byBoard_ID, 
						       BYTE bySetAxis, 
						       DWORD byWriteValue );

FEXPORT LRESULT FTYPE MC8141PSetCompNLimit ( 
	                      BYTE byBoard_ID, 
						       BYTE bySetAxis, 
					      	 DWORD byWriteValue );

FEXPORT LRESULT FTYPE MC8141PEnableCompPLimit ( 
	                      BYTE byBoard_ID, 
						       BYTE bySetAxis, 
					      	 USHORT Enable );

FEXPORT LRESULT FTYPE MC8141PEnableCompNLimit ( 
	                      BYTE byBoard_ID, 
						       BYTE bySetAxis, 
					      	 USHORT Enable );

FEXPORT LRESULT FTYPE MC8141PSetPLimitLogic ( 
	                      BYTE byBoard_ID, 
						       BYTE bySetAxis, 
					      	 USHORT Value );

FEXPORT LRESULT FTYPE MC8141PSetNLimitLogic ( 
	                      BYTE byBoard_ID, 
						       BYTE bySetAxis, 
					      	 USHORT Value );

FEXPORT LRESULT FTYPE MC8141PSetCompareObject ( 
	                      BYTE byBoard_ID, 
						       BYTE bySetAxis, 
					      	 USHORT Value );

FEXPORT LRESULT FTYPE MC8141PSetPulseMode ( 
	                      BYTE byBoard_ID, 
						       BYTE bySetAxis, 
					      	 USHORT Value );

FEXPORT LRESULT FTYPE MC8141PSetPulseLogic ( 
	                      BYTE byBoard_ID, 
						       BYTE bySetAxis, 
					      	 USHORT Value );

FEXPORT LRESULT FTYPE MC8141PSetPulseDirLogic ( 
	                      BYTE byBoard_ID, 
						       BYTE bySetAxis, 
					      	 USHORT Value );

FEXPORT LRESULT FTYPE MC8141PSetEncoderMultiple ( 
	                      BYTE byBoard_ID, 
						       BYTE bySetAxis, 
					      	 USHORT Value );

FEXPORT LRESULT FTYPE MC8141PSetServoAlarm ( 
	                      BYTE byBoard_ID, 
						       BYTE bySetAxis, 
								 USHORT Enable,
					      	 USHORT Value );

FEXPORT LRESULT FTYPE MC8141PSetInPosition ( 
	                      BYTE byBoard_ID, 
						       BYTE bySetAxis, 
								 USHORT Enable,
					      	 USHORT Value );

FEXPORT LRESULT FTYPE MC8141PSetHomeLogic ( 
	                      BYTE byBoard_ID, 
						       BYTE bySetAxis, 								 
					      	 USHORT Value );

FEXPORT LRESULT FTYPE MC8141PSetZLogic ( 
	                      BYTE byBoard_ID, 
						       BYTE bySetAxis, 								 
					      	 USHORT Value );

FEXPORT LRESULT FTYPE MC8141PSetOutput ( 
	                      BYTE byBoard_ID, 
						       BYTE bySetAxis, 								 
					      	 USHORT Value );

FEXPORT LRESULT FTYPE MC8141PSetOutputType ( 
	                      BYTE byBoard_ID, 
						       BYTE bySetAxis, 								 
					      	 USHORT Enable );

FEXPORT LRESULT FTYPE MC8141PSetInputLogic ( 
	                      BYTE byBoard_ID, 
						       BYTE bySetAxis,
								 USHORT D4Value,
								 USHORT D6Value );

FEXPORT LRESULT FTYPE MC8141PGetError (
								 BYTE byBoard_ID, 
						       BYTE byGetAxis,
								 USHORT * lpValue	);

FEXPORT LRESULT FTYPE MC8141PGetDriverState (
								 BYTE byBoard_ID, 
						       BYTE byGetAxis,
								 USHORT * lpValue	);

FEXPORT LRESULT FTYPE MC8141PGetMotionState (
								 BYTE byBoard_ID, 
						       BYTE byGetAxis,
								 USHORT *lpValue	);

FEXPORT LRESULT FTYPE MC8141PGetMotionInput (
								 BYTE byBoard_ID, 
						       BYTE byGetAxis,
								 USHORT *lpValue	);

FEXPORT LRESULT FTYPE MC8141PGetCompareState (
								 BYTE byBoard_ID, 
						       BYTE byGetAxis,
								 USHORT *lpValue	);

FEXPORT LRESULT FTYPE MC8141PGetInput (
								 BYTE byBoard_ID, 
						       BYTE byGetAxis,
								 USHORT *lpValue );

// motion functions
FEXPORT LRESULT FTYPE MC8141PMoveAbs(
						       BYTE byBoard_ID,
								 BYTE byMoveAxis,								 
								 LONG lPulseNumber );

FEXPORT LRESULT FTYPE MC8141PMoveIns(
						       BYTE byBoard_ID,
								 BYTE byMoveAxis,								 
								 LONG lPulseNumber );

FEXPORT LRESULT FTYPE MC8141PMoveCircle(
							    BYTE byBoard_ID,
								 BYTE byMoveAxis,
								 BYTE byAxisDirection,								 
								 LONG lCenter1,
								 LONG lCenter2 );

FEXPORT LRESULT FTYPE MC8141PSetStartSpeed(
								 BYTE byBoard_ID,
								 BYTE bySetAxis,
								 DWORD lSpeedValue );

FEXPORT LRESULT FTYPE MC8141PSetDrivingSpeed(
								 BYTE byBoard_ID,
								 BYTE bySetAxis,
								 DWORD lSpeedValue );

FEXPORT LRESULT FTYPE MC8141PSetAcceleration(
								 BYTE byBoard_ID,
								 BYTE bySetAxis,
								 DWORD accel );

FEXPORT LRESULT FTYPE MC8141PSetDeceleration(
								 BYTE byBoard_ID,
								 BYTE bySetAxis,
								 DWORD decel,
                         LONG lRetrieve );    // leon.jin add 2002-11-14

FEXPORT LRESULT FTYPE MC8141PSetJerk(
								 BYTE byBoard_ID,
								 BYTE bySetAxis,
								 DWORD lJerk );

FEXPORT LRESULT FTYPE MC8141PSetRange(
								 BYTE byBoard_ID,
								 BYTE bySetAxis,
								 DWORD lRange );


FEXPORT LRESULT FTYPE MC8141PGetSpeed (
								 BYTE byBoard_ID, 
						       BYTE byGetAxis,
								 DWORD *lpValue );

FEXPORT LRESULT FTYPE MC8141PGetAcel (
								 BYTE byBoard_ID, 
						       BYTE byGetAxis,
								 DWORD *lpValue );

FEXPORT LRESULT FTYPE MC8141PGetPracticalRegister (
								 BYTE byBoard_ID, 
						       BYTE byGetAxis,
								 DWORD *lpValue );

FEXPORT LRESULT FTYPE MC8141PGetTheorecticalRegister (
								 BYTE byBoard_ID, 
						       BYTE byGetAxis,
								 DWORD *lpValue );

FEXPORT LRESULT FTYPE MC8141PSetPracticalRegister(
								 BYTE byBoard_ID,
								 BYTE bySetAxis,
								 LONG lPosition );

FEXPORT LRESULT FTYPE MC8141PSetTheorecticalRegister(
								 BYTE byBoard_ID,
								 BYTE bySetAxis,
								 LONG lPosition );

/*
// IPO
FEXPORT LRESULT FTYPE MC8141PMoveLineContinuous(
								 BYTE byBoard_ID,
								 BYTE byMoveAxis,
								 LONG lPosition1,
								 LONG lPosition2,
                         LONG lPosition3 );

FEXPORT LRESULT FTYPE MC8141PMoveArcContinuous(
								 BYTE byBoard_ID,
								 BYTE byMoveAxis,
								 BYTE byAxisDirection,
								 LONG lCenter1,
								 LONG lCenter2,
								 LONG lEnd1,
								 LONG lEnd2 );
*/

// port IO
FEXPORT BOOL FTYPE MC8141P_InpWord(
								 BYTE    byBoard_ID,
								 USHORT  nPort,
                         USHORT* ptWord );

FEXPORT BOOL FTYPE MC8141P_OutpWord(
								 BYTE    byBoard_ID,
								 USHORT  nPort,
                         USHORT  wWord );

FEXPORT LRESULT FTYPE MC8141PReadEEPROM (
                         BYTE byBoard_ID, 
                         BYTE byEEPROMAddress, 
                         unsigned short *pusReadValue );

FEXPORT LRESULT FTYPE MC8141PWriteEEPROM (
                         BYTE byBoard_ID, 
                         BYTE byEEPROMAddress, 
	                      unsigned short usWriteValue );
