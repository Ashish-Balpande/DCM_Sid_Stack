#include "dsl.h"
#include "main.h"

Std_ReturnType Dcm_RxIndication(uint8_t *PduInfoType)
{
    printf("\n\nIn DSL: \nThe PduInfoType is : ");
    for(int i=0; i<8; i++)
    {
        PduInfoType2[i] = PduInfoType[i];       //STORE THE FRAME IN BUFFER`
        printf("%.2x ", PduInfoType[i]);
    }

    Std_ReturnType result = verify_DLC();
    display_Result(result);
}

void Response_Code(uint8_t e0, uint8_t e1, uint8_t e2, uint8_t e3, uint8_t e4, uint8_t e5, uint8_t e6, uint8_t e7)
{
    Response[0]= e0; //DLC_SDU
    Response[1]= e1; //SID
    Response[2]= e2; //SubFun
    Response[3]= e3; //
    Response[4]= e4; //
    Response[5]= e5; //
    Response[6]= e6; //
    Response[7]= e7; //

    printf("\n-----------------------------------------------\n");
    if(Response[1] != NEGETIVE_RESPONSE_ID)
    {
        printf("POSSITIVE RESPONSE :    ");
    }
    else
    {
        printf("NEGETIVE RESPONSE :     ");
    }

    Send_Response(Response);
}

void Send_Response(uint8_t Response[])
{
    for(int i=0; i<8; i++)
    {
        printf("%.2x ", Response[i]);
    }
    printf("\n-----------------------------------------------\n\n");

}









