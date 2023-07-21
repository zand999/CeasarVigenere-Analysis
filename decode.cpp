using namespace std;

#include <string>
#include <iostream>
#include <array>
#include <cmath>

double calculateIC(string);
//double calculateAverageIC(string,int);
string normalize(string);
string ceasar(string,int);
string ceasar(string,char);
string* alphabetSplitter(string s, int period);
int approxPeriod(double x);
int** getFrequencies(string *alphabets, int period);
double getFrequencyAverage(int**,int);
double getFrequencyAverage(int*);
double* calculateCF(string s);
string vigenereDecrypt(string cypher,string key);
//string assignment = "UPRCW IHSGY OXQJR IMXTW AXVEB DREGJ AFNIS EECAG SSBZR TVEZU RJCXT OGPCY OOACS EDBGF ZIFUB KVMZU FXCAD CAXGS FVNKM SGOCG FIOWN KSXTS ZNVIZ HUVME DSEZU LFMBL PIXWR MSPUS FJCCA IRMSR FINCZ CXSNI BXAHE LGXZC BESFG HLFIV ESYWO RPGBD SXUAR JUSAR GYWRS GSRZP MDNIH WAPRK HIDHU ZBKEQ NETEX ZGFUI FVRI";
const double letterfrequencies[] = {0.080,0.015,0.030,0.040,0.130,0.020,0.015,0.060,0.065,0.005,0.005,0.035,0.030,0.070,0.080,0.020,0.002,0.065,0.060,0.090,0.030,0.010,0.015,0.005,0.020,0.002};


const string letfrequencies = "HMMMHMMHHMMMMHHMLHHHMLLLLL";
int main(){


   string part2 = "UPRCW IHSGY OXQJR IMXTW AXVEB DREGJ AFNIS EECAG SSBZR TVEZU RJCXT OGPCY OOACS EDBGF ZIFUB KVMZU FXCAD CAXGS FVNKM SGOCG FIOWN KSXTS ZNVIZ HUVME DSEZU LFMBL PIXWR MSPUS FJCCA IRMSR FINCZ CXSNI BXAHE LGXZC BESFG HLFIV ESYWO RPGBD SXUAR JUSAR GYWRS GSRZP MDNIH WAPRK HIDHU ZBKEQ NETEX ZGFUI FVRI ";
    part2 = normalize(part2);
    string input;
    string *alphabets;
    int period = 6;
    int **frequencies;
    int average;

    cout << "Part 1: Cipher: ITSTYXYZRGQJTAJWXTRJYMNSLGJMNSIDTZ\n";
    cout << "Hit Enter\n";
    //cin.ignore(265,'\n');
    getline(cin,input);
    //input = normalize(input);
    double* CF = calculateCF("ITSTYXYZRGQJTAJWXTRJYMNSLGJMNSIDTZ");
    int top;
    double highest = 0.0;
    for (int i = 0; i < 26; i++)
    {
        if(CF[i] > highest){
            highest = CF[i];
            top = i;
        }
    }
    cout << "\nHighest:" << top << " Frequency:" << CF[top];
    cout <<"\nDecrypt with highest val: "<< ceasar("ITSTYXYZRGQJTAJWXTRJYMNSLGJMNSIDTZ", top);
    
    cout << "\n\nPart 2: Cipher: \n";
    
    cout << part2 << endl;
    cout << "Hit Enter\n";
    getline(cin,input);
    cout << "Caluclating Index of Coincidence:\n";
    double IC = calculateIC(part2);
    cout << "IC: "<< IC << "\n";
    cout << "Sugested Period "<< approxPeriod(IC) << "\n" /*<< "Choose Period:"*/;
    //cin >> period;
    cout << "Using Period of 6.";
    cout << "\nCreating Alphabets:";
    alphabets = alphabetSplitter(part2,period);
    delete CF;
    string guessedKey = "";
    for(int i = 0; i < period; i++){

        cout << "\n\nCorrelation Frequency for Alphabet: " << i;
        getline(cin,input);
        double* CF = calculateCF(alphabets[i]);
        highest = 0.0;
        top = 0;
        for (int j = 0; j < 26; j++)
        {
            if(CF[j] > highest){
                highest = CF[j];
                top = j;
            }
        }

        cout << "\nHighest:" << top << " Characher:" <<(char)(top + 65) <<" Frequency:" << CF[top];
        guessedKey += (char)(top + 65);
    }

    cout << "\nMost likely key: " << guessedKey;
    cout << "\nDecoded Text:\n";
    cout << vigenereDecrypt(part2,guessedKey);
    //cout << "\nCreating Alphabet Frequencies:";
    //frequencies = getFrequencies(alphabets, period);
    /*cout << "\nGeting letter frequency average:\n";
    average = getFrequencyAverage(frequencies,period);
    cout << "Average: " << average;*/

}

