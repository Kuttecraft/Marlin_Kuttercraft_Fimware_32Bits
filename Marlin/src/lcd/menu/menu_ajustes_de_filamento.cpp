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
void crear_caja_texto_caja(PGM_P utf8_str_P, int altura = 0, int largo = 11);
void crear_caja_texto_marco(PGM_P utf8_str_P, int altura = 0, int largo = 11);
void menu_list_layer(PGM_P utf8_str_P, int numero_boton_id_ = 0, int numero_posiciones = 0);
void encoder_der_sup(bool dereccion_encoder = true);
void removeSpacesInPlace(char* str);
void crear_espera();

int centrar_texto(int numero, int grande_de_letra = 6);
int cantidad_de_digitos(int numero);
int cantidad_de_digitos_long(long numero);
int rango_encoder(uint32_t valor_maximo, uint32_t valor_minimo = 0);

//salidas de menus
void menu_main();
void ajuste_de_filamento();
void cargar_y_retirar_filamento();

int contador_repeticiones = 0;


//funciones
////////////////////////////////////////
float obtener_valor_actual_e(){
    //encargado de mostrar la posicion actual real del eje z
    get_cartesian_from_steppers();
    xyze_pos_t npos = cartes;
    const xyze_pos_t lpos = npos.asLogical();

    return lpos.e;
}

//Enumerador de comando a ejecutar
int contador_de_comando = 0;

void cargar_filamento_visual(){
    //NO se vuelve al status y se sigue actualizando
    MarlinUI::defer_return_to_status = true;
    MarlinUI::lcdDrawUpdate = LCDVIEW_CALL_REDRAW_NEXT;

    contador_repeticiones++;

    if(!queue.has_commands_queued()){
        switch (contador_de_comando) {
            case 0: queue.inject_P(PSTR("G92 E0"));            SERIAL_ECHOLN("1"); contador_de_comando++; break;
            case 1: queue.inject_P(PSTR("G1 E100 F200"));      SERIAL_ECHOLN("2"); contador_de_comando++; break;
            //case 2: queue.inject_P(PSTR("G92 E0"));            SERIAL_ECHOLN("3"); contador_de_comando++; break;
        }
    }

    //crea la barra de espera
    crear_espera();

    crear_marco_superior(Language_es::MSG_CARGANDO_FILAMENTO,0,11);
    crear_marco_superior(Language_es::MSG_POR_FAVOR_ESPERE, 54, 11);
    
    //Obtiene el valor actual del e
    xyze_pos_t npos = cartes;
    npos.e = planner.get_axis_position_mm(E_AXIS);

    if(npos.e >= 100){
        queue.inject_P(PSTR("G92 E0"));
        MarlinUI::goto_screen(cargar_y_retirar_filamento, 1);
    }
}
/*
;posicionamiento absoluto
G90
;establecer el extrusor en modo absoluto
M82
;Apaga el fan de capa 
M107
;lleva el eje al inicio
G28
;Se mueve a esa posición
G1 X5 Y5 Z15 F3000
G1 Z15.0 F9000
;El eje E esta en cero
G92 E0
;extruye 10mm
G1 F200 E10
G92 E0
;Guardad esa velocidad
G1 F9000
;imprime en el LCD
M117 Imprimiendo...
*/
void cargar_filamento(){
    contador_de_comando = 0;
    MarlinUI::goto_screen(cargar_filamento_visual);
    //hola mundo 
}

void retirar_filamento_visual(){
    //NO se vuelve al status y se sigue actualizando
    MarlinUI::defer_return_to_status = true;
    MarlinUI::lcdDrawUpdate = LCDVIEW_CALL_REDRAW_NEXT; 

    contador_repeticiones++;

    //ejecutor de comando
    if(!queue.has_commands_queued()){
        switch (contador_de_comando) {
            case 0: queue.inject_P(PSTR("G92 E0"));         contador_de_comando++; break;
            case 1: queue.inject_P(PSTR("G1 E30 F200"));    contador_de_comando++; break;
            case 2: queue.inject_P(PSTR("G92 E0"));         contador_de_comando++; break;
            case 3: queue.inject_P(PSTR("G1 E-100 F200"));  contador_de_comando++; break;
        }
    }

    //crea la barra de espera
    crear_espera();
    crear_marco_superior(Language_es::MSG_POR_FAVOR_ESPERE, 54, 11);

    //Obtiene el valor actual del e
    xyze_pos_t npos = cartes;
    npos.e = planner.get_axis_position_mm(E_AXIS);

    if(npos.e >= 1){
        crear_marco_superior(Language_es::MSG_CARGANDO_FILAMENTO,0,11);
    }else{
        crear_marco_superior(Language_es::MSG_RETIRANDO_FILAMENTO,0,11);
    }

    if(npos.e <= -100){
        queue.inject_P(PSTR("G92 E0"));
        MarlinUI::goto_screen(cargar_y_retirar_filamento, 2);
    }
}

