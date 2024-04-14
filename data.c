#include "data.h"
#include "logging.h"
#include <stdio.h>
#include <stdlib.h>
#define MONTHS 12
#define MONTH_DAYS_INITIALIZER                                                 \
  { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 }

#define MONTH_NAMES_INITIALIZER                                                \
  {                                                                            \
    "Gennaio", "Febbraio", "Marzo", "Aprile", "Maggio", "Giugno", "Luglio",    \
        "Agosto", "Settembre", "Ottobre", "Novembre", "Dicembre"               \
  }
typedef enum {
  GENNAIO = 1,
  FEBBRAIO,
  MARZO,
  APRILE,
  MAGGIO,
  GIUGNO,
  LUGLIO,
  AGOSTO,
  SETTEMBRE,
  OTTOBRE,
  NOVEMBRE,
  DICEMBRE
} NOMI_MESI;

struct DataStruct {
  unsigned char minuti;
  unsigned char ora;
  unsigned char giorno;
  unsigned char mese;
  unsigned short anno;
};

static int const months[] = MONTH_DAYS_INITIALIZER;
static const char *const month_names[] = MONTH_NAMES_INITIALIZER;

static const char *get_month_name(ConstData data) {
  return month_names[data->mese - 1];
}

Data new_data(unsigned char minuti, unsigned char ora, unsigned char giorno,
              unsigned char mese, unsigned short anno) {
  Data data = malloc(sizeof(*data));
  if (data == NULL) {
    log_error("Allocazione oggetto 'Data' fallita.");
    return NULL;
  }
  data->minuti = minuti;
  data->ora = ora;
  data->giorno = giorno;
  data->mese = mese;
  data->anno = anno;

  if (!is_valid_data(data)) {
    log_error("Tentativo di creazione data non valida");
    free(data);
    return NULL;
  }
  return data;
}

static int cmp_number(unsigned int a, unsigned int b) {
  if (a < b) {
    return -1;
  }
  if (a == b) {
    return 0;
  }
  return 1;
}

int cmp_data(ConstData data_a, ConstData data_b) {
  // Compare 'anno'
  int result = cmp_number(data_a->anno, data_b->anno);
  if (result != 0) {
    return result;
  }
  // Compare 'mese'
  result = cmp_number(data_a->mese, data_b->mese);
  if (result != 0) {
    return result;
  }

  // Compare 'giorno'
  result = cmp_number(data_a->giorno, data_b->giorno);
  if (result != 0) {
    return result;
  }

  // Compare 'ora'
  result = cmp_number(data_a->ora, data_b->ora);
  if (result != 0) {
    return result;
  }

  // Compare 'minuti'
  return cmp_number(data_a->minuti, data_b->minuti);
}

#define FORMATO_DATA "%d %s %d, %02d:%02d"
char *to_string_data(ConstData data) {
  int len = snprintf(NULL, 0, FORMATO_DATA, data->giorno, get_month_name(data),
                     data->anno, data->ora, data->minuti);
  char *str_res = calloc(len + 1, sizeof(char));
  if (str_res == NULL) {
    log_error(
        "Allocazione oggetto 'str_res' in funzione 'to_string_data' fallita.");
    return NULL;
  }
  if (snprintf(str_res, len + 1, FORMATO_DATA, data->giorno,
               get_month_name(data), data->anno, data->ora, data->minuti) < 0) {
    log_error("Creazione 'stringa data' in funzione 'to_string_data' fallita.");
    free(str_res);
    return NULL;
  }
  return str_res;
}

Data copy_data(ConstData data) {
  if (data == NULL) {
    return NULL;
  }
  return new_data(data->minuti, data->ora, data->giorno, data->mese,
                  data->anno);
}

static void copia_interna(Data dest, ConstData src) {
  dest->minuti = src->minuti;
  dest->ora = src->ora;
  dest->giorno = src->giorno;
  dest->mese = src->mese;
  dest->anno = src->anno;
}

#define LEAP_CHECK(A) (((A) % 4) == 0 && ((A) % 100) != 0) || ((A) % 400) == 0
int is_leap(ConstData data) {
  if (data == NULL) {
    log_error("L'oggetto 'data' passato come parametro alla funzione 'is_leap' "
              "non risulta alloato");
    return -1;
  }

  return LEAP_CHECK(data->anno);
}

#define MINUTES_IN_HOUR 60
#define HOURS_IN_DAY 24
int is_valid_data(ConstData data) {
  if (data->minuti >= MINUTES_IN_HOUR) {
    return 0;
  }
  if (data->ora >= HOURS_IN_DAY) {
    return 0;
  }
  if (data->giorno == 0 || data->mese == 0) {
    return 0;
  }
  if (is_leap(data) && data->mese == FEBBRAIO) {
    return data->giorno <= (months[data->mese - 1] + 1);
  }
  return data->mese <= MONTHS && data->giorno <= months[data->mese - 1];
}

int get_ora(ConstData data) {
  if (data == NULL) {
    log_error("Passato puntatore NULL alla funzione 'get_ora'.");
    return -1;
  }
  return data->ora;
}

int get_minuti(ConstData data) {
  if (data == NULL) {
    log_error("Passato puntatore NULL alla funzione 'get_minuti'.");
    return -1;
  }
  return data->minuti;
}

int get_giorno(ConstData data) {
  if (data == NULL) {
    log_error("Passato puntatore NULL alla funzione 'get_giorno'.");
    return -1;
  }
  return data->giorno;
}

int get_mese(ConstData data) {
  if (data == NULL) {
    log_error("Passato puntatore NULL alla funzione 'get_mese'.");
    return -1;
  }
  return data->mese;
}

int get_anno(ConstData data) {
  if (data == NULL) {
    log_error("Passato puntatore NULL alla funzione 'get_anno'.");
    return -1;
  }
  return data->anno;
}

void free_data(Data data) { free(data); }
