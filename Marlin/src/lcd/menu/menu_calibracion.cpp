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
#include "menu_calibracion.h"

#include "../../module/motion.h"
#include "../../feature/babystep.h"
#include "../../module/planner.h"
#include "../../MarlinCore.h"
#include "../../feature/tmc_util.h"

#include "menu.h"
#include "../dogm/marlinui_DOGM.h"
#include "../mapa_bit/bitmap_kuttercraft.h"
#include "../../module/settings.h"
#include "../../module/probe.h"
#include "../../module/endstops.h"

#include "../../gcode/gcode.h"
#include "../../gcode/queue.h"
#include "../../feature/bedlevel/bedlevel.h"


//constructores de menu
void init_boto(int medida_boton_, int espaciado_, int cantidad_, int altura_, int columna_bit_ = 3);
void crear_boton(const u8g_pgm_uint8_t* img_mapa_bit, const u8g_pgm_uint8_t* img_mapa_bit_2, PGM_P utf8_str_P, screenFunc_t screen, const uint16_t encoder = 0);
void draw_scroll_message(const bool blink, uint8_t lcd_width = 21, int altura_ = 0, bool color_texto = true);
void opciones_no_disponible(screenFunc_t screen, const uint16_t encoder = 0);
void crear_marco_superior(PGM_P utf8_str_P, int altura = 0, int largo = 9);
void crear_texto_centrado(PGM_P utf8_str_P, int altura = 0);
void reset_valor_scroll();
void crear_espera();
void removeSpacesInPlace(char* str);
void encoder_der_sup(bool dereccion_encoder = true);
int rango_encoder(uint32_t valor_maximo, uint32_t valor_minimo = 0);


//SALIDA
void menu_main();
void menu_calibracion_auto();
void menu_kutter_calibracion_con_sensor();

//gcode.process_subcommands_now(ubl_lcd_gcode);
//los mapa de calibracion no se activan de forma automatica hay que hacer que sea asi

//////////////////////////////
//Inicio de Auto calibracion//
//////////////////////////////
bool solo_calibracion = true;


bool led_calibracion = false;
//Pense y apaga la luz led
void prender_y_apagar_led_calibracion(){
    if(led_calibracion){
        led_calibracion = false;
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
        led_calibracion = true;
    }
}

#if(false)
//genera un nuevo mapa de calibracion
//con el valor del offset actual
//y lo guarda en memoria
void auto_calibracion_espera(){
    //NO se vuelve al status y se sigue actualizando
    MarlinUI::defer_return_to_status = true;
    MarlinUI::lcdDrawUpdate = LCDVIEW_CALL_REDRAW_NEXT;
    
    crear_texto_centrado(Language_es::MSG_CALIBRANDO, 20);

    crear_marco_superior(PSTR(MarlinUI::contenedor_str), 53, 11);

    //crea la barra de espera
    crear_espera();

    if(MarlinUI::salida_de_menu){
        //completa el ultimo punto
        unified_bed_leveling::completar_mapa();
        queue.inject_P(PSTR("G29 A\nM420 S1\nM500"));
        
        if(solo_calibracion){
            MarlinUI::goto_screen(menu_calibracion_auto, 3);
        }else{
            solo_calibracion = true;
            MarlinUI::goto_screen(menu_calibracion_auto, 1);
        }
    }
    
}
void auto_calibracion(){
    MarlinUI::contenedor_str[0] = '\0';
    MarlinUI::salida_de_menu = false;
    strcpy(MarlinUI::contenedor_str, GET_TEXT(MSG_AUTO_HOME_ACTION));

    queue.inject_P(PSTR("G28\nG29 P1"));
    MarlinUI::goto_screen(auto_calibracion_espera);
}
#endif
///////////////////////////
//Fin de Auto calibracion//
///////////////////////////

/////////////////////////////
//Inicio de calibrar offset//
/////////////////////////////
#if(false)
void menu_calibracion_();
void mover_eje_z() {
  //Tercera opccion menu calibrar offset
  //NO se vuelve al status y se sigue actualizando
  MarlinUI::defer_return_to_status = true;
  MarlinUI::lcdDrawUpdate = LCDVIEW_CALL_REDRAW_NEXT;

  if (ui.encoderPosition && !ui.manual_move.processing) {
    
    float min, max;
    soft_endstop.get_manual_axis_limits(Z_AXIS, min, max);

    const float diff = float(int32_t(ui.encoderPosition)) * ui.manual_move.menu_scale;


    current_position[Z_AXIS] += diff;

    if (int32_t(ui.encoderPosition) < 0)
      NOLESS(current_position[Z_AXIS], -5);
    else
      NOMORE(current_position[Z_AXIS], 5);

    ui.manual_move.soon(Z_AXIS);
  }
  
  ui.encoderPosition = 0;

  if (ui.should_draw()) {
    const float pos = NATIVE_TO_LOGICAL(
      ui.manual_move.processing ? destination[Z_AXIS] : current_position[Z_AXIS] + TERN0(IS_KINEMATIC, ui.manual_move.offset),
      Z_AXIS
    );
      MenuEditItemBase::draw_edit_screen(GET_TEXT(MSG_MOVE_Z), ui.manual_move.menu_scale >= 0.1f ? ftostr41sign(pos) : ftostr63(pos));
  }

  if (ui.use_click()){
    MarlinUI::contenedor_str[0] = '\0'; //vacia la lista
    //cambia el valor de offset
    // y lo guarda
    
    //strcpy(MarlinUI::contenedor_str, "M851 Z");
    //strcat(MarlinUI::contenedor_str, ftostr63(current_position[Z_AXIS]));
    //strcat(MarlinUI::contenedor_str, "M500\n");

    probe.offset.z = current_position[Z_AXIS];
    
    (void)settings.save();
    (void)settings.load();
    

    if(planner.leveling_active){
        MarlinUI::goto_screen(auto_calibracion, 1);
    }else{
        
        queue.inject_P(PSTR("G1 Z5"));
        MarlinUI::goto_screen(menu_calibracion_, 1);
    }

  }
}

void espera_posicion_offset(){
    //Segunda opccion menu calibrar offset
    //NO se vuelve al status y se sigue actualizando
    MarlinUI::defer_return_to_status = true;
    MarlinUI::lcdDrawUpdate = LCDVIEW_CALL_REDRAW_NEXT;

    crear_texto_centrado(Language_es::MSG_AUTO_HOME_ACTION, 20);
    //crea la barra de espera
    crear_espera();

    /*
     * current_position[Z_AXIS] += probe.offset.z;
     * ui.manual_move.soon(Z_AXIS);
    */

    if(MarlinUI::home_en_accion){
        current_position[Z_AXIS] = 0;
        destination[Z_AXIS] = 0;
        current_position.z = 0;

        ui.manual_move.soon(Z_AXIS);

        ui.encoderPosition = 0;
        MarlinUI::goto_screen(mover_eje_z);
    }

}

void calibrar_offset(){
    //Primer menu calibrar offset
    //Este Comando deveria depender del offset
    //arreglar en el futuro
    
    MarlinUI::offset_temporal = 0;
    probe.offset.z = 0;
    
    solo_calibracion = false;
    MarlinUI::home_en_accion = false;

    //si se entra a esta opcion el sensor inductivo
    //tiene que estar activo
    MarlinUI::inductivo_final_carrera = true;
    
    queue.inject_P(PSTR("G28"));
    
    ui.manual_move.menu_scale = 0.025;
    MarlinUI::goto_screen(espera_posicion_offset);
}
#endif
//////////////////////////
//Fin de calibrar offset//
//////////////////////////


//////////////////////////////
//Inicio de modificar offset//
#if(false)
float valor_offset = 0; //valor de guardado
float valor_offset_aux = 0; //valor de guardado

//menu que muestra el valor del offset y permite cambiarlo.
void modificar_valor_offset(){
    //NO se vuelve al status y se sigue actualizando
    MarlinUI::defer_return_to_status = true;
    MarlinUI::lcdDrawUpdate = LCDVIEW_CALL_REDRAW_NEXT;
    
    if (ui.encoderPosition && !ui.manual_move.processing) {
        float valor_suma = float(int32_t(ui.encoderPosition)) * ui.manual_move.menu_scale;
        valor_offset += valor_suma;
        valor_offset_aux += valor_suma;

        if (int32_t(ui.encoderPosition) < 0)
            NOLESS(valor_offset, -5);
        else
            NOMORE(valor_offset, 5);
    }
  
    ui.encoderPosition = 0;

    if (ui.should_draw()) {
        MenuEditItemBase::draw_edit_screen(GET_TEXT(MSG_MOVE_Z), ftostr63(valor_offset));
    }

    if (ui.use_click()){
        //float nuevo_offset_real = 0;
        MarlinUI::offset_temporal += valor_offset_aux;
        SERIAL_ECHOLN(MarlinUI::offset_temporal);
        MarlinUI::contenedor_str[0] = '\0'; //vacia la lista
        //cambia el valor de offset
        // y lo guarda
        strcpy(MarlinUI::contenedor_str, "M851 Z");
        strcat(MarlinUI::contenedor_str, ftostr63(valor_offset));
        strcat(MarlinUI::contenedor_str, "\nM500\n");

        queue.inject_P(PSTR(MarlinUI::contenedor_str));
        MarlinUI::goto_screen(menu_calibracion_auto, 2);
        
    }
}

//setea los valores para modificar el offset
void modificar_offset(){
    valor_offset = probe.offset.z;
    ui.manual_move.menu_scale = 0.025;
    MarlinUI::goto_screen(modificar_valor_offset);
}
#endif
//Fin de modificar offset//
///////////////////////////

////////////////////////
//inicio aliniar eje z//

float obtener_valor_actual_z(){
    //encargado de mostrar la posicion actual real del eje z
    get_cartesian_from_steppers();
    xyze_pos_t npos = cartes;
    const xyze_pos_t lpos = npos.asLogical();

    return lpos.z;
}

void menu_calibracion_endstop();
void espera_posicion_offset();

void salida_z_espera_home(){
    MarlinUI::defer_return_to_status = true;
    MarlinUI::lcdDrawUpdate = LCDVIEW_CALL_REDRAW_NEXT;

    crear_espera();
    crear_texto_centrado(Language_es::MSG_AUTO_HOME_ACTION, 20);
    crear_marco_superior(PSTR(Language_es::MSG_POSICIONADO_Z), 53, 11);

    if (MarlinUI::home_en_accion || MarlinUI::calibracion_general_valor){
        
        //salida de calibracion general
        if(MarlinUI::calibracion_general_valor){
            MarlinUI::home_en_accion = false;
            queue.inject_P(PSTR("M211 S1"));
            queue.inject_P(PSTR("M851 Z0\nM420 S0\nG28"));
            MarlinUI::goto_screen(espera_posicion_offset);

        }else{
            if(planner.leveling_active){//salida a autocalibracion on
                queue.inject_P(PSTR("M211 S1"));
                MarlinUI::goto_screen(menu_kutter_calibracion_con_sensor, 7);
            }else{
                queue.inject_P(PSTR("M211 S1"));//salida a autocalibracion off
                MarlinUI::goto_screen(menu_calibracion_endstop, 2);
            }
        }
    }
}

void subir_eje_z(){
    MarlinUI::defer_return_to_status = true;
    MarlinUI::lcdDrawUpdate = LCDVIEW_CALL_REDRAW_NEXT;

    float max = Z_MAX_POS + 50;

    crear_marco_superior(PSTR(Language_es::MSG_SUBIENDO_EJE));
    draw_scroll_message(MarlinUI::get_blink(), 16, 20);
    crear_espera();
    crear_marco_superior(PSTR(Language_es::MSG_AUTO_Z_ALIGN), 53, 11);

    //si son iguales sigue subiendo el eje
    //salida por cumplimineto de limite
    if(obtener_valor_actual_z() >= max){
        MarlinUI::home_en_accion = false;
        set_all_unhomed();
        
        //si se entra por calibracion general
        //este home no se ejecuta
        if(!MarlinUI::calibracion_general_valor)
            queue.inject_P(G28_STR);

        MarlinUI::goto_screen(salida_z_espera_home);
    }
}

