# Microsoft Developer Studio Project File - Name="Deer" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=Deer - Win32 Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Deer.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Deer.mak" CFG="Deer - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Deer - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "Deer - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE "Deer - Win32 Demo" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Deer - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_AFXDLL" /FR /Yu"stdafx.h" /FD /Zm200 /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x404 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x404 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 MC8141P.lib version.lib ml.lib PCI-Dask.lib matrix_gpio.lib Shlwapi.lib Dll6.lib GdiPlus.lib /nologo /subsystem:windows /machine:I386 /out:"Release/3111.exe"

!ELSEIF  "$(CFG)" == "Deer - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_AFXDLL" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x404 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x404 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 MC8141P.lib version.lib ml.lib PCI-Dask.lib matrix_gpio.lib Shlwapi.lib Dll6.lib GdiPlus.lib /nologo /subsystem:windows /debug /machine:I386 /out:"\\192.168.1.10\3111\DeerD.exe" /pdbtype:sept

!ELSEIF  "$(CFG)" == "Deer - Win32 Demo"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Deer___Win32_Demo"
# PROP BASE Intermediate_Dir "Deer___Win32_Demo"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Demo"
# PROP Intermediate_Dir "Demo"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_Demo" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x404 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x404 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 MC8141P.lib version.lib ml.lib PCI-Dask.lib matrix_gpio.lib Shlwapi.lib Dll6.lib GdiPlus.lib /nologo /subsystem:windows /debug /machine:I386 /out:"Demo/3111Demo.exe" /pdbtype:sept
# SUBTRACT LINK32 /nodefaultlib

!ENDIF 

# Begin Target

# Name "Deer - Win32 Release"
# Name "Deer - Win32 Debug"
# Name "Deer - Win32 Demo"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\AlignRectTracker.cpp
# End Source File
# Begin Source File

SOURCE=.\base64.cpp
# End Source File
# Begin Source File

SOURCE=.\BtnST.cpp
# End Source File
# Begin Source File

SOURCE=.\C_ColorToolTip.cpp
# End Source File
# Begin Source File

SOURCE=.\CameraDS.cpp
# End Source File
# Begin Source File

SOURCE=.\ColorBtn.cpp
# End Source File
# Begin Source File

SOURCE=.\ColorFontStatic.cpp
# End Source File
# Begin Source File

SOURCE=.\ColorListCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\ColorPickerCB.cpp
# End Source File
# Begin Source File

SOURCE=.\ComboListCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\ContinueFailCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\CSmtp.cpp
# End Source File
# Begin Source File

SOURCE=.\CtrlVision.cpp
# End Source File
# Begin Source File

SOURCE=.\CtrlVisionAlignment.cpp
# End Source File
# Begin Source File

SOURCE=.\CtrlVisionMatch.cpp
# End Source File
# Begin Source File

SOURCE=.\Deer.cpp
# End Source File
# Begin Source File

SOURCE=.\Deer.rc
# End Source File
# Begin Source File

SOURCE=.\DeerDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgAlignment.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgAlignmentCheck.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgAlignmentPw.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgArmLogICImage.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgATCModuleCalibration.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgATCModuleFile.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgATCModuleModify.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgATCModuleNew.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgATCModuleSetting.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgATCMonitor.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgAutoRetry.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgAutoRetrySetting.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgBasicSetting.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgBinColor.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgBinMapping.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgBinModify.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgBinNew.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgBinStatus.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgButton.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgCameraSetting.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgCategory.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgClearCount.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgCommunication.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgCommunicationInfo.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgContactCounter.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgCustomMCFunction.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgCustomPageFunction.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgCylinderLifeTimeTool.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgDebugError.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgDebugErrorList.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgDebugFunction.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgDeviceSetup.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgError.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgEvent.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgExtendFunction.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgFilePath.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgGearRation.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgHandlerComPort.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgHandlerStatus.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgHandlerStatusList.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgHotKey.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgInOutputTrayMap.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgInputTrayMap.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgIOMontior.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgIOMontiorATCModule.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgIOMontiorHandler.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgIOMontiorPTCModule.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgIOMontiorRemote.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgJamRateReportTool.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgJamRateReportToolLastReport.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgLogEnable.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgLotInformation.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgLotInformationDone.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgLotInformationProgress.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgMail.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgManualContact.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgManualContactRecover.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgManualContactTorque.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgManualContactTorqueKgf.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgMotorMontior.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgMotorMove.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgMotorSimpleStatus.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgMotorStatus.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgOffset.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgOffsetTS.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgOutputTrayMap.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgOutputYield.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgPassword.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgPasswordNeed.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgPasswordRead.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgProgramStart.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgReLoadFile.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgRemoteCommMonitor.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgRemoteCommMsg.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgRemoteCommMsgLot.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgRemoteCommunication.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgRemoteControl.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgRemoteControlCustom.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgRemoteControlCustomInput.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgRemoteRecover.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgRepeatTray.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgRepeatTrayBinCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgRepeatTrayEnable.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgRepeatTrayInOutCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgRepeatTrayTemp.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgSetting.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgSettingGpib.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgSettingNote.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgSettingRs232.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgSettingTcp.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgSettingTTL.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgSiteSetting.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgSLTProtocol.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgSLTProtocolHelp.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgSLTProtocolMonitor.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgSLTProtocolSetting.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgSocketMatch.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgSocketVisionCam.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgSocketVisionCtrlLive.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgSocketVisionCtrlSetting.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgSpeed.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgSummaryReport.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgSummaryReportDetail.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgTemperature.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgTemperatureCalibration.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgTemperatureLookupTable.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgTemperatureTool.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgTestResult.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgTestSetting.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgTestTesting.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgThreadMontior.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgTimer.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgTimerSetting.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgTorqueControl.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgTorqueTool.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgTowerSetting.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgTrayDef.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgTrayFile.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgTrayFileChipTray.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgTrayFileNoHeater.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgTrayMap.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgTrayMapRepeat.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgTrayMapReport.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgTrayMapUI.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgTrayRepeatStatus.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgTrayStatus.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgTSRemainIC.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgUPHTool.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgVisionSetup.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgVisualButton.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgWestTool.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgYieldControl.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgYieldMonitor.cpp
# End Source File
# Begin Source File

SOURCE=.\DMsg.cpp
# End Source File
# Begin Source File

SOURCE=.\DriverMotorTorqueControl.cpp
# End Source File
# Begin Source File

SOURCE=.\DriverTestInterface.cpp
# End Source File
# Begin Source File

