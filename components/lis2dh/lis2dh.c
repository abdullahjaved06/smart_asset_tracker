// lisd2h.c

#include <stdio.h>
#include <zephyr/kernel.h>
#include <zephyr/drivers/sensor.h>
#include "lis2dh.h"

static void fetch_and_display(const struct device *sensor)
{
	static unsigned int count;
	struct sensor_value accel[3];
	struct sensor_value temperature;
	const char *overrun = "";
	int rc = sensor_sample_fetch(sensor);

	++count;
	if (rc == -EBADMSG) {
		if (IS_ENABLED(CONFIG_LIS2DH_TRIGGER)) {
			overrun = "[OVERRUN] ";
		}
		rc = 0;
	}
	if (rc == 0) {
		rc = sensor_channel_get(sensor, SENSOR_CHAN_ACCEL_XYZ, accel);
	}
	if (rc < 0) {
		printf("ERROR: Update failed: %d\n", rc);
	} else {
		printf("#%u @ %u ms: %sx %f , y %f , z %f",
		       count, k_uptime_get_32(), overrun,
		       sensor_value_to_double(&accel[0]),
		       sensor_value_to_double(&accel[1]),
		       sensor_value_to_double(&accel[2]));
	}

	if (IS_ENABLED(CONFIG_LIS2DH_MEASURE_TEMPERATURE)) {
		if (rc == 0) {
			rc = sensor_channel_get(sensor, SENSOR_CHAN_DIE_TEMP, &temperature);
			if (rc < 0) {
				printf("\nERROR: Unable to read temperature:%d\n", rc);
			} else {
				printf(", t %f\n", sensor_value_to_double(&temperature));
			}
		}
	} else {
		printf("\n");
	}
}

#ifdef CONFIG_LIS2DH_TRIGGER
static void trigger_handler(const struct device *dev,
			    const struct sensor_trigger *trig)
{
	fetch_and_display(dev);
}
#endif

void lisd2h_init(const struct device *sensor)
{
	if (sensor == NULL) {
		printf("No LIS2DH device found\n");
		return;
	}
	if (!device_is_ready(sensor)) {
		printf("Device %s is not ready\n", sensor->name);
		return;
	}
}

void lisd2h_poll_loop(const struct device *sensor)
{
    while (true) {
        fetch_and_display(sensor);
        k_sleep(K_MSEC(2000));
    }
}


#ifdef CONFIG_LIS2DH_TRIGGER
void lisd2h_trigger_setup(const struct device *sensor)
{
	struct sensor_trigger trig;
	int rc;

	trig.type = SENSOR_TRIG_DATA_READY;
	trig.chan = SENSOR_CHAN_ACCEL_XYZ;

	if (IS_ENABLED(CONFIG_LIS2DH_ODR_RUNTIME)) {
		struct sensor_value odr = { .val1 = 1 };
		rc = sensor_attr_set(sensor, trig.chan, SENSOR_ATTR_SAMPLING_FREQUENCY, &odr);
		if (rc != 0) {
			printf("Failed to set odr: %d\n", rc);
			return;
		}
		printf("Sampling at %u Hz\n", odr.val1);
	}

	rc = sensor_trigger_set(sensor, &trig, trigger_handler);
	if (rc != 0) {
		printf("Failed to set trigger: %d\n", rc);
		return;
	}

	printf("Waiting for triggers\n");
	while (true) {
		k_sleep(K_MSEC(2000));
	}
}
#endif

void lisd2h_poll_once(const struct device *sensor)
{
    fetch_and_display(sensor);
}
