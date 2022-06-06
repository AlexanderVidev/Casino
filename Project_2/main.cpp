/* 
 * File:   main.cpp
 * Author: Aleksandar Videv
 * Created: 5/09/2022
 * Purpose: Project for the game crabs
 * 
 */

//System Libraries
#include <iostream>
#include <iomanip>
#include <cmath>
#include <fstream>
using namespace std;

//User Libraries
void menu(int, float, int);
void craps(int, float, int); // Craps
int sumRolD(); // Roll the two dice and gets the sum of both of them
void oddBet(int, int, int, int, int, float, int);
void odBetPL(int , int , int , int , float , int );
void odbeDPL(int , int , int , int , float , int );

//Global Constants, no Global Variables are allowed
const int begchip = 100;

//Execution Begins Here!
int main(int argc, char** argv) 
{  
    srand(static_cast<unsigned int>(time(0))); // Allows us to get a random number by creating time
       
    //Declare Variables                   
    int chips;   // Every player starts with 100 chips
    float betChip = 0; // How many of the chips he want to bet
    int chipWon = 0;   // How many chis did the player win
     
    char name[100];    // Takes a name the size of 100 letters
    ifstream in; 
    ofstream out;
    in.open ("inName.txt");
    out.open ("outChips.txt");
    
    //Initialize or input i.e. set variable values
    //Display the outputs       
    in >> name;    
    cout << "Welcome to crabs " << name << "." << endl;
    chips = begchip;  
    
    menu(chips, betChip, chipWon);
       
    out << "You left the casino with " << chips;
    //Exit stage right or left!
    in.close();
    out.close();
    return 0;
}

void menu(int chips, float betChip, int chipWon)
{
    int gameOption;    
    cout << "1. Craps" << endl;
    cout << "2. Roulette" << endl;
    cout << "Which game do you want to play:" << endl;
    cin >> gameOption; 
        
    switch(gameOption)
    {       
        case 1:           
            cout << " " << endl;
            craps(chips, betChip, chipWon);                
        break;
            
        /*
        case 2:  
            cout << " " << endl;
            roulette();

            // Checks if the user has more chips then 0. If yes he can continue playing.
            if(chips != 0)
            {
            cout << "Do you want to play another game in the casino? Yes/No:" << endl;
            cin >> playAnotherGame;
                if(tolower(playAnotherGame[0]) == 'y')
                {
                    menu(); 
                }                
            } 
        break;
         * */       
    default:            
    cout << "You entered none of the above." << endl;             
    }
}

