#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct tree{
	int data;
	int damage;
	struct tree *right;
	struct tree *left;
}TREE;
typedef struct stack{
	int data;
	struct stack *next;

}STACK;

STACK* push(STACK *arr,int data);
STACK* stacktostack(STACK* head);

TREE* createNode(int data,int damage);
TREE* insert(TREE* root, int data ,int damage);
TREE* searchTree(TREE *root,int data);
TREE* connect(TREE *root, TREE *target, TREE *new_tree);

int random(int N);

void printTree(TREE* root, int level);
void print(STACK* head);
void preorderTraversal(TREE* target,int data,TREE** new_tree);
void play(TREE **root,int M,int N);
void freeStack(STACK* head);


int main(){
	srand(time(NULL));	
	TREE *head = NULL;
	int N,M;
	printf("----------------------------------\n");
	printf("meyve dusurme oyununa hosgeldiniz\n");
	printf("----------------------------------\n");
	
	do{
		printf("\nN(maximum guc degerini)giriniz:\n");
		scanf("%d",&N);
		printf("\nM(adet sayisini)giriniz:\n");
		scanf("%d",&M);
	}while(N < M);
	
	int i,val;
	TREE *k;
	val = random(N);
	head = insert(head,val,val);
	
	for(i = 1;i< M;i++){
		do{
		// birbirinden farkli degerler olusturulur
		val = random(N);
		k = searchTree(head,val);
		}while(k != NULL);
		insert(head,val,val);
	}
	//oyun baslangici
	play(&head,M,N);
	
	
	
	
	return 0;
}
void play(TREE **root,int M,int N){
	STACK *head = NULL;
	TREE *tmp = *root;
	int t = 0;
	while(t != M){
		// t dusen meyve sayisini tutar ve dongu tum meyveler dusene kadar devam edet
		tmp = *root;
		printf("\n---------------------------------------\n");
		printTree(tmp,0);
		printf("\n---------------------------------------\n");
		TREE *target = NULL;
		int k,p;
		do{	
			//kullanicidan meyve ve guc degerleri alinir
			printf("\nselect leaf\n");
			scanf("%d",&k);
			printf("\nselect weight\n");
			scanf("%d",&p);
			target = searchTree(tmp,k);
		}while(target == NULL);
		//guc degeri hasardan cikarilir
		target->damage = target->damage - p;
		if(target->damage <= 0){
			t++;
			head = push(head,target->data);//stacke meyve nodunun degeri atanir
			TREE *new_tree = NULL;
			//dusen nodun altindakiler gezilir ve yeni agac olusturulur
			preorderTraversal(target,target->data,&new_tree);
			// root ile yeni agac targetttan birlesitirlir			
			*root = connect(*root,target,new_tree);
			//dusen deger free edilir
			free(target);
			
			}
	}
	//ikinci stack olustrulur ve diger stacke atilir 
	STACK *k = NULL;
	k = stacktostack(head);
	print(k);
	//stack free edilir
	freeStack(head);
	freeStack(k);
	
}
void preorderTraversal(TREE* target,int data,TREE** new_tree){
	//targetin altindaki degerler preorder gezilir ve yeni agac olusturulur	
    if (target != NULL){
    	if(target->data != data){
       		(*new_tree)= insert((*new_tree),target->data,target->damage);
		   }
		else{
			
		}
        preorderTraversal(target->left,data,new_tree);
       	
        preorderTraversal(target->right,data,new_tree);
    }
    
}
TREE* connect(TREE *root, TREE *target, TREE *new_tree){
	//agaclari baglar
    if(root == NULL){
    	
        return new_tree;
    }

    if(target == NULL){
        return root;
       
    }

    TREE *parent = NULL;
    TREE *current = root;

    // target nodunun parent nodeu bulunur
    while(current != NULL && current != target){
        parent = current;

        if(target->data < current->data){
            current = current->left;
        } else {
            current = current->right;
        }
    }

    if(parent == NULL){
        return new_tree;
    }

    
    if(target == parent->left){
        parent->left = new_tree;
    } else {
        parent->right = new_tree;
    }
	
    return root;
}

void freeStack(STACK* head){
	STACK* tmp;
	while(head != NULL){
		tmp = head;
		head = head->next;
		free(tmp);
	}
}
STACK* stacktostack(STACK* head){
	//stackteki degerleri sirasilya baska bir stacke alir ve eski stack free edilir
	STACK* tmp = NULL;
	
	while(head != NULL){
		tmp = push(tmp,head->data);
		
		head = head->next;
		
	}
	return tmp;
}
STACK* push(STACK *arr,int data){
	//stack'e veri atar
	STACK *tmp =(STACK*)malloc(sizeof(STACK));
	tmp->data = data;
	tmp->next = NULL;
	
	if(arr != NULL){
		tmp->next = arr;		
	}
	return tmp;	
}
void print(STACK* head){
	//ekrana stackdeki verileri yazdirir
	while(head != NULL){
		printf("%d-",head->data);
		head = head->next;
	}
}
TREE* searchTree(TREE *root,int data){
	//recursive dataya gore arama algoritmasi
	TREE* tmp = root;
	if(root == NULL || root->data == data){
		return tmp;
	}
	if(data > root->data){
		searchTree(root->right,data);
	}
	else{
		searchTree(root->left,data);
	}
}
void printTree(TREE* root, int level){
	// recursive agac yazdirma fonksyionu en saga gidip degeri yazdirir ve ardindan 
	//roota gecer ve enseonunda lefti yazdirmaktadir
	int i;
    if(root == NULL){
        return;
    }
    printTree(root->right, level+1);
    printf("\n");
    for(i = 0; i < level; i++){
        printf("   ");
    }
    
    printf("%d(%d)\n", root->data,root->damage);
	
    printTree(root->left, level+1);
}
int random(int N){
	//random number generator	
	return rand()% N +1;
}
TREE* insert(TREE* root, int data ,int damage){
	//recursive insert fonksiyonu datanin boyutuna gore agaca yerlestirir 
    if(root == NULL){
    	
        return createNode(data,damage);
        
    }else if(data < root->data){
        root->left = insert(root->left, data,damage);
        
    }else{
        root->right = insert(root->right, data,damage);
        
    }
    return root;
}
TREE* createNode(int data,int damage){
	// verilen data ve damage degeri ile yeni node olusturur
    TREE* newNode =(TREE*) malloc(sizeof(TREE));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->damage = damage;
    return newNode;
}

