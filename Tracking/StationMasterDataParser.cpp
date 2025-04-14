#include "StdAfx.h"
#include "StationMasterDataParser.h"
#include "serialnetwork_func.h"

#include <string.h>

unsigned char StationMdataBuffer[13];
structMStationcommType MStationcomm;



//-----------------------------------------------------------------------
//MStationcommresetState() is used by the stream decoding statemachine
//to reset and start the state machine decoding again. This procedure is called
//when a stream, while being decoded does not match the MStationcomm format
// MStationcomm format: refer to WrapMStationcomm() or UnWrapMStationcomm()
//PARAMETER: uState is the current state of the decoding and also the storage location
//                  where the state of the decoding process is stored
//           state  is the current state. Usually zero when reset unless there is an error
//                  state is the state at which the error occurs.
//           szsize is the size in bytes
//RETURN:    NIL
//-----------------------------------------------------------------------
void MStationcommresetState(structMStationcommType *uState, int state)
{
	if (uState)
	{
        unsigned char delimiter0;//, delimiter1;
       // unsigned char *ptr;
        int databuffersize;
        unsigned char *databuffer;
        databuffersize = uState->databuffersize;
        databuffer = uState->databuffer;
        delimiter0 = uState->delimiter0;		//backup the value and restore it back later in this procedure

//        ptr = uState->ptr;						//backup the value and restore it back later in this procedure
        memset(uState, 0x0, sizeof(structMStationcommType));	//zap the whol structure
        uState->delimiter0 = delimiter0;		//restore the earlier backed up value

        uState->databuffersize = 	databuffersize;
        uState->databuffer = 	databuffer;
//        uState->ptr = ptr;						//restore the earlier backed up value
        uState->error = state;					//the state at which the error occurred
	}
}



//------------------------------------------------------------------------------------
//MStationcommStateMachine() is the stream decoding statemachine procedure  characters
//streaming in is passed to this function via the parameter "ch". The character
//is matched to the state at which the decode is at (i.e. the format's character
//position). if the character does not match the state at which it is at the state
//machine state held in "uState" is reset to begin again.
//MStationcomm format: refer to WrapMStationcomm() or UnWrapMStationcomm()
//PARAMETER: uState is the current state of the decoding and also the storage location
//                  where the state of the decoding process is stored
//           ch     is the character passed into this function (input)
//RETURN:    NIL
//------------------------------------------------------------------------------------
void MStationcommStateMachine(unsigned char ch, structMStationcommType *uState)
{
	if (!uState) return;
	unsigned char chksum;
    //-----------------------------------------------------------------------------
    //if the Packet state machine structure is not initialize then initialize it
    //-----------------------------------------------------------------------------
	if (uState->status!=PKT_ACQUIRING)
	{
        MStationcommresetState(uState, uState->state);
        uState->status=PKT_ACQUIRING;						//set status to indicate acquiring packet
        uState->state=0;
   	}

	if (uState->state>=uState->databuffersize)					//state exceed the max allocated defined buffer size
		MStationcommresetState(uState, uState->state);	//zapp

    //-----------------------------------------------------------------------------
    //Locate the current state, pick and check the character against the position
    //defined infor
	// {0x05, 0x0a, 0x37, 0x30, 0x30, 0x45, 0x32, 0x34, 0x39, 0x45, 0x46, 0xe6, 0x0a};
    //-----------------------------------------------------------------------------
    uState->databuffer[uState->state] = ch;	//stores it up
  	switch(uState->state)
  	{
        case 	0:	if (ch==uState->delimiter0)                 //first character must be the delimiter0 (sync1)
                        uState->state++;							//increment the state to point to next state
                    else
                     	MStationcommresetState(uState, uState->state);	//otherwise zapp
                    break;
        case 	12: if (ch==0x0a) 				//second character must be the delimiter1  (sync2)
                    {
                        uState->state++;
                        uState->pktSize = uState->state;		//Yes, assign the packet size variable
                        uState->databuffer[uState->pktSize] = 0x0;
						uState->dataptr = uState->databuffer+1;
						uState->dlength = uState->pktSize - 3;
						chksum = calculate_StationPacketChecksum(uState->dataptr, uState->dlength);
						if (chksum == uState->databuffer[11])
							uState->status = PKT_FOUND;
						else
							uState->status = PKT_CRCERROR;
                    }
                    else
                     	MStationcommresetState(uState, uState->state);	//otherwise zapp
                    break;
        default:    uState->state++;
                    break;
    }
}

