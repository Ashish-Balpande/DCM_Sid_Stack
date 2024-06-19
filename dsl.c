#include <inttypes.h>

//Xxx_StartProtocol(Std_ReturnType, Dcm_ProtocolType, uint16, uint16)

//Dcm_StartProtocol()

typedef uint8_t Std_ReturnType;
#define E_OK 1
#define E_NOK 0

//#define 10 DIAG_SESSION_CONTROL
//#define 11 ECU_RESET




Std_ReturnType PduR_DcmTransmit(uint8_t PduIdType, uint8_t *PduInfoType1)
{
    printf("\n\nIn DSL: \nThe PduIdType is : %x", PduIdType);

    printf("\nThe PduInfoType is : ");
    for(int i=0; i<8; i++)
    {
        printf("%.2x ", PduInfoType1[i]);
    }

    uint8_t pci_frame_id = PduInfoType1[0];
    uint8_t dlc_req = PduInfoType1[1];
    uint8_t sid = PduInfoType1[2];
    uint8_t sub_fun = PduInfoType1[3];

    printf("\nSID : %.2x", sid);
    valid_SID(sid);

    return E_OK;
}

void valid_SID(uint8_t sid, uint8_t sub_fun)
{
    switch(sid)
    {
    case 0x10:
        printf("\nDiagnostic Session Control Service...!");

        switch(sub_fun)
        {
        case 0x01:
            printf("\nDefault Session Activated...!");

            break;
        case 0x02:
            printf("\nProgramming Session Activated...!");

            break;
        case 0x03:
            printf("\nExtended Session Activated...!");

            break;
        default:
            printf("\n\nNRC: 0x12 - Subfunction not supported");
            break;
        }


        break;

    case 0x11:

        break;

    case 0x27:

        break;

    case 0x28:
        printf("\nCommunication Control Service...!");
        break;

    case 0x3E:
        printf("\nTester present Service...!");
        break;

    default:
        printf("\n\nNRC: 0x11 - Service not supported");

    }
}




