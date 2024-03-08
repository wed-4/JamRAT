#include "FunMenu.h"

std::string FunMenu::ToggleTaskMgr()
{
    HKEY hKey;
    LONG result;

    // Open or create the registry key
    result = RegCreateKeyEx(
        HKEY_CURRENT_USER,                      // Hive
        "Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System", // Subkey
        0,                                      // Reserved
        NULL,                                   // Class
        REG_OPTION_NON_VOLATILE,                // Options
        KEY_ALL_ACCESS,                         // SAM desired
        NULL,                                   // Security attributes
        &hKey,                                  // Handle
        NULL                                    // Disposition
    );

    if (result == ERROR_SUCCESS) {
        DWORD dwValue;
        DWORD dwType = REG_DWORD;
        DWORD dwSize = sizeof(DWORD);

        // Check if the value exists
        result = RegQueryValueEx(
            hKey,                               // Handle
            "DisableTaskMgr",                  // Value name
            NULL,                               // Reserved
            &dwType,                            // Data type
            (LPBYTE)&dwValue,                   // Data buffer
            &dwSize                             // Data size
        );

        if (result == ERROR_FILE_NOT_FOUND) {
            // Value does not exist, set it to 1
            dwValue = 1;
            RegSetValueEx(
                hKey,                           // Handle
                "DisableTaskMgr",              // Value name
                0,                              // Reserved
                REG_DWORD,                      // Data type
                (const BYTE*)&dwValue,          // Data buffer
                sizeof(DWORD)                   // Data size
            );
            return "TaskManager is Disabled.";
        }
        else if (result == ERROR_SUCCESS) {
            // Value exists, delete it
            RegDeleteValue(
                hKey,                           // Handle
                "DisableTaskMgr"               // Value name
            );
            return "TaskManager is Enabled.";
        }

        // Close the registry key handle
        RegCloseKey(hKey);
    }
}
