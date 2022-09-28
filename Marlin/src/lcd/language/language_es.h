/**
 * Marlin 3D Printer Firmware
 * Copyright (c) 2020 MarlinFirmware [https://github.com/MarlinFirmware/Marlin]
 *
 * Based on Sprinter and grbl.
 * Copyright (c) 2011 Camiel Gubbels / Erik van der Zalm
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 */
#pragma once

/**
 * Spanish
 *
 * LCD Menu Messages
 * See also https://marlinfw.org/docs/development/lcd_language.html
 */

namespace Language_es {
  using namespace Language_en; // Inherit undefined strings from English

  constexpr uint8_t CHARSIZE              = 2;
  LSTR LANGUAGE                           = _UxGT("Spanish");

  LSTR WELCOME_MSG                        = MACHINE_NAME _UxGT(" Lista");
  LSTR MSG_YES                            = _UxGT("SI");
  LSTR MSG_NO                             = _UxGT("NO");
  LSTR MSG_BACK                           = _UxGT("Atrás");
  LSTR MSG_MEDIA_ABORTING                 = _UxGT("Cancelando...");
  LSTR MSG_MEDIA_INSERTED                 = _UxGT("SD/USB insertado");
  LSTR MSG_MEDIA_REMOVED                  = _UxGT("SD/USB retirado");
  LSTR MSG_MEDIA_WAITING                  = _UxGT("Esperando al SD/USB");
  LSTR MSG_SD_INIT_FAIL                   = _UxGT("Fallo al iniciar SD");
  LSTR MSG_MEDIA_READ_ERROR               = _UxGT("Error lectura SD/USB");
  LSTR MSG_MEDIA_USB_REMOVED              = _UxGT("Disp. USB retirado");
  LSTR MSG_MEDIA_USB_FAILED               = _UxGT("Inicio USB fallido");
  LSTR MSG_KILL_SUBCALL_OVERFLOW          = _UxGT("Desbordamiento de subllamada");
  LSTR MSG_LCD_ENDSTOPS                   = _UxGT("Endstops"); // Max length 8 characters
  LSTR MSG_LCD_SOFT_ENDSTOPS              = _UxGT("Soft Endstops");
  LSTR MSG_MAIN                           = _UxGT("Menú principal");
  LSTR MSG_ADVANCED_SETTINGS              = _UxGT("Ajustes avanzados");
  LSTR MSG_CONFIGURATION                  = _UxGT("Configuración");
  LSTR MSG_RUN_AUTO_FILES                 = _UxGT("Inicio automático");
  LSTR MSG_DISABLE_STEPPERS               = _UxGT("Apagar motores");
  LSTR MSG_DEBUG_MENU                     = _UxGT("Menú depuración");
  LSTR MSG_PROGRESS_BAR_TEST              = _UxGT("Prob. barra progreso");
  LSTR MSG_HOMING                         = _UxGT("Origen");
  LSTR MSG_ITERATION                      = _UxGT("G34 Iteración: %i");
  LSTR MSG_DECREASING_ACCURACY            = _UxGT("¡Precisión disminuyendo!");
  LSTR MSG_ACCURACY_ACHIEVED              = _UxGT("Precisión conseguida");
  LSTR MSG_LEVEL_BED_HOMING               = _UxGT("Origen XYZ");
  LSTR MSG_LEVEL_BED_WAITING              = _UxGT("Pulsar para comenzar");
  LSTR MSG_LEVEL_BED_NEXT_POINT           = _UxGT("Siguiente punto");
  LSTR MSG_LEVEL_BED_DONE                 = _UxGT("¡Nivelación lista!");
  LSTR MSG_Z_FADE_HEIGHT                  = _UxGT("Compen. Altura");
  LSTR MSG_SET_HOME_OFFSETS               = _UxGT("Ajustar desfases");
  LSTR MSG_HOME_OFFSETS_APPLIED           = _UxGT("Desfase aplicada");
  LSTR MSG_SET_ORIGIN                     = _UxGT("Establecer origen");
  #if PREHEAT_COUNT
    LSTR MSG_PREHEAT_1                    = _UxGT("Precal. ") PREHEAT_1_LABEL;
    LSTR MSG_PREHEAT_1_H                  = _UxGT("Precal. ") PREHEAT_1_LABEL " ~";
    LSTR MSG_PREHEAT_1_END                = _UxGT("Precal. ") PREHEAT_1_LABEL _UxGT(" Fusor");
    LSTR MSG_PREHEAT_1_END_E              = _UxGT("Precal. ") PREHEAT_1_LABEL _UxGT(" Fusor ~");
    LSTR MSG_PREHEAT_1_ALL                = _UxGT("Precal. ") PREHEAT_1_LABEL _UxGT(" Todo");
    LSTR MSG_PREHEAT_1_BEDONLY            = _UxGT("Precal. ") PREHEAT_1_LABEL _UxGT(" Cama");
    LSTR MSG_PREHEAT_1_SETTINGS           = _UxGT("Precal. ") PREHEAT_1_LABEL _UxGT(" Ajuste");

    LSTR MSG_PREHEAT_M                   = _UxGT("Precal. $");
    LSTR MSG_PREHEAT_M_H                 = _UxGT("Precal. $ ~");
    LSTR MSG_PREHEAT_M_END               = _UxGT("Precal. $ Fusor");
    LSTR MSG_PREHEAT_M_END_E             = _UxGT("Precal. $ Fusor ~");
    LSTR MSG_PREHEAT_M_ALL               = _UxGT("Precal. $ Todo");
    LSTR MSG_PREHEAT_M_BEDONLY           = _UxGT("Precal. $ Cama");
    LSTR MSG_PREHEAT_M_SETTINGS          = _UxGT("Precal. $ Ajuste");
  #endif
  LSTR MSG_PREHEAT_CUSTOM                 = _UxGT("Precal. manual");
  LSTR MSG_COOLDOWN                       = _UxGT("Enfriar");
  LSTR MSG_CUTTER_FREQUENCY               = _UxGT("Frecuencia");
  LSTR MSG_LASER_MENU                     = _UxGT("Control Láser");
  LSTR MSG_LASER_POWER                    = _UxGT("Potencia Láser");
  LSTR MSG_SPINDLE_MENU                   = _UxGT("Control Mandrino");
  LSTR MSG_SPINDLE_POWER                  = _UxGT("Potencia Mandrino");
  LSTR MSG_SPINDLE_REVERSE                = _UxGT("Invertir giro");
  LSTR MSG_SWITCH_PS_ON                   = _UxGT("Encender Fuente");
  LSTR MSG_SWITCH_PS_OFF                  = _UxGT("Apagar Fuente");
  LSTR MSG_EXTRUDE                        = _UxGT("Extruir");
  LSTR MSG_RETRACT                        = _UxGT("Retraer");
  #if DISABLED(MENU_KUTTERCRAFT)
    LSTR MSG_PID_AUTOTUNE                   = _UxGT("PID Auto-ajuste");
    LSTR MSG_MOVE_AXIS                      = _UxGT("Mover ejes");
    LSTR MSG_AUTO_HOME                      = _UxGT("Llevar al origen");
    LSTR MSG_AUTO_HOME_X                    = _UxGT("Origen X");
    LSTR MSG_AUTO_HOME_Y                    = _UxGT("Origen Y");
    LSTR MSG_AUTO_HOME_Z                    = _UxGT("Origen Z");
    LSTR MSG_AUTO_Z_ALIGN                   = _UxGT("Auto alineado Z");
  #endif
  LSTR MSG_BED_LEVELING                   = _UxGT("Nivelando Cama");
  LSTR MSG_LEVEL_BED                      = _UxGT("Nivelar Cama");
  LSTR MSG_BED_TRAMMING                   = _UxGT("Recorrido Cama");
  LSTR MSG_NEXT_CORNER                    = _UxGT("Siguente Esquina");
  LSTR MSG_MESH_EDITOR                    = _UxGT("Editor Mallado");
  LSTR MSG_EDIT_MESH                      = _UxGT("Editar Mallado");
  LSTR MSG_EDITING_STOPPED                = _UxGT("Ed. Mallado parada");
  LSTR MSG_PROBING_POINT                  = _UxGT("Sondear Punto");
  LSTR MSG_MESH_X                         = _UxGT("Índice X");
  LSTR MSG_MESH_Y                         = _UxGT("Índice Y");
  LSTR MSG_MESH_EDIT_Z                    = _UxGT("Valor Z");
  LSTR MSG_CUSTOM_COMMANDS                = _UxGT("Com. Personalizados");
  LSTR MSG_M48_TEST                       = _UxGT("M48 Probar Sonda");
  LSTR MSG_M48_POINT                      = _UxGT("M48 Punto");
  LSTR MSG_M48_DEVIATION                  = _UxGT("Desviación");
  LSTR MSG_IDEX_MENU                      = _UxGT("Modo IDEX");
  LSTR MSG_OFFSETS_MENU                   = _UxGT("Desfase Herramienta");
  LSTR MSG_IDEX_MODE_AUTOPARK             = _UxGT("Auto-Aparcado");
  LSTR MSG_IDEX_MODE_DUPLICATE            = _UxGT("Duplicar");
  LSTR MSG_IDEX_MODE_MIRRORED_COPY        = _UxGT("Copia Reflejada");
  LSTR MSG_IDEX_MODE_FULL_CTRL            = _UxGT("Control Total");
  LSTR MSG_HOTEND_OFFSET_X                = _UxGT("2ª Fusor X");
  LSTR MSG_HOTEND_OFFSET_Y                = _UxGT("2ª Fusor Y");
  LSTR MSG_HOTEND_OFFSET_Z                = _UxGT("2ª Fusor Z");
  LSTR MSG_UBL_DOING_G29                  = _UxGT("Hacer G29");
  LSTR MSG_UBL_TOOLS                      = _UxGT("Herramientas UBL");
  LSTR MSG_UBL_LEVEL_BED                  = _UxGT("Nivelado UBL");
  LSTR MSG_LCD_TILTING_MESH               = _UxGT("Punto de inclinación");
  LSTR MSG_UBL_MANUAL_MESH                = _UxGT("Crear Mallado man.");
  LSTR MSG_UBL_BC_INSERT                  = _UxGT("Colocar cuña y Medir");
  LSTR MSG_UBL_BC_INSERT2                 = _UxGT("Medir");
  LSTR MSG_UBL_BC_REMOVE                  = _UxGT("Retirar y Medir Cama");
  LSTR MSG_UBL_MOVING_TO_NEXT             = _UxGT("Mover al Siguente");
  LSTR MSG_UBL_ACTIVATE_MESH              = _UxGT("Activar UBL");
  LSTR MSG_UBL_DEACTIVATE_MESH            = _UxGT("Desactivar UBL");
  LSTR MSG_UBL_SET_TEMP_BED               = _UxGT("Temp. Cama");
  LSTR MSG_UBL_BED_TEMP_CUSTOM            = _UxGT("Temp. Cama perso.");
  LSTR MSG_UBL_SET_TEMP_HOTEND            = _UxGT("Temp. Fusor");
  LSTR MSG_UBL_HOTEND_TEMP_CUSTOM         = _UxGT("Temp. Fusor perso.");
  LSTR MSG_UBL_MESH_EDIT                  = _UxGT("Editar Mallado");
  LSTR MSG_UBL_EDIT_CUSTOM_MESH           = _UxGT("Edit. Mallado perso.");
  LSTR MSG_UBL_FINE_TUNE_MESH             = _UxGT("Ajuste fino Mallado");
  LSTR MSG_UBL_DONE_EDITING_MESH          = _UxGT("Term. edici. Mallado");
  LSTR MSG_UBL_BUILD_CUSTOM_MESH          = _UxGT("Crear Mallado Pers.");
  LSTR MSG_UBL_BUILD_MESH_MENU            = _UxGT("Crear Mallado");
  #if PREHEAT_COUNT
    LSTR MSG_UBL_BUILD_MESH_M             = _UxGT("Crear Mallado ($)");
    LSTR MSG_UBL_VALIDATE_MESH_M          = _UxGT("Valid. Mall. ($)");
  #endif
  LSTR MSG_UBL_BUILD_COLD_MESH            = _UxGT("Crear Mallado Frío");
  LSTR MSG_UBL_MESH_HEIGHT_ADJUST         = _UxGT("Ajustar alt. Mallado");
  LSTR MSG_UBL_MESH_HEIGHT_AMOUNT         = _UxGT("Cantidad de altura");
  LSTR MSG_UBL_VALIDATE_MESH_MENU         = _UxGT("Valid. Mallado");
  LSTR MSG_UBL_VALIDATE_CUSTOM_MESH       = _UxGT("Valid. Mall. perso.");
  LSTR MSG_G26_HEATING_BED                = _UxGT("G26 Calentando Cama");
  LSTR MSG_G26_HEATING_NOZZLE             = _UxGT("G26 Calent. Boquilla");
  LSTR MSG_G26_MANUAL_PRIME               = _UxGT("Imprimado manual...");
  LSTR MSG_G26_FIXED_LENGTH               = _UxGT("Impri. longit. fija");
  LSTR MSG_G26_PRIME_DONE                 = _UxGT("Imprimación Lista");
  LSTR MSG_G26_CANCELED                   = _UxGT("G26 Cancelado");
  LSTR MSG_G26_LEAVING                    = _UxGT("Dejando G26");
  LSTR MSG_UBL_CONTINUE_MESH              = _UxGT("Contin. Mallado cama");
  LSTR MSG_UBL_MESH_LEVELING              = _UxGT("Nivelando Mallado");
  LSTR MSG_UBL_3POINT_MESH_LEVELING       = _UxGT("Nivelando 3Puntos");
  LSTR MSG_UBL_GRID_MESH_LEVELING         = _UxGT("Niv. Mall. cuadri");
  LSTR MSG_UBL_MESH_LEVEL                 = _UxGT("Nivel de Mallado");
  LSTR MSG_UBL_SIDE_POINTS                = _UxGT("Puntos Laterales");
  LSTR MSG_UBL_MAP_TYPE                   = _UxGT("Tipo de mapa ");
  LSTR MSG_UBL_OUTPUT_MAP                 = _UxGT("Salida Mapa mallado");
  LSTR MSG_UBL_OUTPUT_MAP_HOST            = _UxGT("Salida para el host");
  LSTR MSG_UBL_OUTPUT_MAP_CSV             = _UxGT("Salida para CSV");
  LSTR MSG_UBL_OUTPUT_MAP_BACKUP          = _UxGT("Cópia de seg. ext");
  LSTR MSG_UBL_INFO_UBL                   = _UxGT("Salida Info. UBL");
  LSTR MSG_UBL_FILLIN_AMOUNT              = _UxGT("Cantidad de relleno");
  LSTR MSG_UBL_MANUAL_FILLIN              = _UxGT("Relleno manual");
  LSTR MSG_UBL_SMART_FILLIN               = _UxGT("Relleno inteligente");
  LSTR MSG_UBL_FILLIN_MESH                = _UxGT("Mallado de relleno");
  LSTR MSG_UBL_INVALIDATE_ALL             = _UxGT("Invalidar todo");
  LSTR MSG_UBL_INVALIDATE_CLOSEST         = _UxGT("Invalidar proximos");
  LSTR MSG_UBL_FINE_TUNE_ALL              = _UxGT("Ajustar Fino Todo");
  LSTR MSG_UBL_FINE_TUNE_CLOSEST          = _UxGT("Ajustar Fino proxi.");
  LSTR MSG_UBL_STORAGE_MESH_MENU          = _UxGT("Almacen de Mallado");
  LSTR MSG_UBL_STORAGE_SLOT               = _UxGT("Huecos memoria");
  LSTR MSG_UBL_LOAD_MESH                  = _UxGT("Cargar Mall. cama");
  LSTR MSG_UBL_SAVE_MESH                  = _UxGT("Guardar Mall. cama");
  LSTR MSG_MESH_LOADED                    = _UxGT("Malla %i Cargada");
  LSTR MSG_MESH_SAVED                     = _UxGT("Malla %i Guardada");
  LSTR MSG_UBL_NO_STORAGE                 = _UxGT("Sin guardar");
  LSTR MSG_UBL_SAVE_ERROR                 = _UxGT("Error: Guardar UBL");
  LSTR MSG_UBL_RESTORE_ERROR              = _UxGT("Error: Restaurar UBL");
  LSTR MSG_UBL_Z_OFFSET                   = _UxGT("Desfase de Z: ");
  LSTR MSG_UBL_Z_OFFSET_STOPPED           = _UxGT("Desfase de Z Parado");
  LSTR MSG_UBL_STEP_BY_STEP_MENU          = _UxGT("UBL Paso a Paso");
  LSTR MSG_UBL_1_BUILD_COLD_MESH          = _UxGT("1.Crear Mall. Frío");
  LSTR MSG_UBL_2_SMART_FILLIN             = _UxGT("2.Relleno intelig.");
  LSTR MSG_UBL_3_VALIDATE_MESH_MENU       = _UxGT("3.Valid. Mallado");
  LSTR MSG_UBL_4_FINE_TUNE_ALL            = _UxGT("4.Ajustar Fino Todo");
  LSTR MSG_UBL_5_VALIDATE_MESH_MENU       = _UxGT("5.Valid. Mallado");
  LSTR MSG_UBL_6_FINE_TUNE_ALL            = _UxGT("6.Ajustar Fino Todo");
  LSTR MSG_UBL_7_SAVE_MESH                = _UxGT("7.Guardar Mall. cama");

