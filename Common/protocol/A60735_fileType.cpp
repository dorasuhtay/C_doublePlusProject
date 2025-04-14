#include "StdAfx.h"
#include <string.h>
#include "A60735_fileType.h"
#include "CRCCCITT.h"

const unsigned char A60735_1sync = 0xA6;	//'#'  1st delimiter
const unsigned char A60735_2sync = 0x07;	//     2nd delimiter
const unsigned char A60735_3sync = 0x35;	//     3rd delimiter
//-----------------------------------------------------------------------
//Wraps the mrt_A60735 packet (mutliplex comms)
// format: #ILLPn......
//         where # is the 1st delimiter 
//               I is the 2nd delimiter 
//               J is the 3rd delimiter 
//               L is length of data + port Xnet_cmd and port number
//               P is port Xnet_cmd character
//               n is the port number
//               . is the contained data
//PARAMETER: netcdata is the resultant mrt_A60735 formatted data (output)
//           data   is the data of szsize to be wrapped (input)
//           szsize is the size in bytes
//RETURN:    if greater than 0, the size of the packet (complete from start to end)
//           0 if no data
//           less than 0 if error (-1 no szsize, no data)
//-----------------------------------------------------------------------
/*
	unsigned char ipv4_1 = 192;
	unsigned char ipv4_2 = 168;
	unsigned char ipv4_3 = 2;
	unsigned char ipv4_4 = 73;
	unsigned short ipv4_port = 7123;
	unsigned char deviceprefix = 'L';			
	unsigned char device = 1;
	unsigned char dtype = 'C';
	int portnum = 7; 
	//unsigned char pktseq = 0;
	*/
int wrapmrt_A60735(const unsigned char *payload, unsigned short szsize, unsigned char *transport, unsigned char type, int lapse, unsigned short seqNo)
{
	unsigned char crchi, crclo;
	unsigned char spare = 0x00;
	int ptr = 0;
	int ii;
	transport[ptr] = A60735_1sync;					ptr++;
	transport[ptr] = A60735_2sync;					ptr++;
	transport[ptr] = A60735_3sync;					ptr++;
	transport[ptr] = type;							ptr++;
	for (ii=0;ii<10;ii++)
	{
		transport[ptr] = spare;						ptr++;
	}
	transport[ptr] = (unsigned char)(seqNo>>8);		ptr++;
	transport[ptr] = (unsigned char)seqNo;			ptr++;
	transport[ptr] = (unsigned char)(lapse>>24);	ptr++;
	transport[ptr] = (unsigned char)(lapse>>16);	ptr++;
	transport[ptr] = (unsigned char)(lapse>>8);		ptr++;
	transport[ptr] = (unsigned char)lapse;			ptr++;
	transport[ptr] = (unsigned char)(szsize>>8);	ptr++;
	transport[ptr] = (unsigned char)szsize;			ptr++;
	memcpy(transport+ptr, payload, szsize);			ptr+=szsize;
	CRC_CCITT(transport,  ptr, &crchi, &crclo);	//calculate the CRC16 checksum
	transport[ptr] = crchi;							ptr++;
	transport[ptr] = crclo;							ptr++;

	return ptr;

	/*
	unsigned char *sptr;
	int ii;
	unsigned char Hi=0;
	unsigned char Lo=0;
	if (!payload) return 0;
	if (!transport) return 0;
	if (szsize==0) return -1;									//nothing to wrap
	sptr = transport;
	*sptr++ = A60735_1sync;								//1st delimiter
	*sptr++ = A60735_2sync;	                             //2nd delimiter
	*sptr++ = A60735_3sync;	                             //3rd delimiter
	*sptr++ = dtype;									//Port Xnet_cmd is either P or C (P refers to port, C refers to CPU)
	*sptr++ = portnum;									//The device number or sub-port binary 0, 1, 2, 3, 4 etc... in ascii
	*sptr++ = ipv4_1;
	*sptr++ = ipv4_2;
	*sptr++ = ipv4_3;
	*sptr++ = ipv4_4;
	*sptr++ = (unsigned char)((ipv4_port>>8)&0x00FF); 	//length (MSB)
	*sptr++ = (unsigned char)(ipv4_port&0x00FF); 		//length (LSB)
	*sptr++ = deviceprefix;			
	*sptr++ = device;
	*sptr++ = pktseq;
	*sptr++ = (unsigned char)((szsize>>8)&0x00FF); 	//length (MSB)
	*sptr++ = (unsigned char)(szsize&0x00FF); 		//length (LSB)
	for (ii=0;ii<szsize;ii++)
  		*sptr++ = payload[ii];									//put the contained data into packet
	szsize+=16;		//include header size
	CRC_CCITT(transport,  szsize, &Hi, &Lo);	//calculate the CRC16 checksum
	transport[szsize++] = Hi;
	transport[szsize++] = Lo;
	transport[szsize] = 0;
    return szsize;
	*/
	/*
	unsigned char *sptr;
	int ii;
	if (!payload) return 0;
	if (!transport) return 0;
	if (szsize==0) return -1;									//nothing to wrap
	sptr = transport;
	*sptr++ = A60735_1sync;								//1st delimiter
	*sptr++ = A60735_2sync;	                             //2nd delimiter
	*sptr++ = A60735_3sync;	                             //3rd delimiter
	szsize+=2;														//length = datasize+dtype+portnum
	*sptr++ = (unsigned char)((szsize>>8)&0x00FF); 	//length (MSB)
	*sptr++ = (unsigned char)(szsize&0x00FF); 		//length (LSB)
	*sptr++ = dtype;									//Port Xnet_cmd is either P or C (P refers to port, C refers to CPU)
	//*sptr++ = '0' + portnum;									//The device number 1, 2, 3, 4 etc... in ascii
	*sptr++ = portnum;									//The device number or sub-port binary 0, 1, 2, 3, 4 etc... in ascii
    szsize-=2;
	for (ii=0;ii<szsize;ii++)
  		*sptr++ = payload[ii];										//put the contained data into packet
    return szsize+6;
	*/
}

