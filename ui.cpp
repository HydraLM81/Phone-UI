#include <iostream> //for console output
#include <vector> //for list app
#include <bits/stdc++.h> 
#include <ctime> //for printTime()
#include <stdlib.h>
#include <unistd.h>
#include <experimental/source_location> //to tell me where logic errors are
using namespace std;

/*used for testing and bug prevention in the form of kill(c,SIGTERM);*/
pid_t c;

/*prints just system time in UTC*/
string printTime(){
  auto givemetime = chrono::system_clock::to_time_t(chrono::system_clock::now());
  string fullTime =ctime(&givemetime);
  string justTime;
  //only selects the hour and minute from the full date
  for(int a=fullTime.find(':')-2;a<fullTime.find(':')+3;a++) 
    justTime+=fullTime[a];
  return justTime;
}

/*turns char arrays into strings*/
string intoString(char word[]){
  string ret;
  for(int a=0;a<5;a++)
    ret+=word[a];
  return ret;
}

/*Lines*/
void dEmpty(int times,string color,const std::experimental::source_location loc = std::experimental::source_location::current()){
  if(times>0)
    for(int a=0;a<times;a++)
      cout<<color<<"|                                |"<<endl;
  else cout<<"Invalid amount of lines in dEmpty() at "<<loc.line();
}
void draw(string text,string color,string color2,const std::experimental::source_location loc = std::experimental::source_location::current()){
  if(text.length()!=0){
    cout<<color<<"| "<<color2<<text<<"\033[0m";
    //if text doesn't have colored attributes
    if(text.find("\033[")==string::npos){
      if(31-text.length()>=0)
        for(int a=0;a<31-text.length();a++)
          cout<<" ";
      else{
        cout<<"Too much text in draw() at line "<<loc.line();
      }
    }
    //if text has colored attributes
    else
        cout<<"                          ";
    cout<<color<<"|\n";
  }
}

/*Screen*/
void screenDrawTop(string color, string color2){
  system("CLS");
  
  cout<<color<<"  ______________________________"<<endl;
  cout<<color<<" /                              \\"<<endl;
  cout<<color<<"|            A Phone             |"<<endl;
  cout<<color<<"|           o   <>   o           |"<<endl;
  cout<<color<<"|________________________________|"<<endl;
  cout<<color<<"|"<<color2<<"AT&T                      "<<printTime()<<color<<" |"<<endl;
}
void screenDrawHome(string color, string color2){
  draw("  ______    ______    ______",color,color2);
  draw(" |\\    /|  | |    |  |      |",color,color2);
  draw(" | \\/\\/ |  | |__  |  | RPS  |",color,color2);
  draw(" |______|  |______|  |______|",color,color2);
  draw("  Wordle     List      RPS",color,color2);
  draw("  ______",color,color2);
  draw(" | SETT |",color,color2);
  draw(" | INGS |",color,color2);
  draw(" |______|",color,color2);
  draw(" Settings",color,color2);
  dEmpty(9,color);
}
void screenDrawBottom(string color){
  cout<<color<<"|________________________________|"<<endl;
  cout<<color<<"|              ____              |"<<endl;
  cout<<color<<"|             |    |             |"<<endl;
  cout<<color<<"|             |____|             |"<<endl;
  cout<<color<<" \\______________________________/\n\n\n";
}

