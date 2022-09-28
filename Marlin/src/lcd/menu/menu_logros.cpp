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
#include "../../module/motion.h"
#include "../../module/planner.h"
#include "../../MarlinCore.h"

#include "menu.h"
#include "../dogm/marlinui_DOGM.h"
#include "../mapa_bit/bitmap_kuttercraft.h"
#include "../../module/settings.h"


//constructores de menu
void init_boto(int medida_boton_, int espaciado_, int cantidad_, int altura_, int columna_bit_ = 3);
void crear_marco_superior(PGM_P utf8_str_P, int altura = 0, int largo = 9);
void crear_logro(PGM_P utf8_str_P_1, PGM_P utf8_str_P_2, PGM_P utf8_str_P_3);
void crear_descuento(PGM_P utf8_str_P_1, PGM_P utf8_str_P_2, PGM_P utf8_str_P_3);
void set_numero_de_descuento(int numero_de_descuento);
int valor_total_id();

//SALIDA
void menu_ajustes();
void menu_logros();

void no_hay_logros(){
    crear_marco_superior(Language_es::MSG_NO_LOGROS, 43, 11);
    crear_marco_superior(Language_es::MSG_TU_PUEDES, 53, 11);
    u8g.drawBitmapP(58, 14, 2, 15, no_logros_ico);

    if(ui.use_click()){
      MarlinUI::goto_screen(menu_ajustes, 3);
    }
}

void cupon_de_descuento_por_filamento(){
    init_boto(23, 2, 5, 2);//restablece el contador a 0

    crear_descuento("TEST", "10% ", Language_es::MSG_EN_FILAMENTO);
    crear_descuento("AWSD", "15% ", Language_es::MSG_EN_RESPUESTOS);
    crear_descuento("EDBA", "10% ", Language_es::MSG_EN_FILAMENTO);
    crear_descuento("BSAS", "",     Language_es::MSG_UN_ENVIO_GRATIS);
    crear_descuento("APEX", "5% ",  Language_es::MSG_EN_MAQUINAS);
    crear_descuento("BOOM", "25% ", Language_es::MSG_EN_GRILON3);
    crear_descuento("BOLO", "10% ", Language_es::MSG_EN_NUESTRA_TIENDA);
    crear_descuento("COSA", "15% ", Language_es::MSG_EN_INSUMOS);
    crear_descuento("DIAL", "10% ", Language_es::MSG_EN_NUESTRA_TIENDA);
    crear_descuento("DATA", "50% ", Language_es::MSG_SERVICIO_TECNICO);

    crear_descuento("DATO", "15% ", Language_es::MSG_EN_NUESTRA_TIENDA);
    crear_descuento("DEAL", "15% ", Language_es::MSG_EN_MAQUINAS);
    crear_descuento("FARO", "15% ", Language_es::MSG_EN_NUESTRA_TIENDA);
    crear_descuento("COPO", "20% ", Language_es::MSG_EN_NUESTRA_TIENDA);
    crear_descuento("CAPO", "15% ", Language_es::MSG_EN_MAQUINAS);
    crear_descuento("AAHH", "20% ", Language_es::MSG_EN_NUESTRA_TIENDA);
    crear_descuento("AULA", "20% ", Language_es::MSG_EN_NUESTRA_TIENDA);
    crear_descuento("AUWW", "20% ", Language_es::MSG_EN_NUESTRA_TIENDA);
    crear_descuento("XDXD", "20% ", Language_es::MSG_EN_MAQUINAS);
    crear_descuento("XPXS", "25% ", Language_es::MSG_EN_NUESTRA_TIENDA);

    crear_descuento("IOSX", "25% ", Language_es::MSG_EN_NUESTRA_TIENDA);
    crear_descuento("IOSX", "25% ", Language_es::MSG_EN_NUESTRA_TIENDA);
    crear_descuento("DIOS", "30% ", Language_es::MSG_EN_NUESTRA_TIENDA);

    if(ui.use_click()){
        MarlinUI::defer_return_to_status = false;
        if(MarlinUI::mostar_un_solo_logro != 0){
            (void)settings.save();
            MarlinUI::goto_screen(MarlinUI::status_screen);
        }else{
            (void)settings.save();
            MarlinUI::goto_screen(menu_logros, 1);
        }        
    }
}

