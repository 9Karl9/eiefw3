/*!*********************************************************************************************************************
@file user_app1.c                                                                
@brief User's tasks / applications are written here.  This description
should be replaced by something specific to the task.

----------------------------------------------------------------------------------------------------------------------
To start a new task using this user_app1 as a template:
 1. Copy both user_app1.c and user_app1.h to the Application directory
 2. Rename the files yournewtaskname.c and yournewtaskname.h
 3. Add yournewtaskname.c and yournewtaskname.h to the Application Include and Source groups in the IAR project
 4. Use ctrl-h (make sure "Match Case" is checked) to find and replace all instances of "user_app1" with "yournewtaskname"
 5. Use ctrl-h to find and replace all instances of "UserApp1" with "YourNewTaskName"
 6. Use ctrl-h to find and replace all instances of "USER_APP1" with "YOUR_NEW_TASK_NAME"
 7. Add a call to YourNewTaskNameInitialize() in the init section of main
 8. Add a call to YourNewTaskNameRunActiveState() in the Super Loop section of main
 9. Update yournewtaskname.h per the instructions at the top of yournewtaskname.h
10. Delete this text (between the dashed lines) and update the Description below to describe your task
----------------------------------------------------------------------------------------------------------------------

------------------------------------------------------------------------------------------------------------------------
GLOBALS
- NONE

CONSTANTS
- NONE

TYPES
- NONE

PUBLIC FUNCTIONS
- NONE

PROTECTED FUNCTIONS
- void UserApp1Initialize(void)
- void UserApp1RunActiveState(void)


**********************************************************************************************************************/

#include "configuration.h"

/***********************************************************************************************************************
Global variable definitions with scope across entire project.
All Global variable names shall start with "G_<type>UserApp1"
***********************************************************************************************************************/
/* New variables */
volatile u32 G_u32UserApp1Flags;                          /*!< @brief Global state flags */


/*--------------------------------------------------------------------------------------------------------------------*/
/* Existing variables (defined in other files -- should all contain the "extern" keyword) */
extern volatile u32 G_u32SystemTime1ms;                   /*!< @brief From main.c */
extern volatile u32 G_u32SystemTime1s;                    /*!< @brief From main.c */
extern volatile u32 G_u32SystemFlags;                     /*!< @brief From main.c */
extern volatile u32 G_u32ApplicationFlags;                /*!< @brief From main.c */

extern volatile u8 G_au8DebugScanfBuffer[DEBUG_SCANF_BUFFER_SIZE];
/***********************************************************************************************************************
Global variable definitions with scope limited to this local application.
Variable names shall start with "UserApp1_<type>" and be declared as static.
***********************************************************************************************************************/
static fnCode_type UserApp1_pfStateMachine;               /*!< @brief The state machine function pointer */
//static u32 UserApp1_u32Timeout;                           /*!< @brief Timeout counter used across states */

static u8 au8DebugGameIF[][27] = 
{
	"012345678901234567890123\n\r",
	"1   1   |   2   |   3   \n\r",
	"2-------|-------|-------\n\r",
	"3   4   |   5   |   6   \n\r",
	"2-------|-------|-------\n\r",
	"5   7   |   8   |   9   \n\r"
};

static bool bDebugTurn = TRUE;
static bool bBleTurn = TRUE;
static u8 u8TurnCount = 0;
/**********************************************************************************************************************
Function Definitions
**********************************************************************************************************************/

/*--------------------------------------------------------------------------------------------------------------------*/
/*! @publicsection */                                                                                            
/*--------------------------------------------------------------------------------------------------------------------*/
void SlaveRxCallback(void)
{
	UserApp1_pfStateMachine = UserApp1SM_Slave;
}

void SlaveTxCallback(void)
{
	
}

void DebugPrintGameIF(void)
{
	static u8 u8Index = 0;
	static u8	*pu8DebugPointer = (u8 *)au8DebugGameIF;
	
	u8Index = sizeof(au8DebugGameIF)/27;
	pu8DebugPointer = au8DebugGameIF[0];
	
	for(; u8Index ; u8Index-- , pu8DebugPointer +=27)
	{
		DebugPrintf(pu8DebugPointer);
	}
	
}

