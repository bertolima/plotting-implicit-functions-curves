#include "QuadTree.hpp"


//constructor and destructor
QuadTree::QuadTree(float width, float height, float coodX, float coodY, int function, int max_depth, int depth){
    this->divided = false;
    this->width = width;
    this->height = height;
    this->coodX = coodX;
    this->coodY = coodY;
    this->max_depth = max_depth;
    this->depth = depth;
    this->function = function;

    this->rec.setOutlineThickness(-1);
    this->rec.setFillColor(sf::Color::Black);
    this->rec.setOutlineColor(sf::Color::White);
    this->rec.setSize(sf::Vector2f(width, height));
    this->rec.setOrigin(this->rec.getGlobalBounds().width/2,this->rec.getGlobalBounds().width/2);
    this->rec.setPosition(coodX, coodY);
    this->ratio = 0.015625;

    this->nw = nullptr;
    this->ne = nullptr;
    this->sw = nullptr;
    this->se = nullptr;

    this->plotTree();


}

QuadTree::~QuadTree(){
    delete this->nw;
    delete this->ne;
    delete this->sw;
    delete this->se;
}

//draw the tree on screen
void QuadTree::draw(std::vector <sf::RectangleShape> &shapes){
    if (this->getDepth() == this->getMaxDepth()){
        return;
    }
    shapes.push_back(this->getRec());

    if (this->isDivided()){
        this->nw->draw(shapes);
        this->ne->draw(shapes);
        this->se->draw(shapes);
        this->sw->draw(shapes);
    }
}

//acesses
int QuadTree::getMaxDepth(){
    return this->max_depth;
}
int QuadTree::getDepth(){
    return this->depth;
}
float QuadTree::getWidth(){
    return this->width;
}
float QuadTree::getHeight(){
    return this->height;
}
bool QuadTree::isDivided(){
    return this->divided;
}
sf::RectangleShape QuadTree::getRec(){
    return this->rec;
}

//tree's methods
bool QuadTree::contains(){

    float esq = this->coodX - this->getRec().getGlobalBounds().width/2;
    float dir = this->coodX + this->getRec().getGlobalBounds().width/2;
    float cima = 512.f + (-1)*(this->coodY - this->getRec().getGlobalBounds().height/2);
    float baixo = 512.f + (-1)*(this->coodY + this->getRec().getGlobalBounds().height/2);


    float cimaEsq = functions.getFunction(this->function)(this->ratio*(esq - 256.f), this->ratio*(cima - 256.f));
    float cimaDir = functions.getFunction(this->function)(this->ratio*(dir - 256.f),this->ratio*(cima - 256.f));
    float baixoDir = functions.getFunction(this->function)(this->ratio*(dir - 256.f), this->ratio*(baixo - 256.f));
    float baixoEsq = functions.getFunction(this->function)(this->ratio*(esq - 256.f), this->ratio*(baixo - 256.f));

    if (cimaEsq == baixoDir && cimaDir == baixoEsq)
        return true;
    if (cimaEsq == cimaDir && baixoDir == baixoEsq)
        return true;
    if (cimaEsq > 0 && cimaDir > 0 && baixoDir > 0 && baixoEsq > 0)
        return false;
    if (cimaEsq < 0 && cimaDir < 0 && baixoDir < 0 && baixoEsq < 0)
        return false;
    return true;
}
void QuadTree::division(){
    float codX = this->coodX;
    float codY = this->coodY;

    float width = this->width/2;
    float height = this->height/2;

    this->nw = new QuadTree(width, height, codX-width/2, codY-height/2, this->function, this->getMaxDepth(), this->getDepth()+1);
    this->ne = new QuadTree(width, height, codX+width/2, codY-height/2, this->function, this->getMaxDepth(), this->getDepth()+1);
    this->se = new QuadTree(width, height, codX+width/2, codY+height/2, this->function, this->getMaxDepth(), this->getDepth()+1);
    this->sw = new QuadTree(width, height, codX-width/2, codY+height/2, this->function, this->getMaxDepth(), this->getDepth()+1);

    this->divided = true;
}
void QuadTree::plotTree(){
    if (this->getDepth() == this->getMaxDepth())
        return;
    if (this->contains())
        this->division();

    if (this->isDivided()){
        this->nw->plotTree();
        this->ne->plotTree();
        this->se->plotTree();
        this->sw->plotTree();
    }
}



void QuadTree::plusDepth(){
    if (this->max_depth < 9){
        this->max_depth = this->max_depth + 1;

        if (this->depth == this->max_depth - 1){
            if(this->contains()){
                this->division();
            }
            return;
        }

        if (this->isDivided()){
            this->nw->plusDepth();
            this->ne->plusDepth();
            this->se->plusDepth();
            this->sw->plusDepth();
        }  
    }
}
void QuadTree::subDepth(){
    if (this->max_depth > 1){
        this->max_depth = this->max_depth - 1;

        if (this->isDivided()){
            this->nw->subDepth();
            this->ne->subDepth();
            this->se->subDepth();
            this->sw->subDepth();
        }
    }
}


// void QuadTree::prevFunction(QuadTree* tree){


//     if (tree->function > 1){
//         tree->function = tree->function-1;
//         tree->clearTree(tree);
//         tree->plotTree(tree);
//     }

//     else if (tree->function == 0){
//         tree->function = 11;
//         tree->clearTree(tree);
//         tree->plotTree(tree);

//     }
// }

// void QuadTree::nextFunction(QuadTree* tree){
//     if (tree->function == 11){
//         tree->function = 0;
//         tree->clearTree(tree);
//         tree->plotTree(tree);
//     }
        
//     else if (tree->function < 11){
//         tree->function = tree->function+1;
//         tree->clearTree(tree);
//         tree->plotTree(tree);

//     }
// }

void QuadTree::clearChildren(){
    delete nw;
    nw = nullptr;
    delete ne;
    ne = nullptr;
    delete sw;
    sw = nullptr;
    delete se;
    se = nullptr;
}