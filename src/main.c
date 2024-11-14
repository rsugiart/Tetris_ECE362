#include "stm32f0xx.h"
#include <stdint.h>
#include <stdlib.h>
#include "lcd.h"
#include "sound.h"

void setup_tim17()
{
    // Configure TIM17 to invoke the ISR 100 times per second.
    // Remember to set the NVIC ISER to allow the interrupt for TIM17.
    RCC -> APB2ENR |= RCC_APB2ENR_TIM17EN;
    TIM17 -> PSC = 48000-1;
    TIM17 -> ARR = 10-1;
    TIM17 -> DIER |= TIM_DIER_UDE;
    NVIC -> ISER[0] = 1 << TIM17_IRQn;
    TIM17 -> CR1 |= TIM_CR1_CEN;
}

void setup_buttons()
{
    // Enable Ports A and B.
    // Set PA0 and PB2 for input and enable pull-down resistors.
    RCC->AHBENR |= RCC_AHBENR_GPIOBEN;
    RCC->AHBENR |= RCC_AHBENR_GPIOAEN;
    GPIOA -> MODER &= ~0x3;
    GPIOB -> MODER &= ~0x30;
    GPIOA -> PUPDR |= 0x2;
    GPIOB -> PUPDR |= 0x20;
}

char check_key()
{
    // If PB2 is pressed, return '*'
    // If PA0 is pressed, return 'D'
    // Otherwise, return 0
    if (GPIOA->IDR && 0x1) {
        return '*';
    }
    if(GPIOB->IDR && (1 << 2)) {
        return 'D';
    }
    return 0;
}

// Copy a subset of a large source picture into a smaller destination.
// sx,sy are the offset into the source picture.
void pic_subset(Picture *dst, const Picture *src, int sx, int sy)
{
    int dw = dst->width;
    int dh = dst->height;
    for(int y=0; y<dh; y++) {
        if (y+sy < 0)
            continue;
        if (y+sy >= src->height)
            break;
        for(int x=0; x<dw; x++) {
            if (x+sx < 0)
                continue;
            if (x+sx >= src->width)
                break;
            dst->pix2[dw * y + x] = src->pix2[src->width * (y+sy) + x + sx];
        }
    }
}

// Overlay a picture onto a destination picture.
// xoffset,yoffset are the offset into the destination picture that the
// source picture is placed.
// Any pixel in the source that is the 'transparent' color will not be
// copied.  This defines a color in the source that can be used as a
// transparent color.
void pic_overlay(Picture *dst, int xoffset, int yoffset, const Picture *src, int transparent)
{
    for(int y=0; y<src->height; y++) {
        int dy = y+yoffset;
        if (dy < 0)
            continue;
        if (dy >= dst->height)
            break;
        for(int x=0; x<src->width; x++) {
            int dx = x+xoffset;
            if (dx < 0)
                continue;
            if (dx >= dst->width)
                break;
            unsigned short int p = src->pix2[y*src->width + x];
            if (p != transparent)
                dst->pix2[dy*dst->width + dx] = p;
        }
    }
}

// Called after a bounce, update the x,y velocity components in a
// pseudo random way.  (+/- 1)
void perturb(int *vx, int *vy)
{
    if (*vx > 0) {
        *vx += (random()%3) - 1;
        if (*vx >= 3)
            *vx = 2;
        if (*vx == 0)
            *vx = 1;
    } else {
        *vx += (random()%3) - 1;
        if (*vx <= -3)
            *vx = -2;
        if (*vx == 0)
            *vx = -1;
    }
    if (*vy > 0) {
        *vy += (random()%3) - 1;
        if (*vy >= 3)
            *vy = 2;
        if (*vy == 0)
            *vy = 1;
    } else {
        *vy += (random()%3) - 1;
        if (*vy <= -3)
            *vy = -2;
        if (*vy == 0)
            *vy = -1;
    }
}

extern const Picture background; // A 240x320 background image
extern const Picture ball; // A 19x19 purple ball with white boundaries
extern const Picture paddle; // A 59x5 paddle

const int border = 20;
int xmin; // Farthest to the left the center of the ball can go
int xmax; // Farthest to the right the center of the ball can go
int ymin; // Farthest to the top the center of the ball can go
int ymax; // Farthest to the bottom the center of the ball can go
int x,y; // Center of ball
int vx,vy; // Velocity components of ball

