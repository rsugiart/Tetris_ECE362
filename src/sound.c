#include "stm32f0xx.h"
#include <math.h>   
#include <stdint.h>
#include <stdio.h>
#include "sound.h"

void nano_wait(int);
void autotest();

//=============================================================================
// Part 1: 7-segment display update with DMA
//=============================================================================

// 16-bits per digit.
// The most significant 8 bits are the digit number.
// The least significant 8 bits are the segments to illuminate.
uint16_t msg[8] = { 0x0000,0x0100,0x0200,0x0300,0x0400,0x0500,0x0600,0x0700 };
uint16_t score = 0; //score held 
extern const char font[];
// Print an 8-character string on the 8 digits
void print(const char str[]);
// Print a floating-point value.
void printfloat(float f);


//============================================================================
// enable_ports()
//============================================================================
void enable_ports(void) {
    RCC->AHBENR |= RCC_AHBENR_GPIOBEN; //clock port b
    RCC->AHBENR |= RCC_AHBENR_GPIOCEN; //clock port c
    
    GPIOB->MODER |= 0x00155555; // port b pins 0-10 output CHANGE
    
    GPIOC->MODER |= 0x00005500; // port c pins 4-7 output
    GPIOC->OTYPER |= 0x000000f0; // port c pins 4-7 open drain output
    GPIOC->MODER &= ~0x000000ff; // port c pins 0-3 input
    GPIOC->PUPDR |= 0x00000055; // port c pins 0-3 resistors pulled up
}

//============================================================================
// setup_dma() + enable_dma()
//============================================================================
void setup_dma(void) {
    RCC->AHBENR |= RCC_AHBENR_DMA1EN; //clock dma
    //loading information for 7-segment display
    DMA1_Channel5->CCR &= ~DMA_CCR_EN; //enable bit off

    DMA1_Channel5->CMAR = (uint32_t)msg; //cmar to address of msg array
    DMA1_Channel5->CPAR = (uint32_t)&GPIOB->ODR; //cpar to address of GPIOB_ODR
    DMA1_Channel5->CNDTR = 8;

    DMA1_Channel5->CCR |= DMA_CCR_DIR; //memory to peripheral
    DMA1_Channel5->CCR |= DMA_CCR_MINC; //increment mode
    DMA1_Channel5->CCR |= DMA_CCR_MSIZE_0; //memory size 16 bit
    DMA1_Channel5->CCR |= DMA_CCR_PSIZE_0; //peripheral size 16 bit
    DMA1_Channel5->CCR |= DMA_CCR_CIRC; //circular mode

    //loading information for score
    DMA1_Channel4->CCR &= ~DMA_CCR_EN; //enable bit off

    DMA1_Channel4->CMAR = (uint32_t)score; //cmar to address of msg array
    DMA1_Channel4->CPAR = (uint32_t)&GPIOB->ODR; //cpar to address of GPIOB_ODR
    DMA1_Channel4->CNDTR = 1; 

    DMA1_Channel4->CCR |= DMA_CCR_DIR; //memory to peripheral
    DMA1_Channel4->CCR |= DMA_CCR_MINC; //increment mode
    DMA1_Channel4->CCR |= DMA_CCR_MSIZE_0; //memory size 16 bit
    DMA1_Channel4->CCR |= DMA_CCR_PSIZE_0; //peripheral size 16 bit
    DMA1_Channel4->CCR |= DMA_CCR_CIRC; //circular mode
}


void enable_dma(void) {
    DMA1_Channel5->CCR |= DMA_CCR_EN; //enable
    DMA1_Channel4->CCR |= DMA_CCR_EN; //enable
}

//============================================================================
// init_tim1() //for score-keeping
//============================================================================
void init_tim1(void) {
    RCC->APB2ENR |= RCC_APB2ENR_TIM1EN; 

    TIM1->PSC = 4799;
    TIM1->ARR = 9;
    TIM1->DIER |= TIM_DIER_UDE; //enable dma

    TIM1->CR1 |= TIM_CR1_CEN; //enable timer
}

//============================================================================
// init_tim15() //for scoreboard
//============================================================================
void init_tim15(void) {
    RCC->APB2ENR |= RCC_APB2ENR_TIM15EN; 

    TIM15->PSC = 4799;
    TIM15->ARR = 9;
    TIM15->DIER |= TIM_DIER_UDE; //enable dma

    TIM15->CR1 |= TIM_CR1_CEN; //enable timer
}

//=============================================================================
// Analog-to-digital conversion for a volume level.
//=============================================================================
uint32_t volume = 2048;

//============================================================================
// setup_adc()
//============================================================================
void setup_adc(void) {
    RCC->AHBENR |= RCC_AHBENR_GPIOAEN; //clock port a
    GPIOA->MODER |= GPIO_MODER_MODER1; //pa1 to analog mode

    RCC->APB2ENR |= RCC_APB2ENR_ADC1EN; //clock adc peripheral
    RCC->CR2 |= RCC_CR2_HSI14ON; //high-speed internal 14 MHz

    while(!(RCC_CR2_HSI14RDY)); //wait for 14MHz clock
    ADC1->CR |= ADC_CR_ADEN;

    while(!(ADC_ISR_ADRDY)); //wait for adc
    ADC1->CHSELR = ADC_CHSELR_CHSEL1; //channel 1

    while(!(ADC_ISR_ADRDY)); //wait for adc again
}

//============================================================================
// Varables for boxcar averaging.
//============================================================================
#define BCSIZE 32
int bcsum = 0;
int boxcar[BCSIZE];
int bcn = 0;