  LSTR MSG_LEDS                           = _UxGT("LEDS");
  LSTR MSG_LED_PRESETS                    = _UxGT("Color predefinido");
  LSTR MSG_SET_LEDS_RED                   = _UxGT("Rojo");
  LSTR MSG_SET_LEDS_ORANGE                = _UxGT("Naranja");
  LSTR MSG_SET_LEDS_YELLOW                = _UxGT("Amarillo");
  LSTR MSG_SET_LEDS_GREEN                 = _UxGT("Verde");
  LSTR MSG_SET_LEDS_BLUE                  = _UxGT("Azul");
  LSTR MSG_SET_LEDS_INDIGO                = _UxGT("Índigo");
  LSTR MSG_SET_LEDS_VIOLET                = _UxGT("Violeta");
  LSTR MSG_SET_LEDS_WHITE                 = _UxGT("Blanco");
  LSTR MSG_SET_LEDS_DEFAULT               = _UxGT("Por defecto");
  LSTR MSG_CUSTOM_LEDS                    = _UxGT("Color personalizado");
  LSTR MSG_INTENSITY_R                    = _UxGT("Intensidad Rojo");
  LSTR MSG_INTENSITY_G                    = _UxGT("Intensidad Verde");
  LSTR MSG_INTENSITY_B                    = _UxGT("Intensidad Azul");
  LSTR MSG_INTENSITY_W                    = _UxGT("Intensidad Blanco");
  LSTR MSG_LED_BRIGHTNESS                 = _UxGT("Brillo");

