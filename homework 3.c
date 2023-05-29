#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
typedef struct vector {
    int data[2];
}VECTOR;

typedef struct adjencylist {
    int vector_num;
    VECTOR *vectors;
}ADJENCY;

bool check(int* l, int n); 


ADJENCY* toList(int courseNum, int** matrix,int k);


void calculate(ADJENCY* node, int n);


int main(void){
	
	int i,j,k = 0;
	int courseNum;
	printf("enter the number of courses\n");
	scanf("%d",&courseNum);
	int **adjencyMatrix;
	
	adjencyMatrix = (int**)malloc(courseNum*(sizeof(int*)));
	for(i = 0;i < courseNum;i++){
		adjencyMatrix[i] = (int*)calloc(courseNum,sizeof(int));
	}
	for(i = 0;i < courseNum;i++){
		for(j = 0; j < courseNum;j++){
			
				printf("%d. kursun %d. kurs ile baglantisi olup olmadigini giriniz\nvar ise 1 yok ise 0\n",i+1,j+1);
				scanf("%d",&adjencyMatrix[i][j]);
				if(i == j){
					adjencyMatrix[i][j] = 0;
				}
				if(adjencyMatrix[i][j] == 1){
					k++;
				}
			}
	}
	printf("\n\n\n-------------------------------------------\n");
	
	ADJENCY *tmp = toList(courseNum,adjencyMatrix,k);
	
	
	for(i = 0;i < courseNum;i++){
		free(adjencyMatrix[i] );
	}
	free(adjencyMatrix);
	
	
	calculate(tmp,courseNum);
	free(tmp->vectors);
	
	return 0;
}

bool check(int* l, int n) {
    int i;
    for (i = 0; i < n; i++) {
        if (l[i] >= 0) {
            return true;
        }
    }
    return false;
}
void calculate(ADJENCY* node, int n) {
    int* l = (int*)calloc(sizeof(int), n);
    int i, k,j = node->vector_num;
	int *bckup = (int*)calloc(sizeof(int), n);
    for (i = 0; i < j; i++) {
        l[node->vectors[i].data[1] - 1]++;
        bckup[node->vectors[i].data[1] - 1]++;
    }
    
    int dcounter = 1;       

    while (check(l, n)) {//worst case n-1 time
    	printf("%d. donem alinacak dersler ",dcounter);
    	dcounter++;
        for (i = 0; i < n; i++) {// n time
            if (l[i] == 0) {
                bckup[i] = -1;
                
                for (k = 0; k < j; k++) {//v time
                    if (i + 1 == node->vectors[k].data[0]) {
                        bckup[node->vectors[k].data[1] - 1]--;
                    }                    
                }
                printf("%d - ", i + 1);     
                
            }
        }
        for (i = 0; i < n; i++) {
            l[i] = bckup[i];  // Copy values from bckup to l
        }
        printf("\n");
    }
    printf("\n%d donemde ogrenci bolumu bitirir\n",dcounter -1);

    free(l);
	free(bckup);  
}

ADJENCY* toList(int courseNum, int** matrix,int k) {
    ADJENCY* head = (ADJENCY*)malloc(sizeof(ADJENCY));
    head->vectors = (VECTOR*)malloc(sizeof(VECTOR) * k);
    head->vector_num = 0;
    int i, j;
    for (i = 0; i < courseNum; i++) {
    	
        for (j = 0; j < courseNum; j++) {
            if (matrix[i][j] != 0) {
                head->vector_num++;
                head->vectors[head->vector_num - 1].data[0] = i+1;
                head->vectors[head->vector_num - 1].data[1] = j+1;
                
                
            }
            
        }
        
    }
    return head;
}

