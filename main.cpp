/* TO DO

1. La weather: transfer de la sf::Sprite la sf::Image pentru functia getPixel() [turbulente??, prabusiri...]
                                                                       ^ probabil sa sara in aer performanta

2. Lista pusa intr-un colt al ecranului cu toate entitatile de pe harta si posibilitatea sa apesi pe un nume
        din acea lista si sa selecteze entitatea

3. Event-uri random pentru emergency-uri pentru avioane si elicoptere
	-> Avioanele pot avea emergency-uri de tipul alarma cu bomba, engine fire, sanatate calator
	-> Emergency-uri elicoptere: Engine fire (si sa isi schimbe de multe ori directia si sa
	scada rapid in altitudine)
si in anumite cazuri entitatile sa aibe un timp pana la prabusire => pot fi preluate de orice aeroport din apropiere
 etc...

4. De adaugat un mini-chat care sa afiseze mereu ultimele 4-5 instructiuni date tuturor entitatilor (e.g.: RYR512 turn
 to heading {newHeading}; ROT125 set speed to 180kts) si mesajele transmise de entitati in cazul emergency-urilor
 (e.g.: WZZ1MK declares engine fire; si sa apara textul cu rosu)

*/

#include "./header/Menu.h"
#include "./header/Game.h"

int main() {
    srand(time(nullptr));

    try {
        ResourcesManager::Instance().load();
    } catch(ErrorResourcesManager &err) {
        std::cout<<err.what();
        return 0;
    }

    Menu menu;
    menu.run();

    if(ResourcesManager::Instance().getSelectedRegion().empty()) { // if game has been closed in menu
        return 0;
    }

    Game game;
    game.run();

    return 0;
}
