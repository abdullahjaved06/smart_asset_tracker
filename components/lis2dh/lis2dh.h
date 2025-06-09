#ifndef LIS2DH_H
#define LIS2DH_H

#include <zephyr/device.h>

#ifdef __cplusplus
extern "C" {
#endif

void lisd2h_init(const struct device *sensor);
void lisd2h_poll_once(const struct device *sensor);  // optional: single-shot poll


#ifdef __cplusplus
}
#endif

#endif // LIS2DH_H
