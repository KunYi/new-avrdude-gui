//---------------------------------------------------------------------------
//
// Name:        MainDlg.h
// Author:      ...
// Created:     11/23/2004
// Copyright:
//
//---------------------------------------------------------------------------
#ifndef __MAINDLG_HPP_
#define __MAINDLG_HPP_


#ifndef WX_PRECOMP
    #include "wx/wx.h"
#endif



////Header Include Start
#include <wx/filedlg.h>
#include <wx/listbox.h>
#include <wx/checkbox.h>
#include <wx/statbox.h>
#include <wx/combobox.h>
#include <wx/button.h>
#include <wx/textctrl.h>
#include <wx/stattext.h>
////Header Include End

#include <wx/dialog.h>
#include <wx/file.h>

#include <wx/process.h>

#include <wx/config.h>      //(to let wxWidgets choose a wxConfig class for your platform)
#include <wx/confbase.h>    //(base config class)
#include <wx/fileconf.h>    //(wxFileConfig class)
//#include <wx/msw/regconf.h> //(wxRegConfig class)
//#include <wx/msw/iniconf.h> //(wxIniConfig class)

////GUI Control ID Start
#define ID_BTNABOUT 1199
#define ID_LBXOUTPUT 1198
#define ID_CHKLPTPOWERON 1197
#define ID_EDTCMDLINE 1196
#define ID_BTNEXECUTE 1194
#define ID_WXSTATICTEXT15 1192
#define ID_WXSTATICTEXT14 1191
#define ID_EDTCYCLECOUNTER 1190
#define ID_CHKCCERASE 1186
#define ID_CHKCCSET 1187
#define ID_CHKEXITVCC 1178
#define ID_CHKEXITNOVCC 1179
#define ID_CHKEXITRESET 1175
#define ID_CHKEXITNORESET 1176
#define ID_CHKOPTDISABLEOUTPUT 1170
#define ID_CHKOPTDISABLEVERIFY 1173
#define ID_CHKOPTVERBOSEOUTPUT 1172
#define ID_CHKOPTTERMINAL 1171
#define ID_CHKOPTVERIFYSIGNATURE 1162
#define ID_CHKOPTDONTWRITE 1163
#define ID_CHKOPTAUTOERASE 1159
#define ID_CHKOPTCHIPERASE 1160
#define ID_WXSTATICBOX12 1157
#define ID_WXSTATICBOX11 1156
#define ID_WXSTATICBOX10 1155
#define ID_CHKWRITESIGNATURE 1151
#define ID_EDTSIGNATURE 1154
#define ID_WXSTATICTEXT13 1153
#define ID_CHKREADSIGNATURE 1152
#define ID_CHKWRITECALIBRATION 1141
#define ID_EDTCALIBRATION 1144
#define ID_WXSTATICTEXT12 1143
#define ID_CHKREADCALIBRATION 1142
#define ID_CHKWRITEEFUSE 1131
#define ID_EDTEFUSE 1134
#define ID_WXSTATICTEXT11 1133
#define ID_CHKREADEFUSE 1132
#define ID_CHKWRITELOCKFUSE 1121
#define ID_EDTLOCKFUSE 1124
#define ID_WXSTATICTEXT10 1123
#define ID_CHKREADLOCKFUSE 1122
#define ID_CHKWRITEHFUSE 1111
#define ID_EDTHFUSE 1114
#define ID_WXSTATICTEXT9 1113
#define ID_CHKREADHFUSE 1112
#define ID_WXSTATICBOX6 1104
#define ID_WXSTATICBOX9 1103
#define ID_WXSTATICBOX8 1102
#define ID_WXSTATICBOX7 1101
#define ID_WXSTATICBOX5 1099
#define ID_WXSTATICTEXT8 1098
#define ID_EDTLFUSE 1097
#define ID_CHKREADLFUSE 1096
#define ID_CHKWRITELFUSE 1095
#define ID_WXSTATICBOX4 1094
#define ID_CHKWRITEEEPROM 1087
#define ID_WXSTATICTEXT7 1093
#define ID_WXCOMBOBOX1 1092
#define ID_WXBUTTON2 1091
#define ID_WXCHECKBOX3 1090
#define ID_WXCHECKBOX2 1089
#define ID_WXEDIT2 1088
#define ID_WXSTATICBOX3 1063
#define ID_BTNSTATUSGIVEIO 1034
#define ID_BTNREMOVEGIVEIO 1033
#define ID_BTNINSTALLGIVEIO 1032
#define ID_GRPGIVEIO 1029
#define ID_WXSTATICTEXT6 1026
#define ID_CMBFLASHFORMAT 1025
#define ID_BTNOPENFLASHFILE 1024
#define ID_CHKVERIFYFLASH 1023
#define ID_CHKREADFLASH 1022
#define ID_CHKWRITEFLASH 1021
#define ID_EDTFLASHFILE 1019
#define ID_WXSTATICBOX1 1018
#define ID_CMBPORT 1017
#define ID_CMBPROGRAMMER 1016
#define ID_WXSTATICTEXT5 1013
#define ID_WXSTATICTEXT4 1012
#define ID_WXSTATICTEXT3 1011
#define ID_CMBDEVICE 1010
#define ID_WXSTATICTEXT2 1007
#define ID_WXBUTTON1 1009
#define ID_WXEDIT1 1008
#define ID_BTNOPENAVRDUDEFILE 1003
#define ID_EDTAVRDUDE 1002
#define ID_WXSTATICTEXT1 1001
////GUI Control ID End

