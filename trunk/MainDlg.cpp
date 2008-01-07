//---------------------------------------------------------------------------
//
// Name:        MainDlg.cpp
// Author:      ...
// Created:     11/23/2004
// Copyright:
//
//---------------------------------------------------------------------------

#ifdef __GNUG__
  #pragma implementation "MainDlg.cpp"
#endif

/* for compilers that support precompilation
   includes "wx/wx.h" */

#include "wx/wxprec.h"
#include "wx/XML/xml.h"

#ifdef __BORLANDC__
  #pragma hdrstop
#endif

#include "MainDlg.h"

////Header Include Start
#include "MainDlg_XPM.xpm"
////Header Include End

#ifdef __WXMSW__
const char * ConfigFilenameString = "avrdude-gui";
#else
const char * ConfigFilenameString = "/.avrdude-guirc";
#endif


//----------------------------------------------------------------------------
// MainDlg
//----------------------------------------------------------------------------

  ////Event Table Start
BEGIN_EVENT_TABLE(MainDlg,wxDialog)
	////Manual Code Start
	////Manual Code End
	
	EVT_CLOSE(MainDlg::MainDlgClose)
	EVT_INIT_DIALOG(MainDlg::MainDlgInit)
	EVT_BUTTON(ID_BTNABOUT,MainDlg::WxbtnAboutClick)
	EVT_CHECKBOX(ID_CHKLPTPOWERON,MainDlg::LptPowerOn)
	EVT_BUTTON(ID_BTNEXECUTE,MainDlg::Execute)
	
	EVT_TEXT(ID_EDTCYCLECOUNTER,MainDlg::ChangeSettings)
	EVT_CHECKBOX(ID_CHKCCERASE,MainDlg::ChangeSettings)
	EVT_CHECKBOX(ID_CHKCCSET,MainDlg::ChangeSettings)
	EVT_CHECKBOX(ID_CHKEXITVCC,MainDlg::ChangeSettings)
	EVT_CHECKBOX(ID_CHKEXITNOVCC,MainDlg::ChangeSettings)
	EVT_CHECKBOX(ID_CHKEXITRESET,MainDlg::ChangeSettings)
	EVT_CHECKBOX(ID_CHKEXITNORESET,MainDlg::ChangeSettings)
	EVT_CHECKBOX(ID_CHKOPTDISABLEOUTPUT,MainDlg::ChangeSettings)
	EVT_CHECKBOX(ID_CHKOPTDISABLEVERIFY,MainDlg::ChangeSettings)
	EVT_CHECKBOX(ID_CHKOPTVERBOSEOUTPUT,MainDlg::ChangeSettings)
	EVT_CHECKBOX(ID_CHKOPTTERMINAL,MainDlg::ChangeSettings)
	EVT_CHECKBOX(ID_CHKOPTVERIFYSIGNATURE,MainDlg::ChangeSettings)
	EVT_CHECKBOX(ID_CHKOPTDONTWRITE,MainDlg::ChangeSettings)
	EVT_CHECKBOX(ID_CHKOPTAUTOERASE,MainDlg::ChangeSettings)
	EVT_CHECKBOX(ID_CHKOPTCHIPERASE,MainDlg::ChangeSettings)
	EVT_CHECKBOX(ID_CHKWRITESIGNATURE,MainDlg::ChangeSettings)
	
	EVT_TEXT(ID_EDTSIGNATURE,MainDlg::ChangeSettings)
	EVT_CHECKBOX(ID_CHKREADSIGNATURE,MainDlg::ChangeSettings)
	EVT_CHECKBOX(ID_CHKWRITECALIBRATION,MainDlg::ChangeSettings)
	
	EVT_TEXT(ID_EDTCALIBRATION,MainDlg::ChangeSettings)
	EVT_CHECKBOX(ID_CHKREADCALIBRATION,MainDlg::ChangeSettings)
	EVT_CHECKBOX(ID_CHKWRITEEFUSE,MainDlg::ChangeSettings)
	
	EVT_TEXT(ID_EDTEFUSE,MainDlg::ChangeSettings)
	EVT_CHECKBOX(ID_CHKREADEFUSE,MainDlg::ChangeSettings)
	EVT_CHECKBOX(ID_CHKWRITELOCKFUSE,MainDlg::ChangeSettings)
	
	EVT_TEXT(ID_EDTLOCKFUSE,MainDlg::ChangeSettings)
	EVT_CHECKBOX(ID_CHKREADLOCKFUSE,MainDlg::ChangeSettings)
	EVT_CHECKBOX(ID_CHKWRITEHFUSE,MainDlg::ChangeSettings)
	
	EVT_TEXT(ID_EDTHFUSE,MainDlg::ChangeSettings)
	EVT_CHECKBOX(ID_CHKREADHFUSE,MainDlg::ChangeSettings)
	
	EVT_TEXT(ID_EDTLFUSE,MainDlg::ChangeSettings)
	EVT_CHECKBOX(ID_CHKREADLFUSE,MainDlg::ChangeSettings)
	EVT_CHECKBOX(ID_CHKWRITELFUSE,MainDlg::ChangeSettings)
	EVT_CHECKBOX(ID_CHKWRITEEEPROM,MainDlg::ChangeSettings)
	
	EVT_TEXT(ID_WXCOMBOBOX1,MainDlg::ChangeSettings)
	EVT_BUTTON(ID_WXBUTTON2,MainDlg::SelectEeprom)
	EVT_CHECKBOX(ID_WXCHECKBOX3,MainDlg::ChangeSettings)
	EVT_CHECKBOX(ID_WXCHECKBOX2,MainDlg::ChangeSettings)
	
	EVT_TEXT(ID_WXEDIT2,MainDlg::ChangeSettings)
	EVT_BUTTON(ID_BTNSTATUSGIVEIO,MainDlg::StatusGiveio)
	EVT_BUTTON(ID_BTNREMOVEGIVEIO,MainDlg::RemoveGiveio)
	EVT_BUTTON(ID_BTNINSTALLGIVEIO,MainDlg::InstallGiveio)
	
	EVT_TEXT(ID_CMBFLASHFORMAT,MainDlg::ChangeSettings)
	EVT_BUTTON(ID_BTNOPENFLASHFILE,MainDlg::SelectFlash)
	EVT_CHECKBOX(ID_CHKVERIFYFLASH,MainDlg::ChangeSettings)
	EVT_CHECKBOX(ID_CHKREADFLASH,MainDlg::ChangeSettings)
	EVT_CHECKBOX(ID_CHKWRITEFLASH,MainDlg::ChangeSettings)
	
	EVT_TEXT(ID_EDTFLASHFILE,MainDlg::ChangeSettings)
	
	EVT_TEXT(ID_CMBPORT,MainDlg::ChangeSettings)
	
	EVT_TEXT(ID_CMBPROGRAMMER,MainDlg::ChangeSettings)
	
	EVT_TEXT(ID_CMBDEVICE,MainDlg::ChangeSettings)
	EVT_BUTTON(ID_WXBUTTON1,MainDlg::SelectConfFile)
	
	EVT_TEXT(ID_WXEDIT1,MainDlg::ChangeSettings)
	EVT_BUTTON(ID_BTNOPENAVRDUDEFILE,MainDlg::SelectAvrdude)
	
	EVT_TEXT(ID_EDTAVRDUDE,MainDlg::ChangeSettings)
END_EVENT_TABLE()
    ////Event Table End



