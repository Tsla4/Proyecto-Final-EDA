#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

int x = 0;
char jugador[15] = "";

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
typedef struct {
    int top;
    unsigned capacity;
    Ficha* array;
}Stack;

// function to create a stack of given capacity. It initializes size of
// stack as 0
Stack* createStack()
{
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    stack->capacity = 110;
    stack->top = -1;
    stack->array = (Ficha*)malloc(stack->capacity * sizeof(Ficha));
    return stack;
}

// Stack is full when top is equal to the last index
int isFull(Stack* stack)
{
    return stack->top == stack->capacity - 1;
}

// Stack is empty when top is equal to -1
int isEmpty(Stack* stack)
{
    return stack->top == -1;
}

// Function to add an item to stack.  It increases top by 1
void push(Stack* stack, Ficha item)
{
    if (isFull(stack)){
      printf("\tOverflow!\n");
      return;
    }

    stack->array[++stack->top] = item;
    //printf("(%d%c) pushed to stack\n", item.numero, item.color);
}

// Function to remove an item from stack.  It decreases top by 1
Ficha pop(Stack* stack)
{
    if (isEmpty(stack)){
      printf("\tUnderflow!\n");
      Ficha emptyFicha = { .color = '\0', .numero = INT_MIN };
      return emptyFicha;
    }
    return stack->array[stack->top--];
}

// Function to return the top from stack without removing it
Ficha peek(Stack* stack)
{
    if (isEmpty(stack)){
      printf("\tUnderflow!\n");
	  Ficha emptyFicha = { .color = '\0', .numero = INT_MIN };
      return emptyFicha;;
    }

    return stack->array[stack->top];
}
//FIN STACKS

//MANOS DE JUGADORES DLL

typedef struct node{
    Ficha key;
    struct node* prev;
    struct node* next;
 
} node;
 
// Head, Tail, first & temp Node
typedef struct {
node* head;
node* tail;
} Hand;

Hand* createHand(){
	Hand* hand = (Hand*)malloc(sizeof(Hand));
	hand->head=NULL;
	hand->tail=NULL;
	return hand;
}

void addToHand(Hand* hand, Ficha ficha) {
    node* newNode = (node*)malloc(sizeof(node));
    newNode->key = ficha;
    newNode->prev = hand->tail;
    newNode->next = NULL;
    if (hand->tail != NULL) {
        hand->tail->next = newNode;
    }
    hand->tail = newNode;
    if (hand->head == NULL) {
        hand->head = newNode;
    }
}

void printHand(Hand* hand) {
    node* current = hand->head;
    int index = 1; // Variable para mantener el índice de la ficha
    while (current != NULL) {
        printf("%d:(%d%c) ", index, current->key.numero, current->key.color);
        current = current->next;
        index++; // Incrementar el índice para la siguiente ficha
    }
    printf("\n");
}

Ficha removeFromHand(Hand* hand,int pos)
{
	Ficha tiroFicha;
	node* current = hand->head;
	int cont=0;
	while(current != NULL && cont!=pos)
	{
		current = current->next;
		cont++;
	}
	
	tiroFicha = current->key;
	if(current->prev!=NULL)
		current->prev->next = current->next;
	else
		hand->head = current->next;
	
	return current->key;
	
}

Ficha peekHand(Hand* hand,int pos)
{
	Ficha ficha;
	node* current = hand->head;
	int cont=0;
	while(current != NULL && cont != pos)
	{
		current = current->next;
		cont++;
	}
	ficha = current->key;
	return current->key;
}

//FIN MANOS DE JUGADORES DLL

Stack* revolver(Ficha* fichasPartida)
{
    // Crear una stack para las fichas
    Stack* Pozo = createStack();

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
    return Pozo;
}
int loading(){
	sleep(1);
    printf(".");
	sleep(1);
	printf(".");
	sleep(1);
	printf(".");
	sleep(1);
	printf(".");
	sleep(1);
	return 0;	
}

Hand repartir(Hand* manoJu, Stack* Pozo)
{
	for(int i=0;i<15;i++)
		addToHand(manoJu, pop(Pozo));
}
//Crear cola para jugadores
typedef struct {
	Hand* pHands[4];
	int front;
	int rear;
	int size;
}Turns;

Turns* createTurns()
{
	Turns* turnos = (Turns*)malloc(sizeof(Turns));
	turnos->front=-1;
	turnos->rear=-1;
	turnos->size=4;
	return turnos;	
}


