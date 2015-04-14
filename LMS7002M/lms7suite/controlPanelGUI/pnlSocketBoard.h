/**
@file 	pnlSocketBoard.h
@author Lime Microsystems
*/
#ifndef PNLSOCKETBOARD_H
#define PNLSOCKETBOARD_H

//(*Headers(pnlSocketBoard)
#include <wx/panel.h>
class wxCheckBox;
class wxFlexGridSizer;
class wxButton;
class wxStaticBoxSizer;
//*)

#include <wx/wx.h>
#include <map>
#include <vector>
#include "GUIPanel.h"

class LMS7002_MainControl;

class SocketBoardButton : public wxButton
{
public:
    SocketBoardButton(wxWindow* parent,wxWindowID id=wxID_ANY, const wxString label="Button", const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize, int style=0, wxValidator valid=wxDefaultValidator, wxString name=wxEmptyString)
    {
        type = 0;
        mirrored = 0;
        Create(parent, id, label, pos, size, style, valid, name);
        int w,h;
        GetSize(&w, &h);
        SetSize(80, 15);
    };
    ~SocketBoardButton(){};
    void OnPaint(wxPaintEvent& event)
    {
        if(type == 1)
        {
        wxPaintDC dc(this);
        dc.Clear();
        wxSize sztxt;
        sztxt = dc.GetTextExtent( GetLabel() );
        int height = 0, width = 0;
        dc.GetSize(&width, &height);
//        if(type == 0)
//        {
//            vector<wxPoint> points;
//            points.push_back(wxPoint(0, 0));
//            points.push_back(wxPoint(width-width/5, 0));
//            points.push_back(wxPoint(width-1, height/2));
//            points.push_back(wxPoint(width-width/5, height-1));
//            points.push_back(wxPoint(0, height-1));
//            points.push_back(wxPoint(0, 0));
//            dc.DrawPolygon(points.size(), &points[0]);
//        }
//        else
        {
            int rad = 5;
            int posx;
            if(mirrored)
                posx = width-rad;
            else
                posx = rad;
            dc.DrawCircle(posx, height/2, rad);
            dc.SetBrush(*wxBLACK_BRUSH);
            dc.DrawCircle(posx, height/2, rad/3);
        }
        dc.DrawText( GetLabel() , width/2-sztxt.x/2, height/2-sztxt.y/2);
        }
    }
    int type;
    bool mirrored;

    DECLARE_EVENT_TABLE()
};



class SourceSymbol : public wxStaticText
{
public:
    SourceSymbol(wxWindow* parent,wxWindowID id=wxID_ANY, const wxString label="Label", const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize, int style=0, wxString name=wxEmptyString)
    {
        Create(parent, id, label, pos, size, style, name);
    };
    ~SourceSymbol(){};
    void OnPaint(wxPaintEvent& event)
    {
        wxPaintDC dc(this);
        dc.Clear();
        wxSize sztxt;
        sztxt = dc.GetTextExtent( GetLabel() );
        int height = 0, width = 0;
        dc.GetSize(&width, &height);
        dc.DrawCircle(-width, height/2, 20);
        //dc.DrawText( GetLabel() , width/2-sztxt.x/2, height/2-sztxt.y/2);
        printf("painting Src\n");
    }

    DECLARE_EVENT_TABLE()
};



struct ObjectMux
{
    ObjectMux() : totalStates(0), controlsCount(0), width(70), pinMarginOffset(15), pinDistance(20), pinRadius(3) {};
    wxPoint pos;
    string name;
    int totalStates;
    int controlsCount;
    bool mirrored;
    int width;
    int pinMarginOffset;
    int pinDistance;
    int pinRadius;
    wxPoint GetInputPos()
    {
        int height = (totalStates+1)*pinDistance;
        if(!mirrored)
            return wxPoint(pos.x-pinMarginOffset, pos.y+height/2);
        else
            return wxPoint(pos.x+width+pinMarginOffset, pos.y+height/2);
    }
    wxPoint GetOutputPos(int index)
    {
        if(!mirrored)
            return wxPoint(pos.x+width+pinMarginOffset, pos.y+pinDistance*(index+1));
        else
            return wxPoint(pos.x-pinMarginOffset, pos.y+pinDistance*(index+1));
    }
};

class pnlSocketBoard: public wxPanel, GUIPanel
{
	public:
		pnlSocketBoard(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize, int style=0, wxString name=wxEmptyString);
		void Initialize(LMS7002_MainControl *pControl);
		void UpdateGUI();
		int ReadbackGPIOStates();
		int SendCommand();
		virtual ~pnlSocketBoard();