SOURCE=.\DriverTestInterfaceTCP.cpp
# End Source File
# Begin Source File

SOURCE=.\DriveWest.cpp
# End Source File
# Begin Source File

SOURCE=.\ErrView.cpp
# End Source File
# Begin Source File

SOURCE=.\EventLog.cpp
# End Source File
# Begin Source File

SOURCE=.\FileCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\Function.cpp
# End Source File
# Begin Source File

SOURCE=.\GridCtrl\GridCell.cpp
# End Source File
# Begin Source File

SOURCE=.\GridCtrl\GridCellBase.cpp
# End Source File
# Begin Source File

SOURCE=.\GridCtrl\GridCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\GridCtrl\GridDropTarget.cpp
# End Source File
# Begin Source File

SOURCE=.\GridCtrl\GroupControl.cpp
# End Source File
# Begin Source File

SOURCE=.\InPlaceComboTP.cpp
# End Source File
# Begin Source File

SOURCE=.\GridCtrl\InPlaceEdit.cpp
# End Source File
# Begin Source File

SOURCE=.\InPlaceEditTP.cpp
# End Source File
# Begin Source File

SOURCE=.\Interface.cpp
# End Source File
# Begin Source File

SOURCE=.\InterfaceTcp.cpp
# End Source File
# Begin Source File

SOURCE=.\Led.cpp
# End Source File
# Begin Source File

SOURCE=.\LogData.cpp
# End Source File
# Begin Source File

SOURCE=.\MailCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\Member.cpp
# End Source File
# Begin Source File

SOURCE=.\Motor.cpp
# End Source File
# Begin Source File

SOURCE=.\PageDebug.cpp
# End Source File
# Begin Source File

SOURCE=.\PageEngineer.cpp
# End Source File
# Begin Source File

SOURCE=.\PageInitial.cpp
# End Source File
# Begin Source File

SOURCE=.\PageRun.cpp
# End Source File
# Begin Source File

SOURCE=.\PageSetup.cpp
# End Source File
# Begin Source File

SOURCE=.\PageUser.cpp
# End Source File
# Begin Source File

SOURCE=.\Parser3111.cpp
# End Source File
# Begin Source File

SOURCE=.\PreheaterFile.cpp
# End Source File
# Begin Source File

SOURCE=.\RADatabase.cpp
# End Source File
# Begin Source File

SOURCE=.\RADatabaseLock.cpp
# End Source File
# Begin Source File

SOURCE=.\Report.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\ThArm.cpp
# End Source File
# Begin Source File

SOURCE=.\ThErrorCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\ThInitialArm.cpp
# End Source File
# Begin Source File

SOURCE=.\ThInserter.cpp
# End Source File
# Begin Source File

SOURCE=.\ThInspect.cpp
# End Source File
# Begin Source File

SOURCE=.\ThIOReadWrite.cpp
# End Source File
# Begin Source File

SOURCE=.\ThIOReadWriteRemoteIO.cpp
# End Source File
# Begin Source File

SOURCE=.\ThManualCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\ThTester.cpp
# End Source File
# Begin Source File

SOURCE=.\GridCtrl\TitleTip.cpp
# End Source File
# Begin Source File

SOURCE=.\TorqueCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\TrayFile.cpp
# End Source File
# Begin Source File

SOURCE=.\TrayMapCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\TrayMapSelCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\ViewIC.cpp
# End Source File
# Begin Source File

SOURCE=.\ViewImage.cpp
# End Source File
# Begin Source File

SOURCE=.\ViewRepeatTrayMotor.cpp
# End Source File
# Begin Source File

SOURCE=.\ViewSockImage.cpp
# End Source File
# Begin Source File

SOURCE=.\ViewSockTrackerImage.cpp
# End Source File
# Begin Source File

SOURCE=.\ViewTrayMap.cpp
# End Source File
# Begin Source File

SOURCE=.\ViewTrayMotor.cpp
# End Source File
# Begin Source File

SOURCE=.\YieldControl.cpp
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=".\res\3110 Layout.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\3110 PreHeater Fix Layout.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\3110 PreHeater Layout.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\3111 Layout.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\A BLAZE.ICO"
# End Source File
# Begin Source File

SOURCE=.\res\Alignment.ico
# End Source File
# Begin Source File

SOURCE=.\res\AlignmentCheck.ico
# End Source File
# Begin Source File

SOURCE=.\res\Arc.ico
# End Source File
# Begin Source File

SOURCE=.\res\ArmLogImageDisable.ico
# End Source File
# Begin Source File

SOURCE=.\res\ArmLogImageEnable.ico
# End Source File
# Begin Source File

SOURCE=.\res\arrow_dn.ico
# End Source File
# Begin Source File

SOURCE=.\res\arrow_up.ico
# End Source File
# Begin Source File

SOURCE=.\res\AutoRetry.ico
# End Source File
# Begin Source File

SOURCE=.\res\Base.ico
# End Source File
# Begin Source File

SOURCE=.\res\BasicSetting.ico
# End Source File
# Begin Source File

SOURCE=.\res\Camcorder.ico
# End Source File
# Begin Source File

SOURCE=.\res\CamcorderOcr.ico
# End Source File
# Begin Source File

SOURCE=.\res\CCDSocketSensor\Camera.ico
# End Source File
# Begin Source File

SOURCE=.\res\CCDSocketSensor\Camera_video.ico
# End Source File
# Begin Source File

SOURCE=.\res\Cancel.ico
# End Source File
# Begin Source File

SOURCE=.\res\Category.ico
# End Source File
# Begin Source File

SOURCE=.\res\CCDList.ico
# End Source File
# Begin Source File

SOURCE=.\res\CCDSocketSetting.ico
# End Source File
# Begin Source File

SOURCE=.\res\CCDSocketSetup.ico
# End Source File
# Begin Source File

SOURCE=.\res\CCDSocketSetupClose.ico
# End Source File
# Begin Source File

SOURCE=.\res\CConnect.ico
# End Source File
# Begin Source File

SOURCE=.\res\CDSTemperture.ico
# End Source File
# Begin Source File

SOURCE=.\res\ChamberCalibration.ico
# End Source File
# Begin Source File

SOURCE=.\res\ChamberOffset.ico
# End Source File
# Begin Source File

SOURCE=.\res\ChamberSetting.ico
# End Source File
# Begin Source File

SOURCE=.\res\ChamnerIO.ico
# End Source File
# Begin Source File

SOURCE=.\res\ChangFile.ico
# End Source File
# Begin Source File

SOURCE=.\res\CheckBook.ico
# End Source File
# Begin Source File

