

#ifndef CONFIG_INTERFACE_H
#define CONFIG_INTERFACE_H

#include <linux/types.h>

extern bool product_type(char *pname);
extern bool get_spk_pa(char *spk_pa);
	
extern int get_touchscreen_type(void);
extern int get_usbphy_tune(void);
extern int get_board_type(void);
extern int get_sd_detect_type(void);
extern int get_sensor_type(void);
extern int get_iomux_type(void);
extern int get_sensor_timing_type();

typedef enum _config_touchscreen_type {
	E_TOUCHSCREEN_TYPE_PLATFORM = 0,
	E_TOUCHSCREEN_TYPE_PHONE
} config_touchscreen_type;

typedef enum _config_usbphy_tune {
	E_USBPHY_TUNE_PLATFORM = 0,
	E_USBPHY_TUNE_U9510
} config_usbphy_tune;

typedef enum _config_board_type {
	E_BOARD_TYPE_PLATFORM = 0,
	E_BOARD_TYPE_U9510,
	E_BOARD_TYPE_U9508
} config_board_type;

typedef enum _config_sensor_type {
	E_SENSOR_TYPE_PLATFORM = 0,
	E_SENSOR_TYPE_PHONE
} config_sensor_type;

typedef enum _config_iomux_type {
	E_IOMUX_PALTFORM_ES = 0,
	E_IOMUX_PALTFORM_CS,
	E_IOMUX_PHONE_ES,
	E_IOMUX_PHONE_CS,
	E_IOMUX_MAX
} config_iomux_type;

typedef enum _sd_detect_type
{
	GPIO_LOW_MEAN_DETECTED =0,
	GPIO_HIGH_MEAN_DETECTED,
	SD_DETECT_TYPE_MAX
}sd_detect_type;

#ifdef CONFIG_HUAWEI_GPIO_UNITE

extern struct gpio_config_type *get_gpio_config_table(void);
extern int get_gpio_num_by_name(char *name);
extern struct pm_gpio_cfg_t *get_pm_gpio_config_table(void);
extern int get_pm_gpio_num_by_name(char *name);

#endif

#ifdef CONFIG_HW_POWER_TREE
extern struct hw_config_power_tree *get_power_config_table(void);
#endif

extern int get_hsd_invert(void);
extern int get_hs_keys(void);

#endif
