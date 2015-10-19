/*
 *  Hisilicon K3 soc camera sensor header file
 *
 *  CopyRight (C) Hisilicon Co., Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#ifndef CAMERA_SENSOR_H_INCLUDED
#define CAMERA_SENSOR_H_INCLUDED

#include <linux/videodev2.h>
#include "../camera.h"

#define LDO_VOLTAGE_15V  1500000
#define LDO_VOLTAGE_18V  1800000
#define LDO_VOLTAGE_28V  2850000

#define CAMERA_MAX_FRAMERATE		30
#define CAMERA_MIN_FRAMERATE		15

#define CAMERA_MIN_CAP_FRAMERATE		8

/* Default camera sensor definitions(use K3 ISP), maybe override by sensor*/
#define CAMERA_MAX_ISO			1600
#define CAMERA_MIN_ISO			100


#define CAMERA_AUTO_FPS_MAX_GAIN	0x60
#define CAMERA_AUTO_FPS_MIN_GAIN	0x28

#define CAMERA_MAX_FRAMERATE		30
#define CAMERA_MIN_FRAMERATE		15
#define CAMERA_MIN_CAP_FRAMERATE	8

#define CAMERA_FLASH_TRIGGER_GAIN	0x80

#define CAMERA_SHARPNESS_PREVIEW	0x30
#define CAMERA_SHARPNESS_CAPTURE	0x0A

/* Below is recommended to be fixed parameters */
#define AUTO_FRAME_RATE_TRIGER_COUNT		4
#define FLASH_TRIGGER_LUM_RATIO	0xc0
/* 600mA flash lum maybe only 4 times of 100mA. */
#define FLASH_CAP2PRE_RATIO			0x04

#define CAMERA_EXPOSURE_MAX		2
#define CAMERA_EXPOSURE_STEP	100

typedef enum {
	CAMERA_CONTRAST_L2 = 0,
	CAMERA_CONTRAST_L1,
	CAMERA_CONTRAST_H0,
	CAMERA_CONTRAST_H1,
	CAMERA_CONTRAST_H2,
	CAMERA_CONTRAST_MAX,
} camera_contrast;

typedef enum {
	CAMERA_SATURATION_L2 = 0,
	CAMERA_SATURATION_L1,
	CAMERA_SATURATION_H0,
	CAMERA_SATURATION_H1,
	CAMERA_SATURATION_H2,
	CAMERA_SATURATION_MAX,
} camera_saturation;

typedef enum {
	CAMERA_FPS_MAX = 0,
	CAMERA_FPS_MIN,
} camera_fps;

typedef enum {
	CAMERA_FRAME_RATE_FIX_MAX = 0,
	CAMERA_FRAME_RATE_FIX_MIN,
	CAMERA_FRAME_RATE_AUTO,
	CAMERA_FRAME_RATE_MAX,
} camera_frame_rate_mode;

typedef enum {
	CAMERA_MAX_EXPOSURE_LIMIT = 0,
	CAMERA_MAX_EXPOSURE_RESUME,
} camera_max_exposrure;

typedef enum {
	CAMERA_EFFECT_NONE = 0,
	CAMERA_EFFECT_MONO,
	CAMERA_EFFECT_NEGATIVE,
	CAMERA_EFFECT_SOLARIZE,
	CAMERA_EFFECT_SEPIA,
	CAMERA_EFFECT_POSTERIZE,
	CAMERA_EFFECT_WHITEBOARD,
	CAMERA_EFFECT_BLACKBOARD,
	CAMERA_EFFECT_AQUA,
	CAMERA_EFFECT_PASTEL,
	CAMERA_EFFECT_MOSAIC,
	CAMERA_EFFECT_REDTINT,
	CAMERA_EFFECT_BLUETINT,
	CAMERA_EFFECT_GREENTINT,
	CAMERA_EFFECT_MAX,
} camera_effects;

