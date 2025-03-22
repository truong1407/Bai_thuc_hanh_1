#ifndef __USART2__
#define __USART2__

#ifdef __cplusplus
extern "C" {
#endif

#include "stdint.h"

void UART2_DEBUG_Init(uint32_t baudrate);
void UART2_DEBUG_SendString(char *str);
void UART2_DEBUG_Int_Number(int num);
void UART2_DEBUG_SendChar(char c);

void USART2_DEBUG_Init(unsigned int baudrates);            
void USART2_DEBUG_SendString(char *varString);            
void USART2_DEBUG_SendChar(char varChar);                    
void USART2_DEBUG_Int_Number(int32_t varNumber);                        
void USART2_DEBUG_Float_Number(float varNumber);
void USART2_DEBUG_ShowString(void);                                    

int8_t USART2_DEBUG_Compare(char *string);                    
int8_t USART2_DEBUG_Strstr(char *string);                        
int8_t USART2_DEBUG_Flag(void);                                            

void USART2_Reset_Count(void);                                            

#ifdef __cplusplus
}
#endif

#endif