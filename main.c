/*
 * Copyright (c) 2021, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "ti_msp_dl_config.h"
#include "UART.h"
#include "delay.h"
#include "ssd1106.h"
#include "pwm.h"
#include "encoder.h"


int main(void)
{
    SYSCFG_DL_init();
    
    //UART
    UART_Init();
    
    //PWM
    PWM_init();

    //ENCODER
    Encoder_Init();

    //SSD1106
    SSD1106_Init();
    SSD1106_ShowString(1, 0, (u8*) "R= ", 16);
    SSD1106_ShowString(1, 2, (u8*) "P= ", 16);
    SSD1106_ShowString(1, 4, (u8*) "Y= ", 16);
    SSD1106_ShowString(1, 6, (u8*) "M1= ", 16);
    float duty=0;
    while(1) 
    {		
        if(UART_GetFlag()==1)
        {
            SSD1106_ShowFNum(17, 0, UART_ReturnRoll(), 8, 4);
            SSD1106_ShowFNum(17, 2, UART_ReturnPitch(), 8, 4);
            SSD1106_ShowFNum(17, 4, UART_ReturnYaw(), 8, 4);
        }
        SSD1106_ShowFNum(25, 6, Encoder_GetM1(), 5, 0);
        SSD1106_ShowFNum(25, 4, Encoder_GetM2(), 5, 0);

        DL_GPIO_togglePins(GPIO_LED_PORT, GPIO_LED_LED_PIN);
    }
}