  LSTR MSG_MOVING                         = _UxGT("Moviendo...");
  LSTR MSG_FREE_XY                        = _UxGT("Libre XY");
  LSTR MSG_MOVE_X                         = _UxGT("Mover X");
  LSTR MSG_MOVE_Y                         = _UxGT("Mover Y");
  LSTR MSG_MOVE_Z                         = _UxGT("Mover Z");
  LSTR MSG_MOVE_E                         = _UxGT("Extrusor");
  LSTR MSG_MOVE_EN                        = _UxGT("Extrusor *");
  LSTR MSG_HOTEND_TOO_COLD                = _UxGT("Hotend muy frio");
  LSTR MSG_MOVE_N_MM                      = _UxGT("Mover %smm");
  LSTR MSG_MOVE_01MM                      = _UxGT("Mover 0.1mm");
  LSTR MSG_MOVE_1MM                       = _UxGT("Mover 1mm");
  LSTR MSG_MOVE_100MM                     = _UxGT("Mover 100mm");
  LSTR MSG_SPEED                          = _UxGT("Velocidad");
  LSTR MSG_BED_Z                          = _UxGT("Cama Z");
  LSTR MSG_NOZZLE                         = _UxGT("Boquilla");
  LSTR MSG_NOZZLE_N                       = _UxGT("Boquilla ~");
  LSTR MSG_NOZZLE_PARKED                  = _UxGT("Boquilla Aparcada");
  LSTR MSG_NOZZLE_STANDBY                 = _UxGT("Boquilla en Espera");
  LSTR MSG_BED                            = _UxGT("Cama");
  LSTR MSG_CHAMBER                        = _UxGT("Recinto");
  LSTR MSG_FAN_SPEED                      = _UxGT("Ventilador");
  LSTR MSG_FAN_SPEED_N                    = _UxGT("Ventilador ~");
  LSTR MSG_STORED_FAN_N                   = _UxGT("Vent. almacenado ~");
  LSTR MSG_EXTRA_FAN_SPEED                = _UxGT("Vel. Ext. ventil.");
  LSTR MSG_EXTRA_FAN_SPEED_N              = _UxGT("Vel. Ext. ventil. ~");
  LSTR MSG_CONTROLLER_FAN                 = _UxGT("Controlador Vent.");
  LSTR MSG_CONTROLLER_FAN_IDLE_SPEED      = _UxGT("Velocidad en reposo");
  LSTR MSG_CONTROLLER_FAN_AUTO_ON         = _UxGT("Modo Auto");
  LSTR MSG_CONTROLLER_FAN_SPEED           = _UxGT("Velocidad Activa");
  LSTR MSG_CONTROLLER_FAN_DURATION        = _UxGT("Periodo de reposo");
  LSTR MSG_FLOW                           = _UxGT("Flujo");
  LSTR MSG_FLOW_N                         = _UxGT("Flujo ~");
  LSTR MSG_CONTROL                        = _UxGT("Control");
  LSTR MSG_MIN                            = " " LCD_STR_THERMOMETER _UxGT(" Min");
  LSTR MSG_MAX                            = " " LCD_STR_THERMOMETER _UxGT(" Max");
  LSTR MSG_FACTOR                         = " " LCD_STR_THERMOMETER _UxGT(" Factor");
  LSTR MSG_AUTOTEMP                       = _UxGT("Temp. Autom.");
  LSTR MSG_LCD_ON                         = _UxGT("[Modo Silencioso]");
  LSTR MSG_LCD_OFF                        = _UxGT("[Modo Fuerza]");
  LSTR MSG_PID_AUTOTUNE_E                 = _UxGT("PID Auto-ajuste *");
  LSTR MSG_SELECT_E                       = _UxGT("Seleccionar *");
  LSTR MSG_ACC                            = _UxGT("Aceleración");
  LSTR MSG_JERK                           = _UxGT("Jerk");
  LSTR MSG_VA_JERK                        = _UxGT("Max ") STR_A _UxGT(" Jerk");
  LSTR MSG_VB_JERK                        = _UxGT("Max ") STR_B _UxGT(" Jerk");
  LSTR MSG_VC_JERK                        = _UxGT("Max ") STR_C _UxGT(" Jerk");
  LSTR MSG_VI_JERK                        = _UxGT("Max ") STR_I _UxGT(" Jerk");
  LSTR MSG_VJ_JERK                        = _UxGT("Max ") STR_J _UxGT(" Jerk");
  LSTR MSG_VK_JERK                        = _UxGT("Max ") STR_K _UxGT(" Jerk");
  LSTR MSG_VE_JERK                        = _UxGT("Max E Jerk");
  LSTR MSG_JUNCTION_DEVIATION             = _UxGT("Desvi. Unión");
  LSTR MSG_VELOCITY                       = _UxGT("Velocidad");
  LSTR MSG_VMAX_A                         = _UxGT("Max ") STR_A _UxGT(" Vel");
  LSTR MSG_VMAX_B                         = _UxGT("Max ") STR_B _UxGT(" Vel");
  LSTR MSG_VMAX_C                         = _UxGT("Max ") STR_C _UxGT(" Vel");
  LSTR MSG_VMAX_I                         = _UxGT("Max ") STR_I _UxGT(" Vel");
  LSTR MSG_VMAX_J                         = _UxGT("Max ") STR_J _UxGT(" Vel");
  LSTR MSG_VMAX_K                         = _UxGT("Max ") STR_K _UxGT(" Vel");
  LSTR MSG_VMAX_E                         = _UxGT("Max ") STR_E _UxGT(" Vel");
  LSTR MSG_VMAX_EN                        = _UxGT("Max * Vel");
  LSTR MSG_VMIN                           = _UxGT("Vmin");
  LSTR MSG_VTRAV_MIN                      = _UxGT("Vel. viaje min");
  LSTR MSG_ACCELERATION                   = _UxGT("Acceleración");
  LSTR MSG_AMAX_A                         = _UxGT("Max ") STR_A _UxGT(" Accel");
  LSTR MSG_AMAX_B                         = _UxGT("Max ") STR_B _UxGT(" Accel");
  LSTR MSG_AMAX_C                         = _UxGT("Max ") STR_C _UxGT(" Accel");
  LSTR MSG_AMAX_I                         = _UxGT("Max ") STR_I _UxGT(" Accel");
  LSTR MSG_AMAX_J                         = _UxGT("Max ") STR_J _UxGT(" Accel");
  LSTR MSG_AMAX_K                         = _UxGT("Max ") STR_K _UxGT(" Accel");
  LSTR MSG_AMAX_E                         = _UxGT("Max ") STR_E _UxGT(" Accel");
  LSTR MSG_AMAX_EN                        = _UxGT("Acel. max *");
  LSTR MSG_A_RETRACT                      = _UxGT("Acel. retrac.");
  LSTR MSG_A_TRAVEL                       = _UxGT("Acel. Viaje");
  LSTR MSG_STEPS_PER_MM                   = _UxGT("Pasos/mm");
  LSTR MSG_A_STEPS                        = STR_A _UxGT(" Steps/mm");
  LSTR MSG_B_STEPS                        = STR_B _UxGT(" Steps/mm");
  LSTR MSG_C_STEPS                        = STR_C _UxGT(" Steps/mm");
  LSTR MSG_I_STEPS                        = STR_I _UxGT(" Steps/mm");
  LSTR MSG_J_STEPS                        = STR_J _UxGT(" Steps/mm");
  LSTR MSG_K_STEPS                        = STR_K _UxGT(" Steps/mm");
  LSTR MSG_E_STEPS                        = _UxGT("E pasos/mm");
  LSTR MSG_EN_STEPS                       = _UxGT("* pasos/mm");
  LSTR MSG_TEMPERATURE                    = _UxGT("Temperatura");
  LSTR MSG_MOTION                         = _UxGT("Movimiento");
  #if DISABLED(MENU_KUTTERCRAFT)
    LSTR MSG_SELECT                         = _UxGT("Seleccionar");
    LSTR MSG_FILAMENT                       = _UxGT("Filamento");
    LSTR MSG_RESET_PRINTER                  = _UxGT("Resetear Impresora");
    LSTR MSG_LED_CONTROL                    = _UxGT("Control LED");
  #endif
  LSTR MSG_VOLUMETRIC_ENABLED             = _UxGT("E en mm") SUPERSCRIPT_THREE;
  LSTR MSG_FILAMENT_DIAM                  = _UxGT("Diámetro Fil.");
  LSTR MSG_FILAMENT_DIAM_E                = _UxGT("Diámetro Fil. *");
  LSTR MSG_FILAMENT_UNLOAD                = _UxGT("Descarga mm");
  LSTR MSG_FILAMENT_LOAD                  = _UxGT("Carga mm");
  LSTR MSG_ADVANCE_K                      = _UxGT("Avance K");
  LSTR MSG_ADVANCE_K_E                    = _UxGT("Avance K *");
  LSTR MSG_CONTRAST                       = _UxGT("Contraste LCD");
  LSTR MSG_STORE_EEPROM                   = _UxGT("Guardar EEPROM");
  LSTR MSG_LOAD_EEPROM                    = _UxGT("Cargar EEPROM");
  LSTR MSG_RESTORE_DEFAULTS               = _UxGT("Rest. fábrica");
  LSTR MSG_INIT_EEPROM                    = _UxGT("Inicializar EEPROM");
  LSTR MSG_ERR_EEPROM_CRC                 = _UxGT("Err: EEPROM CRC");
  LSTR MSG_ERR_EEPROM_INDEX               = _UxGT("Err: Índice EEPROM");
  LSTR MSG_ERR_EEPROM_VERSION             = _UxGT("Err: Versión EEPROM");
  LSTR MSG_MEDIA_UPDATE                   = _UxGT("Actualizar SD/USB");
  LSTR MSG_REFRESH                        = LCD_STR_REFRESH  _UxGT("Recargar");
  LSTR MSG_INFO_SCREEN                    = _UxGT("Pantalla de Inf.");
  LSTR MSG_PREPARE                        = _UxGT("Preparar");
  LSTR MSG_TUNE                           = _UxGT("Ajustar");
  LSTR MSG_START_PRINT                    = _UxGT("Iniciar impresión");
  LSTR MSG_BUTTON_NEXT                    = _UxGT("Siguinte");
  LSTR MSG_BUTTON_INIT                    = _UxGT("Iniciar");
  LSTR MSG_BUTTON_STOP                    = _UxGT("Parar");
  LSTR MSG_BUTTON_PRINT                   = _UxGT("Imprimir");
  LSTR MSG_BUTTON_RESET                   = _UxGT("Reiniciar");
  LSTR MSG_BUTTON_CANCEL                  = _UxGT("Cancelar");
  LSTR MSG_BUTTON_DONE                    = _UxGT("Listo");
  LSTR MSG_BUTTON_BACK                    = _UxGT("Retroceder");
  LSTR MSG_BUTTON_PROCEED                 = _UxGT("Proceder");
  LSTR MSG_PAUSE_PRINT                    = _UxGT("Pausar impresión");
  LSTR MSG_STOP_PRINT                     = _UxGT("Detener impresión");
  LSTR MSG_PRINTING_OBJECT                = _UxGT("Imprimiendo Objeto");
  LSTR MSG_CANCEL_OBJECT                  = _UxGT("Cancelar Objeto");
  LSTR MSG_CANCEL_OBJECT_N                = _UxGT("Cancelar Objeto =");
  LSTR MSG_OUTAGE_RECOVERY                = _UxGT("Rec. Fallo electrico");
  #if DISABLED(MENU_KUTTERCRAFT)
    LSTR MSG_MOVE_10MM                      = _UxGT("Mover 10mm");
    LSTR MSG_RESUME_PRINT                   = _UxGT("Reanudar impresión");
    LSTR MSG_MEDIA_MENU                     = _UxGT("Imprim. desde SD/USB");
  #endif
  LSTR MSG_NO_MEDIA                       = _UxGT("SD/USB no presente");
  LSTR MSG_DWELL                          = _UxGT("Reposo...");
  LSTR MSG_USERWAIT                       = _UxGT("Pulsar para Reanudar");
  LSTR MSG_PRINT_PAUSED                   = _UxGT("Impresión Pausada");
  LSTR MSG_PRINTING                       = _UxGT("Imprimiendo...");
  LSTR MSG_PRINT_ABORTED                  = _UxGT("Impresión cancelada");
  LSTR MSG_PRINT_DONE                     = _UxGT("Impresión Completada");
  LSTR MSG_NO_MOVE                        = _UxGT("Sin movimiento");
  LSTR MSG_KILLED                         = _UxGT("MUERTA");
  LSTR MSG_STOPPED                        = _UxGT("DETENIDA");
  LSTR MSG_CONTROL_RETRACT                = _UxGT("Retraer mm");
  LSTR MSG_CONTROL_RETRACT_SWAP           = _UxGT("Interc. Retraer mm");
  LSTR MSG_CONTROL_RETRACTF               = _UxGT("Retraer  V");
  LSTR MSG_CONTROL_RETRACT_ZHOP           = _UxGT("Levantar mm");
  LSTR MSG_CONTROL_RETRACT_RECOVER        = _UxGT("DesRet mm");
  LSTR MSG_CONTROL_RETRACT_RECOVER_SWAP   = _UxGT("Interc. DesRet mm");
  LSTR MSG_CONTROL_RETRACT_RECOVERF       = _UxGT("DesRet V");
  LSTR MSG_CONTROL_RETRACT_RECOVER_SWAPF  = _UxGT("S UnRet V");
  LSTR MSG_AUTORETRACT                    = _UxGT("Retracción Auto.");
  LSTR MSG_FILAMENT_SWAP_LENGTH           = _UxGT("Inter. longitud");
  LSTR MSG_FILAMENT_PURGE_LENGTH          = _UxGT("Purgar longitud");
  LSTR MSG_TOOL_CHANGE                    = _UxGT("Cambiar Herramienta");
  LSTR MSG_TOOL_CHANGE_ZLIFT              = _UxGT("Aumentar Z");
  LSTR MSG_SINGLENOZZLE_PRIME_SPEED       = _UxGT("Vel. de Cebado");
  LSTR MSG_SINGLENOZZLE_RETRACT_SPEED     = _UxGT("Vel. de retracción");
  #if DISABLED(MENU_KUTTERCRAFT)
    LSTR MSG_INFO_STATS_MENU                = _UxGT("Estadísticas Imp.");
    LSTR MSG_ZPROBE_ZOFFSET                 = _UxGT("Desf. Sonda Z");
    LSTR MSG_FILAMENTCHANGE                 = _UxGT("Cambiar filamento");
    LSTR MSG_FILAMENTCHANGE_E               = _UxGT("Cambiar filamento *");
    LSTR MSG_FILAMENTLOAD_E                 = _UxGT("Cargar filamento *");
    LSTR MSG_FILAMENTLOAD                   = _UxGT("Cargar filamento");
    LSTR MSG_FILAMENTUNLOAD                 = _UxGT("Descargar filamento");
  #endif
  LSTR MSG_FILAMENTUNLOAD_E               = _UxGT("Descargar fil. *");
  LSTR MSG_FILAMENTUNLOAD_ALL             = _UxGT("Descargar todo");
  LSTR MSG_ATTACH_MEDIA                   = _UxGT("Iniciar SD/USB");
  LSTR MSG_CHANGE_MEDIA                   = _UxGT("Cambiar SD/USB");
  LSTR MSG_RELEASE_MEDIA                  = _UxGT("Lanzar SD/USB");
  LSTR MSG_ZPROBE_OUT                     = _UxGT("Sonda Z fuera cama");
  LSTR MSG_SKEW_FACTOR                    = _UxGT("Factor de desviación");
  LSTR MSG_BLTOUCH                        = _UxGT("BLTouch");
  LSTR MSG_BLTOUCH_SELFTEST               = _UxGT("Auto-Prueba");
  LSTR MSG_BLTOUCH_RESET                  = _UxGT("Reiniciar");
  LSTR MSG_BLTOUCH_STOW                   = _UxGT("Subir pistón");
  LSTR MSG_BLTOUCH_DEPLOY                 = _UxGT("Bajar pistón");
  LSTR MSG_BLTOUCH_SW_MODE                = _UxGT("Modo Software");
  LSTR MSG_BLTOUCH_5V_MODE                = _UxGT("Modo 5V");
  LSTR MSG_BLTOUCH_OD_MODE                = _UxGT("Modo OD");
  LSTR MSG_BLTOUCH_MODE_STORE             = _UxGT("Modo almacenar");
  LSTR MSG_BLTOUCH_MODE_STORE_5V          = _UxGT("Poner BLTouch a 5V");
  LSTR MSG_BLTOUCH_MODE_STORE_OD          = _UxGT("Poner BLTouch a OD");
  LSTR MSG_BLTOUCH_MODE_ECHO              = _UxGT("Informe de drenaje");
  LSTR MSG_BLTOUCH_MODE_CHANGE            = _UxGT("PELIGRO: ¡Una mala configuración puede producir daños! ¿Proceder igualmente?");
  LSTR MSG_TOUCHMI_PROBE                  = _UxGT("TouchMI");
  LSTR MSG_TOUCHMI_INIT                   = _UxGT("Iniciar TouchMI");
  LSTR MSG_TOUCHMI_ZTEST                  = _UxGT("Test de desfase Z");
  LSTR MSG_TOUCHMI_SAVE                   = _UxGT("Guardar");
  LSTR MSG_MANUAL_DEPLOY_TOUCHMI          = _UxGT("Subir TouchMI");
  LSTR MSG_MANUAL_DEPLOY                  = _UxGT("Subir Sonda Z");
  LSTR MSG_MANUAL_STOW                    = _UxGT("Bajar Sonda Z");
  LSTR MSG_HOME_FIRST                     = _UxGT("Origen %s%s%s Prim.");
  LSTR MSG_ZPROBE_OFFSETS                 = _UxGT("Desf. Sonda");
  LSTR MSG_ZPROBE_XOFFSET                 = _UxGT("Desf. Sonda X");
  LSTR MSG_ZPROBE_YOFFSET                 = _UxGT("Desf. Sonda Y");
  LSTR MSG_BABYSTEP_X                     = _UxGT("Micropaso X");
  LSTR MSG_BABYSTEP_Y                     = _UxGT("Micropaso Y");
  LSTR MSG_BABYSTEP_Z                     = _UxGT("Micropaso Z");
  LSTR MSG_BABYSTEP_TOTAL                 = _UxGT("Total");
  LSTR MSG_ENDSTOP_ABORT                  = _UxGT("Cancelado - Endstop");
  LSTR MSG_HEATING_FAILED_LCD             = _UxGT("Calent. fallido");
  LSTR MSG_ERR_REDUNDANT_TEMP             = _UxGT("Err: TEMP. REDUN.");
  LSTR MSG_THERMAL_RUNAWAY                = _UxGT("FUGA TÉRMICA");
  LSTR MSG_THERMAL_RUNAWAY_BED            = _UxGT("FUGA TÉRMICA CAMA");
  LSTR MSG_THERMAL_RUNAWAY_CHAMBER        = _UxGT("FUGA TÉRMICA CAMARA");
  LSTR MSG_ERR_MAXTEMP                    = _UxGT("Err:TEMP. MÁX");
  LSTR MSG_ERR_MINTEMP                    = _UxGT("Err:TEMP. MIN");
  LSTR MSG_HALTED                         = _UxGT("IMPRESORA DETENIDA");
  LSTR MSG_PLEASE_RESET                   = _UxGT("Por favor, reinicie");
  LSTR MSG_HEATING                        = _UxGT("Calentando...");
  LSTR MSG_COOLING                        = _UxGT("Enfriando...");
  LSTR MSG_BED_HEATING                    = _UxGT("Calentando Cama...");
  LSTR MSG_BED_COOLING                    = _UxGT("Enfriando Cama...");
  LSTR MSG_CHAMBER_HEATING                = _UxGT("Calentando Cámara...");
  LSTR MSG_CHAMBER_COOLING                = _UxGT("Enfriando Cámara...");
  LSTR MSG_DELTA_CALIBRATE                = _UxGT("Calibración Delta");
  LSTR MSG_DELTA_CALIBRATE_X              = _UxGT("Calibrar X");
  LSTR MSG_DELTA_CALIBRATE_Y              = _UxGT("Calibrar Y");
  LSTR MSG_DELTA_CALIBRATE_Z              = _UxGT("Calibrar Z");
  LSTR MSG_DELTA_CALIBRATE_CENTER         = _UxGT("Calibrar Centro");
  LSTR MSG_DELTA_SETTINGS                 = _UxGT("Configuración Delta");
  LSTR MSG_DELTA_AUTO_CALIBRATE           = _UxGT("Auto Calibración");
  LSTR MSG_DELTA_HEIGHT_CALIBRATE         = _UxGT("Est. Altura Delta");
  LSTR MSG_DELTA_Z_OFFSET_CALIBRATE       = _UxGT("Ajustar Sonda Z");
  LSTR MSG_DELTA_DIAG_ROD                 = _UxGT("Barra Diagonal");
  LSTR MSG_DELTA_HEIGHT                   = _UxGT("Altura");
  LSTR MSG_DELTA_RADIUS                   = _UxGT("Radio");
  LSTR MSG_INFO_MENU                      = _UxGT("Info. Impresora");
  LSTR MSG_INFO_PRINTER_MENU              = _UxGT("Info. Impresora");
  LSTR MSG_3POINT_LEVELING                = _UxGT("Nivelando 3puntos");
  LSTR MSG_LINEAR_LEVELING                = _UxGT("Nivelando Lineal");
  LSTR MSG_BILINEAR_LEVELING              = _UxGT("Nivelando Bilineal");
  LSTR MSG_UBL_LEVELING                   = _UxGT("Nivelando UBL");
  LSTR MSG_MESH_LEVELING                  = _UxGT("Nivelando en Mallado");
  LSTR MSG_INFO_BOARD_MENU                = _UxGT("Info. Controlador");
  LSTR MSG_INFO_THERMISTOR_MENU           = _UxGT("Termistores");
  LSTR MSG_INFO_EXTRUDERS                 = _UxGT("Extrusores");
  LSTR MSG_INFO_BAUDRATE                  = _UxGT("Baudios");
  LSTR MSG_INFO_PROTOCOL                  = _UxGT("Protocolo");
  LSTR MSG_INFO_RUNAWAY_OFF               = _UxGT("Vig. Fuga Térm.: OFF");
  LSTR MSG_INFO_RUNAWAY_ON                = _UxGT("Vig. Fuga Térm.: ON");

