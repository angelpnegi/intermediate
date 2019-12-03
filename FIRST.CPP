#include<iostream.h>
#include<fstream.h>
#include<conio.h>
#include<stdio.h>
#include<string.h>
#include<ctype.h>

//seats taken are represented by '#'
//seats empty are represented by '*'

int k,crow[50],ccol[50];

class client
{
char name[10];
long nop,pr;
public:
int row[50], col[50];
char movie[10];
void disp();
void enter(int n,char mov[10],int prt);
int modify1(char nm[10],char mov[10],int ch,char mname[10]);
int modify2(char nm[10],int n, char mov[10],int ch);
int modify3(char nm[10],int n,int r,int c);
int rnop()
{
return nop;
}
};

void client :: enter(int n,char mov[10],int prt)
{
cout<<"Enter clients name- ";
cin>>name;
strcpy(movie,mov);
nop=n;
pr=prt*n;
for(int i=0;i<n;i++)
{
row[i]=crow[i];
col[i]=ccol[i];
}
}

void client :: disp()
{
cout<<"\nName of client- "<<name<<"\nMovie for which the client has booked- "<<movie<<"\nNumber of seats booked by the client- "<<nop<<"\nSeat numbers are-\n";
for(int i=0;i<nop;i++)
cout<<"\tRow- "<<row[i]<<" and Col- "<<col[i]<<',';
cout<<"\n\nPrice- "<<pr<<'\n' ;
}

int client :: modify1(char nm[10],char mov[10],int q,char mname[10])
{
if((strcmpi(name,nm)==0) && (strcmpi(movie,mov)==0) && (strcmpi(mname,movie)==0))
q++;
return q;
}

int client :: modify2(char nm[10],int n, char mov[10],int q)
{
if((strcmpi(name,nm)==0) && nop==n && (strcmpi(movie,mov)==0))
q++;
return q;
}

int client :: modify3(char nm[30],int n,int r,int c)
{
int q=0;
if(strcmpi(name,nm)==0 && (n==nop || n==101))
{
for(int i=0;i<10;i++)
if((row[i]==r && col[i]==c) || (r==10 && c==10))
q=1;
}
return q;
}

class PVR
{
long ppp,amount, cap, fr, occu;
public:
char hall[10][10];
char mname[10];
void enter();
void disp1(int r[50],int c[50],int n);
void disp2();
void d()
{
cout<<mname;
}
void modify2(int pppt,int frt,int occut,int n)
{
ppp=pppt;
fr=frt-n;
occu=occut+n;
amount=amount+n*pppt;
}
void modify3(int pppt,int frt,int occut,int n)
{
fr=frt+n;
occu=occut-n;
amount=amount-n*pppt;
}
int rppp()
{
return ppp;
}
int rfr()
{
return fr;
}
int roccu()
{
return occu;
}
int rcap()
{
return cap;
}
int ramount()
{
return amount;
}
};

void PVR :: enter()
{
int i,j;
cout<<"Enter movie name- ";
cin>>mname;
for(i=0;i<10;i++)
for(j=0;j<10;j++)
hall[i][j]='*';
cout<<"Enter price per person- ";
cin>>ppp;
amount=0;
cap=100;
fr=100;
occu=0;
}

void PVR :: disp1(int r[50],int c[50],int n)
{
cout<<"\nClients seats- #\n\n";
client C;
int i,j,m,mm=0,nn=0;
cout<<"   ";
for(i=0;i<10;i++)
cout<<i+1<<' ';
cout<<endl;
for(i=0;i<10;i++)
{
cout<<i+1<<' ';
if(i!=9)
cout<<' ';
for(j=0;j<10;j++)
{
mm=0;
for(m=0;m<n;m++)
{
if(r[m]==(i+1) && c[m]==(j+1) && nn<=n)
{
nn++;
cout<<'#'<<' ';
mm=1;
}
}
if(mm==0)
cout<<'*'<<' ';
}
cout<<endl;
}
}