/*List*/
void alphabetList(vector<string> &list){
  for(int b=0;b<list.size()-1;b++)
    for(int a=0;a<list.size()-1;a++)
      if(list[a][0]>list[a+1][0])
        swap(list[a],list[a+1]);
  for(int a=0;a<list.size()-1;a++)
    for(int b=0;b<list.size()-1;b++)
      if(list[a][0]==list[a+1][0]){
        //I thought try blocks were fun so I wanted to use them
        try {
          if(list[a][1]>list[a+1][1])
            swap(list[a],list[a+1]);
          if(list[a][1]==list[a+1][1])
            try{
              if(list[a][2]>list[a+1][2])
                swap(list[a],list[a+1]);
              throw "items under 3 letters";
            }
            catch(...){break;}
            throw "items under 2 letters";
          }
        catch(...){break;}
      }
}
void asileList(vector<string> &list,vector<int> &numList){
   for(int b=0;b<numList.size()-1;b++)
    for(int a=0;a<numList.size()-1;a++)
      if(numList[a]>numList[a+1]){
        swap(numList[a],numList[a+1]);
        swap(list[a],list[a+1]);
      }
}
void printList(vector<string> list, string color,string color2){
  for(int a=0;a<list.size();a++)
    draw(list[a],color,color2);
}
void inputList(vector<string>&list,vector<int>&asile){
  string userItem;
  cin>>ws;
  cin>>userItem;
  list.push_back(userItem);
  int userAsile;
  cin>>ws;
  cin>>userAsile;
  asile.push_back(userAsile);
}
void shoppingList(string color,string color2,vector<string>&list,vector<int>&asile){
  while(true){
    TOP:
    screenDrawTop(color,color2);
    //if something's in the list
    if(list.size()>0){
      draw("Your Current List:",color,color2);
      dEmpty(1,color);
      printList(list,color,color2);
      dEmpty(1,color);
      draw("If you would like to sort the",color,color2);
      draw("list alphabetically, enter 1.",color,color2);
      draw("To rearrange by asile number,",color,color2);
      draw("enter 2. To input more items,",color,color2); 
      draw("enter 3. To clear the list,",color,color2);
      draw("enter 4.",color,color2);
      dEmpty(9-list.size(),color);
      screenDrawBottom(color);
      int rearrange=0;
      cin>>rearrange;
      if(rearrange==1)
        alphabetList(list);
      else if(rearrange==2)
        asileList(list,asile);
      else if(rearrange==3){
        screenDrawTop(color,color2);
        draw("Your Current List:",color,color2);
        dEmpty(1,color);
        printList(list,color,color2);
        dEmpty(1,color);
        draw("Input one item:",color,color2);
        dEmpty(14-list.size(),color);
        screenDrawBottom(color);
        inputList(list,asile);
      }
      else if(rearrange==4){
        list.clear();
        asile.clear();
      }
      else goto TOP;
    }
    else{
      draw("There is nothing in this list.",color,color2);
      draw("Add items by typing their name",color,color2);
      draw("followed by their asile number.",color,color2);
      draw("Press enter between the name",color,color2);
      draw("and number. 1 word names only.",color,color2);
      dEmpty(14,color);
      screenDrawBottom(color);
      inputList(list,asile);
    }
    //Ending list app
    cout<<color2<<"Would you like to go to the home page?\n";
    string stay;
    cin>>ws;
    cin>>stay;
    if(stay=="yes"||stay=="Yes"||stay=="y"||stay=="Y")
      break;
    else goto TOP;
  }
}

/*Settings (only for changing color of text and border)*/
void settings(string &color,string &color2){
  while(true){
    screenDrawTop(color,color2);
    draw("Settings",color,color2);
    draw("Choose border color:",color,color2);
    draw("White",color,"\033[0m");
    draw("Red",color,"\033[31m");
    draw("Green",color,"\033[32m");
    draw("Yellow",color,"\033[33m");
    draw("Blue",color,"\033[34m");
    draw("Magenta",color,"\033[35m");
    draw("Cyan",color,"\033[36m");
    dEmpty(10,color);
    screenDrawBottom(color);
    cin>>color;
    if(color=="White"||color=="white")
      color="\033[0m";
    else if(color=="Red"||color=="red")
      color="\033[31m";
    else if(color=="Green"||color=="green")
      color="\033[32m";
    else if(color=="Yellow"||color=="yellow")
      color="\033[33m";
    else if(color=="Blue"||color=="blue")
      color="\033[34m";
    else if(color=="Magenta"||color=="magenta")
      color="\033[35m";
    else if(color=="Cyan"||color=="cyan")
      color="\033[36m";
   else color="\033[0m";
    screenDrawTop(color,color2);
    draw("Settings",color,color2);
    draw("Choose text color:",color,color2);
    draw("White",color,"\033[0m");
    draw("Red",color,"\033[31m");
    draw("Green",color,"\033[32m");
    draw("Yellow",color,"\033[33m");
    draw("Blue",color,"\033[34m");
    draw("Magenta",color,"\033[35m");
    draw("Cyan",color,"\033[36m");
    dEmpty(10,color);
    screenDrawBottom(color);
    cin>>color2;
    if(color2=="White"||color2=="white")
      color2="\033[0m";
    else if(color2=="Red"||color2=="red")
      color2="\033[31m";
    else if(color2=="Green"||color2=="green")
      color2="\033[32m";
    else if(color2=="Yellow"||color2=="yellow")
      color2="\033[33m";
    else if(color2=="Blue"||color2=="blue")
      color2="\033[34m";
    else if(color2=="Magenta"||color2=="magenta")
      color2="\033[35m";
    else if(color2=="Cyan"||color2=="cyan")
      color2="\033[36m";
    else color2="\033[0m";
    //ending Settings app
    cout<<color2<<"Would you like to go to the home page?\n";
    string stay="no";
    cin>>stay;
    if(stay=="yes"||stay=="Yes"||stay=="y"||stay=="Y")
      break;
  }
}

