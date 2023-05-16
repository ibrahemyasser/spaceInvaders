/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/**        \file  FileName.c
 *        \brief  
 *
 *      \details  
 *
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "../LIBRARIES/common/Std_Types.h"
#include "../LIBRARIES/CpuDriver/inc/cpu_driver.h"
#include "../inc/spaceInvaders.h"
#include "../Nokia5110.h"
#include "../LIBRARIES/COMMON/Mcu_Hw.h"
#include "../../MCAL/PORT/Inc/Port_Cfg.h"
#include "../../LIBRARIES/Common/Bit_Math.h"
#include "../inc/spaceInvaders.h"
#include "../../MCAL/SYSTICK/Inc/Systick.h"

/**********************************************************************************************************************
*  LOCAL MACROS CONSTANT\FUNCTION
*********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL DATA 
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/

extern Port_ConfigType Move_Right_Button;
extern Port_ConfigType Move_Left_Button;
extern Port_ConfigType Fire_Button;

/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/
void GPIOPortE_Handler(void)
{
	if (Fire_Button.GPIOx->GPIORIS & (1<<Fire_Button.ChannelId))
	{
		SET_BIT_PERIPH_BAND(Fire_Button.GPIOx->GPIOICR,Fire_Button.ChannelId);
		fireBullet_Flag = TRUUE;
	}
}
void GPIOPortC_Handler(void)
{
	if (Move_Left_Button.GPIOx->GPIORIS & (1<<Move_Left_Button.ChannelId))
	{//s2 pressed
		SET_BIT_PERIPH_BAND(Move_Left_Button.GPIOx->GPIOICR,Move_Left_Button.ChannelId);
		if(!bye)
		{
			bye = TRUUE;
			return;
		}
		moveLeft_Flag = TRUUE;
		
		//playerBullet.active = TRUUE;
	}
}

void GPIOPortD_Handler(void)
{
	
	if(Move_Right_Button.GPIOx->GPIORIS & (1<<Move_Right_Button.ChannelId))  
	{//s1 pressed
		SET_BIT_PERIPH_BAND(Move_Right_Button.GPIOx->GPIOICR,Move_Right_Button.ChannelId);
		if(!start)
		{
			start = TRUUE;
			return;
		}
		moveRight_Flag = TRUUE;

	}
}

void UART1_Handler(void)
{
	
if (UART1->MIS & UART_MIS_RXMIS) { // If a receive interrupt has occurred
        receivedChar = (uint8_t)UART1->DR; // Read the received character
				switch(receivedChar) {
							case 'a':
									// Handle the 'a' key press
									moveLeft_Flag = TRUUE;
									break;
							case 'd':
									moveRight_Flag = TRUUE;
								break;
							case ' ':
									fireBullet_Flag = TRUUE;
							default:
								break;
						}
				SET_BIT_PERIPH_BAND(UART1->ICR,UART_ICR_RXIC); // Clear the interrupt flag
    }
	
	if (UART1->MIS & UART_MIS_TXMIS) { // If a transmit interrupt has occurred
        UART1->DR = receivedChar; // Send the character stored in the global variable c
       SET_BIT_PERIPH_BAND(UART1->ICR,UART_ICR_TXIC); // Clear the interrupt flag
    }

   }

/******************************************************************************
* \Syntax          : Std_ReturnType FunctionName(AnyType parameterName)        
* \Description     : Describe this service                                    
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : parameterName   Parameter Describtion                     
* \Parameters (out): None                                                      
* \Return value:   : Std_ReturnType  E_OK
*                                    E_NOT_OK                                  
*******************************************************************************/


/**********************************************************************************************************************
 *  END OF FILE: FileName.c
 *********************************************************************************************************************/
