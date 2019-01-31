/*
 ============================================================================
 Name        : function_hdu.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

// XXX: http://acm.hdu.edu.cn/showproblem.php?pid=5608
#if 1
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <assert.h>
#include <stddef.h>
#ifndef ONLINE_JUDGE
#include <unistd.h>
#include <sys/time.h>
#endif
#include <math.h>
#include <stdint.h>
#include <ctype.h>

#ifdef CACA_COMUN_LOG
#include <execinfo.h>
#endif

#ifdef __MACH__
#include <mach/clock.h>
#include <mach/mach.h>
#else
#include <time.h>
#include <stdarg.h>
#endif

#if 1
#ifndef LONG_LONG_MAX
#define LONG_LONG_MAX LONG_MAX
#endif

#ifndef ULONG_LONG_MAX
#define ULONG_LONG_MAX ULONG_MAX
#endif

#define CACA_COMUN_TAM_MAX_LINEA (16*200000)
#define CACA_LOG_MAX_TAM_CADENA 2000

#define CACA_COMUN_BUF_STATICO_TAM 1000
#define CACA_COMUN_BUF_STATICO (char[CACA_COMUN_BUF_STATICO_TAM] ) { '\0' }

#define BITCH_VECTOR_NUM_BITS (sizeof(bitch_vector) * 8)

#define CACA_COMUN_ASSERT_DUROTE 0
#define CACA_COMUN_ASSERT_SUAVECITO 1
#define CACA_COMUN_ASSERT_NIMADRES 2

#define CACA_COMUN_VALOR_INVALIDO ((tipo_dato)UINT_MAX)
#define CACA_COMUN_IDX_INVALIDO ((natural)CACA_COMUN_VALOR_INVALIDO)
#define CACA_COMUN_FUNC_STATICA static

typedef char byteme;
typedef unsigned int natural;
typedef natural tipo_dato;
typedef long long entero_largo;
typedef unsigned long long entero_largo_sin_signo;
typedef long long bitch_vector;

typedef enum BOOLEANOS {
	falso = 0, verdadero
} bool;

/*
 #define CACA_COMUN_TIPO_ASSERT CACA_COMUN_ASSERT_SUAVECITO
 #define CACA_COMUN_TIPO_ASSERT CACA_COMUN_ASSERT_NIMADRES
 */
#define CACA_COMUN_TIPO_ASSERT CACA_COMUN_ASSERT_DUROTE

#define assert_timeout_dummy(condition) 0;

#if CACA_COMUN_TIPO_ASSERT == CACA_COMUN_ASSERT_DUROTE
#define assert_timeout(condition) assert(condition);
#endif
#if CACA_COMUN_TIPO_ASSERT == CACA_COMUN_ASSERT_SUAVECITO
#define assert_timeout(condition) if(!(condition)){while(1){printf("");};abort();}
#endif
#if CACA_COMUN_TIPO_ASSERT == CACA_COMUN_ASSERT_NIMADRES
#define assert_timeout(condition) 0
#endif