MainDlg::MainDlg( wxWindow *parent, wxWindowID id, const wxString &title, const wxPoint &position, const wxSize& size, long style )
    : wxDialog( parent, id, title, position, size, style)
{
  CreateGUIControls();
  BuildCmdLine();
}

MainDlg::~MainDlg()
{
} 

void MainDlg::CreateGUIControls(void)
{
    m_ControlsCreated = 0;
#ifdef __WXMSW__
//ToDo: doesn't work :(   this->SetExtraStyle(wxDIALOG_EX_CONTEXTHELP);
#endif

  ////GUI Items Creation Start
    bool bHaveConf = false;
    wxXmlDocument doc;
    wxXmlNode *ProgList = NULL;
    wxXmlNode *MCUList = NULL;
    wxXmlNode *PortList = NULL;
   
    bHaveConf =doc.Load(wxT("avrdude-gui.conf"));
    if (bHaveConf)
    {
        bHaveConf = (doc.GetRoot()->GetName() == wxT("Configuration"));
        
        if (!bHaveConf)
          wxMessageBox(wxT("Can't find Root \"Configuration\"\n"));          
    }
   
    if (bHaveConf)
    {
        wxXmlNode *child = doc.GetRoot()->GetChildren();
        
        // find programer
        while(child) {
            if (child->GetName() == wxT("ProgrammerList")) {
                ProgList = child;
            } else if (child->GetName() == wxT("MCUList")) {
                MCUList = child;
            } else if (child->GetName() == wxT("PortList")) {
                PortList = child;
            }
            child = child->GetNext();
        }
        
        if (ProgList == NULL) {
            wxMessageBox(wxT("Can't find ProgrammerList option\n"));
        }
        
        if (MCUList == NULL) {
            wxMessageBox(wxT("Can't find MCUList option\n"));
        }
        
        if (PortList == NULL) {
            wxMessageBox(wxT("Can't find PortList option\n"));
        }
    }
        
    
	this->SetSize(8,8,600,710);
	this->SetTitle(wxT("avrdude gui v0.2.2"));
	this->Center();
	wxIcon MainDlg_ICON (MainDlg_XPM);
	this->SetIcon(MainDlg_XPM);
	this->SetToolTip(wxT(_("0")));
	

	OpenFileDialogConfFile =  new wxFileDialog(this, "Choose location of configuration file" , "" , "" , "avrdude conf file (*.*) | *.*", wxOPEN);

	OpenFileDialogFlash =  new wxFileDialog(this, "Choose flash file" , "" , "" , "Flash file (*.hex,*.bin) | *.hex;*.bin", wxOPEN);

	OpenFileDialogEeprom =  new wxFileDialog(this, "Choose EEPROM file" , "" , "" , "Eeprom file (*.hex,*.bin) | *.hex;*.bin", wxOPEN);

	OpenFileDialogAvrdude =  new wxFileDialog(this, "Choose location of avrdude" , "" , "avrdude" , "avrdude executable (avrdude.*) | avrdude.*", wxOPEN);

	btnAbout =  new wxButton(this, ID_BTNABOUT, _("?") , wxPoint(569,2),wxSize(17,18) );

	lbxOutput =  new wxListBox(this, ID_LBXOUTPUT ,wxPoint(4,559),wxSize(585,121), (wxArrayString) NULL  );
	lbxOutput->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_BTNFACE));

	chkLptPowerOn =  new wxCheckBox(this, ID_CHKLPTPOWERON, _("LPT Power On") , wxPoint(365,113),wxSize(100,23) );

	edtCmdline =  new wxTextCtrl(this, ID_EDTCMDLINE, _("") , wxPoint(4,515),wxSize(495,21)  , wxTE_RICH);
	edtCmdline->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_BTNFACE));

	btnExecute =  new wxButton(this, ID_BTNEXECUTE, _("Execute") , wxPoint(499,513),wxSize(89,23) );

	WxStaticText15 =  new wxStaticText(this, ID_WXSTATICTEXT15 ,_("Output:") ,wxPoint(12,542),wxSize(39,17)  );

	WxStaticText14 =  new wxStaticText(this, ID_WXSTATICTEXT14 ,_("Command line:") ,wxPoint(12,498),wxSize(73,17)  );

	edtCycleCounter =  new wxTextCtrl(this, ID_EDTCYCLECOUNTER, _("0") , wxPoint(539,467),wxSize(34,21) );

	chkCcErase =  new wxCheckBox(this, ID_CHKCCERASE, _("-y erase cycle counter") , wxPoint(406,454),wxSize(126,17) );

	chkCcSet =  new wxCheckBox(this, ID_CHKCCSET, _("-Y Set counter to:") , wxPoint(406,469),wxSize(119,17) );

	chkExitVcc =  new wxCheckBox(this, ID_CHKEXITVCC, _("Vcc") , wxPoint(504,391),wxSize(75,17) );

	chkExitNovcc =  new wxCheckBox(this, ID_CHKEXITNOVCC, _("No Vcc") , wxPoint(504,407),wxSize(74,17) );

	chkExitReset =  new wxCheckBox(this, ID_CHKEXITRESET, _("Reset") , wxPoint(406,391),wxSize(75,17) );

	chkExitNoreset =  new wxCheckBox(this, ID_CHKEXITNORESET, _("No reset") , wxPoint(406,407),wxSize(75,17) );

	chkOptDisableOutput =  new wxCheckBox(this, ID_CHKOPTDISABLEOUTPUT, _("-q Disable process bar output") , wxPoint(211,391),wxSize(176,17) );

	chkOptDisableVerify =  new wxCheckBox(this, ID_CHKOPTDISABLEVERIFY, _("-V Disable verify check") , wxPoint(211,439),wxSize(177,17) );

	chkOptVerboseOutput =  new wxCheckBox(this, ID_CHKOPTVERBOSEOUTPUT, _("-v Enable verbose output") , wxPoint(211,423),wxSize(175,17) );

	chkOptTerminal =  new wxCheckBox(this, ID_CHKOPTTERMINAL, _("-t Terminal mode") , wxPoint(211,407),wxSize(175,17) );

	chkOptVerifySignature =  new wxCheckBox(this, ID_CHKOPTVERIFYSIGNATURE, _("-F Verify the device signature") , wxPoint(12,423),wxSize(185,17) );

	chkOptDontWrite =  new wxCheckBox(this, ID_CHKOPTDONTWRITE, _("-n Don't write to the device") , wxPoint(12,439),wxSize(185,17) );

	chkOptAutoErase =  new wxCheckBox(this, ID_CHKOPTAUTOERASE, _("-D Disable auto erase for flash") , wxPoint(12,391),wxSize(185,17) );

	chkOptChipErase =  new wxCheckBox(this, ID_CHKOPTCHIPERASE, _("-e Perform a chip erase") , wxPoint(12,407),wxSize(185,17) );

	WxStaticBox12 =  new wxStaticBox(this, ID_WXSTATICBOX12,_("Cycle counter"),wxPoint(400,437),wxSize(188,56)  );

	WxStaticBox11 =  new wxStaticBox(this, ID_WXSTATICBOX11,_("-E Exitmode"),wxPoint(400,375),wxSize(188,56)  );

	WxStaticBox10 =  new wxStaticBox(this, ID_WXSTATICBOX10,_("Options"),wxPoint(4,375),wxSize(387,118)  );

	chkWriteSignature =  new wxCheckBox(this, ID_CHKWRITESIGNATURE, _("Write") , wxPoint(504,307),wxSize(55,17) );

	edtSignature =  new wxTextCtrl(this, ID_EDTSIGNATURE, _("000000") , wxPoint(529,341),wxSize(44,21) );

	WxStaticText13 =  new wxStaticText(this, ID_WXSTATICTEXT13 ,_("0x") ,wxPoint(514,344),wxSize(15,17)  );

	chkReadSignature =  new wxCheckBox(this, ID_CHKREADSIGNATURE, _("Read") , wxPoint(504,323),wxSize(55,17) );

	chkWriteCalibration =  new wxCheckBox(this, ID_CHKWRITECALIBRATION, _("Write") , wxPoint(406,307),wxSize(55,17) );

	edtCalibration =  new wxTextCtrl(this, ID_EDTCALIBRATION, _("00000000") , wxPoint(425,341),wxSize(56,21) );

	WxStaticText12 =  new wxStaticText(this, ID_WXSTATICTEXT12 ,_("0x") ,wxPoint(410,344),wxSize(15,17)  );

	chkReadCalibration =  new wxCheckBox(this, ID_CHKREADCALIBRATION, _("Read") , wxPoint(406,323),wxSize(55,17) );

	chkWriteEfuse =  new wxCheckBox(this, ID_CHKWRITEEFUSE, _("Write") , wxPoint(308,307),wxSize(55,17) );

	edtEfuse =  new wxTextCtrl(this, ID_EDTEFUSE, _("00") , wxPoint(342,341),wxSize(21,21) );

	WxStaticText11 =  new wxStaticText(this, ID_WXSTATICTEXT11 ,_("0x") ,wxPoint(327,344),wxSize(15,17)  );

	chkReadEfuse =  new wxCheckBox(this, ID_CHKREADEFUSE, _("Read") , wxPoint(308,323),wxSize(55,17) );

	chkWriteLockfuse =  new wxCheckBox(this, ID_CHKWRITELOCKFUSE, _("Write") , wxPoint(209,307),wxSize(55,17) );

	edtLockfuse =  new wxTextCtrl(this, ID_EDTLOCKFUSE, _("00") , wxPoint(243,341),wxSize(21,21) );

	WxStaticText10 =  new wxStaticText(this, ID_WXSTATICTEXT10 ,_("0x") ,wxPoint(228,344),wxSize(15,17)  );

	chkReadLockfuse =  new wxCheckBox(this, ID_CHKREADLOCKFUSE, _("Read") , wxPoint(209,323),wxSize(55,17) );

	chkWriteHfuse =  new wxCheckBox(this, ID_CHKWRITEHFUSE, _("Write") , wxPoint(110,306),wxSize(55,17) );

	edtHfuse =  new wxTextCtrl(this, ID_EDTHFUSE, _("00") , wxPoint(144,341),wxSize(21,21) );

	WxStaticText9 =  new wxStaticText(this, ID_WXSTATICTEXT9 ,_("0x") ,wxPoint(129,344),wxSize(15,17)  );

	chkReadHfuse =  new wxCheckBox(this, ID_CHKREADHFUSE, _("Read") , wxPoint(110,322),wxSize(55,17) );

	WxStaticBox6 =  new wxStaticBox(this, ID_WXSTATICBOX6,_("Lock Fuse"),wxPoint(202,290),wxSize(90,79)  );

	WxStaticBox9 =  new wxStaticBox(this, ID_WXSTATICBOX9,_("Signature"),wxPoint(498,290),wxSize(90,79)  );

	WxStaticBox8 =  new wxStaticBox(this, ID_WXSTATICBOX8,_("Calibration"),wxPoint(400,290),wxSize(90,79)  );

	WxStaticBox7 =  new wxStaticBox(this, ID_WXSTATICBOX7,_("Extended Fuse"),wxPoint(301,290),wxSize(90,79)  );

	WxStaticBox5 =  new wxStaticBox(this, ID_WXSTATICBOX5,_("High Fuse"),wxPoint(103,290),wxSize(90,79)  );

	WxStaticText8 =  new wxStaticText(this, ID_WXSTATICTEXT8 ,_("0x") ,wxPoint(31,344),wxSize(15,17)  );

	edtLfuse =  new wxTextCtrl(this, ID_EDTLFUSE, _("00") , wxPoint(46,341),wxSize(21,21) );

	chkReadLfuse =  new wxCheckBox(this, ID_CHKREADLFUSE, _("Read") , wxPoint(12,323),wxSize(55,17) );

	chkWriteLfuse =  new wxCheckBox(this, ID_CHKWRITELFUSE, _("Write") , wxPoint(12,307),wxSize(55,17) );

	WxStaticBox4 =  new wxStaticBox(this, ID_WXSTATICBOX4,_("Low Fuse"),wxPoint(4,290),wxSize(90,79)  );

	chkWriteEeprom =  new wxCheckBox(this, ID_CHKWRITEEEPROM, _("Write") , wxPoint(12,231),wxSize(57,23) );

	WxStaticText7 =  new wxStaticText(this, ID_WXSTATICTEXT7 ,_("Format:") ,wxPoint(480,236),wxSize(39,17)  );

	wxArrayString arrayStringFor_cmbEepromFormat;
	arrayStringFor_cmbEepromFormat.Add(_("Autodetect"));
	arrayStringFor_cmbEepromFormat.Add(_("Intel Hex"));
	arrayStringFor_cmbEepromFormat.Add(_("Motorola"));
	arrayStringFor_cmbEepromFormat.Add(_("Raw binary"));
	arrayStringFor_cmbEepromFormat.Add(_("Immediate mode"));
	cmbEepromFormat =  new wxComboBox(this, ID_WXCOMBOBOX1 ,_("") ,wxPoint(480,254),wxSize(102,21), arrayStringFor_cmbEepromFormat   );

	btnOpenEepromFile =  new wxButton(this, ID_WXBUTTON2, _("...") , wxPoint(445,253),wxSize(20,23) );

	chkVerifyEeprom =  new wxCheckBox(this, ID_WXCHECKBOX3, _("Verify") , wxPoint(252,231),wxSize(57,23) );

	chkReadEeprom =  new wxCheckBox(this, ID_WXCHECKBOX2, _("Read") , wxPoint(132,231),wxSize(57,23) );

	edtEepromFile =  new wxTextCtrl(this, ID_WXEDIT2, _("eeprom.hex") , wxPoint(12,254),wxSize(434,21) );

	WxStaticBox3 =  new wxStaticBox(this, ID_WXSTATICBOX3,_("EEPROM"),wxPoint(4,217),wxSize(584,67)  );

	btnStatusGiveio =  new wxButton(this, ID_BTNSTATUSGIVEIO, _("Status") , wxPoint(495,94),wxSize(75,23) );

	btnRemoveGiveio =  new wxButton(this, ID_BTNREMOVEGIVEIO, _("Remove") , wxPoint(495,67),wxSize(75,23) );

	btnInstallGiveio =  new wxButton(this, ID_BTNINSTALLGIVEIO, _("Install") , wxPoint(495,40),wxSize(75,23) );

	grpGiveio =  new wxStaticBox(this, ID_GRPGIVEIO,_("GiveIO Driver"),wxPoint(474,17),wxSize(114,116)  );

	WxStaticText6 =  new wxStaticText(this, ID_WXSTATICTEXT6 ,_("Format:") ,wxPoint(480,161),wxSize(39,17)  );

	wxArrayString arrayStringFor_cmbFlashFormat;
	arrayStringFor_cmbFlashFormat.Add(_("Autodetect"));
	arrayStringFor_cmbFlashFormat.Add(_("Intel Hex"));
	arrayStringFor_cmbFlashFormat.Add(_("Motorola"));
	arrayStringFor_cmbFlashFormat.Add(_("Raw binary"));
	arrayStringFor_cmbFlashFormat.Add(_("Immediate mode"));
	cmbFlashFormat =  new wxComboBox(this, ID_CMBFLASHFORMAT ,_("") ,wxPoint(478,179),wxSize(102,21), arrayStringFor_cmbFlashFormat   );

	btnOpenFlashFile =  new wxButton(this, ID_BTNOPENFLASHFILE, _("...") , wxPoint(445,178),wxSize(20,23) );

	chkVerifyFlash =  new wxCheckBox(this, ID_CHKVERIFYFLASH, _("Verify") , wxPoint(252,156),wxSize(57,23) );

	chkReadFlash =  new wxCheckBox(this, ID_CHKREADFLASH, _("Read") , wxPoint(132,156),wxSize(57,23) );

	chkWriteFlash =  new wxCheckBox(this, ID_CHKWRITEFLASH, _("Write") , wxPoint(12,156),wxSize(57,23) );

	edtFlashFile =  new wxTextCtrl(this, ID_EDTFLASHFILE, _("flash.hex") , wxPoint(12,179),wxSize(434,21) );

	WxStaticBox1 =  new wxStaticBox(this, ID_WXSTATICBOX1,_("Flash"),wxPoint(4,142),wxSize(584,67)  );

	wxArrayString arrayStringFor_cmbPort;
	
	if (PortList != NULL) {
	    wxXmlNode *child = PortList->GetChildren();
        
        // find pport
        while(child) {
            if (child->GetName() == wxT("Port"))
            {
                wxString content = child->GetNodeContent();
                wxString Name = child->GetPropVal(wxT("Name"),
                              wxT(""));
                if (Name != wxT("")) {
                    arrayStringFor_cmbPort.Add(Name);
                }
             }
            child = child->GetNext();             
       }
	} else {
	    arrayStringFor_cmbPort.Add(_("lpt1"));
	    arrayStringFor_cmbPort.Add(_("lpt2"));
	    arrayStringFor_cmbPort.Add(_("lpt3"));
	    arrayStringFor_cmbPort.Add(_("com1"));
	    arrayStringFor_cmbPort.Add(_("com2"));
	    arrayStringFor_cmbPort.Add(_("com3"));
	    arrayStringFor_cmbPort.Add(_("com4"));
	    arrayStringFor_cmbPort.Add(_("com5"));
	    arrayStringFor_cmbPort.Add(_("com6"));
	    arrayStringFor_cmbPort.Add(_("com7"));
	    arrayStringFor_cmbPort.Add(_("com8"));
	 }
	cmbPort =  new wxComboBox(this, ID_CMBPORT ,_("") ,wxPoint(253,113),wxSize(91,21), arrayStringFor_cmbPort );


	wxArrayString arrayStringFor_cmbProgrammer;
	
	if (ProgList != NULL ) {
	    wxXmlNode *child = ProgList->GetChildren();
        
        // find programer
        while(child) {
            if (child->GetName() == wxT("Programmer"))
            {
                // process text enclosed by <tag1></tag1>
                wxString content = child->GetNodeContent();
                wxString Name = child->GetPropVal(wxT("Name"),
                              wxT(""));
                wxString Para = child->GetPropVal(wxT("Para"),
                              wxT(""));
                wxString Port = child->GetPropVal(wxT("Port"),
                              wxT("true"));
                              
                if (Name != wxT("")) {
                    arrayStringFor_cmbProgrammer.Add(Name);
                    
                    if (Para == wxT("")) {
                        Para = Name;
                    }                    
                    m_arrayStringProgPara.Add(Para);
                    
                    if (Port.CmpNoCase(wxT("true")))
                        m_arrayStringPort.Add(wxT("true"));
                    else
                        m_arrayStringPort.Add(wxT("false"));
                }
            }            
            child = child->GetNext();
        }
	} else {
	    arrayStringFor_cmbProgrammer.Add(wxT("abcmini"));
        m_arrayStringProgPara.Add(wxT("abcmini"));
        m_arrayStringPort.Add("true");
	    arrayStringFor_cmbProgrammer.Add(_("alf"));
        m_arrayStringProgPara.Add(wxT("alf"));
        m_arrayStringPort.Add("true");
	    arrayStringFor_cmbProgrammer.Add(_("avr910"));
        m_arrayStringProgPara.Add(wxT("avr910"));
        m_arrayStringPort.Add("true");
	    arrayStringFor_cmbProgrammer.Add(_("avrisp"));
        m_arrayStringProgPara.Add(wxT("avrisp"));
        m_arrayStringPort.Add("true");
	    arrayStringFor_cmbProgrammer.Add(_("avrispv2"));
        m_arrayStringProgPara.Add(wxT("avrispv2"));
        m_arrayStringPort.Add("true");
	    arrayStringFor_cmbProgrammer.Add(_("avrispmkII"));
        m_arrayStringProgPara.Add(wxT("avrispmkII"));
        m_arrayStringPort.Add("true");
	    arrayStringFor_cmbProgrammer.Add(_("bascom"));
        m_arrayStringProgPara.Add(wxT("bascom"));
        m_arrayStringPort.Add("true");
	    arrayStringFor_cmbProgrammer.Add(_("bsd"));
        m_arrayStringProgPara.Add(wxT("bsd"));
        m_arrayStringPort.Add("true");
	    arrayStringFor_cmbProgrammer.Add(_("butterfly"));
        m_arrayStringProgPara.Add(wxT("butterfly"));
        m_arrayStringPort.Add("true");
	    arrayStringFor_cmbProgrammer.Add(_("dt006"));
        m_arrayStringProgPara.Add(wxT("dt006"));
        m_arrayStringPort.Add("true");
	    arrayStringFor_cmbProgrammer.Add(_("futurlec"));
        m_arrayStringProgPara.Add(wxT("futurlec"));
        m_arrayStringPort.Add("true");
	    arrayStringFor_cmbProgrammer.Add(_("pavr"));
        m_arrayStringProgPara.Add(wxT("pavr"));
        m_arrayStringPort.Add("true");
	    arrayStringFor_cmbProgrammer.Add(_("picoweb"));
        m_arrayStringProgPara.Add(wxT("picoweb"));
        m_arrayStringPort.Add("true");
	    arrayStringFor_cmbProgrammer.Add(_("pony-stk200"));
        m_arrayStringProgPara.Add(wxT("pony-stk200"));
        m_arrayStringPort.Add("true");
	    arrayStringFor_cmbProgrammer.Add(_("sp12"));
        m_arrayStringProgPara.Add(wxT("sp12"));
        m_arrayStringPort.Add("true");
	    arrayStringFor_cmbProgrammer.Add(_("stk200"));
        m_arrayStringProgPara.Add(wxT("stk200"));
        m_arrayStringPort.Add("true");
	    arrayStringFor_cmbProgrammer.Add(_("stk500"));
        m_arrayStringProgPara.Add(wxT("stk500"));
        m_arrayStringPort.Add("true");
	    arrayStringFor_cmbProgrammer.Add(_("stk500v1"));
        m_arrayStringProgPara.Add(wxT("stk500v1"));
        m_arrayStringPort.Add("true");
	    arrayStringFor_cmbProgrammer.Add(_("stk500v2"));
        m_arrayStringProgPara.Add(wxT("stk500v2"));
        m_arrayStringPort.Add("true");
	    arrayStringFor_cmbProgrammer.Add(_("USBasp"));
        m_arrayStringProgPara.Add(wxT("usbasp"));
        m_arrayStringPort.Add("false");
	}
	
	
	cmbProgrammer =  new wxComboBox(this, ID_CMBPROGRAMMER ,_("") ,wxPoint(132,113),wxSize(91,21), arrayStringFor_cmbProgrammer );

	WxStaticText5 =  new wxStaticText(this, ID_WXSTATICTEXT5 ,_("-P Port:") ,wxPoint(252,96),wxSize(39,17)  );

	WxStaticText4 =  new wxStaticText(this, ID_WXSTATICTEXT4 ,_("-c Programmer:") ,wxPoint(132,96),wxSize(75,17)  );

	WxStaticText3 =  new wxStaticText(this, ID_WXSTATICTEXT3 ,_("-p Device:") ,wxPoint(12,96),wxSize(53,17)  );

	wxArrayString arrayStringFor_cmbDevice;
	if (MCUList != NULL) {
	    wxXmlNode *child = MCUList->GetChildren();
        
        // find programer
        while(child) {
            if (child->GetName() == wxT("MCU"))
            {
                // process text enclosed by <tag1></tag1>
                wxString content = child->GetNodeContent();
                wxString Name = child->GetPropVal(wxT("Name"),
                              wxT(""));
                wxString Para = child->GetPropVal(wxT("Para"),
                              wxT(""));
                              
                if (Name != wxT("") && Para != wxT("")) {
                    arrayStringFor_cmbDevice.Add(Name);
                    m_arrayStringDevice.Add(Para);
                }                                               
            }
            child = child->GetNext();
        }
	    
    } else {
	    arrayStringFor_cmbDevice.Add(_("AT90S1200"));
        m_arrayStringDevice.Add("1200");
	    arrayStringFor_cmbDevice.Add(_("AT90S2313"));
        m_arrayStringDevice.Add("2313");
	    arrayStringFor_cmbDevice.Add(_("AT90S2333"));
        m_arrayStringDevice.Add("2333");
	    arrayStringFor_cmbDevice.Add(_("AT90S2343"));
        m_arrayStringDevice.Add("2343");
	    arrayStringFor_cmbDevice.Add(_("AT90S4414"));
        m_arrayStringDevice.Add("4414");
	    arrayStringFor_cmbDevice.Add(_("AT90S4433"));
        m_arrayStringDevice.Add("4433");
	    arrayStringFor_cmbDevice.Add(_("AT90S4434"));
        m_arrayStringDevice.Add("4434");
	    arrayStringFor_cmbDevice.Add(_("AT90S8515"));
        m_arrayStringDevice.Add("8515");
	    arrayStringFor_cmbDevice.Add(_("AT90S8535"));
        m_arrayStringDevice.Add("8535");
	    arrayStringFor_cmbDevice.Add(_("ATmega103"));
        m_arrayStringDevice.Add("m103");
	    arrayStringFor_cmbDevice.Add(_("ATmega128"));
        m_arrayStringDevice.Add("m128");
	    arrayStringFor_cmbDevice.Add(_("ATmega16"));
        m_arrayStringDevice.Add("m16");
	    arrayStringFor_cmbDevice.Add(_("ATmega161"));
        m_arrayStringDevice.Add("m161");
	    arrayStringFor_cmbDevice.Add(_("ATmega162"));
        m_arrayStringDevice.Add("m162");
	    arrayStringFor_cmbDevice.Add(_("ATmega163"));
        m_arrayStringDevice.Add("m163");
	    arrayStringFor_cmbDevice.Add(_("ATmega169"));
        m_arrayStringDevice.Add("m169");
	    arrayStringFor_cmbDevice.Add(_("ATmega32"));
        m_arrayStringDevice.Add("m32");
	    arrayStringFor_cmbDevice.Add(_("ATmega48"));
        m_arrayStringDevice.Add("m48");
	    arrayStringFor_cmbDevice.Add(_("ATmega64"));
        m_arrayStringDevice.Add("m64");
	    arrayStringFor_cmbDevice.Add(_("ATmega8"));
        m_arrayStringDevice.Add("m8");
	    arrayStringFor_cmbDevice.Add(_("ATmega8515"));
        m_arrayStringDevice.Add("m8515");
	    arrayStringFor_cmbDevice.Add(_("ATmega8535"));
        m_arrayStringDevice.Add("m8535");
	    arrayStringFor_cmbDevice.Add(_("ATmega88"));
        m_arrayStringDevice.Add("m88");
	    arrayStringFor_cmbDevice.Add(_("ATtiny12"));
        m_arrayStringDevice.Add("t12");	    
	    arrayStringFor_cmbDevice.Add(_("ATtiny13"));
        m_arrayStringDevice.Add("t13");
	    arrayStringFor_cmbDevice.Add(_("ATtiny15"));
        m_arrayStringDevice.Add("t15");
	    arrayStringFor_cmbDevice.Add(_("ATtiny2313"));
        m_arrayStringDevice.Add("m2313");
	    arrayStringFor_cmbDevice.Add(_("ATtiny26"));
        m_arrayStringDevice.Add("t26");
	}
	
	cmbDevice =  new wxComboBox(this, ID_CMBDEVICE ,_("") ,wxPoint(12,113),wxSize(91,21), arrayStringFor_cmbDevice   );

	WxStaticText2 =  new wxStaticText(this, ID_WXSTATICTEXT2 ,_("-C Location of alternate configuration file:") ,wxPoint(12,51),wxSize(197,17)  );

	btnOpenConfFile =  new wxButton(this, ID_WXBUTTON1, _("...") , wxPoint(445,67),wxSize(20,23) );

	edtConfFile =  new wxTextCtrl(this, ID_WXEDIT1, _("") , wxPoint(12,68),wxSize(434,21) );

	btnOpenAvrdudeFile =  new wxButton(this, ID_BTNOPENAVRDUDEFILE, _("...") , wxPoint(444,21),wxSize(20,23) );

	edtAvrdude =  new wxTextCtrl(this, ID_EDTAVRDUDE, _("avrdude") , wxPoint(12,22),wxSize(433,21) );

	WxStaticText1 =  new wxStaticText(this, ID_WXSTATICTEXT1 ,_("Location of avrdude:") ,wxPoint(12,5),wxSize(102,17)  );
    ////GUI Items Creation End
    if (PortList == NULL) {
    cmbPort->Clear();
    #ifdef __WXMSW__
	    cmbPort->Append(_("lpt1"));
	    cmbPort->Append(_("lpt2"));
	    cmbPort->Append(_("lpt3"));
	    cmbPort->Append(_("com1"));
	    cmbPort->Append(_("com2"));
	    cmbPort->Append(_("com3"));
	    cmbPort->Append(_("com4"));
	    cmbPort->Append(_("com5"));
	    cmbPort->Append(_("com6"));
	    cmbPort->Append(_("com7"));
	    cmbPort->Append(_("com8"));
    #else
	    cmbPort->Append(_("/dev/lp0"));
	    cmbPort->Append(_("/dev/lp1"));
	    cmbPort->Append(_("/dev/lp2"));
	    cmbPort->Append(_("/dev/ttyS0"));
	    cmbPort->Append(_("/dev/ttyS1"));
	    cmbPort->Append(_("/dev/ttyS2"));
	    cmbPort->Append(_("/dev/ttyS3"));
	    cmbPort->Append(_("/dev/ttyS4"));
	    cmbPort->Append(_("/dev/ttyS5"));
	    cmbPort->Append(_("/dev/ttyS6"));
	    cmbPort->Append(_("/dev/ttyS7"));
    #endif
    }
    cmbDevice->SetSelection(0);
    cmbProgrammer->SetSelection(0);
    cmbPort->SetSelection(0);
    cmbFlashFormat->SetSelection(0);
    cmbEepromFormat->SetSelection(0);
    btnExecute->SetFocus();
  
    m_ControlsCreated = 1;
}

