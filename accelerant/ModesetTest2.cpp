#include <stdio.h>

#include <map>
#include <vector>

#include <Application.h>
#include <Window.h>
#include <Message.h>
#include <Screen.h>

#include <LayoutBuilder.h>

#include <Button.h>
#include <MenuField.h>
#include <PopUpMenu.h>
#include <MenuItem.h>


static display_mode modes[] = {
	{
		.timing = {
			.pixel_clock  = 148500,
			.h_display    = 1920,
			.h_sync_start = 2008,
			.h_sync_end   = 2052,
			.h_total      = 2200,
			.v_display    = 1080,
			.v_sync_start = 1084,
			.v_sync_end   = 1089,
			.v_total      = 1125,
			.flags        = 0 | B_POSITIVE_HSYNC | B_POSITIVE_VSYNC,
		},
		.space = B_RGB32,
		.virtual_width = 1920,
		.virtual_height = 1080,
	},
	{
		.timing = {
			.pixel_clock  = 25170,
			.h_display    = 640,
			.h_sync_start = 656,
			.h_sync_end   = 752,
			.h_total      = 800,
			.v_display    = 480,
			.v_sync_start = 490,
			.v_sync_end   = 492,
			.v_total      = 525,
			.flags        = 0,
		},
		.space = B_RGB32,
		.virtual_width = 640,
		.virtual_height = 480,
	},
	{
		.timing = {
			.pixel_clock  = 27000,
			.h_display    = 720,
			.h_sync_start = 736,
			.h_sync_end   = 798,
			.h_total      = 858,
			.v_display    = 480,
			.v_sync_start = 489,
			.v_sync_end   = 495,
			.v_total      = 525,
			.flags        = 0,
		},
		.space = B_RGB32,
		.virtual_width = 720,
		.virtual_height = 480,
	},
	{
		.timing = {
			.pixel_clock  = 27000,
			.h_display    = 720,
			.h_sync_start = 736,
			.h_sync_end   = 798,
			.h_total      = 858,
			.v_display    = 480,
			.v_sync_start = 489,
			.v_sync_end   = 495,
			.v_total      = 525,
			.flags        = 0,
		},
		.space = B_RGB32,
		.virtual_width = 720,
		.virtual_height = 480,
	},
	{
		.timing = {
			.pixel_clock  = 74180,
			.h_display    = 1280,
			.h_sync_start = 1390,
			.h_sync_end   = 1430,
			.h_total      = 1650,
			.v_display    = 720,
			.v_sync_start = 725,
			.v_sync_end   = 730,
			.v_total      = 750,
			.flags        = 0 | B_POSITIVE_HSYNC | B_POSITIVE_VSYNC,
		},
		.space = B_RGB32,
		.virtual_width = 1280,
		.virtual_height = 720,
	},
	{
		.timing = {
			.pixel_clock  = 148350,
			.h_display    = 1920,
			.h_sync_start = 2008,
			.h_sync_end   = 2052,
			.h_total      = 2200,
			.v_display    = 1080,
			.v_sync_start = 1084,
			.v_sync_end   = 1089,
			.v_total      = 1125,
			.flags        = 0 | B_POSITIVE_HSYNC | B_POSITIVE_VSYNC,
		},
		.space = B_RGB32,
		.virtual_width = 1920,
		.virtual_height = 1080,
	},
	{
		.timing = {
			.pixel_clock  = 27000,
			.h_display    = 720,
			.h_sync_start = 732,
			.h_sync_end   = 796,
			.h_total      = 864,
			.v_display    = 576,
			.v_sync_start = 581,
			.v_sync_end   = 586,
			.v_total      = 625,
			.flags        = 0,
		},
		.space = B_RGB32,
		.virtual_width = 720,
		.virtual_height = 576,
	},
	{
		.timing = {
			.pixel_clock  = 27000,
			.h_display    = 720,
			.h_sync_start = 732,
			.h_sync_end   = 796,
			.h_total      = 864,
			.v_display    = 576,
			.v_sync_start = 581,
			.v_sync_end   = 586,
			.v_total      = 625,
			.flags        = 0,
		},
		.space = B_RGB32,
		.virtual_width = 720,
		.virtual_height = 576,
	},
	{
		.timing = {
			.pixel_clock  = 74250,
			.h_display    = 1280,
			.h_sync_start = 1720,
			.h_sync_end   = 1760,
			.h_total      = 1980,
			.v_display    = 720,
			.v_sync_start = 725,
			.v_sync_end   = 730,
			.v_total      = 750,
			.flags        = 0 | B_POSITIVE_HSYNC | B_POSITIVE_VSYNC,
		},
		.space = B_RGB32,
		.virtual_width = 1280,
		.virtual_height = 720,
	},
	{
		.timing = {
			.pixel_clock  = 54000,
			.h_display    = 1440,
			.h_sync_start = 1464,
			.h_sync_end   = 1592,
			.h_total      = 1728,
			.v_display    = 576,
			.v_sync_start = 581,
			.v_sync_end   = 586,
			.v_total      = 625,
			.flags        = 0 | B_POSITIVE_VSYNC,
		},
		.space = B_RGB32,
		.virtual_width = 1440,
		.virtual_height = 576,
	},
	{
		.timing = {
			.pixel_clock  = 148500,
			.h_display    = 1920,
			.h_sync_start = 2448,
			.h_sync_end   = 2492,
			.h_total      = 2640,
			.v_display    = 1080,
			.v_sync_start = 1084,
			.v_sync_end   = 1089,
			.v_total      = 1125,
			.flags        = 0 | B_POSITIVE_HSYNC | B_POSITIVE_VSYNC,
		},
		.space = B_RGB32,
		.virtual_width = 1920,
		.virtual_height = 1080,
	},
	{
		.timing = {
			.pixel_clock  = 148500,
			.h_display    = 1920,
			.h_sync_start = 2008,
			.h_sync_end   = 2052,
			.h_total      = 2200,
			.v_display    = 1080,
			.v_sync_start = 1084,
			.v_sync_end   = 1089,
			.v_total      = 1125,
			.flags        = 0 | B_POSITIVE_HSYNC | B_POSITIVE_VSYNC,
		},
		.space = B_RGB32,
		.virtual_width = 1920,
		.virtual_height = 1080,
	},
	{
		.timing = {
			.pixel_clock  = 27000,
			.h_display    = 720,
			.h_sync_start = 736,
			.h_sync_end   = 798,
			.h_total      = 858,
			.v_display    = 480,
			.v_sync_start = 489,
			.v_sync_end   = 495,
			.v_total      = 525,
			.flags        = 0,
		},
		.space = B_RGB32,
		.virtual_width = 720,
		.virtual_height = 480,
	},
	{
		.timing = {
			.pixel_clock  = 74250,
			.h_display    = 1280,
			.h_sync_start = 1390,
			.h_sync_end   = 1430,
			.h_total      = 1650,
			.v_display    = 720,
			.v_sync_start = 725,
			.v_sync_end   = 730,
			.v_total      = 750,
			.flags        = 0 | B_POSITIVE_HSYNC | B_POSITIVE_VSYNC,
		},
		.space = B_RGB32,
		.virtual_width = 1280,
		.virtual_height = 720,
	},
	{
		.timing = {
			.pixel_clock  = 27000,
			.h_display    = 720,
			.h_sync_start = 732,
			.h_sync_end   = 796,
			.h_total      = 864,
			.v_display    = 576,
			.v_sync_start = 581,
			.v_sync_end   = 586,
			.v_total      = 625,
			.flags        = 0,
		},
		.space = B_RGB32,
		.virtual_width = 720,
		.virtual_height = 576,
	},
	{
		.timing = {
			.pixel_clock  = 108000,
			.h_display    = 1152,
			.h_sync_start = 1216,
			.h_sync_end   = 1344,
			.h_total      = 1600,
			.v_display    = 864,
			.v_sync_start = 865,
			.v_sync_end   = 868,
			.v_total      = 900,
			.flags        = 0 | B_POSITIVE_HSYNC | B_POSITIVE_VSYNC,
		},
		.space = B_RGB32,
		.virtual_width = 1152,
		.virtual_height = 864,
	},
	{
		.timing = {
			.pixel_clock  = 108000,
			.h_display    = 1280,
			.h_sync_start = 1376,
			.h_sync_end   = 1488,
			.h_total      = 1800,
			.v_display    = 960,
			.v_sync_start = 961,
			.v_sync_end   = 964,
			.v_total      = 1000,
			.flags        = 0 | B_POSITIVE_HSYNC | B_POSITIVE_VSYNC,
		},
		.space = B_RGB32,
		.virtual_width = 1280,
		.virtual_height = 960,
	},
	{
		.timing = {
			.pixel_clock  = 108000,
			.h_display    = 1280,
			.h_sync_start = 1328,
			.h_sync_end   = 1440,
			.h_total      = 1688,
			.v_display    = 1024,
			.v_sync_start = 1025,
			.v_sync_end   = 1028,
			.v_total      = 1066,
			.flags        = 0 | B_POSITIVE_HSYNC | B_POSITIVE_VSYNC,
		},
		.space = B_RGB32,
		.virtual_width = 1280,
		.virtual_height = 1024,
	},
	{
		.timing = {
			.pixel_clock  = 106500,
			.h_display    = 1440,
			.h_sync_start = 1520,
			.h_sync_end   = 1672,
			.h_total      = 1904,
			.v_display    = 900,
			.v_sync_start = 903,
			.v_sync_end   = 909,
			.v_total      = 934,
			.flags        = 0 | B_POSITIVE_VSYNC,
		},
		.space = B_RGB32,
		.virtual_width = 1440,
		.virtual_height = 900,
	},
	{
		.timing = {
			.pixel_clock  = 146250,
			.h_display    = 1680,
			.h_sync_start = 1784,
			.h_sync_end   = 1960,
			.h_total      = 2240,
			.v_display    = 1050,
			.v_sync_start = 1053,
			.v_sync_end   = 1059,
			.v_total      = 1089,
			.flags        = 0 | B_POSITIVE_VSYNC,
		},
		.space = B_RGB32,
		.virtual_width = 1680,
		.virtual_height = 1050,
	},
	{
		.timing = {
			.pixel_clock  = 148500,
			.h_display    = 1920,
			.h_sync_start = 2008,
			.h_sync_end   = 2052,
			.h_total      = 2200,
			.v_display    = 1080,
			.v_sync_start = 1084,
			.v_sync_end   = 1089,
			.v_total      = 1125,
			.flags        = 0 | B_POSITIVE_HSYNC | B_POSITIVE_VSYNC,
		},
		.space = B_RGB32,
		.virtual_width = 1920,
		.virtual_height = 1080,
	},
	{
		.timing = {
			.pixel_clock  = 25175,
			.h_display    = 640,
			.h_sync_start = 656,
			.h_sync_end   = 752,
			.h_total      = 800,
			.v_display    = 480,
			.v_sync_start = 490,
			.v_sync_end   = 492,
			.v_total      = 525,
			.flags        = 0,
		},
		.space = B_RGB32,
		.virtual_width = 640,
		.virtual_height = 480,
	},
	{
		.timing = {
			.pixel_clock  = 31500,
			.h_display    = 640,
			.h_sync_start = 656,
			.h_sync_end   = 696,
			.h_total      = 832,
			.v_display    = 480,
			.v_sync_start = 481,
			.v_sync_end   = 484,
			.v_total      = 520,
			.flags        = 0,
		},
		.space = B_RGB32,
		.virtual_width = 640,
		.virtual_height = 480,
	},
	{
		.timing = {
			.pixel_clock  = 31500,
			.h_display    = 640,
			.h_sync_start = 656,
			.h_sync_end   = 720,
			.h_total      = 840,
			.v_display    = 480,
			.v_sync_start = 481,
			.v_sync_end   = 484,
			.v_total      = 500,
			.flags        = 0,
		},
		.space = B_RGB32,
		.virtual_width = 640,
		.virtual_height = 480,
	},
	{
		.timing = {
			.pixel_clock  = 36000,
			.h_display    = 800,
			.h_sync_start = 824,
			.h_sync_end   = 896,
			.h_total      = 1024,
			.v_display    = 600,
			.v_sync_start = 601,
			.v_sync_end   = 603,
			.v_total      = 625,
			.flags        = 0 | B_POSITIVE_HSYNC | B_POSITIVE_VSYNC,
		},
		.space = B_RGB32,
		.virtual_width = 800,
		.virtual_height = 600,
	},
	{
		.timing = {
			.pixel_clock  = 40000,
			.h_display    = 800,
			.h_sync_start = 840,
			.h_sync_end   = 968,
			.h_total      = 1056,
			.v_display    = 600,
			.v_sync_start = 601,
			.v_sync_end   = 605,
			.v_total      = 628,
			.flags        = 0 | B_POSITIVE_HSYNC | B_POSITIVE_VSYNC,
		},
		.space = B_RGB32,
		.virtual_width = 800,
		.virtual_height = 600,
	},
	{
		.timing = {
			.pixel_clock  = 50000,
			.h_display    = 800,
			.h_sync_start = 856,
			.h_sync_end   = 976,
			.h_total      = 1040,
			.v_display    = 600,
			.v_sync_start = 637,
			.v_sync_end   = 643,
			.v_total      = 666,
			.flags        = 0 | B_POSITIVE_HSYNC | B_POSITIVE_VSYNC,
		},
		.space = B_RGB32,
		.virtual_width = 800,
		.virtual_height = 600,
	},
	{
		.timing = {
			.pixel_clock  = 49500,
			.h_display    = 800,
			.h_sync_start = 816,
			.h_sync_end   = 896,
			.h_total      = 1056,
			.v_display    = 600,
			.v_sync_start = 601,
			.v_sync_end   = 604,
			.v_total      = 625,
			.flags        = 0 | B_POSITIVE_HSYNC | B_POSITIVE_VSYNC,
		},
		.space = B_RGB32,
		.virtual_width = 800,
		.virtual_height = 600,
	},
	{
		.timing = {
			.pixel_clock  = 65000,
			.h_display    = 1024,
			.h_sync_start = 1048,
			.h_sync_end   = 1184,
			.h_total      = 1344,
			.v_display    = 768,
			.v_sync_start = 771,
			.v_sync_end   = 777,
			.v_total      = 806,
			.flags        = 0,
		},
		.space = B_RGB32,
		.virtual_width = 1024,
		.virtual_height = 768,
	},
	{
		.timing = {
			.pixel_clock  = 75000,
			.h_display    = 1024,
			.h_sync_start = 1048,
			.h_sync_end   = 1184,
			.h_total      = 1328,
			.v_display    = 768,
			.v_sync_start = 771,
			.v_sync_end   = 777,
			.v_total      = 806,
			.flags        = 0,
		},
		.space = B_RGB32,
		.virtual_width = 1024,
		.virtual_height = 768,
	},
	{
		.timing = {
			.pixel_clock  = 78750,
			.h_display    = 1024,
			.h_sync_start = 1040,
			.h_sync_end   = 1136,
			.h_total      = 1312,
			.v_display    = 768,
			.v_sync_start = 769,
			.v_sync_end   = 772,
			.v_total      = 800,
			.flags        = 0 | B_POSITIVE_HSYNC | B_POSITIVE_VSYNC,
		},
		.space = B_RGB32,
		.virtual_width = 1024,
		.virtual_height = 768,
	},
	{
		.timing = {
			.pixel_clock  = 135000,
			.h_display    = 1280,
			.h_sync_start = 1296,
			.h_sync_end   = 1440,
			.h_total      = 1688,
			.v_display    = 1024,
			.v_sync_start = 1025,
			.v_sync_end   = 1028,
			.v_total      = 1066,
			.flags        = 0 | B_POSITIVE_HSYNC | B_POSITIVE_VSYNC,
		},
		.space = B_RGB32,
		.virtual_width = 1280,
		.virtual_height = 1024,
	},
	{
		.timing = {
			.pixel_clock  = 25175,
			.h_display    = 640,
			.h_sync_start = 656,
			.h_sync_end   = 752,
			.h_total      = 800,
			.v_display    = 480,
			.v_sync_start = 490,
			.v_sync_end   = 492,
			.v_total      = 525,
			.flags        = 0,
		},
		.space = B_RGB32,
		.virtual_width = 640,
		.virtual_height = 480,
	},
	{
		.timing = {
			.pixel_clock  = 31500,
			.h_display    = 640,
			.h_sync_start = 656,
			.h_sync_end   = 720,
			.h_total      = 840,
			.v_display    = 480,
			.v_sync_start = 481,
			.v_sync_end   = 484,
			.v_total      = 500,
			.flags        = 0,
		},
		.space = B_RGB32,
		.virtual_width = 640,
		.virtual_height = 480,
	},
	{
		.timing = {
			.pixel_clock  = 36000,
			.h_display    = 800,
			.h_sync_start = 824,
			.h_sync_end   = 896,
			.h_total      = 1024,
			.v_display    = 600,
			.v_sync_start = 601,
			.v_sync_end   = 603,
			.v_total      = 625,
			.flags        = 0 | B_POSITIVE_HSYNC | B_POSITIVE_VSYNC,
		},
		.space = B_RGB32,
		.virtual_width = 800,
		.virtual_height = 600,
	},
	{
		.timing = {
			.pixel_clock  = 40000,
			.h_display    = 800,
			.h_sync_start = 840,
			.h_sync_end   = 968,
			.h_total      = 1056,
			.v_display    = 600,
			.v_sync_start = 601,
			.v_sync_end   = 605,
			.v_total      = 628,
			.flags        = 0 | B_POSITIVE_HSYNC | B_POSITIVE_VSYNC,
		},
		.space = B_RGB32,
		.virtual_width = 800,
		.virtual_height = 600,
	},
	{
		.timing = {
			.pixel_clock  = 50000,
			.h_display    = 800,
			.h_sync_start = 856,
			.h_sync_end   = 976,
			.h_total      = 1040,
			.v_display    = 600,
			.v_sync_start = 637,
			.v_sync_end   = 643,
			.v_total      = 666,
			.flags        = 0 | B_POSITIVE_HSYNC | B_POSITIVE_VSYNC,
		},
		.space = B_RGB32,
		.virtual_width = 800,
		.virtual_height = 600,
	},
	{
		.timing = {
			.pixel_clock  = 49500,
			.h_display    = 800,
			.h_sync_start = 816,
			.h_sync_end   = 896,
			.h_total      = 1056,
			.v_display    = 600,
			.v_sync_start = 601,
			.v_sync_end   = 604,
			.v_total      = 625,
			.flags        = 0 | B_POSITIVE_HSYNC | B_POSITIVE_VSYNC,
		},
		.space = B_RGB32,
		.virtual_width = 800,
		.virtual_height = 600,
	},
	{
		.timing = {
			.pixel_clock  = 65000,
			.h_display    = 1024,
			.h_sync_start = 1048,
			.h_sync_end   = 1184,
			.h_total      = 1344,
			.v_display    = 768,
			.v_sync_start = 771,
			.v_sync_end   = 777,
			.v_total      = 806,
			.flags        = 0,
		},
		.space = B_RGB32,
		.virtual_width = 1024,
		.virtual_height = 768,
	},
	{
		.timing = {
			.pixel_clock  = 75000,
			.h_display    = 1024,
			.h_sync_start = 1048,
			.h_sync_end   = 1184,
			.h_total      = 1328,
			.v_display    = 768,
			.v_sync_start = 771,
			.v_sync_end   = 777,
			.v_total      = 806,
			.flags        = 0,
		},
		.space = B_RGB32,
		.virtual_width = 1024,
		.virtual_height = 768,
	},
	{
		.timing = {
			.pixel_clock  = 78750,
			.h_display    = 1024,
			.h_sync_start = 1040,
			.h_sync_end   = 1136,
			.h_total      = 1312,
			.v_display    = 768,
			.v_sync_start = 769,
			.v_sync_end   = 772,
			.v_total      = 800,
			.flags        = 0 | B_POSITIVE_HSYNC | B_POSITIVE_VSYNC,
		},
		.space = B_RGB32,
		.virtual_width = 1024,
		.virtual_height = 768,
	},
	{
		.timing = {
			.pixel_clock  = 108000,
			.h_display    = 1152,
			.h_sync_start = 1216,
			.h_sync_end   = 1344,
			.h_total      = 1600,
			.v_display    = 864,
			.v_sync_start = 865,
			.v_sync_end   = 868,
			.v_total      = 900,
			.flags        = 0 | B_POSITIVE_HSYNC | B_POSITIVE_VSYNC,
		},
		.space = B_RGB32,
		.virtual_width = 1152,
		.virtual_height = 864,
	},
	{
		.timing = {
			.pixel_clock  = 108000,
			.h_display    = 1280,
			.h_sync_start = 1376,
			.h_sync_end   = 1488,
			.h_total      = 1800,
			.v_display    = 960,
			.v_sync_start = 961,
			.v_sync_end   = 964,
			.v_total      = 1000,
			.flags        = 0 | B_POSITIVE_HSYNC | B_POSITIVE_VSYNC,
		},
		.space = B_RGB32,
		.virtual_width = 1280,
		.virtual_height = 960,
	},
	{
		.timing = {
			.pixel_clock  = 108000,
			.h_display    = 1280,
			.h_sync_start = 1328,
			.h_sync_end   = 1440,
			.h_total      = 1688,
			.v_display    = 1024,
			.v_sync_start = 1025,
			.v_sync_end   = 1028,
			.v_total      = 1066,
			.flags        = 0 | B_POSITIVE_HSYNC | B_POSITIVE_VSYNC,
		},
		.space = B_RGB32,
		.virtual_width = 1280,
		.virtual_height = 1024,
	},
	{
		.timing = {
			.pixel_clock  = 135000,
			.h_display    = 1280,
			.h_sync_start = 1296,
			.h_sync_end   = 1440,
			.h_total      = 1688,
			.v_display    = 1024,
			.v_sync_start = 1025,
			.v_sync_end   = 1028,
			.v_total      = 1066,
			.flags        = 0 | B_POSITIVE_HSYNC | B_POSITIVE_VSYNC,
		},
		.space = B_RGB32,
		.virtual_width = 1280,
		.virtual_height = 1024,
	},
}
;


