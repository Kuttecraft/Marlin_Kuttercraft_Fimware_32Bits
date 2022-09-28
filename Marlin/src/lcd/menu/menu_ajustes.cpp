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
#include "../../feature/bedlevel/bedlevel.h"
#include "../../feature/powerloss.h"
#include "../dogm/fontdata/fontdata_ISO10646_1.h"
#include "../../feature/tmc_util.h"
#include "../../module/stepper/indirection.h"

#include "../../module/printcounter.h"


//constructores de menu
void crear_marco_superior(PGM_P utf8_str_P, int altura = 0, int largo = 9);
void menu_main();
void menu_ajustes();
void removeSpacesInPlace(char* str);
void menu_logros();
void crear_cartel_si_no();
void init_boto(int medida_boton_, int espaciado_, int cantidad_, int altura_, int columna_bit_ = 3);
void crear_boton(const u8g_pgm_uint8_t* img_mapa_bit, const u8g_pgm_uint8_t* img_mapa_bit_2, PGM_P utf8_str_P, screenFunc_t screen, const uint16_t encoder = 0);
void opciones_no_disponible(screenFunc_t screen, const uint16_t encoder = 0);
int centrar_texto(int numero, int grande_de_letra = 6);
void crear_texto_centrado(PGM_P utf8_str_P, int altura = 0);
void menu_tmc();
void crear_espera();

//SALIDA
void calcular_pid();

//Variable
uint32_t valorEncoderMenu, posicionMenu;

void salida_menu_ajuste(){MarlinUI::goto_screen(menu_ajustes, valorEncoderMenu, posicionMenu);} //sirve para volver al menu ajustes desde cualquie sub menu

//cartel de vercion
///////////////////
void menu_vercion(){
    u8g.drawBitmapP(23, 0, 10, 12, logo_kuttercraft);

    #if (MOTHERBOARD == BOARD_BTT_SKR_V1_4_TURBO)
      u8g.setFont(u8g_font_4x6);
      lcd_moveto(100, 8);   // posicion del texto
      lcd_put_u8str_P(PSTR(Language_es::MSG_TURBO__)); // el texto
    #endif

    #if (MOTHERBOARD == BOARD_BTT_SKR_V2_0_REV_B)
      u8g.setFont(u8g_font_4x6);
      lcd_moveto(100, 8);   // posicion del texto
      lcd_put_u8str_P(PSTR(Language_es::MSG_SKR2__)); // el texto
    #endif

    #if ENABLED(FICHA_MOTOR)
      //MSG_FICHA__
      u8g.setFont(u8g_font_4x6);
      lcd_moveto(100, 14);
      lcd_put_u8str_P(PSTR(Language_es::MSG_FICHA__));
    #endif
    
    u8g.setFont(u8g_font_6x10);

    crear_marco_superior(Language_es::MSG_SERIE, 35);
    crear_texto_centrado(MarlinUI::numero_de_serie, 45);
    
    crear_marco_superior(Language_es::MSG_INDUSTRIA, 55);

    lcd_moveto(12, 22);   // posicion del texto
    lcd_put_u8str_P(PSTR(Language_es::MSG_VER_VERSION)); // el texto

    lcd_moveto(18, 32);   // posicion del texto
    lcd_put_u8str_P(PSTR(Language_es::MSG_VER_MODELO)); // el texto

    lcd_moveto(66, 22);   // posicion del texto
    lcd_put_u8str_P(PSTR(SHORT_BUILD_VERSION));

    lcd_moveto(66, 32);   // posicion del texto
    lcd_put_u8str_P(PSTR(MODELO_DE_MAQUINA));

    if(ui.use_click()){
      MarlinUI::goto_screen(menu_ajustes, valorEncoderMenu, posicionMenu); //vuelve a la ultima posicion
    }
}


////////////////////////
//menu de estadisticas//
////////////////////////
#if ENABLED(PRINTCOUNTER)
void estadisticas_impreciones(){
    printStatistics stats = print_job_timer.getStats();
    MarlinUI::contenedor_str[0] = '\0';

    crear_marco_superior(Language_es::MSG_INFO_STATS_MENU);
    crear_marco_superior(Language_es::MSG_IMPRESIONES,55);

    //textos
    lcd_moveto(40, 22);   // posicion del texto
    lcd_put_u8str_P(PSTR(Language_es::MSG_TOTAL));

    lcd_moveto(10, 35);   // posicion del texto
    lcd_put_u8str_P(PSTR(Language_es::MSG_TERMINADAS));

    lcd_moveto(4, 48);   // posicion del texto
    lcd_put_u8str_P(PSTR(Language_es::MSG_INCOMPLETAS));

    //kilometros
    ////////////
    strcpy(MarlinUI::contenedor_str, i16tostr3left(stats.totalPrints) ); //guarda el valor en el contenedor
    removeSpacesInPlace(MarlinUI::contenedor_str); //elimina los espacios en blanco generado por la tranformacion
    lcd_moveto(76, 22);
    lcd_put_u8str(MarlinUI::contenedor_str);

    //metro
    ///////
    strcpy(MarlinUI::contenedor_str, i16tostr3left(stats.finishedPrints) ); //guarda el valor en el contenedor
    removeSpacesInPlace(MarlinUI::contenedor_str); //elimina los espacios en blanco generado por la tranformacion
    lcd_moveto(76, 35);
    lcd_put_u8str(MarlinUI::contenedor_str);

    //centimetro
    ////////////
    strcpy(MarlinUI::contenedor_str, i16tostr3left(stats.totalPrints - stats.finishedPrints) ); //guarda el valor en el contenedor
    removeSpacesInPlace(MarlinUI::contenedor_str); //elimina los espacios en blanco generado por la tranformacion
    lcd_moveto(76, 48);
    lcd_put_u8str(MarlinUI::contenedor_str);

    if(ui.use_click()){
      MarlinUI::goto_screen(menu_ajustes, MarlinUI::endcoder_ulti_aux);
    }
}

void estadisticas_horas(){
    printStatistics stats = print_job_timer.getStats();
    MarlinUI::contenedor_str[0] = '\0';

    crear_marco_superior(Language_es::MSG_INFO_STATS_MENU);
    crear_marco_superior(Language_es::MSG_TIEMPO_DE_IMPRESION,55);

    //textos
    lcd_moveto(46, 22);   // posicion del texto
    lcd_put_u8str_P(PSTR(Language_es::MSG_TIEMPO_DIAS));

    lcd_moveto(40, 35);   // posicion del texto
    lcd_put_u8str_P(PSTR(Language_es::MSG_TIEMPO_HORAS));

    lcd_moveto(28, 48);   // posicion del texto
    lcd_put_u8str_P(PSTR(Language_es::MSG_TIEMPO_MINUTOS));

    //Años
    //////
    strcpy(MarlinUI::contenedor_str, i16tostr3left(duration_t(stats.printTime).day()% 24) ); //guarda el valor en el contenedor
    removeSpacesInPlace(MarlinUI::contenedor_str); //elimina los espacios en blanco generado por la tranformacion
    lcd_moveto(76, 22);
    lcd_put_u8str(MarlinUI::contenedor_str);

    //dias
    //////
    strcpy(MarlinUI::contenedor_str, i16tostr3left(duration_t(stats.printTime).hour() % 60) ); //guarda el valor en el contenedor
    removeSpacesInPlace(MarlinUI::contenedor_str); //elimina los espacios en blanco generado por la tranformacion
    lcd_moveto(76, 35);
    lcd_put_u8str(MarlinUI::contenedor_str);

    //horas
    ///////
    strcpy(MarlinUI::contenedor_str, i16tostr3left(duration_t(stats.printTime).minute() % 60) ); //guarda el valor en el contenedor
    removeSpacesInPlace(MarlinUI::contenedor_str); //elimina los espacios en blanco generado por la tranformacion
    lcd_moveto(76, 48);
    lcd_put_u8str(MarlinUI::contenedor_str);

    if(ui.use_click()){
      MarlinUI::goto_screen(estadisticas_impreciones);
    }
}

