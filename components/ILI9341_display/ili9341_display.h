#ifndef DISPLAY_ILI9341_H
#define DISPLAY_ILI9341_H

#ifdef __cplusplus
extern "C" {
#endif

#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/display.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/devicetree.h>
#include <lvgl.h>

int display_init(void);
static void setup_screen_background(void);
static void init_label_style(void);
void ili9341_display_init(void);
void display_text_at(const char *text, lv_coord_t x, lv_coord_t y);


#ifdef __cplusplus
}
#endif

#endif // DISPLAY_ILI9341_H
