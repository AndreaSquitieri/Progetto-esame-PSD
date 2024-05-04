#include "conference.h"
#include "event_bst.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 102

struct ConferenceStruct {
  EventBst bst;
};

Conference new_conference(void) {
  EventBst bst = new_event_bst();
  if (bst == NULL_EVENT_BST) {
    return NULL_CONFERENCE;
  }
  Conference conf = calloc(1, sizeof(*conf));
  if (conf == NULL) {
    free_event_bst(bst);
    return NULL_CONFERENCE;
  }
  conf->bst = bst;
  return conf;
}

int add_conference_event(Conference conf) {
  Event event = read_event();
  if (event == NULL_EVENT) {
    return -1;
  }
  bst_insert_event(conf->bst, event);
  return 0;
}

static int conference_select_event(Conference conf, const char *to_print) {
  print_event_bst(conf->bst);
  ResultInt res;
  while (1) {
    printf("%s", to_print);
    res = read_int();
    if (res.error_code) {
      printf("Valore inserito non valido\n");
      continue;
    }
    break;
  }
  return res.value;
}

int remove_conference_event(Conference conf) {
  int res = conference_select_event(
      conf, "Inserisci l'id dell'evento da rimuovere [inserire un numero "
            "negativo "
            "per annullare l'operazione]: ");
  if (res < 0) {
    return 1; // Action aborted by the user
  }
  Event removed = bst_remove_event_by_id(conf->bst, res);
  if (removed == NULL_EVENT) {
    puts("Qualcosa è andato storto durante la rimozione dell'evento");
    return -1;
  }
  free_event(removed);
  printf("Evento correttamente rimosso\n");
  return 0;
}

static int edit_conference_event_title(Conference conf, Event to_edit) {
  char temp[MAXSIZE];
  printf("Inserisci nome evento [Max 100 caratteri]: ");
  if (read_line(temp, sizeof(temp))) {
    puts("Nome inserito non valido");
    return -1;
  }
  if (set_event_name(to_edit, temp)) {
    puts("Qualcosa è andato storto durante l'inserimento del nome dell'evento");
    return -1;
  }
  return 0;
}

static int edit_conference_event_type(Conference conf, Event to_edit) {
  int type = -1;
  while (!is_valid_event_type(type)) {
    printf(EVENT_TYPE_MENU);
    ResultInt res = read_int();
    if (res.error_code || res.value < 1 || res.value > 3) {
      puts("Valore inserito non valido");
      continue;
    }
    type = res.value - 1;
    break;
  }
  if (set_event_type(to_edit, type)) {
    puts("Qualcosa è andato storto durante l'inserimento del tipo dell'evento");
    return -1;
  }
  return 0;
}

static int edit_conference_event_date(Conference conf, Event to_edit) {
  Date date = NULL_DATE;
  do {
    printf("Inserisci data evento (DD/MM/AAAA hh:mm): ");
    date = read_date();
  } while (date == NULL_DATE && printf("Data inserita non valida\n"));
  return set_event_date(to_edit, date);
}

#define EDIT_MENU                                                              \
  "[1] Nome\n"                                                                 \
  "[2] Tipo\n"                                                                 \
  "[3] Data\n"                                                                 \
  "[4] Esci\n"                                                                 \
  "Selezionare cosa si desidera modificare: "

typedef enum {
  EDIT_EVENT_TITLE = 1,
  EDIT_EVENT_TYPE,
  EDIT_EVENT_DATE,
  EDIT_EVENT_EXIT
} EditMenuChoice;

int edit_conference_event(Conference conf) {
  int res = conference_select_event(
      conf, "Inserisci l'id dell'evento da modificare [inserire un numero "
            "negativo "
            "per annullare l'operazione]: ");
  if (res < 0) {
    return 1; // Action aborted by the user
  }
  Event to_edit = bst_remove_event_by_id(conf->bst, res);
  if (to_edit == NULL_EVENT) {
    printf("Qualcosa è andato storto durante la ricerca dell'evento\n");
    return -1;
  }
  int flag = 1;
  while (flag) {
    printf(EDIT_MENU);
    ResultInt res = read_int();
    if (res.error_code || res.value < 1 || res.value > 4) {
      puts("Valore inserito non valido");
      continue;
    }
    switch ((EditMenuChoice)res.value) {
    case EDIT_EVENT_TITLE: {
      edit_conference_event_title(conf, to_edit);
    } break;
    case EDIT_EVENT_TYPE: {
      edit_conference_event_type(conf, to_edit);
    } break;
    case EDIT_EVENT_DATE: {
      edit_conference_event_date(conf, to_edit);
    } break;
    case EDIT_EVENT_EXIT:
      flag = 0;
      break;
    }
    if (flag) {
      printf("\n\n");
      print_event(to_edit);
      printf("\n\n");
    }
  }
  if (bst_insert_event(conf->bst, to_edit)) {
    free_event(to_edit);
    puts("Qualcosa è andato storto durante la modifica dell'evento");
    return -1;
  }
  puts("Evento correttamente modificato");
  return 0;
}

int display_conference_schedule(ConstConference conf) {
  print_event_bst(conf->bst);
  return 0;
}

void free_conference(Conference conf) {
  free_event_bst(conf->bst);
  free(conf);
}