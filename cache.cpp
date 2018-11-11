#include <iostream>
#include <fstream>
#include "cache.h"
#include <string>
#include <algorithm>
#include <time.h>
using namespace std;

void Mem::print_mem(string mensagem){

  cout<<endl<<mensagem<<endl;
  for (uint i=0;i<this->mem.size();i++){
    cout<<this->mem[i]<<endl;
  }
}

Mp::Mp(){
  this->mem=vector<string>();
}

Ca::Ca(uint N, Mp &mp):Cache(mp){
  this->mem=vector<string>();
  this->val=vector<string>(N,"XXXXXXXXXXXXXXXX");
  this->pos_mem=vector<string>(N,"XXXXX");
}

Cache::Cache(Mp &mp){
  this->mp=mp;

}

int Ca::find_pos(string endereco){


  for (int i=0;i<this->pos_mem.size();i++){

    if (endereco==this->pos_mem[i])
      return i;
  }

  return -1;
}




uint Ca::get_random_pos(){
  return rand()%this->pos_mem.size();
}



void Mem::read_from_file(string arquivo){
  ifstream in;
  in.open(arquivo);
  string linha;
  while(getline(in,linha)){
    this->mem.push_back(linha);
  }
}



 uint Mem::bin2dec(string bin){
  uint res=0;
  uint pos=1;

  for (int i=bin.size()-1;i>=0;i--,pos<<=1){

    if (bin[i]=='1'){
      res+=pos;
    }
  }
  return res;
}


string Mem::dec2bin(uint dec,uint N){
  string bin;
  for (uint i=0;i<N;i++,dec>>=1){
      if(dec%2==0){
        bin+='0';
      }else{
        bin+='1';
      }
  }
  reverse(bin.begin(),bin.end());
  return bin;

}

void Ca::insert_first_elements(){
  int next_cache_pos=0;
  for (;next_cache_pos<this->pos_mem.size() && this->mem.size();next_inst++){
    int cache_pos=find_pos(mem[next_inst]);
    if (cache_pos==-1){
      cache_pos=next_cache_pos++;
      cout<<endl<<endl<<"********miss********"<<endl;
      miss++;

    }else{
      cout<<endl<<endl<<"********hit********"<<endl;
      hit++;
    }

    inserir_valor(cache_pos);
    print_estado_atual(cache_pos);

  }

}

void Ca::inserir_valor(int pos){

  this->val[pos]=this->mp.mem[bin2dec(this->mem[next_inst])];
  this->pos_mem[pos]=this->mem[next_inst];

}

void Ca::print_estado_atual(int pos){

  cout<<"instrucao numero: "<<next_inst<<", na posicao da cache: "<<
  dec2bin(pos, pos_mem.size())<<" com o endereco de memoria: "<<
  pos_mem[pos]<<" o valor: "<<val[pos]<<endl<<endl;

  print_cache( pos);
}

void Ca::main_loop(){

  for(;next_inst<mem.size();next_inst++){
    int cache_pos=find_pos(mem[next_inst]);


    if (cache_pos==-1){
      cout<<endl<<endl<<"********miss********"<<endl;
      cache_pos=get_random_pos();
      miss++;
    }else{
      cout<<endl<<endl<<"********hit********"<<endl;
      hit++;
    }
    inserir_valor(cache_pos);
    print_estado_atual(cache_pos);



  }

  cout<<endl<<endl<<"*****************************************"<<endl<<endl;

  cout<<"total de hits: "<<hit<<", total de miss: "<<miss<<", taxa miss: "<<
  (float)miss/(float)(miss+hit)<<", taxa de hit:"<<(float)hit/(float)(miss+hit)<<endl;


}

void Mem::simulator(int N, string memoria_principal,string memoria_cache){
  Mp mp=Mp();
  mp.read_from_file(memoria_principal);
  Ca ca = Ca(N,mp);


  ca.read_from_file(memoria_cache);
  mp.print_mem("******** status da memoria principal ********");
  ca.print_mem("******** status das proximas instrucoes ********");
  ca.insert_first_elements();
  ca.main_loop();





}

void Ca::print_cache(int pos){
  for (int i=0; i<pos_mem.size();i++){
    if (i==pos){
      cout<<"--> ";
    }
    cout<<pos_mem[i]<<" "<<val[i]<<endl;
  }
}



int main(){
  srand (time(NULL));

  Mem::simulator(8,"ram.txt","pos_mem.txt");



  //mp.read_from_file("ram.txt");




  return 0;
}
