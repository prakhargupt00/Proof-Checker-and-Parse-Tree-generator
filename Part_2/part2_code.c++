#include <vector>
#include <iostream> 
#include <string>                          /// part2 of logic assignment .... it checks that each and every line is correct or not and finally whether the final sequent derived from above lines  is valid or not  regarding the rules applied or not 
using namespace std;                         

int x=0 ; /** in order to check if any of proof lines is incorrect ,if so is case increase value of x by 1 */

string sub(string s)                        /**  "sub"  function taking returns equivalent substring of that line  after removing the rules applied on that    */
{
    if(s.find("/P")!=string::npos)
      return s.substr(0,s.length()-2) ;    /// if premise is there  then remove last 2 characters from string 
     
    else                                  /// else you   should return substring till first occurence  of slash(not including it ofcourse )  
     return s.substr(0,s.find("/")) ; 
}

void and_intro(string str,vector<string> s)                         /**  function to take care care of and introduction  rule        */
{
    size_t f= str.find("/^i") ;                                    // first occurence  of '/'
    size_t g =str.find("/",f+4) ;                                  // third occurence of '/'
    string  ch=str.substr(f+4,g-f-4) ;
    string sh=str.substr(g+1) ; 
    
    string t='('+ sub(s[stoi(ch)])+'^' + sub(s[stoi(sh)]) +')'  ;  // making the formula using the rule by ourself 
  
   if(str.substr(0,f).compare(t)!=0)                               // now comparing the formula made by ourself  with given final formula given in input
     x++ ; 
     
 }


void  and_elim(string str,vector<string> s)           /** function to take care of and elimination rule */
{
    size_t f= str.find("/^e") ;                      // first occurence of '/'
    size_t g =str.find("/",f+4) ;                   // third occurence of '/'
    string  ch=str.substr(f+4,g-f-4) ;             // string between the 2 slashes giving the typeof and elimination 
    string sh=str.substr(g+1) ;                   // string after last slash giving line no on which rule is applied 
    
    int count=0 ,i ;                            // count variable to count the  no of '('

    string t=sub(s[stoi(sh)]) ;                // corresponding substring of line no at 'sh' .. stoi(sh) returns the integer equivalent of sh  
   
    
     for( i=0 ;i<int(t.length());i++)         // here in for loop logic is that stop when count of '(' is one and we reached '^' 
     { 
           if(t[i]=='(')                     // if '(' is there increase count by 1                  
           {                                    
            count++ ; 
           }

           else if(t[i]==')')               // if ')' is ther then we decrease count by 1 as we came out of that bracket
           {
                count-- ; 
           }

           if(count==1 && t[i]=='^')            // we got our required conditon so break i.e count is 1 and we got a '^'     
           {
               break ; 
           }

     }                                              
                                                                 // i tells the position of concerned '^'

 
    if(stoi(ch)==1)                                              // if and elimnation 1 is done 
    {
        if(sub(str).compare(t.substr(1,i-1))!=0)                // comparing  subtring of str i.e formula given  with  string we get after aplying and elimination 1by ourself  
            x++ ; 
    }

    if(stoi(ch)==2)                                            // if and elimination 2 is done                 
    {
        if(sub(str).compare(t.substr(i+1,t.length()-i-2))!=0) // comparing  subtring of str i.e formula given  with  string we get after aplying and elimination 2 by ourself
            x++ ; 
    }

}


void or_intro(string str,vector<string> s)           /** function to take care of or introduction  rule */
{
    size_t f= str.find("/Vi") ;                     // first occurence of '/'

    size_t g =str.find("/",f+4) ;                   // third occurence of '/'
    string  ch=str.substr(f+4,g-f-4) ;              // string between the 2 slashes giving the type of or introduction 
    string sh=str.substr(g+1) ;                    // string after last slash giving line no on which rule is applied
    
    int count=0 ;                                 // count variable to count the  no of '('
    
    
    string t=sub(s[stoi(sh)]) ;                    // corresponding substring of line no at 'sh' .. stoi(sh) returns the integer equivalent of sh  

    

     int i ;                                        // i to know position  of concerned 'V' 
     
     for( i=0 ;i<(int)f;i++)                     // loop iterates till first occurence of  with position of "/" 
     { 
           if(str[i]=='(')                       // if '(' is there we increase count  by 1 
           {
            count++ ; 
           }

           else if(str[i]==')')                  // if ')' is ther then we decrease count by 1 as we came out of that bracket  
           {
                count-- ; 
           }

           if(count==1 && str[i]=='V')          // we got our required conditon so break i.e count is 1 and we got a 'V'
           {
               break ; 
           }

     }


    if(stoi(ch)==1)                               // if or introduction  1 is done 
    { 
        if(t.compare(str.substr(1,i-1))!=0)       // comparing  subtring of str i.e formula given  with  string we get after aplying or intro 1by ourself
            x++ ; 
            
       
    }

    if(stoi(ch)==2)                                // if or introduction  2 is done 
    {
        if(t.compare(str.substr(i+1,f-i-2))!=0)   //// comparing  subtring of str i.e formula given  with  string we get after aplying or intro 2by ourself
            x++ ; 
    }
    
    
}



