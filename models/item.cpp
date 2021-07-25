/* Appunti e commenti momentanei

    Un oggetto del gioco sarà la classe padre di sottoclassi quali:
        . Arma  (possibile modifica all'attuale sparo del player, ovvero si può
   aggiungere un attributo arma al personaggio) . Mina (volendo una mina può
   essere vista anche come un oggetto enemy) . Oggetti raccoglibili: . Bonus /
   Malus: Possibili implementazioni:
                - Modificatori di punteggio
                - Modificatori temporanei / permanenti alle armi
                - Modificatori temporanei / permanenti del personaggio
                - Modificatori temporanei / permanenti dei nemici

    Prendo le coordinate
    Genero il bonus (funzione da scrivere)
    Lo rendo interagibile
    Aggiungere gli effetti causati dalla sua raccolta

*/

#include "item.hpp"

Item::Item() : Coordinate::Coordinate(point) {}
Item::Item(char in_name[], int in_mapTime, int in_duration)
    : Coordinate::Coordinate(point) {
  strcpy(this->name, in_name);
  // this -> skin     = '?';
  this->mapTime = in_mapTime;
  this->duration = in_duration;
}

void Item::decrementMapTime() { this->mapTime -= 1; }
void Item::decrementDuration() { this->duration -= 1; }
void Item::incrementDuration() { this->duration += 1; }