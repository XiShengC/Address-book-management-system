#include<stdio.h>
#include<stdlib.h> 
#include<string.h> 
#include <conio.h>

typedef struct _Contacts
{
	char Name[15];
	int  Mobile;
	int  Initial;
	bool Exist = false;
}Contacts;

Contacts Cont[1000];

int Array_Digit= 0;

void AddContacts(Contacts Cont[]);
void ShowContacts(Contacts Cont[]);
void DeateContacts(Contacts Cont[]);
void SearchContacts(Contacts Cont[]);//Fuzzy search
void ModifyContacts(Contacts Cont[]);

void BubSort_pro(Contacts Cont[]);
void Swap(Contacts *a, Contacts *b);

void FuzzySearch(int Position,char *SearchName);

int main()
{
	int instructions;

	printf("the mene of main function\n");

	while (1){
		printf("    Data addition input 1\n");
		printf("    Data display  input 2\n");
		printf("    Data deletion  input 3\n");
		printf("    Data query input 4\n");
		printf("    Data modification input 5\n");
		printf("    Quit the programer input 0\n");
		printf("Annotation:Digital input only\n");
        
		printf("Select function:");
		scanf("%d", &instructions);
		printf("English input only\n");

		if (instructions == 0)
			break;

		switch (instructions)
		{
		case 1:
			AddContacts(Cont);
			break;
		case 2:
			ShowContacts(Cont);
			break;
		case 3:
			DeateContacts(Cont);
			break;
		case 4:
			SearchContacts(Cont);
			break;
		case 5:
			ModifyContacts(Cont);
			break;
		default:
			printf("error\n");
		}
	}
	return 0;
}

void AddContacts(Contacts Cont[]){
	for(int i =0; i < 15; i++){
		Cont[Array_Digit].Name[i]='~';
    }
			
	printf("name:");
	scanf("%s",Cont[Array_Digit].Name);
	printf("number:");
	scanf("%d",&Cont[Array_Digit].Mobile);
	 
	Array_Digit++;
	
	Cont[Array_Digit-1].Initial = Cont[Array_Digit-1].Name[0];
	
	BubSort_pro(Cont);
}

void BubSort_pro(Contacts Cont[]) {
    for (int i = 0; i < Array_Digit; i++) {
        for (int j = 0; j + 1 < Array_Digit - i; j++) {
            if (Cont[j].Initial > Cont[j+1].Initial) {
                Swap(&Cont[j], &Cont[j+1]);
            }
        }
    }
}