typedef enum {
	CAMERA_SHARPNESS_AUTO = 0,
	CAMERA_SHARPNESS_1,
	CAMERA_SHARPNESS_2,
	CAMERA_SHARPNESS_3,
	CAMERA_SHARPNESS_4,
	CAMERA_SHARPNESS_5,
} camera_sharpness;

typedef enum {
	CAMERA_ISO_AUTO = 0,
	CAMERA_ISO_100,
	CAMERA_ISO_200,
	CAMERA_ISO_400,
	CAMERA_ISO_800,
} camera_iso;

typedef enum {
	CAMERA_METERING_SPOT = 0,
	CAMERA_METERING_CWA,
	CAMERA_METERING_AVERAGE,
} camera_metering;

typedef enum {
	CAMERA_FLASH_ON = 0,
	CAMERA_FLASH_TORCH,
	CAMERA_FLASH_OFF,
	CAMERA_FLASH_AUTO,
	CAMERA_FLASH_MAX,
} camera_flash;

typedef enum {
	CAMERA_RESOLUTION_QCIF,	/* 176 x 144   */
	CAMERA_RESOLUTION_240x176,	/* 240 x 176   */
	CAMERA_RESOLUTION_QVGA,	/* 320 x 240   */
	CAMERA_RESOLUTION_CIF,	/* 352 x 288   */
	CAMERA_RESOLUTION_HVGA,	/* 480 x 320   */
	CAMERA_RESOLUTION_VGA,	/* 640 x 480   */
	CAMERA_RESOLUTION_800x480,	/* 800 x 480   */
	CAMERA_RESOLUTION_SVGA,	/* 800 x 600   */
	CAMERA_RESOLUTION_XGA,	/* 1024 x 768  same as CAMERA_RESOLUTION_QTR_3M */
	CAMERA_RESOLUTION_720P,	/* 1280 x 720   add by y36721 */
	CAMERA_RESOLUTION_VGA4,	/* 1280 x 960  */
	CAMERA_RESOLUTION_QTR_5M,	/* 1296 x 972 (2592 x 1944/4) */
	CAMERA_RESOLUTION_SXGA,	/* 1280 x 1024 */
	CAMERA_RESOLUTION_UXGA,	/* 1600 x 1200 */
	CAMERA_RESOLUTION_1080P,	/* 1920 x 1080  add by y36721 */

	CAMERA_RESOLUTION_QTR_8M,	/*1632 x 1224 (3264 x 2448/4) */
	CAMERA_RESOLUTION_FULL_3M,	/* 2048 x 1536 */
	CAMERA_RESOLUTION_QTR_12M,	/*2104 x 1560 (4208 x 3120/4) */
	CAMERA_RESOLUTION_QTR_16M,	/*2304 x 1728 (4608 x 3456/4) */
	CAMERA_RESOLUTION_QTR_20M,	/* 2582 x 1936(5164 x 3872/4) */
	CAMERA_RESOLUTION_FULL_5M,	/* 2592 x 1944 */
	CAMERA_RESOLUTION_FULL_8M,	/* 3264 x 2448 */
	CAMERA_RESOLUTION_FULL_12M,	/* 4208 x 3120 */
	CAMERA_RESOLUTION_FULL_16M,	/* 4608 x 3456 */
	CAMERA_RESOLUTION_FULL_20M,	/* 5164 x 3872 */
	CAMERA_RESOLUTION_MAX,
} camera_resolutions;

typedef enum {
	CAMERA_SCENE_AUTO = 0,
	CAMERA_SCENE_ACTION,
	CAMERA_SCENE_PORTRAIT,
	CAMERA_SCENE_LANDSPACE,
	CAMERA_SCENE_NIGHT,
	CAMERA_SCENE_NIGHT_PORTRAIT,
	CAMERA_SCENE_THEATRE,
	CAMERA_SCENE_BEACH,
	CAMERA_SCENE_SNOW,
	CAMERA_SCENE_SUNSET,
	CAMERA_SCENE_STEADYPHOTO,
	CAMERA_SCENE_FIREWORKS,
	CAMERA_SCENE_SPORTS,
	CAMERA_SCENE_PARTY,
	CAMERA_SCENE_CANDLELIGHT,
	CAMERA_SCENE_BARCODE,
	CAMERA_SCENE_FLOWERS,
} camera_scene;

