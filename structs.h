#ifndef STRUCTS_H
#define STRUCTS_H

#include <stdio.h>

#define MAX_AUTHOR 50
#define MAX_CONTENT 280

typedef enum{
    REPORT_SPAM,
    REPORT_HATE,
    REPORT_VULGAR,
    REPORT_FAKE,
    REPORT_INAPPRIOPRIATE
}ReportType;

typedef enum{
    MODSTAT_TO_VERIFY,
    MODSTAT_UNDER_ANALYSIS,
    MODSTAT_APPROVED,
    MODSTAT_DELETED
}ModerationStatus;

typedef struct {
    int id;
    char author[MAX_AUTHOR];
    char content[MAX_CONTENT];
    ReportType report;
    int reportsCount;
    ModerationStatus status;

} Post;

typedef struct PostNode {
    Post data;
    struct PostNode *next;
} PostNode;

void printPost(const Post *p);
const char* reportTypeToStr(ReportType r);
const char* statusToStr(ModerationStatus s);


#endif