//encargado de esperar a que el eje z llegue a la posicion indicada
void espera_eje_z(){
    MarlinUI::defer_return_to_status = true;
    MarlinUI::lcdDrawUpdate = LCDVIEW_CALL_REDRAW_NEXT;

    crear_marco_superior(PSTR(Language_es::MSG_ALINEAR_Z));
    draw_scroll_message(MarlinUI::get_blink(), 16, 20);
    crear_espera();
    crear_marco_superior(PSTR(Language_es::MSG_POSICIONADO_Z), 53, 11);

    //espera a que llegue al posicion del eje z
    if(obtener_valor_actual_z() >= Z_MAX_POS - 50){
        MarlinUI::contenedor_str[0] = '\0'; //vacia la lista

        //Se crea el gcode que hace que choque con la parte superiro
        strcpy(MarlinUI::contenedor_str, "M211 S0\nG1 Z");
        strcat(MarlinUI::contenedor_str, i16tostr4signrj(Z_MAX_POS + 50));
        strcat(MarlinUI::contenedor_str, " F500");
        
        queue.inject_P(PSTR(MarlinUI::contenedor_str));//M211 S0 y G1 Z(altura maxima mas 50) 

        MarlinUI::goto_screen(subir_eje_z);
    }
}
void espera_home_alinear_eje_z(){
    MarlinUI::defer_return_to_status = true;
    MarlinUI::lcdDrawUpdate = LCDVIEW_CALL_REDRAW_NEXT;

    crear_texto_centrado(Language_es::MSG_AUTO_HOME_ACTION, 20);
    crear_espera();
    crear_marco_superior(Language_es::MSG_POR_FAVOR_ESPERE, 54, 11);
    
    if(MarlinUI::home_en_accion){
        MarlinUI::goto_screen(espera_eje_z);
    }
}

//crea los comando para posicionar el eje z en la parte superir
void aliniar_eje_z(){
    MarlinUI::contenedor_str[0] = '\0'; //vacia la lista

    if(!MarlinUI::calibracion_general_valor)
        strcat(MarlinUI::contenedor_str, "G28\n");//hay que hacer un home?


    strcat(MarlinUI::contenedor_str, "G1 X");
    strcat(MarlinUI::contenedor_str, i16tostr4signrj(int16_t(X_BED_SIZE / 2)));
    strcat(MarlinUI::contenedor_str, " Z");
    strcat(MarlinUI::contenedor_str, i16tostr4signrj(Z_MAX_POS - 40));
    strcat(MarlinUI::contenedor_str, " F1000");

    queue.inject_P(PSTR(MarlinUI::contenedor_str));

    SERIAL_ECHOLN(MarlinUI::contenedor_str);

    if(!MarlinUI::calibracion_general_valor)
        MarlinUI::goto_screen(espera_home_alinear_eje_z);
    else
        MarlinUI::goto_screen(espera_eje_z);

}
void advertencia_aliniar_eje_z(){
    MarlinUI::defer_return_to_status = true;

    //Guarda un texto largo
    reset_valor_scroll();
    strcpy(MarlinUI::texto_muy_largo, Language_es::MSG_LARGO_ALINEAR_EJE_Z); //set de texto largo

    crear_marco_superior(PSTR(Language_es::MSG_ALINEAR_Z),0,11);

    crear_texto_centrado(Language_es::MSG_ALINIACION_Z_ADV_01, 14);
    crear_texto_centrado(Language_es::MSG_ALINIACION_Z_ADV_02, 22);
    crear_texto_centrado(Language_es::MSG_ALINIACION_Z_ADV_03, 31);
    crear_texto_centrado(Language_es::MSG_ALINIACION_Z_ADV_04, 40);
    
    crear_marco_superior(Language_es::MSG_CLICK_PARA_CONTINUAR, 54, 11);

    if(ui.use_click()){
        MarlinUI::home_en_accion = false;
        MarlinUI::goto_screen(aliniar_eje_z);
    }
}
//inicio aliniar eje z//
////////////////////////

/////////////////////
//inicio mapa de cama

//variables auxiliar

static uint8_t n_edit_pts = 1;
static int8_t x_plot = 0, y_plot = 0; // May be negative during move

void _lcd_ubl_map_edit_cmd_();
void menu_calibracion_printer();

/**
 * UBL LCD "radar" map point editing
 */

void _lcd_ubl_map_edit_cmd_() {
   unified_bed_leveling::ajustar_punto_mapa(x_plot,y_plot);
}

/**
 * UBL LCD Map Movement
 */
void ubl_map_move_to_xy_() {

  // Set the nozzle position to the mesh point
  if(ubl.mesh_index_to_xpos(x_plot) >= 225){
    current_position.set(ubl.mesh_index_to_xpos(x_plot) - 15, ubl.mesh_index_to_ypos(y_plot));
  }else{
    current_position.set(ubl.mesh_index_to_xpos(x_plot), ubl.mesh_index_to_ypos(y_plot));
  }

  // Use the built-in manual move handler
  ui.manual_move.soon(ALL_AXES_ENUM);
}

inline int32_t grid_index(const uint8_t x, const uint8_t y) {
  return (GRID_MAX_POINTS_X) * y + x;
}

void info_iniciar_prueba();
void modificar_un_punto_o_offset();//valor de salida para calibracion general 

//muestra  el mapa de cama
void ubl_map_screen_() {
    // static millis_t next_move = 0;
    // const millis_t ms = millis();

    uint8_t x, y;

    if (ui.first_page) {

        // On click send "G29 P4 ..." to edit the Z value
        //salida a calibrar punto
        if(int32_t(ui.encoderPosition) == -1){
            if (ui.use_click()) {
                const bool esta_imprimiendo = printingIsActive();

                if(!MarlinUI::calibracion_general_valor){//si no se entra por calibracion general

                    if(MarlinUI::mover_a_punto){//salida si se selecciono no mover el eje al punto
                        MarlinUI::goto_screen(menu_kutter_calibracion_con_sensor, 6);

                    }else{

                        if (!esta_imprimiendo && !printingIsPaused()) {//salida si no se esta imprimiendo y se modifico un punto
                            MarlinUI::goto_screen(menu_kutter_calibracion_con_sensor, 6);

                        }else{//salida a modificacion de punto mientras se imprime
                            MarlinUI::goto_screen(menu_calibracion_printer, 2);
                        }
                    }
                }else{//salida para calibracion general
                    MarlinUI::goto_screen(modificar_un_punto_o_offset);
                }

                return;
            }
        
        }else{
            if (ui.use_click()) {
                _lcd_ubl_map_edit_cmd_();
                return;
            }
        }

        ui.defer_status_screen();

        #if IS_KINEMATIC
        // Index of the mesh point upon entry
        const int32_t old_pos_index = grid_index(x_plot, y_plot);
        // Direction from new (unconstrained) encoder value
        const int8_t step_dir = int32_t(ui.encoderPosition) < old_pos_index ? -1 : 1;
        #endif

        do {
            // Now, keep the encoder position within range
            if (int32_t(ui.encoderPosition) < -1) ui.encoderPosition = GRID_MAX_POINTS + TERN(TOUCH_SCREEN, ui.encoderPosition, -1);
            if (int32_t(ui.encoderPosition) > GRID_MAX_POINTS - 1) ui.encoderPosition = TERN(TOUCH_SCREEN, ui.encoderPosition - GRID_MAX_POINTS, -1);

            if(int32_t(ui.encoderPosition) == -1){
                // Draw the grid point based on the encoder
                x = 0 % (GRID_MAX_POINTS_X);
                y = 0 / (GRID_MAX_POINTS_X);
            }else{
                    // Draw the grid point based on the encoder
                x = ui.encoderPosition % (GRID_MAX_POINTS_X);
                y = ui.encoderPosition / (GRID_MAX_POINTS_X);
            }

            // Validate if needed
            #if IS_KINEMATIC
                const xy_pos_t xy = { ubl.mesh_index_to_xpos(x), ubl.mesh_index_to_ypos(y) };
                if (position_is_reachable(xy)) break; // Found a valid point
                ui.encoderPosition += step_dir;       // Test the next point
            #endif
        } while(ENABLED(IS_KINEMATIC));

        // Determine number of points to edit
        #if IS_KINEMATIC
        n_edit_pts = 9; // TODO: Delta accessible edit points
        #else
        const bool xc = WITHIN(x, 1, GRID_MAX_POINTS_X - 2),
                    yc = WITHIN(y, 1, GRID_MAX_POINTS_Y - 2);
        n_edit_pts = yc ? (xc ? 9 : 6) : (xc ? 6 : 4); // Corners
        #endif

        // Refresh is also set by encoder movement
        //if (int32_t(ui.encoderPosition) != grid_index(x, y))
        //  ui.refresh(LCDVIEW_CALL_REDRAW_NEXT);
    }

    if(int32_t(ui.encoderPosition) == -1){
        // Draw the grid point based on the encoder
        x = 0 % (GRID_MAX_POINTS_X);
        y = 0 / (GRID_MAX_POINTS_X);
    }else{
        // Draw the grid point based on the encoder
        x = ui.encoderPosition % (GRID_MAX_POINTS_X);
        y = ui.encoderPosition / (GRID_MAX_POINTS_X);
    }
        
    //dibuja el mapa de cama
    if (ui.should_draw()) ui.ubl_plot(x, y);
    

    // Add a move if needed to match the grid point
    if (x != x_plot || y != y_plot) {
        x_plot = x; y_plot = y;   // The move is always posted, so update the grid point now
        if(int32_t(ui.encoderPosition) != -1){
            if(MarlinUI::mover_a_punto) ubl_map_move_to_xy_();     // Sets up a "manual move"
        }
        
        ui.refresh(LCDVIEW_CALL_REDRAW_NEXT); // Clean up a half drawn box
    }
}


//dibuja el realizando home
void _ubl_map_screen_homing_() {
  ui.defer_status_screen();
  _lcd_draw_homing();
  if (all_axes_homed() || !MarlinUI::mover_a_punto) {
        ubl.lcd_map_control = true;     // Return to the map screen after editing Z
        ui.goto_screen(ubl_map_screen_, grid_index(x_plot, y_plot)); // Pre-set the encoder value
        ui.manual_move.menu_scale = 0;  // Immediate move
        if(MarlinUI::mover_a_punto)
            ubl_map_move_to_xy_();           // Move to current mesh point
        ui.manual_move.menu_scale = 1;  // Delayed moves
  }
}

//Inicio realiza el home de los ejes
void _ubl_goto_map_screen_() {
    if (planner.movesplanned()) return;     // The ACTION_ITEM will do nothing
    if(MarlinUI::mover_a_punto){
        if (!all_axes_homed()) {
            set_all_unhomed();
            queue.inject_P(G28_STR);
        }
    }
    ui.goto_screen(_ubl_map_screen_homing_); // Go to the "Homing" screen
}

void ver_mapa_de_cama(){
    MarlinUI::mover_a_punto = false;
    ui.goto_screen(_ubl_goto_map_screen_,0);
}
void mover_mapa_de_cama(){
    MarlinUI::mover_a_punto = true;
    ui.goto_screen(_ubl_goto_map_screen_,0);
}


//inicio mapa de cama
/////////////////////
#if(false)
void completar_mapa_de_cama(){
    unified_bed_leveling::completar_mapa();
    queue.inject_P(PSTR("M117 Las Partes Faltantes Del Mapa Se Han Completado"));
    MarlinUI::goto_screen(MarlinUI::status_screen);
}

float nuevo_offset_real = 0;
int16_t valor_final = 0;
//calibracion de offset
void calibrar_offset_tiempo_real() {
    //NO se vuelve al status y se sigue actualizando
    MarlinUI::defer_return_to_status = true;
    MarlinUI::lcdDrawUpdate = LCDVIEW_CALL_REDRAW_NEXT;
    
    if (ui.encoderPosition) {
        #if ENABLED(BABYSTEPPING)
            const int16_t steps = int16_t(ui.encoderPosition)  * (BABYSTEP_SIZE_Z);
        #endif
        const float diff = float(int32_t(ui.encoderPosition)) * ui.manual_move.menu_scale;
        #if ENABLED(BABYSTEPPING)
            valor_final += steps;
        #endif
        nuevo_offset_real += diff;
        
        ui.encoderPosition = 0;
        ui.refresh(LCDVIEW_REDRAW_NOW);

        #if ENABLED(BABYSTEPPING)
            babystep.add_mm(Z_AXIS, diff);
        #endif
    }

    if (ui.should_draw()) {
      MenuEditItemBase::draw_edit_screen(Language_es::MSG_ZPROBE_ZOFFSET, ftostr63(probe.offset.z + nuevo_offset_real));
    }

    //salida
    if (ui.use_click()){
        probe.offset.z = probe.offset.z + nuevo_offset_real;

        MarlinUI::offset_temporal = MarlinUI::offset_temporal + nuevo_offset_real;

        nuevo_offset_real = 0;
        (void)settings.save();

        return MarlinUI::goto_screen(menu_calibracion_printer,1);
    }
}
#endif