void estadisticas(){
    printStatistics stats = print_job_timer.getStats(); //obtiene las estadisticas
    MarlinUI::contenedor_str[0] = '\0';                 //variable para guardar texto temporal mente

    crear_marco_superior(Language_es::MSG_INFO_STATS_MENU);
    crear_marco_superior(Language_es::MSG_FILAMENTO_USADO,55);

    //Texto centrales
    lcd_moveto(10, 22);   // posicion del texto
    lcd_put_u8str_P(PSTR(Language_es::MSG_KILOMETRO));

    lcd_moveto(34, 35);   // posicion del texto
    lcd_put_u8str_P(PSTR(Language_es::MSG_METRO));

    lcd_moveto(4, 48);   // posicion del texto
    lcd_put_u8str_P(PSTR(Language_es::MSG_CENTIMETRO));


    //kilometros
    ////////////
    strcpy(MarlinUI::contenedor_str,ltostr7(long(stats.filamentUsed / 1000 / 1000))); //guarda el valor en el contenedor
    removeSpacesInPlace(MarlinUI::contenedor_str); //elimina los espacios en blanco generado por la tranformacion
    lcd_moveto(76, 22);
    lcd_put_u8str(MarlinUI::contenedor_str);

    //metro
    ///////
    strcpy(MarlinUI::contenedor_str,ltostr7(long(stats.filamentUsed / 1000))); //guarda el valor en el contenedor
    removeSpacesInPlace(MarlinUI::contenedor_str); //elimina los espacios en blanco generado por la tranformacion
    lcd_moveto(76, 35);
    lcd_put_u8str(MarlinUI::contenedor_str);

    //centimetro
    ////////////
    strcpy(MarlinUI::contenedor_str,ltostr7(long(stats.filamentUsed / 10) % 100)); //guarda el valor en el contenedor
    removeSpacesInPlace(MarlinUI::contenedor_str); //elimina los espacios en blanco generado por la tranformacion
    lcd_moveto(76, 48);
    lcd_put_u8str(MarlinUI::contenedor_str);

    if(ui.use_click()){
      MarlinUI::goto_screen(estadisticas_horas);
    }
}
#endif
//carteles de si o no
//////////////////////
void error_no_hay_mapa(){
  crear_marco_superior("Error No hay Mapa",0,11);

  u8g.drawBitmapP(58, 14, 2, 15, no_logros_ico);

  crear_texto_centrado("Es Necesario Hacer",32);
  crear_texto_centrado("Un Mapa De Cama Para",42);
  crear_texto_centrado("Activar Autolevel",52);

  if(ui.use_click()){
    MarlinUI::goto_screen(menu_ajustes, MarlinUI::endcoder_ulti_aux);
  }
}

void cambiar_estado_sensor(){MarlinUI::sensor_on_off = !MarlinUI::sensor_on_off; MarlinUI::goto_screen(menu_ajustes, MarlinUI::endcoder_ulti_aux);}



//Cartel para el sensor de filamento
void cartel_sensor_filamento(){
  START_MENU();
  NEXT_ITEM_(2);
  END_MENU();

  crear_marco_superior(Language_es::MSG_BUTTON_ADVERTENCIA);
  init_boto(23, 5, 2, 29);

  crear_boton(boton_detener_a,     boton_detener_b,     Language_es::MSG_BUTTON_CANCEL,   menu_ajustes, 8);
  crear_boton(boton_reanudar_a,    boton_reanudar_b,    Language_es::MSG_BUTTON_ACEPTAR,  cambiar_estado_sensor);
  
  if(MarlinUI::sensor_on_off){
    crear_texto_centrado(Language_es::MSG_CARTEL_SENSOR_01, 18);//desactivar sensor
    crear_texto_centrado(Language_es::MSG_CARTEL_SENSOR_02, 27);//de filamento

  }else{
    crear_texto_centrado(Language_es::MSG_CARTEL_SENSOR_03, 18);
    crear_texto_centrado(Language_es::MSG_CARTEL_SENSOR_04, 27);
  }
}

//////////////////////////////////////
//inicio autolevel on off

//activa la calibrtacion automatica y el uso de sensor inductivo
void cambiar_estado_autolevel(){
  #if ENABLED(AUTO_BED_LEVELING_UBL)
    //guarda el mapa en el primer lugar
    settings.store_mesh(0);
    ubl.storage_slot = 0;

    //cambio de sentido
    if(planner.leveling_active && MarlinUI::inductivo_final_carrera){
      set_bed_leveling_enabled(false);
      MarlinUI::inductivo_final_carrera = false;
    }else{
      set_bed_leveling_enabled(true);
      MarlinUI::inductivo_final_carrera = true;
    }

    //guardado
    (void)settings.save();
    (void)settings.load();

    MarlinUI::goto_screen(salida_menu_ajuste);
 #endif
}

void cartel_auto_calibracion(){
  START_MENU();
  NEXT_ITEM_(2);
  END_MENU();

  crear_marco_superior(Language_es::MSG_BUTTON_ADVERTENCIA);
  init_boto(23, 5, 2, 29);

  crear_boton(boton_detener_a,     boton_detener_b,     Language_es::MSG_BUTTON_CANCEL,   salida_menu_ajuste);
  crear_boton(boton_reanudar_a,    boton_reanudar_b,    Language_es::MSG_BUTTON_ACEPTAR,  cambiar_estado_autolevel);
  
  if(!planner.leveling_active){
    crear_texto_centrado(Language_es::MSG_CARTEL_AUTOLEVEL_03, 9);//El Mapa De Cama
    crear_texto_centrado(Language_es::MSG_CARTEL_AUTOLEVEL_04, 18);//Corregira Las Alturas
  }else{
    crear_texto_centrado(Language_es::MSG_CARTEL_AUTOLEVEL_01, 9);//Se Dejará De Usar
    crear_texto_centrado(Language_es::MSG_CARTEL_AUTOLEVEL_03, 18);//El Mapa De Cama
  }
}

//Redireccion para evitar problemas
void auto_calibracion_on_off(){
  MarlinUI::goto_screen(cartel_auto_calibracion);
}
//final autolevel on off
////////////////////////

void _cambiar_modo_tmc(){
  //serialprintPGM(st.get_stealthChop_status() ? PSTR("stealthChop") : PSTR("spreadCycle"));
}

/////////////////////////
//inicio capas cordenadas

void _informacion_capas_coord(){
  MarlinUI::informacion_capas_coord = !MarlinUI::informacion_capas_coord;//cambia el  sentido

  (void)settings.save();
  (void)settings.load();

  MarlinUI::goto_screen(salida_menu_ajuste);
}

//final capas cordenadas
////////////////////////

void _guardado_on_off(){
  MarlinUI::guardado_on_off = !MarlinUI::guardado_on_off;
  MarlinUI::goto_screen(menu_ajustes, MarlinUI::endcoder_ulti_aux);
}

void _sensor_on_off(){//tiene un cartel de advertencia
  MarlinUI::goto_screen(cartel_sensor_filamento);
}


////////////////////////
//inicio paso de varilla

void _cambiar_paso_varilla(){
  if(planner.settings.axis_steps_per_mm[Z_AXIS] == 400){
    planner.settings.axis_steps_per_mm[Z_AXIS] = 800;
    planner.set_max_feedrate(Z_AXIS, 20);
    planner.set_max_acceleration(Z_AXIS, 200);
  }else{
    planner.settings.axis_steps_per_mm[Z_AXIS] = 400;
    planner.set_max_feedrate(Z_AXIS, 10);
    planner.set_max_acceleration(Z_AXIS, 100);
  }

  MarlinUI::paso_de_varrilla =! MarlinUI::paso_de_varrilla;

  (void)settings.save();
  (void)settings.load();

  MarlinUI::goto_screen(salida_menu_ajuste);
}

//inicio paso de varilla
////////////////////////

////////////////////////
//inicio endoder der izq

void _encode_der_izd(){
  if(MarlinUI::encode_der_izd){
    MarlinUI::encode_der_izd =! MarlinUI::encode_der_izd;
    MarlinUI::encoder_giro = 1;

  }else{
    MarlinUI::encode_der_izd =! MarlinUI::encode_der_izd;
    MarlinUI::encoder_giro = -1;
  }
  (void)settings.save();
  (void)settings.load();
  MarlinUI::goto_screen(salida_menu_ajuste);
}

//Final endoder der izq
///////////////////////

/////////////////////
//inicio kuttermelody
void _k_melody_on_off(){
  MarlinUI::k_melody_on_off =! MarlinUI::k_melody_on_off;

  (void)settings.save();
  (void)settings.load();
  
  MarlinUI::sonar_kuttermelody();//solo suena si esta activo
  MarlinUI::goto_screen(salida_menu_ajuste);
}
//inicio kuttermelody
/////////////////////

///////////////////
//inicio menu eprom
void cambiar_estado_eprom(){
  queue.inject_P(PSTR("M502\nM500")); 
  MarlinUI::goto_screen(salida_menu_ajuste);
}

