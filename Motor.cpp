// Motor.cpp: implementation of the CMotor class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "deer.h"
#include "Motor.h"

// Motor Lib
#include "MC8141P.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMotor::CMotor()
{
	
}

CMotor::~CMotor()
{

}
////////////////////////////////////////////////////////////////////////////////////
// Specially Motor Function
bool CMotor::IsMotorErrorCodeCheck(LRESULT LRes)
{
	bool bOK = false;
	// Speed error
	if (LRes == AxisNumErr)
		;
	else if (LRes == ParaValueErr)
		;
	else if (LRes == ParaValueUnderRange)
		;
	else if (LRes == ParaValueOverRange)
		;
	// Other error
	else if (LRes == BoardNumErr)
		;
	else if (LRes == CreateKernelDriverFail)
		;
	else if (LRes == CallKernelDriverFail)
		;
	else if (LRes == RegistryOpenFail)
		;
	else if (LRes == RegistryReadFail)
		;
	else if (LRes == UnderRGErr)
		;
	else if (LRes == OverRGErr)
		;
	else if (LRes == UnderSVErr)
		;
	else if (LRes == OverSVErr)
		;
	else if (LRes == OverMDVErr)
		;
	else if (LRes == UnderDVErr)
		;
	else if (LRes == OverDVErr)
		;
	else if (LRes == UnderACErr)
		;
	else if (LRes == OverACErr)
		;
	else if (LRes == UnderAKErr)
		;
	else if (LRes == OverAKErr)
		;
	else if (LRes == OverPLmtErr)
		;
	else if (LRes == OverNLmtErr)
		;
	else if (LRes == MaxMoveDistErr)
		;
	else if (LRes == AxisDrvBusy)
		;
	else if (LRes == RegUnDefine)
		;
	else if (LRes == ParaValueErr)
		;
	else if (LRes == ParaValueOverRange)
		;
	else if (LRes == ParaValueUnderRange)
		;
	else if (LRes == AxisHomeBusy)
		;
	else if (LRes == AxisExtBusy)
		;
	else if (LRes == RegistryWriteFail)
		;
	else if (LRes == ParaValueOverErr)
		;
	else if (LRes == ParaValueUnderErr)
		;
	else if (LRes == OverDCErr)
		;
	else if (LRes == UnderDCErr)
		;
	else if (LRes == UnderMDVErr)
		;
	else if (LRes == RegistryCreateFail)
		;
	else if (LRes == CreateThreadErr)
		;
	else if (LRes == HomeSwStop)
		;
	else if (LRes == ChangeSpeedErr)
		;
	else if (LRes == DOPortAsDriverStatus)
		;
	else if (LRes == OpenEventFail)
		;
	else if (LRes == DeviceCloseErr)
		;
	else if (LRes == HomeEMGStop)
		;
	else if (LRes == HomeLMTPStop)
		;
	else if (LRes == HomeLMTNStop)
		;
	else if (LRes == HomeALARMStop)
		;
	else if (LRes == AllocateBufferFail)
		;
	else if (LRes == BufferReAllocate)
		;
	else if (LRes == FreeBufferFail)
		;
	else if (LRes == FirstPointNumberFail)
		;
	else if (LRes == PointNumExceedAllocatedSize)
		;
	else if (LRes == BufferNoneAllocate)
		;
	else if (LRes == SequenceNumberErr)
		;
	else if (LRes == PathTypeErr)
		;
	else if (LRes == PathTypeMixErr)
		;
	else if (LRes == BufferDataNotEnough)
		;
	else if (LRes == CallDllDriverFailed)
		;
	else if (LRes != ERROR_SUCCESS) // 未填入的 Error Code
		;
	else // ERROR_SUCCESS
		bOK = true;
	
	return bOK;
}

CString CMotor::IsMotorErrorCodeLog(LRESULT LRes)
{
	CString cs = "SUCCESS";
	// Speed error
	if (LRes == AxisNumErr)
		cs.Format("Error Code = %s(0x%x)", "AxisNumErr", LRes);
	else if (LRes == ParaValueErr)
		cs.Format("Error Code = %s(0x%x)", "ParaValueErr", LRes);
	else if (LRes == ParaValueUnderRange)
		cs.Format("Error Code = %s(0x%x)", "ParaValueUnderRange", LRes);
	else if (LRes == ParaValueOverRange)
		cs.Format("Error Code = %s(0x%x)", "ParaValueOverRange", LRes);
	// Other error
	else if (LRes == BoardNumErr)
		cs.Format("Error Code = %s(0x%x)", "BoardNumErr", LRes);
	else if (LRes == CreateKernelDriverFail)
		cs.Format("Error Code = %s(0x%x)", "CreateKernelDriverFail", LRes);
	else if (LRes == CallKernelDriverFail)
		cs.Format("Error Code = %s(0x%x)", "CallKernelDriverFail", LRes);
	else if (LRes == RegistryOpenFail)
		cs.Format("Error Code = %s(0x%x)", "RegistryOpenFail", LRes);
	else if (LRes == RegistryReadFail)
		cs.Format("Error Code = %s(0x%x)", "RegistryReadFail", LRes);
	else if (LRes == UnderRGErr)
		cs.Format("Error Code = %s(0x%x)", "UnderRGErr", LRes);
	else if (LRes == OverRGErr)
		cs.Format("Error Code = %s(0x%x)", "OverRGErr", LRes);
	else if (LRes == UnderSVErr)
		cs.Format("Error Code = %s(0x%x)", "UnderSVErr", LRes);
	else if (LRes == OverSVErr)
		cs.Format("Error Code = %s(0x%x)", "OverSVErr", LRes);
	else if (LRes == OverMDVErr)
		cs.Format("Error Code = %s(0x%x)", "OverMDVErr", LRes);
	else if (LRes == UnderDVErr)
		cs.Format("Error Code = %s(0x%x)", "UnderDVErr", LRes);
	else if (LRes == OverDVErr)
		cs.Format("Error Code = %s(0x%x)", "OverDVErr", LRes);
	else if (LRes == UnderACErr)
		cs.Format("Error Code = %s(0x%x)", "UnderACErr", LRes);
	else if (LRes == OverACErr)
		cs.Format("Error Code = %s(0x%x)", "OverACErr", LRes);
	else if (LRes == UnderAKErr)
		cs.Format("Error Code = %s(0x%x)", "UnderAKErr", LRes);
	else if (LRes == OverAKErr)
		cs.Format("Error Code = %s(0x%x)", "OverAKErr", LRes);
	else if (LRes == OverPLmtErr)
		cs.Format("Error Code = %s(0x%x)", "OverPLmtErr", LRes);
	else if (LRes == OverNLmtErr)
		cs.Format("Error Code = %s(0x%x)", "OverNLmtErr", LRes);
	else if (LRes == MaxMoveDistErr)
		cs.Format("Error Code = %s(0x%x)", "MaxMoveDistErr", LRes);
	else if (LRes == AxisDrvBusy)
		cs.Format("Error Code = %s(0x%x)", "AxisDrvBusy", LRes);
	else if (LRes == RegUnDefine)
		cs.Format("Error Code = %s(0x%x)", "RegUnDefine", LRes);
	else if (LRes == ParaValueErr)
		cs.Format("Error Code = %s(0x%x)", "ParaValueErr", LRes);
	else if (LRes == ParaValueOverRange)
		cs.Format("Error Code = %s(0x%x)", "ParaValueOverRange", LRes);
	else if (LRes == ParaValueUnderRange)
		cs.Format("Error Code = %s(0x%x)", "ParaValueUnderRange", LRes);
	else if (LRes == AxisHomeBusy)
		cs.Format("Error Code = %s(0x%x)", "AxisHomeBusy", LRes);
	else if (LRes == AxisExtBusy)
		cs.Format("Error Code = %s(0x%x)", "AxisExtBusy", LRes);
	else if (LRes == RegistryWriteFail)
		cs.Format("Error Code = %s(0x%x)", "RegistryWriteFail", LRes);
	else if (LRes == ParaValueOverErr)
		cs.Format("Error Code = %s(0x%x)", "ParaValueOverErr", LRes);
	else if (LRes == ParaValueUnderErr)
		cs.Format("Error Code = %s(0x%x)", "ParaValueUnderErr", LRes);
	else if (LRes == OverDCErr)
		cs.Format("Error Code = %s(0x%x)", "OverDCErr", LRes);
	else if (LRes == UnderDCErr)
		cs.Format("Error Code = %s(0x%x)", "UnderDCErr", LRes);
	else if (LRes == UnderMDVErr)
		cs.Format("Error Code = %s(0x%x)", "UnderMDVErr", LRes);
	else if (LRes == RegistryCreateFail)
		cs.Format("Error Code = %s(0x%x)", "RegistryCreateFail", LRes);
	else if (LRes == CreateThreadErr)
		cs.Format("Error Code = %s(0x%x)", "CreateThreadErr", LRes);
	else if (LRes == HomeSwStop)
		cs.Format("Error Code = %s(0x%x)", "HomeSwStop", LRes);
	else if (LRes == ChangeSpeedErr)
		cs.Format("Error Code = %s(0x%x)", "ChangeSpeedErr", LRes);
	else if (LRes == DOPortAsDriverStatus)
		cs.Format("Error Code = %s(0x%x)", "DOPortAsDriverStatus", LRes);
	else if (LRes == OpenEventFail)
		cs.Format("Error Code = %s(0x%x)", "OpenEventFail", LRes);
	else if (LRes == DeviceCloseErr)
		cs.Format("Error Code = %s(0x%x)", "DeviceCloseErr", LRes);
	else if (LRes == HomeEMGStop)
		cs.Format("Error Code = %s(0x%x)", "HomeEMGStop", LRes);
	else if (LRes == HomeLMTPStop)
		cs.Format("Error Code = %s(0x%x)", "HomeLMTPStop", LRes);
	else if (LRes == HomeLMTNStop)
		cs.Format("Error Code = %s(0x%x)", "HomeLMTNStop", LRes);
	else if (LRes == HomeALARMStop)
		cs.Format("Error Code = %s(0x%x)", "HomeALARMStop", LRes);
	else if (LRes == AllocateBufferFail)
		cs.Format("Error Code = %s(0x%x)", "AllocateBufferFail", LRes);
	else if (LRes == BufferReAllocate)
		cs.Format("Error Code = %s(0x%x)", "BufferReAllocate", LRes);
	else if (LRes == FreeBufferFail)
		cs.Format("Error Code = %s(0x%x)", "FreeBufferFail", LRes);
	else if (LRes == FirstPointNumberFail)
		cs.Format("Error Code = %s(0x%x)", "FirstPointNumberFail", LRes);
	else if (LRes == PointNumExceedAllocatedSize)
		cs.Format("Error Code = %s(0x%x)", "PointNumExceedAllocatedSize", LRes);
	else if (LRes == BufferNoneAllocate)
		cs.Format("Error Code = %s(0x%x)", "BufferNoneAllocate", LRes);
	else if (LRes == SequenceNumberErr)
		cs.Format("Error Code = %s(0x%x)", "SequenceNumberErr", LRes);
	else if (LRes == PathTypeErr)
		cs.Format("Error Code = %s(0x%x)", "PathTypeErr", LRes);
	else if (LRes == PathTypeMixErr)
		cs.Format("Error Code = %s(0x%x)", "PathTypeMixErr", LRes);
	else if (LRes == BufferDataNotEnough)
		cs.Format("Error Code = %s(0x%x)", "BufferDataNotEnough", LRes);
	else if (LRes == CallDllDriverFailed)
		cs.Format("Error Code = %s(0x%x)", "CallDllDriverFailed", LRes);
	else if (LRes != ERROR_SUCCESS) // 未填入的 Error Code
		cs.Format("Error Code = (0x%x)", LRes);
	else // ERROR_SUCCESS
		;
	
	return cs;
}
void CMotor::IsMotorErrorCode(LRESULT LRes)
{
	CString cs = _T("");
	// Speed error
	if (LRes == AxisNumErr)
		cs.Format("Error Code = %s(0x%x)", "AxisNumErr", LRes);
	else if (LRes == ParaValueErr)
		cs.Format("Error Code = %s(0x%x)", "ParaValueErr", LRes);
	else if (LRes == ParaValueUnderRange)
		cs.Format("Error Code = %s(0x%x)", "ParaValueUnderRange", LRes);
	else if (LRes == ParaValueOverRange)
		cs.Format("Error Code = %s(0x%x)", "ParaValueOverRange", LRes);
	// Other error
	else if (LRes == BoardNumErr)
		cs.Format("Error Code = %s(0x%x)", "BoardNumErr", LRes);
	else if (LRes == CreateKernelDriverFail)
		cs.Format("Error Code = %s(0x%x)", "CreateKernelDriverFail", LRes);
	else if (LRes == CallKernelDriverFail)
		cs.Format("Error Code = %s(0x%x)", "CallKernelDriverFail", LRes);
	else if (LRes == RegistryOpenFail)
		cs.Format("Error Code = %s(0x%x)", "RegistryOpenFail", LRes);
	else if (LRes == RegistryReadFail)
		cs.Format("Error Code = %s(0x%x)", "RegistryReadFail", LRes);
	else if (LRes == UnderRGErr)
		cs.Format("Error Code = %s(0x%x)", "UnderRGErr", LRes);
	else if (LRes == OverRGErr)
		cs.Format("Error Code = %s(0x%x)", "OverRGErr", LRes);
	else if (LRes == UnderSVErr)
		cs.Format("Error Code = %s(0x%x)", "UnderSVErr", LRes);
	else if (LRes == OverSVErr)
		cs.Format("Error Code = %s(0x%x)", "OverSVErr", LRes);
	else if (LRes == OverMDVErr)
		cs.Format("Error Code = %s(0x%x)", "OverMDVErr", LRes);
	else if (LRes == UnderDVErr)
		cs.Format("Error Code = %s(0x%x)", "UnderDVErr", LRes);
	else if (LRes == OverDVErr)
		cs.Format("Error Code = %s(0x%x)", "OverDVErr", LRes);
	else if (LRes == UnderACErr)
		cs.Format("Error Code = %s(0x%x)", "UnderACErr", LRes);
	else if (LRes == OverACErr)
		cs.Format("Error Code = %s(0x%x)", "OverACErr", LRes);
	else if (LRes == UnderAKErr)
		cs.Format("Error Code = %s(0x%x)", "UnderAKErr", LRes);
	else if (LRes == OverAKErr)
		cs.Format("Error Code = %s(0x%x)", "OverAKErr", LRes);
	else if (LRes == OverPLmtErr)
		cs.Format("Error Code = %s(0x%x)", "OverPLmtErr", LRes);
	else if (LRes == OverNLmtErr)
		cs.Format("Error Code = %s(0x%x)", "OverNLmtErr", LRes);
	else if (LRes == MaxMoveDistErr)
		cs.Format("Error Code = %s(0x%x)", "MaxMoveDistErr", LRes);
	else if (LRes == AxisDrvBusy)
		cs.Format("Error Code = %s(0x%x)", "AxisDrvBusy", LRes);
	else if (LRes == RegUnDefine)
		cs.Format("Error Code = %s(0x%x)", "RegUnDefine", LRes);
	else if (LRes == ParaValueErr)
		cs.Format("Error Code = %s(0x%x)", "ParaValueErr", LRes);
	else if (LRes == ParaValueOverRange)
		cs.Format("Error Code = %s(0x%x)", "ParaValueOverRange", LRes);
	else if (LRes == ParaValueUnderRange)
		cs.Format("Error Code = %s(0x%x)", "ParaValueUnderRange", LRes);
	else if (LRes == AxisHomeBusy)
		cs.Format("Error Code = %s(0x%x)", "AxisHomeBusy", LRes);
	else if (LRes == AxisExtBusy)
		cs.Format("Error Code = %s(0x%x)", "AxisExtBusy", LRes);
	else if (LRes == RegistryWriteFail)
		cs.Format("Error Code = %s(0x%x)", "RegistryWriteFail", LRes);
	else if (LRes == ParaValueOverErr)
		cs.Format("Error Code = %s(0x%x)", "ParaValueOverErr", LRes);
	else if (LRes == ParaValueUnderErr)
		cs.Format("Error Code = %s(0x%x)", "ParaValueUnderErr", LRes);
	else if (LRes == OverDCErr)
		cs.Format("Error Code = %s(0x%x)", "OverDCErr", LRes);
	else if (LRes == UnderDCErr)
		cs.Format("Error Code = %s(0x%x)", "UnderDCErr", LRes);
	else if (LRes == UnderMDVErr)
		cs.Format("Error Code = %s(0x%x)", "UnderMDVErr", LRes);
	else if (LRes == RegistryCreateFail)
		cs.Format("Error Code = %s(0x%x)", "RegistryCreateFail", LRes);
	else if (LRes == CreateThreadErr)
		cs.Format("Error Code = %s(0x%x)", "CreateThreadErr", LRes);
	else if (LRes == HomeSwStop)
		cs.Format("Error Code = %s(0x%x)", "HomeSwStop", LRes);
	else if (LRes == ChangeSpeedErr)
		cs.Format("Error Code = %s(0x%x)", "ChangeSpeedErr", LRes);
	else if (LRes == DOPortAsDriverStatus)
		cs.Format("Error Code = %s(0x%x)", "DOPortAsDriverStatus", LRes);
	else if (LRes == OpenEventFail)
		cs.Format("Error Code = %s(0x%x)", "OpenEventFail", LRes);
	else if (LRes == DeviceCloseErr)
		cs.Format("Error Code = %s(0x%x)", "DeviceCloseErr", LRes);
	else if (LRes == HomeEMGStop)
		cs.Format("Error Code = %s(0x%x)", "HomeEMGStop", LRes);
	else if (LRes == HomeLMTPStop)
		cs.Format("Error Code = %s(0x%x)", "HomeLMTPStop", LRes);
	else if (LRes == HomeLMTNStop)
		cs.Format("Error Code = %s(0x%x)", "HomeLMTNStop", LRes);
	else if (LRes == HomeALARMStop)
		cs.Format("Error Code = %s(0x%x)", "HomeALARMStop", LRes);
	else if (LRes == AllocateBufferFail)
		cs.Format("Error Code = %s(0x%x)", "AllocateBufferFail", LRes);
	else if (LRes == BufferReAllocate)
		cs.Format("Error Code = %s(0x%x)", "BufferReAllocate", LRes);
	else if (LRes == FreeBufferFail)
		cs.Format("Error Code = %s(0x%x)", "FreeBufferFail", LRes);
	else if (LRes == FirstPointNumberFail)
		cs.Format("Error Code = %s(0x%x)", "FirstPointNumberFail", LRes);
	else if (LRes == PointNumExceedAllocatedSize)
		cs.Format("Error Code = %s(0x%x)", "PointNumExceedAllocatedSize", LRes);
	else if (LRes == BufferNoneAllocate)
		cs.Format("Error Code = %s(0x%x)", "BufferNoneAllocate", LRes);
	else if (LRes == SequenceNumberErr)
		cs.Format("Error Code = %s(0x%x)", "SequenceNumberErr", LRes);
	else if (LRes == PathTypeErr)
		cs.Format("Error Code = %s(0x%x)", "PathTypeErr", LRes);
	else if (LRes == PathTypeMixErr)
		cs.Format("Error Code = %s(0x%x)", "PathTypeMixErr", LRes);
	else if (LRes == BufferDataNotEnough)
		cs.Format("Error Code = %s(0x%x)", "BufferDataNotEnough", LRes);
	else if (LRes == CallDllDriverFailed)
		cs.Format("Error Code = %s(0x%x)", "CallDllDriverFailed", LRes);
	else if (LRes != ERROR_SUCCESS) // 未填入的 Error Code
		cs.Format("Error Code = (0x%x)", LRes);
	else // ERROR_SUCCESS
		return;
	
	AfxMessageBox(cs);
}