///////////////////////////
//Incio calibracion manual
int numero_de_punto_medir = 0;
void calibrar_off_menu();
void calibrar_off_menu_endstop();

void calibrar_off_mover_a_punto(){
    char str_X[16], str_Y[16];

    if(numero_de_punto_medir == 1){
        sprintf_P(MarlinUI::contenedor_str, PSTR("G1 X%s Y%s F3000\n"),
                dtostrf(50, 1, 3, str_X),
                dtostrf(70, 1, 3, str_Y)
                );
        queue.inject_P(MarlinUI::contenedor_str);

    }else if(numero_de_punto_medir == 3){
        sprintf_P(MarlinUI::contenedor_str, PSTR("G1 X%s Y%s F3000\n"),
                dtostrf(X_BED_SIZE - 30, 1, 3, str_X),
                dtostrf(70, 1, 3, str_Y)
                );
        queue.inject_P(MarlinUI::contenedor_str);

    }else if(numero_de_punto_medir == 4){
        sprintf_P(MarlinUI::contenedor_str, PSTR("G1 X%s Y%s F3000\n"),
                dtostrf(70, 1, 3, str_X),
                dtostrf(Y_BED_SIZE - 70, 1, 3, str_Y)
                );
        queue.inject_P(MarlinUI::contenedor_str);

    }else if(numero_de_punto_medir == 2){
        sprintf_P(MarlinUI::contenedor_str, PSTR("G1 X%s Y%s F3000\n"),
                dtostrf(X_BED_SIZE - 30, 1, 3, str_X),
                dtostrf(Y_BED_SIZE - 70, 1, 3, str_Y)
                );
        queue.inject_P(MarlinUI::contenedor_str);
    }
}

void calibrar_off_ubicar(bool se_suma_se_resta){

    if(se_suma_se_resta){
        numero_de_punto_medir += 1;
    }else{
        numero_de_punto_medir -= 1;
    }

    if(numero_de_punto_medir > 4 || numero_de_punto_medir < 1){
        queue.inject_P(PSTR("G1 Z5"));
        MarlinUI::goto_screen(menu_main, 4);

    }else{
        queue.inject_P(PSTR("G1 Z5"));
        queue.advance();
        calibrar_off_mover_a_punto();
        queue.advance();

        queue.inject_P(PSTR("G1 Z0"));
        queue.advance();

        current_position[Z_AXIS] += probe.offset.z;

        ui.manual_move.soon(Z_AXIS);

        if(MarlinUI::inductivo_final_carrera){//calibrar_off_menu_endstop
            MarlinUI::goto_screen(calibrar_off_menu);
        }else{
            MarlinUI::goto_screen(calibrar_off_menu_endstop);
        }
    }
}


void calibrar_off_resta_punto(){
    calibrar_off_ubicar(false);
}

void calibrar_off_sumar_punto(){
    calibrar_off_ubicar(true);
}

void subir_hacer_home(){
    queue.inject_P(PSTR("G1 Z5 F500"));
    queue.advance();
    queue.inject_P(PSTR("G1 Z0 F500"));
    queue.advance();
    
    current_position[Z_AXIS] += probe.offset.z;
    ui.manual_move.soon(Z_AXIS);
    safe_delay(2000);
    MarlinUI::goto_screen(calibrar_off_menu,1);
}

void subir_hacer_subir_endstop(){
    queue.inject_P(PSTR("G1 Z15 F1000\nG28 Z\nG1 Z0"));
    MarlinUI::goto_screen(calibrar_off_menu_endstop, 1);
}


void calibrar_off_menu(){
    ui.manual_move.menu_scale = 0.025;
    //encoderLine indica la pocision del encoder
    //establese el rango del encoder de 0 / x-1
    START_MENU();
    NEXT_ITEM_(3);
    END_MENU();

    init_boto(30, 5, 3, 17, 4); 

    crear_marco_superior(Language_es::MSG_CALIBRATE);

    crear_boton(volver_boton_a, volver_boton_b, Language_es::MSG_VOLVER,                calibrar_off_resta_punto);
    crear_boton(mesh_ajus_a,    mesh_ajus_b,    Language_es::MSG_SUBIR_BAJAR,           subir_hacer_home);
    crear_boton(seguir_boton_a, seguir_boton_b, Language_es::MSG_LEVEL_BED_NEXT_POINT,  calibrar_off_sumar_punto);
}

void calibrar_off_menu_endstop(){
    ui.manual_move.menu_scale = 0.025;
    //encoderLine indica la pocision del encoder
    //establese el rango del encoder de 0 / x-1
    START_MENU();
    NEXT_ITEM_(3);
    END_MENU();

    init_boto(30, 5, 3, 17, 4);

    crear_marco_superior(Language_es::MSG_CALIBRATE);

    crear_boton(volver_boton_a, volver_boton_b, Language_es::MSG_VOLVER,                calibrar_off_resta_punto);
    crear_boton(home_boton_a,    home_boton_b,  Language_es::MSG_SUBIR_BAJAR,           subir_hacer_subir_endstop);
    crear_boton(seguir_boton_a, seguir_boton_b, Language_es::MSG_LEVEL_BED_NEXT_POINT,  calibrar_off_sumar_punto);
}





//Final calibracion manual
//////////////////////////

void calibrar_off_espera_home(){

    //NO se vuelve al status y se sigue actualizando
    MarlinUI::defer_return_to_status = true;
    MarlinUI::lcdDrawUpdate = LCDVIEW_CALL_REDRAW_NEXT;

    crear_texto_centrado(Language_es::MSG_AUTO_HOME_ACTION, 20);
    //crea la barra de espera
    crear_espera();

    if(current_position[Z_AXIS] == 0){
        queue.inject_P(PSTR("G1 Z5 F1000"));
        queue.advance();

        queue.inject_P(PSTR("G1 X50 Y70 F3000"));
        queue.advance();

        queue.inject_P(PSTR("G1 Z0 F1000"));
        queue.advance();

        current_position[Z_AXIS] += probe.offset.z;
        ui.manual_move.soon(Z_AXIS);

        if(MarlinUI::inductivo_final_carrera){
            MarlinUI::goto_screen(calibrar_off_menu);
        }else{
            MarlinUI::goto_screen(calibrar_off_menu_endstop);
        }
    }

}

void calibrar_off_home(){
    numero_de_punto_medir = 1;
    solo_calibracion = false;
    queue.inject_P(PSTR("G28"));//\nG91\nG1 X44 Y-44 Z1 F1500\nG90\nG1 Z0
    ui.manual_move.menu_scale = 0.025;
    MarlinUI::goto_screen(calibrar_off_espera_home, 1);
}

void menu_calibracion_endstop(){
    probe.offset.z = 0; // dejamos el offset en cero para que no moleste
    //MarlinUI::inductivo_final_carrera = false;
    MarlinUI::defer_return_to_status = false;
    #if(false)
    solo_calibracion = true;
    #endif

    ui.manual_move.menu_scale = 0.025;
    
    START_MENU();
    NEXT_ITEM_(2);
    END_MENU();

    init_boto(30, 5, 2, 17, 4);

    crear_marco_superior(Language_es::MSG_CALIBRATE);

    crear_boton(volver_boton_a, volver_boton_b, Language_es::MSG_VOLVER,            menu_main,  4);
    //crear_boton(mesh_cont_a,    mesh_cont_b,    Language_es::MSG_CALIBRAR_CAMA,     calibrar_off_home);
    crear_boton(mesh_ajus_a,    mesh_ajus_b,    Language_es::MSG_ALINEAR_Z,     advertencia_aliniar_eje_z);
    ///advertencia_aliniar_eje_z
}

void menu_calibracion_(){
    MarlinUI::defer_return_to_status = false;
    #if(false)
    solo_calibracion = true;
    #endif

    ui.manual_move.menu_scale = 0.025;
    //encoderLine indica la pocision del encoder
    //establese el rango del encoder de 0 / x-1
    START_MENU();
    NEXT_ITEM_(3);
    END_MENU();

    init_boto(30, 5, 3, 17, 4);

    crear_marco_superior(Language_es::MSG_CALIBRATE);

    crear_boton(volver_boton_a,     volver_boton_b,     Language_es::MSG_VOLVER,            menu_main,  4);
    //crear_boton(calibrar_auto_a,    calibrar_auto_b,    Language_es::MSG_CALIBRAR_OFFSET,   calibrar_offset);
    //crear_boton(autocalibracion_a,  autocalibracion_b,  Language_es::MSG_CALIBRAR_CAMA,     calibrar_off_home);
}

void menu_calibracion_printer();

void mapa_de_cama(){
    opciones_no_disponible(menu_calibracion_printer, 2);
}

void mapa_de_cama_redirigir(){
    #if(false)
    MarlinUI::goto_screen(ver_mapa_de_cama);
    #endif
}

///////////////////////////////////////////////
//inicio calibrar impresora mientras se imprime

void lcd_babystep_z();

//este menu se muestra mintras se imprime
//modificar offset
//mapa de cama
void ver_mapa_de_cama_tiempo_real(){
    MarlinUI::mover_a_punto = false;
    ui.goto_screen(ubl_map_screen_,0);
}

void menu_calibracion_printer(){
    MarlinUI::defer_return_to_status = false;
    #if(false)
    solo_calibracion = true;
    #endif

    ui.manual_move.menu_scale = 0.025;
    //encoderLine indica la pocision del encoder
    //establese el rango del encoder de 0 / x-1
    START_MENU();
    NEXT_ITEM_(3);
    END_MENU();

    init_boto(30, 5, 3, 17, 4);

    crear_marco_superior(Language_es::MSG_CALIBRATE);

    crear_boton(volver_boton_a,     volver_boton_b,     Language_es::MSG_VOLVER,            menu_main,  2);
    crear_boton(ajustar_offset_a,   ajustar_offset_b,   Language_es::MSG_MODIFICAR_OFFSET,  lcd_babystep_z);
    crear_boton(ajuste_mapa_a,      ajuste_mapa_b,      Language_es::MSG_MAPA_CAMA,         ver_mapa_de_cama_tiempo_real);
 }


//final calibrar impresora mientras se imprime
//////////////////////////////////////////////

//calibracion kuttercraft UBL
//es una modificacion de la UBL de marlin con el fin
//que se mas sencilla de usar
#if ENABLED(AUTO_BED_LEVELING_UBL)

void cal_offset_temp();
void cal_espera_home();
void calibracion_precisa_home_espera();
void temp_probar_calibracion();
void espera_prueba_home();
int se_calibro_un_nuevo_offset = 1;

float axu_offset_maquina = 0;

////////////////////////
// temp selec inicio

//espera a que caliente el hotend y la cama a la temperatura deseada
void calibracion_espera_calentamiento(){
    //NO se vuelve al status y se sigue actualizando
    MarlinUI::defer_return_to_status = true;
    MarlinUI::lcdDrawUpdate = LCDVIEW_CALL_REDRAW_NEXT;

    //crea la barra de espera
    crear_espera();

    crear_marco_superior(Language_es::MSG_CALI_TEMP_CALENTANDO_IMP,0,11);
    crear_marco_superior(Language_es::MSG_POR_FAVOR_ESPERE, 54, 11);

    //informacion de temperatura
    lcd_moveto(89, 29);
    lcd_put_u8str(i16tostr4signrj( int(thermalManager.degTargetHotend(0)) )); //temp objectivo
    lcd_moveto(89, 29);
    lcd_put_u8str_P(PSTR("/"));//separador
    lcd_moveto(64, 29);
    lcd_put_u8str(i16tostr4signrj(thermalManager.degHotend(0)));// temp actual

    //informacion de temperatura
    lcd_moveto(89, 45);
    lcd_put_u8str(i16tostr4signrj( int(thermalManager.degTargetBed()) )); //temp objectivo
    lcd_moveto(89, 45);
    lcd_put_u8str_P(PSTR("/"));//separador
    lcd_moveto(64, 45);
    lcd_put_u8str(i16tostr4signrj(thermalManager.degBed()));// temp actual

    if(int(thermalManager.degHotend(0)) >= int(thermalManager.degTargetHotend(0)) - 5 && int(thermalManager.degBed()) >= int(thermalManager.degTargetBed())){
        MarlinUI::goto_screen(cal_espera_home, 0);
    }
}