		//(*Declarations(pnlSocketBoard)
		SocketBoardButton* btnU47_0;
		wxCheckBox* chkGPIO2;
		SocketBoardButton* btnU38_1;
		wxCheckBox* chkGPIO1;
		SocketBoardButton* btnU48_0;
		wxCheckBox* chkDIG_RST;
		SocketBoardButton* btnU37_1;
		wxCheckBox* chkGPIO7;
		wxCheckBox* chkGPIO0;
		SocketBoardButton* btnU39_0;
		wxCheckBox* chkG_PWR_DWN;
		SocketBoardButton* btnU37_0;
		SocketBoardButton* btnU42_3;
		SocketBoardButton* btnU40_0;
		SocketBoardButton* btnU44_0;
		SocketBoardButton* btnU38_3;
		wxPanel* Panel1;
		SocketBoardButton* btnU42_1;
		wxCheckBox* chkGPIO5;
		wxCheckBox* chkDIO_DIR_CTRL1;
		SocketBoardButton* btnU38_2;
		wxCheckBox* chkIQSEL2_DIR;
		wxCheckBox* chkGPIO6;
		SocketBoardButton* btnU47_1;
		SocketBoardButton* btnU37_3;
		SocketBoardButton* btnU42_2;
		SocketBoardButton* btnU43_1;
		wxCheckBox* chkGPIO3;
		SocketBoardButton* btnU45_1;
		SocketBoardButton* btnU43_0;
		SocketBoardButton* btnU44_1;
		SocketBoardButton* btnU38_0;
		SocketBoardButton* btnU45_0;
		wxCheckBox* chkGPIO4;
		SocketBoardButton* btnU39_1;
		SocketBoardButton* btnU42_0;
		SocketBoardButton* btnU41_0;
		SocketBoardButton* btnU41_1;
		wxCheckBox* chkIQSEL1_DIR;
		wxCheckBox* chkDIO_DIR_CTRL2;
		SocketBoardButton* btnU43_3;
		SocketBoardButton* btnU37_2;
		SocketBoardButton* btnU40_1;
		wxCheckBox* chkDIO_BUFF_OE;
		SocketBoardButton* btnU48_1;
		SocketBoardButton* btnU43_2;
		//*)

	protected:

		//(*Identifiers(pnlSocketBoard)
		static const long ID_BUTTON1;
		static const long ID_BUTTON3;
		static const long ID_BUTTON2;
		static const long ID_BUTTON4;
		static const long ID_BUTTON5;
		static const long ID_BUTTON6;
		static const long ID_BUTTON7;
		static const long ID_BUTTON8;
		static const long ID_BUTTON9;
		static const long ID_BUTTON10;
		static const long ID_BUTTON11;
		static const long ID_BUTTON12;
		static const long ID_BUTTON13;
		static const long ID_BUTTON14;
		static const long ID_BUTTON15;
		static const long ID_BUTTON16;
		static const long ID_BUTTON17;
		static const long ID_BUTTON18;
		static const long ID_BUTTON19;
		static const long ID_BUTTON20;
		static const long ID_BUTTON21;
		static const long ID_BUTTON22;
		static const long ID_BUTTON23;
		static const long ID_BUTTON24;
		static const long ID_CHECKBOX8;
		static const long ID_CHECKBOX9;
		static const long ID_CHECKBOX10;
		static const long ID_CHECKBOX11;
		static const long ID_CHECKBOX12;
		static const long ID_CHECKBOX13;
		static const long ID_CHECKBOX14;
		static const long ID_CHECKBOX15;
		static const long ID_CHECKBOX1;
		static const long ID_CHECKBOX2;
		static const long ID_CHECKBOX3;
		static const long ID_CHECKBOX4;
		static const long ID_CHECKBOX5;
		static const long ID_CHECKBOX6;
		static const long ID_CHECKBOX7;
		static const long ID_TABSOCKETSEVB7V2;
		static const long ID_BUTTON25;
		static const long ID_BUTTON26;
		static const long ID_BUTTON27;
		static const long ID_BUTTON28;
		static const long ID_BUTTON29;
		static const long ID_BUTTON30;
		//*)

	private:

		//(*Handlers(pnlSocketBoard)
		void OnPaint(wxPaintEvent& event);
		void OnEraseBackground(wxEraseEvent& event);
		void OnbtnGNDClick(wxCommandEvent& event);
		void OnbtnLNAW_A1Click(wxCommandEvent& event);
		void OnbtnLNAW_A2Click(wxCommandEvent& event);
		void OnbtnLNAW_A3Click(wxCommandEvent& event);
		void OnU37_0(wxCommandEvent& event);
		void OnU37_1(wxCommandEvent& event);
		void OnU37_2(wxCommandEvent& event);
		void OnU37_3(wxCommandEvent& event);
		void OnU43_0(wxCommandEvent& event);
		void OnU43_1(wxCommandEvent& event);
		void OnU43_2(wxCommandEvent& event);
		void OnU43_3(wxCommandEvent& event);
		void OnU47_0(wxCommandEvent& event);
		void OnU47_1(wxCommandEvent& event);
		void OnchkDIO_DIR_CTRL1Click(wxCommandEvent& event);
		void OnchkDIO_DIR_CTRL2Click(wxCommandEvent& event);
		void OnchkDIO_BUFF_OEClick(wxCommandEvent& event);
		void OnchkIQSEL1_DIRClick(wxCommandEvent& event);
		void OnchkIQSEL2_DIRClick(wxCommandEvent& event);
		void OnchkG_PWR_DWNClick(wxCommandEvent& event);
		void OnchkDIG_RSTClick(wxCommandEvent& event);
		void OnbtnU45_0Click(wxCommandEvent& event);
		void OnbtnU45_1Click(wxCommandEvent& event);
		void OnbtnU48_0Click(wxCommandEvent& event);
		void OnbtnU48_1Click(wxCommandEvent& event);
		void OnbtnU39_0Click(wxCommandEvent& event);
		void OnbtnU39_1Click(wxCommandEvent& event);
		//*)

	protected:
	    std::map< std::string, ObjectMux > muxes;
	    vector< pair<wxPoint, wxPoint> > links;

		void BuildContent(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size);
	    vector<unsigned char> gpioStates;
        void DrawMUX(wxPaintDC &dc, const ObjectMux &mux, int state);
        void DrawLink(wxPaintDC &dc, wxPoint a, wxPoint b);

        unsigned char setbit(const unsigned char src, const int pos, const bool value);
        bool getbit(const unsigned char src, const int pos);
		DECLARE_EVENT_TABLE()
};

#endif