class ModesetWindow final: public BWindow {
private:
	struct ModeResolutionKey;
	struct ModeRefreshRateKey;

	enum {
		resolutionMenuMsg = 1,
		refreshRateMenuMsg,
		colorSpaceMenuMsg,
		applyMsg,
	};

	struct {
		BMenuField *resolution;
		BMenuField *refreshRate;
		BMenuField *colorSpace;
		BButton *apply;
	} fForm {};

	static uint32 GetRefreshRate(const display_timing &timing);
	static void GetResolutionName(BString &name, const display_timing &timing);
	static void GetRefreshRateName(BString &name, const display_timing &timing);
	static void GetColorSpaceName(BString &name, color_space colorSpace);
	void BuildModeMenus(const display_mode *modes, int32 modeCount);

	void SelectVideoMode(const display_mode &mode);

	void ResolutionSelected(BMessage *msg);
	void ApplyPressed(BMessage *msg);

public:
	ModesetWindow();

	void MessageReceived(BMessage *msg) final;
};


uint32 ModesetWindow::GetRefreshRate(const display_timing &timing)
{
	const bool interlaced = B_TIMING_INTERLACED & timing.flags;
	const uint64 multiplier = interlaced ? 2000000LL : 1000000LL;
	return (multiplier * timing.pixel_clock) / ((uint64)timing.h_total * (uint64)timing.v_total);
}

