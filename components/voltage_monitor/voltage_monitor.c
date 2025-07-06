#include "voltage_monitor.h"

#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/sensor.h>
#include <zephyr/logging/log.h>
#include "math.h"

LOG_MODULE_REGISTER(VOLTAGE_MONITOR);

const struct device *vbat_dev = DEVICE_DT_GET(DT_NODELABEL(vbat));
const struct device *vin_dev = DEVICE_DT_GET(DT_NODELABEL(vin));


double get_vbat_voltage(void)
{
    if (!device_is_ready(vbat_dev)) {
        LOG_ERR("VBAT device not ready");
        return NAN;
    }

    struct sensor_value val;
    if (sensor_sample_fetch(vbat_dev) != 0 ||
        sensor_channel_get(vbat_dev, SENSOR_CHAN_VOLTAGE, &val) != 0) {
        LOG_ERR("Failed to read VBAT voltage");
        return NAN;
    }

    return sensor_value_to_double(&val);
}

double get_vin_voltage(void)
{
    if (!device_is_ready(vin_dev)) {
        LOG_ERR("VIN device not ready");
        return NAN;
    }

    struct sensor_value val;
    if (sensor_sample_fetch(vin_dev) != 0 ||
        sensor_channel_get(vin_dev, SENSOR_CHAN_VOLTAGE, &val) != 0) {
        LOG_ERR("Failed to read VIN voltage");
        return NAN;
    }

    return sensor_value_to_double(&val);
}