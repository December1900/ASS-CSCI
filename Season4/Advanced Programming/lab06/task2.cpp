#include <iostream>
using namespace std;
class Porridge{
public:
    string belong;
    void GoldilocksUse(){
        if(belong=="Papa")
            cout<<"She tasted the porridge from the first bowl."
        " This porridge is too hot!\"she exclaimed."<<endl;
        else if(belong=="Mama")
            cout<<"So, she tasted the porridge from the second bowl."
                  " \"This porridge is too cold,\" she said."<<endl;
        else
            cout<<"So, she tasted the last bowl of porridge. \"Ahhh,"
                  " this porridge is just right,\" she said happily"
                  " and she ate it all up."<<endl;
    }
};
class Chair{
public:
    string belong;
    void GoldilocksUse(){
        if(belong=="Papa")
            cout<<"Goldilocks sat in the first chair to rest her feet."
                  " \"This chair is too big!\" she exclaimed"<<endl;
        else if(belong=="Mama")
            cout<<"So she sat in the second chair."
                  " \"This chair is too big, too!\" she whined."<<endl;
        else
            cout<<"\"Ahhh, this chair is just right,\" she sighed."
                  " But just as she settled down into the chair to rest,"
                  " it broke into pieces!"<<endl;
    }
};
class Bed{
public:
    string belong;
    void GoldilocksUse(){
        if(belong=="Papa")
            cout<<"She lay down in the first bed, but it was too hard."<<endl;
        else if(belong=="Mama")
            cout<<"Then she lay in the second bed, but it was too soft."<<endl;
        else
            cout<<"Then she lay down in the third bed and it was just right."
                  " Goldilocks fell asleep."<<endl;
    }
};
class Bear{
public:
//Papa or Mama or Baby
    string BearType;
    bool porridgeUsed;
    bool chairdUsed;
    bool bedUsed;
    void CheckPorridgeUsed(){
        if(!porridgeUsed)
            return;
        if(BearType=="Papa")
            cout<<"\"Someone's been eating my porridge,"
                  "\" growled the "<<BearType<<" bear."<<endl;
        else if(BearType=="Mama")
            cout<<"\"Someone's been eating my porridge,"
        "\" said the "<<BearType<<" bear."<<endl;
        else
        cout<<"\"Someone's been eating my porridge and they ate it all up!"
              "\" cried the "<<BearType<<" bear."<<endl;
    };
    void CheckChairUsed(){
        if(!chairdUsed)
            return;
        if(BearType=="Papa")
            cout<<"\"Someone's been sitting in my chair,"
                  "\" growled the "<<BearType<<" bear."<<endl;
        else if(BearType=="Mama")
            cout<<"\"Someone's been sitting in my chair,"
                  "\" said the "<<BearType<<" bear."<<endl;
        else
            cout<<"\"Someone's been sitting in my chair, "
                  "they've broken it all to pieces,"
                  "\" cried the "<<BearType<<" bear."<<endl;
    };
    void CheckBedgeUsed(){
        if(!bedUsed)
            return;
        if(BearType=="Papa")
            cout<<"\"Someone's been sleeping in my bed,"
                  "\" growled the "<<BearType<<" bear."<<endl;
        else if(BearType=="Mama")
            cout<<"\"Someone's been sleeping in my bed,"
                  "\" said the "<<BearType<<" bear."<<endl;
        else
            cout<<"\"Someone's been sleeping in my bed, "
                  "and she's still there!"
                  "\" exclaimed"<<BearType<<" bear."<<endl;
    };
};
class GBStory {
public:
    Porridge ps[3] = {{"Papa"},{"Mama"},{"Baby"}};
    Chair cs[3] = {{"Papa"},{"Mama"},{"Baby"}};
    Bed bs[3] = {{"Papa"},{"Mama"},{"Baby"}};
    Bear bears[3]= {{"Papa"},{"Mama"},{"Baby"}};
    int FindBearIdx(string str){
        for(int i = 0;i<3;++i){
            if(bears[i].BearType==str)
                return i;
        }
    }
    void Start(){
        cout<<"Once upon a time, there was a little girl\n"
              "named Goldilocks. She went for a walk\n"
              "in the forest. Pretty soon, she came upon\n"
              "a house. She knocked and, when no one\n"
              "answered, she walked right in. "<<endl;

    };
    void GoldilocksPorridges(){
        cout<<"At the table in the kitchen, there were\n"
              "three bowls of porridge. Goldilocks was\n"
              "hungry."<<endl;
    };
    void GoldilocksChairs(){
        cout<<"After she'd eaten the three bears' breakfasts\n"
              "she decided she was feeling a little tired.\n"
              "So, she walked into the living room where\n"
              "she saw three chairs."<<endl;
    };
    void GoldilocksBed(){
        cout<<"Goldilocks was very tired by this time, so\n"
              "she went upstairs to the bedroom. She lay\n"
              "down in the first bed, but it was too hard.\n"
              "Then she lay in the second bed, but it was\n"
              "too soft. Then she lay down in the third\n"
              "bed and it was just right. Goldilocks fell\n"
              "asleep."<<endl;
        cout<<"As she was sleeping, the three bears came home. "<<endl;
    };
    void End(){
        cout<<"Just then, Goldilocks woke up and saw the\n"
              "three bears. She screamed, \"Help!\" And she\n"
              "jumped up and ran out of the room.\n"
              "Goldilocks ran down the stairs, opened the\n"
              "door, and ran away into the forest. And\n"
              "she never returned to the home of the three\n"
              "bears."<<endl;
    };
};

GBStory gb;
int main(){
    gb.Start();
    gb.GoldilocksPorridges();
    for(auto p:gb.ps){
        p.GoldilocksUse();
        gb.bears[gb.FindBearIdx(p.belong)].porridgeUsed = true;
    }
    gb.GoldilocksChairs();
    for(auto c:gb.cs){
        c.GoldilocksUse();
        gb.bears[gb.FindBearIdx(c.belong)].chairdUsed = true;
    }
    gb.GoldilocksBed();
    for(auto b:gb.bs){
        b.GoldilocksUse();
        gb.bears[gb.FindBearIdx(b.belong)].bedUsed = true;
    }
    for(auto b:gb.bears){
        b.CheckPorridgeUsed();
    }
    for(auto b:gb.bears){
        b.CheckChairUsed();
    }
    for(auto b:gb.bears){
        b.CheckBedgeUsed();
    }
    gb.End();
}