Turns* handToTurns(Hand* manoJug, Turns* turnos)
{
	if(turnos->front==-1)
	{
		turnos->pHands[0] = manoJug;
		turnos->front = turnos->front+1;
		turnos->rear = turnos->rear+1;
	}
	else
	{
		turnos->rear = (turnos->rear+1) % turnos->size;
		turnos->pHands[turnos->rear] = manoJug;
	}
	system("CLS");
	printf("Se agrego la mano al juego\n");
	printHand(manoJug);
	system("pause");
	return turnos;
}

void printTurnos(Turns* turno)
{

	for(int i=turno->front;i<=turno->rear;i++)
	{
		if(i==0)
			printf("\nMano de %s", jugador);
		else
			printf("\nMano de CPU%d", i);
			
		printHand(turno->pHands[i]);
		system("pause");
	}
}

//fin cola para jugadores




//CREAR MESA

typedef struct{
	Ficha tiro[100];
	int next;
	int prev;
}Jugada;

Jugada* createJugada()
{
	Jugada* jugada =(Jugada*)malloc(sizeof(Jugada));
	jugada->next=-1;
	jugada->prev=-1;
	return jugada;
}

typedef struct{
	Hand* jugadas;
	int prev;
	int next;
}Mesa;

Mesa* createMesa()
{
	Mesa* mesa = (Mesa*)malloc(sizeof(Mesa));	
	mesa->prev=-1;
	mesa->next=-1;
	return mesa;	
}

void addToMesa(Mesa* mesa, Hand* jugada)
{
    Hand* newHand = createHand();
    newHand->head = jugada->head;
    newHand->tail = jugada->tail;

    if (mesa->next == NULL && mesa->prev == NULL)
	{
        mesa->jugadas = newHand;
        mesa->next = newHand;
        mesa->prev = newHand;
    }
	else
	{
        mesa->jugadas->tail->next = newHand;
        mesa->next = newHand;
    }
}

// FIN MESA

//

//

//Gameplay
Hand* fichasParaJugar(Hand* manoJugador, Mesa* mesa)
{
	Hand* jugada = createHand();
	Hand* valida = createHand();
	int remove[15]; 
	int seleccion;
	int v=0, i=0, valid, p=0;
	char res1, res2, res3;
	printf("\nSelecciona la posicion de las ficha que deseas jugar y presiona (ENTER) (Ingresa -1 para terminar)");
	sleep(2);
	do
	{
		printf("\nIngresa el indice de la ficha que desas jugar: ");
		scanf("%d", &seleccion);
		if (seleccion >=0)
		{
			addToHand(jugada, peekHand(manoJugador, seleccion-1));
		}
		else if(seleccion != -1)
		printf("Indice invalido. Por favor, selecciona un indice dentro del rango");
		
		remove[i] = seleccion-1;
		i++;
		p++;
		
	}
	while (seleccion != -1);
	
	
	do
	{
	
	printf("\nLas fichas que seleccionaste son: ");
	printHand(jugada);
	setbuf(stdin,NULL);
	printf("\nEs correcto? S/N\n");
	scanf("%c", &res1);
	switch(res1)
	{
		case 'S':
			valid = ValidPlay(jugada);
			if (valid==1)
			{
				printf("%d\n", p-1);
				system("pause");
				for(i=0; i < p-1;i++)
				{
					addToHand(valida,removeFromHand(manoJugador, remove[i]-i));
					printf("anadiendo %d",i);
					sleep(1);
				}
				//addToMesa(mesa, valida);
			}
			break;
		case 'N':
			fichasParaJugar(manoJugador, mesa);
		default:
			printf("\nOpcion no valida, selecciona 'S' para si, 'N para no'");
			sleep(2);
			v=1;
	}
	}
	while(v==1);
	
	do
	{
	setbuf(stdin,NULL);
	printf("\nQuieres agregar otra jugada? S/N\n");
	scanf("%c", &res2);
	system("pause");
	switch(res2)
	{
		case 'S':
			system("CLS");
			printf("\nTU MANO ES:\n");
			printHand(manoJugador);
			fichasParaJugar(manoJugador, mesa);
		case 'N':
			break;
		default:
			printf("\nOpcion no valida, selecciona 'S' para si, 'N para no'");
			sleep(2);
			v=2;
	}
	}
	while(v==2);


}


