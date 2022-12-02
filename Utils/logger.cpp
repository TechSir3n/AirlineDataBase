#include "logger.h"

auto Logger::info(const QString &message) -> void {
  std::cout << "[INFO]: " << message.toStdString() << std::endl;
}

auto Logger::debug(const QString &message) -> void {
  std::cout << "[DEBUG]: " << message.toStdString() << std::endl;
}

auto Logger::warning(const QString &message) -> void {
  std::cerr << "[WARNING]: " << message.toStdString() << std::endl;
}

auto Logger::error(const QString &message) -> void {
  std::cerr << "[ERROR]: " << message.toStdString() << std::endl;
}
