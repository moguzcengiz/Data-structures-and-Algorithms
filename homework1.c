#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Node {
    int data;
    struct Node* next;
    struct Node* prev;
} LINKED;

LINKED* setNewHead(LINKED* head, int k, int t);

int* set_pos(int n);

void hizala(LINKED*** arr, int* pos, int M, int N);

int find_passcode(LINKED*** arr, int M, int N); 

LINKED** add_node(int M, int N);

void print_list(LINKED* head);

int random(int n);

int main(){
    srand(time(NULL));
    LINKED** arr;
    int M;  
    int N;  
    int i,j;
    do{
    	printf("Gecerli bir M degeri giriniz:");
    	scanf("%d",&M);
    	printf("Gecerli bir N degeri giriniz");
    	scanf("%d",&N);
	}while(M <= 2 || N < 2*M);
    
    arr = add_node(M, N);
    
    for(i = 0; i < 3; i++){
        printf("List %d: ", i + 1);
        print_list(arr[i]);
        printf("\n");
    }
    
    int answer = find_passcode(&arr,M,N);
    printf("\n");
    
    for(i = 0; i < 3; i++){
        printf("List %d: ", i + 1);
        print_list(arr[i]);
        printf("\n");
    }
    
    
    for(i = 0; i < 3; i++){
        LINKED* current = arr[i];
        for(j = 0; j < M; j++){
            LINKED* temp = current;
            current = current->next;
            free(temp);
        }
    }
    free(arr);
    
    return 0;
}

LINKED* setNewHead(LINKED* head, int k, int t) {
    LINKED* tmp = head;
    int i;
    // carki dondurur
    if(t == 1){
        for(i = 0; i < k; i++){
            tmp = tmp->prev;
        }
    }else{
        for(i = 0; i < k; i++){
            tmp = tmp->next;
        }
    }
    return tmp;
}

int* set_pos(int n) {
    int *arr = (int*)malloc(3*sizeof(int));
    do {
        arr[0] = random(n);
        arr[1] = random(n);
        arr[2] = random(n);
    }while (arr[0] == arr[1] || arr[1] == arr[2] || arr[0] == arr[2]);

    return arr;
}

void hizala(LINKED*** arr, int* pos, int M, int N) {
    int k;
    int i;

    for(i = 1; i < 3; i++){
    	//sifrenin durumuna gore yapilan islemler ve dondurme sayisi ile donus yonu fonksiyona girer
    	//1 ve 0 sol ve sagi ifade eder.
        if(pos[0] < pos[i]){
            if(M/2 > pos[i] - pos[0]){
                k = pos[i] - pos[0];
                printf("\n%d. cark sol tarafa %d adet gider\n", i, k);
                (*(arr))[i] = setNewHead((*(arr))[i], k, 0);
            }else{
                k = M - pos[i] + pos[0];
                printf("\n%d. cark sag tarafa %d adet gider\n", i, k);
                (*(arr))[i] = setNewHead((*(arr))[i], k, 1);
            }
        }else{
            if(M/2 > pos[0] - pos[i]){
                k = pos[0] - pos[i];
                printf("\n%d. cark sag tarafa %d adet gider\n", i, k);
                (*(arr))[i] = setNewHead((*(arr))[i], k, 1);
            }else{
                k = M - pos[0] + pos[i];
                printf("\n%d. cark sol tarafa %d adet gider\n", i, k);
                (*(arr))[i] = setNewHead((*(arr))[i], k, 0);
            }
        }
    }
}


int find_passcode(LINKED*** arr, int M, int N) {
    int i, j, k;
    int pos[3] = {0};
    int datai, dataj, datak;
    int passcode;
    LINKED *headi = (*arr)[0], *headj = (*arr)[1], *headk = (*arr)[2];
	//linear search ama sadece ilk iki carkta eslesme buldugunda son carki ariyor
    for(i = 0; i < M; i++){
        datai = headi->data;
        for(j = 0; j < M; j++){
            dataj = headj->data;
            if(datai == dataj){
                for(k = 0; k < M; k++){
                    datak = headk->data;
                    if(datai == datak){
                        passcode = datak;
                        pos[0] = i;
                        pos[1] = j;
                        pos[2] = k;
                    }
                    headk = headk->next;
                }
            }
            headj = headj->next;
        }
        headi = headi->next;
    }
    printf("\nbulunan sifre: %d\n ",passcode);
    printf("\nsifrenin konumlari su sekildedir:\n1. carkta %d\n2. carkda %d\n3. carkda %d",pos[0]+1,pos[1]+1,pos[2]+1);
    hizala(arr, pos, M, N);
    return passcode;
}

LINKED** add_node(int M, int N){
    LINKED** arr = (LINKED**)malloc(sizeof(LINKED*) * 3);
    arr[0] = NULL;
    arr[1] = NULL;
    arr[2] = NULL;

    int passcode = random(N);
    int data;
    int *pos = set_pos(M);
    int* array = (int*)calloc(N + 1, sizeof(int));//TUM LINKED LISTTE HER SAYININ KAC KEZ GECTIGINI TUTAR



    int i, j;

    for(j = 0; j < 3; j++){
        LINKED* new_node = (LINKED*)malloc(sizeof(LINKED));
        int* array2 = (int*)calloc(N + 1, sizeof(int));//1 LINKE LISTTE O SAYININ GECIP GECMEDIGINI TUTAR

        for(i = 0; i < M; i++){
            if(pos[j] == i + 1){//SIFRE POZISYONU KONTROLU
                if(arr[j] == NULL){
                    data = passcode;
                    LINKED* new_node = (LINKED*)malloc(sizeof(LINKED));
                    new_node->prev = new_node;
                    new_node->next = new_node;
                    new_node->data = data;
                    array[data]++;
                    arr[j] = new_node;
                    array2[data] = 1;
                }else{
                    data = passcode;
                    LINKED* new_node = (LINKED*)malloc(sizeof(LINKED));
                    new_node->prev = arr[j]->prev;
                    new_node->next = arr[j];
                    arr[j]->prev->next = new_node;
                    arr[j]->prev = new_node;
                    new_node->data = data;
                    array[data]++;
                    arr[j] = new_node;
                    array2[data] = 1;
                }
            }else{
                if(arr[j] == NULL){
                    do{
                        data = random(N);
                        //RANDOM VE KURALLARA GORE SAYI URETIMI
                    }while (array[data] > j || array[data] == 2 || array2[data] == 1 || data == passcode);

                    LINKED* new_node = (LINKED*)malloc(sizeof(LINKED));
                    new_node->prev = new_node;
                    new_node->next = new_node;
                    new_node->data = data;
                    array[data]++;
                    arr[j] = new_node;
                    array2[data] = 1;
                }else{
                    do{
                        data = random(N);
                    }while (array[data] > j || array[data] == 2 || array2[data] == 1 || data == passcode);

                    LINKED* new_node = (LINKED*)malloc(sizeof(LINKED));
                    new_node->prev = arr[j]->prev;
                    new_node->next = arr[j];
                    arr[j]->prev->next = new_node;
                    arr[j]->prev = new_node;
                    new_node->data = data;
                    array[data]++;
                    arr[j] = new_node;
                    array2[data] = 1;
                }
            }
        }

        free(array2);
    }

    free(array);

    return arr;
}

void print_list(LINKED* head){
    LINKED* current = head;
            
    while(current->next != head){
        printf("%d ", current->data);
        current = current->next;
        
        
    }
    printf("%d ", current->data);
}

int random(int n){
    int k = rand() % n + 1; 
    return k;
}