SOURCE=.\res\Chroma.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ClearCount.ico
# End Source File
# Begin Source File

SOURCE=.\res\Cmd.ico
# End Source File
# Begin Source File

SOURCE=.\res\CommicationSet.ico
# End Source File
# Begin Source File

SOURCE=.\res\Connect.ico
# End Source File
# Begin Source File

SOURCE=.\res\ContactCounter.ico
# End Source File
# Begin Source File

SOURCE=.\res\Continue.ico
# End Source File
# Begin Source File

SOURCE=.\res\Counter.ico
# End Source File
# Begin Source File

SOURCE=".\res\Cycle Finish.bmp"
# End Source File
# Begin Source File

SOURCE=.\res\dbserver.ico
# End Source File
# Begin Source File

SOURCE=.\res\Debug.ico
# End Source File
# Begin Source File

SOURCE=.\res\debug1.ico
# End Source File
# Begin Source File

SOURCE=.\res\Deer.ico
# End Source File
# Begin Source File

SOURCE=.\res\Deer.rc2
# End Source File
# Begin Source File

SOURCE=.\res\Delete.ico
# End Source File
# Begin Source File

SOURCE=.\res\DeleteOne.ico
# End Source File
# Begin Source File

SOURCE=.\res\DeviceSetup.ico
# End Source File
# Begin Source File

SOURCE=.\res\drop.ico
# End Source File
# Begin Source File

SOURCE=.\res\Engineer.ico
# End Source File
# Begin Source File

SOURCE=.\res\Error.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Error1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ErrorRateReport.ico
# End Source File
# Begin Source File

SOURCE=.\res\Event.bmp
# End Source File
# Begin Source File

SOURCE=.\res\EventLog.ico
# End Source File
# Begin Source File

SOURCE=.\res\Export.ico
# End Source File
# Begin Source File

SOURCE=.\res\File_mod.ico
# End Source File
# Begin Source File

SOURCE=.\res\FilePath.ico
# End Source File
# Begin Source File

SOURCE=.\res\FromSetting.ico
# End Source File
# Begin Source File

SOURCE=.\res\GBIP.ico
# End Source File
# Begin Source File

SOURCE=.\res\GBIPCtrl.ico
# End Source File
# Begin Source File

SOURCE=.\res\GearRation.ico
# End Source File
# Begin Source File

SOURCE=.\res\Hand.cur
# End Source File
# Begin Source File

SOURCE=.\res\ico00001.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00002.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon1.ico
# End Source File
# Begin Source File

SOURCE=".\res\Ink Jet.ico"
# End Source File
# Begin Source File

SOURCE=.\res\InterFace.ico
# End Source File
# Begin Source File

SOURCE=.\res\IOMontior.ico
# End Source File
# Begin Source File

SOURCE=.\res\IOMotorMontior.ico
# End Source File
# Begin Source File

SOURCE=.\res\Language.ico
# End Source File
# Begin Source File

SOURCE=.\res\LastTrayFile.ico
# End Source File
# Begin Source File

SOURCE=.\res\Layout.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Leds_32.bmp
# End Source File
# Begin Source File

SOURCE=.\res\LoadCell.ico
# End Source File
# Begin Source File

SOURCE=.\res\Location.ico
# End Source File
# Begin Source File

SOURCE=.\res\Logo.bmp
# End Source File
# Begin Source File

SOURCE=.\res\LookupTable.ico
# End Source File
# Begin Source File

SOURCE=.\res\LoopTest.ico
# End Source File
# Begin Source File

SOURCE=.\res\LoopTestMap.ico
# End Source File
# Begin Source File

SOURCE=.\res\MainFrame.ico
# End Source File
# Begin Source File

SOURCE=.\res\Manual.ico
# End Source File
# Begin Source File

SOURCE=.\res\ManualContact.ico
# End Source File
# Begin Source File

SOURCE=.\res\ModeDemo.ico
# End Source File
# Begin Source File

SOURCE=.\res\ModeOffline.ico
# End Source File
# Begin Source File

SOURCE=.\res\ModeOnLine.ico
# End Source File
# Begin Source File

SOURCE=.\res\Modify.ico
# End Source File
# Begin Source File

SOURCE=.\res\MotorMontior.ico
# End Source File
# Begin Source File

SOURCE=.\res\MultiInputTray.ico
# End Source File
# Begin Source File

SOURCE=.\res\MultiSVSetting.ico
# End Source File
# Begin Source File

SOURCE=.\res\NewMail.ico
# End Source File
# Begin Source File

SOURCE=.\res\NewText.ico
# End Source File
# Begin Source File

SOURCE=.\res\NoContinue.ico
# End Source File
# Begin Source File

SOURCE=.\res\NoYield.ico
# End Source File
# Begin Source File

SOURCE=.\res\Offset.ico
# End Source File
# Begin Source File

SOURCE=.\res\OK.ico
# End Source File
# Begin Source File

SOURCE=".\res\CCDSocketSensor\Open-Folder-Add.ico"
# End Source File
# Begin Source File

SOURCE=.\res\Orientat.bmp
# End Source File
# Begin Source File

SOURCE=.\res\OrientatExternd.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Orign.ico
# End Source File
# Begin Source File

SOURCE=.\res\page_fun.ico
# End Source File
# Begin Source File

SOURCE=.\res\PreheatSet.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Program.ico
# End Source File
# Begin Source File

SOURCE=.\res\Pxe.ico
# End Source File
# Begin Source File

SOURCE=.\res\ReadTwo.ico
# End Source File
# Begin Source File

SOURCE=.\res\RemoteInput.ico
# End Source File
# Begin Source File

SOURCE=.\res\RepeatTray.bmp
# End Source File
# Begin Source File

SOURCE=.\res\RepeatTray.ico
# End Source File
# Begin Source File

SOURCE=.\res\RepeatTrayEnable.ico
# End Source File
# Begin Source File

SOURCE=.\res\RepeatTrayOff.ico
# End Source File
# Begin Source File

SOURCE=.\res\RepeatTrayOn.ico
# End Source File
# Begin Source File

SOURCE=.\res\RepeatTrayStatus.ico
# End Source File
# Begin Source File

SOURCE=.\res\Report.ico
# End Source File
# Begin Source File

SOURCE=.\res\RotatorD.ico
# End Source File
# Begin Source File

SOURCE=.\res\RotatorN.ico
# End Source File
# Begin Source File

SOURCE=.\res\RotatorO.ico
# End Source File
# Begin Source File