void ModesetWindow::GetResolutionName(BString &name, const display_timing &timing)
{
	name.SetToFormat("%" B_PRIu16 "x%" B_PRIu16, timing.h_display, timing.v_display);
}

void ModesetWindow::GetRefreshRateName(BString &name, const display_timing &timing)
{
	uint32 refreshRate = GetRefreshRate(timing);
	name.SetToFormat("%" B_PRIu32 ".%03" B_PRIu32 " Hz%s", refreshRate / 1000, refreshRate % 1000, (B_TIMING_INTERLACED & timing.flags) != 0 ? " (interlaced)" : "");
}

void ModesetWindow::GetColorSpaceName(BString &name, color_space colorSpace)
{
	switch (colorSpace) {
		case B_GRAY1:
			name = "GRAY1";
			break;
		case B_GRAY8:
			name = "GRAY8";
			break;
		case B_CMAP8:
			name = "CMAP8";
			break;
		case B_RGB15:
			name = "RGB15";
			break;
		case B_RGB16:
			name = "RGB16";
			break;
		case B_RGB32:
			name = "RGB32";
			break;
		case B_RGB48:
			name = "RGB48";
			break;
		default:
			name = "unknown";
	}
}

struct ModesetWindow::ModeResolutionKey {
	const display_timing &timing;

