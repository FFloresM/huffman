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
// recibe como entreada el arbol de huffman , el archivo a descomprimir y el archivo donde queda el archivo descomprimido

void decodificacion (Node* Arbol , fstream & fp , fstream &fdc ){
    Node* Q= Arbol;
    char *p;
    int j,k,n,m;
    unsigned char x,nbit;
    j=0;
    x=fp.get();
    nbit=0;
    n=0;
    while(!fp.eof()){

        if (Q->caracter != '0'){
            if(Q->caracter =='~'){
                fdc<<'\n';
            }else{
            fdc<<Q->caracter;
           
            }
            Q=Arbol;
        } else{

            if (nbit==8){
            x=fp.get();
            
            nbit=0;
            } else {
               
            if (x&(1<<nbit)){ 
                Q=Q->right;
               
            }
            else
            {
                Q=Q->left;
                
            }
            nbit++;
           }
    }



    }
    
        


}


int main(int argc, char const *argv[]){
    fstream compresion , descomp;
    if (argc != 3){
        cout << "debe especificar archivo a descomprimir y nombre archivo descomprimido\n";
        return 1;
    }

    string texto_comprimido = argv[1];
    string texto_descomprimido = argv[2];
   

    descomp.open(texto_descomprimido, ios ::out );
    compresion.open(texto_comprimido ,ios::in | ios :: binary);

    Node *root1 = NULL;
    char val ;
    
    deSerialize(root1 , compresion ,val);
  
    compresion.get(val);
    compresion.get(val);
    
     
 
    //inorder(root1);

    decodificacion(root1, compresion , descomp);
  
    descomp.close();
    compresion.close();
    cout<<"Texto descomprimido" <<endl;

    return 0;
}