void temperatura_preset_pla_espera(){
    thermalManager.setTargetHotend(190, 0);
    thermalManager.setTargetBed(60);
    MarlinUI::goto_screen(calibracion_espera_calentamiento);
}

void temperatura_preset_abs_espera(){
    thermalManager.setTargetHotend(230, 0);
    thermalManager.setTargetBed(80);
    MarlinUI::goto_screen(calibracion_espera_calentamiento);
}

void temperatura_preset_flex_espera(){
    thermalManager.setTargetHotend(220, 0);
    thermalManager.setTargetBed(70);
    MarlinUI::goto_screen(calibracion_espera_calentamiento);
}

void temperatura_preset_nylon_espera(){
    thermalManager.setTargetHotend(240, 0);
    thermalManager.setTargetBed(85);
    MarlinUI::goto_screen(calibracion_espera_calentamiento);
}

void temperatura_preset_calibracion(){
    crear_marco_superior(Language_es::MSG_PREDETERMINADO);

    START_MENU();
    NEXT_ITEM_(5);
    END_MENU();

    init_boto(23, 2, 5, 21);

    if(se_calibro_un_nuevo_offset == 3 || se_calibro_un_nuevo_offset == 5)// salida de calibracion  general y de probar calibracion
        crear_boton(boton_volver_a,  boton_volver_b, Language_es::MSG_VOLVER,           temp_probar_calibracion,1);
    else
        crear_boton(boton_volver_a,  boton_volver_b, Language_es::MSG_VOLVER,           cal_offset_temp,1);

    crear_boton(boton_pla_a,     boton_pla_b,    Language_es::MSG_PRESET_PLA,       temperatura_preset_pla_espera);
    crear_boton(boton_abs_a,     boton_abs_b,    Language_es::MSG_PRESET_ABS,       temperatura_preset_abs_espera);
    crear_boton(boton_flex_a,    boton_flex_b,   Language_es::MSG_PRESET_FLEX,      temperatura_preset_flex_espera);
    crear_boton(boton_nylon_a,   boton_nylon_b,  Language_es::MSG_PRESET_NYLON,     temperatura_preset_nylon_espera);
}

void temperatura_manual_calibracion_bed(){
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
        MarlinUI::goto_screen(calibracion_espera_calentamiento);
    }
}


void temperatura_manual_calibracion_hotend(){
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
        MarlinUI::goto_screen(temperatura_manual_calibracion_bed, thermalManager.degBed());
    }
}

// final temp selec
////////////////////////

////////////////////////
//Calibrar offset inicio
void completar_mapa();

void mapa_punto_menos_offset(){
        //cambia el valor de la matrix
        ubl.z_values[0][0] -= axu_offset_maquina;
        ubl.z_values[0][1] -= axu_offset_maquina;
        ubl.z_values[0][2] -= axu_offset_maquina;
        ubl.z_values[0][3] -= axu_offset_maquina;

        ubl.z_values[1][0] -= axu_offset_maquina;
        ubl.z_values[1][1] -= axu_offset_maquina;
        ubl.z_values[1][2] -= axu_offset_maquina;
        ubl.z_values[1][3] -= axu_offset_maquina;

        ubl.z_values[2][0] -= axu_offset_maquina;
        ubl.z_values[2][1] -= axu_offset_maquina;
        ubl.z_values[2][2] -= axu_offset_maquina;
        ubl.z_values[2][3] -= axu_offset_maquina;

        ubl.z_values[3][0] -= axu_offset_maquina;
        ubl.z_values[3][1] -= axu_offset_maquina;
        ubl.z_values[3][2] -= axu_offset_maquina;
        ubl.z_values[3][3] -= axu_offset_maquina;

        probe.offset.z = axu_offset_maquina;
        queue.inject_P(PSTR("M420S1\nG28\nM500"));
}

void mapa_punto_mas_offset(){
        //cambia el valor de la m   atrix
        ubl.z_values[0][0] += axu_offset_maquina;
        ubl.z_values[0][1] += axu_offset_maquina;
        ubl.z_values[0][2] += axu_offset_maquina;
        ubl.z_values[0][3] += axu_offset_maquina;

        ubl.z_values[1][0] += axu_offset_maquina;
        ubl.z_values[1][1] += axu_offset_maquina;
        ubl.z_values[1][2] += axu_offset_maquina;
        ubl.z_values[1][3] += axu_offset_maquina;

        ubl.z_values[2][0] += axu_offset_maquina;
        ubl.z_values[2][1] += axu_offset_maquina;
        ubl.z_values[2][2] += axu_offset_maquina;
        ubl.z_values[2][3] += axu_offset_maquina;

        ubl.z_values[3][0] += axu_offset_maquina;
        ubl.z_values[3][1] += axu_offset_maquina;
        ubl.z_values[3][2] += axu_offset_maquina;
        ubl.z_values[3][3] += axu_offset_maquina;
}

void otras_calibraciones();
void info_prueba_de_offset();

void espera_sondeo_cama(){
    MarlinUI::defer_return_to_status = true; //NO se vuelve al status y se sigue actualizando
    MarlinUI::lcdDrawUpdate = LCDVIEW_CALL_REDRAW_NEXT;


    crear_marco_superior(Language_es::MSG_CALIBRANDO);
    draw_scroll_message(MarlinUI::get_blink(), 16, 20);
    crear_espera();
    crear_marco_superior(PSTR(MarlinUI::contenedor_str), 53, 11);

    if(MarlinUI::salida_de_G29){

        //salida de la calibracion de offset
        if(se_calibro_un_nuevo_offset == 1){
            completar_mapa();

            probe.offset.z = axu_offset_maquina;
            queue.inject_P(PSTR("M420 S1\nM500"));
            MarlinUI::goto_screen(menu_kutter_calibracion_con_sensor, 1);

        //salida de la calibracion precisa 
        }else if(se_calibro_un_nuevo_offset == 2){
            queue.inject_P(PSTR("M420 S1\nM500"));
            MarlinUI::goto_screen(otras_calibraciones, 2);

        //salida de la calibracion general
        }else if(se_calibro_un_nuevo_offset == 5){
            se_calibro_un_nuevo_offset = 3;

            completar_mapa();
            probe.offset.z = axu_offset_maquina;
            queue.inject_P(PSTR("M420 S1\nM500"));

            //MarlinUI::goto_screen(info_iniciar_prueba);
            MarlinUI::goto_screen(info_prueba_de_offset);

        //salida de la auto calibracion
        }else{
            completar_mapa();

            probe.offset.z = axu_offset_maquina;
            queue.inject_P(PSTR("M420 S1\nM500"));
            MarlinUI::goto_screen(otras_calibraciones, 1);
        }
    }
}

//permite mover el eje z,
//con el fin de bajar este hasta que toque la cama
void menu_calibrar_offset(){
    MarlinUI::defer_return_to_status = true; //NO se vuelve al status y se sigue actualizando
    MarlinUI::lcdDrawUpdate = LCDVIEW_CALL_REDRAW_NEXT;

    //establece los limites y el movimiento del eje z
    if (ui.encoderPosition && !ui.manual_move.processing) {
    
        float min, max;
        soft_endstop.get_manual_axis_limits(Z_AXIS, min, max);

        const float diff = float(int32_t(ui.encoderPosition)) * ui.manual_move.menu_scale;


        current_position[Z_AXIS] += diff;

        if (int32_t(ui.encoderPosition) < 0)
            NOLESS(current_position[Z_AXIS], -5);
        else
            NOMORE(current_position[Z_AXIS], 5);

        ui.manual_move.soon(Z_AXIS);
    }
  
    ui.encoderPosition = 0;//restablece el encode

    //Encargado de dibujar el valor actual del offset
    if (ui.should_draw()) {
        const float pos = NATIVE_TO_LOGICAL(
        ui.manual_move.processing ? destination[Z_AXIS] : current_position[Z_AXIS] + TERN0(IS_KINEMATIC, ui.manual_move.offset),
        Z_AXIS
        );
        MenuEditItemBase::draw_edit_screen(GET_TEXT(MSG_ZPROBE_ZOFFSET), ui.manual_move.menu_scale >= 0.1f ? ftostr41sign(pos) : ftostr63(pos));

        crear_marco_superior(Language_es::MSG_CALI_OFFSET_04_A, 0,  11);
        crear_marco_superior(Language_es::MSG_CALI_OFFSET_04_B, 11, 11);

        //crear_marco_superior(Language_es::MSG_CALI_OFFSET_03, 44,  10);
        crear_marco_superior(Language_es::MSG_CALI_OFFSET_04_C, 54,  11);

    }

    if (ui.use_click()){
        //salida para calibracion precisa
        if(se_calibro_un_nuevo_offset == 2){
            MarlinUI::contenedor_str[0] = '\0'; //vacia la lista

            axu_offset_maquina = current_position[Z_AXIS];

            MarlinUI::salida_de_G29 = false;

            mapa_punto_mas_offset();

            queue.inject_P(PSTR("G28"));

            MarlinUI::goto_screen(calibracion_precisa_home_espera, 0);
        
        //salida para calibrar offset
        }else{
            MarlinUI::contenedor_str[0] = '\0'; //vacia la lista

            axu_offset_maquina = current_position[Z_AXIS];

            queue.inject_P(PSTR("G29 P1\nG29 P3\nM420 S1"));

            MarlinUI::salida_de_G29 = false;

            MarlinUI::goto_screen(espera_sondeo_cama, 0);
        }
    }
}

//solo informa al usuario 
//que hacer
void info_calibracion_de_offset(){
    MarlinUI::defer_return_to_status = true;

    reset_valor_scroll();
    strcpy(MarlinUI::texto_muy_largo, Language_es::MSG_LARGO_CALIBRACION_AUTO); //set de texto largo

    crear_marco_superior(PSTR(Language_es::MSG_CALIBRAR_OFFSET),0,9);

    crear_texto_centrado(Language_es::MSG_CALI_OFFSET_01, 12);
    crear_texto_centrado(Language_es::MSG_CALI_OFFSET_02, 22);
    crear_texto_centrado(Language_es::MSG_CALI_OFFSET_03, 32);
    crear_texto_centrado(Language_es::MSG_CALI_OFFSET_04, 42);
    
    crear_marco_superior(Language_es::MSG_CLICK_PARA_CONTINUAR, 54, 11);

    if(ui.use_click()){
        MarlinUI::home_en_accion = false;
        MarlinUI::goto_screen(menu_calibrar_offset, 0);
    }
}

//espera a que se realize un home para poder continuar
//y mueve la boquilla al centro de la cama
void espera_posicion_offset(){
    MarlinUI::defer_return_to_status = true;
    MarlinUI::lcdDrawUpdate = LCDVIEW_CALL_REDRAW_NEXT;

    crear_texto_centrado(Language_es::MSG_AUTO_HOME_ACTION, 20);
    crear_espera();
    crear_marco_superior(Language_es::MSG_POR_FAVOR_ESPERE, 54, 11);
    
    if(MarlinUI::home_en_accion){
        //se vacia el contenedor
        //y se genera un comando de movimiento
        MarlinUI::contenedor_str[0] = '\0';
        strcpy(MarlinUI::contenedor_str, PSTR(OFFSET_HOTEND_G));//el defase del sensor inductivo
        queue.inject_P(PSTR(MarlinUI::contenedor_str));//LLeva a la maquina al punto Z0 real para encotrar el offset

        ui.manual_move.menu_scale = 0.025;//la escala para modificar el offset

        MarlinUI::goto_screen(info_calibracion_de_offset, 0);
    }

}

