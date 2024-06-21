#include "dsd.h"
#include "dsl.h"

uint8_t ext_flag=0, seed_req_flag=0, send_key_flag=0, read_did_flag=0;

Std_ReturnType verify_DLC()
{
    printf("\n\nIn DSD: ");

    uint8_t dlc_req = PduInfoType2[0];
    uint8_t sid = PduInfoType2[1];
    uint8_t sub_fun = PduInfoType2[2];

    //printf("\nSID : %.2x", sid);

    uint8_t dlc_check=0;
    for(int i=1; i<8; i++)
    {
        if(PduInfoType2[i]==0x00)
        {
            break;
        }
        dlc_check++;
    }

    printf("\ndlc_check : %.2x", dlc_check);
    if (dlc_req == dlc_check)
    {
        valid_SID(sid, sub_fun);
    }
    else
    {
        //printf("\n\nNRC: 0x13 - Incorrect Message Length");
        Response_Code(0x03, 0x7f, sid, 0x13, 0x00, 0x00, 0x00, 0x00);
    }
}


void valid_SID(uint8_t sid, uint8_t sub_fun)
{
    switch(sid)
    {
    case DIAG_SESSION_CONTROL:
        printf("\nDiagnostic Session Control Service...!");

        switch(sub_fun)
        {
        case DEFAULT_SESSION:
            printf("\nDefault Session Activated...!");
            break;
        case PROGRAMMING_SESSION:
            printf("\nProgramming Session Activated...!");
            break;
        case EXTENDED_SESSION:
            printf("\nExtended Session Activated...!\n");
            Response_Code(0x06, PduInfoType2[1]+0x40, 0x03, 0xaa, 0xaa, 0xbb, 0xbb, 0x00);

            ext_flag++;
            return E_OK;
            break;
        default:
            //printf("\n\nNRC: 0x12 - Subfunction not supported");
            Response_Code(0x03, 0x7f, DIAG_SESSION_CONTROL, 0x12, 0x00, 0x00, 0x00, 0x00);

            break;
        }
        break;

    case ECU_RESET:
        printf("\nECU Reset Service...!");
        break;

    case SECURITY_ACCESS:
        printf("\nSecurity Access Service...!\n");

        uint8_t key1 = 0x11;
        uint8_t key2 = 0x22;

        switch(sub_fun)
        {
        case LEVEL_1_SEED_REQ:
            printf("\nLevel 1 seed request...!\n");
            break;
        case LEVEL_1_SEND_KEY:
            printf("\nLevel 1 send key...!\n");
            break;
        case LEVEL_2_SEED_REQ:
            printf("\nLevel 2 seed request...!\n");
            if(ext_flag == 1)
            {
                Response_Code(0x06, 0x67, 0x03, key1, key2, 0x00, 0x00, 0x00);

                ext_flag = 0;
                seed_req_flag++;
                return E_OK;
            }
            else
            {
                //printf("NRC : 24 - Request Sequence Error\n");
                Response_Code(0x03, 0x7f, SECURITY_ACCESS, 0x24, 0x00, 0x00, 0x00, 0x00);
            }
            break;
        case LEVEL_2_SEND_KEY:
            printf("\nLevel 2 send key...!\n");
            if(seed_req_flag == 1)
            {
                if((PduInfoType2[3]==key2)&&(PduInfoType2[4]==key1))
                {
                    //printf("Positive Resp : 0x02\t0x67\t0x04\n\n");
                    Response_Code(0x02, 0x67, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00);

                    seed_req_flag=0;
                    send_key_flag++;
                    return E_OK;
                }
                else
                {
                    //printf("\n\nNRC: 0x35 - Invalid Key");
                    Response_Code(0x03, 0x7f, SECURITY_ACCESS, 0x35, 0x00, 0x00, 0x00, 0x00);
                }
            }
            else
            {
               //printf("NRC : 24\n");
               Response_Code(0x03, 0x7f, SECURITY_ACCESS, 0x24, 0x00, 0x00, 0x00, 0x00);
            }
            break;
        default:
            //printf("\n\nNRC: 0x12 - Subfunction not supported");
            Response_Code(0x03, 0x7f, SECURITY_ACCESS, 0x12, 0x00, 0x00, 0x00, 0x00);
            break;
        }
        break;

    case COMMUNICATION_CONTROL:
        printf("\nCommunication Control Service...!");
        break;

    case TESTER_PRESENT:
        printf("\nTester present Service...!");
        break;

    case READ_DATA_BY_ID:
        printf("\nRead Data by Identifier...!\n");
            if(send_key_flag == 1)
            {
                if((PduInfoType2[2] == 0xf1) && (PduInfoType2[3] == 0x90))
                {
                printf("positive response\n");
                //printf("Positive Resp : 0x06\t0x62\t0xF1\t0x90\t0x11\t0x12\t0x13\t0x14\n\n");
                Response_Code(0x06, 0x62, 0xF1, 0x90, 0x11, 0x12, 0x13, 0x00);

                send_key_flag = 0;
                read_did_flag++;
                }
                else if((PduInfoType2[2] == 0xf1) && (PduInfoType2[3] == 0x91))
                {
                printf("positive response\n");
                //printf("Positive Resp : 0x06\t0x62\t0xF1\t0x91\t0x14\t0x13\t0x12\t0x11\n\n");
                Response_Code(0x06, 0x62, 0xF1, 0x91, 0x14, 0x15, 0x16, 0x00);

                send_key_flag = 0;
                read_did_flag++;
                }
                else
                {
                    //printf("NRC : 31 - Request out of range\n");
                    Response_Code(0x03, 0x7f, READ_DATA_BY_ID, 0x31, 0x00, 0x00, 0x00, 0x00);
                }
                return E_OK;
            }
            else
            {
                //printf("NRC : 24\n");
                Response_Code(0x03, 0x7f, READ_DATA_BY_ID, 0x24, 0x00, 0x00, 0x00, 0x00);
            }

        break;

    default:
        //printf("\n\nNRC: 0x11 - Service not supported");
        Response_Code(0x03, 0x7f, sid, 0x11, 0x00, 0x00, 0x00, 0x00);
    }
}


