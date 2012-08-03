#include "src/SLog.hpp"

int main()
{
    slog::SLog *logger = slog::SLog::getInstance("/dev/stdout");
    logger->info() << "Hello, I'm a logger!" << slog::endl;

    return 0;
}
