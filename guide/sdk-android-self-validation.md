# 개발자 검증(Cordova Android)

## 1. 디버깅 모드 설정
`AndroidManifest.xml` 파일에 디버깅 모드 활성화 여부를 확인해 주세요.

```xml
<!-- 개발시 true, 배포시 false 권장 -->
<meta-data
    android:name="WiseTrackerLogState"
    android:value="true" />
```

## 2. Install

### 2.1 Oraganic Install

##### 1) 안드로이드 단말기에 앱이 기설치된 경우 앱을 제거해 주세요.
##### 2) 안드로이드 단말기에 와이즈트래커 SDK가 포함된 앱을 설치해 주세요. 
##### 3) Android Studio 로그캣을 활성화 합니다.
##### 4) 로그캣에 `WiseTracker Validation` 필터를 걸어주세요.
##### 5) 앱을 실행해 주세요.
##### 6) 콘솔창에 출력된 로그를 확인해 주세요.
![](http://www.wisetracker.co.kr/wp-content/uploads/2020/04/android-organic-install.png)


### 2.2 Non-Organic Install

##### 1) 안드로이드 단말기에 앱이 기설치된 경우 앱을 제거해 주세요.
##### 2) 랜딩 URL에 사용 앱의 안드로이드 패키지를 넣어 주세요.
http://test.wisetracker.co.kr/landing/<YOUR_PACKAGE>
##### 3) URL을 이메일, 메신저를 통해 전송후 해당 URL을 클릭해 주세요.
##### 4) 클릭시 해당 앱의 구글 플레이 스토어로 이동합니다. 앱을 설치 하지 않고, 5번 단계를 진행해 주세요.
##### 5) 안드로이드 단말기에 와이즈트래커 SDK가 포함된 앱을 설치해 주세요. 
##### 6) Android Studio 로그캣을 활성화 합니다.
##### 7) 로그캣에 `WiseTracker Validation` 필터를 걸어주세요.
##### 8) 앱을 실행해 주세요.
##### 9) 콘솔창에 출력된 로그를 확인해 주세요.
![](http://www.wisetracker.co.kr/wp-content/uploads/2020/04/android-non-organic-install.png)

## 3. Click
`Click` 이벤트 발생시 태깅시 입력했던 값을 로그를 통해 확인할 수 있습니다.
![](http://www.wisetracker.co.kr/wp-content/uploads/2020/04/android-click-event.png)
 
## 4. Goal
`Goal` 이벤트 발생시 태깅시 입력했던 값을 로그를 통해 확인할 수 있습니다.
![](http://www.wisetracker.co.kr/wp-content/uploads/2020/04/android-goal-event.png)
 
## 5. Purchase
`구매` 이벤트 발생시 태깅시 입력했던 값을 로그를 통해 확인할 수 있습니다.
![](http://www.wisetracker.co.kr/wp-content/uploads/2020/04/android-revenue-event.png)
 
 