  LSTR MSG_CASE_LIGHT                     = _UxGT("Luz cabina");
  LSTR MSG_CASE_LIGHT_BRIGHTNESS          = _UxGT("Brillo cabina");
  LSTR MSG_KILL_EXPECTED_PRINTER          = _UxGT("Impresora incorrecta");


//--------------kuttercraft--------------//
  LSTR MSG_ORLANDO                         = _UxGT("Orlando2");
  LSTR MSG_INICIO                          = _UxGT("Inicio");
  LSTR MSG_FILAMENT                        = _UxGT("Ajuste De Filamento");
  LSTR MSG_MEDIA_MENU                      = _UxGT("Tarjeta SD");
  LSTR MSG_FILAMENTCHANGE_E                = _UxGT("Cambiar Filamento *");
  
  LSTR MSG_FILAMENTLOAD_E                  = _UxGT("Cargar Filamento *");
  LSTR MSG_CARGA_Y_DESCARGA                = _UxGT("Cargar Y Descarga");
  
  
  //Palabras agregadas para el menu de kuttercraft
  ////////////////////////////////////////////////
  LSTR MSG_PRINT_CANCELAR                  = _UxGT("Cancelar Impresión");
  LSTR MSG_PRINT_CANCELANDO                = _UxGT("Cancelando Impresión");
  LSTR MSG_VELOCITY_MENU                   = _UxGT("Cambiar Velocidad");
  LSTR MSG_RESET_PRINTER                   = _UxGT("Reiniciar Impresora");
  LSTR MSG_SELECT                          = _UxGT("Seleccione");
  LSTR MSG_LA_TEMPERATURE                  = _UxGT("La Temperatura");
  LSTR MSG_FLOW_MENU                       = _UxGT("Modificar Flujo");
  
  LSTR MSG_SALIR                           = _UxGT("Salir");
  LSTR MSG_VOLVER                          = _UxGT("Volver");
  LSTR MSG_MANUALES                        = _UxGT("Manuales");
  LSTR MSG_PREDETERMINADO                  = _UxGT("Predeterminado");
  LSTR MSG_PRESET                          = _UxGT("Preset");
  LSTR MSG_PRESET_PLA                      = _UxGT("Preset PLA");
  LSTR MSG_PRESET_ABS                      = _UxGT("Preset ABS");
  LSTR MSG_PRESET_FLEX                     = _UxGT("Preset FLEX");
  LSTR MSG_PRESET_NYLON                    = _UxGT("Preset NYLON");
  
  LSTR MSG_POR_FAVOR_ESPERE                = _UxGT("Por Favor Espere");
  LSTR MSG_FILAMENTCHANGE                  = _UxGT("Cambiar Filamento");
  LSTR MSG_FILAMENTCHANGE_NOW              = _UxGT("Cambiar Fila. Ahora");
  LSTR MSG_FILAMENTCHANGE_CAPA             = _UxGT("Cambiar Fila. En Capa");
  LSTR MSG_FILAMENTLOAD                    = _UxGT("Cargar Filamento");
  LSTR MSG_CARGANDO_FILAMENTO              = _UxGT("Cargando Filamento");
  LSTR MSG_FILAMENTUNLOAD                  = _UxGT("Retirar Filamento");
  LSTR MSG_RETIRANDO_FILAMENTO             = _UxGT("Retirando Filamento");
  LSTR MSG_RESUME_PRINT                    = _UxGT("Reanudar Impresión");
  LSTR MSG_LIST_CAPA                       = _UxGT("Lista de Cambios");
  LSTR MSG_ADD_CAPA                        = _UxGT("Cambio Por Capa");
  LSTR MSG_CAPA                            = _UxGT("Capa:");
  LSTR MSG_CAPA_MSG_01                     = _UxGT("Selecciones Una Capa");
  LSTR MSG_CAPA_MSG_02                     = _UxGT("Para Cambio de Fila.");
  
  LSTR MSG_CAPA_ERROR_01                   = _UxGT("Error De Capa");
  LSTR MSG_CAPA_ERROR_02                   = _UxGT("Maximo Alcanzado");
  
  LSTR MSG_BED_HOT                         = _UxGT("Cama Caliente");
  LSTR MSG_LED_CONTROL                     = _UxGT("Encender LED");
  LSTR MSG_LED_APAGAR                      = _UxGT("Apagar LED");
  LSTR MSG_CAMBIAR_VERSION                 = _UxGT("Cambiar Version");//"Cambiar Version"
  LSTR MSG_BORRAR_ESTADISTICAS             = _UxGT("Borrar Estadistica");//Borrar Estadistica"

  //Calibración UBL Kuttercraft
  LSTR MSG_CALI_TEMP_00                    = _UxGT("Se Recomenda Calibrar");
  LSTR MSG_CALI_TEMP_01                    = _UxGT("La Base En Caliente");
  LSTR MSG_CALI_TEMP_FRIO                  = _UxGT("Calibrar En Frio");
  LSTR MSG_CALI_TEMP_CALENTANDO_IMP        = _UxGT("Calentando Impresora");
  LSTR MSG_CALI_PRECISA                    = _UxGT("Calibración Precisa");
  LSTR MSG_CALI_PRECISA_01                 = _UxGT("Llevando Al Siguiente");
  LSTR MSG_CALI_PRECISA_02                 = _UxGT("Punto De Calibración");
  LSTR MSG_CALI_PRUEBA                     = _UxGT("Probar Calibración");

  LSTR MSG_CALI_TEMP_03                    = _UxGT("La Impresora Tiene");
  LSTR MSG_CALI_TEMP_04                    = _UxGT("Que Estar Caliente");

  LSTR MSG_CALI_TEMP_05                    = _UxGT("Hay Filamento Cargado");
  LSTR MSG_CALI_TEMP_06                    = _UxGT("En La Impresora?");
  LSTR MSG_CALI_TEMP_07                    = _UxGT("Importante");

  LSTR MSG_CALI_PRUB_SI                    = _UxGT("Si, Tine Filamento");
  LSTR MSG_CALI_PRUB_NO                    = _UxGT("No, Hay Que Cargar");

  LSTR MSG_CALI_TEMP_08                    = _UxGT("Realizando Prueba");
  LSTR MSG_CALI_TEMP_09                    = _UxGT("Iniciar Prueba");
  LSTR MSG_CALI_TEMP_09_B                  = _UxGT("Continuar Calibracion");


