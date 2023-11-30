#include "PCInfo.h"


std::string PCInfo::GetLAN()
{
    WSADATA wsadata;
    WSAStartup(MAKEWORD(1, 1), &wsadata);


    //ホスト名を取得する
    char hostname[256];
    gethostname(hostname, sizeof(hostname));

    //ホスト名からIPアドレスを取得する
    HOSTENT* hostend = gethostbyname(hostname);

    IN_ADDR inaddr;
    memcpy(&inaddr, hostend->h_addr_list[0], 4);
    char ip[256];
    strcpy_s(ip, inet_ntoa(inaddr));


    WSACleanup();
    return ip;
}

std::string PCInfo::GetWAN()
{
    HINTERNET hInternet, hConnect;
    char buffer[256];
    DWORD bytesRead;

    hInternet = InternetOpen("IPFetch", INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0);
    hConnect = InternetOpenUrl(hInternet, "https://ipinfo.io/ip", NULL, 0, INTERNET_FLAG_RELOAD, 0);

    if (InternetReadFile(hConnect, buffer, sizeof(buffer), &bytesRead) && bytesRead > 0) {
        buffer[bytesRead] = '\0';
        return buffer;
    }
    else {
        return "error";
    }
}

std::string PCInfo::GetuserName()
{
    // バッファサイズ
    DWORD size = 50;

    // バッファ
    char buffer[30];

    // ユーザー名を取得
    if (GetUserNameA(buffer, &size)) {
        std::string userName(buffer);
        return userName;
    }
    else {
        std::cerr << "ユーザー名の取得に失敗しました。エラーコード: " << GetLastError() << std::endl;
    }
}

std::string PCInfo::GetPCName()
{
    // バッファサイズ
    DWORD size = MAX_COMPUTERNAME_LENGTH + 1;

    // バッファ
    char buffer[MAX_COMPUTERNAME_LENGTH + 1];

    // PC名を取得
    if (GetComputerNameA(buffer, &size)) {
        std::string computerName(buffer);
        return computerName;
    }
    else {
        return "error";
    }
}

int PCInfo::GetCore()
{
    SYSTEM_INFO sysInfo;
    GetSystemInfo(&sysInfo);

    return sysInfo.dwNumberOfProcessors;
}
