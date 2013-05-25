#include "logger.h"

namespace BAMF {

Logger::Logger()
    : output(&std::cout)
    , delStream(false)
{

}

Logger::Logger(const char *filename)
    : output(new std::ofstream(filename, std::ios_base::ate|std::ios_base::app))
    , delStream(true)
{

}

template <typename T>
Logger& Logger::operator << (const T& obj)
{
    if (!output) {
        //throw std::runtime_error("No stream set for logger");
        std::cerr << "No stream set for logger" << std::endl;
    }

    (*output) << obj;

    return *this;
}

Logger::~Logger()
{
    if (delStream) {
        delete output;
    }
}

} // namespace BAMF