  LSTR MSG_CALI_TEMP_10                    = _UxGT("Quiere Mover La");
  LSTR MSG_CALI_TEMP_11                    = _UxGT("Impresora Al Punto?");

  LSTR MSG_CALI_OFFSET_01                  = _UxGT("Coloque Una Hoja");
  LSTR MSG_CALI_OFFSET_02                  = _UxGT("Debajo De La Boquilla");
  LSTR MSG_CALI_OFFSET_03                  = _UxGT("Y Baje El Eje Hasta");
  LSTR MSG_CALI_OFFSET_04                  = _UxGT("Que Apriete La Hoja");

  LSTR MSG_CALI_OFFSET_04_A                = _UxGT("Muévase Hacia Los");
  LSTR MSG_CALI_OFFSET_04_B                = _UxGT("Numeros Negativos");
  LSTR MSG_CALI_OFFSET_04_C                = _UxGT("1.000 Es Igual A 1mm");

  LSTR MSG_CALI_OFFSET_05                  = _UxGT("Cambiara La Altura");
  LSTR MSG_CALI_OFFSET_06                  = _UxGT("De Todo El Mapa");

  LSTR MSG_CALI_OTROS_00                   = _UxGT("Otras Calibraciónes");

  LSTR MSG_CALI_GENERAL_00                 = _UxGT("Calibración Asistida");
  LSTR MSG_CALI_GENERAL_01                 = _UxGT("Una Guia a Través");   //Una Guia a Través 
  LSTR MSG_CALI_GENERAL_02                 = _UxGT("De Las Calibraciónes");//De Las Calibraciónes
  LSTR MSG_CALI_EMPEZAR                    = _UxGT("Empezar");

  //prueba de offset 
  LSTR MSG_PRUEBA_OFFSET_VOLVER             = _UxGT("Salir Sin Probar Cama");
  LSTR MSG_PRUEBA_OFFSET_OFFSET             = _UxGT("Prueba De Offset");
  LSTR MSG_PRUEBA_OFFSET_PROBAR             = _UxGT("Probar Offset");
  LSTR MSG_PRUEBA_OFFSET_ENDCODER_01        = _UxGT("Gire El Boton Para");
  LSTR MSG_PRUEBA_OFFSET_ENDCODER_02        = _UxGT("Modificar El Offset");

  LSTR MSG_PRUEBA_OFFSET_INFO_01            = _UxGT("Se Imprimirá Una");
  LSTR MSG_PRUEBA_OFFSET_INFO_02            = _UxGT("Pieza De Prueba");
  LSTR MSG_PRUEBA_OFFSET_INFO_03            = _UxGT("Para Poder Modificar");
  LSTR MSG_PRUEBA_OFFSET_INFO_04            = _UxGT("La Altura Del Offset");

  LSTR MSG_PRUEBA_SI                        = _UxGT("¿Quiere Realizar Una");
  LSTR MSG_PRUEBA_NO                        = _UxGT("Prueba De Calibracion");

  //menu tmc kuttercraft
  LSTR MSG_TMC_AMPERAJE                    = _UxGT("Amperaje Del Motor");
  LSTR MSG_TMC_HIBRIDO                     = _UxGT("Conf. Cambio Hibrido");//hibrido
  LSTR MSG_TMC_HOME                        = _UxGT("Sensibilidad Origen");
  LSTR MSG_TMC_MODO_PASO                   = _UxGT("Modo De Movimiento");

  LSTR MSG_PROBAR_ORIGEN                   = _UxGT("Probar Origen");

  //modo de impresion
  LSTR MSG_MODO_IMPRESION_00               = _UxGT("Calidad      [Normal]");
  LSTR MSG_MODO_IMPRESION_01               = _UxGT("Calidad  [Silenciosa]");
  LSTR MSG_MODO_IMPRESION_02               = _UxGT("Calidad      [Rapida]");
  LSTR MSG_MODO_IMPRESION_03               = _UxGT("Calidad    [Personal]");
  LSTR MSG_MODO_IMPRESION                  = _UxGT("Calidad De Impresion");
  LSTR MSG_MODO_IMPRESION_MOD              = _UxGT("Esto Modificara");
  LSTR MSG_MODO_IMPRESION_PRIN             = _UxGT("Valores De Movimiento");
  LSTR MSG_MODO_IMPRESION_INFO             = _UxGT("Info. Calidad Actual");
  LSTR MSG_MODO_IMPRESION_CAN              = _UxGT("Cambiar Calidad");

  LSTR MSG_MODO_IMPRESION_NORMAL_00        = _UxGT("Calidad Normal");
  LSTR MSG_MODO_IMPRESION_NORMAL_01        = _UxGT("Busca El Mejor");
  LSTR MSG_MODO_IMPRESION_NORMAL_02        = _UxGT("Rendimiento Entre");
  LSTR MSG_MODO_IMPRESION_NORMAL_03        = _UxGT("Calidad, Tiempo y");
  LSTR MSG_MODO_IMPRESION_NORMAL_04        = _UxGT("Nivel De Ruido");

  LSTR MSG_MODO_IMPRESION_SILENE_00        = _UxGT("Calidad Silenciosa");
  LSTR MSG_MODO_IMPRESION_SILENE_01        = _UxGT("Busca El Mejor");
  LSTR MSG_MODO_IMPRESION_SILENE_02        = _UxGT("Rendimiento Entre");
  LSTR MSG_MODO_IMPRESION_SILENE_03        = _UxGT("Calidad y Menor Ruido");
  LSTR MSG_MODO_IMPRESION_SILENE_04        = _UxGT("Tarda Mas Tiempo");

  LSTR MSG_MODO_IMPRESION_RAPIDO_00        = _UxGT("Calidad Rapida");
  LSTR MSG_MODO_IMPRESION_RAPIDO_01        = _UxGT("Busca El Mejor");
  LSTR MSG_MODO_IMPRESION_RAPIDO_02        = _UxGT("Rendimiento Entre");
  LSTR MSG_MODO_IMPRESION_RAPIDO_03        = _UxGT("Calidad Y Tiempo");
  LSTR MSG_MODO_IMPRESION_RAPIDO_04        = _UxGT("Mayor Nivel De Ruido");

  LSTR MSG_MODO_IMPRESION_PERSON_00        = _UxGT("Calidad Personalizado");
  LSTR MSG_MODO_IMPRESION_PERSON_01        = _UxGT("Cambiar Calidad");
  LSTR MSG_MODO_IMPRESION_PERSON_02        = _UxGT("Borrara Las");
  LSTR MSG_MODO_IMPRESION_PERSON_03        = _UxGT("Configuraciones");
  LSTR MSG_MODO_IMPRESION_PERSON_04        = _UxGT("Hechas Por El Usuario");
  
  //corte de luz
  LSTR MSG_CORTE_LUZ_REANUDAR              = _UxGT("Reanudar Imprecion");
  LSTR MSG_CORTE_LUZ_MSG_00                = _UxGT("Se Detecto");
  LSTR MSG_CORTE_LUZ_MSG_01                = _UxGT("Un Corte De Luz");

  //Prueba de imprecion
  LSTR MSG_PRUEBA_IMPRESION                = _UxGT("Prueba De Impresión");
  LSTR MSG_PRUEBA_IMPRESION_00             = _UxGT("Se Imprimirá Una");
  LSTR MSG_PRUEBA_IMPRESION_01             = _UxGT("Matriz, Con La");
  LSTR MSG_PRUEBA_IMPRESION_02             = _UxGT("Altura De Los");
  LSTR MSG_PRUEBA_IMPRESION_03             = _UxGT("Puntos Medidos");

  LSTR MSG_PRUEBA_IMPRESION_04             = _UxGT("¿Esta Bien, La Altura");//¿Esta Bien, La Altura
  LSTR MSG_PRUEBA_IMPRESION_05             = _UxGT("En Todos Los Puntos?"); //En Todos Los Puntos?
  LSTR MSG_PRUEBA_IMPRESION_05_B           = _UxGT("En La impresión?"); //En La impresión?

  LSTR MSG_PRUEBA_IMPRESION_06             = _UxGT("Retire La Prueba De");
  LSTR MSG_PRUEBA_IMPRESION_07             = _UxGT("Impresion Sin Sacar");
  LSTR MSG_PRUEBA_IMPRESION_08             = _UxGT("La base Y Seleccione");
  LSTR MSG_PRUEBA_IMPRESION_09             = _UxGT("El Punto a Corregir");

  LSTR MSG_PRUEBA_IMPRESION_08_B           = _UxGT("La base De Impresión");

  LSTR MSG_GENERAL_PUNTO                   = _UxGT("Modificar Un Punto");
  LSTR MSG_GENERAL_MSG_00                  = _UxGT("Puede Modificar Un");
  LSTR MSG_GENERAL_MSG_01                  = _UxGT("Punto Específico o");
  LSTR MSG_GENERAL_MSG_02                  = _UxGT("Todos Con El Offset");

  LSTR MSG_PRUEBA_BIEN                     = _UxGT("Si, Salió Bien");
  LSTR MSG_PRUEBA_MAL                      = _UxGT("No, Quedo Mal");
  LSTR MSG_PRUEBA_VOLVER                   = _UxGT("Volver A Probar");


  LSTR MSG_CALIBRAN_SENSI_S                = _UxGT("Modificar Sens.:");
  LSTR MSG_CALIBRAN_SENSI                  = _UxGT("Calibrar Sensibilidad");
  LSTR MSG_CALIBRAN_SENSI_X                = _UxGT("Sen. EJE X:");
  LSTR MSG_CALIBRAN_SENSI_Y                = _UxGT("Sen. EJE Y:");
  LSTR MSG_CALIBRAN_SENSI_00               = _UxGT("Advertencia el Eje X");
  LSTR MSG_CALIBRAN_SENSI_01               = _UxGT("Eje Y va a Colisionar");
  LSTR MSG_CALIBRAN_SENSI_02               = _UxGT("En La Posición Mínima");

  LSTR MSG_CALIBRAN_SENSI_03               = _UxGT("Mueva a Mano");
  LSTR MSG_CALIBRAN_SENSI_04               = _UxGT("El Eje X a Su");
  LSTR MSG_CALIBRAN_SENSI_05               = _UxGT("Posición Maxima");
  LSTR MSG_CALIBRAN_SENSI_06               = _UxGT("Es Hacia La Derecha");
  LSTR MSG_CALIBRAN_SENSI_07               = _UxGT("El Eje Y a Su");
  LSTR MSG_CALIBRAN_SENSI_08               = _UxGT("Es Hacia El Frente");

  LSTR MSG_CALIBRAN_SENSI_09               = _UxGT("Permite a Los Motores");
  LSTR MSG_CALIBRAN_SENSI_10               = _UxGT("Detectar El Origen");//Seguir Sin Calibrar
  LSTR MSG_CALIBRAN_SENSI_11               = _UxGT("Seguir Sin Calibrar");

  LSTR MSG_CALIBRAN_SENSI_12               = _UxGT("El Valor Define Cunta");
  LSTR MSG_CALIBRAN_SENSI_13               = _UxGT("Fuerza Se Necesita");
  LSTR MSG_CALIBRAN_SENSI_14               = _UxGT("Para Detectar Origen");


  //textos largos
  LSTR MSG_LARGO_CARGA                     = _UxGT(" Apoye El Filamento En El Extrusor Y Espere");
  LSTR MSG_LARGO_RETIRAR                   = _UxGT(" Primero Carga Filamento Y Despues Lo Retira, Para Evitar Atasco");
  LSTR MSG_LARGO_ALINEAR_EJE_Z             = _UxGT(" Moviendo Eje XY A La Posición De Colisión");
  LSTR MSG_LARGO_CALIBRACION_AUTO          = _UxGT(" Se Esta Midiendo La Altura En Distintos Puntos De La Base, Para Crear Un Mapa De Calibración");
  LSTR MSG_LARGO_PRUEBA                    = _UxGT(" Se Esta Imprimiendo La Matriz Del Mapa De Calibración");

