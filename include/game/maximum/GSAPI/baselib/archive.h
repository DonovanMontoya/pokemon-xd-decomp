#ifndef HSD_ARCHIVE_H
#define HSD_ARCHIVE_H
#include <libc/stddef.h>
typedef struct HSD_ArchiveHeader {
    unsigned int file_size, data_size, nb_reloc, nb_public, nb_extern;
    unsigned char version[4], pad[8];
} HSD_ArchiveHeader;
typedef struct HSD_ArchiveRelocationInfo { unsigned int offset; } HSD_ArchiveRelocationInfo;
typedef struct HSD_ArchivePublicInfo { unsigned int offset, symbol; } HSD_ArchivePublicInfo;
typedef HSD_ArchivePublicInfo HSD_ArchiveExternInfo;
typedef struct HSD_Archive {
    HSD_ArchiveHeader header;
    unsigned char* data;
    HSD_ArchiveRelocationInfo* reloc_info;
    HSD_ArchivePublicInfo* public_info;
    HSD_ArchiveExternInfo* extern_info;
    char* symbols;
    void* next;
    char* name;
    unsigned int flags;
    void* top_ptr;
} HSD_Archive;
int HSD_ArchiveParse(HSD_Archive*, unsigned char*, size_t);
void* HSD_ArchiveGetPublicAddress(HSD_Archive*, const char*);
#endif
