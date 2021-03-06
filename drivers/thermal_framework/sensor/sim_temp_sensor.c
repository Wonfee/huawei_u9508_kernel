/*
 * Copyright (c) 2011 Hisilicon Technologies Co., Ltd. All rights reserved.
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * COPYING in the main directory of this source tree, or the
 * OpenIB.org BSD license below:
 *
 *     Redistribution and use in source and binary forms, with or
 *     without modification, are permitted provided that the following
 *     conditions are met:
 *
 *      - Redistributions of source code must retain the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer.
 *
 *      - Redistributions in binary form must reproduce the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer in the documentation and/or other materials
 *        provided with the distribution.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
#include <linux/err.h>
#include <linux/io.h>
#include <linux/debugfs.h>
#include <linux/delay.h>
#include <linux/slab.h>
#include <linux/platform_device.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/device.h>
#include <linux/stddef.h>
#include <linux/sysfs.h>
#include <linux/types.h>
#include <linux/mutex.h>
#include <linux/thermal_framework.h>
#include <linux/temperature_sensor.h>

struct sim_temp_sensor {
	struct platform_device *pdev;
	struct device *dev;
	struct thermal_dev *therm_fw;
	int debug_temp;
};

#define ADC_RTMP_FOR_SIM 0x02
#define SIM_REPORT_DELAY_MS	1000

static int sim_read_current_temp(struct sim_temp_sensor *temp_sensor)
{
	int temp = 0;
	temp = getcalctemperature(ADC_RTMP_FOR_SIM);

	return temp;
}

static int sim_get_temp(struct thermal_dev *tdev)
{
	struct platform_device *pdev = to_platform_device(tdev->dev);
	struct sim_temp_sensor *temp_sensor = platform_get_drvdata(pdev);

	if (NULL == temp_sensor) {
		pr_err("%s %d, platform_get_drvdata is NULL\n", __func__, __LINE__);
		return -1;
	}

	temp_sensor->therm_fw->current_temp =
			sim_read_current_temp(temp_sensor);

	return temp_sensor->therm_fw->current_temp;
}

static void sim_report_fw_temp(struct thermal_dev *tdev)
{
	struct platform_device *pdev = to_platform_device(tdev->dev);
	struct sim_temp_sensor *temp_sensor = platform_get_drvdata(pdev);
	int ret;

	if (NULL == temp_sensor) {
		pr_err("%s %d, platform_get_drvdata is NULL\n", __func__, __LINE__);
		return -1;
	}

	temp_sensor->therm_fw->current_temp = sim_read_current_temp(temp_sensor);
	if (temp_sensor->therm_fw->current_temp != -EINVAL) {
		ret = thermal_sensor_set_temp(temp_sensor->therm_fw);
		if (ret == -ENODEV)
			pr_err("%s:thermal_sensor_set_temp reports error\n",
				__func__);
		kobject_uevent(&temp_sensor->dev->kobj, KOBJ_CHANGE);
	}
}

/*
 * sysfs hook functions
 */
static ssize_t show_sim_temp_user_space(struct device *dev,
			struct device_attribute *devattr, char *buf)
{
	struct platform_device *pdev = to_platform_device(dev);
	struct sim_temp_sensor *temp_sensor = platform_get_drvdata(pdev);

	if (NULL == temp_sensor) {
		pr_err("%s %d, platform_get_drvdata is NULL\n", __func__, __LINE__);
		return -1;
	}

	return snprintf(buf, sizeof(int), "%d\n", temp_sensor->debug_temp);
}

static ssize_t set_sim_temp_user_space(struct device *dev,
			struct device_attribute *devattr,
			const char *buf, size_t count)
{
	struct platform_device *pdev = to_platform_device(dev);
	struct sim_temp_sensor *temp_sensor = platform_get_drvdata(pdev);
	long val;

	if (NULL == temp_sensor) {
		pr_err("%s %d, platform_get_drvdata is NULL\n", __func__, __LINE__);
		return -1;
	}

	if (strict_strtol(buf, 10, &val)) {
		count = -EINVAL;
		pr_err("%s error message[%d]\n\r", __func__, count);
		return count;
	}

	/* Set new temperature */
	temp_sensor->debug_temp = val;

	temp_sensor->therm_fw->current_temp = val;
	thermal_sensor_set_temp(temp_sensor->therm_fw);
	/* Send a kobj_change */
	kobject_uevent(&temp_sensor->dev->kobj, KOBJ_CHANGE);

	return count;
}