void craps(int chips, float betChip, int chipWon)
{ 
    int plBetCh;       // What bet does the player want to make
    int btCOdd;        // Bet chips on odd
    int btChCome;      // Bet chips on come
    string OddBet;     // If he want to make an odd bet
    string ComeBet;    // If he want to make an come bet
      
    int diceOne;
    int diceTwo;
    int sumOfDe;       // The sum of both Dice
    int fDiceRw;       // The first sum the the rowed dice
    int sDiceRw;       // The second sum the the rowed dice
    
    string playAg;     // Ask if the player want to play again
    
    bool stop;         // Stops the program
    int result;
    
    // Loop until the user doesn't want to play
    do   
    { 
        cout << "You can bet on:" << endl;
        cout << "1. Pass Line" << endl;
        cout << "2. Don’t pass bets" << endl;
        cout << "3. EXIT" << endl;
        cout << "What bet do you want to make of the following:" << endl; 
        cin >> plBetCh;
        
        switch(plBetCh)
        {     
            // Pass Line
            case 1:                    
                   
                    if(chips == 0) // Checks for the user has more then 0 chis to play
                    {
                        cout << " " << endl;
                        cout << "You are broke and you can't play anymore" << endl;
                        exit(0);              
                    }

                    cout << " " << endl;
                    cout << "You have " << chips << " chips." << endl;
                    cout << "How much chips do you want to bet:" << endl;
                    cin >> betChip;
                    
                    while(betChip > chips) // Doesn't let the user to input more chips than he has
                    {
                        cout << " " << endl;
                        cout << "You don't have that many chips." << endl;
                        cout << "You have " << chips << " chips." << endl;
                        cout << "Enter an amount of chips that you have:" << endl;
                        cin >> betChip;
                    }
                                     
                    sumOfDe = sumRolD(); 
                    
                    fDiceRw = sumOfDe;
                    cout << " " << endl;
                    cout << "The dice rowed " << fDiceRw << endl;
                    chips -= betChip;

                    // Checking  if the rolled dice are equal to 7, 11
                    if (fDiceRw == 7 ||  fDiceRw == 11) 
                    {
                        cout << " " << endl;
                        cout << "You won your bet" << endl;
                        chipWon = betChip * 2;
                        chips += chipWon;
                        cout << "You won " << chipWon << " chips and your total chips are " <<  chips << endl;
                    }          
                    // Checking  if the rolled dice are equal to 2, 3, 12 
                    else if (fDiceRw == 2 || fDiceRw == 3 || fDiceRw == 12) 
                    {
                        cout << " " << endl;
                        cout << "You lost your bet" << endl;
                        cout << "You lost " << betChip << " chips and your total chips are " <<  chips << endl;
                    }
                    // Go to point numbers and ask him if he want to make an odd or come bet
                    else 
                    {   
                        cout << "This is one of the point numbers" << endl;
                        cout << " " << endl;                                    
                        cout << "Do you want to make a odd bet? Yes/No:" << endl;
                        cin >> OddBet;
                        if(tolower(OddBet[0]) == 'y') // If the user input starts with Y or y it would go inside   
                        {                               
                           odBetPL(btCOdd, sumOfDe, fDiceRw, chips, betChip, chipWon);               
                        }
                        
                        // Checks for the user has more then 0 chis to play
                        if(chips == 0)
                        {                           
                            cout << " " << endl;
                            cout << "You are broke and you can't play anymore" << endl;
                            exit(0);                 
                        }

                        cout << "Do you want to make a come bet? Yes/No:" << endl;
                        cin >> ComeBet;
                        for(ComeBet; tolower(ComeBet[0]) == 'y';) // If the user input starts with Y or y it would go inside   
                        {  
                            // Checks for the user has more then 0 chis to play
                            if(chips != 0) 
                            {
                                cout << "You have " << chips << " chips." << endl;
                                cout << "How much chips do you want to bet on your come bet:" << endl;
                                cin >> btChCome;

                                // Doesn't let the user to input more chips than he has
                                while(btChCome > chips)
                                {
                                    cout << "You don't have that many chips." << endl;
                                    cout << "You have " << chips << " chips." << endl;
                                    cout << "Enter an amount of chips that you have:" << endl;
                                    cin >> btChCome;
                                }      
                                         
                                sumOfDe = sumRolD(); // Roll the two dice and gets the sum of both of them
                                
                                sDiceRw =  sumOfDe;
                                cout << "Your come bet is set on " << sDiceRw << endl;
                                chips -= btChCome;
                                
                                // Checking if the rolled dice are equal to 7 or 11
                                if (sDiceRw == 7 ||  sDiceRw == 11)
                                {
                                    cout << "You won your bet" << endl;
                                    chipWon = btChCome * 2;
                                    chips += chipWon;
                                    cout << "You won " << chipWon << " chips and your total chips are " <<  chips << endl;
                                }
                                // Checking  if the rolled dice are equal to 2, 3, 12 
                                else if (sDiceRw == 2 || sDiceRw == 3 || sDiceRw == 12)
                                {
                                    cout << "You lost your bet" << endl;
                                    cout << "You lost " << btChCome << " chips and your total chips are " <<  chips << endl;
                                }
                                // Checking if the rolled dice are equal to every other number
                                else
                                {            
                                   do
                                   {
                                       sumOfDe = sumRolD(); // Roll the two dice and gets the sum of both of them
                                       
                                       cout << "The dice rowed " << sumOfDe << endl;                                     
                                       
                                       if(sumOfDe == fDiceRw) // Stop the loop when dice get the same number as the first one
                                       {
                                            break;
                                       } 

                                       if(sumOfDe == 7) // Stop the loop when dice get 7
                                       {
                                            break;
                                       }
                                       // Loop until the dice rows 7 or the first number
                                   }while(sumOfDe != sDiceRw || sumOfDe != 7);   
                                   
                                   // Checks if the first row is equal to 7
                                   if(sumOfDe == 7)
                                   {
                                       cout << "The dice rowed the same number as the first row" << endl;
                                       cout << "You lost your bet" << endl;
                                       cout << "You lost " << betChip << " chips and your total chips are " <<  chips << endl;
                                   }
                                  
                                   // Checks if the first row is second row is equal to the first one
                                   if(sumOfDe == sDiceRw)
                                   {
                                       cout << "You won your bet" << endl;
                                       chipWon = betChip * 2;
                                       chips += chipWon;
                                       cout << "You won " << chipWon << " chips and your total chips are " <<  chips << endl;
                                   }
                                }                                           
                            }
                            else
                            {
                                cout << "You don't have enough chips to bet for come bet" << endl;
                            }                               
                            break;
                        }                    

                        cout << " " << endl;
                        cout << "Rowing the dice until they get " << fDiceRw << " or 7" << endl;           
                        do
                        {
                            sumOfDe = sumRolD(); // Roll the two dice and gets the sum of both of them
                            
                            cout << "The dice rowed " << sumOfDe << endl;

                           // Stops the loop when second row is equal to the first one
                            if(sumOfDe == fDiceRw)
                            {
                                break;
                            } 

                            // Stop the loop first row is equal to 7
                            if(sumOfDe == 7)
                            {
                                break;
                            } 

                            // Loop until the dice rows 7 or the first row
                        }while(sumOfDe != fDiceRw || sumOfDe != 7);                                     

                        // // Checks if the first row is second row is equal to the first one
                        if(sumOfDe == fDiceRw && sumOfDe != 7)
                        {
                            cout << " " << endl;
                            cout << "The dice rowed the same number as the first row" << endl;
                            cout << "You won your bet" << endl;
                            chipWon = betChip * 2;
                            chips += chipWon;
                            cout << "You won " << chipWon << " chips and your total chips are " <<  chips << endl;
                        }

                        // Checks if the first row is equal to 7
                        if(sumOfDe == 7)
                        {
                            cout << " " << endl;
                            cout << "You lost your bet" << endl;
                            cout << "You lost " << betChip << " chips and your total chips are " <<  chips << endl;
                        }
                    }                                  
            break;       
                        
            // Don’t pass bets           
            case 2:               
                // Checks for the user has more then 0 chis to play
                if(chips == 0) 
                {
                    cout << " " << endl;
                    cout << "You are broke and you can't play anymore" << endl;
                    break;                 
                }
                
                
                cout << " " << endl;
                cout << "You have " << chips << " chips." << endl;
                cout << "How much chips do you want to bet:" << endl;

                cin >> betChip;
               // Doesn't let the user to input more chips than he has
                while(betChip > chips) 
                {
                    cout << " " << endl;
                    cout << "You don't have that many chips." << endl;
                    cout << "You have " << chips << " chips." << endl;
                    cout << "Enter an amount of chips that you have:" << endl;
                    cin >> betChip;
                }

                sumOfDe = sumRolD(); // Roll the two dice and gets the sum of both of them

                fDiceRw = sumOfDe;
                cout << " " << endl;
                cout << "The dice rowed " << fDiceRw << endl;
                chips -= betChip;

                // Checking  if the rolled dice are equal to 2, 3
                if (fDiceRw == 2 ||  fDiceRw == 3)
                {
                    cout << " " << endl;
                    cout << "You won your bet" << endl;
                    chipWon = betChip * 2;
                    chips += chipWon;
                    cout << "You won " << chipWon << " chips and your total chips are " <<  chips << endl;
                }
                // Checking  if the rolled dice are equal to 7, 11
                else if (fDiceRw == 7 || fDiceRw == 11)
                {
                    cout << " " << endl;
                    cout << "You lost your bet" << endl;
                    cout << "You lost " << betChip << " chips and your total chips are " <<  chips << endl;
                }     
                // Checking  if the rolled dice are equal to 12
                else if (fDiceRw == 12)
                {
                    cout << " " << endl;
                    cout << "It is a tie. You keep your bet." << endl;
                    chipWon = betChip;
                    chips += chipWon;
                    cout << "You have " << chips << " chips." << endl;
                }               
                // Go to point numbers and ask him if he want to make an odd or come bet
                else 
                {
                    cout << "This is one of the point numbers" << endl;
                    cout << " " << endl;                                    
                    cout << "Do you want to make a odd bet? Yes/No:" << endl;
                    cin >> OddBet;
                    if(tolower(OddBet[0]) == 'y') //// If the user input starts with Y or y it would go inside     
                    {   
                        // Checks for the user has more then 0 chis to play
                        odBetPL(btCOdd, sumOfDe, fDiceRw, chips, betChip, chipWon);                      
                    }
                    
                    // Checks if the user has more chips then 0 after the odd bet. If yes he can continue playing.
                    if(chips == 0)
                    {
                        stop = false;
                        if(stop == false)
                        {
                            exit(0);
                        }
                        cout << " " << endl;
                        cout << "You are broke and you can't play anymore" << endl;
                        break;                               
                    }

                    cout << "Do you want to make a come bet? Yes/No:" << endl;
                    cin >> ComeBet;
                    for(ComeBet; tolower(ComeBet[0]) == 'y';) // If the user input starts with Y or y it would go inside   
                    {                       
                        if(chips != 0) 
                        {
                            cout << "You have " << chips << " chips." << endl;
                            cout << "How much chips do you want to bet on your come bet:" << endl;
                            cin >> btChCome;

                            // Will lope if the user input more chips then he has. 
                            while(btChCome > chips)
                            {
                                cout << "You don't have that many chips." << endl;
                                cout << "You have " << chips << " chips." << endl;
                                cout << "Enter an amount of chips that you have:" << endl;
                                cin >> btChCome;
                            }    

                            if(chips == 0)
                            {
                                for (int i = 0; i < 1; i++) {
                                    cout << " " << endl;
                                    cout << "You are broke and you can't play anymore" << endl;
                                    break;   
                                }
                            }

                            sumOfDe = sumRolD(); // Roll the two dice and gets the sum of both of them

                            sDiceRw =  sumOfDe;
                            cout << "Your come bet is set on " << sDiceRw << endl;
                            chips -= btChCome;

                            if (sDiceRw == 7 ||  sDiceRw == 11)
                            {
                                cout << "You won your bet" << endl;
                                chipWon = btChCome * 2;
                                chips += chipWon;
                                cout << "You won " << chipWon << " chips and your total chips are " <<  chips << endl;
                                chips > begchip ? "Wow, you have more chips than you had in the beginning. Good job.\n" : "" ;
                            }
                            // Checking  if the rolled dice are equal to 2, 3, 12 
                            else if (sDiceRw == 2 || sDiceRw == 3 || sDiceRw == 12)
                            {
                                cout << "You lost your bet" << endl;
                                cout << "You lost " << btChCome << " chips and your total chips are " <<  chips << endl;
                            }
                            // I had a problem with this part because I could not make a working array.
                            // That's why I'm printing the dice ones here for the come bet and then for again for the past or don't pass line
                            else
                            {            
                               do
                               {
                                   sumOfDe = sumRolD(); // Roll the two dice and gets the sum of both of them

                                   cout << "The dice rowed " << sumOfDe << endl;

                                   // Stop the loop when dice get the same number as the first one
                                   if(sumOfDe == sDiceRw)
                                   {
                                       break;
                                   }  

                                   // Stop the loop when dice get 7
                                   if(sumOfDe == 7)
                                   {       
                                       break;
                                   } 

                                   // Loop until the dice rows 7 or the first number
                               }while(sumOfDe != sDiceRw || sumOfDe != 7);   

                               // Checks if the number that stop the top loop 7
                               if(sumOfDe == 7)
                               {
                                   cout << "The dice rowed the same number as the first row" << endl;
                                   cout << "You lost your bet" << endl;
                                   cout << "You lost " << betChip << " chips and your total chips are " <<  chips << endl;
                               }

                               // Checks if the number that stop the top loop is same number as the first one
                               if(sumOfDe == sDiceRw)
                               {
                                   cout << "You won your bet" << endl;
                                   chipWon = betChip * 2;
                                   chips += chipWon;
                                   cout << "You won " << chipWon << " chips and your total chips are " <<  chips << endl;
                               }
                            }                                           
                        }
                        else
                        {
                            cout << "You don't have enough chips to bet for come bet" << endl;
                        }                               
                        break;
                    }

                    result = pow(betChip, chipWon);
                    cout << " " << endl;
                    cout << "Rowing the dice until they get " << fDiceRw << " or 7" << endl;           
                    do
                    {
                        sumOfDe = sumRolD(); // Roll the two dice and gets the sum of both of them

                        cout << "The dice rowed " << sumOfDe << endl;

                       // Stop the loop when dice get the same number as the first one
                        if(sumOfDe == fDiceRw)
                        {
                            break;
                        } 

                        // Stop the loop when dice get 7
                        if(sumOfDe == 7)
                        {
                            break;
                        } 

                        // Loop until the dice rows 7 or the first number
                    }while(sumOfDe != fDiceRw || sumOfDe != 7); 

                    // Checks if the number that stop the top loop 7
                    if(sumOfDe == 7)
                    {
                        cout << " " << endl;
                        cout << "You won your bet" << endl;
                        chipWon = betChip * 2;
                        chips += chipWon;
                        cout << "You won " << chipWon << " chips and your total chips are " <<  chips << endl;
                    }

                    // Checks if the number that stop the top loop is same number as the first one
                    if(sumOfDe == fDiceRw && sumOfDe != 7)
                    {
                        cout << " " << endl;
                        cout << "The dice rowed the same number as the first row" << endl;
                        cout << "You lost your bet" << endl;
                        cout << "You lost " << betChip << " chips and your total chips are " <<  chips << endl;
                    }                   
                }                              
            break;
            
            case 3:              
                exit(0);  
                break;           
            default:
                cout << "You entered none of the above." << endl;                      
        }        
        plBetCh = 0;

        cout << "Would you like to play again? Yes/No: " << endl; 
        cin >> playAg;
        cout << " " << endl;
        // Checks if the first letter of the input of the user is Y/y. if yes do again.
    }while(tolower(playAg[0]) == 'y');
}


