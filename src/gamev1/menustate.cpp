#include "menustate.h"
#include <string>
#include <iostream>


const std::string MenuState::s_menuID="MENU";

void MenuState::update(){}
void MenuState::render(){}
bool MenuState::onEnter(){
    std::cout <<"entering MenuState"<<std::endl;
    return true;
}
bool MenuState::onExit(){
    std::cout << "Exiting MenuState"<<std::endl;
    return true;
}

