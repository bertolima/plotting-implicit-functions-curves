#include "QuadTree.hpp"

float f1(float x, float y){
    return (x*x*x* + y - 4);
}

QuadTree::QuadTree(float width, float height, float coodX, float coodY, int max_depth, int depth){
    this->divided = false;
    this->width = width;
    this->height = height;
    this->coodX = coodX;
    this->coodY = coodY;
    this->max_depth = max_depth;
    this->depth = depth;

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
    if (tree->getDepth() == tree->getMax_depth())
        return;
    
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

    this->norte_esq = new QuadTree(width, height, codX-width/2, codY-height/2, tree->getMax_depth(), tree->getDepth()+1);
    this->norte_dir = new QuadTree(width, height, codX+width/2, codY-height/2, tree->getMax_depth(), tree->getDepth()+1);
    this->sul_dir = new QuadTree(width, height, codX+width/2, codY+height/2, tree->getMax_depth(), tree->getDepth()+1);
    this->sul_esq = new QuadTree(width, height, codX-width/2, codY+height/2, tree->getMax_depth(), tree->getDepth()+1);

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
    float cima = tree->coodY + tree->getRec().getGlobalBounds().height/2;
    float baixo = tree->coodY - tree->getRec().getGlobalBounds().height/2;


    float cimaEsq = f1(this->ratio*(esq - tree->getRec().getGlobalBounds().width/2), this->ratio*(cima - tree->getRec().getGlobalBounds().width/2));
    float cimaDir = f1(this->ratio*(dir - tree->getRec().getGlobalBounds().width/2),this->ratio*(cima - tree->getRec().getGlobalBounds().width/2));
    float baixoDir = f1(this->ratio*(dir - tree->getRec().getGlobalBounds().width/2), this->ratio*(baixo - tree->getRec().getGlobalBounds().height/2));
    float baixoEsq = f1(this->ratio*(esq - tree->getRec().getGlobalBounds().width/2), this->ratio*(baixo - tree->getRec().getGlobalBounds().height/2));

    std::cout << esq << std::endl;
    std::cout << dir << std::endl;
    std::cout << cima << std::endl;
    std::cout << baixo << std::endl;

    std::cout << std::endl;

    std::cout << (esq - tree->getRec().getGlobalBounds().width/2) << " " <<  (cima - tree->getRec().getGlobalBounds().width/2) << std::endl;
    std::cout << (dir - tree->getRec().getGlobalBounds().width/2) << " " <<  (cima - tree->getRec().getGlobalBounds().width/2) << std::endl;
    std::cout << (dir - tree->getRec().getGlobalBounds().width/2) << " " <<  (baixo - tree->getRec().getGlobalBounds().height/2) << std::endl;
    std::cout << (esq - tree->getRec().getGlobalBounds().width/2) << " " <<  (baixo - tree->getRec().getGlobalBounds().height/2) << std::endl;

    std::cout << std::endl;

    std::cout << cimaEsq << std::endl;
    std::cout << cimaDir << std::endl;
    std::cout << baixoDir << std::endl;
    std::cout << baixoEsq << std::endl;

    std::cout << std::endl;

    

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