void PVR :: disp2()
{
int i,j;
cout<<"\n----------------------------------------";
cout<<"\nName of movie- "<<mname<<"\nHall Layout- \n   ";
for(i=0;i<10;i++)
cout<<i+1<<' ';
cout<<endl;
for(i=0;i<10;i++)
{
cout<<i+1<<' ';
if(i!=9)
cout<<' ';
for(j=0;j<10;j++)
cout<<hall[i][j]<<' ';
cout<<endl;
}
cout<<"Amount earned- "<<amount<<"\nPrice per person- "<<ppp<<"\nFree seats- "<<fr<<"\nOccupied seats- "<<occu<<endl;
cout<<"----------------------------------------";
}

int count1()     //for number of halls created by the admin
{
k=0;
ifstream f1("PVRhall",ios::binary);
PVR P;
while(f1.read((char *)&P,sizeof(P)))
k++;
f1.close();
return k;
}

int count2()
{
int e=0;
ifstream f2("Client",ios::binary);
client C;
while(f2.read((char *)&C,sizeof(C)))
e++;
f2.close();
return e;
}

void allot(int n,char hall[10][10])
{
int i,j;
int l=0;
for(i=0;i<10;i++)
{
for(j=0;j<10;j++)
{
if(hall[i][j]=='*' && l<=n)
{
hall[i][j]='#';
crow[l]=i+1;
ccol[l]=j+1;
l++;
}
if(l==n)
break;
}
if(l==n)
break;
}
}

void Delete(int r[50],int c[50],int n,char hall[10][10])
{
int m;
for(int i=0;i<10;i++)
{
for(int j=0;j<10;j++)
{
for(int m=0;m<n;m++)
{
if((i+1)==r[m] && (j+1)==c[m] && hall[i][j]=='#')
hall[i][j]='*';
}
}
}
}

void book()
{
int ch1,ch2,l=1, f=1,i,pppt,n,frt,occut;
char hall[10][10],nm[30];
ifstream f1("PVRhall",ios::binary);
ofstream f2("Client",ios::binary|ios::app);
client C;
PVR P;
cout<<"\nEnter movie choice-\n";
while(f1.read((char *)&P,sizeof(P)))
{
cout<<l<<". ";
P.d();
cout<<" (Hall "<<l++<<")"<<endl;
}
f1.close();
cin>>ch1;
switch(ch1)
{
case 1: f=0;
	break;
case 2: if(k>=2)
	f=0;
	else
	cout<<"\nWrong choice\n";
	break;
case 3: if(k>=3)
	f=0;
	else
	cout<<"\nWrong choice\n";
	break;
case 4: if(k==4)
	f=0;
	else
	cout<<"\nWrong choice\n";
	break;
default : cout<<"\nWrong choice\n";
}
if(f==0)
{
fstream f3("PVRhall",ios::binary|ios::in|ios::out);
f3.seekg((ch1-1)*sizeof(P),ios::beg);
f3.read((char *)&P,sizeof(P));
pppt=P.rppp();
occut=P.roccu();
frt=P.rfr();
ch2='N';
do
{
cout<<"Enter number of people (max 50) - " ;
cin>>n;
if(n>0 && n<=50)
{
if((occut+n)<=P.rcap())
{
allot(n,P.hall);
P.modify2(pppt,frt,occut,n);
f3.seekg((ch1-1)*sizeof(P),ios::beg);
f3.write((char *)&P,sizeof(P));
C.enter(n,P.mname,pppt);
f2.write((char *)&C,sizeof(C));
cout<<"\nSeats booked\n";
}
else
{
cout<<"\nFULL, only "<<P.rcap()-occut<<" seats left\nDo you want to book the available seats ?(Y/N)\n";
cin>>ch2;
}
if(ch2=='Y' || ch2=='y')
cout<<"Now, ";
}
}while(ch2=='Y' || ch2=='y');
f3.close();
}
f2.close();
}


