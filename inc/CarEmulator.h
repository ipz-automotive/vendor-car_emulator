#ifndef __CAR_EMULATOR_H__
#define __CAR_EMULATOR_H__

#include <iostream>
#include <thread>
#include <chrono>
#include <random>
#include <array>

 /*
    GEARS_INDEX:
            R -> 0
            N -> 1
            1 -> 0
            2 -> 0
            3 -> 0
            4 -> 0
            5 -> 0
            6 -> 0
*/

 /*
    LIGHTS_INDEX:
            LOW_BEAM -> 0
            HIGH_BEAM -> 1
            TURN_LEFT-> 2
            TURN_RIGHT -> 3
            FOG -> 4
*/

class CarEmulator{
public:
    static constexpr float MAX_SPEED = 250;
    static constexpr float MIN_SPEED = 0.1;
    static constexpr float SPEED_GAIN = 0.5;
    static constexpr float MAX_RPM = 8000;
    static constexpr float MIN_RPM = 500;
    static constexpr float RPM_GAIN = 25;
    static constexpr float MAX_FUEL_LEVEL = 50;
    static constexpr float MIN_FUEL_LEVEL = 0;
    static constexpr uint8_t GEAR_SIZE = 8;
    static constexpr uint8_t LIGHTS_SIZE = 5;
    static constexpr uint8_t TIME_TARGET = 50;
    static constexpr std::array<char, GEAR_SIZE> GEARS = {'N', 'R', '1', '2', '3', '4', '5', '6'};
    void speedUpdate();
    void rpmUpdate();
    void fuelUpdate();
    void gearUpdate();
    void absUpdate();
    void lightsUpdate(uint8_t light);
    void testDashboard();
private:
    float mCurrentSpeed = 0;
    float mCurrentRpm = 500;
    float mCurrentFuelLevel = 50;
    int mCurrentGear = 0;
    std::array<bool, LIGHTS_SIZE> mLights= {false, false, false, false, false};
    bool mAbsActive = false;
    bool mGearReverse = false;
    bool mSlowDown = false;
    bool mRpmDown = false;
};


#endif