void retirar_filamento(){
    contador_de_comando = 0;
    MarlinUI::goto_screen(retirar_filamento_visual);
}

void cargar_y_retirar_filamento(){
    encoder_der_sup(true);
    contador_repeticiones = 0; //reset
    crear_marco_superior(Language_es::MSG_CARGA_Y_DESCARGA);

    START_MENU();
    NEXT_ITEM_(3);
    END_MENU();

    init_boto(30, 5, 3, 17, 4);

    crear_boton(volver_boton_a,  volver_boton_b,    Language_es::MSG_VOLVER,           menu_main,2);
    crear_boton(cargar_boton_a,  cargar_boton_b,    Language_es::MSG_FILAMENTLOAD,     cargar_filamento);
    crear_boton(retirar_boton_a, retirar_boton_b,   Language_es::MSG_FILAMENTUNLOAD,   retirar_filamento);
}

bool salida_de_menu = true;

void ajuste_de_filamento_espera(){
    //NO se vuelve al status y se sigue actualizando
    MarlinUI::defer_return_to_status = true;
    MarlinUI::lcdDrawUpdate = LCDVIEW_CALL_REDRAW_NEXT;
    //crea la barra de espera
    crear_espera();

    crear_marco_superior(Language_es::MSG_POR_FAVOR_ESPERE,0,11);
    crear_marco_superior(Language_es::MSG_HEATING,55);

    //informacion de temperatura
    lcd_moveto(89, 29);
    lcd_put_u8str(i16tostr4signrj( int(thermalManager.degTargetHotend(0)) )); //temp objectivo
    lcd_moveto(89, 29);
    lcd_put_u8str_P(PSTR("/"));//separador
    lcd_moveto(64, 29);
    lcd_put_u8str(i16tostr4signrj(thermalManager.degHotend(0)));// temp actual

    //Ejecutor de comandos:
    if (!all_axes_homed()){
        
        if(!queue.has_commands_queued()){
            switch (contador_de_comando) {
                case 0: salida_de_menu = false;                 contador_de_comando++; SERIAL_ECHOLN("0"); break;
                case 1: queue.inject_P(PSTR("G91"));            contador_de_comando++; SERIAL_ECHOLN("0"); break;
                case 2: queue.inject_P(PSTR("G1 Z20 F1000"));   contador_de_comando++; SERIAL_ECHOLN("1"); break;
                case 3: queue.inject_P(PSTR("G90"));            contador_de_comando++; SERIAL_ECHOLN("2"); break;
                case 4: queue.inject_P(PSTR("G92 E0"));         contador_de_comando++; SERIAL_ECHOLN("3"); break;
                case 5: salida_de_menu = true;                  contador_de_comando++; SERIAL_ECHOLN("4"); break;
            }
        }
    }


    if(int(thermalManager.degHotend(0)) >= int(thermalManager.degTargetHotend(0)) - 5 && salida_de_menu){
        MarlinUI::goto_screen(cargar_y_retirar_filamento, 0);
    }
}

void preset_pla(){
    thermalManager.setTargetHotend(190, 0);
    MarlinUI::goto_screen(ajuste_de_filamento_espera);
}
void preset_abs(){
    thermalManager.setTargetHotend(230, 0);
    MarlinUI::goto_screen(ajuste_de_filamento_espera);
}
void preset_flex(){
    thermalManager.setTargetHotend(225, 0);
    MarlinUI::goto_screen(ajuste_de_filamento_espera);
}
void preset_nylon(){
    thermalManager.setTargetHotend(240, 0);
    MarlinUI::goto_screen(ajuste_de_filamento_espera);
}

