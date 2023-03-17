/*****************************************************************//**
 **\author:Gonçalo Soares
 * \brief: Funções utilizadas
  *********************************************************************/

#include <stdlib.h>
#include <string.h>
#include "Header.h"


#pragma warning(disable: 4996)

#pragma region FunçõesMobilidade
/**
 * 
 * \Enter Entra o endereço de memoria do inicio da lista ligada dos meios de mobilidade eletrica
 * \brief: A função vai guardando os varios valores presentes nas listas da lista ligada
 * \return: Em caso de sucesso retorna 1, em caso de erro retorna 0
 * 
 */
int GuardarMeios(Meio* inicio)
{
    FILE* fp;
    fp = fopen("meios.txt", "w");
    if (fp != NULL)
    {
        Meio* aux = inicio;
        while (aux != NULL)
        {
            fprintf(fp, "%d;%s;%.2f;%0.2f;%.2f;%s;%s\n", aux->codigo, aux->tipo,
                aux->bateria, aux->autonomia,aux->custo, aux->geocodigo,aux->estadoaluguer);
            aux = aux->seguinte;
        }
        fclose(fp);
        return(1);
    }
    else return(0);
}

/**
 * \brief: A função vai lendo os varios valores e vai inserindo-os na lista ligada
 * \return: Retorna o endereço de memoria para o inicio da lista ligada
 * 
 */

Meio* LerMeios()
{
    FILE* fp;
    int cod;
    float bat, aut =0, cust;
    char tipo[50],geo[50],aluguer[30];
    Meio* aux = NULL;
    fp = fopen("meios.txt", "r");
    if (fp != NULL)
    {
        while (!feof(fp))
        {
            fscanf(fp, "%d %[;] %.2f %.2f %f %[;] %[;]\n", &cod, tipo, &bat, &aut, &cust, geo,aluguer);
            aux = InserirMeio(aux, cod, tipo, bat, aut,cust,geo,aluguer);
        }
        fclose(fp);
    }
    return(aux);
}



/**
 * 
 * \Enter Entra o endereço de memoria do inicio da lista ligada e os varios parametros a inserir
 * \brief: A função verifica se existe o determinado meio de transporte e caso náo exista cria uma nova lista com os dados
 * \return: Retorna o novo endereço da lisat ligada em caso de o meio de mobilidade ainda nao existir, caso exista volta devolver o endereço inicial
 * foi passado por parametro no inicio
 * 
 */
Meio* InserirMeio(Meio* inicio, int cod, char tipo[], float bat, float aut,float custo ,char geo[], char estadoaluguer[])
{
    
    if (!ExisteMeio(inicio, cod))
    {
        Meio* novo = malloc(sizeof(struct registo));
        
        if (novo != NULL)
        {
            novo->codigo = cod;
            strcpy(novo->tipo, tipo);
            novo->bateria = bat;
            novo->autonomia = aut;
            novo->custo = custo;
            strcpy(novo->geocodigo, geo);
            strcpy(novo->estadoaluguer, estadoaluguer);
            novo->seguinte = inicio;
            return(novo);
        }
    }
    else return(inicio);
}
/* Determinar existência do 'codigo' na lista ligada 'inicio'*/
/*devolve 1 se existir ou 0 caso contrário */
int ExisteMeio(Meio* inicio, int cod)
{
    while (inicio != NULL)
    {
        if (inicio->codigo == cod)
        {
            return(1);
        }
        inicio = inicio->seguinte;
    }
    return(0);
}

/*Lista na consola o conteudo da lista ligada*/
void ListarMeios(Meio* inicio)
{
    while (inicio != NULL)
    {
        printf("%d %s %.2f %.2f %.2f %s %s \n", inicio->codigo, inicio->tipo,
            inicio->bateria, inicio->autonomia, inicio->custo , inicio->geocodigo, inicio->estadoaluguer);
        inicio = inicio->seguinte;
    }
}

/**
 * 
 * \Enter Entra o endereço inicial da lista ligada e o codigo do meio de mobilidade reduzida a retirar
 * \brief:A função verifica primeiramente se o endereço inicial não é nulo e depois compara os codigos presentes na lista ligada com o que é para eliminar
 * \return: Retorna nulo caso o endereço inicial seja nulo, retorna o novo endreço inicial da lista ligada em caso de sucesso, caso não encontre a lista a eliminar devolve o endereço inicial que foi passado por parametro
 * 
 */
Meio* RemoverMeio(Meio* inicio, int cod)
{
    if (inicio == NULL) return(NULL);
    else if ((inicio != NULL) && (inicio->codigo == cod))
    {
        Meio* aux = inicio->seguinte;
        free(inicio);
        return(aux);
    }
    else {
        inicio->seguinte = RemoverMeio(inicio->seguinte, cod);
        return(inicio);
    }
}