  //movimiento
  LSTR MSG_MOVE_AXIS                       = _UxGT("Mover Ejes");
  LSTR MSG_AUTO_HOME                       = _UxGT("Llevar Al Origen");
  LSTR MSG_AUTO_HOME_ACTION                = _UxGT("Llevando Al Origen");
  LSTR MSG_MOVE_10MM                       = _UxGT("Mover 5mm");
  LSTR MSG_AUTO_HOME_Y                     = _UxGT("Origen Y"); 
  LSTR MSG_PROBING_MESH                    = _UxGT("Midiendo Punto");
  //Calicracion
  LSTR MSG_CALIBRATE                       = _UxGT("Calibrar");
  LSTR MSG_CALIBRAR_OFFSET                 = _UxGT("Calibrar Offset");
  LSTR MSG_CALIBRAR_CAMA                   = _UxGT("Calibrar Cama");
  LSTR MSG_MODIFICAR_OFFSET                = _UxGT("Modificar Offset");
  LSTR MSG_ALINEAR_Z                       = _UxGT("Alinear Eje Z");
  LSTR MSG_POSICIONADO_Z                   = _UxGT("Posicionando Eje Z");
  LSTR MSG_MAPA_CAMA                       = _UxGT("Mapa De Cama");
  LSTR MSG_SUBIR_BAJAR                     = _UxGT("Subir Y Bajar Eje");
  LSTR MSG_MAPA_CAMA_COMPLETAR             = _UxGT("Completar Mapa");
  LSTR MSG_MAPA_CAMA_EDITAR                = _UxGT("Editar Mapa De Cama");
  LSTR MSG_MAPA_CAMA_CALIBRAR              = _UxGT("Calibrar Mapa De Cama");
  LSTR MSG_CALIBRATE_MANUAL                = _UxGT("Calibración Manual");
  LSTR MSG_AUTO_CALIBRATE                  = _UxGT("Calibración Auto.");
  LSTR MSG_AUTO_CALIBRATE_000              = _UxGT("Calibración");
  LSTR MSG_CALIBRANDO                      = _UxGT("Calibrando");
  LSTR MSG_AUTO_Z_ALIGN                    = _UxGT("Calibrando Altura Eje");
  LSTR MSG_SUBIENDO_EJE                    = _UxGT("Subiendo Eje Z");
  LSTR MSG_ZPROBE_ZOFFSET                  = _UxGT("Offset Z:");
  LSTR MSG_ALINIACION_Z_ADV_01             = _UxGT("Advertencia el Eje Z");
  LSTR MSG_ALINIACION_Z_ADV_02             = _UxGT("va  a colisionar con");
  LSTR MSG_ALINIACION_Z_ADV_03             = _UxGT("la parte superion");
  LSTR MSG_ALINIACION_Z_ADV_04             = _UxGT("los motores vibraran");
  //STORE
  LSTR MSG_STORE                           = _UxGT("Kuttercraft Store");
  LSTR MSG_STORE_WEB                       = _UxGT("kuttercraft.com/store");
  LSTR MSG_VERCION                         = _UxGT("Versión");
  LSTR MSG_INFO_STATS_MENU                 = _UxGT("Estadísticas");
  LSTR MSG_LOGROS                          = _UxGT("Logros");
  LSTR MSG_IDIOMA                          = _UxGT("Idioma           [ES");
  LSTR MSG_DELTA_AUTO_CALIBRATE_ON         = _UxGT("Auto Calibración [ON");
  LSTR MSG_DELTA_AUTO_CALIBRATE_OFF        = _UxGT("Auto Calibración[OFF");
  LSTR MSG_INFORMACION_COORD               = _UxGT("Información   [Coord");
  LSTR MSG_INFORMACION_CAPAS               = _UxGT("Información   [Capas");
  LSTR MSG_SENSOR_INDUCTIVO                = _UxGT("Sensor    [Inductivo");
  LSTR MSG_FINAL_DE_CARRERA                = _UxGT("Sensor      [Endstop");
  LSTR MSG_TIPO_EXTRU_BMG                  = _UxGT("Extrusor        [BMG");
  LSTR MSG_TIPO_EXTRU_MK8                  = _UxGT("Extrusor        [MK8");
  LSTR MSG_GUARDADO_ON                     = _UxGT("Auto Guardado    [ON");
  LSTR MSG_GUARDADO_OFF                    = _UxGT("Auto Guardado   [OFF");
  LSTR MSG_RUNOUT_SENSOR_ON                = _UxGT("Sens. Filamento  [ON");
  LSTR MSG_RUNOUT_SENSOR_OFF               = _UxGT("Sens. Filamento [OFF");
  LSTR MSG_ENCODER_ON                      = _UxGT("Encoder         [IZD");
  LSTR MSG_ENCODER_OFF                     = _UxGT("Encoder         [DER");
  LSTR MSG_VARILLA_8MM                     = _UxGT("Paso Varrilla   [8mm");
  LSTR MSG_VARILLA_4MM                     = _UxGT("Paso Varrilla   [4mm");
  LSTR MSG_VARILLA_PERSONAL                = _UxGT("Paso Varrilla   [Per");
  LSTR MSG_KUTTERMELODY_ON                 = _UxGT("Kuttermelody     [ON");
  LSTR MSG_KUTTERMELODY_OFF                = _UxGT("Kuttermelody    [OFF");
  LSTR MSG_TMC2130_CONFI                   = _UxGT("TMC Configuracion");
  LSTR MSG_CONF_MOTOR                      = _UxGT("Configuracion Motor");
  LSTR MSG_TIPO_MOTOR                      = _UxGT("Tipo De Motor");
  LSTR MSG_GIRO_MOTOR                      = _UxGT("Giro De Motor");
  //                                                       = _UxGT("Kuttermelody    [OFF");
  LSTR MSG_TIPO_MOTOR_X_F                  = _UxGT("Eje X         [FICHA");
  LSTR MSG_TIPO_MOTOR_Y_F                  = _UxGT("Eje Y         [FICHA");
  LSTR MSG_TIPO_MOTOR_Z_F                  = _UxGT("Eje Z         [FICHA");
  LSTR MSG_TIPO_MOTOR_E_F                  = _UxGT("Eje E         [FICHA");
  LSTR MSG_TIPO_MOTOR_X_D                  = _UxGT("Eje X       [DIRECTO");
  LSTR MSG_TIPO_MOTOR_Y_D                  = _UxGT("Eje Y       [DIRECTO");
  LSTR MSG_TIPO_MOTOR_Z_D                  = _UxGT("Eje Z       [DIRECTO");
  LSTR MSG_TIPO_MOTOR_E_D                  = _UxGT("Eje E       [DIRECTO");
  LSTR MSG_GIRO_MOTOR_X_D                  = _UxGT("Eje X           [DER");
  LSTR MSG_GIRO_MOTOR_Y_D                  = _UxGT("Eje Y           [DER");
  LSTR MSG_GIRO_MOTOR_Z_D                  = _UxGT("Eje Z           [DER");
  LSTR MSG_GIRO_MOTOR_E_D                  = _UxGT("Eje E           [DER");
  LSTR MSG_GIRO_MOTOR_X_Z                  = _UxGT("Eje X           [IZQ");
  LSTR MSG_GIRO_MOTOR_Y_Z                  = _UxGT("Eje Y           [IZQ");
  LSTR MSG_GIRO_MOTOR_Z_Z                  = _UxGT("Eje Z           [IZQ");
  LSTR MSG_GIRO_MOTOR_E_Z                  = _UxGT("Eje E           [IZQ");
  LSTR MSG_PID_AUTOTUNE                    = _UxGT("Ajustar PID");
  LSTR MSG_CLIBRA_HOME                     = _UxGT("Calibrar Sens. Home");
  LSTR MSG_CONFIG_FABRICA                  = _UxGT("Config. Fabrica");
  LSTR MSG_ENVIAR_GCODE                    = _UxGT("Enviar Gcode");
  LSTR MSG_SISTEMA                         = _UxGT("Sistema");
  LSTR MSG_SERIE                           = _UxGT("Serie:");
  LSTR MSG_INDUSTRIA                       = _UxGT("INDUSTRIA ARGENTINA");
  LSTR MSG_TURBO__                         = _UxGT("TURBO");
  LSTR MSG_SKR2__                          = _UxGT("SKR 2");
  LSTR MSG_FICHA__                         = _UxGT("FICHA");
  LSTR MSG_VER_VERSION                     = _UxGT("Versión:");
  LSTR MSG_VER_MODELO                      = _UxGT("Modelo:");
  //Promociones o descuentos
  LSTR MSG_FILAMENTO_USADO                 = _UxGT("Filamento Usado");
  LSTR MSG_KILOMETRO                       = _UxGT("Kilometros:");
  LSTR MSG_METRO                           = _UxGT("Metros:");
  LSTR MSG_CENTIMETRO                      = _UxGT("Centimetros:");
  LSTR MSG_TIEMPO_DE_IMPRESION             = _UxGT("Tiempo De Impresion");
  LSTR MSG_TIEMPO_YEAR                     = _UxGT("Años:");
  LSTR MSG_TIEMPO_DIAS                     = _UxGT("Días:");
  LSTR MSG_TIEMPO_HORAS                    = _UxGT("Horas:");
  LSTR MSG_TIEMPO_MINUTOS                  = _UxGT("Minutos:");
  LSTR MSG_IMPRESIONES                     = _UxGT("Impresiones");
  LSTR MSG_TOTAL                           = _UxGT("Total:");
  LSTR MSG_TERMINADAS                      = _UxGT("Terminadas:");
  LSTR MSG_INCOMPLETAS                     = _UxGT("Incompletas:");
  LSTR MSG_NO_LOGROS                       = _UxGT("No Hay Logros");
  LSTR MSG_TU_PUEDES                       = _UxGT("Sigue Intentándo");
  LSTR MSG_LOGRO_OBT                       = _UxGT("Logro Obtenido");
  LSTR MSG_HAZ_IMPRESO                     = _UxGT("Haz Impreso Tus");
  LSTR MSG_FELICITACIONES                  = _UxGT("Felicitaciones!!!");
  LSTR MSG_CUPON_DE                        = _UxGT("Cupon De");
  LSTR MSG_DESCUENTO                       = _UxGT("Descuento");
  LSTR MSG_WEB_PROMO                       = _UxGT("kuttercraft.com/promo");
  LSTR MSG_VER_CONDICIONES                 = _UxGT("Ver Condiciones En:");
  LSTR MSG_BUTTON_ACEPTAR                  = _UxGT("Aceptar");
  LSTR MSG_BUTTON_ADVERTENCIA              = _UxGT("Advertencia");
  //alerta de carteles
  //LSTR MSG_CARTEL_AUTOLEVEL_01             = _UxGT("[OFF]Use Endstop Z");
  //LSTR MSG_CARTEL_AUTOLEVEL_02             = _UxGT("Para calibrar");
  //LSTR MSG_CARTEL_AUTOLEVEL_03             = _UxGT("[ON]Cuidado Endstop Z");
  //LSTR MSG_CARTEL_AUTOLEVEL_04             = _UxGT("No debe activarse");
  LSTR MSG_CARTEL_AUTOLEVEL_01             = _UxGT("Se Dejará De Usar");
  LSTR MSG_CARTEL_AUTOLEVEL_02             = _UxGT("El Mapa De Cama");
  LSTR MSG_CARTEL_AUTOLEVEL_03             = _UxGT("El Mapa De Cama");
  LSTR MSG_CARTEL_AUTOLEVEL_04             = _UxGT("Corregira Las Alturas");
  LSTR MSG_NO_SE_USARA                     = _UxGT("No Se Usara El");
  LSTR MSG_MAPEO_CAMA                      = _UxGT("Mapeo De Cama");
  LSTR MSG_SE_USARA                        = _UxGT("Se Usara El");
  LSTR MSG_CARTEL_SENSOR_01                = _UxGT("Desactivar Sensor");
  LSTR MSG_CARTEL_SENSOR_02                = _UxGT("De Filamento");
  LSTR MSG_CARTEL_SENSOR_03                = _UxGT("Activar Sensor");
  LSTR MSG_CARTEL_SENSOR_04                = _UxGT("Pausara La Maquina");
  LSTR MSG_CARTEL_ENDSTOP_01               = _UxGT("Dejará De Medir Con");
  LSTR MSG_CARTEL_ENDSTOP_02               = _UxGT("El Sensor Inductivo");
  LSTR MSG_CARTEL_ENDSTOP_03               = _UxGT("Cuidado Endstop Z");
  LSTR MSG_CARTEL_ENDSTOP_04               = _UxGT("No debe activarse");
  LSTR MSG_CARTEL_EPROM_01                 = _UxGT("Restablecer");
  LSTR MSG_CARTEL_EPROM_02                 = _UxGT("Reiniciar Seteos Fabr");
  LSTR MSG_CARTEL_EPROM_03                 = _UxGT("Sera Permanente");
  LSTR MSG_NO_DISPONIBLE                   = _UxGT("Opcione No Disponible");
  LSTR MSG_SERA_AGREGADO                   = _UxGT("Sera Agregado En");
  LSTR MSG_FUTURA_ACTUALIZACION            = _UxGT("Futura Actualización");
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  LSTR MSG_LOGRO_PZ                        = _UxGT("Logros Por Piezas");
  LSTR MSG_LOGRO_KM                        = _UxGT("Logros Por Km");
  