void espera_posicion_home(){
    MarlinUI::defer_return_to_status = true;
    MarlinUI::lcdDrawUpdate = LCDVIEW_CALL_REDRAW_NEXT;

    crear_texto_centrado(Language_es::MSG_AUTO_HOME_ACTION, 20);
    crear_espera();
    
    if(MarlinUI::home_en_accion){
        MarlinUI::contenedor_str[0] = '\0'; //vacia la lista

        queue.inject_P(PSTR("G29 P1\nG29 P3\nM420 S1"));

        MarlinUI::salida_de_G29 = false;

        MarlinUI::goto_screen(espera_sondeo_cama, 0);
    }

}


//despues de calentar se viene a este menu
//se viene aca antes de un home y se puede tomar varios caminos
//esto se hizo para tener solo un menu de temperatura
void cal_espera_home(){
    MarlinUI::home_en_accion = false; //en el G28 pasa a ser cierto

    //sin esta linia calibra con final de carrera
    MarlinUI::inductivo_final_carrera = true;//se esta usando el sensor inductivo

    //M851 Z0 M420 S0 //se cambia el offsert actual a 0, 
    //se apaga la auto calibracion para que el mapa no moleste
    //se va al origen
    //salida (calibrar offset) y (calibracion precisa)
    if(se_calibro_un_nuevo_offset == 1 || se_calibro_un_nuevo_offset == 2){
        queue.inject_P(PSTR("M851 Z0\nM420 S0\nG28"));
        MarlinUI::goto_screen(espera_posicion_offset);

    }else if(se_calibro_un_nuevo_offset == 3){//entrada a la pruebe de calibracion
        queue.inject_P(PSTR("G28\nG1 Z70 X5 F1000"));
        MarlinUI::goto_screen(espera_prueba_home);
        
    }else if(se_calibro_un_nuevo_offset == 4){//entrada a mover eje, en editar mapa
        MarlinUI::goto_screen(mover_mapa_de_cama);
    //salida a auto calibracion


    //despus de esperar el calentamiento se hace un home
    //Y la maquina se mueve a un costado para poder cargar filamento
    }else if(se_calibro_un_nuevo_offset == 5){
        queue.inject_P(PSTR("G28\nG1 Z70 X5 F1000"));
        MarlinUI::goto_screen(espera_prueba_home);

    }else{//auto calibracion 
        axu_offset_maquina = probe.offset.z;//guarda el offset actual
        probe.offset.z = 0;
        queue.inject_P(PSTR("G28"));//se ejecuta un home para borrar el valor del offset

        //espera al home
        MarlinUI::goto_screen(espera_posicion_home);
    }
    
}

void editar_mapa_de_cama();

//es recomendable calibrar la impresora en caliente
void cal_offset_temp(){
    crear_marco_superior(Language_es::MSG_CALI_TEMP_00, 0,  9); //Se recomenda calibrar
    crear_marco_superior(Language_es::MSG_CALI_TEMP_01, 9,  9); //La base en caliente

    START_MENU();
    NEXT_ITEM_(4);
    END_MENU();

    init_boto(23, 2, 4, 24);
    if(se_calibro_un_nuevo_offset == 1)//salida de calibracion de offset
        crear_boton(boton_volver_a,     boton_volver_b,         Language_es::MSG_VOLVER,         menu_kutter_calibracion_con_sensor,2);
    else if(se_calibro_un_nuevo_offset == 2)//calibracion precisa
        crear_boton(boton_volver_a,     boton_volver_b,         Language_es::MSG_VOLVER,         otras_calibraciones, 2);
    else if(se_calibro_un_nuevo_offset == 4)//salida de mapa de cama
        crear_boton(boton_volver_a,     boton_volver_b,         Language_es::MSG_VOLVER,         editar_mapa_de_cama, 1);
    else
        crear_boton(boton_volver_a,     boton_volver_b,         Language_es::MSG_VOLVER,         otras_calibraciones, 1);

    crear_boton(boton_temp_pred_a,  boton_temp_pred_b,      Language_es::MSG_PREDETERMINADO, temperatura_preset_calibracion,1);
    crear_boton(boton_temp_manual_a,boton_temp_manual_b,    Language_es::MSG_MANUALES,       temperatura_manual_calibracion_hotend,thermalManager.degHotend(0));
    crear_boton(boton_enfriar_a,    boton_enfriar_b,        Language_es::MSG_CALI_TEMP_FRIO, cal_espera_home);

}

void calibrar_offset_temp(){
    se_calibro_un_nuevo_offset = 1;
    MarlinUI::goto_screen(cal_offset_temp,1);
}
void calibrar_automa_temp(){
    se_calibro_un_nuevo_offset = 0;
    MarlinUI::goto_screen(cal_offset_temp,1);
}

//Calibrar offset final
///////////////////////

//completar mapa de cama inicio
float diferencia_de_altura(float x, float y){
  return -1 * (x) + y;
}

float promedio_altura(float x, float y){
  return (x + y)/2;
}

void completar_mapa(){
  //AUTO-completa los puntos exteriores
  //con un valor creciente de la pendiente
  ubl.z_values[3][0] = ubl.z_values[3][0] - 0.35;
  ubl.z_values[3][1] = ubl.z_values[3][1] - 0.2;
  ubl.z_values[3][2] = ubl.z_values[3][2] - 0.2;

  ubl.z_values[0][3] = ubl.z_values[0][2] + promedio_altura(diferencia_de_altura(ubl.z_values[0][1],ubl.z_values[0][2]), diferencia_de_altura(ubl.z_values[0][0],ubl.z_values[0][1]));
  ubl.z_values[1][3] = ubl.z_values[1][2] + promedio_altura(diferencia_de_altura(ubl.z_values[1][1],ubl.z_values[1][2]), diferencia_de_altura(ubl.z_values[1][0],ubl.z_values[1][1]));
  ubl.z_values[2][3] = ubl.z_values[2][2] + promedio_altura(diferencia_de_altura(ubl.z_values[2][1],ubl.z_values[2][2]), diferencia_de_altura(ubl.z_values[2][0],ubl.z_values[2][1]));

  ubl.z_values[0][3] = ubl.z_values[0][3] - 0.1;
  ubl.z_values[1][3] = ubl.z_values[1][3] - 0.1;
  ubl.z_values[2][3] = ubl.z_values[2][3] - 0.1;

  ubl.z_values[3][3] = ubl.z_values[2][2] - 0.1 + promedio_altura(diferencia_de_altura(ubl.z_values[1][1],ubl.z_values[2][2]),diferencia_de_altura(ubl.z_values[0][0],ubl.z_values[1][1]));
} 
//completar mapa de cama final

////////////////////////
//Modificar offset inicio
float valor_offset_actual = 0; 
float valor_offset_nuevo = 0;

void cal_offset_actual_modificar(){
    MarlinUI::defer_return_to_status = true;            //NO se vuelve al status
    MarlinUI::lcdDrawUpdate = LCDVIEW_CALL_REDRAW_NEXT; //se sigue actualizando

    crear_marco_superior(Language_es::MSG_CALI_OFFSET_05,   0,  9);
    crear_marco_superior(Language_es::MSG_CALI_OFFSET_06,   54, 11);
    
    if (ui.encoderPosition && !ui.manual_move.processing) {
        float valor_suma = float(int32_t(ui.encoderPosition)) * ui.manual_move.menu_scale;
        valor_offset_actual += valor_suma; //guarda el valor del nuevo offset
        valor_offset_nuevo  += valor_suma; //guarda la diferencia con el anterior

        if (int32_t(ui.encoderPosition) < 0)
            NOLESS(valor_offset_actual, -5);
        else
            NOMORE(valor_offset_actual, 5);
    }
  
    ui.encoderPosition = 0;

    if (ui.should_draw()) {
        MenuEditItemBase::draw_edit_screen(GET_TEXT(MSG_ZPROBE_ZOFFSET), ftostr63(valor_offset_actual));
    }

    if (ui.use_click()){;
        //cambia el valor del offset
        probe.offset.z = valor_offset_actual;

        /*
        //cambia el valor de la matrix
        ubl.z_values[0][0] += valor_offset_nuevo;
        ubl.z_values[0][1] += valor_offset_nuevo;
        ubl.z_values[0][2] += valor_offset_nuevo;
        ubl.z_values[0][3] += valor_offset_nuevo;

        ubl.z_values[1][0] += valor_offset_nuevo;
        ubl.z_values[1][1] += valor_offset_nuevo;
        ubl.z_values[1][2] += valor_offset_nuevo;
        ubl.z_values[1][3] += valor_offset_nuevo;

        ubl.z_values[2][0] += valor_offset_nuevo;
        ubl.z_values[2][1] += valor_offset_nuevo;
        ubl.z_values[2][2] += valor_offset_nuevo;
        ubl.z_values[2][3] += valor_offset_nuevo;

        ubl.z_values[3][0] += valor_offset_nuevo;
        ubl.z_values[3][1] += valor_offset_nuevo;
        ubl.z_values[3][2] += valor_offset_nuevo;
        ubl.z_values[3][3] += valor_offset_nuevo;
        */

        queue.inject_P(PSTR("M500"));
        if(!MarlinUI::calibracion_general_valor)
            MarlinUI::goto_screen(menu_kutter_calibracion_con_sensor, 3);
        else
            MarlinUI::goto_screen(modificar_un_punto_o_offset, 1);
    }
}

void cal_offset_actual(){
    valor_offset_actual = probe.offset.z;
    ui.manual_move.menu_scale = 0.025;
    MarlinUI::goto_screen(cal_offset_actual_modificar);
}
//Modificar offset final
////////////////////////

////////////////////////////
//Calibracion Precisa inicio

void calibracion_precisa_espera(){
    MarlinUI::defer_return_to_status = true;
    MarlinUI::lcdDrawUpdate = LCDVIEW_CALL_REDRAW_NEXT;

    crear_texto_centrado(Language_es::MSG_CALI_PRECISA_01, 10);
    crear_texto_centrado(Language_es::MSG_CALI_PRECISA_02, 20);
    crear_espera();
}

void calibracion_precisa_home_espera(){
    MarlinUI::defer_return_to_status = true;
    MarlinUI::lcdDrawUpdate = LCDVIEW_CALL_REDRAW_NEXT;

    crear_texto_centrado(Language_es::MSG_AUTO_HOME_ACTION, 20);
    crear_espera();
    
    if(MarlinUI::home_en_accion){
        queue.inject_P(PSTR("G29 P4 R T\nM500"));
        MarlinUI::goto_screen(calibracion_precisa_espera);
    }

}

void calibracion_precisa(){
    se_calibro_un_nuevo_offset = 2;
    MarlinUI::goto_screen(cal_offset_temp,1);
}

//Calibracion Precisa final
///////////////////////////

//////////////////////////////////////////////////////////
//menu de calibrar offset o modificar un punto de la cama

void modificar_un_punto_o_offset(){
    MarlinUI::defer_return_to_status = true;

    START_MENU();
    NEXT_ITEM_(3);
    END_MENU();

    crear_marco_superior(Language_es::MSG_GENERAL_MSG_00);

    crear_texto_centrado(Language_es::MSG_GENERAL_MSG_01, 9);
    crear_texto_centrado(Language_es::MSG_GENERAL_MSG_02, 19);

    init_boto(23, 5, 3, 29);

    crear_boton(boton_detener_a,        boton_detener_b,        Language_es::MSG_GENERAL_PUNTO,    cal_espera_home);
    crear_boton(modificar_offset_a,     modificar_offset_b,     Language_es::MSG_MODIFICAR_OFFSET, cal_offset_actual);
    crear_boton(probar_calibracion_a,   probar_calibracion_b,   Language_es::MSG_PRUEBA_VOLVER,    info_iniciar_prueba);
}

//menu de calibrar offset o modificar un punto de la cama
/////////////////////////////////////////////////////////

//////////////////////////////
//Prueba de calibracion inicio
void cargar_y_retirar_filamento_para_prueba();
int contador_de_comando_para_prueba = 0;
int contador_repeticiones_para_prueba = 0;

