#ifndef GSRES_HPP
#define GSRES_HPP
#include <global.h>
typedef u8 (*GSresFreeCallback)(void*, unsigned long, unsigned long);
extern "C" {
void GSresIsUniqueID(unsigned long, unsigned long, u8);
void GSresUnlockResource(unsigned long, unsigned long);
void GSresLockResource(unsigned long, unsigned long);
void GSresDumpGroup(unsigned long);
void GSresDumpAll();
void GSresFreeGroup(unsigned long);
void GSresFreeResource(unsigned long, unsigned long);
void GSresFreeResourceAllGroup(unsigned long);
void* GSresGetResourceAllGroup(unsigned long);
void* GSresGetResource(unsigned long, unsigned long);
void GSresChangeResourceAdress(void*, unsigned long, unsigned long, GSresFreeCallback);
void GSresRegisterResource(void*, unsigned long, unsigned long, GSresFreeCallback);
void* GSresAllocResourceAlign(unsigned long, unsigned short, unsigned long, unsigned long, GSresFreeCallback);
void* GSresAllocResource(unsigned long, unsigned long, unsigned long, GSresFreeCallback);
void GSresInit(unsigned long);
}
#endif
