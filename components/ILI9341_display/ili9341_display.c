#include "ili9341_display.h"



#define BACKLIGHTNODE DT_NODELABEL(backlight)
static const struct gpio_dt_spec backlight_gpio = GPIO_DT_SPEC_GET(BACKLIGHTNODE, gpios);

const struct device *display_dev = DEVICE_DT_GET(DT_CHOSEN(zephyr_display));

static uint32_t screen_bg_color = 0x3366FF;
static lv_style_t label_style;
static bool style_ready = false;

int display_init(void)
{
    if (!device_is_ready(backlight_gpio.port)) {
        printk("Backlight GPIO device not ready\n");
        return -1;
    }
    gpio_pin_configure_dt(&backlight_gpio, GPIO_OUTPUT_ACTIVE);
    gpio_pin_set_dt(&backlight_gpio, 1);

    if (!device_is_ready(display_dev)) {
        printk("Display device not ready\n");
        return -2;
    }

    printk("Display ready...\n");
    return 0;
}

static void setup_screen_background(void)
{
    lv_obj_set_style_bg_color(lv_scr_act(), lv_color_hex(screen_bg_color), LV_PART_MAIN);
    lv_obj_set_style_bg_opa(lv_scr_act(), LV_OPA_COVER, LV_PART_MAIN);
}

static void init_label_style(void)
{
    if (style_ready) return;

    lv_style_init(&label_style);
    lv_style_set_text_font(&label_style, &lv_font_montserrat_20);
    lv_style_set_text_color(&label_style, lv_color_black());
    lv_style_set_bg_opa(&label_style, LV_OPA_TRANSP);  // transparent background
    // lv_style_set_pad_all(&label_style, 10);
    // lv_style_set_radius(&label_style, 10);

    style_ready = true;
}

void ili9341_display_init(void)
{
    if (display_init() != 0) {
        return;
    }

    setup_screen_background();
    init_label_style();

    display_blanking_off(display_dev);
    lv_task_handler();
}

void display_text_at(const char *text, lv_coord_t x, lv_coord_t y)
{
    if (!style_ready || text == NULL) return;

    lv_obj_t *label = lv_label_create(lv_scr_act());
    lv_obj_add_style(label, &label_style, LV_PART_MAIN);
    // lv_obj_set_width(label, 300);  // Optional: limit label width for wrapping
    lv_label_set_long_mode(label, LV_LABEL_LONG_WRAP);
    lv_label_set_text(label, text);
    lv_obj_align(label, LV_ALIGN_TOP_LEFT, x, y);

    lv_task_handler();
}
