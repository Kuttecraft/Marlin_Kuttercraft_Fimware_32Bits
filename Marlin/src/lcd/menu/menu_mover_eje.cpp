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
void crear_boton(const u8g_pgm_uint8_t* img_mapa_bit, const u8g_pgm_uint8_t* img_mapa_bit_2, PGM_P utf8_str_P, screenFunc_t screen, const uint16_t encoder = 0);
void crear_marco_superior(PGM_P utf8_str_P, int altura = 0, int largo = 9);
void encoder_der_sup(bool dereccion_encoder = true);


//salidas
void menu_main();
void mover_o_home();
void distancia_mover();
void mover_eje();
void realizar_home();

//variables internas
AxisEnum eje_seleccionado;

void mover_xyz(const AxisEnum axis) {
  //NO se vuelve al status y se sigue actualizando
  //MarlinUI::defer_return_to_status = true;
  encoder_der_sup(false);
  MarlinUI::lcdDrawUpdate = LCDVIEW_CALL_REDRAW_NEXT;

  if (ui.encoderPosition && !ui.manual_move.processing) {
    
    float min, max;
    soft_endstop.get_manual_axis_limits(axis, min, max);

    const float diff = float(int32_t(ui.encoderPosition)) * ui.manual_move.menu_scale;


    current_position[axis] += diff;
    if (int32_t(ui.encoderPosition) < 0){
      NOLESS(current_position[axis], min);
    }
    else{
      if(axis == X_AXIS){
        NOMORE(current_position[axis], 230);
      }else{
        NOMORE(current_position[axis], max);
      }
    }

    ui.manual_move.soon(axis);
  }
  
  ui.encoderPosition = 0;

  if (ui.should_draw()) {
    const float pos = NATIVE_TO_LOGICAL(
      ui.manual_move.processing ? destination[axis] : current_position[axis] + TERN0(IS_KINEMATIC, ui.manual_move.offset),
      axis
    );
    if(axis == X_AXIS)
      MenuEditItemBase::draw_edit_screen(GET_TEXT(MSG_MOVE_X), ui.manual_move.menu_scale >= 0.1f ? ftostr41sign(pos) : ftostr63(pos));
    else if(axis == Y_AXIS)
      MenuEditItemBase::draw_edit_screen(GET_TEXT(MSG_MOVE_Y), ui.manual_move.menu_scale >= 0.1f ? ftostr41sign(pos) : ftostr63(pos));
    else
      MenuEditItemBase::draw_edit_screen(GET_TEXT(MSG_MOVE_Z), ui.manual_move.menu_scale >= 0.1f ? ftostr41sign(pos) : ftostr63(pos));
  }

    //encargado de la redirección de salida
  if (ui.use_click()){
    //salida ordenada
    if(ui.manual_move.menu_scale == 0.1){
      ui.encoderPosition = 1;
      MarlinUI::goto_screen(distancia_mover,1);
    }else if(ui.manual_move.menu_scale == 1.0){
      ui.encoderPosition = 2;
      MarlinUI::goto_screen(distancia_mover,2);
    }else{
      ui.encoderPosition = 3;
      MarlinUI::goto_screen(distancia_mover,3);
    }
  }
} 


void mover_01mm(){
  ui.manual_move.menu_scale = 0.1;
  mover_xyz(eje_seleccionado); 
}
void mover_1mm(){
  ui.manual_move.menu_scale = 1;
  mover_xyz(eje_seleccionado);
}
void mover_5mm(){
  ui.manual_move.menu_scale = 5;
  mover_xyz(eje_seleccionado);
}