/**
 * 
 * \Enter  Entra o endreço inicial da lista ligada dos meios e o geocodigo que queremos "procurar"
 * \brief: A função verifica se cada geocodigo que queremos procurar existe na lista.
 * \return: Em caso afirmativo lista o meio de mobilidade presente nesse geocodigo
 * 
 */
void ListagemGeoCodigo(Meio* inicio, char geocodigo[])
{
    while (inicio!= NULL)
    {
        if (stricmp(inicio->geocodigo,geocodigo)== 0)
        {


            printf("%d %s %.2f %.2f %f %s %s\n", inicio->codigo, inicio->tipo,
                inicio->bateria, inicio->autonomia, inicio->custo, inicio->geocodigo,inicio->estadoaluguer);
            

        }
        inicio = inicio->seguinte;
    }

}

/*A função troca os paramtros de ordem*/
void troca(Meio* a, Meio* b) {
    Meio aux = *a;
    *a = *b;
    *b = aux;
}


/**
 * 
 * \Enter Entra o endereço de memoria do inicio da lista ligada
 * \brief: A função vai comparando as autonomias entre as listas ligadas e no fim lista o conteudo da lista ligada por ordem decrescente de autonomia
 * 
 */
void ListarOrdemDecrescente(Meio* inicio)
{
    int aux = 1;
    Meio* atual=inicio;
    Meio* seguinte = NULL;

    while (aux) 
        {
            aux = 0;
            atual = inicio;
            while (atual->seguinte != seguinte) {
                if (atual->autonomia < atual->seguinte->autonomia) {
                    troca(atual, atual->seguinte);
                    aux = 1;
                }
                atual = atual->seguinte;
            }
            seguinte = atual;
        }
        ListarMeios(inicio);
   
   
}

/**
 * 
 * \Enter Entra o endereço do inicio da lista ligada e o codigo do meio de mobilidade eletrica a alugar
 * \brief: A função primeiro compara o codigo do meio pedido com os existentes na lista ligada, caso encontre verifica se ja não se encontra alugado esse meio de mobilidade
 * \return: Retorna 1 em caso de conseguir alugar o meio, retorna 0 em caso do meio ja se encontrar alugado, retorna -1 em caso do meio de mobilidade não existir
 * 
 */
int RegistoAluguer(Meio* inicio, int codigo)
{
    while (inicio != NULL)
    {

        if (inicio->codigo == codigo)
        {
            if (stricmp(inicio->estadoaluguer,"alugado")!=0)
            {
                strcpy(inicio->estadoaluguer,"alugado");
                return 1;
            }
            else
            {
                return 0;
            }
        }
        inicio = inicio->seguinte;
    }
    return -1;


}
/**
 * 
 * \Enter Entra o endereço inicial da lista ligada, o codigo, o tipo, a bateria,a autonomia,o custo, o geoodigo e o estado de aluguer do meio de mobilidade
 * \brief: A funação compara os codigos existentes na lista ligada, com o que queremos procurar, quando encontrar troca os parametros na lista ligada
 * 
 */
Meio* AlterarMeio(Meio* inicio, int cod, char tipo[], float bat, float aut, float custo, char geo[], char estadoaluguer[])
{
    Meio* aux = inicio;
    while (aux != NULL)
    {
        if (aux->codigo==cod);
        {

                aux->codigo = cod;
                strcpy(aux->tipo, tipo);
                aux->bateria = bat;
                aux->autonomia = aut;
                aux->custo = custo;
                strcpy(aux->geocodigo, geo);
                strcpy(aux->estadoaluguer, estadoaluguer);
                return(aux);
            
        }
        
        aux = aux->seguinte;
    }
    return inicio;

}





#pragma endregion


#pragma region FunçõesClientes

/**
 * 
 * \Enter Entra o endereço de memoria da lista ligada e os varios dados a adicionar à lista ligada
 * \brief: A função verifica se existe esse cliente em caso afirmativo vai adicionando os parametros à lista ligada
 * \return: Retorna o novo endereço de memoria da lista ligada em caso de não existir um determinado cliente, em caso de existir o cliente, devolve o endereço de memoria passado anteriormente
 * 
 */
Cliente* InserirCliente(Cliente* inicio, char nome[], char morada[], int nif, float saldo)
{
    
    if (!ExisteCliente(inicio->nome, nome))
    {
        Cliente* novo = malloc(sizeof(struct RegistoCliente));

        if (novo != NULL)
        {
            strcpy(novo->nome, nome);
            strcpy(novo->morada, morada);
            novo->nif = nif;
            novo->saldo = saldo;
            novo->seguinte = inicio;
            return(novo);
        }
    }
    else return(inicio);
}

