/*****************************************************************************/
/* Betriebssysteme                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                       S T R I N G B U F F E R                             */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Die Klasse Stringbuffer stellt einen Puffer fuer die Sammlung von Zeichen */
/* zur Darstellung auf dem Bildschirm oder anderen Ausgabegeraeten bereit.   */
/* Die Ausgabe der Zeichen erfolgt, sobald der Puffer voll ist oder wenn     */
/* explizit die Methode flush() aufgerufen wird.                             */
/* Da Stringbuffer geraeteunabhaengig sein soll, ist flush() eine virtuelle  */
/* Methode, die von den abgeleiteten Klassen definiert werden muss.          */
/*****************************************************************************/

#include "object/strbuf.h"

/* Hier muesst ihr selbst Code vervollstaendigen */ 

Stringbuffer::Stringbuffer(){
    buffer_size = 100;
    this->cleanBuffer();
}

void Stringbuffer::put(char c){

    if(current_index < buffer_size){
        buffer[current_index] = c;
        current_index++;
    }
    else
    {
        //testwert
        current_index = 99;
    }
    

}

void Stringbuffer::cleanBuffer(){
    int current_index = 0;

    for (int i = 0; i < buffer_size; i++){
        buffer[i] = '0';
    }
}
