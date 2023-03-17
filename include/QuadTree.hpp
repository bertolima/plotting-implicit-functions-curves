#include <SFML/Graphics.hpp>
#include "functions.hpp"


class QuadTree{
    private:
        bool divided;
        float width;
        float height;

        float coodX;
        float coodY;


        sf::RectangleShape rec;

        QuadTree* norte_esq;
        QuadTree* norte_dir;
        QuadTree* sul_esq;
        QuadTree* sul_dir;

        int max_depth;
        int depth;
        int function;
        float ratio;

        Functions functions;

        
        void division(QuadTree*);


    public:
        QuadTree(float, float, float, float, int, int, int depth=0);
        ~QuadTree();
        void draw(QuadTree*, std::vector <sf::RectangleShape> &shapes);
        int getMax_depth();
        int getDepth();
        float getWidth();
        float getHeight();
        bool isDivided();
        void plotTree(QuadTree*);
        sf::RectangleShape getRec();
        QuadTree* getNor_Esq();
        QuadTree* getNor_Dir();
        QuadTree* getSul_Dir();
        QuadTree* getSul_Esq();
        int getMaxDepth();
        void plusDepth(QuadTree*);
        void subDepth(QuadTree*);
        bool contains(QuadTree*);
        void prevFunction(QuadTree*);
        void nextFunction(QuadTree*);



};