typedef enum {
	CAMERA_NO_FLIP = 0,
	CAMERA_H_FLIP,
	CAMERA_V_FLIP,
	CAMERA_HV_FLIP,
} camera_flip;

typedef enum {
	CAMERA_BRIGHTNESS_L2 = 0,
	CAMERA_BRIGHTNESS_L1,
	CAMERA_BRIGHTNESS_H0,
	CAMERA_BRIGHTNESS_H1,
	CAMERA_BRIGHTNESS_H2,
	CAMERA_BRIGHTNESS_MAX,
} camera_brightness;

typedef enum {
	CAMERA_WHITEBALANCE_AUTO = 0,
	CAMERA_WHITEBALANCE_INCANDESCENT,
	CAMERA_WHITEBALANCE_FLUORESCENT,
	CAMERA_WHITEBALANCE_WARM_FLUORESCENT,
	CAMERA_WHITEBALANCE_DAYLIGHT,
	CAMERA_WHITEBALANCE_CLOUDY_DAYLIGHT,
	CAMERA_WHITEBALANCE_TWILIGHT,
	CAMERA_WHITEBALANCE_CANDLELIGHT,
	CAMERA_WHITEBALANCE_MAX,
} camera_white_balance;

typedef enum {
	CAMERA_ANTI_BANDING_AUTO = 0,
	CAMERA_ANTI_BANDING_50Hz,
	CAMERA_ANTI_BANDING_60Hz,
	CAMERA_ANTI_BANDING_OFF,
} camera_anti_banding;

typedef enum {
	CAMERA_ZOOM_0 = 0,
	CAMERA_ZOOM_1,
	CAMERA_ZOOM_2,
	CAMERA_ZOOM_3,
	CAMERA_ZOOM_4,
	CAMERA_ZOOM_5,
} camera_zoom;

typedef enum {
	CAMERA_FOCUS_AUTO = 0,
	CAMERA_FOCUS_INFINITY,
	CAMERA_FOCUS_MACRO,
	CAMERA_FOCUS_FIXED,
	CAMERA_FOCUS_EDOF,
	CAMERA_FOCUS_CONTINUOUS_VIDEO,
	CAMERA_FOCUS_CONTINUOUS_PICTURE,
	CAMERA_FOCUS_AUTO_VIDEO,
	CAMERA_FOCUS_MAX,
} camera_focus;

typedef enum {
	CAMERA_ANTI_SHAKING_OFF = 0,
	CAMERA_ANTI_SHAKING_ON,
} camera_anti_shaking;

typedef enum {
	CAMERA_HDR_OFF = 0,
	CAMERA_HDR_ON,
} camera_hdr;

typedef enum {
	CAMERA_EDR_OFF = 0,
	CAMERA_EDR_ON,
} camera_edr;

typedef enum {
	CAMERA_3D_OFF = 0,
	CAMERA_3D_ON,
} camera_3d;

typedef struct {
	u32 id;
	u32 value;
} camera_capability;

typedef enum {
	CAPTURE_ONLINE,
	CAPTURE_OFFLINE,
} capture_type;

typedef enum {
	CAMERA_IPP_MODE_RAW_2_YUV = 0,
	CAMERA_IPP_MODE_HDR,
	CAMERA_IPP_MODE_MAX
} ipp_mode;

typedef enum {
	CAMERA_SHOOT_SINGLE = 0,
	CAMERA_SHOOT_BURST
} camera_shoot_mode;

