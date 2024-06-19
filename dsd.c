


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