SOURCE=.\res\RotatorP.ico
# End Source File
# Begin Source File

SOURCE=.\res\RotatorT.ico
# End Source File
# Begin Source File

SOURCE=.\res\RS232_Flow.bmp
# End Source File
# Begin Source File

SOURCE=.\res\rt_image.ico
# End Source File
# Begin Source File

SOURCE=.\res\RTImage.ico
# End Source File
# Begin Source File

SOURCE=".\res\CCDSocketSensor\Save-as.ico"
# End Source File
# Begin Source File

SOURCE=.\res\Save.ico
# End Source File
# Begin Source File

SOURCE=.\res\SaveImage.ico
# End Source File
# Begin Source File

SOURCE=.\res\SetBase.ico
# End Source File
# Begin Source File

SOURCE=.\res\Setting.ico
# End Source File
# Begin Source File

SOURCE=.\res\Settings.ico
# End Source File
# Begin Source File

SOURCE=.\res\Setup.ico
# End Source File
# Begin Source File

SOURCE=.\res\SetupMotorMontior.ico
# End Source File
# Begin Source File

SOURCE=.\res\SiteSetting.ico
# End Source File
# Begin Source File

SOURCE=.\res\SLTProtocol.ico
# End Source File
# Begin Source File

SOURCE=.\res\Socket.ico
# End Source File
# Begin Source File

SOURCE=.\res\SocketNoVacc.ico
# End Source File
# Begin Source File

SOURCE=.\res\SortSymbol.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Speed.ico
# End Source File
# Begin Source File

SOURCE=.\res\CCDSocketSensor\Stop.ico
# End Source File
# Begin Source File

SOURCE=.\res\SubChipTray.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SubTray.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SummaryReport.ico
# End Source File
# Begin Source File

SOURCE=.\res\Suspend.ico
# End Source File
# Begin Source File

SOURCE=.\res\Task.ico
# End Source File
# Begin Source File

SOURCE=.\res\Tempdia.ico
# End Source File
# Begin Source File

SOURCE=.\res\TempdiaInfomation.ico
# End Source File
# Begin Source File

SOURCE=.\res\TemperatureFile.ico
# End Source File
# Begin Source File

SOURCE=.\res\Temperture.ico
# End Source File
# Begin Source File

SOURCE=".\res\Test Result.ico"
# End Source File
# Begin Source File

SOURCE=.\res\CCDSocketSensor\Test.ico
# End Source File
# Begin Source File

SOURCE=.\res\TestProgram.ico
# End Source File
# Begin Source File

SOURCE=.\res\Timer.ico
# End Source File
# Begin Source File

SOURCE=.\res\Torque_Manual.ico
# End Source File
# Begin Source File

SOURCE=.\res\Tower.ico
# End Source File
# Begin Source File

SOURCE=.\res\TrainShow.ico
# End Source File
# Begin Source File

SOURCE=.\res\CCDSocketSensor\Trashcan.ico
# End Source File
# Begin Source File

SOURCE=.\res\Tray_aut.ico
# End Source File
# Begin Source File

SOURCE=.\res\Tray_InOut.ico
# End Source File
# Begin Source File

SOURCE=.\res\tray_map.ico
# End Source File
# Begin Source File

SOURCE=.\res\Tray_out.ico
# End Source File
# Begin Source File

SOURCE=.\res\TrayAutoSkip.ico
# End Source File
# Begin Source File

SOURCE=.\res\TrayColor.ico
# End Source File
# Begin Source File

SOURCE=.\res\TrayMap.ico
# End Source File
# Begin Source File

SOURCE=.\res\TrayMapUI.ico
# End Source File
# Begin Source File

SOURCE=.\res\Traymode.ico
# End Source File
# Begin Source File

SOURCE=.\res\TrayMode\traymode1.ico
# End Source File
# Begin Source File

SOURCE=.\res\TrayMode\traymode2.ico
# End Source File
# Begin Source File

SOURCE=.\res\TrayMode\traymode3.ico
# End Source File
# Begin Source File

SOURCE=.\res\TrayMode\traymode4.ico
# End Source File
# Begin Source File

SOURCE=.\res\TrayMode\traymode5.ico
# End Source File
# Begin Source File

SOURCE=.\res\TrayMode\traymode6.ico
# End Source File
# Begin Source File

SOURCE=.\res\TrayMode\traymode7.ico
# End Source File
# Begin Source File

SOURCE=.\res\TrayMode\traymode8.ico
# End Source File
# Begin Source File

SOURCE=.\res\TrayNotAutoSkip.ico
# End Source File
# Begin Source File

SOURCE=.\res\TrayPitch.bmp
# End Source File
# Begin Source File

SOURCE=.\res\TraySet.bmp
# End Source File
# Begin Source File

SOURCE=.\res\TsMode.ico
# End Source File
# Begin Source File

SOURCE=.\res\TsModeNo.ico
# End Source File
# Begin Source File

SOURCE=.\res\uph.ico
# End Source File
# Begin Source File

SOURCE=.\res\User.ico
# End Source File
# Begin Source File

SOURCE=.\res\Visual.ico
# End Source File
# Begin Source File

SOURCE=.\res\visual_p.ico
# End Source File
# Begin Source File

SOURCE=.\res\Yield.ico
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\AlignRectTracker.h
# End Source File
# Begin Source File

SOURCE=.\base64.h
# End Source File
# Begin Source File

SOURCE=.\BtnST.h
# End Source File
# Begin Source File

SOURCE=.\C_ColorToolTip.h
# End Source File
# Begin Source File

SOURCE=.\CameraDS.h
# End Source File
# Begin Source File

SOURCE=.\ColorBtn.h
# End Source File
# Begin Source File

SOURCE=.\ColorFontStatic.h
# End Source File
# Begin Source File

SOURCE=.\ColorListCtrl.h
# End Source File
# Begin Source File

SOURCE=.\ColorPickerCB.h
# End Source File
# Begin Source File

SOURCE=.\ComboListCtrl.h
# End Source File
# Begin Source File

SOURCE=.\ContinueFailCtrl.h
# End Source File
# Begin Source File

SOURCE=.\CSmtp.h
# End Source File
# Begin Source File

SOURCE=.\CtrlVision.h
# End Source File
# Begin Source File

SOURCE=.\CtrlVisionAlignment.h
# End Source File
# Begin Source File

SOURCE=.\CtrlVisionMatch.h
# End Source File
# Begin Source File

SOURCE=.\Deer.h
# End Source File
# Begin Source File

SOURCE=.\DeerDlg.h
# End Source File
# Begin Source File

