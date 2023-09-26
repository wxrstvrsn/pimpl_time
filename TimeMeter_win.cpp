//
// Created by wxrstvrsn on 20.09.2023.
//

#include "TimeMeter.h"
#include <windows.h>

struct TimeMeter::TimeMeterImpl {
    LARGE_INTEGER frequency;
    LARGE_INTEGER start;
    LARGE_INTEGER *timestamps;

    TimeMeterImpl(unsigned count) {
        timestamps = new LARGE_INTEGER[count];
        QueryPerformanceFrequency(&frequency);
        QueryPerformanceCounter(&start);
    }

    ~TimeMeterImpl() {
        delete[] timestamps;
    }

    double setTimeStamp(unsigned num) {
        QueryPerformanceCounter(&timestamps[num]);
        return static_cast<double>(timestamps[num].QuadPart - start.QuadPart) / frequency.QuadPart;
    }

    double getSTimeStamp(unsigned num) const {
        return static_cast<double>(timestamps[num].QuadPart - start.QuadPart) / frequency.QuadPart;
    }

    int64_t getMSTimeStamp(unsigned num) const {
        return (timestamps[num].QuadPart - start.QuadPart) * 1000 / frequency.QuadPart;
    }

    double getSDiff(unsigned first, unsigned second) const {
        return static_cast<double>(timestamps[second].QuadPart - timestamps[first].QuadPart) / frequency.QuadPart;
    }

    int64_t getMSDiff(unsigned first, unsigned second) const {
        return (timestamps[second].QuadPart - timestamps[first].QuadPart) * 1000 / frequency.QuadPart;
    }

    bool isLess(unsigned first, unsigned second, int64_t expected) const {
        int64_t actual = getMSDiff(first, second);
        return actual < expected;
    }

    bool isLess(unsigned num, int64_t expected) const {
        int64_t actual = getMSTimeStamp(num);
        return actual < expected;
    }
};

TimeMeter::TimeMeter(unsigned count) : pImpl(new TimeMeterImpl(count)) {}

TimeMeter::~TimeMeter() {
    delete pImpl;
}

double TimeMeter::setTimeStamp(unsigned num) {
    return pImpl->setTimeStamp(num);
}

double TimeMeter::getSTimeStamp(unsigned num) const {
    return pImpl->getSTimeStamp(num);
}

int64_t TimeMeter::getMSTimeStamp(unsigned num) const {
    return pImpl->getMSTimeStamp(num);
}

double TimeMeter::getSDiff(unsigned first, unsigned second) const {
    return pImpl->getSDiff(first, second);
}

int64_t TimeMeter::getMSDiff(unsigned first, unsigned second) const {
    return pImpl->getMSDiff(first, second);
}

bool TimeMeter::isLess(unsigned first, unsigned second, int64_t expected) const {
    return pImpl->isLess(first, second, expected);
}

bool TimeMeter::isLess(unsigned num, int64_t expected) const {
    return pImpl->isLess(num, expected);
}
