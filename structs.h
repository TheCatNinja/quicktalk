#ifndef STRUCTS_H
#define STRUCTS_H

typedef enum{
    REPORT_SPAM,
    REPORT_HATE,
    REPORT_VULGAR,
    REPORT_FAKE,
    REPORT_INAPPRIOPRIATE
} ReportType;

typedef enum{
    MODSTAT_TO_VERIFY,
    MODSTAT_UNDER_ANALYSIS,
    MODSTAT_APPROVED,
    MODSTAT_DELETED
}ModerationStatus;

typedef struct Post {
    int id;
    char author[100];
    char content[280];
    ReportType report;

} Post;

#endif