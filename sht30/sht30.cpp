#include <stdio.h>
#include <string.h>
#include "esp_system.h"
#include "kidbright32.h"
#include "sht30.h"

SHT30::SHT30(int bus_ch, int dev_addr) {
	channel = bus_ch;
	address = dev_addr;
	polling_ms = SHT30_POLLING_MS;
}

void SHT30::init(void) {
	t = 0;
	h = 0;
	state = s_detect;
}

int SHT30::prop_count(void) {
	return 0;
}

bool SHT30::prop_name(int index, char *name) {
	// not supported
	return false;
}

bool SHT30::prop_unit(int index, char *unit) {
	// not supported
	return false;
}

bool SHT30::prop_attr(int index, char *attr) {
	// not supported
	return false;
}

bool SHT30::prop_read(int index, char *value) {
	// not supported
	return false;
}

bool SHT30::prop_write(int index, char *value) {
	// not supported
	return false;
}

void SHT30::process(Driver *drv) {
	I2CDev *i2c = (I2CDev *)drv;

	switch (state) {
		case s_detect:
			if (i2c->detect(channel, address) == ESP_OK) {
				if (i2c->write(channel, address, (uint8_t*)"\x27\x37", 2) == ESP_OK) {
					error = false;
					initialized = true;

					state = s_read;
				} else {
					state = s_error;
				}
			} else {
				state = s_error;
			}
			break;

		case s_read:
			if (is_tickcnt_elapsed(polling_tickcnt, polling_ms)) {
				uint8_t data[6];
				if (i2c->read(channel, address, (uint8_t*)"\xE0\x00", 2, data, 6) == ESP_OK) {
					t = -45.0 + 175.0 * ((float)(((uint16_t)data[0] << 8) | data[1]) / 0xFFFF);
					h = 100.0 * ((float)(((uint16_t)data[3] << 8) | data[4]) / 0xFFFF);

					polling_tickcnt = get_tickcnt();
					state = s_read;
				} else {
					state = s_error;
				}
			}
			break;

		case s_error:
			// set error flag
			error = true;
			// clear initialized flag
			initialized = false;
			// init temperature
			t = 0;
			h = 0;
			// get current tickcnt
			tickcnt = get_tickcnt();
			// goto wait and retry with detect state
			state = s_wait;
			break;

		case s_wait:
			// wait polling_ms timeout
			if (is_tickcnt_elapsed(tickcnt, polling_ms)) {
				state = s_detect;
			}
			break;
	}
}

float SHT30::read(uint8_t type) {
	return type == 0 ? t : h;
}
