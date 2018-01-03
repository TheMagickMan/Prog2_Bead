#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <stack>
#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <queue>
#include <algorithm>
#include <deque>
#include <utility>
#include <cctype>

using namespace std;


struct darab{
    string nev;
    deque<string> lkod;
    //ha vmi kell meg ide irjatok batran;
};


struct szoveg { //szerintem a structban inkább egy-egy aritmetikai utasításnak kéne csak lenine, nem az egész kódnak
    string fnev;
    vector<darab> komplett;
    vector<pair<bool, string> >registers;
    string gkod;
    szoveg(int regnum){
        vector<pair<bool, string> >registers(regnum, make_pair(0, ""));
    }
};

/*struct sor{ //lehet így csinálom majd, még nem biztos
    string valtozonev;
    stack<string> lkod;
    string atirt;
    int regiszter; //0, ha memóriában van tárolva
    int memo; //0, ha regiszterben van tárolva
};*/

/*void lengyel (szoveg &pelda){
    ifstream f,g;
    f.open("proba.txt");
    g.open("proba.txt");
    string aktu;
    string eredet;
    char szam;
    darab elso;
    string vissza;
    stack<char> verem;
    while (f.good()){
        elso.lkod=deque<string>();
        getline(g,eredet,';');
        getline(f,aktu,'=');
        elso.nev=aktu;
        szam='.';
        while (szam!=';' ){
            f >> szam;
            if (szam=='*' || szam=='/' ){
                while (!verem.empty() && verem.top()!='(' && verem.top()!='+' && verem.top()!='-'){
                    vissza=verem.top();
                    elso.lkod.push_back(vissza);
                    verem.pop();
                }
                verem.push(szam);
            }
            else{
                if (szam=='+' || szam=='-' ){
                    while (!verem.empty() && verem.top()!='(' ){
                        vissza=verem.top();
                        elso.lkod.push_back(vissza);
                        verem.pop();
                    }
                    verem.push(szam);
                }
                else{
                    if (szam==')'){
                        while (verem.top()!='('){
                            vissza=verem.top();
                            elso.lkod.push_back(vissza);
                            verem.pop();
                        }
                        verem.pop();
                    }
                    else{
                        if (szam=='('){
                            verem.push('(');
                        }
                        else{
                            if (szam==';'){}
                            else{
                                vissza=szam;
                                elso.lkod.push_back(vissza);
                            }
                        }
                    }
                }
            }
        }
        while (!verem.empty()){
            vissza=verem.top();
            elso.lkod.push_back(vissza);
            verem.pop();
        }
    pelda.komplett.push_back(elso);
    f >> ws;
    }
    deque<string> test = elso.lkod;
    while(!test.empty()){
        cout << test.front();
        test.pop_front();
    }
}*/





void regiszteres (szoveg &pelda){
    for(darab d : pelda.komplett){
        deque<string> current = d.lkod;
        queue<string> operands;
        while(!current.empty()){
            string temp;
            if(! (isdigit(current.front()[0]) || isalpha(current.front()[0])) && ! current.front().empty()){
                string op1 = operands.front();
                operands.pop();
                string op2 = operands.front();
                operands.pop();
                int op1_reg = distance(pelda.registers.begin(), find_if(pelda.registers.begin(), pelda.registers.end(),
                    [op1](const pair<bool,string>& elem) {return op1.compare(elem.second)==0;}))+1;
                int op2_reg = distance(pelda.registers.begin(), find_if(pelda.registers.begin(), pelda.registers.end(),
                    [op2](const pair<bool,string>& elem) {return op2.compare(elem.second)==0;}))+1;
                string utasitas = "reg[" + to_string(op1_reg)+"] " + current.front() + " reg["+to_string(op2_reg) + "]";
                for(int i = 0; i < pelda.registers.size(); i++){
                    if(pelda.registers[i].first == 0){
                        pelda.registers[i].first = true;
                        pelda.registers[i].second = utasitas;
                        temp += "reg[" + to_string(i+1) + "]";
                        operands.push(utasitas);
                        break;
                    }
                }
                temp += " = " + utasitas + "\n";
                current.pop_front();
            }
            else if(!current.front().empty() && !isalnum(current.front()[0])){
                for(int i = 0; i < pelda.registers.size(); i++){
                    if(pelda.registers[i].first == 0){
                        pelda.registers[i].first = true;
                        pelda.registers[i].second = current.front();
                        temp+="reg["+to_string(i+1)+"] = "+current.front()+"\n";
                        operands.push(current.front());
                        break;
                    }
                }
                current.pop_front();
            }
            pelda.gkod += temp;
        }
    }
    cout << pelda.gkod;
}



void gepikod (szoveg &pelda)

{
//Laci a kapott gépi kódot, kiszámolja:
//eredmény , adott példákkal:  a=1; b=2; c=3; d=4; e=5;   erre lesz VALAMI=4, gepivel meg simával is
}


int main()
{
    szoveg pelda(10);
    pelda.fnev="proba.txt";
    //lengyel(pelda);
    deque<string> kod;
    kod.push_back("a");
    kod.push_back("b");
    kod.push_back("+");
    kod.push_back("3");
    kod.push_back("*");
    darab egy;
    egy.nev="";
    egy.lkod = kod;
    pelda.komplett.push_back(egy);
    regiszteres(pelda);
    //gepikod(pelda);
    return 0;
}
