#include <iostream>
//#include "COPY.cpp"
#include <fstream>
#include <string.h>
#define SIZE(x)  (sizeof(x) / sizeof((x)[0]))
//using std::cout;
using namespace std;


typedef struct el
    {
        int Date;
        long int Volume;
    }ELEMENT;


class NODE
{
    private:

    ELEMENT D;
    int Height;
    NODE * left;
    NODE * right;
 //   NODE * parent; mporei na mhn xreiazete

    public:
    friend class AVL;
    NODE(int Date,long int Vol) 
    {
        D.Date=Date;
        D.Volume=Vol;
        Height=0;
        left = right = nullptr;
    }
     NODE(NODE * l,NODE * r,/*NODE * p,*/int Date,long int Vol) 
     {
         D.Date=Date;
        D.Volume=Vol;
        Height=0;
        left = l;
        right = r;

     }
    ~NODE()
    {
        cout<<"\tdeleting...";
        delete(left);
        delete(right);     
    }
    void SetVol(int Vol)
    {
        D.Volume=Vol;     
    }
    void SetHeight(int h)
    {
        Height = h;
    }
    int GetVol()
    {
        return D.Volume;
    }
    int GetDate()
    {
        return D.Date;
    }
    int GetHeight()
    {
        return Height;
    }
    void SetLeft(NODE * l)
    {
        left = l;
    }
    void SetRight(NODE * r)
    {
        right = r;
    }
  
    NODE * GetRight()
    {
        return right;
    }
    NODE * GetLeft()
    {
        return left;
    }
 
    void PrintData()
    {
        cout<<"\nDate:"<<D.Date<<"\nVolume:"<<D.Volume<<"\nHeight:"<<Height;
    }

};

class AVL
{
    private:
    
    public:
    NODE * root;
    AVL()
    {
        root = nullptr;
    }
    ~AVL()
    {}
    int calcheight(NODE *nd)
    {
        
        if(nd->left && nd->right)
            return std::max(nd->left->Height,nd->right->Height)+1;
        else if(nd->left==nullptr&&nd->right)
            return nd->right->Height + 1;
        else if(nd->left&&nd->right==nullptr)
            return nd->left->Height + 1;
        return 1;
    }
    int balanceFactor(NODE *nd)
    {
       /* if(nd->left&&nd->right)
            return nd->left->Height - nd->right->Height;
        else if (nd->left==nullptr&&nd->right)
        {
            cout<<-nd->right->Height;
            return -nd->right->Height;
        }
        else if(nd->left&&nd->right==nullptr)
            return nd->left->Height;*/
        //return 0; //warning
        return (nd->left&&nd->right)?nd->left->Height - nd->right->Height:
        (nd->left==nullptr&&nd->right)?-nd->right->Height:
        (nd->left&&nd->right==nullptr)?nd->left->Height:0;
    }

    NODE * insertNode(NODE * nd,ELEMENT el)
    {   
        if(nd==nullptr)
        {
            NODE * current = new NODE(el.Date,el.Volume);
            nd = current;
            nd->left = nd->right = nullptr;
            nd->Height=1;
            return nd;
        }
        else
        {
            if(el.Date < nd->GetDate())
                nd->left = insertNode(nd->left,el);
            else 
                nd->right = insertNode(nd->right,el);
        }
        
        int tempHeight = nd->Height;
        nd->Height = calcheight(nd);
        
        if(balanceFactor(nd)==2 && balanceFactor(nd->left)==1)
             {
                 nd = LLrotatecase(nd);  
                 nd->right->Height=calcheight(nd->right);
             }
        else if(balanceFactor(nd)==-2 && balanceFactor(nd->right)==-1)
            {
                nd = RRotateCase(nd);
                nd->left->Height = calcheight(nd->left);
            } 
        else if(balanceFactor(nd)==-2 && balanceFactor(nd->right)==1)
            {
                nd = RLotateCase(nd);
                nd->right->Height = calcheight(nd->right);
                nd->left->Height = calcheight(nd->left);
                nd->Height = calcheight(nd); //prosoxh epanypoligismos ton ypson
            } 
        else if(balanceFactor(nd)==2 && balanceFactor(nd->left)==-1)
            {
                nd = LRotateCase(nd);
                nd->right->Height = calcheight(nd->right);
                nd->left->Height = calcheight(nd->left); 
                nd->Height = calcheight(nd);//prosoxh epanypoligismos ton ypson
            }
        
   
        return nd;
    }