typedef enum {
	CAMERA_FRAME_RATE_HIGH = 0,
	CAMERA_FRAME_RATE_LOW,
	CAMERA_EXPO_PRE_REDUCE,
} camera_frame_rate_state;

typedef enum {
	CAMERA_FRAME_RATE_UP = 0,
	CAMERA_FRAME_RATE_DOWN,
} camera_frame_rate_dir;

typedef struct _sensor_reg_t {
	u32 subaddr;
	u32 value;
	u8 mask;
	u16 size;
} sensor_reg_t;

typedef struct _sensor_setting_t {
	sensor_reg_t *setting;
	u32 seq_size;
} sensor_setting_t;

typedef struct _sensor_power_t {
	electrical_valid_t pd_valid;
	electrical_valid_t reset_valid;
	electrical_valid_t vcmpd_valid;
} sensor_power_t;

struct i2c_t {
	i2c_index_t index;
	i2c_speed_t speed;
	u32 addr;
	u32 addr_bits;
	i2c_length val_bits;
};

typedef enum {
	VIEW_FULL = 1,
	VIEW_CROP,
} camera_setting_view_type;

typedef enum {
	RESOLUTION_16_9 = 0,
	RESOLUTION_4_3,
} camera_resolution_type;

/* For sensor framesize definition */
typedef struct _framesize_s {
	u32 left;
	u32 top;
	u32 width;
	u32 height;
	u32 hts;		/* horizontal total size */
	u32 vts;		/* vertical total size */
	u32 fps;
	u32 fps_es;
	u32 banding_step_50hz;
	u32 banding_step_60hz;
	u32 capture_ratio;
	camera_setting_view_type view_type;
	camera_resolution_type resolution_type;
	bool binning;
	sensor_setting_t sensor_setting;	/* sensor setting for cmdset */
} framesize_s;

/* For ISP coordinate structure */
typedef struct _coordinate_s {
	u32 x;
	u32 y;
} coordinate_s;

/* For camera rect definition */
typedef struct _camera_rect_s {
	u32 left;
	u32 top;
	u32 width;
	u32 height;

	/*
	 * used for focus and metering areas; anti-shaking can ignore it.
	 * focus can define windows weight.
	 * every rect can have its own focus weight.
	 */
	u32 weight;
} camera_rect_s;
typedef struct crop_rect_s {
	u32 ori_width;
	u32 ori_height;
	u32 crop_width;
	u32 crop_height;
} crop_rect_s;


typedef struct _axis_triple {
	int x;
	int y;
	int z;
	struct timeval time;
} axis_triple;

/* For focus start or stop command */
typedef enum _FOCUS_ACTION {
	FOCUS_STOP = 0,
	FOCUS_START,
} FOCUS_ACTION;

/* For focus result */
typedef enum _FOCUS_STATUS {
	STATUS_FOCUSING = 0,
	STATUS_FOCUSED,
	STATUS_OUT_FOCUS,
} FOCUS_STATUS;

typedef enum _FOCUS_RANGE{
	RANGE_NORMAL = 0,
	RANGE_INFINITY,
	RANGE_MACRO,
} FOCUS_RANGE;

typedef enum _VCM_TYPE{
	VCM_AD5823 = 0,
	VCM_DW9714,
	VCM_OTHER,
} VCM_TYPE;

/*default should be designed as center area focus*/
typedef struct _focus_area_s {
	u32 focus_rect_num;
	camera_rect_s rect[MAX_FOCUS_RECT];
} focus_area_s;

/* focus result structure */
typedef struct _focus_result_s {
	FOCUS_STATUS status;
	FOCUS_STATUS each_status[MAX_FOCUS_RECT];
} focus_result_s;

/* metering area definition */
typedef struct _metering_area_s {
	u32 metering_rect_num;
	camera_rect_s rect[MAX_METERING_RECT];
} metering_area_s;

