// this is only the testing version of api.h
// the input format and hashing function will be
// different on DSA Judge

#ifndef API_H
#define API_H
#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>

typedef struct mail {
	int id;
	char from[32], to[32];
	char subject[256], content[100000];
} mail;

typedef struct query {
	int id;
	double reward;

	enum query_type {
		expression_match,
		find_similar,
		group_analyse
	} type;

	union query_data {
		struct {
			char expression[2048];
		} expression_match_data;

		struct {
			int mid;
			double threshold;
		} find_similar_data;

		struct {
			int len, mids[512];
		} group_analyse_data;
	} data;
} query;

long _get_process_cputime();

void _assert(bool condition, char message[]);

void _answer(int qid, int answers[], int len);

void api_init(int *n_mails, int *n_queries, mail **mails, query **queries);


static struct {
	void (*init)(int *n_mails, int *n_queries, mail **mails, query **queries);
	void (*answer)(int qid, int answers[], int len);
} api = {api_init, _answer};

#endif
