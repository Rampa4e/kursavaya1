#pragma once

#include <cstdint>
#include <string>
#include <cstring>
#include <array>
#include <iostream>
#include <vector>

#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#include "error.h"
#include "md5.h"

using namespace std;

/**
 * @class VClient
 * @brief Класс для работы с клиентом.
 */
class VClient
{
private:
    int sock; ///< Сокет клиента.
    string addr; ///< Адрес сервера.
    uint16_t port; ///< Порт сервера.
    array<string, 2> conf; ///< Конфигурационные данные для аутентификации.

public:
    /**
     * @brief Конструктор класса VClient.
     * @param addr Адрес сервера.
     * @param port Порт сервера.
     * @param conf Массив строк с конфигурационными данными для аутентификации.
     */
    VClient(string addr, uint16_t port, array<string, 2> conf);

    /**
     * @brief Установить соединение с сервером.
     * @throw VClientError Если не удалось установить соединение.
     */
    void conn();

    /**
     * @brief Закрыть соединение с сервером.
     */
    void stop();

    /**
     * @brief Выполнить аутентификацию на сервере.
     * @throw VClientError Если аутентификация не удалась.
     */
    void auth();

    /**
     * @brief Выполнить расчет данных на сервере.
     * @param data Вектор векторов данных для расчета.
     * @return Вектор рассчитанных данных.
     * @throw VClientError Если расчет завершился ошибкой.
     */
    vector<int32_t> calc(vector<vector<int32_t>> data);

    /**
     * @brief Получить сокет клиента.
     * @return Сокет клиента.
     */
    int getSock();

    /**
     * @brief Получить адрес сервера.
     * @return Адрес сервера.
     */
    string getAddr();

    /**
     * @brief Получить порт сервера.
     * @return Порт сервера.
     */
    uint16_t getPort();

    /**
     * @brief Получить конфигурационные данные для аутентификации.
     * @return Массив строк с конфигурационными данными для аутентификации.
     */
    array<string, 2> getConf();
};
