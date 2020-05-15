#include "Wisetracker.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)

#include <jni.h>
#include <android/log.h>
#include "platform/android/jni/JniHelper.h"

#define  LOG_TAG    "[wisetracker]"
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)
#define  WISETRACKER_CLASS_NAME "kr/co/wisetracker/cocos/CocosHelper"

#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#endif

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)

typedef struct JniMethodInfo_
{
	JNIEnv *    env;
	jclass      classId;
	jmethodID   methodId;
} JniMethodInfo;

extern "C"
{
static JNIEnv* getJNIEnv(void) {
	JavaVM* jvm = cocos2d::JniHelper::getJavaVM();
	if (NULL == jvm) {
		LOGD("Failed to get JNIEnv. JniHelper::getJavaVM() is NULL");
		return NULL;
	}

	JNIEnv *env = NULL;
	// get jni environment
	jint ret = jvm->GetEnv((void**)&env, JNI_VERSION_1_4);

	switch (ret) {
		case JNI_OK :
			// Success!
			return env;

		case JNI_EDETACHED :
			// Thread not attached
			// TODO : If calling AttachCurrentThread() on a native thread
			// must call DetachCurrentThread() in future.
			// see: http://developer.android.com/guide/practices/design/jni.html
			if (jvm->AttachCurrentThread(&env, NULL) < 0)
			{
				LOGD("Failed to get the environment using AttachCurrentThread()");
				return NULL;
			} else {
				// Success : Attached and obtained JNIEnv!
				return env;
			}

		case JNI_EVERSION :
			// Cannot recover from this error
			LOGD("JNI interface version 1.4 not supported");

		default :
			LOGD("Failed to get the environment using GetEnv()");
			return NULL;
	}
}

static bool getStaticMethodInfo(JniMethodInfo &methodInfo, const char *methodName, const char *methodSignature) {
	JNIEnv *pEnv = getJNIEnv();
	if (!pEnv) {
		return false;
	}
	jclass classId = pEnv->FindClass(WISETRACKER_CLASS_NAME);
	if (!classId) {
		LOGD("Failed to find class of %s", WISETRACKER_CLASS_NAME);
		return false;
	}
	jmethodID methodId = pEnv->GetStaticMethodID(classId, methodName, methodSignature);
	if (!methodId) {
		LOGD("Failed to find static method id of %s", methodName);
		pEnv->DeleteLocalRef(classId);
		return false;
	}
	methodInfo.env = pEnv;
	methodInfo.classId = classId;
	methodInfo.methodId = methodId;
	return true;
}

static void callStaticMethod(const char*methodName) {
	JniMethodInfo methodInfo;
	if (!getStaticMethodInfo(methodInfo, methodName, "()V")) {
		return;
	}
	methodInfo.env->CallStaticVoidMethod(methodInfo.classId, methodInfo.methodId);
	methodInfo.env->DeleteLocalRef(methodInfo.classId);
}

static void callStaticMethodWithIntParam(const char*methodName, int param) {
	JniMethodInfo methodInfo;
	if (!getStaticMethodInfo(methodInfo, methodName, "(I)V")) {
		return;
	}
	methodInfo.env->CallStaticVoidMethod(methodInfo.classId, methodInfo.methodId, param);
	methodInfo.env->DeleteLocalRef(methodInfo.classId);
}

static void callStaticMethodWithDoubleParam(const char*methodName, double param) {
	JniMethodInfo methodInfo;
	if (!getStaticMethodInfo(methodInfo, methodName, "(D)V")) {
		return;
	}
	methodInfo.env->CallStaticVoidMethod(methodInfo.classId, methodInfo.methodId, param);
	methodInfo.env->DeleteLocalRef(methodInfo.classId);
}

static void callStaticMethodWithBoolParam(const char*methodName, bool param) {
	JniMethodInfo methodInfo;
	if (!getStaticMethodInfo(methodInfo, methodName, "(Z)V")) {
		return;
	}
	methodInfo.env->CallStaticVoidMethod(methodInfo.classId, methodInfo.methodId, param);
	methodInfo.env->DeleteLocalRef(methodInfo.classId);
}

static void callStaticMethodWithStringParam(const char*methodName, const char* param) {
	JniMethodInfo methodInfo;
	if (!getStaticMethodInfo(methodInfo, methodName, "(Ljava/lang/String;)V")) {
		return;
	}
	jstring paramName = methodInfo.env->NewStringUTF(param);
	methodInfo.env->CallStaticVoidMethod(methodInfo.classId, methodInfo.methodId, paramName);
	methodInfo.env->DeleteLocalRef(paramName);
	methodInfo.env->DeleteLocalRef(methodInfo.classId);
}

static void callStaticMethodWithStringIntParam(const char*methodName, const char* param1, int param2) {
	JniMethodInfo methodInfo;
	if (!getStaticMethodInfo(methodInfo, methodName, "(Ljava/lang/String;I)V")) {
		return;
	}
	jstring paramName = methodInfo.env->NewStringUTF(param1);
	methodInfo.env->CallStaticVoidMethod(methodInfo.classId, methodInfo.methodId, paramName, param2);
	methodInfo.env->DeleteLocalRef(paramName);
	methodInfo.env->DeleteLocalRef(methodInfo.classId);
}

static void callStaticMethodWithStringDoubleParam(const char*methodName, const char* param1, double param2) {
	JniMethodInfo methodInfo;
	if (!getStaticMethodInfo(methodInfo, methodName, "(Ljava/lang/String;D)V")) {
		return;
	}
	jstring paramName = methodInfo.env->NewStringUTF(param1);
	methodInfo.env->CallStaticVoidMethod(methodInfo.classId, methodInfo.methodId, paramName, param2);
	methodInfo.env->DeleteLocalRef(paramName);
	methodInfo.env->DeleteLocalRef(methodInfo.classId);
}

static void callStaticMethodWithStringStringParam(const char*methodName, const char* param1, const char* param2) {
	JniMethodInfo methodInfo;
	if (!getStaticMethodInfo(methodInfo, methodName, "(Ljava/lang/String;Ljava/lang/String;)V")) {
		return;
	}
	jstring paramName1 = methodInfo.env->NewStringUTF(param1);
	jstring paramName2 = methodInfo.env->NewStringUTF(param2);
	methodInfo.env->CallStaticVoidMethod(methodInfo.classId, methodInfo.methodId, paramName1, paramName2);
	methodInfo.env->DeleteLocalRef(paramName1);
	methodInfo.env->DeleteLocalRef(paramName2);
	methodInfo.env->DeleteLocalRef(methodInfo.classId);
}

} // extern "C"


