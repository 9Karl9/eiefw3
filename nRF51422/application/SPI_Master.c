/*!*********************************************************************************************************************
@file SPI_Master.c                                                                
@brief SPI Master are written here.  This description
should be replaced by something specific to the task.

GLOBALS
- NONE

CONSTANTS
- NONE

TYPES
- NONE

PUBLIC FUNCTIONS
- NONE

PROTECTED FUNCTIONS
- void SPI_MasterInitialize(void)
- void SPI_MasterRunActiveState(void)


**********************************************************************************************************************/

#include "configuration.h"

/***********************************************************************************************************************
Global variable definitions with scope across entire project.
All Global variable names shall start with "G_<type>SPI_Master"
***********************************************************************************************************************/
/* New variables */
volatile u32 G_u32SPI_MasterFlags;                          /*!< @brief Global state flags */


/*--------------------------------------------------------------------------------------------------------------------*/
/* Existing variables (defined in other files -- should all contain the "extern" keyword) */
extern volatile u32 G_u32SystemTime1ms;                   /*!< @brief From main.c */
extern volatile u32 G_u32SystemTime1s;                    /*!< @brief From main.c */
extern volatile u32 G_u32SystemFlags;                     /*!< @brief From main.c */
extern volatile u32 G_u32ApplicationFlags;                /*!< @brief From main.c */


/***********************************************************************************************************************
Global variable definitions with scope limited to this local application.
Variable names shall start with "SPI_Master_<type>" and be declared as static.
***********************************************************************************************************************/
static fnCode_type SPI_Master_pfStateMachine;               /*!< @brief The state machine function pointer */
//static u32 SPI_Master_u32Timeout;                           /*!< @brief Timeout counter used across states */


/**********************************************************************************************************************
Function Definitions
**********************************************************************************************************************/

/*--------------------------------------------------------------------------------------------------------------------*/
/*! @publicsection */                                                                                            
/*--------------------------------------------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------------------------------------------*/
/*! @protectedsection */                                                                                            
/*--------------------------------------------------------------------------------------------------------------------*/

/*!--------------------------------------------------------------------------------------------------------------------
@fn void SPI_MasterInitialize(void)

@brief
Initializes the State Machine and its variables.

Should only be called once in main init section.

Requires:
- NONE

Promises:
- NONE

*/
void SPI_Master_Initialize(void)
{
	NRF_GPIO->PIN_CNF[P0_13_INDEX] = P0_13_MOSI_CNF;
	NRF_GPIO->PIN_CNF[P0_12_INDEX] = P0_12_MISO_CNF;
	NRF_GPIO->PIN_CNF[P0_11_INDEX] = P0_11_SCK_CNF;
	NRF_GPIO->PIN_CNF[P0_10_INDEX] = P0_10_CS_CNF;
	NRF_GPIO->PIN_CNF[P0_09_INDEX] = P0_09_SRDY_CNF;
	NRF_GPIO->PIN_CNF[P0_08_INDEX] = P0_08_MRDY_CNF;
	
	NRF_SPI0->PSELSCK = P0_11_INDEX;
	NRF_SPI0->PSELMISO = P0_12_INDEX;
	NRF_SPI0->PSELMOSI = P0_13_INDEX;

	
	NRF_SPI0->INTENSET = SPI_INTENSET_READY_Enabled << SPI_INTENSET_READY_Pos;
	
	NRF_GPIO->OUTCLR = P0_10_CS;
	NRF_SPI0->CONFIG = 0x00;
	NRF_SPI0->FREQUENCY = SPI_FREQUENCY_FREQUENCY_K125 << SPI_FREQUENCY_FREQUENCY_Pos;
	NRF_TWI0->ENABLE = TWI_ENABLE_ENABLE_Disabled << TWI_ENABLE_ENABLE_Pos;
	NRF_SPI0->ENABLE = SPI_ENABLE_ENABLE_Enabled << SPI_ENABLE_ENABLE_Pos;
	
	NRF_SPI0->TXD = 0x99;
  /* If good initialization, set state to Idle */
  if( 1 )
  {
    SPI_Master_pfStateMachine = SPI_Master_Idle;
  }
  else
  {
    /* The task isn't properly initialized, so shut it down and don't run */
    SPI_Master_pfStateMachine = SPI_Master_Error;
  }

} /* end SPI_MasterInitialize() */

  
/*!----------------------------------------------------------------------------------------------------------------------
@fn void SPI_MasterRunActiveState(void)

@brief Selects and runs one iteration of the current state in the state machine.

All state machines have a TOTAL of 1ms to execute, so on average n state machines
may take 1ms / n to execute.

Requires:
- State machine function pointer points at current state

Promises:
- Calls the function to pointed by the state machine function pointer

*/
void SPI_Master_RunActiveState(void)
{
  SPI_Master_pfStateMachine();

} /* end SPI_MasterRunActiveState */


/*------------------------------------------------------------------------------------------------------------------*/
/*! @privatesection */                                                                                            
/*--------------------------------------------------------------------------------------------------------------------*/


/**********************************************************************************************************************
State Machine Function Definitions
**********************************************************************************************************************/
/*-------------------------------------------------------------------------------------------------------------------*/
/* What does this state do? */
static void SPI_Master_Idle(void)
{
//	static u16 u16Time = 10000;
//	
//	
//	u16Time--;
//
//	if(u16Time == 5000)
//	{
//		NRF_GPIO->PIN_CNF[P0_26_INDEX] = P0_26_LED_BLUE_CNF;
//		NRF_GPIO->OUTCLR = P0_26_LED_BLUE;
//	}
//	
//	if(u16Time == 0)
//	{
//		NRF_GPIO->PIN_CNF[P0_26_INDEX] = P0_26_LED_BLUE_CNF;
//		NRF_GPIO->OUTSET = P0_26_LED_BLUE;
//		
//		NRF_SPI0->TXD = 0x22;
//		u16Time = 10000;
//		NRF_SPI0->EVENTS_READY = 0;
//	}
} /* end SPI_Master_Idle() */
     

/*-------------------------------------------------------------------------------------------------------------------*/
/* Handle an error */
static void SPI_Master_Error(void)          
{
  
} /* end SPI_Master_Error() */



/*--------------------------------------------------------------------------------------------------------------------*/
/* End of File                                                                                                        */
/*--------------------------------------------------------------------------------------------------------------------*/
