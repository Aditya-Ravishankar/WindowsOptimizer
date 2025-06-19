//
// Created by adity on 6/16/2025.
//

#include <filesystem>
#include <string>
#include <vector>
#include <fstream>

class TemplateParser
{
public:

    [[nodiscard]]
    static
    std::vector <std::vector<std::string>> GetRegistryConfig()
    {
        using namespace std;
        vector <vector <string>> registryConfig;
        ifstream registryFile(filesystem::path("Templates/Registry.txt"));
        string hive, path, type, name, data;
        while (registryFile >> hive >> path >> type >> name >> data)
        {
            const vector <string> config = {hive, path, type, name, data};
            registryConfig.emplace_back(config);
        }
        return registryConfig;
    }

    [[nodiscard]]
    static
    std::vector<std::string> GetSvcConfig()
    {
        using namespace std;
        vector <string> svcConfig;
        ifstream svcFile(filesystem::path("Templates/services.txt"));
        string service;
        while (svcFile >> service)
        {
            svcConfig.emplace_back(service);
        }
        return svcConfig;
    }
};
