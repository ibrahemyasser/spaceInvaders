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
	Nokia5110_ClearBuffer();
	Nokia5110_DisplayBuffer();      // draw buffer
	if (Fire_Button.GPIOx->GPIORIS & (1<<Fire_Button.ChannelId))
	{
		SET_BIT_PERIPH_BAND(Fire_Button.GPIOx->GPIOICR,Fire_Button.ChannelId);
	//	playerBullet.active = TRUUE;
	}
}

void GPIOPortF_Handler(void)
{
	//Nokia5110_ClearBuffer();
	//Nokia5110_DisplayBuffer();      // draw buffer
	
	if(Move_Right_Button.GPIOx->GPIORIS & (1<<Move_Right_Button.ChannelId))  
	{//s1 pressed
		SET_BIT_PERIPH_BAND(Move_Right_Button.GPIOx->GPIOICR,Move_Right_Button.ChannelId);
		bulletsCounter++;
		fire_PlayerBullet();
		//playerBullet.active = TRUUE;
		Systick_StartTimer(BULLET_DELAY,updatePlayerBullet);
		
	}
	else if (Move_Left_Button.GPIOx->GPIORIS & (1<<Move_Left_Button.ChannelId))
	{//s3 pressed
		SET_BIT_PERIPH_BAND(Move_Left_Button.GPIOx->GPIOICR,Move_Left_Button.ChannelId);
		move_left();
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
