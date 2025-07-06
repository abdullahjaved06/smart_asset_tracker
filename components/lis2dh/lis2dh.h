#ifndef _ACCELEROMETER_H
#define _ACCELEROMETER_H

#include <zephyr/drivers/sensor.h>

struct accel_struct {
   double x;
   double y;
   double z;
   double g;
};

//typedef int (*accel_callback)(void);

void initAccelerometer();
void enableMotionIRQ();
void disableMotionIRQ();
int accelCallbackSet(void (*func)(), struct accel_struct *accelData);
bool readMotionData(double *x, double *y, double *z, double *g);
int accel_data();
void motion_data(const struct device *dev);

bool lis2dh_available(void);


#endif