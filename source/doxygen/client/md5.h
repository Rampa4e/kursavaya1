#pragma once

#include <string>
#include <cryptopp/hex.h>
#include <cryptopp/md5.h>
#include <cryptopp/osrng.h>

using namespace std;

/**
 * @brief Генерирует соль для хеширования.
 * @return Строка сгенерированной соли.
 */
string salt();

/**
 * @brief Вычисляет MD5 хэш от переданных данных.
 * @param data Данные для хеширования.
 * @return Строка с хэшем MD5.
 */
string md5(string &data);