void cartel_eprom(){
  START_MENU();
  NEXT_ITEM_(2);
  END_MENU();

  crear_marco_superior(Language_es::MSG_BUTTON_ADVERTENCIA);

  crear_texto_centrado(Language_es::MSG_CARTEL_EPROM_02, 9);
  crear_texto_centrado(Language_es::MSG_CARTEL_EPROM_03, 18);

  init_boto(23, 5, 2, 29);

  crear_boton(boton_detener_a,     boton_detener_b,     Language_es::MSG_BUTTON_CANCEL,   salida_menu_ajuste);
  crear_boton(boton_reanudar_a,    boton_reanudar_b,    Language_es::MSG_CARTEL_EPROM_01, cambiar_estado_eprom);
}

void _cartel_eprom(){
  MarlinUI::goto_screen(cartel_eprom);
}

//Final menu eprom
//////////////////


///////////////////////////
//Inicio cambio de extrusor

void cambiar_tipo_extrusor(){
  //tipo_de_extrusor es verdadero
  //el extrusor eleguido es un BMG
  if(MarlinUI::tipo_de_extrusor){
    MarlinUI::tipo_de_extrusor = false;
    planner.settings.axis_steps_per_mm[E_AXIS_N(0)] = 95;
  }else{
    MarlinUI::tipo_de_extrusor = true;
    planner.settings.axis_steps_per_mm[E_AXIS_N(0)] = 415;
  }

  (void)settings.save();
  (void)settings.load();

  MarlinUI::goto_screen(salida_menu_ajuste);
}


//Final cambio de extrusor
//////////////////////////

//////////////////////////
//funciones sin terminar//

void _cartel_idioma(){
  opciones_no_disponible(menu_ajustes, 4);
}
void _cartel_idioma_redireccion(){
  MarlinUI::goto_screen(_cartel_idioma);
}

void _cartel_capas(){
  opciones_no_disponible(menu_ajustes, 6);
}
void _cartel_capas_redireccion(){
  MarlinUI::goto_screen(_cartel_capas);
}

////////////////////////
//inicio on off guardado

void _cartel_guardado(){
  if(recovery.enabled){
    recovery.enable(false);
  }else{
    recovery.enable(true);
  }

  (void)settings.save();
  (void)settings.load();

  MarlinUI::goto_screen(salida_menu_ajuste);
}

void _cartel_guardado_redireccion(){
  MarlinUI::goto_screen(_cartel_guardado);
}

//final on off guardado
///////////////////////

////////////////////////////
//inicio sensor de filamento

void on_off_sensor_de_filamento(){
  MarlinUI::sensor_filamento_on_off = !MarlinUI::sensor_filamento_on_off;

  (void)settings.save();
  (void)settings.load();
  
  MarlinUI::goto_screen(salida_menu_ajuste);
}

void _cartel_on_off_sensor_de_filamento(){
  MarlinUI::goto_screen(on_off_sensor_de_filamento);
}

//final  sensor de filamento
////////////////////////////

void _cartel_encode(){
  opciones_no_disponible(menu_ajustes, 10);
}
void _cartel_encode_redireccion(){
  MarlinUI::goto_screen(_cartel_encode);
}

void _cartel_gcode(){
  opciones_no_disponible(menu_ajustes, 14);
}
void _cartel_gcode_redireccion(){
  MarlinUI::goto_screen(_cartel_gcode);
}

void _cartel_sistema(){
  opciones_no_disponible(menu_ajustes, 15);
}
void _cartel_sistema_redireccion(){
  MarlinUI::goto_screen(_cartel_sistema);
}
//funciones sin terminar//
//////////////////////////

////////////////////
//Entrar a sistema//
char aux_numero[10];

void entrar_a_sistema();
void cambiar_serie();

void ir_cambiar_serie() {
  MarlinUI::goto_screen(cambiar_serie);
}

void cambiar_serie(){
  START_MENU();
  NEXT_ITEM_(10);
  END_MENU();

  //muestra el numero seleccionado
  lcd_moveto(66, 40);
  lcd_put_u8str_P(MarlinUI::contenedor_str);

  //textos
  lcd_moveto(22, 40);
  lcd_put_u8str_P(PSTR("Codigo:"));

  crear_marco_superior("Ingrese Generacion:");

  strcpy(aux_numero, ftostr3(int(MarlinUI::encoderPosition)));
  removeSpacesInPlace(aux_numero);

  if(strlen(MarlinUI::contenedor_str) <= 3){
    crear_marco_superior(aux_numero, 55);
  }else{
    crear_marco_superior("Aceptar", 55);
  }

    //accion
  if(ui.use_click()){
    if(strlen(MarlinUI::contenedor_str) <= 3){
      //guardado del nuevo numero
      strcat(MarlinUI::contenedor_str, ftostr3(int(MarlinUI::encoderPosition)));//guarda la info en contenedor_str y lo comvierte en char
      removeSpacesInPlace(MarlinUI::contenedor_str);//elimina los espacios en blanco

      MarlinUI::goto_screen(ir_cambiar_serie, 0);//recarga este menu para ingresar el siguiente numero
    }else{
      //Agrega una separacion "-"
      strcat(MarlinUI::numero_de_serie, PSTR("-"));

      //agrega 0 dependiendo de la catidad de digitos
      for (int i = 0; i < 4 - int(strlen(MarlinUI::contenedor_str)); i++) {
        strcat(MarlinUI::numero_de_serie, PSTR("0"));
      }
      strcat(MarlinUI::numero_de_serie, MarlinUI::contenedor_str);
      removeSpacesInPlace(MarlinUI::numero_de_serie);

      //limpiamos
      MarlinUI::contenedor_str[0] = '\0';
      //guarda el valor
      (void)settings.save();
      (void)settings.load();
      
      ui.set_status(MarlinUI::numero_de_serie);
      
      MarlinUI::goto_screen(MarlinUI::status_screen);
      //Salida
    }
  }
}

void cambiar_version_generacion(){
  
  u8g.drawBox(0, 0, 128, 10);

  //limites
    
  START_MENU();
  NEXT_ITEM_(30);
  END_MENU();

  u8g.setColorIndex(0);
  lcd_moveto(7, 8);
  lcd_put_u8str_P(PSTR("Ingrese Generacion:"));
  u8g.setColorIndex(1);

  strcpy(aux_numero, ftostr3(int(MarlinUI::encoderPosition) + 1));
  removeSpacesInPlace(aux_numero);
  crear_marco_superior(aux_numero, 55);

  //accion
  if(ui.use_click()){
    strcpy(MarlinUI::contenedor_str, ftostr3(int(MarlinUI::encoderPosition) + 1));//guarda el numero
    removeSpacesInPlace(MarlinUI::contenedor_str);//elimina espacios en blanco

    strcat(MarlinUI::numero_de_serie, MarlinUI::contenedor_str);
    MarlinUI::contenedor_str[0] = '\0';

    MarlinUI::goto_screen(cambiar_serie);
  }
}

//se encarga de volver a llamar a la funcion entrar_en_sistema
void cambiar_version_mes(){

  u8g.drawBox(0, 0, 128, 10);

  START_MENU();
  NEXT_ITEM_(12);
  END_MENU();

  u8g.setColorIndex(0);
  lcd_moveto(28, 8);
  lcd_put_u8str_P(PSTR("Ingrese Mes:"));
  u8g.setColorIndex(1);

  strcpy(aux_numero, ftostr3(int(MarlinUI::encoderPosition) + 1));
  removeSpacesInPlace(aux_numero);
  crear_marco_superior(aux_numero, 55);

  SERIAL_ECHOLN(aux_numero);
  SERIAL_ECHOLN(MarlinUI::encoderPosition);

  //accion
  if(ui.use_click()){
    strcpy(MarlinUI::contenedor_str, ftostr3(int(MarlinUI::encoderPosition) + 1));
    removeSpacesInPlace(MarlinUI::contenedor_str);
    //MSG_TIPO
    strcat(MarlinUI::numero_de_serie, PSTR("PK3"));

    if(strlen(MarlinUI::contenedor_str) == 1){
      strcat(MarlinUI::numero_de_serie, PSTR("0"));
      strcat(MarlinUI::numero_de_serie, MarlinUI::contenedor_str);
    }else{
      strcat(MarlinUI::numero_de_serie, MarlinUI::contenedor_str);
    }

    MarlinUI::contenedor_str[0] = '\0';
    MarlinUI::goto_screen(cambiar_version_generacion,21);
  }
}

