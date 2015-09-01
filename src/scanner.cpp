#include "scanner.h"

Scanner::Scanner(char* arquivo) {
	this->arquivo.open(arquivo);
	this->linha = 1;
	this->criarTabelaSimbolos();

	if (!this->arquivo.is_open())
		throw "Erro ao abrir o arquivo!\n";
}

Scanner::~Scanner() {
	if (this->arquivo.is_open())
		this->arquivo.close();
}

int Scanner::getLinha() {
	return this->linha;
}

bool Scanner::isDigit(char c) {
	int ch = (int)c;
	return (ch >= 48 && ch <= 57);
}

bool Scanner::isLowerLetter(char c) {
	int ch = (int)c;
	return (ch >= 97 && ch <= 122);
}

bool Scanner::isUperLetter(char c) {
	int ch = (int)c;
	return (ch >= 65 && ch <= 90);
}

bool Scanner::isLetter(char c) {
	int ch = (int)c;
	return ((ch >= 65 && ch <= 90) || (ch >= 97 && ch <= 122));
}

bool Scanner::isBlank(char ch) {
	return (ch == '\n' || ch == '\t' || ch == '\b');
}

bool Scanner::isSimbolo(char ch) {
	return (ch == '(' || ch == ')' || ch == ';' || ch == '<' || ch == ':' ||
			ch == '.' || ch == '%' || ch == '+' || ch == '-' || ch == '*');
}

int Scanner::consultarTabelaSimbolos(std::string token) {
	if (this->tabelaSimbolos.find(token) != this->tabelaSimbolos.end())
		return this->tabelaSimbolos[token];

	return TOKEN_INVALIDO;
}

void Scanner::criarTabelaSimbolos() {
	this->tabelaSimbolos["tempo"] = TEMPO;
	this->tabelaSimbolos["musica"] = MUSICA;
	this->tabelaSimbolos["faca"] = FACA;
	this->tabelaSimbolos["repetir"] = REPETIR;
	this->tabelaSimbolos["tocar"] = TOCAR;
	this->tabelaSimbolos["se"] = SE;
	this->tabelaSimbolos["senao"] = SENAO;
	this->tabelaSimbolos["fim"] = FIM;
	this->tabelaSimbolos["pausar"] = PAUSAR;
	this->tabelaSimbolos["a"] = VARIAVEL;
	this->tabelaSimbolos["b"] = VARIAVEL;
	this->tabelaSimbolos["c"] = VARIAVEL;
	this->tabelaSimbolos["d"] = VARIAVEL;
	this->tabelaSimbolos["e"] = VARIAVEL;
	this->tabelaSimbolos["f"] = VARIAVEL;
	this->tabelaSimbolos["g"] = VARIAVEL;
	this->tabelaSimbolos["h"] = VARIAVEL;
	this->tabelaSimbolos["i"] = VARIAVEL;
	this->tabelaSimbolos["j"] = VARIAVEL;
	this->tabelaSimbolos["k"] = VARIAVEL;
	this->tabelaSimbolos["l"] = VARIAVEL;
	this->tabelaSimbolos["m"] = VARIAVEL;
	this->tabelaSimbolos["n"] = VARIAVEL;
	this->tabelaSimbolos["o"] = VARIAVEL;
	this->tabelaSimbolos["p"] = VARIAVEL;
	this->tabelaSimbolos["q"] = VARIAVEL;
	this->tabelaSimbolos["r"] = VARIAVEL;
	this->tabelaSimbolos["s"] = VARIAVEL;
	this->tabelaSimbolos["t"] = VARIAVEL;
	this->tabelaSimbolos["u"] = VARIAVEL;
	this->tabelaSimbolos["v"] = VARIAVEL;
	this->tabelaSimbolos["w"] = VARIAVEL;
	this->tabelaSimbolos["x"] = VARIAVEL;
	this->tabelaSimbolos["y"] = VARIAVEL;
	this->tabelaSimbolos["z"] = VARIAVEL;
	this->tabelaSimbolos["A"] = NOTA;
	this->tabelaSimbolos["A#"] = NOTA;
	this->tabelaSimbolos["B"] = NOTA;
	this->tabelaSimbolos["C"] = NOTA;
	this->tabelaSimbolos["C#"] = NOTA;
	this->tabelaSimbolos["D"] = NOTA;
	this->tabelaSimbolos["D#"] = NOTA;
	this->tabelaSimbolos["E"] = NOTA;
	this->tabelaSimbolos["F"] = NOTA;
	this->tabelaSimbolos["F#"] = NOTA;
	this->tabelaSimbolos["G"] = NOTA;
	this->tabelaSimbolos["G#"] = NOTA;
	this->tabelaSimbolos[";"] = PONTO_VIRGULA;
	this->tabelaSimbolos["="] = IGUAL;
	this->tabelaSimbolos["("] = ABRE_PARENTESES;
	this->tabelaSimbolos[")"] = FECHA_PARENTESES;
	this->tabelaSimbolos[":"] = DOIS_PONTOS;
	this->tabelaSimbolos["."] = PONTO;
	this->tabelaSimbolos["%"] = PORCENTO;
	this->tabelaSimbolos["=="] = IGUAL_IGUAL;
	this->tabelaSimbolos["!="] = DIFERENTE;
	this->tabelaSimbolos["<"] = MENOR;
	this->tabelaSimbolos[">"] = MAIOR;
	this->tabelaSimbolos["=<"] = IGUAL_MENOR;
	this->tabelaSimbolos[">="] = MAIOR_IGUAL;
	this->tabelaSimbolos["+"] = MAIS;
	this->tabelaSimbolos["-"] = MENOS;
	this->tabelaSimbolos["*"] = VEZES;
	this->tabelaSimbolos["/"] = DIVIDIDO;
	this->tabelaSimbolos[","] = VIRGULA;
}

