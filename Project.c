#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
typedef struct Trie {
    struct Trie* children[10];
    bool isEndOfWord;
    char *word;
}TRIE;
int getNumberFromChar(char c);

TRIE* createNode();

void insertWord(TRIE* root, char* word);

void searchWords(TRIE* root, char* number);


int main() {
    TRIE* root = createNode();
    
    // sozlukten kelimeleri okuyup trie'ye yerlestirme
    FILE* fp = fopen("sozluk.txt", "r");
    if (fp == NULL) {
        printf("Bulunamadi\n");
        return 0;
    }
    
    char word[100];
    while (fgets(word, 100, fp) != NULL) {
        int length = strlen(word);
        if (word[length - 1] == '\n') {
            word[length - 1] = '\0';  // Yeni satir karakterlerini end karakteriyle degistir
        }
        
        insertWord(root, word);
        
    }
    
    fclose(fp);
    //sayi sorgulama
    
    char number[100];
    do{
	
    printf("> ");
    scanf("%s", number);
    if(number[0] != 'q'){
    	searchWords(root, number);
	}
	}
    while (number[0] != 'q');
    
    return 0;
}


int getNumberFromChar(char t) {
    if (t== '#')
        return 0;
        
    else if(t == 'a' || t == 'b' || t == 'c')
        return 2;
        
    else if(t == 'd' || t == 'e' || t == 'f')
        return 3;
        
    else if(t == 'g' || t == 'h' || t == 'i')
        return 4;
        
    else if(t == 'j' || t == 'k' || t == 'l')
        return 5;
        
    else if(t == 'm' || t == 'n' || t == 'o')
        return 6;
        
    else if(t == 'p' || t == 'q' || t == 'r' || t == 's')
        return 7;
        
    else if(t == 't' || t == 'u' || t == 'v')
        return 8;
        
    else if(t == 'w' || t == 'x' || t == 'y' || t == 'z')
        return 9;
        
    else
        return -1; 
}


TRIE* createNode(){
    TRIE* node = (TRIE*)malloc(sizeof(TRIE));
    node->isEndOfWord = false;
    int i;
    for (i = 0; i < 10; i++) {
        node->children[i] = NULL;
    }
    return node;
}


void insertWord(TRIE* root, char* word){
    TRIE* current = root;
    int i;
    
    for(i = 0; word[i] != '\0'; i++){//tum kelimeyi sirayla gezer
        int index = getNumberFromChar(word[i]);
        
        if(current->children[index] == NULL){//kelimenin indeksi olusturlmamissa olusturur
        	
			current->children[index] = createNode();
        }
        current = current->children[index];//kelimenin bir sonraki harfi icin siradaki node a erisir
    }
    
    if(current->isEndOfWord != true){//eger daha once kelime eklenmemisse ekler
        
		current->isEndOfWord = true;
        current->word = (char*)malloc(sizeof(char) * (strlen(word) + 1));
        
		if(current->word != NULL){
            
			strcpy(current->word, word);//kelimeyi saklar
        }
    }else{
    	
        int index = 0;
        
    	while(current->children[0] != NULL && current->children[0]->isEndOfWord){// bos olan children[0] gorene kadar devam eder
        current = current->children[0];
	    }
	    
	    current->children[0] = createNode();
	    current = current->children[0];
	    current->isEndOfWord = true;
	    current->word = (char*)malloc(sizeof(char) * (strlen(word) + 1));
	    
		if(current->word != NULL){
	        strcpy(current->word, word);//children[0] a ekler
	    }
    }
    
}
void searchWords(TRIE* root, char* number){
    TRIE* current = root;
	int i;
	//2345
    for(i = 0; number[i] != '\0'; i++){
        int index = number[i] - '0';

        if(current->children[index] == NULL){//eger kelimenin harfi initialize edilmemisse kelime yoktur der ve doner
            printf("Bu sayi icin kelime bulunmamaktadir.\n");
            return;
        }

        current = current->children[index];
    }

    if(current->isEndOfWord){//bulunan kelimeyi yazdirir
        printf("'%s' Sayisi icin karsilik gelen kelimeler :\n", number);
        printf("%s\n", current->word);
        
        while(current->children[0] != NULL){//kelimenin altindaki ayni kodlu kalan kelimeleri yazdirir
        	printf("%s\n",current->children[0]->word);
        	current = current->children[0];
		}
		
    }else{
    	
        printf("Bu sayi icin karsiligi olan kelime bulunamadi.\n");
    }
}
