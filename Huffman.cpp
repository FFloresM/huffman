#include <bits/stdc++.h>
#define MARKER -1 
using namespace std;


struct Node 
{ 
    int key;
    char caracter; 
    struct Node* left, *right; 
}; 
  
/* Helper function that allocates a new Node with the 
   given key and NULL left and right pointers. */
Node* newNode(int key , char alfa) 
{ 
    Node* temp = new Node; 
    temp->key = key; 
    temp->caracter = alfa;
    temp->left = temp->right = NULL; 
    return (temp); 
} 
  
int comp(Node * N1 ,Node*  N2){

    if(N1->key < N2->key){
    return 1;
    }
    else{
      return 0;
    }
}
// esta funcion ayuda a serializar el arbol
void serialize(Node *root, fstream &fp) 
{ 
    // If current node is NULL, store marker 
    if (root == NULL) 
    { 
        fp<< MARKER<<" "; 
        return; 
    } 
  
    // Else, store current node and recur for its children 
    fp<<root->caracter<<" "; 
    serialize(root->left, fp); 
    serialize(root->right, fp); 
} 
  

void deSerialize(Node * &root, fstream &fp , char &val) 
{ 
    // Read next item from file. If theere are no more items or next 
    // item is marker, then return 
    if( val== '2') return;
    if ( !fp.get(val) || val == '-1'  || val== '2' ) 
       return;
    
       cout<< val<<" ";
     // Else create node with this item and recur for children 
    root = newNode(0,val); 
    deSerialize(root->left, fp , val); 
    deSerialize(root->right, fp, val); 

} 
  
/*Recorre el arbol inorder recursivamente , generando el codigo para cada caracter */

void inTree(Node *root , vector < int> &codigo , map <char,string> &val ) 
{ 
    if (root->left && root->right) 
    {   
        codigo.push_back(48); // 0 si va por el hijo izquierdo
        inTree(root->left ,codigo , val); 
        codigo.pop_back();

         codigo.push_back(49);// 1 si va por el hijo derecho
        inTree(root->right ,codigo , val);
        codigo.pop_back();
    } 
    else{// cuando llega a una hoja guarda el codigo en un mapa 

        string str(codigo.begin(), codigo.end());

        val.insert(make_pair(root->caracter,str));
    }
} 


void inorder(Node *root) 
{ 
    if (root) 
    { 
        inorder(root->left); 
        cout<< root->caracter<< " "; 
        inorder(root->right); 
    } 
} 

// cacula la frecuencia de cada caracter en el texto entregado, se utiliza un vector para guardar el caracter y otro para asociar la frecuencia de este 
void  calcular_frecuencia (char *text , vector <char> & caracter , vector <int> & frecuencia  ){
    
    int tam_texto = strlen(text);

    
    for(int i = 0; i < tam_texto; i++){

         int pos = find ( caracter.begin(), caracter.end(),*text)- caracter.begin();  // busca si el caracter está en el vector de caracteres

        if(pos >= caracter.size()){// si no está es agregado y se contabiliza una aparición
            caracter.push_back(*text);
            frecuencia.push_back(1);
        }else{
            frecuencia[pos]++;
        }
        *text++;
        }

}
// une 2 nodos y crea un padre el cual es rectornado 
Node * unir_nodos(Node * N1 , Node * N2){
    Node * padre = newNode(N1->key + N2->key ,48);

    cout<< "nodos unidos"<< N1->key << "---"<< N2->key<< endl;
    padre->left= N1;
    padre->right = N2;
    return padre;
}

/* El proceso de construcción del árbol comienza formando un nodo intermedio que agrupa a los dos nodos hoja que tienen menor peso
(frecuencia de aparición). El nuevo nodo intermedio tendrá como nodos hijos a estos dos nodos hoja y su campo peso será igual a la suma de los pesos de los nodos hijos.
Los dos nodos hijos se eliminan de la lista de nodos, sustituyéndolos por el nuevo nodo intermedio. El proceso se repite hasta que sólo quede un nodo en la lista. 
Este último nodo se convierte en el nodo raíz del árbol de Huffman */