void impl_eli(string str ,vector<string> s)                     /** function to take care of the implication elimination rule */                
{ 
    size_t f= str.find("/>e") ;  // first occurence of '/'
    
    size_t g =str.find("/",f+4) ;
    string  ch=str.substr(f+4,g-f-4) ;            
    string sh=str.substr(g+1) ; 
    

    string t='(' + sub(s[stoi(sh)])+'>'+  str.substr(0,f)+')'  ; // making our own string 
  
   if(t.compare(sub(s[stoi(ch)]))!=0)                 // now checking with given one 
     x++ ; 

}

 void modus_tollens(string str,vector<string> s)  /** function to take care of the modus tollens rule */
{
    size_t f= str.find("/MT") ;  // first occurence of '/'

    size_t g =str.find("/",f+4) ;
    string  ch=str.substr(f+4,g-f-4) ;
    string sh=str.substr(g+1) ;                    // all same as before .. 
    
    int count=0 ;
    
    string t=sub(s[stoi(ch)]) ;          // gets substring corresponding to the first mentioned line in the rule 
    string u=sub(s[stoi(sh)]) ;         // gets substring corresponding to  the second mentioned line in the rule 
    

     int i ;        // to get position of '>'
     
     for( i=0 ;i<(int)t.length();i++)                   
     { 
           if(t[i]=='(')
           {
            count++ ; 
           }

           else if(t[i]==')')
           {
                count-- ; 
           }

           if(count==1 && t[i]=='>')      // checking if count is one and we reached '>'
           {
               break ; 
           }

     }                           //  comparing  subtring of str i.e formula given  with  string we get after aplying modes tollens by ourself
        
        if(i+1>=t.length())
         x++ ; 

        else if((u.compare('~'+t.substr(i+1,t.length()-i-2))!=0)||(sub(str).compare('~' + str.substr(1,i-1))!=0))
            x++ ;
        else 
         {;}
        
            
      
}

/** @brief main function is takes the input  and calls different functions corresponding to the diff. rules applied  then it  checks if variable x is 0 if it is then it is a valid proof otherwise not .*/

int main()
{    
    int n;                              /**n denotes the no of lines of proof */
    cin>>n ; 
    
    vector <string> s  ;                /** vector of string for storing all given lines  of proof */
   
   s.push_back("not req") ;             // just to take care of  s[0] ..so that s[0] won't store any of proof lines ...as we generally start proof lines from index 1 not from  index 0 
   
   for(int i=1 ;i<=n ;i++)              // loop to take input of proof lines 
   {   string p ; 
       cin>>p  ; 
        
        s.push_back(p) ;  
      
   }
  
      for(int i=1 ;i<=n ;i++)                    // now checking proof line by line 
   { 
        
        if(s[i].find("/P")!=string::npos)        // if its premise no need to check for any proof rules given it is according to our assumptions
          continue ; 
          
          
        else if(s[i].find("/^i")!=string::npos)  // to find if ^i is there call function correspoding to and intro rule 
        {
            and_intro(s[i],s) ; 
        }
      
        else if(s[i].find("/^e")!=string::npos)  // if ^e is there call function  corresponding to the and elim rule  
        {
             and_elim(s[i],s) ; 
        }
        
        else if(s[i].find("/Vi")!=string::npos)   // if Vi is there call function  corresponding to the or intro rule
        {
            or_intro(s[i],s) ; 
        }
          
        else if(s[i].find("/>e")!=string::npos)   // if >e is ther call  function corresponding to the implication elim rule 
            impl_eli(s[i],s)  ;
        
            
         else if(s[i].find("/MT")!=string::npos)  // if modus tollens rule is  is there call its corresponding function 
             {
                 modus_tollens(s[i],s) ;   
             }

   }
   
   if(x==0)
   cout<<" Valid proof "  ;     /// if x=0 means no rule has been violated and everything is in correct order also the final sequent is valid so output valid proof 
   
   else if(x>0)                /// if x>0 means atleast on one line  of proof is wrong or not written in order  so output invalid proof
   cout<<" Invalid proof " ; 
   
    return 0;
}