void ir_cambiar_version(){
  //limpia estos dos contenedores
  MarlinUI::numero_de_serie[0] = '\0';
  MarlinUI::contenedor_str[0] = '\0';
  MarlinUI::goto_screen(cambiar_version_mes, 1);
}
#if ENABLED(PRINTCOUNTER)
void borrar_estadisticas(){
  print_job_timer.initStats();
  ui.reset_status();

  MarlinUI::numero_de_logro_km = 0;
  MarlinUI::numero_de_logro_pz = 0;
  
  (void)settings.save();
  (void)settings.load();
  
  MarlinUI::goto_screen(MarlinUI::status_screen);
}
#endif
void ir_menu_sistema(){
  MarlinUI::ultimo_valor_ventana = menu_main;
  MarlinUI::ultimo_valor_encoder = 9;

  START_MENU();
  BACK_ITEM(MSG_VOLVER);
  SUBMENU(MSG_CAMBIAR_VERSION,      ir_cambiar_version);
  #if ENABLED(PRINTCOUNTER)
    SUBMENU(MSG_BORRAR_ESTADISTICAS,  borrar_estadisticas);
  #endif
  END_MENU();
}

void recurcion_sistema() {
  MarlinUI::goto_screen(entrar_a_sistema, 0);
}

void entrar_a_sistema() {
  //letras

  lcd_moveto(66, 40);
  lcd_put_u8str_P(MarlinUI::contenedor_str);//el numero completo 6 dígitos
  //textos
  lcd_moveto(22, 40);
  lcd_put_u8str_P(PSTR("Codigo:"));//visual 

  crear_marco_superior("Ingrese Codigo", 0, 11);
  if(strlen(MarlinUI::contenedor_str) <= 5){
    START_MENU();
    NEXT_ITEM_(12);
    END_MENU();

  if(MarlinUI::encoderPosition == 10){
    crear_marco_superior("Borrar", 55);
  }else if(MarlinUI::encoderPosition == 11){
    crear_marco_superior("Salir", 55);
  }else{
    strcpy(aux_numero, ftostr3(int(MarlinUI::encoderPosition)));
    removeSpacesInPlace(aux_numero);
    crear_marco_superior(aux_numero, 55);
  }
  }else{
    START_MENU();
    NEXT_ITEM_(2);
    END_MENU();

    if(MarlinUI::encoderPosition == 1){
      crear_marco_superior("Borrar", 55);
    }else if(MarlinUI::encoderPosition == 2){
      crear_marco_superior("Salir", 55);
    }else{
      crear_marco_superior("Aceptar", 55);
    }
  }

  u8g.setColorIndex(1);

    //accion
  if(ui.use_click()){
    if(MarlinUI::encoderPosition == 10){
      //pregunta si es menor a 1
      if(strlen(MarlinUI::contenedor_str) <= 1){
        MarlinUI::contenedor_str[0] = '\0';
        MarlinUI::goto_screen(recurcion_sistema, 0);
      }else{
        MarlinUI::contenedor_str[strlen(MarlinUI::contenedor_str) - 1] = '\0';
        MarlinUI::goto_screen(recurcion_sistema, 0);
      }
    }else if(MarlinUI::encoderPosition == 11){
      MarlinUI::goto_screen(menu_ajustes, MarlinUI::endcoder_ulti_aux);
    }else{
      if(strlen(MarlinUI::contenedor_str) <= 5){
        //guardado del nuevo numero
        strcat(MarlinUI::contenedor_str, ftostr3(int(MarlinUI::encoderPosition)));//guarda la info en contenedor_str y lo comvierte en char
        removeSpacesInPlace(MarlinUI::contenedor_str);//elimina los espacios en blanco
        //recurcion
        MarlinUI::goto_screen(recurcion_sistema, 0);
      }else{
        if(MarlinUI::encoderPosition == 1){
        //pregunta si es menor a 1
          if(strlen(MarlinUI::contenedor_str) <= 1){
            MarlinUI::contenedor_str[0] = '\0';
            MarlinUI::goto_screen(recurcion_sistema, 0);
          }else{
            MarlinUI::contenedor_str[strlen(MarlinUI::contenedor_str) - 1] = '\0';
            MarlinUI::goto_screen(recurcion_sistema, 0);
          }
        }else{
          //pregunta si esta bien la contraseña
          if(strcmp(MarlinUI::contenedor_str, "011990") == 0){
            //resetea y sigue
            MarlinUI::contenedor_str[0] = '\0';
            MarlinUI::goto_screen(ir_menu_sistema);

          }else{
            ui.set_status("Codigo Incorrecto");
            MarlinUI::goto_screen(MarlinUI::status_screen);
          }          
        }
      }
    }
  }
}

void sens_espera_01(){
  //NO se vuelve al status y se sigue actualizando
  MarlinUI::defer_return_to_status = true;
  MarlinUI::lcdDrawUpdate = LCDVIEW_CALL_REDRAW_NEXT;
    
  crear_texto_centrado(Language_es::MSG_CALIBRANDO, 20);

  crear_marco_superior(PSTR(MarlinUI::contenedor_str), 53, 11);

  //crea la barra de espera
  crear_espera();
  if(current_position[X_AXIS] == 200){
    MarlinUI::goto_screen(MarlinUI::status_screen);
  }
}

void sens_espera(){
  //NO se vuelve al status y se sigue actualizando
  MarlinUI::defer_return_to_status = true;
  MarlinUI::lcdDrawUpdate = LCDVIEW_CALL_REDRAW_NEXT;
    
  crear_texto_centrado(Language_es::MSG_CALIBRANDO, 20);

  crear_marco_superior(PSTR(MarlinUI::contenedor_str), 53, 11);

  //crea la barra de espera
  crear_espera();
  if(all_axes_homed()){
    queue.inject_P(PSTR("G1 X200"));
    MarlinUI::goto_screen(sens_espera_01);
  }

}

void calibracion_de_sensibilidad_home(){
  
  queue.inject_P(PSTR("G28\nG28 X\nG1 X200 Z50"));

  MarlinUI::goto_screen(sens_espera);
}

void ir_entrar_a_sistema(){
  MarlinUI::contenedor_str[0] = '\0';
  MarlinUI::goto_screen(entrar_a_sistema);
}

//Entrar a sistema//
////////////////////

/////////////////////////////
//inicio menu tcm kuttercraft

void advertencia_calibrar_sensibilidad();

void menu_tmc_current();
void menu_tmc_hybrid_thrs();
void menu_tmc_homing_thrs();
void menu_tmc_step_mode();

void salida_del_menu_tmc(){
  (void)settings.save();
  MarlinUI::goto_screen(salida_menu_ajuste);
}

void menu_tmc_kutter(){
  MarlinUI::defer_return_to_status = true;
  //crear_marco_superior(Language_es::MSG_TMC2130_CONFI);

  START_MENU();
  NEXT_ITEM_(6);
  END_MENU();

  init_boto(23, 2, 3, 3);

  crear_boton(boton_volver_a,   boton_volver_b,   Language_es::MSG_VOLVER,           salida_del_menu_tmc);//al salir se guarda el valor del tmc
  crear_boton(boton_amperaje_a, boton_amperaje_b, Language_es::MSG_TMC_AMPERAJE,     menu_tmc_current);
  crear_boton(boton_hidrido_a,  boton_hidrido_b,  Language_es::MSG_TMC_HIBRIDO,      menu_tmc_hybrid_thrs);
  crear_boton(editar_mapa_a,    editar_mapa_b,    Language_es::MSG_CALIBRAN_SENSI,   advertencia_calibrar_sensibilidad);
  crear_boton(boton_inicio_a,   boton_inicio_b,   Language_es::MSG_TMC_HOME,         menu_tmc_homing_thrs);
  crear_boton(calibrar_mapa_a,  calibrar_mapa_b,  Language_es::MSG_TMC_MODO_PASO,    menu_tmc_step_mode);

}

//final menu tcm kuttercraft
////////////////////////////

//////////////////////////
//inicio modo de impresion
template<typename TMC>
void tmc_set_stealthChop__(TMC &st, const bool enable) {
  st.stored.stealthChop_enabled = enable;
  st.refresh_stepping_mode();
}

