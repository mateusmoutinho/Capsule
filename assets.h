#ifndef ASSETS_H
#define ASSETS_H

typedef struct app_embedded_asset {
    const char *path;
    unsigned char *content;
    unsigned long  size;
    int is_binary;
} app_embedded_asset;

extern app_embedded_asset embedded_assets[];
extern unsigned long embedded_assets_total_size;

#endif
