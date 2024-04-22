#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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
	fichas[104].numero = 0;
	fichas[104].color = 'C';
	fichas[105].numero = 0;
	fichas[105].color = 'C';
	
	return fichas;
}

//STACKS
struct Stack {
    int top;
    unsigned capacity;
    Ficha* array;
};

// function to create a stack of given capacity. It initializes size of
// stack as 0
struct Stack* createStack()
{
    struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack));
    stack->capacity = 110;
    stack->top = -1;
    stack->array = (Ficha*)malloc(stack->capacity * sizeof(Ficha));
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
void push(struct Stack* stack, Ficha item)
{
    if (isFull(stack)){
      printf("\tOverflow!\n");
      return;
    }

    stack->array[++stack->top] = item;
    printf("(%d%c) pushed to stack\n", item.numero, item.color);
}

// Function to remove an item from stack.  It decreases top by 1
Ficha pop(struct Stack* stack)
{
    if (isEmpty(stack)){
      printf("\tUnderflow!\n");
      Ficha emptyFicha = { .color = '\0', .numero = INT_MIN };
      return emptyFicha;
    }
    return stack->array[stack->top--];
}

// Function to return the top from stack without removing it
Ficha peek(struct Stack* stack)
{
    if (isEmpty(stack)){
      printf("\tUnderflow!\n");
	  Ficha emptyFicha = { .color = '\0', .numero = INT_MIN };
      return emptyFicha;;
    }

    return stack->array[stack->top];
}


int revolver(Ficha* fichasPartida)
{
    // Crear una stack para las fichas
    struct Stack* Pozo = createStack();

    // Arreglo de índices para representar las posiciones de las fichas
    int* indices = (int*)malloc(sizeof(int) * 106);
    for (int i = 0; i < 106; ++i)
        indices[i] = i;

    // Barajar los índices aleatoriamente
    srand(time(NULL));
    for (int i = 106 - 1; i > 0; --i) {
        int j = rand() % (i + 1);
        int temp = indices[i];
        indices[i] = indices[j];
        indices[j] = temp;
    }

    // Iterar sobre los índices barajados y agregar las fichas correspondientes a la stack
    for (int i = 0; i < 106; ++i) {
        Ficha ficha = fichasPartida[indices[i]];
        push(Pozo, ficha);
        }
	free(indices);
    return 0;
}

int main()
{
	int elec, i=0;
	int numFichas = 106;
	Ficha* fichasPartida = crearFichas(numFichas);
	while(1){
	system("CLS");
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
        	system("pause");
        	//repartir(Pozo);
			break;
		case 2:
			printf("Construcion too...");
			system("pause");
			break;
		case 3:
			return;
		default:
			printf("Opcion invalida, selecciona un numero del 1 al 3");
			sleep(3);
			system("CLS");
			main();
	}
	}
	return 0;
}