void cancel()
{
int i, ch, f=1, n=101, r=10, c=10, pppt, frt, occut,l=1,q,hh=0,h=0,gg=0;
char nm[30];
fstream f1("PVRhall", ios::binary|ios::in|ios::out);
PVR P;
client C;
cout<<"\nEnter movie choice-\n";
f1.seekg(0,ios::beg);
while(f1.read((char *)&P,sizeof(P)))
{
cout<<l<<". ";
P.d();
cout<<" (Hall "<<l++<<")"<<endl;
}
cin>>ch;
f1.close();
switch(ch)
{
case 1: f=0;
	break;
case 2: if(k>=2)
	f=0;
	else
	cout<<"\nWrong choice\n";
	break;
case 3: if(k>=3)
	f=0;
	else
	cout<<"\nWrong choice\n";
	break;
case 4: if(k==4)
	f=0;
	else
	cout<<"\nWrong choice\n";
	break;
default : cout<<"\nWrong choice\n";
}
if(f==0)
{
ifstream f4("PVRhall",ios::binary);
f4.seekg((ch-1)*sizeof(P),ios::beg);
f4.read((char *)&P,sizeof(P));
cout<<"Enter Client's name-\n";
cin>>nm;
q=0;
ifstream f2("Client",ios::binary);
while(f2.read((char *)&C,sizeof(C)))
q=C.modify1(nm,C.movie,q,P.mname);
if(q==1)
cout<<"Found the client\n";
else
if(q==0)
cout<<"No client named "<<nm;
else
if(q>1)
{
cout<<"More than one client named "<<nm<<" in hall "<<ch;
h=1;
cout<<"\nEnter number of seats booked by the client-\n";
cin>>n;
q=0;
f2.close();
ifstream f2("Client",ios::binary);
while(f2.read((char *)&C,sizeof(C)))
q=C.modify2(nm,n,C.movie,q);
if(q==1)
cout<<"Found the client";
else
if(q==0)
cout<<"No client with given info";
else
if(q>1)
{
cout<<"More than one client named "<<nm<<" with "<<n<<" number of seats in hall "<<ch;
hh=1;
cout<<"\nEnter first seat booked by the client-\nRow- ";
cin>>r;
cout<<"Col- ";
cin>>c;
}
}
f4.close();
f2.close();
ifstream f6("Client",ios::binary);
while(f6.read((char *)&C,sizeof(C)))
{
if(h==0)
n=C.rnop();
if(hh==0)
{
r=C.row[0];
c=C.col[0];
}
q=C.modify3(nm,n,r,c);
if(q==0)
{
ofstream f3("Clienttemp",ios::binary|ios::app);
f3.write((char *)&C,sizeof(C));
f3.close();
}
if(q==1)
{
gg=1;
ifstream f8("PVRhall",ios::binary);
f8.seekg((ch-1)*sizeof(P),ios::beg);
pppt=P.rppp();
occut=P.roccu();
frt=P.rfr();
f8.close();
fstream f5("PVRhall",ios::binary|ios::in|ios::out);
f5.seekp((ch-1)*sizeof(P),ios::beg);
Delete(C.row,C.col,n,P.hall);
f5.seekp((ch-1)*sizeof(P),ios::beg);
P.modify3(pppt,frt,occut,n);
f5.seekp((ch-1)*sizeof(P),ios::beg);
f5.write((char *)&P,sizeof(P));
f5.close();
cout<<"\nBooking Canceled\n";
}
}
if(gg==0)
cout<<"\nSorry no client found as per the given info";
f6.close();
if(gg==1)
{
remove("Client");
rename("Clienttemp","Client");
}
}
}

