//
// Created by 이승철 on 2018. 6. 1..
//

#ifndef NDKJNITEST_NDK_H
#define NDKJNITEST_NDK_H

#ifdef __cplusplus
extern "C" {
#endif
void jniReqVoid(void);
int jniReqIntRetInt(int);
void jniCallBackStart(void);
void jniCallBackStop(void);

#ifdef __cplusplus
}
#endif
#endif //NDKJNITEST_NDK_H
