/***************************************************************
 * Name:      sdddMain.h
 * Purpose:   Defines Application Frame
 * Author:     ()
 * Created:   2023-03-20
 * Copyright:  ()
 * License:
 **************************************************************/

#ifndef SDDDMAIN_H
#define SDDDMAIN_H

//(*Headers(sdddFrame)
#include <wx/button.h>
#include <wx/frame.h>
#include <wx/richtext/richtextctrl.h>
#include <wx/textctrl.h>
//*)

class sdddFrame: public wxFrame
{
    public:

        sdddFrame(wxWindow* parent,wxWindowID id = -1);
        virtual ~sdddFrame();

    private:

        //(*Handlers(sdddFrame)
        void OnQuit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        void OnClose(wxCloseEvent& event);
        void OnTextCtrl1Text(wxCommandEvent& event);
        void OnBitmapButton1Click(wxCommandEvent& event);
        void OnClose1(wxCloseEvent& event);
        void OnTextCtrl1Text1(wxCommandEvent& event);
        void OnButton1Click(wxCommandEvent& event);
        void OnRichTextCtrl2Text(wxCommandEvent& event);
        void OnRichTextCtrl1Text(wxCommandEvent& event);
        void OnRichTextCtrl3Text(wxCommandEvent& event);
        //*)

        //(*Identifiers(sdddFrame)
        static const long ID_TEXTCTRL1;
        static const long ID_BUTTON1;
        static const long ID_RICHTEXTCTRL1;
        static const long ID_RICHTEXTCTRL2;
        static const long ID_RICHTEXTCTRL3;
        //*)

        //(*Declarations(sdddFrame)
        wxButton* Button1;
        wxRichTextCtrl* RichTextCtrl1;
        wxRichTextCtrl* RichTextCtrl2;
        wxRichTextCtrl* RichTextCtrl3;
        wxTextCtrl* TextCtrl1;
        //*)

        DECLARE_EVENT_TABLE()
};

#endif // SDDDMAIN_H
