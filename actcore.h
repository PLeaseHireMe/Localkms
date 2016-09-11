#include<windows.h>
#include<string.h>
char *getbit();
char *getwinver();
char *GetActivateKey();
int check();
void install();
void uninstall();
void act();
void copykmsfiles();
char *getbit()
{
    char *OStype;
    HKEY hKey;
    RegOpenKey(HKEY_LOCAL_MACHINE,"Software\\Microsoft\\Windows NT\\currentversion",&hKey);
    char szpath[500];
    DWORD dwSize = sizeof(szpath);
    RegQueryValueEx(hKey,"buildlabex",NULL,NULL,(LPBYTE)szpath,&dwSize);
    char str[500];
    wsprintf(str,"%s",szpath);
    char *p="amd64";
    if(strstr(str,p))
        OStype="x64";
        else
        OStype="Win32";
    return OStype;
}
char *getwinver()
{
    char *wver;
    HKEY hKey;
    RegOpenKey(HKEY_LOCAL_MACHINE,"Software\\Microsoft\\Windows NT\\currentversion",&hKey);
    char szpath[500];
    DWORD dwSize = sizeof(szpath);
    RegQueryValueEx(hKey,"EditionID",NULL,NULL,(LPBYTE)szpath,&dwSize);
    char str[500];
    wsprintf(str,"%s",szpath);
    wver=str;
    return wver;
}
char *GetActivateKey()
{
    char *ActivateKey;
    if(strcmp(getwinver(),"Core")==0)
        ActivateKey="TX9XD-98N7V-6WMQ6-BX7FG-H8Q99";
    else if(strcmp(getwinver(),"CoreCountrySpecific")==0)
        ActivateKey="PVMJN-6DFY6-9CCP6-7BKTT-D3WVR";
    else if(strcmp(getwinver(),"CoreN")==0)
        ActivateKey="3KHY7-WNT83-DGQKR-F7HPR-844BM";
    else if(strcmp(getwinver(),"CoreSingleLanguage")==0)
        ActivateKey="7HNRX-D7KGG-3K4RQ-4WPJ4-YTDFH";
    else if(strcmp(getwinver(),"ProfessionalStudent")==0)
        ActivateKey="YNXW3-HV3VB-Y83VG-KPBXM-6VH3Q";
    else if(strcmp(getwinver(),"ProfessionalStudentN")==0)
        ActivateKey="8G9XJ-GN6PJ-GW787-MVV7G-GMR99";
    else if(strcmp(getwinver(),"Professional")==0)
        ActivateKey="GCRJD-8NW9H-F2CDX-CCM8D-9D6T9";
    else if(strcmp(getwinver(),"ProfessionalN")==0)
        ActivateKey="HMCNV-VVBFX-7HMBH-CTY9B-B4FXY";
    else if(strcmp(getwinver(),"ProfessionalSN")==0)
        ActivateKey="8Q36Y-N2F39-HRMHT-4XW33-TCQR4";
    else if(strcmp(getwinver(),"ProfessionalWMC")==0)
        ActivateKey="NKPM6-TCVPT-3HRFX-Q4H9B-QJ34Y";
    else if(strcmp(getwinver(),"Enterprise")==0)
        ActivateKey="NPPR9-FWDCX-D2C8J-H872K-2YT43";
    else if(strcmp(getwinver(),"EnterpriseN")==0)
        ActivateKey="DPH2V-TTNVB-4X9Q3-TJR4H-KHJW4";
    else if(strcmp(getwinver(),"Education")==0)
        ActivateKey="NW6C2-QMPVW-D7KKK-3GKT6-VCFB2";
    else if(strcmp(getwinver(),"EducationN")==0)
        ActivateKey="2WH4N-8QGBV-H22JP-CT43Q-MDWWJ";
    else if(strcmp(getwinver(),"EnterpriseS")==0)
        ActivateKey="WNMTR-4C88C-JK8YV-HQ7T2-76DF9";
    else if(strcmp(getwinver(),"EnterpriseSN")==0)
        ActivateKey="2F77B-TNFGY-69QQF-B8YKP-D69TJ";
    return ActivateKey;
}
int check()
{
    int ready;
    HKEY hKey;
    RegOpenKey(HKEY_LOCAL_MACHINE,"Software\\Microsoft\\Windows NT\\currentversion",&hKey);
    char szpath[500];
    DWORD dwSize = sizeof(szpath);
    RegQueryValueEx(hKey,"ProductName",NULL,NULL,(LPBYTE)szpath,&dwSize);
    char str[500];
    wsprintf(str,"%s",szpath);
    char *p="Windows 8.1";
    if(strstr(str,p))
        ready=1;
        else
        ready=0;
    return ready;
}
void install()
{
    copykmsfiles();
    system("net stop sppsvc");
    system("reg add \"HKLM\\SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Image File Execution Options\\SppExtComObj.exe\" /f /v \"Debugger\" /t REG_SZ /d \"KMS.exe\"");
    system("reg add \"HKLM\\SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Image File Execution Options\\SppExtComObj.exe\" /f /v \"KMS_Emulation\" /t REG_DWORD /d 1");
    system("reg add \"HKLM\\SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Image File Execution Options\\SppExtComObj.exe\" /f /v \"KMS_ActivationInterval\" /t REG_DWORD /d 120");
    system("reg add \"HKLM\\SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Image File Execution Options\\SppExtComObj.exe\" /f /v \"KMS_RenewalInterval\" /t REG_DWORD /d 10080");
    system("reg add \"HKLM\\SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Image File Execution Options\\SppExtComObj.exe\" /f /v \"Windows\" /t REG_SZ /d Random");
    system("net start sppsvc");
}
void uninstall()
{
    system("net stop sppsvc");
    system("reg delete \"HKLM\\SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Image File Execution Options\\SppExtComObj.exe\" /f");
    system("del /f /q \"%SystemRoot%\\system32\\KMS.exe\"");
    system("del /f /q \"%SystemRoot%\\system32\\KMSHook.dll\"");
    system("net start sppsvc");
}
void act()
{
    char p[500]="";
    strcat(p,"slmgr.vbs /ipk ");
    strcat(p,GetActivateKey());
    system(p);
    system("slmgr.vbs /skms 0.0.0.0");
    system("slmgr.vbs /ato");
}
void copykmsfiles()
{
    char srcpath[MAX_PATH];
    GetCurrentDirectory(MAX_PATH,srcpath);
    strcat(srcpath,"\\");
    strcat(srcpath,getbit());
    strcat(srcpath," ");
    char* pathvar;
    char dstpath[50]="";
    char* cs=" /s /f /h /y";
    pathvar = getenv("windir");
    strcat(dstpath,pathvar);
    strcat(dstpath,"\\System32\\");
    char runcopy[50]="cmd /c xcopy ";
    strcat(runcopy,srcpath);
    strcat(runcopy,dstpath);
    strcat(runcopy,cs);
    system(runcopy);
}


