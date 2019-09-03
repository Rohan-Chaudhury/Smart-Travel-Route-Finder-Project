#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <boost/algorithm/string.hpp>
#include <sstream>
#include <boost/lexical_cast.hpp>
using namespace std;
int main()
{

  vector <vector<string> > v0;

  string line;
  fstream file;
  file.open("city_codes.dat", ios::in | ios::out);
  int i=0;
  int pos1=0;
  int index=0;
  while(std::getline(file, line))
    {   vector<string> v1;
        if(i==0){
            pos1=line.find("CODE");
        }
        else{
          v1.push_back(boost::lexical_cast<string>(index));
          int pos2=line.find(" ");
          string city_name=line.substr(0,pos2);
          v1.push_back(city_name);
          string city_code=line.substr(pos1,3);
          v1.push_back(city_code);
          string temp="End";
          v1.push_back(temp);
          index++;
          //v1.push_back("test");
          //cout<<pos1<<endl;
          //cout<<line.size()<<endl;
          v0.push_back(v1);
        }

        i++;
    }
    string ccode[19][4];
	   for (int i = 0; i < 19; i++) {
        for (int j = 0; j < 4; j++)
        {
          ccode[i][j]=v0[i][j];
//cout<<ccode[i][j]<<"------";
          }
//cout<<endl;
    }

  file.close();






  vector <vector<string> > v2;


  file.open("routes.dat", ios::in | ios::out);
  i=0;
  pos1=0;
  int pos2=0;
  int pos3=0;
  int pos4=0;

  string rest=" ";
  while(std::getline(file, line))
    {   vector<string> v3;

        if(i==0){
            pos1=line.find("SRC");
            pos2=line.find("DEST");
            pos3=line.find("KMs");
            pos4=line.find("COST");
        }
        else{
          int pos5=line.find(" ");
          string route_no=line.substr(0,pos5);

          v3.push_back(route_no);
          rest=line.substr(pos1);
          pos5=rest.find(" ");
          v3.push_back(rest.substr(0,pos5));
          rest=line.substr(pos2);
          pos5=rest.find(" ");
          v3.push_back(rest.substr(0,pos5));
          rest=line.substr(pos3);
          pos5=rest.find(" ",2);
          v3.push_back(rest.substr(0,pos5));
          rest=line.substr(pos4);
          pos5=rest.find(" ",2);
          v3.push_back(rest.substr(0,pos5));
          v2.push_back(v3);
        }

        i++;
    }
    string route[31][5];
   for (int i = 0; i < v2.size(); i++) {
        for (int j = 0; j < v2[i].size(); j++)
        {
          route[i][j]=v2[i][j];
//cout<<route[i][j]<<"--------";
          }
//cout<<endl;
    }

  file.close();
int INF= 999999;
  int ncity=19;
  int graph[ncity][ncity];
  int graph2[ncity][ncity];
  for (int i = 0; i < 19; i++) {
      for (int j = 0; j < 19; j++)
      {if(i==j){
          graph[i][j]=0;
            graph2[i][j]=0;
}
else{
    graph[i][j]=INF;
    graph2[i][j]=INF;
}
        }

  }
  int temp1=-1;
  int temp2=-1;
  for (int i = 0; i < 31; i++) {

      for (int j=0; j<19; j++)
      {

        if(strcmp(route[i][1].c_str(),ccode[j][2].c_str())==0){
          temp1=atoi(ccode[j][0].c_str());


}

      if(strcmp(route[i][2].c_str(),ccode[j][2].c_str())==0){
        temp2=atoi(ccode[j][0].c_str());
}
        }
        if(temp1!=-1 && temp2!=-1)
        {


          graph[temp1][temp2]=atoi(route[i][3].c_str());
  graph2[temp1][temp2]=atoi(route[i][4].c_str());
        }
        temp1=-1;
        temp2=-1;

      }

/*      for(int k=0;k<ncity; k++){
            for (int i = 0; i < ncity; i++) {
                for (int j = 0; j < ncity; j++)
                {
                  if (graph[i][k] + graph[k][j] < graph[i][j])
                            graph[i][j] = graph[i][k] + graph[k][j];

                  }

            }
          }*/
      int V=ncity;
/*     for (int i = 0; i < V; i++)
      {
          for (int j = 0; j < V; j++)
          {

                  cout<<graph[i][j]<<" ";
          }
          cout<<endl;}*/
file.open("STS_config.dat", ios::in | ios::out);
index=0;
int pos8=-1;
string OPTIMALITY;
string OUTPUT_FORMAT;
while(std::getline(file, line)){
  if(index==2){
  int pos6=line.find("=");
pos8=line.size();
  OPTIMALITY=line.substr(pos6+2,pos8-pos6-3);
  }
  if(index==5){
    int pos7=line.find("=");
    int pos9=line.size();
    OUTPUT_FORMAT=line.substr(pos7+2,pos9-pos7-3);

  }
  index++;
}
file.close();
//cout<<pos8<<endl;
cout<<OPTIMALITY<<"---->"<<endl;
cout<<OUTPUT_FORMAT<<"----> "<<endl;
      file.open("find_routes.dat", ios::in | ios::out);
  index=0;
  int to=0;
      while(std::getline(file, line)){
          if(index==0||index==1){ }
      else if(index==2)
        {

        to=line.find("To");
      }
      else{
        string rsrc=line.substr(0,3);
        string rdes=line.substr(to,3);
        temp1=-1;
        temp2=-1;
        for (int j=0; j<19; j++)
        {

          if(strcmp(rsrc.c_str(),ccode[j][2].c_str())==0){
            temp1=atoi(ccode[j][0].c_str());


  }

        if(strcmp(rdes.c_str(),ccode[j][2].c_str())==0){
          temp2=atoi(ccode[j][0].c_str());
  }
          }
          if(temp1!=-1 && temp2!=-1)
          {
if(OPTIMALITY=="LEAST_DISTANCE" && OUTPUT_FORMAT=="CITY_CODES"){

int temp3=-1;
int temp4=-1;
int temp5=-1;
int dist=0;
int dist2=0;
for(int k=0;k<19;k++){
  if(graph[temp1][temp2]>graph[temp1][k]+graph[k][temp2])
  {
    dist=graph[temp1][k]+graph[k][temp2];
    temp3=k;
//    graph[temp1][temp2]=dist;
    cout<<rsrc<<"--->"<< ccode[temp3][2]<<"---->"<<rdes<<"="<<boost::lexical_cast<string>(graph[temp1][temp3])<<"+"<<boost::lexical_cast<string>(graph[temp3][temp2])<<"="<<dist<<endl;
  }

}
for(int m=0;m<V;m++){
for(int k=0;k<V;k++){
  if(graph[temp1][temp2]>graph[temp1][k]+graph[k][m]+graph[m][temp2])
  {
    dist2=graph[temp1][k]+graph[k][m]+graph[m][temp2];
    temp3=k;
    temp4=m;
  //  graph[temp1][temp2]=dist;

if(strcmp(rsrc.c_str(),ccode[temp3][2].c_str())==0||strcmp(ccode[temp3][2].c_str(),ccode[temp4][2].c_str())==0||strcmp(ccode[temp4][2].c_str(),rdes.c_str())==0){}
else{
    cout<<rsrc<<"--->"<< ccode[temp3][2] <<"--->"<<
ccode[temp4][2]<<"---->"<<rdes<<"="<<boost::lexical_cast<string>(graph[temp1][temp3])<<"+"<<boost::lexical_cast<string>(graph[temp3][temp4])<<"+"<<boost::lexical_cast<string>(graph[temp4][temp2])<<"="<<dist2<<endl;
}
}

}
}


if(temp3==-1 && temp4==-1){
if(graph[temp1][temp2]==INF){
  cout<<rsrc<<"--->"<<rdes<<"="<<"Not Possible"<<endl;}
else{ cout<<rsrc<<"--->"<<rdes<<"="<<graph[temp1][temp2]<<endl;
}
}
if(temp3!=-1 && temp4==-1){
//cout<<rsrc<<"--->"<< ccode[temp3][2]<<"---->"<<rdes<<"="<<boost::lexical_cast<string>(graph[temp1][temp3])<<"+"<<boost::lexical_cast<string>(graph[temp3][temp2])<<"="<<dist<<endl;
}
if(temp3!=-1 && temp4!=-1){
//cout<<rsrc<<"--->"<< ccode[temp3][2] <<"--->"<< ccode[temp4][2]<<"---->"<<rdes<<"="<<boost::lexical_cast<string>(graph[temp1][temp3])<<"+"<<boost::lexical_cast<string>(graph[temp3][temp4])<<"+"<<boost::lexical_cast<string>(graph[temp4][temp2])<<"="<<dist<<endl;
}

}
if(OPTIMALITY=="LEAST_COST" && OUTPUT_FORMAT=="CITY_CODES"){

int temp3=-1;
int temp4=-1;
int temp5=-1;
int dist=0;
for(int k=0;k<19;k++){
  if(graph2[temp1][temp2]>graph2[temp1][k]+graph2[k][temp2])
  {
    dist=graph2[temp1][k]+graph2[k][temp2];
    temp3=k;
//    graph2[temp1][temp2]=dist;
    cout<<rsrc<<"--->"<< ccode[temp3][2]
<<"---->"<<rdes<<"="<<boost::lexical_cast<string>(graph2[temp1][temp3])<<"+"<<boost::lexical_cast<string>(graph2[temp3][temp2])<<"="<<dist<<endl;
  }

}
for(int m=0;m<V;m++){
for(int k=0;k<V;k++){
  if(graph2[temp1][temp2]>graph2[temp1][k]+graph2[k][m]+graph2[m][temp2])
  {
    dist=graph2[temp1][k]+graph2[k][m]+graph2[m][temp2];
    temp3=k;
    temp4=m;
  //  graph2[temp1][temp2]=dist;
if(strcmp(rsrc.c_str(),ccode[temp3][2].c_str())==0||strcmp(ccode[temp3][2].c_str(),ccode[temp4][2].c_str())==0||strcmp(ccode[temp4][2].c_str(),rdes.c_str())==0){}
else{
    cout<<rsrc<<"--->"<< ccode[temp3][2] <<"--->"<< ccode[temp4][2]<<"---->"<<rdes<<"="<<boost::lexical_cast<string>(graph2[temp1][temp3])<<"+"<<boost::lexical_cast<string>(graph2[temp3][temp4])<<"+"<<boost::lexical_cast<string>(graph2[temp4][temp2])<<"="<<dist<<endl;
  }
}
}
}


if(temp3==-1 && temp4==-1){
  if(graph[temp1][temp2]==INF){
  cout<<rsrc<<"--->"<<rdes<<"="<<"Not Possible"<<endl;}
else{ cout<<rsrc<<"--->"<<rdes<<"="<<graph[temp1][temp2]<<endl;
}

}
if(temp3!=-1 && temp4==-1){
  //cout<<rsrc<<"--->"<< ccode[temp3][2]<<"---->"<<rdes<<"="<<boost::lexical_cast<string>(graph[temp1][temp3])<<"+"<<boost::lexical_cast<string>(graph[temp3][temp2])<<"="<<dist<<endl;
}
if(temp3!=-1 && temp4!=-1){
  //cout<<rsrc<<"--->"<< ccode[temp3][2] <<"--->"<< ccode[temp4][2]<<"---->"<<rdes<<"="<<boost::lexical_cast<string>(graph[temp1][temp3])<<"+"<<boost::lexical_cast<string>(graph[temp3][temp4])<<"+"<<boost::lexical_cast<string>(graph[temp4][temp2])<<"="<<dist<<endl;
}

}
if(OPTIMALITY=="LEAST_DISTANCE" && OUTPUT_FORMAT=="ROUTE_NOS"){
string route1,route2,route3;
int temp3=-1;
int temp4=-1;
int temp5=-1;
int dist=0;
for(int k=0;k<19;k++){
  if(graph[temp1][temp2]>graph[temp1][k]+graph[k][temp2])
  {
    dist=graph[temp1][k]+graph[k][temp2];
    temp3=k;
    //graph[temp1][temp2]=dist;
      for(int i=0;i<31;i++)
      {
      if(strcmp(rsrc.c_str(),route[i][1].c_str())==0 && strcmp(ccode[temp3][2].c_str(),route[i][2].c_str())==0) {
        route1=route[i][0];
      }
      if(strcmp(ccode[temp3][2].c_str(),route[i][1].c_str())==0 && strcmp(rdes.c_str(),route[i][2].c_str())==0) {
        route2=route[i][0];
      }
      }


cout<<route1<<"---->"<<route2<<"="<<boost::lexical_cast<string>(graph[temp1][temp3])<<"+"<<boost::lexical_cast<string>(graph[temp3][temp2])<<"="<<dist<<endl;


    }

}
for(int m=0;m<V;m++){
for(int k=0;k<V;k++){
  if(graph[temp1][temp2]>graph[temp1][k]+graph[k][m]+graph[m][temp2])
  {
    dist=graph[temp1][k]+graph[k][m]+graph[m][temp2];
    temp3=k;
    temp4=m;
   // graph[temp1][temp2]=dist;
                 for(int i=0;i<31;i++)
      {
      if(strcmp(rsrc.c_str(),route[i][1].c_str())==0 && strcmp(ccode[temp3][2].c_str(),route[i][2].c_str())==0) {
        route1=route[i][0];
      }
      if(strcmp(ccode[temp3][2].c_str(),route[i][1].c_str())==0 && strcmp(ccode[temp4][2].c_str(),route[i][2].c_str())==0) {
        route2=route[i][0];
      }
      if(strcmp(ccode[temp4][2].c_str(),route[i][1].c_str())==0 && strcmp(rdes.c_str(),route[i][2].c_str())==0) {
        route3=route[i][0];
      }

      }

if(strcmp(rsrc.c_str(),ccode[temp3][2].c_str())==0||strcmp(ccode[temp3][2].c_str(),ccode[temp4][2].c_str())==0||strcmp(ccode[temp4][2].c_str(),rdes.c_str())==0){}
else{

cout<<route1<<"---->"<<route2<<"------>"<<route3<<"="<<boost::lexical_cast<string>(graph[temp1][temp3])<<"+"<<boost::lexical_cast<string>(graph[temp3][temp4])<<"+"<<boost::lexical_cast<string>(graph[temp4][temp2])<<"="<<dist<<endl;
}


  }

}
}


if(temp3==-1 && temp4==-1){
  if(graph[temp1][temp2]==INF){
  cout<<rsrc<<"--->"<<rdes<<"="<<"Not Possible"<<endl;}
else{  for(int i=0;i<31;i++)
      {
      if(strcmp(rsrc.c_str(),route[i][1].c_str())==0 && strcmp(rdes.c_str(),route[i][2].c_str())==0) {
        route1=route[i][0];
      }
      }


cout<<route1<<"="<<boost::lexical_cast<string>(graph[temp1][temp2])<<endl;

}

}
if(temp3!=-1 && temp4==-1){
  //cout<<rsrc<<"--->"<< ccode[temp3][2]<<"---->"<<rdes<<"="<<boost::lexical_cast<string>(graph[temp1][temp3])<<"+"<<boost::lexical_cast<string>(graph[temp3][temp2])<<"="<<dist<<endl;
}
if(temp3!=-1 && temp4!=-1){
  //cout<<rsrc<<"--->"<< ccode[temp3][2] <<"--->"<< ccode[temp4][2]<<"---->"<<rdes<<"="<<boost::lexical_cast<string>(graph[temp1][temp3])<<"+"<<boost::lexical_cast<string>(graph[temp3][temp4])<<"+"<<boost::lexical_cast<string>(graph[temp4][temp2])<<"="<<dist<<endl;
}

}
if(OPTIMALITY=="LEAST_COST" && OUTPUT_FORMAT=="ROUTE_NOS"){

  int temp3=-1;
  int temp4=-1;
  int temp5=-1;
  int temp6= -1;
  int temp7= -1;
  int dist=0;
  string route1;
  string route2;
  string route3;
  for(int k=0;k<19;k++){
    if(graph2[temp1][temp2]>graph2[temp1][k]+graph2[k][temp2])
    {
      dist=graph2[temp1][k]+graph2[k][temp2];
      temp3=k;
    //  graph2[temp1][temp2]=dist;
      for(int i=0;i<31;i++)
      {
      if(strcmp(rsrc.c_str(),route[i][1].c_str())==0 && strcmp(ccode[temp3][2].c_str(),route[i][2].c_str())==0) {
        route1=route[i][0];
      }
      if(strcmp(ccode[temp3][2].c_str(),route[i][1].c_str())==0 && strcmp(rdes.c_str(),route[i][2].c_str())==0) {
        route2=route[i][0];
      }
      }

      cout<<route1<<"---->"<<route2<<"="<<boost::lexical_cast<string>(graph2[temp1][temp3])<<"+"<<boost::lexical_cast<string>(graph2[temp3][temp2])<<"="<<dist<<endl;

  }


  }
  for(int m=0;m<V;m++){
  for(int k=0;k<V;k++){
    if(graph2[temp1][temp2]>graph2[temp1][k]+graph2[k][m]+graph2[m][temp2])
    {
      dist=graph2[temp1][k]+graph2[k][m]+graph2[m][temp2];
      temp3=k;
      temp4=m;
     // graph2[temp1][temp2]=dist;
             for(int i=0;i<31;i++)
      {
      if(strcmp(rsrc.c_str(),route[i][1].c_str())==0 && strcmp(ccode[temp3][2].c_str(),route[i][2].c_str())==0) {
        route1=route[i][0];
      }
      if(strcmp(ccode[temp3][2].c_str(),route[i][1].c_str())==0 && strcmp(ccode[temp4][2].c_str(),route[i][2].c_str())==0) {
        route2=route[i][0];
      }
      if(strcmp(ccode[temp4][2].c_str(),route[i][1].c_str())==0 && strcmp(rdes.c_str(),route[i][2].c_str())==0) {
        route3=route[i][0];
      }

      }

if(strcmp(rsrc.c_str(),ccode[temp3][2].c_str())==0||strcmp(ccode[temp3][2].c_str(),ccode[temp4][2].c_str())==0||strcmp(ccode[temp4][2].c_str(),rdes.c_str())==0){}
else{

cout<<route1<<"---->"<<route2<<"------>"<<route3<<"="<<boost::lexical_cast<string>(graph2[temp1][temp3])<<"+"<<boost::lexical_cast<string>(graph2[temp3][temp4])<<"+"<<boost::lexical_cast<string>(graph2[temp3][temp2])<<"="<<dist<<endl;
}

  }
  }

}
  if(temp3==-1 && temp4==-1){
    if(graph[temp1][temp2]==INF){
  cout<<rsrc<<"--->"<<rdes<<"="<<"Not Possible"<<endl;}
else{  for(int i=0;i<31;i++)
      {
      if(strcmp(rsrc.c_str(),route[i][1].c_str())==0 && strcmp(rdes.c_str(),route[i][2].c_str())==0) {
        route1=route[i][0];
      }
      }


cout<<route1<<"="<<boost::lexical_cast<string>(graph2[temp1][temp2])<<endl;

}

  }
  if(temp3!=-1 && temp4==-1){
    //cout<<rsrc<<"--->"<< ccode[temp3][2]<<"---->"<<rdes<<"="<<boost::lexical_cast<string>(graph[temp1][temp3])<<"+"<<boost::lexical_cast<string>(graph[temp3][temp2])<<"="<<dist<<endl;
  }
  if(temp3!=-1 && temp4!=-1){
    //cout<<rsrc<<"--->"<< ccode[temp3][2] <<"--->"<< ccode[temp4][2]<<"---->"<<rdes<<"="<<boost::lexical_cast<string>(graph[temp1][temp3])<<"+"<<boost::lexical_cast<string>(graph[temp3][temp4])<<"+"<<boost::lexical_cast<string>(graph[temp4][temp2])<<"="<<dist<<endl;
  }

}

          }

      }
        index++;
      }
file.close();
  return 0;
}
