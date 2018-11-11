#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define order 4

struct word_meaning {
    char word[16];
    char meaning[50];
};

struct node {
    int isleaf;
    int child_pointer[order +1];
    int blockno;
    int parent_blockno;
    int count;
    struct word_meaning pair[order];
};

void Sort(struct node *root)
{
    printf("at 23\n");
    struct word_meaning temp;
    int i,j;
    for (i = 0; i < root->count - 1 ; i++)
    {
        for (j = i + 1; j < root->count; j++)
        {
            if (strcmp(root->pair[i].word, root->pair[j].word) > 0)
            {
           //     printf("%s %s \n",root->pair[i].word,root->pair[j].word);
                temp = root->pair[i];
                root->pair[i] = root->pair[j];
                root->pair[j] = temp;
            }
        }
    }
}
void split_root(FILE *fptr,struct node *root)
{
    
    struct node *left = (struct node *)malloc(sizeof(struct node));
    struct node *right = (struct node *)malloc(sizeof(struct node));
   // printf("left ->count :%d \n right ->count :%d \n ",left->count,right->count);
    int median = (0 + root->count-1) / 2 ;
   // printf("\nMeidan : %d\n",median);
    int i ;
    for( i = 0; i < median  ; i++) {
        left->pair[i] = root->pair[i];
        left->count++;
    }
    left->isleaf = 1;
    for (i = 0 ; i < left->count ; i++)
    {
        
        printf("Word: %s\t Meaning: %s\t block no: %d   count : %d\n", left->pair[i].word,left->pair[i].meaning, left->blockno,left->count);
        
    }
    printf("\n-----------------------------------\n");
    int j = 0;
  //  printf("\nMeidan : %d\n",median);
    int k = median + 1;
    for( ; k < root->count; k++) {
        right->pair[j] = root->pair[k];
        right->count++;
        j++;
    }
    right->isleaf = 1;
   // printf("right ->count :%d \n",right->count);
    for (i = 0 ; i < right->count ; i++)
    {
        
        printf("Word: %s\t Meaning: %s\t block no: %d   count : %d\n", right->pair[i].word,right->pair[i].meaning, right->blockno,right->count);
        
    }
    printf("\n-----------------------------------\n");

    for( i = 0 ; i < root->count; i++) {
        if(i == 0) {
            root->pair[i] = root->pair[median];
        }
        else{
                strcpy(root->pair[i].word ,"");
                strcpy(root->pair[i].meaning ,"");
           }
    }
        root->count = 1;
    root->isleaf = 0;
    
    for (i = 0 ; i < order ; i++)
    {
        
        printf("Word: %s\t Meaning: %s\t block no: %d   count : %d\n", root->pair[i].word,root->pair[i].meaning, root->blockno,root->count);
        
    }
    printf("\n-----------------------------------\n");
}
void Insert(FILE *fptr, char *word, char *mean)
{
    int i,j;
    fseek(fptr,0,SEEK_SET);
    struct node *root = (struct node *) malloc(sizeof(struct node));
    fread(root, sizeof(struct node), 1, fptr);
    
   // fseek(fptr,0,SEEK_END);
    // printf("Word: %s\t Meaning: %s\t block no: %d   count : %d\n", root->pair[0].word,root->pair[0].meaning, root->blockno,root->count);
    if(root->count == order)
    {
        printf("overflow\n");
        split_root(fptr,root);
        
    } else {
        
        printf("-->%d\n",root->count);
        strcpy(root->pair[root->count].word , word);
        strcpy(root->pair[root->count].meaning , mean);
        root->count++;
        
        printf("-->%d\n",root->count);
        Sort(root);
        fseek(fptr,0,SEEK_SET);
        fwrite(root, sizeof(struct node), 1, fptr);
        
    }
    printf("\n-----------------------------------\n");
    
    fseek(fptr,0,SEEK_SET);
    fread(root, sizeof(struct node), 1, fptr);
   for (i = 0 ; i < order ; i++)
    {
        
            printf("Word: %s\t Meaning: %s\t block no: %d   count : %d\n", root->pair[i].word,root->pair[i].meaning, root->blockno,root->count);
        
    }
    
    
}
int main()
{
    
    FILE *fptr;
    
    printf("\nsize of node %lu\n",sizeof(struct node));
    fptr = fopen("dictionary","rb+");

    if(fptr == NULL)
    {
       // printf("Error \n");
        //return 0;
       struct node *root = (struct node *)malloc(sizeof(struct node));
        root->isleaf = 1;
        root->blockno = 0;
        root->parent_blockno = -1;
       // strcpy(root->pair[0].word ,"I");
        //strcpy(root->pair[0].meaning ,"I is pronoun");
        root->count = 0;
      
        
        fptr = fopen("dictionary","wb+");
        //printf("at 37 \n");
        fwrite(root, sizeof(struct node), 1, fptr);
        
        //fseek(fptr,0,SEEK_SET);
        
        //printf("at 42 \n");
        
        //fread(root, sizeof(struct node), 1, fptr);
        
      // printf("Word: %s\t Meaning: %s\t block no: %d", root->pair[0].word,root->pair[0].meaning, root->blockno);
        
        //printf("at 43");
      //  fclose(fptr);
    }
    
     //   printf("Word: %s\nMeaning:%s\nblock no: %d\ncount: %d \n", root->pair[0].word,root->pair[0].meaning, root->blockno,root->count);
        
       
        char w[99],m[99];
        scanf("%s",w);
        scanf("%s",m);
        Insert(fptr,w,m);
        fclose(fptr);
    
    return 0;
}
