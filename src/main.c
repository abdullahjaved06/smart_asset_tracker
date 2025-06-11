#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/devicetree.h>

#include "../components/ILI9341_display/ili9341_display.h"
#include "../components/lis2dh/lis2dh.h"
#include "../components/sht4x/sht4x.h"

    const struct device *sensor = DEVICE_DT_GET(DT_NODELABEL(lis2dh12));
    const struct device *sht4x_sensor = DEVICE_DT_GET(DT_NODELABEL(sht4x));


#define SLEEP_TIME_MS 2000

void main(void) {
    ili9341_display_init();

    // const struct device *sensor = DEVICE_DT_GET_ANY(st_lis2dh);

    lisd2h_init(sensor);

    while (1) {
        lv_timer_handler();                 // Update display
        lisd2h_poll_once(sensor);          // Read sensor and print
        k_msleep(SLEEP_TIME_MS);
    }
}