#ifdef CACA_COMUN_LOG
#define caca_log_debug(formato, args...) \
		do \
		{ \
			size_t profundidad = 0; \
			void *array[CACA_LOG_MAX_TAM_CADENA]; \
 			profundidad = backtrace(array, CACA_LOG_MAX_TAM_CADENA); \
			caca_log_debug_func(formato,__FILE__, __func__, __LINE__,profundidad,##args); \
		} \
		while(0);
#else
#define caca_log_debug(formato, args...) 0;
#endif

#define caca_comun_max(x,y) ((x) < (y) ? (y) : (x))
#define caca_comun_min(x,y) ((x) < (y) ? (x) : (y))

#define caca_comun_calloc_local(tipo) (&(tipo){0})

void caca_log_debug_func(const char *format, ...);

#ifndef ONLINE_JUDGE
CACA_COMUN_FUNC_STATICA void caca_comun_current_utc_time(struct timespec *ts) {

#ifdef __MACH__
	clock_serv_t cclock;
	mach_timespec_t mts;
	host_get_clock_service(mach_host_self(), CALENDAR_CLOCK, &cclock);
	clock_get_time(cclock, &mts);
	mach_port_deallocate(mach_task_self(), cclock);
	ts->tv_sec = mts.tv_sec;
	ts->tv_nsec = mts.tv_nsec;
#else
#ifdef CACA_COMUN_LOG
	clock_gettime(CLOCK_REALTIME, ts);
#endif
#endif

}

CACA_COMUN_FUNC_STATICA void caca_comun_timestamp(char *stime) {
	time_t ltime;
	long ms;
#ifndef ONLINE_JUDGE
	struct tm result;
	struct timespec spec;
#endif
	char parte_milisecundos[50];

	ltime = time(NULL);

#ifndef ONLINE_JUDGE
	localtime_r(&ltime, &result);
	asctime_r(&result, stime);
#endif

	*(stime + strlen(stime) - 1) = ' ';

#ifndef ONLINE_JUDGE
	caca_comun_current_utc_time(&spec);
	ms = round(spec.tv_nsec / 1.0e3);
#endif
	sprintf(parte_milisecundos, "%ld", ms);
	strcat(stime, parte_milisecundos);
}

#endif
#ifdef CACA_COMUN_LOG
void caca_log_debug_func(const char *format, ...) {

	va_list arg;
	va_list arg2;
	const char *PEDAZO_TIMESTAMP_HEADER = "tiempo: %s; ";
	const char *HEADER =
	"archivo: %s; funcion: %s; linea %d; nivel: %zd caca 8====D ";
	char formato[CACA_LOG_MAX_TAM_CADENA + sizeof(HEADER)
	+ sizeof(PEDAZO_TIMESTAMP_HEADER)] = {'\0'};
	char pedazo_timestamp[sizeof(PEDAZO_TIMESTAMP_HEADER) + 100] = {'\0'};
	char cadena_timestamp[100] = {'\0'};

	caca_comun_timestamp(cadena_timestamp);
	sprintf(pedazo_timestamp, PEDAZO_TIMESTAMP_HEADER, cadena_timestamp);

	strcpy(formato, pedazo_timestamp);
	strcat(formato, HEADER);
	strcat(formato, format);
	strcat(formato, "\n");

	va_start(arg, format);
	va_copy(arg2, arg);
	vprintf(formato, arg2);
	va_end(arg2);
	va_end(arg);
	setbuf(stdout, NULL);
}
#endif

#ifdef CACA_COMUN_LOG
CACA_COMUN_FUNC_STATICA char *caca_comun_arreglo_a_cadena(tipo_dato *arreglo, natural tam_arreglo,
		char *buffer) {
	int i;
	char *ap_buffer = NULL;
	int characteres_escritos = 0;
#ifdef ONLINE_JUDGE
	return NULL;
#endif

	memset(buffer, 0, 100);
	ap_buffer = buffer;

	for (i = 0; i < tam_arreglo; i++) {
		characteres_escritos += sprintf(ap_buffer + characteres_escritos,
				"%1d", *(arreglo + i));
		if (i < tam_arreglo - 1) {
			*(ap_buffer + characteres_escritos++) = ',';
		}
	}
	*(ap_buffer + characteres_escritos) = '\0';
	return ap_buffer;
}

CACA_COMUN_FUNC_STATICA char *caca_comun_arreglo_a_cadena_natural(natural *arreglo,
		natural tam_arreglo, char *buffer) {
	int i;
	char *ap_buffer = NULL;
	int characteres_escritos = 0;
#ifdef ONLINE_JUDGE
	return NULL;
#endif

	memset(buffer, 0, 100);
	ap_buffer = buffer;

	for (i = 0; i < tam_arreglo; i++) {
		characteres_escritos += sprintf(ap_buffer + characteres_escritos, "%2u",
				*(arreglo + i));
		if (i < tam_arreglo - 1) {
			*(ap_buffer + characteres_escritos++) = ',';
		}
	}
	*(ap_buffer + characteres_escritos) = '\0';
	return ap_buffer;
}
char *caca_comun_matrix_a_cadena(tipo_dato *matrix, natural filas_tam,
		natural columas_tam, char *buffer) {
	int i, j;
	natural inicio_buffer_act = 0;
	for (i = 0; i < filas_tam; i++) {
		caca_comun_arreglo_a_cadena(matrix + i * columas_tam, columas_tam,
				buffer + inicio_buffer_act);
		inicio_buffer_act += strlen(buffer + inicio_buffer_act);
		buffer[inicio_buffer_act++] = '\n';
		/*		caca_log_debug("pero q mierda inicio buffer act %u %s",inicio_buffer_act,buffer);*/
	}
	return buffer;
}

CACA_COMUN_FUNC_STATICA char *caca_comun_arreglo_a_cadena_entero_largo_sin_signo(
		entero_largo_sin_signo *arreglo, entero_largo_sin_signo tam_arreglo,
		char *buffer) {
	int i;
	char *ap_buffer = NULL;
	int characteres_escritos = 0;
#ifdef ONLINE_JUDGE
	return NULL;
#endif

	memset(buffer, 0, 100);
	ap_buffer = buffer;

	for (i = 0; i < tam_arreglo; i++) {
		characteres_escritos += sprintf(ap_buffer + characteres_escritos,
				"%llu", *(arreglo + i));
		if (i < tam_arreglo - 1) {
			*(ap_buffer + characteres_escritos++) = ',';
		}
	}
	*(ap_buffer + characteres_escritos) = '\0';
	return ap_buffer;
}
#else
CACA_COMUN_FUNC_STATICA char *caca_comun_arreglo_a_cadena(tipo_dato *arreglo,
		natural tam_arreglo, char *buffer) {
	return NULL;
}
CACA_COMUN_FUNC_STATICA char *caca_comun_arreglo_a_cadena_natural(
		natural *arreglo, natural tam_arreglo, char *buffer) {
	return NULL;
}
char *caca_comun_matrix_a_cadena(tipo_dato *matrix, natural filas_tam,
		natural columas_tam, char *buffer) {
	return NULL;
}

CACA_COMUN_FUNC_STATICA char *caca_comun_arreglo_a_cadena_entero_largo_sin_signo(
		entero_largo_sin_signo *arreglo, entero_largo_sin_signo tam_arreglo,
		char *buffer) {
	return NULL;
}
#endif

#define caca_comun_arreglo_a_cadena_entero_largo_sin_signo_buf_local(a,a_tam) caca_comun_arreglo_a_cadena_entero_largo_sin_signo(a,a_tam,CACA_COMUN_BUF_STATICO)
#define caca_comun_arreglo_a_cadena_buf_local(a,a_tam) caca_comun_arreglo_a_cadena(a,a_tam,CACA_COMUN_BUF_STATICO)
#define caca_comun_arreglo_a_cadena_natural_buf_local(a,a_tam) caca_comun_arreglo_a_cadena_natural(a,a_tam,CACA_COMUN_BUF_STATICO)

CACA_COMUN_FUNC_STATICA void caca_comun_strreplace(char s[], char chr,
		char repl_chr) {
	int i = 0;
	while (s[i] != '\0') {
		if (s[i] == chr) {
			s[i] = repl_chr;
		}
		i++;
	}
}

CACA_COMUN_FUNC_STATICA int caca_comun_lee_matrix_long_stdin(tipo_dato *matrix,
		int *num_filas, int *num_columnas, int num_max_filas,
		int num_max_columnas) {
	int indice_filas = 0;
	int indice_columnas = 0;
	tipo_dato numero = 0;
	char *siguiente_cadena_numero = NULL;
	char *cadena_numero_actual = NULL;
	char *linea = NULL;

	linea = calloc(CACA_COMUN_TAM_MAX_LINEA, sizeof(char));

	while (indice_filas < num_max_filas
			&& fgets(linea, CACA_COMUN_TAM_MAX_LINEA, stdin)) {
		indice_columnas = 0;
		cadena_numero_actual = linea;
		caca_comun_strreplace(linea, '\n', '\0');
		if (!strlen(linea)) {
			caca_log_debug("weird, linea vacia");
			continue;
		}
		for (siguiente_cadena_numero = linea;; siguiente_cadena_numero =
				cadena_numero_actual) {
			numero = strtol(siguiente_cadena_numero, &cadena_numero_actual, 10);
			if (cadena_numero_actual == siguiente_cadena_numero) {
				break;
			}
			*(matrix + indice_filas * num_max_columnas + indice_columnas) =
					numero;
			indice_columnas++;
		}
		if (num_columnas) {
			num_columnas[indice_filas] = indice_columnas;
		}
		indice_filas++;
		caca_log_debug("las filas son %d, con clos %d", indice_filas,
				indice_columnas);
	}

	*num_filas = indice_filas;
	free(linea);
	return 0;
}

CACA_COMUN_FUNC_STATICA natural caca_comun_cuenta_bitchs(tipo_dato num) {
	natural bitch_cnt = 0;
	tipo_dato num_mod = 0;
	num_mod = num;
	while (num_mod) {
		num_mod &= ~(num_mod & (-num_mod));
		bitch_cnt++;
	}
	return bitch_cnt;
}

CACA_COMUN_FUNC_STATICA char caca_comun_letra_a_valor_minuscula(char letra) {
	return letra - 'a';
}

CACA_COMUN_FUNC_STATICA natural caca_comun_max_natural(natural *nums,
		natural nums_tam) {
	natural max = 0;
	int i = 0;

	for (i = 0; i < nums_tam; i++) {
		natural num_act = nums[i];
		if (num_act > max) {
			max = num_act;
		}
	}

	return max;
}

CACA_COMUN_FUNC_STATICA char *caca_comun_trimea(char *cad, natural cad_tam) {
	char c = cad[0];
	char tmp = '\0';
	natural i = 0;
	natural j = 0;

	caca_log_debug("entrada %s cad_tam %u", cad, cad_tam);
	while (j < cad_tam && cad[j] != '\0') {
		caca_log_debug("en j %u car %c", j, cad[j]);
		while (j < cad_tam && !isalpha(cad[j])) {
			caca_log_debug("brincando j %u car %c", j, cad[j]);
			j++;
		}
		caca_log_debug("aora j %u car %c", j, cad[j]);
		if (j == cad_tam) {
			caca_log_debug("q ped");
			break;
		}
		tmp = cad[i];
		cad[i] = cad[j];
		cad[j] = tmp;
		i++;
		j++;
	}
	caca_log_debug("mierda '%c'", cad[j]);

	i = 0;
	while (isalpha(cad[i++]))
		;
	caca_log_debug("salida %s", cad);
	cad[i - 1] = '\0';

	return cad;
}

#endif

#define CACA_COMUN_LIMPIA_MEM(m,s) (memset(m,0,s))
#define CACA_COMUN_LIMPIA_MEM_STATICA(m) (memset(m,0,sizeof(*(m))))

CACA_COMUN_FUNC_STATICA bool caca_comun_es_digito(char c) {
	return c >= '0' && c <= '9';
}

CACA_COMUN_FUNC_STATICA byteme caca_comun_caracter_a_num(char c) {
	return c - '0';
}

CACA_COMUN_FUNC_STATICA void caca_comun_invierte_arreglo_byteme(byteme *a,
		natural a_tam) {
	natural i = 0;
	natural j = a_tam - 1;
	while (i < j) {
		byteme t = a[i];
		a[i] = a[j];
		a[j] = t;
		i++;
		j--;
	}
}

CACA_COMUN_FUNC_STATICA void caca_comun_invierte_arreglo_natural(natural *a,
		natural a_tam) {
	natural i = 0;
	natural j = a_tam - 1;
	while (i < j) {
		natural t = a[i];
		a[i] = a[j];
		a[j] = t;
		i++;
		j--;
	}
}

CACA_COMUN_FUNC_STATICA natural caca_comun_encuentra_minimo_natural(natural *a,
		natural a_tam) {
	natural min = CACA_COMUN_VALOR_INVALIDO;
	natural i;
	for (i = 0; i < a_tam; i++) {
		if (min > a[i]) {
			min = a[i];
		}
	}
	return min;
}

CACA_COMUN_FUNC_STATICA natural caca_comun_mcd(natural a, natural b) {
	natural r = CACA_COMUN_VALOR_INVALIDO;
	while (a && b) {
		natural tmp = b;
		b = a % b;
		a = tmp;
	}

	if (!a) {
		r = b;
	}
	if (!b) {
		r = a;
	}
	return r;
}

#define caca_comun_compara_tipo(tipo) CACA_COMUN_FUNC_STATICA int caca_comun_compara_##tipo(const void *pa, const void *pb) { \
	int r = 0; \
	tipo a = *(tipo *)pa; \
	tipo b = *(tipo *)pb; \
	if (a < b) { \
		r = -1; \
	} else { \
		if (a > b) { \
			r = 1; \
		} \
	} \
	return r; \
}