SOURCE=.\Define.h
# End Source File
# Begin Source File

SOURCE=.\DlgAlignment.h
# End Source File
# Begin Source File

SOURCE=.\DlgAlignmentCheck.h
# End Source File
# Begin Source File

SOURCE=.\DlgAlignmentPw.h
# End Source File
# Begin Source File

SOURCE=.\DlgArmLogICImage.h
# End Source File
# Begin Source File

SOURCE=.\DlgATCModuleCalibration.h
# End Source File
# Begin Source File

SOURCE=.\DlgATCModuleFile.h
# End Source File
# Begin Source File

SOURCE=.\DlgATCModuleModify.h
# End Source File
# Begin Source File

SOURCE=.\DlgATCModuleNew.h
# End Source File
# Begin Source File

SOURCE=.\DlgATCModuleSetting.h
# End Source File
# Begin Source File

SOURCE=.\DlgATCMonitor.h
# End Source File
# Begin Source File

SOURCE=.\DlgAutoRetry.h
# End Source File
# Begin Source File

SOURCE=.\DlgAutoRetrySetting.h
# End Source File
# Begin Source File

SOURCE=.\DlgBasicSetting.h
# End Source File
# Begin Source File

SOURCE=.\DlgBinColor.h
# End Source File
# Begin Source File

SOURCE=.\DlgBinMapping.h
# End Source File
# Begin Source File

SOURCE=.\DlgBinModify.h
# End Source File
# Begin Source File

SOURCE=.\DlgBinNew.h
# End Source File
# Begin Source File

SOURCE=.\DlgBinStatus.h
# End Source File
# Begin Source File

SOURCE=.\DlgButton.h
# End Source File
# Begin Source File

SOURCE=.\DlgCameraSetting.h
# End Source File
# Begin Source File

SOURCE=.\DlgCategory.h
# End Source File
# Begin Source File

SOURCE=.\DlgClearCount.h
# End Source File
# Begin Source File

SOURCE=.\DlgCommunication.h
# End Source File
# Begin Source File

SOURCE=.\DlgCommunicationInfo.h
# End Source File
# Begin Source File

SOURCE=.\DlgContactCounter.h
# End Source File
# Begin Source File

SOURCE=.\DlgCustomMCFunction.h
# End Source File
# Begin Source File

SOURCE=.\DlgCustomPageFunction.h
# End Source File
# Begin Source File

SOURCE=.\DlgCylinderLifeTimeTool.h
# End Source File
# Begin Source File

SOURCE=.\DlgDebugError.h
# End Source File
# Begin Source File

SOURCE=.\DlgDebugErrorList.h
# End Source File
# Begin Source File

SOURCE=.\DlgDebugFunction.h
# End Source File
# Begin Source File

SOURCE=.\DlgDeviceSetup.h
# End Source File
# Begin Source File

SOURCE=.\DlgError.h
# End Source File
# Begin Source File

SOURCE=.\DlgEvent.h
# End Source File
# Begin Source File

SOURCE=.\DlgExtendFunction.h
# End Source File
# Begin Source File

SOURCE=.\DlgFilePath.h
# End Source File
# Begin Source File

SOURCE=.\DlgGearRation.h
# End Source File
# Begin Source File

SOURCE=.\DlgHandlerComPort.h
# End Source File
# Begin Source File

SOURCE=.\DlgHandlerStatus.h
# End Source File
# Begin Source File

SOURCE=.\DlgHandlerStatusList.h
# End Source File
# Begin Source File

SOURCE=.\DlgHotKey.h
# End Source File
# Begin Source File

SOURCE=.\DlgInOutputTrayMap.h
# End Source File
# Begin Source File

SOURCE=.\DlgInputTrayMap.h
# End Source File
# Begin Source File

SOURCE=.\DlgIOMontior.h
# End Source File
# Begin Source File

SOURCE=.\DlgIOMontiorATCModule.h
# End Source File
# Begin Source File

SOURCE=.\DlgIOMontiorHandler.h
# End Source File
# Begin Source File

SOURCE=.\DlgIOMontiorPTCModule.h
# End Source File
# Begin Source File

SOURCE=.\DlgIOMontiorRemote.h
# End Source File
# Begin Source File

SOURCE=.\DlgJamRateReportTool.h
# End Source File
# Begin Source File

SOURCE=.\DlgJamRateReportToolLastReport.h
# End Source File
# Begin Source File

SOURCE=.\DlgLogEnable.h
# End Source File
# Begin Source File

SOURCE=.\DlgLotInformation.h
# End Source File
# Begin Source File

SOURCE=.\DlgLotInformationDone.h
# End Source File
# Begin Source File

SOURCE=.\DlgLotInformationProgress.h
# End Source File
# Begin Source File

SOURCE=.\DlgMail.h
# End Source File
# Begin Source File

SOURCE=.\DlgManualContact.h
# End Source File
# Begin Source File

SOURCE=.\DlgManualContactRecover.h
# End Source File
# Begin Source File

SOURCE=.\DlgManualContactTorque.h
# End Source File
# Begin Source File

SOURCE=.\DlgManualContactTorqueKgf.h
# End Source File
# Begin Source File

SOURCE=.\DlgMotorMontior.h
# End Source File
# Begin Source File

SOURCE=.\DlgMotorMove.h
# End Source File
# Begin Source File

SOURCE=.\DlgMotorSimpleStatus.h
# End Source File
# Begin Source File

SOURCE=.\DlgMotorStatus.h
# End Source File
# Begin Source File

SOURCE=.\DlgOffset.h
# End Source File
# Begin Source File

SOURCE=.\DlgOffsetTS.h
# End Source File
# Begin Source File

SOURCE=.\DlgOutputTrayMap.h
# End Source File
# Begin Source File

SOURCE=.\DlgOutputYield.h
# End Source File
# Begin Source File

SOURCE=.\DlgPassword.h
# End Source File
# Begin Source File

SOURCE=.\DlgPasswordNeed.h
# End Source File
# Begin Source File

SOURCE=.\DlgPasswordRead.h
# End Source File
# Begin Source File

SOURCE=.\DlgProgramStart.h
# End Source File
# Begin Source File

SOURCE=.\DlgReLoadFile.h
# End Source File
# Begin Source File

SOURCE=.\DlgRemoteCommMonitor.h
# End Source File
# Begin Source File

SOURCE=.\DlgRemoteCommMsg.h
# End Source File
# Begin Source File

SOURCE=.\DlgRemoteCommMsgLot.h
# End Source File
# Begin Source File