/*Wordle*/
void wordleRemake(string color,string color2){
  //these need to be declared seperately because c++ is weird. idk why this fixes the problem, but it does. (used in what was checkGuess())
  string white="\033[0m";
  string yellow="\033[43m";
  string green="\033[42m";
  //choosing word
  fstream file("words.txt");
  string word;
  string fromTxt[12972];
  if (file.is_open()) 
    for(int num=0;num<12972;num++) {
      getline(file, word);
      fromTxt[num] = word;
    }
  while(true){
    //declaring and resetting variables for each playthrough
    bool answerFlags[5]={0,0,0,0,0};
    string score[5]={"","","","",""};
    string answerWordString=fromTxt[rand()%12972];
    char answerWord[5]={' ',' ',' ',' ',' '};
    for(int a=0;a<5;a++)
      answerWord[a]=answerWordString[a];
    //storing of guesses
    string storedGuesses[6]={"","","","","",""};
    //starting
    bool solved=false;
    //guesses keeps track of how many guesses and is updated in this for loop
    int guesses=0;
    for(guesses=0;guesses<6&&!solved;guesses++){
      //resetting variables for each guess
      bool answerFlags[5]={0,0,0,0,0};
      string score[5]={"","","","",""};
      //starting
      screenDrawTop(color,color2);
      draw("Welcome to Wordle!",color,color2);
      dEmpty(1,color);
      //drawing all guesses from this round (colorized)
      for(int a=0;a<guesses;a++)
        draw(storedGuesses[a],color,color2);
      dEmpty(1,color);
      draw("Input a 5 letter word:",color,color2);
      dEmpty(15-guesses,color);
      screenDrawBottom(color);
      //fromUser stored as a char array because of individual letter checks (can't use strings and indexes)
      char fromUser[5];
      cin>>fromUser;
      //for valid checking and easier printing
      string fromUserString=intoString(fromUser);
      //error testing
      if (strcmp(fromUser,"xxplx")==0){
        cout<<color2<<answerWordString<<endl;
        sleep(1);
      }
      //check if valid
      bool valid=0;
      for (int a = 0; a < 12972; a++) 
        if (fromTxt[a] == fromUserString) {
          valid=1;
          break;
        }
      //if not valid
      while (valid==0) {
        screenDrawTop(color,color2);
        draw("Welcome to Wordle!",color,color2);
        dEmpty(1,color);
        for(int a=0;a<guesses;a++)
          draw(storedGuesses[a],color,color2);
        dEmpty(1,color);
        draw("That is not a valid word.",color,color2);
        draw("Please try again:",color,color2);
        dEmpty(14-guesses,color);
        screenDrawBottom(color);
        cin >> fromUser;
        fromUserString=intoString(fromUser);
        for (int a = 0; a < 12972; a++) 
          if (fromTxt[a]==fromUserString) {
            valid=1;
            break;
          }
      }
      //checking user guess
      for (int a = 0; a < 5; a++) {
        //if green
        if (fromUserString[a] == answerWord[a]) {
          score[a] = green+fromUserString[a];
          answerFlags[a]=true;
        } 
        //else white
        else
          score[a] = white+fromUserString[a];
      }
      for (int b = 0; b < 5; b++) 
        if (answerFlags[b] == 0) 
          for (int c = 0; c < 5; c++) 
            //if yellow
            if (fromUserString[c] == answerWord[b] && score[c] != green+fromUserString[c]) {
              score[c] = yellow+fromUserString[c];
              break;
            }
      //storing guess for reprint
      for(int a=0;a<5;a++)
        storedGuesses[guesses]+=score[a];
      //check if solved
if(answerFlags[0]==true&&answerFlags[1]==true&&answerFlags[2]==true&&answerFlags[3]==true&&answerFlags[4]==true)
        solved=true;
    }
    //ending
    screenDrawTop(color,color2);
    draw("Welcome to Wordle",color,color2);
    dEmpty(1,color);
    for(int a=0;a<6;a++)
      draw(storedGuesses[a],color,color2);
    //if user was right
    if(solved)
      draw("Congradulations!",color,color2);
    else dEmpty(1,color);
    draw("The word was "+answerWordString,color,color2);
    dEmpty(4,color);
    //playAgain
    draw("Will you play again? y/n",color,color2);
    dEmpty(10-guesses,color);
    screenDrawBottom(color);
    //playAgain (continued)
    string stay="no";
    cin>>stay;
    if(stay=="no"||stay=="No"||stay=="n"||stay=="n")
      break;
  }
}

