#include "stdio.h"
#include "stm32f10x.h"                  
#include "stm32f10x_gpio.h"             
#include "stm32f10x_rcc.h"              
#include "stm32f10x_usart.h"            
#include "stm32f10x_tim.h"              
#include "dht11.h"                    
#include <stdint.h>


uint8_t getC;
uint8_t string_nhan[100];

char Flag = 0;											
uint16_t cnt1 = 0, cnt2 = 0, position; 

void USART2_DEBUG_Init(unsigned int baudrate) {							
    GPIO_InitTypeDef gpio;
    USART_InitTypeDef uart;
    
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);  
    
    gpio.GPIO_Pin = GPIO_Pin_2;  
    gpio.GPIO_Mode = GPIO_Mode_AF_PP;
    gpio.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &gpio);
    
    gpio.GPIO_Pin = GPIO_Pin_3;  
    gpio.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOA, &gpio);
    
    uart.USART_BaudRate = baudrate;
    uart.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    uart.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    uart.USART_Parity = USART_Parity_No;
    uart.USART_StopBits = USART_StopBits_1;
    uart.USART_WordLength = USART_WordLength_8b;
    
    USART_Init(USART2, &uart);
    USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);
    NVIC_EnableIRQ(USART2_IRQn);
    USART_Cmd(USART2, ENABLE);
}	

void USART2_IRQHandler() {														
    if (USART_GetITStatus(USART2, USART_IT_RXNE) != RESET) {
        getC = USART_ReceiveData(USART2);
        if (getC == '\n') {
            string_nhan[cnt1] = '\0';
            Flag = 1;
            cnt1 = 0; 
        } else {
            if (cnt1 < sizeof(string_nhan) - 1) {  
                string_nhan[cnt1++] = getC;
            }
        }
    }
}

void USART2_DEBUG_SendChar(char varChar) {				
    while (USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET);
    USART_SendData(USART2, varChar);
}		

void USART2_DEBUG_SendString(char *varString) {				
    while (*varString) {
        USART2_DEBUG_SendChar(*varString++);
    }
}

void USART2_DEBUG_Int_Number(int32_t varNumber) {						
    char buffer[12];
    sprintf(buffer, "%d", varNumber);
    USART2_DEBUG_SendString(buffer);
}

void USART2_DEBUG_Float_Number(float varNumber) {
    char buffer[20];
    sprintf(buffer, "%.4f", varNumber);  
    USART2_DEBUG_SendString(buffer);
}

int8_t USART2_DEBUG_Flag(void) {											
    if (Flag) {
        Flag = 0;
        return 1;
    }
    return 0;
}

int8_t USART2_DEBUG_Compare(char *string) {							
    cnt2 = 0;
    while (string[cnt2] != '\0') {
        cnt2++;
    }

    if (cnt2 == cnt1) { 
        for (position = 0; position < cnt2; position++) {
            if (string_nhan[position] != string[position]) {
                return 0;
            }
        }
        return 1;
    }
    return 0;
}

int8_t USART2_DEBUG_Strstr(char *string) {								
    uint16_t i, j, temp;
    cnt2 = 0;
    while (string[cnt2] != '\0') {
        cnt2++;
    }

    for (i = 0; i < cnt1; i++) {
        temp = i;
        for (j = 0; j < cnt2; j++) {
            if (string_nhan[temp] != string[j]) {
                break;
            }
            temp++;
        }
        if (j == cnt2) {
            return 1;
        }
    }
    return 0;
}

void USART2_Reset_Count(void) {									
    cnt1 = 0;
    cnt2 = 0;
}

void USART2_DEBUG_ShowString(void) {							
    USART2_DEBUG_SendString(string_nhan);
}


void UART2_DEBUG_Init(uint32_t baudrate) {
    USART2_DEBUG_Init(baudrate);
}

void UART2_DEBUG_SendString(char *str) {
    USART2_DEBUG_SendString(str);
}

void UART2_DEBUG_Int_Number(int num) {
    USART2_DEBUG_Int_Number(num);
}

void UART2_DEBUG_SendChar(char c) {
    USART2_DEBUG_SendChar(c);
}