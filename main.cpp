#include "include/Screen.hpp"

int main(){

    Screen screen;

    while(screen.running()){
        screen.update();
        screen.render();
    }

    return 0;
}