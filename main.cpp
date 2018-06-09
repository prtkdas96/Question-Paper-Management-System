#include<iostream>
#include<windows.h>
#include<mysql.h>
#include<string>
#include<algorithm>
#include<vector>
#include<ctime>
#include<chrono>
#include<cstdlib>
#include <map>
#include<cstring>
#include<fstream>


#define max_f 5
using namespace std;


class Db_Connection
{
    string query,temp1,temp2,temp3,temp4;;
    int qstate;
    const char *q;
    MYSQL *conn;
    MYSQL_ROW row;
    MYSQL_RES *result;

public:
    void establish_connection();
    void data_insertion(string idx,string bh,string ph ,string data);
    string get_records(string id);
    size_t getfile_data();
    //void add_block();
    void validate_block();
    string get_records_for_validation(string id);
    size_t get_file_data_for_validation(int id);

};

void  Db_Connection::establish_connection()
{
    conn = mysql_init(0);
    //string query;

    if(conn)
        cout<<"\t connection object successfully established \n\n";
    else
        cout<<"\t connection not established \n\n";

    conn = mysql_real_connect(conn,"localhost","root","","blockchain",0,NULL,0);


   if(conn)
    {
        cout<<"\t connected to mysql database!! \n\n";}

    else
    {
        cout<<"\t Some error occured while connection try again !! "<<mysql_error(conn);

    }


}

void  Db_Connection::data_insertion(string idx,string bh,string ph ,string data)
{

       query = "insert into blockdata(indexnumber,blockhash,previoushash,data) values ('"+idx+"','"+bh+"','"+ph+"','"+data+"')";
        q= query.c_str();
        qstate= mysql_query(conn,q);
        if(!qstate){
            cout<<"Data Successfully inserted....\n";
        }
         else{
        cout<<"Sorry!! some error occured .....Try again!!:  "<<mysql_error(conn)<<endl;
    }
   /* int n,i;
    string ph,bh,time,data;
    cout<<"Enter number of blocks.... \n";
    cin>>n;
    cout<<"Enter previous hash ,block hash, time and data for each block...\n";
    for(i=0;i<n;i++)
    {
        cout<<"Enter previous hash \n";
        cin>>ph;
        cout<<"Enter block hash \n";
        cin>>bh;
        //cout<<"Enter time \n";
        //cin>>time;
        cout<<"Enter data \n";
        cin>>data;
        query = "insert into blockd(previous_hash,block_hash,timestamp,data) values ('"+ph+"','"+bh+"','"+data+"')";
        q= query.c_str();
        qstate= mysql_query(conn,q);
        if(!qstate){
            cout<<"Data Successfully inserted....\n";
        }
         else{
        cout<<"Sorry!! some error occured .....Try again!!:  "<<mysql_error(conn)<<endl;
    }
    } */

}

string Db_Connection::get_records(string id)
{
    int qstate; string temp;cout<<id<<"  is what you want to search...\n\n";
    temp= "select blockhash from blockdata where indexnumber= "+id;
    qstate= mysql_query(conn,temp.c_str());
     if(!qstate)
        {
            result = mysql_store_result(conn);
            while(row=mysql_fetch_row(result))
            {
                temp1=row[0];
                //cout<<temp1;
            }
            return temp1;
        }
     else{
    cout<<"Sorry!! Some error occured while verification "<<mysql_error(conn)<<"\n\n";
 }

}


string Db_Connection::get_records_for_validation(string id)
{
    int qstate; string temp,temp_n;//cout<<id<<"  is what you want to search...\n\n";
    temp= "select blockhash , data from blockdata where indexnumber= "+id;
    qstate= mysql_query(conn,temp.c_str());
     if(!qstate)
        {
            result = mysql_store_result(conn);
            while(row=mysql_fetch_row(result))
            {
                temp1=row[1];
                temp_n=row[0];
                //cout<<temp1;
            }
            return temp1;
        }
     else{
    cout<<"Sorry!! Some error occured while verification "<<mysql_error(conn)<<"\n\n";
 }
}

size_t Db_Connection::getfile_data()
{
    string d;temp2="";
    // open a file in read mode.
   ifstream file("5.txt");
   if(file.is_open())
   {
       while(getline(file,d))
       {
           temp2+=d;
           cout<<temp2<<"\n";
       }
       hash<string> hash1;
       return hash1(temp2);
       //return temp3;
       file.close();

   }
   else
   {
       cout<<"Some error occured while opening a file....\n\n";
   }

}




