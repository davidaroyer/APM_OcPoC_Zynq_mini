#include <AP_HAL/AP_HAL.h>

#if CONFIG_HAL_BOARD == HAL_BOARD_LINUX && \
    CONFIG_HAL_BOARD_SUBTYPE == HAL_BOARD_SUBTYPE_LINUX_OCPOC_ZYNQ

#include "AP_BattMonitor_XADC.h"

extern const AP_HAL::HAL &hal;

void AP_BattMonitor_XADC::init(void)
{
	xadc_coef = 1 / 4096.0f * (1 + 10000/560.0f);
}

void AP_BattMonitor_XADC::read(void)
{
	float vbat;
	uint32_t buff[1];

	xadc_fd = fopen("/sys/bus/iio/devices/iio:device1/in_voltage8_raw", "r");
	if (xadc_fd != NULL) {
		fscanf(xadc_fd, "%d", buff);
		fclose(xadc_fd);
		vbat = buff[0] * xadc_coef + 0.5;
		_state.voltage = vbat;
		_state.last_time_micros = AP_HAL::micros();;
		_state.healthy = true;
	} else {
		_state.healthy = false;
	}
}

#endif