void DebugWins(void)
{
	LedBlink(RED,LED_4HZ);
	LedBlink(ORANGE,LED_4HZ);
	LedBlink(YELLOW,LED_4HZ);
	LedBlink(GREEN,LED_4HZ);
}

void BleWins(void)
{
	LedBlink(CYAN,LED_4HZ);
	LedBlink(BLUE,LED_4HZ);
	LedBlink(PURPLE,LED_4HZ);
	LedBlink(WHITE,LED_4HZ);
}
/*--------------------------------------------------------------------------------------------------------------------*/
/*! @protectedsection */                                                                                            
/*--------------------------------------------------------------------------------------------------------------------*/

/*!--------------------------------------------------------------------------------------------------------------------
@fn void UserApp1Initialize(void)

@brief
Initializes the State Machine and its variables.

Should only be called once in main init section.

Requires:
- NONE

Promises:
- NONE

*/
void UserApp1Initialize(void)
{
	static SspConfigurationType RequestType;
	
	RequestType.SspPeripheral = USART2;
	RequestType.pCsGpioAddress = AT91C_BASE_PIOB;
	RequestType.u32CsPin = PB_22_ANT_USPI2_CS;
	RequestType.eBitOrder = MSB_FIRST;
	RequestType.fnSlaveRxFlowCallback = SlaveRxCallback;
	RequestType.fnSlaveTxFlowCallback = SlaveTxCallback;
	
	SspRequest(& RequestType);
	
	DebugPrintGameIF();
	DebugLineFeed();
	DebugPrintf("Your input:");
	
	/* If good initialization, set state to Idle */
  if( 1 )
  {
    UserApp1_pfStateMachine = UserApp1SM_Idle;
  }
  else
  {
    /* The task isn't properly initialized, so shut it down and don't run */
    UserApp1_pfStateMachine = UserApp1SM_Error;
  }

} /* end UserApp1Initialize() */

  
/*!----------------------------------------------------------------------------------------------------------------------
@fn void UserApp1RunActiveState(void)

@brief Selects and runs one iteration of the current state in the state machine.

All state machines have a TOTAL of 1ms to execute, so on average n state machines
may take 1ms / n to execute.

Requires:
- State machine function pointer points at current state

Promises:
- Calls the function to pointed by the state machine function pointer

*/
void UserApp1RunActiveState(void)
{
  UserApp1_pfStateMachine();

} /* end UserApp1RunActiveState */


/*------------------------------------------------------------------------------------------------------------------*/
/*! @privatesection */                                                                                            
/*--------------------------------------------------------------------------------------------------------------------*/