////////////////////////////////////////////////////////////////////////////////////
// Motor Function

void CMotor::LoadDriftSpeed(tagMotorParam *pAxis)
{
#ifdef _Demo
	return;
#else

	long Lr;
	int mul = (int)(pAxis->Multiple * 10 / 100.);
	if(mul == 0)
		mul = 1;
//	MC8141PSetRange(pAxis->BoardID, 0, 8000000);
	// SetSpeed
	Lr = MC8141PMotAxisParaSet(pAxis->BoardID, pAxis->AxisNo,
//		0xf,
		0x0,
		pAxis->Start * mul,
		pAxis->DrifSpeed * mul,
		pAxis->DrifSpeed * mul,
		pAxis->Accelerate * _pSpeed * mul,
		62500000 / pAxis->Jerk * mul);
	
	if( Lr != ERROR_SUCCESS )
	{
		CString c = _T("");
		c.Format("LoadDriftSpeed = %d", Lr );
		AfxMessageBox( c );
	}
#endif
}

void CMotor::LoadSearchSpeed(tagMotorParam *pAxis)
{
#ifdef _Demo
	return;
#else
	long Lr;
	int mul = (int)(pAxis->Multiple * 10 / 100.);
	if(mul == 0)
		mul = 1;
//	MC8141PSetRange(pAxis->BoardID, 0, 8000000);
	// SetSpeed

	Lr = MC8141PMotAxisParaSet(pAxis->BoardID, pAxis->AxisNo,
//		0xf,
		0x0,
		pAxis->Start * mul,
		pAxis->SearchSpeed * mul,
		pAxis->SearchSpeed * mul,
		pAxis->Accelerate * _pSpeed * mul,
		62500000 / pAxis->Jerk * mul);


	if( Lr != ERROR_SUCCESS )
	{
		CString c = _T("");
 		c.Format("LoadSearchSpeed = %d", Lr );
		AfxMessageBox( c );
	}
#endif
}
bool CMotor::LoadCycleSpeed(tagMotorParam *pAxis)
{
#ifdef _Demo
	return true;
#else

	long Lr;
	int mul = (int)(pAxis->Multiple * pAxis->Speed / 100.);
	if(mul == 0)
		mul = 1;
//	MC8141PSetRange(pAxis->BoardID, 0, 8000000);
	// SetSpeed
	Lr = MC8141PMotAxisParaSet(pAxis->BoardID, pAxis->AxisNo,
		0xf,
		pAxis->Start * mul,
		pAxis->MaxSpeed * mul,
		pAxis->MaxSpeed * mul,
		pAxis->Accelerate * mul,
		62500000 / pAxis->Jerk * mul);

	if( Lr != ERROR_SUCCESS )
	{
		CString c = _T("");
		c.Format("Speed Parameter = %d", Lr );
		AfxMessageBox( c );
		return false;
	}
#endif
	return true;
}

void CMotor::EnableInterrupt(tagMotorParam *motor, bool bEnable, int iWhichSensor, bool bSensor)
{

#ifdef _Demo
	return;	
#else

	if(bEnable)
	{
		switch(iWhichSensor)
		{
		case enZPhase:
			if(bSensor)
				MC8141PMotWrReg(motor->BoardID, motor->AxisNo, WR1, 0x0003);
			else
				MC8141PMotWrReg(motor->BoardID, motor->AxisNo, WR1, 0x0002);
			break;
		case enTLC:
			if(bSensor)
				MC8141PMotWrReg(motor->BoardID, motor->AxisNo, WR1, 0x0030);
			else
				MC8141PMotWrReg(motor->BoardID, motor->AxisNo, WR1, 0x0020);
			break;
		}
	}
	else
	{
		MC8141PMotWrReg(motor->BoardID, motor->AxisNo, WR1, 0x0000);
		Sleep(_Interrupt_Time_Interval);
		MC8141PMotClrErr(motor->BoardID, motor->AxisNo);
	}
#endif
}

void CMotor::Servo(tagMotorParam *pAxis, bool enable)
{

#ifdef _Demo
	return;
#endif

	EnableInterrupt(pAxis, false);
	if(!m.Info.bCardStatus[pAxis->BoardID])
		return;

	//
	if(enable)
		MC8141PMotDO(pAxis->BoardID, pAxis->AxisNo, 0x01);
	else
		MC8141PMotDO(pAxis->BoardID, pAxis->AxisNo, 0x00);

	//
	pAxis->ServoOn = enable;
	if(!enable)
		m.Info.iStatus = theApp.enUninitial;
}

void CMotor::MotorReadReg(tagMotorParam *pAxis, unsigned short reg, long *value)
{

#ifdef _Demo
	return;
#endif
	
	if(MC8141PMotRdReg(pAxis->BoardID, pAxis->AxisNo, reg, 
		(unsigned long *)value) != ERROR_SUCCESS)
		*value = 0;
}

void CMotor::GetMotorStatus(tagMotorParam *pAxis)
{
#ifdef _Demo
	return;
#endif

	long value = 0;
	MotorReadReg(pAxis, RR2, &value);
	pAxis->nLMT = (value >> 3) & 0x1;
	pAxis->pLMT = (value >> 2) & 0x1;
	pAxis->Alarm = (value >> 4) & 0x1;
	pAxis->EMG = (value >> 5) & 0x1;

	MotorReadReg(pAxis, RR0, &value);
	pAxis->ERRR = ((value >> 4) & pAxis->AxisNo) ? 1 : 0;
	pAxis->DRV = (value & pAxis->AxisNo) ? 1 : 0;

	if(pAxis->AxisNo == X_Axis || pAxis->AxisNo == Y_Axis)
		MotorReadReg(pAxis, RR4, &value);
	else
		MotorReadReg(pAxis, RR5, &value);
	if(pAxis->AxisNo == X_Axis || pAxis->AxisNo == Z_Axis)
	{
		pAxis->InPos = !((value >> 6) & 0x1);
		pAxis->ZPhase = !(value & 0x1);
		pAxis->ZeroSpeed = !((value >> 1) & 0x1);
		pAxis->TLC = !((value >> 2) & 0x1);
	}
	else
	{
		pAxis->InPos = !((value >> 14) & 0x1);
		pAxis->ZPhase = !((value >> 8) & 0x1);
		pAxis->ZeroSpeed = !((value >> 9) & 0x1);
		pAxis->TLC = !((value >> 10) & 0x1);
	}

	MotorReadReg(pAxis, Rcnt, &pAxis->RCount);
	if(pAxis->Reverse)
		pAxis->RCount = -pAxis->RCount;
	MotorReadReg(pAxis, Lcnt, &pAxis->LCount);

	MotorReadReg(pAxis, RR1, &value);
	pAxis->nLMTStop = (value >> 13) & 0x1;
	pAxis->pLMTStop = (value >> 12) & 0x1;
	pAxis->ZPhaseStop = (value >> 8) & 0x1;
	pAxis->TLCStop = (value >> 10) & 0x1;

	if(abs(pAxis->RCount - pAxis->LCount) <= pAxis->InPosRange
		&& !pAxis->DRV)
		pAxis->InPosReal = true;
	else
		pAxis->InPosReal = false;
}
void CMotor::MotorEncoder(tagMotorParam *motor, long pos)
{
#ifdef _Demo
	return;
#endif
	MC8141PMotWrReg(motor->BoardID, motor->AxisNo, Lcnt, pos);
	GetMotorStatus(motor);
	MC8141PMotWrReg(motor->BoardID, motor->AxisNo, Rcnt, -motor->LCount);
}

void CMotor::MotorClearCount(tagMotorParam *pAxis)
{
#ifdef _Demo
	return;
#endif
//	MC8141PMotWrReg(pAxis->BoardID, pAxis->AxisNo, Lcnt, 0);
//	MC8141PMotWrReg(pAxis->BoardID, pAxis->AxisNo, Rcnt, 0);

	MC8141PMotWrReg(pAxis->BoardID, pAxis->AxisNo, Lcnt, 0);
	GetMotorStatus(pAxis);
	MC8141PMotWrReg(pAxis->BoardID, pAxis->AxisNo, Rcnt, -pAxis->LCount);
}

static CMutex MutexMotorClearAlarm; 
void CMotor::ClearMotorAlarm(tagMotorParam *pAxis)
{
#ifdef _Demo

#else
	CAutoLock Lock(MutexMotorClearAlarm);
	MC8141PMotDO(pAxis->BoardID, pAxis->AxisNo, 0x08);
#endif

}
static CMutex MutexMotorClearError;
void CMotor::ClearMotorError(tagMotorParam *pAxis)
{
#ifdef _Demo
	
#else
	CAutoLock Lock(MutexMotorClearAlarm);
	MC8141PMotClrErr(pAxis->BoardID, pAxis->AxisNo);
#endif
}

void CMotor::MotorStop(tagMotorParam *motor)
{
#ifdef _Demo
	
#else
	MC8141PMotStop(motor->BoardID, motor->AxisNo, motor->AxisNo );
#endif
}

int CMotor::GetMotorID(tagMotorParam *motor)
{
#ifdef _Demo
//	return enCodeRunOK;
#endif

	switch(motor->AxisNo)
	{
	case X_Axis:
		return motor->BoardID * 4 + 1;			
		break;
	case Y_Axis:
		return motor->BoardID * 4 + 2;
		break;
	case Z_Axis:
		return motor->BoardID * 4 + 3;
		break;
	default:
		return motor->BoardID * 4 + 4;
		break;
	}

	// if Board 0
	// X_Axis 1
	// Y_Axis 2
	// Z_Axis 3
	// U_Axis 4(default)

	// if Board 1
	// X_Axis 5
	// Y_Axis 6
	// Z_Axis 7
	// U_Axis 8 (default)

	// Inserter	CardID = 0 U_Axis;
	// ArmX		CardID = 0 X_Axis;
	// ArmY		CardID = 0 Y_Axis;
	// ArmZ		CardID = 0 Z_Axis;

	// Shuttle		CardID = 1 X_Axis
}

