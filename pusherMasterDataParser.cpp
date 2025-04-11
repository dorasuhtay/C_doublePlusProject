#include "StdAfx.h"
#include "pusherMasterDataParser.h"

#include <string.h>

//const unsigned char mPsh_1sync = 0x28;	//'#'  1st delimiter
//const unsigned char mPsh_2sync = 0xA7;	//     2nd delimiter

unsigned char pusherMdataBuffer[16];
structMPushercommType MPushercomm;



//-----------------------------------------------------------------------
//MPushercommresetState() is used by the stream decoding statemachine
//to reset and start the state machine decoding again. This procedure is called
//when a stream, while being decoded does not match the MPushercomm format
// MPushercomm format: refer to WrapMPushercomm() or UnWrapMPushercomm()
//PARAMETER: uState is the current state of the decoding and also the storage location
//                  where the state of the decoding process is stored
//           state  is the current state. Usually zero when reset unless there is an error
//                  state is the state at which the error occurs.
//           szsize is the size in bytes
//RETURN:    NIL
//-----------------------------------------------------------------------
void MPushercommresetState(structMPushercommType *uState, int state)
{
	if (uState)
	{
        unsigned char delimiter0, delimiter1, delimiter2;
       // unsigned char *ptr;
        int databuffersize;
        unsigned char *databuffer;
        databuffersize = uState->databuffersize;
        databuffer = uState->databuffer;
        delimiter0 = uState->delimiter0;		//backup the value and restore it back later in this procedure
//        delimiter1 = uState->delimiter1;		//backup the value and restore it back later in this procedure
//	    delimiter2 = uState->delimiter2;		//backup the value and restore it back later in this procedure
//        ptr = uState->ptr;						//backup the value and restore it back later in this procedure
        memset(uState, 0x0, sizeof(structMPushercommType));	//zap the whol structure
        uState->delimiter0 = delimiter0;		//restore the earlier backed up value
//        uState->delimiter1 = delimiter1;		//restore the earlier backed up value
//        uState->delimiter2 = delimiter2;		//restore the earlier backed up value
        uState->databuffersize = 	databuffersize;
        uState->databuffer = 	databuffer;
//        uState->ptr = ptr;						//restore the earlier backed up value
        uState->error = state;					//the state at which the error occurred
	}
}


//------------------------------------------------------------------------------------
//MPushercommStateMachine() is the stream decoding statemachine procedure  characters
//streaming in is passed to this function via the parameter "ch". The character
//is matched to the state at which the decode is at (i.e. the format's character
//position). if the character does not match the state at which it is at the state
//machine state held in "uState" is reset to begin again.
//MPushercomm format: refer to WrapMPushercomm() or UnWrapMPushercomm()
//PARAMETER: uState is the current state of the decoding and also the storage location
//                  where the state of the decoding process is stored
//           ch     is the character passed into this function (input)
//RETURN:    NIL
//------------------------------------------------------------------------------------
void MPushercommStateMachine(unsigned char ch, structMPushercommType *uState)
{
	if (!uState) return;

    //-----------------------------------------------------------------------------
    //if the Packet state machine structure is not initialize then initialize it
    //-----------------------------------------------------------------------------
	if (uState->status!=PKT_ACQUIRING)
	{
        MPushercommresetState(uState, uState->state);
        uState->status=PKT_ACQUIRING;						//set status to indicate acquiring packet
        uState->state=0;
   	}

	if (uState->state>=uState->databuffersize)					//state exceed the max allocated defined buffer size
		MPushercommresetState(uState, uState->state);	//zapp

    //-----------------------------------------------------------------------------
    //Locate the current state, pick and check the character against the position
    //defined infor
    //-----------------------------------------------------------------------------
    uState->databuffer[uState->state] = ch;	//stores it up
	
  	switch(uState->state)
  	{
        case 	0:	if (ch==uState->delimiter0)                 //first character must be the delimiter0 (sync1)
                        uState->state++;							//increment the state to point to next state
                    else
                     	MPushercommresetState(uState, uState->state);	//otherwise zapp
                    break;
      /*  case 	1:	if (ch==uState->delimiter1) 				//second character must be the delimiter1  (sync2)
                        uState->state++;							//increment the state to point to next state
                    else
                     	MPushercommresetState(uState, uState->state);	//otherwise zapp
                    break;
        case 	2:	if (ch==uState->delimiter2) 				//second character must be the delimiter1  (sync2)
                        uState->state++;							//increment the state to point to next state
                    else
                     	MPushercommresetState(uState, uState->state);	//otherwise zapp
                    break;*/
        case 	11: if (ch==0x0a) 				//second character must be the delimiter1  (sync2)
                    {
                        uState->state++;
                        uState->pktSize = uState->state;		//Yes, assign the packet size variable
                        uState->databuffer[uState->pktSize] = 0x0;
                        uState->status = PKT_FOUND;
                    }
                    else
                     	MPushercommresetState(uState, uState->state);	//otherwise zapp
                    break;
        default:    uState->state++;
                    break;
    };
}