/**********************************************************************************************************************
State Machine Function Definitions
**********************************************************************************************************************/
/*-------------------------------------------------------------------------------------------------------------------*/
/* What does this state do? */
static void UserApp1SM_Idle(void)
{
	static u8 au8DebugScanBuffer[3];
	static u8 *pu8Pointer = NULL;
	
	if(DebugScanf(au8DebugScanBuffer))
	{
		DebugLineFeed();
		DebugLineFeed();
		
		if(bDebugTurn == FALSE)
		{
			DebugPrintf("This is not your turn.\n\r");
			DebugLineFeed();
		}
		
		if( bDebugTurn == TRUE)
		{
			switch(au8DebugScanBuffer[0])
			{
				case '1':
				{
					pu8Pointer = &au8DebugGameIF[1][4];
					break;
				}
				case '2':
				{
					pu8Pointer = &au8DebugGameIF[1][12];
					break;
				}
				case '3':
				{
					pu8Pointer = &au8DebugGameIF[1][20];
					break;
				}
				case '4':
				{
					pu8Pointer = &au8DebugGameIF[3][4];
					break;
				}
				case '5':
				{
					pu8Pointer = &au8DebugGameIF[3][12];
					break;
				}
				case '6':
				{
					pu8Pointer = &au8DebugGameIF[3][20];
					break;
				}
				case '7':
				{
					pu8Pointer = &au8DebugGameIF[5][4];
					break;
				}
				case '8':
				{
					pu8Pointer = &au8DebugGameIF[5][12];
					break;
				}
				case '9':
				{
					pu8Pointer = &au8DebugGameIF[5][20];
					break;
				}
				default:
				{
					DebugPrintf("\n\rFalse Format\n\r");
					break;
				}
			}// End of switch
			
				if(pu8Pointer != NULL)
			{
				if( *pu8Pointer == 'X' || *pu8Pointer == 'O' )
				{
					DebugPrintf("The Spot is occupied.\n\r");
					DebugLineFeed();
				}
				
				if( *pu8Pointer != 'X' && *pu8Pointer != 'O' )
				{
					bDebugTurn = FALSE;
					bBleTurn = TRUE;
					*pu8Pointer = 'X';
					u8TurnCount++;
					DebugPrintGameIF();
					DebugLineFeed();
				}
			}// End of if(pu8Pointer != NULL)
			
//			if( au8DebugGameIF[1][4] == au8DebugGameIF[1][12] == au8DebugGameIF[1][20] == 'X')
			
		}// End of if(DebugTurn == TURE)
	}// End of if(DebugScanf(au8DebugScanBuffer))
	
	if( u8TurnCount >= 5 )
	{
		if( (au8DebugGameIF[1][4] == 'X') && (au8DebugGameIF[1][12] == 'X') && (au8DebugGameIF[1][20] == 'X') )
		{
			DebugPrintf("Debug wins\n\r");
			DebugWins();
			u8TurnCount = 0;
		}
		
		if( (au8DebugGameIF[1][4] == 'X') && (au8DebugGameIF[3][4] == 'X') && (au8DebugGameIF[5][4] == 'X') )
		{
			DebugPrintf("Debug wins\n\r");
			DebugWins();
			u8TurnCount = 0;
		}
		
		if( (au8DebugGameIF[1][4] == 'X') && (au8DebugGameIF[3][12] == 'X') && (au8DebugGameIF[5][20] == 'X') )
		{
			DebugPrintf("Debug wins\n\r");
			DebugWins();
			u8TurnCount = 0;
		}
		
		if( (au8DebugGameIF[1][20] == 'X') && (au8DebugGameIF[3][20] == 'X') && (au8DebugGameIF[5][20] == 'X') )
		{
			DebugPrintf("Debug wins\n\r");
			DebugWins();
			u8TurnCount = 0;
		}
		
		if( (au8DebugGameIF[5][4] == 'X') && (au8DebugGameIF[5][12] == 'X') && (au8DebugGameIF[5][20] == 'X') )
		{
			DebugPrintf("Debug wins\n\r");
			DebugWins();
			u8TurnCount = 0;
		}
		
		if( (au8DebugGameIF[1][20] == 'X') && (au8DebugGameIF[3][12] == 'X') && (au8DebugGameIF[5][4] == 'X') )
		{
			DebugPrintf("Debug wins\n\r");
			DebugWins();
			u8TurnCount = 0;
		}
		
		if(u8TurnCount == 9)
		{
			DebugPrintf("Draw\n\r");
			DebugWins();
			BleWins();
			u8TurnCount = 0;
		}
	}
	
	if(WasButtonPressed(BUTTON0))
	{
		ButtonAcknowledge(BUTTON0);
		UserApp1_pfStateMachine = UserApp1SM_StartAgain;
		
	}
	
} /* end UserApp1SM_Idle() */
     