//
long CMotor::ManualMotorSoftRun(tagMotorParam *pAxis, double dPos, bool PreMove )
{
#ifdef _Demo
	return enCodeRunOK;
#endif	
	unsigned long iStart = ::GetTickCount();

	GetMotorStatus(pAxis);
	while(1)
	{
		GetMotorStatus(pAxis);			
		if(!pAxis->DRV) break;
		
		if(!m.Info.bRunning)
			return enCodeRunOK;
		else if((::GetTickCount() - iStart) > (unsigned long)(m.TimerSetting.iMotorRunTimeout))
			return enCodeMotorBaseTimeout + GetMotorID(pAxis);
		else if( pAxis->Alarm || pAxis->EMG )
			return enCodeMotorBaseDriverAlarm + GetMotorID(pAxis);
		else if( pAxis->ERRR)
			return enCodeMotorBaseOverheat + GetMotorID(pAxis);
				
		Sleep(_Wait);
	}
	int mul = (int)(pAxis->Multiple * pAxis->Speed / 100.);
//	MC8141PSetRange(pAxis->BoardID, 0, 8000000);
	// SetSpeed
	MC8141PMotAxisParaSet(pAxis->BoardID, pAxis->AxisNo,
		0xf,
		pAxis->Start * mul,
		pAxis->MaxSpeed * mul,
		pAxis->MaxSpeed * mul,
		pAxis->Accelerate * _pSpeed * mul,
		62500000 / pAxis->Jerk * mul);
	
	GetMotorStatus(pAxis);
	
	long pulse = (long)dPos - pAxis->LCount;
	switch(pAxis->AxisNo)
	{
	case X_Axis:
		MC8141PMotPtp(pAxis->BoardID, X_Axis, 0, pulse, 0, 0, 0);
		break;
	case Y_Axis:
		MC8141PMotPtp(pAxis->BoardID, Y_Axis, 0, 0, pulse, 0, 0);
		break;
	case Z_Axis:
		MC8141PMotPtp(pAxis->BoardID, Z_Axis, 0, 0, 0, pulse, 0);
		break;
	case U_Axis:
		MC8141PMotPtp(pAxis->BoardID, U_Axis, 0, 0, 0, 0, pulse);
		break;
	}
	iStart = ::GetTickCount();
	// Wait for ready
	while(1)
	{
		GetMotorStatus(pAxis);
		
		if( PreMove )
		{
			if(!pAxis->DRV) 
				break;
		}
		else
		{
			if(pAxis->InPosReal) 
				break;
		}

		if(!m.Info.bRunning)
		{
			MC8141PMotStop(pAxis->BoardID, pAxis->AxisNo, pAxis->AxisNo);
			return enCodeRunOK;
		}
		if((::GetTickCount() - iStart) > (unsigned long)m.TimerSetting.iMotorRunTimeout )
		{
			MC8141PMotStop(pAxis->BoardID, pAxis->AxisNo, pAxis->AxisNo);
			return enCodeMotorBaseTimeout + GetMotorID(pAxis);
		}
		if(pAxis->Alarm || pAxis->EMG)
		{
			MC8141PMotStop(pAxis->BoardID, pAxis->AxisNo, pAxis->AxisNo);
			return enCodeMotorBaseOverheat + GetMotorID(pAxis);
		}
		if(pAxis->nLMT || pAxis->pLMT)
		{
			MC8141PMotStop(pAxis->BoardID, pAxis->AxisNo, pAxis->AxisNo);
			return enCodeMotorBaseOverheat + GetMotorID(pAxis);
		}
		f.ThreadWait();
	}

	return enCodeRunOK;
}
//
long CMotor::MotorSoftRun(tagMotorParam *pAxis, double dPos, bool PreMove, long dTimeout )
{
#ifdef _Demo
	return enCodeRunOK;
#endif	
	unsigned long iStart = ::GetTickCount();

	GetMotorStatus(pAxis);
	while(1)
	{
		GetMotorStatus(pAxis);			
		if(!pAxis->DRV) break;
		
		if(f.IsPause())
			return enCodeRunOK; // thread will handle this error
		if(!m.Info.bRunning)
			return enCodeRunOK;
		else if((::GetTickCount() - iStart) > (unsigned long)(dTimeout))
			return enCodeMotorBaseTimeout + GetMotorID(pAxis);
		else if( pAxis->Alarm || pAxis->EMG )
			return enCodeMotorBaseDriverAlarm + GetMotorID(pAxis);
		else if( pAxis->ERRR)
			return enCodeMotorBaseOverheat + GetMotorID(pAxis);
				
		Sleep(_Wait);
	}
	int mul = (int)(pAxis->Multiple * pAxis->Speed / 100.);
//	MC8141PSetRange(pAxis->BoardID, 0, 8000000);
	// SetSpeed
	MC8141PMotAxisParaSet(pAxis->BoardID, pAxis->AxisNo,
		0xf,
		pAxis->Start * mul,
		pAxis->MaxSpeed * mul,
		pAxis->MaxSpeed * mul,
		pAxis->Accelerate * _pSpeed * mul,
		62500000 / pAxis->Jerk * mul);
	
	GetMotorStatus(pAxis);
	
	long pulse = (long)dPos - pAxis->LCount;
	switch(pAxis->AxisNo)
	{
	case X_Axis:
		MC8141PMotPtp(pAxis->BoardID, X_Axis, 0, pulse, 0, 0, 0);
		break;
	case Y_Axis:
		MC8141PMotPtp(pAxis->BoardID, Y_Axis, 0, 0, pulse, 0, 0);
		break;
	case Z_Axis:
		MC8141PMotPtp(pAxis->BoardID, Z_Axis, 0, 0, 0, pulse, 0);
		break;
	case U_Axis:
		MC8141PMotPtp(pAxis->BoardID, U_Axis, 0, 0, 0, 0, pulse);
		break;
	}
	iStart = ::GetTickCount();
	// Wait for ready
	while(1)
	{
		GetMotorStatus(pAxis);
		
		if(pAxis->InPosReal) 
			break;
		if(!pAxis->DRV) 
			break;

		if(!m.Info.bRunning)
		{
			MC8141PMotStop(pAxis->BoardID, pAxis->AxisNo, pAxis->AxisNo);
			return enCodeRunOK;
		}
		if((::GetTickCount() - iStart) > (unsigned long)(dTimeout) )
		{
			MC8141PMotStop(pAxis->BoardID, pAxis->AxisNo, pAxis->AxisNo);
			return enCodeMotorBaseTimeout + GetMotorID(pAxis);
		}
		if(pAxis->Alarm || pAxis->EMG)
		{
			MC8141PMotStop(pAxis->BoardID, pAxis->AxisNo, pAxis->AxisNo);
			return enCodeMotorBaseDriverAlarm + GetMotorID(pAxis);
		}
		if(pAxis->nLMT || pAxis->pLMT)
		{
			MC8141PMotStop(pAxis->BoardID, pAxis->AxisNo, pAxis->AxisNo);
			return enCodeMotorBaseOverheat + GetMotorID(pAxis);
		}
		if(f.IsPause())
		{
			MC8141PMotStop(pAxis->BoardID, pAxis->AxisNo, pAxis->AxisNo);
			return enCodeRunOK;
		}
		f.ThreadWait();
	}

	return enCodeRunOK;
}
//
long CMotor::ManualMotorRunLine(tagMotorParam *pAxis1, double dPos1, 
							 tagMotorParam *pAxis2, double dPos2, 
							 bool PreMove, double dTimeout)
{

#ifdef _Demo
	return enCodeRunOK;
#endif

	int iStart = ::GetTickCount();
	int iPass = 0;

	// Wait for motor really stop
	GetMotorStatus(pAxis1);
	GetMotorStatus(pAxis2);
	while(1)
	{
	

		iPass = ::GetTickCount() - iStart;
		if(!m.Info.bRunning)
			return enCodeRunOK;
		else if(iPass > dTimeout && pAxis1->DRV)
			return enCodeMotorBaseTimeout + GetMotorID(pAxis1);
		else if(iPass > dTimeout && pAxis2->DRV)
			return enCodeMotorBaseTimeout + GetMotorID(pAxis2);
		else if(pAxis1->Alarm || pAxis1->EMG || pAxis1->ERRR)
			return enCodeMotorBaseOverheat + GetMotorID(pAxis1);
		else if(pAxis2->Alarm || pAxis2->EMG || pAxis2->ERRR)
			return enCodeMotorBaseOverheat + GetMotorID(pAxis2);

		if(!pAxis1->DRV && !pAxis2->DRV) break;

		GetMotorStatus(pAxis1);
		GetMotorStatus(pAxis2);
		Sleep(_Wait);
	}

	// Linear interpolation, we use axis2 as master
	long mul = (long)(pAxis2->Multiple * pAxis2->Speed / 100.);
//	MC8141PSetRange(pAxis2->BoardID, 0, 8000000);
	// SetSpeed

	MC8141PMotAxisParaSet(pAxis2->BoardID, 0,
		0xf,
		pAxis2->Start * mul,
		pAxis2->MaxSpeed * mul,
		pAxis2->MaxSpeed * mul,
		pAxis2->Accelerate * _pSpeed * mul,
		62500000 / pAxis2->Jerk * mul);


	long pulse1 = (long)dPos1 - pAxis1->LCount;
	long pulse2 = (long)dPos2 - pAxis2->LCount;

	MC8141PMotLine(pAxis1->BoardID, pAxis1->AxisNo | pAxis2->AxisNo, 0,
		((pAxis1->AxisNo / X_Axis) & 0x1) * pulse1 + ((pAxis2->AxisNo / X_Axis) & 0x1) * pulse2,
		((pAxis1->AxisNo / Y_Axis) & 0x1) * pulse1 + ((pAxis2->AxisNo / Y_Axis) & 0x1) * pulse2,
		((pAxis1->AxisNo / Z_Axis) & 0x1) * pulse1 + ((pAxis2->AxisNo / Z_Axis) & 0x1) * pulse2,
		((pAxis1->AxisNo / U_Axis) & 0x1) * pulse1 + ((pAxis2->AxisNo / U_Axis) & 0x1) * pulse2);

	// Wait for ready
	while(1)
	{
		GetMotorStatus(pAxis1);
		GetMotorStatus(pAxis2);
		
		
		iPass = ::GetTickCount() - iStart;
		if(!m.Info.bRunning)
		{
			MC8141PMotStop(pAxis1->BoardID, pAxis1->AxisNo, pAxis1->AxisNo);
			MC8141PMotStop(pAxis2->BoardID, pAxis2->AxisNo, pAxis2->AxisNo);
			return enCodeRunOK;
		}
		else if(iPass > dTimeout && !pAxis1->InPosReal)
		{
			MC8141PMotStop(pAxis1->BoardID, pAxis1->AxisNo, pAxis1->AxisNo);
			MC8141PMotStop(pAxis2->BoardID, pAxis2->AxisNo, pAxis2->AxisNo);
			return enCodeMotorBaseTimeout + GetMotorID(pAxis1);
		}
		else if(iPass > dTimeout && !pAxis2->InPosReal)
		{
			MC8141PMotStop(pAxis1->BoardID, pAxis1->AxisNo, pAxis1->AxisNo);
			MC8141PMotStop(pAxis2->BoardID, pAxis2->AxisNo, pAxis2->AxisNo);
			return enCodeMotorBaseTimeout + GetMotorID(pAxis2);
		}
		else if(pAxis1->Alarm || pAxis1->EMG || pAxis1->ERRR)
		{
			MC8141PMotStop(pAxis1->BoardID, pAxis1->AxisNo, pAxis1->AxisNo);
			MC8141PMotStop(pAxis2->BoardID, pAxis2->AxisNo, pAxis2->AxisNo);
			return enCodeMotorBaseOverheat + GetMotorID(pAxis1);
		}
		else if(pAxis2->Alarm || pAxis2->EMG || pAxis2->ERRR)
		{
			MC8141PMotStop(pAxis1->BoardID, pAxis1->AxisNo, pAxis1->AxisNo);
			MC8141PMotStop(pAxis2->BoardID, pAxis2->AxisNo, pAxis2->AxisNo);
			return enCodeMotorBaseOverheat + GetMotorID(pAxis2);
		}
		if(PreMove)
		{
			if(!pAxis1->DRV && !pAxis2->DRV)
				break;	
		}
		else
		{	
			if(pAxis1->InPosReal && pAxis2->InPosReal 
				&& !pAxis1->DRV && !pAxis2->DRV )
				break;
		}
		Sleep(_Wait);
	}
	return enCodeRunOK;
}
//

long CMotor::ManualMotorRun(tagMotorParam *pAxis, double dPos, bool PreMove, long dTimeout )
{
#ifdef _Demo
	return enCodeRunOK;
#endif	

	// Note : Manual Mode. We do not care System Status.
	// Because we normal use it in "READY"

	unsigned long iStart = ::GetTickCount();
	
	GetMotorStatus(pAxis);
	while(1)
	{
		GetMotorStatus(pAxis);			
		if(!pAxis->DRV) break;
		
		if(!m.Info.bRunning)
			return enCodeRunOK;
		else if((::GetTickCount() - iStart) > (unsigned long)(dTimeout))
			return enCodeMotorBaseTimeout + GetMotorID(pAxis);
		else if(pAxis->Alarm || pAxis->EMG || pAxis->ERRR)
			return enCodeMotorBaseOverheat + GetMotorID(pAxis);
				
		Sleep(_Wait);
	}
	int mul = (int)(pAxis->Multiple * pAxis->Speed / 100.);
//	MC8141PSetRange(pAxis->BoardID, 0, 8000000);
	// SetSpeed
	MC8141PMotAxisParaSet(pAxis->BoardID, pAxis->AxisNo,
		0xf,
		pAxis->Start * mul,
		pAxis->MaxSpeed * mul,
		pAxis->MaxSpeed * mul,
		pAxis->Accelerate * _pSpeed * mul,
		62500000 / pAxis->Jerk * mul);
	
	GetMotorStatus(pAxis);
	long pulse = (long)dPos - pAxis->LCount;
	switch(pAxis->AxisNo)
	{
	case X_Axis:
		MC8141PMotPtp(pAxis->BoardID, X_Axis, 0, pulse, 0, 0, 0);
		break;
	case Y_Axis:
		MC8141PMotPtp(pAxis->BoardID, Y_Axis, 0, 0, pulse, 0, 0);
		break;
	case Z_Axis:
		MC8141PMotPtp(pAxis->BoardID, Z_Axis, 0, 0, 0, pulse, 0);
		break;
	case U_Axis:
		MC8141PMotPtp(pAxis->BoardID, U_Axis, 0, 0, 0, 0, pulse);
		break;
	}


	iStart = ::GetTickCount();
	// Wait for ready
	while(1)
	{
		GetMotorStatus(pAxis);
		
		if( PreMove )
		{
			if(!pAxis->DRV) 
			break;
		}
		else
		{
			if(pAxis->InPosReal) 
				break;
		}

		if(!m.Info.bRunning)
		{
			MC8141PMotStop(pAxis->BoardID, pAxis->AxisNo, pAxis->AxisNo);
			return enCodeRunOK;
		}

		if((::GetTickCount() - iStart) > (unsigned long)dTimeout )
		{
			MC8141PMotStop(pAxis->BoardID, pAxis->AxisNo, pAxis->AxisNo);
			return enCodeMotorBaseTimeout + GetMotorID(pAxis);
		}
		if(pAxis->Alarm || pAxis->EMG)
		{
			MC8141PMotStop(pAxis->BoardID, pAxis->AxisNo, pAxis->AxisNo);
			return enCodeMotorBaseDriverAlarm + GetMotorID(pAxis);
		}
		if(pAxis->nLMT || pAxis->pLMT)
		{
			MC8141PMotStop(pAxis->BoardID, pAxis->AxisNo, pAxis->AxisNo);
			return enCodeMotorBaseOverheat + GetMotorID(pAxis);
		}
//		if(f.IsPause())
//		{
//			MC8141PMotStop(pAxis->BoardID, pAxis->AxisNo, pAxis->AxisNo);
//			return enCodeRunOK;
//		}

		f.ThreadWait();
	}

	return enCodeRunOK;
}

