#ifndef POSITION_H
#define POSITION_H

class Position {
public:
    void gyro_signals();
    float getAccX();
    float getAccY();
    float getAccZ();
    //tezi dva methoda ne se polzvat i nqmat implementaciq. ako nqma da se izpolzvat da gi mahnem. 
    float getAngleRoll();
    float getAnglePitch();
    //2 
    void readSignal(*AngleX,*AngleY,*AngleZ);
private:
    float AngleRoll, AnglePitch;
    float AccX, AccY, AccZ;
    float RateRoll, RatePitch, RateYaw;
};

#endif // POSITION_H
