#include <format>
#include <iostream>
#include <string>
#include <vector>
#include <format>
#include "Optimization/Optimize.cpp"

int main()
{
    constexpr auto welcomeMsg = "Welcome to Windows Optimizer!";
    std::vector <std::string> options(0);
    options.emplace_back("Full Optimization");
    options.emplace_back("CPU Optimization");
    options.emplace_back("GPU Optimization");
    options.emplace_back("Security Optimization");
    options.emplace_back("UI Optimization");
    options.emplace_back("Memory Optimization");
    options.emplace_back("Windows Apps Optimization");

    std::cout << welcomeMsg << '\n';
    for (size_t i = 1; i < options.size(); i++)
    {
        std::cout << std::format("[{}] {}", i, options[i]) << '\n';
    }

    unsigned int optimizationType = 0;
    std::cin >> optimizationType;

    int exitCode = 0;
    switch (optimizationType)
    {
        case 0:
            {
                std::cout << "No option was chosen" << '\n';
                exitCode = 1;
                break;
            }
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
            {
                const bool isOptimizeOk = Optimize::RunOptimize(optimizationType);
                std::cout << "isOptimizeOk: " << isOptimizeOk << '\n';
                break;
            }

        default:
            std::cout << "Invalid option was chosen" << '\n';
            exitCode = 2;
            break;
    }

    return exitCode;
}