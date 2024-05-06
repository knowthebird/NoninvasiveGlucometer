#include "GlucometerSensor.h"
// #include "RunningAverage.h"
// #include "KickFiltersRT.h"

// RunningAverage myRA(7);
// const float fs = 150;
// KickFiltersRT<float> filtersRT;

uint8_t GlucometerSensor::Initialize() { return 0; }

float GlucometerSensor::GetConcentration_mg_dl() { return 1.0; }