long CMotor::MotorRunAnyway(tagMotorParam *pAxis, double dPos, bool PreMove, long dTimeout )
{
#ifdef _Demo
	return enCodeRunOK;
#endif	
	
	// 1.0Ag
	MC8141PMotStop(pAxis->BoardID, pAxis->AxisNo, pAxis->AxisNo);

	
	GetMotorStatus(pAxis);
	unsigned long iStart = ::GetTickCount();
	while(1)
	{
		GetMotorStatus(pAxis);			
		if(!pAxis->DRV) break;
		
		if(f.IsPause())
			return enCodeRunOK; // thread will handle this error
		if(!m.Info.bRunning)
			return enCodeRunOK;
		else if((::GetTickCount() - iStart) > (unsigned long)(dTimeout))
			return enCodeMotorBaseTimeout + GetMotorID(pAxis);
		else if(pAxis->Alarm || pAxis->EMG )
			return enCodeMotorBaseDriverAlarm + GetMotorID(pAxis);

		Sleep(_Wait);
	}

	int mul = (int)(pAxis->Multiple * 10 / 100.);
	// SetSpeed
	MC8141PMotAxisParaSet(pAxis->BoardID, pAxis->AxisNo,
		0xf,
		pAxis->Start * mul,
		pAxis->SearchSpeed *mul,
		pAxis->SearchSpeed * mul,
		pAxis->Accelerate * _pSpeed * mul,
		62500000 / pAxis->Jerk * mul);
	GetMotorStatus(pAxis);
	long pulse = (long)dPos;
	switch(pAxis->AxisNo)
	{
	case X_Axis:
		MC8141PMotPtp(pAxis->BoardID, X_Axis, 0, pulse, 0, 0, 0);
		break;
	case Y_Axis:
		MC8141PMotPtp(pAxis->BoardID, Y_Axis, 0, 0, pulse, 0, 0);
		break;
	case Z_Axis:
		MC8141PMotPtp(pAxis->BoardID, Z_Axis, 0, 0, 0, pulse, 0);
		break;
	case U_Axis:
		MC8141PMotPtp(pAxis->BoardID, U_Axis, 0, 0, 0, 0, pulse);
		break;
	}

	// 1.0Ag
	// Remove this and re-build new one
//	Sleep(10);
	f.Wait(2000);	//避免太快檢查成功

	iStart = ::GetTickCount();
	// Wait for ready
	while(1)
	{
		GetMotorStatus(pAxis);
		
		if( PreMove )
		{
			if(!pAxis->DRV) 
				break;
		}
		else 
		{
			// 1.0Ag
			// Remove this and re-build new one
			/*
			if(pAxis->InPosReal && !pAxis->DRV )
				break;
			*/
			if(pAxis->InPosReal && !pAxis->DRV && pAxis->ZeroSpeed )
				break;
		}

		if(!m.Info.bRunning)
		{
			MC8141PMotStop(pAxis->BoardID, pAxis->AxisNo, pAxis->AxisNo);
			return enCodeRunOK;
		}
		if(( ::GetTickCount() - iStart) > (unsigned long)dTimeout )
		{
			// DEBUG
			long s = ::GetTickCount();
			MC8141PMotStop(pAxis->BoardID, pAxis->AxisNo, pAxis->AxisNo);
			return enCodeMotorBaseTimeout + GetMotorID(pAxis);
		}
		if(pAxis->Alarm || pAxis->EMG)
		{
			MC8141PMotStop(pAxis->BoardID, pAxis->AxisNo, pAxis->AxisNo);
			return enCodeMotorBaseDriverAlarm + GetMotorID(pAxis);
		}
		if(f.IsPause())
		{
			MC8141PMotStop(pAxis->BoardID, pAxis->AxisNo, pAxis->AxisNo);
			return enCodeRunOK;
		}

		f.ThreadWait();
	}

	return enCodeRunOK;
}

long CMotor::MotorRun(tagMotorParam *pAxis, double dPos, bool PreMove, long dTimeout )
{
#ifdef _Demo
	return enCodeRunOK;
#endif	

	unsigned long iStart = ::GetTickCount();
	
	GetMotorStatus(pAxis);
	while(1)
	{
		GetMotorStatus(pAxis);			
		if(!pAxis->DRV) break;
		
		if(f.IsPause())
			return enCodeRunOK; // thread will handle this error
		if(!m.Info.bRunning)
			return enCodeRunOK;
		else if((::GetTickCount() - iStart) > (unsigned long)(dTimeout))
			return enCodeMotorBaseTimeout + GetMotorID(pAxis);
		else if( pAxis->Alarm || pAxis->EMG )
			return enCodeMotorBaseDriverAlarm + GetMotorID(pAxis);
		else if( pAxis->ERRR)
			return enCodeMotorBaseOverheat + GetMotorID(pAxis);
				
		Sleep(_Wait);
	}
	int mul = (int)(pAxis->Multiple * pAxis->Speed / 100.);
//	MC8141PSetRange(pAxis->BoardID, 0, 8000000);
	// SetSpeed
	LRESULT Res = MC8141PMotAxisParaSet(pAxis->BoardID, pAxis->AxisNo,
		0xf,
		pAxis->Start * mul,
		pAxis->MaxSpeed * mul,
		pAxis->MaxSpeed * mul,
		pAxis->Accelerate * _pSpeed * mul,
		62500000 / pAxis->Jerk * mul);

	//
	if( !f.Motor.IsMotorErrorCodeCheck( Res ) )
	{
		f.SingleMotorLog( f.Motor.IsMotorErrorCodeLog( Res )  );
	}
	
	GetMotorStatus(pAxis);
	long pulse = (long)dPos - pAxis->LCount;
	switch(pAxis->AxisNo)
	{
	case X_Axis:
		MC8141PMotPtp(pAxis->BoardID, X_Axis, 0, pulse, 0, 0, 0);
		break;
	case Y_Axis:
		MC8141PMotPtp(pAxis->BoardID, Y_Axis, 0, 0, pulse, 0, 0);
		break;
	case Z_Axis:
		MC8141PMotPtp(pAxis->BoardID, Z_Axis, 0, 0, 0, pulse, 0);
		break;
	case U_Axis:
		MC8141PMotPtp(pAxis->BoardID, U_Axis, 0, 0, 0, 0, pulse);
		break;
	}

	iStart = ::GetTickCount();
	// Wait for ready
	while(1)
	{
		GetMotorStatus(pAxis);
		
		if( PreMove )
		{
			if(!pAxis->DRV) 
				break;
		}
		else
		{
			if(pAxis->InPosReal) 
				break;
		}

		if(!m.Info.bRunning)
		{
			MC8141PMotStop(pAxis->BoardID, pAxis->AxisNo, pAxis->AxisNo);
			return enCodeRunOK;
		}
		else if((::GetTickCount() - iStart) > (unsigned long)dTimeout )
		{
			MC8141PMotStop(pAxis->BoardID, pAxis->AxisNo, pAxis->AxisNo);
			return enCodeMotorBaseTimeout + GetMotorID(pAxis);
		}
		else if(pAxis->Alarm || pAxis->EMG)
		{
			MC8141PMotStop(pAxis->BoardID, pAxis->AxisNo, pAxis->AxisNo);
			return enCodeMotorBaseDriverAlarm + GetMotorID(pAxis);
		}
		else if(pAxis->nLMT || pAxis->pLMT)
		{
			MC8141PMotStop(pAxis->BoardID, pAxis->AxisNo, pAxis->AxisNo);
			return enCodeMotorBaseOverheat + GetMotorID(pAxis);
		}
		else if(f.IsPause())
		{
			MC8141PMotStop(pAxis->BoardID, pAxis->AxisNo, pAxis->AxisNo);
			return enCodeRunOK;
		}

		f.ThreadWait();
	}

	return enCodeRunOK;
}

//
long CMotor::MotorContinueMove(tagMotorParam *pAxis, bool bDirToPositive, bool bMonitor)
{
#ifdef _Demo
	return enCodeRunOK;
#endif
		// bDirToPositive : true is go pLmt(0x00) . false is go nLmt(motor->AxisNo)
		// MotorContinueMove(tagMotorParam *pAxis, bool bDirToPositive, bool bMonitor)
		int value;
		if(bDirToPositive)
			value = 0x00;
		else
			value = pAxis->AxisNo;
		MC8141PMotCmove(pAxis->BoardID, pAxis->AxisNo, value);
		
		if(!bMonitor) 
			return enCodeRunOK;

		int iStart = ::GetTickCount();
		while(1)
		{
			// Wait for motor really stop
			GetMotorStatus(pAxis);
			if(bDirToPositive && pAxis->pLMT)
				break;
			else if(!bDirToPositive && pAxis->nLMT)
				break;
			else if(!pAxis->DRV)
				MC8141PMotCmove(pAxis->BoardID, pAxis->AxisNo, value);

			if(f.IsPause())
			{
				MC8141PMotStop(pAxis->BoardID, pAxis->AxisNo, pAxis->AxisNo );
				return enCodeRunOK; 
			}
			if(!m.Info.bRunning)
			{
				MC8141PMotStop(pAxis->BoardID, pAxis->AxisNo, pAxis->AxisNo );
				return enCodeRunOK;
			}

			if(pAxis->Alarm || pAxis->EMG)
			{
				MC8141PMotStop(pAxis->BoardID, pAxis->AxisNo, pAxis->AxisNo );
				return enCodeMotorBaseDriverAlarm + GetMotorID(pAxis);
			}
			if(::GetTickCount() - iStart > (unsigned long)(m.TimerSetting.iInitialTimeout) )
			{
				MC8141PMotStop(pAxis->BoardID, pAxis->AxisNo, pAxis->AxisNo );
				return enCodeMotorBaseTimeout + GetMotorID(pAxis);
			}
			
			Sleep(_Wait);
		}
		MC8141PMotStop(pAxis->BoardID, pAxis->AxisNo, pAxis->AxisNo );

		return enCodeRunOK;
}

long CMotor::MoveOffpLimit(tagMotorParam *pAxis, long timeout )
{
#ifdef _Demo
	return enCodeRunOK;
#endif

	int iStart = ::GetTickCount();
	// Move off the limit toward the other limit.
	MC8141PMotCmove(pAxis->BoardID, pAxis->AxisNo, pAxis->AxisNo );
	while (1)
	{		
		GetMotorStatus(pAxis);

		if ( !pAxis->pLMT && !pAxis->ERRR)
		{			
			MC8141PMotStop( pAxis->BoardID, pAxis->AxisNo, pAxis->AxisNo );	// slow down stop
			break;
		}
		else if(!pAxis->DRV)
			MC8141PMotCmove(pAxis->BoardID, pAxis->AxisNo, pAxis->AxisNo);


		if ( f.IsPause() )
		{
			// Stop motor immediately when initializing.
			MC8141PMotStop( pAxis->BoardID, pAxis->AxisNo, pAxis->AxisNo );
			return enCodeRunOK;		// thread will handle this error
		}
		// 8141P need to check ERR flag also.
		if(!m.Info.bRunning)
		{
			MC8141PMotStop( pAxis->BoardID, pAxis->AxisNo, pAxis->AxisNo );
			return enCodeRunOK;
		}
		
		if ( ::GetTickCount() - iStart > (unsigned long)timeout )
		{
			MC8141PMotStop( pAxis->BoardID, pAxis->AxisNo, pAxis->AxisNo );
			return enCodeMotorBaseTimeout + GetMotorID(pAxis);
		}
		Sleep(_Wait);
	}

	return enCodeRunOK;
}

long CMotor::MoveOffnLimit(tagMotorParam *pAxis, long timeout )
{
#ifdef _Demo
	return enCodeRunOK;
#endif

	int iStart = ::GetTickCount();
	// Move off the limit toward the other limit.
	
	int value;
	value = 0x00;
	MC8141PMotCmove(pAxis->BoardID, pAxis->AxisNo, value);	

	while (1)
	{		
		GetMotorStatus(pAxis);

		if (!pAxis->nLMT && !pAxis->ERRR)
		{			
			MC8141PMotStop( pAxis->BoardID, pAxis->AxisNo, pAxis->AxisNo );	// slow down stop
			break;
		}
		else if(!pAxis->DRV)
			MC8141PMotCmove(pAxis->BoardID, pAxis->AxisNo, value);


//		else if ( f.IsPause() )
		if ( f.IsPause() )
		{
			// Stop motor immediately when initializing.
			MC8141PMotStop( pAxis->BoardID, pAxis->AxisNo, pAxis->AxisNo );
			return enCodeRunOK;		// thread will handle this error
		}		
		if(!m.Info.bRunning)
		{
			MC8141PMotStop( pAxis->BoardID, pAxis->AxisNo, pAxis->AxisNo );
			return enCodeRunOK;
		}
		
		// 8141P need to check ERR flag also.
		if ( ::GetTickCount() - iStart > (unsigned long)timeout )
		{
			MC8141PMotStop( pAxis->BoardID, pAxis->AxisNo, pAxis->AxisNo );
			return enCodeMotorBaseTimeout + GetMotorID(pAxis);
		}

		Sleep(_Wait);
	}

	return enCodeRunOK;
}
long CMotor::MoveOffnNLimit(tagMotorParam *pAxis, long timeout )
{
#ifdef _Demo
	return enCodeRunOK;
#endif

	int iStart = ::GetTickCount();
	// Move off the limit toward the other limit.
	
	int value;
	value = 0x00;
	MC8141PMotCmove(pAxis->BoardID, pAxis->AxisNo, value);	

	int iNCounter = 0;
	while (1)
	{		
		GetMotorStatus(pAxis);
		
		if (!pAxis->nLMT && !pAxis->ERRR)
		{	
			iNCounter++;
		}
		else if( pAxis->nLMT && pAxis->ERRR )
		{
			iNCounter = 0;
		}
		else if(!pAxis->DRV)
			MC8141PMotCmove(pAxis->BoardID, pAxis->AxisNo, value);

		//
		if( iNCounter > 5 )
		{
			MC8141PMotStop( pAxis->BoardID, pAxis->AxisNo, pAxis->AxisNo );	// slow down stop
			break;		
		}

//		else if ( f.IsPause() )
		if ( f.IsPause() )
		{
			// Stop motor immediately when initializing.
			MC8141PMotStop( pAxis->BoardID, pAxis->AxisNo, pAxis->AxisNo );
			return enCodeRunOK;		// thread will handle this error
		}		
		if(!m.Info.bRunning)
		{
			MC8141PMotStop( pAxis->BoardID, pAxis->AxisNo, pAxis->AxisNo );
			return enCodeRunOK;
		}
		
		// 8141P need to check ERR flag also.
		if ( ::GetTickCount() - iStart > (unsigned long)timeout )
		{
			MC8141PMotStop( pAxis->BoardID, pAxis->AxisNo, pAxis->AxisNo );
			return enCodeMotorBaseTimeout + GetMotorID(pAxis);
		}

		Sleep(_Wait);
	}

	return enCodeRunOK;
}