  //Lista De Logros
  LSTR MSG_KM_LOGRO_01_A                   = _UxGT("Primeros Pasos");
  LSTR MSG_KM_LOGRO_01_B                   = _UxGT("Haz Impreso 100m");
  LSTR MSG_KM_LOGRO_02_A                   = _UxGT("Calentando Motores");
  LSTR MSG_KM_LOGRO_02_B                   = _UxGT("Haz Impreso 1km");
  LSTR MSG_KM_LOGRO_03_A                   = _UxGT("De Lanus al Obelisco!");
  LSTR MSG_KM_LOGRO_03_B                   = _UxGT("Haz Impreso 12Km");
  LSTR MSG_KM_LOGRO_04_A                   = _UxGT("De CABA a La Plata!");
  LSTR MSG_KM_LOGRO_04_B                   = _UxGT("Haz Impreso 53km");
  LSTR MSG_KM_LOGRO_05_A                   = _UxGT("Camino De Los 7 Lagos");
  LSTR MSG_KM_LOGRO_05_B                   = _UxGT("Haz Impreso 107km");
  LSTR MSG_KM_LOGRO_06_A                   = _UxGT("De Lanus a Chivilcoy!");
  LSTR MSG_KM_LOGRO_06_B                   = _UxGT("Haz Impreso 148km");
  LSTR MSG_KM_LOGRO_07_A                   = _UxGT("De Colonia a Rosario");
  LSTR MSG_KM_LOGRO_07_B                   = _UxGT("Haz Impreso 311km");
  LSTR MSG_KM_LOGRO_08_A                   = _UxGT("De La Habana a Miami");
  LSTR MSG_KM_LOGRO_08_B                   = _UxGT("Haz Impreso 362km");
  LSTR MSG_KM_LOGRO_09_A                   = _UxGT("De Iguazu a Ctes");
  LSTR MSG_KM_LOGRO_09_B                   = _UxGT("Haz Impreso 474km");   
  LSTR MSG_KM_LOGRO_10_A                   = _UxGT("Madrid a Barcelona!");
  LSTR MSG_KM_LOGRO_10_B                   = _UxGT("Haz Impreso 505km");
    
  LSTR MSG_KM_LOGRO_11_A                   = _UxGT("De Fortaleza a Recife");
  LSTR MSG_KM_LOGRO_11_B                   = _UxGT("Haz Impreso 621km");
  LSTR MSG_KM_LOGRO_12_A                   = _UxGT("De Cordoba a Salta");
  LSTR MSG_KM_LOGRO_12_B                   = _UxGT("Haz Impreso 745km");
  LSTR MSG_KM_LOGRO_13_A                   = _UxGT("De Londres a Munich");
  LSTR MSG_KM_LOGRO_13_B                   = _UxGT("Haz Impreso 914km");
  LSTR MSG_KM_LOGRO_14_A                   = _UxGT("Olavarria a Bariloche");
  LSTR MSG_KM_LOGRO_14_B                   = _UxGT("Haz Impreso 1058km");
  LSTR MSG_KM_LOGRO_15_A                   = _UxGT("De Roma a Paris");
  LSTR MSG_KM_LOGRO_15_B                   = _UxGT("Haz Impreso 1105km");
  LSTR MSG_KM_LOGRO_16_A                   = _UxGT("De Canarias a Malaga");
  LSTR MSG_KM_LOGRO_16_B                   = _UxGT("Haz Impreso 1427km");
  LSTR MSG_KM_LOGRO_17_A                   = _UxGT("De Atenas A Praga");
  LSTR MSG_KM_LOGRO_17_B                   = _UxGT("Haz Impreso 1531km");
  LSTR MSG_KM_LOGRO_18_A                   = _UxGT("De Berlin a Moscu");
  LSTR MSG_KM_LOGRO_18_B                   = _UxGT("Haz Impreso 1605km");
  LSTR MSG_KM_LOGRO_19_A                   = _UxGT("De Kamchatka a Tokio");
  LSTR MSG_KM_LOGRO_19_B                   = _UxGT("Haz Impreso 2472km");
    
  LSTR MSG_KM_LOGRO_20_A                   = _UxGT("Ushuaia a La Quiaca!");
  LSTR MSG_KM_LOGRO_20_B                   = _UxGT("Haz Impreso 3700km");
  LSTR MSG_KM_LOGRO_21_A                   = _UxGT("De MDP a Bogota");
  LSTR MSG_KM_LOGRO_21_B                   = _UxGT("Haz Impreso 5038km");
  LSTR MSG_KM_LOGRO_22_A                   = _UxGT("De CABA a Praga");
  LSTR MSG_KM_LOGRO_22_B                   = _UxGT("Haz Impreso 11812km");
  LSTR MSG_KM_LOGRO_23_A                   = _UxGT("La Vuelta al Mundo!!!");
  LSTR MSG_KM_LOGRO_23_B                   = _UxGT("Haz Impreso 12756km");
  
  //logros de piezas imprezas
  LSTR MSG_PZ_LOGRO_01_A                   = _UxGT("Primeras 10 Piezas!");
  LSTR MSG_PZ_LOGRO_01_B                   = _UxGT("Felicitaciones!!!");
  LSTR MSG_PZ_LOGRO_02_A                   = _UxGT("Primeras 27 Piezas!");
  LSTR MSG_PZ_LOGRO_02_B                   = _UxGT("Impresor Constante");
  LSTR MSG_PZ_LOGRO_03_A                   = _UxGT("Primeras 42 Piezas!");
  LSTR MSG_PZ_LOGRO_03_B                   = _UxGT("Impresor de la vida");
  LSTR MSG_PZ_LOGRO_04_A                   = _UxGT("Primeras 64 Piezas!");
  LSTR MSG_PZ_LOGRO_04_B                   = _UxGT("Impresor de poligonos");
  LSTR MSG_PZ_LOGRO_05_A                   = _UxGT("Primeras 101 Piezas!");
  LSTR MSG_PZ_LOGRO_05_B                   = _UxGT("Impresor de manchas");
  LSTR MSG_PZ_LOGRO_06_A                   = _UxGT("Primeras 138 Piezas!");
  LSTR MSG_PZ_LOGRO_06_B                   = _UxGT("Espectacular!");
  LSTR MSG_PZ_LOGRO_07_A                   = _UxGT("Primeras 314 Piezas!");
  LSTR MSG_PZ_LOGRO_07_B                   = _UxGT("Impresor de Tartas");
  LSTR MSG_PZ_LOGRO_08_A                   = _UxGT("Primeras 512 Piezas!");
  LSTR MSG_PZ_LOGRO_08_B                   = _UxGT("Mini Fabrica");
  LSTR MSG_PZ_LOGRO_09_A                   = _UxGT("Primeras 1024 Piezas!");
  LSTR MSG_PZ_LOGRO_09_B                   = _UxGT("Un megabytes Impresos");
  LSTR MSG_PZ_LOGRO_10_A                   = _UxGT("Primeras 1492 Piezas!");
  LSTR MSG_PZ_LOGRO_10_B                   = _UxGT("Impresor Moderno");
  LSTR MSG_PZ_LOGRO_11_A                   = _UxGT("Primeras 1984 Piezas!");
  LSTR MSG_PZ_LOGRO_11_B                   = _UxGT("Impresor del futuro");
  LSTR MSG_PZ_LOGRO_12_A                   = _UxGT("Primeras 2015 Piezas!");
  LSTR MSG_PZ_LOGRO_12_B                   = _UxGT("Se Funda Kuttercraft!");
  
  //logros____descuentos__
  LSTR MSG_EN_FILAMENTO                    = _UxGT("En Filamento");
  LSTR MSG_EN_RESPUESTOS                   = _UxGT("En Repuestos");
  LSTR MSG_EN_INSUMOS                      = _UxGT("En Insumos");
  LSTR MSG_EN_MAQUINAS                     = _UxGT("En Maquinas");
  LSTR MSG_EN_NUESTRA_TIENDA               = _UxGT("En Nuestra Tienda");
  LSTR MSG_SERVICIO_TECNICO                = _UxGT("Servicio Tecnico");
  LSTR MSG_UN_ENVIO_GRATIS                 = _UxGT("Un Envio Gratis!!!");
  LSTR MSG_EN_GRILON3                      = _UxGT("En GriloN3");
  LSTR MSG_EN_BOQUILLAS                    = _UxGT("En Boquillas");
  LSTR MSG_GUARDAR_CONFI                   = _UxGT("Guardar Confi."); 
  LSTR MSG_GUARDAR_CONFI_0                 = _UxGT("Se Ha Guardado"); 
  LSTR MSG_GUARDAR_CONFI_1                 = _UxGT("Correctamente"); //click para salir
  LSTR MSG_CLICK_PARA_SALIR                = _UxGT("Click Para Salir");
  LSTR MSG_CLICK_PARA_CONTINUAR            = _UxGT("Click Para Continuar");
  LSTR MSG_ERROR_SENSOR_IND_2              = _UxGT("Auto Calibración: ON");
  LSTR MSG_ERROR_SENSOR_IND_0              = _UxGT("Calibre Con Sensor");//Error no se puede 
  LSTR MSG_ERROR_SENSOR_IND_1              = _UxGT("Inductivo");
  LSTR MSG_ERROR_SENSOR_IND_3              = _UxGT("Auto Calibración: OFF");//Error no se puede 
  LSTR MSG_ERROR_SENSOR_IND_4              = _UxGT("Calibre Con Endstop");
  LSTR MSG_ERROR_SENSOR_IND_5              = _UxGT("Ubicacion: Eje Z Izq");
  

//--------------kuttercraft--------------//




  #if LCD_WIDTH >= 20
    LSTR MSG_INFO_PRINT_COUNT             = _UxGT("Cont. de impresión");
    LSTR MSG_INFO_COMPLETED_PRINTS        = _UxGT("Completadas");
    LSTR MSG_INFO_PRINT_TIME              = _UxGT("Tiempo total de imp.");
    LSTR MSG_INFO_PRINT_LONGEST           = _UxGT("Impresión más larga");
    LSTR MSG_INFO_PRINT_FILAMENT          = _UxGT("Total Extruido");
  #else
    LSTR MSG_INFO_PRINT_COUNT             = _UxGT("Impresiones");
    LSTR MSG_INFO_COMPLETED_PRINTS        = _UxGT("Completadas");
    LSTR MSG_INFO_PRINT_TIME              = _UxGT("Total");
    LSTR MSG_INFO_PRINT_LONGEST           = _UxGT("Más larga");
    LSTR MSG_INFO_PRINT_FILAMENT          = _UxGT("Extruido");
  #endif

