#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <math.h> 

#include "../components/ILI9341_display/ili9341_display.h"
#include "../components/lis2dh/lis2dh.h"
#include "../components/sht4x/sht4x.h"
#include "../components/ext_flash/max25r16.h"
#include "../components/WiFi/wifi.h"
#include "../components/voltage_monitor/voltage_monitor.h"

#include <zephyr/logging/log.h>

LOG_MODULE_REGISTER(Alertrax);



void main(void)
{
    double temp = tempC();
    double hum = getHumidity();

    if (!isnan(temp) && !isnan(hum)) {
        printk("Temperature: %.2f C\n", temp);
        printk("Humidity: %.2f %%\n", hum);
    } else {
        printk("SHT4X read failed!\n");
    }
}


 
