#pragma once

#include <stdio.h>
#include <string.h>

typedef struct registo
{
	int codigo; /*código do meio de mobilidade elétrica*/
	char tipo[50]; /*bicicleta, trotinete*/
	float bateria; /*55.6%*/
	float autonomia; /*25Km*/
	float custo; /*Custo em %*/
	char geocodigo[30];/*Geocodigo de localização de um meio de mobilidade*/
	char estadoaluguer[50]; /*Parametro para guardar se o meio de mobilidade eletrica esta disponivel ou nao*/
	struct registo* seguinte; /*endereço de memória para uma struct registo*/
} Meio;

typedef struct RegistoCliente
{
	char nome[50]; /*Nome do Cliente*/
	char morada[70]; /*Morada*/
	int nif; /*Nif*/
	float saldo; /*Slado disponivel*/
	struct registo* seguinte; /*endereço de memória para uma struct registo*/
} Cliente;

typedef struct RegistoGestor
{
	char Nomegestor[30];/*Nome do Gestor*/
	float codigogestor;/*Codigo Gestor*/
	char PalavraPasse[20]; /*Passe de acesso gestor*/
	struct registo* seguinte; /*endereço de memória para uma struct registo*/
} Gestor;





Meio* InserirMeio(Meio* inicio, int cod, char tipo[], float bat, float aut, float custo, char geo[]);
int ExisteMeio(Meio* inicio, int cod);
void ListarMeios(Meio* inicio);
Meio* RemoverMeio(Meio* inicio, int cod);
Meio* LerMeios();
int GuardarMeios(Meio* inicio);
Cliente* InserirCliente(Cliente* inicio, char nome[], char morada[], int nif, float saldo);
Cliente* RemoverCliente(Cliente* inicio, char nome);
void ListarClientes(Cliente* inicio);
int GuardarCliente(Cliente* inicio);
Cliente* LerClientes();
Gestor* LerGestor();
Gestor* InserirGestor(Gestor* inicio, char nomegestor[], float codigo, char palavrapasse);
int GuardarGestor(Gestor* inicio);
void ListarGestor(Gestor* inicio);
Gestor* RemoverGestor(Gestor* inicio, char nome);
void ListagemGeoCodigo(Meio* inicio, char geocodigo);
void ListarOrdemDecrescente(Meio* inicio);
int RegistoAluguer(Meio* inicio, int codigo);
Meio* AlterarMeio(Meio* inicio, int cod, char tipo[], float bat, float aut, float custo, char geo[], char estadoaluguer[]);
Cliente* AlterarCliente(Cliente* inicio, char nome[], char morada[], int nif, float saldo);
Gestor* AlterarGestor(Gestor* inicio, char nomegestor[], float codigogestor, char palavrapasse[]);

