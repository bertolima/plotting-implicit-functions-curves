#include "QuadTree.hpp"
#include <vector>
#include <iostream>

class Screen{
    private:
        //window
        sf::RenderWindow* window;
        sf::VideoMode videoMode;
        sf::Event ev;

        QuadTree *quadtree;
        std::vector <sf::RectangleShape> shapes;

        bool plotted;

        //private functions
        void initVariables();
        void initWindow();
        void initQuadTree();
        void initFunctions();
        
    public:
        //cons and desc
        Screen();
        ~Screen();

        //access
        const bool running() const;

        //functions

        void pollEvent();

        void updateTree();
        void update();

        void renderTree();
        void render();

};