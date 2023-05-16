/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/**        \file  IntCtrl_Lcfg.c
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
#include "../MCAL/INTERRUPT/Inc/IntCtrl_Cfg.h"

/**********************************************************************************************************************
*  LOCAL MACROS CONSTANT\FUNCTION
*********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL DATA 
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/
IntCtr_Config Int_RightButton = 
{
	GPIO_PortD_IRQn,0x04,1,0
};
IntCtr_Config UART1_int= 
{
	UART1_IRQn,0x04,1,0
};
IntCtr_Config Int_LeftButton = 
{
	GPIO_PortC_IRQn,0x04,2,0
};

IntCtr_Config Int_FireButton = 
{
	GPIO_PortE_IRQn,0x04,3,0
};

/**********************************************************************************************************************
 *  END OF FILE: IntCtrl_Lcfg.c
 *********************************************************************************************************************/
