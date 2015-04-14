/**
@file	ComboBoxMap.h
@author Lime Microsystems
@brief 	Header for ComboBoxMap.cpp
*/

#ifndef STD_COMBOBOX_H
#define STD_COMBOBOX_H

#include <wx/wx.h>
#include <wx/combo.h>
#include <vector>

using namespace std;
typedef pair<long,wxString> cmbKeyValuePair;

class ComboBoxMapPopup : public wxControl, public wxComboPopup
{
public:
    ComboBoxMapPopup();
    ComboBoxMapPopup(wxWindow *parent, wxWindowID winid);
    ~ComboBoxMapPopup();

    void OnMyEvent(wxCommandEvent& event);

    virtual bool FindItem(const wxString &item, wxString *trueItem=NULL);

    virtual void Init();
    void OnScroll(wxScrollEvent& event);
    virtual bool Create(wxWindow* parent);
    virtual bool Create(wxWindow* parent, wxWindowID id);
    virtual wxWindow *GetControl() { return this; }
    virtual void SetStringValue(const wxString& s);
    virtual wxString GetStringValue() const;
    void OnMouseClick(wxMouseEvent &event);
    void OnMouseMove(wxMouseEvent &event);
    void OnPopup();
    void OnPaint(wxPaintEvent &event);
    void OnEraseBackGround(wxEraseEvent& event);
    void OnMouseWheelMoved(wxMouseEvent &event);

    bool SetSelection(int n);
    bool SetSelectionByIndex(int ind);
    int GetSelection();
    int GetSelectionIndex();

    int Append(const string &str);
    int Append(const wxString &str);
    int Append(const vector<string> &items);
    int Set(const vector<cmbKeyValuePair> keyVals);
    void Clear();

    void SendComboboxEvent();
    int FindStringIndex(const string &str);

protected:
    int m_myID;
    wxWindow *m_cmbbox;
    vector<cmbKeyValuePair> m_strings_items;
    wxScrollBar *ScrollBar1;
    int m_textHeight;

    int showLines;
    int m_selection;
    bool initialized;
    int m_highlightedItem;

private:
    DECLARE_EVENT_TABLE()
};


class ComboBoxMap : public wxComboCtrl
{
public:
    ComboBoxMap();
    ComboBoxMap(wxWindow *parent,
              wxWindowID winid,
              const wxString str = wxEmptyString,
              const wxPoint& pos = wxDefaultPosition,
              const wxSize& size = wxDefaultSize,
              long style = 0, int a=0, int b=0,
              const wxValidator& val = wxDefaultValidator,
              const wxString& name = "ComboBoxMap");

    ComboBoxMap(wxWindow *parent,
              wxWindowID winid,
              const wxPoint& pos = wxDefaultPosition,
              const wxSize& size = wxDefaultSize,
              long style = 0, int a=0, int b=0,
              const wxValidator& val = wxDefaultValidator,
              const wxString& name = "ComboBoxMap");

    bool Create(wxWindow *parent,
              wxWindowID winid,
              const wxPoint& pos = wxDefaultPosition,
              const wxSize& size = wxDefaultSize,
              long style = 0, int a=0, int b=0,
              const wxValidator& val = wxDefaultValidator,
              const wxString& name = "ComboBoxMap");

    int Append(const wxArrayString &sarray);
    int Append(const vector<string> &sarray);
    int Append(const wxString &str);
    int Set(const wxArrayString &sarray);
    int Set(vector<cmbKeyValuePair> keyValuePairs);
    void Clear();
    bool SetSelection(int n);
    int GetSelection();

    bool textOk;
    int pendingIndex;

protected:
    void OnKeyDown(wxKeyEvent &event);
    void OnTextChanged(wxCommandEvent &event);
    void OnMouseWheelMoved(wxMouseEvent &event);
    void OnKillFocus(wxFocusEvent &event);
    ComboBoxMapPopup *m_popup;

    DECLARE_DYNAMIC_CLASS(ComboBoxMap)
    DECLARE_EVENT_TABLE()

};

#endif // STD_COMBOBOX_H

