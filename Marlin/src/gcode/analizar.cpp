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

/**
 *
 * Firmware Modificado Por Kuttercraft
 * Copyright (c) 2021 Kuttercraft [https://www.kuttercraft.com]
 *
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

#include "analizar.h"
#include "parser.h"
#include "../MarlinCore.h"
#include "queue.h"
#include "../lcd/menu/menu_ajustes_de_filamento.h"


/*
//Cura
;LAYER_COUNT:100
;LAYER:0

//Simplifi
; layer 5, Z = 1.040

//slic3r
;LAYER_CHANGE

*/
bool es_slicer = false;
long slicer_numero_de_capa = 0;

void _removeSpacesInPlace(char* str) {
     size_t str_len = strlen(str); // para tener strlen se debe incluir <string.h>
     char result [str_len];
     size_t p = 0; size_t i = 0;
     for (i = 0; i < str_len; ++i)
      {
        if (str[i] != ' ')
        { // result necesita su propio posicionador o iremos dejando agujeros
          result[p] = str[i];
          // Sólo avanzamos la posición p si se realiza la inserción
          p++;
        }
      }
      // funciones como printf buscan el caracter 0
      // aunque dejamos str con el mismo tamaño en memoria, ponemos la
      // marca de fin de la cadena en donde corresponde
      if (p < str_len) str[p] = '\0';
      // Reescribimos str con el contenido de result
      for (i = 0; i < p; ++i)
      {
         str[i] = result[i];
      }
}

//se encarga de eliminar la parte inicial de un str
//hasta un punto marcado
void reductor_str(char* busqueda){
    int total_de_letras = 0, letra_actual = 0;
    MarlinUI::contenedor_str[0] = '\0';

    total_de_letras = strcspn(parser.command_ptr, busqueda) + 1;//total de letras hasta un caracter
        
    //recorre el str para obtener el numero
    for (int i = 0; parser.command_ptr[i] != '\0'; ++i){
        if(total_de_letras <= i){
            if(letra_actual <= 34){ //limite de contenedor_str
                MarlinUI::contenedor_str[letra_actual] = parser.command_ptr[i];
                letra_actual++;
            }
        }
    }
    MarlinUI::contenedor_str[letra_actual] = '\0'; //establese el final de la cadena
}

//se encarga de obtener solo los numero de la capa
void solo_numeros_str(){
    strcpy(parser.command_ptr, MarlinUI::contenedor_str);

    int total_de_letras = 0, letra_actual = 0;
    MarlinUI::contenedor_str[0] = '\0';
        
    //recorre el str para obtener el numero
    for (int i = 0; isdigit(parser.command_ptr[i]); ++i){
        if(total_de_letras <= i){
            if(letra_actual <= 34){ //limite de contenedor_str
                MarlinUI::contenedor_str[letra_actual] = parser.command_ptr[i];
                letra_actual++;
            }
        }
    }
    MarlinUI::contenedor_str[letra_actual] = '\0'; //establese el final de la cadena
}
/*
static long capa_actual;
static long total_de_capas;
*/
//se encarga de buscar informacion util entre los comentarios

bool se_cambio_la_capa = false;

void analizar_comentario(){
    long numero_aux;
    
    //////
    //Cura
    if (strstr(parser.command_ptr,"LAYER_COUNT:") != NULL){
        reductor_str((char*)":");
        _removeSpacesInPlace(MarlinUI::contenedor_str);

        if(strlen(MarlinUI::contenedor_str) <= 12){
            numero_aux = strtol(MarlinUI::contenedor_str,NULL,10); //comvierte a long
            numero_aux = numero_aux - 1;

            strcpy(MarlinUI::contenedor_str, ltostr7(numero_aux));
            _removeSpacesInPlace(MarlinUI::contenedor_str);
            strcpy(MarlinUI::total_de_capas, MarlinUI::contenedor_str);
        }else{
            strcpy(MarlinUI::total_de_capas, "Maximo De Capas");
        }

    }else if(strstr(parser.command_ptr,"LAYER:") != NULL){
        reductor_str((char*)":");
        _removeSpacesInPlace(MarlinUI::contenedor_str);

        if(strlen(MarlinUI::contenedor_str) <= 12){

            numero_aux = strtol(MarlinUI::contenedor_str,NULL,10); //comvierte a long
            numero_aux = numero_aux + 1;

            strcpy(MarlinUI::contenedor_str, ltostr7(numero_aux));
            _removeSpacesInPlace(MarlinUI::contenedor_str);
            strcpy(MarlinUI::capa_actual, MarlinUI::contenedor_str);
            se_cambio_la_capa = true;
        }else{
            strcpy(MarlinUI::capa_actual, "Maximo De Capas");
        }

        
    ////////////
    //Simplify3d
    }else if(strstr(parser.command_ptr,"; layer") != NULL){

        reductor_str((char*)"r");
        _removeSpacesInPlace(MarlinUI::contenedor_str);
        solo_numeros_str();

        strcpy(MarlinUI::capa_actual, MarlinUI::contenedor_str);
        se_cambio_la_capa = true;

    //////////////
    //slicer prusa
    }else if(strstr(parser.command_ptr,"PrusaSlicer") != NULL){
        es_slicer = true;

    }else if(strstr(parser.command_ptr,";LAYER_CHANGE") != NULL){
        if(es_slicer){
            slicer_numero_de_capa++;

            strcpy(MarlinUI::contenedor_str, i16tostr3rj(slicer_numero_de_capa));
            _removeSpacesInPlace(MarlinUI::contenedor_str);

            strcpy(MarlinUI::capa_actual, MarlinUI::contenedor_str);
            se_cambio_la_capa = true;
        }
    }
}

//hay que realizar un cambio de filamento programado?
void scheduled_change(){
    int i; 
    //es true cuando aparce un comando de capa (simplify, cura, prusa)
    if(se_cambio_la_capa){ 
        //antes de analizar la lista comprueba que no este vacia
        if(MarlinUI::list_layer[1][0] != '\0'){
            for (i = 1; i < 20; i++){
                if(strcmp(MarlinUI::capa_actual, MarlinUI::list_layer[i]) == 0){
                    //SERIAL_ECHOLN(MarlinUI::list_layer[i]);
                    se_cambio_la_capa = false;
                    MarlinUI::layer_pointer_memory = i;

                    exit_layer_list = false; //evita la entradaX al menu de lista de capa
                    delte_layer_list();//elimina el cambio de la lista
                    
                    //se tiene que realizar un cambio
                    MarlinUI::m600_waiting_filament_change = true; //la ejecucion esta en la pagina G0_G1
                    //queue.inject_P(PSTR("M600"));
                }
            }
        }
    }
}