caca_comun_compara_tipo(natural)

CACA_COMUN_FUNC_STATICA natural caca_comun_encuentra_divisores(natural n,
		natural *divisores, natural divisores_tam) {
	natural divisores_cnt = 0;
	natural i = 0;
	for (i = 1; i * i < n; i++) {
		if (!(n % i)) {
			assert_timeout(divisores_cnt < divisores_tam);
			divisores[divisores_cnt++] = i;
			assert_timeout(divisores_cnt < divisores_tam);
			divisores[divisores_cnt++] = n / i;
		}
	}

	if (i * i == n) {
		assert_timeout(divisores_cnt < divisores_tam);
		divisores[divisores_cnt++] = n / i;
	}
	qsort(divisores, divisores_cnt, sizeof(natural),
			caca_comun_compara_natural);
	return divisores_cnt;
}

#endif

#if 1

#define PRIMOS_NUM_MAX ((int)1E6)
typedef struct primos_datos {
	natural primos_caca_tam;
	natural primos_caca[PRIMOS_NUM_MAX + 1];
	bool primos_caca_es_primo[PRIMOS_NUM_MAX + 1];

} primos_datos;

//#define PRIMOS_NUM_MAX ((int)101)

typedef void (*primos_caca_primo_encontrado_cb)(natural primo,
		natural idx_primo, void *cb_ctx);
typedef void (*primos_caca_compuesto_encontrado_cb)(natural primo,
		natural idx_primo, natural compuesto_origen, void *cb_ctx);

typedef void (*primos_caca_divisible_encontrado_cb)(natural primo,
		natural idx_primo, natural compuesto, void *cb_ctx);

typedef void (*primos_caca_no_divisible_encontrado_cb)(natural primo,
		natural idx_primo, natural compuesto, void *cb_ctx);

CACA_COMUN_FUNC_STATICA natural primos_caca_criba(natural limite,
		primos_caca_primo_encontrado_cb primo_cb,
		primos_caca_compuesto_encontrado_cb compuesto_cb,
		primos_caca_divisible_encontrado_cb divisible_encontrado_cb,
		primos_caca_no_divisible_encontrado_cb no_divisible_encontrado_cb,
		void *cb_ctx, primos_datos *pd) {
	bool *primos_caca_es_primo = pd->primos_caca_es_primo;
	natural *primos_caca = pd->primos_caca;
	caca_log_debug("primos asta %u", limite);
	assert_timeout(limite<=PRIMOS_NUM_MAX);
	natural i, j;
	for (i = 2; i <= limite; i++) {
		primos_caca_es_primo[i] = verdadero;
	}
	for (i = 2; i <= limite; i++) {
		if (primos_caca_es_primo[i]) {
			primos_caca[pd->primos_caca_tam++] = i;
			if (primo_cb) {
				primo_cb(i, pd->primos_caca_tam - 1, cb_ctx);
			}
		}
		for (j = 0; j < pd->primos_caca_tam && primos_caca[j] * i <= limite;
				j++) {
			primos_caca_es_primo[primos_caca[j] * i] = falso;
			if (compuesto_cb) {
				compuesto_cb(primos_caca[j], j, i, cb_ctx);
			}
			if (!(i % primos_caca[j])) {
				if (divisible_encontrado_cb) {
					divisible_encontrado_cb(primos_caca[j], j, i, cb_ctx);
				}
				break;
			} else {
				if (no_divisible_encontrado_cb) {
					no_divisible_encontrado_cb(primos_caca[j], j, i, cb_ctx);
				}
			}
		}
	}
	caca_log_debug("generados %u primos", pd->primos_caca_tam);
	return pd->primos_caca_tam;
}

#endif

#if 1
#define MORBIUS_MAX_MIERDA PRIMOS_NUM_MAX

typedef struct morbius_datos {
	int morbius[MORBIUS_MAX_MIERDA + 1];
} morbius_datos;