int ValidPlay(Hand* mano)
{
	node* current = mano->head;;
	int cont=0;
	int val_num = 0, val_col = 0;
	while(current->next != NULL)
	{
		if(current->key.numero==current->next->key.numero)
		{
			val_num++;
			current = current->next;
			cont++;
		}
		else if(current->key.numero+1==current->next->key.numero && current->key.color==current->next->key.color)
			{
			val_num++;
			val_col++;
			current = current->next;
			cont++;
			}
		else
		{
			printf("\nNO ES UNA JUGADA VALIDA!!");
			
			//añadir de vuelta a mano jugador
			return 0;
		}
	}
		if(cont>=2 && val_num == val_col)
			{
				printf("ES UNA CORRIDA, SE AGREGA A LA MESA\n");
				system("pause");
				return 1;
				//añadir a la mesa
			}
		else if(cont>=2 && val_num>=2)	
		{
				printf("ES UNA TERCIA, SE AGREGA A LA MESA\n");
				system("pause");
				return 1;
				//añadir a la mesa
		}
		else
		{
			printf("\nFALTAN FICHAS, LA JUGADA DEBE SER DE 3 O MAS");
			sleep(2);
			return 0;
		}
}


//Fin Gameplay

//JUEGO

startGame(Turns* turno, Stack* Pozo, Mesa* mesa)
{
	int t=1;
	int trn=0;

	while(Pozo!=isEmpty){
		system("CLS");
		printf("Turno %d", t);
		//TURNO DEL JUGADOR
		if(trn==0)
		{
			printf("\nTurno de %s", jugador);
			printf("\nTU MANO ES:\n");
			printHand(turno->pHands[trn]);
			fichasParaJugar(turno->pHands[trn], mesa);
			//jugada = opcionesTiro(turno->pHands[trn]);
			system("pause");
		}
		//TURNO DE CPU
		else
		{
			printf("\nTurno de CPU%d", trn);
			printf("\nCPU%d esta pensando", trn);
			loading();
		}
		trn=(trn+1)%4;
		t=t+1;
	}
}


//Fin Juego

int main()
{

	int elec, i=0;
	int numFichas = 106;
	Ficha* fichasPartida = crearFichas(numFichas);
	Turns* turnos = createTurns();
	Mesa* mesa = createMesa();

	
	while(1){
	system("CLS");
	system("color 0E");
	printf( "BIENVENDIO A RUMMY DE LOS EDAMIGOS!\n" );
	printf( "Elige una opcion:\n1.-JUGAR\n2.-VER\n3.-SALIR\n" );
	scanf("%d", &elec);
	switch(elec)
	{
		case 1:
			printf("INTRODUCE TU NOMBRE:\n");
			scanf("%s", jugador);
			printf("ESTAS SON TODAS LAS FICHAS DEL JUEGO:\n");
			for(i=0;i<numFichas;i++)
        		printf("%d%c, ",fichasPartida[i].numero, fichasPartida[i].color);
        	printf("\nREVOLVIENDO LAS FICHAS");
        	loading();
			Stack* Pozo = revolver(fichasPartida);
			Hand* jugador1 = createHand();
			Hand* CPU1 =createHand();
			Hand* CPU2 =createHand();
			Hand* CPU3 =createHand();
        	repartir(jugador1, Pozo);
        	repartir(CPU1, Pozo);
        	repartir(CPU2, Pozo);
        	repartir(CPU3, Pozo);
        	printf("\nREPARTIENDO FICHAS");
        	loading();
        	system("CLS");
        	printf("\nFichas en la mano de %s:\n", jugador);
        	printHand(jugador1);
        	printf("\nFichas en la mano de CPU1:\n");
        	printHand(CPU1);
        	printf("\nFichas en la mano de CPU2:\n");
        	printHand(CPU2);
        	printf("\nFichas en la mano de CPU3:\n");
        	printHand(CPU3);
        	system("pause");
        	handToTurns(jugador1, turnos);
        	handToTurns(CPU1, turnos);
        	handToTurns(CPU2, turnos);
        	handToTurns(CPU3, turnos);
        	system("CLS");
        	printf("Imprimir lista de turnos");
        	printTurnos(turnos);
        	system("CLS");
        	printf("\nCOMIENZA EL JUEGO!!!!!");
        	system("pause");
        	while(1)
        	{
        		startGame(turnos, Pozo, mesa);
			}
			break;
		case 2:
			printf("Construccion");
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
