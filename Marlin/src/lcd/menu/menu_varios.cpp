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
#include "../../module/probe.h"
#include "../../module/printcounter.h"
#include "../../sd/cardreader.h"

#include "../../gcode/gcode.h"


int16_t nuevo_flow = planner.flow_percentage[0];
int16_t nuevo_percentage = feedrate_percentage;
// el G61 no fuenciona como es debido por lo que busque otra solucion
xyze_pos_t valores_antes_pausa;
//debido al problema de no poder injectar comando muy largos cree una secuencia de ejecucion
int secuencia_ejecucion = 0;

//constructores de menu
void crear_boton(const u8g_pgm_uint8_t* img_mapa_bit, const u8g_pgm_uint8_t* img_mapa_bit_2, PGM_P utf8_str_P, screenFunc_t screen, const uint16_t encoder = 0);
void init_boto(int medida_boton_, int espaciado_, int cantidad_, int altura_, int columna_bit_ = 3);
void crear_marco_superior(PGM_P utf8_str_P, int altura = 0, int largo = 9);
void crear_texto_centrado(PGM_P utf8_str_P, int altura = 0);
void removeSpacesInPlace(char* str);
void crear_espera();

void menu_main();

////////
//flow//

//menu que muestra el valor del offset y permite cambiarlo.
void menu_modificar_flow(){
    //NO se vuelve al status y se sigue actualizando
    MarlinUI::defer_return_to_status = true;
    MarlinUI::lcdDrawUpdate = LCDVIEW_CALL_REDRAW_NEXT;

    crear_marco_superior(Language_es::MSG_FLOW_MENU,0,11);
    crear_marco_superior("",53,11);

    nuevo_flow = planner.flow_percentage[0] + int16_t(ui.encoderPosition);

    NOLESS(nuevo_flow, 10);
    NOMORE(nuevo_flow, 400);
  
    //ui.encoderPosition = 0;

    if (ui.should_draw()) {
        MarlinUI::contenedor_str[0] = '\0';

        strcpy(MarlinUI::contenedor_str, GET_TEXT(MSG_FLOW));
        strcat(MarlinUI::contenedor_str, ":");
        strcat(MarlinUI::contenedor_str, i16tostr3left(nuevo_flow));

        removeSpacesInPlace(MarlinUI::contenedor_str);

        crear_texto_centrado(MarlinUI::contenedor_str, 29);
    }

    if (ui.use_click()){
        planner.set_flow(0, nuevo_flow);
        MarlinUI::goto_screen(menu_main, 3);
    }
}
//flow//
////////

/////////////
//velocidad//

//permite cambiar la velocidad de movimento de la maquina
void menu_modificar_velocidad(){
    //NO se vuelve al status y se sigue actualizando
    MarlinUI::defer_return_to_status = true;
    MarlinUI::lcdDrawUpdate = LCDVIEW_CALL_REDRAW_NEXT;

    crear_marco_superior(Language_es::MSG_VELOCITY_MENU,0,11);
    crear_marco_superior("",53,11);

    nuevo_percentage = feedrate_percentage + int16_t(ui.encoderPosition);

    NOLESS(nuevo_flow, 10);
    NOMORE(nuevo_flow, 400);

    if (ui.should_draw()) {
        MarlinUI::contenedor_str[0] = '\0';

        strcpy(MarlinUI::contenedor_str, GET_TEXT(MSG_SPEED));
        strcat(MarlinUI::contenedor_str, ":");
        strcat(MarlinUI::contenedor_str, i16tostr3left(nuevo_percentage));

        removeSpacesInPlace(MarlinUI::contenedor_str);

        crear_texto_centrado(MarlinUI::contenedor_str, 29);
    }

    if (ui.use_click()){
        feedrate_percentage = nuevo_percentage;
        MarlinUI::goto_screen(menu_main, 7);
    }
}

//velocidad//
/////////////

/////////////////
//cancelar menu//
void esperando_reanudar();

uint16_t aux_hotend_temperatura = 0;
uint16_t aux_cama_temperatura = 0;
int contador_de_vueltas = 0;
bool modo_pausa = false;

