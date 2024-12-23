#pragma once

#include <string>
#include <iostream>
#include <stdexcept>
#include "error.h"

using namespace std;

/**
 * @class CMDParser
 * @brief Класс для парсинга командной строки.
 */
class CMDParser {
private:
    string in = "./in.txt";   ///< Путь к входному файлу.
    string out = "./out.bin"; ///< Путь к выходному файлу.
    string cfg = "./cfg.txt"; ///< Путь к файлу конфигурации.
    string addr = "127.0.0.1"; ///< Адрес сервера.
    uint16_t port = 33333;    ///< Порт сервера.

public:
    /**
     * @brief Конструктор класса CMDParser по умолчанию.
     */
    CMDParser() = default;

    /**
     * @brief Получить путь к входному файлу.
     * @return Путь к входному файлу.
     */
    string getIn() const;

    /**
     * @brief Получить путь к выходному файлу.
     * @return Путь к выходному файлу.
     */
    string getOut() const;

    /**
     * @brief Получить путь к файлу конфигурации.
     * @return Путь к файлу конфигурации.
     */
    string getCfg() const;

    /**
     * @brief Получить адрес сервера.
     * @return Адрес сервера.
     */
    string getAddr() const;

    /**
     * @brief Получить порт сервера.
     * @return Порт сервера.
     */
    uint16_t getPort() const;

    /**
     * @brief Парсить аргументы командной строки.
     * @param argc Количество аргументов.
     * @param argv Массив аргументов.
     * @throw VClientError Если парсинг аргументов завершился ошибкой.
     */
    void parse(int argc, char* argv[]);

    /**
     * @brief Показать справку по использованию.
     */
    void showHelp() const;
};