void logros_por_filamento(){
    init_boto(23, 2, 5, 2);//restablece el contador a 0
    MarlinUI::defer_return_to_status = true;
    
    crear_logro(Language_es::MSG_KM_LOGRO_01_A, Language_es::MSG_KM_LOGRO_01_B, Language_es::MSG_FELICITACIONES);
    crear_logro(Language_es::MSG_KM_LOGRO_02_A, Language_es::MSG_KM_LOGRO_02_B, Language_es::MSG_FELICITACIONES);
    crear_logro(Language_es::MSG_KM_LOGRO_03_A, Language_es::MSG_KM_LOGRO_03_B, Language_es::MSG_FELICITACIONES);
    crear_logro(Language_es::MSG_KM_LOGRO_04_A, Language_es::MSG_KM_LOGRO_04_B, Language_es::MSG_FELICITACIONES);
    crear_logro(Language_es::MSG_KM_LOGRO_05_A, Language_es::MSG_KM_LOGRO_05_B, Language_es::MSG_FELICITACIONES);
    crear_logro(Language_es::MSG_KM_LOGRO_06_A, Language_es::MSG_KM_LOGRO_06_B, Language_es::MSG_FELICITACIONES);
    crear_logro(Language_es::MSG_KM_LOGRO_07_A, Language_es::MSG_KM_LOGRO_07_B, Language_es::MSG_FELICITACIONES);
    crear_logro(Language_es::MSG_KM_LOGRO_08_A, Language_es::MSG_KM_LOGRO_08_B, Language_es::MSG_FELICITACIONES);
    crear_logro(Language_es::MSG_KM_LOGRO_09_A, Language_es::MSG_KM_LOGRO_09_B, Language_es::MSG_FELICITACIONES);
    
    crear_logro(Language_es::MSG_KM_LOGRO_10_A, Language_es::MSG_KM_LOGRO_10_B, Language_es::MSG_FELICITACIONES);
    crear_logro(Language_es::MSG_KM_LOGRO_11_A, Language_es::MSG_KM_LOGRO_11_B, Language_es::MSG_FELICITACIONES);
    crear_logro(Language_es::MSG_KM_LOGRO_12_A, Language_es::MSG_KM_LOGRO_12_B, Language_es::MSG_FELICITACIONES);
    crear_logro(Language_es::MSG_KM_LOGRO_13_A, Language_es::MSG_KM_LOGRO_13_B, Language_es::MSG_FELICITACIONES);
    crear_logro(Language_es::MSG_KM_LOGRO_14_A, Language_es::MSG_KM_LOGRO_14_B, Language_es::MSG_FELICITACIONES);
    crear_logro(Language_es::MSG_KM_LOGRO_15_A, Language_es::MSG_KM_LOGRO_15_B, Language_es::MSG_FELICITACIONES);
    crear_logro(Language_es::MSG_KM_LOGRO_16_A, Language_es::MSG_KM_LOGRO_16_B, Language_es::MSG_FELICITACIONES);
    crear_logro(Language_es::MSG_KM_LOGRO_17_A, Language_es::MSG_KM_LOGRO_17_B, Language_es::MSG_FELICITACIONES);
    crear_logro(Language_es::MSG_KM_LOGRO_18_A, Language_es::MSG_KM_LOGRO_18_B, Language_es::MSG_FELICITACIONES);
    crear_logro(Language_es::MSG_KM_LOGRO_19_A, Language_es::MSG_KM_LOGRO_19_B, Language_es::MSG_FELICITACIONES);

    crear_logro(Language_es::MSG_KM_LOGRO_20_A, Language_es::MSG_KM_LOGRO_20_B, Language_es::MSG_FELICITACIONES);
    crear_logro(Language_es::MSG_KM_LOGRO_21_A, Language_es::MSG_KM_LOGRO_21_B, Language_es::MSG_FELICITACIONES);
    crear_logro(Language_es::MSG_KM_LOGRO_22_A, Language_es::MSG_KM_LOGRO_22_B, Language_es::MSG_FELICITACIONES);
    crear_logro(Language_es::MSG_KM_LOGRO_23_A, Language_es::MSG_KM_LOGRO_23_B, Language_es::MSG_FELICITACIONES);

    START_MENU();
    NEXT_ITEM_(MarlinUI::numero_de_logro_km);
    END_MENU();

    if(ui.use_click()){
        set_numero_de_descuento(encoderLine);
        MarlinUI::goto_screen(cupon_de_descuento_por_filamento);
    }
}