void morbius_divisible_encontrado_cb(natural primo, natural idx_primo,
		natural compuesto, void *cb_ctx) {
	morbius_datos *g = cb_ctx;

	g->morbius[compuesto * primo] = 0;
	caca_log_debug("divisible %u %d", compuesto*primo,
			g->morbius[compuesto*primo]);
}
void morbius_no_divisible_encontrado_cb(natural primo, natural idx_primo,
		natural compuesto, void *cb_ctx) {
	morbius_datos *g = cb_ctx;

	g->morbius[compuesto * primo] = g->morbius[compuesto] * -1;
	caca_log_debug("indivisible %u de %u %d", compuesto*primo, compuesto,
			g->morbius[compuesto*primo]);
}

void morbius_primo_encontrado_cb(natural primo, natural idx_primo, void *cb_ctx) {
	morbius_datos *g = cb_ctx;
	g->morbius[primo] = -1;
	caca_log_debug("primo enc %u %d", primo, g->morbius[primo]);
}
#endif

#if 1

#define BITCH_VALOR_INVALIDO CACA_COMUN_VALOR_INVALIDO

typedef struct bitch_vector_ctx {
	natural bitch_numeros_agregados_tam;
	bitch_vector *bitch_mapa;
} bitch_vector_ctx;

CACA_COMUN_FUNC_STATICA bitch_vector_ctx *bitch_init(natural max_nums) {
	bitch_vector_ctx *bvctx = NULL;
	bvctx = calloc(1, sizeof(bitch_vector_ctx));
	bvctx->bitch_mapa = calloc(((max_nums / (sizeof(bitch_vector) * 8)) + 1),
			sizeof(bitch_vector));
	assert_timeout(bvctx->bitch_mapa);
	return bvctx;
}

CACA_COMUN_FUNC_STATICA bool bitch_checa(bitch_vector_ctx *bvctx,
		entero_largo_sin_signo posicion) {
	entero_largo_sin_signo resultado = 0;
	natural idx_arreglo = 0;
	natural idx_registro = 0;

	idx_arreglo = posicion / 64;
	idx_registro = posicion % 64;

	resultado = bvctx->bitch_mapa[idx_arreglo]
			& (bitch_vector) ((bitch_vector) 1 << idx_registro);

	return !!resultado;
}

CACA_COMUN_FUNC_STATICA void bitch_asigna(bitch_vector_ctx *bvctx,
		entero_largo_sin_signo posicion) {
	natural idx_arreglo = 0;
	natural idx_registro = 0;

	idx_arreglo = posicion / 64;
	idx_registro = posicion % 64;

	bvctx->bitch_mapa[idx_arreglo] |= (bitch_vector) ((bitch_vector) 1
			<< idx_registro);
	bvctx->bitch_numeros_agregados_tam++;

}

CACA_COMUN_FUNC_STATICA void bitch_limpia(bitch_vector_ctx *bvctx,
		entero_largo_sin_signo posicion) {
	int idx_arreglo = 0;
	int idx_registro = 0;
	bitch_vector *bits = bvctx->bitch_mapa;

	idx_arreglo = posicion / 64;
	idx_registro = posicion % 64;

	bits[idx_arreglo] &= (bitch_vector) ~((bitch_vector) 1 << idx_registro);

	bvctx->bitch_numeros_agregados_tam--;
}

CACA_COMUN_FUNC_STATICA void bitch_fini(bitch_vector_ctx *bvctx) {
	free(bvctx->bitch_mapa);
	free(bvctx);
}

#endif

#if 1

#if 1

#define XXH_PUBLIC_API static inline
#define FORCE_INLINE static inline
#define XXH_FORCE_NATIVE_FORMAT 0

#define XXH_rotl32(x,r) ((x << r) | (x >> (32 - r)))
#define XXH_rotl64(x,r) ((x << r) | (x >> (64 - r)))

typedef uint64_t U64;
typedef uint8_t BYTE;
typedef uint16_t U16;
typedef uint32_t U32;

static const U64 PRIME64_1 = 11400714785074694791ULL;
static const U64 PRIME64_2 = 14029467366897019727ULL;
static const U64 PRIME64_3 = 1609587929392839161ULL;
static const U64 PRIME64_4 = 9650029242287828579ULL;
static const U64 PRIME64_5 = 2870177450012600261ULL;

typedef enum {
	XXH_OK = 0, XXH_ERROR
} XXH_errorcode;

typedef enum {
	XXH_bigEndian = 0, XXH_littleEndian = 1
} XXH_endianess;

typedef struct XXH64_state_s {
	uint64_t total_len;
	uint64_t v1;
	uint64_t v2;
	uint64_t v3;
	uint64_t v4;
	uint64_t mem64[4];
	uint32_t memsize;
	uint32_t reserved[2]; /* never read nor write, might be removed in a future version */
} XXH64_state_t;
/* typedef'd to XXH64_state_t */

typedef enum {
	XXH_aligned, XXH_unaligned
} XXH_alignment;

static int XXH_isLittleEndian(void) {
	const union {
		U32 u;
		BYTE c[4];
	} one = { 1 }; /* don't use static : performance detrimental  */
	return one.c[0];
}
#define XXH_CPU_LITTLE_ENDIAN   XXH_isLittleEndian()

static U64 XXH64_round(U64 acc, U64 input) {
	acc += input * PRIME64_2;
	acc = XXH_rotl64(acc, 31);
	acc *= PRIME64_1;
	return acc;
}

static U64 XXH_read64(const void* memPtr) {
	U64 val;
	memcpy(&val, memPtr, sizeof(val));
	return val;
}

static U64 XXH_swap64(U64 x) {
	return ((x << 56) & 0xff00000000000000ULL)
			| ((x << 40) & 0x00ff000000000000ULL)
			| ((x << 24) & 0x0000ff0000000000ULL)
			| ((x << 8) & 0x000000ff00000000ULL)
			| ((x >> 8) & 0x00000000ff000000ULL)
			| ((x >> 24) & 0x0000000000ff0000ULL)
			| ((x >> 40) & 0x000000000000ff00ULL)
			| ((x >> 56) & 0x00000000000000ffULL);
}

FORCE_INLINE U64 XXH_readLE64_align(const void* ptr, XXH_endianess endian,
		XXH_alignment align) {
	if (align == XXH_unaligned)
		return endian == XXH_littleEndian ?
				XXH_read64(ptr) : XXH_swap64(XXH_read64(ptr));
	else
		return endian == XXH_littleEndian ?
				*(const U64*) ptr : XXH_swap64(*(const U64*) ptr);
}

static U64 XXH64_mergeRound(U64 acc, U64 val) {
	val = XXH64_round(0, val);
	acc ^= val;
	acc = acc * PRIME64_1 + PRIME64_4;
	return acc;
}

static U32 XXH_read32(const void* memPtr) {
	U32 val;
	memcpy(&val, memPtr, sizeof(val));
	return val;
}

static U32 XXH_swap32(U32 x) {
	return ((x << 24) & 0xff000000) | ((x << 8) & 0x00ff0000)
			| ((x >> 8) & 0x0000ff00) | ((x >> 24) & 0x000000ff);
}

FORCE_INLINE U32 XXH_readLE32_align(const void* ptr, XXH_endianess endian,
		XXH_alignment align) {
	if (align == XXH_unaligned)
		return endian == XXH_littleEndian ?
				XXH_read32(ptr) : XXH_swap32(XXH_read32(ptr));
	else
		return endian == XXH_littleEndian ?
				*(const U32*) ptr : XXH_swap32(*(const U32*) ptr);
}