void display1()
{
int ch,n=101,r=10,c=10,f=1,q=0,l=1,h=0;
char nm[30];
ifstream f1("PVRhall",ios::binary);
PVR P;
client C;
cout<<"\nEnter movie choice-\n";
while(f1.read((char *)&P,sizeof(P)))
{
cout<<l<<". ";
P.d();
cout<<" (Hall "<<l++<<")"<<endl;
}
cin>>ch;
f1.close();
switch(ch)
{
case 1: f=0;
	break;
case 2: if(k>=2)
	f=0;
	else
	cout<<"\nWrong choice\n";
	break;
case 3: if(k>=3)
	f=0;
	else
	cout<<"\nWrong choice\n";
	break;
case 4: if(k==4)
	f=0;
	else
	cout<<"\nWrong choice\n";
	break;
default : cout<<"\nWrong choice\n";
}
if(f==0)
{
ifstream f4("PVRhall",ios::binary);
f4.seekg((ch-1)*sizeof(P),ios::beg);
f4.read((char *)&P,sizeof(P));
cout<<"Enter Client's name-\n";
cin>>nm;
q=0;
ifstream f2("Client",ios::binary);
while(f2.read((char *)&C,sizeof(C)))
q=C.modify1(nm,C.movie,q,P.mname);
f4.close();
if(q==1)
cout<<"Found the client";
else
if(q==0)
cout<<"No client named "<<nm;
else
if(q>1)
{
cout<<"More than one client named "<<nm<<" in hall "<<ch;
cout<<"\n\nEnter number of seats booked by the client- ";
cin>>n;
h=1;
q=0;
f2.close();
ifstream f2("Client",ios::binary);
while(f2.read((char *)&C,sizeof(C)))
q=C.modify2(nm,n,C.movie,q);
if(q==1)
cout<<"Found the client";
else
if(q==0)
cout<<"No client with given info";
else
if(q>1)
{
cout<<"More than one client named "<<nm<<" with "<<n<<" number of seats in hall "<<ch;
cout<<"\nEnter any one of the seats numbers booked by the client-\nRow- ";
cin>>r;
cout<<"Col- ";
cin>>c;
}
}
f2.close();
ifstream f3("Client",ios::binary);
while(f3.read((char *)&C,sizeof(C)))
{
if(h==0)
n=C.rnop();
q=C.modify3(nm,n,r,c);
if(q==1)
break;
}
if(q==1)
{
ifstream f5("PVRhall",ios::binary);
cout<<endl<<"----------Client's info----------\n";
C.disp();
cout<<"----------------------------------------";
getch();
cout<<"----------------------------------------";
P.disp1(C.row,C.col,n);
f5.close();
cout<<"----------------------------------------";
getch();
}
else
cout<<"\nSorry no client";
f3.close();
}
}

void initialize()
{
k=count1();
if(k<4)
{
char ch;
ofstream f1("PVRhall",ios::binary|ios::app);
PVR P;
do
{
P.enter();
f1.write((char *)&P,sizeof(P));
k++;
cout<<"Do you want to continue ?(Y/N)";
cin>>ch;
}while((ch=='y' || ch=='Y') && k<4);
if(k>4)
cout<<"Only 4 halls available";
f1.close();
}
else
cout<<"\nAll halls are occupied\n";
}

void display2()
{
PVR P;
k=count1();
if(k==0)
cout<<"\nNo halls initialized yet\n";
else
{
ifstream f1("PVRhall",ios::binary);
int ch1=0,ch2=0,l=1;
while(ch1!=1 && ch1!=2)
{
cout<<"\nDisplay choice-\n1. All halls info\n2. Hall of your choice\n";
cin>>ch1;
}
if(ch1==2)
{
cout<<"\nEnter hall / movie info you want to display-\n";
while(f1.read((char *)&P,sizeof(P)))
{
cout<<l<<". ";
P.d();
cout<<" (Hall "<<l++<<")"<<endl;
}
f1.close();
cin>>ch2;
ifstream f3("PVRhall",ios::binary);
f3.seekg((ch2-1)*sizeof(P),ios::beg);
f3.read((char *)&P,sizeof(P));
P.disp2();
f3.close();
getch();
}
if(ch1==1)
{
ifstream f4("PVRhall",ios::binary);
while(f4.read((char *)&P,sizeof(P)))
{
P.disp2();
getch();
}
f4.close();
}
}
}

void display3()
{
int ch1,ch2,l=1;
char m[20];
cout<<"\nEnter choice-\n1. Display info of clients of all halls\n2. Display info of clients of a particular hall\n";
cin>>ch1;
if(ch1!=1 && ch1!=2)
cout<<"Wrong choice";
else
{
client C;
if(ch1==1)
{
ifstream f2("Client",ios::binary);
while(f2.read((char *)&C,sizeof(C)))
{
cout<<"\n--\t--\t--\t--\t--";
C.disp();
cout<<"--\t--\t--\t--\t--";
getch();
}
f2.close();
}
if(ch1==2)
{
ifstream f3("Client",ios::binary);
ifstream f1("PVRhall",ios::binary);
PVR P;
cout<<"Enter hall choice-\n";
while(f1.read((char *)&P,sizeof(P)))
{
cout<<l<<". ";
P.d();
cout<<" (Hall "<<l++<<")"<<endl;
}
f1.close();
cin>>ch2;
ifstream f4("PVRhall",ios::binary);
f4.seekg((ch2-1)*sizeof(P),ios::beg);
f4.read((char *)&P,sizeof(P));
strcpy(m,P.mname);
f4.close();
while(f3.read((char *)&C,sizeof(C)))
{
if(strcmpi(C.movie,m)==0)
{
cout<<"\n--\t--\t--\t--\t--";
C.disp();
cout<<"--\t--\t--\t--\t--";
getch();
}
}
f3.close();
}
}
}

