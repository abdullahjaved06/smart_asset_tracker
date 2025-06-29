#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/devicetree.h>

#include "../components/ILI9341_display/ili9341_display.h"
#include "../components/lis2dh/lis2dh.h"
#include "../components/sht4x/sht4x.h"
#include "../components/ext_flash/max25r16.h"
#include "../components/WiFi/wifi.h"
#include "../components/voltage_monitor/voltage_monitor.h"

#include <zephyr/logging/log.h>

LOG_MODULE_REGISTER(Alertrax);

const struct device *sensor = DEVICE_DT_GET(DT_NODELABEL(lis2dh12));


#define SLEEP_TIME_MS 2000
#define SHT4X_NODE DT_NODELABEL(sht4x)

void main(void) {
    
    const struct device *sht4x_sensor = DEVICE_DT_GET(SHT4X_NODE);
    int ret=0;
    // ili9341_display_init();
       /* Initialize the SHT4x sensor */
    // ret = init_sht4x_sensor(&sht4x_sensor);
    // if (ret) {
    //     return;
    // }
    //      ret = wifi_connect();
    // if (ret != 0) {
    //     LOG_ERR("Wi-Fi connection failed");
    //     return ret;
    // }

    LOG_INF("Wi-Fi connected! Starting main loop...");
   

    // const struct device *sensor = DEVICE_DT_GET_ANY(st_lis2dh);

    // lisd2h_init(sensor);

    while (1) {
        // lv_timer_handler();                 // Update display
        // lisd2h_poll_once(sensor);          // Read sensor and print
        //  /* Fetch sensor data and print it */
        // ret = sht4x_sensor_data(sht4x_sensor);
        // if (ret) {
        //     return;
        // }
        k_msleep(SLEEP_TIME_MS);
    }
}



 