#define XXH_get32bits(p) XXH_readLE32_align(p, endian, align)

#define XXH_get64bits(p) XXH_readLE64_align(p, endian, align)

static U64 XXH64_avalanche(U64 h64) {
	h64 ^= h64 >> 33;
	h64 *= PRIME64_2;
	h64 ^= h64 >> 29;
	h64 *= PRIME64_3;
	h64 ^= h64 >> 32;
	return h64;
}

static U64 XXH64_finalize(U64 h64, const void* ptr, size_t len,
		XXH_endianess endian, XXH_alignment align) {
	const BYTE* p = (const BYTE*) ptr;

#define PROCESS1_64          \
    h64 ^= (*p) * PRIME64_5; \
    p++;                     \
    h64 = XXH_rotl64(h64, 11) * PRIME64_1;

#define PROCESS4_64          \
    h64 ^= (U64)(XXH_get32bits(p)) * PRIME64_1; \
    p+=4;                    \
    h64 = XXH_rotl64(h64, 23) * PRIME64_2 + PRIME64_3;

#define PROCESS8_64 {        \
    U64 const k1 = XXH64_round(0, XXH_get64bits(p)); \
    p+=8;                    \
    h64 ^= k1;               \
    h64  = XXH_rotl64(h64,27) * PRIME64_1 + PRIME64_4; \
}

	switch (len & 31) {
	case 24:
		PROCESS8_64
		;
		/* fallthrough */
	case 16:
		PROCESS8_64
		;
		/* fallthrough */
	case 8:
		PROCESS8_64
		;
		return XXH64_avalanche(h64);

	case 28:
		PROCESS8_64
		;
		/* fallthrough */
	case 20:
		PROCESS8_64
		;
		/* fallthrough */
	case 12:
		PROCESS8_64
		;
		/* fallthrough */
	case 4:
		PROCESS4_64
		;
		return XXH64_avalanche(h64);

	case 25:
		PROCESS8_64
		;
		/* fallthrough */
	case 17:
		PROCESS8_64
		;
		/* fallthrough */
	case 9:
		PROCESS8_64
		;
		PROCESS1_64
		;
		return XXH64_avalanche(h64);

	case 29:
		PROCESS8_64
		;
		/* fallthrough */
	case 21:
		PROCESS8_64
		;
		/* fallthrough */
	case 13:
		PROCESS8_64
		;
		/* fallthrough */
	case 5:
		PROCESS4_64
		;
		PROCESS1_64
		;
		return XXH64_avalanche(h64);

	case 26:
		PROCESS8_64
		;
		/* fallthrough */
	case 18:
		PROCESS8_64
		;
		/* fallthrough */
	case 10:
		PROCESS8_64
		;
		PROCESS1_64
		;
		PROCESS1_64
		;
		return XXH64_avalanche(h64);

	case 30:
		PROCESS8_64
		;
		/* fallthrough */
	case 22:
		PROCESS8_64
		;
		/* fallthrough */
	case 14:
		PROCESS8_64
		;
		/* fallthrough */
	case 6:
		PROCESS4_64
		;
		PROCESS1_64
		;
		PROCESS1_64
		;
		return XXH64_avalanche(h64);

	case 27:
		PROCESS8_64
		;
		/* fallthrough */
	case 19:
		PROCESS8_64
		;
		/* fallthrough */
	case 11:
		PROCESS8_64
		;
		PROCESS1_64
		;
		PROCESS1_64
		;
		PROCESS1_64
		;
		return XXH64_avalanche(h64);

	case 31:
		PROCESS8_64
		;
		/* fallthrough */
	case 23:
		PROCESS8_64
		;
		/* fallthrough */
	case 15:
		PROCESS8_64
		;
		/* fallthrough */
	case 7:
		PROCESS4_64
		;
		/* fallthrough */
	case 3:
		PROCESS1_64
		;
		/* fallthrough */
	case 2:
		PROCESS1_64
		;
		/* fallthrough */
	case 1:
		PROCESS1_64
		;
		/* fallthrough */
	case 0:
		return XXH64_avalanche(h64);
	}

	/* impossible to reach */
	assert(0);
	return 0; /* unreachable, but some compilers complain without it */
}

FORCE_INLINE U64 XXH64_endian_align(const void* input, size_t len, U64 seed,
		XXH_endianess endian, XXH_alignment align) {
	const BYTE* p = (const BYTE*) input;
	const BYTE* bEnd = p + len;
	U64 h64;

	if (len >= 32) {
		const BYTE* const limit = bEnd - 32;
		U64 v1 = seed + PRIME64_1 + PRIME64_2;
		U64 v2 = seed + PRIME64_2;
		U64 v3 = seed + 0;
		U64 v4 = seed - PRIME64_1;

		do {
			v1 = XXH64_round(v1, XXH_get64bits(p));
			p += 8;
			v2 = XXH64_round(v2, XXH_get64bits(p));
			p += 8;
			v3 = XXH64_round(v3, XXH_get64bits(p));
			p += 8;
			v4 = XXH64_round(v4, XXH_get64bits(p));
			p += 8;
		} while (p <= limit);

		h64 =
				XXH_rotl64(v1,
						1) + XXH_rotl64(v2, 7) + XXH_rotl64(v3, 12) + XXH_rotl64(v4, 18);
		h64 = XXH64_mergeRound(h64, v1);
		h64 = XXH64_mergeRound(h64, v2);
		h64 = XXH64_mergeRound(h64, v3);
		h64 = XXH64_mergeRound(h64, v4);

	} else {
		h64 = seed + PRIME64_5;
	}

	h64 += (U64) len;

	return XXH64_finalize(h64, p, len, endian, align);
}

#define XXH_FORCE_ALIGN_CHECK 0
XXH_PUBLIC_API unsigned long long XXH64(const void* input, size_t len,
		unsigned long long seed) {
#if 0
	/* Simple version, good for code maintenance, but unfortunately slow for small inputs */
	XXH64_state_t state;
	XXH64_reset(&state, seed);
	XXH64_update(&state, input, len);
	return XXH64_digest(&state);
#else
	XXH_endianess endian_detected = (XXH_endianess) XXH_CPU_LITTLE_ENDIAN;

	if (XXH_FORCE_ALIGN_CHECK) {
		if ((((size_t) input) & 7) == 0) { /* Input is aligned, let's leverage the speed advantage */
			if ((endian_detected == XXH_littleEndian) || XXH_FORCE_NATIVE_FORMAT)
				return XXH64_endian_align(input, len, seed, XXH_littleEndian,
						XXH_aligned);
			else
				return XXH64_endian_align(input, len, seed, XXH_bigEndian,
						XXH_aligned);
		}
	}

	if ((endian_detected == XXH_littleEndian) || XXH_FORCE_NATIVE_FORMAT)
		return XXH64_endian_align(input, len, seed, XXH_littleEndian,
				XXH_unaligned);
	else
		return XXH64_endian_align(input, len, seed, XXH_bigEndian,
				XXH_unaligned);
#endif
}

