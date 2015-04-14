/**
@file 	GUIPanel.h
@author Lime Microsystems
@brief	base class for tooltips updating
*/

#ifndef GUI_PANEL_H
#define GUI_PANEL_H

#include "LMS7002_MainControl.h"
#include <wx/panel.h>
#include <wx/tooltip.h>
#include <iostream>
#include <map>
#include "RegistersMap.h"
using namespace std;
class GUIPanel
{
public:
    GUIPanel(){};
    ~GUIPanel(){};

    std::map<long, LMS7002_Parameter> wndId2Enum;
    LMS7002_MainControl *lmsControl;

    virtual void UpdateTooltips(wxWindow* panel)
    {
        wxWindow *field = NULL;
        std::map<long, LMS7002_Parameter>::iterator fieldIds;
        wxString sttip = "";
        for(fieldIds = wndId2Enum.begin(); fieldIds != wndId2Enum.end(); ++fieldIds)
        {
            field = panel->FindWindow(fieldIds->first);
            wxToolTip *ttip = NULL;
            ttip = field->GetToolTip();
            if(ttip)
                sttip = ttip->GetTip();
            else
                sttip = "";

            ControlParameter cp = lmsControl->getRegistersMap()->getParameterInfo( fieldIds->second );
            if(cp.bitCount == 0)
                cout << "Warning: bit count = 0" << endl;
            char cname[64];
            sprintf(cname, "%s", cp.m_name.c_str());
            char caddr[64];
            if(cp.bitCount == 1)
                sprintf(caddr, "0x%.4X[%i]", cp.address, cp.LSBpos);
            else
                sprintf(caddr, "0x%.4X[%i:%i]", cp.address, cp.LSBpos+cp.bitCount-1, cp.LSBpos);
            field->SetToolTip(NULL);
            field->SetToolTip( wxString::Format("%s.\n %s %s", sttip.c_str(), caddr, cname) );
            ttip = field->GetToolTip();
        }
    }
};

#endif // GUI_PANEL_H