/* AF vcm information definition */
typedef struct _vcm_info_s {
	VCM_TYPE vcm_type;
	u32 vcm_bits;		/* 16bits or 8bits */
	u32 vcm_id;		/* for example, "DW9714" is 0x18 */
	u32 moveLensAddr[2];

	u32 offsetInit;		/* should be calibrated by focus at infinite distance */
	u32 fullRange;		/* should be calibrated by focus at an macro distance */

	u32 infiniteDistance;	/* should be calibrated by focus at infinite distance */

	u32 normalDistanceEnd;
	u32 normalStep;
	u32 normalStrideRatio; /* 0x10 is 1:1, 0x18 is 1:1.5, 0x20 is 1:2 */

	u32 videoDistanceEnd;
	u32 videoStep;
	u32 videoStrideRatio;

	u32 strideOffset;

	u32 coarseStep;
	u32 fineStep; /* half of coarseStep */

	u32 motorResTime;	/* response time, in unit of ms */
	u32 motorDelayTime;	/* delay time of each step in stride divide case */
	u32 strideDivideOffset;

	FOCUS_RANGE moveRange;/*0:Auto; 1:Infinite; 2:Macro*/


	void (*get_vcm_otp) (u16 *vcm_start, u16 *vcm_end);
} vcm_info_s;

struct _camera_sensor;

/* camera tune operations function definitions. */
typedef struct {
	/*
	 * isp_auto_focus:
	 * param: int flag=1 start, flag=0 cancel or stop
	 */
	int (*isp_auto_focus) (int flag);
	int (*isp_set_focus_mode) (camera_focus focus_mode);
	/*
	 * param: focus_area_s *area, rects definition;
	 */
	int (*isp_set_focus_area) (focus_area_s *area, u32 zoom);	
	int (*isp_get_focus_result) (focus_result_s *result);
	int (*isp_set_focus_zoom) (u32 zoom);
	int (*isp_set_sharpness_zoom) (u32 zoom);

	/* For anti-shaking */
	int (*isp_set_anti_shaking) (camera_anti_shaking flag);
	int (*isp_set_anti_shaking_block) (int blocksize);
	int (*isp_get_anti_shaking_coordinate) (coordinate_s *coordinate);

	/* For other functions */
	int (*set_iso) (camera_iso iso);
	int (*set_ev) (int ev);
	int (*set_metering_mode) (camera_metering mode);
	int (*set_metering_area) (metering_area_s *area, u32 zoom);

	int (*set_gsensor_stat) (axis_triple *xyz);

	int (*set_bracket_info) (int *ev);

	int (*set_anti_banding) (camera_anti_banding banding);
	int (*get_anti_banding) (void);
	int (*set_awb) (camera_white_balance awb_mode);

	int (*set_sharpness) (camera_sharpness sharpness);
	int (*set_saturation) (camera_saturation saturation);
	int (*set_contrast) (camera_contrast contrast);
	int (*set_scene) (camera_scene scene);
	int (*set_brightness) (camera_brightness brightness);
	int (*set_effect) (camera_effects effect);
	int (*isp_get_actual_iso) (void);
	int (*isp_get_exposure_time) (void);

	int (*isp_get_focus_distance) (void);
	void (*isp_set_fps_lock) (int);
	u32 (*isp_get_awb_gain)(int withShift);
	u32 (*isp_get_focus_code)(void);
	u32 (*isp_get_focus_rect)(camera_rect_s *rect);
	u32 (*isp_get_expo_line)(void);
	u32 (*isp_get_sensor_vts)(void);

	u32 (*isp_get_current_ccm_rgain)(void);
	u32 (*isp_get_current_ccm_bgain)(void);

} isp_tune_ops;

typedef enum {
	LED_FLASH = 0,
	XEON_FLASH,
} flash_type;

typedef enum {
	FLASH_MODE = 0,
	TORCH_MODE,
} work_mode;

