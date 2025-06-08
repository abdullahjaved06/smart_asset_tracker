#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <zephyr/drivers/display.h>
#include <zephyr/drivers/gpio.h>
#include <lvgl.h>

#define SLEEP_TIME_MS 10
#define BACKLIGHTNODE DT_NODELABEL(backlight)

static const struct gpio_dt_spec backlight_gpio = GPIO_DT_SPEC_GET(BACKLIGHTNODE, gpios);

void main(void) {
    const struct device *display_dev;

      if (!device_is_ready(backlight_gpio.port)) {
        printk("Backlight GPIO device not ready\n");
        return;
    }
    gpio_pin_configure_dt(&backlight_gpio, GPIO_OUTPUT_ACTIVE);  // Set HIGH initially
    gpio_pin_set_dt(&backlight_gpio,1); //set HIGH
    display_dev = DEVICE_DT_GET(DT_CHOSEN(zephyr_display));
    if (!device_is_ready(display_dev)) {
        printk("Display device not ready\n");
        return;
    }
    printk("Display ready...\n");

    // Set screen background color
    // lv_obj_set_style_bg_color(lv_scr_act(), lv_color_white(), LV_PART_MAIN);
    // lv_obj_set_style_bg_opa(lv_scr_act(), LV_OPA_COVER, LV_PART_MAIN);

    lv_obj_set_style_bg_color(lv_scr_act(), lv_color_hex(0x3366FF), LV_PART_MAIN);
    lv_obj_set_style_bg_opa(lv_scr_act(), LV_OPA_COVER, LV_PART_MAIN);


    // Create a label with custom style
    static lv_style_t style;
    lv_style_init(&style);

    lv_style_set_text_font(&style, &lv_font_montserrat_28);
    lv_style_set_text_color(&style, lv_color_black());

    lv_style_set_bg_color(&style, lv_color_hex(0x3366FF)); // Optional: label background
    lv_style_set_bg_opa(&style, LV_OPA_COVER);
    lv_style_set_pad_all(&style, 10);
    lv_style_set_radius(&style, 10);

    lv_obj_t *label = lv_label_create(lv_scr_act());
    lv_obj_add_style(label, &style, LV_PART_MAIN);
    lv_label_set_text(label, "Hello Display!");
    lv_obj_align(label, LV_ALIGN_CENTER, 0, 0);

    // Refresh LVGL and unblank the display
    lv_task_handler();
    display_blanking_off(display_dev);

    while (1) {
        lv_timer_handler();
        k_msleep(SLEEP_TIME_MS);
    }
}
