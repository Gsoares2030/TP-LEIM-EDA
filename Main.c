/*****************************************************************//**
 **\author: Gonçalo Soares
 * \brief: Ficheiro onde vão ser testadas as funções
 *  
  *********************************************************************/
#include <stdio.h>
#include "Header.h"


#pragma warning(disable: 4996)

int menuPrincipal()
{
	int opcaoPrincipal;
	printf("M E N U\n");
	printf("1 Cliente \n");
	printf("2 Gestor\n");
	printf("Opcao:\n");
	scanf("%d", &opcaoPrincipal);
	printf("***************************************************\n");
	return(opcaoPrincipal);
	
}
int MenuCliente()
{
	int opCliente;
	printf("***************************************************\n");
	printf("1 Listar Meios\n");
	printf("2 Listagem por Autonomia\n");
	printf("3 Listagem Meios num Geocodigo\n ");
	printf("0 Sair\n");
	printf("***************************************************\n");
	printf("Opcao:\n");
	scanf("%d", &opCliente);
	printf("***************************************************\n");
	return (opCliente);

}
int MenuGestor()
{
	
	int opGestor;
	
	printf("***************************************************\n");
	printf("1 Inserir Meio\n");
	printf("2 Listar Meios\n");
	printf("3 Remover Meio\n");
	printf("4 Guardar Meios\n");
	printf("5 Ler Meios\n");
	printf("6 Alteração de um dado especifico de um meio\n");
	printf("7 Inserir Cliente\n");
	printf("8 Listar Clientes\n");
	printf("9 Remover Cliente\n");
	printf("10 Guardar Cliente\n");
	printf("11 Ler Cliente\n");
	printf("12 Alteração de um dado especifico de um cliente \n");
	printf("13 Inserir Gestor\n");
	printf("14 Listar Gestores\n");
	printf("15 Remover Gestor\n");
	printf("16 Guardar Gestor\n");
	printf("17 Ler Gestor\n");
	printf("18 Alteração de um dado especifico de um gestor\n");
	printf("19 Registo Aluguer Meio \n");
	printf("20 Listagem por Autonomia\n");
	printf("21 Listagem Meios num Geocodigo\n ");
	printf("0 Sair\n");
	printf("***************************************************\n");
	printf("Opcao: \n");
	scanf("%d", &opGestor);
	printf("***************************************************\n");
	return (opGestor);

}

int Cliente1()
{
	int opcaoCliente;
	Meio* mobilidade = NULL;/* Lista ligada de meios de mobilidade vazia*/

	char geoprocurar[50];


	do
	{
		opcaoCliente = MenuCliente();
		switch (opcaoCliente)
		{
	
		case 1: ListarMeios(mobilidade);
			break;

		case 2: ListarOrdemDecrescente(mobilidade);
			break;
           
		case 3:
			printf("Geocodigo onde será procurado os meios: \n");
			scanf("%s", &geoprocurar);
			ListagemGeoCodigo(mobilidade, geoprocurar);
			break;
		}
		
	} while (opcaoCliente != 0);


	return(0);
}



