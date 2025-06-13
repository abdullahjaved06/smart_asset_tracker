#include <math.h>
#include <stdio.h>
#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/sensor.h>
#include <zephyr/logging/log.h>

#include "lis2dh.h"


LOG_MODULE_REGISTER(accelerometer);

const struct device *devMotion = DEVICE_DT_GET_ANY(st_lis2dh);
void (*func_ptr)() = NULL;
struct accel_struct *returnAccelData = NULL;

float getGbaseline();
static void trigger_handler(const struct device *dev, const struct sensor_trigger *trig);

void initAccelerometer()
{
	int ret = 0;
	int int_baseline = 0, baseline_remainder = 0.0;
	float baseline_g = 0.0;

	// devMotion = DEVICE_DT_GET_ANY(st_lis2dh);

	if (devMotion == NULL) {
		LOG_ERR("Could not get %s device\n", devMotion->name);
	} else {
		LOG_DBG("Bound %s device\n", devMotion->name);
		struct sensor_trigger trig;

		trig.type = SENSOR_TRIG_DELTA; // SENSOR_TRIG_DATA_READY;
		trig.chan = SENSOR_CHAN_ACCEL_XYZ;
		struct sensor_value odr = {
			.val1 = 50,
		};
		if (IS_ENABLED(CONFIG_LIS2DH_ODR_RUNTIME)) {

			ret = sensor_attr_set(devMotion, trig.chan, SENSOR_ATTR_SAMPLING_FREQUENCY,
					      &odr);
			if (ret != 0) {
				LOG_ERR("Failed to set odr: %d", ret);
			} else
				LOG_INF("Sampling at %u Hz", odr.val1);
		}

		struct sensor_value gScale;
		sensor_g_to_ms2(2, &gScale);
		ret = sensor_attr_set(devMotion, SENSOR_CHAN_ACCEL_XYZ, SENSOR_ATTR_FULL_SCALE,
				      &gScale);
		if (ret)
			LOG_INF("Failed to set g-scale: %d\n", ret);

		/*
			   ret = sensor_trigger_set(devMotion, &trig, trigger_handler);
			   if (ret)
			      LOG_ERR("Trigger set error: %d", ret);
			   else
			      LOG_INF("Trigger data ready set");
			 */

		/*
		  trig.type = SENSOR_TRIG_DELTA;
		  trig.chan = SENSOR_CHAN_ACCEL_XYZ;
	     ret = sensor_trigger_set(devMotion, &trig, trigger_handler);
	     if (ret)
		     LOG_ERR("Trigger set error: %d", ret);
		  else
		     LOG_INF("Trigger threshold set");
		*/

		LOG_DBG("Setting up sensor triggers");
		baseline_g = getGbaseline() + 0.5f;
		int_baseline = (int)baseline_g;
		baseline_remainder = (int)((baseline_g - int_baseline) * 1000000);
		printf("Baseline: %f %d %d\n", (double)baseline_g, int_baseline,
		       baseline_remainder);

		struct sensor_value threshold = {
			.val1 = 10,    // before decimal - 1G = 1000
			.val2 = 950000 // after decimal
				       //.val2 = 875000// after decimal
				       //.val1 = int_baseline,
				       //.val2 = baseline_remainder
		};

		ret = sensor_attr_set(devMotion, SENSOR_CHAN_ACCEL_XYZ, SENSOR_ATTR_SLOPE_TH,
				      &threshold);
		if (ret) {
			LOG_ERR("Trigger attr set error: %d", ret);
			LOG_ERR("Make sure trigger mode is configured");
		} else
			LOG_DBG("sensor_attr_set");

		struct sensor_value duration = {.val1 = odr.val1 / 20, .val2 = 0};
		ret = sensor_attr_set(devMotion, SENSOR_CHAN_ACCEL_XYZ, SENSOR_ATTR_SLOPE_DUR,
				      &duration);
		if (ret) {
			LOG_ERR("Trigger attr set error: %d", ret);
			LOG_ERR("Make sure trigger mode is configured");
		} else
			LOG_DBG("sensor_attr_set");
	}
}

// SYS_INIT(initAccelerometer, APPLICATION, CONFIG_APPLICATION_INIT_PRIORITY);

void enableMotionIRQ()
{
	// irq_enable(devMotion);
}

void disableMotionIRQ()
{
	// irq_disable(devMotion);
}

static void trigger_handler(const struct device *dev, const struct sensor_trigger *trig)
{
	switch (trig->type) {
	case SENSOR_TRIG_DATA_READY:
		// LOG_INF("Data ready");
		motion_data(dev);
		/*
			if (sensor_sample_fetch(dev) < 0) {
				LOG_ERR("Motion sample fetch error");
				return;
			}
			*/
		break;
	case SENSOR_TRIG_THRESHOLD:
	case SENSOR_TRIG_DELTA:
		LOG_WRN("Threshold trigger");
		// motion_data(dev);
		if (returnAccelData != NULL)
			accel_data();
		if (func_ptr != NULL)
			(*func_ptr)();
		/*
	int minutes = (k_uptime_get() - last_trigger) / 1000 / 60;
	if (deviceInMotion && (minutes >= 2)) {
	   LOG_INF("Motion TX time");
	   last_trigger = k_uptime_get();
	   deviceInMotion = false;
	} else
	   LOG_INF("Motion TX timeout: %d", minutes);
	deviceInMotion = true;
	*/
		break;
	default:
		// accel_data();
		if (func_ptr != NULL)
			(*func_ptr)();
		// LOG_INF("Unknown trigger: %d", trig->type);
	}
}