typedef enum {
	CLK_400M = 0x0c,
	CLK_450M = 0x2c,
	CLK_500M = 0x0e,
	CLK_550M = 0x2e,
	CLK_600M = 0x10,
	CLK_650M = 0x30,
	CLK_700M = 0x12,
	CLK_750M = 0x32,
	CLK_800M = 0x14,
	CLK_850M = 0x34,
	CLK_900M = 0x54,
	CLK_950M = 0x74,
} mipi_clk;

typedef enum {
	LUM_LEVEL0 = 0,
	LUM_LEVEL1,
	LUM_LEVEL2,
	LUM_LEVEL3,
	LUM_LEVEL4,
	LUM_LEVEL5,
	LUM_LEVEL6,
	LUM_LEVEL7,
	LUM_LEVEL_MAX,
} flash_lum_level;

typedef enum {
	FLASH_100MA = 0x04,
	FLASH_200MA = 0x08,
	FLASH_300MA = 0x0b,
	FLASH_400MA = 0x10,
	FLASH_500MA = 0x14,
	FLASH_600MA = 0x18,
	FLASH_700MA = 0x1b,
	FLASH_800MA = 0x20,
	FLASH_MA_MAX = 0x20,
} flash_value;


typedef enum {
	TOUCH_100MA = 0x12,
	TOUCH_150MA = 0x1b,
	TOUCH_200MA = 0x24,
	TOUCH_250MA = 0x2d,
	TOUCH_300MA = 0x36,
	TOUCH_MA_MAX = 0x36,
} touch_value;

typedef enum {
	FLASH_ON = 0,
	FLASH_OFF,
} camera_flash_state;

typedef enum {
	FLASH_TESTING = 0,
	FLASH_DONE,
	FLASH_FROZEN,
} camera_flash_flow;

/* changed by y00231328. sensor gain and expo active fuction is almost like OV or Sony. */
typedef enum {
	SENSOR_OV = 0,
	SENSOR_SONY,
	SENSOR_SAMSUNG,
	SENSOR_LIKE_OV,	/* sensor gain effect next frame, expo effect next 2 frames. */
	SENSOR_LIKE_SONY,	/* sensor gain and expo effect next 2 frames. */
} camera_sensor_type;

typedef enum {
	SENSOR_GRBG = 0,
	SENSOR_RGGB,
	SENSOR_BGGR,
} camera_sensor_rgb_type;

typedef enum {
	OFFLINE_RUNNING = 0,
	OFFLINE_READY,
} offline_state_t;

typedef enum {
	FRAMESIZE_NOBINNING = 0,
	FRAMESIZE_BINNING,
	FRAMESIZE_BINNING_MAX,
} binning_t;

typedef enum {
	FLASH_PLATFORM_U9510 = 0,
	FLASH_PLATFORM_9510E,
	FLASH_PLATFORM_S10,
	FLASH_PLATFORM_U9508,
	FLASH_PLATFORM_MAX,
} flash_platform_t;

typedef struct _camera_flashlight {
	int (*init) (void);
	void (*exit) (void);
	int (*reset) (void);
	int (*turn_on) (work_mode mode, flash_lum_level lum);
	int (*test) (void);
	int (*turn_off) (void);

	flash_type type;
} camera_flashlight;

typedef struct _image_setting {
	u8 *lensc_param;
	u16 *ccm_param;
	u8 *awb_param;
} image_setting_t;

typedef struct _awb_gain {
	u16 b_gain;
	u16 gb_gain;
	u16 gr_gain;
	u16 r_gain;
} awb_gain_t;

typedef struct _ccm_gain {
	u16 b_gain;
	u16 g_gain;
	u16 r_gain;
} ccm_gain_t;

