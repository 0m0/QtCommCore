#ifndef UTC2GMT_H
#define UTC2GMT_H

#ifdef __cplusplus
extern "C" {
#endif

char *utctogmt(char *buff, signed long seconds, signed long fraction, signed long qflags);

#ifdef __cplusplus
}
#endif

#endif // UTC2GMT_H
