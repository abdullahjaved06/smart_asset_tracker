#include <zephyr/kernel.h>
#include <math.h>
#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <zephyr/drivers/sensor.h>
#include <zephyr/logging/log.h>
#include <zephyr/drivers/sensor/sht4x.h>

#include "sht4x.h"

#if !DT_HAS_COMPAT_STATUS_OKAY(sensirion_sht4x)
#error "No sensirion,sht4x compatible node found in the device tree"
#endif

LOG_MODULE_DECLARE(SHT4X);

#if CONFIG_MCP9808
static const struct device *tempDev = DEVICE_DT_GET_ANY(microchip_mcp9808);
#elif CONFIG_SHT4X
static const struct device *tempDev = DEVICE_DT_GET_ANY(sensirion_sht4x);
#elif CONFIG_ENS210
static const struct device *tempDev = DEVICE_DT_GET_ANY(ams_ens210);
#endif

K_MUTEX_DEFINE(tempMutex);

int initTemp()
{
	bool ready = device_is_ready(tempDev);

	if (!ready) {
		LOG_ERR("Could not get %s device\n", tempDev ? tempDev->name : "NULL");
	} else {
		LOG_INF("Bound %s device\n", tempDev->name);
	}

	return ready;
}


SYS_INIT(initTemp, APPLICATION, CONFIG_APPLICATION_INIT_PRIORITY);

double tempC()
{
	struct sensor_value temp;
	int rc;

	k_mutex_lock(&tempMutex, K_FOREVER);
	rc = sensor_sample_fetch(tempDev);
	if (rc != 0) {
		LOG_DBG("sensor_sample_fetch error: %d\n", rc);
		k_mutex_unlock(&tempMutex);
		return NAN;
	}

	rc = sensor_channel_get(tempDev, SENSOR_CHAN_AMBIENT_TEMP, &temp);
	if (rc != 0) {
		LOG_DBG("sensor_channel_get error: %d\n", rc);
		k_mutex_unlock(&tempMutex);
		return NAN;
	}

	k_mutex_unlock(&tempMutex);
	return sensor_value_to_double(&temp);
}


double tempF()
{
	double temp = tempC();

	if (!isnan(temp))
		temp = temp * 1.8 + 32.0;

	return temp;
}


double getHumidity()
{
	struct sensor_value humidity;
	int rc;

	k_mutex_lock(&tempMutex, K_FOREVER);
	rc = sensor_sample_fetch(tempDev);
	if (rc != 0) {
		LOG_DBG("sensor_sample_fetch error: %d\n", rc);
		k_mutex_unlock(&tempMutex);
		return NAN;
	}

	rc = sensor_channel_get(tempDev, SENSOR_CHAN_HUMIDITY, &humidity);
	if (rc != 0) {
		LOG_DBG("sensor_channel_get error: %d\n", rc);
		k_mutex_unlock(&tempMutex);
		return NAN;
	}

	k_mutex_unlock(&tempMutex);
	return sensor_value_to_double(&humidity);
}
