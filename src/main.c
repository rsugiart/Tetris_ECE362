/**
  ******************************************************************************
  * @file    main.c
  * @author  Weili An, Niraj Menon
  * @date    Feb 7, 2024
  * @brief   ECE 362 Lab 7 student template
  ******************************************************************************
*/

/*******************************************************************************/

// Fill out your username!  Even though we're not using an autotest, 
// it should be a habit to fill out your username in this field now.
const char* username = "jiang857";

/*******************************************************************************/ 

#include "stm32f0xx.h"
#include <stdint.h>

void internal_clock();

// Uncomment only one of the following to test each step
//#define STEP1
//#define STEP2
//#define STEP3
#define STEP4

void init_usart5() {
    // TODO
    RCC->AHBENR |= RCC_AHBENR_GPIOCEN; //gpioc clock
    RCC->AHBENR |= RCC_AHBENR_GPIODEN; //gpiod clock
    GPIOC->MODER |= GPIO_MODER_MODER12_1; 
    GPIOD->MODER |= GPIO_MODER_MODER2_1;
    GPIOC->AFR[1] |= 0x2 << 4 * (12 - 8);
    GPIOD->AFR[0] |= 0x2 << 4 * (2);
    RCC->APB1ENR |= RCC_APB1ENR_USART5EN; //usart5 clock

    USART5->CR1 &= ~USART_CR1_UE; //disable ue bit
    USART5->CR1 &= ~(USART_CR1_M0 | USART_CR1_M1); //word size 8 bits
    USART5->CR2 &= ~USART_CR2_STOP; //1 stop bit
    USART5->CR1 &= ~USART_CR1_PCE; //no parity control
    USART5->CR1 &= ~USART_CR1_OVER8; //16x oversampling
    USART5->BRR =  48000000/115200; //baude rate
    USART5->CR1 |= USART_CR1_TE | USART_CR1_RE; //transitter an receiver

    USART5->CR1 |= USART_CR1_UE; //enable usart ue = 1

    while (!(USART5->ISR & USART_ISR_TEACK) || !(USART5->ISR & USART_ISR_REACK)) {
        // Wait for TEACK and REACK bits to be set
    }

}

#ifdef STEP1
int main(void){
    internal_clock();
    init_usart5();
    for(;;) {
        while (!(USART5->ISR & USART_ISR_RXNE)) { }
        char c = USART5->RDR;
        while(!(USART5->ISR & USART_ISR_TXE)) { }
        USART5->TDR = c;
    }
}
#endif

#ifdef STEP2
#include <stdio.h>

// TODO Resolve the echo and carriage-return problem

int __io_putchar(int c) {
    // TODO
    if (c == '\n') {
        while(!(USART5->ISR & USART_ISR_TXE));
        USART5->TDR = '\r';
    }

    while(!(USART5->ISR & USART_ISR_TXE));
    USART5->TDR = c;
    return c;
}

int __io_getchar(void) {
    while (!(USART5->ISR & USART_ISR_RXNE));
    char c = USART5->RDR;
    // TODO
    if (c == '\r') {
        c = '\n';
    } 
    __io_putchar(c);
    return c;
}

int main() {
    internal_clock();
    init_usart5();
    setbuf(stdin,0);
    setbuf(stdout,0);
    setbuf(stderr,0);
    printf("Enter your name: ");
    char name[80];
    fgets(name, 80, stdin);
    printf("Your name is %s", name);
    printf("Type any characters.\n");
    for(;;) {
        char c = getchar();
        putchar(c);
    }
}
#endif

#ifdef STEP3
#include <stdio.h>
#include "fifo.h"
#include "tty.h"
int __io_putchar(int c) {
    // TODO Copy from your STEP2
    if (c == '\n') {
        while(!(USART5->ISR & USART_ISR_TXE));
        USART5->TDR = '\r';
    }

    while(!(USART5->ISR & USART_ISR_TXE));
    USART5->TDR = c;
    return c;
}

int __io_getchar(void) {
    // TODO
    return line_buffer_getchar();
}

