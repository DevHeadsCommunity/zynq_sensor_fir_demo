
#include "Filter.h"

/*for FIR filter*/
#ifdef FIR
static float FIR_IMPULSE_RESPONSE[FIR_FILTER_LENGTH] = {0.0029964f,0.0047929f,0.0000000f,-0.0203316f,-0.0374544f,0.0000000f,0.1194024f,0.2660849f,0.3333333f,0.2660849f,0.1194024f,0.0000000f,-0.0374544f,-0.0203316f,0.0000000f,0.0047929f};
#endif

/*for moving average(MA) filter*/
#ifdef MA
static float FIR_IMPULSE_RESPONSE[FIR_FILTER_LENGTH] = {0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f};	//10 point. for 4 point, use 0.25f four times.
#endif

#ifdef FIR
void FIRFilter_Init(FIRFilter *fir) {

	/*clear filter buffer*/
	for(uint8_t n = 0; n < FIR_FILTER_LENGTH; n++) {
		fir->buf[n] = 0.0f;
	}

	/*reset buffer index*/
	fir->bufIndex = 0;

	/*clear filter output*/
	fir->out = 0.0f;
}

float FIRFilter_Update(FIRFilter *fir, float inp) {

	/*store latest sample in the buffer*/
	fir->buf[fir->bufIndex] = inp;

	/*increment buffer index and wrap around if necessary*/
	fir->bufIndex++;

	if(fir->bufIndex == FIR_FILTER_LENGTH) {
		fir->bufIndex = 0;
	}

	/*compute new output sample via convolution*/
	fir->out = 0.0f;

	uint8_t sumIndex = fir->bufIndex;

	for(uint8_t n = 0; n < FIR_FILTER_LENGTH; n++) {

		/*decrement index and wrap if necessary*/
		if(sumIndex > 0) {
			sumIndex --;
		} else {
			sumIndex = FIR_FILTER_LENGTH - 1;
		}

		/*multiply impulse response with shifted input sample and add to output*/
		fir->out += FIR_IMPULSE_RESPONSE[n] * fir->buf[sumIndex];
	}

	/*return filtered output*/
	return fir->out;
}
#endif

#ifdef IIR
void IIRFilter_Init(IIRFilter *filt, float alpha, float beta) {

	filt->alpha = alpha;
	filt->beta = beta;
	filt->output = 0.0f;

}

float IIRFilter_Update(IIRFilter *filt, float input) {

	/*y[n] = alpha * x[n] - beta * y[n-1]*/
	filt->output = filt->alpha * input - filt->beta * filt->output;

	return(filt->output);

}
#endif
