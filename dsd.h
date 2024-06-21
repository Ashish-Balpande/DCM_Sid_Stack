#include <stdio.h>
#include <inttypes.h>

#define E_OK 1
#define E_NOT_OK 0

#define DIAG_SESSION_CONTROL 0x10
#define ECU_RESET 0x11
#define COMMUNICATION_CONTROL 0x28
#define SECURITY_ACCESS 0x27
#define TESTER_PRESENT 0x3E
#define READ_DATA_BY_ID 0X22
#define WRITE_DATA_BY_ID 0X2E

#define DEFAULT_SESSION 0x01
#define PROGRAMMING_SESSION 0x02
#define EXTENDED_SESSION 0x03
#define LEVEL_1_SEED_REQ 0x01
#define LEVEL_1_SEND_KEY 0x02
#define LEVEL_2_SEED_REQ 0x03
#define LEVEL_2_SEND_KEY 0x04

//typedef uint8_t Std_ReturnType;
