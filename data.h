#ifndef DATA_H_
#define DATA_H_

typedef struct DataStruct *Data;
typedef const struct DataStruct *ConstData;

Data new_data(unsigned char minuti, unsigned char ora, unsigned char giorno,
              unsigned char mese, unsigned int anno);
int is_valid_data(ConstData data);
int is_leap(ConstData data);
int cmp_data(ConstData data_a, ConstData data_b);
char *to_string_data(ConstData);
Data copy_data(ConstData);
void free_data(Data);

#endif // DATA_H_