void Swap(Contacts *a, Contacts *b) {
    Contacts temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

void DeateContacts(Contacts Cont[]){
	
	char name[15];

	bool ctl=true;
	
	printf("name:\n");
	scanf("%s",name);
	
	for(int i = 0;i <= Array_Digit;i++ ){
		if(strcmp(name, Cont[i].Name) == 0){
			printf("%d\n",Cont[i].Mobile);
			for(int j =i;j<=Array_Digit;j++){
				strcpy(Cont[j].Name,Cont[j+1].Name);
	            Cont[j].Mobile=Cont[j+1].Mobile;	
			}
			ctl = false;
			break;
		}
	}
	
	if (ctl==true){
		printf("Not exist\n");
	}
	else{
		Array_Digit--;	  
	}	
}

void SearchContacts(Contacts Cont[])//Fuzzy search: Sliding winddow algorithm to judge existence of minimum coverage subring
{
	char name[15];
	bool ctl = false;
	
	printf("name:");
	scanf("%s",name);
    
    for(int k=0;k<Array_Digit;k++){
    	FuzzySearch(k,name);
	}
	
	for(int l=0;l<Array_Digit;l++){
    	if(Cont[l].Exist==true){
    		if( ctl==false){
    			printf("Contact that meets the requirements:\n");
			}
    		ctl=true;
    		
    		printf("%s:",Cont[l].Name);
		    printf("%d\n",Cont[l].Mobile);
		    Cont[l].Exist=false;
		}
	}
	
	if(ctl==false){
		printf("Contents do not exist");
	}	
}

void FuzzySearch(int Position,char *SearchName){
	char s[100];
    char t[100];
    strcpy(s, SearchName);
    strcpy(t, Cont[Position].Name);
    
	int length_s = strlen(s);
    int length_t = strlen(t);
    int length_clean = length_s;
    
    int Length_rem = length_t;
    

    char clean[100];
    strcpy(clean, s);
    
    int req_count[128] = { 0 };
    int memory[128];

    int left = 0;
    int right = -1;
    int min,start,end;

    //Delate duplicates
    for (int i = 0; i < length_clean; i++) {
        for (int j = i + 1; j < length_clean; j++) {
            if (clean[i] == clean[j]) {
                for (int temp = j; temp < length_clean - 1; temp++) { clean[temp] = clean[temp + 1]; }
                j--;
                length_clean--;
            }
        }
    }
    clean[length_clean] = '\0';

    //Simulate        
    for (int n = 0; n < length_t; n++) {//for s
        for (int m = 0; m < length_clean; m++) {//for clean
            if (s[n] == clean[m]) req_count[m] ++;
        }
    }
    
	for(int y = 0; y < 3; y++) memory[y] = req_count[y];
	
    int ok_ctl = 0;
    int num_ctl;
    int j1 = 0;
        
    while (right < length_t  && ok_ctl == 0)
	{
	    ok_ctl=0; 
		right ++;  
       
		for (int i1 = 0; i1 < length_clean && ok_ctl == 0; i1 ++) {//To find the position for req_count to decrease
            if (t[right] == clean[i1])	 req_count[i1] --;
			 	
			num_ctl = length_clean;
                    
			for (j1 = 0; j1 < length_clean; j1 ++) {//After req_count decrease, determine if all the req_count is less or equal to 1
                if (req_count[j1] <= 0) {  
                    num_ctl --;
				} //All the req_count  is less than 0 or equal to 0
			}
			if(num_ctl == 0) {
                min = right - left;
                start = left;
                end = right;
                ok_ctl = 1;                        
            }
		}  
	}
	
    int remember = left;
    
	int fine_ctl = 0;     
    while ((right - left) >= length_s) 
	{
		fine_ctl = 0; 
		left = remember;
		left ++;
		remember = left;
		
		num_ctl = length_clean;	
		for(int y = 0; y < 3 ; y++)  req_count[y] = memory[y];
		
		while (left <= right && fine_ctl == 0) 
		{
		    for (int m = 0; m < length_clean && fine_ctl== 0 && left <= right; m ++)
			{
                num_ctl = length_clean;
			
			    if (t[left] == clean[m]){
				    req_count[m] --;			    			
			    }	 
								                    
			    for (int n = 0; n < length_clean; n ++) {
                    if (req_count[n] <= 0) {  
					    num_ctl --;
				    }
			    }
		
			    if(num_ctl == 0) {
			    	fine_ctl = 1;
			    	break;
				}	
		    }
		    left ++;
	    }
		   
		left = remember;
        
		if(num_ctl == 0) {
			if((right-left) <= min){
				min = right - left;
                start = left;
                end = right; 					
			}                     
        }
            
        else{
            if(right == (length_t-1) ) ;
			else right ++; 
			} 
	}
    
	if(left!=right||(left==0&&right==0)||left==Length_rem-1&&right==Length_rem-1){
		Cont[Position].Exist=true;
		//printf("primitive:%s\n",Cont[Position].Name);
	}    
//	printf("%d\n",left);
//	printf("%d\n",right);
}
				
void ShowContacts(Contacts Cont[]){

	for(int i = 0;i < Array_Digit;i++ ){
		printf("%s:",Cont[i].Name);
		printf("%d\n",Cont[i].Mobile);
		}
}

void ModifyContacts(Contacts Cont[]){
	char name[15];

	bool ctl=true;
	
	printf("name:\n");
	scanf("%s",name);
	
	for(int i = 0;i <= Array_Digit;i++ ){
		if(strcmp(name, Cont[i].Name) == 0){
			printf("number:");
			scanf("%d",&Cont[i].Mobile);	
			ctl = false;
		}
	}
	
	if (ctl==true){
		printf("Not exist\n");
	}
}
























