#ifndef DATA_H_
#define DATA_H_

typedef struct DataStruct *Data;

Data nuovo_data();
int modifica_data(Data, long unsigned);
char cmp_data(Data, Data);
char *stringa_data(Data);
Data copia_data(Data);
void free_data(Data);

#endif // DATA_H_