//ejecuta unos comando despues de cancelar
void espera_cancelacion_posicion(){
    get_cartesian_from_steppers();
    //xyze_pos_t npos = cartes;
    //const xyze_pos_t lpos = npos.asLogical();

    //visual
    MarlinUI::defer_return_to_status = true;
    MarlinUI::lcdDrawUpdate = LCDVIEW_CALL_REDRAW_NEXT;

    crear_marco_superior(PSTR(Language_es::MSG_PRINT_CANCELANDO), 0, 11);
    crear_texto_centrado(Language_es::MSG_MEDIA_ABORTING, 20);
    crear_marco_superior(PSTR(Language_es::MSG_POR_FAVOR_ESPERE), 53, 11);

    crear_espera();

    if((true) || modo_pausa){
        contador_de_vueltas += 1;

        //Levanta el eje Z
        if(contador_de_vueltas == 10){
            queue.enqueue_now_P(PSTR("G91"));
            queue.enqueue_now_P(PSTR("G1 Z20 F1000"));
            queue.enqueue_now_P(PSTR("G90"));
        }

        //espera a que el comando anterior se ejecute
        if(contador_de_vueltas >= 250){
            //envio un mensaje al usuario
            queue.enqueue_now_P(PSTR("M117 Impresion Cancelada"));
            
            MarlinUI::contenedor_str[0] = '\0';//borra la cadena

            //crea un M104 con la temperatura objetivo anterior
            strcpy(MarlinUI::contenedor_str, "M104 S");
            strcat(MarlinUI::contenedor_str, i16tostr4signrj(int(aux_hotend_temperatura)));
            removeSpacesInPlace(MarlinUI::contenedor_str);

            queue.enqueue_one_now(MarlinUI::contenedor_str);//Ejecuta ese comando ya!
            
            //Se repite lo mismo para la temperatura de cama
            MarlinUI::contenedor_str[0] = '\0';

            strcpy(MarlinUI::contenedor_str, "M140 S");
            strcat(MarlinUI::contenedor_str, i16tostr4signrj(int(aux_cama_temperatura)));
            removeSpacesInPlace(MarlinUI::contenedor_str);

            queue.enqueue_one_now(MarlinUI::contenedor_str);

            //Se obtiene los valores maximo y minimo del eje
            float min, max;
            soft_endstop.get_manual_axis_limits(Y_AXIS, min, max);
            
            char str_Y[16]; 
            MarlinUI::contenedor_str[0] = '\0'; //vacia la lista
            
            sprintf_P(MarlinUI::contenedor_str, PSTR("G1 Y%s F3000\nM84"), dtostrf(max - 20, 1, 3, str_Y));

            queue.enqueue_one_now(PSTR(MarlinUI::contenedor_str));
            
            MarlinUI::return_to_status();//Salida
        }
    }
}

void espera_de_cancelacion(){
    //menu visual
    secuencia_ejecucion = 0;
    MarlinUI::defer_return_to_status = true;
    MarlinUI::lcdDrawUpdate = LCDVIEW_CALL_REDRAW_NEXT;

    crear_marco_superior(PSTR(Language_es::MSG_PRINT_CANCELANDO), 0, 11);
    crear_texto_centrado(Language_es::MSG_MEDIA_ABORTING, 20);
    crear_marco_superior(PSTR(Language_es::MSG_POR_FAVOR_ESPERE), 53, 11);

    //espera al ingreso del comando

    if(!queue.has_commands_queued()){
        //queue.enqueue_one_P(PSTR("G1 X5 Y5 F1500"));
        MarlinUI::goto_screen(espera_cancelacion_posicion);
    }    
}

//cancela la imprecion y espera a que se cansela
void cancelar_imprecion_valores(){
    aux_hotend_temperatura = thermalManager.degTargetHotend(0); //
    aux_cama_temperatura = thermalManager.degTargetBed();       //guarda la temperatura antes de canselar

    //se ejetuta un delay por tik
    contador_de_vueltas = 0;

    //esto evita la espera de 109 y 190
    thermalManager.setTargetHotend(0, 0);
    thermalManager.setTargetBed(0);

    //cancela la impresion
    if (IS_SD_PRINTING()){
        card.flag.abort_sd_printing = true;
    }else if (card.isMounted()){
        card.closefile();
    }

    MarlinUI::goto_screen(espera_de_cancelacion);
}


//en caso de que se encuentre en pausa mientras se cansela la imprecion
//salimos del modo pausa (para evitar errores)
void cancelar_comando(){
    if(printingIsPaused()){
        modo_pausa = true;
        MarlinUI::goto_screen(esperando_reanudar); //pausa menu
    }else{
        modo_pausa = false;
        MarlinUI::goto_screen(cancelar_imprecion_valores);
    }
    
}

//menu de cancelar imprecion si o no
void cancelar_imprecion(){
    crear_marco_superior(PSTR(Language_es::MSG_BUTTON_ADVERTENCIA), 0, 11); //advercencia
    crear_marco_superior(PSTR(Language_es::MSG_PRINT_CANCELAR), 11, 11); //reiniciar impresora

    init_boto(23, 2, 2, 27);

    START_MENU();
    NEXT_ITEM_(2);
    END_MENU();

    crear_boton(boton_x_a,           boton_x_b,           Language_es::MSG_BUTTON_CANCEL,    menu_main, 4);
    crear_boton(boton_reanudar_a,    boton_reanudar_b,    Language_es::MSG_PRINT_CANCELAR,   cancelar_comando);//reiniciar impresora
}
//cancelar menu//
/////////////////

//////////////
//menu pausa//