/** 
 * To shorten the code and make it easier to understand
 * @return  Rolls two dices and adds them together in one variable
 */
int sumRolD()
{  
    int diceOne = rand() % 6 + 1; // get a rand num between 1 and 6
    int diceTwo = rand() % 6 + 1; // get a rand num between 1 and 6     
    
    int sumOfDices = diceOne + diceTwo;
    return sumOfDices;  
}

void oddBet(int plBetCh, int btCOdd, int sumOfDe, int fDiceRw, int chips, float betChip, int chipWon)
{
    if(chips != 0)  // Checks for the user has more then 0 chis to play
    {
        cout << "You have " << chips << " chips." << endl;
        cout << "How much chips do you want to bet on your odd Bet:" << endl;
        cin >> btCOdd;
        cout << " " << endl;

        while(btCOdd > chips) // Doesn't let the user to input more chips than he has
        {
            cout << "You don't have that many chips." << endl;
            cout << "You have " << chips << " chips." << endl;
            cout << "Enter an amount of chips that you have:" << endl;
            cin >> btCOdd;
            cout << " " << endl;
        }

        sumOfDe = sumRolD(); // Roll the two dice and gets the sum of both of them

        fDiceRw =  sumOfDe;
        cout << "Your  bet is set on " << fDiceRw << endl;
        chips -= btCOdd;

        cout << " " << endl;
        cout << "Rowing the dice until they get " << fDiceRw << " or 7" << endl;

        // Loop until the dice rows 7 or the first number
        do
        {
            sumOfDe = sumRolD(); // Roll the two dice and gets the sum of both of them

            cout << "The dice rowed " << sumOfDe << endl;

            if(sumOfDe == fDiceRw) // Stop the loop when dice get the same number as the first one
            {
                break;
            } 

            if(sumOfDe == 7) // Stop the loop when dice get 7
            {
                break;
            }           
        }while(sumOfDe != fDiceRw || sumOfDe != 7); 

        // Odd bet on the pass line
        if(plBetCh == 1)
        {
            odBetPL(btCOdd, sumOfDe, fDiceRw, chips, betChip, chipWon);   
        }
        else
        {
            odbeDPL(btCOdd, sumOfDe, fDiceRw, chips, betChip, chipWon);
        }                                                      
    }
    else
    {
        cout << "You don't have enough chips to bet for odd bet" << endl;                    
    }
}

