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

//
// Job Recovery Menu
//

#include "../../inc/MarlinConfigPre.h"

#if BOTH(HAS_LCD_MENU, POWER_LOSS_RECOVERY)

#include "menu_item.h"
#include "../../gcode/queue.h"
#include "../../sd/cardreader.h"
#include "../../feature/powerloss.h"

#if ENABLED(MENU_KUTTERCRAFT)
  #include "../mapa_bit/bitmap_kuttercraft.h"

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
#endif

static void lcd_power_loss_recovery_resume() {
  ui.return_to_status();
  queue.inject(F("M1000"));
}

void lcd_power_loss_recovery_cancel() {
  recovery.cancel();
  ui.return_to_status();
}

// TODO: Display long filename with Cancel/Resume buttons
//       Requires supporting methods in PLR class.
void menu_job_recovery() {
  #if ENABLED(MENU_KUTTERCRAFT)
    MarlinUI::defer_return_to_status = true;

    START_MENU();
    NEXT_ITEM_(2);
    END_MENU();

    crear_marco_superior(Language_es::MSG_BUTTON_ADVERTENCIA);
    init_boto(23, 5, 2, 29);

    crear_boton(boton_detener_a,     boton_detener_b,     Language_es::MSG_BUTTON_CANCEL,       lcd_power_loss_recovery_cancel);
    crear_boton(boton_reanudar_a,    boton_reanudar_b,    Language_es::MSG_CORTE_LUZ_REANUDAR,  lcd_power_loss_recovery_resume);
    
    crear_texto_centrado(Language_es::MSG_CORTE_LUZ_MSG_00, 9);
    crear_texto_centrado(Language_es::MSG_CORTE_LUZ_MSG_01, 18);

  #else
    ui.defer_status_screen();
    START_MENU();
    STATIC_ITEM(MSG_OUTAGE_RECOVERY);
    ACTION_ITEM(MSG_RESUME_PRINT, lcd_power_loss_recovery_resume);
    ACTION_ITEM(MSG_STOP_PRINT, lcd_power_loss_recovery_cancel);
    END_MENU();}
  #endif
}

#endif // HAS_LCD_MENU && POWER_LOSS_RECOVERY
