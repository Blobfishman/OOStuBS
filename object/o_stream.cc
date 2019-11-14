/*****************************************************************************/
/* Betriebssysteme                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                            O _ S T R E A M                                */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Die Klasse O_Stream enthaelt die Definition des << Operators fuer die     */
/* wichtigsten der vordefinierten Datentypen und realisiert somit die        */
/* bekannte Ausgabefunktion der C++ IO_Stream Bibliothek. Zur Zeit wird die  */
/* Darstellung von Zeichen, Zeichenketten und ganzen Zahlen unterstuetzt.    */
/* Ein weiterer << Operator erlaubt die Verwendung von Manipulatoren.        */
/*                                                                           */
/* Neben der Klasse O_Stream sind hier auch die Manipulatoren hex, dec, oct  */
/* und bin fuer die Wahl der Basis bei der Zahlendarstellung, sowie endl     */
/* fuer den Zeilenumbruch definiert.                                         */
/*****************************************************************************/

#include "object/o_stream.h"

/* Hier muesst ihr selbst Code vervollstaendigen */ 
O_Stream::O_Stream(){
    
}

void O_Stream::flush(){

}

O_Stream& O_Stream::operator<<(unsigned char c){
    if (this->getCurrentIndex() < this->getBufferSize())
    {
        this->put(c);
    }
    else
    {
        this->flush();
        this->cleanBuffer();

        this->put(c);
    }
}

O_Stream& O_Stream::operator<<(char c){
    if (this->getCurrentIndex() < this->getBufferSize())
    {
        this->put(c);
    }
    else
    {
        this->flush();
        this->cleanBuffer();

        this->put(c);
    }
}

O_Stream& O_Stream::operator<<(unsigned short number){

    short p = 1;
    short char_number=0;
    while (p<=number)
    {
        p*=10;
        char_number++;
    }
    p = p/10;
    
    if ((this->getCurrentIndex()+ char_number) < this->getBufferSize())
    {
        while (p > 1)
        {
            this->put(((char) (number/p)));
            number %= p; 
            p /=10; 
        }
        
    }
    else
    {
        this->flush();
        this->cleanBuffer();

        while (p > 1)
        {
            this->put(((char) (number/p)));
            number %= p; 
            p /=10; 
        }

    }

    return *this;
}

O_Stream& O_Stream::operator<<(short number){

    short p = 1;
    short char_number = 0;
    bool flag = false;

    if(number < 0){
        flag = true;
        number *= (-1);
        char_number++;
    }

    while (p<=number)
    {
        p*=10;
        char_number++;
    }
    p = p/10;

    if ((this->getCurrentIndex()+ char_number) < this->getBufferSize())
    {
        if(flag){
            this->put('-');
        }
        while (p > 1)
        {
            this->put(((char) (number/p)));
            number %= p; 
            p /=10; 
        }
    }
    else
    {
        this->flush();
        this->cleanBuffer();

        if(flag){
            this->put('-');
        }
        while (p > 1)
        {
            this->put(((char) (number/p)));
            number %= p; 
            p /=10; 
        }
    }
}

O_Stream& O_Stream::operator<<(unsigned int number){
    
    if (this->getCurrentIndex() < this->getBufferSize())
    {
        
    }
    else
    {
        flush();
    }
}

O_Stream& O_Stream::operator<<(int number){
    if (this->getCurrentIndex() < this->getBufferSize())
    {
        
    }
    else
    {
        flush();
    }
}

O_Stream& O_Stream::operator<<(unsigned long number){
    if (this->getCurrentIndex() < this->getBufferSize())
    {
        
    }
    else
    {
        flush();
    }
}
O_Stream& O_Stream::operator<<(long number){
    if (this->getCurrentIndex() < this->getBufferSize())
    {
        
    }
    else
    {
        flush();
    }
}
