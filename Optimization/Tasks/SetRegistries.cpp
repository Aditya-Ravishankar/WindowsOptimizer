//
// Created by adity on 6/16/2025.
//
#include <unordered_map>
#include <windows.h>
#include "../Util/TemplateParser.cpp"

class SetRegistries
{
public:
    SetRegistries() = delete;

    [[nodiscard]]
    static
    bool UpsertRegistryKey(const HKEY & hive, const std::string & path, const DWORD & type, const std::string & name, const std::string & data)
    {
        bool isUpsertOk;

        HKEY hKey;
        const LPCSTR subKey = path.c_str();
        const LPCSTR valueName = name.c_str();
        const LPCSTR valueData = data.c_str();

        // Create or open the registry key
        long result = RegCreateKeyExA(
            hive,                       // Root key
            subKey,                     // Subkey path
            0,                          // Reserved, must be 0
            nullptr,                    // Class type
            REG_OPTION_NON_VOLATILE,    // Option
            KEY_WRITE,                  // Desired access
            nullptr,                    // Security attributes
            &hKey,                      // Handle to opened key
            nullptr                     // Disposition
        );

        if (result == ERROR_SUCCESS)
        {
            // Set the value
            result = RegSetValueExA(
                hKey,                                           // Handle to key
                valueName,                                      // Value name
                0,                                              // Reserved
                type,                                           // Value type
                reinterpret_cast<const BYTE *>(valueData),      // Data
                (DWORD)(strlen(valueData) + 1)                  // Data size
            );

            if (result == ERROR_SUCCESS)
            {
                isUpsertOk = true;
            }
            else
            {
                isUpsertOk = false;
            }
            RegCloseKey(hKey);
        }
        else
        {
            isUpsertOk = false;
        }
        return isUpsertOk;
    }

    [[nodiscard]]
    static
    bool RunRegistryFromConfig()
    {
        using namespace std;

        std::unordered_map<std::string, HKEY> hiveMap;
        std::unordered_map<std::string, DWORD> keyTypeMap;

        hiveMap.insert({"HKEY_CLASSES_ROOT", HKEY_CLASSES_ROOT});
        hiveMap.insert({"HKEY_CURRENT_USER", HKEY_CURRENT_USER});
        hiveMap.insert({"HKEY_LOCAL_MACHINE", HKEY_LOCAL_MACHINE});
        hiveMap.insert({"HKEY_USERS", HKEY_USERS});
        hiveMap.insert({"HKEY_PERFORMANCE_DATA", HKEY_PERFORMANCE_DATA});
        hiveMap.insert({"HKEY_PERFORMANCE_TEXT", HKEY_PERFORMANCE_TEXT});
        hiveMap.insert({"HKEY_PERFORMANCE_NLSTEXT", HKEY_PERFORMANCE_NLSTEXT});
        hiveMap.insert({"HKEY_CURRENT_CONFIG", HKEY_CURRENT_CONFIG});
        hiveMap.insert({"HKEY_DYN_DATA", HKEY_DYN_DATA});
        hiveMap.insert({"HKEY_CURRENT_USER_LOCAL_SETTINGS", HKEY_CURRENT_USER_LOCAL_SETTINGS});

        keyTypeMap.insert({"REG_NONE", REG_NONE});
        keyTypeMap.insert({"REG_SZ", REG_SZ});
        keyTypeMap.insert({"REG_EXPAND_SZ", REG_EXPAND_SZ});
        keyTypeMap.insert({"REG_BINARY", REG_BINARY});
        keyTypeMap.insert({"REG_DWORD", REG_DWORD});
        keyTypeMap.insert({"REG_DWORD_LITTLE_ENDIAN", REG_DWORD_LITTLE_ENDIAN});
        keyTypeMap.insert({"REG_DWORD_BIG_ENDIAN", REG_DWORD_BIG_ENDIAN});
        keyTypeMap.insert({"REG_LINK", REG_LINK});
        keyTypeMap.insert({"REG_MULTI_SZ", REG_MULTI_SZ});
        keyTypeMap.insert({"REG_RESOURCE_LIST", REG_RESOURCE_LIST});
        keyTypeMap.insert({"REG_FULL_RESOURCE_DESCRIPTOR", REG_FULL_RESOURCE_DESCRIPTOR});
        keyTypeMap.insert({"REG_RESOURCE_REQUIREMENTS_LIST", REG_RESOURCE_REQUIREMENTS_LIST});
        keyTypeMap.insert({"REG_QWORD", REG_QWORD});
        keyTypeMap.insert({"REG_QWORD_LITTLE_ENDIAN", REG_QWORD_LITTLE_ENDIAN});


        const vector < vector < string >> registryConfig = TemplateParser::GetRegistryConfig();

        bool isRunOk = true;
        for (const auto &r: registryConfig)
        {
            const HKEY& hive = hiveMap.at(r.at(0));
            const string& path = r.at(1);
            const DWORD type = keyTypeMap.at(r.at(2));
            const string& name = r.at(3);
            const string& data = r.at(4);

            const bool isUpsertOk = UpsertRegistryKey(hive, path, type, name, data);
            if (isUpsertOk == false)
            {
                isRunOk = false;
                break;
            }
        }
        return isRunOk;
    }
};