    NODE * LLrotatecase(NODE *nd)
    {
        NODE * tmp,*tmp2;

        tmp = nd;
        tmp2 = tmp->left;

        tmp->left = tmp2->right;
        tmp2->right = tmp;

        return tmp2;
    }
    NODE * RRotateCase(NODE *nd)
    {
        NODE * tmp,*tmp2;
    
        tmp = nd;
        tmp2 = tmp->right;

        tmp->right = tmp2->left;
        tmp2->left = tmp;

        return tmp2;
    }
    NODE * RLotateCase(NODE *nd)
    {  
      
        NODE * tmp;
        NODE*tmp2;
        NODE*tmp3;
    
        tmp = nd;
        tmp2 = tmp->right; 
        tmp3 = tmp2->left;

        tmp -> right = tmp3->left;
        tmp2 -> left = tmp3 -> right;
        tmp3->left = tmp;
        tmp3->right = tmp2;

        return tmp3;
    }
    NODE * LRotateCase(NODE *nd)
    {
         NODE * tmp,*tmp2,*tmp3;
             
        tmp = nd;
        tmp2 = tmp->left;
        tmp3 = tmp2->right;

        tmp -> left = tmp3->right;
        tmp2 -> right = tmp3 -> left;
        tmp3->right = tmp;
        tmp3->left = tmp2;

        return tmp3;
    }

    NODE * deleteNode(NODE * nd, int Date)
    {
        
        //exoume thema me thn bash ths anadromhs
        if((nd->left==nullptr &&nd->right==nullptr)&&nd->GetDate()==Date)
        {
            if(nd==this->root)
                this->root = nullptr;  
            
            delete nd;
            cout<<"\nDeletion was successfully completed\n";
            return nullptr;
        }
        else if(nd->left==nullptr&&nd->right==nullptr)
        {
            cout<<"There is no such record\n";
            return nd;
        }

        NODE *pred;
        NODE *succ;
        if(nd->GetDate()<Date)
            nd->right = deleteNode(nd->right,Date);
        else if(nd->GetDate()>Date)
            nd->left = deleteNode(nd->left,Date);
        else
        {
            if(nd->left!=nullptr)
            {
                pred = predecessor(nd->left);
                nd->D.Date = pred->D.Date;
                nd->left = deleteNode(nd->left,pred->D.Date);
            }
            else 
            {
                succ = successor(nd->right);
                nd->D.Date = succ->D.Date;
                nd->right = deleteNode(nd->right,succ->D.Date);
            }
        }

       
        if(balanceFactor(nd)==2 && balanceFactor(nd->left)==1)
        {
            nd = LLrotatecase(nd);  
            nd->right->Height=calcheight(nd->right);            
        }             
        else if(balanceFactor(nd)==2 && balanceFactor(nd->left)==-1) //ok
        {
            nd = LRotateCase(nd); 
            nd->right->Height = calcheight(nd->right);
            nd->left->Height = calcheight(nd->left); 
            nd->Height = calcheight(nd);//prosoxh epanypoligismos ton ypson
        }
        else if(balanceFactor(nd)==2 && balanceFactor(nd->left)==0)
        {
             nd = LLrotatecase(nd); 
             nd->right->Height=calcheight(nd->right);
       }
        else if(balanceFactor(nd)==-2 && balanceFactor(nd->right)==-1) //ok
       {
               nd = RRotateCase(nd); 
               nd->left->Height = calcheight(nd->left);
       }
        else if(balanceFactor(nd)==-2 && balanceFactor(nd->right)==1)
       {      nd = RLotateCase(nd);
              nd->right->Height = calcheight(nd->right);
              nd->left->Height = calcheight(nd->left);
              nd->Height = calcheight(nd); //prosoxh epanypoligismos ton ypson 
        }   
        else if(balanceFactor(nd)==-2 && balanceFactor(nd->right)==0)  //ok
       {
            nd = RRotateCase(nd); 
            nd->left->Height = calcheight(nd->left);
       }
       
       nd->Height = calcheight(nd); //prosoxh epanypoligismos ton ypson 

        
        return nd;

    }
    NODE *predecessor(NODE *nd)
    {
        while(nd->right!=nullptr)
            nd=nd->right;
        cout<<"date:"<<nd->D.Date;
        return nd;
    }
    NODE *successor(NODE *nd)
    {
        while(nd->left!=nullptr)
            nd = nd->left;

        return nd;
    }

