; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CLEDFontDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "LEDFont.h"

ClassCount=3
Class1=CLEDFontApp
Class2=CLEDFontDlg
Class3=CAboutDlg

ResourceCount=3
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Resource3=IDD_LEDFONT_DIALOG

[CLS:CLEDFontApp]
Type=0
HeaderFile=LEDFont.h
ImplementationFile=LEDFont.cpp
Filter=N

[CLS:CLEDFontDlg]
Type=0
HeaderFile=LEDFontDlg.h
ImplementationFile=LEDFontDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=IDC_STATUS

[CLS:CAboutDlg]
Type=0
HeaderFile=LEDFontDlg.h
ImplementationFile=LEDFontDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_LEDFONT_DIALOG]
Type=1
Class=CLEDFontDlg
ControlCount=6
Control1=IDC_BUTTON_LED,button,1342242816
Control2=IDC_EDIT_DATA,edit,1350631552
Control3=IDC_STATIC,static,1342308354
Control4=IDC_STATIC_LED,static,1342308352
Control5=IDC_BUTTON_LED_FONT,button,1342242816
Control6=IDC_STATUS,static,1342308352