void info_editar_mapa_de_calibracion(){
    MarlinUI::defer_return_to_status = true;
    se_calibro_un_nuevo_offset = 4;//indica que hay que moverse al punto

    crear_marco_superior(PSTR(Language_es::MSG_MAPA_CAMA),0,9);

    crear_texto_centrado(Language_es::MSG_PRUEBA_IMPRESION_06, 12);
    crear_texto_centrado(Language_es::MSG_PRUEBA_IMPRESION_07, 22);
    crear_texto_centrado(Language_es::MSG_PRUEBA_IMPRESION_08, 32);
    crear_texto_centrado(Language_es::MSG_PRUEBA_IMPRESION_09, 42);
    
    crear_marco_superior(Language_es::MSG_CLICK_PARA_CONTINUAR, 54, 11);

    if(ui.use_click()){
        MarlinUI::home_en_accion = false;
        MarlinUI::goto_screen(modificar_un_punto_o_offset, 0);
    }
}

void salida_de_calibracion_general(){
    MarlinUI::defer_return_to_status = false;
    MarlinUI::calibracion_general_valor = false;
    MarlinUI::goto_screen(menu_kutter_calibracion_con_sensor,1);
}

//pregunta si la prueba salio bien
void la_prueba_quedo_bien(){
    MarlinUI::defer_return_to_status = true;

    START_MENU();
    NEXT_ITEM_(2);
    END_MENU();

    crear_marco_superior(Language_es::MSG_PRUEBA_IMPRESION);

    crear_texto_centrado(Language_es::MSG_PRUEBA_IMPRESION_04, 9);
    crear_texto_centrado(Language_es::MSG_PRUEBA_IMPRESION_05, 19);

    init_boto(23, 5, 2, 29);

    crear_boton(boton_detener_a,    boton_detener_b,    Language_es::MSG_PRUEBA_MAL,    info_editar_mapa_de_calibracion);
    crear_boton(boton_tilde_a,      boton_tilde_b,      Language_es::MSG_PRUEBA_BIEN,   salida_de_calibracion_general, 1);
}

void esperando_que_termine_prueba(){

    //NO se vuelve al status y se sigue actualizando
    MarlinUI::defer_return_to_status = true;
    MarlinUI::lcdDrawUpdate = LCDVIEW_CALL_REDRAW_NEXT;

    //crea la barra de espera
    draw_scroll_message(MarlinUI::get_blink(), 16, 20);
    crear_espera();
    crear_marco_superior(Language_es::MSG_CALI_TEMP_08,0,11);
    crear_marco_superior(Language_es::MSG_POR_FAVOR_ESPERE, 54, 11);

    if(MarlinUI::salida_de_G26){
        //se crea un comando de movimiento
        MarlinUI::contenedor_str[0] = '\0';
        strcpy(MarlinUI::contenedor_str, "G1 Z100 X5 Y");
        strcat(MarlinUI::contenedor_str, i16tostr4signrj(Y_BED_SIZE - 10));
        strcat(MarlinUI::contenedor_str, " F2000");

        //salida de calibracion general
        if(MarlinUI::calibracion_general_valor){
            queue.inject_P(PSTR(MarlinUI::contenedor_str));
            MarlinUI::goto_screen(la_prueba_quedo_bien);
        //salida de prueba de calibracion
        }else{
            queue.inject_P(PSTR(MarlinUI::contenedor_str));
            MarlinUI::goto_screen(menu_kutter_calibracion_con_sensor,6);
        }
    }
}

void inicia_la_prueba(){
    //si se entra de la calibracion general
    //pasa a una aliniacion de eje z
    if(se_calibro_un_nuevo_offset == 5){
        MarlinUI::goto_screen(advertencia_aliniar_eje_z);

    //si se entra de probar calibracion
    //se pasa a realizar la prueba
    }else{
        MarlinUI::salida_de_G26 = false;

        queue.inject_P(PSTR("G1 X1 Z0 F1000\nG92 E0\nG1 E30 F200\nG92 E0\nG1 X30 F2000\nG28\nG26C"));
        MarlinUI::goto_screen(esperando_que_termine_prueba);
    }
    
}

void info_iniciar_prueba(){
    MarlinUI::defer_return_to_status = true;

    reset_valor_scroll();
    strcpy(MarlinUI::texto_muy_largo, Language_es::MSG_LARGO_PRUEBA);//No hay nada seteado XP

    crear_marco_superior(PSTR(Language_es::MSG_PRUEBA_IMPRESION),0,9);

    crear_texto_centrado(Language_es::MSG_PRUEBA_IMPRESION_00, 12);
    crear_texto_centrado(Language_es::MSG_PRUEBA_IMPRESION_01, 22);
    crear_texto_centrado(Language_es::MSG_PRUEBA_IMPRESION_02, 32);
    crear_texto_centrado(Language_es::MSG_PRUEBA_IMPRESION_03, 42);
    
    crear_marco_superior(Language_es::MSG_CLICK_PARA_CONTINUAR, 54, 11);

    if(ui.use_click()){
        MarlinUI::home_en_accion = false;
        MarlinUI::goto_screen(inicia_la_prueba);
    }
}

//es la espera mientras se esta cargando filamento
void cargar_filamento_visual_para_prueba(){
    //NO se vuelve al status y se sigue actualizando
    MarlinUI::defer_return_to_status = true;
    MarlinUI::lcdDrawUpdate = LCDVIEW_CALL_REDRAW_NEXT;

    contador_repeticiones_para_prueba++;

    if(!queue.has_commands_queued()){
        switch (contador_de_comando_para_prueba) {
            case 0: queue.inject_P(PSTR("G92 E0"));            SERIAL_ECHOLN("1"); contador_de_comando_para_prueba++; break;
            case 1: queue.inject_P(PSTR("G1 E100 F200"));      SERIAL_ECHOLN("2"); contador_de_comando_para_prueba++; break;
        }
    }


    //texto largo
    draw_scroll_message(MarlinUI::get_blink(), 16, 20);

    //crea la barra de espera
    crear_espera();

    crear_marco_superior(Language_es::MSG_CARGANDO_FILAMENTO,0,11);
    crear_marco_superior(Language_es::MSG_POR_FAVOR_ESPERE, 54, 11);
    
    //Obtiene el valor actual del e
    xyze_pos_t npos = cartes;
    npos.e = planner.get_axis_position_mm(E_AXIS);

    if(npos.e >= 100){
        queue.inject_P(PSTR("G92 E0"));
        MarlinUI::goto_screen(cargar_y_retirar_filamento_para_prueba, 1);
    }
}

void retirar_filamento_visual_para_prueba(){
    //NO se vuelve al status y se sigue actualizando
    MarlinUI::defer_return_to_status = true;
    MarlinUI::lcdDrawUpdate = LCDVIEW_CALL_REDRAW_NEXT; 

    contador_repeticiones_para_prueba++;

    //ejecutor de comando
    if(!queue.has_commands_queued()){
        switch (contador_de_comando_para_prueba) {
            case 0: queue.inject_P(PSTR("G92 E0"));         contador_de_comando_para_prueba++; break;
            case 1: queue.inject_P(PSTR("G1 E30 F200"));    contador_de_comando_para_prueba++; break;
            case 2: queue.inject_P(PSTR("G92 E0"));         contador_de_comando_para_prueba++; break;
            case 3: queue.inject_P(PSTR("G1 E-100 F200"));  contador_de_comando_para_prueba++; break;
        }
    }

    //texto largo
    draw_scroll_message(MarlinUI::get_blink(), 16, 20);

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
        MarlinUI::goto_screen(cargar_y_retirar_filamento_para_prueba, 2);
    }
}

void cargar_filamento_para_prueba(){
    reset_valor_scroll();
    strcpy(MarlinUI::texto_muy_largo, Language_es::MSG_LARGO_CARGA); //set de texto largo

    //se mueve al menu de espera de carga de filamento
    contador_de_comando_para_prueba = 0;
    MarlinUI::goto_screen(cargar_filamento_visual_para_prueba);
}

void retirar_filamento_para_prueba(){
    reset_valor_scroll();
    strcpy(MarlinUI::texto_muy_largo, Language_es::MSG_LARGO_RETIRAR); //set de texto largo

    //va al menu de espera
    contador_de_comando_para_prueba = 0;
    MarlinUI::goto_screen(retirar_filamento_visual_para_prueba);
}

void quiere_calibrar_sensibilidad();
//menu de cargar y retirar filamento de calibracion
//se puede entrar a este menu para hacer una prueba de calibracion
//o se puede entrar por una calibracion general
void cargar_y_retirar_filamento_para_prueba(){
    MarlinUI::defer_return_to_status = true;// no vuelve al menu inicial
    
    encoder_der_sup(true);//define el giro del encoder
    
    contador_repeticiones_para_prueba = 0; //reset

    crear_marco_superior(Language_es::MSG_CARGA_Y_DESCARGA);

    START_MENU();
    NEXT_ITEM_(3);
    END_MENU();

    init_boto(30, 5, 3, 17, 4);

    if(se_calibro_un_nuevo_offset == 5)//Se cambia solo el texto para la calibracion general
        crear_boton(seguir_boton_a,  seguir_boton_b,    Language_es::MSG_CALI_TEMP_09_B,    quiere_calibrar_sensibilidad);
    else
        crear_boton(seguir_boton_a,  seguir_boton_b,    Language_es::MSG_CALI_TEMP_09,     inicia_la_prueba);

    crear_boton(cargar_boton_a,  cargar_boton_b,    Language_es::MSG_FILAMENTLOAD,     cargar_filamento_para_prueba);
    crear_boton(retirar_boton_a, retirar_boton_b,   Language_es::MSG_FILAMENTUNLOAD,   retirar_filamento_para_prueba);
}

void advertencia_calibrar_sensibilidad();
//pregunta si se quiere hacer la calibracion de sensibilidas
void quiere_calibrar_sensibilidad(){
    MarlinUI::defer_return_to_status = true;

    START_MENU();
    NEXT_ITEM_(2);
    END_MENU();

    crear_marco_superior(Language_es::MSG_CALIBRAN_SENSI);//Calibrar Sensibilidad

    crear_texto_centrado(Language_es::MSG_CALIBRAN_SENSI_09, 9);//permite a los motores 
    crear_texto_centrado(Language_es::MSG_CALIBRAN_SENSI_10, 19);//Detectar el Origen

    init_boto(23, 5, 2, 29);


    crear_boton(probar_calibracion_a,   probar_calibracion_b,   Language_es::MSG_CALIBRAN_SENSI_11, inicia_la_prueba);
    crear_boton(calibrar_mapa_a,        calibrar_mapa_b,        Language_es::MSG_CALIBRAN_SENSI,    advertencia_calibrar_sensibilidad);
}

//pregunta si hay filamento cargado
void probar_calibracion_filamento(){
    MarlinUI::defer_return_to_status = true;

    START_MENU();
    NEXT_ITEM_(2);
    END_MENU();

    crear_marco_superior(Language_es::MSG_CALI_TEMP_07);// Importante
    init_boto(23, 5, 2, 29);

    if(MarlinUI::calibracion_general_valor){
        crear_boton(probar_calibracion_a,   probar_calibracion_b, Language_es::MSG_CALI_PRUB_SI,    quiere_calibrar_sensibilidad);
    }else{
        crear_boton(probar_calibracion_a,   probar_calibracion_b, Language_es::MSG_CALI_PRUB_SI,    inicia_la_prueba);
    }
    crear_boton(boton_filamento_a,      boton_filamento_b,    Language_es::MSG_CALI_PRUB_NO,    cargar_y_retirar_filamento_para_prueba);


    crear_texto_centrado(Language_es::MSG_CALI_TEMP_05, 9);//Hay Filamento Cargado
    crear_texto_centrado(Language_es::MSG_CALI_TEMP_06, 19);//En La Impresora?
}


void calibracion_general();//para la salida de calibracion general

