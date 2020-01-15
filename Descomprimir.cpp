#include <bits/stdc++.h>
#define MARKER '$' 
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

void deSerialize(Node * &root, fstream &fp , char &val) 
{ 
    // Read next item from file. If theere are no more items or next 
    // item is marker, then return 
    if( val== '2') return;
    if ( !fp.get(val) || val == '$'  || val== '2' ) {
        //cout<< val<< "  ";
       return;}
    
       //cout<< val<<" ";
     // Else create node with this item and recur for children 
    root = newNode(0,val); 

    deSerialize(root->left, fp , val); 
    deSerialize(root->right, fp, val); 

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

void decodificacion (Node* Arbol , fstream & fp , fstream &fdc ){
    char cod;
    Node *aux = Arbol;
    fp.get(cod);

    while(!fp.eof()){
        
        if( aux ->caracter !='0'){
            if(aux ->caracter =='~'){
                fdc<<'\n';
            }else{
            fdc<<aux->caracter;
            //cout<< aux->caracter;
            }
            aux= Arbol;
            }
        if(cod== '1') aux= aux->right;
        if(cod== '0' )aux= aux->left;
        fp.get(cod);
    }

}


int main(int argc, char const *argv[]){

    fstream compresion , descomp;

    string texto_comprimido = argv[1];
    string texto_descomprimido = argv[2];
 //   cin >> texto_comprimido;
 //   cin >> texto_descomprimido;

    // string texto_descomprimido = "descomprimido_" + texto_comprimido;

    descomp.open(texto_descomprimido, ios ::out);
    compresion.open(texto_comprimido ,ios::in);

    Node *root1 = NULL;
    char val ;
    //cout << endl;
    deSerialize(root1 , compresion ,val);
    //cout << endl;
    compresion.get(val);
    //compresion.get(val);
    //cout <<" 1"<< endl;
    // inorder(root1);
    //cout << endl;
    //cout << endl; 

    decodificacion(root1, compresion , descomp);
    //cout << endl;
    //cout << endl;
    descomp.close();
    compresion.close();
    cout<<"Texto descomprimido" <<endl;
}