	bool operator<(const ModeResolutionKey &other) const {
		if (timing.h_display != other.timing.h_display) {
			return timing.h_display < other.timing.h_display;
		}
		return timing.v_display < other.timing.v_display;
	}
};

struct ModesetWindow::ModeRefreshRateKey {
	const display_timing &timing;

	bool operator<(const ModeRefreshRateKey &other) const {
		uint32 refreshRate = ModesetWindow::GetRefreshRate(timing);
		uint32 otherRefreshRate = ModesetWindow::GetRefreshRate(other.timing);
		if (refreshRate != otherRefreshRate) {
			return refreshRate < otherRefreshRate;
		}
		bool interlaced = B_TIMING_INTERLACED & timing.flags;
		bool otherInterlaced = B_TIMING_INTERLACED & other.timing.flags;
		return interlaced < otherInterlaced;
	}
};

void ModesetWindow::BuildModeMenus(const display_mode *modes, int32 modeCount)
{
	// (width, height) -> (refreshRate, interlaced) -> {mode}
	// refreshRates -> modes

	std::map<
		ModeResolutionKey,
		std::map<
			ModeRefreshRateKey,
			std::vector<const display_mode*>
		>
	> groupedModes;

	for (int32 i = 0; i < modeCount; i++) {
		const display_mode &mode = modes[i];

		ModeResolutionKey resolutionKey {mode.timing};
		ModeRefreshRateKey refreshRateKey {mode.timing};

		auto[it1, inserted1] = groupedModes.insert({resolutionKey, {}});
		auto[it2, inserted2] = it1->second.insert({refreshRateKey, {}});
		it2->second.push_back(&mode);
	}

	for (const auto &pair1: groupedModes) {
		BString name;
		GetResolutionName(name, pair1.first.timing);
		BMessage *resolutionItemMsg = new BMessage(resolutionMenuMsg);
		BMenuItem *resolutionItem = new BMenuItem(name.String(), resolutionItemMsg);
		fForm.resolution->Menu()->AddItem(resolutionItem);
		for (const auto &pair2: pair1.second) {
			BMessage modesMsg;
			for (const auto mode: pair2.second) {
				modesMsg.AddData("modes", B_RAW_TYPE, &mode->timing, sizeof(display_timing));
			}
			resolutionItemMsg->AddMessage("refreshRates", &modesMsg);
		}
	}
}


