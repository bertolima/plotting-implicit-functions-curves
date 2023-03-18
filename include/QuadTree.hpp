#include <SFML/Graphics.hpp>
#include "functions.hpp"
#include <iostream>


class QuadTree{
    private:
        //tree variables
        bool divided;
        float width;
        float height;
        float coodX;
        float coodY;
        int max_depth;
        int depth;
        int function;

        //children
        QuadTree* nw;
        QuadTree* ne;
        QuadTree* se;
        QuadTree* sw;

        //control variables
        sf::RectangleShape rec;
        float ratio;
        Functions functions;

        //private functions
        void division();


    public:
    
        //const and desc
        QuadTree(float, float, float, float, int, int, int depth=0);
        ~QuadTree();

        //draw tree
        void draw(std::vector <sf::RectangleShape> &shapes);

        //access
        int getDepth();
        int getMaxDepth();
        float getWidth();
        float getHeight();
        bool isDivided();
        QuadTree getNor_Esq();
        QuadTree getNor_Dir();
        QuadTree getSul_Dir();
        QuadTree getSul_Esq();
        sf::RectangleShape getRec();

        //create all tree structure
        void plotTree();

        //public functions
        void plusDepth();
        void subDepth();
        bool contains();
        void prevFunction();
        void nextFunction();
        void clearChildren();

};