void odBetPL(int btCOdd, int sumOfDe, int fDiceRw, int chips, float betChip, int chipWon)
{
    if(sumOfDe == fDiceRw && sumOfDe != 7)
    {
        // Checking if the rolled dice are equal to 4 or 10
        if(sumOfDe == 4 || sumOfDe == 10) 
        {
            cout << " " << endl;
            cout << "The dice rowed the same number as the first row" << endl;
            cout << "You won your bet and your odd bet" << endl;
            chipWon = betChip * 2 + (btCOdd + (btCOdd * 1.75));
            chips += chipWon;
            cout << "You won " << chipWon << " chips and your total chips are " <<  chips << endl;
        }
        // Checking if the rolled dice are equal to 5 or 9
        else if(sumOfDe == 5 || sumOfDe == 9)
        {
            cout << " " << endl;
            cout << "The dice rowed the same number as the first row" << endl;
            cout << "You won your bet and your odd bet" << endl;
            chipWon = betChip * 2 + (btCOdd + (btCOdd * 1.5));
            chips += chipWon;
            cout << "You won " << chipWon << " chips and your total chips are " <<  chips << endl;
        }
        // Checking if the rolled dice are equal to every other number
        else 
        {
            cout << " " << endl;
            cout << "The dice rowed the same number as the first row" << endl;
            cout << "You won your bet and your odd bet" << endl;
            chipWon = betChip * 2 + (btCOdd + (btCOdd * 1.2));
            chips += chipWon;
            cout << "You won " << fixed << setprecision(1) << showpoint << chipWon << " chips and your total chips are " <<  chips << endl;
        }
    }

    if(sumOfDe == 7) // Checking if the rolled dice are equal to 7
    {
        cout << " " << endl;
        cout << "You lost your bet and your odd bet" << endl;
        cout << "You lost " << betChip + btCOdd << " chips and your total chips are " <<  chips << endl;
    }
}