Node *  huffman (vector <char> & caracteres ,vector<int> & t_frecuencias){
  
    vector<Node*> lista_nodos;
    Node * head;

    // son ingresados todos los nodos que contienen cada caracter y su frecuencia a la lista de nodos 
    for(int  i = 0 ; i < caracteres.size(); i++ ){ 

       lista_nodos.push_back(newNode(t_frecuencias[i], caracteres[i]));
    }
    // los nodos son ordenados en orden creciente 
    sort(lista_nodos.begin() , lista_nodos.end(), comp);

    
    // se unen los nodos con menor frecuencia y se borran de la lista , es ingresado a la lista el nodo intermedio 
    while(lista_nodos.size()>1){
        head = unir_nodos(lista_nodos[0] , lista_nodos[1]);
        lista_nodos.erase (lista_nodos.begin(), lista_nodos.begin()+2);
        lista_nodos.push_back(head);
        
        sort(lista_nodos.begin() , lista_nodos.end(), comp);
    
        for(int  i = 0 ; i < lista_nodos.size(); i++ ){

       cout<< lista_nodos[i]->caracter << " -- " << lista_nodos[i]->key <<endl;
    }
        }
    cout<< head->key<<endl; 

    return head;// es retornado la raiz del arbol construido 
}
/* recibe de entrada la raiz del arbol de huffman y retorna un mapa que contiene cada caracter asociado con  su respectivo codigo*/
map<char , string> codificacion(Node * Arbol ){
    Node *aux=Arbol;
    map <char , string> tabla_cod;
    vector<int> codifica;
    inTree (Arbol, codifica ,tabla_cod);
    return tabla_cod;
}

/* utiliza la tabla de codigos para comprimir el texto , el texto se lee carcter a caracter  y es agregado al archivo referenciado */
void comprimir (map<char,string> t_Codif, char* text ,fstream &fp){
   int tam_texto = strlen(text);
   map<char, string>::iterator p;
   char * m;
    for(int i = 0; i < tam_texto; i++){
       
        p = t_Codif.find(*text);
        fp << p->second;
        *text++;
        }


}



int main() { 

    fstream archivo;
    fstream compresion;
    
    string texto , auxtext;
    char *text;
    text = new char [5000000];
    vector <char> caracter;
    vector <int> frecuencia , cod;
    map <char , string> t_codigos;
    Node * arbol_H;

    archivo.open("dna.txt",ios::in);
     if(archivo.fail()){
       cout<<"error al abrir el archivo";
       exit(0);
       }    
   while( !archivo.eof()){
       getline(archivo,auxtext);
        strcat(text, auxtext.c_str());
       if(strlen(text)>1000) break;
   }
   FILE *fp = fopen("tree.txt", "w"); 
    if (fp == NULL) 
    { 
        puts("Could not open file"); 
        return 0; 
    } 
    compresion.open("textocom.txt" ,ios::out);

    calcular_frecuencia(text ,caracter , frecuencia);
   /*caracter.push_back('A');
   caracter.push_back('B');
   caracter.push_back('C');
   caracter.push_back('D');
   caracter.push_back('E');
   frecuencia.push_back(25);
   frecuencia.push_back(25);
   frecuencia.push_back(20);
   frecuencia.push_back(15);
   frecuencia.push_back(15);*/
    arbol_H=  huffman(caracter, frecuencia);
    inorder(arbol_H);

   serialize( arbol_H, compresion);
   compresion<< 2 <<endl;

   comprimir(codificacion(arbol_H), text , compresion);
    compresion.close();
   
   compresion.open("textocom.txt" ,ios::in);

   Node *root1 = NULL;
   char val ;
   deSerialize(root1 , compresion ,val);
   cout <<"inorder"<< endl;
   
   inorder(root1);

   
   

    compresion.close();


  archivo.close();
  
  return 0; 
} 