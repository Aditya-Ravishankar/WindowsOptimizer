//
// Created by adity on 6/16/2025.
//

#include <windows.h>

class DisableServices
{
    public:

    DisableServices() = delete;

    [[nodiscard]]
    static
    bool DisableService(const std::string& serviceName)
    {
        const SC_HANDLE hSCManager = OpenSCManager(nullptr, nullptr, SC_MANAGER_ALL_ACCESS);
        if (hSCManager == nullptr)
        {
            return false;
        }

        const SC_HANDLE hService = OpenService(hSCManager, serviceName.c_str(), SERVICE_CHANGE_CONFIG);
        if (hService == nullptr)
        {
            CloseServiceHandle(hSCManager);
            return false;
        }

        const BOOL success = ChangeServiceConfig(
            hService,
            SERVICE_NO_CHANGE,        // Service type
            SERVICE_DISABLED,         // Start type
            SERVICE_NO_CHANGE,        // Error control
            nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr);


        CloseServiceHandle(hService);
        CloseServiceHandle(hSCManager);

        return success;
    }

    [[nodiscard]]
    static
    bool RunSvcFromConfig()
    {
        using namespace std;
        bool isSvcRunOk = true;
        const vector<string> services = TemplateParser::GetSvcConfig();
        for (const auto& s : services)
        {
            bool isSvcKillOk = DisableService(s);
            if (isSvcKillOk == false)
            {
                isSvcRunOk = false;
                break;
            }
        }
        return isSvcRunOk;
    }
};
