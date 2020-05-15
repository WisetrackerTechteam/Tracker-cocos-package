
## 1. Cocos2d-x 플러그인 설치

### 1.1 Cocos2d-x 패키지 패키지 다운로드

Cocos2d-x 플러그인 패키지를 다운로드 해주세요.
[패키지 다운로드](https://github.com/WisetrackerTechteam/Tracker-cocos-package)

## 2. Android 설정

### 2.1 SDK 설치

#### 2.1.1 Classes 파일 삽입

Cocos2dx 프로젝트의 Classes 폴더에 다운로드 받은 패키지의 Classes 폴더에 들어있는 파일(`Wisetracker.cpp`, `Wisetracker.h`)을 복사해 주세요.

#### 2.1.2 Classes 파일 설정

Cocos2dx 프로젝트의 `CMakeLists.txt` 파일에 `소스파일`과 `헤더파일`을 선언해 주세요.

```
list(APPEND GAME_SOURCE
     Classes/Wisetracker.cpp // 추가
     )
list(APPEND GAME_HEADER
     Classes/Wisetracker.h   // 추가
     )
```

#### 2.1.3 wisetracker-cocos.jar 삽입

다운로드 받은 패키지 폴더의 `proj.android/libs/wisetracker-cocos.jar` 파일을 안드로이드 스튜디오 `Project/app/libs` 폴더에에 삽입해 주세요.

#### 2.1.4 SDK Download

Android 프로젝트 `app/build.gradle` 파일 `dependencies` 블록에 의존성을 추가해 주세요.

```gradle
dependencies {
    implementation fileTree(dir: 'libs', include: ['*.jar']) 
    ....
    implementation 'kr.co.wisetracker.insight:SDK_V1:21.3.39'

}
```

### 2.2 SDK 설정

#### 2.2.1 Wisetracker App Key 등록

##### (1) Wisetracker App Key 발급

- `http://report.wisetracker.co.kr` 로그인
- 설정 > 기본설정 > 서비스 > Android 분석코드 (AppKey) 클릭 > AppKey 복사
  ![Appkey 등록](https://dzf8vqv24eqhg.cloudfront.net/userfiles/6274/8379/ckfinder/images/016.png?dc=201702100857-66 "Appkey 등록")

##### (2) Wisetracker App Key 적용

`AndroidManifest.xml` 파일에 (1)에서 발급 받은 APP KEY 등록해 주세요.

```xml
<meta-data
  android:name="WiseTrackerKey"
  android:value="YOUR_APP_KEY" />
```

#### 2.2.2 디버깅 모드 설정

`AndroidManifest.xml` 파일에 아래와 같이 디버깅 설정 코드를 적용해 주세요.

```xml
<!-- 개발시 true. 배포시 false 권장 -->
<meta-data
  android:name="WiseTrackerLogState"
  android:value="true" />
```

#### 2.2.3 Http 통신 허용 설정

프로젝트의 `Target API 28 이상`일 경우 Http 통신 허용을 추가해 주세요.

```xml
<!-- AndroidManifest.xml -->
<application
  android:icon="@mipmap/ic_launcher"
  android:label="@string/app_name"
  android:networkSecurityConfig="@xml/network_security_config"
  android:theme="@style/AppTheme">
```

```xml

<!-- app/res/xml/network_security_config.xml -->
<?xml version="1.0" encoding="utf-8"?>
<network-security-config>
    <domain-config cleartextTrafficPermitted="true">
        <domain includeSubdomains="true">trk.wisetracker.co.kr</domain>
    </domain-config>
</network-security-config>
```

## 3. 유입 경로 분석 적용

### 3.1 딥링크 분석

딥링크를 통해 앱이 실행되는 경로 분석이 필요한 경우 적용해 주세요.

#### 3.1.1 딥링크 등록

`AndroidManifest.xml` 파일에서 앱의 환경에 맞춰 `android:host`, `android:scheme` 값을 변경해 주세요.

```xml
<!-- 예시는 wisetracker://wisetracker.co.kr 링크로 앱 진입 경우 -->
<activity android:name="kr.co.wisetracker.cocos.DeepLinkActivity"
          android:launchMode="singleTop" >
    <intent-filter>
        <action android:name="android.intent.action.VIEW" />
        <category android:name="android.intent.category.DEFAULT" />
        <category android:name="android.intent.category.BROWSABLE" />
        <!-- 딥링크로 진입될 스키마와 호스트 정보 수정 -->
        <data android:host="wisetracker.co.kr"
              android:scheme="wisetracker" />
    </intent-filter>
</activity>
```

#### 3.1.2 딥링크 수신

딥링크가 실행되는 `Activity`에서 아래와 같은 코드를 적용해 주세요.
`위의 설정된 kr.co.wisetracker.cocos.DeepLinkActivity` 사용시 설정 불필요합니다.
`커스텀 딥링크 사용하시는 경우에 적용해 주세요.`

```java

public class DeepLinkActivity extends Activity {

    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        // SDK 호출
        if(!WiseTracker.checkWisetrackerSDKInitState()) {
           WiseTracker.initWithIntent(context, intent);
        } else {
           WiseTracker.checkReferrer(intent);
        }
    }

    @Override
    protected void onNewIntent(Intent intent) {
        super.onNewIntent(intent);
        // SDK 호출
        if(!WiseTracker.checkWisetrackerSDKInitState()) {
           WiseTracker.initWithIntent(context, intent);
        } else {
           WiseTracker.checkReferrer(intent);
        }
    }

}
```

## 4. 기본 설정

### 4.1 헤더 파일 추가

SDK를 사용하는 .cpp 파일에서 `Wisetracker.h` 파일을 `include` 해주세요.

```c
#include "Wisetracker.h"
```

### 4.2 페이지 분석

페이지 분석을 위해 페이지 `진입`과 `이탈`시 각각 아래와 같이 코드를 삽입해 주세요.  

```csharp
// 페이지 진입시
WiseTracker::startPage("PAGE_CODE");
// 페이지 이탈시
WiseTracker::endPage("PAGE_CODE");
```

### 4.3 체류 시간 분석

체류시간 분석 페이지 `진입`과 `이탈`시 각각 아래와 같이 코드를 삽입해 주세요.  

```csharp
// 체류 시간 분석을 위한 시간(분 단위)을 넣어주세요
// 예) 15분 단위로 체류 페이지 자동 전송
WiseTracker::onPlayStart(15);
```

```csharp
WiseTracker::onPlayStop();
```

