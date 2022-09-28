/**************************************************/
/*╔╗╔═╦╗ ╔╦════╦════╦═══╦═══╦═══╦═══╦═══╦═══╦════╗*/
/*║║║╔╣║ ║║╔╗╔╗║╔╗╔╗║╔══╣╔═╗║╔═╗║╔═╗║╔═╗║╔══╣╔╗╔╗║*/
/*║╚╝╝║║ ║╠╝║║╚╩╝║║╚╣╚══╣╚═╝║║ ╚╣╚═╝║║ ║║╚══╬╝║║╚╝*/
/*║╔╗║║║ ║║ ║║   ║║ ║╔══╣╔╗╔╣║ ╔╣╔╗╔╣╚═╝║╔══╝ ║║  */
/*║║║╚╣╚═╝║ ║║   ║║ ║╚══╣║║╚╣╚═╝║║║╚╣╔═╗║║    ║║  */
/*╚╝╚═╩═══╝ ╚╝   ╚╝ ╚═══╩╝╚═╩═══╩╝╚═╩╝ ╚╩╝    ╚╝  */
/*             ╔═╗                                */
/*             ║╔╝                                */
/*            ╔╝╚╦╦═╦╗╔╦╗╔╗╔╦══╦═╦══╗             */
/*            ╚╗╔╬╣╔╣╚╝║╚╝╚╝║╔╗║╔╣║═╣             */
/*             ║║║║║║║║╠╗╔╗╔╣╔╗║║║║═╣             */
/*             ╚╝╚╩╝╚╩╩╝╚╝╚╝╚╝╚╩╝╚══╝             */
/**************************************************/

#include "../../inc/MarlinConfigPre.h"

#if HAS_LCD_MENU
#if ENABLED(MENU_KUTTERCRAFT)

#include "menu_item.h"
#include "../../feature/babystep.h"
#include "../../MarlinCore.h"

void menu_main();

bool estado_del_led = false;

bool estado_actual_led(){
    return estado_del_led;
}

void prender_apagar_led(){
    const bool esta_imprimiendo = printingIsActive();

    if(estado_del_led){
        estado_del_led = false;
        #if (MOTHERBOARD == BOARD_BTT_SKR_V1_4_TURBO) || (MOTHERBOARD == BOARD_BTT_SKR_V1_4)
            WRITE(P2_04, LOW);
        #else
            WRITE(PB4, LOW);
        #endif

    }else{
        #if (MOTHERBOARD == BOARD_BTT_SKR_V1_4_TURBO) || (MOTHERBOARD == BOARD_BTT_SKR_V1_4)
            WRITE(P2_04, HIGH);
        #else
            WRITE(PB4, HIGH);
        #endif

        estado_del_led = true;
    }
    if(!esta_imprimiendo){
        //kuttercraft
        SERIAL_ECHOLN("Nuevo Offset:");//steps[BS_AXIS_IND(Z_AXIS)]
        SERIAL_ECHOLN(MarlinUI::offset_temporal);

        //babystep.add_steps(Z_AXIS, MarlinUI::offset_temporal);

        MarlinUI::goto_screen(menu_main, 5);
    }else{
        //kuttercraft
        SERIAL_ECHOLN("Nuevo Offset:");//steps[BS_AXIS_IND(Z_AXIS)]
        SERIAL_ECHOLN(MarlinUI::offset_temporal);

        //babystep.add_steps(Z_AXIS, MarlinUI::offset_temporal);

        MarlinUI::goto_screen(menu_main, 8);
    }
}

#endif // MENU_KUTTERCRAFT
#endif // HAS_LCD_MENU