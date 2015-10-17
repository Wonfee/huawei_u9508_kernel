/*sensor unification for differ platform*/
/*==============================================================================
History

Problem NO.         Name        Time         Reason

==============================================================================*/
#include <linux/kernel.h>
#include <linux/gpio.h>
#include <linux/init.h>
#include <linux/platform_device.h>
#include <linux/input.h>
#include <linux/io.h>
#include <linux/i2c.h>
#include <mach/gpio.h>
#include <mach/boardid.h>

#include "../../accelerometer/lis3dh.h"
#include "../../accelerometer/adxl34x.h"
#include "../../accelerometer/gs_mma8452.h"
#include "../../gyroscope/l3g4200d.h"
#include "../../compass/akm8975.h"
#include "../../compass/akm8963.h"
#include "../../light/apds990x.h"
#include "../../compass/yas.h"
#include "../../compass/yas_cfg.h"
#include <linux/board_sensors.h>
#include <hsad/config_interface.h>

#define GSENSOR_INT_GPIO	GPIO_18_4
#define COMPASS_INT_GPIO	GPIO_15_5
#define PROXIMITY_INT_GPIO	GPIO_15_6

static struct lis3dh_acc_platform_data gs_platform_data = {

	.poll_interval = 10,
	.min_interval = 10,

	.g_range = 0x00,

	.axis_map_x = 0,
	.axis_map_y = 1,
	.axis_map_z = 2,

	.negate_x = 1,	
	.negate_y = 1,	
	.negate_z = 0,

	.gpio_int1 = -1, /* if used this irq,set gpio_int1=GPIO_18_4 */
	.gpio_int2 = -1, /* if used this irq,set gpio_int2=GPIO_6_3	*/
};

struct mma8452_acc_platform_data mma8452_platform_data = {
};

static struct akm8975_platform_data compass_platform_data = {
	.gpio_DRDY = GPIO_15_5 ,/* GPIO-125	*/ 
};
#ifdef CONFIG_HUAWEI_FEATURE_SENSORS_AKM8963
static struct akm8963_platform_data compass_akm8963_platform_data = {
	.outbit = 1,
	.gpio_DRDY = GPIO_15_5 ,/* GPIO-125	*/
	.gpio_RST = 0,
};
#endif
static struct l3g4200d_gyr_platform_data l3g4200d_gyr_platform_data = {
	.poll_interval = 10,
	.min_interval = 10,

	.fs_range = 0x30,

	.axis_map_x = 1,	
	.axis_map_y = 0,
	.axis_map_z = 2,

	.negate_x = 1,
	.negate_y = 1,
	.negate_z = 0,
};

static struct adxl34x_platform_data adxl34x_default_init = {
	.tap_threshold = 35,
	.tap_duration = 3,
	.tap_latency = 20,
	.tap_window = 20,
	.tap_axis_control = ADXL_TAP_X_EN | ADXL_TAP_Y_EN | ADXL_TAP_Z_EN,
	.act_axis_control = 0xFF,
	.activity_threshold = 6,
	.inactivity_threshold = 4,
	.inactivity_time = 3,
	.free_fall_threshold = 8,
	.free_fall_time = 0x20,
	.data_rate = 10,
	/* .data_rate = 8, */
	.data_range = ADXL_FULL_RES,

	.ev_type = EV_ABS,
	.ev_code_x = ABS_X,    /* EV_REL */
	.ev_code_y = ABS_Y,    /* EV_REL */
	.ev_code_z = ABS_Z,    /* EV_REL */

	.ev_code_tap_x = BTN_TOUCH,    /* EV_KEY */
	.ev_code_tap_y = BTN_TOUCH,    /* EV_KEY */
	.ev_code_tap_z = BTN_TOUCH,    /* EV_KEY */
	.power_mode = ADXL_LINK,
	.fifo_mode = FIFO_STREAM,
	.watermark = 0,
};

struct apds990x_platform_data apds990x_light_platform_data = {
};
#ifdef CONFIG_HUAWEI_FEATURE_SENSORS_YAMAHA_COMPASS
static struct yamaha_platform_data yamaha_compass_platform_data = {
	.gpio_DRDY = GPIO_15_5,
	.gpio_RST = 48,
	.layout = 3,
	.outbit = 1,
};
#endif