void MainDlg::MainDlgInit(wxInitDialogEvent& event )
{

  LoadSettings();

#ifdef __WXMSW__

#else
    grpGiveio->Show(false);
    btnInstallGiveio->Show(false);
    btnRemoveGiveio->Show(false);
    btnStatusGiveio->Show(false);
#endif
}

void MainDlg::MainDlgClose(wxCloseEvent& event)
{
    SaveSettings();
    
    // --> Don't use Close with a wxDialog,
    // use Destroy instead.
    Destroy();
}

void MainDlg::ChangeSettings(wxCommandEvent& event)
{
    BuildCmdLine();
}

void MainDlg::SelectAvrdude(wxCommandEvent& event)
{
  if (OpenFileDialogAvrdude->ShowModal() == wxID_OK)
  {
    edtAvrdude->SetValue(OpenFileDialogAvrdude->GetPath().c_str());
  }  
}
  
void MainDlg::SelectConfFile(wxCommandEvent& event)
{
  if (OpenFileDialogConfFile->ShowModal() == wxID_OK)
  {
    edtConfFile->SetValue(OpenFileDialogConfFile->GetPath().c_str());
  }  
}
  
void MainDlg::SelectFlash(wxCommandEvent& event)
{
  if (OpenFileDialogFlash->ShowModal() == wxID_OK)
  {
    edtFlashFile->SetValue(OpenFileDialogFlash->GetPath().c_str());
  }  
}
  