//
long CMotor::MotorRunLine(tagMotorParam &pAxis1, double dPos1, 
							 tagMotorParam &pAxis2, double dPos2, 
							 bool PreMove, double dTimeout)
{

#ifdef _Demo
	return enCodeRunOK;
#endif

	int iStart = ::GetTickCount();
	int iPass = 0;

	// Wait for motor really stop
	GetMotorStatus(&pAxis1);
	GetMotorStatus(&pAxis2);
	while(1)
	{
		if(!pAxis1.DRV && !pAxis2.DRV) break;

		iPass = ::GetTickCount() - iStart;
		if( f.IsPause())
			return enCodeRunOK;
		else if(!m.Info.bRunning)
			return enCodeRunOK;
		else if(iPass > dTimeout && pAxis1.DRV)
			return enCodeMotorBaseTimeout + GetMotorID(&pAxis1);
		else if(iPass > dTimeout && pAxis2.DRV)
			return enCodeMotorBaseTimeout + GetMotorID(&pAxis2);
		else if(pAxis1.Alarm || pAxis1.EMG || pAxis1.ERRR)
			return enCodeMotorBaseOverheat + GetMotorID(&pAxis1);
		else if(pAxis2.Alarm || pAxis2.EMG || pAxis2.ERRR)
			return enCodeMotorBaseOverheat + GetMotorID(&pAxis2);

		GetMotorStatus(&pAxis1);
		GetMotorStatus(&pAxis2);
		Sleep(_Wait);
	}

	// Linear interpolation, we use axis2 as master
//	long mul = (long)(pAxis2.Multiple * pAxis2.Speed / 100.);
	int mul = (pAxis2.Multiple * pAxis2.Speed / 100.);
//	MC8141PSetRange(pAxis2.BoardID, 0, 8000000);
	// SetSpeed

	LRESULT Res = MC8141PMotAxisParaSet(pAxis2.BoardID, 0,
		0xf,
		pAxis2.Start * mul,
		pAxis2.MaxSpeed * mul,
		pAxis2.MaxSpeed * mul,
		pAxis2.Accelerate * _pSpeed * mul,
		62500000 / pAxis2.Jerk * mul);

	// 
	// 檢查速度有沒有寫進去
	if( !f.Motor.IsMotorErrorCodeCheck( Res ) )
	{
		f.MotorLog( f.Motor.IsMotorErrorCodeLog( Res )  );
	}

	if( pAxis2.Start * mul != 5000 ||
		pAxis2.MaxSpeed * mul != 360000||
		pAxis2.MaxSpeed * mul != 360000||
		pAxis2.Accelerate * _pSpeed * mul != 800000 ||
		62500000 / pAxis2.Jerk * mul != 20491800
	   )
	  {
		 f.SpeedMotorLog( "Speed No Match");
	  }

	//

	long pulse1 = (long)dPos1 - pAxis1.LCount;
	long pulse2 = (long)dPos2 - pAxis2.LCount;

	MC8141PMotLine(pAxis1.BoardID, pAxis1.AxisNo | pAxis2.AxisNo, 0,
		((pAxis1.AxisNo / X_Axis) & 0x1) * pulse1 + ((pAxis2.AxisNo / X_Axis) & 0x1) * pulse2,
		((pAxis1.AxisNo / Y_Axis) & 0x1) * pulse1 + ((pAxis2.AxisNo / Y_Axis) & 0x1) * pulse2,
		((pAxis1.AxisNo / Z_Axis) & 0x1) * pulse1 + ((pAxis2.AxisNo / Z_Axis) & 0x1) * pulse2,
		((pAxis1.AxisNo / U_Axis) & 0x1) * pulse1 + ((pAxis2.AxisNo / U_Axis) & 0x1) * pulse2);

	// Wait for ready
	while(1)
	{
		GetMotorStatus(&pAxis1);
		GetMotorStatus(&pAxis2);
		if(PreMove)
		{
			if(!pAxis1.DRV && !pAxis2.DRV)
				break;
		}
		else
		{
			if(pAxis1.InPosReal && pAxis2.InPosReal
				&& !pAxis1.DRV && !pAxis2.DRV )
				break;
		}

		// 
		if( m.Setting.m_bPreMove )
		{
			if ( m.Setting.m_iPreMoveDistance != 0 )
			{
				if ( abs(dPos1 - pAxis1.RCount) < 
					( m.Setting.m_iPreMoveDistance * m.m_Ratio.X_GearRation ) )
				{
					if( abs(dPos2 - pAxis2.RCount) < 
						( m.Setting.m_iPreMoveDistance * m.m_Ratio.Y_GearRation ) )
						break;
				}
			}
		}
		
		iPass = ::GetTickCount() - iStart;
		if( f.IsPause())
		{
			MC8141PMotStop(pAxis1.BoardID, pAxis1.AxisNo, pAxis1.AxisNo);
			MC8141PMotStop(pAxis2.BoardID, pAxis2.AxisNo, pAxis2.AxisNo);
			return enCodeRunOK;
		}
		else if(!m.Info.bRunning)
		{
			MC8141PMotStop(pAxis1.BoardID, pAxis1.AxisNo, pAxis1.AxisNo);
			MC8141PMotStop(pAxis2.BoardID, pAxis2.AxisNo, pAxis2.AxisNo);
			return enCodeRunOK;
		}
		else if(iPass > dTimeout && !pAxis1.InPosReal)
		{
			MC8141PMotStop(pAxis1.BoardID, pAxis1.AxisNo, pAxis1.AxisNo);
			MC8141PMotStop(pAxis2.BoardID, pAxis2.AxisNo, pAxis2.AxisNo);
			return enCodeMotorBaseTimeout + GetMotorID(&pAxis1);
		}
		else if(iPass > dTimeout && !pAxis2.InPosReal)
		{
			MC8141PMotStop(pAxis1.BoardID, pAxis1.AxisNo, pAxis1.AxisNo);
			MC8141PMotStop(pAxis2.BoardID, pAxis2.AxisNo, pAxis2.AxisNo);
			return enCodeMotorBaseTimeout + GetMotorID(&pAxis2);
		}
		else if(pAxis1.Alarm || pAxis1.EMG || pAxis1.ERRR)
		{
			MC8141PMotStop(pAxis1.BoardID, pAxis1.AxisNo, pAxis1.AxisNo);
			MC8141PMotStop(pAxis2.BoardID, pAxis2.AxisNo, pAxis2.AxisNo);
			return enCodeMotorBaseOverheat + GetMotorID(&pAxis1);
		}
		else if(pAxis2.Alarm || pAxis2.EMG || pAxis2.ERRR)
		{
			MC8141PMotStop(pAxis1.BoardID, pAxis1.AxisNo, pAxis1.AxisNo);
			MC8141PMotStop(pAxis2.BoardID, pAxis2.AxisNo, pAxis2.AxisNo);
			return enCodeMotorBaseOverheat + GetMotorID(&pAxis2);
		}

		Sleep(_Wait);
	}

	return enCodeRunOK;
}

// 
long CMotor::MotorRunLineLocation(tagMotorParam &pAxis1, double dPos1, 
							 tagMotorParam &pAxis2, double dPos2, 
							 bool PreMove, double dTimeout)
{

#ifdef _Demo
	return enCodeRunOK;
#endif

	int iStart = ::GetTickCount();
	int iPass = 0;

	// Wait for motor really stop
	GetMotorStatus(&pAxis1);
	GetMotorStatus(&pAxis2);
	while(1)
	{
		if(!pAxis1.DRV && !pAxis2.DRV) break;

		iPass = ::GetTickCount() - iStart;
		if( f.IsPause())
			return enCodeRunOK;
		else if(!m.Info.bRunning)
			return enCodeRunOK;
		else if(iPass > dTimeout && pAxis1.DRV)
			return enCodeMotorBaseTimeout + GetMotorID(&pAxis1);
		else if(iPass > dTimeout && pAxis2.DRV)
			return enCodeMotorBaseTimeout + GetMotorID(&pAxis2);
		else if(pAxis1.Alarm || pAxis1.EMG || pAxis1.ERRR)
			return enCodeMotorBaseOverheat + GetMotorID(&pAxis1);
		else if(pAxis2.Alarm || pAxis2.EMG || pAxis2.ERRR)
			return enCodeMotorBaseOverheat + GetMotorID(&pAxis2);

		GetMotorStatus(&pAxis1);
		GetMotorStatus(&pAxis2);
		Sleep(_Wait);
	}

	// Linear interpolation, we use axis2 as master
//	long mul = (long)(pAxis2.Multiple * pAxis2.Speed / 100.);
	int mul = (pAxis2.Multiple * pAxis2.Speed / 100.);
//	MC8141PSetRange(pAxis2.BoardID, 0, 8000000);
	// SetSpeed

	LRESULT Res = MC8141PMotAxisParaSet(pAxis2.BoardID, 0,
		0xf,
		pAxis2.Start * mul,
		pAxis2.MaxSpeed * mul,
		pAxis2.MaxSpeed * mul,
		pAxis2.Accelerate * _pSpeed * mul,
		62500000 / pAxis2.Jerk * mul);

	// 
	// 檢查速度有沒有寫進去
	if( !f.Motor.IsMotorErrorCodeCheck( Res ) )
	{
		f.MotorLog( f.Motor.IsMotorErrorCodeLog( Res )  );
	}

	if( pAxis2.Start * mul != 5000 ||
		pAxis2.MaxSpeed * mul != 360000||
		pAxis2.MaxSpeed * mul != 360000||
		pAxis2.Accelerate * _pSpeed * mul != 800000 ||
		62500000 / pAxis2.Jerk * mul != 20491800
	   )
	  {
		 f.SpeedMotorLog( "Speed No Match");
	  }

	//

	long pulse1 = (long)dPos1 - pAxis1.LCount;
	long pulse2 = (long)dPos2 - pAxis2.LCount;

	MC8141PMotLine(pAxis1.BoardID, pAxis1.AxisNo | pAxis2.AxisNo, 0,
		((pAxis1.AxisNo / X_Axis) & 0x1) * pulse1 + ((pAxis2.AxisNo / X_Axis) & 0x1) * pulse2,
		((pAxis1.AxisNo / Y_Axis) & 0x1) * pulse1 + ((pAxis2.AxisNo / Y_Axis) & 0x1) * pulse2,
		((pAxis1.AxisNo / Z_Axis) & 0x1) * pulse1 + ((pAxis2.AxisNo / Z_Axis) & 0x1) * pulse2,
		((pAxis1.AxisNo / U_Axis) & 0x1) * pulse1 + ((pAxis2.AxisNo / U_Axis) & 0x1) * pulse2);

	// Wait for ready
	while(1)
	{
		GetMotorStatus(&pAxis1);
		GetMotorStatus(&pAxis2);
		if(PreMove)
		{
			if(!pAxis1.DRV && !pAxis2.DRV)
				break;
		}
		else
		{
			if(pAxis1.InPosReal && pAxis2.InPosReal
				&& !pAxis1.DRV && !pAxis2.DRV )
				break;
		}

		if( m.Setting.m_bPreMove )
		{
			if ( m.Setting.m_iPreMoveDistance != 0 )
			{
				if ( abs(dPos1 - pAxis1.RCount) < 
					( m.Setting.m_iPreMoveDistance * m.m_Ratio.X_GearRation ) )
				{
					if( abs(dPos2 - pAxis2.RCount) < 
						( m.Setting.m_iPreMoveDistance * m.m_Ratio.Y_GearRation ) )
						break;
				}
			}
		}
		
		iPass = ::GetTickCount() - iStart;
		if( f.IsPause())
		{
			MC8141PMotStop(pAxis1.BoardID, pAxis1.AxisNo, pAxis1.AxisNo);
			MC8141PMotStop(pAxis2.BoardID, pAxis2.AxisNo, pAxis2.AxisNo);
			return enCodeRunOK;
		}
		else if(!m.Info.bRunning)
		{
			MC8141PMotStop(pAxis1.BoardID, pAxis1.AxisNo, pAxis1.AxisNo);
			MC8141PMotStop(pAxis2.BoardID, pAxis2.AxisNo, pAxis2.AxisNo);
			return enCodeRunOK;
		}
		else if(iPass > dTimeout && !pAxis1.InPosReal)
		{
			MC8141PMotStop(pAxis1.BoardID, pAxis1.AxisNo, pAxis1.AxisNo);
			MC8141PMotStop(pAxis2.BoardID, pAxis2.AxisNo, pAxis2.AxisNo);
			return enCodeMotorBaseTimeout + GetMotorID(&pAxis1);
		}
		else if(iPass > dTimeout && !pAxis2.InPosReal)
		{
			MC8141PMotStop(pAxis1.BoardID, pAxis1.AxisNo, pAxis1.AxisNo);
			MC8141PMotStop(pAxis2.BoardID, pAxis2.AxisNo, pAxis2.AxisNo);
			return enCodeMotorBaseTimeout + GetMotorID(&pAxis2);
		}
		else if(pAxis1.Alarm || pAxis1.EMG || pAxis1.ERRR)
		{
			MC8141PMotStop(pAxis1.BoardID, pAxis1.AxisNo, pAxis1.AxisNo);
			MC8141PMotStop(pAxis2.BoardID, pAxis2.AxisNo, pAxis2.AxisNo);
			return enCodeMotorBaseOverheat + GetMotorID(&pAxis1);
		}
		else if(pAxis2.Alarm || pAxis2.EMG || pAxis2.ERRR)
		{
			MC8141PMotStop(pAxis1.BoardID, pAxis1.AxisNo, pAxis1.AxisNo);
			MC8141PMotStop(pAxis2.BoardID, pAxis2.AxisNo, pAxis2.AxisNo);
			return enCodeMotorBaseOverheat + GetMotorID(&pAxis2);
		}

		Sleep(_Wait);
	}

	return enCodeRunOK;
}