static struct i2c_board_info  k3v2oem1_i2c_0_boardinfo[] = {

#ifdef CONFIG_HUAWEI_FEATURE_SENSORS_AKM8975
	{
		I2C_BOARD_INFO(AKM8975C_I2C_NAME, AKM8975C_I2C_ADDR),
		.platform_data = &compass_platform_data,
		.irq = IRQ_GPIO(COMPASS_INT_GPIO),
	},
#endif
#ifdef CONFIG_HUAWEI_FEATURE_SENSORS_AKM8963
	{
		I2C_BOARD_INFO(AKM8963_I2C_NAME, AKM8963_I2C_ADDR),
		.platform_data = &compass_akm8963_platform_data,
		.irq = IRQ_GPIO(COMPASS_INT_GPIO),
	},
#endif
#ifdef CONFIG_HUAWEI_FEATURE_SENSORS_YAMAHA_COMPASS
    {
        I2C_BOARD_INFO("yamaha_geomagnetic", 0x2e),//7 bit addr, no write bit
        .platform_data = &yamaha_compass_platform_data,
		.irq = IRQ_GPIO(COMPASS_INT_GPIO),
	},
#endif
#ifdef CONFIG_HUAWEI_FEATURE_SENSORS_ACCELEROMETER_ST_LIS3XH
	{
		I2C_BOARD_INFO(LIS3DH_I2C_NAME, LIS3DH_I2C_ADDR),
		.platform_data = &gs_platform_data,
	},
#endif

#ifdef CONFIG_HUAWEI_FEATURE_SENSORS_ACCELEROMETER_MMA8452
	{
		I2C_BOARD_INFO(MMA8452_I2C_NAME, MMA8452_I2C_ADDR),
		.platform_data = &mma8452_platform_data,
	},
#endif

#ifdef CONFIG_HUAWEI_FEATURE_GYROSCOPE_L3G4200DH
	{
		I2C_BOARD_INFO(L3G4200D_I2C_NAME, L3G4200D_I2C_ADDR),
		.platform_data = &l3g4200d_gyr_platform_data,
	},
#endif

#ifdef CONFIG_HUAWEI_FEATURE_SENSORS_ACCELEROMETER_ADI_ADXL346
	{
		I2C_BOARD_INFO(ADXL34X_I2C_NAME, ADXL34X_I2C_ADDR),
		.irq = IRQ_GPIO(GSENSOR_INT_GPIO),
		.platform_data = &adxl34x_default_init,
	},
#endif

#ifdef CONFIG_HUAWEI_FEATURE_PROXIMITY_APDS990X
	{
		I2C_BOARD_INFO(APDS990x_I2C_NAME, APDS990x_I2C_ADDR),
		.irq = IRQ_GPIO(PROXIMITY_INT_GPIO),
		.platform_data = &apds990x_light_platform_data,
	},
#endif

};

/* sensor layout init for different board */
void sensor_layout_init(void)
{
	unsigned int sensor_type;

	sensor_type = get_sensor_type();
	switch (sensor_type) {
	case E_SENSOR_TYPE_PHONE:
		gs_platform_data.negate_x = 1;
		gs_platform_data.negate_y = 1;
		mma8452_platform_data.config_mxc_mma_position = 1;
		adxl34x_default_init.config_adxl34x_position = 0;
		compass_platform_data.config_akm_position = 3;
		#ifdef CONFIG_HUAWEI_FEATURE_SENSORS_AKM8963
		compass_akm8963_platform_data.layout = 3;
		#endif
		l3g4200d_gyr_platform_data.negate_x = 1;
		l3g4200d_gyr_platform_data.negate_y = 1;
		break;
	case E_SENSOR_TYPE_PLATFORM:
		gs_platform_data.negate_x = 0;
		gs_platform_data.negate_y = 0;
		mma8452_platform_data.config_mxc_mma_position = 3;
		adxl34x_default_init.config_adxl34x_position = 2;
		compass_platform_data.config_akm_position = 1;
		l3g4200d_gyr_platform_data.negate_x = 0;
		l3g4200d_gyr_platform_data.negate_y = 0;
		break;
	default:
		pr_err("sensor_type unsupported\n");
		break;
	}
}

static int __devinit hw_devices_init(void)
{
	sensor_layout_init();
	i2c_register_board_info(0, k3v2oem1_i2c_0_boardinfo, ARRAY_SIZE(k3v2oem1_i2c_0_boardinfo));
	return 0;
}

core_initcall(hw_devices_init);

MODULE_AUTHOR("huawei skf55108");
MODULE_DESCRIPTION("huawei devices init");
MODULE_LICENSE("GPL");