void MainDlg::SelectEeprom(wxCommandEvent& event)
{
  if (OpenFileDialogEeprom->ShowModal() == wxID_OK)
  {
    edtEepromFile->SetValue(OpenFileDialogEeprom->GetPath().c_str());
  }  
}

void MainDlg::InstallGiveio(wxCommandEvent& event)
{
  if (wxFile::Exists("install_giveio.bat"))
    ExecWithRedirect("install_giveio.bat");
}

void MainDlg::RemoveGiveio(wxCommandEvent& event)
{
  if (wxFile::Exists("install_giveio.bat"))
    ExecWithRedirect("remove_giveio.bat");
}

void MainDlg::StatusGiveio(wxCommandEvent& event)
{
  ExecWithRedirect("loaddrv status giveio");
}

//ToDo: Switch Power on if SP12-kompatible programmer is available
void MainDlg::LptPowerOn(wxCommandEvent& event)
{
#ifdef __WXMSW__

/*
  HWND hDevice;
  word ret;

  hDevice:= CreateFile("\\.\\giveio",GENERIC_READ,0,nil,
                       OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,0);

  if (hDevice = INVALID_HANDLE_VALUE)    // did we succeed?
    // possibly call GetLastError() to get a hint what failed
    // and terminate (it is useless to continue if we can’t connect to Direct I/O)
//    ShowMessage('GiveIO Driver Not Installed.');
    raise EPortError.Create("GiveIO Driver Not Installed");
*/

  if (chkLptPowerOn->GetValue())
  {
    wxMessageBox("Sorry. This function isn't implemented yet.");

/*
    //power off
    //ToDo: Ermitteln der echten LPT-Adresse im System
    ret:= PortIn($0378);
    //ToDo: echte Verküpfung eintragen
    ret:= ret and $0000;
    PortOut($0378, ret);
*/    
  }
/*
  else
  {
    //power on
    //ToDo: Ermitteln der echten LPT-Adresse im System
    ret:= PortIn($0378);
    //ToDo: echte Verküpfung eintragen
    ret:= ret or $ffff;
    PortOut($0378, ret);
  }
   CloseHandle(hDevice);
*/
#endif
}
 

