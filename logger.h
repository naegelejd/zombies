#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>
#include <fstream>

namespace BAMF {

class Logger {
    public:
        Logger();
        Logger(const char *);
        ~Logger();

        template <typename T>
        Logger& operator << (const T& obj);

    private:
        std::ostream* output;
        bool delStream;
};

} // namespace BAMF

#endif // LOGGER_H