static void UserApp1SM_Slave(void)
{
	static u8 u8BleSet = 0;
	static u8 *pu8Pointer = NULL;
	
	u8BleSet = AT91C_BASE_US2->US_RHR;
	
	if(bBleTurn == FALSE)
	{
		DebugPrintf("This is not your turn.\n\r");
		DebugLineFeed();
	}
	
	if(bBleTurn == TRUE)
	{
		switch(u8BleSet)
		{
			case 0x11:
			{
				pu8Pointer = &au8DebugGameIF[1][4];
				break;
			}
			case 0x12:
			{
				pu8Pointer = &au8DebugGameIF[1][12];
				break;
			}
			case 0x13:
			{
				pu8Pointer = &au8DebugGameIF[1][20];
				break;
			}
			case 0x21:
			{
				pu8Pointer = &au8DebugGameIF[3][4];
				break;
			}
			case 0x22:
			{
				pu8Pointer = &au8DebugGameIF[3][12];
				break;
			}
			case 0x23:
			{
				pu8Pointer = &au8DebugGameIF[3][20];
				break;
			}
			case 0x31:
			{
				pu8Pointer = &au8DebugGameIF[5][4];
				break;
			}
			case 0x32:
			{
				pu8Pointer = &au8DebugGameIF[5][12];
				break;
			}
			case 0x33:
			{
				pu8Pointer = &au8DebugGameIF[5][20];
				break;
			}
			default:
			{
				DebugPrintf("\n\rFalse format\n\r");
				break;
			}
		}//End of switch(u8BleSet)
		
		if(pu8Pointer != NULL)
		{
			if( *pu8Pointer == 'X' || *pu8Pointer == 'O' )
			{
				DebugPrintf("The Spot is occupied\n\r");
				DebugLineFeed();
			}
			
			if( *pu8Pointer != 'X' && *pu8Pointer != 'O' )
			{
				bBleTurn = FALSE;
				bDebugTurn = TRUE;
				*pu8Pointer = 'O';
				u8TurnCount++;
				DebugPrintGameIF();
				DebugLineFeed();
			}
		}// End of if(pu8Pointer != NULL)
	}//End of if(bBleTurn == TRUE)
	
	if( u8TurnCount >= 5 )
	{
		if( (au8DebugGameIF[1][4] == 'O') && (au8DebugGameIF[1][12] == 'O') && (au8DebugGameIF[1][20] == 'O') )
		{
			DebugPrintf("Ble wins\n\r");
			BleWins();
			u8TurnCount = 0;
		}
		
		if( (au8DebugGameIF[1][4] == 'O') && (au8DebugGameIF[3][4] == 'O') && (au8DebugGameIF[5][4] == 'O') )
		{
			DebugPrintf("Ble wins\n\r");
			BleWins();
			u8TurnCount = 0;
		}
		
		if( (au8DebugGameIF[1][4] == 'O') && (au8DebugGameIF[3][12] == 'O') && (au8DebugGameIF[5][20] == 'O') )
		{
			DebugPrintf("Ble wins\n\r");
			BleWins();
			u8TurnCount = 0;
		}
		
		if( (au8DebugGameIF[1][20] == 'O') && (au8DebugGameIF[3][20] == 'O') && (au8DebugGameIF[5][20] == 'O') )
		{
			DebugPrintf("Ble wins\n\r");
			BleWins();
			u8TurnCount = 0;
		}
		
		if( (au8DebugGameIF[5][4] == 'O') && (au8DebugGameIF[5][12] == 'O') && (au8DebugGameIF[5][20] == 'O') )
		{
			DebugPrintf("Ble wins\n\r");
			BleWins();
			u8TurnCount = 0;
		}
		
		if( (au8DebugGameIF[1][20] == 'O') && (au8DebugGameIF[3][12] == 'O') && (au8DebugGameIF[5][4] == 'O') )
		{
			DebugPrintf("Ble wins\n\r");
			BleWins();
			u8TurnCount = 0;
		}
		
		if(u8TurnCount == 9)
		{
			DebugPrintf("Draw\n\r");
			DebugWins();
			BleWins();
			u8TurnCount = 0;
		}
	}
	
	UserApp1_pfStateMachine = UserApp1SM_Idle;
}/* end UserApp1SM_Slave() */

static void UserApp1SM_StartAgain(void)
{
	u8TurnCount = 0;
	
	LedOff(RED);
	LedOff(ORANGE);
	LedOff(YELLOW);
	LedOff(GREEN);
	LedOff(CYAN);
	LedOff(BLUE);
	LedOff(PURPLE);
	LedOff(WHITE);
	
	au8DebugGameIF[1][4] = '1';
	au8DebugGameIF[1][12] = '2';
	au8DebugGameIF[1][20] = '3';
	au8DebugGameIF[3][4] = '4';
	au8DebugGameIF[3][12] = '5';
	au8DebugGameIF[3][20] = '6';
	au8DebugGameIF[5][4] = '7';
	au8DebugGameIF[5][12] = '8';
	au8DebugGameIF[5][20] = '9';

	DebugPrintf("Start over");
	DebugLineFeed();
	DebugPrintGameIF();

	UserApp1_pfStateMachine = UserApp1SM_Idle;
}


/*-------------------------------------------------------------------------------------------------------------------*/
/* Handle an error */
static void UserApp1SM_Error(void)          
{

} /* end UserApp1SM_Error() */



/*--------------------------------------------------------------------------------------------------------------------*/
/* End of File                                                                                                        */
/*--------------------------------------------------------------------------------------------------------------------*/