static void set_stealth_status__(const bool enable, const uint8_t axis) {
  #define TMC_SET_STEALTH(Q) tmc_set_stealthChop__(stepper##Q, enable)

  constexpr int8_t index = -1;

    switch (axis) {
      case X_AXIS:
        TERN_(X_HAS_STEALTHCHOP,  if (index < 0 || index == 0) TMC_SET_STEALTH(X));
        break;

      #if HAS_Y_AXIS
        case Y_AXIS:
          TERN_(Y_HAS_STEALTHCHOP,  if (index < 0 || index == 0) TMC_SET_STEALTH(Y));
          break;
      #endif

      #if HAS_Z_AXIS
        case Z_AXIS:
          TERN_(Z_HAS_STEALTHCHOP,  if (index < 0 || index == 0) TMC_SET_STEALTH(Z));
          break;
      #endif

      #if E_STEPPERS
        case E_AXIS: {
          TERN_(E0_HAS_STEALTHCHOP, if (index < 0 || index == 0) TMC_SET_STEALTH(E0));
        } break;
      #endif
    }
  
}
void set_hybrid_mode(int32_t value, const uint8_t axis){
  #define TMC_SET_PWMTHRS(A,Q) stepper##Q.set_pwm_thrs(value)
  #define TMC_SET_PWMTHRS_E(E) stepperE##E.set_pwm_thrs(value)

  constexpr int8_t index = -1;

  switch (axis) {
    #if X_HAS_STEALTHCHOP
      case X_AXIS:
        TERN_(X_HAS_STEALTHCHOP,  if (index < 0 || index == 0) TMC_SET_PWMTHRS(X,X));
        break;
    #endif

    #if Y_HAS_STEALTHCHOP
      case Y_AXIS:
        TERN_(Y_HAS_STEALTHCHOP,  if (index < 0 || index == 0) TMC_SET_PWMTHRS(Y,Y));
        break;
    #endif

    #if Z_HAS_STEALTHCHOP
      case Z_AXIS:
        TERN_(Z_HAS_STEALTHCHOP,  if (index < 0 || index == 0) TMC_SET_PWMTHRS(Z,Z));
        break;
    #endif

    #if E0_HAS_STEALTHCHOP
      case E_AXIS: {
        TERN_(E0_HAS_STEALTHCHOP, if (index < 0 || index == 0) TMC_SET_PWMTHRS_E(0));
      } break;
    #endif
  }  
}

void cambiar_modo_de_impresion(){
  MarlinUI::modo_de_impresion += 1;

  //si se pasa vuelve al normal
  if(MarlinUI::modo_de_impresion > 2)
    MarlinUI::modo_de_impresion = 0;

  //setea los valores para los distintos modos

  //modo normal
  if(MarlinUI::modo_de_impresion == 0){

    //M201
    planner.set_max_acceleration(X_AXIS, 900);
    planner.set_max_acceleration(Y_AXIS, 900);
    planner.set_max_acceleration(Z_AXIS, 200);
    planner.set_max_acceleration(E_AXIS, 10000);
    
    //M203 Max Feed Rate (mm/s)
    planner.set_max_feedrate(X_AXIS, 100);
    planner.set_max_feedrate(Y_AXIS, 100);
    planner.set_max_feedrate(Z_AXIS, 12);
    planner.set_max_feedrate(E_AXIS, 120);

    //M204
    planner.settings.acceleration         = 500;  //Acceleration
    planner.settings.retract_acceleration = 1200; //Retract Acceleration
    planner.settings.travel_acceleration  = 700;  //Travel Acceleration

    //M205
    planner.junction_deviation_mm = 0.03;

    //Valores TMC 0 = MODO FUERZAS
    set_stealth_status__(1, X_AXIS);
    set_stealth_status__(1, Y_AXIS);
    set_stealth_status__(1, Z_AXIS);
    set_stealth_status__(0, E_AXIS);

    //HYBRID_THRESHOLD
    set_hybrid_mode(1, X_AXIS);
    set_hybrid_mode(1, Y_AXIS);
    set_hybrid_mode(3, Z_AXIS);
    set_hybrid_mode(60, E_AXIS);

  //modo silencioso
  }else if(MarlinUI::modo_de_impresion == 1){//Silencioso
    //M201
    planner.set_max_acceleration(X_AXIS, 800);
    planner.set_max_acceleration(Y_AXIS, 800);
    planner.set_max_acceleration(Z_AXIS, 200);
    planner.set_max_acceleration(E_AXIS, 10000);
    
    //M203 Max Feed Rate (mm/s)
    planner.set_max_feedrate(X_AXIS, 100);
    planner.set_max_feedrate(Y_AXIS, 100);
    planner.set_max_feedrate(Z_AXIS, 12);
    planner.set_max_feedrate(E_AXIS, 120);

    //M204
    planner.settings.acceleration         = 400;  //Acceleration
    planner.settings.retract_acceleration = 1200; //Retract Acceleration
    planner.settings.travel_acceleration  = 600;  //Travel Acceleration

    //M205
    planner.junction_deviation_mm = 0.03;

    //Valor 1 = silencio
    set_stealth_status__(1, X_AXIS);
    set_stealth_status__(1, Y_AXIS);
    set_stealth_status__(1, Z_AXIS);
    set_stealth_status__(1, E_AXIS);

    //HYBRID_THRESHOLD
    set_hybrid_mode(50, X_AXIS);
    set_hybrid_mode(50, Y_AXIS);
    set_hybrid_mode(3, Z_AXIS);
    set_hybrid_mode(40, E_AXIS);

  //modo rapido
  }else if(MarlinUI::modo_de_impresion == 2){
    //M201
    planner.set_max_acceleration(X_AXIS, 1000);
    planner.set_max_acceleration(Y_AXIS, 1000);
    planner.set_max_acceleration(Z_AXIS, 200);
    planner.set_max_acceleration(E_AXIS, 10000);
    
    //M203 Max Feed Rate (mm/s)
    planner.set_max_feedrate(X_AXIS, 200);
    planner.set_max_feedrate(Y_AXIS, 200);
    planner.set_max_feedrate(Z_AXIS, 12);
    planner.set_max_feedrate(E_AXIS, 120);

    //M204
    planner.settings.acceleration         = 700;  //Acceleration
    planner.settings.retract_acceleration = 1200; //Retract Acceleration
    planner.settings.travel_acceleration  = 700;  //Travel Acceleration

    //M205
    planner.junction_deviation_mm = 0.03;

    set_stealth_status__(0, X_AXIS);
    set_stealth_status__(0, Y_AXIS);
    set_stealth_status__(1, Z_AXIS);
    set_stealth_status__(0, E_AXIS);

    //HYBRID_THRESHOLD
    set_hybrid_mode(60, X_AXIS);
    set_hybrid_mode(60, Y_AXIS);
    set_hybrid_mode(3, Z_AXIS);
    set_hybrid_mode(80, E_AXIS);
  }
  
  //el personal es elegido por el usuario 
  //asi que no se puede volver a setear

  //guardado
  (void)settings.save();
  (void)settings.load();


  MarlinUI::goto_screen(salida_menu_ajuste);
}

void cartel_cambio_modo_impresion();

void cartel_info_modo_impresion(){
  //velocidad normal
  if(MarlinUI::modo_de_impresion == 0){
    crear_marco_superior(Language_es::MSG_MODO_IMPRESION_NORMAL_00);

    crear_texto_centrado(Language_es::MSG_MODO_IMPRESION_NORMAL_01, 12);//Busca el Mejor
    crear_texto_centrado(Language_es::MSG_MODO_IMPRESION_NORMAL_02, 22);//Rendimiento Entre
    crear_texto_centrado(Language_es::MSG_MODO_IMPRESION_NORMAL_03, 32);//Calidad, Tiempo y
    crear_texto_centrado(Language_es::MSG_MODO_IMPRESION_NORMAL_04, 42);//Ruido

  //modo Silencioso
  }else if(MarlinUI::modo_de_impresion == 1){
    crear_marco_superior(Language_es::MSG_MODO_IMPRESION_SILENE_00);

    crear_texto_centrado(Language_es::MSG_MODO_IMPRESION_SILENE_01, 12);
    crear_texto_centrado(Language_es::MSG_MODO_IMPRESION_SILENE_02, 22);
    crear_texto_centrado(Language_es::MSG_MODO_IMPRESION_SILENE_03, 32);
    crear_texto_centrado(Language_es::MSG_MODO_IMPRESION_SILENE_04, 42);

  //modo Rapido
  }else if(MarlinUI::modo_de_impresion == 2){
    crear_marco_superior(Language_es::MSG_MODO_IMPRESION_RAPIDO_00);

    crear_texto_centrado(Language_es::MSG_MODO_IMPRESION_RAPIDO_01, 12);
    crear_texto_centrado(Language_es::MSG_MODO_IMPRESION_RAPIDO_02, 22);
    crear_texto_centrado(Language_es::MSG_MODO_IMPRESION_RAPIDO_03, 32);
    crear_texto_centrado(Language_es::MSG_MODO_IMPRESION_RAPIDO_04, 42);
  
  //configuracion personal
  }else{
    crear_marco_superior(Language_es::MSG_MODO_IMPRESION_PERSON_00);

    crear_texto_centrado(Language_es::MSG_MODO_IMPRESION_PERSON_01, 12);
    crear_texto_centrado(Language_es::MSG_MODO_IMPRESION_PERSON_02, 22);
    crear_texto_centrado(Language_es::MSG_MODO_IMPRESION_PERSON_03, 32);
    crear_texto_centrado(Language_es::MSG_MODO_IMPRESION_PERSON_04, 42);
  }

  crear_marco_superior(Language_es::MSG_CLICK_PARA_SALIR, 55, 9);
  
  if(ui.use_click()){
    MarlinUI::goto_screen(cartel_cambio_modo_impresion, 1);
  }

}

