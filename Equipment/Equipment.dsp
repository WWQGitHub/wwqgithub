# Microsoft Developer Studio Project File - Name="Equipment" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=Equipment - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Equipment.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Equipment.mak" CFG="Equipment - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Equipment - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "Equipment - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Equipment - Win32 Release"

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
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# SUBTRACT CPP /WX /Fr
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# SUBTRACT MTL /Oicf
# ADD BASE RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /profile /map /debug /machine:I386

!ELSEIF  "$(CFG)" == "Equipment - Win32 Debug"

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
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "Equipment - Win32 Release"
# Name "Equipment - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\_recordset.cpp
# End Source File
# Begin Source File

SOURCE=.\AddEquip.cpp
# End Source File
# Begin Source File

SOURCE=.\AddKinds.cpp
# End Source File
# Begin Source File

SOURCE=.\adodc.cpp
# End Source File
# Begin Source File

SOURCE=.\column.cpp
# End Source File
# Begin Source File

SOURCE=.\columns.cpp
# End Source File
# Begin Source File

SOURCE=.\CustomBar.cpp
# End Source File
# Begin Source File

SOURCE=.\DataBackup.cpp
# End Source File
# Begin Source File

SOURCE=.\dataformatdisp.cpp
# End Source File
# Begin Source File

SOURCE=.\datagrid.cpp
# End Source File
# Begin Source File

SOURCE=.\DataManage1.cpp
# End Source File
# Begin Source File

SOURCE=.\DataRestore.cpp
# End Source File
# Begin Source File

SOURCE=.\DeleteEquipment.cpp
# End Source File
# Begin Source File

SOURCE=.\Depre.cpp
# End Source File
# Begin Source File

SOURCE=.\EquipKind.cpp
# End Source File
# Begin Source File

SOURCE=.\Equipment.cpp
# End Source File
# Begin Source File

SOURCE=.\Equipment.rc
# End Source File
# Begin Source File

SOURCE=.\EquipmentDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\field.cpp
# End Source File
# Begin Source File

SOURCE=.\fields.cpp
# End Source File
# Begin Source File

SOURCE=.\font.cpp
# End Source File
# Begin Source File

SOURCE=.\NumberEdit.cpp
# End Source File
# Begin Source File

SOURCE=.\picture.cpp
# End Source File
# Begin Source File

SOURCE=.\properties.cpp
# End Source File
# Begin Source File

SOURCE=.\property.cpp
# End Source File
# Begin Source File

SOURCE=.\ReduceEquip.cpp
# End Source File
# Begin Source File

SOURCE=.\ReduceKinds.cpp
# End Source File
# Begin Source File

SOURCE=.\selbookmarks.cpp
# End Source File
# Begin Source File

SOURCE=.\split.cpp
# End Source File
# Begin Source File

SOURCE=.\splits.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\stddataformatsdisp.cpp
# End Source File
# Begin Source File

SOURCE=.\SysIni.cpp
# End Source File
# Begin Source File

SOURCE=.\UnDepre.cpp
# End Source File
# Begin Source File

SOURCE=.\UpdateEquip.cpp
# End Source File
# Begin Source File

SOURCE=.\UseState.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\_recordset.h
# End Source File
# Begin Source File

SOURCE=.\AddEquip.h
# End Source File
# Begin Source File

SOURCE=.\AddKinds.h
# End Source File
# Begin Source File

SOURCE=.\adodc.h
# End Source File
# Begin Source File

SOURCE=.\column.h
# End Source File
# Begin Source File

SOURCE=.\columns.h
# End Source File
# Begin Source File

SOURCE=.\CustomBar.h
# End Source File
# Begin Source File

SOURCE=.\DataBackup.h
# End Source File
# Begin Source File

SOURCE=.\dataformatdisp.h
# End Source File
# Begin Source File

SOURCE=.\datagrid.h
# End Source File
# Begin Source File

SOURCE=.\DataManage1.h
# End Source File
# Begin Source File

SOURCE=.\DataRestore.h
# End Source File
# Begin Source File

