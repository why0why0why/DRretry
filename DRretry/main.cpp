#include <windows.h>
#include <iostream>
#include <shlobj.h>
#include <string>
#include <fstream>

using namespace std;

int main()
{
    int i = 0, j = 0;
    char my_documents[MAX_PATH];

    HRESULT result = SHGetFolderPathA(NULL, CSIDL_PERSONAL, NULL, SHGFP_TYPE_CURRENT, my_documents);

    if (result != S_OK)
    {
        cout << "Error: " << result << "\n";
        return 1;
    }
    else
    {
        wstring path, section[10];
        wchar_t sectionstr[256], path16[256];
        size_t size = 0;
        mbstowcs_s(&size, path16, my_documents, 256);
        path = path16;
        path += L"\\desktop.ini";
        GetPrivateProfileSectionNames(sectionstr, 250, path.data());
        i = 0;
        j = 0;
        while (true)
        {
            if (sectionstr[i] == '\0' && sectionstr[i - 1] == '\0')
            {
                break;
            }
            section[j] = sectionstr + i;
            if (section[j] == L".ShellClassInfo")
            {
                i += section[j].size() + 1;
                j++;
                continue;
            }
            else
            {
                WritePrivateProfileStruct(section[j].data(), NULL, NULL, 0, path.data());
                i += section[j].size() + 1;
                j++;
            }
        }
        RegDeleteTree(HKEY_CURRENT_USER, L"Software\\DmitriRender");
        system("pause");
    }
    return 0;
}