//============================================================================
// Timer 2 ISR
//============================================================================
// Write the Timer 2 ISR here.  Be sure to give it the right name.
void TIM2_IRQHandler(){
    TIM2->SR &= ~TIM_SR_UIF;
    ADC1->CR |= ADC_CR_ADSTART;
    while(!(ADC1->ISR & ADC_ISR_EOC));

    bcsum -= boxcar[bcn];
    bcsum += boxcar[bcn] = ADC1->DR;
    bcn += 1;
    if (bcn >= BCSIZE) {
        bcn = 0;
    }
    volume = bcsum / BCSIZE;
}


//============================================================================
// init_tim2()
//============================================================================
void init_tim2(void) {
    RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
    
    TIM2->PSC = 4800-1;
    TIM2->ARR = 1000-1;
    TIM2->DIER |= TIM_DIER_UIE;
    TIM2->CR1 |= TIM_CR1_CEN;

    // NVIC->ISER[0] = 1 << TIM2_IRQn;
    NVIC_EnableIRQ(TIM2_IRQn);
    NVIC_SetPriority(TIM2_IRQn, 3);
}

//=============================================================================
// Part 2: Debounced keypad scanning.
//=============================================================================

uint8_t col; // the column being scanned

void drive_column(int);   // energize one of the column outputs
int  read_rows();         // read the four row inputs
void update_history(int col, int rows); // record the buttons of the driven column
char get_key_event(void); // wait for a button event (press or release)
char get_keypress(void);  // wait for only a button press event.
float getfloat(void);     // read a floating-point number from keypad
void show_keys(void);     // demonstrate get_key_event()

//===========================================================================
// Part 4: Create an analog sine wave of a specified frequency
//===========================================================================
void dialer(void);

// Parameters for the wavetable size and expected synthesis rate.
#define N 1000
#define RATE 20000
short int wavetable[N];
int step0 = 0;
int offset0 = 0;
int step1 = 0;
int offset1 = 0;

//===========================================================================
// init_wavetable()
// Write the pattern for a complete cycle of a sine wave into the
// wavetable[] array.
//===========================================================================
void init_wavetable(void) {
    for(int i=0; i < N; i++)
        wavetable[i] = 32767 * sin(2 * M_PI * i / N);
}

//============================================================================
// set_freq()
//============================================================================
void set_freq(int chan, float f) {
    if (chan == 0) {
        if (f == 0.0) {
            step0 = 0;
            offset0 = 0;
        } else
            step0 = (f * N / RATE) * (1<<16);
    }
    if (chan == 1) {
        if (f == 0.0) {
            step1 = 0;
            offset1 = 0;
        } else
            step1 = (f * N / RATE) * (1<<16);
    }
}

//============================================================================
// setup_dac()
//============================================================================
void setup_dac(void) {
    RCC->AHBENR |= RCC_AHBENR_GPIOAEN; //clock port a
    RCC->APB1ENR |= RCC_APB1ENR_DACEN; //clock DAC peripheral
    GPIOA->MODER |= GPIO_MODER_MODER4; //pa4 analog mode

    DAC1->CR &= ~DAC_CR_TSEL1;
    DAC1->CR |= DAC_CR_TEN1; //enable DAC trigger channel 1
    DAC1->CR |= DAC_CR_EN1; //enable DAC
}

//============================================================================
// Timer 6 ISR
//============================================================================
// Write the Timer 6 ISR here.  Be sure to give it the right name.
void TIM6_DAC_IRQHandler(){
    TIM6->SR &= ~TIM_SR_UIF;

    offset0 += step0;
    offset1 += step1;
    if(offset0 >= (N >> 16)) {
        offset0 -= (N >> 16);
    }
    if(offset1 >= (N >> 16)) {
        offset1 -= (N >> 16);
    }
    int samp = wavetable[offset0 >> 16] + wavetable[offset1 >> 16];
    samp *= volume;
    samp = (samp >> 17);
    samp += 2048;
    DAC->DHR12R1 = samp;
}


//============================================================================
// init_tim6()
//============================================================================
void init_tim6(void) {
    RCC->APB1ENR |= RCC_APB1ENR_TIM6EN;
    
    TIM6->PSC = 47;
    TIM6->ARR = (1000000 / RATE) - 1;
    TIM6->DIER |= TIM_DIER_UIE;
    TIM6->CR1 |= TIM_CR1_CEN;
    TIM6->CR2 |= TIM_CR2_MMS_1;

    NVIC_EnableIRQ(TIM6_DAC_IRQn);
}

//============================================================================
// All the things you need to test your subroutines.
//============================================================================
int main(void) {
    internal_clock();
    // Initialize the display to something interesting to get started.
    msg[0] |= font['T'];
    msg[1] |= font['E'];
    msg[2] |= font['T'];
    msg[3] |= font['R'];
    msg[4] |= font['I'];
    msg[5] |= font['S'];
    msg[6] |= font[' '];
    msg[7] |= font['2'];

    enable_ports();
    setup_dma();
    enable_dma();
    init_tim15();
    init_tim1();

    //init_tim7();

    setup_adc();
    init_tim2();

    //showing voltage for adc
    // for(;;) {
    //     printfloat(2.95 * volume / 4096);
    // }

    //dac
    init_wavetable();
    setup_dac();
    init_tim6();

    float f = 261.626; // 261.626 Hz tone

    //sound for when score levels up
    for(;;) {
        if (score % 100) { //level up each 100
            set_freq(0, f); //set frequency
            nano_wait(1000000);
            set_freq(0, 0); //turn off sound
        }
    }

    score = 50;
    //updating scoreboard
    for (;;) {
        printfloat(score);
    }

    dialer();
}