SOURCE=.\DeleteEquipment.h
# End Source File
# Begin Source File

SOURCE=.\Depre.h
# End Source File
# Begin Source File

SOURCE=.\EquipKind.h
# End Source File
# Begin Source File

SOURCE=.\Equipment.h
# End Source File
# Begin Source File

SOURCE=.\EquipmentDlg.h
# End Source File
# Begin Source File

SOURCE=.\field.h
# End Source File
# Begin Source File

SOURCE=.\fields.h
# End Source File
# Begin Source File

SOURCE=.\font.h
# End Source File
# Begin Source File

SOURCE=.\NumberEdit.h
# End Source File
# Begin Source File

SOURCE=.\picture.h
# End Source File
# Begin Source File

SOURCE=.\properties.h
# End Source File
# Begin Source File

SOURCE=.\property.h
# End Source File
# Begin Source File

SOURCE=.\ReduceEquip.h
# End Source File
# Begin Source File

SOURCE=.\ReduceKinds.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\selbookmarks.h
# End Source File
# Begin Source File

SOURCE=.\split.h
# End Source File
# Begin Source File

SOURCE=.\splits.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\stddataformatsdisp.h
# End Source File
# Begin Source File

SOURCE=.\SysIni.h
# End Source File
# Begin Source File

SOURCE=.\UnDepre.h
# End Source File
# Begin Source File

SOURCE=.\UpdateEquip.h
# End Source File
# Begin Source File

SOURCE=.\UseState.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\02.ico

!IF  "$(CFG)" == "Equipment - Win32 Release"

# PROP Ignore_Default_Tool 1

!ELSEIF  "$(CFG)" == "Equipment - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\res\35.ico

!IF  "$(CFG)" == "Equipment - Win32 Release"

# PROP Ignore_Default_Tool 1

!ELSEIF  "$(CFG)" == "Equipment - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\res\51.ico

!IF  "$(CFG)" == "Equipment - Win32 Release"

# PROP Ignore_Default_Tool 1

!ELSEIF  "$(CFG)" == "Equipment - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\res\63.ico

!IF  "$(CFG)" == "Equipment - Win32 Release"

# PROP Ignore_Default_Tool 1

!ELSEIF  "$(CFG)" == "Equipment - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\res\65.ico

!IF  "$(CFG)" == "Equipment - Win32 Release"

# PROP Ignore_Default_Tool 1

!ELSEIF  "$(CFG)" == "Equipment - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\res\a.ico

!IF  "$(CFG)" == "Equipment - Win32 Release"

# PROP Ignore_Default_Tool 1

!ELSEIF  "$(CFG)" == "Equipment - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=".\res\BE EDIT.ICO"

!IF  "$(CFG)" == "Equipment - Win32 Release"

# PROP Ignore_Default_Tool 1

!ELSEIF  "$(CFG)" == "Equipment - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\res\bitmap2.bmp

!IF  "$(CFG)" == "Equipment - Win32 Release"

# PROP Ignore_Default_Tool 1

!ELSEIF  "$(CFG)" == "Equipment - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\res\bitmap4.bmp

!IF  "$(CFG)" == "Equipment - Win32 Release"

# PROP Ignore_Default_Tool 1

!ELSEIF  "$(CFG)" == "Equipment - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\res\bitmap5.bmp

!IF  "$(CFG)" == "Equipment - Win32 Release"

# PROP Ignore_Default_Tool 1

!ELSEIF  "$(CFG)" == "Equipment - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\res\car1.bmp

!IF  "$(CFG)" == "Equipment - Win32 Release"

# PROP Ignore_Default_Tool 1

!ELSEIF  "$(CFG)" == "Equipment - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\res\desktop.bmp

!IF  "$(CFG)" == "Equipment - Win32 Release"

# PROP Ignore_Default_Tool 1

!ELSEIF  "$(CFG)" == "Equipment - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\res\Equipment.ico

!IF  "$(CFG)" == "Equipment - Win32 Release"

# PROP Ignore_Default_Tool 1

!ELSEIF  "$(CFG)" == "Equipment - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\res\Equipment.rc2

