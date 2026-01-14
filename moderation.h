#ifndef MODERATION_H
#define MODERATION_H

#include "structs.h"

void initList(void);
void freeList(void);

PostNode* addPost(const char *author, const char *content, ReportType report, int reportsCount);

PostNode* findPostById(int id);

int editPost(int id);

void printAllPosts(void);

#endif