void cartel_cambio_modo_impresion(){
  START_MENU();
  NEXT_ITEM_(3);
  END_MENU();

  crear_marco_superior(Language_es::MSG_MODO_IMPRESION);
  init_boto(23, 5, 3, 29);

  crear_boton(boton_detener_a,     boton_detener_b,     Language_es::MSG_BUTTON_CANCEL,        salida_menu_ajuste);
  crear_boton(boton_velocidad_a,   boton_velocidad_b,   Language_es::MSG_MODO_IMPRESION_INFO,  cartel_info_modo_impresion);
  crear_boton(boton_reanudar_a,    boton_reanudar_b,    Language_es::MSG_MODO_IMPRESION_CAN,   cambiar_modo_de_impresion);
  
  crear_texto_centrado(Language_es::MSG_MODO_IMPRESION_MOD, 9);
  crear_texto_centrado(Language_es::MSG_MODO_IMPRESION_PRIN,18);

}
//final modo de impresion
/////////////////////////

/////////////////////////
//inicio calibrar_sensibilidad
void inicia_la_prueba();

void espera_calibrar_sensibilidad_eje_x();
void espera_calibrar_sensibilidad_eje_x_confirmacion();
void espera_calibrar_sensibilidad_eje_y();
void espera_calibrar_sensibilidad_eje_y_confirmacion();

int16_t espera_tiempo_para_confirmar = 0;
int16_t valor_anterior_ensibilidad = 0;
bool solo_una_vez_sensibilidad = false;

//una ultima confirmacion que el valor este bien
//y una calibracion mas fina
void espera_calibrar_sensibilidad_eje_y_confirmacion(){
  MarlinUI::defer_return_to_status = true;
  MarlinUI::lcdDrawUpdate = LCDVIEW_CALL_REDRAW_NEXT;

  crear_marco_superior(Language_es::MSG_CALIBRAN_SENSI);//calibra. sensibilidad

  lcd_moveto(13, 29);
  lcd_put_u8str(Language_es::MSG_CALIBRAN_SENSI_Y);

  lcd_moveto(89, 29);
  lcd_put_u8str(i16tostr4signrj(stepperY.stored.homing_thrs)); //temp objectivo

  crear_espera();
  crear_marco_superior(PSTR(Language_es::MSG_POR_FAVOR_ESPERE), 53, 11);

  //espera que termine el home
  if(MarlinUI::home_en_accion){
    //significa que la ultima prueba esta mal
    if(MarlinUI::salida_calibrando_sensibilidad){
      //se restablese la senal de fallo y la detección de home
      MarlinUI::salida_calibrando_sensibilidad = false;
      MarlinUI::home_en_accion = false;

      //modifica la sensivilidad
      stepperY.homing_threshold(stepperY.stored.homing_thrs - 1);

      //Se creea comando de movimiento
      MarlinUI::contenedor_str[0] = '\0';
      strcpy(MarlinUI::contenedor_str, "G1 Z0 Y");
      strcat(MarlinUI::contenedor_str, i16tostr4signrj(Y_BED_SIZE - 5));
      strcat(MarlinUI::contenedor_str, " F4000\nG28Y");
      queue.inject_P(PSTR(MarlinUI::contenedor_str));//EJECUTA EL COMANDO

      //se vuelve a ejecutar un loop
      MarlinUI::goto_screen(espera_calibrar_sensibilidad_eje_y_confirmacion);

    //significa que se encontro el minimo se sigue calibrando el eje y
    }else{
      MarlinUI::calibrando_sensibilidad = false;
      //se disminuye uno mas
      stepperY.homing_threshold(stepperY.stored.homing_thrs - 5);
      (void)settings.save();//seguarda

      if(MarlinUI::calibracion_general_valor){
        //salida de menu calibracion general
        MarlinUI::goto_screen(inicia_la_prueba);
      }else{
        //salida de menu TCM
        MarlinUI::goto_screen(menu_tmc_kutter, 3);
      }
    }
  }
}


void espera_calibrar_sensibilidad_eje_y(){
  MarlinUI::defer_return_to_status = true;
  MarlinUI::lcdDrawUpdate = LCDVIEW_CALL_REDRAW_NEXT;

  crear_marco_superior(Language_es::MSG_CALIBRAN_SENSI);//calibra. sensibilidad

  lcd_moveto(13, 29);
  lcd_put_u8str(Language_es::MSG_CALIBRAN_SENSI_Y);

  lcd_moveto(89, 29);
  lcd_put_u8str(i16tostr4signrj(stepperY.stored.homing_thrs)); //temp objectivo

  crear_espera();
  crear_marco_superior(PSTR(Language_es::MSG_POR_FAVOR_ESPERE), 53, 11);

  //fin parte visual

  //cuanta cuanto tiempo paso desde que se realizo un home
  if(MarlinUI::home_en_accion){
    if(stepperY.stored.homing_thrs == valor_anterior_ensibilidad){
      espera_tiempo_para_confirmar += 1;
    }else{
      espera_tiempo_para_confirmar = 0;
      valor_anterior_ensibilidad = stepperY.stored.homing_thrs;
    }
  }
  
  //esta es la salida del loop para saber el valor de sensibilidad
  if(espera_tiempo_para_confirmar == 30){
    //se acualiza el valor de home para el siguiente menu
    valor_anterior_ensibilidad = stepperY.stored.homing_thrs;
    //se restablese la senal de fallo y la detección de home
    MarlinUI::salida_calibrando_sensibilidad = false; //avisa que hay que buscar un error de home
    MarlinUI::sensibilidad_primera_parte = false;     //evita que el home se haga en la apccion de endstop
    MarlinUI::home_en_accion = false;                 //espera a terminar el siguiente home
    solo_una_vez_sensibilidad = true;                 //ejecuta una apccion solo una ves en las repeticiones

    //se nueve el eje para confirmar que el valor sea el minimo posible
    queue.inject_P(PSTR("G1 Y150 Z5 F4000\nG28Y"));
    //se va a otro menu de espera
    MarlinUI::goto_screen(espera_calibrar_sensibilidad_eje_y_confirmacion);
  }

  SERIAL_ECHOLN(espera_tiempo_para_confirmar);

  //se activa cuando se detecta que fallo la detección del home
  if(MarlinUI::salida_calibrando_sensibilidad){
    //se restablese la senal de fallo y la detección de home
    MarlinUI::salida_calibrando_sensibilidad = false;
    MarlinUI::home_en_accion = false;

    //modifica la sensivilidad
    stepperY.homing_threshold(stepperY.stored.homing_thrs - 1);

    //Se creea comando de movimiento
    MarlinUI::contenedor_str[0] = '\0';
    strcpy(MarlinUI::contenedor_str, "G1 Z5 Y");
    strcat(MarlinUI::contenedor_str, i16tostr4signrj(Y_BED_SIZE - 5));
    strcat(MarlinUI::contenedor_str, " F4000\nG28Y");
    queue.inject_P(PSTR(MarlinUI::contenedor_str));//EJECUTA EL COMANDO
    
    //se vuelve a este menu para ejecutar un loop
    MarlinUI::goto_screen(espera_calibrar_sensibilidad_eje_y);
  }
}