void ModesetWindow::SelectVideoMode(const display_mode &mode)
{

}


void ModesetWindow::ResolutionSelected(BMessage *msg)
{
	fForm.refreshRate->Menu()->RemoveItems(0, fForm.refreshRate->Menu()->CountItems(), true);
	int32 refreshRateCount;
	msg->GetInfo("refreshRates", NULL, &refreshRateCount);
	for (int32 i = 0; ; i++) {
		BMessage modesMsg;
		if (msg->FindMessage("refreshRates", i, &modesMsg) < B_OK) {
			break;
		}
		const display_timing *timing {};
		modesMsg.FindData("modes", B_RAW_TYPE, 0, (const void**)&timing, NULL);

		BString name;
		GetRefreshRateName(name, *timing);
		BMessage *refreshRateMsg = new BMessage(refreshRateMenuMsg);
		refreshRateMsg->AddData("mode", B_RAW_TYPE, timing, sizeof(display_timing));
		BMenuItem *item = new BMenuItem(name.String(), refreshRateMsg);
		if (i == 0) {
			item->SetMarked(true);
		}
		fForm.refreshRate->Menu()->AddItem(item);
	}
}

void ModesetWindow::ApplyPressed(BMessage *msg)
{
	BMenuItem *refreshRateMenuItem = fForm.refreshRate->Menu()->FindMarked();
	BMenuItem *colorSpaceMenuItem = fForm.colorSpace->Menu()->FindMarked();
	if (refreshRateMenuItem == nullptr || colorSpaceMenuItem == nullptr) {
		return;
	}
	refreshRateMenuItem->Message()->PrintToStream();
	colorSpaceMenuItem->Message()->PrintToStream();
}


