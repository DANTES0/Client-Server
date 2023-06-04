/***************************************************************
 * Name:      sdddMain.cpp
 * Purpose:   Code for Application Frame
 * Author:     ()
 * Created:   2023-03-20
 * Copyright:  ()
 * License:
 **************************************************************/

#include "sdddMain.h"
#include <wx/msgdlg.h>
#define WIN32_LEAN_AND_MEAN
#include <stdio.h>
#include <winsock2.h>
#include <WS2tcpip.h>
#include <windows.h>
#include <ctime>
#include <string>
#include <fstream>
#include <iostream>
#include <wx/textfile.h>
#include "wx/file.h"



//(*InternalHeaders(sdddFrame)
#include <wx/font.h>
#include <wx/intl.h>
#include <wx/settings.h>
#include <wx/string.h>
//*)


//helper functions
enum wxbuildinfoformat {
    short_f, long_f };

wxString wxbuildinfo(wxbuildinfoformat format)
{
    wxString wxbuild(wxVERSION_STRING);

    if (format == long_f )
    {
#if defined(__WXMSW__)
        wxbuild << _T("-Windows");
#elif defined(__UNIX__)
        wxbuild << _T("-Linux");
#endif

#if wxUSE_UNICODE
        wxbuild << _T("-Unicode build");
#else
        wxbuild << _T("-ANSI build");
#endif // wxUSE_UNICODE
    }

    return wxbuild;
}

//(*IdInit(sdddFrame)
const long sdddFrame::ID_TEXTCTRL1 = wxNewId();
const long sdddFrame::ID_BUTTON1 = wxNewId();
const long sdddFrame::ID_RICHTEXTCTRL1 = wxNewId();
const long sdddFrame::ID_RICHTEXTCTRL2 = wxNewId();
const long sdddFrame::ID_RICHTEXTCTRL3 = wxNewId();
//*)
WSADATA wsaDAta;
ADDRINFO hints;
ADDRINFO* addrResult = NULL;
SOCKET ConnectSocket = INVALID_SOCKET;

char recvBuffer[512];

int result;
int menu = 10;
int i = 0;
int flag_1 = 0, flag_2 = 0, flag_3 = 0;

BEGIN_EVENT_TABLE(sdddFrame,wxFrame)
    //(*EventTable(sdddFrame)
    //*)
END_EVENT_TABLE()