    NODE * Find(NODE *nd,int Date)
    {   
        if (nd==nullptr || nd->GetDate()==Date)
            return nd;
        
        if (nd->GetDate()<Date)
            return Find(nd->right,Date);

        return Find(nd->left,Date);
    }


    bool Modify(NODE *nd,int Date)
    {
        NODE * tmp = Find(nd,Date);
        if (tmp)
        {
           int Vol;
           cout<<"\nPlease enter a new Volume :";
           cin>>Vol;
           tmp->SetVol(Vol); 
           cout<<"====================================";
           cout<<"\nSo after the change the new data of the share are:\nDate:"<<formatstr(tmp->GetDate())<<"\nVolume:"<<tmp->GetVol()<<"\n";
           cout<<"====================================\n";
           return true;
        }
        return false;
    }


string formatstr(int Date)
{
    string f = to_string(Date);
    f.insert(4,"-");
    f.insert(7,"-");
    return f;
}

    void InOrder(NODE * root)
    {
        if(root == nullptr)
            return;
        InOrder(root->left);

        cout<<"===================\nDate: "<<formatstr(root->GetDate())<</*"\nHeight:"<<root->Height<<*/"\nVolume:"<<root->GetVol()<<"\n===================\n";

        InOrder(root->right);
    }
    void PreOrder(NODE * root)
    {
        if(root==nullptr)
            return;
        
        
        cout<<"===================\nDate: "<<root->GetDate()<<"\nHeight\n:"<<root->Height<<"\nVolume:"<<root->GetVol()<<"\n===================\n";
        PreOrder(root->left);
        PreOrder(root->right);
    }
    void PostOrder(NODE * root)
    {
        if(root==nullptr)
            return;
        
        
        PreOrder(root->left);
        PreOrder(root->right);
        cout<<"===================\nDate: "<<root->GetDate()<<"\nHeight\n:"<<root->Height<<"\nVolume:"<<root->GetVol()<<"\n===================\n";
    }

};

int formatstring(string str)
{
    str.erase(str.begin()+4,str.end()-5);
    str.erase(str.end()-3);
    return stoi(str);
}

void menu(AVL avl)
{
    string Date;
    while(true)
    {
        cout<<"\tWelcome to the main Interface\n=========================================\n"
        <<"1)In-Order traversal\n2)Search by date\n3)Modify the Volume of a share(Please give Date)\n"
        <<"4)Delete a record(Please give Date)\n5)Exit\n| | | Please select: | | |";
        int selection=0;
        cin>>selection;
        switch (selection){
            
        case 1: // inorder
        avl.InOrder(avl.root);
        cout<<"\n\n\t\t{-_-}Returning...{-_-}\n\n\n";
        break;
        case 2: //search
        cout<<"\nEnter Date(Year-Month-Date):";
        cin>>Date;
        NODE * TMP;
        TMP = avl.Find(avl.root,formatstring(Date));
        if(TMP)
            cout<<"\nThe volume on that day was "<<TMP->GetVol()<<"\n\n";
        else 
            cout<<"\nThere was no record of that day\n\n";
        break;
        case 3: //modify
        cout<<"\nEnter Date(Year-Month-Date):";
        cin>>Date;
        if(!avl.Modify(avl.root,formatstring(Date)) )
            cout<<"\nThere is no record for that day\n";
        break;
        case 4: //deletion
        cout<<"\nEnter Date(Year-Month-Date):";
        cin>>Date;
        avl.deleteNode(avl.root,formatstring(Date));
        cout<<"\n\n\t\t{-_-}Returning...{-_-}\n\n\n";
        break;
        case 5: //exit
        cout<<"\nExiting...\n";
        exit(0);
        break;
        default :
        cout<<"\nInvalid choice./.Exiting...\n";
        exit(0);
        break;
        }  
    }
}


