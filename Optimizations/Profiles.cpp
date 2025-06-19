#include "Tasks/SetRegistries.cpp"
#include "Tasks/DisableServices.cpp"

class Profiles
{
    int profile = 0;

    [[nodiscard]]
    static
    constexpr
    bool RunCmd()
    {
        return true;
    }

    [[nodiscard]]
    static
    constexpr
    bool RunSvc()
    {
        const bool isSvcRunOk = DisableServices::RunSvcFromConfig();
        return isSvcRunOk;
    }

    [[nodiscard]]
    static
    bool RunRegistries()
    {
        const bool isRegistryRunOk = SetRegistries::RunRegistryFromConfig();
        return isRegistryRunOk;
    }

    public:

    [[nodiscard]]
    static
    bool RunOptimize(const unsigned int p)
    {
        std::cout << "RunOptimize: " << p << '\n';
        constexpr bool isRunCmdsSuccess = Profiles::RunCmd();
        const bool isRunSvcSuccess = Profiles::RunSvc();
        const bool isRunRegSuccess = Profiles::RunRegistries();
        return isRunCmdsSuccess && isRunSvcSuccess && isRunRegSuccess;
    }
};