#pragma once

#include <string>
#include <vector>
#include <array>
#include <cstdint>
#include <fstream>
#include <sstream>
#include <iostream>
#include "error.h"

using namespace std;

/**
 * @class ReadWrite
 * @brief Класс для чтения и записи данных из файлов.
 */
class ReadWrite
{
public:
    /**
     * @brief Конструктор класса ReadWrite.
     * @param inVec Имя входного файла.
     * @param outVec Имя выходного файла.
     * @param cfg Имя файла конфигурации.
     */
    ReadWrite(string &inVec, string &outVec, string &cfg);

    /**
     * @brief Получить имя входного файла.
     * @return Имя входного файла.
     */
    string getIn();

    /**
     * @brief Получить имя выходного файла.
     * @return Имя выходного файла.
     */
    string getOut();

    /**
     * @brief Получить имя файла конфигурации.
     * @return Имя файла конфигурации.
     */
    string getCfg();

    /**
     * @brief Записать вектор данных в выходной файл.
     * @param data Вектор данных для записи.
     * @throw VClientError Если файл не может быть открыт или запись в файл завершилась ошибкой.
     */
    void writeVec(const vector<int32_t> &data);

    /**
     * @brief Прочитать векторы данных из входного файла.
     * @return Вектор векторов данных.
     * @throw VClientError Если файл не может быть открыт или чтение из файла завершилось ошибкой.
     */
    vector<vector<int32_t>> readVec();

    /**
     * @brief Прочитать конфигурационные данные из файла конфигурации.
     * @return Массив строк с конфигурационными данными.
     * @throw VClientError Если файл не может быть открыт или чтение конфигурации завершилось ошибкой.
     */
    array<string, 2> readCfg();

private:
    string in;   ///< Имя входного файла.
    string out;  ///< Имя выходного файла.
    string cfg;  ///< Имя файла конфигурации.
};

/**
 * @brief Вывести вектор данных на консоль.
 * @param vec Вектор данных для вывода.
 */
void printVector(const vector<int32_t> &vec);

/**
 * @brief Вывести векторы данных на консоль.
 * @param vec Вектор векторов данных для вывода.
 */
void printVectors(const vector<vector<int32_t>> &vec);