SOURCE=.\DlgRemoteCommunication.h
# End Source File
# Begin Source File

SOURCE=.\DlgRemoteControl.h
# End Source File
# Begin Source File

SOURCE=.\DlgRemoteControlCustom.h
# End Source File
# Begin Source File

SOURCE=.\DlgRemoteControlCustomInput.h
# End Source File
# Begin Source File

SOURCE=.\DlgRemoteRecover.h
# End Source File
# Begin Source File

SOURCE=.\DlgRepeatTray.h
# End Source File
# Begin Source File

SOURCE=.\DlgRepeatTrayBinCtrl.h
# End Source File
# Begin Source File

SOURCE=.\DlgRepeatTrayEnable.h
# End Source File
# Begin Source File

SOURCE=.\DlgRepeatTrayInOutCtrl.h
# End Source File
# Begin Source File

SOURCE=.\DlgRepeatTrayTemp.h
# End Source File
# Begin Source File

SOURCE=.\DlgSetting.h
# End Source File
# Begin Source File

SOURCE=.\DlgSettingGpib.h
# End Source File
# Begin Source File

SOURCE=.\DlgSettingNote.h
# End Source File
# Begin Source File

SOURCE=.\DlgSettingRs232.h
# End Source File
# Begin Source File

SOURCE=.\DlgSettingTcp.h
# End Source File
# Begin Source File

SOURCE=.\DlgSettingTTL.h
# End Source File
# Begin Source File

SOURCE=.\DlgSiteSetting.h
# End Source File
# Begin Source File

SOURCE=.\DlgSLTProtocol.h
# End Source File
# Begin Source File

SOURCE=.\DlgSLTProtocolHelp.h
# End Source File
# Begin Source File

SOURCE=.\DlgSLTProtocolMonitor.h
# End Source File
# Begin Source File

SOURCE=.\DlgSLTProtocolSetting.h
# End Source File
# Begin Source File

SOURCE=.\DlgSocketMatch.h
# End Source File
# Begin Source File

SOURCE=.\DlgSocketVisionCam.h
# End Source File
# Begin Source File

SOURCE=.\DlgSocketVisionCtrlLive.h
# End Source File
# Begin Source File

SOURCE=.\DlgSocketVisionCtrlSetting.h
# End Source File
# Begin Source File

SOURCE=.\DlgSpeed.h
# End Source File
# Begin Source File

SOURCE=.\DlgSummaryReport.h
# End Source File
# Begin Source File

SOURCE=.\DlgSummaryReportDetail.h
# End Source File
# Begin Source File

SOURCE=.\DlgTemperature.h
# End Source File
# Begin Source File

SOURCE=.\DlgTemperatureCalibration.h
# End Source File
# Begin Source File

SOURCE=.\DlgTemperatureLookupTable.h
# End Source File
# Begin Source File

SOURCE=.\DlgTemperatureTool.h
# End Source File
# Begin Source File

SOURCE=.\DlgTestResult.h
# End Source File
# Begin Source File

SOURCE=.\DlgTestSetting.h
# End Source File
# Begin Source File

SOURCE=.\DlgTestTesting.h
# End Source File
# Begin Source File

SOURCE=.\DlgThreadMontior.h
# End Source File
# Begin Source File

SOURCE=.\DlgTimer.h
# End Source File
# Begin Source File

SOURCE=.\DlgTimerSetting.h
# End Source File
# Begin Source File

SOURCE=.\DlgTorqueControl.h
# End Source File
# Begin Source File

SOURCE=.\DlgTorqueTool.h
# End Source File
# Begin Source File

SOURCE=.\DlgTowerSetting.h
# End Source File
# Begin Source File

SOURCE=.\DlgTrayDef.h
# End Source File
# Begin Source File

SOURCE=.\DlgTrayFile.h
# End Source File
# Begin Source File

SOURCE=.\DlgTrayFileChipTray.h
# End Source File
# Begin Source File

SOURCE=.\DlgTrayFileNoHeater.h
# End Source File
# Begin Source File

SOURCE=.\DlgTrayMap.h
# End Source File
# Begin Source File

SOURCE=.\DlgTrayMapRepeat.h
# End Source File
# Begin Source File

SOURCE=.\DlgTrayMapReport.h
# End Source File
# Begin Source File

SOURCE=.\DlgTrayMapUI.h
# End Source File
# Begin Source File

SOURCE=.\DlgTrayRepeatStatus.h
# End Source File
# Begin Source File

SOURCE=.\DlgTrayStatus.h
# End Source File
# Begin Source File

SOURCE=.\DlgTSRemainIC.h
# End Source File
# Begin Source File

SOURCE=.\DlgUPHTool.h
# End Source File
# Begin Source File

SOURCE=.\DlgVisionSetup.h
# End Source File
# Begin Source File

SOURCE=.\DlgVisualButton.h
# End Source File
# Begin Source File

SOURCE=.\DlgWestTool.h
# End Source File
# Begin Source File

SOURCE=.\DlgYieldControl.h
# End Source File
# Begin Source File

SOURCE=.\DlgYieldMonitor.h
# End Source File
# Begin Source File

SOURCE=.\DMsg.h
# End Source File
# Begin Source File

SOURCE=.\DriverMotorTorqueControl.h
# End Source File
# Begin Source File

SOURCE=.\DriverTestInterface.h
# End Source File
# Begin Source File

SOURCE=.\DriverTestInterfaceTCP.h
# End Source File
# Begin Source File

SOURCE=.\DriveWest.h
# End Source File
# Begin Source File

SOURCE=.\ErrView.h
# End Source File
# Begin Source File

SOURCE=.\EventLog.h
# End Source File
# Begin Source File

SOURCE=.\FileCtrl.h
# End Source File
# Begin Source File

SOURCE=.\Function.h
# End Source File
# Begin Source File

SOURCE=.\GridCtrl\GridCell.h
# End Source File
# Begin Source File

SOURCE=.\GridCtrl\GridCellBase.h
# End Source File
# Begin Source File

SOURCE=.\GridCtrl\GridCtrl.h
# End Source File
# Begin Source File

SOURCE=.\GridCtrl\GridDropTarget.h
# End Source File
# Begin Source File

SOURCE=.\GridCtrl\GroupControl.h
# End Source File
# Begin Source File

SOURCE=.\InPlaceComboTP.h
# End Source File
# Begin Source File

SOURCE=.\GridCtrl\InPlaceEdit.h
# End Source File
# Begin Source File

SOURCE=.\InPlaceEditTP.h
# End Source File
# Begin Source File

