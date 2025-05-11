#include "Utils/Logger.hpp"
#include <iostream>
#include <thread>
#include <vector>
#include <chrono>

const int num_threads = 8;
const int num_messages_per_thread = 1000;

using namespace Utils::Logger;

void LogMessages(Logger& logger, int thread_id, int num_messages) {
    for (int i = 0; i < num_messages; ++i) {
        logger.Info("Thread {}: Message {}", thread_id, i);
    }
}

void TestConsoleOutput(Logger& logger) {
    std::vector<std::thread> threads;
    for (int i = 0; i < num_threads; ++i) {
        threads.emplace_back(LogMessages, std::ref(logger), i, num_messages_per_thread);
    }
    for (auto& thread : threads) {
        thread.join();
    }
    logger.Flush();
}

void TestFileOutput(Logger& logger) {
    std::vector<std::thread> threads;
    for (int i = 0; i < num_threads; ++i) {
        threads.emplace_back(LogMessages, std::ref(logger), i, num_messages_per_thread);
    }
    for (auto& thread : threads) {
        thread.join();
    }
    logger.Flush();
}

void TestMixedOutput(Logger& logger) {
    std::vector<std::thread> threads;
    for (int i = 0; i < num_threads; ++i) {
        threads.emplace_back(LogMessages, std::ref(logger), i, num_messages_per_thread);
    }
    for (auto& thread : threads) {
        thread.join();
    }
    logger.Flush();
}

int main() {
    Logger logger;
    logger.AddPolicy(std::make_shared<FileLogPolicy>("log.txt"));
    logger.AddPolicy(std::make_shared<ConsoleLogPolicy>());
    auto start_time = std::chrono::high_resolution_clock::now();
    // TestConsoleOutput(logger);
    // TestFileOutput(logger);
    TestMixedOutput(logger);
    auto end_time = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end_time - start_time;
    std::cout << "Mixed Output Test: Logged " << num_threads * num_messages_per_thread << " messages in " << elapsed.count() << " seconds." << std::endl;
    std::cout << "Speed: " << int(static_cast<double >(num_threads * num_messages_per_thread) / elapsed.count() )<< " messages/second" << std::endl;
    return 0;
}