// Motor Function
////////////////////////////////////////////////////////////////////////////////////
bool CMotor::SearchMotorMovetopLimt(tagMotorParam *pAxis, long timeout )
{
#ifdef _Demo
	return true;
#endif
	// nLmt		 檢查 nLmt	設為1要檢查.設為0不檢查
	// pLmt		 檢查 pLmt	設為1要檢查.設為0不檢查
	// direct;	 檢查時, 先往那個方向. 設為1先往 nLmt.設為0先往 pLmt
	// bDirToPositive : true is go pLmt(0x00) . false is go nLmt(motor->AxisNo)

	int value;
	value = 0x00;
	MC8141PMotCmove(pAxis->BoardID, pAxis->AxisNo, value);	
	
	int iStart = ::GetTickCount();
	while(1)
	{
		// Wait for motor really stop
		GetMotorStatus(pAxis);

		if( pAxis->pLMT )
			break;	//	找到正極限OK

		else if(!pAxis->DRV)
			MC8141PMotCmove(pAxis->BoardID, pAxis->AxisNo, value);
		
		if( f.IsPause())
		{
			MC8141PMotStop(pAxis->BoardID, pAxis->AxisNo, pAxis->AxisNo );
			return false; 
		}

		if(!m.Info.bRunning)
		{
			MC8141PMotStop(pAxis->BoardID, pAxis->AxisNo, pAxis->AxisNo );
			return false;
		}
		
		if( pAxis->Alarm || pAxis->EMG)
		{
			MC8141PMotStop(pAxis->BoardID, pAxis->AxisNo, pAxis->AxisNo );
			return false;
		}
		if(::GetTickCount() - iStart  > (unsigned long)(timeout) )
		{
			MC8141PMotStop(pAxis->BoardID, pAxis->AxisNo, pAxis->AxisNo );
			return false;
		}
		
		Sleep(_Wait);
	}

	MC8141PMotStop(pAxis->BoardID, pAxis->AxisNo, pAxis->AxisNo );	
	
	return true;
}
bool CMotor::SearchMotorMovetonLimt(tagMotorParam *pAxis, long timeout )
{
#ifdef _Demo
	return true;
#endif

	// nLmt		 檢查 nLmt	設為1要檢查.設為0不檢查
	// pLmt		 檢查 pLmt	設為1要檢查.設為0不檢查
	// direct;	 檢查時, 先往那個方向. 設為1先往 nLmt.設為0先往 pLmt
	// bDirToPositive : true is go pLmt(0x00) . false is go nLmt(motor->AxisNo)

	int value = 0;
	value = pAxis->AxisNo;
	MC8141PMotCmove(pAxis->BoardID, pAxis->AxisNo, value);	
	
	int iStart = ::GetTickCount();
	while(1)
	{
		// Wait for motor really stop
		GetMotorStatus(pAxis);

		if( pAxis->nLMT )
			break;	// 找到負極限 OK

		else if(!pAxis->DRV)
			MC8141PMotCmove(pAxis->BoardID, pAxis->AxisNo, value);
		
		if( f.IsPause())
		{
			MC8141PMotStop(pAxis->BoardID, pAxis->AxisNo, pAxis->AxisNo );
			return false; 
		}
		if(!m.Info.bRunning)
		{
			MC8141PMotStop(pAxis->BoardID, pAxis->AxisNo, pAxis->AxisNo );
			return false;
		}
		
		if(pAxis->Alarm || pAxis->EMG)
		{
			MC8141PMotStop(pAxis->BoardID, pAxis->AxisNo, pAxis->AxisNo );
			return false;
		}
		if(::GetTickCount() - iStart > (unsigned long)(timeout) )
		{
			MC8141PMotStop(pAxis->BoardID, pAxis->AxisNo, pAxis->AxisNo );
			return false;
		}
		
		Sleep(_Wait);
	}

	MC8141PMotStop(pAxis->BoardID, pAxis->AxisNo, pAxis->AxisNo );	

	return true;
}
///////////////////////////////////////////////////////////////////////
long CMotor::MotorLmtCounterClear()
{
	m.m_LmtCounter.iTSnLmtCounter	= 0;
	m.m_LmtCounter.iXpLmtCounter	= 0;
	m.m_LmtCounter.iYpLmtCounter	= 0;

	m.m_LmtCounter.iYnLmtCounter	= 0;
	m.m_LmtCounter.iTSpLmtCounter	= 0;
	m.m_LmtCounter.iXnLmtCounter	= 0;

	return enCodeRunOK;
}
long CMotor::MotorLmtCounter2(unsigned char BordID, unsigned char Axis )
{
//		Inserter	CardID = 0 U_Axis;
//		ArmX		CardID = 0 X_Axis;
//		ArmY		CardID = 0 Y_Axis;
//		ArmZ		CardID = 0 Z_Axis;

	if( BordID == 0 && Axis == U_Axis )
		m.m_LmtCounter.iTSpLmtCounter++;	// TS
	else if( BordID == 0 && Axis == X_Axis )
		m.m_LmtCounter.iXnLmtCounter++;		// Arm X
	else if( BordID == 0 && Axis == Y_Axis )
		m.m_LmtCounter.iYnLmtCounter++;		// Arm Y
	else if( BordID == 0 && Axis == Z_Axis )
		m.m_LmtCounter.iZpLmtCounter++;		// Arm Z
	else
		;	// Nerver be here

	return enCodeRunOK;
}
long CMotor::MotorLmtCounter(unsigned char BordID, unsigned char Axis )
{
//		Inserter	CardID = 0 U_Axis;
//		ArmX		CardID = 0 X_Axis;
//		ArmY		CardID = 0 Y_Axis;
//		ArmZ		CardID = 0 Z_Axis;
	
	if( BordID == 0 && Axis == U_Axis )
		m.m_LmtCounter.iTSnLmtCounter++;	// TS
	else if( BordID == 0 && Axis == X_Axis )
		m.m_LmtCounter.iXpLmtCounter++;		// Arm X
	else if( BordID == 0 && Axis == Y_Axis )
		m.m_LmtCounter.iYpLmtCounter++;		// Arm Y
	else if( BordID == 0 && Axis == Z_Axis )
		m.m_LmtCounter.iZnLmtCounter++;		// Arm Z
	else
		;	// Nerver be here

	return enCodeRunOK;
}
long CMotor::MotorMovetopPLimt(tagMotorParam &pAxis, long timeout )
{
#ifdef _Demo
	return enCodeRunOK;
#endif

	// nLmt		 檢查 nLmt	設為1要檢查.設為0不檢查
	// pLmt		 檢查 pLmt	設為1要檢查.設為0不檢查
	// direct;	 檢查時, 先往那個方向. 設為1先往 nLmt.設為0先往 pLmt
	// bDirToPositive : true is go pLmt(0x00) . false is go nLmt(motor->AxisNo)

	int value;
	value = 0x00;
	MC8141PMotCmove(pAxis.BoardID, pAxis.AxisNo, value);	
	
	int pLmtCount = 0;
	int iStart = ::GetTickCount();
	while(1)
	{
		// Wait for motor really stop
		GetMotorStatus(&pAxis);

		if( pAxis.pLMT )
		{
			MotorLmtCounter( pAxis.BoardID, pAxis.AxisNo );
			pLmtCount++;
		}
		else
			pLmtCount = 0;

		if( pAxis.nLMT )
		{
			MotorLmtCounter2( pAxis.BoardID, pAxis.AxisNo );
		}

		if( pLmtCount > 5 )
		{
			MC8141PMotStop(pAxis.BoardID, pAxis.AxisNo, pAxis.AxisNo );	
			break;
		}
		else if(!pAxis.DRV)
			MC8141PMotCmove(pAxis.BoardID, pAxis.AxisNo, value);
		
		if( f.IsPause())
		{
			MC8141PMotStop(pAxis.BoardID, pAxis.AxisNo, pAxis.AxisNo );
			return enCodeRunOK; 
		}
		if(!m.Info.bRunning)
		{
			MC8141PMotStop(pAxis.BoardID, pAxis.AxisNo, pAxis.AxisNo );
			return enCodeRunOK;
		}		
		if( pAxis.Alarm || pAxis.EMG)
		{
			MC8141PMotStop(pAxis.BoardID, pAxis.AxisNo, pAxis.AxisNo );
			return enCodeMotorBaseDriverAlarm + GetMotorID(&pAxis);
		}
		if(::GetTickCount() - iStart  > (unsigned long)(timeout) )
		{
			MC8141PMotStop(pAxis.BoardID, pAxis.AxisNo, pAxis.AxisNo );
			return enCodeMotorBaseTimeout + GetMotorID(&pAxis);
		}
		
		// 1.0At
		/*
		Sleep(_Wait);
		*/
		Sleep(0);
	}	
	return enCodeRunOK;
}
///////////////////////////////////////////////////////////////////////
long CMotor::MotorMovetopLimt(tagMotorParam *pAxis, long timeout )
{
#ifdef _Demo
	return enCodeRunOK;
#endif

	// nLmt		 檢查 nLmt	設為1要檢查.設為0不檢查
	// pLmt		 檢查 pLmt	設為1要檢查.設為0不檢查
	// direct;	 檢查時, 先往那個方向. 設為1先往 nLmt.設為0先往 pLmt
	// bDirToPositive : true is go pLmt(0x00) . false is go nLmt(motor->AxisNo)

	int value;
	value = 0x00;
	MC8141PMotCmove(pAxis->BoardID, pAxis->AxisNo, value);	
	
	int iStart = ::GetTickCount();
	while(1)
	{
		// Wait for motor really stop
		GetMotorStatus(pAxis);

		if( pAxis->pLMT )
		{
			MC8141PMotStop(pAxis->BoardID, pAxis->AxisNo, pAxis->AxisNo );	
			break;
		}
		else if(!pAxis->DRV)
			MC8141PMotCmove(pAxis->BoardID, pAxis->AxisNo, value);
		
		if( f.IsPause())
		{
			MC8141PMotStop(pAxis->BoardID, pAxis->AxisNo, pAxis->AxisNo );
			return enCodeRunOK; 
		}
		if(!m.Info.bRunning)
		{
			MC8141PMotStop(pAxis->BoardID, pAxis->AxisNo, pAxis->AxisNo );
			return enCodeRunOK;
		}		
		if( pAxis->Alarm || pAxis->EMG)
		{
			MC8141PMotStop(pAxis->BoardID, pAxis->AxisNo, pAxis->AxisNo );
			return enCodeMotorBaseDriverAlarm + GetMotorID(pAxis);
		}
		if(::GetTickCount() - iStart  > (unsigned long)(timeout) )
		{
			MC8141PMotStop(pAxis->BoardID, pAxis->AxisNo, pAxis->AxisNo );
			return enCodeMotorBaseTimeout + GetMotorID(pAxis);
		}
		
		Sleep(_Wait);
	}	
	return enCodeRunOK;
}
////////////////////////////////////////////////////////////////////////
long CMotor::MotorMovetonNLimt(tagMotorParam &pAxis, long timeout )
{
#ifdef _Demo
	return enCodeRunOK;
#endif
	// nLmt		 檢查 nLmt	設為1要檢查.設為0不檢查
	// pLmt		 檢查 pLmt	設為1要檢查.設為0不檢查
	// direct;	 檢查時, 先往那個方向. 設為1先往 nLmt.設為0先往 pLmt
	// bDirToPositive : true is go pLmt(0x00) . false is go nLmt(motor->AxisNo)

	int value;
	value = pAxis.AxisNo;
	MC8141PMotCmove(pAxis.BoardID, pAxis.AxisNo, value);	
	
	int nLmtCount = 0;
	int iStart = ::GetTickCount();
	while(1)
	{
		// Wait for motor really stop
		GetMotorStatus(&pAxis);

		if( pAxis.nLMT )	
		{
			MotorLmtCounter( pAxis.BoardID, pAxis.AxisNo );
			nLmtCount++;
		}
		else
			nLmtCount = 0;

		if( pAxis.pLMT )
		{
			MotorLmtCounter2( pAxis.BoardID, pAxis.AxisNo );
		}

		if( nLmtCount > 5 )
		{
			MC8141PMotStop(pAxis.BoardID, pAxis.AxisNo, pAxis.AxisNo );
			break;
		}
		else if(!pAxis.DRV)
			MC8141PMotCmove(pAxis.BoardID, pAxis.AxisNo, value);
		
		if( f.IsPause())
		{
			MC8141PMotStop(pAxis.BoardID, pAxis.AxisNo, pAxis.AxisNo  );
			return enCodeRunOK; 
		}
		if(!m.Info.bRunning)
		{
			MC8141PMotStop(pAxis.BoardID, pAxis.AxisNo, pAxis.AxisNo );
			return enCodeRunOK;
		}
		
		if(pAxis.Alarm || pAxis.EMG)
		{
			MC8141PMotStop(pAxis.BoardID, pAxis.AxisNo, pAxis.AxisNo );
			return enCodeMotorBaseDriverAlarm + GetMotorID(&pAxis);
		}
		if(::GetTickCount() - iStart > (unsigned long)(timeout) )
		{
			MC8141PMotStop(pAxis.BoardID, pAxis.AxisNo, pAxis.AxisNo );
			return enCodeMotorBaseTimeout + GetMotorID(&pAxis);
		}
			
		// 1.0At
		/*
		Sleep(_Wait);
		*/
		Sleep(0);
	}

	return enCodeRunOK;
}
////////////////////////////////////////////////////////////////////////
long CMotor::MotorMovetonLimt(tagMotorParam *pAxis, long timeout )
{
#ifdef _Demo
	return enCodeRunOK;
#endif
	// nLmt		 檢查 nLmt	設為1要檢查.設為0不檢查
	// pLmt		 檢查 pLmt	設為1要檢查.設為0不檢查
	// direct;	 檢查時, 先往那個方向. 設為1先往 nLmt.設為0先往 pLmt
	// bDirToPositive : true is go pLmt(0x00) . false is go nLmt(motor->AxisNo)

	int value = 0;
	value = pAxis->AxisNo;
	MC8141PMotCmove(pAxis->BoardID, pAxis->AxisNo, value);	
	
	int iStart = ::GetTickCount();
	while(1)
	{
		// Wait for motor really stop
		GetMotorStatus(pAxis);

		if( pAxis->nLMT )
		{
			MC8141PMotStop(pAxis->BoardID, pAxis->AxisNo, pAxis->AxisNo );
			break;
		}
		else if(!pAxis->DRV)
			MC8141PMotCmove(pAxis->BoardID, pAxis->AxisNo, value);
		
		if( f.IsPause())
		{
			MC8141PMotStop(pAxis->BoardID, pAxis->AxisNo, pAxis->AxisNo  );
			return enCodeRunOK; 
		}
		if(!m.Info.bRunning)
		{
			MC8141PMotStop(pAxis->BoardID, pAxis->AxisNo, pAxis->AxisNo );
			return enCodeRunOK;
		}
		
		if(pAxis->Alarm || pAxis->EMG)
		{
			MC8141PMotStop(pAxis->BoardID, pAxis->AxisNo, pAxis->AxisNo );
			return enCodeMotorBaseDriverAlarm + GetMotorID(pAxis);
		}
		if(::GetTickCount() - iStart > (unsigned long)(timeout) )
		{
			MC8141PMotStop(pAxis->BoardID, pAxis->AxisNo, pAxis->AxisNo );
			return enCodeMotorBaseTimeout + GetMotorID(pAxis);
		}
				
		Sleep(_Wait);
	}

	return enCodeRunOK;
}
long CMotor::MotorRunSoftTLC(tagMotorParam *pAxis, double dPos, bool PreMove , long dTimeout, int SoftSpeed )
{
#ifdef _Demo
	return enCodeRunOK;
#endif	

	unsigned long iStart = ::GetTickCount();
	
	GetMotorStatus(pAxis);
	while(1)
	{
		GetMotorStatus(pAxis);			
		if(!pAxis->DRV) break;
		
		if(f.IsPause())
			return enCodeRunOK; // thread will handle this error
		if(!m.Info.bRunning)
			return enCodeRunOK;
		else if((::GetTickCount() - iStart) > (unsigned long)(dTimeout))
			return enCodeMotorBaseTimeout + GetMotorID(pAxis);
		else if(pAxis->Alarm || pAxis->EMG)
			return enCodeMotorBaseDriverAlarm + GetMotorID(pAxis);
		else if(pAxis->ERRR)
			return enCodeMotorBaseOverheat + GetMotorID(pAxis);
				
		Sleep(_Wait);
	}
	int mul = (int)(pAxis->Multiple * SoftSpeed / 100.);
//	MC8141PSetRange(pAxis->BoardID, 0, 8000000);
	// SetSpeed
	MC8141PMotAxisParaSet(pAxis->BoardID, pAxis->AxisNo,
		0xf,
		pAxis->Start * mul,
		pAxis->MaxSpeed * mul,
		pAxis->MaxSpeed * mul,
		pAxis->Accelerate * _pSpeed * mul,
		62500000 / pAxis->Jerk * mul);
	
	GetMotorStatus(pAxis);
	long pulse = (long)dPos - pAxis->LCount;
	switch(pAxis->AxisNo)
	{
	case X_Axis:
		MC8141PMotPtp(pAxis->BoardID, X_Axis, 0, pulse, 0, 0, 0);
		break;
	case Y_Axis:
		MC8141PMotPtp(pAxis->BoardID, Y_Axis, 0, 0, pulse, 0, 0);
		break;
	case Z_Axis:
		MC8141PMotPtp(pAxis->BoardID, Z_Axis, 0, 0, 0, pulse, 0);
		break;
	case U_Axis:
		MC8141PMotPtp(pAxis->BoardID, U_Axis, 0, 0, 0, 0, pulse);
		break;
	}

	iStart = ::GetTickCount();
	// Wait for ready
	while(1)
	{
		GetMotorStatus(pAxis);
		
		if( PreMove )
		{
			if(!pAxis->DRV) 
				break;
		}
		else
		{
			if(pAxis->InPosReal || (pAxis->TLC && pAxis->ZeroSpeed) )
				break;
		}

		if(!m.Info.bRunning)
		{
			MC8141PMotStop(pAxis->BoardID, pAxis->AxisNo, pAxis->AxisNo);
			return enCodeRunOK;
		}
		if((::GetTickCount() - iStart) > (unsigned long)dTimeout )
		{
			MC8141PMotStop(pAxis->BoardID, pAxis->AxisNo, pAxis->AxisNo);
			return enCodeMotorBaseTimeout + GetMotorID(pAxis);
		}
		if(pAxis->Alarm || pAxis->EMG)
		{
			MC8141PMotStop(pAxis->BoardID, pAxis->AxisNo, pAxis->AxisNo);
			return enCodeMotorBaseDriverAlarm + GetMotorID(pAxis);
		}
		if(pAxis->nLMT || pAxis->pLMT)
		{
			MC8141PMotStop(pAxis->BoardID, pAxis->AxisNo, pAxis->AxisNo);
			return enCodeMotorBaseOverheat + GetMotorID(pAxis);
		}
		if(f.IsPause())
		{
			MC8141PMotStop(pAxis->BoardID, pAxis->AxisNo, pAxis->AxisNo);
			return enCodeRunOK;
		}

		////////////////////////////////////////////////////////////////////
		// TLC Mode
		// 如果馬達的 TLC 達到和速度都為 0 就要停止, 然後通知測試機測試
//		if( pAxis->TLC && pAxis->ZeroSpeed )
//		{
//			MC8141PMotStop(pAxis->BoardID, pAxis->AxisNo, pAxis->AxisNo);
//			return enCodeRunOK;
//		}
		////////////////////////////////////////////////////////////////////

		f.ThreadWait();
	}
	return enCodeRunOK;
}
long CMotor::MotorRunTSRemainIC(tagMotorParam *pAxis, double dPos, bool PreMove, long dTimeout, long lSpeed )
{
#ifdef _Demo
	return enCodeRunOK;
#endif	

	unsigned long iStart = ::GetTickCount();
	
	GetMotorStatus(pAxis);
	while(1)
	{
		GetMotorStatus(pAxis);			
		if(!pAxis->DRV) break;
		
		if(f.IsPause())
			return enCodeRunOK; // thread will handle this error
		if(!m.Info.bRunning)
			return enCodeRunOK;
		else if((::GetTickCount() - iStart) > (unsigned long)(dTimeout))
			return enCodeMotorBaseTimeout + GetMotorID(pAxis);
		else if( pAxis->Alarm || pAxis->EMG )
			return enCodeMotorBaseDriverAlarm + GetMotorID(pAxis);
		else if( pAxis->ERRR)
			return enCodeMotorBaseOverheat + GetMotorID(pAxis);
				
		Sleep(_Wait);
	}
	int mul = (int)(pAxis->Multiple * lSpeed / 100.);
//	MC8141PSetRange(pAxis->BoardID, 0, 8000000);
	// SetSpeed
	LRESULT Res = MC8141PMotAxisParaSet(pAxis->BoardID, pAxis->AxisNo,
		0xf,
		pAxis->Start * mul,
		pAxis->MaxSpeed * mul,
		pAxis->MaxSpeed * mul,
		pAxis->Accelerate * _pSpeed * mul,
		62500000 / pAxis->Jerk * mul);

	// 
	if( !f.Motor.IsMotorErrorCodeCheck( Res ) )
	{
		f.SingleMotorLog( f.Motor.IsMotorErrorCodeLog( Res )  );
	}
	
	GetMotorStatus(pAxis);
	long pulse = (long)dPos - pAxis->LCount;
	switch(pAxis->AxisNo)
	{
	case X_Axis:
		MC8141PMotPtp(pAxis->BoardID, X_Axis, 0, pulse, 0, 0, 0);
		break;
	case Y_Axis:
		MC8141PMotPtp(pAxis->BoardID, Y_Axis, 0, 0, pulse, 0, 0);
		break;
	case Z_Axis:
		MC8141PMotPtp(pAxis->BoardID, Z_Axis, 0, 0, 0, pulse, 0);
		break;
	case U_Axis:
		MC8141PMotPtp(pAxis->BoardID, U_Axis, 0, 0, 0, 0, pulse);
		break;
	}

	iStart = ::GetTickCount();
	// Wait for ready
	while(1)
	{
		GetMotorStatus(pAxis);
		
		if( PreMove )
		{
			if(!pAxis->DRV) 
				break;
		}
		else
		{
			if(pAxis->InPosReal) 
				break;
		}

		if(!m.Info.bRunning)
		{
			MC8141PMotStop(pAxis->BoardID, pAxis->AxisNo, pAxis->AxisNo);
			return enCodeRunOK;
		}
		else if((::GetTickCount() - iStart) > (unsigned long)dTimeout )
		{
			MC8141PMotStop(pAxis->BoardID, pAxis->AxisNo, pAxis->AxisNo);
			return enCodeMotorBaseTimeout + GetMotorID(pAxis);
		}
		else if(pAxis->Alarm || pAxis->EMG)
		{
			MC8141PMotStop(pAxis->BoardID, pAxis->AxisNo, pAxis->AxisNo);
			return enCodeMotorBaseDriverAlarm + GetMotorID(pAxis);
		}
		else if(pAxis->nLMT || pAxis->pLMT)
		{
			MC8141PMotStop(pAxis->BoardID, pAxis->AxisNo, pAxis->AxisNo);
			return enCodeMotorBaseOverheat + GetMotorID(pAxis);
		}
		else if(f.IsPause())
		{
			MC8141PMotStop(pAxis->BoardID, pAxis->AxisNo, pAxis->AxisNo);
			return enCodeRunOK;
		}

		f.ThreadWait();
	}

	return enCodeRunOK;
}
// 
long CMotor::MotorRunTSCheckICDrop(tagMotorParam *pAxis, double dPos, bool PreMove, long dTimeout, long lSpeed )
{
#ifdef _Demo
	return enCodeRunOK;
#endif	

	unsigned long iStart = ::GetTickCount();
	
	GetMotorStatus(pAxis);
	while(1)
	{
		GetMotorStatus(pAxis);			
		if(!pAxis->DRV) break;
		
		if(f.IsPause())
			return enCodeRunOK; // thread will handle this error
		if(!m.Info.bRunning)
			return enCodeRunOK;
		else if((::GetTickCount() - iStart) > (unsigned long)(dTimeout))
			return enCodeMotorBaseTimeout + GetMotorID(pAxis);
		else if( pAxis->Alarm || pAxis->EMG )
			return enCodeMotorBaseDriverAlarm + GetMotorID(pAxis);
		else if( pAxis->ERRR)
			return enCodeMotorBaseOverheat + GetMotorID(pAxis);
				
		Sleep(_Wait);
	}
	int mul = (int)(pAxis->Multiple * lSpeed / 100.);
//	MC8141PSetRange(pAxis->BoardID, 0, 8000000);
	// SetSpeed
	LRESULT Res = MC8141PMotAxisParaSet(pAxis->BoardID, pAxis->AxisNo,
		0xf,
		pAxis->Start * mul,
		pAxis->MaxSpeed * mul,
		pAxis->MaxSpeed * mul,
		pAxis->Accelerate * _pSpeed * mul,
		62500000 / pAxis->Jerk * mul);

	// 
	if( !f.Motor.IsMotorErrorCodeCheck( Res ) )
	{
		f.SingleMotorLog( f.Motor.IsMotorErrorCodeLog( Res )  );
	}
	
	GetMotorStatus(pAxis);
	long pulse = (long)dPos - pAxis->LCount;
	switch(pAxis->AxisNo)
	{
	case X_Axis:
		MC8141PMotPtp(pAxis->BoardID, X_Axis, 0, pulse, 0, 0, 0);
		break;
	case Y_Axis:
		MC8141PMotPtp(pAxis->BoardID, Y_Axis, 0, 0, pulse, 0, 0);
		break;
	case Z_Axis:
		MC8141PMotPtp(pAxis->BoardID, Z_Axis, 0, 0, 0, pulse, 0);
		break;
	case U_Axis:
		MC8141PMotPtp(pAxis->BoardID, U_Axis, 0, 0, 0, 0, pulse);
		break;
	}

	int iVaccSensor = 0;

	iStart = ::GetTickCount();
	// Wait for ready
	while(1)
	{
		GetMotorStatus(pAxis);
		
		if( PreMove )
		{
			if(!pAxis->DRV) 
				break;
		}
		else
		{
			if(pAxis->InPosReal) 
				break;
		}

		if(!m.Info.bRunning)
		{
			MC8141PMotStop(pAxis->BoardID, pAxis->AxisNo, pAxis->AxisNo);
			return enCodeRunOK;
		}
		else if((::GetTickCount() - iStart) > (unsigned long)dTimeout )
		{
			MC8141PMotStop(pAxis->BoardID, pAxis->AxisNo, pAxis->AxisNo);
			return enCodeMotorBaseTimeout + GetMotorID(pAxis);
		}
		else if(pAxis->Alarm || pAxis->EMG)
		{
			MC8141PMotStop(pAxis->BoardID, pAxis->AxisNo, pAxis->AxisNo);
			return enCodeMotorBaseDriverAlarm + GetMotorID(pAxis);
		}
		else if(pAxis->nLMT || pAxis->pLMT)
		{
			MC8141PMotStop(pAxis->BoardID, pAxis->AxisNo, pAxis->AxisNo);
			return enCodeMotorBaseOverheat + GetMotorID(pAxis);
		}
		else if(f.IsPause())
		{
			MC8141PMotStop(pAxis->BoardID, pAxis->AxisNo, pAxis->AxisNo);
			return enCodeRunOK;
		}
		else if(1)
		{
			if( m.OutStatus.TestSiteVacc && m.InStatus.TestSiteZVaccSensor == _TSVacOff )
				iVaccSensor++;
			else
				iVaccSensor = 0;

			//
			if( iVaccSensor > 35 )
			{
				iVaccSensor = 0;
				MC8141PMotStop(pAxis->BoardID, pAxis->AxisNo, pAxis->AxisNo);
				return enCodeTestSiteMoveICMissing;
			}
		}

		f.ThreadWait();
	}

	return enCodeRunOK;
}
//
long CMotor::MotorRunTLCCheckICDrop(tagMotorParam *pAxis, double dPos, bool PreMove , long dTimeout )
{
#ifdef _Demo
	return enCodeRunOK;
#endif	

	unsigned long iStart = ::GetTickCount();
	
	GetMotorStatus(pAxis);
	while(1)
	{
		GetMotorStatus(pAxis);			
		if(!pAxis->DRV) break;
		
		if(f.IsPause())
			return enCodeRunOK; // thread will handle this error
		if(!m.Info.bRunning)
			return enCodeRunOK;
		else if((::GetTickCount() - iStart) > (unsigned long)(dTimeout))
			return enCodeMotorBaseTimeout + GetMotorID(pAxis);
		else if(pAxis->Alarm || pAxis->EMG)
			return enCodeMotorBaseDriverAlarm + GetMotorID(pAxis);
		else if(pAxis->ERRR)
			return enCodeMotorBaseOverheat + GetMotorID(pAxis);
				
		Sleep(_Wait);
	}
	int mul = (int)(pAxis->Multiple * pAxis->Speed / 100.);
//	MC8141PSetRange(pAxis->BoardID, 0, 8000000);
	// SetSpeed
	MC8141PMotAxisParaSet(pAxis->BoardID, pAxis->AxisNo,
		0xf,
		pAxis->Start * mul,
		pAxis->MaxSpeed * mul,
		pAxis->MaxSpeed * mul,
		pAxis->Accelerate * _pSpeed * mul,
		62500000 / pAxis->Jerk * mul);
	
	GetMotorStatus(pAxis);
	long pulse = (long)dPos - pAxis->LCount;
	switch(pAxis->AxisNo)
	{
	case X_Axis:
		MC8141PMotPtp(pAxis->BoardID, X_Axis, 0, pulse, 0, 0, 0);
		break;
	case Y_Axis:
		MC8141PMotPtp(pAxis->BoardID, Y_Axis, 0, 0, pulse, 0, 0);
		break;
	case Z_Axis:
		MC8141PMotPtp(pAxis->BoardID, Z_Axis, 0, 0, 0, pulse, 0);
		break;
	case U_Axis:
		MC8141PMotPtp(pAxis->BoardID, U_Axis, 0, 0, 0, 0, pulse);
		break;
	}

	int iVaccSensor = 0;

	iStart = ::GetTickCount();
	// Wait for ready
	while(1)
	{
		GetMotorStatus(pAxis);
		
		if(PreMove)
		{
			if(!pAxis->DRV) 
				break;
		}
		else
		{
			if(pAxis->InPosReal || (pAxis->TLC && pAxis->ZeroSpeed && !pAxis->DRV) )
				break;
		}

		if(!m.Info.bRunning)
		{
			MC8141PMotStop(pAxis->BoardID, pAxis->AxisNo, pAxis->AxisNo);
			return enCodeRunOK;
		}
		if((::GetTickCount() - iStart) > (unsigned long)dTimeout )
		{
			MC8141PMotStop(pAxis->BoardID, pAxis->AxisNo, pAxis->AxisNo);
			return enCodeMotorBaseTimeout + GetMotorID(pAxis);
		}
		if(pAxis->Alarm || pAxis->EMG)
		{
			MC8141PMotStop(pAxis->BoardID, pAxis->AxisNo, pAxis->AxisNo);
			return enCodeMotorBaseDriverAlarm + GetMotorID(pAxis);
		}
		if(pAxis->nLMT || pAxis->pLMT)
		{
			MC8141PMotStop(pAxis->BoardID, pAxis->AxisNo, pAxis->AxisNo);
			return enCodeMotorBaseOverheat + GetMotorID(pAxis);
		}
		if(f.IsPause())
		{
			MC8141PMotStop(pAxis->BoardID, pAxis->AxisNo, pAxis->AxisNo);
			return enCodeRunOK;
		}
		else if(1)
		{
			if( m.OutStatus.TestSiteVacc && m.InStatus.TestSiteZVaccSensor == _TSVacOff )
				iVaccSensor++;
			else
				iVaccSensor = 0;

			//
			if( iVaccSensor > 35 )
			{
				iVaccSensor = 0;
				MC8141PMotStop(pAxis->BoardID, pAxis->AxisNo, pAxis->AxisNo);
				return enCodeTestSiteMoveICMissing;
			}
		}

		f.ThreadWait();
	}
	return enCodeRunOK;
}
//
long CMotor::MotorRunTLC(tagMotorParam *pAxis, double dPos, bool PreMove , long dTimeout )
{
#ifdef _Demo
	return enCodeRunOK;
#endif	

	unsigned long iStart = ::GetTickCount();
	
	GetMotorStatus(pAxis);
	while(1)
	{
		GetMotorStatus(pAxis);			
		if(!pAxis->DRV) break;
		
		if(f.IsPause())
			return enCodeRunOK; // thread will handle this error
		if(!m.Info.bRunning)
			return enCodeRunOK;
		else if((::GetTickCount() - iStart) > (unsigned long)(dTimeout))
			return enCodeMotorBaseTimeout + GetMotorID(pAxis);
		else if(pAxis->Alarm || pAxis->EMG)
			return enCodeMotorBaseDriverAlarm + GetMotorID(pAxis);
		else if(pAxis->ERRR)
			return enCodeMotorBaseOverheat + GetMotorID(pAxis);
				
		Sleep(_Wait);
	}
	int mul = (int)(pAxis->Multiple * pAxis->Speed / 100.);
//	MC8141PSetRange(pAxis->BoardID, 0, 8000000);
	// SetSpeed
	MC8141PMotAxisParaSet(pAxis->BoardID, pAxis->AxisNo,
		0xf,
		pAxis->Start * mul,
		pAxis->MaxSpeed * mul,
		pAxis->MaxSpeed * mul,
		pAxis->Accelerate * _pSpeed * mul,
		62500000 / pAxis->Jerk * mul);
	
	GetMotorStatus(pAxis);
	long pulse = (long)dPos - pAxis->LCount;
	switch(pAxis->AxisNo)
	{
	case X_Axis:
		MC8141PMotPtp(pAxis->BoardID, X_Axis, 0, pulse, 0, 0, 0);
		break;
	case Y_Axis:
		MC8141PMotPtp(pAxis->BoardID, Y_Axis, 0, 0, pulse, 0, 0);
		break;
	case Z_Axis:
		MC8141PMotPtp(pAxis->BoardID, Z_Axis, 0, 0, 0, pulse, 0);
		break;
	case U_Axis:
		MC8141PMotPtp(pAxis->BoardID, U_Axis, 0, 0, 0, 0, pulse);
		break;
	}

	iStart = ::GetTickCount();
	// Wait for ready
	while(1)
	{
		GetMotorStatus(pAxis);
		
		if(PreMove)
		{
			if(!pAxis->DRV) 
				break;
		}
		else
		{
			if(pAxis->InPosReal || (pAxis->TLC && pAxis->ZeroSpeed && !pAxis->DRV) )
				break;
		}

		if(!m.Info.bRunning)
		{
			MC8141PMotStop(pAxis->BoardID, pAxis->AxisNo, pAxis->AxisNo);
			return enCodeRunOK;
		}
		if((::GetTickCount() - iStart) > (unsigned long)dTimeout )
		{
			MC8141PMotStop(pAxis->BoardID, pAxis->AxisNo, pAxis->AxisNo);
			return enCodeMotorBaseTimeout + GetMotorID(pAxis);
		}
		if(pAxis->Alarm || pAxis->EMG)
		{
			MC8141PMotStop(pAxis->BoardID, pAxis->AxisNo, pAxis->AxisNo);
			return enCodeMotorBaseDriverAlarm + GetMotorID(pAxis);
		}
		if(pAxis->nLMT || pAxis->pLMT)
		{
			MC8141PMotStop(pAxis->BoardID, pAxis->AxisNo, pAxis->AxisNo);
			return enCodeMotorBaseOverheat + GetMotorID(pAxis);
		}
		if(f.IsPause())
		{
			MC8141PMotStop(pAxis->BoardID, pAxis->AxisNo, pAxis->AxisNo);
			return enCodeRunOK;
		}

		f.ThreadWait();
	}
	return enCodeRunOK;
}
// Check Error / Alarm
bool CMotor::IsMotorError( tagMotorParam *pAxis )
{
#ifdef _Demo
	return true;	// 表示沒有 Error
#endif	
	
	GetMotorStatus( pAxis );

	if( pAxis->ERRR && !pAxis->nLMT && !pAxis->pLMT)
		return false;
	else
		return true;
	// 如果是碰到正負極限就不要清 Error

}
bool CMotor::IsMotorAlarm( tagMotorParam *pAxis )
{
#ifdef _Demo
	return true;	// 表示沒有 Alarm
#endif	

	GetMotorStatus( pAxis );

	if( pAxis->Alarm )
		return false;
	else
		return true;
}
long CMotor::ManualMotorRunSoftTLC(tagMotorParam *pAxis, 
								   double dPos, bool PreMove , long dTimeout, int SoftSpeed )
{
#ifdef _Demo
	return enCodeRunOK;
#endif	

	unsigned long iStart = ::GetTickCount();
	
	GetMotorStatus(pAxis);
	while(1)
	{
		GetMotorStatus(pAxis);			
		if(!pAxis->DRV) break;
		
		if(!m.Info.bRunning)
			return enCodeRunOK;
		else if((::GetTickCount() - iStart) > (unsigned long)(dTimeout))
			return enCodeMotorBaseTimeout + GetMotorID(pAxis);
		else if(pAxis->Alarm || pAxis->EMG)
			return enCodeMotorBaseDriverAlarm + GetMotorID(pAxis);
		else if(pAxis->ERRR)
			return enCodeMotorBaseOverheat + GetMotorID(pAxis);
				
		Sleep(_Wait);
	}
	int mul = (int)(pAxis->Multiple * SoftSpeed / 100.);
//	MC8141PSetRange(pAxis->BoardID, 0, 8000000);
	// SetSpeed
	MC8141PMotAxisParaSet(pAxis->BoardID, pAxis->AxisNo,
		0xf,
		pAxis->Start * mul,
		pAxis->MaxSpeed * mul,
		pAxis->MaxSpeed * mul,
		pAxis->Accelerate * _pSpeed * mul,
		62500000 / pAxis->Jerk * mul);
	
	GetMotorStatus(pAxis);
	long pulse = (long)dPos - pAxis->LCount;
	switch(pAxis->AxisNo)
	{
	case X_Axis:
		MC8141PMotPtp(pAxis->BoardID, X_Axis, 0, pulse, 0, 0, 0);
		break;
	case Y_Axis:
		MC8141PMotPtp(pAxis->BoardID, Y_Axis, 0, 0, pulse, 0, 0);
		break;
	case Z_Axis:
		MC8141PMotPtp(pAxis->BoardID, Z_Axis, 0, 0, 0, pulse, 0);
		break;
	case U_Axis:
		MC8141PMotPtp(pAxis->BoardID, U_Axis, 0, 0, 0, 0, pulse);
		break;
	}

	iStart = ::GetTickCount();
	// Wait for ready
	while(1)
	{
		GetMotorStatus(pAxis);
		
		if( PreMove )
		{
			if(!pAxis->DRV) 
				break;
		}
		else
		{
			if(pAxis->InPosReal || (pAxis->TLC && pAxis->ZeroSpeed && !pAxis->DRV) )
				break;
		}

		if(!m.Info.bRunning)
		{
			MC8141PMotStop(pAxis->BoardID, pAxis->AxisNo, pAxis->AxisNo);
			return enCodeRunOK;
		}
		if((::GetTickCount() - iStart) > (unsigned long)dTimeout )
		{
			MC8141PMotStop(pAxis->BoardID, pAxis->AxisNo, pAxis->AxisNo);
			return enCodeMotorBaseTimeout + GetMotorID(pAxis);
		}
		if(pAxis->Alarm || pAxis->EMG)
		{
			MC8141PMotStop(pAxis->BoardID, pAxis->AxisNo, pAxis->AxisNo);
			return enCodeMotorBaseDriverAlarm + GetMotorID(pAxis);
		}
		if(pAxis->nLMT || pAxis->pLMT)
		{
			MC8141PMotStop(pAxis->BoardID, pAxis->AxisNo, pAxis->AxisNo);
			return enCodeMotorBaseOverheat + GetMotorID(pAxis);
		}

		f.ThreadWait();
	}
	return enCodeRunOK;
}
long CMotor::ManualMotorHome(tagMotorParam *pAxis, long timeout )
{
#ifdef _Demo
	return enCodeRunOK;
#endif	
	unsigned long iStart = ::GetTickCount();

	GetMotorStatus(pAxis);
	while(1)
	{
		GetMotorStatus(pAxis);			
		if(!pAxis->DRV) 
			break;
		
		if(f.IsPause())
			return enCodeRunOK; // thread will handle this error
		if(!m.Info.bRunning)
			return enCodeRunOK;
		else if((::GetTickCount() - iStart) > (unsigned long)(timeout))
			return enCodeMotorBaseTimeout + GetMotorID(pAxis);
		else if(pAxis->Alarm || pAxis->EMG)
			return enCodeMotorBaseOverheat + GetMotorID(pAxis);
//		else if(pAxis->Alarm || pAxis->EMG || pAxis->ERRR)
//			return enCodeMotorBaseOverheat + GetMotorID(pAxis);
				
		Sleep(_Wait);
	}

	//Home function parameters
	MC8141PMotWrReg(pAxis->BoardID, pAxis->AxisNo, HomeType, 0x04);
//	MC8141PMotWrReg(pAxis->BoardID, pAxis->AxisNo, HomeP0_Dir, 0);   // Value: 0 for CW, 1 for CCW
	MC8141PMotWrReg(pAxis->BoardID, pAxis->AxisNo, HomeP0_Dir, 1);   // Value: 0 for CW, 1 for CCW
	MC8141PMotWrReg(pAxis->BoardID, pAxis->AxisNo, HomeP0_Speed, pAxis->MaxSpeed ); //speed
	MC8141PMotWrReg(pAxis->BoardID, pAxis->AxisNo, HomeOffset, 2500 );                
	MC8141PMotWrReg(pAxis->BoardID, pAxis->AxisNo, HomeOffset_Speed, pAxis->MaxSpeed );

	//Motor Go Home
	MC8141PMotHome(pAxis->BoardID, pAxis->AxisNo);

	GetMotorStatus(pAxis);
	iStart = ::GetTickCount();

	long Lr;
	DWORD value;
	while(1)
	{
		GetMotorStatus(pAxis);
		Lr = MC8141PMotHomeStatus(pAxis->BoardID, pAxis->AxisNo, &value);
	
		if(!m.Info.bRunning)
		{
			MC8141PMotStop(pAxis->BoardID, pAxis->AxisNo, pAxis->AxisNo);
			return enCodeRunOK;
		}

		if((::GetTickCount() - iStart) > (unsigned long)2000000 )
		{
			MC8141PMotStop(pAxis->BoardID, pAxis->AxisNo, pAxis->AxisNo);
			return enCodeMotorBaseTimeout + GetMotorID(pAxis);
		}
		if(pAxis->Alarm || pAxis->EMG)
		{
			MC8141PMotStop(pAxis->BoardID, pAxis->AxisNo, pAxis->AxisNo);
			return enCodeMotorBaseDriverAlarm + GetMotorID(pAxis);
		}

		// Motor Home
		if( value == ERROR_SUCCESS )
		{
			break;
		}
		else if( value == 0x15 )
		{
			Sleep(0);
			// Drv busy
			// AfxMessageBox("Drv Busy.!");
		}
		else if( value == 0x1a )
		{
			Sleep(0);
			// Home busy
			// AfxMessageBox("Home Busy.!");
		}

		f.ThreadWait();
	}
	return enCodeRunOK;
}