//tiene dos entradas una para prueba de calibracion
//y la otra entrada es para calibracion general
void temp_probar_calibracion(){
    MarlinUI::defer_return_to_status = true;

    crear_marco_superior(Language_es::MSG_CALI_TEMP_03, 0,  9); //La Impresora Tiene 
    crear_marco_superior(Language_es::MSG_CALI_TEMP_04, 9,  9); //Que Estar Caliente

    START_MENU();
    NEXT_ITEM_(3);
    END_MENU();

    init_boto(23, 2, 3, 24);

    if(se_calibro_un_nuevo_offset == 5){
        crear_boton(boton_volver_a,     boton_volver_b,         Language_es::MSG_VOLVER,         calibracion_general,1);
    }else{
        crear_boton(boton_volver_a,     boton_volver_b,         Language_es::MSG_VOLVER,         menu_kutter_calibracion_con_sensor,5);
    }
    crear_boton(boton_temp_pred_a,  boton_temp_pred_b,      Language_es::MSG_PREDETERMINADO,     temperatura_preset_calibracion,1);
    crear_boton(boton_temp_manual_a,boton_temp_manual_b,    Language_es::MSG_MANUALES,           temperatura_manual_calibracion_hotend, thermalManager.degHotend(0));
}

void inciar_prueba_calibracion(){
    se_calibro_un_nuevo_offset = 3;     // se indica el tipo de salida
    MarlinUI::calibracion_general_valor = false;  //no se una prueba general
    MarlinUI::goto_screen(temp_probar_calibracion, 1);
}


//menu de espera a que se realice un home
//y va al menu de hay filamento
void espera_prueba_home(){
    MarlinUI::defer_return_to_status = true;
    MarlinUI::lcdDrawUpdate = LCDVIEW_CALL_REDRAW_NEXT;

    crear_texto_centrado(Language_es::MSG_AUTO_HOME_ACTION, 20);
    crear_marco_superior(Language_es::MSG_POR_FAVOR_ESPERE, 54, 11);
    crear_espera();
    
    if(MarlinUI::home_en_accion){
        MarlinUI::goto_screen(probar_calibracion_filamento, 1);
    }
}

//Prueba de calibracion final
/////////////////////////////

//////////////////////////////////////////////////
//Una peque;a parte del editar mapa de cama inicio

//pregunta si hay filamento cargado
void editar_mapa_de_cama(){
    START_MENU();
    NEXT_ITEM_(2);
    END_MENU();

    //si se quiere mover al punto preguta si queres calentar
    se_calibro_un_nuevo_offset = 4;

    crear_marco_superior(Language_es::MSG_MAPA_CAMA);// Importante

    crear_texto_centrado(Language_es::MSG_CALI_TEMP_10, 9);//Quiere mover la
    crear_texto_centrado(Language_es::MSG_CALI_TEMP_11, 19);//impresora al punto?

    init_boto(23, 5, 2, 29);

    crear_boton(editar_mapa_a,  editar_mapa_b,  Language_es::MSG_NO,     ver_mapa_de_cama);
    crear_boton(calibrar_mapa_a,calibrar_mapa_b,Language_es::MSG_YES,    cal_offset_temp); //preguta de tempertura
}

//Una peque;a parte del editar mapa de cama final
/////////////////////////////////////////////////

//inicio otras calibraciones

void otras_calibraciones(){
    MarlinUI::defer_return_to_status = false; //se vuelve al menu pricipal si paso mucho tiempo

    //encoderLine indica la pocision del encoder
    //establese el rango del encoder de 0 / x-1
    START_MENU();
    NEXT_ITEM_(3);
    END_MENU();

    crear_marco_superior(Language_es::MSG_CALI_OTROS_00);

    //crear_texto_centrado(Language_es::MSG_CALI_TEMP_10, 9);
    //crear_texto_centrado(Language_es::MSG_CALI_TEMP_11, 19);


    init_boto(23, 2, 3, 21);

    crear_boton(boton_volver_a,         boton_volver_b,         Language_es::MSG_VOLVER,                menu_kutter_calibracion_con_sensor,  4);
    crear_boton(calibrar_automatico_a,  calibrar_automatico_b,  Language_es::MSG_DELTA_AUTO_CALIBRATE,  calibrar_automa_temp,   1); //4 Calibracion automatica con el mismo offset
    crear_boton(calibrar_precisa_a,     calibrar_precisa_b,     Language_es::MSG_CALI_PRECISA,          calibracion_precisa,    1); //5 Calibracion Precisa

}

//final otras calibraciones
////////////////////////////

////////////////////////////
//Inicio calibracion general

void empezar_cali_general(){
    se_calibro_un_nuevo_offset = 5;     //indica el tipo de salida
    MarlinUI::calibracion_general_valor = true;   //indica que es una prueba general

    MarlinUI::goto_screen(temp_probar_calibracion, 1);
}

void calibracion_general(){
    MarlinUI::defer_return_to_status = false; //se vuelve al menu pricipal si paso mucho tiempo

    START_MENU();
    NEXT_ITEM_(2);
    END_MENU();

    crear_marco_superior(Language_es::MSG_CALI_GENERAL_00);
    
    crear_texto_centrado(Language_es::MSG_CALI_GENERAL_01, 9);
    crear_texto_centrado(Language_es::MSG_CALI_GENERAL_02, 18);

    init_boto(23, 5, 2, 29);

    crear_boton(boton_detener_a,     boton_detener_b,     Language_es::MSG_BUTTON_CANCEL,   menu_kutter_calibracion_con_sensor, 1);
    crear_boton(boton_reanudar_a,    boton_reanudar_b,    Language_es::MSG_CALI_EMPEZAR,    empezar_cali_general);
}

//final calibracion general
///////////////////////////


///////////////////////////
bool valor_super_aux = true;

void prueba_de_textos_largos(){
    MarlinUI::defer_return_to_status = true;
    MarlinUI::lcdDrawUpdate = LCDVIEW_CALL_REDRAW_NEXT;

    draw_scroll_message(MarlinUI::get_blink(), 16, 20);
    //crea la barra de espera
    crear_espera();
}

void ir_prueba_texto_largo(){
    strcpy(MarlinUI::texto_muy_largo, "La Maquina Esta Midiendo Los Puntos De La Cama, Para Correguir La Altura Durante La Impresion");

    MarlinUI::goto_screen(prueba_de_textos_largos);
}

///////////////////////////



////////////////
//prueba
#if ENABLED(PK3_Plus_Plus) || ENABLED(PK3_Plus_Ext)
#define PRUEBA_OFFSET             \
"G28\n                            \
G1 Z5 F5000\n                     \
G1 X5 Y5 F2000\n                  \
G92 E0\n                          \
G1 F200 E10\n                     \
G90\n                             \
M83\n                             \
G92 E0\n                          \
G1 E-6.00000 F2100.000\n          \
G1 Z0.260 F6000.000\n             \
G1 X164.715 Y209.800\n            \
G1 E6.00000 F2400.000\n           \
M204 S500\n                       \
G1 F1200.000\n                    \
G1 X164.939 Y209.800 E0.01223\n   \
G1 X164.715 Y209.800 F6000.000\n  \
G1 F1200.000\n                    \
G1 X105.400 Y209.800 E3.24101\n   \
G1 X105.234 Y209.766 E0.00925\n   \
G1 X105.200 Y209.600 E0.00925\n   \
G1 X105.200 Y202.800 E0.37156\n   \
G1 X105.234 Y202.634 E0.00925\n   \
G1 X105.400 Y202.600 E0.00925\n   \
G1 X164.600 Y202.600 E3.23473\n   \
G1 X164.766 Y202.566 E0.00925\n   \
G1 X164.800 Y202.400 E0.00925\n   \
G1 X164.800 Y195.600 E0.37156\n   \
G1 X164.766 Y195.434 E0.00925\n   \
G1 X164.600 Y195.400 E0.00925\n   \
G1 X105.400 Y195.400 E3.23473\n   \
G1 X105.234 Y195.366 E0.00925\n   \
G1 X105.200 Y195.200 E0.00925\n   \
G1 X105.200 Y188.400 E0.37156\n   \
G1 X105.234 Y188.234 E0.00925\n   \
G1 X105.400 Y188.200 E0.00925\n   \
G1 X164.600 Y188.200 E3.23473\n   \
G1 X164.766 Y188.166 E0.00925\n   \
G1 X164.800 Y188.000 E0.00925\n   \
G1 X164.800 Y181.200 E0.37156\n   \
G1 X164.766 Y181.034 E0.00925\n   \
G1 X164.600 Y181.000 E0.00925\n   \
G1 X105.400 Y181.000 E3.23473\n   \
G1 X105.234 Y180.966 E0.00925\n   \
G1 X105.200 Y180.800 E0.00925\n   \
G1 X105.200 Y174.000 E0.37156\n   \
G1 X105.234 Y173.834 E0.00925\n   \
G1 X105.400 Y173.800 E0.00925\n   \
G1 X164.600 Y173.800 E3.23473\n   \
G1 X164.766 Y173.766 E0.00925\n   \
G1 X164.800 Y173.600 E0.00925\n   \
G1 X164.800 Y166.800 E0.37156\n   \
G1 X164.766 Y166.634 E0.00925\n   \
G1 X164.600 Y166.600 E0.00925\n   \
G1 X105.400 Y166.600 E3.23473\n   \
G1 X105.234 Y166.566 E0.00925\n   \
G1 X105.200 Y166.400 E0.00925\n   \
G1 X105.200 Y159.600 E0.37156\n   \
G1 X105.234 Y159.434 E0.00925\n   \
G1 X105.400 Y159.400 E0.00925\n   \
G1 X164.600 Y159.400 E3.23473\n   \
G1 X164.766 Y159.366 E0.00925\n   \
G1 X164.800 Y159.200 E0.00925\n   \
G1 X164.800 Y152.400 E0.37156\n   \
G1 X164.766 Y152.234 E0.00925\n   \
G1 X164.600 Y152.200 E0.00925\n   \
G1 X105.400 Y152.200 E3.23473\n   \
G1 X105.234 Y152.166 E0.00925\n   \
G1 X105.200 Y152.000 E0.00925\n   \
G1 X105.200 Y145.200 E0.37156\n   \
G1 X105.234 Y145.034 E0.00925\n   \
G1 X105.400 Y145.000 E0.00925\n   \
G1 X164.600 Y145.000 E3.23473\n   \
G1 X164.766 Y144.966 E0.00925\n   \
G1 X164.800 Y144.800 E0.00925\n   \
G1 X164.800 Y138.000 E0.37156\n   \
G1 X164.766 Y137.834 E0.00925\n   \
G1 X164.600 Y137.800 E0.00925\n   \
G1 X105.400 Y137.800 E3.23473\n   \
G1 X105.234 Y137.766 E0.00925\n   \
G1 X105.200 Y137.600 E0.00925\n   \
G1 X105.200 Y130.400 E0.39341\n   \
G1 X105.234 Y130.234 E0.00925\n   \
G1 X105.400 Y130.200 E0.00925\n   \
G1 X164.939 Y130.200 E3.25324\n   \
G1 E-4.20000 F2100.000\n          \
G1 F4800.000\n                    \
G1 X160.824 Y130.200 E-1.71000\n  \
G1 E-0.09000 F2100.000\n          \
G28 X0\n                          \
M117 Prueba Realizada\n"
#else
#define PRUEBA_OFFSET             \
"G28\n                            \
G1 Z5 F5000\n                     \
G1 X5 Y5 F2000\n                  \
G92 E0\n                          \
G1 F200 E10\n                     \
G90\n                             \
M83\n                             \
G92 E0\n                          \
G1 E-6.00000 F2100.000\n          \
G1 Z0.260 F6000.000\n             \
G1 X164.715 Y159.800\n            \
G1 E6.00000 F2400.000\n           \
M204 S500\n                       \
G1 F1200.000\n                    \
G1 X164.939 Y159.800 E0.01223\n   \
G1 X164.715 Y159.800 F6000.000\n  \
G1 F1200.000\n                    \
G1 X105.400 Y159.800 E3.24101\n   \
G1 X105.234 Y159.766 E0.00925\n   \
G1 X105.200 Y159.600 E0.00925\n   \
G1 X105.200 Y152.800 E0.37156\n   \
G1 X105.234 Y152.634 E0.00925\n   \
G1 X105.400 Y152.600 E0.00925\n   \
G1 X164.600 Y152.600 E3.23473\n   \
G1 X164.766 Y152.566 E0.00925\n   \
G1 X164.800 Y152.400 E0.00925\n   \
G1 X164.800 Y145.600 E0.37156\n   \
G1 X164.766 Y145.434 E0.00925\n   \
G1 X164.600 Y145.400 E0.00925\n   \
G1 X105.400 Y145.400 E3.23473\n   \
G1 X105.234 Y145.366 E0.00925\n   \
G1 X105.200 Y145.200 E0.00925\n   \
G1 X105.200 Y138.400 E0.37156\n   \
G1 X105.234 Y138.234 E0.00925\n   \
G1 X105.400 Y138.200 E0.00925\n   \
G1 X164.600 Y138.200 E3.23473\n   \
G1 X164.766 Y138.166 E0.00925\n   \
G1 X164.800 Y138.000 E0.00925\n   \
G1 X164.800 Y131.200 E0.37156\n   \
G1 X164.766 Y131.034 E0.00925\n   \
G1 X164.600 Y131.000 E0.00925\n   \
G1 X105.400 Y131.000 E3.23473\n   \
G1 X105.234 Y130.966 E0.00925\n   \
G1 X105.200 Y130.800 E0.00925\n   \
G1 X105.200 Y124.000 E0.37156\n   \
G1 X105.234 Y123.834 E0.00925\n   \
G1 X105.400 Y123.800 E0.00925\n   \
G1 X164.600 Y123.800 E3.23473\n   \
G1 X164.766 Y123.766 E0.00925\n   \
G1 X164.800 Y123.600 E0.00925\n   \
G1 X164.800 Y116.800 E0.37156\n   \
G1 X164.766 Y116.634 E0.00925\n   \
G1 X164.600 Y116.600 E0.00925\n   \
G1 X105.400 Y116.600 E3.23473\n   \
G1 X105.234 Y116.566 E0.00925\n   \
G1 X105.200 Y116.400 E0.00925\n   \
G1 X105.200 Y109.600 E0.37156\n   \
G1 X105.234 Y109.434 E0.00925\n   \
G1 X105.400 Y109.400 E0.00925\n   \
G1 X164.600 Y109.400 E3.23473\n   \
G1 X164.766 Y109.366 E0.00925\n   \
G1 X164.800 Y109.200 E0.00925\n   \
G1 X164.800 Y102.400 E0.37156\n   \
G1 X164.766 Y102.234 E0.00925\n   \
G1 X164.600 Y102.200 E0.00925\n   \
G1 X105.400 Y102.200 E3.23473\n   \
G1 X105.234 Y102.166 E0.00925\n   \
G1 X105.200 Y102.000 E0.00925\n   \
G1 X105.200 Y95.200 E0.37156\n    \
G1 X105.234 Y95.034 E0.00925\n    \
G1 X105.400 Y95.000 E0.00925\n    \
G1 X164.600 Y95.000 E3.23473\n    \
G1 X164.766 Y94.966 E0.00925\n    \
G1 X164.800 Y94.800 E0.00925\n    \
G1 X164.800 Y88.000 E0.37156\n    \
G1 X164.766 Y87.834 E0.00925\n    \
G1 X164.600 Y87.800 E0.00925\n    \
G1 X105.400 Y87.800 E3.23473\n    \
G1 X105.234 Y87.766 E0.00925\n    \
G1 X105.200 Y87.600 E0.00925\n    \
G1 X105.200 Y80.400 E0.39341\n    \
G1 X105.234 Y80.234 E0.00925\n    \
G1 X105.400 Y80.200 E0.00925\n    \
G1 X164.939 Y80.200 E3.25324\n    \
G1 E-4.20000 F2100.000\n          \
G1 F4800.000\n                    \
G1 X160.824 Y80.200 E-1.71000\n   \
G1 E-0.09000 F2100.000\n          \
G28 X0\n                          \
M117 Prueba Realizada\n"
#endif
//preuba
////////////////