//-----------------------------------------------------------------------
//A60735resetState() is used by the stream decoding statemachine
//to reset and start the state machine decoding again. This procedure is called
//when a stream, while being decoded does not match the mrt_A60735 format
// mrt_A60735 format: refer to Wrapmrt_A60735() or UnWrapmrt_A60735()
//PARAMETER: uState is the current state of the decoding and also the storage location
//                  where the state of the decoding process is stored
//           state  is the current state. Usually zero when reset unless there is an error
//                  state is the state at which the error occurs.
//           szsize is the size in bytes
//RETURN:    NIL
//-----------------------------------------------------------------------
void A60735resetState(structA60735_fileType *uState, int state)
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
        delimiter1 = uState->delimiter1;		//backup the value and restore it back later in this procedure
        delimiter2 = uState->delimiter2;		//backup the value and restore it back later in this procedure
//        ptr = uState->ptr;						//backup the value and restore it back later in this procedure
        memset(uState, 0x0, sizeof(structA60735_fileType));	//zap the whol structure
        uState->delimiter0 = delimiter0;		//restore the earlier backed up value
        uState->delimiter1 = delimiter1;		//restore the earlier backed up value
        uState->delimiter2 = delimiter2;		//restore the earlier backed up value
        uState->databuffersize = 	databuffersize;
        uState->databuffer = 	databuffer;
//        uState->ptr = ptr;						//restore the earlier backed up value
        uState->error = state;					//the state at which the error occurred
	}
}