/**
 * 
 * \Enter Entra o endereço de memoria do inicio da lista ligada, e o nome a procurar
 * \brief: A função verifica se o cliente ja exite, comparando os nomes
 * \return: Retorna o 0 em caso de serem iguais, e um valor diferente de 0 em caso de serem diferentes
 * 
 */
int ExisteCliente(Cliente* inicio, char nome[])
    {
        
        while (inicio!= NULL)
        {
            if (stricmp(inicio->nome, nome))
            {
                return 1;

            }
            inicio = inicio->seguinte;
        }
        return 0;
    }

/**
 * 
 * \Enter Entra o endereço de memoria de uma lista ligada, e o nome do cliente a remover
 * \brief: A função verifica primeiramente se o endereço inicial não é nulo e depois compara os nomes presentes na lista ligada com o que é para eliminar da lista
 * \return: Retorna nulo caso o endereço de memoria inicial seja nulo, retorna o novo endereço de memoria da lista ligada em caso de eliminar um cliente,
 *  em caso de não eliminar nenhum retorna o enderço de memoria que inicialmnete foi passado
 * 
 */
    Cliente* RemoverCliente(Cliente* inicio, char nome)
    {
        if (inicio == NULL) return(NULL);
        else if ((inicio != NULL) && (ExisteCliente(inicio->nome,nome)==0))
        {
            Cliente* aux = inicio->seguinte;
            free(inicio);
            return(aux);
        }
        else {
            inicio->seguinte = RemoverCliente(inicio->seguinte,nome);
            return(inicio);
        }
    }

    /*Lista na consola o conteudo da lista ligada*/
   
    void ListarClientes(Cliente* inicio)
    {
        while (inicio!= NULL)
        {
            printf("%s %s %d %.2f \n", inicio->nome, inicio->morada,
                inicio->nif, inicio->saldo);
            
            inicio = inicio->seguinte;
        }
    }

   /**
 *
 * \Enter Entra o endereço de memoria do inicio da lista ligada
 * \brief: A função vai guardando os varios valores presentes nas listas da lista ligada
 * \return: Em caso de sucesso retorna 1, em caso de erro retorna 0
 *
 */
   int GuardarCliente(Cliente* inicio)
   {
       FILE* fp;
       fp = fopen("cliente.txt", "w");
       if (fp != NULL)
       {
           Cliente* aux = inicio;
           while (aux != NULL)
           {
               fprintf(fp,"%s;%s;%d;%.2f;\n", aux->nome, aux->morada,
                   aux->nif, aux->saldo);
               aux = aux->seguinte;
           }
           fclose(fp);
           return(1);
       }
       else return(0);
   }

   /**
 * \brief: A função vai lendo os varios valores e vai inserindo-os na lista ligada
 * \return: Retorna o endereço de memoria para o inicio da lista ligada
 *
 */

   Cliente* LerClientes()
   {
       FILE* fp;
       int nif;
       float saldo;
       char nome[20],morada[50];
       Cliente* aux = NULL;
       fp = fopen("Clientes.txt", "r");
       if (fp != NULL)
       {
           while (!feof(fp))
           {
               fscanf(fp, "%[;]%[;]%f;%f;\n", nome, morada, &nif, &saldo);
               aux = InserirCliente(aux,nome, morada, nif, saldo);
           }
           fclose(fp);
       }
       return(aux);
   }


   /**
    * 
    * \Enter Entra o endereço do inicio da lista ligada, o nome, a morada, o nif e o saldo do cliente
    * \brief: A função compara os nomes presentes na lista ligada com o pedido pelo utilizador e caso encontre troca os dados do cliente
    * 
    */
   Cliente* AlterarCliente(Cliente* inicio, char nome[], char morada[], int nif, float saldo)
   {
       Cliente* aux = inicio;
       while (aux!= NULL)
       {
           if (!ExisteCliente(aux->nome, nome))
           {

                   strcpy(aux->nome,nome);
                   strcpy(aux->morada, morada);
                   aux->nif = nif;
                   aux->saldo =saldo;
                   return(inicio);
               
           }

           aux = aux->seguinte;
       }
       return aux;
   }
  


#pragma endregion

