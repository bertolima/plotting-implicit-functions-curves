#include "QuadTree.hpp"



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

    this->plotTree(this);

}

void QuadTree::draw(QuadTree* tree, std::vector <sf::RectangleShape> &shapes){
    if (tree->getDepth() == tree->getMax_depth()){
        return;
    }
    shapes.push_back(tree->getRec());
    

    if (tree->isDivided()){
        tree->draw(tree->getNor_Esq(), shapes);
        tree->draw(tree->getNor_Dir(), shapes);
        tree->draw(tree->getSul_Dir(), shapes);
        tree->draw(tree->getSul_Esq(), shapes);
    }
    
}

void QuadTree::division(QuadTree* tree){
    float codX = tree->coodX;
    float codY = tree->coodY;

    float width = tree->width/2;
    float height = tree->height/2;

    this->norte_esq = new QuadTree(width, height, codX-width/2, codY-height/2, tree->function, tree->getMax_depth(), tree->getDepth()+1);
    this->norte_dir = new QuadTree(width, height, codX+width/2, codY-height/2, tree->function, tree->getMax_depth(), tree->getDepth()+1);
    this->sul_dir = new QuadTree(width, height, codX+width/2, codY+height/2, tree->function, tree->getMax_depth(), tree->getDepth()+1);
    this->sul_esq = new QuadTree(width, height, codX-width/2, codY+height/2, tree->function, tree->getMax_depth(), tree->getDepth()+1);

    this->divided = true;
}

int QuadTree::getMax_depth(){
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

void QuadTree::plotTree(QuadTree* tree){
    if (tree->getDepth() == tree->getMax_depth())
        return;
    if (tree->contains(tree) == true)
        tree->division(tree);

    if (tree->divided == true){
        tree->plotTree(tree->getNor_Esq());
        tree->plotTree(tree->getNor_Dir());
        tree->plotTree(tree->getSul_Dir());
        tree->plotTree(tree->getSul_Esq());
    }

}

sf::RectangleShape QuadTree::getRec(){
    return this->rec;
}

QuadTree* QuadTree::getNor_Esq(){
    return this->norte_esq;
}

QuadTree* QuadTree::getNor_Dir(){
    return this->norte_dir;
}

QuadTree* QuadTree::getSul_Dir(){
    return this->sul_dir;
}

QuadTree* QuadTree::getSul_Esq(){
    return this->sul_esq;
}

bool QuadTree::contains(QuadTree* tree){

    float esq = tree->coodX - tree->getRec().getGlobalBounds().width/2;
    float dir = tree->coodX + tree->getRec().getGlobalBounds().width/2;
    float cima = 512.f + (-1)*(tree->coodY - tree->getRec().getGlobalBounds().height/2);
    float baixo = 512.f + (-1)*(tree->coodY + tree->getRec().getGlobalBounds().height/2);


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

void QuadTree::plusDepth(QuadTree* tree){
    if (tree->max_depth < 9){
        tree->max_depth = tree->max_depth + 1;

        if (tree->depth == tree->max_depth - 1){
            if(tree->contains(tree) == true){
                tree->division(tree);
            }
            return;
        }

        if (tree->isDivided() == true){
            tree->plusDepth(tree->getNor_Esq());
            tree->plusDepth(tree->getNor_Dir());
            tree->plusDepth(tree->getSul_Dir());
            tree->plusDepth(tree->getSul_Esq());
        }  
    }
}

void QuadTree::subDepth(QuadTree* tree){
    if (tree->max_depth > 1){
        tree->max_depth = tree->max_depth - 1;

        if (tree->isDivided() == true){
            tree->subDepth(tree->getNor_Esq());
            tree->subDepth(tree->getNor_Dir());
            tree->subDepth(tree->getSul_Dir());
            tree->subDepth(tree->getSul_Esq());
        }
    }
}

int QuadTree::getMaxDepth(){
    return this->max_depth;
}

void QuadTree::prevFunction(QuadTree* tree){
    if (tree->function > 1){
        tree->norte_esq = nullptr;
        tree->norte_dir = nullptr;
        tree->sul_dir = nullptr;
        tree->sul_esq = nullptr;
        tree->function = tree->function-1;
        tree->plotTree(tree);
    }
}

void QuadTree::nextFunction(QuadTree* tree){
    if (tree->function < 11){
        tree->norte_esq = nullptr;
        tree->norte_dir = nullptr;
        tree->sul_dir = nullptr;
        tree->sul_esq = nullptr;
        tree->function = tree->function+1;
        tree->plotTree(tree);
    }
}