sdddFrame::sdddFrame(wxWindow* parent,wxWindowID id)
{
    //(*Initialize(sdddFrame)
    Create(parent, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE|wxBORDER_STATIC, _T("wxID_ANY"));
    SetClientSize(wxSize(1058,471));
    SetBackgroundColour(wxColour(232,221,232));
    TextCtrl1 = new wxTextCtrl(this, ID_TEXTCTRL1, wxEmptyString, wxPoint(24,400), wxSize(656,37), 0, wxDefaultValidator, _T("ID_TEXTCTRL1"));
    Button1 = new wxButton(this, ID_BUTTON1, _("Enter"), wxPoint(688,400), wxSize(112,40), 0, wxDefaultValidator, _T("ID_BUTTON1"));
    Button1->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_ACTIVECAPTION));
    RichTextCtrl1 = new wxRichTextCtrl(this, ID_RICHTEXTCTRL1, wxEmptyString, wxPoint(368,32), wxSize(312,336), wxRE_MULTILINE|wxRE_READONLY, wxDefaultValidator, _T("ID_RICHTEXTCTRL1"));
    wxRichTextAttr rchtxtAttr_1;
    rchtxtAttr_1.SetBulletStyle(wxTEXT_ATTR_BULLET_STYLE_ALIGN_LEFT);
    wxFont Font_1(10,wxFONTFAMILY_MODERN,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_BOLD,false,_T("Courier New"),wxFONTENCODING_DEFAULT);
    rchtxtAttr_1.SetFontFaceName(Font_1.GetFaceName());
    rchtxtAttr_1.SetFontSize(Font_1.GetPointSize());
    rchtxtAttr_1.SetFontStyle(Font_1.GetStyle());
    rchtxtAttr_1.SetFontUnderlined(Font_1.GetUnderlined());
    rchtxtAttr_1.SetFontWeight(Font_1.GetWeight());
    RichTextCtrl1->SetBasicStyle(rchtxtAttr_1);
    RichTextCtrl2 = new wxRichTextCtrl(this, ID_RICHTEXTCTRL2, wxEmptyString, wxPoint(24,32), wxSize(312,336), wxRE_READONLY, wxDefaultValidator, _T("ID_RICHTEXTCTRL2"));
    wxRichTextAttr rchtxtAttr_2;
    rchtxtAttr_2.SetBulletStyle(wxTEXT_ATTR_BULLET_STYLE_ALIGN_LEFT);
    wxFont Font_2(10,wxFONTFAMILY_MODERN,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_BOLD,false,_T("Courier New"),wxFONTENCODING_DEFAULT);
    rchtxtAttr_2.SetFontFaceName(Font_2.GetFaceName());
    rchtxtAttr_2.SetFontSize(Font_2.GetPointSize());
    rchtxtAttr_2.SetFontStyle(Font_2.GetStyle());
    rchtxtAttr_2.SetFontUnderlined(Font_2.GetUnderlined());
    rchtxtAttr_2.SetFontWeight(Font_2.GetWeight());
    RichTextCtrl2->SetBasicStyle(rchtxtAttr_2);
    RichTextCtrl3 = new wxRichTextCtrl(this, ID_RICHTEXTCTRL3, wxEmptyString, wxPoint(712,32), wxSize(312,336), wxRE_MULTILINE|wxRE_READONLY, wxDefaultValidator, _T("ID_RICHTEXTCTRL3"));
    wxRichTextAttr rchtxtAttr_3;
    rchtxtAttr_3.SetBulletStyle(wxTEXT_ATTR_BULLET_STYLE_ALIGN_LEFT);
    wxFont Font_3(10,wxFONTFAMILY_MODERN,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,_T("Courier New"),wxFONTENCODING_DEFAULT);
    rchtxtAttr_3.SetFontFaceName(Font_3.GetFaceName());
    rchtxtAttr_3.SetFontSize(Font_3.GetPointSize());
    rchtxtAttr_3.SetFontStyle(Font_3.GetStyle());
    rchtxtAttr_3.SetFontUnderlined(Font_3.GetUnderlined());
    rchtxtAttr_3.SetFontWeight(Font_3.GetWeight());
    RichTextCtrl3->SetBasicStyle(rchtxtAttr_3);

    Connect(ID_TEXTCTRL1,wxEVT_COMMAND_TEXT_UPDATED,(wxObjectEventFunction)&sdddFrame::OnTextCtrl1Text1);
    Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&sdddFrame::OnButton1Click);
    Connect(ID_RICHTEXTCTRL1,wxEVT_COMMAND_TEXT_UPDATED,(wxObjectEventFunction)&sdddFrame::OnRichTextCtrl1Text);
    Connect(ID_RICHTEXTCTRL2,wxEVT_COMMAND_TEXT_UPDATED,(wxObjectEventFunction)&sdddFrame::OnRichTextCtrl2Text);
    Connect(ID_RICHTEXTCTRL3,wxEVT_COMMAND_TEXT_UPDATED,(wxObjectEventFunction)&sdddFrame::OnRichTextCtrl3Text);
    //*)
    result = WSAStartup(MAKEWORD(2,2), &wsaDAta);
    if(result!=0)
       {

       }

    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

     result = getaddrinfo("localhost", "666", &hints, &addrResult);
     if (result!=0)
    {

    }
    ConnectSocket = socket(addrResult->ai_family, addrResult -> ai_socktype, addrResult ->ai_protocol);
    if(ConnectSocket == INVALID_SOCKET)
    {

    }
    result = connect(ConnectSocket, addrResult->ai_addr, (int)addrResult->ai_addrlen);
    if(result == SOCKET_ERROR)
    {
       RichTextCtrl2->WriteText("No connection.");
    }
    else
    {
       RichTextCtrl2->WriteText("Connected.\n Список функций:\n 1. Посчитать количество гласных букв в строке.\n 2. Посчитать количество согласных букв в строке.\n 3. Проверить слово на полиндром.");
    }
    RichTextCtrl1->WriteText("Результат запроса:\n");


    std::string line;
    std::ifstream in("History.txt");
    if(in.is_open())
    {
        while(getline(in,line))
        {
            RichTextCtrl3->WriteText(line+"\n");
        }
    }
    in.close();

}

