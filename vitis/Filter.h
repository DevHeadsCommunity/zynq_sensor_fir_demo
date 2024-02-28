#ifndef FILTER_H
#define FILTER_H

/*define filter type
 * FIR - finite impulse response
 * MA - moving average
 * IIR - infinite impulse response
 */
#define FIR

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef FIR
#define FIR_FILTER_LENGTH	16
#endif

#ifdef MA
#define FIR_FILTER_LENGTH	10
#endif

#ifdef IIR
#define SAMPLE_TIME_FILTER_MS	10
#define SAMPLE_TIME_LED_MS		500
#define SINUSOID_FREQUENCY_HZ	1.0f

#define IIRFILTER_ALPHA			1.0f
#define IIRFILTER_BETA			0.1f
#endif

#ifdef FIR
typedef struct {
	float buf[FIR_FILTER_LENGTH];
	uint8_t bufIndex;
	float out;

} FIRFilter;
#endif

typedef struct {
	float alpha;
	float beta;
	float output;

} IIRFilter;

#ifdef FIR
/*initialization function that resets*/
void FIRFilter_Init(FIRFilter *fir);

/*update function that returns the filtered output*/
float FIRFilter_Update(FIRFilter *fir, float inp);
#endif

#endif	/*FILTER_H*/