#endif

typedef natural hm_iter;
#define HASH_MAP_VALOR_INVALIDO ((hm_iter)CACA_COMUN_VALOR_INVALIDO)
typedef struct hash_map_entry {
	const void *llave;
	natural llave_tam;
	entero_largo valor;
} hm_entry;
typedef struct hash_map_cubeta {
	uint64_t hash;
	hm_entry *entry;
} hm_cubeta;
typedef struct hash_map_robin_hood_back_shift {
	hm_cubeta *buckets_;
	uint64_t num_buckets_;
	uint64_t num_buckets_used_;
	uint64_t probing_min_;
	uint64_t probing_max_;
} hm_rr_bs_tabla;

static inline entero_largo_sin_signo hash_map_robin_hood_hashear(
		hm_rr_bs_tabla *ht, byteme *mierda, natural mierda_tam) {
	entero_largo_sin_signo ass = 0;

	ass = XXH64(mierda, mierda_tam, ass) % ht->num_buckets_;
	caca_log_debug("%u mapea a %u", *(natural *)mierda, ass);
	return ass;
}

int hash_map_robin_hood_back_shift_init(hm_rr_bs_tabla *ht, int num_cubetas) {
	ht->num_buckets_ = num_cubetas;
	ht->buckets_ = (hm_cubeta *) calloc(ht->num_buckets_, sizeof(hm_cubeta));
	ht->num_buckets_used_ = 0;
	ht->probing_max_ = num_cubetas;
	return 0;
}
int hash_map_robin_hood_back_shift_fini(hm_rr_bs_tabla *ht) {
	uint32_t i = 0;
	i = 0;
	if (ht->buckets_ != NULL) {
		for (i = 0; i < ht->num_buckets_; i++) {
			if (ht->buckets_[i].entry != NULL) {
				free(ht->buckets_[i].entry);
				ht->buckets_[i].entry = NULL;
			}
		}
		free(ht->buckets_);
	}
	return 0;
}
static inline int hash_map_robin_hood_back_shift_llena_distancia_a_indice_inicio(
		hm_rr_bs_tabla *ht, uint64_t index_stored, uint64_t *distance) {
	hm_cubeta cubeta = ht->buckets_[index_stored];
	*distance = 0;
	if (cubeta.entry == NULL)
		return -1;
	uint64_t num_cubetas = ht->num_buckets_;
	uint64_t index_init = cubeta.hash % num_cubetas;
	if (index_init <= index_stored) {
		*distance = index_stored - index_init;
	} else {
		*distance = index_stored + (num_cubetas - index_init);
	}
	return 0;
}
hm_iter hash_map_robin_hood_back_shift_obten(hm_rr_bs_tabla *ht,
		const void *key, natural key_len, entero_largo *value) {
	uint64_t num_cubetas = ht->num_buckets_;
	uint64_t prob_max = ht->probing_max_;
	uint64_t hash = hash_map_robin_hood_hashear(ht, (void *) key, key_len);
	uint64_t index_init = hash;
	uint64_t probe_distance = 0;
	uint64_t index_current;
	bool found = falso;
	uint32_t i;
	*value = HASH_MAP_VALOR_INVALIDO;
	for (i = 0; i < num_cubetas; i++) {
		index_current = (index_init + i) % num_cubetas;
		hm_entry *entrada = ht->buckets_[index_current].entry;
		if (entrada == NULL) {
			break;
		}
		hash_map_robin_hood_back_shift_llena_distancia_a_indice_inicio(ht,
				index_current, &probe_distance);
		if (i > probe_distance) {
			break;
		}
		if (!memcmp(entrada->llave, key, entrada->llave_tam)) {
			*value = entrada->valor;
			found = verdadero;
			break;
		}
	}
	if (found)
		return index_current;
	return HASH_MAP_VALOR_INVALIDO;
}
hm_iter hash_map_robin_hood_back_shift_pon(hm_rr_bs_tabla *ht, const void *key,
		natural key_len, entero_largo value, bool *nuevo_entry) {
	uint64_t num_cubetas = ht->num_buckets_;
	uint64_t prob_max = ht->probing_max_;
	uint64_t prob_min = ht->probing_min_;
	hm_cubeta *cubetas = ht->buckets_;
	*nuevo_entry = verdadero;
	if (ht->num_buckets_used_ == num_cubetas) {
		*nuevo_entry = falso;
		return HASH_MAP_VALOR_INVALIDO;
	}
	ht->num_buckets_used_ += 1;
	uint64_t hash = hash_map_robin_hood_hashear(ht, (void *) key, key_len);
	uint64_t index_init = hash;
	hm_entry *entry = (hm_entry *) calloc(1, sizeof(hm_entry));
	entry->llave = key;
	entry->llave_tam = key_len;
	entry->valor = value;
	uint64_t index_current = index_init % num_cubetas;
	uint64_t probe_current = 0;
	uint64_t probe_distance;
	hm_entry *entry_temp;
	uint64_t hash_temp;
	uint64_t i;
	for (i = 0; i < num_cubetas; i++) {
		index_current = (index_init + i) % num_cubetas;
		hm_cubeta *cubeta = cubetas + index_current;
		if (cubeta->entry == NULL) {
			cubeta->entry = entry;
			cubeta->hash = hash;
			if (index_current > prob_max) {
				ht->probing_max_ = index_current;
			}
			if (index_current < prob_min) {
				ht->probing_min_ = index_current;
			}
			break;
		} else {
			if (!memcmp(cubeta->entry->llave, key, cubeta->entry->llave_tam)) {
				free(entry);
				*nuevo_entry = falso;
				break;
			}
			hash_map_robin_hood_back_shift_llena_distancia_a_indice_inicio(ht,
					index_current, &probe_distance);
			if (probe_current > probe_distance) {
				// Swapping the current bucket with the one to insert
				entry_temp = cubeta->entry;
				hash_temp = cubeta->hash;
				cubeta->entry = entry;
				cubeta->hash = hash;
				entry = entry_temp;
				hash = hash_temp;
				probe_current = probe_distance;
			}
		}
		probe_current++;
	}
	return index_current;
}
int hash_map_robin_hood_back_shift_borra(hm_rr_bs_tabla *ht, const void *key,
		natural key_len) {
	uint64_t num_cubetas = ht->num_buckets_;
	uint64_t prob_max = ht->probing_max_;
	uint64_t prob_min = ht->probing_max_;
	uint64_t hash = hash_map_robin_hood_hashear(ht, (void *) key, key_len);
	uint64_t index_init = hash;
	bool found = falso;
	uint64_t index_current = 0;
	uint64_t probe_distance = 0;
	hm_entry *entrada = NULL;
	uint64_t i = 0;
	for (i = 0; i < num_cubetas; i++) {
		index_current = (index_init + i) % num_cubetas;
		entrada = ht->buckets_[index_current].entry;
		hash_map_robin_hood_back_shift_llena_distancia_a_indice_inicio(ht,
				index_current, &probe_distance);
		if (entrada == NULL || i > probe_distance) {
			break;
		}
		if (!memcmp(entrada->llave, key, entrada->llave_tam)) {
			found = verdadero;
			break;
		}
	}
	if (found) {
		free(entrada);
		uint64_t i = 1;
		uint64_t index_previous = 0, index_swap = 0;
		for (i = 1; i < num_cubetas; i++) {
			index_previous = (index_current + i - 1) % num_cubetas;
			index_swap = (index_current + i) % num_cubetas;
			hm_cubeta *cubeta_swap = ht->buckets_ + index_swap;
			hm_cubeta *cubeta_previous = ht->buckets_ + index_previous;
			if (cubeta_swap->entry == NULL) {
				cubeta_previous->entry = NULL;
				break;
			}
			uint64_t distance;
			if (hash_map_robin_hood_back_shift_llena_distancia_a_indice_inicio(
					ht, index_swap, &distance) != 0) {
				fprintf(stderr, "Error in FillDistanceToInitIndex()");
			}
			if (!distance) {
				cubeta_previous->entry = NULL;
				break;
			}
			cubeta_previous->entry = cubeta_swap->entry;
			cubeta_previous->hash = cubeta_swap->hash;
		}
		if (i < num_cubetas) {
			if (index_previous == prob_min) {
				prob_min++;
				if (prob_min >= num_cubetas) {
					prob_min = 0;
				} else {
					while (prob_min < num_cubetas
							&& ht->buckets_[prob_min].entry) {
						prob_min++;
					}
					if (prob_min >= num_cubetas) {
						prob_min = num_cubetas;
					}
				}
				ht->probing_min_ = prob_min;
			}
			if (index_previous == prob_max) {
				prob_max--;
				if (prob_max >= num_cubetas) {
					prob_max = num_cubetas;
				} else {
					while (((int64_t) prob_max) >= 0
							&& ht->buckets_[prob_max].entry) {
						prob_max--;
					}
					if (prob_max >= num_cubetas) {
						prob_max = 0;
					}
				}
				ht->probing_max_ = prob_max;
			}
		}
		ht->num_buckets_used_--;
		return 0;
	}
	return 1;
}
static inline void hash_map_robin_hood_back_shift_indice_pon_valor(
		hm_rr_bs_tabla *ht, hm_iter indice, entero_largo valor) {
	assert_timeout(indice <= ht->probing_max_ && indice >= ht->probing_min_);
	hm_entry *entrada = ht->buckets_[indice].entry;
	assert_timeout(entrada);
	entrada->valor = valor;
}
int hash_map_robin_hood_back_shift_indice_borra(hm_rr_bs_tabla *ht,
		hm_iter indice) {
	assert_timeout(indice <= ht->probing_max_ && indice >= ht->probing_min_);
	uint64_t num_cubetas = ht->num_buckets_;
	uint64_t prob_max = ht->probing_max_;
	uint64_t prob_min = ht->probing_max_;
	uint64_t index_current = indice;
	hm_entry *entrada = ht->buckets_[index_current].entry;
	assert_timeout(entrada);
	free(entrada);
	uint64_t i = 1;
	uint64_t index_previous = 0, index_swap = 0;
	for (i = 1; i < num_cubetas; i++) {
		index_previous = (index_current + i - 1) % num_cubetas;
		index_swap = (index_current + i) % num_cubetas;
		hm_cubeta *cubeta_swap = ht->buckets_ + index_swap;
		hm_cubeta *cubeta_previous = ht->buckets_ + index_previous;
		if (cubeta_swap->entry == NULL) {
			cubeta_previous->entry = NULL;
			break;
		}
		uint64_t distance;
		if (hash_map_robin_hood_back_shift_llena_distancia_a_indice_inicio(ht,
				index_swap, &distance) != 0) {
			fprintf(stderr, "Error in FillDistanceToInitIndex()");
		}
		if (!distance) {
			cubeta_previous->entry = NULL;
			break;
		}
		cubeta_previous->entry = cubeta_swap->entry;
		cubeta_previous->hash = cubeta_swap->hash;
	}
	if (i < num_cubetas) {
		if (index_previous == prob_min) {
			prob_min++;
			if (prob_min >= num_cubetas) {
				prob_min = 0;
			} else {
				while (prob_min < num_cubetas && ht->buckets_[prob_min].entry) {
					prob_min++;
				}
				if (prob_min >= num_cubetas) {
					prob_min = num_cubetas;
				}
			}
			ht->probing_min_ = prob_min;
		}
		if (index_previous == prob_max) {
			prob_max--;
			if (prob_max >= num_cubetas) {
				prob_max = num_cubetas;
			} else {
				while (((int64_t) prob_max) >= 0 && ht->buckets_[prob_max].entry) {
					prob_max--;
				}
				if (prob_max >= num_cubetas) {
					prob_max = 0;
				}
			}
			ht->probing_max_ = prob_max;
		}
	}
	ht->num_buckets_used_--;
	return 0;
}

