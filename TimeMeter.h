//
// Created by wxrstvrsn on 20.09.2023.
//

#pragma once

#include <cstdint>
#include <memory>

class TimeMeter {
public:
    //! Запоминает время начала отсчета и необходимое количество временных меток
    TimeMeter(unsigned count);

    ~TimeMeter();

    //! Установка временной метки (от начала времени отсчета)
    double setTimeStamp(unsigned num);

    //! Получение времени метки в секундах
    double getSTimeStamp(unsigned num) const;

    //! Получение времени метки в миллисекундах
    int64_t getMSTimeStamp(unsigned num) const;

    //! Получение разницы между метками в секундах
    double getSDiff(unsigned first, unsigned second) const;

    //! Получение разницы между метками в миллисекундах
    int64_t getMSDiff(unsigned first, unsigned second) const;

    //! Проверка, не превосходит ли ожидаемого значения (в секундах)
    bool isLess(unsigned first, unsigned second, int64_t expected) const;

    //! Проверка, не превосходит ли ожидаемого значения (в миллисекундах)
    bool isLess(unsigned num, int64_t expected) const;

private:
    struct TimeMeterImpl;
    TimeMeterImpl *pImpl;
};

