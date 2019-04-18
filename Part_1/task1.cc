
/**@file */


#include <iostream>
#include <stack>
#include <string>
#include <time.h>
#include "task2.h"

using namespace std;

/**
 *@brief returns priority
 *
 *Takes an operand and returns its priotity based on precedence.
 *Return -1 for '(' so that it always remains on the stack until ')' is encountered in infix.
 *
 *@param c operand or '('
 *
 *@return priority value
 */ 
            
int priority(char c)          
{ 
	 switch(c)
	{ 
		case '>': return  0 ; 
		case 'V': return  1 ; 
		case '^': return  1 ; 
		case '~': return  2 ; 
		case '(': return -1 ; 			
	} 
}
 
stack <char> op ;/**<op-stack of operators*/ 
/**
 *@brief makes a stack of operands and builds postfix
 *
 *Takes each character from the infix,and ensures that elements are pushed and popped off the stack,and constructs postfix
 *
 *@param c character to be pushed onto stack
 *@param  postfix intermediate postfix expression which will be completely formed
 *
 *@return  returns the intermediate postfix expression
 */ 

string add_to_stack(char c,string postfix)              // to handle all charcters of infix other than alphabets
{  
	 //check if stack is empty
     if(op.empty())
      op.push(c) ;            
    
     //push onto stack if c is an operand
     else if(c!='(' && c!=')') 
     {

		/*
		 *priority function takes an operator as argument and returns its priority based on precedence	
		 *priority function is called to ensure proper postfix is generated,inspite of the user not giving a proper parenthesised formula
		 *Postfix will be generated based on precedence/associativity of the operators in that case
		 * 
		 * Ex:if infix is aVb>c postfix will be abVc> 	
		 */
	
		//check if priority of the operator c is higher than the previous operator on stack 
        if(priority(c)>priority(op.top()))
            op.push(c) ; 
                
         else 
         {
            postfix+=op.top() ; 
            op.pop() ; 
         	op.push(c) ; 
         }
         
     }
     
    //push if c is '(' 
    else if(c=='(')
     {
         op.push(c) ; 
     }
     
     //pop all the elements until you pop off '('
     else if(c==')')                         
     { 
         while(op.top()!='(')
         {  
             postfix+=op.top() ; 
             op.pop() ;                        
         }
         
         op.pop() ;// pop the '('  
     }

      return postfix;
}

/**
 *@brief This function takes infix and returns a corresponding postfix
 *
 *@param infix expression which is input
 *
 *@return  postfix expression of the given infix
 */

string to_postfix(string infix)
{     
     string::iterator it;/**<a string iterator */
     string postfix;/**<postfix expression to be returned */
     
     //iterate over each character of the infix
     for(it=infix.begin() ;it!=infix.end() ;it++)
     { 
       //if character is a literal then concatenate to postfix 
       if(*it>='a' && *it<='z')
            postfix+=*it ; 
       //else call function add     
        else 
            postfix=add_to_stack(*it,postfix) ; 
          
    }
      
     //pop all elements remaining in the stack
     while(!op.empty())                             
     {   
         if(op.top()!='(' && op.top()!=')')
         postfix+=op.top(); 
          
            op.pop() ;
              
     }
       
	return postfix;
}

/**
 *@brief main function takes infix and outputs postfix,traverses parse tree to print back infix
 *
 *Program starts here.
 *An infix is taken from the user ,and a postfix is generated. 
 *Parse tree is made from postfix and inorder traversal is made to get back infix. 
 *If both the input infix and the infix from traversal of parsetree match then the formula is VALID and prints "MATCHING". 
 *Else if both do not match then  the function prints "NOTMATCHING" which indicates an invalid formula.
 *
 *@see to_postfix
 *@see add_to_stack
 *@see priority
 *@warning input is to be well parenthesised
 */

 
int main()
{ 
  	 string infix;/**<infix - infix expression to be input from the user */
  	 string postfix; /**<postfix - postfix expression to be generated */
     
     cout<<"Input(well parenthesised formula):";
     cin>>infix;
     
     clock_t start1 = clock();//to note the  time taken before calling function
     
     //call to_postfix function to generate postfix  
     postfix=to_postfix(infix);
            
 	 clock_t stop1 = clock();//to note the  time taken after calling function    

	 double elapsed1 = (double)(stop1 - start1) * 1000.0 / CLOCKS_PER_SEC;
            
     clock_t start2 = clock();//to note the  time taken before calling function
     	
 	 //call task2 to make a parse tree and traverse to get infix back
     string infix2=make_parsetree(postfix); /**<infix expression after traversing the parse tree made from the postfix*/
     
 	 clock_t stop2 = clock();//to note the  time taken after calling function
 	 
 	 double elapsed2 = (double)(stop2 - start2) * 1000.0 / CLOCKS_PER_SEC;//calculating time elapsed   


     // if both infix expressions are not the same
     if(infix2!=infix)
	 {
			cout<<"infix:"<<infix ; 
    		cout<<endl <<"postfix:"<< postfix<<endl ;
    		cout<<"infix after traversing postfix:"<<infix2<<endl;
    		cout<<"ERROR:NOT MATCHING"<<endl;
    		cout<<"Recheck infix"<<endl;  		
			cout<<"NOTE:Input should be fully parenthesised"<<endl;
			cout<<"Time for generating postfix:"<<elapsed1<<endl;
			cout<<"Time for making and traversing parse tree:"<<elapsed2<<endl;
	 }    
     
     // if both infix expressions are not the same
     else
     {
			cout<<"infix:"<<infix ; 
    		cout<<endl <<"postfix:"<< postfix<<endl ;
    		cout<<"infix after traversing postfix:"<<infix2<<endl;
    		cout<<"MATCHING"<<endl;
    		cout<<"Time for generating postfix:"<<elapsed1<<endl;
			cout<<"Time for making and traversing parse tree:"<<elapsed2<<endl;
    	
     }
   	 return 0;
}

