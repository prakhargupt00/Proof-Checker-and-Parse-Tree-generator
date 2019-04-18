/**@file */

#include <iostream>
#include <stack>
#include <string>

/**
 *@brief Parse tree node for each symbol
 */
class node
{
	public:
	
	node* left;/**<left - address of left child*/
	node* right;/**<right - address of right child*/	
	char ch;/**<ch - character in the node*/
	
	
	/**
	 *constructor for node
	 *
	 *@param le left child address
	 *@param ri right child address
	 *@param c character to be put in the node
	 */
	node(node* le,node* ri,char c)
	{
		left=le;
		right=ri;
		ch=c;
	}
	
};

/**
 *@brief traverse the parsetree
 *
 *This function recursively calls itself and completes an inorder traversal of the parsetree
 *
 *@param root root of the subchild
 *@param output alias of the output string(infix after traversing)
 *
 *@return output the infix after traversing parsetree
 */
std :: string traverse(node * root,std :: string &output)
{	
	//check if this is a leaf node
	if(root->left==NULL&&root->right==NULL)
		output+=root->ch;		
	
	//check if the node contains'~'
	else if(root->ch == '~')
	{   
		//check if the right child  is '~'  (this block is to only ensure a well parenthesised output)
		if(root->right->ch=='~')
		{
			//adding character in node to the output(infix)		
			output+=root->ch;
			
			/*
			 *add additional set of parenthesis
			 * Ex:~(~p)	is ensured not ~~p		
			 */
			output+="(";			
			traverse(root->right,output);//recursive call 			
			output+=")";
		}
			
		else
		{
			output+=root->ch;			
			traverse(root->right,output);//recursive call
		}
	}
	
	//if it is some other operator than '~'
	else
	{
		
		output+="(";
		if(root->left!=NULL)
		{
			traverse(root->left,output);//recursive call		
		}
	
		output+=root->ch;
		
	
		if(root->right!=NULL)
		{
			traverse(root->right,output);//recursive call		
		}
		
		output+=")";
		
	}	
	
	return output;
}

/**
 *@brief makes a parsetree 
 *
 *takes postfix expression ,creates nodes and constructs a parse tree
 *
 *@param postfix postfix from which parse tree is to be made
 *
 *@return infix2 infix expression after traversing the parsetree 
 */
std :: string make_parsetree(std :: string postfix)
{	
	std :: stack <node*> nd;/**<stack of addresses of each node */	
	node *root=NULL;/**<root of the parsetree*/
	
	//iterate over postfix
	for(int i=0;i<postfix.length();i++)
	{
		char ch=postfix[i];
		
		//create a node for each symbol in the postfix 
		node *address= new node(NULL,NULL,ch);
		//if character then push its address onto the stack
		if(ch>='a'&&ch<='z')
		{
			nd.push(address);	
		}
		
		//make the topmost symbol on the stack as '~'s right child		
		else if(ch=='~')
		{
			address->right=nd.top();
			nd.pop();
			nd.push(address);		
		}
		
		//make the top 2 symbols on the stack present node's right and left child
		else 
		{
			address->right=nd.top();
			nd.pop();
			address->left=nd.top();
			nd.pop();
			nd.push(address);
		}
		
		//update root
		root=address;		
	}
	
	//ensure root is not a bracket
	if(root->ch==')'||root->ch=='(')		
		return "Not well parenthesised";		
	
	else
	{
		std :: string output;/*<string to store infix*/		
		std :: string infix2=traverse(root,output);/*<final infix after completing traversal*/		
		return infix2;
	}
	
} 

