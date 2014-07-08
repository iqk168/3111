//////////////////////////A6S3更新部分/////////////////////////
V0.1Ba
1.把編譯檔案移到外面硬碟

V0.1B
1.把ErrorCode 補齊

V0.1A~
1.抽換RemoteControl 開Port 通訊層
2.新增Parser3111 為命令處理層
3.Include 的東西包到自己的資料夾中

////////////////////Ken 更新部分////////////////////////////////
V1.0
1: Origneal Version

V1.0Aa
1: 修正 Access Level登入權限,如果按下Cancel會錯誤登入Super User的權限
2: 修正 Interface 在Send Start Delay如果輸入0導致無法儲存的問題, 並且增加提示視窗
3: 修正 Run Page Tips, 提示 Catoregy 錯誤字串
4: 增加 Test Site Vacc 功能, 讓使用者可以關閉或啟動測試期間關閉 Vacuum

V1.0Ab
1: Offset增加說明文件功能,說明文字檔案在\System\3111.OfNote
2: Setup Page, TrayMap Setting 變更文字為 Tray Map Setting
3: Setup Page, IO Montior 修正為 IO Monitor
4: Setup Pagem Tray Map Setting表單, 內頁標題由Input / Output Tray修改為 Tray Map Setting
5: Manaul Contact, TS Offset 表單標題增加單位 (mm)
6: Manual Contact,在Enable Manual Contact增加Test Site Direct Contact 選項,Enable後,在Manual Contact會出現
Contact模式選擇,可以選由Shuttle Input入料,或是直接放到Soaket
7: Manual Contact,在Enable Manual Contact增加Test Site Vacc功能 選項,Enable後,
在Manual Contact會出現Ts Vacc模式可以選擇, 如果關閉,那麼如果由Shuttle入料,則會關閉Vacc,避免Vacc太大聲的噪音
8: Shuttle 增加入料檢查, 當Shuttle 移動到入料區(TestSite)下方,再檢查一次Jam sensor, 避免移動的過程中IC Jam, 
導致 Wrokpress 壓壞IC, TestSite Skip 會重新入料, 此ErrorCode 為 605 Shuttle Input Jam
9: Tray File 表單標題移除 List, 修改為 Tray File
10:Tray File 修改 Base File 的長度
11:在Run Page 如果在Device Setup選好TrayFile,但是還沒建立新的工單,那麼可以直接由系統模式的文字方塊
點選切換Mode
12:Test Site Remain IC可以由Debug Function用來設定該客戶是否需要啟動該功能
13:Shuttle Jam Log, 如果在Shuttle 移動到 Test Site 下方那麼就會Log, _ShuttleJam.txt

V1.0Ac
1: Device Setup, TrayFile修改為Drop List, 避免內容被改到
2: 增加 Repeat Tray 功能
3: 在沒有建立工單的情況, 可以由 Run Page 的檔案資訊欄叫出Device Seup 修改 Tray File
4: 在沒有建立工單的情況, 可以由 Run Page 的檔案資訊欄叫出Repeat Tray 修改設定
5: Run Page 增加 Visual Panel 方便使用
6: Run Page 增加 Tray Stat 功能, 用來檢視, 目前 Repeat Tray 取/放的資訊
7: Run Page 增加 Tray Color 功能, 用來調整 Repeat Tray 顯示資訊, 當下Tray File的模式

V1.0Ad
1: 可透過　m.Setting.m_bCancelDoubleChkChange, 如果有改變參數, 決定離開表單要不要向使用者確認,1表示要確認
2: 增加即時讀取 Test Site Drive, Torque status(%) 功能, 接上馬達連接線, 並且在Com Port欄位設定相對應連接口
然後到 \System\3111.System 把 Enable Torque Status=1 設定為1, 那麼重開軟體, Initial 結束後, 就會開始讀取Torque
3: 修正讀取 CDriverMotorTorqueControl 產生的問題
4: Repeat Tray, Max Value, 在 Basic Setting 改為可以設定, 而非 Disable
5: 修正 Alarm Mail 解構造成關程式的 Delay
6: 修正 West 解構造成關程式偶發 Memory leak

V1.0Ae
1: 修正 CWest 關執行緒的不穩定的問題
2: 修正 Repeat Tray Output Z down

