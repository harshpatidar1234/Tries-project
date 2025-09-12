#include<bits/stdc++.h>
#include<stdio.h>
using namespace std;
//numChild denotes the number of children assigned for each TriNode
int numChild=10;
// start tells the starting character of the dictionary/ phone directory
char start='0';
// del_yes tells whether the string is deleted or not
bool del_yes=true;
// This data structure stores the string character after character
class TrieNode{
    public:
    //data represents the character stored in the node
    char data;
    // Children stores the remaining string excluding the first character of the input string
    TrieNode** children;
    //isTerminal tells whether this node is ending of a word or not
    bool isTerminal;
    int number_of_children;
    // number_of_children tells the number of children so far of the node
    //Constructor called for the creation of new Node
    TrieNode(char x){
        data=x;
        children=new TrieNode*[numChild];
        // Initializing the children of new Node with NULL
        for(int i=0;i<numChild;i++){
            children[i]=NULL;
        }
        number_of_children=0;
        isTerminal=false;
    }
};
// Trie represents the the data structure which stores the Trienode as root and performs further operations 
class Trie{
    public:
    TrieNode* root;
    Trie(){
        //This root is just for kepping the top of the trie reserved
        root=new TrieNode('\0');
    }
    // Keeping the functions private which we don't want to be accessible to the users
    private:
    // This insert function uses recursion
    void insert(TrieNode* root,string a){
        // If the string is fully inserted then the isTerminal of last character node is changed to true
        if(a.size()==0){
            root->isTerminal=true;
            return;
        }
        // i is the index representing the first character of the input string
        int i=a[0]-start;
        if(root->children[i]==NULL){
            root->number_of_children++;
            // Creating new node as the ith child is NULL 
            root->children[i]=new TrieNode(a[0]);
        }
        // calling recursion on the rest of the string
        insert(root->children[i],a.substr(1));
    }
    // search_node returns the node of the last characeter of the input string is the string is present else it returns NULL
    TrieNode* search_node(TrieNode* root,string a){
        if(a.size()==0){
            return root;
        }
        int i=a[0]-start;
        // returning NULL if the string is not present
        if(root->children[i]==NULL){
            return NULL;
        }
        // calling recursion on the rest of the string
        return search_node(root->children[i],a.substr(1));
    }
    //Returns true if the string is present else returns false
    bool search(TrieNode* root,string a){
        if(a.size()==0){
            // If the string is present then we check whether the last character is an ending character of a string or not
            return root->isTerminal;
        }
        int i=a[0]-start;
        if(root->children[i]==NULL){
            return false;
        }
        // calling recursion on the rest of the string as the string till now is present
        return search(root->children[i],a.substr(1));
    }
    // This function prints all the strings inserted which have a prefix string a
    void auto_complete(TrieNode* root,string a){
        if(root==NULL){
            return;
        }

        if(root->isTerminal){
            cout<<a<<endl;
        }
        if(a.size()==0){
            return;
        }
        for(int i=0;i<numChild;i++){
            // appending the character corresponding to ith child and sending the resulting string to the recursion call on ith children
            char c=start+i;
            string b=a+c;
            auto_complete(root->children[i],b);
        }
    }
    // del function deletes the input string from the storage if the string is present else it just returns without doing any change 
    void del(TrieNode* root,string a){
        if(root==NULL){
            //String is not present then we just return
            del_yes=false;
            return;
        }
        if(a.size()==0){
            if(!root->isTerminal){
                del_yes=false;
            }
            //The word gets deleted if isTerminal is changed to false
            root->isTerminal=false;
            return;
        }
        int i=a[0]-start;
        del(root->children[i],a.substr(1));
        // Cheacking if extra space if acquired after the deletion of string
        if(root->children[i]!=NULL){
            TrieNode* child=root->children[i];
            // if the child has no children and it is not ending of a string then this means that it is of no use and acquiring extra space so we replace it with NULL
            if(child->number_of_children==0 && !child->isTerminal){
                root->number_of_children--;
                delete(root->children[i]);
                root->children[i]=NULL;
            }
        }
        
    }
    // public functions are accessed by the user
    public:
    void insert(string a){
        insert(root,a);
    }
    bool search(string a){
        return search(root,a);
    }
    void auto_complete(string a){
        TrieNode* x=search_node(root,a);
        if(x==NULL){
            cout<<"No such string exists"<<endl;
            return;
        }
        auto_complete(x,a);
    }
    void del(string a){
        del(root,a);
    }
    // print_all prints all the strings inserted so far
    void print_all(){
        for(int i=0;i<numChild;i++){
            char x=start+i;
            string s="";
            s+=x;
            auto_complete(root->children[i],s);
        }
    }
};
int main(){
    
    int x;
    cout<<"What do you want to implement:\n1)Dictionary\n2)Number phone directory\n";
    cin>>x;
    if(x==1){
        numChild=26;
        start='a';
    }
    Trie* root=new Trie;
    if(x==1){
        //Storing some words in the dictionary using the attached text file
        ifstream inFile;
        inFile.open("words.txt");
        string s;
        while(getline(inFile, s)) {
        // insertion of string s in trie data structure
        root->insert(s);
        }
    }
    if(x==2){
        //Storing some numbers in the phone directory using the attached text file
        ifstream inFile;
        inFile.open("numbers.txt");
        string s;
        while(getline(inFile, s)){
            // insertion of string s in trie data structure
            root->insert(s);
        }
    }
    int t=0;
    while(t!=6){
        cout<<"Choose out of the following options:\n1. Insert a string\n2. Search a string\n3. Auto complete a string\n4. Delete a string\n5. Print all the input strings\n6. Quit\n";
        cin>>t;
        if(t==1){
            cout<<"Enter the string to be inserted\n";
            string s;
            cin>>s;
            root->insert(s);
        }
        else if(t==2){
            cout<<"Enter the string to be searched\n";
            string s;
            cin>>s;
            bool yes=root->search(s);
            if(yes){
                cout<<"String present"<<endl;
            }
            else{
                cout<<"String Not present"<<endl;
            }
        }
        else if(t==3){
            cout<<"Enter the string to be auto completed\n";
            string s;
            cin>>s;
            cout<<"The strings with prefix "<<s<<" are:"<<endl;
            root->auto_complete(s);
        }
        else if(t==4){
            cout<<"Enter the string to be deleted\n";
            string s;
            cin>>s;
            del_yes=true;
            root->del(s);
            if(del_yes){
                cout<<"String deleted"<<endl;
            }
            else{
                cout<<"No such string exist"<<endl;
            }
        }
        else if(t==5){
            root->print_all();
        }
        else if(t==6){
         break;   
        }
    }
    
    return 0;
}