int main() {
    internal_clock();
    init_usart5();
    setbuf(stdin,0);
    setbuf(stdout,0);
    setbuf(stderr,0);
    printf("Enter your name: ");
    char name[80];
    fgets(name, 80, stdin);
    printf("Your name is %s", name);
    printf("Type any characters.\n");
    for(;;) {
        char c = getchar();
        putchar(c);
    }
}
#endif

#ifdef STEP4

#include <stdio.h>
#include "fifo.h"
#include "tty.h"

// TODO DMA data structures
#define FIFOSIZE 16
char serfifo[FIFOSIZE];
int seroffset = 0;

void enable_tty_interrupt(void) {
    // TODO

    USART5->CR1 |= USART_CR1_RXNEIE; //usart5 receive interrupt
    NVIC->ISER[0] |= 0x1 << 29U; //enable nvic interrupt
    USART5->CR3 |= USART_CR3_DMAR; //dma mode for recption
    
    RCC->AHBENR |= RCC_AHBENR_DMA2EN; //clock for dma 
    DMA2->CSELR |= DMA2_CSELR_CH2_USART5_RX;
    DMA2_Channel2->CCR &= ~DMA_CCR_EN;  // First make sure DMA is turned off

    // The DMA channel 2 configuration goes here
    DMA2_Channel2->CMAR = (serfifo);
    DMA2_Channel2->CPAR = &(USART5 -> RDR);
    DMA2_Channel2->CNDTR = FIFOSIZE;
    DMA2_Channel2->CCR &= ~DMA_CCR_DIR; //periheral to memory
    DMA2_Channel2->CCR &= ~DMA_CCR_MSIZE; //memory size 8 bit
    DMA2_Channel2->CCR &= ~DMA_CCR_PSIZE; //periheral size 8 bit
    DMA2_Channel2->CCR |= DMA_CCR_MINC; //memory increment mode enable
    DMA2_Channel2->CCR &= ~DMA_CCR_PINC; //disable peripheral increment
    DMA2_Channel2->CCR |= DMA_CCR_CIRC; //enable circular mode
    DMA2_Channel2->CCR &= ~DMA_CCR_MEM2MEM; //disable memory to memory
    DMA2_Channel2->CCR |= DMA_CCR_PL; //set channel priority to highest

    DMA2_Channel2->CCR |= DMA_CCR_EN; //enable dma
}

// Works like line_buffer_getchar(), but does not check or clear ORE nor wait on new characters in USART
char interrupt_getchar() {
    // TODO
    while (fifo_newline(&input_fifo) == 0) {
        //wait for an interrupt (WFI)
        asm volatile("wfi");
    }

    char ch = fifo_remove(&input_fifo);
    return ch;
}

int __io_putchar(int c) {
    // TODO copy from STEP2
    if (c == '\n') {
        while(!(USART5->ISR & USART_ISR_TXE));
        USART5->TDR = '\r';
    }

    while(!(USART5->ISR & USART_ISR_TXE));
    USART5->TDR = c;
    return c;
}

int __io_getchar(void) {
    // TODO Use interrupt_getchar() instead of line_buffer_getchar()
    return interrupt_getchar();
}

// TODO Copy the content for the USART5 ISR here
// TODO Remember to look up for the proper name of the ISR function
void USART3_8_IRQHandler(void) {
    while(DMA2_Channel2->CNDTR != sizeof serfifo - seroffset) {
        if (!fifo_full(&input_fifo))
            insert_echo_char(serfifo[seroffset]);
        seroffset = (seroffset + 1) % sizeof serfifo;
    }
}

int main() {
    internal_clock();
    init_usart5();
    enable_tty_interrupt();

    setbuf(stdin,0); // These turn off buffering; more efficient, but makes it hard to explain why first 1023 characters not dispalyed
    setbuf(stdout,0);
    setbuf(stderr,0);
    printf("Enter your name: "); // Types name but shouldn't echo the characters; USE CTRL-J to finish
    char name[80];
    fgets(name, 80, stdin);
    printf("Your name is %s", name);
    printf("Type any characters.\n"); // After, will type TWO instead of ONE
    for(;;) {
        char c = getchar();
        putchar(c);
    }
}
#endif