//una ultima confirmacion que el valor este bien
//y una calibracion mas fina
void espera_calibrar_sensibilidad_eje_x_confirmacion(){
  MarlinUI::defer_return_to_status = true;
  MarlinUI::lcdDrawUpdate = LCDVIEW_CALL_REDRAW_NEXT;

  crear_marco_superior(Language_es::MSG_CALIBRAN_SENSI);//calibra. sensibilidad

  lcd_moveto(13, 29);
  lcd_put_u8str(Language_es::MSG_CALIBRAN_SENSI_X);

  lcd_moveto(89, 29);
  lcd_put_u8str(i16tostr4signrj(stepperX.stored.homing_thrs)); //temp objectivo

  crear_espera();
  crear_marco_superior(PSTR(Language_es::MSG_POR_FAVOR_ESPERE), 53, 11);

  //espera que termine el home
  if(MarlinUI::home_en_accion){
    //significa que la ultima prueba esta mal
    if(MarlinUI::salida_calibrando_sensibilidad){
      //se restablese la senal de fallo y la detección de home
      MarlinUI::salida_calibrando_sensibilidad = false;
      MarlinUI::home_en_accion = false;

      //modifica la sensivilidad
      stepperX.homing_threshold(stepperX.stored.homing_thrs - 1);

      //Se creea comando de movimiento
      MarlinUI::contenedor_str[0] = '\0';
      strcpy(MarlinUI::contenedor_str, "G1 Z5 X");
      strcat(MarlinUI::contenedor_str, i16tostr4signrj(X_BED_SIZE - 5));
      strcat(MarlinUI::contenedor_str, " F4000\nG28X");
      queue.inject_P(PSTR(MarlinUI::contenedor_str));//EJECUTA EL COMANDO

      //se vuelve a ejecutar un loop
      MarlinUI::goto_screen(espera_calibrar_sensibilidad_eje_x_confirmacion);

    //significa que se encontro el minimo se sigue calibrando el eje y
    }else{
      //se restablese la senal de fallo y la detección de home
      MarlinUI::salida_calibrando_sensibilidad = false; //avisa que hay que buscar un error de home
      MarlinUI::sensibilidad_primera_parte = false;     //evita que el home se haga en la apccion de endstop
      MarlinUI::home_en_accion = false;                 //espera a terminar el siguiente home
      solo_una_vez_sensibilidad = true;                 //ejecuta una apccion solo una ves en las repeticiones
      espera_tiempo_para_confirmar = 0;

      //se disminuye uno mas
      stepperX.homing_threshold(stepperX.stored.homing_thrs - 5);

      queue.inject_P(PSTR("G28 Y"));//EJECUTA EL COMANDO
      MarlinUI::goto_screen(espera_calibrar_sensibilidad_eje_y);
    }
  }
}


void espera_calibrar_sensibilidad_eje_x(){
  MarlinUI::defer_return_to_status = true;
  MarlinUI::lcdDrawUpdate = LCDVIEW_CALL_REDRAW_NEXT;

  crear_marco_superior(Language_es::MSG_CALIBRAN_SENSI);//calibra. sensibilidad

  lcd_moveto(13, 29);
  lcd_put_u8str(Language_es::MSG_CALIBRAN_SENSI_X);

  lcd_moveto(89, 29);
  lcd_put_u8str(i16tostr4signrj(stepperX.stored.homing_thrs)); //temp objectivo

  crear_espera();
  crear_marco_superior(PSTR(Language_es::MSG_POR_FAVOR_ESPERE), 53, 11);

  //fin parte visual

  //cuanta cuanto tiempo paso desde que se realizo un home
  if(MarlinUI::home_en_accion){
    if(stepperX.stored.homing_thrs == valor_anterior_ensibilidad){
      espera_tiempo_para_confirmar += 1;
    }else{
      espera_tiempo_para_confirmar = 0;
      valor_anterior_ensibilidad = stepperX.stored.homing_thrs;
    }
  }
  
  //esta es la salida del loop para saber el valor de sensibilidad
  if(espera_tiempo_para_confirmar == 30){
    //se acualiza el valor de home para el siguiente menu
    valor_anterior_ensibilidad = stepperX.stored.homing_thrs;
    //se restablese la senal de fallo y la detección de home
    MarlinUI::salida_calibrando_sensibilidad = false; //avisa que hay que buscar un error de home
    MarlinUI::sensibilidad_primera_parte = false;     //evita que el home se haga en la apccion de endstop
    MarlinUI::home_en_accion = false;                 //espera a terminar el siguiente home
    solo_una_vez_sensibilidad = true;                 //ejecuta una apccion solo una ves en las repeticiones

    //se nueve el eje para confirmar que el valor sea el minimo posible
    queue.inject_P(PSTR("G1 X150 Z5 F4000\nG28X"));
    //se va a otro menu de espera
    MarlinUI::goto_screen(espera_calibrar_sensibilidad_eje_x_confirmacion);
  }

  SERIAL_ECHOLN(espera_tiempo_para_confirmar);

  //se activa cuando se detecta que fallo la detección del home
  if(MarlinUI::salida_calibrando_sensibilidad){
    //se restablese la senal de fallo y la detección de home
    MarlinUI::salida_calibrando_sensibilidad = false;
    MarlinUI::home_en_accion = false;

    //modifica la sensivilidad
    stepperX.homing_threshold(stepperX.stored.homing_thrs - 1);

    //Se creea comando de movimiento
    MarlinUI::contenedor_str[0] = '\0';
    strcpy(MarlinUI::contenedor_str, "G1 Z5 X");
    strcat(MarlinUI::contenedor_str, i16tostr4signrj(X_BED_SIZE - 5));
    strcat(MarlinUI::contenedor_str, " F4000\nG28X");
    queue.inject_P(PSTR(MarlinUI::contenedor_str));//EJECUTA EL COMANDO
    
    //se vuelve a este menu para ejecutar un loop
    MarlinUI::goto_screen(espera_calibrar_sensibilidad_eje_x);
  }
}

void calibrar_sensibilidad(){
  //hace un init de los valores
  espera_tiempo_para_confirmar = 0;
  valor_anterior_ensibilidad = 0;
  solo_una_vez_sensibilidad = false;
  MarlinUI::salida_calibrando_sensibilidad = false;
  MarlinUI::calibrando_sensibilidad = true;
  MarlinUI::home_en_accion = false;
  MarlinUI::sensibilidad_primera_parte = true;

  //pone la sensibilidad muy baja
  //para que falle y tenga que ser modificada
  stepperX.homing_threshold(36);
  stepperY.homing_threshold(36);
  queue.inject_P(PSTR("G28X"));

  //menu de espera a la prueba
  MarlinUI::goto_screen(espera_calibrar_sensibilidad_eje_x, 1);
}

void advertencia_calibrar_sensibilidad_Y(){
  MarlinUI::defer_return_to_status = true;

  crear_marco_superior(PSTR(Language_es::MSG_CALIBRAN_SENSI),0,11);

  crear_texto_centrado(Language_es::MSG_CALIBRAN_SENSI_03,  12);
  crear_texto_centrado(Language_es::MSG_CALIBRAN_SENSI_07,  22);
  crear_texto_centrado(Language_es::MSG_CALIBRAN_SENSI_05,  32);
  crear_texto_centrado(Language_es::MSG_CALIBRAN_SENSI_08,  42);
    
  crear_marco_superior(Language_es::MSG_CLICK_PARA_CONTINUAR, 54, 11);

  if(ui.use_click()){
    MarlinUI::goto_screen(calibrar_sensibilidad);
  }
}

void advertencia_calibrar_sensibilidad_x(){
  MarlinUI::defer_return_to_status = true;

  crear_marco_superior(PSTR(Language_es::MSG_CALIBRAN_SENSI),0,11);

  crear_texto_centrado(Language_es::MSG_CALIBRAN_SENSI_03,  12);
  crear_texto_centrado(Language_es::MSG_CALIBRAN_SENSI_04,  22);
  crear_texto_centrado(Language_es::MSG_CALIBRAN_SENSI_05,  32);
  crear_texto_centrado(Language_es::MSG_CALIBRAN_SENSI_06,  42);
    
  crear_marco_superior(Language_es::MSG_CLICK_PARA_CONTINUAR, 54, 11);

  if(ui.use_click()){
    MarlinUI::goto_screen(advertencia_calibrar_sensibilidad_Y);
  }
}

void advertencia_calibrar_sensibilidad(){
    MarlinUI::defer_return_to_status = true;

    crear_marco_superior(PSTR(Language_es::MSG_CALIBRAN_SENSI),0,11);

    crear_texto_centrado(Language_es::MSG_CALIBRAN_SENSI_00,  12);
    crear_texto_centrado(Language_es::MSG_CALIBRAN_SENSI_01,  22);
    
    lcd_moveto(2, 8 + 32);
    lcd_put_u8str_P(PSTR(Language_es::MSG_CALIBRAN_SENSI_02));

    crear_texto_centrado(Language_es::MSG_ALINIACION_Z_ADV_04,42);
    
    crear_marco_superior(Language_es::MSG_CLICK_PARA_CONTINUAR, 54, 11);

    if(ui.use_click()){
      queue.inject_P(PSTR("M84"));
      MarlinUI::home_en_accion = false;
      MarlinUI::goto_screen(advertencia_calibrar_sensibilidad_x);
    }
}