int Gestor1() 
{
	int opcaoGestor;
	Meio* mobilidade = NULL;/* Lista ligada de meios de mobilidade vazia*/
	Gestor* gestor = NULL; /* Lista ligada de dados do gestor vazia*/
	Cliente* cliente = NULL; /* Lista ligada de dados do cliente vazia*/

	int cod, nif, codre, posicao, opção;
	float bat, aut, custo, saldo, codigogestor;
	char tipo[50], geo[50], estado[30], nome[50], morada[70], nomeremover[50], nomegestor[30], palavrapasse[20], geoprocurar[50];
	

	do
	{
		opcaoGestor = MenuGestor();
		switch (opcaoGestor)
		{ 
			
		case 1: printf("Codigo?\n");
			scanf("%d", &cod);
			printf("Tipo:\n");
			scanf("%s", &tipo);
			printf("Nivel da bateria?\n");
			scanf("%f", &bat);
			printf("Autonomia\n");
			scanf("%f", &aut);
			printf("Custo:\n");
			scanf("%f", &custo);
			printf("Geocodigo\n");
			scanf("%s", &geo);
			printf("Estado Aluguer\n");
			scanf("%s", &estado);

			mobilidade = InserirMeio(mobilidade, cod, tipo, bat, aut, custo, geo, estado);
			break;
		case 2: ListarMeios(mobilidade);
			printf("*******************************\n");
			break;
		case 3: printf("Codigo do meio de mobilidade a remover?\n");
			scanf_s("%d", &cod);
			mobilidade = RemoverMeio(mobilidade, cod);
			break;
		case 4: GuardarMeios(mobilidade); break;
		case 5: mobilidade = LerMeios(); break;
		case 6:
			printf("Digite o codigo do meio de mobilidade no qual iremos altera os seus dados\n");
			scanf("%d", &cod);
			printf("Digite o tipo de meio de mobilidade\n");
			scanf("%s", &tipo);
			printf("Digite o nivel de bateria do meio de mobilidade\n");
			scanf("%f", &bat);
			printf("Digite a autonomia do meio de mobilidade\n");
			scanf("%f", &aut);
			printf("Digite o custo\n");
			scanf("%f", &custo);
			printf("Digite o geocodigo do meio de mobilidade\n");
			scanf("%s", &geo);
			printf("Digite o estado de aluguer\n");
			scanf("%s", &estado);

			mobilidade = AlterarMeio(mobilidade, cod, tipo, bat, aut, custo, geo, estado);
			break;

		case 7: printf("Nome?\n");
			scanf("%s", &nome);
			printf("Morada\n");
			scanf("%s", &morada);
			printf("Nif \n");
			scanf("%d", &nif);
			printf("Saldo\n");
			scanf("%f", &saldo);

			cliente = InserirCliente(cliente, nome, morada, nif, saldo);
			break;

		case 8: ListarClientes(cliente);
			printf("*******************************\n");
			break;

		case 9: printf("Nome Cliente a remover:\n");
			scanf("%s", &nomeremover);
			RemoverCliente(cliente, nomeremover); break;

		case 10: GuardarCliente(cliente); break;

		case 11: cliente=LerClientes();

			break;

		case 12:

			printf("Digite o nome do Cliente a alterar os dados\n");
			scanf("%s", &nome);
			printf("Digite a morada do Cliente\n");
			scanf("%s", &morada);
			printf("Digite o nif do cliente\n");
			scanf("%d", &nif);
			printf("Digite o saldo do cliente\n");
			scanf("%f", &saldo);
            cliente= AlterarCliente(cliente,nome,morada,nif, saldo);
			
			break;


		case 13: printf("Nome?\n");
			scanf("%s", &nomegestor);
			printf("Codigo Gestor\n");
			scanf("%f", &codigogestor);
			printf("PalavraPasse:\n");
			scanf("%s", &palavrapasse);

			gestor = InserirGestor(gestor, nomegestor, codigogestor, palavrapasse);
			break;



		case 14: ListarGestor(gestor);
			printf("***********************");
			break;

		case 15: printf("Nome Gestor a remover: \n");
			scanf("%s", &nomeremover);
			RemoverGestor(gestor, nomeremover); break;

		case 16: GuardarGestor(gestor);
			break;

		case 17: gestor=LerGestor(gestor);
			printf("*******************************\n");
			break;

		case 18:
			printf("Digite o nome do Gestor a alterar os dados\n");
			scanf("%s", &nomegestor);
			printf("Digite o codigo de Gestor\n");
			scanf("%f", &codigogestor);
			printf("Digite a palavra passe\n");
			scanf("%s", &palavrapasse);
			gestor = AlterarGestor(gestor, nomegestor,codigogestor,palavrapasse);
			break;

		case 19: printf("Codigo do Meio a Alugar:\n");
			scanf("%d", &codre);
			RegistoAluguer(mobilidade, codre);
			break;

		case 20: ListarOrdemDecrescente(mobilidade);
			printf("*******************************\n");
			break;

		case 21:
			printf("Geocodigo onde será procurado os meios: \n");
			scanf("%s", &geoprocurar);
			ListagemGeoCodigo(mobilidade, geoprocurar);
			printf("*******************************\n");
			break;

		}
	} while (opcaoGestor != 0);


	return(0);
}



int main()
{

	Meio* mobilidade = NULL;/* Lista ligada de meios de mobilidade vazia*/
	Gestor* gestor = NULL; /* Lista ligada de dados do gestor vazia*/
	Cliente* cliente = NULL; /* Lista ligada de dados do cliente vazia*/

	int opPrincipal = menuPrincipal();
	switch (opPrincipal)
	{
	case 1: Cliente1();
		break;
	case 2: Gestor1();
		break;
	default: printf("Opção invalida!!!\n");
		
	}
	
}
