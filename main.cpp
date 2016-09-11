#include <windows.h>
#include <commctrl.h>
#include <stdio.h>
#include "actcore.h"
#include "resource.h"

HINSTANCE hInst;

BOOL CALLBACK DlgMain(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch(uMsg)
    {
    case WM_INITDIALOG:
    {
        if(check()==1)
        {
        SetDlgItemText(hwndDlg,winver,getwinver());
        SetDlgItemText(hwndDlg,actkey,GetActivateKey());
        }
    }
    return TRUE;

    case WM_CLOSE:
    {
        EndDialog(hwndDlg, 0);
    }
    return TRUE;

    case WM_COMMAND:
    {
        switch(LOWORD(wParam))
        {
        case INSTALL_ACT:
            {
            if(check()==1)
             {
               install();
               act();
             }
             else{
                MessageBox(hwndDlg,"不支持的操作系统","提示",MB_OK);
             }
            return TRUE;
            }
        case ONLY_ACT:
            {
            if(check()==1)
             {
               install();
               act();
               uninstall();
             }
             else{
                MessageBox(hwndDlg,"不支持的操作系统","提示",MB_OK);
             }
             return TRUE;
            }
        case UNINSTALL_KMS:
            {
            if(check()==1)
             {
               uninstall();
             }
             else{
                MessageBox(hwndDlg,"不支持的操作系统","提示",MB_OK);
             }
            return TRUE;
            }
        }
    }
    return TRUE;
    }
    return FALSE;
}


int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
    hInst=hInstance;
    InitCommonControls();
    return DialogBox(hInst, MAKEINTRESOURCE(DLG_MAIN), NULL, (DLGPROC)DlgMain);
}
