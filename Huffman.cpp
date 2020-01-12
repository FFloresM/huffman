#include <bits/stdc++.h>
#define MARKER -1 
using namespace std;
  
/* A binary tree Node has key, pointer to left and right children */
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
// This function stores a tree in a file pointed by fp 
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
  
// This function constructs a tree from a file pointed by 'fp' 
/*void deSerialize(Node *&root, FILE *fp) 
{ 
    // Read next item from file. If theere are no more items or next 
    // item is marker, then return 
    int val; 
    if ( !fscanf(fp, "%d ", &val) || val == MARKER) 
       return; 
  
    // Else create node with this item and recur for children 
    root = newNode(val); 
    deSerialize(root->left, fp); 
    deSerialize(root->right, fp); 
} */
  
// A simple inorder traversal used for testing the constructed tree 

void inorder(Node *root , vector < int> &codigo , map <char,string> &val ) 
{ 
    if (root->left && root->right) 
    {   
        codigo.push_back(48);
        inorder(root->left ,codigo , val); 
        codigo.pop_back();
        //printf("%d --- %c  ", root->key , root->caracter); 
         codigo.push_back(49);
        inorder(root->right ,codigo , val);
        codigo.pop_back();
    } 
    else{
        cout << "codigo de " <<root->caracter<< "---" ;
        string str(codigo.begin(), codigo.end());
        cout << str;


        val.insert(make_pair(root->caracter,str));
        cout<<endl;
    }
} 

void  calcular_frecuencia (char *text , vector <char> & caracter , vector <int> & frecuencia  ){
    
    int tam_texto = strlen(text);

    
    for(int i = 0; i < tam_texto; i++){
         int pos = find ( caracter.begin(), caracter.end(),*text)- caracter.begin();     
         
        if(pos >= caracter.size()){
            caracter.push_back(*text);
            frecuencia.push_back(1);
        }else{
            frecuencia[pos]++;
        }
        *text++;
        
        }

  
}

Node * unir_nodos(Node * N1 , Node * N2){
    Node * padre = newNode(N1->key + N2->key ,48);

    cout<< "nodos unidos"<< N1->key << "---"<< N2->key<< endl;
    padre->left= N1;
    padre->right = N2;
    return padre;
}


Node *  huffman (vector <char> & caracteres ,vector<int> & t_frecuencias){
    vector<Node*> lista_nodos;
    Node * head;
    for(int  i = 0 ; i < caracteres.size(); i++ ){
       lista_nodos.push_back(newNode(t_frecuencias[i], caracteres[i]));
    }

    sort(lista_nodos.begin() , lista_nodos.end(), comp);

     for(int  i = 0 ; i < caracteres.size(); i++ ){

       cout<< lista_nodos[i]->caracter << " -- " << lista_nodos[i]->key <<endl;
        }
    
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
    return head;
}


map<char , string> codificacion(Node * Arbol ){
    Node *aux=Arbol;
    map <char , string> tabla_cod;
    vector<int> codifica;
    inorder (Arbol, codifica ,tabla_cod);
    return tabla_cod;
}
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
   serialize( arbol_H, compresion);
   compresion<< 2 <<endl;

   comprimir(codificacion(arbol_H), text , compresion);
   
   compresion.close();




  archivo.close();
  
  return 0; 
} 