size_t Db_Connection::get_file_data_for_validation(int id)
{
    string temp_string="",d,c;
    c=to_string(id)+".txt";


   ifstream file(c);
   if(file.is_open())
   {
       while(getline(file,d))
       {
           temp_string+=d;
           //cout<<temp2<<"\n";
       }
       hash<string> hash1;
       //cout<<hash1(temp_string)<<" is the hash being returned...\n";
       return hash1(temp_string);
       //return temp3;
       file.close();
    }
    else
   {
       cout<<"Some error occured while opening a file....\n\n";
   }

    /*else if(id==3)
    {

   ifstream file("3.txt");
   if(file.is_open())
   {
       while(getline(file,d))
       {
           temp_string+=d;
           //cout<<temp2<<"\n";
       }
       hash<string> hash1;
       cout<<hash1(temp_string)<<" is the hash being returned...\n";
       return hash1(temp_string);
       //return temp3;
       file.close();
    }
    else
   {
       cout<<"Some error occured while opening a file....\n\n";
   }}
    if(id==4)
    {

   ifstream file("4.txt");
   if(file.is_open())
   {
       while(getline(file,d))
       {
           temp_string+=d;
           //cout<<temp2<<"\n";
       }
       hash<string> hash1;
       cout<<hash1(temp_string)<<" is the hash being returned...\n";
       return hash1(temp_string);
       //return temp3;
       file.close();
    }
    else
   {
       cout<<"Some error occured while opening a file....\n\n";
   }}

    if(id==5)
    {

   ifstream file("5.txt");
   if(file.is_open())
   {
       while(getline(file,d))
       {
           temp_string+=d;
           //cout<<temp2<<"\n";
       }
       hash<string> hash1;
       cout<<hash1(temp_string)<<" is the hash being returned...\n";
       return hash1(temp_string);
       //return temp3;
       file.close();
    }
    else
   {
       cout<<"Some error occured while opening a file....\n\n";
   }} */



}



void Db_Connection::validate_block()
{
    int i,flag=0;string file_hash,hash_from_db;
    /*file_hash= to_string(get_file_data_for_validation(i));
    hash_from_db= get_records_for_validation(to_string(i));
    cout<<hash_from_db<<"is the hash retrieved from database.....\n";
    cout<<file_hash<<" is the hash of the file calculated....\n";
    if(file_hash.compare(hash_from_db)==0)
        {
            cout<<"chain is valid....\n\n";
        }*/
    for(i=2;i<=max_f;i++)
    {
        file_hash= to_string(get_file_data_for_validation(i));
        hash_from_db= get_records_for_validation(to_string(i));
        if(file_hash.compare(hash_from_db)!=0)
        {
            cout<<"Question paper has been tampered...."<<" tampering is done in "<<i<<" th block \n";
            cout<<"So chain is not valid...\n\n";
            flag=1;
            break;
        }
        else
        {
            cout<<"Block "<<i-1<<" is valid.....\n\n";
        }

    }
    if(flag==0)
        cout<<"....Question Papers remain untampered. The complete Blockchain is valid....\n\n";
}
//BLOCK
class Block{
    protected:
        int index;
        size_t blockHash;
        size_t previousHash;
        size_t generateHash();
        string data;

    public:
        Block(int idx, string d, size_t prevHash);
        size_t getHash();
        size_t getPreviousHash();
        bool isHashValid();
};



Block::Block(int idx, string d, size_t prevHash){
    index=idx;
    data=d;
    previousHash=prevHash;
    blockHash=generateHash();
}


size_t Block::generateHash(){

    string a,b,c;
    hash<string> hash1;
    hash<size_t> hash2;
    hash<size_t> finalHash;
    string toHash=to_string(index)+to_string(blockHash)+data;
    cout<<toHash<<"Is the data to be hashed...... \n\n";
    return finalHash(hash1(toHash)+ hash2(previousHash));
}

size_t Block::getHash(){
    return blockHash;
}

size_t Block::getPreviousHash(){
    return previousHash ;
}

bool Block::isHashValid(){
    return generateHash() == blockHash;
}



int main()
{
    string t1,td; long ls;
    size_t res;int idx=max_f;

    Db_Connection u1;
    u1.establish_connection();

    //FILE *pFile=fopen("2.txt","w");

    /* t1= u1.get_records(to_string(idx-1));
    //cout<<t1<<"is the previous hash....\n";
    sscanf(t1.c_str(), "%zu", &res);
    cout<<t1<<"  is theprevious blockhash...\n\n";
    //cout<<u1.getfile_data()<<"\n\n";
    td= to_string(u1.getfile_data());
    cout<<"\n"<<td<<"is the returnd hash ....\n\n";



    Block b1(idx,td,res);
    size_t t2=b1.getHash();
    //string a= to_string(t1);
    u1.data_insertion(to_string(idx),to_string(t2),t1,td); */
    u1.validate_block();




    return 0;
}