////Dialog Style Start
	#define THIS_DIALOG_STYLE wxCAPTION | wxSYSTEM_MENU | wxMINIMIZE_BOX |  wxCLOSE_BOX
////Dialog Style End

// Define an array of process pointers used by MyFrame
class MyPipedProcess;
WX_DEFINE_ARRAY(MyPipedProcess *, MyProcessesArray);

class MainDlg : public wxDialog
{
public:
    MainDlg( wxWindow *parent, wxWindowID id = 1, const wxString &title = _T("Untitled1"),
        const wxPoint& pos = wxDefaultPosition,
        const wxSize& size = wxDefaultSize,
        long style = THIS_DIALOG_STYLE);
    virtual ~MainDlg();
public:
  ////GUI Control Declaration Start
	wxFileDialog *OpenFileDialogConfFile;
	wxFileDialog *OpenFileDialogFlash;
	wxFileDialog *OpenFileDialogEeprom;
	wxFileDialog *OpenFileDialogAvrdude;
	wxButton *btnAbout;
	wxListBox *lbxOutput;
	wxCheckBox *chkLptPowerOn;
	wxTextCtrl *edtCmdline;
	wxButton *btnExecute;
	wxStaticText *WxStaticText15;
	wxStaticText *WxStaticText14;
	wxTextCtrl *edtCycleCounter;
	wxCheckBox *chkCcErase;
	wxCheckBox *chkCcSet;
	wxCheckBox *chkExitVcc;
	wxCheckBox *chkExitNovcc;
	wxCheckBox *chkExitReset;
	wxCheckBox *chkExitNoreset;
	wxCheckBox *chkOptDisableOutput;
	wxCheckBox *chkOptDisableVerify;
	wxCheckBox *chkOptVerboseOutput;
	wxCheckBox *chkOptTerminal;
	wxCheckBox *chkOptVerifySignature;
	wxCheckBox *chkOptDontWrite;
	wxCheckBox *chkOptAutoErase;
	wxCheckBox *chkOptChipErase;
	wxStaticBox *WxStaticBox12;
	wxStaticBox *WxStaticBox11;
	wxStaticBox *WxStaticBox10;
	wxCheckBox *chkWriteSignature;
	wxTextCtrl *edtSignature;
	wxStaticText *WxStaticText13;
	wxCheckBox *chkReadSignature;
	wxCheckBox *chkWriteCalibration;
	wxTextCtrl *edtCalibration;
	wxStaticText *WxStaticText12;
	wxCheckBox *chkReadCalibration;
	wxCheckBox *chkWriteEfuse;
	wxTextCtrl *edtEfuse;
	wxStaticText *WxStaticText11;
	wxCheckBox *chkReadEfuse;
	wxCheckBox *chkWriteLockfuse;
	wxTextCtrl *edtLockfuse;
	wxStaticText *WxStaticText10;
	wxCheckBox *chkReadLockfuse;
	wxCheckBox *chkWriteHfuse;
	wxTextCtrl *edtHfuse;
	wxStaticText *WxStaticText9;
	wxCheckBox *chkReadHfuse;
	wxStaticBox *WxStaticBox6;
	wxStaticBox *WxStaticBox9;
	wxStaticBox *WxStaticBox8;
	wxStaticBox *WxStaticBox7;
	wxStaticBox *WxStaticBox5;
	wxStaticText *WxStaticText8;
	wxTextCtrl *edtLfuse;
	wxCheckBox *chkReadLfuse;
	wxCheckBox *chkWriteLfuse;
	wxStaticBox *WxStaticBox4;
	wxCheckBox *chkWriteEeprom;
	wxStaticText *WxStaticText7;
	wxComboBox *cmbEepromFormat;
	wxButton *btnOpenEepromFile;
	wxCheckBox *chkVerifyEeprom;
	wxCheckBox *chkReadEeprom;
	wxTextCtrl *edtEepromFile;
	wxStaticBox *WxStaticBox3;
	wxButton *btnStatusGiveio;
	wxButton *btnRemoveGiveio;
	wxButton *btnInstallGiveio;
	wxStaticBox *grpGiveio;
	wxStaticText *WxStaticText6;
	wxComboBox *cmbFlashFormat;
	wxButton *btnOpenFlashFile;
	wxCheckBox *chkVerifyFlash;
	wxCheckBox *chkReadFlash;
	wxCheckBox *chkWriteFlash;
	wxTextCtrl *edtFlashFile;
	wxStaticBox *WxStaticBox1;
	wxComboBox *cmbPort;
	wxComboBox *cmbProgrammer;
	wxStaticText *WxStaticText5;
	wxStaticText *WxStaticText4;
	wxStaticText *WxStaticText3;
	wxComboBox *cmbDevice;
	wxStaticText *WxStaticText2;
	wxButton *btnOpenConfFile;
	wxTextCtrl *edtConfFile;
	wxButton *btnOpenAvrdudeFile;
	wxTextCtrl *edtAvrdude;
	wxStaticText *WxStaticText1;
  ////GUI Control Declaration End

private:
    DECLARE_EVENT_TABLE()
    short int m_ControlsCreated;
    MyProcessesArray m_running;
    wxArrayString    m_arrayStringProgPara;
    wxArrayString    m_arrayStringPort;
    wxArrayString    m_arrayStringDevice;

public:
    void MainDlgClose(wxCloseEvent& event);
    void MainDlgInit(wxInitDialogEvent& event);
    void CreateGUIControls(void);
    void ChangeSettings(wxCommandEvent& event);
    void SelectAvrdude(wxCommandEvent& event);
    void SelectConfFile(wxCommandEvent& event);
    void SelectFlash(wxCommandEvent& event);
    void SelectEeprom(wxCommandEvent& event);
    void InstallGiveio(wxCommandEvent& event);
    void RemoveGiveio(wxCommandEvent& event);
    void StatusGiveio(wxCommandEvent& event);
    void LptPowerOn(wxCommandEvent& event);
    void Execute(wxCommandEvent& event);
    void ExecWithRedirect(const wxString& cmd, bool sync = true);
    void ShowOutput(const wxArrayString& output);
    void LoadSettings(void);
    void SaveSettings(void);
    void BuildCmdLine(void);
	void WxbtnAboutClick(wxCommandEvent& event);
};


#endif
 
 
 
 