void WiseTracker::sendTransaction() {
	callStaticMethod("sendTransaction");
}
void WiseTracker::initPushSet(const char* key, const char* value) {
	callStaticMethodWithStringStringParam("initPushSet", key, value);
}
void WiseTracker::putInitData(const char* key, const char* value) {
	callStaticMethodWithStringStringParam("putInitData", key, value);
}
void WiseTracker::onPlayStart(int period) {
	callStaticMethodWithIntParam("onPlayStart", period);
}
void WiseTracker::onPlayStop() {
	callStaticMethod("onPlayStop");
}
void WiseTracker::startPage(const char* code) {
	callStaticMethodWithStringParam("startPage", code);
}
void WiseTracker::endPage(const char* code) {
	callStaticMethodWithStringParam("endPage", code);
}
void WiseTracker::putSessionData(const char* key, const char* value) {
	callStaticMethodWithStringStringParam("putSessionData", key, value);
}
void WiseTracker::setGoal(const char* key, double value) {
	callStaticMethodWithStringDoubleParam("setGoal", key, value);
}
void WiseTracker::setAcceptPushReceived(bool isAccepted) {
	callStaticMethodWithBoolParam("setAcceptPushReceived", isAccepted);
}
void WiseTracker::sendGoalData() {
	callStaticMethod("sendGoalData");
}
void WiseTracker::setGoalCustomMvtTag(const char* key, const char* value) {
	callStaticMethodWithStringStringParam("setGoalCustomMvtTag", key, value);
}
void WiseTracker::setGoalProduct(const char* code) {
	callStaticMethodWithStringParam("setGoalProduct", code);
}
void WiseTracker::setGoalProductArray(char* array) {
	callStaticMethodWithStringParam("setGoalProductArray", array);
}
void WiseTracker::setGoalProductType(const char* type) {
	callStaticMethodWithStringParam("setGoalProductType", type);
}
void WiseTracker::setGoalProductTypeArray(char* array) {
	callStaticMethodWithStringParam("setGoalProductTypeArray", array);
}
void WiseTracker::setGoalProductCategory(const char* code) {
	callStaticMethodWithStringParam("setGoalProductCategory", code);
}
void WiseTracker::setExhibit(const char* exhibit) {
	callStaticMethodWithStringParam("setExhibit", exhibit);
}
void WiseTracker::setProduct(const char* key, const char* value) {
	callStaticMethodWithStringStringParam("setProduct", key, value);
}
void WiseTracker::setProductType(const char* type) {
	callStaticMethodWithStringParam("setProductType", type);
}
void WiseTracker::setProductCategory(const char* category) {
	callStaticMethodWithStringParam("setProductCategory", category);
}
void WiseTracker::setOrderCustomMvtTag(const char* key, const char* value) {
	callStaticMethodWithStringStringParam("setOrderCustomMvtTag", key, value);
}
void WiseTracker::setOrderCustomMvtTagArray(const char* key, char* array) {
	callStaticMethodWithStringStringParam("setOrderCustomMvtTagArray", key, array);
}