/*Rock paper scissors*/
void rps(string color,string color2){
  //keeps track of ai points and user points throughout the use of the app (resets every call of rps())
  int userPoints=0;
  int aiPoints=0;
  while(true){
    screenDrawTop(color,color2);
    draw("Rock Paper Scissors",color,color2);
    dEmpty(1,color);
    draw("Type Rock, Paper, or Scissors",color,color2);
    draw("to choose your move. Ready? y/n",color,color2);
    dEmpty(15,color);
    screenDrawBottom(color);
    //checking if user is ready
    string ready;
    getline(cin,ready);
    //keeping them until ready
    while(ready!="yes"&&ready!="Yes"&&ready!="Y"&&ready!="y"){
      screenDrawTop(color,color2);
      draw("Rock Paper Scissors",color,color2);
      dEmpty(1,color);
      draw("Type Rock, Paper, or Scissors",color,color2);
      draw("to choose your move. Ready? y/n",color,color2);
      dEmpty(15,color);
      screenDrawBottom(color);
      cin>>ready;
    }
    //the intro thing for the game
    {
    screenDrawTop(color,color2);
    draw("Rock Paper Scissors",color,color2);
    dEmpty(2,color);
    draw("Rock",color,color2);
    dEmpty(15,color);
    screenDrawBottom(color);
    sleep(1);
    screenDrawTop(color,color2);
    draw("Rock Paper Scissors",color,color2);
    dEmpty(2,color);
    draw("Rock",color,color2);
    draw("Paper",color,color2);
    dEmpty(14,color);
    screenDrawBottom(color);
    sleep(1);
    screenDrawTop(color,color2);
    draw("Rock Paper Scissors",color,color2);
    dEmpty(2,color);
    draw("Rock",color,color2);
    draw("Paper",color,color2);
    draw("Scissors",color,color2);
    dEmpty(13,color);
    screenDrawBottom(color);
    sleep(1);
    screenDrawTop(color,color2);
    draw("Rock Paper Scissors",color,color2);
    dEmpty(2,color);
    draw("Rock",color,color2);
    draw("Paper",color,color2);
    draw("Scissors",color,color2);
    draw("Shoot!",color,color2);
    dEmpty(12,color);
    screenDrawBottom(color);
    }
    string userChoice;
    cin>>userChoice;
    //1=rock, 2=paper, 3=scissors, 4=error
    int aiNum=rand()%3+1;
    screenDrawTop(color,color2);
    draw("Rock Paper Scissors",color,color2);
    dEmpty(1,color);
    string aiChoice;
    if(aiNum==1){
      draw("Rock!",color,color2);
      aiChoice="rock";  
    }
    else if(aiNum==2){
      draw("Paper!",color,color2);
      aiChoice="paper";  
    }
    else if(aiNum==3){
      draw("Scissors!",color,color2);
      aiChoice="scissors";  
    }
    
    dEmpty(1,color);
    //who is for grammar and comparison checking
    string who;
    //user chose rock
    if(userChoice=="Rock"||userChoice=="rock"){
      if(aiChoice=="rock")
        who="neither of us";
      else if(aiChoice=="paper")
        who="I";
      else who="you";
    }
    //user chose paper
    else if(userChoice=="Paper"||userChoice=="paper"){
      if(aiChoice=="rock")
        who="you";
      else if(aiChoice=="paper")
        who="neither of us";
      else who="I";
    }
    //user chose scissors
    else if(userChoice=="Scissors"||userChoice=="scissors"){
      if(aiChoice=="rock")
        who="I";
      else if(aiChoice=="paper")
        who="you";
      else who="neither of us";
    }
    //mainly for grammar so I don't have to deal with these things 
    else{
      draw("Improper input. Try again.",color,color2);
      userChoice="improper input";
      who="neither of us";
    }
    draw("Since you chose "+userChoice,color,color2);
    draw("and I chose "+aiChoice+",",color,color2);
    draw(who+" won.",color,color2);
    if(who=="you"){
      userPoints++;
      dEmpty(1,color);  
    }
    else if(who=="I") {
      aiPoints++;
      dEmpty(1,color);  
    }
    //printing points
    draw("Your points: "+to_string(userPoints),color,color2);
    draw("My points: "+to_string(aiPoints),color,color2);
    dEmpty(2,color);
    //playagain
    draw("Will you play again? y/n",color,color2);
    dEmpty(6,color);
    screenDrawBottom(color);
    //checking if playagain
    string stay="no";
    cin>>stay;
    if(stay=="no"||stay=="No"||stay=="n"||stay=="n")
      break;
  }
}

