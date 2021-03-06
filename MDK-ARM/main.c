/*
 * IAP: in application program tools
 * Usaging X/Y/Zmodem protocol
 */

#include "iap.h"
#include "common.h"

int main(void)
{
	IAP_Init();
	
	while(1) {
		switch (IAP_ReadFlag()) {
        case APPRUN_FLAG_DATA:
            /* Jump into app */
            if (IAP_RunApp())
                IAP_WriteFlag(INIT_FLAG_DATA);
            break;
        case INIT_FLAG_DATA:
            /* Initialze state (blank mcu) */
            IAP_Main_Menu();
            break;
        case UPDATE_FLAG_DATA:
            /* Download app state */
            if (!IAP_Update())
                IAP_WriteFlag(APPRUN_FLAG_DATA);
            else
                IAP_WriteFlag(INIT_FLAG_DATA);
            break;
        case UPLOAD_FLAG_DATA:
            /* Upload app state */
            /*
            if( !IAP_Upload())
                IAP_WriteFlag(APPRUN_FLAG_DATA);
            else
                IAP_WriteFlag(INIT_FLAG_DATA);
            */
            break;
        case ERASE_FLAG_DATA:
            /* Erase app state */
            IAP_Erase();
            IAP_WriteFlag(INIT_FLAG_DATA);
            break;
        default:
            break;
		}
	}
}
