#ifndef LOGGER_H
#define LOGGER_H

#include <QString>
#include <iostream>

class Logger
{
public:
    auto info(const QString & message) -> void;

    auto debug(const QString & message) -> void;

    auto warning(const QString & message) -> void;

    auto error(const QString & message) -> void;
};

#endif // LOGGER_H