!IF  "$(CFG)" == "Equipment - Win32 Release"

# PROP Ignore_Default_Tool 1

!ELSEIF  "$(CFG)" == "Equipment - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\res\f.bmp

!IF  "$(CFG)" == "Equipment - Win32 Release"

# PROP Ignore_Default_Tool 1

!ELSEIF  "$(CFG)" == "Equipment - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=".\res\GR 027.ico"

!IF  "$(CFG)" == "Equipment - Win32 Release"

# PROP Ignore_Default_Tool 1

!ELSEIF  "$(CFG)" == "Equipment - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\res\HOxmas1.ico

!IF  "$(CFG)" == "Equipment - Win32 Release"

# PROP Ignore_Default_Tool 1

!ELSEIF  "$(CFG)" == "Equipment - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\res\HOxmas12.ico

!IF  "$(CFG)" == "Equipment - Win32 Release"

# PROP Ignore_Default_Tool 1

!ELSEIF  "$(CFG)" == "Equipment - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\res\HOxmas33.ico

!IF  "$(CFG)" == "Equipment - Win32 Release"

# PROP Ignore_Default_Tool 1

!ELSEIF  "$(CFG)" == "Equipment - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\res\HOxmas34.ico

!IF  "$(CFG)" == "Equipment - Win32 Release"

# PROP Ignore_Default_Tool 1

!ELSEIF  "$(CFG)" == "Equipment - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\res\HTMLDOC.ICO

!IF  "$(CFG)" == "Equipment - Win32 Release"

# PROP Ignore_Default_Tool 1

!ELSEIF  "$(CFG)" == "Equipment - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\res\ico00001.ico

!IF  "$(CFG)" == "Equipment - Win32 Release"

# PROP Ignore_Default_Tool 1

!ELSEIF  "$(CFG)" == "Equipment - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\res\ico00002.ico

!IF  "$(CFG)" == "Equipment - Win32 Release"

# PROP Ignore_Default_Tool 1

!ELSEIF  "$(CFG)" == "Equipment - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\res\ico00003.ico

!IF  "$(CFG)" == "Equipment - Win32 Release"

# PROP Ignore_Default_Tool 1

!ELSEIF  "$(CFG)" == "Equipment - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\res\icon1.ico

!IF  "$(CFG)" == "Equipment - Win32 Release"

# PROP Ignore_Default_Tool 1

!ELSEIF  "$(CFG)" == "Equipment - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\res\icon10.ico

!IF  "$(CFG)" == "Equipment - Win32 Release"

# PROP Ignore_Default_Tool 1

!ELSEIF  "$(CFG)" == "Equipment - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\res\icon11.ico

!IF  "$(CFG)" == "Equipment - Win32 Release"

# PROP Ignore_Default_Tool 1

!ELSEIF  "$(CFG)" == "Equipment - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\res\icon12.ico

!IF  "$(CFG)" == "Equipment - Win32 Release"

# PROP Ignore_Default_Tool 1

!ELSEIF  "$(CFG)" == "Equipment - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\res\icon2.ico

!IF  "$(CFG)" == "Equipment - Win32 Release"

# PROP Ignore_Default_Tool 1

!ELSEIF  "$(CFG)" == "Equipment - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\res\icon3.ico

!IF  "$(CFG)" == "Equipment - Win32 Release"

# PROP Ignore_Default_Tool 1

!ELSEIF  "$(CFG)" == "Equipment - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\res\icon4.ico

!IF  "$(CFG)" == "Equipment - Win32 Release"

# PROP Ignore_Default_Tool 1

!ELSEIF  "$(CFG)" == "Equipment - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\res\icon5.ico

!IF  "$(CFG)" == "Equipment - Win32 Release"

# PROP Ignore_Default_Tool 1

!ELSEIF  "$(CFG)" == "Equipment - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\res\icon6.ico

!IF  "$(CFG)" == "Equipment - Win32 Release"

# PROP Ignore_Default_Tool 1

!ELSEIF  "$(CFG)" == "Equipment - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\res\icon7.ico

!IF  "$(CFG)" == "Equipment - Win32 Release"

