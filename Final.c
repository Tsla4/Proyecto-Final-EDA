#include <stdio.h>
#include <stdlib.h>

typedef struct
{
	char color;
	int numero;
} Ficha;

Ficha* crearFichas(int numFichas)
{
	Ficha* fichas = (Ficha*)malloc(numFichas * sizeof(Ficha));
	int contador=0;
	for (int numero = 1; numero<=13; numero++)
	{
		for(char color='A'; color <='D'; color++)
		{
			if(color=='A'){
			fichas[contador].numero = numero;
			fichas[contador].color = color;
			contador++;
			}
			if(color=='B'){
			fichas[contador].numero = numero;
			fichas[contador].color = 'N';
			contador++;
			}
			if(color=='C'){
			fichas[contador].numero = numero;
			fichas[contador].color = 'R';
			contador++;
			}
			if(color=='D'){
			fichas[contador].numero = numero;
			fichas[contador].color = 'V';
			contador++;
			}
		}
	}
	for (int numero = 1; numero<=13; numero++)
	{
		for(char color='A'; color <='D'; color++)
		{
			if(color=='A'){
			fichas[contador].numero = numero;
			fichas[contador].color = color;
			contador++;
			}
			if(color=='B'){
			fichas[contador].numero = numero;
			fichas[contador].color = 'N';
			contador++;
			}
			if(color=='C'){
			fichas[contador].numero = numero;
			fichas[contador].color = 'R';
			contador++;
			}
			if(color=='D'){
			fichas[contador].numero = numero;
			fichas[contador].color = 'V';
			contador++;
			}
		}
	}
	return fichas;
}

//STACKS
struct Stack {
    int top;
    unsigned capacity;
    int* array;
};

// function to create a stack of given capacity. It initializes size of
// stack as 0
struct Stack* createStack()
{
    struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack));
    stack->capacity = 110;
    stack->top = -1;
    stack->array = (int*)malloc(stack->capacity * sizeof(int));
    return stack;
}

// Stack is full when top is equal to the last index
int isFull(struct Stack* stack)
{
    return stack->top == stack->capacity - 1;
}

// Stack is empty when top is equal to -1
int isEmpty(struct Stack* stack)
{
    return stack->top == -1;
}

// Function to add an item to stack.  It increases top by 1
void push(struct Stack* stack, int item)
{
    if (isFull(stack)){
      printf("\tOverflow!\n");
      return;
    }

    stack->array[++stack->top] = item;
    printf("%d pushed to stack\n", item);
}

// Function to remove an item from stack.  It decreases top by 1
int pop(struct Stack* stack)
{
    if (isEmpty(stack)){
      printf("\tUnderflow!\n");
      return INT_MIN;
    }
    return stack->array[stack->top--];
}

// Function to return the top from stack without removing it
int peek(struct Stack* stack)
{
    if (isEmpty(stack)){
      printf("\tUnderflow!\n");
      return INT_MIN;
    }

    return stack->array[stack->top];
}

int revolver(Ficha* fichasPartida)
{
	
	Stack* Pozo = createStack();
	
}


int main()
{
	int elec, i=0;
	int numFichas = 104;
	Ficha* fichasPartida = crearFichas(numFichas);
	system("color 0E");
	printf( "BIENVENDIO A RUMMY DE LOS EDAMIGOS!\n" );
	printf( "Elige una opcion:\n1.-JUGAR\n2.-VER\n3.-SALIR\n" );
	scanf("%d", &elec);
	switch(elec)
	{
		case 1:

			printf("ESTAS SON TODAS lAS FICHAS DEL JUEGO:\n");
			for(i=0;i<numFichas;i++)
        		printf("%d%c, ",fichasPartida[i].numero, fichasPartida[i].color);
        	printf("\nREVOLVIENDO LAS FICHAS");
        	sleep(1);
        	printf(".");
        	sleep(1);
        	printf(".");
        	sleep(1);
        	printf(".");
        	sleep(1);
        	printf(".");
        	revolver(fichasPartida);
			break;
		case 2:
			printf("Construcion too...");
			break;
		case 3:
			return;
		default:
			printf("Opcion invalida, selecciona un numero del 1 al 3");
			sleep(3);
			system("CLS");
			main();
	}
	return 0;
}
