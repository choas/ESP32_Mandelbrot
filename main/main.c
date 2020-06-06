/* Hello World Example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_spi_flash.h"

#include <time.h>
#include "tftspi.h"
#include "tft.h"



// ==========================================================
// Define which spi bus to use TFT_VSPI_HOST or TFT_HSPI_HOST
#define SPI_BUS TFT_HSPI_HOST
// ==========================================================


static int _demo_pass = 0;
static uint8_t doprint = 1;
// static uint8_t run_gs_demo = 0; // Run gray scale demo if set to 1

// static struct tm* tm_info;

// static time_t time_now, time_last = 0;


#define GDEMO_TIME 1000
#define GDEMO_INFO_TIME 5000


double xl = -2.0;
double xu = 0.5;
double yl = -1.1;
double yu = 1.1;

int reps = 40;
int width = 40;
int height = 25;


int calcMandel(int i, int j) {

    double xinc = (xu - xl) / width;
    double yinc = (yu - yl) / height;

    double nreal = xl + i * xinc;
    double nimg = yl + j * yinc;
    double rz = 0.0;
    double iz = 0.0;
    double r2z = 0.0;
    double i2z = 0.0;
    for (int k = 1; k <= reps; k++) {
        
        r2z = rz * rz - iz * iz;
        i2z = 2 * rz * iz;
        rz = r2z + nreal;
        iz = i2z + nimg;
        
        if ((rz * rz + iz * iz) > 4) {
            return k;
        }
    }
    return 0;   
}


// //-------------------------------------------------------------------
// static unsigned int rand_interval(unsigned int min, unsigned int max)
// {
//     int r;
//     const unsigned int range = 1 + max - min;
//     const unsigned int buckets = RAND_MAX / range;
//     const unsigned int limit = buckets * range;

//     /* Create equal size buckets all in a row, then fire randomly towards
//      * the buckets until you land in one of them. All buckets are equally
//      * likely. If you land off the end of the line of buckets, try again. */
//     do
//     {
//         r = rand();
//     } while (r >= limit);

//     return min + (r / buckets);
// }

// // Generate random color
// //-----------------------------
// static color_t random_color() {

// 	color_t color;
// 	color.r  = (uint8_t)rand_interval(8,252);
//     color.r = 10;
// 	color.g  = (uint8_t)rand_interval(8,252);
//     color.g = 10;
// 	color.b  = (uint8_t)rand_interval(8,252);
// 	return color;
// }




// //----------------------
// static void _checkTime()
// {
// 	time(&time_now);
// 	if (time_now > time_last) {
// 		color_t last_fg, last_bg;
// 		time_last = time_now;
// 		tm_info = localtime(&time_now);
// 		// sprintf(tmp_buff, "%02d:%02d:%02d", tm_info->tm_hour, tm_info->tm_min, tm_info->tm_sec);

// 		TFT_saveClipWin();
// 		TFT_resetclipwin();

// 		Font curr_font = cfont;
// 		last_bg = _bg;
// 		last_fg = _fg;
// 		_fg = TFT_YELLOW;
// 		_bg = (color_t){ 64, 64, 64 };
// 		TFT_setFont(DEFAULT_FONT, NULL);

// 		TFT_fillRect(1, _height-TFT_getfontheight()-8, _width-3, TFT_getfontheight()+6, _bg);
// 		// TFT_print(tmp_buff, CENTER, _height-TFT_getfontheight()-5);

// 		cfont = curr_font;
// 		_fg = last_fg;
// 		_bg = last_bg;

// 		TFT_restoreClipWin();
// 	}
// }

// //---------------------
// static int Wait(int ms)
// {
// 	uint8_t tm = 1;
// 	if (ms < 0) {
// 		tm = 0;
// 		ms *= -1;
// 	}
// 	if (ms <= 50) {
// 		vTaskDelay(ms / portTICK_RATE_MS);
// 		//if (_checkTouch()) return 0;
// 	}
// 	else {
// 		for (int n=0; n<ms; n += 50) {
// 			vTaskDelay(50 / portTICK_RATE_MS);
// 			if (tm) _checkTime();
// 			//if (_checkTouch()) return 0;
// 		}
// 	}
// 	return 1;
// }


