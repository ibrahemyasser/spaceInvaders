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
#include "../MCAL/PORT/Inc/Port_Cfg.h"
#include "spaceInvaders.h"

/**********************************************************************************************************************
*  LOCAL MACROS CONSTANT\FUNCTION
*********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL DATA 
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/

Port_ConfigType led_indicators [MAX_LIVES] = {
	{
		GPIOF,
		PORTF,
		PF1,
		DIGITAL_PIN,
		HIGH,
		OUTPUT,
		PULL_UP,
		R8R
		
	},
	{
		GPIOF,
		PORTF,
		PF2,
		DIGITAL_PIN,
		HIGH,
		OUTPUT,
		PULL_UP,
		R8R
	},
	{
		GPIOF,
		PORTF,
		PF3,
		DIGITAL_PIN,
		HIGH,
		OUTPUT,
		PULL_UP,
		R8R
	}
};

Port_ConfigType Move_Right_Button =
	{
		GPIOD,
		PORTD,
		PD0,
		DIGITAL_PIN,
		HIGH,
		INPUT,
		PULL_UP,
		R4R
		
	};
	GPIO_EXTI_ConfigType Right_Button=
	{
		GPIOD,
		PD0,
		EDGE_SENSITIVE,
		EDGE_CONTROLLED,
		FALLING_LOW,
		GPIO_PortD_IRQn
	};
	Port_ConfigType Fire_Button =
	{
		GPIOE,
		PORTE,
		PE0,
		DIGITAL_PIN,
		HIGH,
		INPUT,
		PULL_UP,
		R4R
		
	};
	GPIO_EXTI_ConfigType Fire_EXTI_Button=
	{
		GPIOE,
		PE0,
		EDGE_SENSITIVE,
		EDGE_CONTROLLED,
		FALLING_LOW,
		GPIO_PortE_IRQn
	};
	
Port_ConfigType Move_Left_Button= 
	{
		GPIOC,
		PORTC,
		PC4,
		DIGITAL_PIN,
		HIGH,
		INPUT,
		PULL_UP,
		R4R
		
	};
	GPIO_EXTI_ConfigType Left_Button=
	{
		GPIOC,
		PC4,
		EDGE_SENSITIVE,
		EDGE_CONTROLLED,
		FALLING_LOW,
		GPIO_PortC_IRQn
	};

	
	Port_ConfigType UART1_Rx =
	{
		GPIOB,
		PORTB,
		PB0,
		PB0_U1Rx,
		ALFF,
		ALF,
		NONE,
		NONEE
		
	};
	Port_ConfigType UART1_Tx=
	{
		GPIOB,
		PORTB,
		PB1,
		PB1_U1Tx,
		ALFF,
		ALF,
		NONE,
		NONEE
		
	};
	

	

/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/



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