void odbeDPL(int btCOdd, int sumOfDe, int fDiceRw, int chips, float betChip, int chipWon)
{
    if(sumOfDe == fDiceRw && sumOfDe != 7)
    {
        if(sumOfDe == 4 || sumOfDe == 10)
        {
            cout << " " << endl;
            cout << "You lost your , but you won the odd bet" << endl;
            chipWon = btCOdd + (btCOdd * 0.5);
            chips += chipWon;
            cout << "You lost " << betChip << "from your bet and won" + btCOdd << " chips from your odd bet. Your total chips are " <<  chips << endl;
        }
        else if(sumOfDe == 5 || sumOfDe == 9)
        {
            cout << " " << endl;
            cout << "You lost your , but you won the odd bet" << endl;
            chipWon = btCOdd + (btCOdd * 0.6);
            chips += chipWon;
            cout << "You lost " << betChip << "from your bet and won" + btCOdd << " chips from your odd bet. Your total chips are " <<  chips << endl;
        }
        else 
        {
            cout << " " << endl;
            cout << "You lost your , but you won the odd bet" << endl;
            chipWon = btCOdd + ((int)btCOdd * 0.8);
            chips += chipWon;
            cout << "You lost " << betChip << "from your bet and won" + btCOdd << " chips from your odd bet. Your total chips are " <<  chips << endl;
        }       
    }

    // Checks if the number that stop the top loop 7
    if(sumOfDe == 7)
    {         
        cout << " " << endl;
        cout << "The dice rowed the same number as the first row" << endl;
        cout << "You won your bet and your odd bet" << endl;
        chipWon = betChip * 2 + (btCOdd + (btCOdd * 1.75));
        chips += chipWon;
        cout << "You won " << chipWon << " chips and your total chips are " <<  chips << endl;
    }
}