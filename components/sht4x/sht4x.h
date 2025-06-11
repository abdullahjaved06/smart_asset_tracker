#ifndef SHT4X_H
#define SHT4X_H


#include <zephyr/drivers/sensor.h>

/* Function to initialize the SHT4x sensor */
int init_sht4x_sensor(const struct device *sht4x_sensor);

/* Function to fetch sensor data and print it */
int sht4x_sensor_data(const struct device *sht4x_sensor);

#endif /* SHT4X_H */
