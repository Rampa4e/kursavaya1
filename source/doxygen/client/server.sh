#!/bin/bash

DATA_TYPE="int32_t"
HASH_TYPE="MD5"
SALT_TYPE="client"

# Проверка, какие процессы используют порт 33333 и их завершение
PIDS=$(lsof -t -i:33333)
if [ -n "$PIDS" ]; then 
    kill -9 $PIDS
fi

# Запуск сервера в новой консоли
./server -T $DATA_TYPE -H $HASH_TYPE -S $SALT_TYPE
exit