# PROP Ignore_Default_Tool 1

!ELSEIF  "$(CFG)" == "Equipment - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\res\icon8.ico

!IF  "$(CFG)" == "Equipment - Win32 Release"

# PROP Ignore_Default_Tool 1

!ELSEIF  "$(CFG)" == "Equipment - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\res\icon9.ico

!IF  "$(CFG)" == "Equipment - Win32 Release"

# PROP Ignore_Default_Tool 1

!ELSEIF  "$(CFG)" == "Equipment - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\res\temp.bmp

!IF  "$(CFG)" == "Equipment - Win32 Release"

# PROP Ignore_Default_Tool 1

!ELSEIF  "$(CFG)" == "Equipment - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\res\toolbar1.bmp

!IF  "$(CFG)" == "Equipment - Win32 Release"

# PROP Ignore_Default_Tool 1

!ELSEIF  "$(CFG)" == "Equipment - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\res\toolbar1.ico

!IF  "$(CFG)" == "Equipment - Win32 Release"

# PROP Ignore_Default_Tool 1

!ELSEIF  "$(CFG)" == "Equipment - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\res\toolbar2.bmp

!IF  "$(CFG)" == "Equipment - Win32 Release"

# PROP Ignore_Default_Tool 1

!ELSEIF  "$(CFG)" == "Equipment - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\res\toolbar2.ico

!IF  "$(CFG)" == "Equipment - Win32 Release"

# PROP Ignore_Default_Tool 1

!ELSEIF  "$(CFG)" == "Equipment - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\res\toolbar3.ico

!IF  "$(CFG)" == "Equipment - Win32 Release"

# PROP Ignore_Default_Tool 1

!ELSEIF  "$(CFG)" == "Equipment - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\res\toolbar4.ico

!IF  "$(CFG)" == "Equipment - Win32 Release"

# PROP Ignore_Default_Tool 1

!ELSEIF  "$(CFG)" == "Equipment - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\res\toolbar5.ico

!IF  "$(CFG)" == "Equipment - Win32 Release"

# PROP Ignore_Default_Tool 1

!ELSEIF  "$(CFG)" == "Equipment - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\res\toolbar6.ico

!IF  "$(CFG)" == "Equipment - Win32 Release"

# PROP Ignore_Default_Tool 1

!ELSEIF  "$(CFG)" == "Equipment - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\res\toolbar7.ico

!IF  "$(CFG)" == "Equipment - Win32 Release"

# PROP Ignore_Default_Tool 1

!ELSEIF  "$(CFG)" == "Equipment - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\res\toolbar8.ico

!IF  "$(CFG)" == "Equipment - Win32 Release"

# PROP Ignore_Default_Tool 1

!ELSEIF  "$(CFG)" == "Equipment - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\res\toolbar9.ico

!IF  "$(CFG)" == "Equipment - Win32 Release"

# PROP Ignore_Default_Tool 1

!ELSEIF  "$(CFG)" == "Equipment - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=".\res\删除.ico"

!IF  "$(CFG)" == "Equipment - Win32 Release"

# PROP Ignore_Default_Tool 1

!ELSEIF  "$(CFG)" == "Equipment - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=".\res\未标题-1 拷贝.bmp"

!IF  "$(CFG)" == "Equipment - Win32 Release"

# PROP Ignore_Default_Tool 1

!ELSEIF  "$(CFG)" == "Equipment - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=".\res\资产设备管理系统主界面.bmp"

!IF  "$(CFG)" == "Equipment - Win32 Release"

# PROP Ignore_Default_Tool 1

!ELSEIF  "$(CFG)" == "Equipment - Win32 Debug"

!ENDIF 

# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
# Section Equipment : {99FF4676-FFC3-11D0-BD02-00C04FC2FB86}
# 	2:5:Class:CStdDataFormatsDisp
# 	2:10:HeaderFile:stddataformatsdisp.h
# 	2:8:ImplFile:stddataformatsdisp.cpp
# End Section
# Section Equipment : {CDE57A4F-8B86-11D0-B3C6-00A0C90AEA82}
# 	2:5:Class:CColumn
# 	2:10:HeaderFile:column.h
# 	2:8:ImplFile:column.cpp
# End Section
# Section Equipment : {47A738F1-7FAF-11D0-B148-00A0C922E820}
# 	2:5:Class:CAdodc
# 	2:10:HeaderFile:adodc.h
# 	2:8:ImplFile:adodc.cpp
# End Section
# Section Equipment : {CDE57A43-8B86-11D0-B3C6-00A0C90AEA82}
# 	2:21:DefaultSinkHeaderFile:datagrid.h
# 	2:16:DefaultSinkClass:CDataGrid
# End Section
# Section Equipment : {CDE57A53-8B86-11D0-B3C6-00A0C90AEA82}
# 	2:5:Class:CSplits
# 	2:10:HeaderFile:splits.h
# 	2:8:ImplFile:splits.cpp
# End Section
# Section Equipment : {BEF6E003-A874-101A-8BBA-00AA00300CAB}
# 	2:5:Class:COleFont
# 	2:10:HeaderFile:font.h
# 	2:8:ImplFile:font.cpp
# End Section
# Section Equipment : {00000569-0000-0010-8000-00AA006D2EA4}
# 	2:5:Class:CField
# 	2:10:HeaderFile:field.h
# 	2:8:ImplFile:field.cpp
# End Section
# Section Equipment : {00000504-0000-0010-8000-00AA006D2EA4}
# 	2:5:Class:CProperties
# 	2:10:HeaderFile:properties.h
# 	2:8:ImplFile:properties.cpp
# End Section
# Section Equipment : {00000564-0000-0010-8000-00AA006D2EA4}
# 	2:5:Class:CFields
# 	2:10:HeaderFile:fields.h
# 	2:8:ImplFile:fields.cpp
# End Section
# Section Equipment : {CDE57A52-8B86-11D0-B3C6-00A0C90AEA82}
# 	2:5:Class:CSelBookmarks
# 	2:10:HeaderFile:selbookmarks.h
# 	2:8:ImplFile:selbookmarks.cpp
# End Section
# Section Equipment : {7BF80981-BF32-101A-8BBB-00AA00300CAB}
# 	2:5:Class:CPicture
# 	2:10:HeaderFile:picture.h
# 	2:8:ImplFile:picture.cpp
# End Section
# Section Equipment : {67397AA3-7FB1-11D0-B148-00A0C922E820}
# 	2:21:DefaultSinkHeaderFile:adodc.h
# 	2:16:DefaultSinkClass:CAdodc
# End Section
# Section Equipment : {00000503-0000-0010-8000-00AA006D2EA4}
# 	2:5:Class:CProperty
# 	2:10:HeaderFile:property.h
# 	2:8:ImplFile:property.cpp
# End Section
# Section Equipment : {CDE57A41-8B86-11D0-B3C6-00A0C90AEA82}
# 	2:5:Class:CDataGrid
# 	2:10:HeaderFile:datagrid.h
# 	2:8:ImplFile:datagrid.cpp
# End Section
# Section Equipment : {CDE57A50-8B86-11D0-B3C6-00A0C90AEA82}
# 	2:5:Class:CColumns
# 	2:10:HeaderFile:columns.h
# 	2:8:ImplFile:columns.cpp
# End Section
# Section Equipment : {CDE57A54-8B86-11D0-B3C6-00A0C90AEA82}
# 	2:5:Class:CSplit
# 	2:10:HeaderFile:split.h
# 	2:8:ImplFile:split.cpp
# End Section
# Section Equipment : {00000556-0000-0010-8000-00AA006D2EA4}
# 	2:5:Class:C_Recordset
# 	2:10:HeaderFile:_recordset.h
# 	2:8:ImplFile:_recordset.cpp
# End Section
# Section Equipment : {E675F3F0-91B5-11D0-9484-00A0C91110ED}
# 	2:5:Class:CDataFormatDisp
# 	2:10:HeaderFile:dataformatdisp.h
# 	2:8:ImplFile:dataformatdisp.cpp
# End Section
