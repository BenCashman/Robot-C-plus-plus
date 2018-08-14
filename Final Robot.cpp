//  main.cpp
//  Final Robot Project
//
//  Created by Benjamin Cashman on 5/29/17.
//  Copyright © 2017 Benjamin Cashman. All rights reserved.
//

#include <iostream>
#include <string>
using namespace std;

// declare grid constants as global
const int rowSize= 25;
const int colSize= 25;
char grid[rowSize][colSize];



class Robot {
private:
    int x;
    int y;
    char payload;
public:

    Robot()
    {
        x = 1;
        y = 1;
        payload = ' ';
    }

    Robot (int x, int y,char payload )
    {
        this ->x =x;
        this ->y =y;
        this ->payload = payload;
    }
    // getters
    //getters
    int getX(){
        return x;
    }
    int getY(){
        return y;
    }
    char getPayload(){
        return payload;
    }

    //setters

    void setGrid()
    {
        // initialize grid
        for (int i = 1; i<rowSize;i++)
            for (int j = 1; j<colSize;j++)
                grid[i][j]= '-';

        // place some letters randomly thorugh grid

        grid[5][15]= 'A';
        grid[7][11]= 'B';
        grid[10][9]= 'C';
        grid[5][7] = 'D';
        grid[15][6]= 'E';
        grid[19][4]= 'F';

    }

    void setX(int a){
        x=a;
    }
    void setY(int a){
        y=a;
    }
    void setPayload(char c){
        payload=c;
    }



    // setters

    void moveRight(){
        y++;
    }
    void moveLeft(){
        y--;
    }
    void moveUp(){
        x--;
    }
    void moveDown(){
        x++;
    }
    void moveTo(int a, int b){
        int xS, yS, xD, yD;
        xS = getX();
        yS = getY();
        xD = a;
        yD = b;

        int xDiff = xD - xS;
        int yDiff = yD - yS;

        cout << "The robot is at (" << xS <<"," << yS << ")" << endl;
        cout << "Move the robot to point (" << xD <<"," << yD << ")" << endl;

        //cout << "Moving in X direction::" << endl << "\t";
        // condition if outside for loop for computation
        if (xDiff > 0)
        {
            for(int i = 1; i <= abs(xDiff); i++)
                moveDown();
        }
        else
            for(int i = 1; i <= abs(xDiff); i++)
                moveUp();
        cout <<endl;

        //cout << "Moving in Y direction::" << endl << "\t";
        if (yDiff >0)
        {
            for(int i = 1; i <= abs(yDiff); i++)
                moveRight();
        }
        else
            for(int i = 1; i <= abs(yDiff); i++){
                moveLeft();
            }
    } // end of moveTo()

    void print(){
        cout << "Robot is at x, y  position " << x << " , "<< y <<" and has a payload of value = ("<< payload << ") char"<< endl;
        // display grid
        for (int i = 1; i<rowSize;i++){
            for (int j = 1; j<colSize;j++)
                if(i ==x && j ==y)
                    cout << "R-"<<payload<<"|";  // change to "grid" from -
                else
                    cout << "---|"; // change to use |
            cout<< endl; // need to start new row at end of colum
        }
    }


    bool pickup(int lx,int ly){
        if(getX()==lx && getY()==ly && grid[lx][ly]!= '-' && getPayload()==' ')
        {
            setPayload(grid[lx][ly]);
            grid[lx][ly]='-';
            return true;
        }

        else if(getX()!=lx || getY()!=ly){
            cout<<"Not at ("<<lx<<", "<<ly<<")"<<'\n';
            return false;
        }

        else if (grid[lx][ly] =='-'){
            cout<<"No load at this location \n";
            return false;
        }
        else if(getPayload() !=' '){
            cout<<"payload not empty \n";
            return false;
        }
        else{
            return false;
        }
    }

    bool dropoff(int lx,int ly){
        if(getX()==lx && getY()==ly){
            if(getPayload()!=' '){
                grid[lx][ly]=getPayload();
                setPayload(' ');
                return true;
            }
            else{
                cout<<"Payload was empty\n";
                return false;
            }
        }
        else{
            cout<<"Not at "<<lx<<", "<<ly<<'\n';
            return false;
        }
    }
};


