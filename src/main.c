#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <math.h>
#include <stdio.h>

#include "../components/ILI9341_display/ili9341_display.h"
#include "../components/lis2dh/lis2dh.h"
#include "../components/sht4x/sht4x.h"
#include "../components/ext_flash/max25r16.h"
#include "../components/WiFi/wifi.h"
#include "../components/voltage_monitor/voltage_monitor.h"

#include <zephyr/logging/log.h>

LOG_MODULE_REGISTER(AlertraxTestFirmware);

void main(void)
{
    ili9341_display_init(); // Initialize display and styles
    display_text_at("Test Firmware v1.0", 10, 10);

    // Sensor Read
    bool sht4x_ok = initTemp();
    double temp = tempC();
    double hum = getHumidity();

    char buffer[64];

    if (sht4x_ok && !isnan(temp) && !isnan(hum))
    {
        printk("Temperature: %.2f C\n", temp);
        printk("Humidity: %.2f %%\n", hum);

        display_text_at("SHT4X: OK", 10, 50);

        snprintf(buffer, sizeof(buffer), "Temp: %.2f C", temp);
        display_text_at(buffer, 10, 90);

        snprintf(buffer, sizeof(buffer), "Humidity: %.2f %%", hum);
        display_text_at(buffer, 10, 130);
    }
    else
    {
        printk("SHT4X read failed!\n");
        display_text_at("SHT4X: FAIL", 10, 50);
    }

    double vin = get_vin_voltage();
    double vbat = get_vbat_voltage();

    char buf[32];

    // --- VIN ---
    if (!isnan(vin))
    {
        snprintf(buf, sizeof(buf), "VIN: %.2f V", vin);
        display_text_at(buf, 10, 170);
        printk("%s\n", buf);
    }
    else
    {
        display_text_at("VIN: FAIL", 10, 170);
        printk("VIN: Read failed\n");
    }

    // --- VBAT ---
    if (!isnan(vbat))
    {
        snprintf(buf, sizeof(buf), "VBAT: %.2f V", vbat);
        display_text_at(buf, 10, 210);
        printk("%s\n", buf);
    }
    else
    {
        display_text_at("VBAT: FAIL", 10, 210);
        printk("VBAT: Read failed\n");
    }

    if (lis2dh_available()) {
    display_text_at("LIS2DH: OK", 10, 250);
    printk("LIS2DH: OK\n");
} else {
    display_text_at("LIS2DH: FAIL", 10, 250);
    printk("LIS2DH: FAIL\n");
}

}
