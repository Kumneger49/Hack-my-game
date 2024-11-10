#include <iostream>
#include <fstream>
#include "hacking_functions.h"
void dataHackFunc(long**, long[], int, int);

using namespace std;
int main(){
    //create an input file stream and open the gameinfo.txt file
    ifstream fileread("gameinfo.txt");
    if(fileread.fail()){
        cout<<"Error";
        return -1;
    }
    int processId=0;
    // long  *healthPtr, *energyPtr, *uiCharPtr;
    // long *moneyPtr;
    long amoneyPtr, ahealthPtr, aenergyPtr, auiCharPtr;
    int maxProp=0;
    char newUiChar, choice;
    //read the content of the file one line at a time
    fileread>>processId;
    fileread>>maxProp;
    fileread>>hex>>amoneyPtr;
    fileread>>hex>>ahealthPtr;
    fileread>>hex>>aenergyPtr;
    fileread>>hex>>auiCharPtr;
 
   
    //attach the program to the game
    attachToProcess(processId);

    long propertiesArray[3]={amoneyPtr, ahealthPtr, aenergyPtr};

    //create a 2d array and populate it with values that read from the gameinfo.txt file
    long **gameprops=new long*[3];

    for(int i=0; i<3; i++){
        gameprops[i]=new long[maxProp];
        for(int j=0; j<maxProp; j++){
            gameprops[i][j]=0;
         }
    }

 
        cout<<"\n\nPlease select the desired mode"<<endl;
        cout<<"[1] UI Hacking Mode"<<endl;
        cout<<"[2] Data Hacking Mode"<<endl;
        cout<<"[3] Exit"<<endl<<endl;
        cin>>choice;
        switch (choice)
        {
        case '1':
            //code to change the ui character of the game
            cout<<"This is the current character of the game: "<<readUIChar(processId, auiCharPtr)<<endl;
            cout<<"What do you want to change it to?"<<endl;
            cin>>newUiChar;
            //calling the predefined function "writeUIchar" to change the character of the game
            cout<<"You have successfuly changed the character from "<<readUIChar(processId, auiCharPtr)<<" to "<<newUiChar<<endl;
            writeUIChar(processId,  auiCharPtr, newUiChar);
            break;
        case '2':
            //code to modify the value inside the game
            dataHackFunc(gameprops, propertiesArray, processId, maxProp);
            break; 
        case '3':
            cout<<"You have chosen to exit the program."<<endl;
            cout<<"Thank you!"<<endl;
            break;
        default:
            //code whenever the user enters other than 1, 2, or 3
            cout<<"You entered a wrong key"<<endl;
            break;
        }
 
    //close the file 
    fileread.close();
    //iterate over and delete the memory address three arrays are holding
    for(int i=0; i<3; i++){
        delete[]gameprops[i];
    }
    //delete the memory address of the array that contains the three arrays 
    delete []gameprops;
    detachProcess(processId);
}

void dataHackFunc(long **gamePropsArg, long propertiesArray[], int pID, int max){
    int propNumber=-1, newValue=-1, count=0, ctr=0;
    string array[3]={"Money", "Health", "Energy"};
    while(true){
        propNumber=-1; newValue=-1; count=0; ctr=0;
        while(propNumber<0 || propNumber>2){//as long as the user enters a wrong key
            if(count==0){//if the first time the user is attempting 
                cout<<"Select which game value to hack"<<endl;
            }
            else{//or if the user tried it before and entered a wrong key
                cout<<"Wrong choice, choose 0, 1, or 2"<<endl;
            }
            cout<<"[0] Money"<<endl;
            cout<<"[1] Health"<<endl;
            cout<<"[2] Energy"<<endl;
            cin>>propNumber;
            count++;//keep track of how many times the user entered this block 
        }
        count=0;//make count 0 so that the other blocks can use it for the same logic

        for(int i=0; i<max; i++){
            int a=readValue(pID, propertiesArray[propNumber]+i);
            if(a>=1){
                ctr++;
            }
        }


        while(newValue<0 || newValue>max){
            if(count==0){
                cout<<"This is the value at the moment: "<<ctr<<endl;
                cout<<"Enter the number you want to change your game value to (0 to "<<max<<")"<<endl;
            }
            else{
                cout<<"Wrong choice, choose from 0 through "<<max<<endl;
            }
            cin>>newValue;
            count++;
        }
        char c;
        cout<<"Do you want to modify values before hacking? n for no and any other key for yes"<<endl;
        cin>>c;
        if(c=='n'){
        break;
        }
    }
    

    if(newValue==0){
        for(int i=0; i<max; i++){
            modifyValue(pID, propertiesArray[propNumber]+i, 0);
        }
    }
    
    else{
        for(int i=0; i<newValue; i++){
            //modify your arry you cloned from the game memory
            // gamePropsArg[i][j]=1;
            //using the predefined function "modifyValue" modify the game memory
            modifyValue(pID, propertiesArray[propNumber]+i, 1);
        }
    }
    cout<<"You have successfuly changed the " <<array[propNumber]<<" property from "<<ctr<<" to "<<newValue<<endl;

}