  LSTR MSG_INFO_MIN_TEMP                  = _UxGT("Temp. Mínima");
  LSTR MSG_INFO_MAX_TEMP                  = _UxGT("Temp. Máxima");
  LSTR MSG_INFO_PSU                       = _UxGT("F. Aliment.");
  LSTR MSG_DRIVE_STRENGTH                 = _UxGT("Fuerza de empuje");
  LSTR MSG_DAC_PERCENT_A                  = STR_A _UxGT(" Driver %");
  LSTR MSG_DAC_PERCENT_B                  = STR_B _UxGT(" Driver %");
  LSTR MSG_DAC_PERCENT_C                  = STR_C _UxGT(" Driver %");
  LSTR MSG_DAC_PERCENT_I                  = STR_I _UxGT(" Driver %");
  LSTR MSG_DAC_PERCENT_J                  = STR_J _UxGT(" Driver %");
  LSTR MSG_DAC_PERCENT_K                  = STR_K _UxGT(" Driver %");
  LSTR MSG_DAC_PERCENT_E                  = _UxGT("E Driver %");
  LSTR MSG_ERROR_TMC                      = _UxGT("ERROR CONEX. TMC");
  LSTR MSG_DAC_EEPROM_WRITE               = _UxGT("Escribe DAC EEPROM");
  LSTR MSG_FILAMENT_CHANGE_HEADER         = _UxGT("CAMBIAR FILAMENTO");
  LSTR MSG_FILAMENT_CHANGE_HEADER_PAUSE   = _UxGT("IMPRESIÓN PAUSADA");
  LSTR MSG_FILAMENT_CHANGE_HEADER_LOAD    = _UxGT("CARGAR FILAMENTO");
  LSTR MSG_FILAMENT_CHANGE_HEADER_UNLOAD  = _UxGT("DESCARGAR FILAMENTO");
  LSTR MSG_FILAMENT_CHANGE_OPTION_HEADER  = _UxGT("OPC. REINICIO:");
  LSTR MSG_FILAMENT_CHANGE_OPTION_PURGE   = _UxGT("Purgar más");
  LSTR MSG_FILAMENT_CHANGE_OPTION_RESUME  = _UxGT("Continuar imp.");
  LSTR MSG_FILAMENT_CHANGE_NOZZLE         = _UxGT("  Boquilla: ");
  LSTR MSG_RUNOUT_SENSOR                  = _UxGT("Sens. filamento");
  LSTR MSG_RUNOUT_DISTANCE_MM             = _UxGT("Dist. filamento mm");
  LSTR MSG_KILL_HOMING_FAILED             = _UxGT("Ir a origen Fallado");
  LSTR MSG_LCD_PROBING_FAILED             = _UxGT("Sondeo Fallado");

  LSTR MSG_MMU2_CHOOSE_FILAMENT_HEADER    = _UxGT("ELIJE FILAMENTO");
  LSTR MSG_MMU2_MENU                      = _UxGT("MMU");
  LSTR MSG_KILL_MMU2_FIRMWARE             = _UxGT("¡Actu. MMU Firmware!");
  LSTR MSG_MMU2_NOT_RESPONDING            = _UxGT("MMU Necesita Cuidado");
  LSTR MSG_MMU2_RESUME                    = _UxGT("Continuar imp.");
  LSTR MSG_MMU2_RESUMING                  = _UxGT("Resumiendo...");
  LSTR MSG_MMU2_LOAD_FILAMENT             = _UxGT("Cargar Filamento");
  LSTR MSG_MMU2_LOAD_ALL                  = _UxGT("Cargar Todo");
  LSTR MSG_MMU2_LOAD_TO_NOZZLE            = _UxGT("Cargar hasta boqui.");
  LSTR MSG_MMU2_EJECT_FILAMENT            = _UxGT("Expulsar Filamento");
  LSTR MSG_MMU2_EJECT_FILAMENT_N          = _UxGT("Expulsar Filamento ~");
  LSTR MSG_MMU2_UNLOAD_FILAMENT           = _UxGT("Descargar Filamento");
  LSTR MSG_MMU2_LOADING_FILAMENT          = _UxGT("Cargando Fil. %i...");
  LSTR MSG_MMU2_EJECTING_FILAMENT         = _UxGT("Expulsando Fil. ...");
  LSTR MSG_MMU2_UNLOADING_FILAMENT        = _UxGT("Descargando Fil....");
  LSTR MSG_MMU2_ALL                       = _UxGT("Todo");
  LSTR MSG_MMU2_FILAMENT_N                = _UxGT("Filamento ~");
  LSTR MSG_MMU2_RESET                     = _UxGT("Reiniciar MMU");
  LSTR MSG_MMU2_RESETTING                 = _UxGT("Reiniciando MMU...");
  LSTR MSG_MMU2_EJECT_RECOVER             = _UxGT("Retirar, y pulsar");

  LSTR MSG_MIX                            = _UxGT("Mezcla");
  LSTR MSG_MIX_COMPONENT_N                = _UxGT("Componente =");
  LSTR MSG_MIXER                          = _UxGT("Miezclador");
  LSTR MSG_GRADIENT                       = _UxGT("Degradado");
  LSTR MSG_FULL_GRADIENT                  = _UxGT("Degradado Total");
  LSTR MSG_TOGGLE_MIX                     = _UxGT("Mezcla Conmutada");
  LSTR MSG_CYCLE_MIX                      = _UxGT("Mezcla Cíclica");
  LSTR MSG_GRADIENT_MIX                   = _UxGT("Mezcla de Degradado");
  LSTR MSG_REVERSE_GRADIENT               = _UxGT("Degradado inverso");
  LSTR MSG_ACTIVE_VTOOL                   = _UxGT("Activar Herr.V");
  LSTR MSG_START_VTOOL                    = _UxGT("Inicio Herr.V");
  LSTR MSG_END_VTOOL                      = _UxGT("   Fin Herr.V");
  LSTR MSG_GRADIENT_ALIAS                 = _UxGT("Alias Herr.V");
  LSTR MSG_RESET_VTOOLS                   = _UxGT("Reiniciar Herr.V");
  LSTR MSG_COMMIT_VTOOL                   = _UxGT("Cometer mezc. Herr.V");
  LSTR MSG_VTOOLS_RESET                   = _UxGT("Herr.V reiniciados");
  LSTR MSG_START_Z                        = _UxGT("Inicio Z:");
  LSTR MSG_END_Z                          = _UxGT("   Fin Z:");

  LSTR MSG_GAMES                          = _UxGT("Juegos");
  LSTR MSG_BRICKOUT                       = _UxGT("Brickout");
  LSTR MSG_INVADERS                       = _UxGT("Invaders");
  LSTR MSG_SNAKE                          = _UxGT("Sn4k3");
  LSTR MSG_MAZE                           = _UxGT("Maze");

  #if LCD_HEIGHT >= 4
    LSTR MSG_ADVANCED_PAUSE_WAITING       = _UxGT(MSG_2_LINE("Pulsar el botón para", "reanudar impresión"));
    LSTR MSG_PAUSE_PRINT_PARKING          = _UxGT(MSG_1_LINE("Aparcando..."));
    LSTR MSG_FILAMENT_CHANGE_INIT         = _UxGT(MSG_3_LINE("Esperando para", "iniciar el cambio", "de filamento"));
    LSTR MSG_FILAMENT_CHANGE_INSERT       = _UxGT(MSG_3_LINE("Inserte el filamento", "y pulse el botón", "para continuar..."));
    LSTR MSG_FILAMENT_CHANGE_HEAT         = _UxGT(MSG_2_LINE("Pulse el botón para", "calentar la boquilla"));
    LSTR MSG_FILAMENT_CHANGE_HEATING      = _UxGT(MSG_2_LINE("Calentando boquilla", "Espere por favor..."));
    LSTR MSG_FILAMENT_CHANGE_UNLOAD       = _UxGT(MSG_2_LINE("Espere para", "liberar el filamento"));
    LSTR MSG_FILAMENT_CHANGE_LOAD         = _UxGT(MSG_2_LINE("Espere para", "cargar el filamento"));
    LSTR MSG_FILAMENT_CHANGE_PURGE        = _UxGT(MSG_2_LINE("Espere para", "purgar el filamento"));
    LSTR MSG_FILAMENT_CHANGE_CONT_PURGE   = _UxGT(MSG_2_LINE("Pulse para finalizar", "la purga de filamen."));
    LSTR MSG_FILAMENT_CHANGE_RESUME       = _UxGT(MSG_2_LINE("Esperando impresora", "para reanudar..."));
    LSTR MSG_FILAMENT_CHANGE_K_RETIRAR    = _UxGT(MSG_2_LINE("Retirando Filamento", "Espere por favor..."));
    LSTR MSG_FILAMENT_CHANGE_K_CARGA         = _UxGT(MSG_2_LINE("Cargando Filamento",  "Espere por favor..."));
    LSTR MSG_FILAMENT_CHANGE_K_CARGA_RETIRAR = _UxGT(MSG_2_LINE("Espere para Dar", "Forma Al Filamento"));
  #else
    LSTR MSG_ADVANCED_PAUSE_WAITING       = _UxGT(MSG_1_LINE("Pulse para continuar"));
    LSTR MSG_PAUSE_PRINT_PARKING          = _UxGT(MSG_1_LINE("Aparcando..."));
    LSTR MSG_FILAMENT_CHANGE_INIT         = _UxGT(MSG_1_LINE("Por Favor espere..."));
    LSTR MSG_FILAMENT_CHANGE_INSERT       = _UxGT(MSG_1_LINE("Inserte y Pulse"));
    LSTR MSG_FILAMENT_CHANGE_HEAT         = _UxGT(MSG_1_LINE("Pulse para Calentar"));
    LSTR MSG_FILAMENT_CHANGE_HEATING      = _UxGT(MSG_1_LINE("Calentando..."));
    LSTR MSG_FILAMENT_CHANGE_UNLOAD       = _UxGT(MSG_1_LINE("Liberando..."));
    LSTR MSG_FILAMENT_CHANGE_LOAD         = _UxGT(MSG_1_LINE("Cargando..."));
    LSTR MSG_FILAMENT_CHANGE_PURGE        = _UxGT(MSG_1_LINE("Purgando..."));
    LSTR MSG_FILAMENT_CHANGE_CONT_PURGE   = _UxGT(MSG_1_LINE("Pulse para finalizar"));
    LSTR MSG_FILAMENT_CHANGE_RESUME       = _UxGT(MSG_1_LINE("Reanudando..."));
  #endif
  LSTR MSG_TMC_DRIVERS                    = _UxGT("Controladores TMC");
  LSTR MSG_TMC_CURRENT                    = _UxGT("Amperaje Controlador");
  LSTR MSG_TMC_HYBRID_THRS                = _UxGT("Límite Hibrido");
  LSTR MSG_TMC_HOMING_THRS                = _UxGT("Origen sin sensores");
  LSTR MSG_TMC_STEPPING_MODE              = _UxGT("Modo de pasos");
  LSTR MSG_TMC_STEALTH_ENABLED            = _UxGT("StealthChop Habilit.");
  LSTR MSG_SERVICE_RESET                  = _UxGT("Reiniciar");
  LSTR MSG_SERVICE_IN                     = _UxGT(" dentro:");
  LSTR MSG_BACKLASH                       = _UxGT("Backlash");
  LSTR MSG_BACKLASH_CORRECTION            = _UxGT("Corrección");
  LSTR MSG_BACKLASH_SMOOTHING             = _UxGT("Suavizado");

  LSTR MSG_LEVEL_X_AXIS                   = _UxGT("Nivel Eje X");
  #if DISABLED(MENU_KUTTERCRAFT)
    LSTR MSG_AUTO_CALIBRATE                 = _UxGT("Auto Calibrar");
  #endif
  LSTR MSG_HEATER_TIMEOUT                 = _UxGT("T. de esp. Calent.");
  LSTR MSG_REHEAT                         = _UxGT("Recalentar");
  LSTR MSG_REHEATING                      = _UxGT("Recalentando...");
}
