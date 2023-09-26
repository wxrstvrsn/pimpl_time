//
// Created by wxrstvrsn on 20.09.2023.
//

#include "TimeMeter.h"
#include <ctime>

struct TimeMeter::TimeMeterImpl {
    timespec start;
    timespec* timestamps;

    TimeMeterImpl(unsigned count) {
        timestamps = new timespec[count];
        clock_gettime(CLOCK_MONOTONIC, &start);
    }

    ~TimeMeterImpl() {
        delete[] timestamps;
    }

    double setTimeStamp(unsigned num) {
        clock_gettime(CLOCK_MONOTONIC, &timestamps[num]);
        return static_cast<double>(timestamps[num].tv_nsec - start.tv_nsec) / 1e9 +
               static_cast<double>(timestamps[num].tv_sec - start.tv_sec);
    }

    double getSTimeStamp(unsigned num) const {
        return static_cast<double>(timestamps[num].tv_nsec - start.tv_nsec) / 1e9 +
               static_cast<double>(timestamps[num].tv_sec - start.tv_sec);
    }

    int64_t getMSTimeStamp(unsigned num) const {
        return (timestamps[num].tv_sec - start.tv_sec) * 1000 +
               (timestamps[num].tv_nsec - start.tv_nsec) / 1000000;
    }

    double getSDiff(unsigned first, unsigned second) const {
        return static_cast<double>(timestamps[second].tv_nsec - timestamps[first].tv_nsec) / 1e9 +
               static_cast<double>(timestamps[second].tv_sec - timestamps[first].tv_sec);
    }

    int64_t getMSDiff(unsigned first, unsigned second) const {
        return (timestamps[second].tv_sec - timestamps[first].tv_sec) * 1000 +
               (timestamps[second].tv_nsec - timestamps[first].tv_nsec) / 1000000;
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