#pragma region FunçõesGestor

   /**
    * \brief: A função vai lendo os varios valores e vai inserindo-os na lista ligada
    * \return: Retorna o endereço de memoria para o inicio da lista ligada
    * 
    */
   Gestor* LerGestor()
   {
       FILE* fp;
       float codigogestor;
       char nomegestor[30], passe[20];
       Gestor* aux = NULL;
       fp = fopen("Gestor.txt", "r");
       if (fp != NULL)
       {
           while (!feof(fp))
           {
               fscanf(fp, "%[;]%f;%s\n",&nomegestor,&codigogestor,&passe);
               aux = InserirGestor(aux,nomegestor,codigogestor,passe);
           }
           fclose(fp);
       }
       return(aux);
   }

   /**
 *
 * \Enter Entra o endereço de memoria da lista ligada e os varios dados a adicionar à lista ligada
 * \brief: A função verifica se existe esse gestor em caso afirmativo vai adicionando os parametros à lista ligada
 * \return: Retorna o novo endereço de memoria da lista ligada em caso de não existir um determinado gestor, em caso de existir o gestor, devolve o endereço de memoria passado anteriormente
 *
 */
   Gestor* InserirGestor(Gestor* inicio, char nomegestor[], float codigo,char palavrapasse[])
   {
       if (!ExisteGestor(inicio->Nomegestor, nomegestor))
       {
           Gestor* novo = malloc(sizeof(struct RegistoGestor));

           if (novo != NULL)
           {
               strcpy(novo->Nomegestor, nomegestor);
               novo->codigogestor = codigo;
               strcpy(novo->PalavraPasse, palavrapasse);
               novo->seguinte =inicio;
               return(novo);
           }
       }
       else return(inicio);
   }

  /**
 *
 * \Enter Entra o endereço de memoria do inicio da lista ligada, e o nome a procurar
 * \brief: A função verifica se o gestor ja exite, comparando os nomes
 * \return: Retorna o 0 em caso de serem iguais, e um valor diferente de 0 em caso de serem diferentes
 *
 */
   int ExisteGestor(Gestor* inicio, char nome[])
   {
       int valor;
       while (inicio!= NULL)
       {
           if (stricmp(inicio->Nomegestor, nome))
           {
               return 1;

           }
           inicio = inicio->seguinte;
       }
       return 0;
   }

   /**
 *
 * \Enter Entra o endereço de memoria do inicio da lista ligada
 * \brief: A função vai guardando os varios valores presentes nas listas da lista ligada
 * \return: Em caso de sucesso retorna 1, em caso de erro retorna 0
 *
 */
   int GuardarGestor(Gestor* inicio)
   {
       FILE* fp;
       fp = fopen("Gestor.txt", "w");
       if (fp != NULL)
       {
           Gestor* aux = inicio;
           while (aux != NULL)
           {
               fprintf(fp, "%s;%.2f;%s;\n", aux->Nomegestor, aux->codigogestor,aux->PalavraPasse);
               aux = aux->seguinte;
           }
           fclose(fp);
           return(1);
       }
       else return(0);
   }

   /*Lista na consola o conteudo da lista ligada*/
   void ListarGestor(Gestor* inicio)
   {
       while (inicio!= NULL)
       {
           printf("%s %.2f %s \n", inicio->Nomegestor, inicio->codigogestor,
               inicio->PalavraPasse);
           
           inicio = inicio->seguinte;
       }
   }

   /**
    *
    * \Enter Entra o endereço de memoria de uma lista ligada, e o nome do gestor a remover
    * \brief: A função verifica primeiramente se o endereço inicial não é nulo e depois compara os nomes presentes na lista ligada com o que é para eliminar da lista
    * \return: Retorna nulo caso o endereço de memoria inicial seja nulo, retorna o novo endereço de memoria da lista ligada em caso de eliminar um gestor,
    *  em caso de não eliminar nenhum retorna o enderço de memoria que inicialmnete foi passado
    *
    */
   Gestor* RemoverGestor(Gestor* inicio, char nome)
   {
       if (inicio == NULL) return(NULL);
       else if ((inicio != NULL) && (!ExisteGestor(inicio->Nomegestor, nome)))
       {
           Gestor* aux = inicio->seguinte;
           free(inicio);
           return(aux);
       }
       else {
           inicio->seguinte = RemoverGestor(inicio->seguinte, nome);
           return(inicio);
       }
   }
  
/**
 * 
 * \Enter Entra o endereço inicial da lista ligada, o nome do gestor, o codigo de gestor e a palavra-passe
 * \brief: A função comparar os nones dos gestores presentes na lista ligada e compara com o nome do gestor pedido.
 * 
 */
Gestor* AlterarGestor(Gestor* inicio, char nomegestor[], float codigogestor, char palavrapasse[])
{
    while (inicio != NULL)
    {
        if (!ExisteGestor(inicio, nomegestor))
        {

            
                strcpy(inicio->Nomegestor, nomegestor);
                inicio->codigogestor = codigogestor;
                strcpy(inicio->PalavraPasse,palavrapasse);
                return(inicio);
            
        }

        inicio = inicio->seguinte;
    }

    return inicio;


 }

 
#pragma endregion
