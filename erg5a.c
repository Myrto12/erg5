#include <stdio.h>
#include <stdlib.h>
#define N 10

typedef enum {false = 0,true = 1} bool;
typedef bool (*FUNC) (bool);

typedef struct gate{
    bool in;
    bool out;
    FUNC behavior;
    struct gate *next;
} GATE;

bool gate_func_not(bool);
GATE * create_gate();
void create_linked_list(GATE *);
void calculate_circuit_output(GATE *);

int main(void){
    GATE *head=create_gate(); //φτιαχνω το πρωτο gate
    head->in=1;   //δινω εισοδο 1
    create_linked_list(head);//δημιουργω linked list και κατα τη δημιουργια καθε κομβου καλειται η create gate ωστε καθε κομβος να αντιστοιχει σε gate
    calculate_circuit_output(head);//Διατρεχει καθε κομβο, υπολογιζει την εξοδο και την οριζει σαν εισοδο στην επομενη πυλη
    getchar();
    return 0;
}

bool gate_func_not(bool in) {
    return !in;  //επιστρεφει ΝΟΤ(in)
}

void create_linked_list(GATE *head){
    GATE *tmp=head;
    for(int i=1;i<N;i++){
        tmp->next=create_gate(); //καθε κομβος αντιστοιχει σε πυλη

        tmp=tmp->next;  //συνδεση κομβου με τον επομενο
    }
}

GATE * create_gate(){
    GATE *newgate = malloc(sizeof(GATE));  //δεσμευει χωρο για την πυλη
    if(newgate==NULL){
        printf("memory not allocated\n");
    }
    else{
        newgate->behavior=gate_func_not;  //δημιουργει πυλη NOT 
        newgate->next=NULL;  //παει στην επομενη πυλη
        newgate->in=true;
        newgate->out=true;
    }
    return newgate;
}

void calculate_circuit_output(GATE *head){
    GATE *current = head;
    int gate_number = 1;
    while(current!=NULL){
        current->out = (current->behavior)(current->in); //βγαζει την αντιθετη τιμη 
        printf("GATE No%d   IN:%d   OUT:%d\n",gate_number,current->in,current->out);
        gate_number++;
    
    if(current->next!=NULL){
        current->next->in = current->out;  //η εισοδος της επομενης ειναι η εξοδος της προηγουμενης

    }
    current = current->next; //παω στον επομενο κομβο της λιστας
    }
    return;
}