#include "sht4x.h"
#include <stdio.h>
#include <zephyr/kernel.h>
#include <zephyr/drivers/sensor.h>

#define SHT4X_NODE DT_NODELABEL(sht4x)  // Assuming device tree label

/* Function to initialize the SHT4x sensor */
int init_sht4x_sensor(const struct device *sht4x_sensor)
{
    /* Check if the sensor device is ready */
    if (!device_is_ready(sht4x_sensor)) {
        printf("SHT4x sensor device not found or not ready\n");
        return -ENODEV;
    }

    printf("SHT4x sensor device is ready\n");
    return 0;
}

/* Function to fetch sensor data and print it */
int sht4x_sensor_data(const struct device *sht4x_sensor)
{
    int ret;
    struct sensor_value temp, humidity;

    /* Fetch the sensor sample (temperature and humidity) */
    ret = sensor_sample_fetch(sht4x_sensor);
    if (ret) {
        printf("Failed to fetch data from the sensor\n");
        return ret;
    }

    /* Get temperature data */
    ret = sensor_channel_get(sht4x_sensor, SENSOR_CHAN_AMBIENT_TEMP, &temp);
    if (ret) {
        printf("Failed to get temperature data\n");
        return ret;
    }

    /* Get humidity data */
    ret = sensor_channel_get(sht4x_sensor, SENSOR_CHAN_HUMIDITY, &humidity);
    if (ret) {
        printf("Failed to get humidity data\n");
        return ret;
    }

    /* Print the temperature and humidity data */
    printf("Temperature: %d.%02d C\n", temp.val1, temp.val2);
    printf("Humidity: %d.%02d %%\n", humidity.val1, humidity.val2);

    return 0;
}