//-----------------------
static void circle_demo()
{
	int x, y, r, n;

	// disp_header("CIRCLE DEMO");

	// uint32_t end_time = clock() + GDEMO_TIME;

#if IGNORE

	n = 0;
	while ((clock() < end_time) && (Wait(0))) {
		x = rand_interval(8, dispWin.x2-8);
		y = rand_interval(8, dispWin.y2-8);
		if (x < y) r = rand_interval(2, x/2);
		else r = rand_interval(2, y/2);
		TFT_drawCircle(x,y,r,random_color());
		n++;
	}
	// sprintf(tmp_buff, "%d CIRCLES", n);
	// update_header(NULL, tmp_buff);
	Wait(-GDEMO_INFO_TIME);

#endif

	// update_header("FILLED CIRCLE", "");
	// TFT_fillWindow(TFT_BLACK);
	// end_time = clock() + GDEMO_TIME;
	n = 0;
    x = y = 8;

    int px = 0;
    int py = 0;


	//while ((clock() < end_time) && (Wait(0))) {
    while(px < 27) {

        int c = calcMandel(py, px);

        color_t color;
        color.r = 10;
        color.g = 10;
        color.b = c * 6;

		// x = rand_interval(8, dispWin.x2-8);
		// y = rand_interval(8, dispWin.y2-8);
		// if (x < y) r = rand_interval(2, x/2);
		// else r = rand_interval(2, y/2);
        r = 3;
		TFT_fillCircle((px + 1) * 8 - 4 + 10, (py + 1) * 8 - 4,r, color);
        //random_color());

        py += 1;
        if (py > 40) {
            py = 0;
            px += 1;
        }
        // r = 4
		// TFT_drawCircle(x,y,r,random_color());
		n++;
	}
    printf("%d circles - %d:%d\n", n, dispWin.x2, dispWin.y2);
	// sprintf(tmp_buff, "%d CIRCLES", n);
	// update_header(NULL, tmp_buff);
	// Wait(-GDEMO_INFO_TIME);

    vTaskDelay(10 / portTICK_RATE_MS);
}


//===============
void tft_demo() {

	font_rotate = 0;
	text_wrap = 0;
	font_transparent = 0;
	font_forceFixed = 0;
	TFT_resetclipwin();

	image_debug = 0;

    char dtype[16];
    
    switch (tft_disp_type) {
        case DISP_TYPE_ILI9341:
            sprintf(dtype, "ILI9341");
            break;
        case DISP_TYPE_ILI9488:
            sprintf(dtype, "ILI9488");
            break;
        case DISP_TYPE_ST7789V:
            sprintf(dtype, "ST7789V");
            break;
        case DISP_TYPE_ST7735:
            sprintf(dtype, "ST7735");
            break;
        case DISP_TYPE_ST7735R:
            sprintf(dtype, "ST7735R");
            break;
        case DISP_TYPE_ST7735B:
            sprintf(dtype, "ST7735B");
            break;
        default:
            sprintf(dtype, "Unknown");
    }
    
    uint8_t disp_rot = PORTRAIT;
	_demo_pass = 0;
	gray_scale = 0;
	doprint = 1;

#if IGNORE
	TFT_setRotation(disp_rot);
	disp_header("ESP32 TFT DEMO");
	TFT_setFont(COMIC24_FONT, NULL);
	int tempy = TFT_getfontheight() + 4;
	_fg = TFT_ORANGE;
	TFT_print("ESP32", CENTER, (dispWin.y2-dispWin.y1)/2 - tempy);
	TFT_setFont(UBUNTU16_FONT, NULL);
	_fg = TFT_CYAN;
	TFT_print("TFT Demo", CENTER, LASTY+tempy);
	tempy = TFT_getfontheight() + 4;
	TFT_setFont(DEFAULT_FONT, NULL);
	_fg = TFT_GREEN;
	sprintf(tmp_buff, "Read speed: %5.2f MHz", (float)max_rdclock/1000000.0);
	TFT_print(tmp_buff, CENTER, LASTY+tempy);

	Wait(4000);
#endif


	while (1) {
		// if (run_gs_demo) {
		// 	if (_demo_pass == 8) doprint = 0;
		// 	// Change gray scale mode on every 2nd pass
		// 	gray_scale = _demo_pass & 1;
		// 	// change display rotation
		// 	if ((_demo_pass % 2) == 0) {
		// 		_bg = TFT_BLACK;
		// 		TFT_setRotation(disp_rot);
		// 		disp_rot++;
		// 		disp_rot &= 3;
		// 	}
		// }
		// else {
			if (_demo_pass == 4) doprint = 0;
			// change display rotation
#if IGNORE
			_bg = TFT_BLACK;
			TFT_setRotation(disp_rot);
#endif
			// disp_rot++;
			disp_rot &= 3;
		// }

#ifdef IGNORE

		if (doprint) {
			if (disp_rot == 1) sprintf(tmp_buff, "PORTRAIT");
			if (disp_rot == 2) sprintf(tmp_buff, "LANDSCAPE");
			if (disp_rot == 3) sprintf(tmp_buff, "PORTRAIT FLIP");
			if (disp_rot == 0) sprintf(tmp_buff, "LANDSCAPE FLIP");
			printf("\r\n==========================================\r\nDisplay: %s: %s %d,%d %s\r\n\r\n",
					dtype, tmp_buff, _width, _height, ((gray_scale) ? "Gray" : "Color"));
		}

		disp_header("Welcome to ESP32");

		test_times();
		font_demo();
		line_demo();
		aline_demo();
		rect_demo();
#endif

		circle_demo();
#ifdef IGNORE
		ellipse_demo();
		arc_demo();
		triangle_demo();
		poly_demo();
		pixel_demo();
		disp_images();
		touch_demo();
#endif
		_demo_pass++;
	}
}

