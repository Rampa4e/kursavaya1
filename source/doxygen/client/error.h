#pragma once

#include <string>
#include <exception>

using namespace std;

/**
 * @class VClientError
 * @brief Класс для обработки ошибок в клиенте.
 */
class VClientError : public exception {
public:
    /**
     * @brief Конструктор класса VClientError.
     * @param errorName Название ошибки.
     * @param errorMsg Сообщение об ошибке.
     * @param funcName Имя функции, в которой произошла ошибка.
     */
    VClientError(const string& errorName, const string& errorMsg, const string& funcName);

    /**
     * @brief Получить полное сообщение об ошибке.
     * @return Полное сообщение об ошибке.
     */
    const char* what() const noexcept override;

    /**
     * @brief Получить название ошибки.
     * @return Название ошибки.
     */
    string getErrorName() const;

    /**
     * @brief Получить сообщение об ошибке.
     * @return Сообщение об ошибке.
     */
    string getErrorMsg() const;

    /**
     * @brief Получить имя функции, в которой произошла ошибка.
     * @return Имя функции, в которой произошла ошибка.
     */
    string getFuncName() const;

private:
    string errorName;  ///< Название ошибки.
    string errorMsg;   ///< Сообщение об ошибке.
    string funcName;   ///< Имя функции, в которой произошла ошибка.
    mutable string fullMsg; ///< Полное сообщение об ошибке.
};