void distancia_mover(){
  //determina como tiene queser la vuelta
  int volver_aux = 0;

  if(eje_seleccionado == X_AXIS)
    volver_aux = 1;
  else if(eje_seleccionado == Y_AXIS)
    volver_aux = 2;
  else
    volver_aux = 3;
  
    
  crear_marco_superior(Language_es::MSG_MOVE_AXIS, 0, 11);

  START_MENU();
  NEXT_ITEM_(4);
  END_MENU();

  init_boto(23, 2, 4, 21);

  crear_boton(boton_volver_a, boton_volver_b, Language_es::MSG_VOLVER,       mover_eje, volver_aux);
  crear_boton(boton_01_a,     boton_01_b,     Language_es::MSG_MOVE_01MM,    mover_01mm);
  crear_boton(boton_1_a,      boton_1_b,      Language_es::MSG_MOVE_1MM,     mover_1mm);
  crear_boton(boton_5_a,      boton_5_b,      Language_es::MSG_MOVE_10MM,    mover_5mm);
} 

void seleccionar_eje_x(){
  eje_seleccionado = X_AXIS;
  MarlinUI::goto_screen(distancia_mover);
}
void seleccionar_eje_y(){
  eje_seleccionado = Y_AXIS;
  MarlinUI::goto_screen(distancia_mover);
}
void seleccionar_eje_z(){
  eje_seleccionado = Z_AXIS;
  MarlinUI::goto_screen(distancia_mover);
}

void mover_eje(){
    crear_marco_superior(Language_es::MSG_MOVE_AXIS, 0, 11);

    START_MENU();
    NEXT_ITEM_(4);
    END_MENU();

    init_boto(23, 2, 4, 21);

    crear_boton(boton_volver_a, boton_volver_b, Language_es::MSG_VOLVER,       mover_o_home, 1);
    crear_boton(boton_x_a,      boton_x_b,      Language_es::MSG_MOVE_X,       seleccionar_eje_x);
    crear_boton(boton_y_a,      boton_y_b,      Language_es::MSG_MOVE_Y,       seleccionar_eje_y);
    crear_boton(boton_z_a,      boton_z_b,      Language_es::MSG_MOVE_Z,       seleccionar_eje_z);
}

void realizar_home_xyz(){
  queue.inject_P(PSTR("G28"));
  MarlinUI::goto_screen(realizar_home,1);
}
void realizar_home_x(){
  queue.inject_P(PSTR("G28X"));
  MarlinUI::goto_screen(realizar_home,2);
}
void realizar_home_y(){
  queue.inject_P(PSTR("G28Y"));
  MarlinUI::goto_screen(realizar_home,3);
}
void realizar_home_z(){
  queue.inject_P(PSTR("G28Z"));
  MarlinUI::goto_screen(realizar_home,4);
}

void realizar_home(){
  crear_marco_superior(Language_es::MSG_AUTO_HOME, 0, 11);

  START_MENU();
  NEXT_ITEM_(5);
  END_MENU();

  init_boto(23, 2, 5, 21);

  crear_boton(boton_volver_a, boton_volver_b, Language_es::MSG_VOLVER,            mover_o_home, 2);
  crear_boton(boton_inicio_a, boton_inicio_b, Language_es::MSG_LEVEL_BED_HOMING,  realizar_home_xyz);
  crear_boton(boton_x_a,      boton_x_b,      Language_es::MSG_AUTO_HOME_X,       realizar_home_x);
  crear_boton(boton_y_a,      boton_y_b,      Language_es::MSG_AUTO_HOME_Y,       realizar_home_y);
  crear_boton(boton_z_a,      boton_z_b,      Language_es::MSG_AUTO_HOME_Z,       realizar_home_z);
}

void mover_o_home(){
    crear_marco_superior(Language_es::MSG_MOVE_AXIS, 0, 11);

    START_MENU();
    NEXT_ITEM_(3);
    END_MENU();

    init_boto(30, 5, 3, 17, 4);

    crear_boton(volver_boton_a, volver_boton_b, Language_es::MSG_VOLVER,    menu_main,  6);
    crear_boton(mover_boton_a,  mover_boton_b,  Language_es::MSG_MOVE_AXIS, mover_eje);
    crear_boton(home_boton_a,   home_boton_b,   Language_es::MSG_AUTO_HOME, realizar_home);
}



#endif // MENU_KUTTERCRAFT
#endif // HAS_LCD_MENU