/////////////////////////
//inicio prueba de offset
void prueba_de_offset();

void menu_realizar_prueba_si_no(){
    MarlinUI::defer_return_to_status = true;

    START_MENU();
    NEXT_ITEM_(2);
    END_MENU();

    crear_marco_superior(Language_es::MSG_PRUEBA_IMPRESION);

    crear_texto_centrado(Language_es::MSG_PRUEBA_SI, 9);
    crear_texto_centrado(Language_es::MSG_PRUEBA_NO, 19);

    init_boto(23, 5, 2, 29);

    crear_boton(boton_volver_a,         boton_volver_b,         Language_es::MSG_PRUEBA_OFFSET_VOLVER,  menu_kutter_calibracion_con_sensor, 1);
    crear_boton(probar_calibracion_a,   probar_calibracion_b,   Language_es::MSG_CALI_PRUEBA,           info_iniciar_prueba);
}

void prueba_de_offset_retire_imprecion(){
    MarlinUI::defer_return_to_status = true;

    crear_marco_superior(PSTR(Language_es::MSG_PRUEBA_OFFSET_OFFSET),0,9);

    crear_texto_centrado(Language_es::MSG_PRUEBA_IMPRESION_06, 17);
    crear_texto_centrado(Language_es::MSG_PRUEBA_IMPRESION_07, 27);
    crear_texto_centrado(Language_es::MSG_PRUEBA_IMPRESION_08_B, 37);
    
    crear_marco_superior(Language_es::MSG_CLICK_PARA_CONTINUAR, 54, 11);

    if(ui.use_click()){
        MarlinUI::goto_screen(prueba_de_offset);
    }
}

void prueba_de_offset_retire_imprecion_salida(){
    MarlinUI::defer_return_to_status = true;

    crear_marco_superior(PSTR(Language_es::MSG_PRUEBA_OFFSET_OFFSET),0,9);

    crear_texto_centrado(Language_es::MSG_PRUEBA_IMPRESION_06, 17);
    crear_texto_centrado(Language_es::MSG_PRUEBA_IMPRESION_07, 27);
    crear_texto_centrado(Language_es::MSG_PRUEBA_IMPRESION_08_B, 37);
    
    crear_marco_superior(Language_es::MSG_CLICK_PARA_CONTINUAR, 54, 11);

    if(ui.use_click()){
        MarlinUI::goto_screen(menu_realizar_prueba_si_no, 1); //salida prueba de offset
    }
}

void menu_volver_prueba_de_offset(){
    MarlinUI::defer_return_to_status = true;

    START_MENU();
    NEXT_ITEM_(2);
    END_MENU();

    crear_marco_superior(Language_es::MSG_PRUEBA_IMPRESION);

    crear_texto_centrado(Language_es::MSG_PRUEBA_IMPRESION_04, 9);
    crear_texto_centrado(Language_es::MSG_PRUEBA_IMPRESION_05_B, 19);

    init_boto(23, 5, 2, 29);

    crear_boton(boton_detener_a,    boton_detener_b,    Language_es::MSG_PRUEBA_MAL,    prueba_de_offset_retire_imprecion);
    crear_boton(boton_tilde_a,      boton_tilde_b,      Language_es::MSG_PRUEBA_BIEN,   prueba_de_offset_retire_imprecion_salida); 
}

//guarda el valor modificado del offset
void guarda_valor_de_prueba_oofset(){
    MarlinUI::contenedor_str[0] = '\0';
    strcpy(MarlinUI::contenedor_str, "G1 Y");
    strcat(MarlinUI::contenedor_str, i16tostr4signrj(Y_BED_SIZE - 20));
    strcat(MarlinUI::contenedor_str, " F2000");

    queue.inject_P(PSTR(MarlinUI::contenedor_str));

    const float mps1 = planner.mm_per_step[Z_AXIS];
    probe.offset.z = probe.offset.z + (mps1 * babystep.accum);

    (void)settings.save();

    return MarlinUI::goto_screen(menu_volver_prueba_de_offset,1);
}

//permite cambiar el offset mientras se hace la prueva
void espera_prueba_de_offser() {
    MarlinUI::defer_return_to_status = true;
    MarlinUI::lcdDrawUpdate = LCDVIEW_CALL_REDRAW_NEXT;

    crear_marco_superior(Language_es::MSG_CALI_TEMP_08);
    crear_marco_superior(Language_es::MSG_PRUEBA_OFFSET_ENDCODER_01,46);
    crear_marco_superior(Language_es::MSG_PRUEBA_OFFSET_ENDCODER_02,55);

    if (ui.encoderPosition) {
      const int16_t steps = int16_t(ui.encoderPosition) * (
        BABYSTEP_SIZE_Z
      );
      ui.encoderPosition = 0;

      babystep.add_steps(Z_AXIS, steps);
    }
    if (ui.should_draw()) {
      const float mps = planner.mm_per_step[Z_AXIS];
      MenuEditItemBase::draw_edit_screen(GET_TEXT(MSG_ZPROBE_ZOFFSET), BABYSTEP_TO_STR((mps * babystep.accum) + probe.offset.z));
    }

    if(ui.use_click()){
        prender_y_apagar_led_calibracion();
    }

    if(MarlinUI::salida_M117){
        MarlinUI::goto_screen(guarda_valor_de_prueba_oofset);
    }
}

//entradp a la prueba de offset
void prueba_de_offset(){
    babystep.accum = 0;
    MarlinUI::salida_M117 = false;
    queue.inject_P(PSTR(PRUEBA_OFFSET));
    SERIAL_ECHOLN(PRUEBA_OFFSET);
    MarlinUI::goto_screen(espera_prueba_de_offser);
}

void info_prueba_de_offset(){
    MarlinUI::defer_return_to_status = true;

    crear_marco_superior(PSTR(Language_es::MSG_PRUEBA_OFFSET_OFFSET),0,9);

    crear_texto_centrado(Language_es::MSG_PRUEBA_OFFSET_INFO_01, 12);
    crear_texto_centrado(Language_es::MSG_PRUEBA_OFFSET_INFO_02, 22);
    crear_texto_centrado(Language_es::MSG_PRUEBA_OFFSET_INFO_03, 32);
    crear_texto_centrado(Language_es::MSG_PRUEBA_OFFSET_INFO_04, 42);
    
    crear_marco_superior(Language_es::MSG_CLICK_PARA_CONTINUAR, 54, 11);

    if(ui.use_click()){
        MarlinUI::goto_screen(prueba_de_offset);
    }
}

//final prueba de offset
////////////////////////



void _ubl_goto_map_screen();

void menu_kutter_calibracion_con_sensor(){
    MarlinUI::defer_return_to_status = false; //se vuelve al menu pricipal si paso mucho tiempo
    MarlinUI::calibracion_general_valor = false;

    //encoderLine indica la pocision del encoder
    //establese el rango del encoder de 0 / x-1
    START_MENU();
    NEXT_ITEM_(8);
    END_MENU();

    init_boto(23, 2, 4, 3);

    //crear_marco_superior(Language_es::MSG_CALIBRATE);

    crear_boton(boton_volver_a,         boton_volver_b,         Language_es::MSG_VOLVER,                menu_main,  4);             //1 Volver
    crear_boton(calibracion_general_a,  calibracion_general_b,  Language_es::MSG_CALI_GENERAL_00,       calibracion_general,    1); //4 Calibración general
    crear_boton(calibrar_offset_a,      calibrar_offset_b,      Language_es::MSG_CALIBRAR_OFFSET,       calibrar_offset_temp,   1); //2 Calibra el offset y despues crea una malla
    crear_boton(modificar_offset_a,     modificar_offset_b,     Language_es::MSG_MODIFICAR_OFFSET,      cal_offset_actual,      1); //3 Modificar Offset

    crear_boton(completar_mapa_a,       completar_mapa_b,       Language_es::MSG_CALI_OTROS_00,         otras_calibraciones,    1);     //5 Otras calibraciones
    crear_boton(probar_calibracion_a,   probar_calibracion_b,   Language_es::MSG_CALI_PRUEBA,           info_iniciar_prueba,    1);     //6 Probar calibracion
    crear_boton(mapa_de_cama_a,         mapa_de_cama_b,         Language_es::MSG_MAPA_CAMA,             editar_mapa_de_cama);           //7 Mapa de calibracion
    crear_boton(aliniar_eje_z_a,        aliniar_eje_z_b,        Language_es::MSG_ALINEAR_Z,             advertencia_aliniar_eje_z);     //8 Alineacion del eje Z

}
#endif

#endif // MENU_KUTTERCRAFT
#endif // HAS_LCD_MENU