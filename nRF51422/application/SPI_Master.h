/*!*********************************************************************************************************************
@file SPI_Master.h                                                                
@brief Header file for user_app2


**********************************************************************************************************************/

#ifndef __SPI_Master_H
#define __SPI_Master_H

/**********************************************************************************************************************
Type Definitions
**********************************************************************************************************************/


/**********************************************************************************************************************
Function Declarations
**********************************************************************************************************************/

/*------------------------------------------------------------------------------------------------------------------*/
/*! @publicsection */                                                                                            
/*--------------------------------------------------------------------------------------------------------------------*/


/*------------------------------------------------------------------------------------------------------------------*/
/*! @protectedsection */                                                                                            
/*--------------------------------------------------------------------------------------------------------------------*/
void SPI_Master_Initialize(void);
void SPI_Master_RunActiveState(void);


/*------------------------------------------------------------------------------------------------------------------*/
/*! @privatesection */                                                                                            
/*--------------------------------------------------------------------------------------------------------------------*/


/***********************************************************************************************************************
State Machine Declarations
***********************************************************************************************************************/
static void SPI_Master_Idle(void);    
static void SPI_Master_Error(void);         



/**********************************************************************************************************************
Constants / Definitions
**********************************************************************************************************************/




/***********************************************************************************************************************
##### GPIO setup values
***********************************************************************************************************************/

/* Pin configuration - Pins are set up using the PIN_CNF registers (one register per pin) */

#define P0_08_MRDY_CNF     	 		 ( (GPIO_PIN_CNF_DIR_Input       << GPIO_PIN_CNF_DIR_Pos)   | \
                                	 (GPIO_PIN_CNF_INPUT_Connect << GPIO_PIN_CNF_INPUT_Pos) | \
                                	 (GPIO_PIN_CNF_PULL_Disabled    << GPIO_PIN_CNF_PULL_Pos)  | \
                                	 (GPIO_PIN_CNF_DRIVE_S0S1       << GPIO_PIN_CNF_DRIVE_Pos) | \
                                	 (GPIO_PIN_CNF_SENSE_Disabled   << GPIO_PIN_CNF_SENSE_Pos) )

#define P0_09_SRDY_CNF     	 		 ( (GPIO_PIN_CNF_DIR_Input       << GPIO_PIN_CNF_DIR_Pos)   | \
                                	 (GPIO_PIN_CNF_INPUT_Connect << GPIO_PIN_CNF_INPUT_Pos) | \
                                	 (GPIO_PIN_CNF_PULL_Disabled    << GPIO_PIN_CNF_PULL_Pos)  | \
                                	 (GPIO_PIN_CNF_DRIVE_S0S1       << GPIO_PIN_CNF_DRIVE_Pos) | \
                                	 (GPIO_PIN_CNF_SENSE_Disabled   << GPIO_PIN_CNF_SENSE_Pos) )

#define P0_10_CS_CNF     	 		 	 ( (GPIO_PIN_CNF_DIR_Output       << GPIO_PIN_CNF_DIR_Pos)   | \
                                	 (GPIO_PIN_CNF_INPUT_Disconnect << GPIO_PIN_CNF_INPUT_Pos) | \
                                	 (GPIO_PIN_CNF_PULL_Disabled    << GPIO_PIN_CNF_PULL_Pos)  | \
                                	 (GPIO_PIN_CNF_DRIVE_S0S1       << GPIO_PIN_CNF_DRIVE_Pos) | \
                                	 (GPIO_PIN_CNF_SENSE_Disabled   << GPIO_PIN_CNF_SENSE_Pos) )

#define P0_11_SCK_CNF     	 		 ( (GPIO_PIN_CNF_DIR_Output       << GPIO_PIN_CNF_DIR_Pos)   | \
                                	 (GPIO_PIN_CNF_INPUT_Disconnect << GPIO_PIN_CNF_INPUT_Pos) | \
                                	 (GPIO_PIN_CNF_PULL_Disabled    << GPIO_PIN_CNF_PULL_Pos)  | \
                                	 (GPIO_PIN_CNF_DRIVE_S0S1       << GPIO_PIN_CNF_DRIVE_Pos) | \
                                	 (GPIO_PIN_CNF_SENSE_Disabled   << GPIO_PIN_CNF_SENSE_Pos) )

#define P0_12_MISO_CNF     	 		 ( (GPIO_PIN_CNF_DIR_Input       << GPIO_PIN_CNF_DIR_Pos)   | \
                                	 (GPIO_PIN_CNF_INPUT_Connect << GPIO_PIN_CNF_INPUT_Pos) | \
                                	 (GPIO_PIN_CNF_PULL_Disabled    << GPIO_PIN_CNF_PULL_Pos)  | \
                                	 (GPIO_PIN_CNF_DRIVE_S0S1       << GPIO_PIN_CNF_DRIVE_Pos) | \
                                	 (GPIO_PIN_CNF_SENSE_Disabled   << GPIO_PIN_CNF_SENSE_Pos) )

#define P0_13_MOSI_CNF     	 		 ( (GPIO_PIN_CNF_DIR_Output       << GPIO_PIN_CNF_DIR_Pos)   | \
                                	 (GPIO_PIN_CNF_INPUT_Disconnect << GPIO_PIN_CNF_INPUT_Pos) | \
                                	 (GPIO_PIN_CNF_PULL_Disabled    << GPIO_PIN_CNF_PULL_Pos)  | \
                                	 (GPIO_PIN_CNF_DRIVE_S0S1       << GPIO_PIN_CNF_DRIVE_Pos) | \
                                	 (GPIO_PIN_CNF_SENSE_Disabled   << GPIO_PIN_CNF_SENSE_Pos) )



#endif /* __SPI_Master_H */
/*--------------------------------------------------------------------------------------------------------------------*/
/* End of File                                                                                                        */
/*--------------------------------------------------------------------------------------------------------------------*/
