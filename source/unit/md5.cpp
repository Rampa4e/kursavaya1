#include "md5.h"

string salt()
{
    const size_t size = 8;               // размер соли в байтах (64 бита = 8 байт)
    CryptoPP::byte salt[size];           // массив для соли
    CryptoPP::AutoSeededRandomPool prng; //
    prng.GenerateBlock(salt, size);      // генерация соли
    string salt_hex;                     // строка для соли
    CryptoPP::ArraySource(
        salt,
        size,
        true,
        new CryptoPP::HexEncoder(
            new CryptoPP::StringSink(salt_hex),
            true // Заглавные буквы
            ));

    // Дополнение соли нулями слева до 16 символов
    while (salt_hex.size() < 16)
        salt_hex = "0" + salt_hex;

    return salt_hex;
};
string md5(string &data)
{
    CryptoPP::MD5 hash_func; // создаем объект хеш-функции
    string hash_hex;

    // формирование хэша и преобразование в шестнадцатеричную строку
    CryptoPP::StringSource(
        data,
        true,
        new CryptoPP::HashFilter(
            hash_func,
            new CryptoPP::HexEncoder(
                new CryptoPP::StringSink(hash_hex),
                true // Заглавные буквы
                )));

    return hash_hex;
};