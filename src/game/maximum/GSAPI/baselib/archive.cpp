#include "game/maximum/GSAPI/baselib/archive.h"

#include <libc/string.h>
extern void OSReport(const char*, ...);
static inline void Locate(HSD_Archive* archive)
{
    unsigned int i;
    unsigned int* ptr;
    for (i = 0; i < archive->header.nb_reloc; i++) {
        ptr = (unsigned int*)(archive->data + archive->reloc_info[i].offset);
        *ptr += (unsigned int)archive->data;
    }
}
int HSD_ArchiveParse(HSD_Archive* archive, unsigned char* src, size_t file_size)
{
    unsigned int offset;
    if (archive == 0) return -1;
    memset(archive, 0, sizeof(HSD_Archive));
    archive->flags |= 1;
    memcpy(archive, src, sizeof(HSD_ArchiveHeader));
    if (archive->header.file_size != file_size) {
        OSReport("HSD_ArchiveParse: byte-order mismatch! Please check data format\n");
        return -1;
    }
    offset = sizeof(HSD_ArchiveHeader);
    if (archive->header.data_size != 0) {
        archive->data = src + sizeof(HSD_ArchiveHeader);
        offset = archive->header.data_size + sizeof(HSD_ArchiveHeader);
    }
    if (archive->header.nb_reloc != 0) {
        archive->reloc_info = (HSD_ArchiveRelocationInfo*)(src + offset);
        offset += archive->header.nb_reloc * sizeof(HSD_ArchiveRelocationInfo);
    }
    if (archive->header.nb_public != 0) {
        archive->public_info = (HSD_ArchivePublicInfo*)(src + offset);
        offset += archive->header.nb_public * sizeof(HSD_ArchivePublicInfo);
    }
    if (archive->header.nb_extern != 0) {
        archive->extern_info = (HSD_ArchiveExternInfo*)(src + offset);
        offset += archive->header.nb_extern * sizeof(HSD_ArchiveExternInfo);
    }
    if (offset < archive->header.file_size) archive->symbols = (char*)(src + offset);
    archive->top_ptr = src;
    Locate(archive);
    return 0;
}
void* HSD_ArchiveGetPublicAddress(HSD_Archive* archive, const char* symbols)
{
    unsigned int i;
    for (i = 0; i < archive->header.nb_public; i++) {
        int comparison = strcmp(archive->symbols + archive->public_info[i].symbol, symbols);
        if (comparison == 0) return archive->data + archive->public_info[i].offset;
    }
    return 0;
}