typedef enum {
	OVERRIDE_ISO_HIGH = 0,
	OVERRIDE_ISO_LOW,

	OVERRIDE_AUTO_FPS_GAIN_HIGH,
	OVERRIDE_AUTO_FPS_GAIN_LOW,

	OVERRIDE_FPS_MAX,
	OVERRIDE_FPS_MIN,
	OVERRIDE_CAP_FPS_MIN,

	OVERRIDE_FLASH_TRIGGER_GAIN,
	
	OVERRIDE_SHARPNESS_PREVIEW,
	OVERRIDE_SHARPNESS_CAPTURE,

	OVERRIDE_TYPE_MAX,
} camera_override_type_t;

typedef struct _camera_sensor {
	/* init and exit function */
	int (*init) (void);
	void (*exit) (void);

	/* shut down sensor */
	void (*shut_down) (void);

	/* reset camera */
	int (*reset) (camera_power_state power_state);

	/* set camera power */
	int (*power) (camera_power_state power);

	int (*check_sensor) (void);
	int (*init_reg) (void);
	int (*stream_on) (camera_state state);

	/* get camera clock */
	/* unsigned long (*get_camera_clock)(void); */

	/* set/get camera flash mode */
	int (*set_flash) (camera_flash flash);
	int (*get_flash) (void);

	/* set/get camera scene */
	int (*set_scene) (camera_scene scene);
	int (*get_scene) (void);

	/* set/get camera horizontal/vertical image flip */
	int (*set_hflip) (int);
	int (*get_hflip) (void);
	int (*set_vflip) (int);
	int (*get_vflip) (void);
	int (*update_flip) (u16 width, u16 height);
	u8 hflip;
	u8 vflip;
	u8 old_flip;

	int (*get_format) (struct v4l2_fmtdesc *fmt);

	/* enum/try/set the resolutions */
	int (*enum_framesizes) (struct v4l2_frmsizeenum *framesizes);
	int (*try_framesizes) (struct v4l2_frmsizeenum *framesizes);
	int (*set_framesizes) (camera_state state,
			       struct v4l2_frmsize_discrete *fs, int flag, camera_setting_view_type view_type);
	int (*get_framesizes) (camera_state state,
			       struct v4l2_frmsize_discrete *fs);

	/* enum/try/set/get frame intervals */
	int (*enum_frame_intervals) (struct v4l2_frmivalenum *fi);
	int (*try_frame_intervals) (struct v4l2_frmivalenum *fi);
	int (*set_frame_intervals) (struct v4l2_fract *f);
	int (*get_frame_intervals) (struct v4l2_fract *f);

	/* get capabilities of sensor */
	int (*get_capability) (u32 id, u32 *value);

	int skip_frames;	/* y36721 use it 2012-04-10 for SONY sensor. */

	/* interface_type : MIPI or DVP */
	data_interface_t interface_type;
	csi_lane_t mipi_lane_count;
	csi_index_t mipi_index;
	sensor_power_t power_conf;
	sensor_index_t sensor_index;
	struct i2c_t i2c_config;

	camera_sensor_type sensor_type;
	/* changed by y00231328. Differ from sensor type and bayer order */
	camera_sensor_rgb_type sensor_rgb_type;

	u32 aec_addr[3];	/*high and low byte, y36721 2012-04-12 add a new higher byte */
	u32 agc_addr[2];	/*high and low byte */

	/*in AP write AE mode, delay time(unit us) between report expo&gain and ISP download sensor settings.*/
	u32 ap_writeAE_delay;

	/*if 1, then isp is integrated in sensor */
	isp_location_t isp_location;

	isp_tune_ops *sensor_tune_ops;

	u32 (*sensor_gain_to_iso) (int gain);
	u32 (*sensor_iso_to_gain) (int iso);
	void (*get_ccm_pregain) (camera_state state, u32 frame_index, u8 *bgain, u8 *rgain);
	void(*get_flash_awb)(flash_platform_t type, awb_gain_t *flash_awb);

	/*set ISP gain and exposure to sensor */
	void (*set_gain) (u32 gain);
	u32 (*get_gain) (void);
	void (*set_exposure) (u32 exposure);
	u32 (*get_exposure) (void);

	/* changed by y00231328.some sensor such as S5K4E1, expo and gain should be set together in holdon mode */
	void (*set_exposure_gain) (u32 exposure, u32 gain);

	void (*set_vts) (u16 vts);
	u32 (*get_vts_reg_addr) (void);

	/* effect */
	void (*set_effect) (camera_effects effect);
	void (*set_awb) (camera_white_balance awb_mode);

	/* anti-banding */
	int (*set_anti_banding) (camera_anti_banding banding);

	/* update_framerate*/
	void (*update_framerate) (camera_frame_rate_mode mode);

	void (*awb_dynamic_ccm_gain) (u32 frame_index, u32 ae, awb_gain_t  *awb_gain, ccm_gain_t *ccm_gain);

	int (*get_sensor_aperture)(void);
	int (*get_equivalent_focus)(void);

	/*get sensor override parameters */
	u32 (*get_override_param)(camera_override_type_t type);

	u32 fmt[STATE_MAX];
	u32 preview_frmsize_index;
	u32 capture_frmsize_index;
	framesize_s *frmsize_list;

	/* following struct can decide a sensor's frame rate and some AF feature */
	/* frame configs */
	u32 pclk;

	/* all above parameter decide this fps */
	u32 fps_max;
	u32 fps_min;
	u32 fps;

	/* for AEC/AGC
	 * integrate time
	 * gain
	 */
	u32 max_int_lines;
	u32 min_int_lines;
	u32 real_int_lines;

	/*here gain is in unit of 1/16, it is same as OV8830 */
	u32 min_gain;
	u32 max_gain;
	u32 real_gain;

	/* af information */
	/* if false, following vcm info is invalid */
	u32 af_enable;
	vcm_info_s *vcm;

	/* some sensor related params */
	image_setting_t image_setting;

	/* red clip correcttion function for raw sensor switch*/
	bool rcc_enable;

	struct module *owner;
	camera_info_t info;
	u8 lane_clk;
} camera_sensor;