sdddFrame::~sdddFrame()
{
    //(*Destroy(sdddFrame)
    //*)
}

void sdddFrame::OnTextCtrl1Text(wxCommandEvent& event)
{
}

void sdddFrame::OnBitmapButton1Click(wxCommandEvent& event)
{
}

void sdddFrame::OnTextCtrl1Text1(wxCommandEvent& event) //нижняя штука
{
}

void sdddFrame::OnButton1Click(wxCommandEvent& event) //ентр
{
    wxString a;
    a = TextCtrl1->GetValue();

    if (a=="1")
    {
            RichTextCtrl1->SetValue("");
            RichTextCtrl1->WriteText("Результат запроса:\n");
            RichTextCtrl1->WriteText("Напишите строку:");
            TextCtrl1->SetValue("");
            flag_1 = 1;
    }
    if (flag_1 == 1)    //1
    {
        if (TextCtrl1->GetValue() != "")
        {
            TextCtrl1->SetValue("");
            time_t seconds = time(NULL);
            tm* timeinfo = localtime(&seconds);

            wxTextFile file;

            char* sendData = new char[128];
            ZeroMemory(sendData, 128);

            strncpy(sendData, (const char*)a.mb_str(wxConvUTF8),128);

            char* sendBufferCase1 = "vowels";
            char proccesed[512] = "vowelsproccesed";
            result = send(ConnectSocket, sendBufferCase1,(int)strlen(sendBufferCase1), 0 );
            if(result == SOCKET_ERROR)
            {
                RichTextCtrl1->WriteText("Send error function 1");
            }
            ZeroMemory(recvBuffer, sizeof(recvBuffer));
            result = recv(ConnectSocket, recvBuffer, 512, 0);
            if(result >0)//проверка отправки
            {

            }
            else if(result == 0)
                RichTextCtrl1->WriteText("Connection closed");
            else
                RichTextCtrl1->WriteText("recv failed with error" );
            if(strcmp(recvBuffer, proccesed) == 0)
            {
                RichTextCtrl1 ->WriteText("\n");
                result = send(ConnectSocket, sendData, (int)strlen(sendData),0);
                if(result == SOCKET_ERROR)
                {
                    //Destroy("Send error function3", ConnectSocket, addrResult);
                    RichTextCtrl1->WriteText("\n Send Error 2");
                }
                ZeroMemory(recvBuffer, sizeof(recvBuffer));
                result = recv(ConnectSocket, recvBuffer, 512, 0);
                if(result >0)
                {
                    wxString mystring;
                    mystring << result;
                    RichTextCtrl3->WriteText("Функция: Vowels");
                    RichTextCtrl3->WriteText("\nОтправленные данные: ");
                    RichTextCtrl3->WriteText(sendData);
                    RichTextCtrl3->WriteText("\nОбработанные данные: ");
                    RichTextCtrl3->WriteText(recvBuffer);
                    RichTextCtrl3->WriteText("\nВремя запроса: ");
                    RichTextCtrl3->WriteText(asctime(timeinfo));
                    RichTextCtrl3->WriteText("-----------------------\n");

                    RichTextCtrl1->WriteText("\nКоличество гласных букв ");
                    RichTextCtrl1->WriteText(recvBuffer);
                    RichTextCtrl1->WriteText(" в строке");
                    RichTextCtrl1->WriteText(" \" ");
                    RichTextCtrl1->WriteText(sendData);
                    RichTextCtrl1->WriteText(" \" ");

                    std::ofstream out("History.txt",std::ios::out | std::ios::trunc);
                    if(out.is_open())
                    {
                        out<<"";
                        int nLines = RichTextCtrl3->GetNumberOfLines();
                        for (int nLine =0; nLine <nLines; nLine++)
                        {
                            out << RichTextCtrl3->GetLineText(nLine) << std::endl;
                        }
                    }
                }
                else if(result == 0)
                    RichTextCtrl1->WriteText("\n Connection Closed");
                else
                    RichTextCtrl1->WriteText("recv failed with error");
            }
            delete(sendData);
            flag_1 = 0;
        }

    }
    a = TextCtrl1->GetValue();
    if (a=="2")
    {
        RichTextCtrl1->SetValue("");
        RichTextCtrl1->WriteText("Результат запроса:\n");
        RichTextCtrl1->WriteText("Напишите строку:");
        TextCtrl1->SetValue("");
        flag_2 = 1;
    }

    if (flag_2 == 1)    //2
    {
        if (TextCtrl1->GetValue() != "")
        {
            TextCtrl1->SetValue("");
            time_t seconds = time(NULL);
            tm* timeinfo = localtime(&seconds);

            wxTextFile file;

            char* sendData = new char[128];
            ZeroMemory(sendData, 128);

            strncpy(sendData, (const char*)a.mb_str(wxConvUTF8),128);

            char* sendBufferCase1 = "consonants";
            char proccesed[512] = "consonantsproccesed";
            result = send(ConnectSocket, sendBufferCase1,(int)strlen(sendBufferCase1), 0 );
            if(result == SOCKET_ERROR)
            {
                RichTextCtrl1->WriteText("Send error function 1");
            }
            ZeroMemory(recvBuffer, sizeof(recvBuffer));
            result = recv(ConnectSocket, recvBuffer, 512, 0);
            if(result >0)//проверка отправки
            {

            }
            else if(result == 0)
                RichTextCtrl1->WriteText("Connection closed");
            else
                RichTextCtrl1->WriteText("recv failed with error" );
            if(strcmp(recvBuffer, proccesed) == 0)
            {
                RichTextCtrl1 ->WriteText("\n");
                result = send(ConnectSocket, sendData, (int)strlen(sendData),0);
                if(result == SOCKET_ERROR)
                {
                    //Destroy("Send error function3", ConnectSocket, addrResult);
                    RichTextCtrl1->WriteText("\n Send Error 2");
                }
                ZeroMemory(recvBuffer, sizeof(recvBuffer));
                result = recv(ConnectSocket, recvBuffer, 512, 0);
                if(result >0)
                {
                    wxString mystring;
                    mystring << result;
                    RichTextCtrl3->WriteText("Функция: Consonants");
                    RichTextCtrl3->WriteText("\nОтправленные данные: ");
                    RichTextCtrl3->WriteText(sendData);
                    RichTextCtrl3->WriteText("\nОбработанные данные: ");
                    RichTextCtrl3->WriteText(recvBuffer);
                    RichTextCtrl3->WriteText("\nВремя запроса: ");
                    RichTextCtrl3->WriteText(asctime(timeinfo));
                    RichTextCtrl3->WriteText("-----------------------\n");

                    RichTextCtrl1->WriteText("\nКоличество согласных букв ");
                    RichTextCtrl1->WriteText(recvBuffer);
                    RichTextCtrl1->WriteText(" в строке");
                    RichTextCtrl1->WriteText(" \" ");
                    RichTextCtrl1->WriteText(sendData);
                    RichTextCtrl1->WriteText(" \" ");

                    std::ofstream out("History.txt",std::ios::out | std::ios::trunc);
                    if(out.is_open())
                    {
                        out<<"";
                        int nLines = RichTextCtrl3->GetNumberOfLines();
                        for (int nLine =0; nLine <nLines; nLine++)
                        {
                            out << RichTextCtrl3->GetLineText(nLine) << std::endl;
                        }
                    }
                }
                else if(result == 0)
                    RichTextCtrl1->WriteText("\n Connection Closed");
                else
                    RichTextCtrl1->WriteText("recv failed with error");
            }
            delete(sendData);
            flag_2 = 0;
        }

    }

    a = TextCtrl1->GetValue();
    if (a=="3")
    {
        RichTextCtrl1->SetValue("");
        RichTextCtrl1->WriteText("Результат запроса:\n");
        RichTextCtrl1->WriteText("Напишите строку:");
        TextCtrl1->SetValue("");
        flag_3 = 1;
    }

    if (flag_3 == 1)    //3
    {
        if (TextCtrl1->GetValue() != "")
        {
            TextCtrl1->SetValue("");
            time_t seconds = time(NULL);
            tm* timeinfo = localtime(&seconds);

            wxTextFile file;

            char* sendData = new char[128];
            ZeroMemory(sendData, 128);

            strncpy(sendData, (const char*)a.mb_str(wxConvUTF8),128);

            char* sendBufferCase1 = "check_polindrom";
            char proccesed[512] = "check_polindromproccesed";
            result = send(ConnectSocket, sendBufferCase1,(int)strlen(sendBufferCase1), 0 );
            if(result == SOCKET_ERROR)
            {
                RichTextCtrl1->WriteText("Send error function 3");
            }
            ZeroMemory(recvBuffer, sizeof(recvBuffer));
            result = recv(ConnectSocket, recvBuffer, 512, 0);
            if(result >0)//проверка отправки
            {

            }
            else if(result == 0)
                RichTextCtrl1->WriteText("Connection closed");
            else
                RichTextCtrl1->WriteText("recv failed with error" );
            if(strcmp(recvBuffer, proccesed) == 0)
            {
                RichTextCtrl1 ->WriteText("\n");
                result = send(ConnectSocket, sendData, (int)strlen(sendData),0);
                if(result == SOCKET_ERROR)
                {
                    //Destroy("Send error function3", ConnectSocket, addrResult);
                    RichTextCtrl1->WriteText("\n Send Error 2");
                }
                ZeroMemory(recvBuffer, sizeof(recvBuffer));
                result = recv(ConnectSocket, recvBuffer, 512, 0);
                if(result >0)
                {
                    wxString mystring;
                    mystring << result;
                    RichTextCtrl3->WriteText("Функция: Check_polindrom");
                    RichTextCtrl3->WriteText("\nОтправленные данные: ");
                    RichTextCtrl3->WriteText(sendData);
                    RichTextCtrl3->WriteText("\nОбработанные данные: ");
                    RichTextCtrl3->WriteText(recvBuffer);
                    RichTextCtrl3->WriteText("\nВремя запроса: ");
                    RichTextCtrl3->WriteText(asctime(timeinfo));
                    RichTextCtrl3->WriteText("-----------------------\n");

                    RichTextCtrl1->WriteText("\nСлово ");
                    RichTextCtrl1->WriteText(" \" ");
                    RichTextCtrl1->WriteText(sendData);
                    RichTextCtrl1->WriteText(" \" является палиндромом:  ");
                    RichTextCtrl1->WriteText(recvBuffer);


                    std::ofstream out("History.txt",std::ios::out | std::ios::trunc);
                    if(out.is_open())
                    {
                        out<<"";
                        int nLines = RichTextCtrl3->GetNumberOfLines();
                        for (int nLine =0; nLine <nLines; nLine++)
                        {
                            out << RichTextCtrl3->GetLineText(nLine) << std::endl;
                        }
                    }
                }
                else if(result == 0)
                    RichTextCtrl1->WriteText("\n Connection Closed");
                else
                    RichTextCtrl1->WriteText("recv failed with error");
            }
            delete(sendData);
            flag_3 = 0;
        }

    }


}

void sdddFrame::OnRichTextCtrl2Text(wxCommandEvent& event) //левая штука
{
    RichTextCtrl2->SetFocus();
    RichTextCtrl2->GetCaret()->Hide();
}

void sdddFrame::OnRichTextCtrl1Text(wxCommandEvent& event) //правая штука
{
    RichTextCtrl1->SetFocus();
    RichTextCtrl1->GetCaret()->Hide();
}


void sdddFrame::OnRichTextCtrl3Text(wxCommandEvent& event)
{
    RichTextCtrl3->SetFocus();
    RichTextCtrl3->GetCaret()->Hide();
}