int main() { 
  //making it random
  srand(time(NULL));
  //setting text and border colors to white
  string color="\033[0m";
  string color2="\033[0m";
  //so the list app doesn't reset between uses
  vector<string>list;
  vector<int>asile;
  while(true){
    screenDrawTop(color, color2);
    screenDrawHome(color,color2);
    screenDrawBottom(color);
    cout<<"You can choose what app you want to use by typing its name when prompted.\nAny further instructions will be provided within the app if applicable. Are you ready to proceed? y/n\n";
    string proceed;
    getline(cin,proceed);
    sleep(1);
    if(proceed=="y"||proceed=="yes"||proceed=="Y"||proceed=="Yes")
      break;
  }
  //to use multiple apps 
  while(true){
    screenDrawTop(color,color2);
    screenDrawHome(color,color2);
    screenDrawBottom(color);
    //asking for appChoice
    cout<<color2<<"What app do you want to use?\n";
    string appChoice;
    //using getline instead of cin to prevent skipping the quit cin
    cin>>appChoice;
    if(appChoice=="List"||appChoice=="list")
      shoppingList(color,color2,list,asile);
    else if(appChoice=="Wordle"||appChoice=="wordle")
      wordleRemake(color,color2);
    else if(appChoice=="RPS"||appChoice=="rps")
      rps(color,color2);
    else if(appChoice=="Settings"||appChoice=="settings")
      settings(color,color2);
    else cout<<color2<<"Not a valid option.\n";
    //continue program or not
    cout<<color2<<"Quit? y/n\n";
    string stay;
    //getline again for the same reason
    getline(cin,stay);
    if(stay=="y"||stay=="yes"||stay=="Y"||stay=="Yes"){
      cout<<color2<<"Thanks for using me!";
      break;
    }
  }
}