//=============
void ttf_main()
{
    //test_sd_card();
    // ========  PREPARE DISPLAY INITIALIZATION  =========

    esp_err_t ret;

    // === SET GLOBAL VARIABLES ==========================

    // ===================================================
    // ==== Set display type                         =====
    tft_disp_type = DEFAULT_DISP_TYPE;
	//tft_disp_type = DISP_TYPE_ILI9341;
	//tft_disp_type = DISP_TYPE_ILI9488;
	//tft_disp_type = DISP_TYPE_ST7735B;
    // ===================================================

	// ===================================================
	// === Set display resolution if NOT using default ===
	// === DEFAULT_TFT_DISPLAY_WIDTH &                 ===
    // === DEFAULT_TFT_DISPLAY_HEIGHT                  ===
	_width = DEFAULT_TFT_DISPLAY_WIDTH;  // smaller dimension
	_height = DEFAULT_TFT_DISPLAY_HEIGHT; // larger dimension
	//_width = 128;  // smaller dimension
	//_height = 160; // larger dimension
	// ===================================================

	// ===================================================
	// ==== Set maximum spi clock for display read    ====
	//      operations, function 'find_rd_speed()'    ====
	//      can be used after display initialization  ====
	max_rdclock = 8000000;
	// ===================================================

    // ====================================================================
    // === Pins MUST be initialized before SPI interface initialization ===
    // ====================================================================
    TFT_PinsInit();

    // ====  CONFIGURE SPI DEVICES(s)  ====================================================================================

    spi_lobo_device_handle_t spi;
	
    spi_lobo_bus_config_t buscfg={
        .miso_io_num=PIN_NUM_MISO,				// set SPI MISO pin
        .mosi_io_num=PIN_NUM_MOSI,				// set SPI MOSI pin
        .sclk_io_num=PIN_NUM_CLK,				// set SPI CLK pin
        .quadwp_io_num=-1,
        .quadhd_io_num=-1,
		.max_transfer_sz = 6*1024,
    };
    spi_lobo_device_interface_config_t devcfg={
        .clock_speed_hz=8000000,                // Initial clock out at 8 MHz
        .mode=0,                                // SPI mode 0
        .spics_io_num=-1,                       // we will use external CS pin
		.spics_ext_io_num=PIN_NUM_CS,           // external CS pin
		.flags=LB_SPI_DEVICE_HALFDUPLEX,        // ALWAYS SET  to HALF DUPLEX MODE!! for display spi
    };

    // ====================================================================================================================


    vTaskDelay(500 / portTICK_RATE_MS);
	printf("\r\n==============================\r\n");
    printf("TFT display DEMO, LoBo 11/2017\r\n");
	printf("==============================\r\n");
    printf("Pins used: miso=%d, mosi=%d, sck=%d, cs=%d\r\n", PIN_NUM_MISO, PIN_NUM_MOSI, PIN_NUM_CLK, PIN_NUM_CS);
	printf("==============================\r\n\r\n");

	// ==================================================================
	// ==== Initialize the SPI bus and attach the LCD to the SPI bus ====

	ret=spi_lobo_bus_add_device(SPI_BUS, &buscfg, &devcfg, &spi);
    assert(ret==ESP_OK);
	printf("SPI: display device added to spi bus (%d)\r\n", SPI_BUS);
	disp_spi = spi;

	// ==== Test select/deselect ====
	ret = spi_lobo_device_select(spi, 1);
    assert(ret==ESP_OK);
	ret = spi_lobo_device_deselect(spi);
    assert(ret==ESP_OK);

	printf("SPI: attached display device, speed=%u\r\n", spi_lobo_get_speed(spi));
	printf("SPI: bus uses native pins: %s\r\n", spi_lobo_uses_native_pins(spi) ? "true" : "false");

	// ================================
	// ==== Initialize the Display ====

	printf("SPI: display init...\r\n");
	TFT_display_init();
    printf("OK\r\n");
	
	// ---- Detect maximum read speed ----
	max_rdclock = find_rd_speed();
	printf("SPI: Max rd speed = %u\r\n", max_rdclock);

    // ==== Set SPI clock used for display operations ====
	spi_lobo_set_speed(spi, DEFAULT_SPI_CLOCK);
	printf("SPI: Changed speed to %u\r\n", spi_lobo_get_speed(spi));

    printf("\r\n---------------------\r\n");
	printf("Graphics demo started\r\n");
	printf("---------------------\r\n");

	font_rotate = 0;
	text_wrap = 0;
	font_transparent = 0;
	font_forceFixed = 0;
	gray_scale = 0;
    TFT_setGammaCurve(DEFAULT_GAMMA_CURVE);
	TFT_setRotation(PORTRAIT);
	TFT_setFont(DEFAULT_FONT, NULL);
	TFT_resetclipwin();

#if IGNORE
	disp_header("File system INIT");
    _fg = TFT_CYAN;
	TFT_print("Initializing SPIFFS...", CENTER, CENTER);
    // ==== Initialize the file system ====
    printf("\r\n\n");
	vfs_spiffs_register();
    if (!spiffs_is_mounted) {
    	_fg = TFT_RED;
    	TFT_print("SPIFFS not mounted !", CENTER, LASTY+TFT_getfontheight()+2);
    }
    else {
    	_fg = TFT_GREEN;
    	TFT_print("SPIFFS Mounted.", CENTER, LASTY+TFT_getfontheight()+2);
    }
	Wait(-2000);
#endif

	//=========
    // Run demo
    //=========
	tft_demo();
}


void app_main()
{
    printf("Hello world!\n");

    /* Print chip information */
    esp_chip_info_t chip_info;
    esp_chip_info(&chip_info);
    printf("This is ESP32 chip with %d CPU cores, WiFi%s%s, ",
            chip_info.cores,
            (chip_info.features & CHIP_FEATURE_BT) ? "/BT" : "",
            (chip_info.features & CHIP_FEATURE_BLE) ? "/BLE" : "");

    printf("silicon revision %d, ", chip_info.revision);

    printf("%dMB %s flash\n", spi_flash_get_chip_size() / (1024 * 1024),
            (chip_info.features & CHIP_FEATURE_EMB_FLASH) ? "embedded" : "external");

    // for (int i = 10; i >= 0; i--) {
    //     printf("Restarting in %d seconds...\n", i);
    //     vTaskDelay(1000 / portTICK_PERIOD_MS);
    // }
    // printf("Restarting now.\n");
    // fflush(stdout);
    // esp_restart();

    ttf_main();
}
