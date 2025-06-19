#include "Tasks/SetRegistries.cpp"
#include "Tasks/DisableServices.cpp"

class Optimize
{
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
        bool isOptimizeOk = true;
        bool isRunCmdsSuccess = true;
        bool isRunSvcSuccess = true;
        bool isRunRegSuccess = true;

        switch (p)
        {
            case 1:
                isRunCmdsSuccess = Optimize::RunCmd();
                isRunSvcSuccess = Optimize::RunSvc();
                isRunRegSuccess = Optimize::RunRegistries();
                isOptimizeOk = isRunCmdsSuccess && isRunSvcSuccess && isRunRegSuccess;

            case 2:
            case 3:
            case 4:
            case 5:
            case 6:
            default:
                break;;
        }

        return isOptimizeOk;
    }
};