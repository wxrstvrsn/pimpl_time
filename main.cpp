#include "TimeMeter.h"
#include <iostream>
#include <chrono>
#include <thread>

int main() {

    TimeMeter timer(5);


    timer.setTimeStamp(0);

    double timeStart = timer.getSTimeStamp(0);

    std::cout << "Time difference between timestamps 0 and start: " << timeStart << " seconds" << std::endl;

    std::this_thread::sleep_for(std::chrono::seconds(2));

    timer.setTimeStamp(1);


    double timeDiff = timer.getSDiff(0, 1);
    std::cout << "Time difference between timestamps 0 and 1: " << timeDiff << " seconds" << std::endl;


    timer.setTimeStamp(2);

    std::this_thread::sleep_for(std::chrono::seconds(3));

    timer.setTimeStamp(3);

    double elapsedTime = timer.getMSDiff(0,2);
    std::cout << "Elapsed time from start to timestamp 2: " << elapsedTime << " milliseconds" << std::endl;

    double elapsedTime2_3 = timer.getMSDiff(2,3);
    std::cout << "Time difference between timestamps 2 and 3 :" << elapsedTime2_3 << " milliseconds" << std::endl;

    double elapsedTimeStamp = timer.getMSTimeStamp(3);
    std::cout << "Elapsed time from start to timestamp 3: " << elapsedTimeStamp << " milliseconds" << std::endl;

    return 0;
}