void Scanner::ungetChar(char ch) {
	if (ch == '\n') {
		this->linha--;
	}
	this->arquivo.unget();
}

Lexema Scanner::getLexema() {
	Lexema lexema;
	char ch;

	lexema.tipo = FIM_ARQ_NORMAL;
	lexema.token = "";
	int estado = 1;

	while (estado != 10) {
		this->arquivo >> std::noskipws >> ch;

		if (ch == '\n')
			this->linha++;

		if ((this->arquivo.eof() || this->arquivo.fail())) {
			if (estado != 1)
				lexema.tipo = FIM_ARQ_INEXPERADO;

			break;
		}

		switch (estado) {
			case 1:
				if (Scanner::isBlank(ch))
					continue;
				if (Scanner::isSimbolo(ch)) {
					lexema.token += ch;
					lexema.tipo = this->consultarTabelaSimbolos(lexema.token);
					estado = 10;
				}
				if (ch == '=') {
					lexema.token += ch;
					estado = 2;
				} else if (ch == '>') {
					lexema.token += ch;
					estado = 3;
				} else if (ch == '!') {
					lexema.token += ch;
					estado = 4;
				} else if (Scanner::isDigit(ch)) {
					lexema.token += ch;
					estado = 5;
				} else if (ch == '"') {
					estado = 6;
				} else if (Scanner::isLetter(ch)) {
					lexema.token += ch;
					estado = 7;
				} else if (ch == '/') {
					estado = 8;
				}
				break;
			case 2:
				if (ch == '<') {
					lexema.token += ch;
					lexema.tipo = this->consultarTabelaSimbolos(lexema.token);
				} else if (ch == '=') {
					lexema.token += ch;
					lexema.tipo = this->consultarTabelaSimbolos(lexema.token);
				} else {
					lexema.tipo = this->consultarTabelaSimbolos(lexema.token);
					this->ungetChar(ch);
				}
				estado = 10;
				break;
			case 3:
				if (ch == '=') {
					lexema.token += ch;
					lexema.tipo = this->consultarTabelaSimbolos(lexema.token);
				} else {
					lexema.tipo = this->consultarTabelaSimbolos(lexema.token);
					this->ungetChar(ch);
				}
				estado = 10;
				break;
			case 4:
				if (ch == '=') {
					lexema.token += ch;
					lexema.tipo = this->consultarTabelaSimbolos(lexema.token);
				} else {
					lexema.tipo = TOKEN_INVALIDO;
				}
				estado = 10;
				break;
			case 5:
				if (Scanner::isDigit(ch)) {
					lexema.token += ch;
				} else {
					lexema.tipo = NUMERO;
					this->ungetChar(ch);
					estado = 10;
				}
				break;
			case 6:
				if (ch != '"') {
					lexema.token += ch;
				} else {
					lexema.tipo = STRING;
					estado = 10;
				}
				break;
			case 7:
				if (Scanner::isLetter(ch) || ch == '#') {
					lexema.token += ch;
				} else {
					lexema.tipo = this->consultarTabelaSimbolos(lexema.token);
					this->ungetChar(ch);
					estado = 10;
				}
				break;
			case 8:
				if (ch == '/') {
					estado = 9;
				} else {
					lexema.token += ch;
					lexema.tipo = this->consultarTabelaSimbolos(lexema.token);
					estado = 10;
				}
				break;
			case 9:
				if (ch == '\n')
					estado = 1;
		}
	}
	return lexema;
}