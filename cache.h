
#include <vector>
using namespace std;



class Mem{
public:
   void read_from_file(string arquivo);
   void print_mem(string mensagem);
   static uint bin2dec(string bin);
   static string dec2bin(uint dec,uint N);
   static void simulator(int N,string memoria_principal,string memoria_cache);
   std::vector<string> mem;


};

class Mp: public Mem{
public:
  Mp();

};


class Cache:public Mem{

public:
  explicit Cache(Mp &mp);
protected:
  uint miss=0;
  uint hit=0;
  uint next_inst=0;

  Mp mp;
};

class Ca: public Cache {
public:
  Ca(uint N,Mp &mp);
  virtual int find_pos(string endereco);
  virtual void insert_first_elements();
  virtual uint get_random_pos();
  virtual void main_loop();
  virtual void inserir_valor(int pos);
  virtual void print_estado_atual(int pos);
  virtual void print_cache(int pos);

private:
  vector<string> val;
  vector<string> pos_mem;

};
