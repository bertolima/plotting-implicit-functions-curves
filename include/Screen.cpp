#include "Screen.hpp"


void Screen::initVariables(){
    this->window = nullptr;
    this->plotted = false;
}

void Screen::initWindow(){
    this->videoMode.height = 512;
    this->videoMode.width = 512;

    this->window = new sf::RenderWindow(this->videoMode, "Plotting implicit functions curves", sf::Style::Titlebar | sf::Style::Close);
    this->window->setFramerateLimit(60);
}


void Screen::initQuadTree(){
    this->quadtree = new QuadTree(512.f,512.f, 256, 256, 9);
}

Screen::Screen(){
    this->initVariables();
    this->initWindow();
    this->initQuadTree();
}

Screen::~Screen(){

}

const bool Screen::running() const{
    return this->window->isOpen();
}

void Screen::pollEvent(){
    while(this->window->pollEvent(this->ev)){
        switch(this->ev.type){
            case sf::Event::Closed:
                this->window->close();
                break;
            case sf::Event::KeyPressed:
                if (this->ev.key.code == sf::Keyboard::Escape)
                    this->window->close();
                break;
        }
    }
}

void Screen::updateTree(){
    if (plotted == false){
        this->quadtree->draw(this->quadtree, this->shapes);
        this->plotted = true;
    }
}

void Screen::update(){
    this->pollEvent();
    this->updateTree();

}

void Screen::renderTree(){
    for (auto it : this->shapes){
        this->window->draw(it);
    }
    
}
void Screen::render(){

    this->window->clear();
    
    this->renderTree();

    this->window->display();
}

