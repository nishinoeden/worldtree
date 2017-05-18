#include <stdio.h>

typedef struct device device_t;

typedef struct worker worker_t;

worker_t *ws_wtd_new();
void *ws_wtd_start( worker_t *worker );
void *ws_wtd_exec( void *wtd );
void *ws_wtd_listen( worker_t *worker );
void *ws_print_header();
