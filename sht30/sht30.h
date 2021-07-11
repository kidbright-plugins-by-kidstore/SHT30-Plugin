#ifndef __SHT30_H__
#define __SHT30_H__

#include "driver.h"
#include "device.h"
#include "i2c-dev.h"

#define SHT30_POLLING_MS 200

class SHT30 : public Device {
	private:
		enum {
			 s_detect, s_read, s_error, s_wait
		} state;
		TickType_t tickcnt, polling_tickcnt;

		float t = 0, h = 0;

	public:
		// constructor
		SHT30(int bus_ch, int dev_addr);

		// override
		void init(void);
		void process(Driver *drv);
		int prop_count(void);
		bool prop_name(int index, char *name);
		bool prop_unit(int index, char *unit);
		bool prop_attr(int index, char *attr);
		bool prop_read(int index, char *value);
		bool prop_write(int index, char *value);

		// method
		float read(uint8_t type);
};

#endif