CACA_COMUN_FUNC_STATICA void hash_map_robin_hood_back_shift_reemplazar(
		hm_rr_bs_tabla *ht, void *llave, natural llave_tam, entero_largo valor) {
	hm_iter iter = 0;
	entero_largo *valor_int = &(entero_largo ) { 0 };

	iter = hash_map_robin_hood_back_shift_obten(ht, llave, llave_tam,
			valor_int);

	assert_timeout(iter!=HASH_MAP_VALOR_INVALIDO);

	hash_map_robin_hood_back_shift_indice_pon_valor(ht, iter, valor);
}

CACA_COMUN_FUNC_STATICA void hash_map_robin_hood_back_shift_insertar_nuevo(
		hm_rr_bs_tabla *ht, void *llave, natural llave_tam, entero_largo valor) {
	hm_iter iter = 0;
	bool nuevo = falso;
	iter = hash_map_robin_hood_back_shift_pon(ht, llave, llave_tam, valor,
			&nuevo);

	assert_timeout(iter!=HASH_MAP_VALOR_INVALIDO);
	assert_timeout(nuevo);
}

CACA_COMUN_FUNC_STATICA void hash_map_robin_hood_back_shift_obten_inseguro(
		hm_rr_bs_tabla *ht, void *llave, natural llave_tam,
		entero_largo *valor_contenedor) {
	hm_iter iter = 0;

	iter = hash_map_robin_hood_back_shift_obten(ht, llave, llave_tam,
			valor_contenedor);

	assert_timeout(iter!=HASH_MAP_VALOR_INVALIDO);
}

#define hash_map_robin_hood_back_shift_obten_inseguro_simple(ht,llave,valor_contenedor) hash_map_robin_hood_back_shift_obten_inseguro(ht, &(llave), sizeof(llave), &(valor_contenedor))

#define hash_map_robin_hood_back_shift_insertar_nuevo_simple(ht,llave,valor_contenedor) hash_map_robin_hood_back_shift_insertar_nuevo(ht,llave,sizeof(*llave), valor_contenedor)

#endif

