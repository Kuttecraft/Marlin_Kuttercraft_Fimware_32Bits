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
void crear_texto_centrado(PGM_P utf8_str_P, int altura = 0);

int centrar_texto(int numero);
int cantidad_de_digitos(int numero);
int rango_encoder(uint32_t valor_maximo, uint32_t valor_minimo = 0);
void crear_espera();
void salida_menu_ajuste();

//Espera hasta que termine el calculo de pid
void calcular_pid_03(){
    //NO se vuelve al status y se sigue actualizando
    MarlinUI::defer_return_to_status = true;
    MarlinUI::lcdDrawUpdate = LCDVIEW_CALL_REDRAW_NEXT;
    //crea la barra de espera
    crear_espera();

    crear_marco_superior(Language_es::MSG_POR_FAVOR_ESPERE,0,11);
    crear_marco_superior(Language_es::MSG_HEATING,55);

    //informacion de temperatura
    lcd_moveto(89, 29);
    lcd_put_u8str(i16tostr4signrj( int(thermalManager.degHotend(0)) )); //temp objectivo

    if(MarlinUI::salida_pid){
        (void)settings.save();
        (void)settings.load();
        queue.inject_P(PSTR("M117 PID GUARDADO"));
        MarlinUI::goto_screen(salida_menu_ajuste);
    }
}

//se selecciona la temperatura para ajustar el hotend
void calcular_pid_02(){
    MarlinUI::defer_return_to_status = true;
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
        //sprintf_P(cmd, PSTR("M303 C10 U1 S%s"), i16tostr4signrj(valor_mintero));
        
        
        MarlinUI::contenedor_str[0] = '\0'; //vacia la lista

        strcpy(MarlinUI::contenedor_str, PSTR("M106P2S225\nM303 C10 U1 S"));
        strcat(MarlinUI::contenedor_str, i16tostr4signrj(valor_mintero));

        SERIAL_ECHOLN(MarlinUI::contenedor_str);//imprime el valor en consola

        queue.inject_P(MarlinUI::contenedor_str);//ejecuta el comando


        MarlinUI::goto_screen(calcular_pid_03);
    }
}

//primer paso se elije la velocidad del fan de capa
void calcular_pid_01(){
    MarlinUI::defer_return_to_status = true;
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
        thermalManager.set_fan_speed(0, valor_mintero);
        MarlinUI::goto_screen(calcular_pid_02);
    }
}
void espera_home_pid(){
    MarlinUI::defer_return_to_status = true;
    MarlinUI::lcdDrawUpdate = LCDVIEW_CALL_REDRAW_NEXT;

    crear_texto_centrado(Language_es::MSG_AUTO_HOME_ACTION, 20);
    crear_espera();

    if(MarlinUI::home_en_accion){
        MarlinUI::goto_screen(calcular_pid_01);
    }
}

void calcular_pid(){
    MarlinUI::fan_prueba_pid = true;
    MarlinUI::salida_pid = false;
    MarlinUI::home_en_accion = false;
    queue.inject_P(PSTR("G28")); //centra la cama para un calculo mas preciso
    MarlinUI::goto_screen(espera_home_pid);
}
#endif
#endif
