#ifndef __NOTA_H__
#define __NOTA_H__

#include <string>
#include <list>

class Nota {
private:
  double nota;
  std::string nomeNota;
//  static std::list<const Nota> listaNotas;

  Nota(double, std::string);
public:
  static const Nota La;
  static const Nota LaSustenido;
  static const Nota Si;
  static const Nota Do;
  static const Nota DoSustenido;
  static const Nota Re;
  static const Nota ReSustenido;
  static const Nota Mi;
  static const Nota Fa;
  static const Nota FaSustenido;
  static const Nota Sol;
  static const Nota SolSustenido;

  operator double() const;
  operator std::string() const;

  std::string nome();
  double frequencia();

//  static std::list<const Nota> obterNotas();
  static const Nota nomeParaNota(std::string nome);

};

#endif