int px; // Center of paddle offset
int newpx; // New center of paddle

// This C macro will create an array of Picture elements.
// Really, you'll just use it as a pointer to a single Picture
// element with an internal pix2[] array large enough to hold
// an image of the specified size.
// BE CAREFUL HOW LARGE OF A PICTURE YOU TRY TO CREATE:
// A 100x100 picture uses 20000 bytes.  You have 32768 bytes of SRAM.
#define TempPicturePtr(name,width,height) Picture name[(width)*(height)/6+2] = { {width,height,2} }

// Create a 29x29 object to hold the ball plus padding
TempPicturePtr(object,29,29);

void TIM17_IRQHandler(void)
{
    TIM17->SR &= ~TIM_SR_UIF;
    char key = check_key();
    if (key == '*')
        newpx -= 1;
    else if (key == 'D')
        newpx += 1;
    
    x += vx;
    y += vy;
    if (x <= xmin) {
        // Ball hit the left wall.
        vx = - vx;
        if (x < xmin)
            x += vx;
        perturb(&vx,&vy);
    }
    if (x >= xmax) {
        // Ball hit the right wall.
        vx = -vx;
        if (x > xmax)
            x += vx;
        perturb(&vx,&vy);
    }
    if (y <= ymin) {
        // Ball hit the top wall.
        vy = - vy;
        if (y < ymin)
            y += vy;
        perturb(&vx,&vy);
    }
    if (y >= ymax - paddle.height &&
        x >= (px - paddle.width/2) &&
        x <= (px + paddle.width/2)) {
        // The ball has hit the paddle.  Bounce.
        int pmax = ymax - paddle.height;
        vy = -vy;
        if (y > pmax)
            y += vy;
    }
    else if (y >= ymax) {
        // The ball has hit the bottom wall.  Set velocity of ball to 0,0.
        vx = 0;
        vy = 0;
    }

    TempPicturePtr(tmp,29,29); // Create a temporary 29x29 image.
    pic_subset(tmp, &background, x-tmp->width/2, y-tmp->height/2); // Copy the background
    pic_overlay(tmp, 0,0, object, 0xffff); // Overlay the object
    pic_overlay(tmp, (px-paddle.width/2) - (x-tmp->width/2),
            (background.height-border-paddle.height) - (y-tmp->height/2),
            &paddle, 0xffff); // Draw the paddle into the image
    LCD_DrawPicture(x-tmp->width/2,y-tmp->height/2, tmp); // Re-draw it to the screen
    // The object has a 5-pixel border around it that holds the background
    // image.  As long as the object does not move more than 5 pixels (in any
    // direction) from it's previous location, it will clear the old object.
}

// int main(void)
// {
//     setup_buttons();
//     //internal_clock();
//     LCD_Setup();
//     LCD_Clear(RED);
//     // nano_wait(1000000000);

// //     // Draw the background.
// //     LCD_DrawPicture(0,0,&background);
  
 
    
//     LCD_DrawFillRectangle(20,20,60,40,RED);
//     xmin = border + 10;
//     xmax = background.width - border - 10;
//     ymin = border + 10;
//     ymax = background.height - border - 10;
//     x = (xmin+xmax)/2; // Center of ball
//     y = ymin;
//     vx = 0; // Velocity components of ball
//     vy = 1;
//     setup_tim17();
// }

// Center the 19x19 ball into center of the 29x29 object.
   // Set all pixels in the object to white.
    // for(int i=0; i<29*29; i++)
    //     object->pix2[i] = 0xffff;
    // // Now, the 19x19 ball has 5-pixel white borders in all directions.
    // pic_overlay(object,5,5,&ball,0xffff);
    // //nano_wait(100000);
    // // Initialize the game state.
    // xmin = border + ball.width/2;
    // xmax = background.width - border - ball.width/2;
    // ymin = border + ball.width/2;
    // ymax = background.height - border - ball.height/2;
    // x = (xmin+xmax)/2; // Center of ball
    // y = ymin;
    // vx = 0; // Velocity components of ball
    // vy = 1;

//     // px = -1; // Center of paddle offset (invalid initial value to force update)
//     // newpx = (xmax+xmin)/2; // New center of paddle