static struct sensor_trigger m_trig;
int accelCallbackSet(void (*func)(), struct accel_struct *accelData)
{
	int ret = 0;

	func_ptr = func;
	returnAccelData = accelData;

	m_trig.type = SENSOR_TRIG_DELTA;
	m_trig.chan = SENSOR_CHAN_ACCEL_XYZ;
	ret = sensor_trigger_set(devMotion, &m_trig, trigger_handler);
	if (ret)
		LOG_ERR("Trigger set error: %d", ret);
	else
		LOG_INF("Trigger threshold set");
	return ret;
}

float getGbaseline()
{
	struct sensor_value accel[3];
	double g, x, y, z;
	double baseline_g = 0.0;
	int rc;

	for (int i = 0; i < 10; i++) {

		rc = sensor_sample_fetch(devMotion);

		if (rc == 0) {
			rc = sensor_channel_get(devMotion, SENSOR_CHAN_ACCEL_XYZ, accel);
		} else {
			LOG_ERR("Error getting sensor data");
			continue;
		}

		x = sensor_value_to_double(&accel[0]);
		y = sensor_value_to_double(&accel[1]);
		z = sensor_value_to_double(&accel[2]);
		g = fabs(sqrt(x * x + y * y + z * z) - 9.8);
		if (fabs(g) > fabs(baseline_g))
			baseline_g = g;
	}
	return baseline_g + 9.8;
}

bool readMotionData(double *x, double *y, double *z, double *g)
{
	struct sensor_value accel[3];
	int rc;

	rc = sensor_sample_fetch(devMotion);

	if (rc == 0) {
		rc = sensor_channel_get(devMotion, SENSOR_CHAN_ACCEL_XYZ, accel);
	} else {
		LOG_ERR("Error getting sensor data");
		return false;
	}

	*x = sensor_value_to_double(&accel[0]);
	*y = sensor_value_to_double(&accel[1]);
	*z = sensor_value_to_double(&accel[2]);
	*g = fabs(sqrt(*x * *x + *y * *y + *z * *z) - 9.8);
	return true;
}

int accel_data()
{
	struct sensor_value accel[3];
	double g, x, y, z;

	const char *overrun = "";
	int rc = sensor_sample_fetch(devMotion);

	if (rc == -EBADMSG) {
		/* Sample overrun.  Ignore in polled mode. */
		if (IS_ENABLED(CONFIG_LIS2DH_TRIGGER)) {
			overrun = "[OVERRUN] ";
		}
		rc = 0;
	}
	if (rc == 0) {
		rc = sensor_channel_get(devMotion, SENSOR_CHAN_ACCEL_XYZ, accel);
	} else
		LOG_ERR("Error getting sensor data");

	x = sensor_value_to_double(&accel[0]);
	y = sensor_value_to_double(&accel[1]);
	z = sensor_value_to_double(&accel[2]);
	g = fabs(sqrt(x * x + y * y + z * z) - 9.8);
	returnAccelData->g = g;
	returnAccelData->y = y;
	returnAccelData->z = z;
	returnAccelData->x = x;

	int x_int = (int)x;
	int y_int = (int)y;
	int z_int = (int)z;
	int g_int = (int)g;
	int x_dec = abs((int)((x - x_int) * 10));
	int y_dec = abs((int)((y - y_int) * 10));
	int z_dec = abs((int)((z - z_int) * 10));
	int g_dec = abs((int)((g - g_int) * 10));

	LOG_INF("Accel After: x: %d.%d, y: %d.%d, z: %d.%d, g: %d.%d", x_int, x_dec, y_int, y_dec,
		z_int, z_dec, g_int, g_dec);
	return rc;
}

void motion_data(const struct device *dev)
{
	struct sensor_value accel[3];
	double g, x, y, z;

	const char *overrun = "";
	// setRedLED(true);
	int rc = sensor_sample_fetch(dev);

	if (rc == -EBADMSG) {
		/* Sample overrun.  Ignore in polled mode. */
		if (IS_ENABLED(CONFIG_LIS2DH_TRIGGER)) {
			overrun = "[OVERRUN] ";
		}
		rc = 0;
	}
	if (rc == 0) {
		rc = sensor_channel_get(dev, SENSOR_CHAN_ACCEL_XYZ, accel);
	} else
		LOG_ERR("Error getting sensor data");

	x = sensor_value_to_double(&accel[0]);
	y = sensor_value_to_double(&accel[1]);
	z = sensor_value_to_double(&accel[2]);
	g = fabs(sqrt(x * x + y * y + z * z) - 9.8);
	// motionSensed(g, &gps_work);

	printk("\ng: %.1f, x: %.1f, y: %.1f, z: %.1f (m/s^2)\n", g, x, y, z);
	// k_sleep(K_MSEC(500));
	// setRedLED(false);
}