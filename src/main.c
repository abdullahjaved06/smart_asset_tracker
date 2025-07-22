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

// Function declarations
void test_sht4x(bool *ok);
void test_voltage(bool *ok);
void test_lis2dh(bool *ok);
void test_flash(bool *ok);

void main(void)
{
    ili9341_display_init(); // Initialize display and styles
    // display_text_at("Test Firmware", 10, 10);

    bool sht4x_ok = false;
    bool voltage_ok = false;
    bool lis2dh_ok = false;
    bool flash_ok = false;

    test_sht4x(&sht4x_ok);
    test_lis2dh(&lis2dh_ok);
    test_voltage(&voltage_ok);
    test_flash(&flash_ok);

    // --- Wi-Fi Connect ---
    if (sht4x_ok && voltage_ok && lis2dh_ok && flash_ok)
    {
        display_text_at("TESTS PASS", 100, 150);
        printk("All tests passed. Attempting Wi-Fi connection...\n");

        if (wifi_connect() == 0)
        {
            display_text_at("Wi-Fi:Connected ", 100, 180);
            printk("Wi-Fi connection successful.\n");
        }
        else
        {
            display_text_at("Wi-Fi: FAIL", 100, 180);
            printk("Wi-Fi connection failed.\n");
        }
    }
    else
    {
        display_text_at("TESTS FAIL", 100, 150);
        display_text_at("Wi-Fi: SKIPPED", 100, 180);
        printk("One or more tests failed. Skipping Wi-Fi connection.\n");   
    }
     while (1) {
        lv_task_handler();
        k_msleep(10);  // Every 10ms is enough
    }
   
}




void test_sht4x(bool *ok)
{
    *ok = false;
    bool sht4x_ready = initTemp();
    double temp = tempC();
    double hum = getHumidity();

    char buf[64];

    if (sht4x_ready && !isnan(temp) && !isnan(hum)) {
        *ok = true;
        printk("SHT4X OK: Temp=%.2f C, Hum=%.2f%%\n", temp, hum);
        display_text_at("SHT4X: OK", 0, 5);
        snprintf(buf, sizeof(buf), "Temp: %.2f C", temp);
        display_text_at(buf, 180, 5);
        snprintf(buf, sizeof(buf), "Humi: %.2f %%", hum);
        display_text_at(buf, 180, 30);
    } else {
        printk("SHT4X: FAIL\n");
        display_text_at("SHT4X: FAIL", 0, 5);
    }
}
void test_lis2dh(bool *ok)
{
    *ok = lis2dh_available();
    if (*ok) {
        display_text_at("LIS2DH: OK", 0, 40);
        printk("LIS2DH: OK\n");
    } else {
        display_text_at("LIS2DH: FAIL", 0, 40);
        printk("LIS2DH: FAIL\n");
    }
}


void test_voltage(bool *ok)
{
    *ok = false;
    double vin = get_vin_voltage();
    double vbat = get_vbat_voltage();
    char buf[32];

    if (!isnan(vin)) {
        *ok = true;
        snprintf(buf, sizeof(buf), "VIN: %.2f V", vin);
        display_text_at(buf, 180, 60);
        printk("%s\n", buf);
    } else {
        display_text_at("VIN:    FAIL", 180, 60);
        printk("VIN: Read failed\n");
    }

    if (!isnan(vbat)) {
        snprintf(buf, sizeof(buf), "VBAT: %.2f V", vbat);
        display_text_at(buf, 180, 90);
        printk("%s\n", buf);
    } else {
        display_text_at("VBAT: FAIL", 180, 90);
        printk("VBAT: Read failed\n");
        *ok = false;
    }
}





void test_flash(bool *ok)
{
    *ok = external_flash_available();
    if (*ok) {
        display_text_at("FLASH: OK", 0, 80);
        printk("FLASH: OK\n");
    } else {
        display_text_at("FLASH: FAIL", 0, 80);
        printk("FLASH: FAIL\n");
    }
}
