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
    this->quadtree = new QuadTree(512.f,512.f, 256, 256, 0, 8);
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
                switch(ev.key.code){
                    case sf::Keyboard::Escape:
                        this->window->close();
                        break;
                    case sf::Keyboard::Up:
                        this->quadtree->plusDepth();
                        this->quadtree->draw(this->shapes);
                        break;
                    case sf::Keyboard::Down:
                        this->quadtree->subDepth();
                        this->quadtree->draw(this->shapes);
                        break;
                    case sf::Keyboard::Left:
                        this->shapes.clear();
                        this->quadtree->prevFunction();
                        this->quadtree->draw(this->shapes);
                        break;
                    case sf::Keyboard::Right:
                        this->shapes.clear();
                        this->quadtree->nextFunction();
                        this->quadtree->draw(this->shapes);
                        break;
                }
                break;
        }
    }
}

void Screen::updateTree(){
    if (plotted == false){
        this->quadtree->draw(this->shapes);
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

