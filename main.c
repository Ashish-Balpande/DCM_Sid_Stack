#include "main.h"

typedef uint8_t Std_ReturnType;
#define E_OK 1
#define E_NOK 0

uint8_t PduInfoType[8];                    //12 12 23 45 67 85 8b ab   //00

void main()
{
    printf("Enter the Elements (in hex formate): ");
    for(int i=0; i<8; i++)
    {
        scanf("%x", &PduInfoType[i]);
    }

    printf("\nIn Main: \nThe above SDU is : ");
    for(int i=0; i<8; i++)
    {
        printf("%.2x ", PduInfoType[i]);
    }

    uint8_t PduIdType = PduInfoType[0];

    Std_ReturnType result = PduR_DcmTransmit(PduIdType, &PduInfoType[0]);

    if(result == 1)
    {
        printf("\nResult : E_OK");
    }
    else
    {
        printf("\nResult : E_NOK");
    }

}
//id | dlc
//PCI_INFO  DLC_Req SID SF
//12 12 23 45 67 85 8b ab
//00 02 3E 03 00 00 00 00

//Std_ReturnType  PduR_DcmTransmit(Std_ReturnType, PduIdType, const PduInfoType*):
//Dcm_TpRxIndication(PduIdType, Std_ReturnType);