SOURCE=.\Interface.h
# End Source File
# Begin Source File

SOURCE=.\InterfaceTcp.h
# End Source File
# Begin Source File

SOURCE=.\Led.h
# End Source File
# Begin Source File

SOURCE=.\LogData.h
# End Source File
# Begin Source File

SOURCE=.\MailCtrl.h
# End Source File
# Begin Source File

SOURCE=.\Member.h
# End Source File
# Begin Source File

SOURCE=.\Motor.h
# End Source File
# Begin Source File

SOURCE=.\ni488.h
# End Source File
# Begin Source File

SOURCE=.\PageDebug.h
# End Source File
# Begin Source File

SOURCE=.\PageEngineer.h
# End Source File
# Begin Source File

SOURCE=.\PageInitial.h
# End Source File
# Begin Source File

SOURCE=.\PageRun.h
# End Source File
# Begin Source File

SOURCE=.\PageSetup.h
# End Source File
# Begin Source File

SOURCE=.\PageUser.h
# End Source File
# Begin Source File

SOURCE=.\Parser3111.h
# End Source File
# Begin Source File

SOURCE=.\PreheaterFile.h
# End Source File
# Begin Source File

SOURCE=.\RADatabase.h
# End Source File
# Begin Source File

SOURCE=.\RADatabaseLock.h
# End Source File
# Begin Source File

SOURCE=.\Report.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\ThArm.h
# End Source File
# Begin Source File

SOURCE=.\ThErrorCtrl.h
# End Source File
# Begin Source File

SOURCE=.\ThInitialArm.h
# End Source File
# Begin Source File

SOURCE=.\ThInserter.h
# End Source File
# Begin Source File

SOURCE=.\ThInspect.h
# End Source File
# Begin Source File

SOURCE=.\ThIOReadWrite.h
# End Source File
# Begin Source File

SOURCE=.\ThIOReadWriteRemoteIO.h
# End Source File
# Begin Source File

SOURCE=.\ThManualCtrl.h
# End Source File
# Begin Source File

SOURCE=.\ThTester.h
# End Source File
# Begin Source File

SOURCE=.\GridCtrl\TitleTip.h
# End Source File
# Begin Source File

SOURCE=.\TorqueCtrl.h
# End Source File
# Begin Source File

SOURCE=.\TrayFile.h
# End Source File
# Begin Source File

SOURCE=.\TrayMapCtrl.h
# End Source File
# Begin Source File

SOURCE=.\TrayMapSelCtrl.h
# End Source File
# Begin Source File

SOURCE=.\ViewIC.h
# End Source File
# Begin Source File

SOURCE=.\ViewImage.h
# End Source File
# Begin Source File

SOURCE=.\ViewRepeatTrayMotor.h
# End Source File
# Begin Source File

SOURCE=.\ViewSockImage.h
# End Source File
# Begin Source File

SOURCE=.\ViewSockTrackerImage.h
# End Source File
# Begin Source File

SOURCE=.\ViewTrayMap.h
# End Source File
# Begin Source File

SOURCE=.\ViewTrayMotor.h
# End Source File
# Begin Source File

SOURCE=.\YieldControl.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\Information.txt
# End Source File
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# Begin Source File

SOURCE=.\SLTProtocol
# End Source File
# Begin Source File