void preset_temperaturas(){
    crear_marco_superior(Language_es::MSG_PREDETERMINADO);

    START_MENU();
    NEXT_ITEM_(5);
    END_MENU();

    init_boto(23, 2, 5, 21);

    crear_boton(boton_volver_a,  boton_volver_b, Language_es::MSG_VOLVER,           ajuste_de_filamento,149);
    crear_boton(boton_pla_a,     boton_pla_b,    Language_es::MSG_PRESET_PLA,       preset_pla);
    crear_boton(boton_abs_a,     boton_abs_b,    Language_es::MSG_PRESET_ABS,       preset_abs);
    crear_boton(boton_flex_a,    boton_flex_b,   Language_es::MSG_PRESET_FLEX,      preset_flex);
    crear_boton(boton_nylon_a,   boton_nylon_b,  Language_es::MSG_PRESET_NYLON,     preset_nylon);

}
//seleccione temperatura
void ajuste_de_filamento(){
    encoder_der_sup(true);
    START_MENU();
    NEXT_ITEM_(281);
    END_MENU();

    //establece un rango de movimiento para el encoder
    int valor_mintero = rango_encoder(280, 148);

    //SERIAL_ECHOLN(valor_mintero);

    crear_marco_superior(Language_es::MSG_SELECT);
    crear_marco_superior(Language_es::MSG_LA_TEMPERATURE, 8, 11);

    //texto temperatura:
    lcd_moveto(16, 45);
    lcd_put_u8str_P(PSTR(Language_es::MSG_TEMPERATURE));
    lcd_moveto(82, 45);
    lcd_put_u8str_P(PSTR(":"));

    //SALIDA
    if(valor_mintero == 148){
        lcd_moveto(88, 45);
        lcd_put_u8str_P(PSTR(Language_es::MSG_SALIR));

        if(ui.use_click()){
            MarlinUI::goto_screen(menu_main, 2);
        }
    //PRESET
    }else if (valor_mintero == 149){
        lcd_moveto(88, 45);
        lcd_put_u8str_P(PSTR(Language_es::MSG_PRESET));

        if(ui.use_click()){
            MarlinUI::goto_screen(preset_temperaturas);
        }
    //SELECCIONAR TEMPERATURA
    }else{
        lcd_moveto(64 + (cantidad_de_digitos(valor_mintero) * 6), 45);
        lcd_put_u8str(i16tostr4signrj(valor_mintero));

        if(ui.use_click()){
            thermalManager.setTargetHotend(valor_mintero, 0);
            //sube el eje si es desconocida la pocision
            MarlinUI::goto_screen(ajuste_de_filamento_espera);
        }
    }
    
}

//MENU del cambio de filamento mintras la impresora imprime
void _menu_filamento(){
    queue.inject_P(PSTR("M600"));
    MarlinUI::goto_screen(MarlinUI::status_screen);
}
//la idea es que haya un menu que me pueda agregar un cambio de filamento por capas
//va a ver dos opciones una lista de cambios y otra agregar un cabio, y el volver que esta por defecto
void redirigir_filamento();
void lista_de_cambio_capa();

//
int  numer_layer_list  = 0;
int aux_numero_layer = 0;

//axis_mon

//el maximo de cambios programables alcanzado
void max_layer_(){
    crear_marco_superior(Language_es::MSG_CAPA_ERROR_01);//Error de capa 
    crear_marco_superior(Language_es::MSG_CAPA_ERROR_02, 9, 9);//Maximo Alcanzado

    crear_marco_superior(Language_es::MSG_CLICK_PARA_SALIR, 55, 9);//Maximo Alcanzado
    if(ui.use_click()){
        MarlinUI::goto_screen(lista_de_cambio_capa, 2);
    }
}

void select_to_layer(){
    encoder_der_sup(true);

    START_MENU();
    NEXT_ITEM_(100000);
    END_MENU();

    long valor_mintero;

    //El maximo y minimo por capa//;
    //tiene en cuanta si no se puede ver el total de capas 
    if(MarlinUI::total_de_capas[0] == '\0'){
        if(MarlinUI::capa_actual[0] == '\0'){
            valor_mintero = rango_encoder(99999999, 2);
        }else{
            valor_mintero = rango_encoder(99999999, strtol(MarlinUI::capa_actual,NULL,10));
        }
    }else{
        if(MarlinUI::capa_actual[0] == '\0'){
            valor_mintero = rango_encoder(strtol(MarlinUI::total_de_capas,NULL,10), 2);
        }else{
            valor_mintero = rango_encoder(strtol(MarlinUI::total_de_capas,NULL,10), strtol(MarlinUI::capa_actual,NULL,10));
        }
    }

    if(ui.use_click()){
        //numero de lista actual
        //solo hay 20 puestos para guardar cambios de filamento
        if(numer_layer_list >= 19){
            MarlinUI::goto_screen(max_layer_, 2);
        }else{
            //filtra el valor
            strcpy(MarlinUI::contenedor_str, ltostr7(valor_mintero)); //guarda el valor en el contenedor
            removeSpacesInPlace(MarlinUI::contenedor_str); //elimina los espacios en blanco generado por la tranformacion
            
            //guarda el numero de capa en la lista de cambios
            strcpy(MarlinUI::list_layer[numer_layer_list + 1], MarlinUI::contenedor_str);

            //aumenta la pocicion
            numer_layer_list++;

            MarlinUI::goto_screen(lista_de_cambio_capa, 2);
        }
    }
    //texto
    crear_marco_superior(Language_es::MSG_CAPA_MSG_01);//Selecciones Una Capa 
    crear_marco_superior(Language_es::MSG_CAPA_MSG_02, 9, 9);//Para Cambio de Fila.

    lcd_moveto( centrar_texto( cantidad_de_digitos_long(valor_mintero) ), 45);

    strcpy(MarlinUI::contenedor_str, ltostr7(valor_mintero));
    removeSpacesInPlace(MarlinUI::contenedor_str);
    lcd_put_u8str(MarlinUI::contenedor_str);
}

