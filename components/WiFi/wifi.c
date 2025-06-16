// #include <zephyr/kernel.h>
// #include <zephyr/net/net_mgmt.h>
// #include <zephyr/net/wifi_mgmt.h>
// #include <net/wifi_credentials.h>
// #include <zephyr/logging/log.h>
// #include <zephyr/device.h>

#include "wifi.h"

// LOG_MODULE_REGISTER(wifi_module, LOG_LEVEL_INF);

// #define EVENT_MASK (NET_EVENT_L4_CONNECTED | NET_EVENT_L4_DISCONNECTED)

// static struct net_mgmt_event_callback mgmt_cb;
// static bool connected;
// static K_SEM_DEFINE(wifi_connected_sem, 0, 1);

// static void net_mgmt_event_handler(struct net_mgmt_event_callback *cb,
//                                    uint32_t mgmt_event, struct net_if *iface)
// {
//     if ((mgmt_event & EVENT_MASK) != mgmt_event) {
//         return;
//     }

//     if (mgmt_event == NET_EVENT_L4_CONNECTED) {
//         LOG_INF("Wi-Fi connected");
//         connected = true;
//         k_sem_give(&wifi_connected_sem);
//     }

//     if (mgmt_event == NET_EVENT_L4_DISCONNECTED) {
//         if (connected) {
//             LOG_INF("Wi-Fi disconnected");
//             connected = false;
//         } else {
//             LOG_INF("Waiting for connection...");
//         }
//         k_sem_reset(&wifi_connected_sem);
//     }
// }

// #ifdef CONFIG_WIFI_CREDENTIALS_STATIC
// static int wifi_args_to_params(struct wifi_connect_req_params *params)
// {
//     params->ssid = CONFIG_WIFI_CREDENTIALS_STATIC_SSID;
//     params->ssid_length = strlen(params->ssid);
//     params->psk = CONFIG_WIFI_CREDENTIALS_STATIC_PASSWORD;
//     params->psk_length = strlen(params->psk);
//     params->channel = WIFI_CHANNEL_ANY;
//     params->security = WIFI_SECURITY_TYPE_PSK;
//     params->mfp = WIFI_MFP_OPTIONAL;
//     params->timeout = SYS_FOREVER_MS;
//     params->band = WIFI_FREQ_BAND_UNKNOWN;
//     memset(params->bssid, 0, sizeof(params->bssid));
//     return 0;
// }
// #endif

// int wifi_connect(void)
// {
//     net_mgmt_init_event_callback(&mgmt_cb, net_mgmt_event_handler, EVENT_MASK);
//     net_mgmt_add_event_callback(&mgmt_cb);

//     struct net_if *iface = net_if_get_first_wifi();
//     if (iface == NULL) {
//         LOG_ERR("No Wi-Fi interface found");
//         return -ENODEV;
//     }

// #ifdef CONFIG_WIFI_CREDENTIALS_STATIC
//     struct wifi_connect_req_params params;
//     wifi_args_to_params(&params);

//     LOG_INF("Attempting to connect to SSID: %s", CONFIG_WIFI_CREDENTIALS_STATIC_SSID);
//     int err = net_mgmt(NET_REQUEST_WIFI_CONNECT, iface, &params, sizeof(params));
//     if (err) {
//         LOG_ERR("Wi-Fi connection failed: %d", err);
//         return err;
//     }

//     k_sem_take(&wifi_connected_sem, K_SECONDS(15));
//     if (!connected) {
//         LOG_ERR("Wi-Fi connection timed out");
//         return -ETIMEDOUT;
//     }
// #endif

//     return 0;
// }