void WiseTracker::setOrderProduct(const char* code) {
	callStaticMethodWithStringParam("setOrderProduct", code);
}
void WiseTracker::setOrderProductArray(char* array) {
	callStaticMethodWithStringParam("setOrderProductArray", array);
}
void WiseTracker::setOrderProductType(const char* type) {
	callStaticMethodWithStringParam("setOrderProductType", type);
}
void WiseTracker::setOrderProductTypeArray(char* array) {
	callStaticMethodWithStringParam("setOrderProductTypeArray", array);
}
void WiseTracker::setOrderProductCategory(const char* category) {
	callStaticMethodWithStringParam("setOrderProductCategory", category);
}
void WiseTracker::setOrderProductCategoryArray(char* array) {
	callStaticMethodWithStringParam("setOrderProductCategoryArray", array);
}
void WiseTracker::setOrderAmount(double value) {
	callStaticMethodWithDoubleParam("setOrderAmount", value);
}
void WiseTracker::setOrderAmountArray(char* array) {
	callStaticMethodWithStringParam("setOrderAmountArray", array);
}
void WiseTracker::setOrderConversionData(const char* key, double value) {
	callStaticMethodWithStringDoubleParam("setOrderConversionData", key, value);
}
void WiseTracker::setOrderConversionDataArray(const char* key, char* array) {
	callStaticMethodWithStringStringParam("setOrderConversionDataArray",key, array);
}
void WiseTracker::useIkwdWithConversion(const char* value) {
	callStaticMethodWithStringParam("useIkwdWithConversion", value);
}
void WiseTracker::useMvt1WithConversion(const char* value) {
	callStaticMethodWithStringParam("useMvt1WithConversion", value);
}
void WiseTracker::useMvt2WithConversion(const char* value) {
	callStaticMethodWithStringParam("useMvt2WithConversion", value);
}
void WiseTracker::useMvt3WithConversion(const char* value) {
	callStaticMethodWithStringParam("useMvt3WithConversion", value);
}
void WiseTracker::setOrderNo(const char* orderNo) {
	callStaticMethodWithStringParam("setOrderNo", orderNo);
}
void WiseTracker::setOrderQuantity(int value) {
	callStaticMethodWithIntParam("setOrderQuantity", value);
}
void WiseTracker::setOrderQuantityArray(char* array) {
	callStaticMethodWithStringParam("setOrderQuantityArray", array);
}
void WiseTracker::setContents(const char* contents) {
	callStaticMethodWithStringParam("setContents", contents);
}
void WiseTracker::setPageIdentity(const char* identify) {
	callStaticMethodWithStringParam("setPageIdentity", identify);
}
void WiseTracker::setSearchKeyword(const char* keyword) {
	callStaticMethodWithStringParam("setSearchKeyword", keyword);
}
void WiseTracker::setGoalSearchKeyword(const char* goalSearchKeyword) {
	callStaticMethodWithStringParam("setGoalSearchKeyword", goalSearchKeyword);
}
void WiseTracker::setOrderSearchKeyword(const char* orderSearchKeyword) {
	callStaticMethodWithStringParam("setOrderSearchKeyword", orderSearchKeyword);
}
void WiseTracker::setOrderSearchKeywordArray(char* array) {
	callStaticMethodWithStringParam("setOrderSearchKeywordArray", array);
}
void WiseTracker::setSearchKeywordResult(int count) {
	callStaticMethodWithIntParam("setSearchKeywordResult", count);
}
void WiseTracker::setSearchKeywordCategory(const char* category) {
	callStaticMethodWithStringParam("setSearchKeywordCategory", category);
}
void WiseTracker::setMember(const char* member) {	
	callStaticMethodWithStringParam("setMember", member);
}
void WiseTracker::setGender(const char* gender) {
	callStaticMethodWithStringParam("setGender", gender);
}
void WiseTracker::setAge(const char* age) {
	callStaticMethodWithStringParam("setAge", age);
}
void WiseTracker::setUserAttribute(const char* key, const char* value) {
	callStaticMethodWithStringStringParam("setUserAttribute", key, value);
}
void WiseTracker::setCustomMvtTag(const char* key, const char* value) {
	callStaticMethodWithStringStringParam("setCustomMvtTag", key, value);
}
void WiseTracker::setOrderDate(const char* orderDate) {
	callStaticMethodWithStringParam("setOrderDate", orderDate);
}
void WiseTracker::setOrderDateArray(const char* orderDate, int itemCount) {
	callStaticMethodWithStringIntParam("setOrderDateArray", orderDate, itemCount);
}
void WiseTracker::setWisetrackerDebugMode(bool mode) {
	callStaticMethodWithBoolParam("setWisetrackerDebugMode", mode);
}
void WiseTracker::sendClickData(const char* key, const char* value) {
	callStaticMethodWithStringStringParam("sendClickData", key, value);
}
void WiseTracker::sendImmediatelyClickData(const char* key, const char* value) {
	callStaticMethodWithStringStringParam("sendImmediatelyClickData", key, value);
}

