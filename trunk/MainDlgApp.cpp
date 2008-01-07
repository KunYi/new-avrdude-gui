//---------------------------------------------------------------------------
//
// Name:        MainDlgApp.cpp
// Author:      J. Lachmann
// Created:     11/23/2004
// Copyright:
//
//---------------------------------------------------------------------------
#include "MainDlgApp.h"
#include "MainDlg.h"

IMPLEMENT_APP(MainDlgApp)

bool MainDlgApp::OnInit()
{
   MainDlg *myDlg = new  MainDlg(NULL);
   SetTopWindow(myDlg);
   myDlg->Show(TRUE);      
   return TRUE;
}
 
int MainDlgApp::OnExit()
{
   return 0;
}
