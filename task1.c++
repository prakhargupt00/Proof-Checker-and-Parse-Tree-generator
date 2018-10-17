/// logic assignment task 1 

#include <iostream>
#include <stack>
#include <string>
using namespace std;

stack <char> op ;           /// op is stack of symbols including '(' but not ')'
string postfix ,infix  ;    // infix is input and postfix is final output 
 
  int priority(char c)          /// priority is to calculate priority of sign since we are not adding ')' to op so need priority of it 
 { 
     switch(c)
    { case '>': return 0 ; 
     case 'V': return 1 ; 
     case '^': return 1 ; 
     case '~': return 2 ; 
     case '(': return -1 ; 
        
    }
     
 }
 
 void add(char c)              // to handle all charcters of infix other than alphabets
 {  
     if(op.empty())
      op.push(c) ;           // if empty then just add in op 
    
      
     else if(c!='(' && c!=')') 
     {
         if(priority(c)>priority(op.top()))
                op.push(c) ; 
                
         else if(priority(c)<=priority(op.top()))
            {
                postfix+=op.top() ; 
                op.pop() ; 
                op.push(c) ; 
            }
         
     }
     
    else if(c=='(')
     {
         op.push(c) ; 
     }
     
     else if(c==')')                         // if ')' then print all values till its associated '('
     { 
         while(op.top()!='(')
         {  
             postfix+=op.top() ; 
             op.pop() ;                        // adding symbol in postfix and then popping it
         }
         
         op.pop() ;                            /// pop the '('  
     }

      
 }
 
int main()
{ 
     
     cin>>infix ; 
     
     for(auto it=infix.begin() ;it!=infix.end() ;it++)
     { 
          if(*it>='a' && *it<='z')
            postfix+=*it ; 
            
        else 
            add(*it) ; 
          
    }
      
     
     while(!op.empty())                            /// at last if we have something other than ( or ) left than add in postfix 
     {   
         if(op.top()!='(' && op.top()!=')')
          postfix+=op.top() ; 
          
            op.pop() ;
              
     }
     
     cout<<"infix   : "<<infix ; 
     cout<<endl <<"postfix : "<< postfix<<endl ; 
     
   
}

