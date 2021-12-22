//Çiya Baran ÖNER 181180056
#include <stdio.h>
#include<string.h>

typedef struct list { //linked list
    int code;//lecture code
   	char lecture_name[50]; // lecture name
    struct list *next; // next element in list
} list;


list *new, *first = NULL, *temp; // creating lists
FILE *file,*new_file; // defination of files

//defination of functions
void addList(int,char*); // adds elements to list if doesn't exist already
void writeToFile(); // writes elements to Sorted.txt from list
void writeToScreen(); // writes elements to screen from list
void readFileAndAddToList(); // reads Data.dat and adds elements to list with using addList() function
void assignLectureName(char *d,char *e); // assigns lecture name from temp lecture names 

int main() { // main fuction

	readFileAndAddToList();
	writeToScreen();
	writeToFile();
	
}


void assignLectureName(char *d,char *e) // i created this method to change values by (Call By Referance)
{		
	strcpy(d,e);
}

void readFileAndAddToList() 
{
	char word[20]; // it will storage all words step by step while we reading the file
	char temp_lecture_name[50]; // it will storage lecture names temporary
	*temp_lecture_name='\0'; // i reseted this so as not to get the undesirable result, otherwise it storages a meaningless char for the first time
	
	file=fopen("Data.dat","r"); // open Data.dat file to read

	while(!feof(file)) // this continues if are there items to read
	{
		fscanf(file,"%s",&word); // assigns each words to the (var)word respectively, during the cycle

		if(atoi(word)==0) // if word is not a number
		{
			char space[]=" "; 
			strcat(temp_lecture_name,space); // adds a space between words
			strcat(temp_lecture_name,word); // combine words to complete lecture names. It works until we encounter a lecture code

		}
		else //if we encounter a lecture code, it means the lecture name storaging has been completed  
		{	
			char* s;
			s=word;
			int temp_lecture_code=atoi(s); // we changed lecture code from string to int

			addList(temp_lecture_code,temp_lecture_name); // adds datas to linkedlist
			*temp_lecture_name='\0'; // i reseted temp_lecture_name because it will receive new values, otherwise it storages old values as well
		}	
	
	}

	fclose(file); // close file
}

void writeToFile() 
{
	new_file=fopen("Sorted.dat","w"); //open file to write
    //if file is empty
    if (first == NULL) 
    	printf("List is empty\n");

    else 
	{
    	temp = first; //not to lose first value
    	while (temp != NULL) // it works till reaching to the last element in list
		{
    		fprintf(new_file,"%d\t %s\n", temp->code,temp->lecture_name); // write to the file
    		temp = temp->next; // moving to the next element
    	}
    }
    fclose(new_file); //close the file
} 

void writeToScreen()
{
    //if file is empty
    if (first == NULL) 
    	printf("List is empty\n");

    else 
	{
    	temp = first;//not to lose first value
    	while (temp != NULL) // it works till reaching to the last element in list
		{	
			printf("%d\t %s\n", temp->code,temp->lecture_name);// write to the screen
    		temp = temp->next; // moving to the next element
    	}
    }
} 


void addList(int number,char *temp_lecture_name) 
{ 
    //if list is empty, adds element to the first order
    if (first == NULL)
	{	
    	first= (list*) malloc(sizeof (list)); 
        first->code = number; //lecture code has been assigned for the element 
        first->next= NULL; 
        assignLectureName(&first->lecture_name,temp_lecture_name); //lecture name has been assigned for the element. (CALL BY REFERANCE)
        
    } else { // if list is not empty
  	  	temp = first; //to start from first element
  	  	
  	  	//is element already exist
    	while (temp != NULL) //unless it is last element
		{
        	if (temp->code == number){ // if element is already exist
			//printf("Var olan item.\n");
			return ;
        }
		temp = temp->next;
    	}
    	
        //if number is less than lecture code of in the first position element, it will be new first element
        if ((first->code) > (number)) 
		{
            new = (list*) malloc(sizeof (list));
            new->code = number;	//lecture code has been assigned for the element 
            assignLectureName(&new->lecture_name,temp_lecture_name); //lecture name has been assigned for the element. (CALL BY REFERANCE)
            new->next= first;
			first = new;
         
        } 
		else
		{ 
            temp = first;
            new= (list*) malloc(sizeof (list));
            new->code = number; //lecture code has been assigned for the element 
        	assignLectureName(&new->lecture_name,temp_lecture_name); //lecture name has been assigned for the element. (CALL BY REFERANCE)   
			while (temp != NULL) 
			{
                //if number is bigger than lecture code of in the last position element, it will be new last element
                if (temp->next == NULL && (temp->code) <= (number)) 
				{
                    new->next = NULL;
                    temp->next= new;
                    break;
                }
                //if it could not add element to the first or last position. we will control the other elements
                if ((temp->next->code) > (number)) 
				{
                    new->next= temp->next;
                    temp->next= new;
					break;
                }
                temp = temp->next; // go next
            }
        }
    }
    
}

 


