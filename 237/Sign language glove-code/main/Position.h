#ifndef POSITION_H
#define POSITION_H

class Position {
public:
    void gyro_signals();  // Function declaration for gyro_signals
    float getAccX();  // Function declaration for getting X-axis acceleration
    float getAccY();  // Function declaration for getting Y-axis acceleration
    float getAccZ();  // Function declaration for getting Z-axis acceleration
private:
    float AccX, AccY, AccZ;  // Private member variables for storing acceleration values
};

#endif // POSITION_H
