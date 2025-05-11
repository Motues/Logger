#include "Utils/Logger.hpp"

using namespace Utils::Logger;
int main() {
    // 创建日志策略
    auto filePolicy = std::make_shared<FileLogPolicy>("log.txt");
    auto consolePolicy = std::make_shared<ConsoleLogPolicy>();

    // 初始化 Logger
    Logger logger;
    logger.AddPolicy(filePolicy);
    logger.AddPolicy(consolePolicy);

    // 记录日志
    logger.Trace("Tracing execution flow.");
    logger.Debug("Debugging with value: {}, {}", 42, 66);
    logger.Info("Application started.");
    logger.Warning("This is a warning message.");
    logger.Error("An error occurred: {}", "file not found");

    // 刷新日志
    logger.Flush();

    return 0;
}
