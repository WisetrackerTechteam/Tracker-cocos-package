#ifndef __WISETRACKER_H__
#define __WISETRACKER_H__

#include "cocos2d.h"

class WiseTracker {
public:
static void sendTransaction();
static void initPushSet(const char* key, const char* value);
static void putInitData(const char* key, const char* value);
static void onPlayStart(int period);
static void onPlayStop();
static void startPage(const char* code);
static void endPage(const char* code);
static void putSessionData(const char* key, const char* value);
static void setGoal(const char* key, double value);
static void setAcceptPushReceived(bool isAccepted);
static void sendGoalData();
static void setGoalCustomMvtTag(const char* key, const char* value);
static void setGoalProduct(const char* code);
static void setGoalProductArray(char* array);
static void setGoalProductType(const char* type);
static void setGoalProductTypeArray(char* array);
static void setGoalProductCategory(const char* code);
static void setExhibit(const char* exhibit);
static void setProduct(const char* key, const char* value);
static void setProductType(const char* type);
static void setProductCategory(const char* category);
static void setOrderCustomMvtTag(const char* key, const char* value);
static void setOrderCustomMvtTagArray(const char* key, char* array);
static void setOrderProduct(const char* code);
static void setOrderProductArray(char* array);
static void setOrderProductType(const char* type);
static void setOrderProductTypeArray(char* array);
static void setOrderProductCategory(const char* category);
static void setOrderProductCategoryArray(char* array);
static void setOrderAmount(double value);
static void setOrderAmountArray(char* array);
static void setOrderConversionData(const char* key, double value);
static void setOrderConversionDataArray(const char* key, char* array);
static void useIkwdWithConversion(const char* value);
static void useMvt1WithConversion(const char* value);
static void useMvt2WithConversion(const char* value);
static void useMvt3WithConversion(const char* value);
static void setOrderNo(const char* orderNo);
static void setOrderQuantity(int value);
static void setOrderQuantityArray(char* array);
static void setContents(const char* contents);
static void setPageIdentity(const char* identify);
static void setSearchKeyword(const char* keyword);
static void setGoalSearchKeyword(const char* goalSearchKeyword);
static void setOrderSearchKeyword(const char* orderSearchKeyword);
 static void setOrderSearchKeywordArray(char* array);
static void setSearchKeywordResult(int count);
static void setSearchKeywordCategory(const char* category);
static void setMember(const char* member);
static void setGender(const char* gender);
static void setAge(const char* age);
static void setUserAttribute(const char* key, const char* value);
static void setCustomMvtTag(const char* key, const char* value);
static void setOrderDate(const char* orderDate);
static void setOrderDateArray(const char* orderDate, int itemCount);
static void setWisetrackerDebugMode(bool mode);
static void sendClickData(const char* key, const char* value);
static void sendImmediatelyClickData(const char* key, const char* value);
};

#endif // __DOP_H__