void display4()
{
int ch1,ch2,l=1;
long s=0;
char m[20];
cout<<"\nEnter choice-\n1. Display money earned through all halls\n2. Display money earned through a particular hall\n";
cin>>ch1;
if(ch1!=1 && ch1!=2)
cout<<"Wrong choice";
else
{
PVR P;
if(ch1==1)
{
ifstream f2("PVRhall",ios::binary);
while(f2.read((char *)&P,sizeof(P)))
s=s+P.ramount();
f2.close();
cout<<"\nMoney earned through all halls is "<<s;
}
if(ch1==2)
{
ifstream f1("PVRhall",ios::binary);
cout<<"\nEnter hall choice-\n";
while(f1.read((char *)&P,sizeof(P)))
{
cout<<l<<". ";
P.d();
cout<<" (Hall "<<l++<<")"<<endl;
}
f1.close();
cin>>ch2;
ifstream f4("PVRhall",ios::binary);
f4.seekg((ch2-1)*sizeof(P),ios::beg);
f4.read((char *)&P,sizeof(P));
strcpy(m,P.mname);
s=P.ramount();
f4.close();
cout<<"\nMoney earned through movie "<<m<<" playing in hall "<<ch2<<" is "<<s;
}
getch();
}
}

void end()
{
PVR P;
char ch;
long s=0;
ifstream f1("PVRhall",ios::binary);
ifstream f2("Client",ios::binary);
cout<<"\nBefore ending the day, do you want yo take a look at the halls ?\n";
cin>>ch;
if(ch=='Y' || ch=='y')
{
while(f1.read((char *)&P,sizeof(P)))
{
s=s+P.ramount();
P.disp2();
cout<<endl;
getch();
}
}
f1.close();
f2.close();
cout<<"\n\nTotal amount earned today- "<<s;
remove ("PVRhall");
remove ("Client");
}

void main()
{
clrscr();
int ch1,ch2,ch3,ch4;
char pas[30];
k=count1();
cout<<"\n====================\n# WELCOME TO PVR #\n====================\nOption-\n1. Client\n2. Admin\n";
cin>>ch3;
if(ch3==1)
{
ch2=0;
if(k!=0)
{
do
{
cout<<"\n\n-----------------\nPVR MOVIE OPTION\n-----------------\n1. Book ticket\n2. Cancel tickets\n3. Display your seats\n4. Exit as Client\n";
cin>>ch1;
switch(ch1)
{
case 1: book();
	break;
case 2: if(count2!=0)
	cancel();
	else
	cout<<"No bookings done yet";
	break;
case 3:	if(count2!=0)
	display1();
	else
	cout<<"No bookings done yet";
	break;
case 4: ch2=1;
	break;
default: cout<<"Wrong choice";
}
}while(ch2==0);
cout<<"THANK YOU\nVisit Again\n";
}
else
cout<<"\nSORRY, no Movie alloted yet. Please wait for admin to initialize movies\n";
}
else
if(ch3==2)
{
ch2=0;
cout<<"Enter Password-\n";
cin>>pas;
if(strcmp(pas,"PVRproject")==0)
{
cout<<"\nWelcome Admin\n";
do
{
cout<<"\n\nADMIN Operations-\n1. Initialize a hall(at most 4)\n2. Take a look at hall layouts\n3. Take a look at the clients list\n4. Display money earned\n5. Exit as Admin\n6. End day\n";
cin>>ch4;
switch(ch4)
{
case 1: initialize();
	break;
case 2: display2();
	break;
case 3: display3();
	break;
case 4: display4();
	break;
case 5: ch2=1;
	break;
case 6: end();
	ch2=2;
	break;
default : cout<<"Wrong choice";
}
}while(ch2==0);
if(ch2==1)
cout<<"\nYou are exiting as admin\n" ;
if(ch2==2)
cout<<"\nEnd of Day\nTHANK YOU\n";
}
else
cout<<"Wrong password" ;
}
getch();
}