//final calibrar_sensibilidad
/////////////////////////////
/*
void aux_calibracion_sensibilidad(){
  MarlinUI::defer_return_to_status = true;

  START_MENU();
  NEXT_ITEM_(3);
  END_MENU();

  crear_marco_superior(Language_es::MSG_CALIBRAN_SENSI_12);

  crear_texto_centrado(Language_es::MSG_CALIBRAN_SENSI_13, 9);
  crear_texto_centrado(Language_es::MSG_CALIBRAN_SENSI_14, 19);   

  init_boto(23, 5, 3, 29);

  crear_boton(boton_inicio_a,   boton_inicio_b,   Language_es::MSG_PROBAR_ORIGEN,   salida_menu_ajuste);
  crear_boton(calibrar_mapa_a,  calibrar_mapa_b,  Language_es::MSG_CALIBRAN_SENSI,  salida_menu_ajuste);
  crear_boton(boton_reanudar_a, boton_reanudar_b, Language_es::MSG_CALI_TEMP_09_B,  salida_menu_ajuste);
}
*/
///////////////////
//Menu de ajustes//
///////////////////
void menu_ajustes(){
  MarlinUI::lcdDrawUpdate = LCDVIEW_CALL_REDRAW_NEXT; //actualiza la pantalla actual

  //setea los valores del boton volver
  MarlinUI::ultimo_valor_ventana = menu_main; //a que menu vuelve
  MarlinUI::ultimo_valor_encoder = 9;         // y la posicion del encoder al volver

  valorEncoderMenu = MarlinUI::encoderPosition; //Guarda el ultimo valor del encoder
  posicionMenu     = encoderTopLine;            //Guarda la posicion del menu
  
  START_MENU();
  BACK_ITEM(MSG_VOLVER);                                    //0 volver
  SUBMENU(MSG_VERCION,                      menu_vercion);  //1 permite ver el menu de vercion con la informacion de serie

  //SUBMENU(MSG_VERCION,                      aux_calibracion_sensibilidad);

  //se apago por las dudas
  //hay que revisar si funciona correcta mente
  #if ENABLED(PRINTCOUNTER)
    SUBMENU(MSG_INFO_STATS_MENU,            estadisticas);  //2
    SUBMENU(MSG_LOGROS,                     menu_logros);   //3
  #endif

  //opcion de calibracion, pendida o apagada
  if(planner.leveling_active || MarlinUI::inductivo_final_carrera)
    SUBMENU2(MSG_DELTA_AUTO_CALIBRATE_ON,    auto_calibracion_on_off);     //5   |Se mostrar el menu de calibracion automatica
  else
    SUBMENU2(MSG_DELTA_AUTO_CALIBRATE_OFF,   auto_calibracion_on_off);     //5   |Se mostrar la calibracion manual
  
  
  //la idea es que haya 3 tipos de calibracion
  //pero de momento no es nesesario asi que se elimina esta opcion de momento
  /*
  if(MarlinUI::inductivo_final_carrera){
    SUBMENU2(MSG_SENSOR_INDUCTIVO,          ir_cartel_error_sensor);      //6   |Cartel
  }else{
    SUBMENU2(MSG_FINAL_DE_CARRERA,          ir_cartel_error_endstop);     //6   |no se puede porque esta prendido sensor
  }
  */

  //modo de impresión el obetivo es que haya distintos modo de configuracion
  //para los tmc
  //los modos son [silencioso] [normal] [rapido] ?[Personal]?
  if(MarlinUI::modo_de_impresion == 0)       //modo normal
    SUBMENU2(MSG_MODO_IMPRESION_00,         cartel_cambio_modo_impresion);

  else if(MarlinUI::modo_de_impresion == 1)  //modo rapido
    SUBMENU2(MSG_MODO_IMPRESION_01,         cartel_cambio_modo_impresion);

  else if(MarlinUI::modo_de_impresion == 2)  //modo silencioso
    SUBMENU2(MSG_MODO_IMPRESION_02,         cartel_cambio_modo_impresion);

  else if(MarlinUI::modo_de_impresion == 3)  //modo personal
    SUBMENU2(MSG_MODO_IMPRESION_03,         cartel_cambio_modo_impresion);
  
  //permite elejir entre mostrar las capas de la pieza
  //o las coordenadas actuales de la maquina 
  if(MarlinUI::informacion_capas_coord)
    SUBMENU2(MSG_INFORMACION_CAPAS,         _informacion_capas_coord);     //7 
  else
    SUBMENU2(MSG_INFORMACION_COORD,         _informacion_capas_coord);     //7

  //permite eligir entre nuestros dos extrusores
  //el Mk8 Kuttercraft y el BMG
  if(MarlinUI::tipo_de_extrusor)
    SUBMENU2(MSG_TIPO_EXTRU_BMG,            cambiar_tipo_extrusor);       //8 tipo_de_extrusor == true == BMG
  else
    SUBMENU2(MSG_TIPO_EXTRU_MK8,            cambiar_tipo_extrusor);       //8
  
  
  //define el sentido del encode
  //por defecto es IZD == True
  if(MarlinUI::encode_der_izd)
    SUBMENU2(MSG_ENCODER_ON,                _encode_der_izd);              //10   |
  else
    SUBMENU2(MSG_ENCODER_OFF,               _encode_der_izd);              //10   |
  

  //paso del varilla
  //en la ultima electronica por defecto el falso
  //esto es porque esta configurado para varrilla
  //de paso de 4mm == 800
  if(planner.settings.axis_steps_per_mm[Z_AXIS] == 800)
    SUBMENU2(MSG_VARILLA_4MM,               _cambiar_paso_varilla);        //11   |
  else if(planner.settings.axis_steps_per_mm[Z_AXIS] == 400)
    SUBMENU2(MSG_VARILLA_8MM,               _cambiar_paso_varilla);        //11   | defecto
  else
    SUBMENU2(MSG_VARILLA_PERSONAL,          _cambiar_paso_varilla);        //11   | defecto
  
  //se quiere poder retomar una pieza
  //por defecto esta activo
  //esto genera un cartel cunado la impresion
  //no se termino adecuada mente
  if(recovery.enabled)
    SUBMENU2(MSG_GUARDADO_ON,               _cartel_guardado_redireccion); //12   |
  else
    SUBMENU2(MSG_GUARDADO_OFF,              _cartel_guardado_redireccion); //12   |
  
  
  
  //MarlinUI::sensor_filamento_on_off si es cierto
  //esta activo el sensor de filamento
  //por defecto esta en falso
  if(MarlinUI::sensor_filamento_on_off)
    SUBMENU2(MSG_RUNOUT_SENSOR_ON,          _cartel_on_off_sensor_de_filamento);               //13   |sensor_on_off //_sensor_on_off
  else
    SUBMENU2(MSG_RUNOUT_SENSOR_OFF,         _cartel_on_off_sensor_de_filamento);               //13   |sensor_on_off
  
  

  //es un sonido cuando termina la impresion
  //una se;al auditiva, por defecto esta activo
  if(MarlinUI::k_melody_on_off)
    SUBMENU2(MSG_KUTTERMELODY_ON,           _k_melody_on_off);             //14  |
  else
    SUBMENU2(MSG_KUTTERMELODY_OFF,          _k_melody_on_off);             //14  |

  

  //abre el menu de configuracion de los tmc
  SUBMENU(MSG_TMC2130_CONFI,                menu_tmc_kutter);

  /*SUBMENU(MSG_CONF_MOTOR,                   menu_motores);*/

  //permite calcular denuevo el pid con el comando M303
  SUBMENU(MSG_PID_AUTOTUNE,                 calcular_pid);                 //11  |Te dirive a PID

  
  /*SUBMENU(MSG_CLIBRA_HOME,               calibracion_de_sensibilidad_home);*/

  
  SUBMENU(MSG_CONFIG_FABRICA,               _cartel_eprom);                //12  |Tiene cartel de advertencia Carte

  //SUBMENU(MSG_ENVIAR_GCODE,               _cartel_gcode_redireccion);                      //13  |
  SUBMENU(MSG_SISTEMA,                      ir_entrar_a_sistema);                      //14

  END_MENU();
}

#endif // MENU_KUTTERCRAFT
#endif // HAS_LCD_MENU