void list_leyer_all();
//recore la lista eliminado el numero por caida
bool exit_layer_list = false;
void delte_layer_list(){
    int i;
    //empieza por el numero que hay que remplazar
    for (i = MarlinUI::layer_pointer_memory; i < 20; i++){
        strcpy(MarlinUI::list_layer[i], MarlinUI::list_layer[i + 1]);
    }
    MarlinUI::list_layer[19][0] = '\0';

    numer_layer_list--;
    if(exit_layer_list){
        //se vuelve al menu anterior pero a una posición mas arriba
        MarlinUI::goto_screen(list_leyer_all, MarlinUI::layer_pointer_memory -1);
    }
}
//

//muestra el listado de capas guardadas
void list_leyer_all(){
    START_MENU();
    NEXT_ITEM_(numer_layer_list + 1);
    END_MENU();

    exit_layer_list = true;
    
    //permite avanzar recien despues que se llega al limite
    if(encoderLine > 4){
        aux_numero_layer = encoderLine - 4;
    }else{
        aux_numero_layer = 0;
    }

    menu_list_layer(MarlinUI::list_layer[0 + aux_numero_layer], 0 + aux_numero_layer, 0);

    if(numer_layer_list > 0) menu_list_layer(MarlinUI::list_layer[1 + aux_numero_layer], 1 + aux_numero_layer, 1);
    if(numer_layer_list > 1) menu_list_layer(MarlinUI::list_layer[2 + aux_numero_layer], 2 + aux_numero_layer, 2);
    if(numer_layer_list > 2) menu_list_layer(MarlinUI::list_layer[3 + aux_numero_layer], 3 + aux_numero_layer, 3);
    if(numer_layer_list > 3) menu_list_layer(MarlinUI::list_layer[4 + aux_numero_layer], 4 + aux_numero_layer, 4);

    //salida
    if(ui.use_click()){
        if(encoderLine == 0) MarlinUI::goto_screen(lista_de_cambio_capa, 1);
        if(encoderLine != 0){
            MarlinUI::layer_pointer_memory = encoderLine;
            MarlinUI::goto_screen(delte_layer_list);
        }

    }
}

void lista_de_cambio_capa(){
    encoder_der_sup(true);
    crear_marco_superior(Language_es::MSG_FILAMENTCHANGE_CAPA);

    START_MENU();
    NEXT_ITEM_(3);
    END_MENU();

    init_boto(30, 5, 3, 17, 4);

    crear_boton(volver_boton_a,         volver_boton_b,         Language_es::MSG_VOLVER,         redirigir_filamento,2);
    crear_boton(lista_cambios_a,       lista_cambios_b,         Language_es::MSG_LIST_CAPA,      list_leyer_all);
    crear_boton(cambio_programado_a,    cambio_programado_b,    Language_es::MSG_ADD_CAPA,       select_to_layer); 
}

void redirigir_filamento(){
    encoder_der_sup(true);
    crear_marco_superior(Language_es::MSG_FILAMENTCHANGE);

    START_MENU();
    NEXT_ITEM_(3);
    END_MENU();

    init_boto(30, 5, 3, 17, 4);

    crear_boton(volver_boton_a,  volver_boton_b,    Language_es::MSG_VOLVER,                    menu_main,6);
    crear_boton(cambio_ahora_a,  cambio_ahora_b,    Language_es::MSG_FILAMENTCHANGE_NOW,        _menu_filamento);
    crear_boton(lista_cambios_a, lista_cambios_b,   Language_es::MSG_FILAMENTCHANGE_CAPA,       lista_de_cambio_capa);
}





#endif // MENU_KUTTERCRAFT
#endif // HAS_LCD_MENU