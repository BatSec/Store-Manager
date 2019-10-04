#include<iostream>
#include<fstream>
#include<string.h>
#include<cstdio>
#include<conio.h>
using namespace std;

char passw[7];
int check=0;
string pass;
void auth()                                 //checking for verified user's password
{
  cout<<"Hello Admin! Please enter your password\n";
  for(int i=0;i<7;i++)
  {
	passw[i]=getch();  	
  	cout<<"*";
  }
  pass=passw;
	if(pass=="pass123")
	{
		system("cls");
		cout<<"\n\t\t\t\t\t\tWelcome Admin!!"<<endl;
		return;
	}
	   
	else
	{
		system("cls");
	    cout<<"Sorry! You are not granted the access!!"; 
	    exit(1);
       }

}


class shop{
	char pname[26];
	char pcode[10];
	float pcost;
	int pq;
public:
     void input();
	 void display();		 		
     int checkpc(char ac[])                //accessor function
	 { return strcmp(pcode,ac);
		 }
	 void modify();
 }s,sh;

 void shop::input()
 {
	 	cout<<"Enter the name of product: "<<endl;
	 	  cin>>pname;
	 	cout<<"Enter the product code: "<<endl;
		   cin>>pcode;
		cout<<"Enter the product cost: "<<endl;
		  cin>>pcost;     
		cout<<"Enter the product quantity: "<<endl;
		  cin>>pq;	 
	}
			 
 void shop::display()
{
     	cout<<"\t\tName of the product:"<<pname<<endl;
     	cout<<"\t\tProduct code of product:"<<pcode<<endl;
     	cout<<"\t\tCost of the product:"<<pcost<<endl;
     	cout<<"\t\tProduct Quantity in stock:"<<pq<<endl<<endl;
	}

 void shop::modify()
 {
 	  	cout<<"Product Name: "<<pname<<endl;
	  	cout<<"Product Code: "<<pcode<<endl;
	  	cout<<"Product Cost: "<<pcost<<endl;
	  	cout<<"Product Quantity: "<<pq<<endl;
	  	
	  	char pn[2]=" ",pc[2]=" ";
	  	float pcs; int pqq;
	  	
	  	cout<<"New Product Name:(Enter '.' to retain old one)";
	  	  cin>>pn;
	  	cout<<"New Product code:(Enter '.' to retain old one)";
		  cin>>pc;
		cout<<"New Product cost:(Enter '0' to retain old one)";
		  cin>>pcs;
		cout<<"New Product quantity:(Enter '0' to retain old one)";
		  cin>>pqq;
		
		if(strcmp(pn,".")!=0)
		   strcpy(pname,pn);
		if(strcmp(pc,".")!=0)
		   strcpy(pcode,pc);          
	  	if(pcs!=0)
		   pcost=pcs;
		if(pqq!=0)
		   pq=pqq;
 	
    }

 void add()
 {
 	ofstream fo;
 	fo.open("items.dat",ios::app);
 	char ans='y';
 	while((ans=='y')||(ans=='Y'))
	{
		s.input();
		fo.write((char*)&s,sizeof(s));
		cout<<"Item added to file!!\n";
		cout<<"Want to Add more items(y/n): ";
		cin>>ans;
	}
	system("cls");
	fo.close();
 }
 
 
 void mod()
 {
 	
    fstream fio;
	fio.open("items.dat",ios::in|ios::out);
	char mpc[10];
	long pos; char found='f';
	cout<<"\nEnter the Product code to be modified:";
	  cin>>mpc;
	while(!fio.eof())
	{
		pos=fio.tellg();  //befor reading a record its begining pos is determined with tellg()
		fio.read((char*)&s,sizeof(s));
		if(s.checkpc(mpc)==0)
		{
			s.modify();
			fio.seekg(pos);
			fio.write((char*)&s,sizeof(s));
			found='t';
			break;
		}
	}  
	  
	  if(found=='f')
	    cout<<"\nRecord not found!!\n";
	  fio.close();			
	  system("cls");			 	
 }
   
   
   
  void delt()
  {
    ifstream fio("items.dat");
    ofstream file("temp.dat",ios::out);
    char mpc1[10];
    char found='f',confirm='n';
    cout<<"\nEnter the Product code to be modified:";
	  cin>>mpc1;
	while(!fio.eof())
	{
		fio.read((char*)&s,sizeof(s));
		if(s.checkpc(mpc1)==0)
		{
			s.display();
			found='t';
			cout<<"Are you sure , you want to delete this record(y/n):.. ";
			  cin>>confirm;
			if(confirm=='n')
			  file.write((char*)&s,sizeof(s));  
		}
		else
		     file.write((char*)&s,sizeof(s));
	    
	   } 
		if(found=='f')
		 cout<<"\nRecord not found!!\n";
		fio.close();
		file.close();
		remove("items.dat");
		rename("temp.dat","items.dat");   //old file is removed and temp file is renamed
		system("cls");
	  }
	
void dis()
{	
	cout<<"\nThe file contains:\n";
	ifstream fio("items.dat");
	while(!fio.eof())
	
	{
	  fio.read((char*)&sh,sizeof(sh));
	  if(fio.eof())
	    break;
	  sh.display();		
	  }
	fio.close();
	cout<<"Please press Enter to continue....";
	getch();
	system("cls");
 }	
	 
int main()
{	
	system("cls");
	cout<<"****************************Welcome to Ridhu's Shop**************************\n";
	int c;
	if(check==0)
		auth();
	check++;
	while(c!=6)
		{
		
		cout<<"Enter your choice: \n";	
		
		cout<<"\t\t\t1. Add Items"<<endl;
		cout<<"\t\t\t2. Modify Item"<<endl;
		cout<<"\t\t\t3. Delete an item"<<endl;
		cout<<"\t\t\t4. Show Data of items:"<<endl;
		cout<<"\t\t\t5. Exit"<<endl;
		cin>>c;
	   	system("cls");
	    switch(c)
	    {
	    	case 1:  add();
	    	         break;
	    	case 2:  mod();
			         break;
			case 3:  delt();
			         break;
			case 4:  dis();
			         break;
			case 5:  exit(1);
			         break;
			default:cout<<"Sorry! Wrong input!!";
					getch();
					system("cls");
					main();
		}
	}
	return 0;
}