void esperando_reanudar(){
    MarlinUI::defer_return_to_status = true;
    MarlinUI::lcdDrawUpdate = LCDVIEW_CALL_REDRAW_NEXT;
    //
    char str_X[16], str_Y[16], str_Z[16], str_E[16];
    MarlinUI::contenedor_str[0] = '\0'; //vacia la lista

    //visual
    crear_marco_superior(PSTR(Language_es::MSG_FILAMENT_CHANGE_HEADER_PAUSE), 0, 11);
    crear_marco_superior(PSTR(Language_es::MSG_POR_FAVOR_ESPERE), 53, 11);
    crear_espera();
    
    if(secuencia_ejecucion == 0){
        if(!queue.has_commands_queued()){
            queue.inject_P(PSTR("G91\nG1 E15 F300\nG90"));
            secuencia_ejecucion = 1;
        }
    }
    if(secuencia_ejecucion == 1){
        if(!queue.has_commands_queued()){
            queue.inject_P(PSTR("G91\nG1 Z-5 F1000\nG90"));
            secuencia_ejecucion = 2;
        }
    }
    if(secuencia_ejecucion == 2){
        if(!queue.has_commands_queued()){
            queue.inject_P(PSTR("G1 F3000"));
            secuencia_ejecucion = 3;
        }
    }
    //G91\nG1 Z5 E-5 F1000\nG90
    if(secuencia_ejecucion == 3){
        if(!queue.has_commands_queued()){
            //crea un comando de retorno
            sprintf_P(MarlinUI::contenedor_str, PSTR("G1 X%s Y%s Z%s F3000"),
                dtostrf(valores_antes_pausa.x, 1, 3, str_X),
                dtostrf(valores_antes_pausa.y, 1, 3, str_Y),
                dtostrf(valores_antes_pausa.z, 1, 3, str_Z)
            );
            queue.inject_P(PSTR(MarlinUI::contenedor_str));
            secuencia_ejecucion = 4;
        }
    }
    if(secuencia_ejecucion == 4){
        MarlinUI::contenedor_str[0] = '\0'; //vacia la lista
        sprintf_P(MarlinUI::contenedor_str, PSTR("G92 E%s\nM24"),
                dtostrf(valores_antes_pausa.e, 1, 3, str_E)
            );
        queue.inject_P(PSTR(MarlinUI::contenedor_str));

        if(modo_pausa){
            MarlinUI::goto_screen(cancelar_imprecion_valores);//entra en el menu de cancelacion
        }else{
            MarlinUI::goto_screen(menu_main, 5);//salida
        }

    }
        
}


void esperando_pausa(){
    //NO se vuelve al status y se sigue actualizando
    MarlinUI::defer_return_to_status = true;
    MarlinUI::lcdDrawUpdate = LCDVIEW_CALL_REDRAW_NEXT;

    crear_marco_superior(PSTR(Language_es::MSG_FILAMENT_CHANGE_HEADER_PAUSE), 0, 11);
    //crear_texto_centrado(Language_es::MSG_MEDIA_ABORTING, 20);
    crear_marco_superior(PSTR(Language_es::MSG_POR_FAVOR_ESPERE), 53, 11);
    //crea la barra de espera
    crear_espera();
    
    if(!queue.has_commands_queued()){
        //guarda la posicion de los ejes
        valores_antes_pausa.x = current_position[X_AXIS];
        valores_antes_pausa.y = current_position[Y_AXIS];
        valores_antes_pausa.z = current_position[Z_AXIS];
        valores_antes_pausa.e = current_position[E_AXIS];

        //ejecuta estos comandos
        queue.inject_P(PSTR("G60 S1\nG91\nG1 Z5 E-5 F1000\nG90\nG1 X5 Y5 F3000"));


        MarlinUI::goto_screen(menu_main, 5);
        
    }

}
void pausando(){
    //para pausar host
    TERN_(HOST_PROMPT_SUPPORT, host_prompt_open(PROMPT_PAUSE_RESUME, PSTR("UI Pause"), PSTR("Resume")));

    //entra en pausa
    #if ENABLED(SDSUPPORT)
      queue.inject_P(PSTR("M25"));
    #elif defined(ACTION_ON_PAUSE)
      host_action_pause();
    #endif
    //va al menu de espera
    MarlinUI::goto_screen(esperando_pausa);
}

//pausa la imprecion y se mueve para un costado
void menu_pausa_reanudar(){
    secuencia_ejecucion = 0;
    if(printingIsPaused()){
        MarlinUI::goto_screen(esperando_reanudar);
    }else{
        MarlinUI::goto_screen(pausando);
    }
}
//menu pausa//
//////////////

/////////////
//Reiniciar//

//LCD_PINS_RS

void reiniciar_sistema_comando(){
    //reset software
    NVIC_SystemReset();
    MarlinUI::goto_screen(menu_main, 9);
}

void reiniciar_sistema(){
    crear_marco_superior(PSTR(Language_es::MSG_BUTTON_ADVERTENCIA), 0, 11); //advercencia
    crear_marco_superior(PSTR(Language_es::MSG_RESET_PRINTER), 11, 11); //reiniciar impresora

    init_boto(23, 2, 2, 27);

    START_MENU();
    NEXT_ITEM_(2);
    END_MENU();

    crear_boton(boton_x_a,           boton_x_b,           Language_es::MSG_BUTTON_CANCEL,    menu_main, 9);
    crear_boton(boton_reanudar_a,    boton_reanudar_b,    Language_es::MSG_RESET_PRINTER,    reiniciar_sistema_comando);//reiniciar impresora
}

//Reiniciar//
//////////////
#endif // MENU_KUTTERCRAFT
#endif // HAS_LCD_MENU