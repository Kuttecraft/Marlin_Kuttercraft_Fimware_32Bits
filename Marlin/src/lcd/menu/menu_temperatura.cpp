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
#include "../../module/temperature.h"
#include "../../MarlinCore.h"

#include "menu.h"
#include "../dogm/marlinui_DOGM.h"
#include "../mapa_bit/bitmap_kuttercraft.h"
#include "../../module/settings.h"

//constructores de menu
void init_boto(int medida_boton_, int espaciado_, int cantidad_, int altura_, int columna_bit_ = 3);
void crear_boton(const u8g_pgm_uint8_t* img_mapa_bit, const u8g_pgm_uint8_t* img_mapa_bit_2, PGM_P utf8_str_P, screenFunc_t screen, const uint16_t encoder = 0);
void crear_marco_superior(PGM_P utf8_str_P, int altura = 0, int largo = 9);
void encoder_der_sup(bool dereccion_encoder = true);

int centrar_texto(int numero);
int cantidad_de_digitos(int numero);
int rango_encoder(uint32_t valor_maximo, uint32_t valor_minimo = 0);

//salidas
void menu_main();
void temperatura_preset_manual();


//funciones
///////////

void temperatura_hotend(){
    encoder_der_sup(true);
    
    START_MENU();
    NEXT_ITEM_(281);
    END_MENU();
    
    int valor_mintero = rango_encoder(280, 0);

    crear_marco_superior(Language_es::MSG_SELECT);
    crear_marco_superior(Language_es::MSG_LA_TEMPERATURE, 8, 11);

    //texto temperatura:
    lcd_moveto(20, 42);
    lcd_put_u8str_P(PSTR(Language_es::MSG_NOZZLE));
    lcd_moveto(20 + (6*8), 42);
    lcd_put_u8str_P(PSTR(":"));

    //la cuenta es para centrar
    lcd_moveto(20 + (6*8), 42);
    lcd_put_u8str(i16tostr4signrj(valor_mintero));
    //salida y guardado
    if(ui.use_click()){
        thermalManager.setTargetHotend(valor_mintero, 0);
        MarlinUI::return_to_status();
    }

}

void temperatura_bed(){
    encoder_der_sup(true);
    
    START_MENU();
    NEXT_ITEM_(111);
    END_MENU();
    
    int valor_mintero = rango_encoder(110, 0);

    crear_marco_superior(Language_es::MSG_SELECT);
    crear_marco_superior(Language_es::MSG_LA_TEMPERATURE, 8, 11);

    //texto temperatura:
    lcd_moveto(16, 42);
    lcd_put_u8str_P(PSTR(Language_es::MSG_BED_HOT));
    lcd_moveto(16 + (6*13), 42);
    lcd_put_u8str_P(PSTR(":"));

    lcd_moveto(16 + (6*13), 42);
    lcd_put_u8str(i16tostr4signrj(valor_mintero));

    if(ui.use_click()){
        thermalManager.setTargetBed(valor_mintero);
        MarlinUI::return_to_status();
    }
}

void temperatura_fan(){
    encoder_der_sup(true);
    
    START_MENU();
    NEXT_ITEM_(101);
    END_MENU();
    int valor_mintero = rango_encoder(100, 0);

    crear_marco_superior(Language_es::MSG_SELECT);
    crear_marco_superior(Language_es::MSG_LA_TEMPERATURE, 8, 11);

    //texto temperatura:
    lcd_moveto(19, 42);
    lcd_put_u8str_P(PSTR(Language_es::MSG_FAN_SPEED));
    lcd_moveto(19 + (6*10), 42);
    lcd_put_u8str_P(PSTR(":"));

    lcd_moveto(19 + (6*10), 42);
    lcd_put_u8str(i16tostr4signrj(valor_mintero));

    if(ui.use_click()){
        valor_mintero = (valor_mintero * 255) / 100;
        thermalManager.fan_speed[0] = valor_mintero;
        MarlinUI::return_to_status();
    }

}