void MainDlg::Execute(wxCommandEvent& event)
{
  wxSetCursor(*wxHOURGLASS_CURSOR);
  ExecWithRedirect(edtCmdline->GetValue());
  wxSetCursor(*wxSTANDARD_CURSOR);
}

void MainDlg::LoadSettings(void)
{
    bool value;

    wxConfig *cfg = new wxConfig(ConfigFilenameString);  // ->registry

    edtAvrdude->SetValue(cfg->Read("avrdude/path", "avrdude"));
    edtConfFile->SetValue(cfg->Read("options/conf", ""));

    cmbDevice->SetSelection(cfg->Read("options/device", (long)0));

    cmbProgrammer->SetSelection(cfg->Read("options/programmer", (long)0));
    cmbPort->SetSelection(cfg->Read("options/port", (long)0));

    chkWriteFlash->SetValue(cfg->Read("options/write_flash", value));
    chkReadFlash->SetValue(cfg->Read("options/read_flash", value));
    chkVerifyFlash->SetValue(cfg->Read("options/verify_flash", value));
    edtFlashFile->SetValue(cfg->Read("options/flash_file", "flash.hex"));
    cmbFlashFormat->SetSelection(cfg->Read("options/flash_format", (long)0));

    chkWriteEeprom->SetValue(cfg->Read("options/write_eeprom", value));
    chkReadEeprom->SetValue(cfg->Read("options/read_eeprom", value));
    chkVerifyEeprom->SetValue(cfg->Read("options/verify_eeprom", value));
    edtEepromFile->SetValue(cfg->Read("options/eeprom_file", "eeprom.hex"));
    cmbEepromFormat->SetSelection(cfg->Read("options/eeprom_format", (long)0));
    
    chkWriteLfuse->SetValue(cfg->Read("options/write_lfuse", value));
    chkReadLfuse->SetValue(cfg->Read("options/read_lfuse", value));
    edtLfuse->SetValue(cfg->Read("options/lfuse", "00"));

    chkWriteHfuse->SetValue(cfg->Read("options/write_hfuse", value));
    chkReadHfuse->SetValue(cfg->Read("options/read_hfuse", value));
    edtHfuse->SetValue(cfg->Read("options/hfuse", "00"));

    chkWriteEfuse->SetValue(cfg->Read("options/write_efuse", value));
    chkReadEfuse->SetValue(cfg->Read("options/read_efuse", value));
    edtEfuse->SetValue(cfg->Read("options/efuse", "00"));

    chkWriteLockfuse->SetValue(cfg->Read("options/write_lockfuse", value));
    chkReadLockfuse->SetValue(cfg->Read("options/read_lockfuse", value));
    edtLockfuse->SetValue(cfg->Read("options/lockfuse", "00"));

    chkWriteCalibration->SetValue(cfg->Read("options/write_calibration", value));
    chkReadCalibration->SetValue(cfg->Read("options/read_calibration", value));
    edtCalibration->SetValue(cfg->Read("options/calibration", "00000000"));

    chkWriteSignature->SetValue(cfg->Read("options/write_signature", value));
    chkReadSignature->SetValue(cfg->Read("options/read_signature", value));
    edtSignature->SetValue(cfg->Read("options/signature", "000000"));

    chkOptAutoErase->SetValue(cfg->Read("options/disable_auto_erase", value));
    chkOptChipErase->SetValue(cfg->Read("options/perform_chip_erase", value));
    chkOptVerifySignature->SetValue(cfg->Read("options/verify_device_signature", value));
    chkOptDontWrite->SetValue(cfg->Read("options/dont_write", value));
    chkOptDisableOutput->SetValue(cfg->Read("options/disable_process_output", value));
    chkOptVerboseOutput->SetValue(cfg->Read("options/enable_verbose_output", value));
    chkOptDisableVerify->SetValue(cfg->Read("options/disable_verify_check", value));
    chkOptTerminal->SetValue(cfg->Read("options/terminal_mode", value));

    chkExitReset->SetValue(cfg->Read("options/exit_reset", value));
    chkExitNoreset->SetValue(cfg->Read("options/exit_noreset", value));
    chkExitVcc->SetValue(cfg->Read("options/exit_vcc", value));
    chkExitNovcc->SetValue(cfg->Read("options/exit_novcc", value));

    chkCcErase->SetValue(cfg->Read("options/erase_cycle_counter", value));
    chkCcSet->SetValue(cfg->Read("options/set_cycle_counter", value));
    edtCycleCounter->SetValue(cfg->Read("options/cycle_counter", "0"));

    delete cfg;
}    

