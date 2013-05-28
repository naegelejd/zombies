#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>
#include <fstream>

namespace BAMF {

class Logger
{
public:
    Logger()
        : output(&std::cout)
        , delStream(false)
    {}

    Logger(const char *filename)
        : output(new std::ofstream(filename, std::ios_base::ate|std::ios_base::app))
        , delStream(true)
    {}

    ~Logger()
    {
        if (delStream) {
            delete output;
        }
    }

    template <typename T>
    friend Logger& operator << (Logger& logger, const T& obj)
    {
        if (!logger.output) {
            //throw std::runtime_error("No stream set for logger");
            std::cerr << "No stream set for logger" << std::endl;
        }

        *(logger.output) << obj << std::endl;

        return logger;
    }

    void log(const std::string& str)
    {
        if (!output) {
            //throw std::runtime_error("No stream set for logger");
            std::cerr << "No stream set for logger" << std::endl;
        }

        *output << str << std::endl;
    }

private:
    Logger(const Logger&);
    Logger& operator=(const Logger&);

    std::ostream* output;
    bool delStream;
};

} // namespace BAMF

#endif // LOGGER_H
