//-------------
// Libraries ||
//-------------
# include <iostream>

//-------------
// Constants ||
//-------------
# define TOTAL_WAGONS 4
# define FULL       0x00000000
# define FIRST_BIT  0x80000000
# define LAST_BIT   0x00000001

//-------------------------------
// Structs, Methods, Functions ||
//-------------------------------

/*  Diseño de la estructura de datos:

-   La disponibilidad de los asientos se representan mediante bits
    donde 0 indica OCUPADO y 1 indica DISPONIBLE

-   Se opto esta simbologia con la intencion de poder comparar con
    el operador & y una constante para excluir otros bits

Ej. num = 5     (0101)
    num & 8     (& 1000 = 0000) Asiento 1 ocupado

    num <<= 1   (1010)  Revisa asiento 2
    num &= 8    (1000)  Apaga bits en otras posiciones
    num == 8    (true)  Asiento disponible

-   Cada vagon es entonces representado por un numero entero (32 asientos)
    dando como resultado un arreglo de enteros para modelar el tren         */
struct Train
{
    unsigned int wagons[TOTAL_WAGONS];
};

/*  F:  Revisa si el bit de una posicion N esta encendido
    I:  wagon (int)  - Representacion entera de un vagon
        seatID (int) - Posicionamiento de izq a derecha
    O:  Retorna true si el asiento esta disponible, false si no */
bool is_first_available(int wagon, int seatID)
{
    wagon <<= seatID;
    return ((wagon & FIRST_BIT) == FIRST_BIT);
}// Function end

/*  F:  Revisa si el bit de una posicion N esta encendido
    I:  wagon (int)  - Representacion entera de un vagon
        seatID (int) - Posicionamiento de derecha a izq
    O:  Retorna true si el asiento esta disponible, false si no */
bool is_last_available(int wagon, int seatID)
{
    wagon >>= seatID;
    return ((wagon & LAST_BIT) == LAST_BIT);
}// Function end

/*  F:  Recorre y encuentra los primeros 10 asientos disponibles de un tren
    I:  train (Train) - Arreglo de enteros representativos de un vagon
    O:  Imprime los asientos mediante identificadores numericos */
void print_first_seats(Train& train)
{
    int index = 0;
    int count = 0;
    for (; index < TOTAL_WAGONS; index++)
    {
        int wagon = train.wagons[index];
        int seatID = 0;
        if ( wagon == FULL)
            continue;
        for (; seatID < (sizeof(int) * 8); seatID++)
        {
            if (is_first_available(wagon, seatID))
            {
                count++;
                if (count < 10)
                {
                    printf("%d, ", (32*index + seatID + 1));
                } else {
                    printf("%d.", (32*index + seatID + 1));
                    return;
                }
            }
        }
    }
}// Function end

/*  F:  Recorre y encuentra los ultimos 10 asientos disponibles de un tren
    I:  train (Train) - Arreglo de enteros representativos de un vagon
    O:  Imprime los asientos mediante identificadores numericos */
void print_last_seats(Train& train)
{
    int index = TOTAL_WAGONS - 1;
    int count = 0;
    for (; index >= 0; index--)
    {
        int wagon = train.wagons[index];
        int seatID = 0;
        if ( wagon == FULL)
            continue;
        for (; seatID < (sizeof(int) * 8); seatID++)
        {
            if (is_last_available(wagon, seatID))
            {
                count++;
                if (count < 10)
                {
                    printf("%d, ", (32*index + 32 - seatID));
                } else {
                    printf("%d.", (32*index + 32 - seatID));
                    return;
                }
            }
        }
    }
}// Function end

/*  F:  Encuentra los 10 primeros y ultimos asientos disponibles de un tren
    I:  train (Train) - Arreglo de enteros representativos de un vagon
    O:  Imprime los asientos mediante identificadores numericos */
void print_seats(Train& train)
{
    printf("Primeros 10 asientos disponibles: ");
    print_first_seats(train);
    printf("\nUltimos 10 asientos disponibles: ");
    print_last_seats(train);
}// Function end

//----------------
// Main Program ||
//----------------

Train example1 = {0xF8880000,   // (  1 -  32) |  1111 1000 1000 1000 0000 0000 0000 0000
                 FULL,          // ( 33 -  64) |  0000 0000 0000 0000 0000 0000 0000 0000
                 0x0000006B,    // ( 65 -  96) |  0000 0000 0000 0000 0000 0000 0110 1011
                 0x00000004};   // ( 97 - 128) |  0000 0000 0000 0000 0000 0000 0000 0100

Train example2 = {FULL,         // (  1 -  32) |  0000 0000 0000 0000 0000 0000 0000 0000
                 0x09000200,    // ( 33 -  64) |  0000 1001 0000 0000 0000 0010 0000 0000
                 0x0001000C,    // ( 65 -  96) |  0000 0000 0000 0001 0000 0000 0000 1100
                 0x00000800};   // ( 97 - 128) |  0000 0000 0000 0000 0000 1000 0000 0000

int main()
{
    printf("\nEjemplo 1:\n");
    print_seats(example1);

    printf("\n\nEjemplo 2:\n");
    print_seats(example2);

    return 0;
}