void MainDlg::SaveSettings(void)
{

//    wxFileConfig *cfg = new wxFileConfig ("", "",
//                                          ConfigFilenameString, "",
//                                          wxCONFIG_USE_LOCAL_FILE | wxCONFIG_USE_RELATIVE_PATH);
    
    wxConfig *cfg = new wxConfig(ConfigFilenameString);  // ->registry

    cfg->Write("avrdude/path", edtAvrdude->GetValue());
    cfg->Write("options/conf", edtConfFile->GetValue());

    cfg->Write("options/device", cmbDevice->GetSelection());
    cfg->Write("options/programmer", cmbProgrammer->GetSelection());
    cfg->Write("options/port", cmbPort->GetSelection());

    cfg->Write("options/write_flash", chkWriteFlash->GetValue());
    cfg->Write("options/read_flash", chkReadFlash->GetValue());
    cfg->Write("options/verify_flash", chkVerifyFlash->GetValue());
    cfg->Write("options/flash_file", edtFlashFile->GetValue());
    cfg->Write("options/flash_format", cmbFlashFormat->GetSelection());

    cfg->Write("options/write_eeprom", chkWriteEeprom->GetValue());
    cfg->Write("options/read_eeprom", chkReadEeprom->GetValue());
    cfg->Write("options/verify_eeprom", chkVerifyEeprom->GetValue());
    cfg->Write("options/eeprom_file", edtEepromFile->GetValue());
    cfg->Write("options/eeprom_format", cmbEepromFormat->GetSelection());

    cfg->Write("options/write_lfuse", chkWriteLfuse->GetValue());
    cfg->Write("options/read_lfuse", chkReadLfuse->GetValue());
    cfg->Write("options/lfuse", edtLfuse->GetValue());

    cfg->Write("options/write_hfuse", chkWriteHfuse->GetValue());
    cfg->Write("options/read_hfuse", chkReadHfuse->GetValue());
    cfg->Write("options/hfuse", edtHfuse->GetValue());

    cfg->Write("options/write_efuse", chkWriteEfuse->GetValue());
    cfg->Write("options/read_efuse", chkReadEfuse->GetValue());
    cfg->Write("options/efuse", edtEfuse->GetValue());

    cfg->Write("options/write_lockfuse", chkWriteLockfuse->GetValue());
    cfg->Write("options/read_lockfuse", chkReadLockfuse->GetValue());
    cfg->Write("options/lockfuse", edtLockfuse->GetValue());

    cfg->Write("options/write_calibration", chkWriteCalibration->GetValue());
    cfg->Write("options/read_calibration", chkReadCalibration->GetValue());
    cfg->Write("options/calibration", edtCalibration->GetValue());

    cfg->Write("options/write_signature", chkWriteSignature->GetValue());
    cfg->Write("options/read_signature", chkReadSignature->GetValue());
    cfg->Write("options/signature", edtSignature->GetValue());

    cfg->Write("options/disable_auto_erase", chkOptAutoErase->GetValue());
    cfg->Write("options/perform_chip_erase", chkOptChipErase->GetValue());
    cfg->Write("options/verify_device_signature", chkOptVerifySignature->GetValue());
    cfg->Write("options/dont_write", chkOptDontWrite->GetValue());
    cfg->Write("options/disable_process_output", chkOptDisableOutput->GetValue());
    cfg->Write("options/enable_verbose_output", chkOptVerboseOutput->GetValue());
    cfg->Write("options/disable_verify_check", chkOptDisableVerify->GetValue());
    cfg->Write("options/terminal_mode", chkOptTerminal->GetValue());

    cfg->Write("options/exit_reset", chkExitReset->GetValue());
    cfg->Write("options/exit_noreset", chkExitNoreset->GetValue());
    cfg->Write("options/exit_vcc", chkExitVcc->GetValue());
    cfg->Write("options/exit_novcc", chkExitNovcc->GetValue());

    cfg->Write("options/erase_cycle_counter", chkCcErase->GetValue());
    cfg->Write("options/set_cycle_counter", chkCcSet->GetValue());
    cfg->Write("options/cycle_counter", edtCycleCounter->GetValue());

    delete cfg;
}
    
