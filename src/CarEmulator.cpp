#include "../inc/CarEmulator.h"

std::random_device randomNumberEngine;
std::uniform_int_distribution<int> distribution(0, 7);

void CarEmulator::speedUpdate() {
    mCurrentSpeed += (!mSlowDown) ?  SPEED_GAIN : -SPEED_GAIN;
    if (mCurrentSpeed <= MIN_SPEED) {
            mCurrentSpeed = MIN_SPEED;
            mSlowDown = false;
    } else if (mCurrentSpeed >= MAX_SPEED) {
            mCurrentSpeed = MAX_SPEED;
            mSlowDown = true;
    } 

    gearUpdate();
}

void CarEmulator::rpmUpdate() {
    mCurrentRpm += (!mRpmDown) ? RPM_GAIN : -RPM_GAIN;
    if (mCurrentRpm <= MIN_RPM) {
            mCurrentRpm = MIN_RPM;
            mRpmDown = false;
    } else if (mCurrentRpm >= MAX_RPM) {
            mCurrentRpm = MAX_RPM;
            mRpmDown = true;
    } 
}

void CarEmulator::fuelUpdate() {
    float fuelChange = (mCurrentRpm * 0.001) + (0.01 * mCurrentSpeed);   
    mCurrentFuelLevel -= (!mSlowDown) ? fuelChange * 1.3 : fuelChange;
    if (mCurrentFuelLevel < MIN_FUEL_LEVEL) {
        mCurrentFuelLevel += MAX_FUEL_LEVEL;
    }
}

void CarEmulator::gearUpdate() {
    if (!mGearReverse) {
        if (mCurrentRpm == MIN_RPM && mCurrentSpeed == MIN_SPEED) {
            mCurrentGear = 0;
        } else if (mCurrentSpeed > MIN_SPEED && mCurrentSpeed < 20) {
            mCurrentGear = 2;
        } else if (mCurrentSpeed >= 20 && mCurrentSpeed < 40) {
            mCurrentGear = 3;
        } else if (mCurrentSpeed >= 40  && mCurrentSpeed < 70) {
            mCurrentGear = 4;
        } else if (mCurrentSpeed >= 70 && mCurrentSpeed < 90) {
            mCurrentGear = 5;
        } else if (mCurrentSpeed >= 90 && mCurrentSpeed < 160) {
            mCurrentGear = 6;
        } else if (mCurrentSpeed >= 160) {
            mCurrentGear = 7;
        }
    } else {
        mCurrentGear = 1;
    }
}

void CarEmulator::absUpdate() {
    mAbsActive = !mAbsActive;
}

void CarEmulator::lightsUpdate(uint8_t light) {
    mLights[light] = !mLights[light];
}

void CarEmulator::testDashboard() {
    uint8_t randomEventTimer = 0;
    while (1) {
        int randomEventNumber = distribution(randomNumberEngine);
        std::cout << "Kph: " << mCurrentSpeed << " RPM: " << mCurrentRpm << " Fuel: " << mCurrentFuelLevel 
        << " Gear: " << GEARS[mCurrentGear] << " ABS ON:" << mAbsActive << std::endl;
        speedUpdate();
        rpmUpdate();
        fuelUpdate();
        randomEventTimer++;
        if (randomEventTimer == TIME_TARGET) {
            switch (randomEventNumber) {
                case 0:
                    absUpdate();
                    randomEventTimer = 0;
                    break;
                case 1:
                    mGearReverse = !mGearReverse;
                    randomEventTimer = 0;
                    break;
                case 2:
                    lightsUpdate(0);
                    randomEventTimer = 0;                
                    break;
                case 3:
                    lightsUpdate(1);
                    randomEventTimer = 0;
                    break;
                case 4:
                    lightsUpdate(2);
                    randomEventTimer = 0;
                    break;
                case 5:
                    lightsUpdate(3);
                    randomEventTimer = 0;
                    break;
                case 6:
                    lightsUpdate(4);
                    randomEventTimer = 0;
                    break;
                default:
                    randomEventTimer = 0;
                    break;
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(75));
    }
}