//------------------------------------------------------------------------------------
//A60735StateMachine() is the stream decoding statemachine procedure  characters
//streaming in is passed to this function via the parameter "ch". The character
//is matched to the state at which the decode is at (i.e. the format's character
//position). if the character does not match the state at which it is at the state
//machine state held in "uState" is reset to begin again.
//mrt_A60735 format: refer to Wrapmrt_A60735() or UnWrapmrt_A60735()
//PARAMETER: uState is the current state of the decoding and also the storage location
//                  where the state of the decoding process is stored
//           ch     is the character passed into this function (input)
//RETURN:    NIL
//------------------------------------------------------------------------------------
void A60735StateMachine(unsigned char ch, structA60735_fileType *uState)
{
	if (!uState) return;

    //-----------------------------------------------------------------------------
    //if the Packet state machine structure is not initialize then initialize it
    //-----------------------------------------------------------------------------
	if (uState->status!=PKT_ACQUIRING)
	{
        A60735resetState(uState, uState->state);
        uState->status=PKT_ACQUIRING;						//set status to indicate acquiring packet
        uState->state=0;
   	}

	if (uState->state>=uState->databuffersize)					//state exceed the max allocated defined buffer size
		A60735resetState(uState, uState->state);	//zapp

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
                     	A60735resetState(uState, uState->state);	//otherwise zapp
                    break;
        case 	1:	if (ch==uState->delimiter1) 				//second character must be the delimiter1  (sync2)
                        uState->state++;							//increment the state to point to next state
                    else
                     	A60735resetState(uState, uState->state);	//otherwise zapp
                    break;
        case 	2:	if (ch==uState->delimiter2) 				//second character must be the delimiter1  (sync2)
                        uState->state++;							//increment the state to point to next state
                    else
                     	A60735resetState(uState, uState->state);	//otherwise zapp
                    break;

        case 	3:  //dtype
                    uState->dtype = ch  ;
                    uState->state++;							//increment the state to point to next state
                    break;
        case 	4:  //spare
        case 	5:  //spare
        case 	6:  //spare
        case 	7:  //spare
        case 	8:  //spare
        case 	9:  //spare
        case 	10: //spare
        case 	11: //spare
        case 	12: //spare
        case 	13: //spare
                    uState->spare1 = ch;
                    uState->state++;							//increment the state to point to next state
                    break;

        case 	14: //Length(MSB) of data
                    uState->state++;							//increment the state to point to next state
                    uState->seqno = ch;						//assign the length variable (number of characters to wait for)
                    uState->seqno <<= 8;
                    break;
        case 	15: //Length(LSB) of data
                    uState->state++;							//increment the state to point to next state
                    uState->seqno |= (unsigned short)ch &0xFF;						//assign the length variable (number of characters to wait for)
                    break;

        case 	16:  //lapse
					uState->lapse |= ((int)ch<<24);
                    uState->state++;							//increment the state to point to next state
					break;
        case 	17:  //lapse
					uState->lapse |= ((int)ch<<16);
                    uState->state++;							//increment the state to point to next state
					break;
		case 	18:  //lapse
					uState->lapse |= ((int)ch<<8);
                    uState->state++;							//increment the state to point to next state
					break;
        case 	19:  //lapse
					uState->lapse |= ((int)ch&0xFF);
                    uState->state++;	
					break;
 
        case 	20://Length(MSB) of data
                    uState->state++;							//increment the state to point to next state
                    uState->dlength = ch;						//assign the length variable (number of characters to wait for)
                    uState->dlength <<= 8;
                    break;
        case 	21://Length(LSB) of data
                    uState->state++;							//increment the state to point to next state
                    uState->dlength |= (unsigned short)ch &0xFF;						//assign the length variable (number of characters to wait for)
                    uState->length = uState->dlength;
                    if (uState->length<=0)
                        A60735resetState(uState, uState->state);	//otherwise zapp
					uState->payloadleft = uState->dlength;
                    break;
        default:    if (uState->dataptr==0)
					{
						uState->dataptr = uState->databuffer+uState->state;
						uState->payloadleft+=2;		//add checksum 2bytes
					}
					
					if (uState->payloadleft==1)
					{
						unsigned char Hi=0;
						unsigned char Lo=0;
						uState->pktSize = uState->state+1;		//Yes, assign the packet size variaable
						uState->databuffer[uState->pktSize] = 0x0;
                    	CRC_CCITT(uState->databuffer,  uState->pktSize-2, &Hi, &Lo);	//calculate the CRC16 checksum
                        if ((uState->databuffer[uState->pktSize-2]==Hi)&&(uState->databuffer[uState->pktSize-1]==Lo))
							uState->status = PKT_FOUND;				//     and indicate the status as found (complete)
                        else
							uState->status = PKT_CRCERROR;				//     and indicate the status as found (complete)
						/*
                        uState->pktSize = uState->state+1;		//Yes, assign the packet size variable
                        uState->databuffer[uState->pktSize] = 0x0;
                        uState->status = PKT_FOUND;	
						*/
					}
					if (uState->payloadleft<0)
					{
                        uState->status = PKT_ABORT;             //abort
                        A60735resetState(uState, uState->state);		//zapp
                        break;
					}
					uState->payloadleft--;
					uState->state++;								//increment the state to point to next state

/*

					uState->lnoffset = 3+(int)uState->dlength;			//determine the remaining number of states or characters before making a comletion decision
                    if (uState->state>uState->lnoffset)                 //something's wrong and cannot be such so...
                    {
                        uState->status = PKT_ABORT;             //abort
                        A60735resetState(uState, uState->state);		//zapp
                        break;
                  	}
                    if (uState->state==uState->lnoffset)                //Are all characters acquired?
                    {
                        uState->pktSize = uState->state+1;		//Yes, assign the packet size variable
                        uState->databuffer[uState->pktSize] = 0x0;
                        uState->status = PKT_FOUND;				//     and indicate the status as found (complete)
                    }
                    else
                        uState->state++;								//increment the state to point to next state
						*/
                    break;
    }
}