V1.0Af
1: 增加 Lamp Setup 功能, 可自由設定 三色指示燈的行為模式
2: 修改 Ts Counter 改為可以讓 Engineer 修改
3: 修改 Ts Counter 可以由 Run Page 打開, 並根據不同的權限, 決定可不可以清除
4: 增加 DMSG 用來紀錄開機的過程是否正確
5: 修正 Lot Done Prograss, 改為要 Handle Thread 是否被關閉
6: 修改 UpdataMainMsg, 讓 Door Disable 改變為閃爍
7: 修正 OpenCamera(int nCamID, bool bDisplayProperties, int nWidth, int nHeight),
當 Camera 全部移除時, 程式啟動造成的當機
8: 修改, 移除 CMotor 內全部的 MC8141PSetRange(pAxis->BoardID, 0, 8000000);
9: 修正, CMotor, MotorRunAway 裡面的速度, 由載入檔案速度修改為固定 10%速度, 以避免Initial ArmXY 原點不穩定
10: 修正 CThIOReadWriteRemoteIO::SetTorque(), 無法設定到 10 Volt的問題
11: 修正 Jam Rate Report 計算總數量的錯誤
12: 修正 CCameraDS::CloseCamera(), 沒有先 Detach(); , 造成解構時 return code 異常
13: 修正 InitOutputColor, 沒有載入顏色的問題
14: 新增 Arm Log Image 功能, 運轉中每次放 IC 前要取像, 每次建立一筆新的工單都會根據工單產生一份資料夾, 用來儲存檔案
( 檔名格式 : 002_Tray1_001.jpg ( ICLocation_TrayFrom_RepeatTimes.jpg ), 資料夾格式 : yyyy_mm_dd_hhss_LotNo
15: 增加 Tray File Mode, Remote 項目
16: 增加 GDIPlus, // GDIPlus 類別, 用來轉檔
17: 修正 LoadCounter, SaveCounter 寫錯陣列的問題
18: 修改 預設不再變更 AutoSkip 的選項, 跟隨檔案紀錄
19: 修正 ThIOReadWritaRemoteIO 移除 ND_ReadBackDO 以避免開啟 HeaterOn 異常
20: 修改 Lot Information 可以選擇 TrayFile
21: 修改 Lot Done Progress 自動消失

V1.0Ag
1: 修改 _InitialInPosRange 由 1 修改為 2, 避免Initial 容易 Timeout
2: 修改 MotorRunAway, 修改下命令前的等待時間, 避免 pulse 移動前造成誤判
3: 修改 MotorRunAway, 修改 確認到位沒有誤判

V1.0Ah
1: 修改 Manual Contact, Torque 修改為 Contact Force
2: 修改 Summary Report 表單, 標題由 Summary Report List 修改為 Summary Report
3: 修改 Offset 表單, Input(Place), Ouput(Pick) 修改為 Place, Pick, 避免客戶混淆
4: 修改 IO Monitor 表單, Rotator 內 Missing LED 修改為 Present
5: 新增 Manual Contact, 增加操作說明
6: 新增 Offset, OffsetTs 增加單位說明
7: 修改 Extend Function, 如果 Rotator 功能關閉, 則不顯示選項, 如果啟動, 則顯示選項, 以避免客戶混淆
8: 修改 各頁面表單, 如果該頁面是根據 TrayFile, 則頁面會標示為 Tray, 
如果該頁面是跟隨 Machine 則頁面會標示 Machine, 
ex: TrayFile -> [Tray File Information], Machine -> [Machine File Information]
Handler: TrayColorDef, AutoRetry, RepeatTray, TowerSetting, Motor Monitor, Alignment, TS Counter, Alarm Mail
Tray: Site Setting, Yield Control, Offset, Speed, Timer, Catoregy, Offset TS
9: 移除 Simulation Setting 相關參數
10: 移除 Loop Test 相關參數
11: 增加 ErrorCode: enCodeTestSiteMoveICMissing	(606 Test Site move to place, IC missing), 
當 Test Site 下降去 Socket 放IC時, 則如果連續檢查到35次IO關閉,則表示IC掉落, 
則會將 Test Site拉起, 然後發出Alarm, 請使用者按下 Test Site Skip 移除 掉落IC後, 繼續運轉
12: 修改 Arm Log Image, 只有啟動該功能, 才新增資料夾
13: 修改 Initial 的時候, 如果 Shuttle 已經停在 Pick/Place的位置, 則最後才回到 Home
以避免如果Initial時, 最後停的位置是 TestSite到Shuttle Pick IC, 會造成 TestSite 升到一半, 突然被拉回 Home,導致Workpress損壞
14: 修改 如果關程式, 最後停的位置是 TestSite到Shuttle Pick IC, 會造成關程式後 Shuttle 會拉住 Test Site 造成 Wrokpress 損傷
因此 發現最後停的位置是 Pick/Place位置, 則強迫設定到 Pick/Place的位置
15: 修正 Tester Setting, Interface Setting IP 顯示錯誤的問題, 新增 GetHandlerIPAddress() 取得正確IP

V 1.0Ai
1: 修正 Error Code, 509 如果在 Shuttle Pick IC 的時候, 如果 Retry 會造成返回放IC ArmLog 取值錯誤, 導致
放到 -1 的錯誤位置, 已修正

V 1.0Aj
1: 增加 MoveOffnNLimit, 確保 Initial 一定會正確離開負極限
2: 修改 Arm Z Initial, 將 MotorMovetonLimt 變更為 MotorMovetonNLimt, 以確保訊號正確, 不會因為短暫極限訊號閃一下,
造成系統 Initial 異常
3: 增加 Pass/Fail 模式在Repeat Tray, 因此修改 GetRepeatTrayModeMoation(), 增加 ResetInputStatus()
增加 ErrorCode: enCodeArmOutputTray1Full (516 Tray1 Fail Full),	enCodeArmOutputTray2Full (517 Tray2 Fail Full)
4: 增加 SLT Protocol 功能,
5: 增加 RemoteErrorMessage, 用來傳送 Event 事件
6: 修正 enToOutputHomeEnd, 寫入 BinLog 錯誤, 導致無法正確產生報表
7: 修正 Initial 減少單機模擬時的時間
8: 新增 InitialMissionOnTheGo(), SetRemoteCoordRequest(), GetRemoteCoordRequest(), 
通知 ThArm 開始執行 Coordnation 任務

V 1.0Ak
1: 修正 SLT Protocol 永遠無法開啟成功的錯誤
2: 增加 tagRemoteCtrlFun, 用來開啟與設定相關功能

V 1.0Al
1: 修改 SLT Protocol 行為模式, 增加 SetStateErrorCtrlDone
2: 修改 SLT Protocol 的目前 baund rate 115200 -> 9600
3: 修正 SetSiteTemp 沒有限制溫度的問題, 並且把限制開為 145.00
4: 新增 UpdateYieldSetting, 避免 RunPage 的良率表格閃爍

V 1.0Am
1: 新增 SLT Protocol 命令, SetTestSiteVacc, 當測試時, 用來關閉, Test Site Vacc
2: 在 SetErrorMessage 內, Demo 模式增加
3: 增加 RepeatTrayReport 功能,在Repeat Tray模式下, 
如果設定為 Both/Disable, Disable/Both, Both/Both 將會產生報表, 但是 Bin(H/W) 因為沒有根據H/W 分Bin, 因此預設值為 None

V 1.0An
1: 新增 CDlgTrayMapRepeat 表單, 用來表示Repeat Tray模式下, 目前Tray Map的格式
# 增加 RepeatTray, TrayMap相關TrayMap功能,SaveTrayMapRepeat, LoadTrayMapRepeat, AddTrayMapRepeat
# 增加 LotDoneClearTrayMapRepeat, 在 LotDone 時, 清除 Repeat Tray 的相關資料
# 新增 _Output_Stack_Number, m.TrayMapRepeat, 用來處理Repeat Tray相關的TrayMap資料
# 修改 CViewTrayMap 配合 RepeatTray 模式下的繪圖
# RepeatTray TrayMap
2: 在 Demo 模式下, 會啟動 RS232/TCP/IP

V 1.0Ao
1: 修改 在 Demo 模式下, 會關閉 RS232/TCP/IP
2: SLT Protocol 修改
# 增加 CDriverTestInterfaceTCP (m_TesterInterfaceTcp), TCP/IP 層
# 修改 Cordnation 初始值Col,Row,Tray 的預設值由-1,轉為0
# 增加 GetBaudRate 取得 當前 BaudRate 數值

3: 修改 Initial (Page Initial) 畫面, 把把即時顯示的表單拉長, 以避免資料蓋過
4: 修改 Interface Setting, TCP/IP 的切換, 以避免顯示斷行
5: 新增 User Page 的 SLT Protocol Dialog, 包括Basic Setting用來顯示設定, 
Monitor用來即時顯示訊息, Help 用來顯示目前的指令集

V 1.0Ap
1: SLT Protocol 修改
# 增加 InitTestInterfaceExcute, 將 ProcessCommand, 獨立出來處理

V1.0Aq
1: SLT Protocol 修改
# 修改 SETCOORDNATESRETURN, <<SETCOORDNATIONRETURN: DONE>> 修改為 <<SETCOORDINATESRETURN: DONE>>

V1.0Ar
1: SLT Protocol 修正
# 修正 ReadTCP, 因為未分離 TCP, Serial 資料層造成解碼錯誤

V1.0As
1: 增加 Repeat Tray Yield Rate

V1.0At
1: 在 Setup Page, TrayMapSetting, 如果在啟動Repeat Tray的情況下
啟動 TrayMapSetting, 會轉為 Repeat Tray
2: 







 