#else

void WiseTracker::sendTransaction() {}
void WiseTracker::initPushSet(const char* key, const char* value) {}
void WiseTracker::putInitData(const char* key, const char* value) {}
void WiseTracker::onPlayStart(int period) {}
void WiseTracker::onPlayStop() {}
void WiseTracker::startPage(const char* code) {}
void WiseTracker::endPage(const char* code) {}
void WiseTracker::putSessionData(const char* key, const char* value) {}
void WiseTracker::setGoal(const char* key, double value) {}
void WiseTracker::setAcceptPushReceived(bool isAccepted) {}
void WiseTracker::sendGoalData() {}
void WiseTracker::setGoalCustomMvtTag(const char* key, const char* value) {}
void WiseTracker::setGoalProduct(const char* code) {}
void WiseTracker::setGoalProductArray(char* array[) {}
void WiseTracker::setGoalProductType(const char* type) {}
void WiseTracker::setGoalProductTypeArray(char* array) {}
void WiseTracker::setGoalProductCategory(const char* code) {}
void WiseTracker::setExhibit(const char* exhibit) {}
void WiseTracker::setProduct(const char* key, const char* value) {}
void WiseTracker::setProductType(const char* type) {}
void WiseTracker::setProductCategory(const char* category) {}
void WiseTracker::setOrderCustomMvtTag(const char* key, const char* value) {}
void WiseTracker::setOrderCustomMvtTagArray(const char* key,char* array) {}
void WiseTracker::setOrderProduct(const char* code) {}
void WiseTracker::setOrderProductArray(char* array) {}
void WiseTracker::setOrderProductType(const char* type) {}
void WiseTracker::setOrderProductTypeArray(const char* array) {}
void WiseTracker::setOrderProductCategory(const char* category) {}
void WiseTracker::setOrderProductCategoryArray(char* array) {}
void WiseTracker::setOrderAmount(double value) {}
void WiseTracker::setOrderAmountArray(char* array) {}
void WiseTracker::setOrderConversionData(const char* key, double value) {}
void WiseTracker::setOrderConversionDataArray(const char* key, char* array) {}
void WiseTracker::useIkwdWithConversion(const char* value) {}
void WiseTracker::useMvt1WithConversion(const char* value) {}
void WiseTracker::useMvt2WithConversion(const char* value) {}
void WiseTracker::useMvt3WithConversion(const char* value) {}
void WiseTracker::setOrderNo(const char* orderNo) {}
void WiseTracker::setOrderQuantity(int value) {}
void WiseTracker::setOrderQuantityArray(int array) {}
void WiseTracker::setContents(const char* contents) {}
void WiseTracker::setPageIdentity(const char* identify) {}
void WiseTracker::setSearchKeyword(const char* keyword) {}
void WiseTracker::setGoalSearchKeyword(const char* goalSearchKeyword) {}
void WiseTracker::setOrderSearchKeyword(const char* orderSearchKeyword) {}
void WiseTracker::setOrderSearchKeywordArray(char* array) {}
void WiseTracker::setSearchKeywordResult(int count) {}
void WiseTracker::setSearchKeywordCategory(const char* category) {}
void WiseTracker::setMember(const char* member) {}
void WiseTracker::setGender(const char* gender) {}
void WiseTracker::setAge(const char* age) {}
void WiseTracker::setUserAttribute(const char* key, const char* value) {}
void WiseTracker::setCustomMvtTag(const char* key, const char* value) {}
void WiseTracker::setOrderDate(const char* orderDate) {}
void WiseTracker::setOrderDateArray(const char* orderDate, int itemCount) {}
void WiseTracker::setWisetrackerDebugMode(bool mode) {}
void WiseTracker::sendClickData(const char* key, const char* value) {}
void WiseTracker::sendImmediatelyClickData(const char* key, const char* value) {}

#endif

