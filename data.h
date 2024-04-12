#ifndef DATA_H_
#define DATA_H_

typedef struct c_data *data;

data nuovo_data();
int modifica_data(data, long unsigned);
char cmp_data(data, data);
char *stringa_data(data);
data copia_data(data);
void free_data(data);

#endif // DATA_H_
