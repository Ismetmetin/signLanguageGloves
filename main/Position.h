#ifndef POSITION_H
#define POSITION_H

class Position {
public:
    void gyro_signals();
    float getAccX();
    float getAccY();
    float getAccZ();
    void getPosition();

private:
    
    float AccX, AccY, AccZ;
    float RateRoll, RatePitch, RateYaw;
};

#endif // POSITION_H