extern framesize_s camera_framesizes[CAMERA_RESOLUTION_MAX];
extern vcm_info_s vcm_ad5823;
extern vcm_info_s vcm_dw9714;
extern u32 sensor_override_params[];

/* get camera control data struct */
camera_sensor *get_camera_sensor_from_array(sensor_index_t sensor_index);
camera_sensor **get_camera_sensor(sensor_index_t sensor_index);
void set_camera_sensor(sensor_index_t sensor_index, camera_sensor *sensor);
int clean_camera_sensor(sensor_index_t sensor_index);

/* register a sensor to system */
int register_camera_sensor(sensor_index_t sensor_index, camera_sensor *sensor);

/* unregister a sensor to system */
int unregister_camera_sensor(sensor_index_t sensor_index, camera_sensor *sensor);

camera_flashlight *get_camera_flash(void);

int register_camera_flash(camera_flashlight *flash);

int unregister_camera_flash(camera_flashlight *flash);

/* dump all registered sensors */
void dump_camera_sensors(void);

/* get width and height value by resolution index */
int camera_get_size_by_resolution(camera_resolutions res, u32 *width,
				  u32 *height);

/* get resolution index by width and height: -1 means failed */
int camera_get_resolution_by_size(u32 width, u32 height);
camera_resolution_type camera_get_resolution_type(u32 width, u32 height);

/* get camera count */
int get_camera_count(void);

/* power core ldo */
int camera_power_core_ldo(camera_power_state power);
int camera_power_id_gpio(camera_power_state power);

int camera_get_i2c_speed(unsigned int chip_id, i2c_speed_t i2c_speed_idx);
int camera_timing_is_match(int type);
camera_sensor **get_camera_sensor_array(sensor_index_t sensor_index);
#endif /*CAMERA_SENSOR_H_INCLUDED */

/********************************* END ***********************************************/
