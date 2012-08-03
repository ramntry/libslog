/*
 * File:   SLog.cpp
 * Author: Filinger
 *
 * Created on July 12, 2012, 2:15 PM
 */

#include <cstdio>
#include "SLog.hpp"

namespace slog
{
SLog::SLog() { }
SLog::SLog(const std::string& file_name, LogLevel verbosity)
{
    file_ = fopen(file_name.c_str(), "a");
    verbosity_level_ = verbosity;
}
SLog::~SLog()
{
    fclose(file_);
}
SLog& SLog::operator <<(const std::string& input_str)
{
    if (current_level_ <= verbosity_level_)
        log_string_.append(input_str);
    return *this;
}
SLog&SLog::operator <<(const int& input_int)
{
    if (current_level_ <= verbosity_level_)
    {
        sprintf(&temp_buff_[0], "%d", input_int);
        log_string_.append(temp_buff_);
    }
    return *this;
}
void SLog::operator <<(slog::SLog& (*pf)(slog::SLog&))
{
    if (current_level_ <= verbosity_level_)
        pf(*this);
}
SLog& SLog::getStream(LogLevel level)
{
    current_level_ = level;
    if (current_level_ <= verbosity_level_)
    {
        time_t rawtime;
        struct tm* timeinfo;
        time(&rawtime);
        timeinfo = localtime(&rawtime);
        strftime(&temp_buff_[0], 10, "%X", timeinfo);
        if (current_level_ == kInfo)
        {
            log_string_.append("\033[32m");
            log_string_.append(temp_buff_);
            log_string_.append(" <Info> ");
        } else if (current_level_ == kWarning)
        {
            log_string_.append("\033[33m");
            log_string_.append(temp_buff_);
            log_string_.append(" <Warning> ");
        } else if (current_level_ == kError)
        {
            log_string_.append("\033[31m");
            log_string_.append(temp_buff_);
            log_string_.append(" <Error> ");
        } else
        {
            log_string_.append("\033[36m");
            log_string_.append(temp_buff_);
            log_string_.append(" <Debug> ");
        }
    }
    return *this;
}
void SLog::flushStream()
{
    if (current_level_ <= verbosity_level_)
    {
        fprintf(file_, "%s\n", log_string_.c_str());
        fflush(file_);
        log_string_.clear();
    }
}
void SLog::showStream()
{
    if (current_level_ <= verbosity_level_)
    {
        fprintf(stderr, "%s\n", log_string_.c_str());
        log_string_.clear();
    }
}

}
