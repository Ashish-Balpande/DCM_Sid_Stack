#include "main.h"

uint8_t PduInfoType[8];
Std_ReturnType Result;

void main()
{
    while(1)
    {
        Start();
    }
}

void Start()
{
    printf("\n\nEnter the Elements (in hex format): ");
    printf("\n-----------------------------------------------\n");
    printf("REQUEST :               ");
    for(int i=0; i<8; i++)
    {
        scanf("%x", &PduInfoType[i]);
    }
    printf("-----------------------------------------------");

    printf("\nIn MAIN: \nThe PduInfoType is : ");
    for(int i=0; i<8; i++)
    {
        printf("%.2x ", PduInfoType[i]);
    }

    Result = Dcm_RxIndication(&PduInfoType[0]);

    display_Result(Result);
}


void display_Result(uint8_t result)
{
    if(result == 1)
    {
        printf("Result : E_OK\n");
        Start();
    }
    else
    {
        printf("Result : E_NOT_OK\n");
    }
}

//Req Ext Ses :     02 10 03 00 00 00 00 00
//Req Seed :        02 27 03 00 00 00 00 00
//Send Key :        04 27 04 22 11 00 00 00
//DID Read req :    03 22 F1 90 00 00 00 00   //03 22 F1 91 00 00 00 00

//Std_ReturnType  PduR_DcmTransmit(Std_ReturnType, PduIdType, const PduInfoType*):
//Dcm_TpRxIndication(PduIdType, Std_ReturnType);