//#define FUNCTION_HDU_MAX_NUM MORBIUS_MAX_MIERDA
#define FUNCTION_HDU_MAX_NUM ((natural)1E9)
//#define FUNCTION_HDU_MAX_NUM (101)

#define FUNCTION_HDU_MAX_LINEAR ((natural)1E6)
//#define FUNCTION_HDU_MAX_LINEAR (22)

typedef struct function_hdu_data {
//	entero_largo sumatoria_morbius[FUNCTION_HDU_MAX_NUM + 1];
	hm_rr_bs_tabla *sumatoria_morbius;
	hm_rr_bs_tabla sumatoria_morbius_storage;
	bitch_vector_ctx *generados;
} function_hdu_data;

CACA_COMUN_FUNC_STATICA entero_largo function_hdu_sumatoria_convolucion_morbius_I(
		natural n) {
	return 1;
}

CACA_COMUN_FUNC_STATICA entero_largo function_hdu_funcion_I(natural n) {
	return 1;
}

CACA_COMUN_FUNC_STATICA entero_largo function_hdu_sumatoria_funcion_I(natural n) {
	return n;
}

natural comple = 0;
CACA_COMUN_FUNC_STATICA entero_largo *function_hdu_calloc() {
	entero_largo *r = NULL;
	r = calloc(1, sizeof(entero_largo));
	assert_timeout(r);

	comple++;
	return r;
}
CACA_COMUN_FUNC_STATICA entero_largo function_hdu_sumatoria_morbius(natural n,
		function_hdu_data *fhd) {
	entero_largo r = 0;
	entero_largo nl = 0;
	if (bitch_checa(fhd->generados, n)) {
//		r = fhd->sumatoria_morbius[n];
		nl = n;
		hash_map_robin_hood_back_shift_obten_inseguro_simple(
				fhd->sumatoria_morbius, nl, r);
//		assert_timeout(n < 3 || r);
	} else {
		for (natural cd = 2, d, la; cd < n; cd = la + 1) {
			d = n / cd;
			la = n / d;
			r += function_hdu_sumatoria_morbius(d, fhd)
					* (function_hdu_sumatoria_funcion_I(la)
							- function_hdu_sumatoria_funcion_I(cd - 1));
		}
		r = (function_hdu_sumatoria_convolucion_morbius_I(n) - r)
				/ function_hdu_funcion_I(1);
//		fhd->sumatoria_morbius[n] = r;
		entero_largo *np = function_hdu_calloc();
		*np = n;
		hash_map_robin_hood_back_shift_insertar_nuevo_simple(
				fhd->sumatoria_morbius, np, r);
		bitch_asigna(fhd->generados, n);
	}
	return r;
}

CACA_COMUN_FUNC_STATICA entero_largo function_hdu_funcion_g(natural n) {
	entero_largo nl = n;
	return nl * nl - 3 * nl + 2;
}

CACA_COMUN_FUNC_STATICA entero_largo function_hdu_sumatoria_funcion_g(natural n) {
	entero_largo nl = n;
	return ((nl * (nl + 1) * (2 * nl + 1)) / 6) - (3 * (((nl * (nl + 1)) / 2)))
			+ 2 * nl;
}

CACA_COMUN_FUNC_STATICA entero_largo function_hdu_sumatoria_convolucion_funcion_morbius(
		natural n, function_hdu_data *fhd) {
	entero_largo r = 0;
	for (natural cd = 2, d, la; cd < n; cd = la + 1) {
		d = n / cd;
		la = n / d;
		r += function_hdu_sumatoria_morbius(d, fhd)
				* (function_hdu_sumatoria_funcion_g(la)
						- function_hdu_sumatoria_funcion_g(cd - 1));
//		r += function_hdu_sumatoria_morbius(d, fhd)
//				* (function_hdu_sumatoria_funcion_I(la)
//						- function_hdu_sumatoria_funcion_I(cd - 1));
	}
	r += function_hdu_funcion_g(1) * function_hdu_sumatoria_morbius(n, fhd);
	return r;
}

CACA_COMUN_FUNC_STATICA void function_hdu_main() {
	function_hdu_data *d = NULL;
	morbius_datos *md = NULL;
	primos_datos *pd = NULL;
	natural t = 0;

	d = calloc(1, sizeof(function_hdu_data));
	assert_timeout(d);
	d->sumatoria_morbius = &d->sumatoria_morbius_storage;
	d->generados = bitch_init(FUNCTION_HDU_MAX_NUM + 1);
	hash_map_robin_hood_back_shift_init(d->sumatoria_morbius,
	FUNCTION_HDU_MAX_LINEAR << 4);

	md = calloc(1, sizeof(morbius_datos));
	assert_timeout(md);
	md->morbius[1] = 1;

	pd = calloc(1, sizeof(primos_datos));
	assert_timeout(pd);

	primos_caca_criba(FUNCTION_HDU_MAX_LINEAR, morbius_primo_encontrado_cb,
	NULL, morbius_divisible_encontrado_cb, morbius_no_divisible_encontrado_cb,
			md, pd);

	entero_largo *ip = function_hdu_calloc();
	*ip = 0;
	hash_map_robin_hood_back_shift_insertar_nuevo_simple(d->sumatoria_morbius,
			ip, 0);
	for (natural i = 1; i <= 0; i++) {
		entero_largo r = 0;
		entero_largo i_ant = i - 1;
		entero_largo *ip = function_hdu_calloc();

		hash_map_robin_hood_back_shift_obten_inseguro_simple(
				d->sumatoria_morbius, i_ant, r);
//		assert_timeout(i_ant < 3 || r);

//		d->sumatoria_morbius[i] = md->morbius[i] + d->sumatoria_morbius[i - 1];
		ip = function_hdu_calloc();
		*ip = i;
		r += md->morbius[i];
		hash_map_robin_hood_back_shift_insertar_nuevo_simple(
				d->sumatoria_morbius, ip, r);

		bitch_asigna(d->generados, i);
	}

//	for (natural i = FUNCTION_HDU_MAX_LINEAR<<1; i >= 1; i--) {
//		entero_largo r = function_hdu_sumatoria_morbius(i, d);
//		caca_log_debug("f[%u]=%lld", i, r);
//		printf("comple %u\n", comple);
//	}

//	for (natural i = 1; i <= FUNCTION_HDU_MAX_LINEAR; i++) {
//		entero_largo r = function_hdu_sumatoria_convolucion_funcion_morbius(i,
//				d);
//		caca_log_debug("f[%u]=%lld", i, r);
//		printf("f[%u]=%lld\n", i, r % (((natural)1e9) + 1));
//	}

	scanf("%u", &t);

	while (t--) {
		natural n = 0;
		scanf("%u", &n);
		entero_largo r = function_hdu_sumatoria_convolucion_funcion_morbius(n,
				d);
		printf("%llu\n", r % ((int) 1E9 + 7));
	}

	hash_map_robin_hood_back_shift_fini(d->sumatoria_morbius);
	bitch_fini(d->generados);
	free(d);
	free(md);
	free(pd);
}

int main(void) {
	function_hdu_main();
	return EXIT_SUCCESS;
}