double* calculateCF(string s){

    double frequencies[26];
    double frequency = 0.0;
    double *COFs = new double[26];

    for (int i = 0; i < 26; i++)
    {
        frequencies[i] = 0;
    }
    

    for (int i = 0; i < s.length(); i++)
    {
        frequencies[s.at(i)-65] += 1;
    }
    cout << "Character Quanitiy\n";
    for (int i = 0; i < 26; i++)
    {
        
        cout << (char)(i+65) << ":"<< frequencies[i] << ",";
    }
    cout << "\nCharacter Frequencies\n";
    for (int i = 0; i < 26; i++)
    {
        //frequencies[i] = frequencies[i] / 26;
        frequencies[i] = frequencies[i] / s.length();
        cout <<  (char)(i+65) << ":"<< frequencies[i] << ",";
    }
    cout << "\nCoF for each shift/key:";
    for (int j = 0; j < 26; j++)
    {
        frequency = 0.0;
        for (int i = 0; i < 26; i++)
        {
            //cout << "\n";
            //cout <<i;
            //cout <<"frequencies[i]: " << frequencies[i] * letterfrequencies[(26 + i - 5)%26];
            frequency += frequencies[i] * letterfrequencies[(26 + i - j)%26];
        }
    COFs[j] = frequency;
    cout <<"\n"<< j << ":"<< (char)(j+65) <<":" << frequency;
    }

    int top5[] = {0,0,0,0,0};
    for (int i = 1; i < 5; i++)
    {
        for (int j = 25; j >= 0; j--)//
        {
            

        }
        
        
    }

    return COFs;

}

double calculateIC(string s){

    //check for zero length string
    

    if(s.length() == 0){
        return 0;
    }

    //set to uppercase
    s = normalize(s);


    double density = 0.0, result = 0.0,coincidence = 0.0;

    int frequencies[26];
    
    for (int i = 0; i < 26; i++)
    {
        frequencies[i] = 0.0;
    }
    
    
    for (int i = 0; i < s.length(); i++)
    {
        //cout << ((int)s.at(i) - 65) << ",";
        frequencies[ (s.at(i)) - 65 ] += 1;
    }

    /*cout << "\n{";
    for (int i = 0; i < 26; i++)
    {
        cout << frequencies[i] << ",";
    }
    cout << "}\n";*/

    for (int i=0; i < 26; i++) {
        coincidence += frequencies[i] * (frequencies[i] - 1);
    }

    return coincidence / (double)(s.length()*(s.length()-1));
    

}



string normalize(string s){

    for (int i = 0; i < s.length(); i++)
    {
        if(s.at(i)== ' ' || s.at(i)== '\n'){
            s.erase(s.begin() + i);
        }
        s[i] = toupper(s[i]);
    }
    
    return s;
}

string ceasar(string s, int offset){

    for (int i = 0; i < s.length(); i++)
    {
        s[i] -= offset;
        if(s[i] < 65){
            s[i] += 26;
        }
    }
    
    return s;

}
string ceasar(string s, char offset){

    
    return ceasar(s,toupper(offset) - 65);

}

string* alphabetSplitter(string s, int period){

    string *out = new string[period];

    cout << "\n{";

    for (int i = 0; i < period; i++)
    {
        //cout << "test";
        for(int j = i; j < s.length(); j += period){

            out[i] += s.at(j);

        }
        
        cout << out[i] << "\t" << calculateIC(out[i]) << ",\n";
    }
    cout << "\n";
    
    
    return out;

}

int approxPeriod(double x){
    //actual math to get period 
    //return round(1.190508 + (68.0421 - 1.190508)/(1.0 + pow((x/0.03528018),12.61607)));
    //correction as the this text does not follow convention
    return round(1.190508 + (68.0421 - 1.190508)/(1.0 + pow((x/0.03528018),12.61607)))-1;


}




int** getFrequencies(string *alphabets, int period){

    int **frequencies = new int*[period];
    //int average = 0;
    for (int i = 0; i < period; i++)
    {
        frequencies[i] = new int[26];
    }
    
    
    for (int i = 0; i <period; i++)
    {
        for (int j = 0; j < 26; j++)
        {
            frequencies[i][j] = 0;
            
        }
        
    }
    
    
    for (int i = 0; i <period ; i++)
    {
        
        for (int j = 0; j < alphabets[i].length(); j++)
        {
            
            frequencies[i][(alphabets[i].at(j))-65] +=1;
        }
        
    }
    
    cout << "\n";
    for (int i = 0; i < 26; i++)
    {
        cout << letfrequencies.at(i) << ",";
    }

    cout << "\n";
    for (int i = 0; i < 26; i++)
    {
        cout << (char)(i+65) << ",";
    }
    cout << "\n";
    for (int i = 0; i < 26; i++)
    {
        cout << "-";
    }
    cout << "\n";
    for (int i = 0; i <period; i++)
    {
        //average = 0;
        for (int j = 0; j < 26; j++)
        {
            //average += frequencies[i][j];
            cout<< frequencies[i][j]<< ",";
        }
        cout <</*"\tAverage: " << getFrequencyAverage(frequencies[i]) <<*/ "\n";
        
    }



    //cout << getFrequencyAverage(frequencies,period);

    

    return frequencies;

}

double getFrequencyAverage(int** frequencies,int period){

    int total = 0;
    //cout <<"test";

    for (int i = 0; i <period; i++)
    {
        for (int j = 0; j < 26; j++)
        {
            total += frequencies[i][j];
        }
        
        
    }
    return (double)total / (26*period);

}

double getFrequencyAverage(int* frequencies){

    int total = 0;
    //cout <<"test";

    
    for (int j = 0; j < 26; j++)
    {
        total += frequencies[j];
    }
        
        
    return (double)total/26;

}


string vigenereDecrypt(string cypher,string key){


    for (int i = 0; i < cypher.length(); )
    {
        for (int j = 0; j < key.length() && i < cypher.length(); j++,i++)
        {
            //cout << key[j];
            cypher[i] -= ((int)key[j] -65);
            if(cypher[i] < 65){
                cypher[i]+=26;
            }    
            
        }
        
        
    }
    
    return cypher;
}