void cupon_de_descuento_por_piezas(){
    init_boto(23, 2, 5, 2);//restablece el contador a 0

    crear_descuento("TEST", "10% ",     Language_es::MSG_EN_FILAMENTO);
    crear_descuento("AWSD", "10% ",     Language_es::MSG_EN_RESPUESTOS);
    crear_descuento("EDBA", "12% ",     Language_es::MSG_EN_FILAMENTO);
    crear_descuento("BSAS", "12% ",     Language_es::MSG_EN_RESPUESTOS);
    crear_descuento("APEX", "15% ",     Language_es::MSG_EN_FILAMENTO);
    crear_descuento("BOOM", "15% ",     Language_es::MSG_EN_RESPUESTOS);
    crear_descuento("BOLO", "31.4% ",   Language_es::MSG_EN_BOQUILLAS);
    crear_descuento("COSA", "20% ",     Language_es::MSG_EN_RESPUESTOS);
    crear_descuento("DIAL", "20% ",     Language_es::MSG_EN_RESPUESTOS);
    crear_descuento("DATA", "10% ",     Language_es::MSG_EN_MAQUINAS);

    crear_descuento("DATO", "20% ",     Language_es::MSG_EN_RESPUESTOS);
    crear_descuento("DEAL", "15% ",     Language_es::MSG_EN_MAQUINAS);

    if(ui.use_click()){
        MarlinUI::defer_return_to_status = false;
        if(MarlinUI::mostar_un_solo_logro != 0){
            (void)settings.save();
            MarlinUI::goto_screen(MarlinUI::status_screen);
        }else{
            (void)settings.save();
            MarlinUI::goto_screen(menu_logros, 2);
        }        
    }
}

void logros_por_piezas(){
    init_boto(23, 2, 5, 2);//restablece el contador a 0
    MarlinUI::defer_return_to_status = true;

    crear_logro(Language_es::MSG_HAZ_IMPRESO, Language_es::MSG_PZ_LOGRO_01_A, Language_es::MSG_PZ_LOGRO_01_B);
    crear_logro(Language_es::MSG_HAZ_IMPRESO, Language_es::MSG_PZ_LOGRO_02_A, Language_es::MSG_PZ_LOGRO_02_B);
    crear_logro(Language_es::MSG_HAZ_IMPRESO, Language_es::MSG_PZ_LOGRO_03_A, Language_es::MSG_PZ_LOGRO_03_B);
    crear_logro(Language_es::MSG_HAZ_IMPRESO, Language_es::MSG_PZ_LOGRO_04_A, Language_es::MSG_PZ_LOGRO_04_B);
    crear_logro(Language_es::MSG_HAZ_IMPRESO, Language_es::MSG_PZ_LOGRO_05_A, Language_es::MSG_PZ_LOGRO_05_B);
    crear_logro(Language_es::MSG_HAZ_IMPRESO, Language_es::MSG_PZ_LOGRO_06_A, Language_es::MSG_PZ_LOGRO_06_B);
    crear_logro(Language_es::MSG_HAZ_IMPRESO, Language_es::MSG_PZ_LOGRO_07_A, Language_es::MSG_PZ_LOGRO_07_B);
    crear_logro(Language_es::MSG_HAZ_IMPRESO, Language_es::MSG_PZ_LOGRO_08_A, Language_es::MSG_PZ_LOGRO_08_B);
    crear_logro(Language_es::MSG_HAZ_IMPRESO, Language_es::MSG_PZ_LOGRO_09_A, Language_es::MSG_PZ_LOGRO_09_B);

    crear_logro(Language_es::MSG_HAZ_IMPRESO, Language_es::MSG_PZ_LOGRO_10_A, Language_es::MSG_PZ_LOGRO_10_B);
    crear_logro(Language_es::MSG_HAZ_IMPRESO, Language_es::MSG_PZ_LOGRO_11_A, Language_es::MSG_PZ_LOGRO_11_B);
    crear_logro(Language_es::MSG_HAZ_IMPRESO, Language_es::MSG_PZ_LOGRO_12_A, Language_es::MSG_PZ_LOGRO_12_B);


    START_MENU();
    NEXT_ITEM_(MarlinUI::numero_de_logro_pz);
    END_MENU();

    if(ui.use_click()){
        set_numero_de_descuento(encoderLine);
        MarlinUI::goto_screen(cupon_de_descuento_por_piezas);
    }
}

void hay_logro_de_km(){
    if(MarlinUI::numero_de_logro_km == 0){
        MarlinUI::goto_screen(no_hay_logros);
    }else{
        MarlinUI::goto_screen(logros_por_filamento);
    }
}

void hay_logro_de_pz(){
    if(MarlinUI::numero_de_logro_pz == 0){
        MarlinUI::goto_screen(no_hay_logros);
    }else{
        MarlinUI::goto_screen(logros_por_piezas);
    }
}

void menu_logros(){
    MarlinUI::ultimo_valor_ventana = menu_ajustes;
    MarlinUI::ultimo_valor_encoder = 3;
    MarlinUI::mostar_un_solo_logro = 0;

    START_MENU();
    BACK_ITEM(MSG_VOLVER);
    SUBMENU(MSG_LOGRO_KM, hay_logro_de_km);
    SUBMENU(MSG_LOGRO_PZ, hay_logro_de_pz);
    END_MENU();
}

#endif
#endif
