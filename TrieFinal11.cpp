#include<iostream>
#include<string>
#include<cstdio>
#include<cstdlib>
#include<fstream>
#include<algorithm>
#include<vector>
#include <ctime> //for clocking the code

//===========================================================================
#include <cstring> //because dirent stores dir names in char arrays...i.e. c type strings
#include <dirent.h> //format of directory entries
#include <sstream> //string stream
DIR *dpdf;
struct dirent *epdf;
//==================================================================================================
#define NUM_ALPHABET 26
#define ChartoIndex(c) ((int)c-(int)'a')
const int NUM_FILES=100;
//---------trie node--------============================================================================
class trienode{
public:
  //int is_end;
  int freq[NUM_FILES];
  trienode *child[NUM_ALPHABET];
  //constructor
  trienode(){
    //is_end=0;
    for(int i=0;i<NUM_FILES;i++)
        freq[i]=0;

    for(int i=0;i<NUM_ALPHABET;i++)
      child[i]=NULL;
  }


};
//create a new node
  trienode*  getnode(){
    trienode* pnode=new trienode;
    //pnode->is_end=1;
    for(int i=0;i<NUM_FILES;i++)
        pnode->freq[i]=0;

    for(int i=0;i<NUM_ALPHABET;i++)
      pnode->child[i]=NULL;
    return pnode;
  }

// trie ADT
class trie{
public:
    trienode *root;
    //int count;
  trie(){
    root=getnode();
    //count=0;
}


//inserting into trie(if word not present, insert. if present,increase freq and mark as leaf)
void insert(std::string key,int file_index)
{
  int depth;
  int length=key.length();
  int index;
  trienode* pCrawl;//crawler

  //ptrie->count++;
  pCrawl=root;
  for(depth=0;depth<length;depth++)
    {
      index=ChartoIndex(key[depth]);
      if(pCrawl->child[index]==NULL)
	pCrawl->child[index]=getnode();
	
      //pCrawl->child[index]->freq[file_index]++;//increase the frequency for that letter
      pCrawl=pCrawl->child[index];
    }
	pCrawl->freq[file_index]++;
  //mark lastnode as leaf
  //pCrawl->is_end=ptrie->count;
}


//search the trie for the key. return zero if not found. if foing, return the frequency.
int* search(std::string key){
  int depth;
  int length=key.length();
  int index;
  trienode* pCrawl;//crawler
  pCrawl=root;
  for(depth=0;depth<length;depth++)
    {
      index=ChartoIndex(key[depth]);
      if(pCrawl->child[index]==NULL)
	return 0;
      pCrawl=pCrawl->child[index];
    }
  return((pCrawl->freq));
}


void maketrie(std::string *filename,int file_index){
    // A buffer to store one word at a time
    std::string buffer;
    std::ifstream fileptr;
    fileptr.open(filename->c_str());
    while(!fileptr.eof())//loop till end of file
    {fileptr>>buffer;//read one word to buffer

    //remove punctuations...
    buffer.erase (std::remove_if (buffer.begin (), buffer.end (), ispunct), buffer.end ());

    //make lover case
    transform(buffer.begin(), buffer.end(), buffer.begin(), ::tolower);

    //insert in trie
    insert(buffer,file_index);}
}
};
//=====================================================================

//=====================================================================
class BTreeNode{
public:
int filenum;
long int freq;
BTreeNode* left;
BTreeNode* right;

BTreeNode(){
filenum=0;
freq=0;
left=NULL;
right=NULL;
}
};

class BTree{
    public:
BTreeNode* root;
BTree(){root=NULL;}
void insertnode(int Fnum,long int Ffreq)
{
    //make the node
    BTreeNode* pnode=new BTreeNode;
    pnode->filenum=Fnum;
    pnode->freq=Ffreq;
    pnode->left=NULL;
    pnode->right=NULL;
    //insert node
    BTreeNode* x,*y;
    x=root;
    y=NULL;
    while(x!=NULL)
    {
        y=x;
        if(x->freq > pnode->freq)
            x=x->left;
        else x=x->right;
    }
    if(y==NULL) root=pnode;
    else{
        if(y->freq>pnode->freq)
            y->left=pnode;
        else y->right=pnode;
    }

}
void BTreeSort(BTreeNode *root,std::vector<std::string> filenames){
    BTreeNode* x=root;
    if(x!=NULL)
    {
        BTreeSort(x->right,filenames);
        if(x->freq)//don't print if frequency zero
            std::cout<<"File name: "<<filenames[x->filenum]<<"\tfrequency: "<<x->freq<<"\n";
        BTreeSort(x->left,filenames);

        //stop if frequency 0
        //if(x->freq==0) return 0;
    }
}

};
//driver
int main(){
//==============get the file names of files in the directory=============

/*    cout<<"Enter the path of the directory in which you wish to search"<<endl;
string dir_path;
cin>>dir_path;
cout<<"The target directory is...\n"<<dir_path.c_str()<<endl;*/

	clock_t begin = clock();

//reading all the files in the directory
std::cout<<"Getting all files in the desired directory.....\n";
dpdf = opendir("./files/"); //opening the current directory

std::vector<std::string> filenames;


//printing the file names
if (dpdf != NULL){
   while (epdf = readdir(dpdf)){
      filenames.push_back(epdf->d_name);

   }
}



    //======================================
    //std::vector<std::string> filenames;
    //filenames.push_back("a.txt");
    //filenames.push_back("b.txt");
    //filenames.push_back("c.txt");
    int num_files=filenames.size();

                        //NUM_FILES=num_files;gives error
//========making trie for files==========
    std::ifstream fileptr;
    std::string filename;
    trie trie1;

    std::size_t found,temp;

    for(int i=0;i<num_files;i++){
    found = filenames[i].find(".txt");
	 temp = filenames[i].find(".txt~");
  if ((found!=std::string::npos)&&!(temp!=std::string::npos)){
    filename="./files/"+filenames[i];

    std::cout<<"inserting in trie the file: "<<filename.c_str()<<" .............\n";
    fileptr.open(filename.c_str());
    if (!fileptr.is_open())
        {printf ("File does not exist \n");continue;}
    else
        
    trie1.maketrie(&filename,i);}}

	clock_t end = clock();
  	double elapsed_secs1 = double(end - begin) / CLOCKS_PER_SEC;
	std::cout<<"total time elapsed in making the trie is "<<elapsed_secs1<<"\n";


//======================Searching==============================
char flag='y';//to control flow for multiple search
while(flag!='n')
    {std::string search_string;
    std::cout<<"enter the string you want to search for\n";
    std::cin>>search_string;

transform(search_string.begin(), search_string.end(), search_string.begin(), ::tolower);
	clock_t begin1=clock();
    // Search for string
    BTree *BST=new BTree;
            int* FREQ=NULL;
            FREQ=trie1.search(search_string);



if(FREQ==NULL)//word not found
    std::cout<<"word not found\ntry another word!\n";
else{
    for(int i=0;i<num_files;i++)
      BST->insertnode(i,FREQ[i]);

    //Print result
    std::cout<<"search result....\n";
    BST->BTreeSort(BST->root,filenames);
    std::cout<<"\nNo more results to display.";
    }

	clock_t end1 = clock();
  	double elapsed_secs = double(end1 - begin1) / CLOCKS_PER_SEC;
	printf("time elapsed to search for this string is %.9f\n",elapsed_secs);
    //prompt for another search
    std::cout<<"\n\ntry another search?(y/n)\n";
    std::cin>>flag;}
    std::cout<<"\n\nSearch has concluded. End of program.\n";

    //deallocating memory


    return 0;
}



