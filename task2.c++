#include<iostream>
#include<string>
#include<stack>

using namespace std;

class node
{
	public:
	
	node* left;
	node* right;	
	char ch;
	
	node(node* le,node* ri,char c)
	{
		left=le;
		right=ri;
		ch=c;
	}
	
	

};

void traverse(node * root)
{	
	cout<<"(";
	
	if(root->left!=NULL)
	{
		traverse(root->left);		
	}
	
	
	cout<<root->ch;
	
	if(root->right!=NULL)
	{
		traverse(root->right);		
	}
	
	cout<<")";
	
	return;
}


int main()
{
	string postfix;
	cin>>postfix;
	
	
	stack <node*> nd;	
	node *root=NULL;	
	for(int i=0;i<postfix.length();i++)
	{
		char ch=postfix[i];
		node *address= new node(NULL,NULL,ch);
		
		if(ch>='a'&&ch<='z')
		{
			nd.push(address);	
		}
		
		else if(ch=='~')
		{
			address->right=nd.top();
			nd.pop();
			nd.push(address);		
		}
		
		else 
		{
			address->right=nd.top();
			nd.pop();
			address->left=nd.top();
			nd.pop();
			nd.push(address);
		}
		
		root=address;		
	}
	
	
	traverse(root);	
	
	return 0;
}
