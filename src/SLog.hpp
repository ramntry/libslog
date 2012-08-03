/*
 * File:   SLog.hpp
 * Author: Filinger
 *
 * Created on July 12, 2012, 2:15 PM
 */

#ifndef SLOG_HPP
#define SLOG_HPP

#include <string>

namespace slog
{

enum LogLevel
{
    kNoLog = 0, kError, kWarning, kInfo, kDebug
};

class SLog
{
public:
    static SLog* getInstance(const std::string& file_name = "/dev/null", int verbosity = 0)
    {
        LogLevel verb_level = slog::kNoLog;

        switch (verbosity)
        {
        case 1:
            verb_level = slog::kError;
            break;
        case 2:
            verb_level = slog::kWarning;
            break;
        case 3:
            verb_level = slog::kInfo;
            break;
        case 4:
            verb_level = slog::kDebug;
            break;
        default:
            verb_level = slog::kInfo;
        }

        static SLog exposed_log_(file_name, verb_level);
        return &exposed_log_;
    }

    SLog& operator <<(const std::string& input_str);
    SLog& operator <<(const int& input_int);
    void operator <<(slog::SLog& (*pf)(slog::SLog&));

    inline SLog& info()
    {
        return getStream(kInfo);
    }
    inline SLog& warn()
    {
        return getStream(kWarning);
    }
    inline SLog& err()
    {
        return getStream(kError);
    }
    inline SLog& debug()
    {
        return getStream(kDebug);
    }

protected:
    friend inline SLog& endl(SLog& in);
    friend inline SLog& show(SLog& in);

private:
    SLog& getStream(LogLevel level);
    void flushStream();
    void showStream();

    FILE* file_;
    std::string log_string_;
    char temp_buff_[10];
    LogLevel verbosity_level_;
    LogLevel current_level_;

    SLog();
    SLog(const std::string& file_name, LogLevel verbosity);
    virtual ~SLog();

    SLog(const SLog&);
    void operator=(const SLog&);
};

inline SLog& endl(SLog& in)
{
    in.flushStream();
    return in;
}

inline SLog& show(SLog& in)
{
    in.showStream();
    return in;
}

} //End namespace slog

#endif	/* LOGGER_HPP */