void ReadFile(const string inputfile,AVL &ins)
{
    int i=0;
    ifstream  InFile(inputfile);
    if(InFile.good())
    {
        string temp,temp2,temp3;
        ELEMENT tmp;
        getline(InFile,temp);
       

        while(!InFile.eof())
     {
        getline(InFile,temp,'-');
        getline(InFile,temp2,'-');
        getline(InFile,temp3,',');
        tmp.Date = stoi(temp+temp2+temp3);
       

        for(int j=0; j<=4;j++)
            getline(InFile,temp,',');
        
        tmp.Volume = stoi(temp);
        ins.root = ins.insertNode(ins.root,tmp);
        
       

        getline(InFile,temp);
        ++i;   
     }
    InFile.close();
    }
   else
   {
      cout<<"Error opennning the file...Aborting..."<<endl;
      exit(0);
   }
}

//testing2
void ReadFilet(const string inputfile,ELEMENT *array)
{
    int i=0;
    ifstream  InFile(inputfile);
    if(InFile.good())
    {
        string temp,temp2,temp3;
        getline(InFile,temp);
       

        while(!InFile.eof())
     {
        getline(InFile,temp,'-');
        getline(InFile,temp2,'-');
        getline(InFile,temp3,',');
        temp = temp+temp2+temp3;
        array[i].Date=stoi(temp);

        for(int j=0; j<=4;j++)
            getline(InFile,temp,',');
        
        array[i].Volume=stof(temp);
        getline(InFile,temp);
        ++i;   
     }
    InFile.close();
    }
   else
   {
      cout<<"Error opennning the file...Aborting..."<<endl;
      exit(0);
   }
}

int NoOfLine(string f)
{
    int cnt=0;
    ifstream file(f);
    string cline;
    if(file.good())
    {
     while(getline(file,cline))
        cnt++;   
    file.close();
    }
   else
   {
      cout<<"Error opennning the file...Aborting..."<<endl;
      exit(0);
   }
    return cnt-1;
}
//testing2



int main()
{
    AVL avl;
    ReadFile("agn.us.txt",avl);
    //ELEMENT S[NoOfLine("agn.us.txt")];
    //ReadFilet("agn.us.txt",S);
    menu(avl);
   
    /*ELEMENT l1={10,0};
    ELEMENT l2={20,1};
    ELEMENT l3={15,2};
    ELEMENT l4={18,3};
    ELEMENT l5={22,4};
    ELEMENT l6={16,2};
    ELEMENT l7={21,3};
    ELEMENT l8={23,4};
    ELEMENT l9={27,1};
    ELEMENT l10={24,1};
    ELEMENT l11={24,4};

    
    
    avl.root=avl.insertNode(avl.root,l1);
    avl.root=avl.insertNode(avl.root,l2);
    avl.root=avl.insertNode(avl.root,l3);
    avl.root=avl.insertNode(avl.root,l4);
    avl.root=avl.insertNode(avl.root,l5);
    avl.root=avl.insertNode(avl.root,l6);
    avl.root=avl.insertNode(avl.root,l7);
    avl.root=avl.insertNode(avl.root,l8);
    avl.root=avl.insertNode(avl.root,l9);
    avl.root=avl.insertNode(avl.root,l10);*/
    
   // avl.InOrder(avl.root);
   // avl.PostOrder(avl.root);
  
     
    
    
    return 0;
}