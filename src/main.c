#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <zephyr/drivers/display.h>
#include <zephyr/drivers/gpio.h>
#include <lvgl.h>

#include "../components/ILI9341_display/ili9341_display.h"

#define SLEEP_TIME_MS 10

void main(void) {
    ili9341_display_init();

    while (1) {
        lv_timer_handler();
        k_msleep(SLEEP_TIME_MS);
    }
}
