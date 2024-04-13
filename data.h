#ifndef DATA_H_
#define DATA_H_

typedef struct DataStruct *Data;
typedef const struct DataStruct *ConstData;

Data nuovo_data(void);
int modifica_data(Data, long unsigned);
char cmp_data(ConstData, ConstData);
char *stringa_data(ConstData);
Data copia_data(ConstData);
void free_data(Data);

#endif // DATA_H_