static int sim_temp_sensor_read_temp(struct device *dev,
				      struct device_attribute *devattr,
				      char *buf)
{
	struct platform_device *pdev = to_platform_device(dev);
	struct sim_temp_sensor *temp_sensor = platform_get_drvdata(pdev);
	int temp = 0;

	if (NULL == temp_sensor) {
		pr_err("%s %d, platform_get_drvdata is NULL\n", __func__, __LINE__);
		return -1;
	}

	temp = sim_read_current_temp(temp_sensor);
	return snprintf(buf, sizeof(int), "%d\n", temp);
}

static DEVICE_ATTR(debug_sim_user, S_IWUSR | S_IRUGO, show_sim_temp_user_space,
			  set_sim_temp_user_space);
static DEVICE_ATTR(temp_sim_input, S_IRUGO, sim_temp_sensor_read_temp,
			  NULL);

static struct attribute *sim_temp_sensor_attributes[] = {
	&dev_attr_temp_sim_input.attr,
	&dev_attr_debug_sim_user.attr,
	NULL
};

static const struct attribute_group sim_temp_sensor_group = {
	.attrs = sim_temp_sensor_attributes,
};


static struct thermal_dev_ops sim_sensor_ops = {
	.report_temp = sim_get_temp,
};

static int __devinit sim_temp_sensor_probe(struct platform_device *pdev)
{
	struct sim_temp_sensor_pdata *pdata = pdev->dev.platform_data;
	struct sim_temp_sensor *temp_sensor;
	int ret = 0;

	if (!pdata) {
		dev_err(&pdev->dev, "%s: platform data missing\n", __func__);
		return -EINVAL;
	}

	temp_sensor = kzalloc(sizeof(struct sim_temp_sensor), GFP_KERNEL);
	if (!temp_sensor)
		return -ENOMEM;

	temp_sensor->pdev = pdev;
	temp_sensor->dev = &pdev->dev;

	kobject_uevent(&pdev->dev.kobj, KOBJ_ADD);
	platform_set_drvdata(pdev, temp_sensor);

	temp_sensor->therm_fw = kzalloc(sizeof(struct thermal_dev), GFP_KERNEL);
	if (NULL == temp_sensor->therm_fw) {
		dev_err(&pdev->dev, "%s:Cannot alloc memory for thermal fw\n",
			__func__);
		ret = -ENOMEM;
		goto therm_fw_alloc_err;
	}

	temp_sensor->therm_fw->name = "sim_sensor";
	temp_sensor->therm_fw->domain_name = "cpu";
	temp_sensor->therm_fw->dev = temp_sensor->dev;
	temp_sensor->therm_fw->dev_ops = &sim_sensor_ops;
	thermal_sensor_dev_register(temp_sensor->therm_fw);

	ret = sysfs_create_group(&pdev->dev.kobj,
				 &sim_temp_sensor_group);
	if (ret) {
		dev_err(&pdev->dev, "could not create sysfs files\n");
		goto sysfs_create_err;
	}

	sim_report_fw_temp(temp_sensor->therm_fw);

	dev_info(&pdev->dev, "%s : '%s'\n", temp_sensor->therm_fw->name,
			pdata->name);

	return ret;

sysfs_create_err:
	thermal_sensor_dev_unregister(temp_sensor->therm_fw);
	kfree(temp_sensor->therm_fw);
	platform_set_drvdata(pdev, NULL);
therm_fw_alloc_err:
	kfree(temp_sensor);
	return ret;
}

static int __devexit sim_temp_sensor_remove(struct platform_device *pdev)
{
	struct sim_temp_sensor *temp_sensor = platform_get_drvdata(pdev);

	if (NULL == temp_sensor) {
		pr_err("%s %d, platform_get_drvdata is NULL\n", __func__, __LINE__);
		return -1;
	}

	sysfs_remove_group(&pdev->dev.kobj, &sim_temp_sensor_group);
	thermal_sensor_dev_unregister(temp_sensor->therm_fw);
	kfree(temp_sensor->therm_fw);
	kobject_uevent(&temp_sensor->dev->kobj, KOBJ_REMOVE);
	platform_set_drvdata(pdev, NULL);
	kfree(temp_sensor);

	return 0;
}

static struct platform_driver sim_temp_sensor_driver = {
	.probe = sim_temp_sensor_probe,
	.remove = sim_temp_sensor_remove,
	.driver = {
		.name = "sim_temp_sensor",
	},
};

int __init sim_temp_sensor_init(void)
{
	return platform_driver_register(&sim_temp_sensor_driver);
}

static void __exit sim_temp_sensor_exit(void)
{
	platform_driver_unregister(&sim_temp_sensor_driver);
}

module_init(sim_temp_sensor_init);
module_exit(sim_temp_sensor_exit);

MODULE_DESCRIPTION("SIM Temperature Sensor Driver");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:" DRIVER_NAME);
MODULE_AUTHOR("Texas Instruments Inc");