ModesetWindow::ModesetWindow():
	BWindow(BRect(), "Modeset", B_TITLED_WINDOW, B_ASYNCHRONOUS_CONTROLS | B_QUIT_ON_WINDOW_CLOSE | B_AUTO_UPDATE_SIZE_LIMITS)
{
	fForm.resolution = new BMenuField("resolution", "Resolution", new BPopUpMenu("resolution"));
	fForm.refreshRate = new BMenuField("refreshRate", "Refresh Rate", new BPopUpMenu("refreshRate"));
	fForm.colorSpace = new BMenuField("colorSpace", "Colors", new BPopUpMenu("colorSpace"));

	fForm.apply = new BButton("apply", "Apply", new BMessage(applyMsg));

	BuildModeMenus(modes, B_COUNT_OF(modes));

	color_space colorSpaces[] = {
		B_GRAY1,
		B_GRAY8,
		B_CMAP8,
		B_RGB15,
		B_RGB16,
		B_RGB32,
		B_RGB48,
	};
	for (color_space colorSpace: colorSpaces) {
		BMessage *message = new BMessage(colorSpaceMenuMsg);
		message->AddUInt32("colorSpace", (uint32)colorSpace);
		BString name;
		GetColorSpaceName(name, colorSpace);
		fForm.colorSpace->Menu()->AddItem(new BMenuItem(name.String(), message));
	}

	BLayoutBuilder::Group<>(this, B_VERTICAL, B_USE_SMALL_SPACING)
		.SetInsets(B_USE_SMALL_SPACING)
		.Add(fForm.resolution)
		.Add(fForm.refreshRate)
		.Add(fForm.colorSpace)
		.Add(fForm.apply)
	.End();
}

void ModesetWindow::MessageReceived(BMessage *msg)
{
	switch (msg->what) {
		case resolutionMenuMsg: {
			printf("resolutionMenuMsg\n");
			msg->PrintToStream();
			ResolutionSelected(msg);
			break;
		}
		case refreshRateMenuMsg: {
			printf("refreshRateMenuMsg\n");
			msg->PrintToStream();
			break;
		}
		case applyMsg: {
			printf("applyMsg\n");
			ApplyPressed(msg);
			break;
		}
	}
	BWindow::MessageReceived(msg);
}


int main()
{
	BApplication app("application/x-vnd.Test.ModesetTest2");
	ModesetWindow *wnd = new ModesetWindow();
	wnd->CenterOnScreen();
	wnd->Show();
	app.Run();
	return 0;
}
