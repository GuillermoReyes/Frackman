#include "StudentWorld.h"
#include <string>
#include <cstdlib>
using namespace std;

GameWorld* createStudentWorld(string assetDir)
{
    return new StudentWorld(assetDir);
}

void StudentWorld::manageDirt(int X, int Y) {
    //dirt[X][Y]->setVisible(false);
    // x is thte row
    // y is the column
    if(Y==59){
        for(int i = 0; i <= 3; i++)
            dirt[X+i][Y]->setDead();
        
        
    }
    if(Y==58){
        for(int i = 0; i <= 3; i++)
            for(int j = 0 ; j <=1 ; j++)
                dirt[X+i][Y+j]->setDead();
        
    }
    if(Y==57){
        for(int i = 0; i <= 3; i++)
            for(int j = 0 ; j <=2 ; j++)
                dirt[X+i][Y+j]->setDead();
        
    }
    if((X<61 && X>=0 ) && (Y< 57 && Y>=0)){
        for(int i = 0; i <= 3; i++)
            for(int j = 0 ; j <=3 ; j++)
                dirt[X+i][Y+j]->setDead();
        
    }
    return;
}
void StudentWorld::cleanDead(){
    // need to erify if this works , or not
    for(int i = 0; i < m_actor.size(); i++)  {
        if(m_actor.at(i)->isDead())
            m_actor.erase(m_actor.begin()+i-1);
        i--;
    }
}
void StudentWorld::setBarrels(int amount)

{
    m_barrels = amount;
}
void StudentWorld::decBarrels() {
    m_barrels--;
}
int  StudentWorld::getBarrels() const {
    return m_barrels;
}
bool StudentWorld::tickCount(const int& interval){
    bool reset = false;
    if(t_count == interval){
        reset = true;
    }
    
    t_count++;
    return reset;
}
int StudentWorld::getPlayerX(){
    return player->getX();
}
int StudentWorld::getPlayerY(){
    return player->getY();
}
bool StudentWorld::getObject(GameObject* &mp, int X, int Y, int radius){
    
    for(int i = 0; i < m_actor.size(); i++){
        int rx = abs(m_actor.at(i)->getX() - X);
        int ry = abs(m_actor.at(i)->getY()-Y);
        if(rx <=radius && ry <= radius){
            mp = m_actor.at(i);
            return true;
        }
    }
    return false;
}
bool StudentWorld::dirtThere(int X, int Y){
    if(dirt[X][Y]->isDead()){
        return false;
    }
    return true;
}
Frackman* StudentWorld::accessPlayer(){
    return player;
}
void StudentWorld::storeItem(GameObject* item){
    m_actor.push_back(item);
}
bool StudentWorld::nearFrackman(int X, int Y, int radius){
    int rx = abs(X - player->getX());
    int ry = abs(Y - player->getY());
    if(rx <=radius && ry <=radius){
        return true;
    }
    return false;
}
void StudentWorld::computePath(int currx, int curry, int& nextX, int& nextY){
   // for(int i = currx; i <= 60; i++)
    //    for(int j = curry ; j <=60; j++)
         
}
bool StudentWorld::isViable(int x, int y){
    if(x>=61){
        return false;
    }
    
    for(int j = 0; j<=3; j++){
        for(int i = 0; i<=3; i++){
            if(dirtThere(x+i,y+j)){
                return false;
            }
        }
    }
    
    if( x <=0 || x>61 || y<=0 || y>=61){
        return false;
    }
    
    
    return true;
}
bool StudentWorld::boulderThere(int X , int Y ) {
    for(int i = 0; i < m_actor.size(); i++){
        if(m_actor.at(i)->getID() == IID_BOULDER ){
            int rx = abs(X - m_actor.at(i)->getX());
            int ry = abs(Y - m_actor.at(i)->getY());
            if(ry<=4 || rx <= 4){
                return true;
            }
        }
    }
    return false;
}
bool StudentWorld::isInShaft(int X, int Y){
    for(int i = 30; i < 34; i++)
        for(int j = 3; j <60; j++)
            if(X == i && Y== j ){
                return true;
            }
    return false;
}
bool StudentWorld::pathExists( int nRows, int nCols, int sr, int sc, int er, int ec){
    if (sr < 0  ||  sr > nRows  ||  sc < 0  || sc > nCols  ||
        er < 0  ||  er > nRows  ||  ec < 0  || ec > nCols  ||
        a[sr][sc] != OPEN  ||  a[er][ec] != OPEN)
        return false;
    
    
    explore( sr, sc);
    
    while ( ! toDo.empty() )
    {
        Coord curr = toDo.front();
        toDo.pop();
        
        const int cr = curr.r();
        const int cc = curr.c();
        
        if (cr == er  &&  cc == ec)
            return true;
        
        explore(  cr-1, cc);  // north
        explore(  cr, cc+1);  // east
        explore(  cr+1, cc);  // south
        explore(  cr, cc-1);  // west
    }
    return false;

}
void StudentWorld::updateMaze(){
    for(int i = 0; i <=60; i++){
        for(int j = 0; i <=60; j++){
            if(isViable(i,j) && a[i][j]!='o'){
                a[i][j]= '.';
            }
            if(!isViable(i,j)){
                 a[i][j]='X';
            }
        }
    }
}
void StudentWorld::explore( int r, int c){
    
    if (a[r][c] == OPEN)
    {
        toDo.push(Coord(r,c));
        a[r][c] = SEEN;  // anything non-OPEN will do
    }

}
StudentWorld::~StudentWorld(){
    for(int i = 0; i < m_actor.size(); i++){
        delete m_actor.at(i);
    }
    
    for(int i = 0; i < 64; i++)
        for(int j = 0; j < 60 ; j++)
            delete dirt[i][j];
    
    
}
// Students:  Add code to this file (if you wish), StudentWorld.h, Actor.h and Actor.cpp