void MainDlg::ExecWithRedirect(const wxString& cmd, bool sync)
{
    //sync exec
    if (sync)
    {
        wxArrayString output, errors;
        int code = wxExecute(cmd, output, errors);
//no statusbar :(        
//        wxLogStatus(_T("command '%s' terminated with exit code %d."), cmd.c_str(), code);

        if ( code != -1 )
        {
            ShowOutput(output);
            ShowOutput(errors);
        }
    }

    //async exec
    else
    {
/*
        MyPipedProcess *process = new MyPipedProcess(this, cmd);
        if ( !wxExecute(cmd, wxEXEC_ASYNC, process) )
        {
            wxLogError(_T("Execution of '%s' failed."), cmd.c_str());
            delete process;
        }
        else
        {
            AddAsyncProcess(process);
        }
*/        
    }
}

void MainDlg::ShowOutput(const wxArrayString& output)
{
    size_t count = output.GetCount();
    if ( !count )
        return;

    lbxOutput->Clear();
    for ( size_t n = 0; n < count; n++ )
    {
        lbxOutput->Append(output[n]);
    }
}

void MainDlg::BuildCmdLine(void)
{
  wxString device, exitmode, format;
  wxString programmer;
  bool bPort = true;

  if (m_ControlsCreated != 0)
  {
    edtCmdline->SetValue("\"" + edtAvrdude->GetValue() + "\"");

  //Device
   device = m_arrayStringDevice[cmbDevice->GetCurrentSelection()];
  
  edtCmdline->AppendText(" -p " + device);

  if (m_arrayStringProgPara.GetCount() > 0)
  {
    int sel = cmbProgrammer->GetCurrentSelection();
    programmer = m_arrayStringProgPara[sel];
    bPort = m_arrayStringPort[sel].Cmp(wxT("true"));
  } else if (cmbProgrammer->GetStringSelection() == "USBasp") {
    programmer = "usbasp";
    bPort = false;
  } else {
    programmer = cmbProgrammer->GetStringSelection();
    bPort = true;
  }
  

  edtCmdline->AppendText(" -c " + programmer);
  
  if (bPort) { 
    if (cmbProgrammer->GetStringSelection() == "sp12")
        chkLptPowerOn->Show(true);
    else
        chkLptPowerOn->Show(false);

    edtCmdline->AppendText(" -P " + cmbPort->GetStringSelection());
  }

  if (edtConfFile->GetValue() != "") edtCmdline->AppendText(" -C \"" + edtConfFile->GetValue()+ "\"");

  
  //Operationmode
  if (cmbFlashFormat->GetStringSelection() == "Autodetect")     format = "a";
  if (cmbFlashFormat->GetStringSelection() == "Intel Hex")      format = "i";
  if (cmbFlashFormat->GetStringSelection() == "Motorola")       format = "s";
  if (cmbFlashFormat->GetStringSelection() == "Raw binary")     format = "r";
  if (cmbFlashFormat->GetStringSelection() == "Immediate mode") format = "m";
//ToDo: Set file between ""
  if (chkWriteFlash->IsChecked())  edtCmdline->AppendText(" -U flash:w:\"" + edtFlashFile->GetValue() + "\":" + format);
  if (chkReadFlash->IsChecked())   edtCmdline->AppendText(" -U flash:r:\"" + edtFlashFile->GetValue() + "\":" + format);
  if (chkVerifyFlash->IsChecked()) edtCmdline->AppendText(" -U flash:v:\"" + edtFlashFile->GetValue() + "\":" + format);

  if (cmbEepromFormat->GetStringSelection() == "Autodetect")     format = "a";
  if (cmbEepromFormat->GetStringSelection() == "Intel Hex")      format = "i";
  if (cmbEepromFormat->GetStringSelection() == "Motorola")       format = "s";
  if (cmbEepromFormat->GetStringSelection() == "Raw binary")     format = "r";
  if (cmbEepromFormat->GetStringSelection() == "Immediate mode") format = "m";
  if (chkWriteEeprom->IsChecked())  edtCmdline->AppendText(" -U eeprom:w:\"" + edtEepromFile->GetValue() + "\":" + format);
  if (chkReadEeprom->IsChecked())   edtCmdline->AppendText(" -U eeprom:r:\"" + edtEepromFile->GetValue() + "\":" + format);
  if (chkVerifyEeprom->IsChecked()) edtCmdline->AppendText(" -U eeprom:v:\"" + edtEepromFile->GetValue() + "\":" + format);

  //Fuses
  if (chkWriteLfuse->IsChecked()) edtCmdline->AppendText(" -U lfuse:w:" + edtLfuse->GetValue());
  if (chkReadLfuse->IsChecked())  edtCmdline->AppendText(" -U lfuse:r:con:r");
  edtLfuse->Enable(chkWriteLfuse->IsChecked());

  if (chkWriteHfuse->IsChecked()) edtCmdline->AppendText(" -U hfuse:w:" + edtHfuse->GetValue());
  if (chkReadHfuse->IsChecked())  edtCmdline->AppendText(" -U hfuse:r:con:r");
  edtHfuse->Enable(chkWriteHfuse->IsChecked());

  if (chkWriteLockfuse->IsChecked()) edtCmdline->AppendText(" -U lock:w:" + edtLockfuse->GetValue());
  if (chkReadLockfuse->IsChecked())  edtCmdline->AppendText(" -U lock:r:con:r");
  edtLockfuse->Enable(chkWriteLockfuse->IsChecked());

  if (chkWriteEfuse->IsChecked()) edtCmdline->AppendText(" -U efuse:w:" + edtEfuse->GetValue());
  if (chkReadEfuse->IsChecked())  edtCmdline->AppendText(" -U efuse:r:con:r");
  edtEfuse->Enable(chkWriteEfuse->IsChecked());

  if (chkWriteCalibration->IsChecked()) edtCmdline->AppendText(" -U calibration:w:" + edtCalibration->GetValue());
  if (chkReadCalibration->IsChecked())  edtCmdline->AppendText(" -U calibration:r:con:r");
  edtCalibration->Enable(chkWriteCalibration->IsChecked());

  if (chkWriteSignature->IsChecked()) edtCmdline->AppendText(" -U signature:w:" + edtSignature->GetValue());
  if (chkReadSignature->IsChecked())  edtCmdline->AppendText(" -U signature:r:con:r");
  edtSignature->Enable(chkWriteSignature->IsChecked());

 //Options
  if (chkOptAutoErase->IsChecked())  edtCmdline->AppendText(" -D");
  if (chkOptChipErase->IsChecked())  edtCmdline->AppendText(" -e");
  if (chkOptVerifySignature->IsChecked())  edtCmdline->AppendText(" -F");
  if (chkOptDontWrite->IsChecked())  edtCmdline->AppendText(" -n");
  if (chkOptDisableOutput->IsChecked())  edtCmdline->AppendText(" -q");
  if (chkOptVerboseOutput->IsChecked())  edtCmdline->AppendText(" -v");
  if (chkOptDisableVerify->IsChecked())  edtCmdline->AppendText(" -V");
  if (chkOptTerminal->IsChecked()) edtCmdline->AppendText(" -t");

  //Exitmode
  if (chkExitReset->IsChecked())
    exitmode = "reset";
  if (chkExitNoreset->IsChecked())
    if (exitmode != "")
      exitmode = exitmode + ",noreset";
    else
      exitmode = "noreset";
  if (chkExitVcc->IsChecked())
    if (exitmode != "")
      exitmode = exitmode + ",vcc";
    else
      exitmode = "vcc";
  if (chkExitNovcc->IsChecked())
    if (exitmode != "")
      exitmode = exitmode + ",novcc";
    else
      exitmode = "novcc";

  if (exitmode != "") 
    edtCmdline->AppendText(" -E " + exitmode);

  //counter
  if (chkCcErase->IsChecked()) edtCmdline->AppendText(" -y");
  edtCycleCounter->Enable(chkCcSet->IsChecked());
  if (chkCcSet->IsChecked()) edtCmdline->AppendText(" -Y " + edtCycleCounter->GetValue());

  }
}


/*
 * WxbtnAboutClick
 */
void MainDlg::WxbtnAboutClick(wxCommandEvent& event)
{
	// insert your code here
    wxMessageBox("avrdude-gui v0.2.2\n\n" \
                 "A GUI for the command line tool 'avrdude'\n" \
                 "to program the wide range of \n" \
                 "Atmel AVR RISC microcontrollers.\n\n" \
                 "This software is covered by the GPL.\n\n" \
                 "http://avrdude-gui.sourceforge.net/ \n\n" \
                 "avrdude-gui project \n" \
                 "http://sourceforge.net/projects/avrdude-gui\n\n" \
                 "the version modify by kunyi.chen@gmail.com \n" \
                 "added configuration(XML format) support\n"
                 , "avrdude-gui");

	event.Skip();
}

