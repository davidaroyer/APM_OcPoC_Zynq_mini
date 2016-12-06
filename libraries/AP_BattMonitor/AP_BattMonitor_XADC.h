#pragma once

#include <AP_Common/AP_Common.h>
#include <AP_HAL/AP_HAL.h>
#include "AP_BattMonitor_Backend.h"
#include <stdio.h>

class AP_BattMonitor_XADC :public AP_BattMonitor_Backend
{
public:
    // constructor. This incorporates initialisation as well.
	AP_BattMonitor_XADC(AP_BattMonitor &mon, uint8_t instance, AP_BattMonitor::BattMonitor_State &mon_state):
        AP_BattMonitor_Backend(mon, instance, mon_state)
    {};

    virtual ~AP_BattMonitor_XADC(void) {};

    // initialise
    void init();

    // read the latest battery voltage
    void read();

private:
    FILE* xadc_fd;
    float xadc_coef;
};
