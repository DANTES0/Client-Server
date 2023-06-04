#include<stdio.h>
#include<winsock2.h>
#include<windows.h>
#include<ws2tcpip.h>
#include<iostream>

#define WIN32_LEAN_AND_MEAN

using namespace std;

char* vowels(char* a)
{
    char vow[]="aeiouyAEIOUY";
    char *b = new char;
    int gl = 0, i, j;
    for(i=0; i<(strlen(a)); i++)
        for(j=0; j<strlen(vow); j++)
            if(a[i]==vow[j])
                gl++;
    itoa(gl, b, 10);
    return b;
}

char* consonants(char* a)
{
    char vow[]="aeiouyAEIOUY";
    char *b = new char;
    int gl = 0, i, j;
    for(i=0; i<(strlen(a)); i++)
        for(j=0; j<strlen(vow); j++)
            if(a[i]==vow[j])
                gl++;
    itoa(strlen(a)-gl, b, 10);
    return b;
}

char* check_polindrom(char* word)
{
    char *b = new char;
    int len = strlen(word);
    for(int i = 0; i < len/2; ++i)
    {
        if(word[i] != word[len-i-1])
        {
            return b = "No";
        }
    }
    return b = "Yes";
}

int main(int argc, char *argv[])
{
    int result;
    const char* sendBuffer = "Hello from Client!";
    char recvBuffer[512];
    WSADATA wsaData;
    ADDRINFO hints;
    ADDRINFO* addrResult = NULL;
    SOCKET ClientSocket = INVALID_SOCKET;
    SOCKET ListenSocket = INVALID_SOCKET;

    result = WSAStartup(MAKEWORD(2,2), &wsaData);
    if (result != 0)
    {
        cout <<"WSAStartup failed, result = "<< result <<endl;
        return 1;
    }


    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    hints.ai_flags = AI_PASSIVE;

    result = getaddrinfo(NULL, "666", &hints, &addrResult); // 1 Айпи компа 2 порт
    if (result != 0)
    {
        cout <<"getaddrinfo failed with error:  "<< result <<endl;
        WSACleanup();
        return 1;
    }

    ListenSocket = socket(addrResult->ai_family, addrResult->ai_socktype, addrResult->ai_protocol);
    if (ListenSocket == INVALID_SOCKET)
    {
        cout << "Socket creation failed" << endl;
        freeaddrinfo(addrResult);
        WSACleanup();
        return 1;
    }

    result = bind(ListenSocket, addrResult->ai_addr, (int)addrResult->ai_addrlen);
    if (result == SOCKET_ERROR)
    {
        cout << "Binding socket failed" << endl;
        closesocket(ListenSocket);
        ListenSocket = INVALID_SOCKET;
        freeaddrinfo(addrResult);
        WSACleanup();
        return 1;
    }

    result = listen(ListenSocket, SOMAXCONN);
    if (result == SOCKET_ERROR)
    {
        cout << "Listening socket failed" <<endl;
        closesocket(ListenSocket);
        ListenSocket = INVALID_SOCKET;
        freeaddrinfo(addrResult);
        WSACleanup();
        return 1;
    }

    ClientSocket = accept(ListenSocket, NULL, NULL);
    if (ClientSocket == INVALID_SOCKET)
    {
        cout << "Accepting socket failed" <<endl;
        closesocket(ListenSocket);
        ListenSocket = INVALID_SOCKET;
        freeaddrinfo(addrResult);
        WSACleanup();
        return 1;
    }

    closesocket(ListenSocket);

    do
    {
        char function1[512] = "vowels";
        char function2[512] = "consonants";
        char function3[512] = "check_polindrom";
        ZeroMemory(recvBuffer, sizeof(recvBuffer));
        result = recv(ClientSocket, recvBuffer, 512, 0);
        if(result >0)
        {
            cout << "Recived " << result << "bytes" << endl;
            cout << "Recived data " << recvBuffer << endl;
            if(strcmp(recvBuffer, function1) == 0)//проверка что запрошена функция 1
            {

                char* Procces = "vowelsproccesed";
                result = send(ClientSocket, Procces, (int)strlen(Procces),0);
                if(result == SOCKET_ERROR)
                {
                    cout << "Failed to send data back" << endl;
                    closesocket(ClientSocket);
                    freeaddrinfo(addrResult);
                    WSACleanup();
                    system("pause");
                    return 1;
                }
                ZeroMemory(recvBuffer, sizeof(recvBuffer));
                result = recv(ClientSocket, recvBuffer, 512, 0);
                if(result > 0)
                {
                    cout << "Recived " << result << " bytes" << endl;
                    cout << "Recived data " << recvBuffer << endl;//получает somedata
                }
                //обработка данных
                char *a;
                a = vowels(recvBuffer);
                cout << "New Data " << a << endl;
                result = send(ClientSocket, a, (int)strlen(a),0);
                if(result == SOCKET_ERROR)
                {
                    cout << "Failed to send data back" << endl;
                    closesocket(ClientSocket);
                    freeaddrinfo(addrResult);
                    WSACleanup();
                    system("pause");
                    return 1;
                }
            }
            if(strcmp(recvBuffer, function2) == 0)//проверка что запрошена функция 2
            {
                char* Procces = "consonantsproccesed";
                result = send(ClientSocket, Procces, (int)strlen(Procces),0);
                if(result == SOCKET_ERROR)
                {
                    cout << "Failed to send data back" << endl;
                    closesocket(ClientSocket);
                    freeaddrinfo(addrResult);
                    WSACleanup();
                    system("pause");
                    return 1;
                }
                ZeroMemory(recvBuffer, sizeof(recvBuffer));
                result = recv(ClientSocket, recvBuffer, 512, 0);
                if(result > 0)
                {
                    cout << "Recived " << result << "bytes" << endl;
                    cout << "Recived data " << recvBuffer << endl;//получает somedata
                }
                //обработка данных
                char *a;
                a = consonants(recvBuffer);
                cout << "New data " << a << endl;
                result = send(ClientSocket, a, (int)strlen(a),0);
                if(result == SOCKET_ERROR)
                {
                    cout << "Failed to send data back" << endl;
                    closesocket(ClientSocket);
                    freeaddrinfo(addrResult);
                    WSACleanup();
                    system("pause");
                    return 1;
                }
            }
            if(strcmp(recvBuffer, function3) == 0)//проерка что запрошена функция 1
            {
                char* Procces = "check_polindromproccesed";
                result = send(ClientSocket, Procces, (int)strlen(Procces),0);
                if(result == SOCKET_ERROR)
                {
                    cout << "Failed to send data back" << endl;
                    closesocket(ClientSocket);
                    freeaddrinfo(addrResult);
                    WSACleanup();
                    system("pause");
                    return 1;
                }
                ZeroMemory(recvBuffer, sizeof(recvBuffer));
                result = recv(ClientSocket, recvBuffer, 512, 0);
                if(result > 0)
                {
                    cout << "Recived " << result << "bytes" << endl;
                    cout << "Recived data " << recvBuffer << endl;//получает somedata
                }
                //обработка данных
                char *a;
                a = check_polindrom(recvBuffer);
                cout << "New data " << a << endl;
                result = send(ClientSocket, a, (int)strlen(a),0);
                if(result == SOCKET_ERROR)
                {
                    cout << "Failed to send data back" << endl;
                    closesocket(ClientSocket);
                    freeaddrinfo(addrResult);
                    WSACleanup();
                    system("pause");
                    return 1;
                }
            }
        }
        else if(result == 0)
        {
            cout << "Connection closing..." << endl;
            system("pause");
            return 0;

        }
        else
        {
            cout << "recv failed with error" << endl;
            closesocket(ClientSocket);
            freeaddrinfo(addrResult);
            WSACleanup();
            return 1;
        }

    }
    while(1);


    result = shutdown(ClientSocket, SD_SEND);
    if (result == SOCKET_ERROR)
    {
        cout << "shutdown client socked failed" << endl;
        closesocket(ClientSocket);
        freeaddrinfo(addrResult);
        WSACleanup();
        return 1;
    }
    closesocket(ClientSocket);
    freeaddrinfo(addrResult);
    WSACleanup();

    system("pause");
    return 0;
}