// Initial 專用功能
long CMotor::InitialMotorMoveOffLoadPoint(tagMotorParam *pAxis, unsigned char* pSensor, unsigned char* LpSensor, long dTimeout )
{
#ifdef _Demo
	return enCodeRunOK;
#endif	

	// m.InStatus.OutliftTrayAtUnloadPoint	/ pSensor
	// m.InStatus.OutliftTrayOnSgltrs		/ LpSensor

	MotorClearCount( pAxis );		// 先清零, 然後再往下
	Sleep( 100 );					// 等 100 ms 再開始動
	int cRCount = pAxis->RCount;	// 記得目前的位置, 讓往下跑的時候, 移動到固定距離就停止

	int iStart = ::GetTickCount();
	
	int value;
	value = 0x00;
	MC8141PMotCmove(pAxis->BoardID, pAxis->AxisNo, value);	

	while (1)
	{		
		GetMotorStatus(pAxis);
	
		if(!pAxis->DRV)
			MC8141PMotCmove(pAxis->BoardID, pAxis->AxisNo, pAxis->AxisNo);

		if ( f.IsPause() )
		{
			// Stop motor immediately when initializing.
			MC8141PMotStop( pAxis->BoardID, pAxis->AxisNo, pAxis->AxisNo );
			return enCodeRunOK;		// thread will handle this error
		}		
		if(!m.Info.bRunning)
		{
			MC8141PMotStop( pAxis->BoardID, pAxis->AxisNo, pAxis->AxisNo );
			return enCodeRunOK;
		}
		
		// 8141P need to check ERR flag also.
		if ( pAxis->pLMT && pAxis->ERRR)
		{			
			MC8141PMotStop( pAxis->BoardID, pAxis->AxisNo, pAxis->AxisNo );
			break;
		}
		if ( ::GetTickCount() - iStart > (unsigned long)dTimeout )
		{
			MC8141PMotStop( pAxis->BoardID, pAxis->AxisNo, pAxis->AxisNo );
			return enCodeRunOK;
		}

		////////////////////////////////////////////////////////////////
		// 離開 Sensor 後停止
		// Note: pSensor is Output Stack load point sensor
		// Note: LpSensor is Output Stack clamp sensor
		// Before Initial process. make sure tray already leave those two sensor range.
		if( *pSensor == 0 && *LpSensor == 0 )
		{
			// 離開 load point 就可以離開
			f.Wait(100);	// Wait for 1/10 sec, Make sure it really copmplete leave sensor range.
			MC8141PMotStop(pAxis->BoardID, pAxis->AxisNo, pAxis->AxisNo );
			return enCodeRunOK;
		}
		/////////////////////////////////////////////////////////////////

		Sleep(_Wait);
	}

	return enCodeRunOK;
}

void CMotor::TorqueChange(tagMotorParam *pAxis, bool enable)
{
	int iServoOnValue, iTL1Value;
	if(pAxis->ServoOn)
		iServoOnValue = 0x01;
	else 
		iServoOnValue = 0x00;

	if (enable)
		iTL1Value = 0x02;
	else 
		iTL1Value = 0x00;

	MC8141PMotDO(pAxis->BoardID, pAxis->AxisNo, (iServoOnValue | iTL1Value));

	pAxis->TL1 = enable;
}