// non member print grid function
void printGrid(const char m[][colSize], int rowSize){// grid is char array
    // display grid
    for (int i = 1; i<rowSize;i++){
        for (int j = 1; j<colSize;j++)
            cout <<"-"<< m[i][j]<<"-|";// modifiy from video2 to show grid
        cout<< endl; // need to start new row at end of colum
    }
}


void clear(char grid[][colSize], int rowSize)
{
    int count = 0;
    for(unsigned int i = 1; i < rowSize; i++)
    {
        for (unsigned int j = 1; j < colSize; j++)
        {
            if ( grid[i][j]  != '-')
            {
                count++;
                Robot* pRobot1 = new Robot(i,j,' ');
                pRobot1-> pickup(i, j);
                delete pRobot1;
            }
        }
    }
}

int main() {
    //needed to do a seprate grid set function to give pickup access to the grid.
    Robot setGrid;
    setGrid.setGrid();

    printGrid(grid,rowSize);
    cout << endl;

        Robot r1;
        Robot r2(10,15,'L');

        r1.print();
        r2.print();

        cout << "Testing Move Functions"<< endl;
        cout <<"-----------------------" << endl;
        r2.moveRight();
        r2.print();
        cout <<"-----------------------" << endl;
        r2.moveUp();
        r2.print();
        cout <<"-----------------------" << endl;
        r2.moveLeft();
        r2.print();
        cout <<"-----------------------" << endl;
        r2.moveDown();
        r2.print();
        cout <<"-----------------------" << endl;

        cout << "-=-=-=-=-=-=-=-=-DEMO moveTO()  test--==-="<< endl;
        r2.moveTo(13,17);
        r2.print();

        // Pickup test to payload test to get letter D at 5 7
        cout <<"++++++++++++++++++++XXXXXXXXXXXXXXXXXXXXXXXXXXX+++++++++++++++++++++"<< endl;
        cout <<"++++++++++++++++++++XXXXXXXXXXXXXXXXXXXXXXXXXXX+++++++++++++++++++++"<<endl;
        cout << "Pickup test at  'D' 5,7" << endl;
        r2.print();
        r2.pickup(5,7);
        cout << "Try again, after first using moveTo() to move Robot" << endl;
        r2.moveTo(5,7);
        r2.pickup(5,7);
        cout << "Try again, after first resetting payload to empty" << endl;

        r2.setPayload(' ');
        r2.pickup(5,7);
        r2.print(); // print to check if Robot is at called location e.g. (5,7)

        // DropOff test to  put payload test to get letter D at 4 9
        cout <<"++++++++++++++++++++XXXXXXXXXXXXXXXXXXXXXXXXXXX+++++++++++++++++++++"<< endl;
        cout <<"++++++++++++++++++++XXXXXXXXXXXXXXXXXXXXXXXXXXX+++++++++++++++++++++"<<endl;
        cout << "dropoff test at  'D' 4,9" << endl;
        r2.print();
        r2.dropoff(4,9);
        cout << "Try again, after first using moveTo() to move Robot" << endl;
        r2.moveTo(4,9);
        cout << "Empty payload and test if anything can be droped off at (4,9)" << endl;

        r2.setPayload(' ');
        r2.dropoff(4,9);

        cout << "Try again, after first resetting payload with 'D' " << endl;
        r2.setPayload('D');
        r2.dropoff(4,9);

        r2.print(); // print to check id Robot ad  called location e.g. (4,9)
        r2.dropoff(4,9);
        cout << "Check to confirm payload empty after dropoff" << endl;
        r2.print();
        cout <<"++++++++++++++++++++OOOOOOOOOOOOOOOOOOOOOOOOOOOO+++++++++++++++++++++"<< endl;


    printGrid(grid, rowSize);
    cout << "**********************************************************************" <<endl;
    cout << "Now using the Clear Function on the grid " << endl;
    clear(grid, rowSize);
    cout << "After using the Clear Function on the grid " << endl;
    printGrid(grid, rowSize);


    return 0;
}// end of main