void enfriar_maquina(){                     //Enfriado
    thermalManager.setTargetHotend(0, 0);   //hotend    0
    thermalManager.setTargetBed(0);         //cama      0
    thermalManager.fan_speed[0] = 0;        //fan       0
    MarlinUI::return_to_status();           
}

void temperatura_manual(){
    crear_marco_superior(Language_es::MSG_TEMPERATURE);

    START_MENU();
    NEXT_ITEM_(5);
    END_MENU();

    init_boto(23, 2, 5, 21);

    crear_boton(boton_volver_a,   boton_volver_b,   Language_es::MSG_VOLVER,       temperatura_preset_manual,2);
    crear_boton(boton_hotend_a,   boton_hotend_b,   Language_es::MSG_NOZZLE,       temperatura_hotend,  int(thermalManager.degTargetHotend(0)));
    crear_boton(boton_cama_a,     boton_cama_b,     Language_es::MSG_BED_HOT,      temperatura_bed,     int(thermalManager.degTargetBed()));
    crear_boton(boton_fan_a,      boton_fan_b,      Language_es::MSG_FAN_SPEED,    temperatura_fan,     int((thermalManager.fan_speed[0] * 100) / 255));
    crear_boton(boton_enfriar_a,  boton_enfriar_b,  Language_es::MSG_COOLDOWN,     enfriar_maquina);
}

void temperatura_preset_pla(){
    thermalManager.setTargetHotend(190, 0);

    thermalManager.setTargetBed(60);
    MarlinUI::return_to_status();
}

void temperatura_preset_abs(){
    thermalManager.setTargetHotend(230, 0);

    thermalManager.setTargetBed(80);
    MarlinUI::return_to_status();
}

void temperatura_preset_flex(){
    thermalManager.setTargetHotend(220, 0);

    thermalManager.setTargetBed(70);
    MarlinUI::return_to_status();
}

void temperatura_preset_nylon(){
    thermalManager.setTargetHotend(240, 0);

    thermalManager.setTargetBed(85);
    MarlinUI::return_to_status();
}

void temperatura_preset(){
    crear_marco_superior(Language_es::MSG_PREDETERMINADO);

    START_MENU();
    NEXT_ITEM_(5);
    END_MENU();

    init_boto(23, 2, 5, 21);

    crear_boton(boton_volver_a,  boton_volver_b, Language_es::MSG_VOLVER,           temperatura_preset_manual,1);
    crear_boton(boton_pla_a,     boton_pla_b,    Language_es::MSG_PRESET_PLA,       temperatura_preset_pla);
    crear_boton(boton_abs_a,     boton_abs_b,    Language_es::MSG_PRESET_ABS,       temperatura_preset_abs);
    crear_boton(boton_flex_a,    boton_flex_b,   Language_es::MSG_PRESET_FLEX,      temperatura_preset_flex);
    crear_boton(boton_nylon_a,   boton_nylon_b,  Language_es::MSG_PRESET_NYLON,     temperatura_preset_nylon);
}

void temperatura_preset_manual(){
    const bool esta_imprimiendo = printingIsActive();

    crear_marco_superior(Language_es::MSG_TEMPERATURE);

    START_MENU();
    NEXT_ITEM_(3);
    END_MENU();

    init_boto(30, 5, 3, 17, 4);
    if(!esta_imprimiendo && !printingIsPaused()){
        crear_boton(volver_boton_a,      volver_boton_b,        Language_es::MSG_VOLVER,            menu_main,  3);
    }else{
        crear_boton(volver_boton_a,      volver_boton_b,        Language_es::MSG_VOLVER,            menu_main,  1);
    }
    crear_boton(temp_preset_boton_a, temp_preset_boton_b,   Language_es::MSG_PREDETERMINADO,    temperatura_preset);
    crear_boton(temp_manual_boton_a, temp_manual_boton_b,   Language_es::MSG_MANUALES,          temperatura_manual);
}

#endif // MENU_KUTTERCRAFT
#endif // HAS_LCD_MENU