SOURCE=.\SLTProtocol_Marvell
# End Source File
# End Target
# End Project
# Section Deer : {28B794DD-9DFD-46E6-9C8E-92986475F55C}
# 	2:19:CLASS: lImageStruct:lImageStruct
# 	2:10:CameraDS.h:CameraDS.h
# 	2:16:CLASS: CCameraDS:CCameraDS
# 	2:12:CameraDS.cpp:CameraDS.cpp
# 	2:16:CLASS: ImageSize:ImageSize
# 	2:19:Application Include:deer.h
# End Section
# Section Deer : {D1FF3584-6D6F-4AB8-8610-7B9A907FCCD3}
# 	2:10:ENUM: enum:enum
# 	2:16:CLASS: CButtonST:CButtonST
# 	2:9:BtnST.cpp:BtnST.cpp
# 	2:19:Application Include:Deer.h
# 	2:7:BtnST.h:BtnST.h
# End Section
# Section Deer : {EB16713D-6B36-4624-9219-86C5441DBEF7}
# 	2:24:CLASS: CContinueFailCtrl:CContinueFailCtrl
# 	2:20:ContinueFailCtrl.cpp:ContinueFailCtrl.cpp
# 	2:19:Application Include:deer.h
# 	2:18:ContinueFailCtrl.h:ContinueFailCtrl.h
# End Section
# Section Deer : {88D3E60F-057C-431B-8B4A-43E7C3B3A272}
# 	2:10:TrayFile.h:TrayFile.h
# 	2:12:TrayFile.cpp:TrayFile.cpp
# 	2:16:CLASS: CTrayFile:CTrayFile
# 	2:19:Application Include:Deer.h
# End Section
# Section Deer : {B32C41F2-94B7-453A-B3F8-036D408031A0}
# 	2:12:ListReport.h:ListReport.h
# 	2:14:ENUM: ItemType:ItemType
# 	2:18:CLASS: CListReport:CListReport
# 	2:14:ListReport.cpp:ListReport.cpp
# 	2:19:Application Include:deer.h
# End Section
# Section Deer : {4CE8205C-7087-49BA-BFB3-905CDD7C57CA}
# 	2:23:CLASS: CColorFontStatic:CColorFontStatic
# 	2:17:ColorFontStatic.h:ColorFontStatic.h
# 	2:19:ColorFontStatic.cpp:ColorFontStatic.cpp
# 	2:19:Application Include:Deer.h
# End Section
# Section Deer : {5A3E5297-7E21-406F-98D1-2F3F994CA9FD}
# 	2:14:GridCellBase.h:GridCellBase.h
# 	2:16:GridCellBase.cpp:GridCellBase.cpp
# 	2:16:TYPEDEF: GV_ITEM:GV_ITEM
# 	2:15:CLASS: _GV_ITEM:_GV_ITEM
# 	2:19:Application Include:deer.h
# 	2:20:CLASS: CGridCellBase:CGridCellBase
# End Section
# Section Deer : {B97376C8-5BEA-4F14-8884-B52157F151E0}
# 	2:12:ColorBtn.cpp:ColorBtn.cpp
# 	2:10:ColorBtn.h:ColorBtn.h
# 	2:16:CLASS: CColorBtn:CColorBtn
# 	2:19:Application Include:Deer.h
# End Section
# Section Deer : {D3C0D228-17A2-499A-A2D7-42AF3E8E9C30}
# 	2:21:DefaultSinkHeaderFile:traymap.h
# 	2:16:DefaultSinkClass:CTrayMap
# End Section
# Section Deer : {BE6DE805-5791-4BC5-9C2C-3E895D07712E}
# 	2:19:CLASS: CInPlaceEdit:CInPlaceEdit
# 	2:15:InPlaceEdit.cpp:InPlaceEdit.cpp
# 	2:19:Application Include:Deer.h
# 	2:13:InPlaceEdit.h:InPlaceEdit.h
# End Section
# Section Deer : {DD6147A2-2D6E-49A3-8DDF-9361FF22BD60}
# 	2:10:TitleTip.h:TitleTip.h
# 	2:16:CLASS: CTitleTip:CTitleTip
# 	2:12:TitleTip.cpp:TitleTip.cpp
# 	2:19:Application Include:Deer.h
# End Section
# Section Deer : {79B1DB88-0BE5-42B6-8F30-E11F0B5382CB}
# 	2:7:Led.cpp:Led.cpp
# 	2:11:CLASS: CLed:CLed
# 	2:10:ENUM: enum:enum
# 	2:19:Application Include:deer.h
# 	2:5:Led.h:Led.h
# End Section
# Section Deer : {DA5CC0E2-4550-4106-99D4-22D88F29EC9F}
# 	2:12:GridCtrl.cpp:GridCtrl.cpp
# 	2:21:CLASS: tagGV_DISPINFO:tagGV_DISPINFO
# 	2:21:TYPEDEF: GRIDCALLBACK:GRIDCALLBACK
# 	2:10:GridCtrl.h:GridCtrl.h
# 	2:16:CLASS: CGridCtrl:CGridCtrl
# 	2:21:TYPEDEF: GV_CACHEHINT:GV_CACHEHINT
# 	2:20:TYPEDEF: NM_GRIDVIEW:NM_GRIDVIEW
# 	2:22:CLASS: tagGV_CACHEHINT:tagGV_CACHEHINT
# 	2:20:TYPEDEF: GV_DISPINFO:GV_DISPINFO
# 	2:19:Application Include:deer.h
# 	2:17:TYPEDEF: GRID_ROW:GRID_ROW
# 	2:21:CLASS: tagNM_GRIDVIEW:tagNM_GRIDVIEW
# End Section
# Section Deer : {829502F2-0A77-4856-94EF-8C460180E1FA}
# 	2:16:CLASS: CAutoLock:CAutoLock
# 	2:17:TorqueControl.cpp:TorqueControl.cpp
# 	2:21:CLASS: CTorqueControl:CTorqueControl
# 	2:15:TorqueControl.h:TorqueControl.h
# 	2:19:Application Include:deer.h
# End Section
# Section Deer : {D5C5CD72-94FB-444D-ACD3-3CC91C8A01FB}
# 	2:15:TrayMapCtrl.cpp:TrayMapCtrl.cpp
# 	2:19:CLASS: CTrayMapCtrl:CTrayMapCtrl
# 	2:19:Application Include:deer.h
# 	2:13:TrayMapCtrl.h:TrayMapCtrl.h
# End Section
# Section Deer : {78442DF1-FB85-40C7-8502-EB4160D70E31}
# 	2:5:Class:CTrayMap
# 	2:10:HeaderFile:traymap.h
# 	2:8:ImplFile:traymap.cpp
# End Section
# Section Deer : {3274C5FE-9EE9-44EF-9BB6-9512FA9CB908}
# 	2:19:CLASS: lImageStruct:lImageStruct
# 	2:10:CameraDS.h:CameraDS.h
# 	2:16:CLASS: CCameraDS:CCameraDS
# 	2:12:CameraDS.cpp:CameraDS.cpp
# 	2:16:CLASS: ImageSize:ImageSize
# 	2:19:Application Include:deer.h
# End Section
# Section Deer : {B71582DE-D98B-4CAE-B6FB-36F8A544C839}
# 	2:13:Interface.cpp:Interface.cpp
# 	2:11:Interface.h:Interface.h
# 	2:17:CLASS: CInterface:CInterface
# 	2:19:Application Include:deer.h
# End Section
# Section Deer : {29195922-6864-484A-BDE8-E1D0A370FC0F}
# 	2:16:CLASS: CEventLog:CEventLog
# 	2:10:EventLog.h:EventLog.h
# 	2:12:EventLog.cpp:EventLog.cpp
# 	2:19:Application Include:deer.h
# End Section
# Section Deer : {A8A6BBDD-9E4F-4A3E-9612-4D25EA71F86F}
# 	2:20:CLASS: CYieldControl:CYieldControl
# 	2:14:YieldControl.h:YieldControl.h
# 	2:19:Application Include:Deer.h
# 	2:16:YieldControl.cpp:YieldControl.cpp
# End Section
# Section Deer : {7EC4CD83-56CD-447F-ADD8-1E90153ACE55}
# 	2:14:GroupControl.h:GroupControl.h
# 	2:31:TYPEDEF: GROUPCONTROLACTIONFUNC:GROUPCONTROLACTIONFUNC
# 	2:20:CLASS: CGroupControl:CGroupControl
# 	2:19:Application Include:Deer.h
# 	2:16:GroupControl.cpp:GroupControl.cpp
# End Section
# Section Deer : {3BFFDA47-3B33-43E8-B77C-7D8DED52CEFF}
# 	2:23:CLASS: CGridDefaultCell:CGridDefaultCell
# 	2:12:GridCell.cpp:GridCell.cpp
# 	2:10:GridCell.h:GridCell.h
# 	2:16:CLASS: CGridCell:CGridCell
# 	2:19:Application Include:deer.h
# End Section
# Section Deer : {C94A7E75-56DF-4458-8F57-2C0E268AF78F}
# 	2:14:SocketVision.h:SocketVision.h
# 	2:20:CLASS: CSocketVision:CSocketVision
# 	2:16:SocketVision.cpp:SocketVision.cpp
# 	2:15:CLASS: tagMatch:tagMatch
# 	2:19:Application Include:deer.h
# End Section
# Section Deer : {FB357CDA-226F-475A-8DDE-6A06402F0427}
# 	2:18:GridDropTarget.cpp:GridDropTarget.cpp
# 	2:16:GridDropTarget.h:GridDropTarget.h
# 	2:22:CLASS: CGridDropTarget:CGridDropTarget
# 	2:19:Application Include:deer.h
# End Section
